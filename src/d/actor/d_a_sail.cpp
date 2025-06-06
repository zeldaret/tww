//
// Generated by dtk
// Translation Unit: d_a_sail.cpp
//

#include "d/actor/d_a_sail.h"
#include "d/res/res_kaizokusen.h"
#include "d/res/res_cloth.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo_wether.h"
#include "d/actor/d_a_obj_pirateship.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_mtx.h"
#include "SSystem/SComponent/c_lib.h"
#include "SSystem/SComponent/c_angle.h"

#include "weak_bss_936_to_1036.h" // IWYU pragma: keep
#include "weak_data_1811.h" // IWYU pragma: keep

static daObjPirateship::Act_c* l_p_ship;
static daSail_HIO_c l_HIO;

Vec l_pos[] = {
    {-840.0f, 0.0f, 0.0f},
    {-560.0f, 0.0f, 0.0f},
    {-280.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {280.0f, 0.0f, 0.0f},
    {560.0f, 0.0f, 0.0f},
    {840.0f, 0.0f, 0.0f},
    {-840.0f, -100.0f, 0.0f},
    {-560.0f, -100.0f, 0.0f},
    {-280.0f, -100.0f, 0.0f},
    {0.0f, -100.0f, 0.0f},
    {280.0f, -100.0f, 0.0f},
    {560.0f, -100.0f, 0.0f},
    {840.0f, -100.0f, 0.0f},
    {-840.0f, -200.0f, 0.0f},
    {-560.0f, -200.0f, 0.0f},
    {-280.0f, -200.0f, 0.0f},
    {0.0f, -200.0f, 0.0f},
    {280.0f, -200.0f, 0.0f},
    {560.0f, -200.0f, 0.0f},
    {840.0f, -200.0f, 0.0f},
    {-840.0f, -300.0f, 0.0f},
    {-560.0f, -300.0f, 0.0f},
    {-280.0f, -300.0f, 0.0f},
    {0.0f, -300.0f, 0.0f},
    {280.0f, -300.0f, 0.0f},
    {560.0f, -300.0f, 0.0f},
    {840.0f, -300.0f, 0.0f},
    {-840.0f, -400.0f, 0.0f},
    {-560.0f, -400.0f, 0.0f},
    {-280.0f, -400.0f, 0.0f},
    {0.0f, -400.0f, 0.0f},
    {280.0f, -400.0f, 0.0f},
    {560.0f, -400.0f, 0.0f},
    {840.0f, -400.0f, 0.0f},
    {-840.0f, -500.0f, 0.0f},
    {-560.0f, -500.0f, 0.0f},
    {-280.0f, -500.0f, 0.0f},
    {0.0f, -500.0f, 0.0f},
    {280.0f, -500.0f, 0.0f},
    {560.0f, -500.0f, 0.0f},
    {840.0f, -500.0f, 0.0f},
    {-840.0f, -600.0f, 0.0f},
    {-560.0f, -600.0f, 0.0f},
    {-280.0f, -600.0f, 0.0f},
    {0.0f, -600.0f, 0.0f},
    {280.0f, -600.0f, 0.0f},
    {560.0f, -600.0f, 0.0f},
    {840.0f, -600.0f, 0.0f},
    {-840.0f, -700.0f, 0.0f},
    {-560.0f, -700.0f, 0.0f},
    {-280.0f, -700.0f, 0.0f},
    {0.0f, -700.0f, 0.0f},
    {280.0f, -700.0f, 0.0f},
    {560.0f, -700.0f, 0.0f},
    {840.0f, -700.0f, 0.0f},
    {-840.0f, -800.0f, 0.0f},
    {-560.0f, -800.0f, 0.0f},
    {-280.0f, -800.0f, 0.0f},
    {0.0f, -800.0f, 0.0f},
    {280.0f, -800.0f, 0.0f},
    {560.0f, -800.0f, 0.0f},
    {840.0f, -800.0f, 0.0f},
    {-840.0f, -900.0f, 0.0f},
    {-560.0f, -900.0f, 0.0f},
    {-280.0f, -900.0f, 0.0f},
    {0.0f, -900.0f, 0.0f},
    {280.0f, -900.0f, 0.0f},
    {560.0f, -900.0f, 0.0f},
    {840.0f, -900.0f, 0.0f},
    {-840.0f, -1000.0f, 0.0f},
    {-560.0f, -1000.0f, 0.0f},
    {-280.0f, -1000.0f, 0.0f},
    {0.0f, -1000.0f, 0.0f},
    {280.0f, -1000.0f, 0.0f},
    {560.0f, -1000.0f, 0.0f},
    {840.0f, -1000.0f, 0.0f},
    {-840.0f, -1100.0f, 0.0f},
    {-560.0f, -1100.0f, 0.0f},
    {-280.0f, -1100.0f, 0.0f},
    {0.0f, -1100.0f, 0.0f},
    {280.0f, -1100.0f, 0.0f},
    {560.0f, -1100.0f, 0.0f},
    {840.0f, -1100.0f, 0.0f},
};

cXy l_texCoord[] = {
    {0.0f, 0.0f},
    {0.165f, 0.0f},
    {0.33f, 0.0f},
    {0.495f, 0.0f},
    {0.66f, 0.0f},
    {0.825f, 0.0f},
    {1.0f, 0.0f},
    {0.0f, 0.09f},
    {0.165f, 0.09f},
    {0.33f, 0.09f},
    {0.495f, 0.09f},
    {0.66f, 0.09f},
    {0.825f, 0.09f},
    {1.0f, 0.09f},
    {0.0f, 0.18f},
    {0.165f, 0.18f},
    {0.33f, 0.18f},
    {0.495f, 0.18f},
    {0.66f, 0.18f},
    {0.825f, 0.18f},
    {1.0f, 0.18f},
    {0.0f, 0.27f},
    {0.165f, 0.27f},
    {0.33f, 0.27f},
    {0.495f, 0.27f},
    {0.66f, 0.27f},
    {0.825f, 0.27f},
    {1.0f, 0.27f},
    {0.0f, 0.36f},
    {0.165f, 0.36f},
    {0.33f, 0.36f},
    {0.495f, 0.36f},
    {0.66f, 0.36f},
    {0.825f, 0.36f},
    {1.0f, 0.36f},
    {0.0f, 0.45f},
    {0.165f, 0.45f},
    {0.33f, 0.45f},
    {0.495f, 0.45f},
    {0.66f, 0.45f},
    {0.825f, 0.45f},
    {1.0f, 0.45f},
    {0.0f, 0.54f},
    {0.165f, 0.54f},
    {0.33f, 0.54f},
    {0.495f, 0.54f},
    {0.66f, 0.54f},
    {0.825f, 0.54f},
    {1.0f, 0.54f},
    {0.0f, 0.63f},
    {0.165f, 0.63f},
    {0.33f, 0.63f},
    {0.495f, 0.63f},
    {0.66f, 0.63f},
    {0.825f, 0.63f},
    {1.0f, 0.63f},
    {0.0f, 0.72f},
    {0.165f, 0.72f},
    {0.33f, 0.72f},
    {0.495f, 0.72f},
    {0.66f, 0.72f},
    {0.825f, 0.72f},
    {1.0f, 0.72f},
    {0.0f, 0.81f},
    {0.165f, 0.81f},
    {0.33f, 0.81f},
    {0.495f, 0.81f},
    {0.66f, 0.81f},
    {0.825f, 0.81f},
    {1.0f, 0.81f},
    {0.0f, 0.9f},
    {0.165f, 0.9f},
    {0.33f, 0.9f},
    {0.495f, 0.9f},
    {0.66f, 0.9f},
    {0.825f, 0.9f},
    {1.0f, 0.9f},
    {0.0f, 1.0f},
    {0.165f, 1.0f},
    {0.33f, 1.0f},
    {0.495f, 1.0f},
    {0.66f, 1.0f},
    {0.825f, 1.0f},
    {1.0f, 1.0f},
};

#include "assets/l_sail_DL.h"
#include "assets/l_sail_matDL.h"
#include "assets/l_Txa_kizoku_mastTEX.h"

Vec l_mast_pos[] = {
    {900.0f, 9.676933f, -16.760941f},
    {900.0f, -9.676933f, -16.760941f},
    {900.0f, -19.353867f, -0.000004f},
    {900.0f, -9.676933f, 16.760941f},
    {900.0f, 9.676933f, 16.760941f},
    {900.0f, 19.353867f, -0.000001f},
    {-900.0f, 9.676933f, -16.760941f},
    {-900.0f, -9.676933f, -16.760941f},
    {-900.0f, -19.353867f, -0.000004f},
    {-900.0f, -9.676933f, 16.760941f},
    {-900.0f, 9.676933f, 16.760941f},
    {-900.0f, 19.353867f, -0.000001f},
    {900.0f, -0.000001f, -0.000001f},
    {-900.0f, -0.000001f, -0.000001f},
    {0.0f, 6.105309f, 28.277588f},
    {0.0f, -26.54686f, 28.277588f},
    {0.0f, -42.875366f, -0.000005f},
    {0.0f, -26.546822f, -28.277588f},
    {0.0f, 6.105347f, -28.277588f},
    {0.0f, 22.42897f, 0.0f},
};

GXColor l_mast_color[] = {
    {0xA8, 0xA8, 0xA8, 0xFF},
    {0x5D, 0x5D, 0x5D, 0xFF},
    {0xF3, 0xF3, 0xF3, 0xFF},
    {0xC6, 0xC6, 0xC6, 0xFF},
    {0x38, 0x38, 0x38, 0xFF},
    {0x56, 0x56, 0x56, 0xFF},
    {0x0B, 0x0B, 0x0B, 0xFF},
    {0xA1, 0xA1, 0xA1, 0xFF},
};

cXy l_mast_texCoord[] = {
    {1.0f, 0.0f},
    {1.0f, 1.0f},
    {0.0f, 1.0f},
    {0.0f, 0.0f},
    {0.881686f, 1.0f},
    {0.89115f, 0.0f},
    {0.888606f, 1.0f},
    {0.888606f, 0.0f},
};

#include "assets/l_AmastDL.h"

/* 000000EC-00000364       .text setCorrectNrmAngle__15daSail_packet_cFsf */
void daSail_packet_c::setCorrectNrmAngle(s16 param_0, f32 param_1) {
    m1C38 += (s16)(900 + (s32)cM_rndF(200.0f));

    m1C34 = 300.0f * cM_ssin(m1C38);

    s16 r28 = param_0 + 0x8000;
    s32 r27 = param_0;

    s16 r26 = l_HIO.m10 * (1.0f - 0.5f * param_1);
    s32 r0 = abs(r28);
    s16 r30 = cAngle::d2s(1.25f * r26);

    if (r0 < r30) {
        s16 targetAngle = r28 > 0 ? (s16)cAngle::d2s(-r26) : (s16)cAngle::d2s(r26);
        cLib_addCalcAngleS2(&m1C36, targetAngle, 5, 192);
    } else if (abs(r27) < r30) {
        s16 targetAngle = (s16)r27 > 0 ? (s16)cAngle::d2s(-r26) : (s16)cAngle::d2s(r26);
        cLib_addCalcAngleS2(&m1C36, targetAngle, 5, 192);
    } else {
        cLib_addCalcAngleS2(&m1C36, 0, 5, 192);
    }
    m1C34 += m1C36;
}

/* 00000364-00000398       .text setNrmMtx__15daSail_packet_cFv */
void daSail_packet_c::setNrmMtx() {
    mDoMtx_YrotS(*calc_mtx, m1C34);
}

/* 00000398-00000424       .text setBackNrm__15daSail_packet_cFv */
void daSail_packet_c::setBackNrm() {
    cXyz* vtxNrm1 = getNrm();
    cXyz* vtxNrm2 = m1454[m1C3A];
    for (int i = 0; i < 0x54; i++) {
        vtxNrm2->setall(0.0f);
        *vtxNrm2 -= *vtxNrm1;
        vtxNrm1++;
        vtxNrm2++;
    }
}

/* 00000424-00000834       .text setNrmVtx__15daSail_packet_cFP4cXyzii */
void daSail_packet_c::setNrmVtx(cXyz* param_0, int param_1, int param_2) {
    cXyz spF8;
    cXyz spEC;
    cXyz spE0;
    cXyz spD4;
    cXyz spC8;
    cXyz* vtxPos = getPos();
    s32 idx = param_2 * 7;
    spC8.set(vtxPos[param_1 + idx]);
    spD4.setall(0.0f);

    if (param_1 != 0) {
        spF8 = vtxPos[idx - 1 + param_1] - spC8;
        if (param_2 != 0) {
            spEC = vtxPos[(param_2 - 1) * 7 + param_1] - spC8;
            spE0 = spEC.outprod(spF8);
            spE0 = spE0.normZC();
            spD4 += spE0;
        }
        if (param_2 != 11) {
            spEC = vtxPos[(param_2 + 1) * 7 + param_1] - spC8;
            spE0 = spF8.outprod(spEC);
            spE0 = spE0.normZC();
            spD4 += spE0;
        }
    }
    if (param_1 != 6) {
        spF8 = vtxPos[param_1 + 1 + idx] - spC8;
        if (param_2 != 0) {
            spEC = vtxPos[(param_2 - 1) * 7 + param_1] - spC8;
            spE0 = spF8.outprod(spEC);
            spE0 = spE0.normZC();
            spD4 += spE0;
        }
        if (param_2 != 11) {
            spEC = vtxPos[(param_2 + 1) * 7 + param_1] - spC8;
            spE0 = spEC.outprod(spF8);
            spE0 = spE0.normZC();
            spD4 += spE0;
        }
    }

    spD4 = spD4.normZC();

    MtxPush();
    mDoMtx_YrotM(*calc_mtx, cM_ssin(-800 * (param_1 + param_2)) * 900.0f);
    MtxPosition(&spD4, &spE0);
    *param_0 = spE0.normZC();
    MtxPull();
}

/* 00000870-000010D8       .text draw__15daSail_packet_cFv */
void daSail_packet_c::draw() {
    j3dSys.reinitGX();

#if VERSION > VERSION_JPN
    GXSetNumIndStages(0);
#endif

    dKy_GxFog_tevstr_set(mTevStr);

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

    ResTIMG* kaizokusen = (ResTIMG*)dComIfG_getObjectRes("Kaizokusen", KAIZOKUSEN_INDEX_BTI_TXA_KAIZOKU_HO);
    GXInitTexObj(&texObj, (u8*)kaizokusen + kaizokusen->imageOffset, kaizokusen->width, kaizokusen->height,
        (GXTexFmt)kaizokusen->format, (GXTexWrapMode)kaizokusen->wrapS, (GXTexWrapMode)kaizokusen->wrapT,
        kaizokusen->mipmapCount > 1);
    GXInitTexObjLOD(&texObj, (GXTexFilter)kaizokusen->minFilter, (GXTexFilter)kaizokusen->magFilter,
        kaizokusen->minLOD * 0.125f, kaizokusen->maxLOD * 0.125f, kaizokusen->LODBias * 0.01f,
        kaizokusen->biasClamp, kaizokusen->doEdgeLOD, (GXAnisotropy)kaizokusen->maxAnisotropy);
    GXLoadTexObj(&texObj, GX_TEXMAP0);

    ResTIMG* cloth = (ResTIMG*)dComIfG_getObjectRes("Cloth", CLOTH_BTI_CLOTHTOON);
    GXInitTexObj(&texObj, (u8*)cloth + cloth->imageOffset, cloth->width, cloth->height,
        (GXTexFmt)cloth->format, (GXTexWrapMode)cloth->wrapS, (GXTexWrapMode)cloth->wrapT,
        cloth->mipmapCount > 1);
    GXInitTexObjLOD(&texObj, (GXTexFilter)cloth->minFilter, (GXTexFilter)cloth->magFilter,
        cloth->minLOD * 0.125f, cloth->maxLOD * 0.125f, cloth->LODBias * 0.01f,
        cloth->biasClamp, cloth->doEdgeLOD, (GXAnisotropy)cloth->maxAnisotropy);
    GXLoadTexObj(&texObj, GX_TEXMAP1);

    GXSetNumChans(1);

    u8 numTevStages, lightMask;
    if (mTevStr->mColorK1.a != 0) {
        numTevStages = 3;
        lightMask = GX_LIGHT0 | GX_LIGHT1;
    } else {
        numTevStages = 2;
        lightMask = GX_LIGHT0;
    }

    if (l_HIO.m05 != 0) {
        GXSetChanCtrl(GX_COLOR0, 1, GX_SRC_REG, GX_SRC_REG, lightMask, GX_DF_CLAMP, GX_AF_NONE);
        GXSetNumTexGens(2);
        GXLoadTexMtxImm(*getTexMtx(), 30, GX_MTX3x4);
        GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_TEX0, 30);
        GXSetTexCoordGen(GX_TEXCOORD1, GX_TG_SRTG, GX_TG_COLOR0, 60);
        GXSetNumTevStages(numTevStages);
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
        if (numTevStages == 3) {
            GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP2);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_C2, GX_CC_TEXC, GX_CC_CPREV);
            GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        }
    } else {
        GXSetChanCtrl(GX_COLOR0, 1, GX_SRC_REG, GX_SRC_REG, lightMask, GX_DF_CLAMP, GX_AF_NONE);
        GXSetNumTexGens(1);
        GXLoadTexMtxImm(*getTexMtx(), 30, GX_MTX3x4);
        GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_TEX0, 30);
        GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 60);
        GXSetNumTevStages(numTevStages);
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
        if (numTevStages == 3) {
            GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP2, GX_TEV_SWAP0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_C2, GX_CC_RASC, GX_CC_CPREV);
            GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        }
    }

    GXSetTevColorS10(GX_TEVREG0, mTevStr->mColorC0);
    GXSetTevColor(GX_TEVREG1, mTevStr->mColorK0);
    GXSetTevColor(GX_TEVREG2, mTevStr->mColorK1);
    GXCallDisplayList(l_sail_matDL, 0x20);

    GXLoadPosMtxImm(*getMtx(), 0);
    GXLoadNrmMtxImm(*getMtx(), 0);

    GXSetZCompLoc(GX_FALSE);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetCullMode(GX_CULL_BACK);
    GXCallDisplayList(l_sail_DL, 0x200);

    GXSetCullMode(GX_CULL_FRONT);
    GXSetArray(GX_VA_NRM, getNrm() + 2 * 0x54, sizeof(cXyz));
    GXCallDisplayList(l_sail_DL, 0x200);

