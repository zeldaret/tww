#ifndef C_BG_W_H
#define C_BG_W_H

#include "JSystem/JUtility/JUTAssert.h"
#include "SSystem/SComponent/c_xyz.h"
#include "SSystem/SComponent/c_sxyz.h"
#include "SSystem/SComponent/c_m3d_g_aab.h"
#include "SSystem/SComponent/c_m3d_g_pla.h"
#include "dolphin/mtx/mtx.h"

class cBgW_BgId {
private:
    /* 0x0 */ int m_id;
    /* 0x4 vtable */

public:
    void Release();
    void Regist(int);

    virtual ~cBgW_BgId() {}

    cBgW_BgId() { Ct(); }
    void Ct() { m_id = 0x100; }

    int GetId() const { return m_id; }
    void SetId(int id) { m_id = id; }
    bool ChkUsed() const {
        if (m_id >= 0 && m_id < 0x100) {
            return true;
        }
        return false;
    }
};

struct cBgD_Vtx_t;

struct cBgD_Blk_t {
    /* 0x0 */ u16 field_0x00;
};

struct cBgD_Ti_t {
public:
    /* 0x00 */ u32 mPolyInf0;
    /* 0x04 */ u32 mPolyInf1;
    /* 0x08 */ u32 mPolyInf2;
    /* 0x0C */ u32 mPolyInf3;
};

struct cBgD_Tri_t {
public:
    /* 0x00 */ u16 vtx0;
    /* 0x02 */ u16 vtx1;
    /* 0x04 */ u16 vtx2;
    /* 0x06 */ u16 id;
    /* 0x08 */ u16 grp;
};

struct cBgD_Grp_t {
    /* 0x00 */ char* m_name;
    /* 0x04 */ cXyz m_scale;
    /* 0x10 */ csXyz m_rotation;
    /* 0x18 */ cXyz m_translation;
    /* 0x24 */ u16 m_parent;
    /* 0x26 */ u16 m_next_sibling;
    /* 0x28 */ u16 m_first_child;
    /* 0x2A */ u16 m_room_id;
    /* 0x2C */ u16 m_first_vtx_idx;
    /* 0x2E */ u16 m_tree_idx;
    /* 0x30 */ u32 m_info;
}; // Size: 0x34

class cBgW_NodeTree : public cM3dGAab {
public:
    virtual ~cBgW_NodeTree();
};

class cBgD_t {
public:
    /* 0x00 */ s32 m_v_num;
    /* 0x04 */ cBgD_Vtx_t* m_v_tbl;
    /* 0x08 */ s32 m_t_num;
    /* 0x0C */ cBgD_Tri_t* m_t_tbl;
    /* 0x10 */ s32 m_b_num;
    /* 0x14 */ cBgD_Blk_t* m_b_tbl;
    /* 0x18 */ s32 m_tree_num;
    /* 0x1C */ void* m_tree_tbl;
    /* 0x20 */ s32 m_g_num;
    /* 0x24 */ cBgD_Grp_t* m_g_tbl;
    /* 0x28 */ s32 m_ti_num;
    /* 0x2C */ cBgD_Ti_t* m_ti_tbl;
    /* 0x30 */ u32 flag;
};
class cBgS_LinChk;
class cBgS_GndChk;
class cBgS_ShdwDraw;
class cBgS_PolyPassChk;
class cBgS_GrpPassChk;

class cBgW_RwgElm {
public:
    /* 0x00 */ u16 next;

public:
    virtual ~cBgW_RwgElm() {}
};

class cBgW_BlkElm;
class cBgW_TriElm {
public:
    /* 0x00 */ cM3dGPla m_plane;

    virtual ~cBgW_TriElm() {}
};

class cBgW_GrpElm {
public:
    virtual ~cBgW_GrpElm() {}

public:
    /* 0x00 */ cM3dGAab aab;
};

class cBgW : public cBgW_BgId {
public:
    enum Flags_e {
        MOVE_BG_e = 0x1,
        NO_VTX_TBL_e = 0x10,
        GLOBAL_e = 0x20,
        LOCK_e = 0x80,
    };

    enum PRIORITY {
        
    };

    cBgW();

    void FreeArea();
    void GlobalVtx();
    void SetVtx();
    
    bool SetTri();
    void BlckConnect(u16*, int*, int);
    void MakeBlckTransMinMax(cXyz*, cXyz*);
    void MakeBlckMinMax(int, cXyz*, cXyz*);
    void MakeBlckBnd(int, cXyz*, cXyz*);
    void MakeNodeTreeRp(int);
    void MakeNodeTreeGrpRp(int);
    void MakeNodeTree();
    bool ChkMemoryError();
    bool Set(cBgD_t*, u32, f32(*)[3][4]);
    void RwgLineCheck(u16, cBgS_LinChk*);
    void LineCheckRp(cBgS_LinChk*, int);
    bool LineCheckGrpRp(cBgS_LinChk*, int, int);
    bool RwgGroundCheckCommon(f32, u16, cBgS_GndChk*);
    bool RwgGroundCheckGnd(u16, cBgS_GndChk*);
    bool RwgGroundCheckWall(u16, cBgS_GndChk*);
    void GroundCrossRp(cBgS_GndChk*, int);
    bool GroundCrossGrpRp(cBgS_GndChk*, int, int);
    void CopyOldMtx();
    void Move();
    void RwgShdwDraw(int, cBgS_ShdwDraw*);
    void ShdwDrawRp(cBgS_ShdwDraw*, int);
    void ShdwDrawGrpRp(cBgS_ShdwDraw*, int);
    void GetTrans(cXyz*) const;
    void GetTriPnt(int, cXyz*, cXyz*, cXyz*) const;
    void GetTopUnder(f32*, f32*) const;

