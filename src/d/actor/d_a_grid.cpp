#include "d/dolzel.h" // IWYU pragma: keep
#include "d/actor/d_a_grid.h"
#include "d/actor/d_a_ship.h"
#include "f_op/f_op_camera.h"
#include "d/d_kankyo_wether.h"
#include "d/d_s_play.h"

#include "res/Object/Cloth.h"
#include "res/Object/Ship.h"

static daHo_HIO_c l_HIO;
static daShip_c* l_ship;

static f32 dummyFloat(int _) {
    switch (_) {
    case 0: return 1.0f;
    default: return 0.5f;
    }
}

static f64 dummyDouble() {
    return 4503601774854144.0;
}

/* 800E8CC0-800E8D48       .text setBackNrm__13daHo_packet_cFv */
void daHo_packet_c::setBackNrm() {
    cXyz* nrm_p = mNrm[field_0x18a2];
    cXyz* backNrm_p = mBackNrm[field_0x18a2];

    for (int i = 0; i < 85; i++) {
        backNrm_p->set(0.0f, 0.0f, 0.0f);
        *backNrm_p -= *nrm_p;
        nrm_p++;
        backNrm_p++;
    }
}

/* 800E8D48-800E8D74       .text setNrmMtx__13daHo_packet_cFR4cXyz */
void daHo_packet_c::setNrmMtx(cXyz&) {
    cMtx_YrotS(*calc_mtx, field_0x189c);
}

/* 800E8D74-800E92AC       .text setNrmVtx__13daHo_packet_cFP4cXyzii */
void daHo_packet_c::setNrmVtx(cXyz* o_vtx, int i_x, int i_y) {
    cXyz x_diff;
    cXyz y_diff;
    cXyz norm;
    cXyz total;
    cXyz pos;

    cXyz* pos_p = getPos();
    int idx = i_y * 7;

    pos = pos_p[i_x + idx];
    total.setall(0.0f);

    if (i_x != 0) {
        x_diff = pos_p[idx - 1 + i_x] - pos;

        if (i_y != 0 && i_y != 9) {
            y_diff = pos_p[(i_y - 1) * 7 + i_x] - pos;
            norm = x_diff.outprod(y_diff);
            norm = norm.normZC();
            total += norm;
        }

        if (i_y == 11) {
            y_diff = pos_p[84] - pos;
            norm = y_diff.outprod(x_diff);
            norm = norm.normZC();
            total += norm;
        } else if (i_y != 8) {
            y_diff = pos_p[(i_y + 1) * 7 + i_x] - pos;
            norm = y_diff.outprod(x_diff);
            norm = norm.normZC();
            total += norm;
        }
    }

    if (i_x != 6) {
        x_diff = pos_p[i_x + 1 + idx] - pos;

        if (i_y != 0 && i_y != 9) {
            y_diff = pos_p[(i_y - 1) * 7 + i_x] - pos;
            norm = y_diff.outprod(x_diff);
            norm = norm.normZC();
            total += norm;
        }

        if (i_y == 11) {
            y_diff = pos_p[84] - pos;
            norm = x_diff.outprod(y_diff);
            norm = norm.normZC();
            total += norm;
        } else if (i_y != 8) {
            y_diff = pos_p[(i_y + 1) * 7 + i_x] - pos;
            norm = x_diff.outprod(y_diff);
            norm = norm.normZC();
            total += norm;
        }
    }

    if (i_y > 7) {
        total.y = 0.0f;
    }

    if (!total.normalizeRS()) {
        total.x = 1.0f;
        total.y = 0.0f;
        total.z = 0.0f;
    }

    MtxPush();
    cMtx_YrotM(*calc_mtx, cM_ssin((i_x + i_y) * -800) * 900.0f);
    MtxPosition(&total, &norm);
    *o_vtx = norm.normZC();
    MtxPull();
}

