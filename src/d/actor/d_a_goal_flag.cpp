/**
 * d_a_goal_flag.cpp
 * Object - Big red finish line flag (Boating Course, Flight Control Platform)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_goal_flag.h"
#include "d/actor/d_a_npc_sarace.h"
#include "d/d_kankyo_wether.h"
#include "d/d_minigame_starter.h"
#if VERSION == VERSION_DEMO
#include "d/d_s_play.h"
#endif
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
    GXBool mipmap_cnt_over_one = GXBool(tex_info_p->mipmapCount > 1);
    GXInitTexObj(
        &mTexObj, 
        (u8*)tex_info_p + tex_info_p->imageOffset, 
        tex_info_p->width, 
        tex_info_p->height, 
        GXTexFmt(tex_info_p->format), 
        GXTexWrapMode(tex_info_p->wrapS), 
        GXTexWrapMode(tex_info_p->wrapT),
        mipmap_cnt_over_one
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
    GXBool mipmap_cnt_over_one = GXBool(tex_info_p->mipmapCount > 1);
    GXInitTexObj(
        &mToonTexObj, 
        (u8*)tex_info_p + tex_info_p->imageOffset, 
        tex_info_p->width, 
        tex_info_p->height, 
        GXTexFmt(tex_info_p->format), 
        GXTexWrapMode(tex_info_p->wrapS), 
        GXTexWrapMode(tex_info_p->wrapT),
        mipmap_cnt_over_one
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
#if VERSION > VERSION_JPN
    GXSetNumIndStages(0);
#endif
    dKy_GxFog_tevstr_set(mpTevStr);
    dKy_setLight_mine(mpTevStr);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxDesc(GX_VA_NRM, GX_INDEX8);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGBA, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_CLR_RGB, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_CLR_RGBA, GX_F32, 0);
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
    if (l_HIO.mDrawCelShaded) {
        GXSetChanCtrl(GX_COLOR0, true, GX_SRC_REG, GX_SRC_REG, lightMask, GX_DF_CLAMP, GX_AF_NONE);
        GXSetNumTexGens(2);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, false, GX_PTIDENTITY);
        GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_SRTG, GX_TG_COLOR0, GX_IDENTITY, false, GX_PTIDENTITY);
        GXSetNumTevStages(num_tev_stages);
        GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C0, GX_CC_C1, GX_CC_TEXC, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, true, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, true, GX_TEVPREV);
        GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_CPREV, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, true, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, true, GX_TEVPREV);
        if (num_tev_stages == 3) {
            GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP2);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_C2, GX_CC_TEXC, GX_CC_CPREV);
            GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, true, GX_TEVPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, true, GX_TEVPREV);
        }
    } else {
        GXSetChanCtrl(GX_COLOR0, true, GX_SRC_REG, GX_SRC_REG, lightMask, GX_DF_CLAMP, GX_AF_NONE);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, false, GX_PTIDENTITY);
        GXSetNumTevStages(num_tev_stages);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP1, GX_TEV_SWAP0);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C0, GX_CC_C1, GX_CC_RASC, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, true, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, true, GX_TEVPREV);
        GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, true, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, true, GX_TEVPREV);
        if (num_tev_stages == 3) {
            GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP2, GX_TEV_SWAP0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_C2, GX_CC_RASC, GX_CC_CPREV);
            GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, true, GX_TEVPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, true, GX_TEVPREV);
        }
    }
    GXSetTevColorS10(GX_TEVREG0, mpTevStr->mColorC0);
    GXSetTevColor(GX_TEVREG1, mpTevStr->mColorK0);
    GXSetTevColor(GX_TEVREG2, mpTevStr->mColorK1);
    GXCallDisplayList(l_goal_flag_matDL, 32);
    GXLoadPosMtxImm(mMtx, 0);
    GXLoadNrmMtxImm(mMtx, 0);
    GXSetCullMode(GX_CULL_BACK);
    GXCallDisplayList(l_goal_flag_DL, 256);
    GXSetCullMode(GX_CULL_FRONT);
    GXSetArray(GX_VA_NRM, &mBackNrm[mCurrArr], sizeof(cXyz));
    GXCallDisplayList(l_goal_flag_DL, 256);
#if VERSION > VERSION_JPN
    J3DShape::sOldVcdVatCmd = 0;
#endif
}

/* 00000978-00000A04       .text setBackNrm__16daGFlag_packet_cFv */
void daGFlag_packet_c::setBackNrm() {
    cXyz* nrm_arr = mNrm[mCurrArr];
    cXyz* back_nrm_arr = mBackNrm[mCurrArr];
    for (int i = 0; i < ARRAY_SSIZE(*mBackNrm); i++) {
        back_nrm_arr->setall(0.0f);
        *back_nrm_arr -= *nrm_arr;

        nrm_arr++;
        back_nrm_arr++;
    }
} 

