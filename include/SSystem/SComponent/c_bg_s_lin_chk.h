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
    void Set2(cXyz*, cXyz*, unsigned int);
    void PreCalc();
    void GetCross();

    virtual ~cBgS_LinChk() {}

    void ClrHit() { mFlag &= ~0x10; }
    void SetHit() { mFlag |= 0x10; }
    u32 ChkHit() const { return mFlag & 0x10; }
    void ClrSttsRoofOff() { mFlag &= ~0x20000000; }
    void SetCross(const cXyz& pos) { mLin.SetEnd(pos); }
    cXyz& i_GetCross() { return mLin.GetEnd(); }
    cM3dGLin* GetLinP() { return &mLin; }
    void OnBackFlag() { mBackFlag = true; }
    void OffBackFlag() { mBackFlag = false; }
    bool ChkBackFlag() const { return mBackFlag; }
    bool ChkFrontFlag() const { return mFrontFlag; }
    bool GetPreWallChk() const { return mPreWallChk; }
    bool GetPreGroundChk() const { return mPreGroundChk; }
    bool GetPreRoofChk() const { return mPreRoofChk; }
};  // Size: 0x58

#endif /* C_BG_S_LIN_CHK_H */
