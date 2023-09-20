#ifndef C_BG_W_H
#define C_BG_W_H

#include "SSystem/SComponent/c_xyz.h"
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

    u16 GetId() const { return m_id; }
    bool ChkUsed() const {
        if (m_id >= 0 && m_id < 0x100) {
            return true;
        }
        return false;
    }
};

class cBgW_TriElm;
class cBgW_RwgElm;
class cBgW_BlkElm;
class cBgW_GrpElm;
class cBgW_NodeTree;
class cBgD_t;
class cBgS_LinChk;
class cBgS_GndChk;
class cBgS_ShdwDraw;
class cBgS_PolyPassChk;
class cBgS_GrpPassChk;

class cBgW : public cBgW_BgId {
public:
    enum Flags_e {
        MOVE_BG_e = 0x1,
        NO_VTX_TBL_e = 0x10,
        GLOBAL_e = 0x20,
        LOCK_e = 0x80,
    };

    cBgW();

    void FreeArea();
    void GlobalVtx();
    void SetVtx();
    
    void SetTri();
    void BlckConnect(u16*, int*, int);
    void MakeBlckTransMinMax(cXyz*, cXyz*);
    void MakeBlckMinMax(int, cXyz*, cXyz*);
    void MakeBlckBnd(int, cXyz*, cXyz*);
    void MakeNodeTreeRp(int);
    void MakeNodeTreeGrpRp(int);
    void MakeNodeTree();
    void ChkMemoryError();
    bool Set(cBgD_t*, u32, f32(*)[3][4]);
    void RwgLineCheck(u16, cBgS_LinChk*);
    void LineCheckRp(cBgS_LinChk*, int);
    void LineCheckGrpRp(cBgS_LinChk*, int, int);
    void RwgGroundCheckCommon(f32, u16, cBgS_GndChk*);
    void RwgGroundCheckGnd(u16, cBgS_GndChk*);
    void RwgGroundCheckWall(u16, cBgS_GndChk*);
    void GroundCrossRp(cBgS_GndChk*, int);
    void GroundCrossGrpRp(cBgS_GndChk*, int, int);
    void CopyOldMtx();
    void Move();
    void RwgShdwDraw(int, cBgS_ShdwDraw*);
    void ShdwDrawRp(cBgS_ShdwDraw*, int);
    void ShdwDrawGrpRp(cBgS_ShdwDraw*, int);
    void GetTrans(cXyz*) const;
    void GetTriPnt(int, cXyz*, cXyz*, cXyz*) const;
    void GetTopUnder(f32*, f32*) const;

    virtual ~cBgW();
    virtual void GetGrpToRoomIndex(int) const;
    virtual void CalcPlane();
    virtual void ClassifyPlane();
    virtual void ChkPolyThrough(int, cBgS_PolyPassChk*);
    virtual void ChkShdwDrawThrough(int, cBgS_PolyPassChk*);
    virtual bool ChkGrpThrough(int, cBgS_GrpPassChk*, int);

    /* 0x08 */ Mtx* mpModelMtx;
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
    /* 0x88 */ cBgW_TriElm* mpTriElm;
    /* 0x8C */ cBgW_RwgElm* mpRwg;
    /* 0x90 */ cXyz* mpVtxTbl;
    /* 0x94 */ cBgD_t* mpBgDt;
    /* 0x98 */ cBgW_BlkElm* mpBlk;
    /* 0x9C */ cBgW_GrpElm* mpGrp;
    /* 0xA0 */ cBgW_NodeTree* mpNodeTree;
    /* 0xA4 */ int mRootGrpIdx;
};

bool cBgW_CheckBGround(f32 a1);
bool cBgW_CheckBRoof(f32 a1);
bool cBgW_CheckBWall(f32 a1);

#endif /* C_BG_W_H */
