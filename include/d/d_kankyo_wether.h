#ifndef D_KANKYO_WETHER_H
#define D_KANKYO_WETHER_H

#include "JSystem/J3DGraphBase/J3DPacket.h"
#include "SSystem/SComponent/c_xyz.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"

class JUTTexture;
class JPABaseEmitter;
class WIND_INFLUENCE;

class dKankyo_sun_Packet : public J3DPacket {
public:
    dKankyo_sun_Packet() {}

    virtual void draw();
    virtual ~dKankyo_sun_Packet();

    /* 0x10 */ cXyz mPos[2];
    /* 0x28 */ u32 mVizChkData[5];
    /* 0x3C */ u8 field_0x3c;
    /* 0x3D */ bool field_0x3d;
    /* 0x40 */ f32 mVisibility;
    /* 0x44 */ f32 mSunAlpha;
    /* 0x48 */ f32 mMoonAlpha;
    /* 0x4C */ GXColor mColor;
    /* 0x50 */ u8* mpTextureData[5];
};

class dKankyo_sunlenz_Packet : public J3DPacket {
public:
    dKankyo_sunlenz_Packet() {}

    virtual void draw();
    virtual ~dKankyo_sunlenz_Packet();

    /* 0x10 */ GXColor mColorTmp;
    /* 0x14 */ u8* mpTexSnow01;
    /* 0x18 */ u8* mpTexLensHalf;
    /* 0x1C */ u8* mpTexRingHalf;
    /* 0x20 */ cXyz mPositions[8];
    /* 0x80 */ f32 field_0x80;
    /* 0x84 */ f32 field_0x84;
    /* 0x88 */ f32 field_0x88;
    /* 0x8C */ f32 field_0x8c;
    /* 0x90 */ f32 mAngleDeg;
    /* 0x94 */ f32 mDistFalloff;
    /* 0x98 */ s16 field_0x98;
    /* 0x9A */ bool mbDrawLenzInSky;
};

struct RAIN_EFF {
    RAIN_EFF();
    ~RAIN_EFF();

    /* 0x00 */ u8 mStatus;
    /* 0x04 */ cXyz mPos;
    /* 0x10 */ cXyz mBasePos;
    /* 0x1C */ f32 field_0x1c;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 mAlpha;
    /* 0x2C */ f32 field_0x2c;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ s16 mTimer;
};

class dKankyo_rain_Packet : public J3DPacket {
public:
    dKankyo_rain_Packet() {}

    virtual void draw();
    virtual ~dKankyo_rain_Packet();

    /* 0x0010 */ u8* mpTxSnow01;
    /* 0x0014 */ u8* mpTxRingAHalf;
    /* 0x0018 */ RAIN_EFF mEff[250];
    /* 0x36C8 */ f32 field_0x36c8;
    /* 0x36CC */ f32 field_0x36cc;
    /* 0x36D0 */ s16 mRainCount;
    /* 0x36D2 */ u8 field_0x36D2[0x36D8 - 0x36D2];
    /* 0x36D8 */ cXyz mCamEyePos;
    /* 0x36E4 */ cXyz mCamCenterPos;
    /* 0x36F0 */ cXyz mCenterDelta;
    /* 0x36FC */ f32 mCenterDeltaMul;
    /* 0x3700 */ f32 field_0x3700;
    /* 0x3704 */ f32 mSibukiAlpha;
    /* 0x3708 */ f32 mOverheadFade;
    /* 0x370C */ f32 mFwd1Fade;
    /* 0x3710 */ f32 mFwdFade2;
    /* 0x3714 */ u8 mStatus;
};

struct SNOW_EFF {
    SNOW_EFF();
    ~SNOW_EFF();

    /* 0x00 */ u8 mStatus;
    /* 0x04 */ cXyz mPos;
    /* 0x10 */ cXyz mBasePos;
    /* 0x1C */ f32 mPosWaveX;
    /* 0x20 */ f32 mPosWaveZ;
    /* 0x24 */ f32 mGravity;
    /* 0x28 */ f32 mWindSpeed;
    /* 0x2C */ f32 mScale;
    /* 0x30 */ u8 field_0x30[0x34 - 0x30];
    /* 0x34 */ s16 mTimer;
};

class dKankyo_snow_Packet : public J3DPacket {
public:
    dKankyo_snow_Packet() {}

    virtual void draw();
    virtual ~dKankyo_snow_Packet();

