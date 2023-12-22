#ifndef D_CAM_PARAM_H
#define D_CAM_PARAM_H

#include "dolphin/types.h"
#include "SSystem/SComponent/c_angle.h"

struct dCamera__Style;

class dCstick_c {
public:
    /* 0x00 */ f32 m00;
    /* 0x04 */ f32 m04;
    /* 0x08 */ u32 m08;
    /* 0x0C */ u8 m0C[0x10 - 0x0C];
public:
    dCstick_c();
    virtual ~dCstick_c() {}

    void Shift(u32);
};

class dCamBGChk_c {
public:
    dCamBGChk_c();

public:
    /* 0x00 */ f32 m00;
    /* 0x04 */ f32 m04;
    /* 0x08 */ f32 m08;
    /* 0x0C */ f32 m0C;
    /* 0x10 */ f32 m10;
    /* 0x14 */ f32 m14;
    /* 0x18 */ f32 m18;
    /* 0x1C */ f32 m1C;
    /* 0x20 */ f32 m20;
    /* 0x24 */ f32 m24;
    /* 0x28 */ f32 m28;
    /* 0x2C */ f32 m2C;
    /* 0x30 */ f32 m30;
    /* 0x34 */ f32 m34;
    /* 0x38 */ f32 m38;
    /* 0x3C */ f32 m3C;
    /* 0x40 */ f32 m40;
    /* 0x44 */ f32 m44;
    /* 0x48 */ f32 m48;
    /* 0x4C */ f32 m4C;
    /* 0x50 */ f32 m50;
    /* 0x54 */ f32 m54;
    /* 0x58 */ f32 m58;
    /* 0x5C */ f32 m5C;
};

class dCamSetup_c {
public:
    /* 0x000 */ f32 m000;
    /* 0x004 */ f32 m004;
    /* 0x008 */ u16 m008;
    /* 0x00A */ u8 m00A[0x00C - 0x00A];
    /* 0x00C */ u32 m00C;
    /* 0x010 */ int m010;
    /* 0x014 */ u8 m014[0x01C - 0x014];
    /* 0x01C */ int m01C;
    /* 0x020 */ f32 m020;
    /* 0x024 */ f32 m024;
    /* 0x028 */ f32 m028;
    /* 0x02C */ f32 m02C;
    /* 0x030 */ f32 m030;
    /* 0x034 */ f32 m034;
    /* 0x038 */ f32 m038;
    /* 0x03C */ f32 m03C;
    /* 0x040 */ f32 m040;
    /* 0x044 */ f32 m044;
    /* 0x048 */ f32 m048;
    /* 0x04C */ f32 m04C;
    /* 0x050 */ f32 m050;
    /* 0x054 */ f32 m054;
    /* 0x058 */ f32 m058;
    /* 0x05C */ f32 m05C;
    /* 0x060 */ f32 m060;
    /* 0x064 */ f32 m064;
    /* 0x068 */ f32 m068;
    /* 0x06C */ f32 m06C;
    /* 0x070 */ f32 m070;
    /* 0x074 */ u32 m074;
    /* 0x078 */ f32 m078;
    /* 0x07C */ f32 m07C;
    /* 0x080 */ f32 m080;
    /* 0x084 */ f32 m084;
    /* 0x088 */ f32 m088;
    /* 0x08C */ f32 m08C;
    /* 0x090 */ u8 m090[0x094 - 0x090];
    /* 0x094 */ u32 m094;
    /* 0x098 */ f32 m098;
    /* 0x09C */ f32 m09C;
    /* 0x0A0 */ f32 m0A0;
    /* 0x0A4 */ f32 m0A4;
    /* 0x0A8 */ u32 m0A8;
    /* 0x0AC */ f32 m0AC;
    /* 0x0B0 */ u32 m0B0;
    /* 0x0B4 */ f32 m0B4;
    /* 0x0B8 */ f32 m0B8;
    /* 0x0BC */ f32 m0BC;
    /* 0x0C0 */ f32 m0C0;
    /* 0x0C4 */ f32 m0C4;
    /* 0x0C8 */ u32 m0C8;

public:
    dCamSetup_c();
    virtual ~dCamSetup_c();

    void CheckLatitudeRange(s16*);
    void FanBank();

public:
    /* 0x0D0 */ dCstick_c mCstick;
    /* 0x0E4 */ dCamBGChk_c mBGChk;
};

class dCamParam_c {
public:
    /* 0x0 */ dCamera__Style* mpStyle;
    /* 0x4 */ int mStyleIdx;

public:
    dCamParam_c(s32);
    virtual ~dCamParam_c();

    void Flag(s32, u16);
    void Val(s32, int);
    void Change(s32);
    void SearchStyle(u32);
    void ratiof(f32, f32, f32, f32);
    void DefaultRadius(f32*);
    void RadiusRatio(f32);
    void CenterHeight(f32);
    void Fovy(f32);
    void LockonLongitude(f32);
    void LockonLatitude(f32);
    void LockonFovy(f32);
    void LockonCenterHeight(f32);
};

class dCamMath {
public:
    void rationalBezierRatio(f32, f32);
    void customRBRatio(f32, f32);
    void zoomFovy(f32, f32);
    void xyzRotateX(cXyz&, cSAngle);
    void xyzRotateY(cXyz&, cSAngle);
    void xyzHorizontalDistance(cXyz&, cXyz&);
    void xyzProjPosOnYZ(cSAngle, cXyz&, cXyz&);
};

#endif /* D_CAM_PARAM_H */
