#include "dolphin/gx/GXPixel.h"
#include "dolphin/gx/GX.h"

void GXSetFog(GXFogType type, f32 startz, f32 endz, f32 nearz, f32 farz, GXColor color) {
    u32 fogclr, fog0, fog1, fog2, fog3;
    f32 A, B, B_mant, C, a, c;
    u32 B_expn;
    u32 b_m;
    u32 b_s;
    u32 a_hex;
    u32 c_hex;

    if (farz == nearz || endz == startz) {
        A = 0.0f;
        B = 0.5f;
        C = 0.0f;
    } else {
        A = (farz * nearz) / ((farz - nearz) * (endz - startz));
        B = farz / (farz - nearz);
        C = startz / (endz - startz);
    }

    B_mant = B;
    B_expn = 0;
    while (B_mant > 1.0) {
        B_mant /= 2;
        B_expn++;
    }
    while (B_mant > 0 && B_mant < 0.5) {
        B_mant *= 2;
        B_expn--;
    }

    a = A / (f32)(1 << (B_expn + 1));
    b_m = 8.388638e6f * B_mant;
    b_s = B_expn + 1;
    c = C;

    fog1 = 0;
    SET_REG_FIELD(fog1, 24, 0, b_m);
    SET_REG_FIELD(fog1, 8, 24, 0xEF);

    fog2 = 0;
    SET_REG_FIELD(fog2, 5, 0, b_s);
    SET_REG_FIELD(fog2, 8, 24, 0xF0);

    a_hex = *(u32*)&a;
    c_hex = *(u32*)&c;

    fog0 = 0;
    SET_REG_FIELD(fog0, 11, 0, (a_hex >> 12) & 0x7FF);
    SET_REG_FIELD(fog0, 8, 11, (a_hex >> 23) & 0xFF);
    SET_REG_FIELD(fog0, 1, 19, (a_hex >> 31));
    SET_REG_FIELD(fog0, 8, 24, 0xEE);

    fog3 = 0;
    SET_REG_FIELD(fog3, 11, 0, (c_hex >> 12) & 0x7FF);
    SET_REG_FIELD(fog3, 8, 11, (c_hex >> 23) & 0xFF);
    SET_REG_FIELD(fog3, 1, 19, (c_hex >> 31));
    SET_REG_FIELD(fog3, 3, 21, type);
    SET_REG_FIELD(fog3, 8, 24, 0xF1);

    fogclr = 0;
    SET_REG_FIELD(fogclr, 8, 0, color.b);
    SET_REG_FIELD(fogclr, 8, 8, color.g);
    SET_REG_FIELD(fogclr, 8, 16, color.r);
    SET_REG_FIELD(fogclr, 8, 24, 0xF2);

    GX_WRITE_RAS_REG(fog0);
    GX_WRITE_RAS_REG(fog1);
    GX_WRITE_RAS_REG(fog2);
    GX_WRITE_RAS_REG(fog3);
    GX_WRITE_RAS_REG(fogclr);

    gx->bpSentNot = GX_FALSE;
}

void GXSetFogRangeAdj(GXBool enable, u16 center, GXFogAdjTable* table) {
    u32 fogRangeReg;
    u32 fogRangeRegK;
    u32 i;

    if (enable) {
        for (i = 0; i < 10; i += 2) {
            fogRangeRegK = 0;
            GX_SET_REG(fogRangeRegK, table->fogVals[i], GX_BP_FOGRANGEK_HI_ST,
                       GX_BP_FOGRANGEK_HI_END);
            GX_SET_REG(fogRangeRegK, table->fogVals[i + 1], GX_BP_FOGRANGEK_LO_ST,
                       GX_BP_FOGRANGEK_LO_END);
            GX_SET_REG(fogRangeRegK, GX_BP_REG_FOGRANGEK0 + (i / 2), 0, 7);
            GX_BP_LOAD_REG(fogRangeRegK);
        }
    }

    fogRangeReg = 0;
    GX_SET_REG(fogRangeReg, center + 342, GX_BP_FOGRANGE_CENTER_ST, GX_BP_FOGRANGE_CENTER_END);
    GX_SET_REG(fogRangeReg, enable, GX_BP_FOGRANGE_ENABLED_ST, GX_BP_FOGRANGE_ENABLED_END);
    GX_SET_REG(fogRangeReg, GX_BP_REG_FOGRANGE, 0, 7);
    GX_BP_LOAD_REG(fogRangeReg);

    gx->bpSentNot = GX_FALSE;
}

void GXSetBlendMode(GXBlendMode type, GXBlendFactor src_factor, GXBlendFactor dst_factor,
                    GXLogicOp op) {
    u32 blendModeReg = gx->cmode0;
    blendModeReg = __rlwimi(blendModeReg, type == GX_BM_SUBTRACT, 11, 20, 20);
    blendModeReg = __rlwimi(blendModeReg, type, 0, 31, 31);
    blendModeReg = __rlwimi(blendModeReg, type == GX_BM_LOGIC, 1, 30, 30);
    blendModeReg = __rlwimi(blendModeReg, op, 12, 16, 19);
    blendModeReg = __rlwimi(blendModeReg, src_factor, 8, 21, 23);
    blendModeReg = __rlwimi(blendModeReg, dst_factor, 5, 24, 26);

    GX_BP_LOAD_REG(blendModeReg);
    gx->cmode0 = blendModeReg;

    gx->bpSentNot = FALSE;
}

