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

class dBgW : public cBgW {
public:
    enum PushPullLabel {
        PP_UNK1_e = 0x01,
        PP_UNK2_e = 0x02,
        PP_UNK4_e = 0x04,
        PP_UNK8_e = 0x08,
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

    virtual ~dBgW() {}
    virtual bool ChkPolyThrough(int, cBgS_PolyPassChk*);
    virtual bool ChkShdwDrawThrough(int, cBgS_PolyPassChk*);
    virtual bool ChkGrpThrough(int, cBgS_GrpPassChk*, int);
    virtual void CrrPos(cBgS_PolyInfo&, void*, bool, cXyz*, csXyz*, csXyz*);
    virtual void TransPos(cBgS_PolyInfo&, void*, bool, cXyz*, csXyz*, csXyz*);
    virtual void MatrixCrrPos(cBgS_PolyInfo&, void*, bool, cXyz*, csXyz*, csXyz*);

    void SetCrrFunc(dBgW_CrrFunc func) { m_crr_func = func; }
    void SetRideCallback(dBgW_RideCallBack func) { mpRideCb = func; }
    void SetPushPullCallback(dBgW_PPCallBack func) { mpPushPullCb = func; }

    /* 0xA8 */ dBgW_CrrFunc m_crr_func;
    /* 0xAC */ s16 mOldRotY;
    /* 0xAE */ s16 mRotYDelta;
    /* 0xB0 */ dBgW_RideCallBack mpRideCb;
    /* 0xB4 */ dBgW_PPCallBack mpPushPullCb;
    /* 0xB8 */ u16 mRoomNo;
    /* 0xBA */ u8 mFlag;
    /* 0xBB */ u8 mRoomNo2;
};  // Size: 0xBC

dBgW* dBgW_NewSet(cBgD_t*, unsigned long, float(*)[3][4]);

#endif /* D_BG_W_H */
