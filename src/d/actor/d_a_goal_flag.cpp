/**
 * d_a_goal_flag.cpp
 * Object - Big red finish line flag (Boating Course, Flight Control Platform)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_goal_flag.h"
#include "d/actor/d_a_npc_sarace.h"
#include "d/d_minigame_starter.h"
#include "d/res/res_cloth.h"
#include "d/res/res_gflag.h"
#include "d/res/res_tgflag.h"
#include "d/d_path.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

#include "assets/l_txa_dummy_hataTEX.h"
#include "m_Do/m_Do_controller_pad.h"

static Vec l_pos[] = {
    { -1000.0f,    0.0f, 0.0f }, 
    {  -750.0f,    0.0f, 0.0f }, 
    {  -500.0f,    0.0f, 0.0f }, 
    {  -250.0f,    0.0f, 0.0f }, 
    {     0.0f,    0.0f, 0.0f }, 
    {   250.0f,    0.0f, 0.0f }, 
    {   500.0f,    0.0f, 0.0f }, 
    {   750.0f,    0.0f, 0.0f }, 
    {  1000.0f,    0.0f, 0.0f }, 
    { -1000.0f, -100.0f, 0.0f }, 
    {  -750.0f, -100.0f, 0.0f }, 
    {  -500.0f, -100.0f, 0.0f }, 
    {  -250.0f, -100.0f, 0.0f }, 
    {     0.0f, -100.0f, 0.0f }, 
    {   250.0f, -100.0f, 0.0f }, 
    {   500.0f, -100.0f, 0.0f }, 
    {   750.0f, -100.0f, 0.0f }, 
    {  1000.0f, -100.0f, 0.0f }, 
    { -1000.0f, -200.0f, 0.0f }, 
    {  -750.0f, -200.0f, 0.0f }, 
    {  -500.0f, -200.0f, 0.0f }, 
    {  -250.0f, -200.0f, 0.0f }, 
    {     0.0f, -200.0f, 0.0f }, 
    {   250.0f, -200.0f, 0.0f }, 
    {   500.0f, -200.0f, 0.0f }, 
    {   750.0f, -200.0f, 0.0f }, 
    {  1000.0f, -200.0f, 0.0f }, 
    { -1000.0f, -300.0f, 0.0f }, 
    {  -750.0f, -300.0f, 0.0f }, 
    {  -500.0f, -300.0f, 0.0f }, 
    {  -250.0f, -300.0f, 0.0f }, 
    {     0.0f, -300.0f, 0.0f }, 
    {   250.0f, -300.0f, 0.0f }, 
    {   500.0f, -300.0f, 0.0f }, 
    {   750.0f, -300.0f, 0.0f }, 
    {  1000.0f, -300.0f, 0.0f }, 
    { -1000.0f, -400.0f, 0.0f }, 
    {  -750.0f, -400.0f, 0.0f }, 
    {  -500.0f, -400.0f, 0.0f }, 
    {  -250.0f, -400.0f, 0.0f }, 
    {     0.0f, -400.0f, 0.0f }, 
    {   250.0f, -400.0f, 0.0f }, 
    {   500.0f, -400.0f, 0.0f }, 
    {   750.0f, -400.0f, 0.0f }, 
    {  1000.0f, -400.0f, 0.0f } 
};

static cXy l_texCoord[] = {
    {   1.0f,  0.0f }, 
    { 0.875f,  0.0f }, 
    {  0.75f,  0.0f }, 
    { 0.625f,  0.0f }, 
    {   0.5f,  0.0f }, 
    { 0.375f,  0.0f }, 
    {  0.25f,  0.0f }, 
    { 0.125f,  0.0f }, 
    {   0.0f,  0.0f }, 
    {   1.0f, 0.25f }, 
    { 0.875f, 0.25f }, 
    {  0.75f, 0.25f }, 
    { 0.625f, 0.25f }, 
    {   0.5f, 0.25f }, 
    { 0.375f, 0.25f }, 
    {  0.25f, 0.25f }, 
    { 0.125f, 0.25f }, 
    {   0.0f, 0.25f }, 
    {   1.0f,  0.5f }, 
    { 0.875f,  0.5f }, 
    {  0.75f,  0.5f }, 
    { 0.625f,  0.5f }, 
    {   0.5f,  0.5f }, 
    { 0.375f,  0.5f }, 
    {  0.25f,  0.5f }, 
    { 0.125f,  0.5f }, 
    {   0.0f,  0.5f }, 
    {   1.0f, 0.75f }, 
    { 0.875f, 0.75f }, 
    {  0.75f, 0.75f }, 
    { 0.625f, 0.75f }, 
    {   0.5f, 0.75f }, 
    { 0.375f, 0.75f }, 
    {  0.25f, 0.75f }, 
    { 0.125f, 0.75f }, 
    {   0.0f, 0.75f }, 
    {   1.0f,  1.0f }, 
    { 0.875f,  1.0f }, 
    {  0.75f,  1.0f }, 
    { 0.625f,  1.0f }, 
    {   0.5f,  1.0f }, 
    { 0.375f,  1.0f }, 
    {  0.25f,  1.0f }, 
    { 0.125f,  1.0f }, 
    {   0.0f,  1.0f } 
};

#include "assets/l_goal_flag_DL.h"
#include "assets/l_goal_flag_matDL.h"
l_goal_flag_matDL(l_txa_dummy_hataTEX);

static const char* sub_arcname_tbl[] = {
    "Gflag",
    "Tgflag"
};
static const char arcname[] = "Cloth";

static daGFlag_HIO_c l_HIO;

daGFlag_HIO_c::~daGFlag_HIO_c() {
    m04 = -1;
}

/* 000000EC-00000210       .text setTexObj__16daGFlag_packet_cFUc */
void daGFlag_packet_c::setTexObj(u8 i_arcIdx) {
    static char* arc_name_tbl[] = {
        "Gflag",
        "Tgflag"
    };
    static const int index_tbl[] = {
        GFLAG_BTI_B_FRAGGAIKOT,
        TGFLAG_BTI_B_FRAGTORI
    };
    // index_tbl likely existed in this function but passing 
    // an element of it into getObjectRes breaks the match
    ResTIMG* tex_info_p = (ResTIMG*) dComIfG_getObjectRes(arc_name_tbl[i_arcIdx], 3);
    GXInitTexObj(
        &mTexObj, 
        (u8*)tex_info_p + tex_info_p->imageOffset, 
        tex_info_p->width, 
        tex_info_p->height, 
        GXTexFmt(tex_info_p->format), 
        GXTexWrapMode(tex_info_p->wrapS), 
        GXTexWrapMode(tex_info_p->wrapT),
        GXBool(tex_info_p->mipmapCount > 1)
    );
    GXInitTexObjLOD(
        &mTexObj,
        GXTexFilter(tex_info_p->minFilter),
        GXTexFilter(tex_info_p->magFilter),
        (f32)tex_info_p->minLOD * 0.125f,
        (f32)tex_info_p->maxLOD * 0.125f,
        (f32)tex_info_p->LODBias * 0.01f,
        GXBool(tex_info_p->biasClamp),
        GXBool(tex_info_p->doEdgeLOD),
        GXAnisotropy(tex_info_p->maxAnisotropy)
    );
}