/* 00000A04-00000E78       .text setNrmVtx__16daGFlag_packet_cFP4cXyzii */
void daGFlag_packet_c::setNrmVtx(cXyz* o_nrm, int i_col, int i_row) {
    cXyz* dpos_arr = getDPos();
    cXyz horizontal_edge;
    cXyz vertical_edge;
    cXyz tri_normal;
    cXyz averaged_normal;
    cXyz center_vertex = dpos_arr[(i_row * 9) + i_col];
    averaged_normal.setall(0.0f);

    if (i_col != 0) {
        horizontal_edge = dpos_arr[(i_row * 9) + (i_col - 1)] - center_vertex;
        if (i_row != 0) {
            vertical_edge = dpos_arr[(i_row - 1) * 9 + i_col] - center_vertex;
            tri_normal = vertical_edge.outprod(horizontal_edge);
            tri_normal = tri_normal.normZP();
            averaged_normal += tri_normal;
        }
        if (i_row != 4) {
            vertical_edge = dpos_arr[(i_row + 1) * 9 + i_col] - center_vertex;
            tri_normal = horizontal_edge.outprod(vertical_edge);
            tri_normal = tri_normal.normZP();
            averaged_normal += tri_normal;
        }
    } 
    if (i_col != 8) {
        horizontal_edge = dpos_arr[(i_col + 1) + i_row * 9] - center_vertex;
        if (i_row != 0) {
            vertical_edge = dpos_arr[(i_row - 1) * 9 + i_col] - center_vertex;
            tri_normal = horizontal_edge.outprod(vertical_edge);
            tri_normal = tri_normal.normZP();
            averaged_normal += tri_normal;
        }
        if (i_row != 4) {
            vertical_edge = dpos_arr[(i_row + 1) * 9 + i_col] - center_vertex;
            tri_normal = vertical_edge.outprod(horizontal_edge);
            tri_normal = tri_normal.normZP();
            averaged_normal += tri_normal;
        }
    }
    averaged_normal = averaged_normal.normZC();

    MtxPush();
    cMtx_YrotM(*calc_mtx, 
        DEMO_SELECT(REG10_S(2) + 0x200, 512.0f) *
        cM_ssin(
            mNormalFlutterPhase + 
            (i_col * (DEMO_SELECT(REG10_S(3), 0) + -0x400) + 
            i_row * (DEMO_SELECT(REG10_S(4), 0) + 0x100))
        )
    );
    cMtx_XrotM(*calc_mtx, 
        DEMO_SELECT(REG10_S(5) + 0x200, 512.0f) * 
        cM_scos(
            mNormalFlutterPhase + 
            (i_col * (DEMO_SELECT(REG10_S(6), 0) + -0x400) + 
            i_row * (DEMO_SELECT(REG10_S(7), 0) + 0x100))
        )
    );
    MtxPosition(&averaged_normal, &tri_normal);
    o_nrm->set(tri_normal.normZP());
    MtxPull();
}

/* 00000EB4-00000F80       .text getRacePath__13daGoal_Flag_cFUc */
BOOL daGoal_Flag_c::getRacePath(u8 i_pathId) {
    int i = 0;
    mpRopePaths[i] = dPath_GetRoomPath(i_pathId, fopAcM_GetRoomNo(this));
    if (!mpRopePaths[i]) {
        return FALSE;
    }
 
    mNumRopeBuoys[i] = mpRopePaths[i]->m_num;
    u8 next_path_id = mpRopePaths[i]->m_nextID;
    for (i++; i < ARRAY_SSIZE(mpRopePaths) && next_path_id != 0xFFU; i++) {        
        mpRopePaths[i] = dPath_GetRoomPath(next_path_id, fopAcM_GetRoomNo(this));
        mNumRopeBuoys[i] = mpRopePaths[i]->m_num;
        next_path_id = mpRopePaths[i]->m_nextID;
    }
    mNumRopes = i;

    return TRUE;
}

