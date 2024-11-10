#include "dolphin/gx/GX.h"
#include "dolphin/os/OS.h"
#include "dolphin/vi/vi.h"
#include "dolphin/base/PPCArch.h"

char* __GXVersion = "<< Dolphin SDK - GX    release build: Nov 10 2004 06:27:12 (0x2301) >>";

static GXData gxData;

static GXFifoObj FifoObj;

GXData* const gx = &gxData;

GXTexRegion* __GXDefaultTexRegionCallback(const GXTexObj* obj, GXTexMapID id) {
    GXTexFmt format;

    format = GXGetTexObjFmt(obj);

    if (format != GX_TF_C4 && format != GX_TF_C8 && format != GX_TF_C14X2) {
        return &gx->TexRegions0[gx->nextTexRgn++ % GX_MAX_TEXMAP];
    } else {
        return &gx->TexRegions1[gx->nextTexRgnCI++ % 4];
    }
}

GXTlutRegion* __GXDefaultTlutRegionCallback(u32 tlut) {
    if (tlut >= 0x14) {
        return NULL;
    } else {
        return &gx->TlutRegions[tlut];
    }
}

u32 resetFuncRegistered;

u32 calledOnce;

OSTime time;

u32 peCount;

vu16* __memReg;

u16* __peReg;

u16* __cpReg;

/* ############################################################################################## */
u32* __piReg;

static u16 DefaultTexData[] ALIGN_DECL(32) = {
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};

static GXVtxAttrFmtList GXDefaultVATList[] = {
    {GX_VA_POS, GX_POS_XYZ, GX_F32, 0},
    {GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0},
    {GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0},
    {GX_VA_CLR1, GX_CLR_RGBA, GX_RGBA8, 0},
    {GX_VA_TEX0, GX_TEX_ST, GX_F32, 0},
    {GX_VA_TEX1, GX_TEX_ST, GX_F32, 0},
    {GX_VA_TEX2, GX_TEX_ST, GX_F32, 0},
    {GX_VA_TEX3, GX_TEX_ST, GX_F32, 0},
    {GX_VA_TEX4, GX_TEX_ST, GX_F32, 0},
    {GX_VA_TEX5, GX_TEX_ST, GX_F32, 0},
    {GX_VA_TEX6, GX_TEX_ST, GX_F32, 0},
    {GX_VA_TEX7, GX_TEX_ST, GX_F32, 0},
    {GX_VA_NULL, GX_COMPCNT_NULL, GX_COMP_NULL, 0},
};

static f32 GXDefaultProjData[] = {1.0f, 0.0f, 1.0f, 0.0f, -1.0f, -2.0f, 0.0f};

static u32 GXTexRegionAddrTable[] = {
    0x00000, 0x10000, 0x20000, 0x30000, 0x40000, 0x50000, 0x60000, 0x70000, 0x08000, 0x18000,
    0x28000, 0x38000, 0x48000, 0x58000, 0x68000, 0x78000, 0x00000, 0x90000, 0x20000, 0xB0000,
    0x40000, 0x98000, 0x60000, 0xB8000, 0x80000, 0x10000, 0xA0000, 0x30000, 0x88000, 0x50000,
    0xA8000, 0x70000, 0x00000, 0x90000, 0x20000, 0xB0000, 0x40000, 0x90000, 0x60000, 0xB0000,
    0x80000, 0x10000, 0xA0000, 0x30000, 0x80000, 0x50000, 0xA0000, 0x70000,
};

static void EnableWriteGatherPipe() {
    u32 hid2;  // r31
    hid2 = PPCMfhid2();
    PPCMtwpar(OSUncachedToPhysical((void*)GXFIFO_ADDR));
    hid2 |= 0x40000000;
    PPCMthid2(hid2);
}