#if VERSION > VERSION_JPN
    J3DShape::resetVcdVatCache();
#endif
}

/* 000010D8-000013CC       .text daSail_Draw__FP10sail_class */
static BOOL daSail_Draw(sail_class* i_this) {
    if (l_p_ship->m2CC == 0) {
        return FALSE;
    }

    i_this->tevStr = l_p_ship->tevStr;

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->current.pos, &i_this->tevStr);
    g_env_light.setLightTevColorType(i_this->mSailPacket.mStickModel, &i_this->tevStr);
    mDoExt_modelUpdateDL(i_this->mSailPacket.mStickModel);

    MtxTrans(i_this->current.pos.x, i_this->current.pos.y, i_this->current.pos.z, 0);
    mDoMtx_YrotM(*calc_mtx, i_this->current.angle.y);
    mDoMtx_XrotM(*calc_mtx, i_this->current.angle.x);
    mDoMtx_ZrotM(*calc_mtx, i_this->current.angle.z);

    mDoMtx_concat(j3dSys.getViewMtx(), *calc_mtx, *i_this->mSailPacket.getMtx());

    cXyz* vtxPos = i_this->mSailPacket.getPos();
    MtxTrans(
        i_this->current.pos.x,
        i_this->current.pos.y + vtxPos[0x53].y,
        i_this->current.pos.z,
        0
    );

    mDoMtx_YrotM(*calc_mtx, i_this->current.angle.y);
    mDoMtx_XrotM(*calc_mtx, i_this->current.angle.x);
    mDoMtx_ZrotM(*calc_mtx, i_this->current.angle.z);

    mDoMtx_concat(j3dSys.getViewMtx(), *calc_mtx, *i_this->mSailPacket.getStickMtx());
    i_this->mSailPacket.mStickModel->setBaseTRMtx(*calc_mtx);

    MtxTrans(0.0f, 0.0f, 0.0f, 0);
    mDoMtx_copy(*calc_mtx, i_this->mSailPacket.mTexMtx);

    i_this->mSailPacket.setTevStr(&i_this->tevStr);

    j3dSys.getDrawBuffer(0)->entryImm(&i_this->mSailPacket, 0);

    return TRUE;
}