/* 00000F80-000010F4       .text RopeMove__13daGoal_Flag_cFv */
void daGoal_Flag_c::RopeMove() {
    static const f32 down_offset[] = {
        0.0f, 150.0f, 225.0f, 150.0f
    };
    for (int i = 0; i < mNumRopes; i++) {
        cXyz* rope_start = getRopePos(i, 0);
        cXyz* rope_end = getRopePos(i, mNumRopeBuoys[i]);
        rope_end->set(*rope_start);
        for (int j = 0; j < (int)(mNumRopeBuoys[i] << 2); j++) {
            int interpolated_point = j & 3;
            int anchor_point = j >> 2;
            if (interpolated_point != 0) {
                cXyz* A = getRopePos(i, anchor_point);
                cXyz* B = getRopePos(i, anchor_point + 1);
                cXyz& C = getRopePos(i, anchor_point)[interpolated_point];
                f32 t = (f32)interpolated_point * 0.25f;
                f32 one_minus_t = 1.0f - t;
                C.set((*A) * one_minus_t + (*B) * t);
                C.y -= down_offset[interpolated_point];
            }
        }
    }
}

/* 000010F4-0000123C       .text CreateBuoyRaces__13daGoal_Flag_cFv */
BOOL daGoal_Flag_c::CreateBuoyRaces() {
    int i;
    dPnt* rope_points_p;
    cXyz* segment;
    for (i = 0; i < mNumRopes; i++) {
        rope_points_p = mpRopePaths[i]->m_points;
        segment = getRopePos(i, 0);
        for (int j = 0; j < mNumRopeBuoys[i]; j++, rope_points_p++, segment++) {
            cXyz rope_point_pos;
            rope_point_pos.set(
                rope_points_p->m_position.x,
                rope_points_p->m_position.y,
                rope_points_p->m_position.z
            );
            fopAcM_createChild(
                PROC_Obj_Buoyrace, 
                fopAcM_GetID(this), 
                j | (i << 8), &rope_point_pos, 
                fopAcM_GetRoomNo(this), 
                NULL
            );
            segment->set(
                rope_points_p->m_position.x, 
                rope_points_p->m_position.y + 250.0f, 
                rope_points_p->m_position.z
            );
        }
        segment->set(*getRopePos(i, 0));
    }
    return TRUE;
}

/* 0000123C-00001450       .text goal_check__13daGoal_Flag_cFv */
int daGoal_Flag_c::goal_check() {
    int o_result;
    cXyz player_from_line_start = dComIfGp_getPlayer(0)->current.pos - mGoalFlagPolePos[0];

    cXyz finish_line_dir = mGoalFlagPolePos[1] - mGoalFlagPolePos[0];

    finish_line_dir.y = 0.0f;
    finish_line_dir = finish_line_dir.normZP();

    player_from_line_start.y = 0.0f;

    f32 finish_line_len = (mGoalFlagPolePos[1] - mGoalFlagPolePos[0]).absXZ();
    f32 player_along_line = finish_line_dir.getDotProduct(player_from_line_start);
    
    cXyz finish_line_normal;
    finish_line_normal.set(finish_line_dir.z, 0.0f, -finish_line_dir.x);

    // Positive values mean the player is behind the finish line
    // Negative values mean the player is in front of it
    f32 player_finish_side = finish_line_normal.getDotProduct(player_from_line_start);

    o_result = 0; // Not yet crossed the finish line
    if (player_along_line > 0.0f && player_along_line < finish_line_len) {
        if (mPrevPlayerLineSide > 0.0f && player_finish_side <= 0.0f) {
            o_result = 1; // Crossed the finish line normally
        } else if (mPrevPlayerLineSide <= 0.0f && player_finish_side > 0.0f) {
            o_result = -1; // Crossed the finish line the wrong way
        }
    }

    mPrevPlayerLineSide = player_finish_side;
    return o_result;
}