/* 00000210-00000330       .text setToonTexObj__16daGFlag_packet_cFv */
void daGFlag_packet_c::setToonTexObj() {
    ResTIMG* tex_info_p = (ResTIMG*) dComIfG_getObjectRes("Cloth", CLOTH_BTI_CLOTHTOON);
    GXInitTexObj(
        &mToonTexObj, 
        (u8*)tex_info_p + tex_info_p->imageOffset, 
        tex_info_p->width, 
        tex_info_p->height, 
        GXTexFmt(tex_info_p->format), 
        GXTexWrapMode(tex_info_p->wrapS), 
        GXTexWrapMode(tex_info_p->wrapT),
        GXBool(tex_info_p->mipmapCount > 1)
    );
    GXInitTexObjLOD(
        &mToonTexObj,
        GXTexFilter(tex_info_p->minFilter),
        GXTexFilter(tex_info_p->magFilter),
        (f32)tex_info_p->minLOD * 0.125f,
        (f32)tex_info_p->maxLOD * 0.125f,
        (f32)tex_info_p->LODBias * 0.01f,
        GXBool(tex_info_p->biasClamp),
        GXBool(tex_info_p->doEdgeLOD),
        GXAnisotropy(tex_info_p->maxAnisotropy)
    );
}

/* 00000330-00000978       .text draw__16daGFlag_packet_cFv */
void daGFlag_packet_c::draw() {
    j3dSys.reinitGX();
    GXSetNumIndStages(0);
    dKy_GxFog_tevstr_set(mpTevStr);
    dKy_setLight_mine(mpTevStr);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS,GX_INDEX8);
    GXSetVtxDesc(GX_VA_NRM,GX_INDEX8);
    GXSetVtxDesc(GX_VA_TEX0,GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_POS,GX_CLR_RGBA,GX_F32,0);
    GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_NRM,GX_CLR_RGB,GX_F32,0);
    GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_TEX0,GX_CLR_RGBA,GX_F32,0);
    GXSetArray(GX_VA_POS, &mDPos[mCurrArr], sizeof(cXyz));
    GXSetArray(GX_VA_NRM, &mNrm[mCurrArr], sizeof(cXyz));
    GXSetArray(GX_VA_TEX0, l_texCoord, sizeof(cXy));
    GXLoadTexObj(getTexObjP(), GX_TEXMAP0);
    GXLoadTexObj(getToonTexObjP(), GX_TEXMAP1);
    GXSetNumChans(1);
    u8 num_tev_stages, lightMask;
    if (mpTevStr->mColorK1.a != 0) {
        num_tev_stages = 3;
        lightMask = 3;
    } else {
        num_tev_stages = 2;
        lightMask = 1;
    }
    if (l_HIO.m05 != 0) {
        GXSetChanCtrl(GX_COLOR0,true,GX_SRC_REG,GX_SRC_REG,lightMask,GX_DF_CLAMP,GX_AF_NONE);
        GXSetNumTexGens(2);
        GXSetTexCoordGen2(GX_TEXCOORD0,GX_TG_MTX2x4,GX_TG_TEX0,GX_IDENTITY,false,GX_PTIDENTITY);
        GXSetTexCoordGen2(GX_TEXCOORD1,GX_TG_SRTG,GX_TG_COLOR0,GX_IDENTITY,false,GX_PTIDENTITY);
        GXSetNumTevStages(num_tev_stages);
        GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP1);
        GXSetTevOrder(GX_TEVSTAGE0,GX_TEXCOORD1,GX_TEXMAP1,GX_COLOR0A0);
        GXSetTevColorIn(GX_TEVSTAGE0,GX_CC_C0,GX_CC_C1,GX_CC_TEXC,GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0,GX_TEV_ADD,GX_TB_ZERO,GX_CS_SCALE_1,true,GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0,GX_CA_ZERO,GX_CA_ZERO,GX_CA_ZERO,GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0,GX_TEV_ADD,GX_TB_ZERO,GX_CS_SCALE_1,true,GX_TEVPREV);
        GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GXSetTevOrder(GX_TEVSTAGE1,GX_TEXCOORD0,GX_TEXMAP0,GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE1,GX_CC_ZERO,GX_CC_TEXC,GX_CC_CPREV,GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE1,GX_TEV_ADD,GX_TB_ZERO,GX_CS_SCALE_1,true,GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE1,GX_CA_ZERO,GX_CA_ZERO,GX_CA_ZERO,GX_CA_TEXA);
        GXSetTevAlphaOp(GX_TEVSTAGE1,GX_TEV_ADD,GX_TB_ZERO,GX_CS_SCALE_1,true,GX_TEVPREV);
        if (num_tev_stages == 3) {
            GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP2);
            GXSetTevOrder(GX_TEVSTAGE2,GX_TEXCOORD1,GX_TEXMAP1,GX_COLOR_NULL);
            GXSetTevColorIn(GX_TEVSTAGE2,GX_CC_ZERO,GX_CC_C2,GX_CC_TEXC,GX_CC_CPREV);
            GXSetTevColorOp(GX_TEVSTAGE2,GX_TEV_ADD,GX_TB_ZERO,GX_CS_SCALE_1,true,GX_TEVPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE2,GX_CA_ZERO,GX_CA_ZERO,GX_CA_ZERO,GX_CA_TEXA);
            GXSetTevAlphaOp(GX_TEVSTAGE2,GX_TEV_ADD,GX_TB_ZERO,GX_CS_SCALE_1,true,GX_TEVPREV);
        }
    } else {
        GXSetChanCtrl(GX_COLOR0,true,GX_SRC_REG,GX_SRC_REG,lightMask,GX_DF_CLAMP,GX_AF_NONE);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0,GX_TG_MTX2x4,GX_TG_TEX0,GX_IDENTITY,false,GX_PTIDENTITY);
        GXSetNumTevStages(num_tev_stages);
        GXSetTevOrder(GX_TEVSTAGE0,GX_TEXCOORD_NULL,GX_TEXMAP_NULL,GX_COLOR0A0);
        GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP1, GX_TEV_SWAP0);
        GXSetTevColorIn(GX_TEVSTAGE0,GX_CC_C0,GX_CC_C1,GX_CC_RASC,GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0,GX_TEV_ADD,GX_TB_ZERO,GX_CS_SCALE_1,true,GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0,GX_CA_ZERO,GX_CA_ZERO,GX_CA_ZERO,GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0,GX_TEV_ADD,GX_TB_ZERO,GX_CS_SCALE_1,true,GX_TEVPREV);
        GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GXSetTevOrder(GX_TEVSTAGE1,GX_TEXCOORD0,GX_TEXMAP0,GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE1,GX_CC_ZERO,GX_CC_CPREV,GX_CC_TEXC,GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE1,GX_TEV_ADD,GX_TB_ZERO,GX_CS_SCALE_1,true,GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE1,GX_CA_ZERO,GX_CA_ZERO,GX_CA_ZERO,GX_CA_TEXA);
        GXSetTevAlphaOp(GX_TEVSTAGE1,GX_TEV_ADD,GX_TB_ZERO,GX_CS_SCALE_1,true,GX_TEVPREV);
        if (num_tev_stages == 3) {
            GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP2, GX_TEV_SWAP0);
            GXSetTevOrder(GX_TEVSTAGE2,GX_TEXCOORD_NULL,GX_TEXMAP_NULL,GX_COLOR_NULL);
            GXSetTevColorIn(GX_TEVSTAGE2,GX_CC_ZERO,GX_CC_C2,GX_CC_RASC,GX_CC_CPREV);
            GXSetTevColorOp(GX_TEVSTAGE2,GX_TEV_ADD,GX_TB_ZERO,GX_CS_SCALE_1,true,GX_TEVPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE2,GX_CA_ZERO,GX_CA_ZERO,GX_CA_ZERO,GX_CA_TEXA);
            GXSetTevAlphaOp(GX_TEVSTAGE2,GX_TEV_ADD,GX_TB_ZERO,GX_CS_SCALE_1,true,GX_TEVPREV);
        }
    }
    GXColorS10 color = mpTevStr->mColorC0;
    GXSetTevColorS10(GX_TEVREG0, color);
    GXColor colorK0 = mpTevStr->mColorK0;
    GXSetTevColor(GX_TEVREG1, colorK0);
    GXColor colorK1 = mpTevStr->mColorK1;
    GXSetTevColor(GX_TEVREG2, colorK1);
    GXCallDisplayList(l_goal_flag_matDL, 32);
    GXLoadPosMtxImm(mMtx, 0);
    GXLoadNrmMtxImm(mMtx, 0);
    GXSetCullMode(GX_CULL_BACK);
    GXCallDisplayList(l_goal_flag_DL, 256);
    GXSetCullMode(GX_CULL_FRONT);
    GXSetArray(GX_VA_NRM, &mBackNrm[mCurrArr], sizeof(cXyz));
    GXCallDisplayList(l_goal_flag_DL, 256);
    J3DShape::sOldVcdVatCmd = 0;
}