    s32 GetGrpInf(int grp_id) const {
        JUT_ASSERT(0x2e1, 0 <= grp_id && grp_id < pm_bgd->m_g_num);
        return pm_bgd->m_g_tbl[grp_id].m_info;
    }

    s32 GetTriGrp(int poly_index) const {
        JUT_ASSERT(0x2a2, 0 <= poly_index && poly_index < pm_bgd->m_t_num);
        return pm_bgd->m_t_tbl[poly_index].grp;
    }

    cM3dGPla * GetTriPla(int poly_index) {
        JUT_ASSERT(0x2af, 0 <= poly_index && poly_index < pm_bgd->m_t_num);
        return &pm_tri[poly_index].m_plane;
    }

    void SetPriority(PRIORITY priority) { mWallCorrectPriority = priority; }
    void SetLock() { mFlags |= LOCK_e; }

    void ChkFlush() {}
    void ChkGroundRegist() {}
    void ChkLock() {}
    bool ChkMoveBg() { return mFlags & MOVE_BG_e; }
    void ChkNoCalcVtx() {}
    BOOL ChkPriority(int prio) { return mWallCorrectPriority == prio; }
    void ChkRoofRegist() {}
    void ChkThrough() {}
    void ChkWallRegist() {}
    void ClrNoCalcVtx() {}
    void GetBaseMtxP() {}
    void GetOldInvMtx(float(*)[4]) const {}
    u32 GetPolyInfId(int poly_index) const {
        JUT_ASSERT(0x2f1, 0 <= poly_index && poly_index < pm_bgd->m_t_num);
        return pm_bgd->m_t_tbl[poly_index].id;
    }
    u32 GetPolyInf0(int id) const {
        JUT_ASSERT(0x2f8, 0 <= id && id < pm_bgd->m_ti_num);
        return pm_bgd->m_ti_tbl[id].mPolyInf0;
    }
    u32 GetPolyInf1(int id) const {
        JUT_ASSERT(0x2fd, 0 <= id && id < pm_bgd->m_ti_num);
        return pm_bgd->m_ti_tbl[id].mPolyInf1;
    }
    u32 GetPolyInf2(int id) const {
        JUT_ASSERT(0x302, 0 <= id && id < pm_bgd->m_ti_num);
        return pm_bgd->m_ti_tbl[id].mPolyInf2;
    }
    u32 GetPolyInf3(int id) const {
        JUT_ASSERT(0x307, 0 <= id && id < pm_bgd->m_ti_num);
        return pm_bgd->m_ti_tbl[id].mPolyInf3;
    }
    void GetVtxNum() const {}
    void GetVtxTbl() const {}
    void GroundCross(cBgS_GndChk*) {}
    void LineCheck(cBgS_LinChk*) {}
    void OffRoofRegist() {}
    void SetBaseMtxP(float(*)[3][4]) {}
    void SetNoCalcVtx() {}
    void SetVtxTbl(Vec*) {}
    void ShdwDraw(cBgS_ShdwDraw*) {}

    virtual ~cBgW();
    virtual u32 GetGrpToRoomIndex(int) const;
    virtual void CalcPlane();
    virtual void ClassifyPlane();
    virtual bool ChkPolyThrough(int, cBgS_PolyPassChk*);
    virtual bool ChkShdwDrawThrough(int, cBgS_PolyPassChk*);
    virtual bool ChkGrpThrough(int, cBgS_GrpPassChk*, int);

    /* 0x08 */ Mtx* pm_base;
    /* 0x0C */ Mtx mOldMtx;
    /* 0x3C */ Mtx mCurMtx;
    /* 0x6C */ u8 mFlags;
    /* 0x6D */ u8 mbNeedsFullTransform;
    /* 0x6E */ u8 field_0x6E[0x74 - 0x6E];
    /* 0x74 */ u8 mMoveCounter;
    /* 0x75 */ u8 mWallCorrectPriority;
    /* 0x76 */ u8 field_0x76[0x78 - 0x76];
    /* 0x78 */ int mIgnorePlaneType;
    /* 0x7C */ cXyz mTransVel;
    /* 0x88 */ cBgW_TriElm* pm_tri;
    /* 0x8C */ cBgW_RwgElm* pm_rwg;
    /* 0x90 */ cXyz* pm_vtx_tbl;
    /* 0x94 */ cBgD_t* pm_bgd;
    /* 0x98 */ cBgW_BlkElm* pm_blk;
    /* 0x9C */ cBgW_GrpElm* pm_grp;
    /* 0xA0 */ cBgW_NodeTree* pm_node_tree;
    /* 0xA4 */ int m_rootGrpIdx;
};

bool cBgW_CheckBGround(f32 a1);
bool cBgW_CheckBRoof(f32 a1);
bool cBgW_CheckBWall(f32 a1);

#endif /* C_BG_W_H */