/* 000013CC-00001CEC       .text sail_pos_move__FP10sail_class */
static void sail_pos_move(sail_class* i_this) {
    cXyz* windVec = dKyw_get_wind_vec();
    s16 windAngle = cM_atan2s(windVec->x, windVec->z);
    mDoMtx_YrotS(*calc_mtx, -(i_this->current.angle.y - windAngle));

    cXyz sp28;
    cXyz sp1C;
    cXyz sp10;

    sp28.set(0.0f, 0.0f, 0.064f);
    MtxPosition(&sp28, &sp1C);

    f32 f31 = (0.9f * std::fabsf(sp1C.z)) + 0.02f + (0.064f / 10.0f);
    sp28.x = 0.0f;
    sp28.z = 1.0f;
    MtxPosition(&sp28, &sp1C);

    f32 f25 = (0.9f * std::fabsf(sp1C.z)) + 0.1f;
    f32 f0 = std::fabsf(sp1C.x);

    i_this->mSailPacket.m1C40 += (s32)((1.0f - (i_this->mSailPacket.m1C44 * 0.95f)) * 4000.0f) * ((f25 * 0.85f) + 0.15f);
    i_this->mSailPacket.m1C50 = ((f0 * 1.5f) + 1.0f) * 7500.0f;
    i_this->mSailPacket.m1C52 = ((f25 * 0.95f) + 0.05f) * 7200.0f;

    cXyz* vtxPos = i_this->mSailPacket.getPos();
    f32 sp6C[7] = {};
    f32 sp34[7] = {};

    f25 *= 1.0f - (0.5f * i_this->mSailPacket.m1C44 * i_this->mSailPacket.m1C4C);
    f0 *= 1.0f - (0.75f * i_this->mSailPacket.m1C44);

    f32 ELEVEN = 11.0f; // this must be non-const

    for (int i = 0; i < 12; i++) {
        f32 f12 = i - 6;
        f32 f13 = i - 5.5f;

        sp10.z = f25 * (-ELEVEN * f12 * f12 + 396.0f);

        for (int j = 0; j < 7; j++, vtxPos++) {
            f32 f24;
            f32 f23 = j - 3;
            f32 f22, f21, f20; // these are xyz components
            f32 f17 = i * 5.0f;

            // these explicit casts are necessary
            u32 r22 = (i_this->mSailPacket.m1C50 * (s32)f23) + (i_this->mSailPacket.m1C52 * (s32)f12);

            f20 = 1750.0f * ((f0 * f0) + 0.05f) * cM_ssin(-i_this->mSailPacket.m1C40 + r22) * f31;
            f22 = 550.0f * ((f0 * f0) + 0.1f) * cM_scos(i_this->mSailPacket.m1C40 + r22) * f31;
            f21 = std::sqrtf((f22 * f22) + (f20 * f20)) * 0.1f;

            f24 = (f25 * ((10.0f * f17) + (-f17 * f23 * f23)));
            f24 += ((sp10.z * (18.0f - f23 * f23)) / 18.0f);

            f32 f15 = f24 - sp34[j];

            f32 f16;
            if (f15 > 100.0f) {
                f16 = 100.0f;
                sp34[j] += 100.0f;
            } else {
                f16 = -100.0f;
                if (f15 < f16) {
                    sp34[j] -= 100.0f;
                } else {
                    f16 = f15;
                    sp34[j] = f24;
                }
            }

            f32 f14 = 100.0f - std::sqrtf((125.0f * 125.0f) - (f16 * f16));
            sp6C[j] += f14 > -10.0f ? f14 : -10.0f;

            sp10.x = 0.0f;
            sp10.y = 0.0f;
            if (i < 3) {
                f22 *= i * 0.33f;
                f21 *= i * 0.33f;
                f20 *= i * 0.33f;
            } else if (i == 11 && std::fabsf(f23) == 3.0f) {
                f22 = 0.0f;
                f21 = 0.0f;
                f20 = 0.0f;
            }

            vtxPos->x = sp10.x + f22;
            vtxPos->y = ((sp6C[j] + sp10.y + f21) - (i * 1.25f * (f23 * f23)));
            vtxPos->z = f24 + f20;

            vtxPos->x += l_pos[i * 7 + j].x;
            vtxPos->y += l_pos[i * 7 + j].y;
            vtxPos->z += l_pos[i * 7 + j].z;

            vtxPos->y *= (1.0f - ((i_this->mSailPacket.m1C44 * (f13 * f13)) / 30.25f));
            vtxPos->y *= ((ELEVEN - (i_this->mSailPacket.m1C44 * i)) / ELEVEN);
            vtxPos->z *= (1.0f - ((i_this->mSailPacket.m1C44 * (f13 * f13)) / 30.25f));
            vtxPos->z *= ((ELEVEN - (i_this->mSailPacket.m1C44 * i)) / ELEVEN);

            if (i_this->mSailPacket.m1C44 > 0.0f && i < 6) {
                f32 f15_2 = i - 3;
                f32 f20 = (9.0f - (f15_2 * f15_2)) / 9.0f;
                vtxPos->z += (700.0f * f20 * i_this->mSailPacket.m1C44);
                vtxPos->y -= (150.0f * f20 * i_this->mSailPacket.m1C44);
            }

            vtxPos->y *= (0.3f * (j & 1) * i_this->mSailPacket.m1C44) + (1.0f - i_this->mSailPacket.m1C44);
            vtxPos->z *= (0.15f * (j & 1) * i_this->mSailPacket.m1C44) + (1.0f - i_this->mSailPacket.m1C44);
        }
    }
}