/* 00000978-00000A04       .text setBackNrm__16daGFlag_packet_cFv */
void daGFlag_packet_c::setBackNrm() {
    cXyz* nrm_p = mNrm[mCurrArr];
    cXyz* back_nrm_p = mBackNrm[mCurrArr];
    for (int i = 0; i < ARRAY_SSIZE(*mBackNrm); i++) {
        back_nrm_p->setall(0.0f);
        *back_nrm_p -= *nrm_p;

        nrm_p++;
        back_nrm_p++;
    }
} 

/* 00000A04-00000E78       .text setNrmVtx__16daGFlag_packet_cFP4cXyzii */
void daGFlag_packet_c::setNrmVtx(cXyz* param_1, int param_2, int param_3) {
    cXyz* dpos_arr_p = getDPos();
    cXyz temp1;
    cXyz temp2;
    cXyz temp3;
    cXyz temp4;
    cXyz temp5 = dpos_arr_p[(param_3 * 9) + param_2];
    temp4.setall(0.0f);

    if (param_2 != 0) {
        temp1 = dpos_arr_p[(param_3 * 9 + param_2) - 1] - temp5;
        if (param_3 != 0) {
            temp2 = dpos_arr_p[(param_3 - 1) * 9 + param_2] - temp5;
            temp3 = temp2.outprod(temp1);
            temp3 = temp3.normZP();
            temp4 += temp3;
        }
        if (param_3 != 4) {
            temp2 = dpos_arr_p[(param_3 + 1) * 9 + param_2] - temp5;
            temp3 = temp1.outprod(temp2);
            temp3 = temp3.normZP();
            temp4 += temp3;
        }
    } 
    if (param_2 != 8) {
        temp1 = dpos_arr_p[(param_2 + 1) + param_3 * 9] - temp5;
        if (param_3 != 0) {
            temp2 = dpos_arr_p[(param_3 - 1) * 9 + param_2] - temp5;
            temp3 = temp1.outprod(temp2);
            temp3 = temp3.normZP();
            temp4 += temp3;
        }
        if (param_3 != 4) {
            temp2 = dpos_arr_p[(param_3 + 1) * 9 + param_2] - temp5;
            temp3 = temp2.outprod(temp1);
            temp3 = temp3.normZP();
            temp4 += temp3;
        }
    }
    temp4 = temp4.normZC();
    MtxPush();
    mDoMtx_YrotM(*calc_mtx, cM_ssin(m0010 + (param_2 * -0x400 + param_3 * 0x100)) * 512.0f);
    mDoMtx_XrotM(*calc_mtx, cM_scos(m0010 + (param_2 * -0x400 + param_3 * 0x100)) * 512.0f);
    MtxPosition(&temp4, &temp3);
    param_1->set(temp3.normZP());
    MtxPull();
}

