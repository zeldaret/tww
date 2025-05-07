#ifndef D_CAM_PARAM_H
#define D_CAM_PARAM_H

#include "dolphin/types.h"
#include "SSystem/SComponent/c_angle.h"

// Array indexes, do not change values
enum dCamStyleParam_e {
    dCamStyleParam_UNK0 = 0,
    dCamStyleParam_UNK1 = 1,
    dCamStyleParam_UNK2 = 2,
    dCamStyleParam_UNK3 = 3,
    dCamStyleParam_UNK4 = 4,
    dCamStyleParam_CENTER_HEIGHT_BASE = 5,
    dCamStyleParam_CENTER_HEIGHT_UPPER = 6,
    dCamStyleParam_CENTER_HEIGHT_LOWER = 7,
    dCamStyleParam_LOCKON_CENTER_HEIGHT_MIN = 8,
    dCamStyleParam_LOCKON_CENTER_HEIGHT_MAX = 9,
    dCamStyleParam_UNK10 = 10,
    dCamStyleParam_UNK11 = 11,
    dCamStyleParam_UNK12 = 12,
    dCamStyleParam_UNK13 = 13,
    dCamStyleParam_UNK14 = 14,
    dCamStyleParam_UNK15 = 15,
    dCamStyleParam_UNK16 = 16,
    dCamStyleParam_UNK17 = 17,
    dCamStyleParam_LOCKON_LATITUDE_MIN = 18,
    dCamStyleParam_LOCKON_LATITUDE_MAX = 19,
    dCamStyleParam_UNK20 = 20,
    dCamStyleParam_UNK21 = 21,
    dCamStyleParam_UNK22 = 22,
    dCamStyleParam_LOCKON_LONGITUDE_MIN = 23,
    dCamStyleParam_LOCKON_LONGITUDE_MAX = 24,
    dCamStyleParam_FOVY_BASE = 25,
    dCamStyleParam_FOVY_UPPER = 26,
    dCamStyleParam_FOVY_LOWER = 27,
    dCamStyleParam_LOCKON_FOVY_MIN = 28,
    dCamStyleParam_LOCKON_FOVY_MAX = 29,
};

enum dCamParamFlag_e {
    dCamParam_UNK001 = 0x001,
    dCamParam_UNK002 = 0x002,
    dCamParam_UNK004 = 0x004,
    dCamParam_UNK010 = 0x010,
    dCamParam_UNK020 = 0x020,
    dCamParam_UNK040 = 0x040,
    dCamParam_UNK080 = 0x080,
    dCamParam_UNK100 = 0x100,
    dCamParam_UNK200 = 0x200,
    dCamParam_UNK400 = 0x400,
};

struct dCamera__Style {
    /* 0x00 */ u32 m00;
    /* 0x04 */ int engineIdx;
    /* 0x08 */ f32 styleParam[30];
    /* 0x80 */ u16 flag;
};  // Size: 0x84

class dCstick_c {
public:
    /* 0x00 */ f32 m00;
    /* 0x04 */ f32 m04;
    /* 0x08 */ u32 m08;
    /* 0x0C */ u8 m0C[0x10 - 0x0C];
public:
    dCstick_c();
    virtual ~dCstick_c() {}

    s32 Shift(u32);
};

class dCamBGChk_c {
public:
    dCamBGChk_c();

    // copied these from TP's implementation, may not be correct
    f32 WallUpDistance() { return mWallUpDistance; }
    f32 FwdDistance(s32 param_0) { return mChkInfo[param_0].mDistance; }
    s16 FwdChkAngle(s32 param_0) { return cAngle::d2s(mChkInfo[param_0].mChkAngle); }
    f32 FwdWeightH(s32 param_0) { return mChkInfo[param_0].mWeightH; }
    f32 FwdWeightL(s32 param_0) { return mChkInfo[param_0].mWeightL; }
    f32 FwdBackMargin() { return mFwdBackMargin; }
    f32 FwdCushion() { return mFwdCushion; }
    f32 GazeBackMargin() { return mGazeBackMargin; }
    f32 WallCushion() { return mWallCushion; }
    f32 WallBackCushion() { return mWallBackCushion; }
    f32 CornerCushion() { return mCornerCushion; }
    f32 CornerAngleMax() { return mCornerAngleMax; }
    f32 FloorMargin() { return mFloorMargin; }

    // name is a guess for now
    struct ChkInfo {
        /* 0x0 */ f32 mDistance;
        /* 0x4 */ f32 mChkAngle;
        /* 0x8 */ f32 mWeightH;
        /* 0xC */ f32 mWeightL;
    };  // Size: 0x10

public:
    /* 0x00 */ f32 mFloorMargin;
    /* 0x04 */ ChkInfo mChkInfo[2];
    /* 0x24 */ f32 mFwdBackMargin;
    /* 0x28 */ f32 mFwdCushion;
    /* 0x2C */ f32 m2C;
    /* 0x30 */ f32 mGazeBackMargin;
    /* 0x34 */ f32 mCornerCushion;
    /* 0x38 */ f32 mWallCushion;
    /* 0x3C */ f32 mWallUpDistance;
    /* 0x40 */ f32 mWallBackCushion;
    /* 0x44 */ f32 mCornerAngleMax;
    /* 0x48 */ f32 m48;
    /* 0x4C */ f32 m4C;
    /* 0x50 */ f32 m50;
    /* 0x54 */ f32 m54;
    /* 0x58 */ f32 m58;
    /* 0x5C */ f32 m5C;
};