/* 00001CEC-00001DB0       .text demo_move__FP10sail_class */
static BOOL demo_move(sail_class* i_this) {
    if (i_this->demoActorID == 0) {
        return FALSE;
    }
    dDemo_actor_c* demo_actor = dComIfGp_demo_getActor(i_this->demoActorID);
    if (demo_actor != NULL) {
        if (demo_actor->checkEnable(dDemo_actor_c::ENABLE_ANM_FRAME_e)) {
            f32 frame = demo_actor->getAnmFrame();
            frame = 0.6f - (frame * 0.006f);
            i_this->mSailPacket.m1C44 = frame;
            i_this->mSailPacket.m1C44 = cLib_minMaxLimit<f32>(i_this->mSailPacket.m1C44, 0.0f, 0.6f);
        }
        return TRUE;
    }
    return FALSE;
}

/* 00001DB0-00002094       .text sail_move__FP10sail_class */
static void sail_move(sail_class* i_this) {
    cXyz* windVec = dKyw_get_wind_vec();
    if (l_HIO.m06 == 0 && i_this->mSailPacket.m1C44 < 0.6f) {
        if (i_this->mSailPacket.m1C48 <= 0.0f) {
            i_this->mSailPacket.m1C48 = 0.015f;
        } else {
            i_this->mSailPacket.m1C48 -= 0.001f;
        }
        cLib_addCalc(&i_this->mSailPacket.m1C44, 0.6f, 0.1f, i_this->mSailPacket.m1C48, 0.01f);
    } else {
        if (l_HIO.m06 == 1 && i_this->mSailPacket.m1C44 > 0.0f) {
            i_this->mSailPacket.m1C48 += 0.0075f;
            cLib_addCalc(&i_this->mSailPacket.m1C44, 0.0f, 0.3f, i_this->mSailPacket.m1C48, 0.01f);
        } else {
            i_this->mSailPacket.m1C48 = 0.0f;
        }
    }

    if (i_this->mSailPacket.m1C44 > 1.0f) {
        i_this->mSailPacket.m1C44 = 1.0f;
    } else if (i_this->mSailPacket.m1C44 < 0.0f) {
        i_this->mSailPacket.m1C44 = 0.0f;
    }

    if (!demo_move(i_this) && l_HIO.m08 != 0) {
        i_this->mSailPacket.m1C44 = l_HIO.m0C;
    }
    i_this->mSailPacket.m1C4C = (i_this->mSailPacket.m1C44 - 0.6f) * 15.0f;

    s16 windAngle = cM_atan2s(windVec->x, windVec->z);
    mDoMtx_YrotS(*calc_mtx, -(i_this->current.angle.y - windAngle));

    cXyz sp2C(0.0f, 0.0f, 0.064f);
    cXyz sp20;
    MtxPosition(&sp2C, &sp20);

    sp2C.x = 0.0f;
    sp2C.z = 1.0f;
    MtxPosition(&sp2C, &sp20);

    f32 f31_1 = std::fabsf(sp20.z);
    sail_pos_move(i_this);
    f32 f31_2 = f31_1 * (1.0f - (i_this->mSailPacket.m1C44 * 0.5f * i_this->mSailPacket.m1C4C));

    cXyz* vtxPos = i_this->mSailPacket.getPos() + 3 * 0x54;

    s16 angleY = i_this->current.angle.y;
    cXyz light;
    dKy_FirstlightVec_get(&light);
    s16 lightAngle = cM_atan2s(light.x, light.z);

    i_this->mSailPacket.setCorrectNrmAngle(lightAngle - angleY, f31_2);

    i_this->mSailPacket.setNrmMtx();
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 7; j++) {
            i_this->mSailPacket.setNrmVtx(vtxPos, j, i);
            vtxPos++;
        }
    }
    i_this->mSailPacket.setBackNrm();

