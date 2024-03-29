//
// Generated by dtk
// Translation Unit: d_bg_w.cpp
//

#include "d/d_bg_w.h"
#include "d/d_bg_s.h"
#include "d/d_bg_s_acch.h"
#include "d/d_bg_s_sph_chk.h"

#define CHECK_FLOAT_CLASS(line, x) JUT_ASSERT(line, !(((sizeof(x) == sizeof(float)) ? __fpclassifyf((float)(x)) : __fpclassifyd((double)(x)) ) == 1));

/* 800A5C3C-800A5CA8       .text __ct__4dBgWFv */
dBgW::dBgW() {
    mRotYDelta = 0;
    mOldRotY = 0;
    m_crr_func = NULL;
    mpRideCb = NULL;
    mpPushPullCb = NULL;
    mFlag = 0;
    mRoomNo = 0xFFFF;
    mRoomNo2 = 0xFF;
}

/* 800A5CA8-800A5CD4       .text Move__4dBgWFv */
void dBgW::Move() {
    mFlag |= 0x01;
    cBgW::Move();
}

/* 800A5CD4-800A5E64       .text positionWallCorrect__4dBgWFP9dBgS_AcchfR8cM3dGPlaP4cXyzf */
void dBgW::positionWallCorrect(dBgS_Acch* acch, f32 dist, cM3dGPla& plane, cXyz* pupper_pos, f32 speed) {
    acch->SetWallHit();
    f32 move = speed * dist;
    pupper_pos->x += move * plane.mNormal.x;
    pupper_pos->z += move * plane.mNormal.z;
    CHECK_FLOAT_CLASS(0xd0, pupper_pos->x);
    CHECK_FLOAT_CLASS(0xd1, pupper_pos->z);
}

/* 800A5E64-800A6DF8       .text RwgWallCorrect__4dBgWFP9dBgS_AcchUs */
bool dBgW::RwgWallCorrect(dBgS_Acch*, u16) {
    /* Nonmatching */
}

/* 800A6DF8-800A7004       .text WallCorrectRp__4dBgWFP9dBgS_Acchi */
bool dBgW::WallCorrectRp(dBgS_Acch* acch, int i) {
    cBgW_NodeTree* node = &m_nt_tbl[i];
    if (!node->Cross(acch->GetWallBmdCylP()))
        return false;

    cBgD_Tree_t* tree = &pm_bgd->m_tree_tbl[i];
    bool ret = false;
    if (tree->mFlag & 1) {
        if (pm_blk[tree->mBlock].wall != 0xFFFF && RwgWallCorrect(acch, pm_blk[tree->mBlock].wall))
            ret = true;
        if (pm_blk[tree->mBlock].roof != 0xFFFF && RwgWallCorrect(acch, pm_blk[tree->mBlock].roof))
            ret = true;
        return ret;
    } else {
        if (tree->mChild[0] != 0xFFFF && WallCorrectRp(acch, tree->mChild[0]))
            ret = true;
        if (tree->mChild[1] != 0xFFFF && WallCorrectRp(acch, tree->mChild[1]))
            ret = true;
        if (tree->mChild[2] != 0xFFFF && WallCorrectRp(acch, tree->mChild[2]))
            ret = true;
        if (tree->mChild[3] != 0xFFFF && WallCorrectRp(acch, tree->mChild[3]))
            ret = true;
        if (tree->mChild[4] != 0xFFFF && WallCorrectRp(acch, tree->mChild[4]))
            ret = true;
        if (tree->mChild[5] != 0xFFFF && WallCorrectRp(acch, tree->mChild[5]))
            ret = true;
        if (tree->mChild[6] != 0xFFFF && WallCorrectRp(acch, tree->mChild[6]))
            ret = true;
        if (tree->mChild[7] != 0xFFFF && WallCorrectRp(acch, tree->mChild[7]))
            ret = true;
        return ret;
    }
}