/* 00000EB4-00000F80       .text getRacePath__13daGoal_Flag_cFUc */
BOOL daGoal_Flag_c::getRacePath(u8 i_pathIdx) {
    field_0x168C[0] = dPath_GetRoomPath(i_pathIdx, fopAcM_GetRoomNo(this));

    if (!field_0x168C[0]) {
        return FALSE;
    }

    field_0x169C[0] = field_0x168C[0]->m_num;
    u8 next_path_id = field_0x168C[0]->m_nextID;
    int i, j;
    for (j = i = 1; i < ARRAY_SSIZE(field_0x168C) && next_path_id != 0xFFU; i++, j++) {        
        field_0x168C[j] = dPath_GetRoomPath(next_path_id, fopAcM_GetRoomNo(this));
        field_0x169C[j] = field_0x168C[j]->m_num;
        next_path_id = field_0x168C[j]->m_nextID;
    }
    field_0x16AC = i;
    
    return TRUE;
}

/* 00000F80-000010F4       .text RopeMove__13daGoal_Flag_cFv */
void daGoal_Flag_c::RopeMove() {
    // TODO: wtf is going on in this method?
    static const f32 down_offset[] = {
        0.0f, 150.0f, 225.0f, 150.0f
    };
    for (int i = 0; i < field_0x16AC; i++) {
        cXyz* temp = getRopePos(i, field_0x169C[i]);
        temp->set(*getRopePos(i, 0));
        for (u32 j = 0; (s32)j < (s32)(field_0x169C[i] << 2); j++) {
            s32 temp2 = j & 3;
            s32 temp3 = (int)j >> 2;
            if (temp2 != 0) {
                cXyz* temp4 = getRopePos(i, temp3);
                cXyz* temp5 = getRopePos(i, temp3 + 1);
                cXyz& temp6 = getRopePos(i, temp3)[temp2];
                // looks like a LERP
                f32 temp7 = (f32)temp2 * 0.25f;
                f32 temp8 = 1.0f - temp7;
                temp6.set((*temp4 * temp8) + (*temp5 * temp7));
                temp6.y -= down_offset[temp2];
            }
        }
    }
}