#if VERSION <= VERSION_JPN
    // Bug: The number of bytes (0x14AC0) passed here is way too large and causes an overflow.
    // The below sizeof calculation is a guess as to what led the devs to arriving at this wrong number.
    DCStoreRangeNoSync(i_this->mSailPacket.getPos(), sizeof(*i_this->mSailPacket.mPos) * sizeof(*i_this->mSailPacket.mNrm) / sizeof(cXyz));
#else
    DCStoreRangeNoSync(i_this->mSailPacket.getPos(), sizeof(*i_this->mSailPacket.mPos));
    DCStoreRangeNoSync(i_this->mSailPacket.getNrm(), sizeof(*i_this->mSailPacket.mNrm));
    DCStoreRangeNoSync(i_this->mSailPacket.getNrm() + sizeof(i_this->mSailPacket.mNrm) / sizeof(cXyz), sizeof(*i_this->mSailPacket.m1454)); // Fakematch?
#endif
}

/* 00002094-00002154       .text daSail_Execute__FP10sail_class */
static BOOL daSail_Execute(sail_class* i_this) {
    static cXyz sail_offset(0.0f, 2100.0f, 100.0f);
    cMtx_multVec(l_p_ship->mpModel->getBaseTRMtx(), &sail_offset, &i_this->current.pos);
    i_this->current.angle = l_p_ship->shape_angle;
    sail_move(i_this);
    return TRUE;
}