/* 800A7004-800A7120       .text WallCorrectGrpRp__4dBgWFP9dBgS_Acchii */
bool dBgW::WallCorrectGrpRp(dBgS_Acch* acch, int grp_id, int depth) {
    /* Nonmatching */
    if (ChkGrpThrough(grp_id, acch->GetGrpPassChk(), depth))
        return false;

    cBgW_GrpElm* grp = &pm_grp[grp_id];

    if (!grp->aab.Cross(acch->GetWallBmdCylP()))
        return false;

    bool ret = false;
    u32 tree_idx = pm_bgd->m_g_tbl[grp_id].m_tree_idx;
    if (tree_idx != 0xFFFF && WallCorrectRp(acch, tree_idx))
        ret = true;

    s32 child_idx = pm_bgd->m_g_tbl[grp_id].m_first_child;
    while (true) {
        if (child_idx == 0xFFFF)
            break;
        if (WallCorrectGrpRp(acch, child_idx, depth + 1))
            ret = true;
        child_idx = pm_bgd->m_g_tbl[child_idx].m_next_sibling;
    }

    return ret;
}

/* 800A7120-800A72E0       .text RwgRoofChk__4dBgWFUsP12dBgS_RoofChk */
bool dBgW::RwgRoofChk(u16 poly_index, dBgS_RoofChk* chk) {
    /* Nonmatching */

    bool ret = false;
    while (true) {
        f32 y;
        if (pm_tri[poly_index].m_plane.getCrossY(*chk->GetPosP(), &y) && y > chk->GetPosP()->y && y < chk->GetNowY()) {
            cBgD_Tri_t* tri;
            tri = &pm_bgd->m_t_tbl[poly_index];
            if (cM3d_CrossY_Tri(pm_vtx_tbl[tri->vtx0], pm_vtx_tbl[tri->vtx1], pm_vtx_tbl[tri->vtx2], pm_tri[poly_index].m_plane, chk->GetPosP()) && !ChkPolyThrough(poly_index, chk->GetPolyPassChk())) {
                chk->SetNowY(y);
                chk->SetPolyIndex(poly_index);
                ret = true;
            }
        }

        if (pm_rwg[poly_index].next == 0xFFFF)
            break;

        poly_index = pm_rwg[poly_index].next;
    }

    return ret;
}

/* 800A72E0-800A7514       .text RoofChkRp__4dBgWFP12dBgS_RoofChki */
bool dBgW::RoofChkRp(dBgS_RoofChk* chk, int i) {
    /* Nonmatching */
    cBgW_NodeTree* node = &m_nt_tbl[i];
    // if (!node->CrossY(chk->GetPosP()) || !node->UnderPlaneYUnder(chk->GetNowY()) || node->TopPlaneYUnder(chk->GetPosP()->y))
    if (!node->CrossY(chk->GetPosP()) || !(node->GetMinY() < chk->GetNowY()) || node->TopPlaneYUnder(chk->GetPosP()->y))
        return false;

    cBgD_Tree_t* tree = &pm_bgd->m_tree_tbl[i];
    if (tree->mFlag & 1) {
        if (pm_blk[tree->mBlock].roof != 0xFFFF && RwgRoofChk(pm_blk[tree->mBlock].roof, chk))
            return true;
        return false;
    } else {
        bool ret = false;
        if (tree->mChild[0] != 0xFFFF && RoofChkRp(chk, tree->mChild[0]))
            ret = true;
        if (tree->mChild[1] != 0xFFFF && RoofChkRp(chk, tree->mChild[1]))
            ret = true;
        if (tree->mChild[2] != 0xFFFF && RoofChkRp(chk, tree->mChild[2]))
            ret = true;
        if (tree->mChild[3] != 0xFFFF && RoofChkRp(chk, tree->mChild[3]))
            ret = true;
        if (tree->mChild[4] != 0xFFFF && RoofChkRp(chk, tree->mChild[4]))
            ret = true;
        if (tree->mChild[5] != 0xFFFF && RoofChkRp(chk, tree->mChild[5]))
            ret = true;
        if (tree->mChild[6] != 0xFFFF && RoofChkRp(chk, tree->mChild[6]))
            ret = true;
        if (tree->mChild[7] != 0xFFFF && RoofChkRp(chk, tree->mChild[7]))
            ret = true;
        return ret;
    }
}