/* 000010F4-0000123C       .text CreateBuoyRaces__13daGoal_Flag_cFv */
BOOL daGoal_Flag_c::CreateBuoyRaces() {
    int i;
    dPnt* points_p;
    cXyz* segment;
    for (i = 0; i < field_0x16AC; i++) {
        points_p = points_p = field_0x168C[i]->m_points;
        segment = getRopePos(i, 0);
        for (u32 j = 0; (s32)j < (s32)field_0x169C[i]; j++, points_p++, segment++) {
            cXyz temp2;
            temp2.set(
                points_p->m_position.x,
                points_p->m_position.y,
                points_p->m_position.z
            );
            fopAcM_createChild(
                PROC_Obj_Buoyrace, 
                fopAcM_GetID(this), 
                j | (i << 8), &temp2, 
                fopAcM_GetRoomNo(this), 
                NULL
            );
            segment->set(
                points_p->m_position.x, 
                points_p->m_position.y + 250.0f, 
                points_p->m_position.z
            );
        }
        segment->set(*getRopePos(i, 0));
    }
    return TRUE;
}

/* 0000123C-00001450       .text goal_check__13daGoal_Flag_cFv */
int daGoal_Flag_c::goal_check() {
    int o_ret;
    cXyz temp1 = dComIfGp_getPlayer(0)->current.pos - field_0x1658[0];

    cXyz temp2 = field_0x1658[1] - field_0x1658[0];
    temp2.y = 0.0f;
    temp2 = temp2.normZP();

    temp1.y = 0.0f;

    f32 mag = (field_0x1658[1] - field_0x1658[0]).absXZ();
    f32 dot = VECDotProduct(&temp2, &temp1);
    
    cXyz temp4;
    temp4.x = temp2.z;
    temp4.y = 0.0f;
    temp4.z = -temp2.x;

    f32 dot2 = VECDotProduct(&temp4, &temp1);

    o_ret = 0;
    if (dot > 0.0f && dot < mag) {
        if (field_0x1680 > 0.0f && dot2 <= 0.0f) {
            o_ret = 1;
        } else if (field_0x1680 <= 0.0f && dot2 > 0.0f) {
            o_ret = -1;
        }
    }

    field_0x1680 = dot2;
    return o_ret;
}

/* 00001450-0000183C       .text flag_move__13daGoal_Flag_cFv */
void daGoal_Flag_c::flag_move() {
    /* Nonmatching */
}

/* 0000183C-00001970       .text get_cloth_anim_sub_factor__FP4cXyzP4cXyzP4cXyzf */
void get_cloth_anim_sub_factor(cXyz* param_1, cXyz* param_2, cXyz* param_3, f32 param_4) {
    cXyz temp = *param_2 - *param_1;
    cXyz temp2 = temp.normZP();
    
    f32 mag = temp.abs();

    f32 temp3 = (mag - param_4);
    temp3 *= l_HIO.m3C;

    temp2 *= temp3;
    *param_3 += temp2;
}

