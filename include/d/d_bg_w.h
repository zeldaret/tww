#ifndef D_BG_W_H
#define D_BG_W_H

#include "SSystem/SComponent/c_bg_w.h"
#include "SSystem/SComponent/c_sxyz.h"

class dBgS_Acch;
class cM3dGPla;
class dBgS_RoofChk;
class dBgS_SplGrpChk;
class dBgS_SphChk;
class cM3dGTri;
class dBgS_CrrPos;
class cBgS_PolyInfo;

class dBgW;
typedef void (*dBgW_CrrFunc)(dBgW*, void*, cBgS_PolyInfo&, bool, cXyz*, csXyz*, csXyz*);

class dBgW : public cBgW {
public:
    enum PushPullLabel {};

    dBgW();

    void Move();
    void positionWallCorrect(dBgS_Acch*, f32, cM3dGPla&, cXyz*, f32);
    void RwgWallCorrect(dBgS_Acch*, u16);
    void WallCorrectRp(dBgS_Acch*, int);
    void WallCorrectGrpRp(dBgS_Acch*, int, int);
    void RwgRoofChk(u16, dBgS_RoofChk*);
    void RoofChkRp(dBgS_RoofChk*, int);
    void RoofChkGrpRp(dBgS_RoofChk*, int, int);
    void RwgSplGrpChk(u16, dBgS_SplGrpChk*);
    void SplGrpChkRp(dBgS_SplGrpChk*, int);
    void SplGrpChkGrpRp(dBgS_SplGrpChk*, int, int);
    void RwgSphChk(u16, dBgS_SphChk*, void*);
    void SphChkRp(dBgS_SphChk*, void*, int);
    void SphChkGrpRp(dBgS_SphChk*, void*, int, int);
    void positionWallCrrPos(cM3dGTri&, dBgS_CrrPos*, cXyz*, f32, f32);
    void RwgWallCrrPos(u16, dBgS_CrrPos*);
    void WallCrrPosRp(dBgS_CrrPos*, int);
    void WallCrrPosGrpRp(dBgS_CrrPos*, int, int);
    void WallCrrPos(dBgS_CrrPos*);
    void ChangeAttributeCodeByPathPntNo(int, u32);

    virtual ~dBgW() {}
    virtual void ChkPolyThrough(int, cBgS_PolyPassChk*);
    virtual void ChkShdwDrawThrough(int, cBgS_PolyPassChk*);
    virtual bool ChkGrpThrough(int, cBgS_GrpPassChk*, int);
    virtual void CrrPos(cBgS_PolyInfo&, void*, bool, cXyz*, csXyz*, csXyz*);
    virtual void TransPos(cBgS_PolyInfo&, void*, bool, cXyz*, csXyz*, csXyz*);
    virtual void MatrixCrrPos(cBgS_PolyInfo&, void*, bool, cXyz*, csXyz*, csXyz*);

    void SetCrrFunc(dBgW_CrrFunc func) { m_crr_func = func; }

    /* 0xA8 */ dBgW_CrrFunc m_crr_func;
    /* 0xAC */ s16 mOldRotY;
    /* 0xAE */ s16 mRotYDelta;
    /* 0xB0 */ void* mpRideCb;
    /* 0xB4 */ void* mpPushPullCb;
    /* 0xB8 */ s16 mRoomNo;
    /* 0xBA */ u8 mFlag;
    /* 0xBB */ u8 mRoomNo2;
};

#endif /* D_BG_W_H */