/* 800E92AC-800E93B8       .text setTopNrmVtx__13daHo_packet_cFP4cXyz */
void daHo_packet_c::setTopNrmVtx(cXyz* o_vtx) {
    cXyz sp68;
    cXyz sp5C;
    cXyz sp50;
    cXyz sp44;

    cXyz* pos_p = getPos();
    sp68 = pos_p[77] - pos_p[84];
    sp5C = pos_p[83] - pos_p[84];

    sp44 = sp68.outprod(sp5C);
    sp44 = sp44.normZC();
    MtxPosition(&sp44, &sp50);
    *o_vtx = sp50.normZC();
}

#include "assets/l_pos__d_a_grid.h"
#include "assets/l_texCoord__d_a_grid.h"
#include "assets/l_DL__d_a_grid.h"
#include "assets/l_matDL__d_a_grid.h"

/* 800E93B8-800E9BE8       .text draw__13daHo_packet_cFv */
void daHo_packet_c::draw() {
    j3dSys.reinitGX();

    #if VERSION >= VERSION_USA
    GXSetNumIndStages(0);
    #endif

    dKy_GxFog_tevstr_set(mpTevStr);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxDesc(GX_VA_NRM, GX_INDEX8);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetArray(GX_VA_POS, getPos(), sizeof(cXyz));
    GXSetArray(GX_VA_NRM, getNrm(), sizeof(cXyz));
    GXSetArray(GX_VA_TEX0, l_texCoord, sizeof(cXy));

    GXTexObj texObj;
    GXTlutObj tlutObj;

    ResTIMG* ho1_timg = (ResTIMG*)dComIfG_getObjectRes("Ship", dRes_ID_SHIP_BTI_NEW_HO1_e);
    GXInitTlutObj(&tlutObj, (u8*)ho1_timg + ho1_timg->paletteOffset, GX_TL_RGB565, 0x100);
    GXInitTexObjCI(&texObj, (u8*)ho1_timg + ho1_timg->imageOffset, ho1_timg->width, ho1_timg->height,
                   (GXCITexFmt)ho1_timg->format, (GXTexWrapMode)ho1_timg->wrapS,
                   (GXTexWrapMode)ho1_timg->wrapT, ho1_timg->mipmapCount > 1, GX_TLUT0);
    GXInitTexObjLOD(&texObj, (GXTexFilter)ho1_timg->minFilter, (GXTexFilter)ho1_timg->magFilter,
                    ho1_timg->minLOD * 0.125f, ho1_timg->maxLOD * 0.125f, ho1_timg->LODBias * 0.01f,
                    ho1_timg->biasClamp, ho1_timg->doEdgeLOD, (GXAnisotropy)ho1_timg->maxAnisotropy);
    GXLoadTlut(&tlutObj, GX_TLUT0);
    GXLoadTexObj(&texObj, GX_TEXMAP0);

    ResTIMG* toon_timg = (ResTIMG*)dComIfG_getObjectRes("Cloth", dRes_ID_CLOTH_BTI_CLOTHTOON_e);
    GXInitTexObj(&texObj, (u8*)toon_timg + toon_timg->imageOffset, toon_timg->width, toon_timg->height,
                 (GXTexFmt)toon_timg->format, (GXTexWrapMode)toon_timg->wrapS,
                 (GXTexWrapMode)toon_timg->wrapT, toon_timg->mipmapCount > 1);
    GXInitTexObjLOD(&texObj, (GXTexFilter)toon_timg->minFilter, (GXTexFilter)toon_timg->magFilter,
                    toon_timg->minLOD * 0.125f, toon_timg->maxLOD * 0.125f,
                    toon_timg->LODBias * 0.01f, toon_timg->biasClamp, toon_timg->doEdgeLOD,
                    (GXAnisotropy)toon_timg->maxAnisotropy);
    GXLoadTexObj(&texObj, GX_TEXMAP1);

    GXSetNumChans(1);

    u8 num_stages;
    u8 light_mask;
    if (mpTevStr->mColorK1.a != 0) {
        num_stages = 3;
        light_mask = GX_LIGHT0 | GX_LIGHT1;
    } else {
        num_stages = 2;
        light_mask = GX_LIGHT0;
    }

    if (l_HIO.field_0x5) {
        GXSetChanCtrl(GX_COLOR0, 1, GX_SRC_REG, GX_SRC_REG, light_mask, GX_DF_CLAMP, GX_AF_NONE);
        GXSetNumTexGens(2);
        GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
        GXSetTexCoordGen(GX_TEXCOORD1, GX_TG_SRTG, GX_TG_COLOR0, GX_IDENTITY);
        GXSetNumTevStages(num_stages);
        GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C0, GX_CC_C1, GX_CC_TEXC, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_CPREV, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

        if (num_stages == 3) {
            GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP2);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_C2, GX_CC_TEXC, GX_CC_CPREV);
            GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        }
    } else {
        GXSetChanCtrl(GX_COLOR0, 1, GX_SRC_REG, GX_SRC_REG, light_mask, GX_DF_CLAMP, GX_AF_NONE);
        GXSetNumTexGens(1);
        GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
        GXSetNumTevStages(num_stages);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP1, GX_TEV_SWAP0);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C0, GX_CC_C1, GX_CC_RASC, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

        if (num_stages == 3) {
            GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP2, GX_TEV_SWAP0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_C2, GX_CC_RASC, GX_CC_CPREV);
            GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        }
    }

    mpTevStr->mColorC0.a = mAlpha;
    GXSetTevColorS10(GX_TEVREG0, mpTevStr->mColorC0);
    GXSetTevColor(GX_TEVREG1, mpTevStr->mColorK0);
    GXSetTevColor(GX_TEVREG2, mpTevStr->mColorK1);
    GXCallDisplayList(l_matDL, 0x20);

    GXLoadPosMtxImm(getMtx(), 0);
    GXLoadNrmMtxImm(getMtx(), 0);
    GXSetCullMode(GX_CULL_BACK);
    GXCallDisplayList(l_DL, 0x220);

    GXSetCullMode(GX_CULL_FRONT);
    GXSetArray(GX_VA_NRM, mBackNrm[field_0x18a2], sizeof(cXyz));
    GXCallDisplayList(l_DL, 0x220);

    #if VERSION >= VERSION_USA
    J3DShape::resetVcdVatCache();
    #endif
}

