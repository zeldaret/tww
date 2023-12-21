//
// Generated by dtk
// Translation Unit: J3DSys.cpp
//

#include "JSystem/J3DGraphBase/J3DSys.h"
#include "JSystem/J3DGraphBase/J3DGD.h"
#include "JSystem/J3DGraphBase/J3DTexture.h"
#include "JSystem/J3DGraphBase/J3DTevs.h"
#include "JSystem/J3DGraphBase/J3DShape.h"
#include "dolphin/os/OS.h"
#include "global.h"

extern void JRNLoadTexCached(GXTexMapID, u32, GXTexCacheSize, u32, GXTexCacheSize);
extern void makeTexCoordTable();
extern void makeAlphaCmpTable();
extern void makeZModeTable();
extern void makeTevSwapTable();

/* 802D8AA8-802D8B8C       .text __ct__6J3DSysFv */
J3DSys::J3DSys() {
    makeTexCoordTable();
    makeTevSwapTable();
    makeAlphaCmpTable();
    makeZModeTable();

    mFlags = 0;
    MTXIdentity(mViewMtx);
    mDrawMode = 1;
    mMaterialMode = 0;
    mModel = NULL;
    mShape = NULL;
    for (u32 i = 0; i < ARRAY_SIZE(mDrawBuffer); i++)
        mDrawBuffer[i] = NULL;
    mTexture = NULL;
    mMatPacket = NULL;
    mShapePacket = NULL;
    mModelDrawMtx = NULL;
    mModelNrmMtx = NULL;
    mVtxPos = NULL;
    mVtxNrm = NULL;
    mVtxCol = NULL;
    field_0x11c = NULL;
    field_0x104 = NULL;
    field_0x120 = NULL;

    for (u32 i = 0; i < 8; i ++) {
        sTexCoordScaleTable[i].field_0x00 = 1;
        sTexCoordScaleTable[i].field_0x02 = 1;
        sTexCoordScaleTable[i].field_0x04 = 0;
        sTexCoordScaleTable[i].field_0x06 = 0;
    }
}

/* 802D8B8C-802D8BB0       .text loadPosMtxIndx__6J3DSysCFiUs */
void J3DSys::loadPosMtxIndx(int addr, u16 indx) const {
    J3DFifoLoadIndx(GX_CMD_LOAD_INDX_A, indx, 0xB000 | ((u16)(addr * 0x0C)));
}

/* 802D8BB0-802D8BD8       .text loadNrmMtxIndx__6J3DSysCFiUs */
void J3DSys::loadNrmMtxIndx(int addr, u16 indx) const {
    J3DFifoLoadIndx(GX_CMD_LOAD_INDX_B, indx, 0x8000 | ((u16)((addr * 0x09) + 0x400)));
}

/* 802D8BD8-802D8C58       .text J3DFifoLoadPosMtxImm__FPA4_fUl */
void J3DFifoLoadPosMtxImm(Mtx mtx, u32 idx) {
    J3DFifoWriteXFCmd(idx << 2, 12);
    u32 * mtx_u32 = (u32*)mtx;

    GFX_FIFO(u32) = mtx_u32[0];
    GFX_FIFO(u32) = mtx_u32[1];
    GFX_FIFO(u32) = mtx_u32[2];
    GFX_FIFO(u32) = mtx_u32[3];

    GFX_FIFO(u32) = mtx_u32[4];
    GFX_FIFO(u32) = mtx_u32[5];
    GFX_FIFO(u32) = mtx_u32[6];
    GFX_FIFO(u32) = mtx_u32[7];

    GFX_FIFO(u32) = mtx_u32[8];
    GFX_FIFO(u32) = mtx_u32[9];
    GFX_FIFO(u32) = mtx_u32[10];
    GFX_FIFO(u32) = mtx_u32[11];
}

/* 802D8C58-802D8CC4       .text J3DFifoLoadNrmMtxImm__FPA4_fUl */
void J3DFifoLoadNrmMtxImm(Mtx mtx, u32 idx) {
    J3DFifoWriteXFCmd(0x400 + (idx * 3), 9);
    u32 * mtx_u32 = (u32*)mtx;

    GFX_FIFO(u32) = mtx_u32[0];
    GFX_FIFO(u32) = mtx_u32[1];
    GFX_FIFO(u32) = mtx_u32[2];

    GFX_FIFO(u32) = mtx_u32[4];
    GFX_FIFO(u32) = mtx_u32[5];
    GFX_FIFO(u32) = mtx_u32[6];

    GFX_FIFO(u32) = mtx_u32[8];
    GFX_FIFO(u32) = mtx_u32[9];
    GFX_FIFO(u32) = mtx_u32[10];
}