/* 00002154-0000215C       .text daSail_IsDelete__FP10sail_class */
static BOOL daSail_IsDelete(sail_class* i_this) {
    return TRUE;
}

/* 0000215C-000021D8       .text daSail_Delete__FP10sail_class */
static BOOL daSail_Delete(sail_class* i_this) {
    dComIfG_resDelete(&i_this->mClothPhase, "Cloth");
    dComIfG_resDelete(&i_this->mKaizokusenPhase, "Kaizokusen");
    
    if (l_HIO.mNo >= 0) {
        mDoHIO_root.m_subroot.deleteChild(l_HIO.mNo);
        l_HIO.mNo = -1;
    }
    
    return TRUE;
}

/* 000021D8-00002254       .text daSail_checkCreateHeap__FP10fopAc_ac_c */
static BOOL daSail_checkCreateHeap(fopAc_ac_c* i_actor) {
    sail_class* i_this = (sail_class*)i_actor;
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Kaizokusen", KAIZOKUSEN_INDEX_BDL_AMAST);
    if (modelData == NULL) {
        return FALSE;
    }
    i_this->mSailPacket.mStickModel = mDoExt_J3DModel__create(modelData, 0x00080000, 0x11000002);
    if (i_this->mSailPacket.mStickModel != NULL) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 00002254-000024E4       .text daSail_Create__FP10fopAc_ac_c */
static cPhs_State daSail_Create(fopAc_ac_c* i_actor) {
    fopAcM_SetupActor(i_actor, sail_class);
    sail_class* i_this = (sail_class*)i_actor;
    
    {
        cPhs_State phase_state = dComIfG_resLoad(&i_this->mClothPhase, "Cloth");
        if (phase_state != cPhs_COMPLEATE_e) {
            return phase_state;
        }
        phase_state = dComIfG_resLoad(&i_this->mKaizokusenPhase, "Kaizokusen");
        if (phase_state != cPhs_COMPLEATE_e) {
            return phase_state;
        }
    }
    
    cPhs_State phase_state = cPhs_COMPLEATE_e;
    if (fopAcM_entrySolidHeap(i_this, daSail_checkCreateHeap, 0x4C0)) {
        if (l_HIO.mNo < 0) {
            l_HIO.mNo = mDoHIO_root.m_subroot.createChild("海賊船の帆", &l_HIO); // "Pirate Ship's Sail"
        }
        
        i_this->mSailPacket.m1C44 = 0.0f;
        i_this->mSailPacket.m1C48 = 0.0f;
        cXyz* vtxPosSpd = i_this->mSailPacket.getPosSpd();
        cXyz* vtxPos = i_this->mSailPacket.getPos();
        for (int i = 0; i < ARRAY_SIZE(l_pos); i++, vtxPosSpd++, vtxPos++) {
            vtxPosSpd->setall(0.0f);
            vtxPos->set(l_pos[i]);
        }
        
        l_p_ship = (daObjPirateship::Act_c*)fopAcM_SearchByID(i_this->parentActorID);
        if (l_p_ship->m2CE == 0) {
            l_HIO.m06 = 0;
            i_this->mSailPacket.m1C44 = 0.6f;
        } else {
            l_HIO.m06 = 1;
        }
        
        sail_move(i_this);
    } else {
        phase_state = cPhs_ERROR_e;
    }
    
    return phase_state;
}

static actor_method_class l_daSail_Method = {
    (process_method_func)daSail_Create,
    (process_method_func)daSail_Delete,
    (process_method_func)daSail_Execute,
    (process_method_func)daSail_IsDelete,
    (process_method_func)daSail_Draw,
};

actor_process_profile_definition g_profile_SAIL = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_SAIL,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(sail_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_SAIL,
    /* Actor SubMtd */ &l_daSail_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