/* 800E9BE8-800E9C0C       .text daGrid_Draw__FP8daGrid_c */
static BOOL daGrid_Draw(daGrid_c* i_this) {
    return ((daGrid_c*)i_this)->_draw();
}

/* 800E9C0C-800EA928       .text ho_move__FP8daGrid_c */
// NONMATCHING - some small reg alloc
void ho_move(daGrid_c* i_this) {
    if (l_HIO.field_0x38) {
        return;
    }

    static f32 z_rate_tbl[] = {
        0.05f, 0.125f, 0.175f, 0.15f, 0.0625f, 0.15f, 0.2f,
        0.15f, 0.075f, 0.175f, 0.175f, 0.1f, 0.0f,
    };

    static f32 z_rate_tbl2[] = {
        1.0f, 0.425f, 0.45f, 0.4f, 0.2f, 0.4f, 0.45f,
        0.4f, 0.2f, 0.5f, 0.75f, 1.0f, 1.0f,
    };

    static f32 x_rate_tbl[] = {
        1.0f, 0.95f, 0.9f, 0.85f, 0.8f, 0.75f, 0.7f,
        0.65f, 0.55f, 0.4f, 0.25f, 0.1f, 0.0f,
    };

    f32 temp_f31;
    f32 temp_f30;

    #if VERSION == VERSION_DEMO
    f32 temp_f15 = 0.4f * (2.0f + 0.05f * REG10_F(1));
    #endif

    cXyz* windVec = dKyw_get_wind_vec();
    f32 windPow = dKyw_get_wind_pow();
    i_this->mPacket.changeCurrentPos();

    i_this->field_0x1b4c = 7500;
    i_this->field_0x1b4e = 7200;

    s16 sail_angle = l_ship->getSailAngle();

    s16 windAngle = cM_atan2s(windVec->x, windVec->z);
    int var_r28 = (s16)(i_this->current.angle.y + sail_angle);
    var_r28 -= windAngle;

    s16 temp_r3 = var_r28 + 0x8000;
    if (temp_r3 > 0) {
        if (sail_angle > 0 && sail_angle < 0x4000) {
            temp_r3 = 0;
        }
    } else if (sail_angle < 0 && sail_angle > -0x4000) {
        temp_r3 = 0;
    }

    s16 temp_r4 = 0.6f * temp_r3;
    if (!i_this->mIsForceWindRelAngle) {
        cLib_addCalcAngleS2(&i_this->field_0x2210, temp_r4, 4, 0x1000);
    } else {
        s16 temp_r4_2 = i_this->mForceWindRelAngle - l_ship->getSailAngle() + 0x8000;
        cLib_addCalcAngleS2(&i_this->field_0x2210, temp_r4_2, 2, 0x1400);
    }

    i_this->mIsForceWindRelAngle = FALSE;

    cMtx_YrotS(*calc_mtx, i_this->field_0x2210);
    cXyz sp34(0.0f, 0.0f, DEMO_SELECT((temp_f15 * 0.08f) * (1.0f + REG10_F(0)), 0.064f));
    cXyz sp28;
    MtxPosition(&sp34, &sp28);

    f32 temp_f1 = std::fabsf(sp28.z) + 0.02f;
    sp34.x = 1.0f;
    sp34.z = 0.0f;
    MtxPosition(&sp34, &sp28);

    f32 temp_f28 = std::fabsf(sp28.z);
    temp_f28 *= 1.0f - i_this->field_0x2200;
    f32 temp_f = 1.0f + (0.01f + REG6_F(15)) * (temp_f28 * cM_ssin(i_this->field_0x1b44));
    s32 temp_r0_2 = 2500.0f + (9000.0f * (DEMO_SELECT(temp_f15, 0.8f) * windPow)) * DEMO_SELECT((1.0f + REG10_F(3)), 1);
    i_this->field_0x1b44 += cLib_maxLimit(temp_r0_2, (s32)10000);
    i_this->field_0x2212 += (s16)(3000.0f * cM_scos(var_r28));

    s16 temp_r3_2;
    if (i_this->field_0x2212 > 0) {
        temp_r3_2 = 300;
    } else {
        temp_r3_2 = -300;
    }
    i_this->field_0x2212 += temp_r3_2;

    f32 temp_f26 = 0.5f * cM_ssin(var_r28);
    sp34.x = 0.0f;
    sp34.z = DEMO_SELECT(temp_f15 * (REG0_F(14) + 2.0f), 1.6f);

    cXyz* pos = i_this->mPacket.getPos();

    if (!l_HIO.field_0x8) {
        if (l_ship->getSailOn()) {
            if (i_this->field_0x2208 == 0.0f) {
                if (i_this->field_0x2200 <= 0.0001f + l_HIO.field_0xc) {
                    i_this->field_0x2208 = 1.0f;
                    i_this->field_0x1b4a = 15;
                }
            } else if (i_this->field_0x1b4a > 0) {
                cLib_addCalc2(&i_this->field_0x2204, 1.414f, 0.25f, l_HIO.field_0x20);
                i_this->field_0x1b4a--;
            } else {
                cLib_addCalc2(&i_this->field_0x2204, 1.0f, 0.1f, 0.05f);
            }
        } else {
            if (i_this->field_0x2200 > 0.7f) {
                i_this->field_0x2208 = 0.0f;
                i_this->field_0x1b4a = 0;
            }
            cLib_addCalc2(&i_this->field_0x2204, 1.0f - 0.65f * i_this->field_0x2200, 0.1f, 0.05f);
        }
    } else {
        i_this->field_0x2200 = l_HIO.field_0x10;
    }

    int var_r24 = 0;
    int var_r23 = 0;
    for (int i = 0; i < 85; i++, pos++) {
        f32 temp_f25 = 1.0f - i_this->field_0x2200;
        f32 temp_f24 = 3 - var_r24;
        f32 temp_f23 = var_r23 - 2 + DEMO_SELECT(REG0_F(5), 0);
        s16 sp50 = 10922.0f * x_rate_tbl[var_r23];

        temp_f31 = temp_f1 * cM_ssin(i_this->field_0x1b44 + i * i_this->field_0x1b4c);
        temp_f30 = 0.5f * (temp_f1 * cM_scos(i_this->field_0x1b44 + i * i_this->field_0x1b4e));

        MtxPosition(&sp34, &sp28);
        f32 x_value = 0.25f + 0.75f * windPow;
        sp28.x = sp28.x * cLib_maxLimit(x_value, 1.0f);

        f32 z_value = 0.5f + 0.25f * windPow;
        sp28.z = sp28.z * cLib_maxLimit(z_value, 1.0f);

        temp_f31 += i_this->field_0x2204 * (temp_f25 * (sp28.x * temp_f));
        temp_f30 += i_this->field_0x2204 * (temp_f25 * (sp28.z * temp_f28));

        f32 temp_f2 = std::sqrtf(SQUARE(temp_f31) + SQUARE(temp_f30));
        f32 temp_f2_2 = 0.05f * temp_f2;
        f32 temp_f0_2 = i_this->field_0x1b54[i];

        temp_f31 *= temp_f0_2;
        temp_f2_2 *= temp_f0_2;
        temp_f30 *= temp_f0_2;

        f32 temp_f0_3 = temp_f23 < 0.0f ? temp_f23 : 0.0f;
        f32 temp_f1_2 = 0.67f + 0.3f * (SQUARE(temp_f0_3) / DEMO_SELECT(SQUARE(2 - REG10_S(5)), 4));
        f32 temp_f3 = 1.0f - temp_f1_2 * i_this->field_0x2200;
        f32 z_rate;
        f32 temp_f4 = 120.0f;
        f32 temp_f5;

        if (l_HIO.field_0x39) {
            temp_f3 *= temp_f25 + l_HIO.field_0x70[var_r23] * i_this->field_0x2200;
            z_rate = l_HIO.field_0x3c[var_r23];
            temp_f4 *= z_rate * i_this->field_0x2200;
            temp_f5 = i_this->field_0x2200 * (5.0f * z_rate * var_r24);
        } else {
            temp_f3 *= temp_f25 + z_rate_tbl2[var_r23] * i_this->field_0x2200;
            z_rate = z_rate_tbl[var_r23];
            temp_f4 *= i_this->field_0x2200 * z_rate;
            temp_f5 = i_this->field_0x2200 * (var_r24 * (5.0f * z_rate));
        }

        pos->x = l_pos[i].x;
        pos->y = temp_f3 * l_pos[i].y + (1.0f - temp_f3) * l_pos[var_r23 * 7].y;
        pos->z = temp_f3 * l_pos[i].z;

        f32 ivar16 = cM_ssin(i_this->field_0x2212 + sp50 * var_r24);
        f32 temp_f6 = 9.0f - SQUARE(temp_f24);
        f32 temp_f7 = ((i_this->field_0x2200 * ivar16 * temp_f6) / 9.0f) - ((temp_f26 * temp_f6) / 9.0f);
        temp_f4 *= temp_f7;

        f32 cos_ = cM_scos(i_this->field_0x2212 + sp50 * var_r24);
        temp_f5 *= (i_this->field_0x2200 * cos_ * var_r24) / 6.0f;

        f32 temp = 1.0f - 0.5f * (SQUARE(temp_f0_3) / 4);
        temp_f5 *= temp;
        temp_f4 *= temp;

        f32 temp_f0_5 = std::sqrtf(SQUARE(temp_f4) + SQUARE(temp_f5));
        f32 temp_f1_3 = 0.25f * -temp_f0_5;
        if (var_r24 > 4) {
            f32 temp = std::fabsf(cM_ssin(i_this->field_0x2212 + (sp50 * 2) * var_r24));
            temp_f1_3 += 4.25f * ((var_r24 - 4) * temp);
        }

        if (l_HIO.field_0x39) {
            temp_f1_3 *= i_this->field_0x2200 * (6.0f * l_HIO.field_0x3c[var_r23] * (var_r24 / 6.0f));
        } else {
            temp_f1_3 *= i_this->field_0x2200 * (6.0f * z_rate_tbl[var_r23] * (var_r24 / 6.0f));
        }

        pos->x += temp_f4 + (0.65f * temp_f25 + 0.35f) * (temp_f31 * i_this->field_0x2204);
        pos->y += temp_f5 + temp_f2_2 * (0.65f * temp_f25 + 0.35f);
        pos->z += temp_f1_3 + ((0.65f * temp_f25 + 0.35f) * (temp_f30 * i_this->field_0x2204) - 13.75f);

        var_r23 = var_r24 < 6 ? var_r23 : var_r23 + 1;
        var_r24 = var_r24 < 6 ? var_r24 + 1 : 0;
    }

    pos = i_this->mPacket.getPos();

    f32 temp_f4_2 = std::fabsf(pos[59].x);
    f32 fvar5 = 1.0f - temp_f4_2 * (0.0015f + REG6_F(8));
    f32 fvar11 = 1.0f - temp_f4_2 * (0.000700000033f + REG6_F(9));
    f32 fvar12 = 1.0f - temp_f4_2 * (0.000200000068f + REG6_F(10));
    f32 fvar10 = 1.0f - temp_f4_2 * (0.0015f + REG6_F(11));
    f32 fvar6 = 1.0f - temp_f4_2 * (0.0012f + REG6_F(12));

    for (int i = 0; i < 85; i++, pos++) {
        if (i >= 56 && i <= 62) {
            pos->z *= fvar5;
        } else if (i >= 49 && i <= 55) {
            pos->z *= fvar11;
        } else if (i >= 42 && i <= 48) {
            pos->z *= fvar12;
        } else if (i >= 63 && i <= 69) {
            pos->z *= fvar10;
        } else if (i >= 70 && i <= 77) {
            pos->z *= fvar6;
        }
    }

    cXyz* nrm = i_this->mPacket.getNrm();
    cXyz sp1C = i_this->tevStr.mLightPosWorld - i_this->current.pos;
    i_this->mPacket.setNrmMtx(sp1C);

    for (int y = 0; y < 12; y++) {
        for (int x = 0; x < 7; x++) {
            i_this->mPacket.setNrmVtx(nrm, x, y);
            nrm++;
        }
    }

    i_this->mPacket.setTopNrmVtx(nrm);
    i_this->mPacket.setBackNrm();

    DCStoreRangeNoSync(i_this->mPacket.getPos(), sizeof(i_this->mPacket.mPos[0]));

    #if VERSION >= VERSION_USA
    DCStoreRangeNoSync(i_this->mPacket.getNrm(), sizeof(i_this->mPacket.mNrm[0]));
    DCStoreRangeNoSync(i_this->mPacket.getBackNrm(), sizeof(i_this->mPacket.mBackNrm[0]));
    #endif
}