    /* 0x0010 */ u8* mpTexture;
    /* 0x0014 */ SNOW_EFF mEff[250];
    /* 0x36C4 */ cXyz mOldEyePos;
    /* 0x36D0 */ f32 field_0x36d0;
    /* 0x36D4 */ f32 field_0x36d4;
    /* 0x36D8 */ s16 mEffCount;
    /* 0x36DA */ s16 mTamariStart;
    /* 0x36DC */ void *field_0x36dc;
};

struct STAR_EFF {
    STAR_EFF();
    ~STAR_EFF();

    /* 0x00 */ u8 field_0x00[0x1C - 0x00];
    /* 0x1C */ f32 mAnimCounter;
    /* 0x20 */ u8 field_0x20[0x28 - 0x20];
    /* 0x28 */ f32 mSin;
    /* 0x2C */ u8 field_0x2c[0x34 - 0x2C];
};

class dKankyo_star_Packet : public J3DPacket {
public:
    dKankyo_star_Packet() {}

    virtual void draw();
    virtual ~dKankyo_star_Packet();

    /* 0x10 */ u8* mpTexture;
    /* 0x14 */ STAR_EFF mStarEff[1];
    /* 0x48 */ s16 mCount;
};

struct POISON_EFF {
    POISON_EFF();
    ~POISON_EFF();

    /* 0x00 */ s8 mStatus;
    /* 0x04 */ cXyz mPos;
    /* 0x10 */ u8 field_0x10[0x10];
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 mAlpha;
    /* 0x28 */ f32 mSize;
    /* 0x2E */ s16 field_0x2e;
};

STATIC_ASSERT(sizeof(POISON_EFF) == 0x30);

class dKankyo_poison_Packet : public J3DPacket {
public:
    dKankyo_poison_Packet() {}

    virtual void draw();
    virtual ~dKankyo_poison_Packet();

    /* 0x0010 */ POISON_EFF mEff[1000];
    /* 0xBB90 */ cXyz mBasePos;
    /* 0xBB9C */ cXyz field_0xbb9c;
    /* 0xBBA8 */ s32 mCount;
    /* 0xBBAC */ u8* mpTexture;
};

struct CLOUD_EFF {
    CLOUD_EFF();
    ~CLOUD_EFF();

    /* 0x00 */ u8 mStatus;
    /* 0x04 */ cXyz mPos;
    /* 0x10 */ cXyz mBasePos;
    /* 0x1C */ cXyz mPntWindVel;
    /* 0x28 */ cXyz mVelRndm;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 mWindSpeed;
    /* 0x3C */ s16 mAnimCounter;
    /* 0x40 */ f32 mAlpha;
    /* 0x44 */ f32 mSize;
    /* 0x48 */ f32 mInitialSize;
};

class dKankyo_cloud_Packet : public J3DPacket {
public:
    dKankyo_cloud_Packet() {}

    virtual void draw();
    virtual ~dKankyo_cloud_Packet();

    /* 0x0010 */ u8* mpTexture;
    /* 0x0014 */ int mCount;
    /* 0x0018 */ CLOUD_EFF mEff[100];
};

struct HOUSI_EFF {
    HOUSI_EFF();
    ~HOUSI_EFF();

    /* 0x00 */ u8 mState;
    /* 0x04 */ cXyz mPos;
    /* 0x10 */ cXyz mBasePos;
    /* 0x1C */ cXyz mVel;
    /* 0x28 */ cXyz mScale;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ u8 field_0x38[0x3C - 0x38];
    /* 0x3C */ s16 field_0x3c;
    /* 0x3E */ u8 field_0x3E[0x40 - 0x3E];
    /* 0x40 */ f32 mAlpha;
    /* 0x44 */ u8 field_0x44[0x48 - 0x44];
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ s16 field_0x4c;
};

class dKankyo_housi_Packet : public J3DPacket {
public:
    dKankyo_housi_Packet() {}

    virtual void draw();
    virtual ~dKankyo_housi_Packet();

    /* 0x0010 */ u8* mpTex;
    /* 0x0014 */ HOUSI_EFF mEff[300];
    /* 0x5DD4 */ u8 field_0x5DD4[0x5DDC - 0x5DD4];
    /* 0x5DDC */ f32 field_0x5ddc;
    /* 0x5DE0 */ s16 mCount;
    /* 0x5DE2 */ u8 field_0x5de2[0x5DE8 - 0x5DE2];
};

struct VRKUMO_EFF {
    VRKUMO_EFF();
    ~VRKUMO_EFF();

