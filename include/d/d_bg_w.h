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
class fopAc_ac_c;
class dBgS_CaptPoly;
typedef struct _GXColor GXColor;

class dBgW : public cBgW {
public:
    enum PushPullLabel {
        PPLABEL_NONE = 0x00,
        PPLABEL_PUSH = 0x01,
        PPLABEL_PULL = 0x02,
        PPLABEL_UNK4 = 0x04,
        PPLABEL_HEAVY = 0x08,
    };
    
    typedef void (*dBgW_CrrFunc)(dBgW*, void*, cBgS_PolyInfo&, bool, cXyz*, csXyz*, csXyz*);
    typedef void (*dBgW_RideCallBack)(dBgW*, fopAc_ac_c*, fopAc_ac_c*);
    typedef fopAc_ac_c* (*dBgW_PPCallBack)(fopAc_ac_c*, fopAc_ac_c*, s16, dBgW::PushPullLabel);

    dBgW();

    void Move();
    void positionWallCorrect(dBgS_Acch*, f32, cM3dGPla&, cXyz*, f32);
    bool RwgWallCorrect(dBgS_Acch*, u16);
    bool WallCorrectRp(dBgS_Acch*, int);
    bool WallCorrectGrpRp(dBgS_Acch*, int, int);
    bool RwgRoofChk(u16, dBgS_RoofChk*);
    bool RoofChkRp(dBgS_RoofChk*, int);
    bool RoofChkGrpRp(dBgS_RoofChk*, int, int);
    bool RwgSplGrpChk(u16, dBgS_SplGrpChk*);
    bool SplGrpChkRp(dBgS_SplGrpChk*, int);
    bool SplGrpChkGrpRp(dBgS_SplGrpChk*, int, int);
    bool RwgSphChk(u16, dBgS_SphChk*, void*);
    bool SphChkRp(dBgS_SphChk*, void*, int);
    bool SphChkGrpRp(dBgS_SphChk*, void*, int, int);
    void positionWallCrrPos(cM3dGTri&, dBgS_CrrPos*, cXyz*, f32, f32);
    bool RwgWallCrrPos(u16, dBgS_CrrPos*);
    bool WallCrrPosRp(dBgS_CrrPos*, int);
    bool WallCrrPosGrpRp(dBgS_CrrPos*, int, int);
    bool WallCrrPos(dBgS_CrrPos*);
    void ChangeAttributeCodeByPathPntNo(int, u32);

    void dummyfunc(); // for assert. TODO remove later

    virtual ~dBgW() {}
    virtual bool ChkPolyThrough(int, cBgS_PolyPassChk*);
    virtual bool ChkShdwDrawThrough(int, cBgS_PolyPassChk*);
    virtual bool ChkGrpThrough(int, cBgS_GrpPassChk*, int);
    virtual void CrrPos(cBgS_PolyInfo&, void*, bool, cXyz*, csXyz*, csXyz*);
    virtual void TransPos(cBgS_PolyInfo&, void*, bool, cXyz*, csXyz*, csXyz*);
    virtual void MatrixCrrPos(cBgS_PolyInfo& poly, void* user, bool accept, cXyz* pos, csXyz* angle, csXyz* shape_angle) {
        CrrPos(poly, user, accept, pos, angle, shape_angle);
    }

    void SetCrrFunc(dBgW_CrrFunc func) { m_crr_func = func; }
    void SetRideCallback(dBgW_RideCallBack func) { mpRideCb = func; }
    void SetPushPullCallback(dBgW_PPCallBack func) { mpPushPullCb = func; }
    dBgW_RideCallBack GetRideCallback() { return mpRideCb; }
    dBgW_PPCallBack GetPushPullCallback() { return mpPushPullCb; }

    u16 GetRoomId() { return mRoomId; }
    u8 GetGrpRoomInf() { return mGrpRoomInf; }
    void SetRoomId(u16 roomNo) { mRoomId = roomNo; }
    void SetGrpRoomInf(int roomNo) { mGrpRoomInf = roomNo; }
    void ClrRoomId() { mRoomId = -1; }
    void ClrGrpRoomInf() { mGrpRoomInf = -1; }

