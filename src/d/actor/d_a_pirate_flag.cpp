//
// Generated by dtk
// Translation Unit: d_a_pirate_flag.cpp
//

#include "d/actor/d_a_pirate_flag.h"
#include "d/d_procname.h"
#include "d/res/res_kaizokusen.h"
#include "d/res/res_cloth.h"
#include "d/actor/d_a_obj_pirateship.h"

// Needed for the .data section to match.
static Vec dummy_2100 = {1.0f, 1.0f, 1.0f};
static Vec dummy_2080 = {1.0f, 1.0f, 1.0f};
static u8 dummy_1811[] = {0x02, 0x00, 0x02, 0x01};
static f64 dummy4[2] = {3.0, 0.5};

static Vec l_pos[25] = {
    {0.0f, 2200.0f, 0.0f},
    {0.0f, 2200.0f, 200.0f},
    {0.0f, 2200.0f, 400.0f},
    {0.0f, 2200.0f, 600.0f},
    {0.0f, 2200.0f, 800.0f},

    {0.0f, 2100.0f, 0.0f},
    {0.0f, 2100.0f, 200.0f},
    {0.0f, 2100.0f, 400.0f},
    {0.0f, 2100.0f, 600.0f},
    {0.0f, 2100.0f, 800.0f},

    {0.0f, 2000.0f, 0.0f},
    {0.0f, 2000.0f, 200.0f},
    {0.0f, 2000.0f, 400.0f},
    {0.0f, 2000.0f, 600.0f},
    {0.0f, 2000.0f, 800.0f},

    {0.0f, 1900.0f, 0.0f},
    {0.0f, 1900.0f, 200.0f},
    {0.0f, 1900.0f, 400.0f},
    {0.0f, 1900.0f, 600.0f},
    {0.0f, 1900.0f, 800.0f},

    {0.0f, 1800.0f, 0.0f},
    {0.0f, 1800.0f, 200.0f},
    {0.0f, 1800.0f, 400.0f},
    {0.0f, 1800.0f, 600.0f},
    {0.0f, 1800.0f, 800.0f},
};

static cXy l_texCoord[] = {
    {0.0f,  0.0f},
    {0.25f, 0.0f},
    {0.5f,  0.0f},
    {0.75f, 0.0f},
    {1.0f,  0.0f},

    {0.0f,  0.25f},
    {0.25f, 0.25f},
    {0.5f,  0.25f},
    {0.75f, 0.25f},
    {1.0f,  0.25f},

    {0.0f,  0.5f},
    {0.25f, 0.5f},
    {0.5f,  0.5f},
    {0.75f, 0.5f},
    {1.0f,  0.5f},

    {0.0f,  0.75f},
    {0.25f, 0.75f},
    {0.5f,  0.75f},
    {0.75f, 0.75f},
    {1.0f,  0.75f},

    {0.0f,  1.0f},
    {0.25f, 1.0f},
    {0.5f,  1.0f},
    {0.75f, 1.0f},
    {1.0f,  1.0f},
};

