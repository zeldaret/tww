#ifndef D_CAM_PARAM_H
#define D_CAM_PARAM_H

#include "dolphin/types.h"
#include "SSystem/SComponent/c_angle.h"

enum dCamStyle_e {
    dCamStyle_NONE_e = -1,
    /* 0x00 */ dCamStyle_NN00_e,
    /* 0x01 */ dCamStyle_FN08_e,
    /* 0x02 */ dCamStyle_PN05_e,
    /* 0x03 */ dCamStyle_PN12_e,
    /* 0x04 */ dCamStyle_EN00_e,
    /* 0x05 */ dCamStyle_FN12_e,
    /* 0x06 */ dCamStyle_TT01_e,
    /* 0x07 */ dCamStyle_TT02_e,
    /* 0x08 */ dCamStyle_TT03_e,
    /* 0x09 */ dCamStyle_LA03_e,
    /* 0x0A */ dCamStyle_LP01_e,
    /* 0x0B */ dCamStyle_LA02_e,
    /* 0x0C */ dCamStyle_FN13_e,
    /* 0x0D */ dCamStyle_LH01_e,
    /* 0x0E */ dCamStyle_LH02_e,
    /* 0x0F */ dCamStyle_LB02_e,
    /* 0x10 */ dCamStyle_LP02_e,
    /* 0x11 */ dCamStyle_LP03_e,
    /* 0x12 */ dCamStyle_LP04_e,
    /* 0x13 */ dCamStyle_CC01_e,
    /* 0x14 */ dCamStyle_CC02_e,
    /* 0x15 */ dCamStyle_LL06_e,
    /* 0x16 */ dCamStyle_LL08_e,
    /* 0x17 */ dCamStyle_LL07_e,
    /* 0x18 */ dCamStyle_LP10_e,
    /* 0x19 */ dCamStyle_SN15_e,
    /* 0x1A */ dCamStyle_BW07_e,
    /* 0x1B */ dCamStyle_FN18_e,
    /* 0x1C */ dCamStyle_JN05_e,
    /* 0x1D */ dCamStyle_XN06_e,
    /* 0x1E */ dCamStyle_LB01_e,
    /* 0x1F */ dCamStyle_LA01_e,
    /* 0x20 */ dCamStyle_BP07_e,
    /* 0x21 */ dCamStyle_LW02_e,
    /* 0x22 */ dCamStyle_HP16_e,
    /* 0x23 */ dCamStyle_HN16_e,
    /* 0x24 */ dCamStyle_BN07_e,
    /* 0x25 */ dCamStyle_LP05_e,
    /* 0x26 */ dCamStyle_LP06_e,
    /* 0x27 */ dCamStyle_HN18_e,
    /* 0x28 */ dCamStyle_FN25_e,
    /* 0x29 */ dCamStyle_BP08_e,
    /* 0x2A */ dCamStyle_BN08_e,
    /* 0x2B */ dCamStyle_FN29_e,
    /* 0x2C */ dCamStyle_SX01_e,
    /* 0x2D */ dCamStyle_SY01_e,
    /* 0x2E */ dCamStyle_SX02_e,
    /* 0x2F */ dCamStyle_MM06_e,
    /* 0x30 */ dCamStyle_MM05_e,
    /* 0x31 */ dCamStyle_MM09_e,
    /* 0x32 */ dCamStyle_MM04_e,
    /* 0x33 */ dCamStyle_LN17_e,
    /* 0x34 */ dCamStyle_QN07_e,
    /* 0x35 */ dCamStyle_LE01_e,
    /* 0x36 */ dCamStyle_LN01_e,
    /* 0x37 */ dCamStyle_LW01_e,
    /* 0x38 */ dCamStyle_GN01_e,
    /* 0x39 */ dCamStyle_MM01_e,
#if VERSION <= VERSION_JPN
    dCamStyle_MM03_e,
#endif
    /* Value comments below are for USA/PAL */
    /* 0x3A */ dCamStyle_MM02_e,
    /* 0x3B */ dCamStyle_MM10_e,
    /* 0x3C */ dCamStyle_MM08_e,
    /* 0x3D */ dCamStyle_MM83_e,
    /* 0x3E */ dCamStyle_FP01_e,
    /* 0x3F */ dCamStyle_ZZ00_e,
    /* 0x40 */ dCamStyle_PN13_e,
    /* 0x41 */ dCamStyle_FN82_e,
    /* 0x42 */ dCamStyle_IN01_e,
    /* 0x43 */ dCamStyle_IN02_e,
    /* 0x44 */ dCamStyle_MM82_e,
    /* 0x45 */ dCamStyle_LL11_e,
    /* 0x46 */ dCamStyle_LL01_e,
    /* 0x47 */ dCamStyle_LL02_e,
    /* 0x48 */ dCamStyle_LL03_e,
    /* 0x49 */ dCamStyle_LL04_e,
    /* 0x4A */ dCamStyle_LL05_e,
    /* 0x4B */ dCamStyle_LL10_e,
    /* 0x4C */ dCamStyle_LL09_e,
    /* 0x4D */ dCamStyle_LL12_e,
    /* 0x4E */ dCamStyle_LL13_e,
    /* 0x4F */ dCamStyle_LL14_e,
    /* 0x50 */ dCamStyle_LL15_e,
    /* 0x51 */ dCamStyle_LL16_e,
    /* 0x52 */ dCamStyle_LL82_e,
    /* 0x53 */ dCamStyle_FN01_e,
    /* 0x54 */ dCamStyle_FN02_e,
    /* 0x55 */ dCamStyle_FN03_e,
    /* 0x56 */ dCamStyle_FN04_e,
    /* 0x57 */ dCamStyle_FN06_e,
    /* 0x58 */ dCamStyle_FN09_e,
    /* 0x59 */ dCamStyle_FN07_e,
    /* 0x5A */ dCamStyle_FN10_e,
    /* 0x5B */ dCamStyle_FN14_e,
    /* 0x5C */ dCamStyle_FN15_e,
    /* 0x5D */ dCamStyle_FN17_e,
    /* 0x5E */ dCamStyle_FN20_e,
    /* 0x5F */ dCamStyle_FN21_e,
    /* 0x60 */ dCamStyle_FN22_e,
    /* 0x61 */ dCamStyle_FN23_e,
    /* 0x62 */ dCamStyle_FN24_e,
    /* 0x63 */ dCamStyle_FN26_e,
    /* 0x64 */ dCamStyle_FN27_e,
    /* 0x65 */ dCamStyle_FN28_e,
    /* 0x66 */ dCamStyle_FN30_e,
    /* 0x67 */ dCamStyle_FN31_e,
    /* 0x68 */ dCamStyle_FN32_e,
    /* 0x69 */ dCamStyle_FN33_e,
    /* 0x6A */ dCamStyle_FN34_e,
    /* 0x6B */ dCamStyle_FN35_e,
    /* 0x6C */ dCamStyle_LL17_e,
    /* 0x6D */ dCamStyle_FN37_e,
#if VERSION <= VERSION_JPN
    dCamStyle_FN38_e,
#endif
    /* 0x6E */ dCamStyle_BE08_e,
    /* 0x6F */ dCamStyle_BE07_e,
    /* 0x70 */ dCamStyle_TT04_e,
    /* 0x71 */ dCamStyle_FP38_e,
    /* 0x72 */ dCamStyle_FN39_e,
    /* 0x73 */ dCamStyle_MM16_e,
    /* 0x74 */ dCamStyle_MM14_e,
    /* 0x75 */ dCamStyle_MM15_e,
    /* 0x76 */ dCamStyle_MM07_e,
    /* 0x77 */ dCamStyle_FN81_e,
    /* 0x78 */ dCamStyle_FN40_e,
    /* 0x79 */ dCamStyle_FN41_e,
    /* 0x7A */ dCamStyle_FN19_e,
    /* 0x7B */ dCamStyle_LL81_e,
    /* 0x7C */ dCamStyle_DD01_e,
    /* 0x7D */ dCamStyle_MM19_e,
    /* 0x7E */ dCamStyle_DD02_e,
    /* 0x7F */ dCamStyle_FN42_e,
    /* 0x80 */ dCamStyle_IN03_e,
    /* 0x81 */ dCamStyle_FN43_e,
    /* 0x82 */ dCamStyle_FN11_e,
    /* 0x83 */ dCamStyle_MM21_e,
    /* 0x84 */ dCamStyle_MM20_e,
    /* 0x85 */ dCamStyle_FN05_e,
    /* 0x86 */ dCamStyle_FN36_e,
    /* 0x87 */ dCamStyle_MM81_e,
    /* 0x88 */ dCamStyle_SS01_e,
    /* 0x89 */ dCamStyle_LL18_e,
    /* 0x8A */ dCamStyle_DD04_e,
    /* 0x8B */ dCamStyle_MM22_e,
    /* 0x8C */ dCamStyle_MM18_e,
    /* 0x8D */ dCamStyle_MM17_e,
#if VERSION > VERSION_JPN
    /* 0x8E */ dCamStyle_MM03_e,
    /* 0x8F */ dCamStyle_MM23_e,
    /* 0x90 */ dCamStyle_FN38_e,
#endif
};