/* 800A7514-800A767C       .text RoofChkGrpRp__4dBgWFP12dBgS_RoofChkii */
bool dBgW::RoofChkGrpRp(dBgS_RoofChk* chk, int grp_id, int depth) {
    if (ChkGrpThrough(grp_id, chk->GetGrpPassChk(), depth))
        return false;

    cBgW_GrpElm* grp = &pm_grp[grp_id];

    // if (!grp->aab.CrossY(chk->GetPosP()) || !grp->aab.UnderPlaneYUnder(chk->GetNowY()) || grp->aab.TopPlaneYUnder(chk->GetPosP()->y))
    if (!grp->aab.CrossY(chk->GetPosP()) || !(grp->aab.GetMinY() < chk->GetNowY()) || grp->aab.TopPlaneYUnder(chk->GetPosP()->y))
        return false;

    bool ret = false;
    cBgD_Grp_t* grpd = &pm_bgd->m_g_tbl[grp_id];
    u32 tree_idx = grpd->m_tree_idx;
    if (tree_idx != 0xFFFF && RoofChkRp(chk, tree_idx))
        ret = true;

    s32 child_idx = grpd->m_first_child;
    while (true) {
        if (child_idx == 0xFFFF)
            break;
        if (RoofChkGrpRp(chk, child_idx, depth + 1))
            ret = true;
        child_idx = pm_bgd->m_g_tbl[child_idx].m_next_sibling;
    }

    return ret;
}

/* 800A767C-800A783C       .text RwgSplGrpChk__4dBgWFUsP14dBgS_SplGrpChk */
bool dBgW::RwgSplGrpChk(u16 poly_index, dBgS_SplGrpChk* chk) {
    /* Nonmatching */

    bool ret = false;
    while (true) {
        f32 y;
        if (pm_tri[poly_index].m_plane.getCrossY(*chk->GetPosP(), &y) && y < chk->GetRoof() && y > chk->GetHeight()) {
            cBgD_Tri_t* tri;
            tri = &pm_bgd->m_t_tbl[poly_index];
            if (cM3d_CrossY_Tri(pm_vtx_tbl[tri->vtx0], pm_vtx_tbl[tri->vtx1], pm_vtx_tbl[tri->vtx2], pm_tri[poly_index].m_plane, chk->GetPosP()) && !ChkPolyThrough(poly_index, chk->GetPolyPassChk())) {
                chk->SetHeight(y);
                chk->SetPolyIndex(poly_index);
                ret = true;
            }
        }

        if (pm_rwg[poly_index].next == 0xFFFF)
            break;

        poly_index = pm_rwg[poly_index].next;
    }

    return ret;
}