static u8 l_pirate_flag_DL[0xA4] ALIGN_DECL(32) = {
    0x98, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x05, 0x05, 0x05, 0x01, 0x01, 0x01,
    0x06, 0x06, 0x06, 0x02, 0x02, 0x02, 0x07, 0x07, 0x07, 0x03, 0x03, 0x03,
    0x08, 0x08, 0x08, 0x04, 0x04, 0x04, 0x09, 0x09, 0x09, 0x98, 0x00, 0x0a,
    0x05, 0x05, 0x05, 0x0a, 0x0a, 0x0a, 0x06, 0x06, 0x06, 0x0b, 0x0b, 0x0b,
    0x07, 0x07, 0x07, 0x0c, 0x0c, 0x0c, 0x08, 0x08, 0x08, 0x0d, 0x0d, 0x0d,
    0x09, 0x09, 0x09, 0x0e, 0x0e, 0x0e, 0x98, 0x00, 0x0a, 0x0a, 0x0a, 0x0a,
    0x0f, 0x0f, 0x0f, 0x0b, 0x0b, 0x0b, 0x10, 0x10, 0x10, 0x0c, 0x0c, 0x0c,
    0x11, 0x11, 0x11, 0x0d, 0x0d, 0x0d, 0x12, 0x12, 0x12, 0x0e, 0x0e, 0x0e,
    0x13, 0x13, 0x13, 0x98, 0x00, 0x0a, 0x0f, 0x0f, 0x0f, 0x14, 0x14, 0x14,
    0x10, 0x10, 0x10, 0x15, 0x15, 0x15, 0x11, 0x11, 0x11, 0x16, 0x16, 0x16,
    0x12, 0x12, 0x12, 0x17, 0x17, 0x17, 0x13, 0x13, 0x13, 0x18, 0x18, 0x18,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static u8 l_pirate_flag_matDL[0x34] ALIGN_DECL(32) = {
    0x61, 0x43, 0x00, 0x00, 0x01, 0x61, 0x40, 0x00, 0x00, 0x17, 0x61,
    0x41, 0x00, 0x04, 0xAD, 0x61, 0xF3, 0x64, 0x80, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

};

static daObjPirateship::Act_c* l_p_ship;

static daPirate_Flag_HIO_c l_HIO;

/* 000000EC-00000364       .text setCorrectNrmAngle__22daPirate_Flag_packet_cFsf */
void daPirate_Flag_packet_c::setCorrectNrmAngle(s16 param_0, f32 param_1) {
    m87C += (s16)((s32)cM_rndF(200.0f) + 900);
    m878 = 300.0f * cM_ssin(m87C);

    s16 temp_r0 = param_0 + 0x8000;
    s32 param_0_int = param_0; // Probably fake variable
    s16 temp_r26 = (l_HIO.m1C * (1.0f - param_1 * 0.5f));

    if (abs((s32)temp_r0) < (s16)cM_deg2s(temp_r26 * 1.25f)) {
        s16 var_r4;
        if (temp_r0 > 0) {
            var_r4 = (s16)cM_deg2s(-temp_r26);
        } else {
            var_r4 = (s16)cM_deg2s(temp_r26);
        }

        cLib_addCalcAngleS2(&m87A, var_r4, 5, 0xC0);
    } else if (abs(param_0_int) < (s16)cM_deg2s(temp_r26 * 1.25f)) {
        s16 var_r4;
        if ((s16)param_0_int > 0) { // Fakematch? Pointless cast
            var_r4 = (s16)cM_deg2s(-temp_r26);
        } else {
            var_r4 = (s16)cM_deg2s(temp_r26);
        }

        cLib_addCalcAngleS2(&m87A, var_r4, 5, 0xC0);
    } else {
        cLib_addCalcAngleS2(&m87A, 0, 5, 0xC0);
    }

    m878 += m87A;
}

/* 00000364-000003F0       .text setBackNrm__22daPirate_Flag_packet_cFv */
void daPirate_Flag_packet_c::setBackNrm() {
    cXyz* a = getNrm();
    cXyz* b = m4F4[m87E];
    for (int i = 0; i < (s32)ARRAY_SIZE(mNrm[0]); i++) {
        b->setall(0.0f);
        *b -= *a;

        a++;
        b++;
    }
}

/* 000003F0-00000800       .text setNrmVtx__22daPirate_Flag_packet_cFP4cXyzii */
void daPirate_Flag_packet_c::setNrmVtx(cXyz* param_0, int param_1, int param_2) {
    cXyz* vec_arr = getPos();

    cXyz tmp;
    cXyz tmp2;
    cXyz tmp3;
    cXyz spD4;
    cXyz spC8 = vec_arr[param_1 + (param_2 * 5)];
    spD4.setall(0.0f);

    if (param_1 != 0) {
        tmp = vec_arr[(param_1 + (param_2 * 5)) - 1] - spC8;
        if (param_2 != 0) {
            tmp2 = vec_arr[(param_1 + (param_2 - 1) * 5)] - spC8;
            tmp3 = tmp.outprod(tmp2);
            tmp3 = tmp3.normZP();
            spD4 += tmp3;
        }

        if (param_2 != 4) {
            tmp2 = vec_arr[(param_1 + (param_2 + 1) * 5)] - spC8;
            tmp3 = tmp2.outprod(tmp);
            tmp3 = tmp3.normZP();
            spD4 += tmp3;
        }
    }

    if (param_1 != 4) {
        tmp = vec_arr[1 + param_1 + param_2 * 5] - spC8;
        if (param_2 != 0) {
            tmp2 = vec_arr[(param_1 + (param_2 - 1) * 5)] - spC8;
            tmp3 = tmp2.outprod(tmp);
            tmp3 = tmp3.normZP();
            spD4 += tmp3;
        }

        if (param_2 != 4) {
            tmp2 = vec_arr[(param_1 + (param_2 + 1) * 5)] - spC8;
            tmp3 = tmp.outprod(tmp2);
            tmp3 = tmp3.normZP();
            spD4 += tmp3;
        }
    }

    spD4 = spD4.normZP();
    MtxPush();
    cMtx_YrotM(*calc_mtx, 900.0f * cM_ssin((param_1 + param_2) * -800));
    MtxPosition(&spD4, &tmp3);

    *param_0 = tmp3.normZP();
    MtxPull();
}

/* 0000083C-00000E44       .text draw__22daPirate_Flag_packet_cFv */
void daPirate_Flag_packet_c::draw() {
    j3dSys.reinitGX();

    GXSetNumIndStages(0);
    dKy_GxFog_tevstr_set(mTevStr);
    dKy_setLight_mine(mTevStr);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxDesc(GX_VA_NRM, GX_INDEX8);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_POS_XY, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_POS_XYZ, GX_F32, 0);
    GXSetArray(GX_VA_POS, getPos(), sizeof(cXyz));
    GXSetArray(GX_VA_NRM, getNrm(), sizeof(cXyz));
    GXSetArray(GX_VA_TEX0, l_texCoord, sizeof(*l_texCoord));
    GXTexObj texObj;
    ResTIMG* timg = static_cast<ResTIMG*>(dComIfG_getObjectRes("Kaizokusen", KAIZOKUSEN_INDEX_BTI_TXA_KAIZOKU_HATA));
    GXInitTexObj(&texObj, (char*)timg + timg->imageOffset, timg->width, timg->height,
        (GXTexFmt)timg->format, (GXTexWrapMode)timg->wrapS, (GXTexWrapMode)timg->wrapT,
        (GXBool)(timg->mipmapCount > 1));
    GXInitTexObjLOD(&texObj, (GXTexFilter)timg->minFilter, (GXTexFilter)timg->magFilter,
                    timg->minLOD * 0.125f, timg->maxLOD * 0.125f, timg->LODBias * 0.01f,
                    (GXBool)timg->biasClamp, (GXBool)timg->doEdgeLOD,
                    (GXAnisotropy)timg->maxAnisotropy);
    GXLoadTexObj(&texObj, GX_TEXMAP0);

    timg = static_cast<ResTIMG*>(dComIfG_getObjectRes("Cloth", CLOTH_BTI_CLOTHTOON));
    GXInitTexObj(&texObj, (char*)timg + timg->imageOffset, timg->width, timg->height,
                 (GXTexFmt)timg->format, (GXTexWrapMode)timg->wrapS, (GXTexWrapMode)timg->wrapT,
                 (GXBool)(timg->mipmapCount > 1));
    GXInitTexObjLOD(&texObj, (GXTexFilter)timg->minFilter, (GXTexFilter)timg->magFilter,
                    timg->minLOD * 0.125f, timg->maxLOD * 0.125f, timg->LODBias * 0.01f,
                    (GXBool)timg->biasClamp, (GXBool)timg->doEdgeLOD,
                    (GXAnisotropy)timg->maxAnisotropy);
    GXLoadTexObj(&texObj, GX_TEXMAP1);
    GXSetNumChans(1);
    u8 var_r0, tevCount;
    if (mTevStr->mColorK1.a != 0) {
        tevCount = 3;
        var_r0 = GX_LIGHT0 | GX_LIGHT1;
    } else {
        tevCount = 2;
        var_r0 = GX_LIGHT0;
    }

    GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_REG, var_r0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetNumTexGens(2);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_SRTG, GX_TG_COLOR0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(tevCount);

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
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

    if (tevCount == 3) {
        GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP2);
        GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_C2, GX_CC_TEXC, GX_CC_CPREV);
        GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
        GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    }
    GXSetTevColorS10(GX_TEVREG0, mTevStr->mColorC0);
    GXSetTevColor(GX_TEVREG1, mTevStr->mColorK0);
    GXSetTevColor(GX_TEVREG2, mTevStr->mColorK1);
    GXCallDisplayList(l_pirate_flag_matDL, sizeof(l_pirate_flag_matDL) - 0x14);

    GXLoadPosMtxImm(getMtx(), GX_PNMTX0);
    GXLoadNrmMtxImm(getMtx(), GX_PNMTX0);
    GXSetCullMode(GX_CULL_BACK);
    GXCallDisplayList(l_pirate_flag_DL, sizeof(l_pirate_flag_DL) - 0x04);

    GXSetCullMode(GX_CULL_FRONT);
    GXSetArray(GX_VA_NRM, m4F4[m87E], sizeof(cXyz));
    GXCallDisplayList(l_pirate_flag_DL, sizeof(l_pirate_flag_DL) - 0x04);

    J3DShape::resetVcdVatCache();

}

