#ifndef C_BG_S_LIN_CHK_H
#define C_BG_S_LIN_CHK_H

#include "SSystem/SComponent/c_bg_s_chk.h"
#include "SSystem/SComponent/c_bg_s_poly_info.h"
#include "SSystem/SComponent/c_m3d_g_lin.h"
#include "dolphin/types.h"

class cBgS_LinChk : public cBgS_Chk, public cBgS_PolyInfo {
public:
    /* 0x024 */ cM3dGLin mLin;
    /* 0x040 */ cXyz field_0x40;
    /* 0x04C */ u32 mFlag;
    /* 0x050 */ bool mPreWallChk;
    /* 0x051 */ bool mPreGroundChk;
    /* 0x052 */ bool mPreRoofChk;
    /* 0x053 */ bool mFrontFlag;
    /* 0x054 */ bool mBackFlag;

public:
    cBgS_LinChk() { ct(); }
    void ct();
    void Set2(cXyz* pStart, cXyz* pEnd, uint actorPid);

    virtual ~cBgS_LinChk() {}

    void SetHit() { mFlag |= 0x10; }
    void ClrHit() { mFlag &= ~0x10; }
    bool ChkHit() { return mFlag & 0x10; }
    void SetSttsWallOff() { mFlag |= 0x40000000; }
    void ClrSttsWallOff() { mFlag &= ~0x40000000; }
    bool ChkSttsWallOff() { return mFlag & 0x40000000; }
    void SetSttsGroundOff() { mFlag |= 0x80000000; }
    void ClrSttsGroundOff() { mFlag &= ~0x80000000; }
    bool ChkSttsGroundOff() { return mFlag & 0x80000000; }
    void SetSttsRoofOff() { mFlag |= 0x20000000; }
    void ClrSttsRoofOff() { mFlag &= ~0x20000000; }
    bool ChkSttsRoofOff() { return mFlag & 0x20000000; }

    void SetCross(cXyz& pos) { mLin.SetEnd(pos); }
    cXyz& GetCross() { return mLin.GetEnd(); }
    cXyz* GetCrossP() { return mLin.GetEndP(); }
    cM3dGLin* GetLinP() { return &mLin; }

    void OnFrontFlag() { mFrontFlag = true; }
    void OffFrontFlag() { mFrontFlag = false; }
    bool ChkFrontFlag() { return mFrontFlag; }
    void OnBackFlag() { mBackFlag = true; }
    void OffBackFlag() { mBackFlag = false; }
    bool ChkBackFlag() { return mBackFlag; }
    bool GetPreWallChk() const { return mPreWallChk; }
    bool GetPreGroundChk() const { return mPreGroundChk; }
    bool GetPreRoofChk() const { return mPreRoofChk; }
    void PreCalc() {
        mPreWallChk = !ChkSttsWallOff();
        mPreGroundChk = !ChkSttsGroundOff();
        mPreRoofChk = !ChkSttsRoofOff();
    }
    void ClearCheckIndex() {} // TODO
};  // Size: 0x58

#endif /* C_BG_S_LIN_CHK_H */