/* 800A783C-800A7A74       .text SplGrpChkRp__4dBgWFP14dBgS_SplGrpChki */
bool dBgW::SplGrpChkRp(dBgS_SplGrpChk* chk, int i) {
    cBgW_NodeTree* node = &m_nt_tbl[i];
    // if (!node->CrossY(chk->GetPosP()) || !node->UnderPlaneYUnder(chk->GetRoof()) || node->TopPlaneYUnder(chk->GetHeight()))
    if (!node->CrossY(chk->GetPosP()) || !(node->GetMinY() < chk->GetRoof()) || node->GetMaxY() < chk->GetHeight())
        return false;

    cBgD_Tree_t* tree = &pm_bgd->m_tree_tbl[i];
    if (tree->mFlag & 1) {
        if (pm_blk[tree->mBlock].ground != 0xFFFF && RwgSplGrpChk(pm_blk[tree->mBlock].ground, chk))
            return true;
        return false;
    } else {
        bool ret = false;
        if (tree->mChild[0] != 0xFFFF && SplGrpChkRp(chk, tree->mChild[0]))
            ret = true;
        if (tree->mChild[1] != 0xFFFF && SplGrpChkRp(chk, tree->mChild[1]))
            ret = true;
        if (tree->mChild[2] != 0xFFFF && SplGrpChkRp(chk, tree->mChild[2]))
            ret = true;
        if (tree->mChild[3] != 0xFFFF && SplGrpChkRp(chk, tree->mChild[3]))
            ret = true;
        if (tree->mChild[4] != 0xFFFF && SplGrpChkRp(chk, tree->mChild[4]))
            ret = true;
        if (tree->mChild[5] != 0xFFFF && SplGrpChkRp(chk, tree->mChild[5]))
            ret = true;
        if (tree->mChild[6] != 0xFFFF && SplGrpChkRp(chk, tree->mChild[6]))
            ret = true;
        if (tree->mChild[7] != 0xFFFF && SplGrpChkRp(chk, tree->mChild[7]))
            ret = true;
        return ret;
    }
}

/* 800A7A74-800A7BDC       .text SplGrpChkGrpRp__4dBgWFP14dBgS_SplGrpChkii */
bool dBgW::SplGrpChkGrpRp(dBgS_SplGrpChk* chk, int grp_id, int depth) {
    if (ChkGrpThrough(grp_id, chk->GetGrpPassChk(), depth))
        return false;

    cBgW_GrpElm* grp = &pm_grp[grp_id];

    // if (!grp->aab.CrossY(chk->GetPosP()) || !grp->aab.UnderPlaneYUnder(chk->GetRoof()) || grp->aab.TopPlaneYUnder(chk->GetHeight()))
    if (!grp->aab.CrossY(chk->GetPosP()) || !(grp->aab.GetMinY() < chk->GetRoof()) || grp->aab.GetMaxY() < chk->GetHeight())
        return false;

    bool ret = false;
    cBgD_Grp_t* grpd = &pm_bgd->m_g_tbl[grp_id];
    u16 tree_idx = grpd->m_tree_idx;
    if (tree_idx != 0xFFFF && SplGrpChkRp(chk, tree_idx))
        ret = true;

    s32 child_idx = grpd->m_first_child;
    while (true) {
        if (child_idx == 0xFFFF)
            break;
        if (SplGrpChkGrpRp(chk, child_idx, depth + 1))
            ret = true;
        child_idx = pm_bgd->m_g_tbl[child_idx].m_next_sibling;
    }

    return ret;
}

/* 800A7BDC-800A7DCC       .text RwgSphChk__4dBgWFUsP11dBgS_SphChkPv */
bool dBgW::RwgSphChk(u16 poly_index, dBgS_SphChk* chk, void* user) {
    /* Nonmatching */
    cM3dGTri gtri;

    bool ret = false;
    while (true) {
        if (!ChkPolyThrough(poly_index, chk->GetPolyPassChk())) {
            cBgW_TriElm* tri_elm;
            cBgD_Tri_t* tri;

            tri = &pm_bgd->m_t_tbl[poly_index];
            tri_elm = &pm_tri[poly_index];

            gtri.setBg(&pm_vtx_tbl[tri->vtx0], &pm_vtx_tbl[tri->vtx1], &pm_vtx_tbl[tri->vtx2], &tri_elm->m_plane);
            if (cM3d_Cross_SphTri(chk, &gtri)) {
                if (chk->mpCallback != NULL) {
                    chk->mpCallback(chk, (cBgD_Vtx_t*)pm_vtx_tbl, tri->vtx0, tri->vtx1, tri->vtx2, &pm_tri[poly_index].m_plane, user);
                }
                chk->SetPolyIndex(poly_index);
                ret = true;
            }
        }

        if (pm_rwg[poly_index].next == 0xFFFF)
            break;

        poly_index = pm_rwg[poly_index].next;
    }

    return ret;
}