/* 802D8CC4-802D8D30       .text J3DFifoLoadNrmMtxImm3x3__FPA3_fUl */
void J3DFifoLoadNrmMtxImm3x3(Mtx33 mtx, u32 idx) {
    J3DFifoWriteXFCmd(0x400 + (idx * 3), 9);
    u32 * mtx_u32 = (u32*)mtx;

    GFX_FIFO(u32) = mtx_u32[0];
    GFX_FIFO(u32) = mtx_u32[1];
    GFX_FIFO(u32) = mtx_u32[2];

    GFX_FIFO(u32) = mtx_u32[3];
    GFX_FIFO(u32) = mtx_u32[4];
    GFX_FIFO(u32) = mtx_u32[5];

    GFX_FIFO(u32) = mtx_u32[6];
    GFX_FIFO(u32) = mtx_u32[7];
    GFX_FIFO(u32) = mtx_u32[8];
}

u8 NullTexData[16] ALIGN_DECL(32) = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

Mtx j3dIdentityMtx = {
    1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
};

/* 802D8D30-802D8EE0       .text setTexCacheRegion__6J3DSysF15_GXTexCacheSize */
void J3DSys::setTexCacheRegion(GXTexCacheSize size) {
    const u32 kSize[] = {
        0x00008000,
        0x00020000,
        0x00080000,
        0x00000000,
    };
    const u32 kRegionNum[] = {8, 4, 1, 0};

    u32 regionNum = kRegionNum[size];
    mTexCacheRegionNum = regionNum;

    if (!!(mFlags & 0x80000000)) {
        for (u32 i = 0; i < regionNum; i++) {
            if (!!(i & 1)) {
                GXInitTexCacheRegion(&mTexCacheRegion[i], GX_FALSE, i * kSize[size] + 0x80000, size, i * kSize[size], size);
                JRNLoadTexCached((GXTexMapID)i, i * kSize[size] + 0x80000, size, i * kSize[size], size);
            } else {
                GXInitTexCacheRegion(&mTexCacheRegion[i], GX_FALSE, i * kSize[size], size, i * kSize[size] + 0x80000, size);
                JRNLoadTexCached((GXTexMapID)i, i * kSize[size], size, i * kSize[size] + 0x80000, size);
            }
        }
    } else {
        for (u32 i = 0; i < regionNum; i++) {
            GXInitTexCacheRegion(&mTexCacheRegion[i], GX_FALSE, i * kSize[size], size, i * kSize[size] + 0x80000, size);
            JRNLoadTexCached((GXTexMapID)i, i * kSize[size], size, i * kSize[size] + 0x80000, size);
        }
    }
}