GXFifoObj* GXInit(void* base, u32 size) {
    u32 i;
    u32 pad2;  // for stack matching

    OSRegisterVersion(__GXVersion);
    gx->inDispList = GX_FALSE;
    gx->dlSaveContext = GX_TRUE;

    gx->tcsManEnab = 0;
    gx->tevTcEnab = 0;

    GXSetMisc(GX_MT_XF_FLUSH, 0);

    __piReg = (void*)OSPhysicalToUncached(GX_PI_ADDR);
    __cpReg = (void*)OSPhysicalToUncached(GX_CP_ADDR);
    __peReg = (void*)OSPhysicalToUncached(GX_PE_ADDR);
    __memReg = (void*)OSPhysicalToUncached(GX_MEM_ADDR);

    __GXFifoInit();

    GXInitFifoBase(&FifoObj, base, size);
    GXSetCPUFifo(&FifoObj);
    GXSetGPFifo(&FifoObj);

    __GXPEInit();
    EnableWriteGatherPipe();

    gx->genMode = 0;
    SET_REG_FIELD(gx->genMode, 8, 24, 2);

    gx->bpMask = 255;
    SET_REG_FIELD(gx->bpMask, 8, 24, 2);

    gx->lpSize = 0;
    SET_REG_FIELD(gx->lpSize, 8, 24, 2);

    for (i = 0; i < GX_MAX_TEVSTAGE; i++) {
        gx->tevc[i] = 0;
        gx->teva[i] = 0;
        gx->tref[i / 2] = 0;
        gx->texmapId[i] = GX_TEXMAP_NULL;

        SET_REG_FIELD(gx->tevc[i], 8, 24, 2);
        SET_REG_FIELD(gx->teva[i], 8, 24, 2);
        SET_REG_FIELD(gx->tevKsel[i / 2], 8, 24, 2);
        SET_REG_FIELD(gx->tref[i / 2], 8, 24, 2);
    }

    gx->iref = 0;
    SET_REG_FIELD(gx->iref, 8, 24, 2);

    for (i = 0; i < GX_MAXCOORD; i++) {
        gx->suTs0[i] = 0;
        gx->suTs1[i] = 0;

        SET_REG_FIELD(gx->suTs0[i], 8, 24, 2);
        SET_REG_FIELD(gx->suTs1[i], 8, 24, 2);
    }

    SET_REG_FIELD(gx->suScis0, 8, 24, 2);
    SET_REG_FIELD(gx->suScis1, 8, 24, 2);

    SET_REG_FIELD(gx->cmode0, 8, 24, 2);
    SET_REG_FIELD(gx->cmode1, 8, 24, 2);

    SET_REG_FIELD(gx->zmode, 8, 24, 2);
    SET_REG_FIELD(gx->peCtrl, 8, 24, 2);

    SET_REG_FIELD(gx->cpTex, 2, 7, 2);

    gx->zScale = 1.6777216E7f;
    gx->zOffset = 0.0f;

    gx->dirtyState = 0;
    gx->dirtyVAT = 0;

    {
        u32 val1;
        u32 val2;

        val2 = OS_BUS_CLOCK / 500;

        __GXFlushTextureState();

        val1 = (val2 / 2048) | 0x69000400;

        GFWriteBPCmd(val1);

        __GXFlushTextureState();

        val1 = (val2 / 4224) | 0x46000200;
        GFWriteBPCmd(val1);
    }

    for (i = 0; i < GX_MAX_TEXMAP; i++) {
        GXInitTexCacheRegion(&gx->TexRegions0[i], GX_FALSE, GXTexRegionAddrTable[i],
                             GX_TEXCACHE_32K, GXTexRegionAddrTable[i + 8], GX_TEXCACHE_32K);
        GXInitTexCacheRegion(&gx->TexRegions1[i], GX_FALSE, GXTexRegionAddrTable[i + 16],
                             GX_TEXCACHE_32K, GXTexRegionAddrTable[i + 24], GX_TEXCACHE_32K);
        // GXInitTexCacheRegion(&__GXData->TexRegions2[i], GX_TRUE, GXTexRegionAddrTable[i + 32],
        //                      GX_TEXCACHE_32K, GXTexRegionAddrTable[i + 40], GX_TEXCACHE_32K);
    }

    for (i = 0; i < GX_MAX_TLUT; i++) {
        GXInitTlutRegion(&gx->TlutRegions[i], 0xC0000 + 0x2000 * i, GX_TLUT_256);
    }

    for (i = 0; i < GX_MAX_BIGTLUT; i++) {
        GXInitTlutRegion(&gx->TlutRegions[i + 16], 0xE0000 + 0x8000 * i, GX_TLUT_1K);
    }

    GX_SET_CP_REG(3, 0);

    SET_REG_FIELD(gx->perfSel, 4, 4, 2);

    GXFIFO.u8 = 0x8;
    GXFIFO.u8 = 0x20;
    GXFIFO.u32 = gx->perfSel;

    GXFIFO.u8 = 0x10;
    GXFIFO.u32 = 0x1006;
    GXFIFO.u32 = 0;

    GFWriteBPCmd(0x23000000);

    GFWriteBPCmd(0x24000000);

    GFWriteBPCmd(0x67000000);

    __GXSetTmemConfig(2);
    __GXInitGX();

    return &FifoObj;
}