const u8 dummy_4211[] = {0x00, 0xFF, 0x00, 0x80};
const u8 dummy_4243[] = {0x00, 0x00, 0xFF, 0x80};
const u8 dummy_4245[] = {0xFF, 0x00, 0x00, 0x80};

/* 00000E44-000011A0       .text daPirate_Flag_Draw__FP17pirate_flag_class */
static BOOL daPirate_Flag_Draw(pirate_flag_class* i_this) {
    if (l_p_ship->m2CC == 0) {
        return FALSE;
    }

    i_this->tevStr = l_p_ship->tevStr;
    MtxTrans(i_this->current.pos.x, i_this->current.pos.y, i_this->current.pos.z, false);
    cMtx_YrotM(*calc_mtx, i_this->current.angle.y + i_this->shape_angle.y);
    cMtx_XrotM(*calc_mtx, i_this->current.angle.x);
    cMtx_ZrotM(*calc_mtx, i_this->current.angle.z);
    MtxTrans(0.0f, 0.0f, 30.0f, true);
    cMtx_concat(j3dSys.getViewMtx(), *calc_mtx, i_this->mPacket.getMtx());
    i_this->mPacket.setTevStr(&i_this->tevStr);

    j3dSys.getDrawBuffer(0)->entryImm(&i_this->mPacket, 0);
    if (l_HIO.m05 != 0) {
        s16 tmp_r29 = i_this->current.angle.y;

        cXyz tmp;
        dKy_FirstlightVec_get(&tmp);

        s16 tmp2 = cM_atan2s(tmp.x, tmp.z);
        s16 tmp3 = tmp_r29 + i_this->mPacket.getEscapeNrmAngle();
        cXyz vec3;
        cXyz vec4;
        cXyz vec1;
        cXyz vec2;
        vec1.set(cM_ssin(tmp2) * 400.0f, 0.0f, cM_scos(tmp2) * 400.0f);
        vec2.set(cM_ssin(tmp2) * -400.0f, 0.0f, cM_scos(tmp2) * -400.0f);
        vec3.set(cM_ssin(tmp_r29) * 400.0f, 0.0f, cM_scos(tmp_r29) * 400.0f);
        vec4.set(cM_ssin(tmp3) * 400.0f, 0.0f, cM_scos(tmp3) * 400.0f);

        vec1 += i_this->current.pos;
        vec2 += i_this->current.pos;
        vec3 += i_this->current.pos;
        vec4 += i_this->current.pos;

        // dDbVw_drawArrowXlu gets called here in debug build
    }

    return TRUE;
}