    /* 0x00 */ u8 mStatus;
    /* 0x01 */ u8 field_0x01[0x04 - 0x01];
    /* 0x04 */ cXyz mPosition;
    /* 0x10 */ u8 field_0x10[0x1C - 0x10];
    /* 0x1C */ f32 mHeight;
    /* 0x20 */ f32 mAlpha;
    /* 0x24 */ f32 mDistFalloff;
    /* 0x28 */ f32 mSpeed;
};

class dKankyo_vrkumo_Packet : public J3DPacket {
public:
    dKankyo_vrkumo_Packet() {}

    virtual void draw();
    virtual ~dKankyo_vrkumo_Packet();

    /* 0x0010 */ GXColor mColorTmp;
    /* 0x0014 */ u8* mpCloudTx1;
    /* 0x0018 */ u8* mpCloudTx2;
    /* 0x001C */ u8* mpCloudTx3;
    /* 0x0020 */ VRKUMO_EFF mInst[100];
};

struct WAVE_EFF {
    WAVE_EFF();
    ~WAVE_EFF();

    /* 0x00 */ cXyz mPos;
    /* 0x0C */ cXyz mBasePos;
    /* 0x18 */ f32 mSpeed;
    /* 0x1C */ f32 mScale;
    /* 0x20 */ f32 mCounterSpeed;
    /* 0x24 */ f32 mCounter;
    /* 0x28 */ f32 mAlpha;
    /* 0x2C */ f32 mStrengthEnv;
    /* 0x30 */ s16 field_0x30;
    /* 0x32 */ s16 field_0x32;
    /* 0x34 */ s8 mStatus;
};

class dKankyo_wave_Packet : public J3DPacket {
public:
    dKankyo_wave_Packet() {}

    virtual void draw();
    virtual ~dKankyo_wave_Packet();

    /* 0x0010 */ u8* mpTexUsonami;
    /* 0x0014 */ u8* mpTexUsonamiM;
    /* 0x0018 */ WAVE_EFF mEff[300];
    /* 0x41B8 */ f32 mSkewWidth;
    /* 0x41BC */ f32 mSkewDir;
};

struct KAMOME_EFF {
    KAMOME_EFF();
    ~KAMOME_EFF();

    /* 0x00 */ JPABaseEmitter* mpBaseEmitter;
    /* 0x04 */ cXyz mPos;
    /* 0x10 */ s16 field_0x10;
    /* 0x12 */ s16 field_0x12;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ s16 field_0x1c;
    /* 0x1E */ u8 field_0x1e;
};

struct WIND_EFF {
    WIND_EFF();
    ~WIND_EFF();

    /* 0x00 */ JPABaseEmitter* mpEmitter;
    /* 0x04 */ cXyz mBasePos;
    /* 0x10 */ cXyz mRandomPos;
    /* 0x1C */ f32 mStateTimer;
    /* 0x20 */ f32 mAlpha;
    /* 0x24 */ int mState;
    /* 0x28 */ int field_0x28;
    /* 0x2C */ s16 field_0x2c;
    /* 0x2E */ s16 mAngleY;
    /* 0x30 */ s16 mAngleXZ;
    /* 0x32 */ u8 field_0x32;
};

// is this the correct name?
struct WINDEFF_SET {
    /* 0x000 */ WIND_EFF mWindEff[30];
    /* 0x618 */ KAMOME_EFF mKamomeEff[10];
    /* 0x758 */ u8 mbHasCustomWindPower;
    /* 0x759 */ u8 field_0x759;
};

void dKyw_wether_init();
void dKyw_wether_init2();
void dKyw_wether_move();
void dKyw_wether_move_draw();
void dKyw_wether_move_draw2();
void dKyw_wether_draw();
void dKyw_wether_draw2();
void dKyw_wether_proc();
void dKyw_wether_delete();
void dKyw_wether_delete2();
void dKyw_rain_set(int);
void dKyw_wind_set();
void dKyw_wind_init();
int dKyw_get_windsdir();
void dKyw_pntwind_init();
void dKy_wave_chan_init();
f32 dKyw_get_wind_pow();
f32* dKyw_get_wind_power();
cXyz dKyw_get_wind_vecpow();
cXyz * dKyw_get_wind_vec();
void squal_proc();
void dKyw_pntwind_set(WIND_INFLUENCE*);
void dKyw_pntwind_cut(WIND_INFLUENCE*);
void dKyw_pwind_cylinder_set(WIND_INFLUENCE*);
void dKyw_evt_wind_set(s16 i_windX, s16 i_windY);
void dKyw_evt_wind_set_go();
void dKyw_get_AllWind_vec(cXyz* param_0, cXyz* i_direction, f32* i_power);

#endif /* D_KANKYO_WETHER_H */
