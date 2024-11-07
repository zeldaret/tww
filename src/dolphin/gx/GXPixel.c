#include "dolphin/gx/GXPixel.h"
#include "dolphin/gx/GX.h"

void GXSetFog(GXFogType type, f32 startz, f32 endz, f32 nearz, f32 farz, GXColor color) {
    f32 a, c;
    u32 a_bits, c_bits;

    u32 fogColorReg = 0;
    u32 fogParamReg0 = 0;
    u32 fogParamReg1 = 0;
    u32 fogParamReg2 = 0;
    u32 fogParamReg3 = 0;

    u32 fsel = type & 7;
    BOOL isOrtho = (type >> 3) & 1;
    u32 col;

    if (isOrtho) {
        if (farz == nearz || endz == startz) {
            a = 0.0f;
            c = 0.0f;
        } else {
            a = (1.0f / (endz - startz)) * (farz - nearz);
            c = (1.0f / (endz - startz)) * (startz - nearz);
        }
    } else {
        f32 tmpA, tmpB, tmpC;
        u32 expB, magB, shiftB;

        if (farz == nearz || endz == startz) {
            tmpA = 0.0f;
            tmpB = 0.5f;
            tmpC = 0.0f;
        } else {
            tmpA = (farz * nearz) / ((farz - nearz) * (endz - startz));
            tmpB = farz / (farz - nearz);
            tmpC = startz / (endz - startz);
        }

        expB = 0;
        while (tmpB > 1.0) {
            tmpB /= 2.0f;
            expB++;
        }
        while (tmpB > 0.0f && tmpB < 0.5) {
            tmpB *= 2.0f;
            expB--;
        }

        a = tmpA / (1 << (expB + 1));
        magB = 8388638.0f * tmpB;
        shiftB = expB + 1;
        c = tmpC;

        GX_SET_REG(fogParamReg1, magB, GX_BP_FOGPARAM1_B_MAG_ST, GX_BP_FOGPARAM1_B_MAG_END);
        GX_SET_REG(fogParamReg2, shiftB, GX_BP_FOGPARAM2_B_SHIFT_ST, GX_BP_FOGPARAM2_B_SHIFT_END);

        GX_SET_REG(fogParamReg1, GX_BP_REG_FOGPARAM1, 0, 7);
        GX_SET_REG(fogParamReg2, GX_BP_REG_FOGPARAM2, 0, 7);
    }

    a_bits = *(u32*)&a;
    c_bits = *(u32*)&c;

    GX_SET_REG(fogParamReg0, a_bits >> 12, GX_BP_FOGPARAM0_A_MANT_ST, GX_BP_FOGPARAM0_A_MANT_END);
    GX_SET_REG(fogParamReg0, a_bits >> 23, GX_BP_FOGPARAM0_A_EXP_ST, GX_BP_FOGPARAM0_A_EXP_END);
    GX_SET_REG(fogParamReg0, a_bits >> 31, GX_BP_FOGPARAM0_A_SIGN_ST, GX_BP_FOGPARAM0_A_SIGN_END);
    GX_SET_REG(fogParamReg0, GX_BP_REG_FOGPARAM0, 0, 7);

    GX_SET_REG(fogParamReg3, c_bits >> 12, GX_BP_FOGPARAM3_C_MANT_ST, GX_BP_FOGPARAM3_C_MANT_END);
    GX_SET_REG(fogParamReg3, c_bits >> 23, GX_BP_FOGPARAM3_C_EXP_ST, GX_BP_FOGPARAM3_C_EXP_END);
    GX_SET_REG(fogParamReg3, c_bits >> 31, GX_BP_FOGPARAM3_C_SIGN_ST, GX_BP_FOGPARAM3_C_SIGN_END);
    GX_SET_REG(fogParamReg3, isOrtho, GX_BP_FOGPARAM3_PROJ_ST, GX_BP_FOGPARAM3_PROJ_END);
    GX_SET_REG(fogParamReg3, fsel, GX_BP_FOGPARAM3_FSEL_ST, GX_BP_FOGPARAM3_FSEL_END);
    GX_SET_REG(fogParamReg3, GX_BP_REG_FOGPARAM3, 0, 7);

    col = *(u32*)&color;
    GX_SET_REG(fogColorReg, col >> 8, GX_BP_FOGCOLOR_RGB_ST, GX_BP_FOGCOLOR_RGB_END);
    GX_SET_REG(fogColorReg, GX_BP_REG_FOGCOLOR, 0, 7);

    GX_BP_LOAD_REG(fogParamReg0);
    GX_BP_LOAD_REG(fogParamReg1);
    GX_BP_LOAD_REG(fogParamReg2);
    GX_BP_LOAD_REG(fogParamReg3);
    GX_BP_LOAD_REG(fogColorReg);

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
    GX_SET_REG(blendModeReg, type == GX_BM_SUBTRACT, GX_BP_BLENDMODE_SUBTRACT_ST,
               GX_BP_BLENDMODE_SUBTRACT_END);
    GX_SET_REG(blendModeReg, type, GX_BP_BLENDMODE_ENABLE_ST, GX_BP_BLENDMODE_ENABLE_END);
    GX_SET_REG(blendModeReg, type == GX_BM_LOGIC, GX_BP_BLENDMODE_LOGIC_OP_ST,
               GX_BP_BLENDMODE_LOGIC_OP_END);
    GX_SET_REG(blendModeReg, op, GX_BP_BLENDMODE_LOGICMODE_ST, GX_BP_BLENDMODE_LOGICMODE_END);
    GX_SET_REG(blendModeReg, src_factor, GX_BP_BLENDMODE_SRCFACTOR_ST,
               GX_BP_BLENDMODE_SRCFACTOR_END);
    GX_SET_REG(blendModeReg, dst_factor, GX_BP_BLENDMODE_DSTFACTOR_ST,
               GX_BP_BLENDMODE_DSTFACTOR_END);

    GX_BP_LOAD_REG(blendModeReg);
    gx->cmode0 = blendModeReg;

    gx->bpSentNot = FALSE;
}