/* 00001970-00001CC0       .text get_cloth_anim_factor__13daGoal_Flag_cFP4cXyzP4cXyzP4cXyzii */
cXyz daGoal_Flag_c::get_cloth_anim_factor(cXyz* param_1, cXyz* param_2, cXyz* param_3, int param_4, int param_5) {
    /* Apparent match, .rodata offsets issue */
    int temp = (param_5 * 9) + param_4;
    cXyz temp2 = param_1[temp];
    f32 dot = VECDotProduct(param_3, &param_2[temp]);
    if ((param_5 == 0 || param_5 == 4) && (param_4 == 0 || param_4 == 8)) {
        return cXyz::Zero;
    } else {
        cXyz temp3 = param_2[temp] * dot;
        temp3.y += l_HIO.m38 * ((float)param_5 * 0.25f);
        if (param_4 != 0) {
            get_cloth_anim_sub_factor(&temp2, &param_1[(param_4 - 1) + (param_5 * 9)], &temp3, 250.0f); 
            if (param_5 != 0) {
                get_cloth_anim_sub_factor(&temp2, &param_1[param_4 + (param_5 - 1) * 9], &temp3, 120.0f); 
                get_cloth_anim_sub_factor(&temp2, &param_1[(param_4 - 1) + (param_5 - 1) * 9], &temp3, 277.3085f);     
            }
            if (param_5 != 4) {
                get_cloth_anim_sub_factor(&temp2, &param_1[param_4 + (param_5 + 1) * 9], &temp3, 120.0f); 
                get_cloth_anim_sub_factor(&temp2, &param_1[(param_4 - 1) + (param_5 + 1) * 9], &temp3, 277.3085f);     
            }
            if (param_4 != 8) {
                get_cloth_anim_sub_factor(&temp2, &param_1[(param_4 + 1) + param_5 * 9], &temp3, 250.0f);
                if (param_5 != 0) {
                    get_cloth_anim_sub_factor(&temp2, &param_1[(param_4 + 1) + (param_5 - 1) * 9], &temp3, 277.3085f);
                }
                if (param_5 != 4) {
                    get_cloth_anim_sub_factor(&temp2, &param_1[(param_4 + 1) + (param_5 + 1) * 9], &temp3, 277.3085f);
                }
            }
            return temp3;
        } else {
            get_cloth_anim_sub_factor(&temp2, &param_1[(param_4 + 1) + (param_5 * 9)], &temp3, 250.0f);
            if (param_5 != 0) {
                get_cloth_anim_sub_factor(&temp2, &param_1[param_4 + (param_5 - 1) * 9], &temp3, 120.0f);
                get_cloth_anim_sub_factor(&temp2, &param_1[(param_4 + 1) + (param_5 - 1) * 9], &temp3, 277.3085f);
            }
            if (param_5 != 4) {
                get_cloth_anim_sub_factor(&temp2, &param_1[param_4 + (param_5 + 1) * 9], &temp3, 120.0f);
                get_cloth_anim_sub_factor(&temp2, &param_1[(param_4 + 1) + (param_5 + 1) * 9], &temp3, 277.3085f);
            }
            return temp3;
        }
    }
}

/* 00001CC0-00001CE0       .text checkCreateHeap__FP10fopAc_ac_c */
static BOOL checkCreateHeap(fopAc_ac_c* i_actor) {
    return ((daGoal_Flag_c*)i_actor)->CreateHeap();
}

/* 00001CE0-00001D74       .text CreateHeap__13daGoal_Flag_cFv */
BOOL daGoal_Flag_c::CreateHeap() {
    for (int i = 0; i < field_0x16AC; i++) {
        if (!field_0x16B0[i].init(1, (field_0x169C[i] << 2) + 1, 0)) {
            return FALSE;
        }
    }
    return TRUE;
}

/* 00001D74-00001DB4       .text getDemoAction__13daGoal_Flag_cFi */
int daGoal_Flag_c::getDemoAction(int param_1) {
    /* Apparent match, .data offsets issue */
    static char* ActionNames[] = { 
        "00_dummy",
        "01_dummy",
        "02_dummy",
        "03_dummy",
        "04_dummy" 
    };
    return dComIfGp_evmng_getMyActIdx(param_1, ActionNames, 5, FALSE, 0);
}

/* 00001DB4-00001F60       .text RaceStart__13daGoal_Flag_cFv */
BOOL daGoal_Flag_c::RaceStart() {
    /* Apparent match, .rodata offsets issue */
    int staff_idx = dComIfGp_evmng_getMyStaffId("Gflag");
    int action_idx = getDemoAction(staff_idx);

    if (field_0x1688 == 0) {
        if (staff_idx != -1 && action_idx == 0) {
            dComIfGp_evmng_cutEnd(staff_idx);
        } else {
            return TRUE;
        }         
        field_0x1688++;
    } else {
        dTimer_c* timer_p = (dTimer_c*) fopMsgM_SearchByID(field_0x1674);
        dMinigame_Starter_c* mgame_start_p = (dMinigame_Starter_c*) fopMsgM_SearchByID(field_0x1678);

        if (action_idx == 1 && mgame_start_p) {
            if (!mgame_start_p->field_0x111) {
                mgame_start_p->field_0x111 = true;
            }
            dComIfGp_evmng_cutEnd(staff_idx);
        }

        if (timer_p && mgame_start_p && mgame_start_p->startCheck()) {
            dComIfGp_evmng_cutEnd(staff_idx);
            timer_p->start(7);
            if (field_0x1688 == 1) {
                mDoAud_bgmStart(JA_BGM_SEA_GAME);
                field_0x1688++;
            }
        }

        bool end_chk = dComIfGp_evmng_endCheck("race_start_cam");
        if (end_chk) {
            setAction(&daGoal_Flag_c::TimerExecute);
            field_0x1688 = 0;
        }
    }
    return TRUE;
}