    u32 ChkMoveFlag() { return mFlag & 0x01; }
    void OnMoveFlag() { mFlag |= 0x01; }
    void OffMoveFlag() { mFlag &= ~0x01; }

    void CalcDiffShapeAngleY(s16 shape_angle) {
        mRotYDelta = shape_angle - mOldRotY;
        mOldRotY = shape_angle;
    }
    s16 GetDiffShapeAngleY() { return mRotYDelta; }
    void SetOldShapeAngleY(s16 angle) { mOldRotY = angle; }

    bool WallCorrect(dBgS_Acch* acch) { return WallCorrectGrpRp(acch, m_rootGrpIdx, 1); }
    bool RoofChk(dBgS_RoofChk* chk) { return RoofChkGrpRp(chk, m_rootGrpIdx, 1); }
    bool SplGrpChk(dBgS_SplGrpChk* chk) { return SplGrpChkGrpRp(chk, m_rootGrpIdx, 1); }
    bool SphChk(dBgS_SphChk* chk, void* i_data) { return SphChkGrpRp(chk, i_data, m_rootGrpIdx, 1); }

    u32 GetMaskPolyInfo0(int poly_index, u32 mask, u32 shift) {
        return (GetPolyInf0(GetPolyInfId(poly_index)) >> shift) & mask;
    }
    u32 GetMaskPolyInfo3_NoShift(int poly_index, u32 mask) {
        return GetPolyInf3(GetPolyInfId(poly_index)) & mask;
    }
    u32 GetShdwThrough(int poly_index) { return GetMaskPolyInfo0(poly_index, 0x01, 27); }
    u32 GetPolyObjThrough(int poly_index) { return GetMaskPolyInfo3_NoShift(poly_index, 0x02); }
    u32 GetPolyCamThrough(int poly_index) { return GetMaskPolyInfo3_NoShift(poly_index, 0x01); }
    u32 GetPolyLinkThrough(int poly_index) { return GetMaskPolyInfo3_NoShift(poly_index, 0x04); }
    u32 GetPolyArrowThrough(int poly_index) { return GetMaskPolyInfo3_NoShift(poly_index, 0x08); }
    u32 GetPolyBombThrough(int poly_index) { return GetMaskPolyInfo3_NoShift(poly_index, 0x20); }
    u32 GetPolyBoomerangThrough(int poly_index) { return GetMaskPolyInfo3_NoShift(poly_index, 0x40); }
    u32 GetPolyRopeThrough(int poly_index) { return GetMaskPolyInfo3_NoShift(poly_index, 0x80); }
    u32 GetPolyHSStick(int poly_index) { return GetMaskPolyInfo3_NoShift(poly_index, 0x10); }
    
    // Debug-only funcs
    void DebugDraw() {}
    void DrawBox() {}
    void DrawPoly(cBgS_PolyInfo&, GXColor&) {}
    void CaptPoly(dBgS_CaptPoly&) {}
    void CaptPolyGrpRp(dBgS_CaptPoly&, int) {}
    void CaptPolyRp(dBgS_CaptPoly&, int) {}
    void RwgCaptPoly(int, dBgS_CaptPoly&) {}

    /* 0xA8 */ dBgW_CrrFunc m_crr_func;
    /* 0xAC */ s16 mOldRotY;
    /* 0xAE */ s16 mRotYDelta;
    /* 0xB0 */ dBgW_RideCallBack mpRideCb;
    /* 0xB4 */ dBgW_PPCallBack mpPushPullCb;
    /* 0xB8 */ u16 mRoomId;
    /* 0xBA */ u8 mFlag;
    /* 0xBB */ u8 mGrpRoomInf;
};  // Size: 0xBC

dBgW* dBgW_NewSet(cBgD_t*, u32, Mtx*);

#endif /* D_BG_W_H */