/* 802D8EE0-802D956C       .text drawInit__6J3DSysFv */
void J3DSys::drawInit() {
    GXSetMisc(2, 0);
    GXInvalidateVtxCache();
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetCullMode(GX_CULL_BACK);
    GXSetCoPlanar(GX_FALSE);
    GXSetClipMode(GX_CLIP_ENABLE);
    GXSetColorUpdate(GX_TRUE);
    GXSetDither(GX_TRUE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRC_ALPHA, GX_BL_INV_SRC_ALPHA, GX_LO_NOOP);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetZCompLoc(GX_TRUE);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR1, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_CLR_RGBA, GX_RGBA4, 7);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX1, GX_CLR_RGBA, GX_RGBA4, 7);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX2, GX_CLR_RGBA, GX_RGBA4, 7);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX3, GX_CLR_RGBA, GX_RGBA4, 7);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX4, GX_CLR_RGBA, GX_RGBA4, 7);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX5, GX_CLR_RGBA, GX_RGBA4, 7);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX6, GX_CLR_RGBA, GX_RGBA4, 7);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX7, GX_CLR_RGBA, GX_RGBA4, 7);

    GXSetNumIndStages(0);
    reinitTexture();

    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE3, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE4, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE5, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE6, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE7, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE8, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE9, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE10, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE11, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE12, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE13, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE14, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE15, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);

    for (u32 i = 0; i < 10; i++)
        GXLoadTexMtxImm(j3dIdentityMtx, GX_TEXMTX0 + i * 3, GX_MTX3x4);

    Mtx23 indTexMtx = {
        {0.5f, 0.0f, 0.0f},
        {0.0f, 0.5f, 0.0f},
    };

    u8 i;
    for (i = 0; i < 3; i++)
        GXSetIndTexMtx((GXIndTexMtxID)(GX_ITM_0 + i), (f32*)indTexMtx, 1);

    GXSetChanMatColor(GX_COLOR0A0, j3dDefaultColInfo);
    GXSetChanMatColor(GX_COLOR1A1, j3dDefaultColInfo);

    GXSetNumChans(j3dDefaultColorChanNum);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_NONE);

    for (i = 0; i < GX_MAX_TEXMAP; i++)
        GXSetTexCoordGen2((GXTexCoordID)i, (GXTexGenType)j3dDefaultTexCoordInfo[i].mTexGenType,
                          (GXTexGenSrc)j3dDefaultTexCoordInfo[i].mTexGenSrc,
                          j3dDefaultTexCoordInfo[i].mTexGenMtx, GX_FALSE, GX_PTIDENTITY);

    for (i = 0; i < GX_MAX_INDTEXSTAGE; i++)
        GXSetIndTexCoordScale((GXIndTexStageID)i, GX_ITS_1, GX_ITS_1);

    for (i = 0; i < GX_MAX_TEVREG; i++)
        GXSetTevKColor((GXTevKColorID)i, j3dDefaultTevKColor);

    for (i = 0; i < GX_MAX_TEVREG; i++)
        GXSetTevColorS10((GXTevRegID)i, j3dDefaultTevColor);

    for (i = 0; i < GX_MAX_TEVSTAGE; i++) {
        GXSetTevColorIn((GXTevStageID)i, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
        GXSetTevColorOp((GXTevStageID)i, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE,
                        GX_TEVPREV);
        GXSetTevAlphaIn((GXTevStageID)i, GX_CA_RASA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevAlphaOp((GXTevStageID)i, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE,
                        GX_TEVPREV);
    }

    for (i = 0; i < GX_MAX_TEVSTAGE; i++)
        GXSetTevSwapMode((GXTevStageID)i, GX_TEV_SWAP0, GX_TEV_SWAP0);

    GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_RED, GX_CH_RED, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_GREEN, GX_CH_GREEN, GX_CH_GREEN, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE, GX_CH_ALPHA);

    for (i = 0; i < GX_MAX_TEVSTAGE; i++)
        GXSetTevIndirect((GXTevStageID)i, GX_INDTEXSTAGE0, GX_ITF_8, GX_ITB_NONE, GX_ITM_OFF,
                         GX_ITW_OFF, GX_ITW_OFF, GX_FALSE, GX_FALSE, GX_ITBA_OFF);

    i_OSInitFastCast();
    setTexCacheRegion(GX_TEXCACHE_32K);
}

/* 802D956C-802D95C8       .text reinitGX__6J3DSysFv */
void J3DSys::reinitGX() {
    reinitGenMode();
    reinitLighting();
    reinitTransform();
    reinitTexture();
    reinitTevStages();
    reinitIndStages();
    reinitPixelProc();
}

/* 802D95C8-802D9614       .text reinitGenMode__6J3DSysFv */
void J3DSys::reinitGenMode() {
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetNumIndStages(0);
    GXSetCullMode(GX_CULL_BACK);
    GXSetCoPlanar(GX_FALSE);
}

GXColor ColorBlack = {0x00, 0x00, 0x00, 0x00};
GXColor ColorWhite = {0xFF, 0xFF, 0xFF, 0xFF};

/* 802D9614-802D96C0       .text reinitLighting__6J3DSysFv */
void J3DSys::reinitLighting() {
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanAmbColor(GX_COLOR0A0, ColorBlack);
    GXSetChanAmbColor(GX_COLOR1A1, ColorBlack);
    GXSetChanMatColor(GX_COLOR0A0, ColorWhite);
    GXSetChanMatColor(GX_COLOR1A1, ColorWhite);
}

/* 802D96C0-802D97C4       .text reinitTransform__6J3DSysFv */
void J3DSys::reinitTransform() {
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX2, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD3, GX_TG_MTX2x4, GX_TG_TEX3, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD4, GX_TG_MTX2x4, GX_TG_TEX4, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD5, GX_TG_MTX2x4, GX_TG_TEX5, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD6, GX_TG_MTX2x4, GX_TG_TEX6, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD7, GX_TG_MTX2x4, GX_TG_TEX7, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
}