void __GXInitGX(void) {
    GXRenderModeObj* renderObj;
    Mtx ident;
    GXColor clearColor = {64, 64, 64, 255};
    GXColor ambColor = {0, 0, 0, 0};
    GXColor matColor = {255, 255, 255, 255};
    u32 i;

    switch (VIGetTvFormat()) {
    case VI_NTSC:
        renderObj = &GXNtsc480IntDf;
        break;

    case VI_PAL:
        renderObj = &GXPal528IntDf;
        break;

    case VI_EURGB60:
        renderObj = &GXEurgb60Hz480IntDf;
        break;

    case VI_MPAL:
        renderObj = &GXMpal480IntDf;
        break;

    default:
        renderObj = &GXNtsc480IntDf;
        break;
    }

    GXSetCopyClear(clearColor, 0xFFFFFF);

    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXSetTexCoordGen(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_IDENTITY);
    GXSetTexCoordGen(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX2, GX_IDENTITY);
    GXSetTexCoordGen(GX_TEXCOORD3, GX_TG_MTX2x4, GX_TG_TEX3, GX_IDENTITY);
    GXSetTexCoordGen(GX_TEXCOORD4, GX_TG_MTX2x4, GX_TG_TEX4, GX_IDENTITY);
    GXSetTexCoordGen(GX_TEXCOORD5, GX_TG_MTX2x4, GX_TG_TEX5, GX_IDENTITY);
    GXSetTexCoordGen(GX_TEXCOORD6, GX_TG_MTX2x4, GX_TG_TEX6, GX_IDENTITY);
    GXSetTexCoordGen(GX_TEXCOORD7, GX_TG_MTX2x4, GX_TG_TEX7, GX_IDENTITY);

    GXSetNumTexGens(1);
    GXClearVtxDesc();
    GXInvalidateVtxCache();

    for (i = GX_VA_POS; i <= GX_LIGHT_ARRAY; i++) {
        GXSetArray((GXAttr)i, gx, 0);
    }

    for (i = 0; i < GX_MAX_VTXFMT; i++) {
        GXSetVtxAttrFmtv((GXVtxFmt)i, GXDefaultVATList);
    }

    GXSetLineWidth(6, GX_TO_ZERO);
    GXSetPointSize(6, GX_TO_ZERO);
    GXEnableTexOffsets(GX_TEXCOORD0, GX_FALSE, GX_FALSE);
    GXEnableTexOffsets(GX_TEXCOORD1, GX_FALSE, GX_FALSE);
    GXEnableTexOffsets(GX_TEXCOORD2, GX_FALSE, GX_FALSE);
    GXEnableTexOffsets(GX_TEXCOORD3, GX_FALSE, GX_FALSE);
    GXEnableTexOffsets(GX_TEXCOORD4, GX_FALSE, GX_FALSE);
    GXEnableTexOffsets(GX_TEXCOORD5, GX_FALSE, GX_FALSE);
    GXEnableTexOffsets(GX_TEXCOORD6, GX_FALSE, GX_FALSE);
    GXEnableTexOffsets(GX_TEXCOORD7, GX_FALSE, GX_FALSE);

    ident[0][0] = 1.0f;
    ident[0][1] = 0.0f;
    ident[0][2] = 0.0f;
    ident[0][3] = 0.0f;

    ident[1][0] = 0.0f;
    ident[1][1] = 1.0f;
    ident[1][2] = 0.0f;
    ident[1][3] = 0.0f;

    ident[2][0] = 0.0f;
    ident[2][1] = 0.0f;
    ident[2][2] = 1.0f;
    ident[2][3] = 0.0f;

    GXLoadPosMtxImm(ident, GX_PNMTX0);
    GXLoadNrmMtxImm(ident, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);

    GXLoadTexMtxImm(ident, GX_IDENTITY, GX_MTX3x4);
    GXLoadTexMtxImm(ident, GX_PTIDENTITY, GX_MTX3x4);

    GXSetViewport(0.0f, 0.0f, renderObj->fb_width, renderObj->xfb_height, 0.0f, 1.0f);

    GXSetProjectionv(GXDefaultProjData);

    GXSetCoPlanar(GX_FALSE);
    GXSetCullMode(GX_CULL_BACK);
    GXSetClipMode(GX_CLIP_ENABLE);

    GXSetScissor(0, 0, renderObj->fb_width, renderObj->efb_height);
    GXSetScissorBoxOffset(0, 0);

    GXSetNumChans(0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetChanAmbColor(GX_COLOR0A0, ambColor);
    GXSetChanMatColor(GX_COLOR0A0, matColor);

    GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetChanAmbColor(GX_COLOR1A1, ambColor);
    GXSetChanMatColor(GX_COLOR1A1, matColor);

    GXInvalidateTexAll();
    gx->nextTexRgn = 0;
    gx->nextTexRgnCI = 0;
    GXSetTexRegionCallback(__GXDefaultTexRegionCallback);
    GXSetTlutRegionCallback(__GXDefaultTlutRegionCallback);

    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD2, GX_TEXMAP2, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE3, GX_TEXCOORD3, GX_TEXMAP3, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE4, GX_TEXCOORD4, GX_TEXMAP4, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE5, GX_TEXCOORD5, GX_TEXMAP5, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE6, GX_TEXCOORD6, GX_TEXMAP6, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE7, GX_TEXCOORD7, GX_TEXMAP7, GX_COLOR0A0);

    GXSetTevOrder(GX_TEVSTAGE8, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE9, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE10, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE11, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE12, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE13, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE14, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE15, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);

    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);

    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);

    GXSetZTexture(GX_ZT_DISABLE, GX_TF_Z8, 0);

    for (i = 0; i < GX_MAX_TEVSTAGE; i++) {
        GXSetTevKColorSel((GXTevStageID)i, GX_TEV_KCSEL_1_4);
        GXSetTevKAlphaSel((GXTevStageID)i, GX_TEV_KASEL_1);
        GXSetTevSwapMode((GXTevStageID)i, GX_TEV_SWAP0, GX_TEV_SWAP0);
    }

    GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_RED, GX_CH_RED, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_GREEN, GX_CH_GREEN, GX_CH_GREEN, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE, GX_CH_ALPHA);

    for (i = 0; i < GX_MAX_TEVSTAGE; i++) {
        GXSetTevDirect((GXTevStageID)i);
    }

    GXSetNumIndStages(0);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE1, GX_ITS_1, GX_ITS_1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE2, GX_ITS_1, GX_ITS_1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE3, GX_ITS_1, GX_ITS_1);

    GXSetFog(GX_FOG_NONE, 0.0f, 1.0f, 0.1f, 1.0f, ambColor);
    GXSetFogRangeAdj(GX_FALSE, 0, NULL);

    GXSetBlendMode(GX_BM_NONE, GX_BL_SRC_ALPHA, GX_BL_INV_SRC_ALPHA, GX_LO_CLEAR);

    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetZCompLoc(GX_TRUE);

    GXSetDither(GX_TRUE);

    GXSetDstAlpha(GX_FALSE, 0);
    GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);

    GXSetFieldMask(GX_TRUE, GX_TRUE);
    GXSetFieldMode(
        (GXBool)renderObj->field_rendering,
        (GXBool)((renderObj->vi_height == 2 * renderObj->xfb_height) ? GX_TRUE : GX_FALSE));

    GXSetDispCopySrc(0, 0, renderObj->fb_width, renderObj->efb_height);
    GXSetDispCopyDst(renderObj->fb_width, renderObj->efb_height);
    GXSetDispCopyYScale((f32)renderObj->xfb_height / (f32)renderObj->efb_height);
    GXSetCopyClamp(GX_CLAMP_BOTH);

    GXSetCopyFilter(renderObj->antialiasing, renderObj->sample_pattern, GX_TRUE,
                    renderObj->vfilter);
    GXSetDispCopyGamma(GX_GM_1_0);
    GXSetDispCopyFrame2Field(GX_COPY_PROGRESSIVE);
    GXClearBoundingBox();

    GXPokeColorUpdate(GX_TRUE);
    GXPokeAlphaUpdate(GX_TRUE);
    GXPokeDither(GX_FALSE);
    GXPokeBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ONE, GX_LO_SET);
    GXPokeAlphaMode(GX_ALWAYS, 0);
    GXPokeAlphaRead(GX_READ_FF);
    GXPokeDstAlpha(GX_FALSE, 0);
    GXPokeZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    GXSetGPMetric(GX_PERF0_NONE, GX_PERF1_NONE);
    GXClearGPMetric();
}
