//
// Generated by dtk
// Translation Unit: d_bg_w_sv.cpp
//

#include "d/d_bg_w_sv.h"
#include "SSystem/SComponent/c_bg_s_poly_info.h"

/* 800AABFC-800AAC84       .text Set__6dBgWSvFP6cBgD_tUl */
bool dBgWSv::Set(cBgD_t* bgd, u32 flag) {
    if (cBgW::Set(bgd, MOVE_BG_e | NO_CALC_VTX_e | GLOBAL_e | UNK40_e, NULL)) {
        return true;
    }
    mSvFlag = flag;
    if (ChkNoCrrPos()) {
        return false;
    }
    SetBackVtx(new Vec[pm_bgd->m_v_num]);
    if (GetBackVtx() == NULL) {
        return true;
    }
    return false;
}

/* 800AAC84-800AACF0       .text CopyBackVtx__6dBgWSvFv */
void dBgWSv::CopyBackVtx() {
    if (mBackVtx == NULL || pm_vtx_tbl == NULL) {
        return;
    }
    for (int i = 0; i < pm_bgd->m_v_num; i++) {
        mBackVtx[i] = pm_vtx_tbl[i];
    }
}

/* 800AACF0-800AAEA8       .text CrrPosWork__6dBgWSvFP4cXyziii */
bool dBgWSv::CrrPosWork(cXyz* pos, int v0, int v1, int v2) {
    cXyz sp2c;
    cXyz sp20;
    sp2c.x = mBackVtx[v1].x - mBackVtx[v0].x;
    sp2c.y = mBackVtx[v1].y - mBackVtx[v0].y;
    sp2c.z = mBackVtx[v1].z - mBackVtx[v0].z;
    sp20.x = mBackVtx[v2].x - mBackVtx[v0].x;
    sp20.y = mBackVtx[v2].y - mBackVtx[v0].y;
    sp20.z = mBackVtx[v2].z - mBackVtx[v0].z;
    if (cM3d_IsZero(sp2c.z) || cM3d_IsZero(sp20.z)) { return true; }
    
    f32 f8 = sp2c.x - (sp2c.z * (sp20.x / sp20.z));
    f32 f5 = sp20.x - (sp20.z * (sp2c.x / sp2c.z));
    if (cM3d_IsZero(f8) || cM3d_IsZero(f5)) { return true; }
    
    pos->x -= mBackVtx[v0].x;
    pos->z -= mBackVtx[v0].z;
    
    f32 f6 = (pos->x - (pos->z * (sp20.x / sp20.z))) / f8;
    f32 f7 = (pos->x - (pos->z * (sp2c.x / sp2c.z))) / f5;
    
    cXyz sp14;
    cXyz sp08;
    sp14.x = pm_vtx_tbl[v1].x - pm_vtx_tbl[v0].x;
    sp14.z = pm_vtx_tbl[v1].z - pm_vtx_tbl[v0].z;
    sp08.x = pm_vtx_tbl[v2].x - pm_vtx_tbl[v0].x;
    sp08.z = pm_vtx_tbl[v2].z - pm_vtx_tbl[v0].z;
    
    pos->x = f6 * sp14.x + f7 * sp08.x;
    pos->z = f6 * sp14.z + f7 * sp08.z;
    
    pos->x += pm_vtx_tbl[v0].x;
    pos->z += pm_vtx_tbl[v0].z;
    
    return false;
}

/* 800AAEA8-800AAF64       .text CrrPos__6dBgWSvFR13cBgS_PolyInfoPvbP4cXyzP5csXyzP5csXyz */
void dBgWSv::CrrPos(cBgS_PolyInfo& poly, void* user, bool accept, cXyz* pos, csXyz* angle, csXyz* shape_angle) {
    if (ChkNoCrrPos()) { return; }
    if (!accept) { return; }
    u16 polyIndex = poly.GetPolyIndex();
    int vtx0 = pm_bgd->m_t_tbl[polyIndex].vtx0;
    int vtx1 = pm_bgd->m_t_tbl[polyIndex].vtx1;
    int vtx2 = pm_bgd->m_t_tbl[polyIndex].vtx2;
    if (!CrrPosWork(pos, vtx0, vtx1, vtx2)) { return; }
    if (!CrrPosWork(pos, vtx1, vtx2, vtx0)) { return; }
    if (!CrrPosWork(pos, vtx2, vtx0, vtx1)) {}
}