void GXSetColorUpdate(GXBool updateEnable) {
    u32 blendModeReg = gx->cmode0;
    blendModeReg = __rlwimi(blendModeReg, updateEnable, 3, 28, 28);
    GX_BP_LOAD_REG(blendModeReg);
    gx->cmode0 = blendModeReg;
    gx->bpSentNot = GX_FALSE;
}

void GXSetAlphaUpdate(GXBool updateEnable) {
    u32 blendModeReg = gx->cmode0;
    blendModeReg = __rlwimi(blendModeReg, updateEnable, 4, 27, 27);
    GX_BP_LOAD_REG(blendModeReg);
    gx->cmode0 = blendModeReg;
    gx->bpSentNot = GX_FALSE;
}

void GXSetZMode(GXBool compareEnable, GXCompare func, GXBool updateEnable) {
    u32 zModeReg = gx->zmode;
    zModeReg = __rlwimi(zModeReg, compareEnable, 0, 31, 31);
    zModeReg = __rlwimi(zModeReg, func, 1, 28, 30);
    zModeReg = __rlwimi(zModeReg, updateEnable, 4, 27, 27);
    GX_BP_LOAD_REG(zModeReg);
    gx->zmode = zModeReg;
    gx->bpSentNot = GX_FALSE;
}

void GXSetZCompLoc(GXBool beforeTex) {
    GX_SET_REG(gx->peCtrl, beforeTex, GX_BP_ZCONTROL_BEFORE_TEX_ST,
               GX_BP_ZCONTROL_BEFORE_TEX_END);
    GX_BP_LOAD_REG(gx->peCtrl);
    gx->bpSentNot = GX_FALSE;
}

void GXSetPixelFmt(GXPixelFmt pixelFmt, GXZFmt16 zFmt) {
    GXBool isZ16;
    static u32 p2f[GX_PF_MAX] = {GX_PF_RGB8_Z24, GX_PF_RGBA6_Z24, GX_PF_RGB565_Z16, GX_PF_Z24,
                                 GX_PF_Y8,       GX_PF_Y8,        GX_PF_Y8,         GX_PF_U8};

    const u32 zControlRegOld = gx->peCtrl;

    GX_SET_REG(gx->peCtrl, p2f[pixelFmt], GX_BP_ZCONTROL_PIXEL_FMT_ST,
               GX_BP_ZCONTROL_PIXEL_FMT_END);
    GX_SET_REG(gx->peCtrl, zFmt, GX_BP_ZCONTROL_Z_FMT_ST, GX_BP_ZCONTROL_Z_FMT_END);

    if (zControlRegOld != gx->peCtrl) {
        GX_BP_LOAD_REG(gx->peCtrl);
        isZ16 = (pixelFmt == GX_PF_RGB565_Z16) ? GX_TRUE : GX_FALSE;
        GX_SET_REG(gx->genMode, isZ16, GX_BP_GENMODE_MULTISAMPLE_ST,
                   GX_BP_GENMODE_MULTISAMPLE_END);
        gx->dirtyState |= GX_DIRTY_GEN_MODE;
    }

    if (p2f[pixelFmt] == GX_PF_Y8) {
        SET_REG_FIELD(gx->cmode1, 2, 9, (pixelFmt - GX_PF_Y8) & 3);
        GX_SET_REG(gx->cmode1, GX_BP_REG_DSTALPHA, 0, 7);
        GX_BP_LOAD_REG(gx->cmode1);
    }

    gx->bpSentNot = FALSE;
}

void GXSetDither(GXBool dither) {
    u32 blendModeReg = gx->cmode0;
    GX_SET_REG(blendModeReg, dither, GX_BP_BLENDMODE_DITHER_ST, GX_BP_BLENDMODE_DITHER_END);
    GX_BP_LOAD_REG(blendModeReg);
    gx->cmode0 = blendModeReg;
    gx->bpSentNot = GX_FALSE;
}

void GXSetDstAlpha(GXBool enable, u8 alpha) {
    u32 dstAlpha = gx->cmode1;
    dstAlpha = __rlwimi(dstAlpha, alpha, 0, 24, 31);
    dstAlpha = __rlwimi(dstAlpha, enable, 8, 23, 23);
    GX_BP_LOAD_REG(dstAlpha);
    gx->cmode1 = dstAlpha;
    gx->bpSentNot = GX_FALSE;
}

void GXSetFieldMask(GXBool enableEven, GXBool enableOdd) {
    u32 fieldMaskReg = 0;
    GX_SET_REG(fieldMaskReg, enableOdd, GX_BP_FIELDMASK_ODD_ST, GX_BP_FIELDMASK_ODD_END);
    GX_SET_REG(fieldMaskReg, enableEven, GX_BP_FIELDMASK_EVEN_ST, GX_BP_FIELDMASK_EVEN_END);
    GX_SET_REG(fieldMaskReg, GX_BP_REG_FIELDMASK, 0, 7);

    GX_BP_LOAD_REG(fieldMaskReg);
    gx->bpSentNot = GX_FALSE;
}

void GXSetFieldMode(GXBool texLOD, GXBool adjustAR) {
    GX_SET_REG(gx->lpSize, adjustAR, GX_BP_LINEPTWIDTH_ADJUST_ST,
               GX_BP_LINEPTWIDTH_ADJUST_END);
    GX_BP_LOAD_REG(gx->lpSize);

    __GXFlushTextureState();
    GX_BP_LOAD_REG(GX_BP_REG_FIELDMODE << 24 | texLOD);
    __GXFlushTextureState();
}