/* 00001450-0000183C       .text flag_move__13daGoal_Flag_cFv */
void daGoal_Flag_c::flag_move() {
    cXyz cloth_anim_factor;
    cXyz* prev_pos_arr = mFlagPacket.getPos();
    cXyz* prev_nrm_arr = mFlagPacket.getNrm();
    mFlagPacket.changeCurrentPos();
    cXyz* curr_pos_arr = mFlagPacket.getPos();
    cXyz* velocity_arr = mFlagPacket.getOffsetVec();

    mWindScalePhase += l_HIO.mWindScalePhaseInc;
    mFlagPacket.mNormalFlutterPhase += l_HIO.mNormalFlutterPhaseInc;
    mFlagPacket.mFlagWavePhase += l_HIO.mFlagWavePhaseInc;

    f32 scale_blend_factor = 0.5f + (cM_ssin(mWindScalePhase) * 0.5f);
    f32 wind_vector_scale = l_HIO.mWindScale1 * scale_blend_factor + (l_HIO.mWindScale2 * (1.0f - scale_blend_factor));

    cMtx_YrotS(*calc_mtx, -current.angle.y);
    cXyz wind_vector;
    MtxPosition(dKyw_get_wind_vec(), &wind_vector);
    f32 mag = wind_vector.getSquareMag();

    if (cM3d_IsZero(mag)) {
        wind_vector = cXyz::Zero;
    } else {
        wind_vector = wind_vector.norm();
        wind_vector.x *= DEMO_SELECT(REG10_F(24) + 0.2f, 0.2f);
        wind_vector *= wind_vector_scale;
    }

    int index;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 5; j++) {
            index = i + j * 9;
            curr_pos_arr[index].set(prev_pos_arr[index]);
            cloth_anim_factor = get_cloth_anim_factor(
                prev_pos_arr, 
                prev_nrm_arr, 
                &wind_vector, 
                i, 
                j
            );
            velocity_arr[index] += cloth_anim_factor;
            velocity_arr[index] *= DEMO_SELECT(0.85f - REG10_F(25), 0.85f);
            curr_pos_arr[index] += velocity_arr[index];
        }
    }

    cXyz* curr_dpos_arr = mFlagPacket.getDPos();
    for (int k = 0; k < 9; k++) {
        for (int l = 0; l < 5; l++) {
            index = k + l * 9;
            curr_dpos_arr[index] = curr_pos_arr[index];
            f32 center_to_edge_falloff = ((20.25f - std::abs(4.5f - (f32)k) * std::abs(4.5f - (f32)k)) / 20.25f);
            curr_dpos_arr[index].z += ( 
                DEMO_SELECT(40.0f + REG10_F(10), 40.0f) * 
                center_to_edge_falloff * 
                cM_ssin(k * 0x4000 + l * 0x2000 + mFlagPacket.mFlagWavePhase)
            );
        }    
    }

    cXyz* curr_nrm_p = mFlagPacket.getNrm();
    for (int m = 0; m < 5; m++) {
        for (int n = 0; n < 9; n++) {
            mFlagPacket.setNrmVtx(curr_nrm_p, n, m);
            curr_nrm_p++;
        }
    }

    mFlagPacket.setBackNrm();
    DCStoreRangeNoSync(mFlagPacket.getDPos(), sizeof(mFlagPacket.mDPos[0]));
#if VERSION > VERSION_JPN
    DCStoreRangeNoSync(mFlagPacket.getNrm(), sizeof(mFlagPacket.mNrm[0]));
    DCStoreRangeNoSync(mFlagPacket.getBackNrm(), sizeof(mFlagPacket.mBackNrm[0]));
#endif
}

static BOOL checkCreateHeap(fopAc_ac_c*);

