#ifndef D_KANKYO_D_KANKYO_H
#define D_KANKYO_D_KANKYO_H

#include "global.h"
#include "dolphin/gx/GX.h"
#include "SSystem/SComponent/c_xyz.h"

// setup properly later
struct J3DLightObj {
    u8 temp[0x74];
};

class dKy_tevstr_c {
public:
    /* 0x00 */ J3DLightObj mLightObj;
    /* 0x74 */ cXyz mLightPosWorld;
    /* 0x80 */ GXColorS10 mColorC0;
    /* 0x88 */ GXColor mColorK0;
    /* 0x8C */ GXColor mColorK1;
    /* 0x90 */ GXColorS10 mFogColor;
    /* 0x98 */ f32 mFogStartZ;
    /* 0x9C */ f32 mFogEndZ;
    /* 0xA0 */ f32 mColpatBlend;
    /* 0xA4 */ u8 mInitTimer;
    /* 0xA5 */ u8 mEnvrIdxCurr;
    /* 0xA6 */ u8 mEnvrIdxPrev;
    /* 0xA7 */ u8 mColpatCurr;
    /* 0xA8 */ u8 mColpatPrev;
    /* 0xA9 */ s8 mRoomNo;
    /* 0xAA */ u8 mEnvrIdxOverride;
    /* 0xAB */ u8 mLightMode;
    /* 0xAC */ u8 mInitType;
};  // Size = 0xB0

STATIC_ASSERT(sizeof(dKy_tevstr_c) == 0xB0);

#endif /* D_KANKYO_D_KANKYO_H */