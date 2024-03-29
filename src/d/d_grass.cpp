//
// Generated by dtk
// Translation Unit: d_grass.cpp
//

#include "d/d_grass.h"
#include "f_op/f_op_overlap_mng.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_lib.h"
#include "dolphin/gf/GFGeometry.h"
#include "dolphin/gf/GFTev.h"

/* 80077048-8007712C       .text setBatta__FP4cXyzP8_GXColor */
void setBatta(cXyz* pos, GXColor* color) {
    if (!dKy_rain_check() && !dComIfGp_event_runCheck() && strncmp(dComIfGp_getStartStageName(), "kin", 3) != 0 && strcmp(dComIfGp_getStartStageName(), "Xboss1") != 0 && cM_rnd() > 0.99f)
        dComIfGp_particle_set(0x453, pos, NULL, NULL, 0xFF, NULL, -1, color, color);
}

/* 8007712C-8007734C       .text WorkCo__13dGrass_data_cFP10fopAc_ac_cUli */
void dGrass_data_c::WorkCo(fopAc_ac_c*, u32, int) {
    /* Nonmatching */
}

/* 8007734C-800775E4       .text WorkAt_NoCutAnim__13dGrass_data_cFP10fopAc_ac_cUliP15dCcMassS_HitInfP8cCcD_Obj */
void dGrass_data_c::WorkAt_NoCutAnim(fopAc_ac_c*, u32, int, dCcMassS_HitInf*, cCcD_Obj*) {
    /* Nonmatching */
}

/* 800775EC-800777CC       .text WorkAt__13dGrass_data_cFP10fopAc_ac_cUliP15dCcMassS_HitInf */
void dGrass_data_c::WorkAt(fopAc_ac_c*, u32, int, dCcMassS_HitInf*) {
    /* Nonmatching */
}

/* 800777CC-800779D4       .text hitCheck__13dGrass_data_cFi */
void dGrass_data_c::hitCheck(int) {
    /* Nonmatching */
}

/* 80077A1C-80077A2C       .text newData__13dGrass_room_cFP13dGrass_data_c */
void dGrass_room_c::newData(dGrass_data_c* data) {
    data->mpNextData = mpData;
    mpData = data;
}

/* 80077A2C-80077A90       .text deleteData__13dGrass_room_cFv */
void dGrass_room_c::deleteData() {
    while (mpData != NULL) {
        mpData->mState = 0;
        mDoAud_seDeleteObject(&mpData->mPos);
        mpData = mpData->mpNextData;
    }
}

/* 80077A90-80077CB8       .text __ct__15dGrass_packet_cFv */
dGrass_packet_c::dGrass_packet_c() {
    /* Nonmatching */
}

/* 80077CB8-80077CC4       .text __ct__13dGrass_room_cFv */
dGrass_room_c::dGrass_room_c() {
    mpData = NULL;
}

/* 80077CC4-80077CD0       .text __ct__12dGrass_anm_cFv */
dGrass_anm_c::dGrass_anm_c() {
    mState = 0;
}

/* 80077CD0-80077CDC       .text __ct__13dGrass_data_cFv */
dGrass_data_c::dGrass_data_c() {
    mState = 0;
}

/* 80077CDC-80077E58       .text draw__15dGrass_packet_cFv */
void dGrass_packet_c::draw() {
    /* Nonmatching */
    j3dSys.reinitGX();
    GXSetNumIndStages(0);

    static GXVtxDescList l_vtxDescList[] = {
        {GX_VA_POS, GX_INDEX8},
        {GX_VA_CLR0, GX_INDEX8},
        {GX_VA_TEX0, GX_INDEX8},
        {GX_VA_NULL, GX_NONE},
    };

    static GXVtxAttrFmtList l_vtxAttrFmtList[] = {
        {GX_VA_POS, GX_POS_XYZ, GX_F32, 0x00},
        {GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0x00},
        {GX_VA_TEX0, GX_TEX_ST, GX_F32, 0x00},
        {GX_VA_NULL, GX_POS_XYZ, GX_F32, 0x00},
    };

    GFSetVtxDescv(l_vtxDescList);
    GFSetVtxAttrFmtv(GX_VTXFMT0, l_vtxAttrFmtList);
    GFSetArray(GX_VA_POS, mpPosArr, sizeof(cXyz));
    GFSetArray(GX_VA_CLR0, mpColorArr, sizeof(*mpColorArr));
    GFSetArray(GX_VA_TEX0, mpTexCoordArr, sizeof(cXy));
    GXCallDisplayList(mpMatDL, mMatDLSize);

    dGrass_room_c* room = &mGrassRoom[0];
    for (s32 i = 0; i < (s32)ARRAY_SIZE(mGrassRoom); room++, i++) {
        dKy_tevstr_c* tevstr = dComIfGp_roomControl_getTevStr(i);
        GFSetTevColorS10(GX_TEVREG0, tevstr->mColorC0);
        GFSetTevColor(GX_TEVREG1, tevstr->mColorK0);
        dKy_GfFog_tevstr_set(tevstr);
        for (dGrass_data_c* data = room->mpData; data != NULL; data = data->mpNextData) {
            if (!(data->mInitFlags & 2)) {
                GXLoadPosMtxImm(data->mModelMtx, GX_PNMTX0);
                if (data->mAnimIdx >= 0)
                    GXCallDisplayList(mpDL, mDLSize);
                else
                    GXCallDisplayList(mpDLCut, mDLCutSize);
            }
        }
    }

    J3DShape::resetVcdVatCache();
}