/* 800EA928-800EA94C       .text daGrid_Execute__FP8daGrid_c */
static BOOL daGrid_Execute(daGrid_c* i_this) {
    return ((daGrid_c*)i_this)->_execute();
}

/* 800EA94C-800EA954       .text daGrid_IsDelete__FP8daGrid_c */
static BOOL daGrid_IsDelete(daGrid_c*) {
    return TRUE;
}

/* 800EA954-800EA978       .text daGrid_Delete__FP8daGrid_c */
static BOOL daGrid_Delete(daGrid_c* i_this) {
    return ((daGrid_c*)i_this)->_delete();
}

/* 800EA978-800EA998       .text daGrid_Create__FP10fopAc_ac_c */
static cPhs_State daGrid_Create(fopAc_ac_c* i_this) {
    return ((daGrid_c*)i_this)->_create();
}

/* 800EA998-800EAEAC       .text _create__8daGrid_cFv */
cPhs_State daGrid_c::_create() {
    #if VERSION == VERSION_DEMO
    field_0x1b48 = fopAcM_GetParam(this);

    cPhs_State phase = dComIfG_resLoad(&mClothPhase, "Cloth");
    cPhs_State phase2 = dComIfG_resLoad(&mShipPhase, "Ship");
    if (phase == cPhs_ERROR_e || phase2 == cPhs_ERROR_e) {
        return cPhs_ERROR_e;
    }

    if (phase != cPhs_COMPLEATE_e) {
        return phase;
    }

    if (phase2 != cPhs_COMPLEATE_e) {
        return phase2;
    }

    cPhs_State temp_r0 = cPhs_COMPLEATE_e;
    if (temp_r0 == cPhs_COMPLEATE_e) {
    #endif

    fopAcM_ct(this, daGrid_c);

    #if VERSION >= VERSION_JPN
    field_0x1b48 = fopAcM_GetParam(this);
    
    cPhs_State phase = dComIfG_resLoad(&mClothPhase, "Cloth");
    if (phase != cPhs_COMPLEATE_e) {
        return phase;
    }

    phase = dComIfG_resLoad(&mShipPhase, "Ship");
    if (phase != cPhs_COMPLEATE_e) {
        return phase;
    }
    #endif

    if (l_HIO.mNo < 0) {
        l_HIO.mNo = mDoHIO_createChild("船の帆", &l_HIO);
    }

    int var_r29;
    int i = 0;
    Vec* pos_p = l_pos;

    for (; i < 85; i++) {
        f32 var_f27;
        if (i >= 0 && i <= 6) {
            var_f27 = 10.0f * (4.0f + DEMO_SELECT(REG0_F(18), 0));
        } else if (i >= 7 && i <= 13) {
            var_f27 = 10.0f * (7.0f + DEMO_SELECT(REG0_F(4), 0));
        } else if ((i >= 49 && i <= 55) || (i >= 42 && i <= 48)) {
            var_f27 = 10.0f * (8.5f + DEMO_SELECT(REG0_F(19), 0));
        } else {
            var_f27 = 10.0f * (8.0f + DEMO_SELECT(REG0_F(13), 0));
        }

        var_r29 = 6;

        f32 temp_f4 = std::fabsf(pos_p[0].z - pos_p[i].z);
        f32 temp_f2 = std::fabsf(pos_p[var_r29].z - pos_p[i].z);
        f32 temp_f0 = std::fabsf(pos_p[0].z - pos_p[var_r29].z);
        temp_f0 *= 0.5f;

        f32 temp_f1 = 1.05f * ((M_PI / 2) / temp_f0);
        if (temp_f4 > temp_f2) {
            temp_f4 = temp_f2;
        }

        f32 temp_f1_2 = sin(temp_f4 * temp_f1);
        var_f27 *= temp_f1_2;

        for (int j = 0; j < 7; j++) {
            if (i == j
                || i == j + 7
                || i == j + 14
                || i == j + 21
                || i == j + 28
                || i == j + 35 
                || i == j + 42
                || i == j + 49
                || i == j + 56
                || i == j + 63
                || i == j + 70
                || i == j + 77)
            {
                var_r29 = j + 56;
            }
        }

        f32 pos_y = pos_p[i].y;
        Vec* temp_r0 = &pos_p[var_r29];

        f32 temp_f26;
        f32 temp_f1_3;
        f32 temp_f1_4;
        f32 temp_f0_2;
        if (pos_y < temp_r0->y) {
            temp_f0_2 = std::fabsf(pos_p[0].y - pos_y);
            temp_f1_3 = std::fabsf(temp_r0->y - pos_y);

            f32 temp_f2_2 = std::fabsf(temp_r0->y - pos_p[0].y);
            temp_f2_2 *= 0.5f;
            temp_f1_4 = 1.05f * ((M_PI / 2) / temp_f2_2);

            if (var_r29 == 56) {
                temp_f26 = 10.0f * (3.5f + DEMO_SELECT(REG0_F(16), 0));
            } else if (var_r29 == 57) {
                temp_f26 = 10.0f * (7.0f + DEMO_SELECT(REG0_F(5), 0));
            } else {
                temp_f26 = 10.0f * (8.0f + DEMO_SELECT(REG0_F(15), 0));
            }
        } else {
            temp_f0_2 = std::fabsf(temp_r0->y - pos_y);
            temp_f1_3 = std::fabsf(pos_p[84].y - pos_y);

            f32 temp_f2_2 = std::fabsf(temp_r0->y - pos_p[84].y);
            temp_f2_2 *= 0.5f;
            temp_f1_4 = 1.15f * ((M_PI / 2) / temp_f2_2);
            temp_f26 = 10.0f * (2.0f + DEMO_SELECT(REG0_F(17), 0));
        }

        if (temp_f0_2 > temp_f1_3) {
            temp_f0_2 = temp_f1_3;
        }

        f32 sin_ = sin(temp_f0_2 * temp_f1_4);
        f32 temp_f4_2 = temp_f26 * sin_;
        field_0x1b54[i] = std::sqrtf(SQUARE(var_f27) + SQUARE(temp_f4_2));
    }

    l_ship = (daShip_c*)fopAcM_SearchByName(fpcNm_SHIP_e);
    ho_move(this);

#if VERSION == VERSION_DEMO
    }
#endif

    return cPhs_COMPLEATE_e;
}