void GXSetColorUpdate(GXBool updateEnable) {
    u32 blendModeReg = gx->cmode0;
    GX_SET_REG(blendModeReg, updateEnable, GX_BP_BLENDMODE_COLOR_UPDATE_ST,
               GX_BP_BLENDMODE_COLOR_UPDATE_END);
    GX_BP_LOAD_REG(blendModeReg);
    gx->cmode0 = blendModeReg;
    gx->bpSentNot = GX_FALSE;
}

void GXSetAlphaUpdate(GXBool updateEnable) {
    u32 blendModeReg = gx->cmode0;
    GX_SET_REG(blendModeReg, updateEnable, GX_BP_BLENDMODE_ALPHA_UPDATE_ST,
               GX_BP_BLENDMODE_ALPHA_UPDATE_END);
    GX_BP_LOAD_REG(blendModeReg);
    gx->cmode0 = blendModeReg;
    gx->bpSentNot = GX_FALSE;
}

void GXSetZMode(GXBool compareEnable, GXCompare func, GXBool updateEnable) {
    u32 zModeReg = gx->zmode;
    GX_SET_REG(zModeReg, compareEnable, GX_BP_ZMODE_TEST_ENABLE_ST, GX_BP_ZMODE_TEST_ENABLE_END);
    GX_SET_REG(zModeReg, func, GX_BP_ZMODE_COMPARE_ST, GX_BP_ZMODE_COMPARE_END);
    GX_SET_REG(zModeReg, updateEnable, GX_BP_ZMODE_UPDATE_ENABLE_ST, GX_BP_ZMODE_UPDATE_ENABLE_END);
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
        GX_SET_REG(gx->cmode1, pixelFmt - GX_PF_Y8, GX_BP_DSTALPHA_YUV_FMT_ST,
                   GX_BP_DSTALPHA_YUV_FMT_END);
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
    GX_SET_REG(dstAlpha, alpha, GX_BP_DSTALPHA_ALPHA_ST, GX_BP_DSTALPHA_ALPHA_END);
    GX_SET_REG(dstAlpha, enable, GX_BP_DSTALPHA_ENABLE_ST, GX_BP_DSTALPHA_ENABLE_END);
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