/* 80077E58-80078008       .text calc__15dGrass_packet_cFv */
void dGrass_packet_c::calc() {
    /* Nonmatching */
}

/* 80078008-800782B8       .text checkGroundY__FR4cXyz */
static f32 checkGroundY(cXyz& pos) {
    dBgS_GndChk chk;
    pos.y += 50.0f;
    chk.SetPos(&pos);
    f32 y = dComIfG_Bgsp()->GroundCross(&chk);
    pos.y -= 50.0f;
    if (y <= -1000000000.0f)
        return pos.y;
    else
        return y;
}

/* 800782B8-800784E8       .text update__15dGrass_packet_cFv */
void dGrass_packet_c::update() {
    /* Nonmatching */
    dGrass_anm_c* anm = &mGrassAnm[0];
    for (s32 i = 0; i < (s32)ARRAY_SIZE(mGrassAnm); anm++, i++) {
        mDoMtx_stack_c::YrotS(anm->mRotY);
        mDoMtx_stack_c::XrotM(anm->mRotX);
        mDoMtx_stack_c::YrotM(-anm->mRotY);
        mDoMtx_copy(mDoMtx_stack_c::get(), anm->mAnimMtx);
    }

    dGrass_data_c* data = &mGrassData[0];
    mDoLib_clipper::changeFar(mDoLib_clipper::getFar() * 1.636364f);
    s32 numPerFrame = 0;
    s32 angle = 0;
    for (s32 i = 0; i < (s32)ARRAY_SIZE(mGrassData); data++, i++) {
        if (data->mState != 0) {
            if (data->mState == 1 && numPerFrame < 30) {
                data->mPos.y = checkGroundY(data->mPos);
                data->mState = 2;
                numPerFrame++;
            }

            cXyz pos;
            pos.z = data->mPos.z;
            pos.y = data->mPos.y + 260.0f;
            pos.x = data->mPos.x;
            if (mDoLib_clipper::clip(j3dSys.getViewMtx(), pos, 260.0f)) {
                data->mInitFlags |= 2;
            } else {
                data->mInitFlags &= ~2;
                if (data->mAnimIdx >= 0) {
                    Mtx& mtx = mGrassAnm[data->mAnimIdx].mAnimMtx;
                    mtx[0][3] = pos.x;
                    mtx[1][3] = pos.y;
                    mtx[2][3] = pos.z;
                    mDoMtx_concat(j3dSys.getViewMtx(), mtx, data->mModelMtx);
                } else {
                    mDoMtx_trans(data->mModelMtx, pos.x, pos.y, pos.z);
                    mDoMtx_YrotM(data->mModelMtx, angle);
                    mDoMtx_concat(j3dSys.getViewMtx(), data->mModelMtx, data->mModelMtx);
                }
            }
        }
        angle += 3535;
    }
    mDoLib_clipper::resetFar();
    j3dSys.getDrawBuffer(0)->entryImm(this, 0);
}

/* 800784E8-800785C0       .text setData__15dGrass_packet_cFP13dGrass_data_ciR4cXyziSc */
void dGrass_packet_c::setData(dGrass_data_c* data, int nextIdx, cXyz& pos, int i_roomNo, s8 itemIdx) {
    /* Nonmatching */
    f32 y;
    if (fopOvlpM_IsPeek()) {
        y = checkGroundY(pos);
        data->mState = 2;
    } else {
        y = pos.y;
        data->mState = 1;
    }
    data->mInitFlags = 2;
    data->mAnimIdx = (u8)cM_rndF(7.0f);
    data->mPos.set(pos.x, y, pos.z);
    data->mItemIdx = itemIdx;
    mGrassRoom[i_roomNo].newData(data);
    mNextIdx = nextIdx;
}

/* 800785C0-800786FC       .text newData__15dGrass_packet_cFR4cXyziSc */
dGrass_data_c* dGrass_packet_c::newData(cXyz& pos, int i_roomNo, s8 itemIdx) {
    /* Nonmatching */
    JUT_ASSERT(0x600, 0 <= i_roomNo && i_roomNo < 64);
    s16 idx = mNextIdx;
    dGrass_data_c* data = &mGrassData[idx];
}

/* 800786FC-80078748       .text newAnm__15dGrass_packet_cFv */
s32 dGrass_packet_c::newAnm() {
    dGrass_anm_c* anm = &mGrassAnm[8];
    for (s32 i = 8; i < 104; anm++, i++) {
        if (anm->mState == 0) {
            anm->mState = 1;
            anm->mRotY = 0;
            anm->mRotX = 0;
            return i;
        }
    }
    return -1;
}

/* 80078748-80078770       .text setAnm__15dGrass_packet_cFis */
void dGrass_packet_c::setAnm(int idx, s16 angleY) {
    dGrass_anm_c& anm = mGrassAnm[idx];
    anm.mState = 1;
    anm.mRotY = angleY;
    anm.mRotX = 0;
}