/* 802D97C4-802D9868       .text reinitTexture__6J3DSysFv */
void J3DSys::reinitTexture() {
    GXTexObj texObj;
    GXInitTexObj(&texObj, NullTexData, 4, 4, GX_TF_IA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXLoadTexObj(&texObj, GX_TEXMAP0);
    GXLoadTexObj(&texObj, GX_TEXMAP1);
    GXLoadTexObj(&texObj, GX_TEXMAP2);
    GXLoadTexObj(&texObj, GX_TEXMAP3);
    GXLoadTexObj(&texObj, GX_TEXMAP4);
    GXLoadTexObj(&texObj, GX_TEXMAP5);
    GXLoadTexObj(&texObj, GX_TEXMAP6);
    GXLoadTexObj(&texObj, GX_TEXMAP7);
}

/* 802D9868-802D9B70       .text reinitTevStages__6J3DSysFv */
void J3DSys::reinitTevStages() {
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE3, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE4, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE5, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE6, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE7, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE8, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE9, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE10, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE11, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE12, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE13, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE14, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE15, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);

    GXSetTevColor(GX_TEVREG0, ColorWhite);
    GXSetTevColor(GX_TEVREG1, ColorWhite);
    GXSetTevColor(GX_TEVREG2, ColorWhite);
    GXSetTevKColor(GX_KCOLOR0, ColorWhite);
    GXSetTevKColor(GX_KCOLOR1, ColorWhite);
    GXSetTevKColor(GX_KCOLOR2, ColorWhite);
    GXSetTevKColor(GX_KCOLOR3, ColorWhite);

    for (u32 i = 0; i < GX_MAX_TEVSTAGE; i++) {
        GXSetTevColorIn((GXTevStageID)i, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
        GXSetTevColorOp((GXTevStageID)i, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn((GXTevStageID)i, GX_CA_RASA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevAlphaOp((GXTevStageID)i, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevKColorSel((GXTevStageID)i, GX_TEV_KCSEL_1_4);
        GXSetTevKAlphaSel((GXTevStageID)i, GX_TEV_KASEL_1);
        GXSetTevSwapMode((GXTevStageID)i, GX_TEV_SWAP0, GX_TEV_SWAP0);
    }

    GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_RED, GX_CH_RED, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_GREEN, GX_CH_GREEN, GX_CH_GREEN, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE, GX_CH_ALPHA);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
}

Mtx23 IndMtx = {0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f};

/* 802D9B70-802D9C68       .text reinitIndStages__6J3DSysFv */
void J3DSys::reinitIndStages() {
    for (u32 i = 0; i < GX_MAX_TEVSTAGE; i++) {
        GXSetTevDirect((GXTevStageID)i);
    }

    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD0, GX_TEXMAP0);
    GXSetIndTexOrder(GX_INDTEXSTAGE1, GX_TEXCOORD1, GX_TEXMAP1);
    GXSetIndTexOrder(GX_INDTEXSTAGE2, GX_TEXCOORD2, GX_TEXMAP2);
    GXSetIndTexOrder(GX_INDTEXSTAGE3, GX_TEXCOORD3, GX_TEXMAP3);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE1, GX_ITS_1, GX_ITS_1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE2, GX_ITS_1, GX_ITS_1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE3, GX_ITS_1, GX_ITS_1);
    GXSetIndTexMtx(GX_ITM_0, (f32*)IndMtx, 1);
    GXSetIndTexMtx(GX_ITM_1, (f32*)IndMtx, 1);
    GXSetIndTexMtx(GX_ITM_2, (f32*)IndMtx, 1);
}

/* 802D9C68-802D9CFC       .text reinitPixelProc__6J3DSysFv */
void J3DSys::reinitPixelProc() {
    GXSetBlendMode(GX_BM_NONE, GX_BL_SRC_ALPHA, GX_BL_INV_SRC_ALPHA, GX_LO_CLEAR);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);
    GXSetDither(GX_TRUE);
    GXSetFog(GX_FOG_NONE, 0.0f, 1.0f, 0.1f, 1.0f, ColorBlack);
    GXSetFogRangeAdj(GX_FALSE, 0, NULL);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetZCompLoc(GX_TRUE);
}

J3DSys j3dSys;
Mtx J3DSys::mCurrentMtx;
Vec J3DSys::mCurrentS;
Vec J3DSys::mParentS;
J3DTexCoordScaleInfo J3DSys::sTexCoordScaleTable[8];

u32 j3dDefaultViewNo;