/* 800EAEAC-800EAF28       .text _delete__8daGrid_cFv */
bool daGrid_c::_delete() {
    dComIfG_resDelete(&mClothPhase, "Cloth");
    dComIfG_resDelete(&mShipPhase, "Ship");

    if (l_HIO.mNo >= 0) {
        mDoHIO_deleteChild(l_HIO.mNo);
        l_HIO.mNo = -1;
    }

    return true;
}

/* 800EAF28-800EB0EC       .text _execute__8daGrid_cFv */
bool daGrid_c::_execute() {
    u8 alpha = mPacket.getAlpha();
    u8 target_alpha;

    if (!dComIfGp_event_runCheck()) {
        cXyz eye = dComIfGp_getCamera(0)->mCamera.Eye();
        f32 cam_eye_dist = (current.pos - eye).abs();

        u8 target;
        if (cam_eye_dist > l_HIO.field_0x34) {
            target = l_HIO.field_0x30;
        } else {
            f32 rate = cam_eye_dist / l_HIO.field_0x34;
            target = l_HIO.field_0x30 * rate + l_HIO.field_0x31 * (1.0f - rate);
        }
        target_alpha = target;
    } else {
        target_alpha = l_HIO.field_0x30;
    }

    if (target_alpha > alpha + 5) {
        mPacket.setAlpha(alpha + 5);
    } else if (target_alpha < alpha - 5) {
        mPacket.setAlpha(alpha - 5);
    } else {
        mPacket.setAlpha(target_alpha);
    }

    if (scale.y < 0.06f) {
        return true;
    }

    ho_move(this);
    return true;
}