/* 00002400-00002968       .text _create__13daGoal_Flag_cFv */
cPhs_State daGoal_Flag_c::_create() {
    cPhs_State cloth_resload_state;
    cPhs_State flag_resload_state;
    u8 arc_index;
    dPath* path_p;

    fopAcM_ct(this, daGoal_Flag_c);

    u8 prm = fopAcM_GetParam(this) & 0xFF;
    cloth_resload_state = dComIfG_resLoad(&mClothPhs, "Cloth");

#if VERSION > VERSION_DEMO
    if (cloth_resload_state != cPhs_COMPLEATE_e) {
        return cloth_resload_state;
    }
#endif

    if (prm == 0 || prm == 0xFF) {
        arc_index = 0;
        flag_resload_state = dComIfG_resLoad(&mFlagPhs, "Gflag");
        scale.set(1.05f, 1.0f, 1.0f);
    } else {
        arc_index = 1;
        flag_resload_state = dComIfG_resLoad(&mFlagPhs, "Tgflag");
        scale.set(0.98f, 1.0f, 1.0f);
    }


#if VERSION > VERSION_DEMO
    if (flag_resload_state != cPhs_COMPLEATE_e) {
        return flag_resload_state;
    }
#else
    if (cloth_resload_state == cPhs_ERROR_e || flag_resload_state == cPhs_ERROR_e) {
        return cPhs_ERROR_e;
    } 
    if (cloth_resload_state != cPhs_COMPLEATE_e) { 
        return cloth_resload_state;
    }
    if (flag_resload_state != cPhs_COMPLEATE_e) {
        return flag_resload_state;
    }

    int dummy_int = 4;
    if (dummy_int == 4) 
#endif
    {
        u8 path_id = fopAcM_GetParam(this) >> 16u;
        if (path_id != 0xFF) {
            path_p = dPath_GetRoomPath(path_id, fopAcM_GetRoomNo(this));
            if (path_p) {
                u8 path_id = path_p->m_nextID;
                if (getRacePath(path_id)) {
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

        cXyz* pos_arr = mFlagPacket.getPos();
        for (int i = 0; i < 45; i++, pos_arr++) {
            pos_arr->set(l_pos[i]);
        }

        mFlagPacket.setTexObj(arc_index);
        mFlagPacket.setToonTexObj();

        path_id = fopAcM_GetParam(this) >> 16u;
        path_p = dPath_GetRoomPath(path_id, fopAcM_GetRoomNo(this));

        if (path_p) {
            mGoalFlagPolePos[0].set(path_p->m_points[0].m_position);
            mGoalFlagPolePos[1].set(path_p->m_points[1].m_position);
        }

        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::YrotM(shape_angle.y);
        mDoMtx_stack_c::scaleM(scale);
        MTXCopy(mDoMtx_stack_c::get(), mMtx);
        if (
            strcmp(dComIfGp_getStartStageName(), "Ocean") == 0 &&
            dComIfGp_getStartStagePoint() == 1
        ) {
            u16 time_limit = l_HIO.mTimeLimit;
            u16 time_limit_modifier = (u16)dComIfGs_getEventReg(dSv_event_flag_c::UNK_AAFF) * 10;
            time_limit -= time_limit_modifier;
            mTimerProcID = fopMsgM_Timer_create(
                PROC_TIMER, 
                2, 
                time_limit, 
                3, 
                0, 
                221.0f, 
                439.0f, 
                32.0f, 
                419.0f, 
                NULL
            );
            
            mMgameStartProcID = fopMsgM_MiniGameStarter_create(
                PROC_MINIGAME_STARTER, 
                0, 
                0x200, 
                NULL
            );

            dComIfGp_startMiniGame(1);
            dComIfGp_setMiniGameRupee(0);

            setAction(&daGoal_Flag_c::RaceStart);     
            mRaceStartState = 0;
        }

        cXyz initial_player_from_start = dComIfGp_getPlayer(0)->current.pos - mGoalFlagPolePos[0];

        cXyz finish_line_dir = mGoalFlagPolePos[1] - mGoalFlagPolePos[0];
        finish_line_dir.y = 0.0f;
        finish_line_dir = finish_line_dir.normZP();

        cXyz finish_line_normal;
        finish_line_normal.set(finish_line_dir.z, 0.0f, -finish_line_dir.x);

        mPrevPlayerLineSide = finish_line_normal.getDotProduct(initial_player_from_start);
        mRaceEndState = 0;

        for (int i = 0; i < 20; i++) {
            flag_move();
        }
    }

    return cPhs_COMPLEATE_e;
}


/* 0000183C-00001970       .text get_cloth_anim_sub_factor__FP4cXyzP4cXyzP4cXyzf */
void get_cloth_anim_sub_factor(cXyz* i_posP, cXyz* i_otherP, cXyz* o_dst, f32 i_idealDist) {
    cXyz vec_to_neighbor = *i_otherP - *i_posP;
    cXyz correction_dir = vec_to_neighbor.normZP();
    
    f32 diff_from_ideal = (vec_to_neighbor.abs() - i_idealDist);
    diff_from_ideal *= l_HIO.mClothStiffness;

    correction_dir *= diff_from_ideal;
    *o_dst += correction_dir;
}

/* 00001970-00001CC0       .text get_cloth_anim_factor__13daGoal_Flag_cFP4cXyzP4cXyzP4cXyzii */
cXyz daGoal_Flag_c::get_cloth_anim_factor(cXyz* i_posArr, cXyz* i_nrmArr, cXyz* i_windVecP, int i_col, int i_row) {
    int index = (i_row * 9) + i_col;
    cXyz pos = i_posArr[index];
    f32 dot = i_windVecP->getDotProduct(i_nrmArr[index]);
    if ((i_row == 0 || i_row == 4) && (i_col == 0 || i_col == 8)) {
        return cXyz::Zero;
    } else {
        cXyz anim_factor = i_nrmArr[index] * dot;
        anim_factor.y += l_HIO.mFlagSagFactor * ((float)i_row * 0.25f);
        if (i_col != 0) {
            get_cloth_anim_sub_factor(
                &pos, &i_posArr[(i_col - 1) + (i_row * 9)], 
                &anim_factor, 250.0f); 
            if (i_row != 0) {
                get_cloth_anim_sub_factor(
                    &pos, &i_posArr[i_col + (i_row - 1) * 9], 
                    &anim_factor, 120.0f); 
                get_cloth_anim_sub_factor(
                    &pos, &i_posArr[(i_col - 1) + (i_row - 1) * 9], 
                    &anim_factor, 277.3085f);     
            }
            if (i_row != 4) {
                get_cloth_anim_sub_factor(
                    &pos, &i_posArr[i_col + (i_row + 1) * 9], 
                    &anim_factor, 120.0f); 
                get_cloth_anim_sub_factor(
                    &pos, &i_posArr[(i_col - 1) + (i_row + 1) * 9], 
                    &anim_factor, 277.3085f);     
            }
            if (i_col != 8) {
                get_cloth_anim_sub_factor(
                    &pos, &i_posArr[(i_col + 1) + i_row * 9], 
                    &anim_factor, 250.0f);
                if (i_row != 0) {
                    get_cloth_anim_sub_factor(
                        &pos, &i_posArr[(i_col + 1) + (i_row - 1) * 9], 
                        &anim_factor, 277.3085f);
                }
                if (i_row != 4) {
                    get_cloth_anim_sub_factor(
                        &pos, &i_posArr[(i_col + 1) + (i_row + 1) * 9], 
                        &anim_factor, 277.3085f);
                }
            }
            return anim_factor;
        } else {
            get_cloth_anim_sub_factor(
                &pos, &i_posArr[(i_col + 1) + (i_row * 9)], 
                &anim_factor, 250.0f);
            if (i_row != 0) {
                get_cloth_anim_sub_factor(
                    &pos, &i_posArr[i_col + (i_row - 1) * 9], 
                    &anim_factor, 120.0f);
                get_cloth_anim_sub_factor(
                    &pos, &i_posArr[(i_col + 1) + (i_row - 1) * 9], 
                    &anim_factor, 277.3085f);
            }
            if (i_row != 4) {
                get_cloth_anim_sub_factor(
                    &pos, &i_posArr[i_col + (i_row + 1) * 9], 
                    &anim_factor, 120.0f);
                get_cloth_anim_sub_factor(
                    &pos, &i_posArr[(i_col + 1) + (i_row + 1) * 9], 
                    &anim_factor, 277.3085f);
            }
            return anim_factor;
        }
    }
}

/* 00001CC0-00001CE0       .text checkCreateHeap__FP10fopAc_ac_c */
static BOOL checkCreateHeap(fopAc_ac_c* i_actor) {
    return ((daGoal_Flag_c*)i_actor)->CreateHeap();
}

/* 00001CE0-00001D74       .text CreateHeap__13daGoal_Flag_cFv */
BOOL daGoal_Flag_c::CreateHeap() {
    for (int i = 0; i < mNumRopes; i++) {
        if (!mRopeLines[i].init(1, (mNumRopeBuoys[i] << 2) + 1, 0)) {
            return FALSE;
        }
    }
    return TRUE;
}

bool daGoal_Flag_c::_delete() {
    u8 prm = fopAcM_GetParam(this) & 0xFF;
    dComIfG_resDeleteDemo(&mClothPhs, arcname);
    dComIfG_resDeleteDemo(&mFlagPhs, sub_arcname_tbl[prm]);

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

/* 00001D74-00001DB4       .text getDemoAction__13daGoal_Flag_cFi */
int daGoal_Flag_c::getDemoAction(int param_1) {
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
    int staff_idx = dComIfGp_evmng_getMyStaffId("Gflag");
    int action_idx = getDemoAction(staff_idx);

    if (mRaceStartState == 0) {
        if (staff_idx != -1 && action_idx == 0) {
            dComIfGp_evmng_cutEnd(staff_idx);
        } else {
            return TRUE;
        }         
        mRaceStartState++;
    } else {
        dTimer_c* timer_p = (dTimer_c*) fopMsgM_SearchByID(mTimerProcID);
        dMinigame_Starter_c* mgame_start_p = (dMinigame_Starter_c*) fopMsgM_SearchByID(mMgameStartProcID);

        if (action_idx == 1 && mgame_start_p) {
            mgame_start_p->countStart();
            dComIfGp_evmng_cutEnd(staff_idx);
        }

        if (timer_p && mgame_start_p && mgame_start_p->startCheck()) {
            dComIfGp_evmng_cutEnd(staff_idx);
            timer_p->start(7);
            if (mRaceStartState == 1) {
                mDoAud_bgmStart(JA_BGM_SEA_GAME);
                mRaceStartState++;
            }
        }

        if (dComIfGp_evmng_endCheck("race_start_cam")) {
            setAction(&daGoal_Flag_c::TimerExecute);
            mRaceStartState = 0;
        }
    }
    return TRUE;
}

/* 00001F60-00002290       .text TimerExecute__13daGoal_Flag_cFv */
BOOL daGoal_Flag_c::TimerExecute() {
    dTimer_c* timer_p = (dTimer_c *) fopMsgM_SearchByID(mTimerProcID);
    s32 finish_type;
    int goal_chk;
    int rupees_collected;
    int remaining_time;
    dMinigame_Starter_c* mgame_start_p;
    if (mMgameStartProcID != -1) {
        mgame_start_p = (dMinigame_Starter_c*) fopMsgM_SearchByID(mMgameStartProcID);
        if (mgame_start_p && mgame_start_p->deleteCheck()) {
            fopMsgM_Delete(mgame_start_p);
            mMgameStartProcID = -1;
        }
    }

    goal_chk = goal_check();

    if (goal_chk == 1) {
        if (mRaceEndState == 1) {
            timer_p->end(-1);
            if (dComIfGp_getMiniGameRupee() == 0) {
                mRaceEndState = 2;
            } else {
                mRaceEndState = 3;
            }
        } else {
            mRaceEndState = 1;
        }
    } else if (goal_chk == -1) {
        timer_p->end(-1);
        mDoAud_seStart(JA_SE_SGAME_TIMER_0);
        mRaceEndState = 2;
    }

    if (timer_p->getRestTimeMs() == 0 && (timer_p->end(-1), mRaceEndState != 3)) {
        mRaceEndState = 2;
        mDoAud_seStart(JA_SE_SGAME_TIMER_0);
    }

    if (mRaceEndState == 3 || mRaceEndState == 2) {
        if (eventInfo.checkCommandDemoAccrpt()) {
            timer_p->timerHide();
            if (mRaceEndState == 3) {
                // 1 is standard finish, 2 is perfect (got all 150 rupees)
                finish_type = dComIfGp_getMiniGameRupee() < l_HIO.mPerfectRupeeScore ? 1 : 2;
                dComIfGp_setMiniGameResult(1);
            } else {
                // 0 is did not finish or got no rupees
                finish_type = 0;
                dComIfGp_setMiniGameResult(2);
            }
            if (u16(finish_type) == 1 || u16(finish_type) == 2) {
                mDoAud_bgmStart(JA_BGM_SEA_GOAL);
            } else {
                mDoAud_bgmStart(JA_BGM_SEA_FAIL);
            }
            dComIfGp_clearPlayerStatus0(0, daPyStts0_TELESCOPE_LOOK_e);
            rupees_collected = dComIfGp_getMiniGameRupee();
            remaining_time = timer_p->getRestTimeMs() / 10;
            mMgameTermProcID = fopMsgM_MiniGameTerminater_create(
                PROC_MINIGAME_TERMINATER, 
                0, 
                finish_type, 
                remaining_time, 
                rupees_collected, 
                NULL
            );
            fopMsgM_SearchByID(mMgameTermProcID); // Unused return
            mCamFramesPassed = 0;
            setAction(&daGoal_Flag_c::RaceEnd);
            mRaceStartState = 0;
        } else {
            static char* event_name_tbl[] = {
                "race_goal_cam",
                "race_fail_cam",
            };
            char* event_name = event_name_tbl[mRaceEndState != 3 ? 1 : 0];
            fopAcM_orderOtherEvent2(this, event_name, dEvtFlag_NOPARTNER_e);
            eventInfo.onCondition(dEvtCnd_UNK2_e);
        }
    }

    return TRUE;
}

/* 00002290-000023E0       .text RaceEnd__13daGoal_Flag_cFv */
BOOL daGoal_Flag_c::RaceEnd() {
    static char* event_name_tbl[] = {
        "race_goal_cam",
        "race_fail_cam",
    };

    mCamFramesPassed++;
    
    dTimer_c* timer_p;
    if (
        mTimerProcID != -1 && 
        (timer_p = (dTimer_c*)fopMsgM_SearchByID(mTimerProcID)) &&
        timer_p->deleteCheck()
    ) {
        fopMsgM_Delete(timer_p);
        mTimerProcID = -1;
    }

    int staff_idx = dComIfGp_evmng_getMyStaffId("Gflag");
    
    if (staff_idx != -1) {
        dComIfGp_evmng_cutEnd(staff_idx);
    } 

    BOOL end_chk = dComIfGp_evmng_endCheck(event_name_tbl[mRaceEndState != 3 ? 1 : 0]);
    
    if (end_chk || (mCamFramesPassed > l_HIO.mEndCamEarlyFrame && 
        (CPad_CHECK_TRIG_A(0) || CPad_CHECK_TRIG_B(0) || CPad_CHECK_TRIG_START(0)) )) {
        dComIfGp_setNextStage("sea", 1, 0x30);
    }

    return true;
}

/* 000023E0-00002400       .text daGoal_FlagCreate__FPv */
static cPhs_State daGoal_FlagCreate(void* i_this) {
    return ((daGoal_Flag_c*)i_this)->_create();
}

/* 000029CC-00002AAC       .text daGoal_FlagDelete__FPv */
static BOOL daGoal_FlagDelete(void* i_this) {
    return ((daGoal_Flag_c*)i_this)->_delete();
}

bool daGoal_Flag_c::_execute() {
    if (mCurrProc != NULL) {
        (this->*mCurrProc)();
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
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);

    MtxTrans(current.pos.x, current.pos.y, current.pos.z, FALSE);
    cMtx_YrotM(*calc_mtx, current.angle.y);
    MtxScale(scale.x, scale.y, scale.z, TRUE);

    cMtx_concat(j3dSys.getViewMtx(), *calc_mtx, mFlagPacket.getMtx());

    mFlagPacket.setTevStr(&tevStr);
    j3dSys.getDrawBuffer(0)->entryImm(&mFlagPacket, 0);

    for (int i = 0; i < mNumRopes; i++) {
        GXColor rope_color;
        rope_color.r = l_HIO.mRopeColorR;
        rope_color.g = l_HIO.mRopeColorG;
        rope_color.b = l_HIO.mRopeColorB;
        rope_color.a = 0xFF;
        mRopeLines[i].update((mNumRopeBuoys[i] << 2) + 1, 20.0f, rope_color, 0, &tevStr);
        dComIfGd_set3DlineMat(&mRopeLines[i]);
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