/* 000011A0-000012D4       .text get_cloth_anim_sub_factor__FP4cXyzP4cXyzP4cXyzP4cXyzf */
static void get_cloth_anim_sub_factor(cXyz* param_0, cXyz* param_1, cXyz* param_2, cXyz* param_3, float param_4) {
    cXyz tmp = *param_1 - *param_0;
    cXyz normZP = tmp.normZP();
    f32 tmp2 = tmp.abs() - param_4;
    tmp2 *= l_HIO.m18;
    normZP *= tmp2;
    *param_2 += normZP;
}

/* 000012D4-00001624       .text get_cloth_anim_factor__FP17pirate_flag_classP4cXyzP4cXyzP4cXyzP4cXyzii */
static cXyz get_cloth_anim_factor(pirate_flag_class* param_0, cXyz* param_1, cXyz* param_2, cXyz* param_3, cXyz* param_4, int param_5, int param_6) {
    int temp_r30 = param_6 * 5;
    int idx = param_5 + temp_r30;

    cXyz sp20(param_1[idx]);
    cXyz sp14 = param_2[idx] * param_3->inprod(param_2[idx]);
    sp14.y += l_HIO.m14;

    if (param_5 != 0) {
        get_cloth_anim_sub_factor(&sp20, &param_1[temp_r30 + (param_5 - 1)], &sp14, param_4, 200.0f);
        if (param_6 != 0) {
            get_cloth_anim_sub_factor(&sp20, &param_1[ (param_6 - 1) * 5 + param_5], &sp14, param_4, 100.0f);
            get_cloth_anim_sub_factor(&sp20, &param_1[(param_6 - 1) * 5 + (param_5 - 1)], &sp14, param_4, 223.6068f);
        }

        if (param_6 != 4) {
            get_cloth_anim_sub_factor(&sp20, &param_1[(param_6 + 1) * 5 + param_5], &sp14, param_4, 100.0f);
            get_cloth_anim_sub_factor(&sp20, &param_1[(param_6 + 1) * 5 + (param_5 - 1)], &sp14, param_4, 223.6068f);
        }

        if (param_5 != 4) {
            get_cloth_anim_sub_factor(&sp20, &param_1[1 + param_5 + temp_r30], &sp14, param_4, 200.0f);
            if (param_6 != 0) {
                get_cloth_anim_sub_factor(&sp20, &param_1[1 + param_5 + ((param_6 - 1) * 5)], &sp14, param_4, 223.6068f);
            }

            if (param_6 != 4) {
                get_cloth_anim_sub_factor(&sp20, &param_1[1 + param_5 + ((param_6 + 1) * 5)], &sp14, param_4, 223.6068f);
            }
        }

        return sp14;
    }

    if (param_6 != 0 && param_6 != 4) {
        get_cloth_anim_sub_factor(&sp20, &param_1[temp_r30 + (param_5 + 1)], &sp14, param_4, 200.0f);
        if (param_6 != 0) {
            get_cloth_anim_sub_factor(&sp20, &param_1[(param_6 - 1) * 5 + param_5], &sp14, param_4, 100.0f);
            get_cloth_anim_sub_factor(&sp20, &param_1[(param_6 - 1) * 5 + (param_5 + 1)], &sp14, param_4, 223.6068f);
        }

        if (param_6 != 4) {
            get_cloth_anim_sub_factor(&sp20, &param_1[(param_6 + 1) * 5 + param_5], &sp14, param_4, 100.0f);
            get_cloth_anim_sub_factor(&sp20, &param_1[(param_6 + 1) * 5 + (param_5 + 1)], &sp14, param_4, 223.6068f);
        }

        return sp14;
    }

    return cXyz::Zero;
}