/* 00001F60-00002290       .text TimerExecute__13daGoal_Flag_cFv */
BOOL daGoal_Flag_c::TimerExecute() {
    /* Nonmatching */
    field_0x1720 = &daGoal_Flag_c::RaceEnd;
    static char* event_name_tbl[] = {
        "race_goal_cam",
        "race_fail_cam",
    };
}

/* 00002290-000023E0       .text RaceEnd__13daGoal_Flag_cFv */
BOOL daGoal_Flag_c::RaceEnd() {
    /* Apparent match, .data and .rodata offsets */
    static char* event_name_tbl[] = {
        "race_goal_cam",
        "race_fail_cam",
    };

    field_0x1686++;
    
    dTimer_c* timer_p;
    if (
        field_0x1674 != -1 && 
        (timer_p = (dTimer_c*)fopMsgM_SearchByID(field_0x1674)) &&
        timer_p->deleteCheck()
    ) {
        fopMsgM_Delete(timer_p);
        field_0x1674 = -1;
    }

    int staff_idx = dComIfGp_evmng_getMyStaffId("Gflag");
    
    if (staff_idx != -1) {
        dComIfGp_evmng_cutEnd(staff_idx);
    } 

    bool end_chk = dComIfGp_evmng_endCheck(event_name_tbl[field_0x1684 != 3 ? 1 : 0]);

    
    if (end_chk || ( (int)field_0x1686 > (int)l_HIO.m20 && 
        (CPad_CHECK_TRIG_A(0) || CPad_CHECK_TRIG_B(0) || CPad_CHECK_TRIG_START(0)) )) {
        dComIfGp_setNextStage("sea", 1, 0x30);
    }

    return true;
}

/* 000023E0-00002400       .text daGoal_FlagCreate__FPv */
static cPhs_State daGoal_FlagCreate(void* i_this) {
    return ((daGoal_Flag_c*)i_this)->_create();
}

/* 00002400-00002968       .text _create__13daGoal_Flag_cFv */
cPhs_State daGoal_Flag_c::_create() {
    /* Apparent match, .data and .rodata offsets issue */
    cPhs_State rt;
    u8 temp;
    dPath* path_p;

    fopAcM_SetupActor(this, daGoal_Flag_c);

    u32 prm = fopAcM_GetParam(this) & 0xFF;
    rt = dComIfG_resLoad(&field_0x1618, "Cloth");

    if (rt != cPhs_COMPLEATE_e) {
        return rt;
    }

    if (prm == 0 || prm == 0xFF) {
        temp = 0;
        rt = dComIfG_resLoad(&field_0x1620, "Gflag");
        scale.set(1.05f, 1.0f, 1.0f);
    } else {
        temp = 1;
        rt = dComIfG_resLoad(&field_0x1620, "Tgflag");
        scale.set(0.98f, 1.0f, 1.0f);
    }

    if (rt != cPhs_COMPLEATE_e) {
        return rt;
    }

    prm = (fopAcM_GetParam(this) >> 0x10) & 0xFF;
    if (prm != 0xFF) {
        path_p = dPath_GetRoomPath(prm, fopAcM_GetRoomNo(this));
        if (path_p) {
            BOOL path = getRacePath(path_p->m_nextID);
            if (path != FALSE) {
                if (fopAcM_entrySolidHeap(this, checkCreateHeap, 0x10000)) {
                    CreateBuoyRaces();
                } else {
                    return cPhs_ERROR_e;
                }
            }
        } else {
            return cPhs_ERROR_e;
        }
    } else {
        return cPhs_ERROR_e;
    }

    cXyz* pos_arr_p = field_0x0290.getPos();
    for (int i = 0; i < 45; i++, pos_arr_p++) {
        pos_arr_p->set(l_pos[i]);
    }

    field_0x0290.setTexObj(temp);
    field_0x0290.setToonTexObj();

    path_p = dPath_GetRoomPath((fopAcM_GetParam(this) >> 0x10) & 0xFF, fopAcM_GetRoomNo(this));

    if (path_p) {
        field_0x1658[0].set(path_p->m_points[0].m_position);
        field_0x1658[1].set(path_p->m_points[1].m_position);
    }
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    mDoMtx_stack_c::scaleM(scale);
    MTXCopy(mDoMtx_stack_c::get(), field_0x1628);
    if (
        strcmp(dComIfGp_getStartStageName(), "Ocean") == 0 &&
        dComIfGp_getStartStagePoint() == 1
    ) {
        u16 temp2 = l_HIO.m18;
        u16 reg = (u16)dComIfGs_getEventReg(dSv_event_flag_c::UNK_AAFF) * 10;
        temp2 -= reg;
        field_0x1674 = fopMsgM_Timer_create(PROC_TIMER, 2, temp2, 3, 0, 221.0f, 439.0f, 32.0f, 419.0f, NULL);
        
        // TODO: Fakematch, debug map mentions a call to an inline func named
        // fopMsgM_MiniGameStarter_create, but the parameters do not match up one-to-one, 
        // so it's not entirely obvious how the call to fopMsgM_create is constructed.
        u32 temp3 = 0;
        temp3 |= 0x2000000;
        field_0x1678 = fopMsgM_create(PROC_MINIGAME_STARTER, NULL, NULL, &temp3, &temp3, NULL);

        dComIfGp_startMiniGame(1);
        dComIfGp_setMiniGameRupee(0);

        setAction(&daGoal_Flag_c::RaceStart);     
        field_0x1688 = 0;
    }

    cXyz temp5 = dComIfGp_getPlayer(0)->current.pos - field_0x1658[0];

    cXyz temp6 = field_0x1658[1] - field_0x1658[0];
    temp6.y = 0.0f;
    temp6 = temp6.normZP();

    cXyz temp7;
    temp7.x = temp6.z;
    temp7.y = 0.0f;
    temp7.z = -temp6.x;

    field_0x1680 = VECDotProduct(&temp7, &temp5);
    field_0x1684 = 0;

    for (int i = 0; i < 20; i++) {
        flag_move();
    }

    return cPhs_COMPLEATE_e;
}