/* 800A7DCC-800A8038       .text SphChkRp__4dBgWFP11dBgS_SphChkPvi */
bool dBgW::SphChkRp(dBgS_SphChk* chk, void* user, int i) {
    cBgW_NodeTree* node = &m_nt_tbl[i];
    if (!node->Cross(chk))
        return false;

    cBgD_Tree_t* tree = &pm_bgd->m_tree_tbl[i];
    bool ret = false;
    if (tree->mFlag & 1) {
        if (pm_blk[tree->mBlock].ground != 0xFFFF && RwgSphChk(pm_blk[tree->mBlock].ground, chk, user))
            ret = true;
        if (pm_blk[tree->mBlock].roof != 0xFFFF && RwgSphChk(pm_blk[tree->mBlock].roof, chk, user))
            ret = true;
        if (pm_blk[tree->mBlock].wall != 0xFFFF && RwgSphChk(pm_blk[tree->mBlock].wall, chk, user))
            ret = true;
        return ret;
    } else {
        if (tree->mChild[0] != 0xFFFF && SphChkRp(chk, user, tree->mChild[0]))
            ret = true;
        if (tree->mChild[1] != 0xFFFF && SphChkRp(chk, user, tree->mChild[1]))
            ret = true;
        if (tree->mChild[2] != 0xFFFF && SphChkRp(chk, user, tree->mChild[2]))
            ret = true;
        if (tree->mChild[3] != 0xFFFF && SphChkRp(chk, user, tree->mChild[3]))
            ret = true;
        if (tree->mChild[4] != 0xFFFF && SphChkRp(chk, user, tree->mChild[4]))
            ret = true;
        if (tree->mChild[5] != 0xFFFF && SphChkRp(chk, user, tree->mChild[5]))
            ret = true;
        if (tree->mChild[6] != 0xFFFF && SphChkRp(chk, user, tree->mChild[6]))
            ret = true;
        if (tree->mChild[7] != 0xFFFF && SphChkRp(chk, user, tree->mChild[7]))
            ret = true;
        return ret;
    }
}

/* 800A8038-800A8158       .text SphChkGrpRp__4dBgWFP11dBgS_SphChkPvii */
bool dBgW::SphChkGrpRp(dBgS_SphChk* chk, void* user, int grp_id, int depth) {
    if (ChkGrpThrough(grp_id, chk->GetGrpPassChk(), depth))
        return false;

    cBgW_GrpElm* grp = &pm_grp[grp_id];

    if (!grp->aab.Cross(chk))
        return false;

    bool ret = false;
    cBgD_Grp_t* grpd = &pm_bgd->m_g_tbl[grp_id];
    u16 tree_idx = grpd->m_tree_idx;
    if (tree_idx != 0xFFFF && SphChkRp(chk, user, tree_idx))
        ret = true;

    s32 child_idx = grpd->m_first_child;
    while (true) {
        if (child_idx == 0xFFFF)
            break;
        if (SphChkGrpRp(chk, user, child_idx, depth + 1))
            ret = true;
        child_idx = pm_bgd->m_g_tbl[child_idx].m_next_sibling;
    }

    return ret;
}

/* 800A8158-800A819C       .text positionWallCrrPos__4dBgWFR8cM3dGTriP11dBgS_CrrPosP4cXyzff */
void dBgW::positionWallCrrPos(cM3dGTri& plane, dBgS_CrrPos* crr, cXyz* pos, f32 dist, f32 rad) {
    crr->SetWallHit();
    f32 move = (crr->GetWallR() - rad) * dist;
    pos->x += move * plane.mNormal.x;
    pos->z += move * plane.mNormal.z;
}

/* 800A819C-800A8964       .text RwgWallCrrPos__4dBgWFUsP11dBgS_CrrPos */
bool dBgW::RwgWallCrrPos(u16, dBgS_CrrPos*) {
    /* Nonmatching */
}

