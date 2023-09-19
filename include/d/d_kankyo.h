#ifndef D_KANKYO_D_KANKYO_H
#define D_KANKYO_D_KANKYO_H

#include "global.h"
#include "dolphin/gx/GX.h"
#include "SSystem/SComponent/c_xyz.h"
#include "JSystem/J3DGraphBase/J3DStruct.h"

class J3DModel;

struct color_RGB_class {
    u8 r;
    u8 g;
    u8 b;
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

enum TevType {
    TEV_TYPE_ACTOR,
    TEV_TYPE_BG0,
    TEV_TYPE_BG1,
    TEV_TYPE_BG2,
    TEV_TYPE_BG3,
    TEV_TYPE_BG0_FULL,
    TEV_TYPE_BG1_FULL,
    TEV_TYPE_BG2_FULL,
    TEV_TYPE_BG3_FULL,
    TEV_TYPE_PLAYER,
    TEV_TYPE_BG0_PLIGHT,
    TEV_TYPE_BG1_PLIGHT,
    TEV_TYPE_BG2_PLIGHT,
    TEV_TYPE_ACTOR_NOLIGHT,
};

struct dScnKy_env_light_c {
public:
    void settingTevStruct(int, cXyz*, dKy_tevstr_c*);
    void setLightTevColorType(J3DModel*, dKy_tevstr_c*);

public:
    u8 pad[0xC9C];
};  // Size = 0xC9C

extern dScnKy_env_light_c g_env_light;

int dKy_getdaytime_hour();
BOOL dKy_daynight_check();
BOOL dKy_checkEventNightStop();
void dKy_set_nexttime(f32);
void dKy_Sound_set(cXyz i_pos, int param_1, unsigned int i_actorID, int param_3);
void dKy_itudemo_se();

#endif /* D_KANKYO_D_KANKYO_H */