/* 00001624-00001938       .text pirate_flag_move__FP17pirate_flag_class */
static void pirate_flag_move(pirate_flag_class*) {
    /* Nonmatching */
}

/* 00001938-00001A38       .text daPirate_Flag_Execute__FP17pirate_flag_class */
static BOOL daPirate_Flag_Execute(pirate_flag_class*) {
    /* Nonmatching */
}

/* 00001A38-00001A40       .text daPirate_Flag_IsDelete__FP17pirate_flag_class */
static BOOL daPirate_Flag_IsDelete(pirate_flag_class*) {
    return TRUE;
}

/* 00001A40-00001A90       .text daPirate_Flag_Delete__FP17pirate_flag_class */
static BOOL daPirate_Flag_Delete(pirate_flag_class* i_this) {
    dComIfG_resDelete(&i_this->mPhs1, "Cloth");
    dComIfG_resDelete(&i_this->mPhs2, "Kaizokusen");

    return TRUE;
}

/* 00001A90-00001C8C       .text daPirate_Flag_Create__FP10fopAc_ac_c */
static s32 daPirate_Flag_Create(fopAc_ac_c*) {
    /* Nonmatching */
}

static s32 daPirate_Flag_ToFore(pirate_flag_class*); // Unused
static s32 daPirate_Flag_ToBack(pirate_flag_class*); // Unused

static actor_method_class l_daPirate_Flag_Method = {
    (process_method_func)daPirate_Flag_Create,
    (process_method_func)daPirate_Flag_Delete,
    (process_method_func)daPirate_Flag_Execute,
    (process_method_func)daPirate_Flag_IsDelete,
    (process_method_func)daPirate_Flag_Draw,
};

actor_process_profile_definition g_profile_PIRATE_FLAG = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_PIRATE_FLAG,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(pirate_flag_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x006A,
    /* Actor SubMtd */ &l_daPirate_Flag_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