/* 800A8964-800A8B70       .text WallCrrPosRp__4dBgWFP11dBgS_CrrPosi */
bool dBgW::WallCrrPosRp(dBgS_CrrPos* crr, int i) {
    cBgW_NodeTree* node = &m_nt_tbl[i];
    if (!node->Cross(crr->GetCylP()))
        return false;

    bool ret = false;
    cBgD_Tree_t* tree = &pm_bgd->m_tree_tbl[i];
    if (tree->mFlag & 1) {
        if (pm_blk[tree->mBlock].wall != 0xFFFF && RwgWallCrrPos(pm_blk[tree->mBlock].wall, crr))
            ret = true;
        if (pm_blk[tree->mBlock].roof != 0xFFFF && RwgWallCrrPos(pm_blk[tree->mBlock].roof, crr))
            ret = true;
        return ret;
    } else {
        if (tree->mChild[0] != 0xFFFF && WallCrrPosRp(crr, tree->mChild[0]))
            ret = true;
        if (tree->mChild[1] != 0xFFFF && WallCrrPosRp(crr, tree->mChild[1]))
            ret = true;
        if (tree->mChild[2] != 0xFFFF && WallCrrPosRp(crr, tree->mChild[2]))
            ret = true;
        if (tree->mChild[3] != 0xFFFF && WallCrrPosRp(crr, tree->mChild[3]))
            ret = true;
        if (tree->mChild[4] != 0xFFFF && WallCrrPosRp(crr, tree->mChild[4]))
            ret = true;
        if (tree->mChild[5] != 0xFFFF && WallCrrPosRp(crr, tree->mChild[5]))
            ret = true;
        if (tree->mChild[6] != 0xFFFF && WallCrrPosRp(crr, tree->mChild[6]))
            ret = true;
        if (tree->mChild[7] != 0xFFFF && WallCrrPosRp(crr, tree->mChild[7]))
            ret = true;
        return ret;
    }
}

/* 800A8B70-800A8C8C       .text WallCrrPosGrpRp__4dBgWFP11dBgS_CrrPosii */
bool dBgW::WallCrrPosGrpRp(dBgS_CrrPos* crr, int grp_id, int depth) {
    if (ChkGrpThrough(grp_id, crr->GetGrpPassChk(), depth))
        return false;

    cBgW_GrpElm* grp = &pm_grp[grp_id];

    if (!grp->aab.Cross(crr->GetCylP()))
        return false;

    bool ret = false;
    u32 tree_idx = pm_bgd->m_g_tbl[grp_id].m_tree_idx;
    if (tree_idx != 0xFFFF && WallCrrPosRp(crr, tree_idx))
        ret = true;

    s32 child_idx = pm_bgd->m_g_tbl[grp_id].m_first_child;
    while (true) {
        if (child_idx == 0xFFFF)
            break;
        if (WallCrrPosGrpRp(crr, child_idx, depth + 1))
            ret = true;
        child_idx = pm_bgd->m_g_tbl[child_idx].m_next_sibling;
    }

    return ret;
}

/* 800A8C8C-800A8CB4       .text WallCrrPos__4dBgWFP11dBgS_CrrPos */
bool dBgW::WallCrrPos(dBgS_CrrPos* crr) {
    return WallCrrPosGrpRp(crr, m_rootGrpIdx, 1);
}

/* 800A8CB4-800A8CF0       .text CrrPos__4dBgWFR13cBgS_PolyInfoPvbP4cXyzP5csXyzP5csXyz */
void dBgW::CrrPos(cBgS_PolyInfo& poly, void* user, bool accept, cXyz* pos, csXyz* angle, csXyz* shape_angle) {
    if (m_crr_func != NULL)
        m_crr_func(this, user, poly, accept, pos, angle, shape_angle);
}