// Array indexes, do not change values
enum dCamStyleParam_e {
    /* 0x00 */ dCamStyleParam_UNK0 = 0,
    /* 0x01 */ dCamStyleParam_UNK1 = 1,
    /* 0x02 */ dCamStyleParam_UNK2 = 2,
    /* 0x03 */ dCamStyleParam_UNK3 = 3,
    /* 0x04 */ dCamStyleParam_UNK4 = 4,
    /* 0x05 */ dCamStyleParam_CENTER_HEIGHT_BASE = 5,
    /* 0x06 */ dCamStyleParam_CENTER_HEIGHT_UPPER = 6,
    /* 0x07 */ dCamStyleParam_CENTER_HEIGHT_LOWER = 7,
    /* 0x08 */ dCamStyleParam_LOCKON_CENTER_HEIGHT_MIN = 8,
    /* 0x09 */ dCamStyleParam_LOCKON_CENTER_HEIGHT_MAX = 9,
    /* 0x0A */ dCamStyleParam_UNK10 = 10,
    /* 0x0B */ dCamStyleParam_UNK11 = 11,
    /* 0x0C */ dCamStyleParam_UNK12 = 12,
    /* 0x0D */ dCamStyleParam_UNK13 = 13,
    /* 0x0E */ dCamStyleParam_UNK14 = 14,
    /* 0x0F */ dCamStyleParam_UNK15 = 15,
    /* 0x10 */ dCamStyleParam_UNK16 = 16,
    /* 0x11 */ dCamStyleParam_UNK17 = 17,
    /* 0x12 */ dCamStyleParam_LOCKON_LATITUDE_MIN = 18,
    /* 0x13 */ dCamStyleParam_LOCKON_LATITUDE_MAX = 19,
    /* 0x14 */ dCamStyleParam_UNK20 = 20,
    /* 0x15 */ dCamStyleParam_UNK21 = 21,
    /* 0x16 */ dCamStyleParam_UNK22 = 22,
    /* 0x17 */ dCamStyleParam_LOCKON_LONGITUDE_MIN = 23,
    /* 0x18 */ dCamStyleParam_LOCKON_LONGITUDE_MAX = 24,
    /* 0x19 */ dCamStyleParam_FOVY_BASE = 25,
    /* 0x1A */ dCamStyleParam_FOVY_UPPER = 26,
    /* 0x1B */ dCamStyleParam_FOVY_LOWER = 27,
    /* 0x1C */ dCamStyleParam_LOCKON_FOVY_MIN = 28,
    /* 0x1D */ dCamStyleParam_LOCKON_FOVY_MAX = 29,
};

enum dCamParamFlag_e {
    dCamPrmFlg_UNK001 = 0x001,
    dCamPrmFlg_UNK002 = 0x002,
    dCamPrmFlg_UNK004 = 0x004,
    dCamPrmFlg_UNK010 = 0x010,
    dCamPrmFlg_UNK020 = 0x020,
    dCamPrmFlg_UNK040 = 0x040,
    dCamPrmFlg_UNK080 = 0x080,
    dCamPrmFlg_UNK100 = 0x100,
    dCamPrmFlg_UNK200 = 0x200,
    dCamPrmFlg_UNK400 = 0x400,
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