/* 800AAF64-800AB180       .text TransPosWork__6dBgWSvFP4cXyziii */
bool dBgWSv::TransPosWork(cXyz* pos, int v0, int v1, int v2) {
    cXyz sp2c;
    cXyz sp20;
    sp2c.x = mBackVtx[v1].x - mBackVtx[v0].x;
    sp2c.y = mBackVtx[v1].y - mBackVtx[v0].y;
    sp2c.z = mBackVtx[v1].z - mBackVtx[v0].z;
    sp20.x = mBackVtx[v2].x - mBackVtx[v0].x;
    sp20.y = mBackVtx[v2].y - mBackVtx[v0].y;
    sp20.z = mBackVtx[v2].z - mBackVtx[v0].z;
    if (cM3d_IsZero(sp2c.z) || cM3d_IsZero(sp20.z)) { return true; }
    
    f32 f8 = sp2c.x - (sp2c.z * (sp20.x / sp20.z));
    f32 f4 = sp20.x - (sp20.z * (sp2c.x / sp2c.z));
    if (cM3d_IsZero(f8) || cM3d_IsZero(f4)) { return true; }
    
    f32 f5 = pos->x - mBackVtx[v0].x;
    f32 f1 = pos->z - mBackVtx[v0].z;
    f32 f8_2 = (f5 - (f1 * (sp20.x / sp20.z))) / f8;
    f32 f9 = (f5 - (f1 * (sp2c.x / sp2c.z))) / f4;
    
    if (f8_2 < 0.0f || f8_2 > 1.0f || f9 < 0.0f || f9 > 1.0f) {
        return true;
    }
    
    cXyz sp14;
    cXyz sp08;
    sp14.x = pm_vtx_tbl[v1].x - pm_vtx_tbl[v0].x;
    sp14.y = pm_vtx_tbl[v1].y - pm_vtx_tbl[v0].y;
    sp14.z = pm_vtx_tbl[v1].z - pm_vtx_tbl[v0].z;
    sp08.x = pm_vtx_tbl[v2].x - pm_vtx_tbl[v0].x;
    sp08.y = pm_vtx_tbl[v2].y - pm_vtx_tbl[v0].y;
    sp08.z = pm_vtx_tbl[v2].z - pm_vtx_tbl[v0].z;
    
    pos->x = f8_2 * sp14.x + f9 * sp08.x;
    pos->y = f8_2 * sp14.y + f9 * sp08.y;
    pos->z = f8_2 * sp14.z + f9 * sp08.z;
    
    pos->x += pm_vtx_tbl[v0].x;
    pos->y += pm_vtx_tbl[v0].y;
    pos->z += pm_vtx_tbl[v0].z;
    
    return false;
}

/* 800AB180-800AB23C       .text TransPos__6dBgWSvFR13cBgS_PolyInfoPvbP4cXyzP5csXyzP5csXyz */
void dBgWSv::TransPos(cBgS_PolyInfo& poly, void* user, bool accept, cXyz* pos, csXyz* angle, csXyz* shape_angle) {
    if (ChkNoCrrPos()) { return; }
    if (!accept) { return; }
    u16 polyIndex = poly.GetPolyIndex();
    int vtx0 = pm_bgd->m_t_tbl[polyIndex].vtx0;
    int vtx1 = pm_bgd->m_t_tbl[polyIndex].vtx1;
    int vtx2 = pm_bgd->m_t_tbl[polyIndex].vtx2;
    if (!TransPosWork(pos, vtx0, vtx1, vtx2)) { return; }
    if (!TransPosWork(pos, vtx1, vtx2, vtx0)) { return; }
    if (!TransPosWork(pos, vtx2, vtx0, vtx1)) {}
}