bool daGoal_Flag_c::_delete() {
    u8 prm = fopAcM_GetParam(this) & 0xFF;
    dComIfG_resDelete(&field_0x1618, arcname);
    dComIfG_resDelete(&field_0x1620, sub_arcname_tbl[prm]);

    if (dComIfGp_getMiniGameType() == 1) {
        if (dComIfGp_getMiniGameResult() == 1) {
            daNpc_Sarace_c::ship_race_result = 2;
            daNpc_Sarace_c::ship_race_rupee = dComIfGp_getMiniGameRupee();
        } else if (dComIfGp_getMiniGameResult() == 2) {
            daNpc_Sarace_c::ship_race_result = 1;
            daNpc_Sarace_c::ship_race_rupee = dComIfGp_getMiniGameRupee();
        }
        dComIfGp_endMiniGame(1);
    }

    return true;
}

/* 000029CC-00002AAC       .text daGoal_FlagDelete__FPv */
static BOOL daGoal_FlagDelete(void* i_this) {
    return ((daGoal_Flag_c*)i_this)->_delete();
}

bool daGoal_Flag_c::_execute() {
    if (field_0x1720 != NULL) {
        (this->*field_0x1720)();
    }
    flag_move();
    RopeMove();
    return true;
} 

/* 00002AAC-00002B14       .text daGoal_FlagExecute__FPv */
static BOOL daGoal_FlagExecute(void* i_this) {
    return ((daGoal_Flag_c*)i_this)->_execute();
}

bool daGoal_Flag_c::_draw() {
    /* Apparent match, .rodata offsets issue */
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);

    MtxTrans(current.pos.x, current.pos.y, current.pos.z, false);
    mDoMtx_YrotM(*calc_mtx, current.angle.y);
    MtxScale(scale.x, scale.y, scale.z, true);

    Mtx* mtx_p = field_0x0290.getMtx();
    MTXConcat(j3dSys.getViewMtx(), *calc_mtx, *mtx_p);

    field_0x0290.setTevStr(&tevStr);
    j3dSys.getDrawBuffer(0)->entryImm(&field_0x0290, 0);

    for (int i = 0; i < field_0x16AC; i++) {
        GXColor color;
        color.r = l_HIO.m24;
        color.g = l_HIO.m28;
        color.b = l_HIO.m2C;
        color.a = 0xFF;
        field_0x16B0[i].update((field_0x169C[i] << 2) + 1, 20.0f, color, 0, &tevStr);
        dComIfGd_set3DlineMat(&field_0x16B0[i]);
    }

    return true;
}

/* 00002B14-00002CA4       .text daGoal_FlagDraw__FPv */
static BOOL daGoal_FlagDraw(void* i_this) {
    return ((daGoal_Flag_c*)i_this)->_draw();
}

/* 00002CA4-00002CAC       .text daGoal_FlagIsDelete__FPv */
static BOOL daGoal_FlagIsDelete(void*) {
    return TRUE;
}

static actor_method_class daGoal_FlagMethodTable = {
    (process_method_func)daGoal_FlagCreate,
    (process_method_func)daGoal_FlagDelete,
    (process_method_func)daGoal_FlagExecute,
    (process_method_func)daGoal_FlagIsDelete,
    (process_method_func)daGoal_FlagDraw,
};

actor_process_profile_definition g_profile_Goal_Flag = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Goal_Flag,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daGoal_Flag_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Goal_Flag,
    /* Actor SubMtd */ &daGoal_FlagMethodTable,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