class dCamSetup_c {
public:
    /* 0x000 */ f32 mDrawNear;
    /* 0x004 */ f32 mDrawFar;
    /* 0x008 */ u16 mDebugFlags;
    /* 0x00A */ u16 mFlags2;
    /* 0x00C */ int m00C;
    /* 0x010 */ int mModeSwitchType;
    /* 0x014 */ void* mTypeTable;
    /* 0x018 */ int mTypeNum;
    /* 0x01C */ int mForceType;
    /* 0x020 */ f32 mCusCus;
    /* 0x024 */ f32 m024;
    /* 0x028 */ f32 m028;
    /* 0x02C */ f32 m02C;
    /* 0x030 */ f32 m030;
    /* 0x034 */ f32 m034;
    /* 0x038 */ f32 mBaseCushion;
    /* 0x03C */ f32 mJumpCushion;
    /* 0x040 */ f32 mParallelDist;
    /* 0x044 */ f32 m044;
    /* 0x048 */ f32 m048;
    /* 0x04C */ f32 mCurveWeight;
    /* 0x050 */ f32 m050;
    /* 0x054 */ f32 m054;
    /* 0x058 */ f32 m058;
    /* 0x05C */ f32 m05C;
    /* 0x060 */ f32 m060;
    /* 0x064 */ f32 mTrimVistaHeight;
    /* 0x068 */ f32 mTrimCineScopeHeight;
    /* 0x06C */ f32 m06C;
    /* 0x070 */ f32 mForceLockOffDist;
    /* 0x074 */ int mForceLockOffTimer;
    /* 0x078 */ f32 m078;
    /* 0x07C */ f32 m07C;
    /* 0x080 */ f32 m080;
    /* 0x084 */ f32 m084;
    /* 0x088 */ f32 mDMCValue;
    /* 0x08C */ f32 mDMCAngle;
    /* 0x090 */ f32 m090;
    /* 0x094 */ int m094;
    /* 0x098 */ f32 m098;
    /* 0x09C */ f32 m09C;
    /* 0x0A0 */ f32 m0A0;
    /* 0x0A4 */ f32 m0A4;
    /* 0x0A8 */ int m0A8;
    /* 0x0AC */ f32 mChargeLatitude;
    /* 0x0B0 */ int mChargeTimer;
    /* 0x0B4 */ f32 mChargeBRatio;
    /* 0x0B8 */ f32 mManualStartCThreshold;
    /* 0x0BC */ f32 mManualEndVal;
    /* 0x0C0 */ f32 m0C0;
    /* 0x0C4 */ f32 mLockonChangeCushion;
    /* 0x0C8 */ int mLockonChangeTimer;

public:
    dCamSetup_c();
    virtual ~dCamSetup_c();

    bool CheckLatitudeRange(s16*);
    f32 FanBank();
    f32 PlayerHideDist();

    bool CheckFlag2(u16 i_flag) { return (i_flag & mFlags2) != 0; }
    f32 ChargeBRatio() { return mChargeBRatio; }
    int ChargeTimer() { return mChargeTimer; }
    f32 ChargeLatitude() { return mChargeLatitude; }

    f32 ManualEndVal() { return mManualEndVal; }
    f32 CinemaScopeTrimHeight() { return mTrimCineScopeHeight; }
    f32 VistaTrimHeight() { return mTrimVistaHeight; }
    f32 ForceLockOffTimer() { return mForceLockOffTimer; }
    f32 ForceLockOffDist() { return mForceLockOffDist; }
    f32 LockonChangeCushion() { return mLockonChangeCushion; }
    int LockonChangeTimer() { return mLockonChangeTimer; }
    f32 Cushion4Base() { return mBaseCushion; }
    f32 Cushion4Jump() { return mJumpCushion; }
    f32 CusCus() { return mCusCus; }
    f32 ParallelDist() { return mParallelDist; }
    f32 CurveWeight() { return mCurveWeight; }
    f32 DMCAngle() { return mDMCAngle; }
    f32 DMCValue() { return mDMCValue; }

public:
    /* 0x0D0 */ dCstick_c mCstick;
    /* 0x0E4 */ dCamBGChk_c mBGChk;
};

class dCamParam_c {
public:
    /* 0x0 */ const dCamera__Style* mpStyle;
    /* 0x4 */ s32 mStyleIdx;

    static const dCamera__Style styles[];
    static const s32 style_num;

public:
    dCamParam_c(s32);
    virtual ~dCamParam_c();

    u16 Flag(s32 styleIdx, u16 mask) { return mask & styles[styleIdx].flag; }
    f32 Val(s32 styleIdx, int paramIdx) { return styles[styleIdx].styleParam[paramIdx]; }
    BOOL Change(s32);
    s32 SearchStyle(u32);
    f32 ratiof(f32, f32, f32, f32);
    BOOL DefaultRadius(f32*);
    f32 RadiusRatio(f32);
    f32 CenterHeight(f32);
    f32 Fovy(f32);
    s16 LockonLongitude(f32);
    s16 LockonLatitude(f32);
    f32 LockonFovy(f32);
    f32 LockonCenterHeight(f32);
    int Algorythmn(s32 i_style) { return styles[i_style].engineIdx; }
    int Algorythmn() { return mpStyle->engineIdx; }
    bool CheckFlag(u16 flag) { return mpStyle->flag & flag; }
};

class dCamMath {
public:
    static f32 rationalBezierRatio(f32, f32);
    static f32 customRBRatio(f32, f32);
    static f32 zoomFovy(f32, f32);
    static cXyz xyzRotateX(cXyz&, cSAngle);
    static cXyz xyzRotateY(cXyz&, cSAngle);
    static f32 xyzHorizontalDistance(cXyz&, cXyz&);
    static cXyz xyzProjPosOnYZ(cSAngle, cXyz&, cXyz&);
};

#endif /* D_CAM_PARAM_H */