/* 800EB0EC-800EB328       .text _draw__8daGrid_cFv */
bool daGrid_c::_draw() {
    if (scale.y < 0.06f) {
        return TRUE;
    }

    tevStr = l_ship->tevStr;

    MtxTrans(current.pos.x, current.pos.y, current.pos.z, false);
    cMtx_YrotM(*calc_mtx, current.angle.y);
    cMtx_XrotM(*calc_mtx, current.angle.x);
    cMtx_ZrotM(*calc_mtx, current.angle.z);
    cMtx_YrotM(*calc_mtx, l_ship->getSailAngle());
    MtxScale(1.0f, scale.y, 1.0f, true);
    MtxScale(l_HIO.field_0x24, l_HIO.field_0x28, l_HIO.field_0x2c, true);
    cMtx_concat(j3dSys.getViewMtx(), *calc_mtx, mPacket.getMtx());
    mPacket.setTevStr(&tevStr);

    J3DDrawBuffer* buffer = mDoGph_gInf_c::isMonotone() ? dComIfGd_getXluListP1() : dComIfGd_getXluList();
    buffer->setZMtx(*calc_mtx);
    buffer->entryZSort(&mPacket);
    return true;
}

static actor_method_class l_daGrid_Method = {
    (process_method_func)daGrid_Create,
    (process_method_func)daGrid_Delete,
    (process_method_func)daGrid_Execute,
    (process_method_func)daGrid_IsDelete,
    (process_method_func)daGrid_Draw,
};

actor_process_profile_definition g_profile_GRID = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_GRID_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daGrid_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_GRID_e,
    /* Actor SubMtd */ &l_daGrid_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_0_e,
};