/* 800A8CF0-800A8D2C       .text TransPos__4dBgWFR13cBgS_PolyInfoPvbP4cXyzP5csXyzP5csXyz */
void dBgW::TransPos(cBgS_PolyInfo& poly, void* user, bool accept, cXyz* pos, csXyz* angle, csXyz* shape_angle) {
    if (m_crr_func != NULL)
        m_crr_func(this, user, poly, accept, pos, angle, shape_angle);
}

/* 800A8D2C-800A9474       .text ChkPolyThrough__4dBgWFiP16cBgS_PolyPassChk */
bool dBgW::ChkPolyThrough(int poly_index, cBgS_PolyPassChk* chk) {
    /* Nonmatching */
    if (chk == NULL)
        return false;
    if (chk->mbObjThrough && GetPolyInf3(GetPolyInfId(poly_index)) & 0x02)
        return true;
    if (chk->mbCamThrough && GetPolyInf3(GetPolyInfId(poly_index)) & 0x01)
        return true;
    if (chk->mbLinkThrough && GetPolyInf3(GetPolyInfId(poly_index)) & 0x04)
        return true;
    if (chk->mbArrowThrough && GetPolyInf3(GetPolyInfId(poly_index)) & 0x08)
        return true;
    if (chk->mbBombThrough && GetPolyInf3(GetPolyInfId(poly_index)) & 0x20)
        return true;
    if (chk->mbBoomerangThrough && GetPolyInf3(GetPolyInfId(poly_index)) & 0x40)
        return true;
    if (chk->mbRopeThrough && GetPolyInf3(GetPolyInfId(poly_index)) & 0x80)
        return true;
    return false;
}

/* 800A9474-800A9684       .text ChkShdwDrawThrough__4dBgWFiP16cBgS_PolyPassChk */
bool dBgW::ChkShdwDrawThrough(int poly_index, cBgS_PolyPassChk* chk) {
    /* Nonmatching */
    if ((GetPolyInf0(GetPolyInfId(poly_index)) >> 27) & 1)
        return true;

    if (GetPolyInf3(GetPolyInfId(poly_index)) & 0x08)
        return true;

    return false;
}

/* 800A9684-800A974C       .text ChkGrpThrough__4dBgWFiP15cBgS_GrpPassChki */
bool dBgW::ChkGrpThrough(int grp_id, cBgS_GrpPassChk* _chk, int depth) {
    dBgS_GrpPassChk* chk = (dBgS_GrpPassChk*)_chk;
    if (depth != 2 || chk == NULL)
        return false;

    int info = pm_bgd->m_g_tbl[grp_id].m_info;
    if (!(info & 0x80700) && chk->MaskNormalGrp())
        return false;
    if ((info & 0x00100) && chk->MaskWaterGrp())
        return false;
    if ((info & 0x00200) && chk->MaskYoganGrp())
        return false;
    if ((info & 0x00400) && chk->MaskDokuGrp())
        return false;
    if ((info & 0x80000) && chk->MaskLightGrp())
        return false;
    return true;
}

/* 800A974C-800A97E4       .text ChangeAttributeCodeByPathPntNo__4dBgWFiUl */
void dBgW::ChangeAttributeCodeByPathPntNo(int pnt_no, u32 attr) {
    if (pm_bgd != NULL) {
        for (s32 i = 0; i < pm_bgd->m_ti_num; i++) {
            u32 ti_pnt_no = dBgS_GetRoomPathPntNo(pm_bgd->m_ti_tbl[i].mPolyInf2);
            if (ti_pnt_no == pnt_no)
                dBgS_ChangeAttributeCode(attr, &pm_bgd->m_ti_tbl[i].mPolyInf1);
        }
    }
}

/* 800A97E4-800A986C       .text dBgW_NewSet__FP6cBgD_tUlPA3_A4_f */
dBgW* dBgW_NewSet(cBgD_t* bgd, u32 flag, Mtx* mtx) {
    dBgW* rt = new dBgW();
    if (rt == NULL)
        return NULL;
    if (rt->Set(bgd, flag, mtx))
        return NULL;
    return rt;
}
