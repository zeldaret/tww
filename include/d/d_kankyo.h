#ifndef D_KANKYO_D_KANKYO_H
#define D_KANKYO_D_KANKYO_H

#include "JSystem/J3DGraphBase/J3DStruct.h"
#include "SSystem/SComponent/c_xyz.h"
#include "dolphin/gx/GX.h"
#include "global.h"

class J3DModel;

struct color_RGB_class {
    u8 r;
    u8 g;
    u8 b;
};

struct LIGHT_INFLUENCE {
    ~LIGHT_INFLUENCE() {}
    LIGHT_INFLUENCE() {}

    /* 0x00 */ cXyz mPos;
    /* 0x0C */ GXColorS10 mColor;
    /* 0x14 */ f32 mPower;
    /* 0x18 */ f32 mFluctuation;
    /* 0x1C */ int mIdx;
};

struct WIND_INFLUENCE {
    ~WIND_INFLUENCE() {}

    /* 0x00 */ cXyz mPos;
    /* 0x0C */ cXyz mDir;
    /* 0x18 */ f32 mRadius;
    /* 0x1C */ f32 mStrength;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ u32 field_0x24;
    /* 0x28 */ u8 mbConstant;
};

struct WIND_INF_ENTITY {
    ~WIND_INF_ENTITY() {}
    WIND_INF_ENTITY() {}

    /* 0x00 */ u8 mbInUse;
    /* 0x04 */ f32 mMinRadius;
    /* 0x08 */ f32 mSpeed;
    /* 0x0C */ f32 mStrengthMaxVel;
    /* 0x10 */ WIND_INFLUENCE mInfluence;
};

struct dKankyo_wave__INFLUENCE {};

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

struct dScnKy__Schedule {
    /* 0x0 */ f32 mTimeEnd;
    /* 0x4 */ f32 mTimeBegin;
    /* 0x8 */ u8 mPalIdx0;
    /* 0x9 */ u8 mPalIdx1;
};

class dKankyo_sun_Packet;
class dKankyo_sunlenz_Packet;
class dKankyo_rain_Packet;
class dKankyo_snow_Packet;
class dKankyo_housi_Packet;
class dKankyo_cloud_Packet;
class dKankyo_vrkumo_Packet;
class dKankyo_wave_Packet;
class dKyr__wind_Packet;
class dKankyo_star_Packet;
class stage_palet_info_class;
class stage_pselect_info_class;
class stage_envr_info_class;
class stage_vrbox_info_class;
class stage_plight_info_class;

class dScnKy_env_light_c {
public:
    dScnKy_env_light_c();
    virtual ~dScnKy_env_light_c();

    void setDaytime();
    void SetSchbit();
    void setSunpos();
    f32 getDaytime();
    void setLight_palno_get(u8*, u8*, u8*, u8*, u8*, u8*, u8*, u8*, f32*, int*, int*, f32*, u8*);
    void setLight();
    void setLight_bg(dKy_tevstr_c*, GXColorS10*, GXColorS10*, GXColorS10*, GXColorS10*, GXColorS10*,
                     GXColorS10*, GXColorS10*, GXColorS10*, GXColorS10*, f32*, f32*);
    void setLight_actor(dKy_tevstr_c*, GXColorS10*, f32*, f32*);
    void settingTevStruct_colget_actor(cXyz*, dKy_tevstr_c*, GXColorS10*, GXColorS10*, GXColorS10*,
                                       f32*, f32*);
    void settingTevStruct_colget_player(dKy_tevstr_c*);
    void settingTevStruct_plightcol_plus(cXyz*, dKy_tevstr_c*, GXColorS10, GXColorS10, u8);
    void settingTevStruct_eflightcol_plus(cXyz*, dKy_tevstr_c*);
    void settingTevStruct(int, cXyz*, dKy_tevstr_c*);
    void setLightTevColorType(J3DModel*, dKy_tevstr_c*);
    void CalcTevColor();
    void Sndpos();
    void Eflight_flush_proc();
    void SetBaseLight();
    void exeKankyo();
    void drawKankyo();

    /* 0x004 */ stage_palet_info_class* mpPaletInfo;
    /* 0x008 */ stage_pselect_info_class* mpPselectInfo;
    /* 0x00C */ stage_envr_info_class* mpEnvrInfo;
    /* 0x010 */ stage_vrbox_info_class* mpVrboxInfo;
    /* 0x014 */ dScnKy__Schedule* mpSchejule;
    /* 0x018 */ LIGHT_INFLUENCE mBaseLightInfluence;
    /* 0x038 */ LIGHT_INFLUENCE mLightInfluence[30];
    /* 0x3F8 */ LIGHT_INFLUENCE* mpPLights[200];
    /* 0x718 */ LIGHT_INFLUENCE* mpEfLights[10];
    /* 0x740 */ u8 field_0x740[0x764 - 0x740];
    /* 0x764 */ u8 mSwordState;
    /* 0x765 */ u8 mSwordFrame;
    /* 0x766 */ u8 field_0x766[0x768 - 0x766];
    /* 0x768 */ int mSwordLightType;
    /* 0x76C */ LIGHT_INFLUENCE mSwordLight;
    /* 0x78C */ stage_plight_info_class* mpPlightInfo;
    /* 0x790 */ WIND_INFLUENCE* mpWindInfluence[30];
    /* 0x808 */ WIND_INF_ENTITY mWindInfluenceEntity[5];
    /* 0x934 */ u8 field_0x934[0x944 - 0x934];
    /* 0x944 */ int field_0x944;
    /* 0x948 */ u8 field_0x948[0x94c - 0x948];
    /* 0x94C */ f32 field_0x94c;
    /* 0x950 */ f32 field_0x950;
    /* 0x954 */ f32 field_0x954;
    /* 0x958 */ f32 mWaveSpeed;
    /* 0x95C */ f32 mWaveSpawnDist;
    /* 0x960 */ f32 mWaveSpawnRadius;
    /* 0x964 */ f32 mWaveScale;
    /* 0x968 */ f32 mWaveScaleRand;
    /* 0x96C */ f32 mWaveCounterSpeedScale;
    /* 0x970 */ f32 mWaveScaleBottom;
    /* 0x974 */ f32 mWaveFlatInter;
    /* 0x978 */ s16 mWaveCount;
    /* 0x97A */ u8 mWaveReset;
    /* 0x97B */ u8 field_0x97b;
    /* 0x97C */ cXyz mWindVec;
    /* 0x988 */ cXyz* mpWindVecOverride;
    /* 0x98C */ u8 field_0x98C[0x990 - 0x98C];
    /* 0x990 */ f32 field_0x990;
    /* 0x994 */ u8 field_0x994[0x998 - 0x994];
    /* 0x998 */ f32 mWindPower;
    /* 0x99C */ f32 mWindStrengthOverride;
    /* 0x9A0 */ f32 mCustomWindPower;
    /* 0x9A4 */ s16 mTactWindAngleX;
    /* 0x9A6 */ s16 mTactWindAngleY;
    /* 0x9A8 */ s16 mEvtWindAngleX;
    /* 0x9AA */ s16 mEvtWindAngleY;
    /* 0x9AC */ u8 mTactWindAngleFlags;
    /* 0x9AD */ u8 mEvtWindSet;
    /* 0x9AE */ u8 field_0x9AE[0x9B0 - 0x9AE];
    /* 0x9B0 */ u8 mbSunInitialized;
    /* 0x9B1 */ u8 field_0x9B1[0x9B4 - 0x9B1];
    /* 0x9B4 */ dKankyo_sun_Packet* mpSunPacket;
    /* 0x9B8 */ dKankyo_sunlenz_Packet* mpSunlenzPacket;
    /* 0x9BC */ u8 mbRainInitialized;
    /* 0x9BD */ u8 field_0x9BD[0x9C0 - 0x9BD];
    /* 0x9C0 */ int mRainCount;
    /* 0x9C4 */ dKankyo_rain_Packet* mpRainPacket;
    /* 0x9C8 */ u8 mbSnowInitialized;
    /* 0x9C9 */ u8 field_0x9C9[0x9CC - 0x9C9];
    /* 0x9CC */ int mSnowCount;
    /* 0x9D0 */ dKankyo_snow_Packet* mpSnowPacket;
    /* 0x9D4 */ u8 mbStarInitialized;
    /* 0x9D5 */ u8 field_0x9D5[0x9D8 - 0x9D5];
    /* 0x9D8 */ int mStarCount;
    /* 0x9DC */ f32 mStarCountTarget;
    /* 0x9E0 */ dKankyo_star_Packet* mpStarPacket;
    /* 0x9E4 */ u8 field_0x9E4[0x9F0 - 0x9E4];
    /* 0x9F0 */ u8 mbHouseInitialized;
    /* 0x9F1 */ u8 field_0x9F1[0x9F4 - 0x9F1];
    /* 0x9F4 */ int mHousiCount;
    /* 0x9F8 */ dKankyo_housi_Packet* mpHousiPacket;
    /* 0x9FC */ u8 mMoyaInitialized;
    /* 0x9FD */ u8 mMoyaMode;
    /* 0x9FE */ u8 field_0x9FE[0xA00 - 0x9FE];
    /* 0xA00 */ int mMoyaCount;
    /* 0xA04 */ dKankyo_cloud_Packet* mpMoyaPacket;
    /* 0xA08 */ u8 mVrkumoStatus;
    /* 0xA09 */ u8 field_0xA09[0xA0C - 0xA09];
    /* 0xA0C */ int mVrkumoCount;
    /* 0xA10 */ f32 mVrkumoStrength;
    /* 0xA14 */ dKankyo_vrkumo_Packet* mpVrkumoPacket;
    /* 0xA18 */ u8 mWaveInitialized;
    /* 0xA19 */ u8 field_0xA19[0xA20 - 0xA19];
    /* 0xA20 */ dKankyo_wave_Packet* mpWavePacket;
    /* 0xA24 */ u8 mbWindlineInitialized;
    /* 0xA25 */ u8 field_0xA25[0xA28 - 0xA25];
    /* 0xA28 */ int mWindlineCount;
    /* 0xA2C */ dKyr__wind_Packet* mpWind;
    /* 0xA30 */ bool mbThunderActive;
    /* 0xA31 */ u8 mThunderStateTimer;
    /* 0xA32 */ u8 field_0xA32[0xA34 - 0xA32];
    /* 0xA34 */ int mThunderMode;
    /* 0xA38 */ f32 mThunderFlashTimer;
    /* 0xA3C */ f32 field_0xa3c;
    /* 0xA40 */ f32 field_0xa40;
    /* 0xA44 */ u8 field_0xA44[0xA48 - 0xA44];
    /* 0xA48 */ LIGHT_INFLUENCE mThunderLightInfluence;
    /* 0xA68 */ dKankyo_wave__INFLUENCE* mpWaveInfl[10];
    /* 0xA90 */ cXyz mLightDir;
    /* 0xA9C */ cXyz mSunPos2;
    /* 0xAA8 */ cXyz mPLightNearPlayer;
    /* 0xAB4 */ cXyz mSunPos;
    /* 0xAC0 */ cXyz mMoonPos;
    /* 0xACC */ GXFogAdjTable mFogAdjTable;
    /* 0xAE0 */ GXColorS10 mVrSkyColor;
    /* 0xAE8 */ GXColorS10 mVrUsoUmiColor;
    /* 0xAF0 */ GXColorS10 mVrkumoColor;
    /* 0xAF8 */ GXColorS10 mVrkumoCenterColor;
    /* 0xB00 */ GXColorS10 mVrKasumiMaeColor;
    /* 0xB08 */ GXColorS10 mC0;
    /* 0xB10 */ GXColorS10 mK0;
    /* 0xB18 */ GXColorS10 mActorC0;
    /* 0xB20 */ GXColorS10 mActorK0;
    /* 0xB28 */ GXColorS10 mBG0_C0;
    /* 0xB30 */ GXColorS10 mBG0_K0;
    /* 0xB38 */ GXColorS10 mBG1_C0;
    /* 0xB40 */ GXColorS10 mBG1_K0;
    /* 0xB48 */ GXColorS10 mBG2_C0;
    /* 0xB50 */ GXColorS10 mBG2_K0;
    /* 0xB58 */ GXColorS10 mBG3_C0;
    /* 0xB60 */ GXColorS10 mBG3_K0;
    /* 0xB68 */ GXColorS10 mFogColor;
    /* 0xB70 */ GXColorS10 mActorAddColAmb;
    /* 0xB78 */ GXColorS10 mActorAddColDif;
    /* 0xB80 */ GXColorS10 mBgAddColAmb;
    /* 0xB88 */ GXColorS10 mBgAddColDif;
    /* 0xB90 */ GXColorS10 mBg1AddColAmb;
    /* 0xB98 */ GXColorS10 mBg1AddColDif;
    /* 0xBA0 */ GXColorS10 mBg2AddColAmb;
    /* 0xBA8 */ GXColorS10 mBg2AddColDif;
    /* 0xBB0 */ GXColorS10 mBg3AddColAmb;
    /* 0xBB8 */ GXColorS10 mBg3AddColDif;
    /* 0xBC0 */ GXColorS10 mAddColFog;
    /* 0xBC8 */ GXColorS10 mVrboxAddColSky0;
    /* 0xBD0 */ GXColorS10 mVrboxAddColKasumi;
    /* 0xBD8 */ f32 mDiceWeatherChangeTime;
    /* 0xBDC */ f32 mDiceWeatherTime;
    /* 0xBE0 */ f32 mColPatBlend;
    /* 0xBE4 */ f32 mColPatBlendGather;
    /* 0xBE8 */ f32 mFogStartZ__setLight;
    /* 0xBEC */ f32 mFogEndZ__setLight;
    /* 0xBF0 */ f32 mFogStartZ;
    /* 0xBF4 */ f32 mFogEndZ;
    /* 0xBF8 */ f32 mFogRatio;
    /* 0xBFC */ f32 mAllColRatio;
    /* 0xC00 */ f32 mActColRatio;
    /* 0xC04 */ f32 mBgColRatio;
    /* 0xC08 */ f32 mFogColRatio;
    /* 0xC0C */ f32 mVrboxSoraColRatio;
    /* 0xC10 */ f32 mVrboxKumoColRatio;
    /* 0xC14 */ f32 mAllColGatherRatio;
    /* 0xC18 */ f32 mActColGatherRatio;
    /* 0xC1C */ f32 mBgColGatherRatio;
    /* 0xC20 */ f32 mFogColGatherRatio;
    /* 0xC24 */ f32 mVrboxSoraColGatherRatio;
    /* 0xC28 */ f32 mVrboxKumoColGatherRatio;
    /* 0xC2C */ f32 field_0xc2c;
    /* 0xC30 */ f32 field_0xc30;
    /* 0xC34 */ f32 field_0xc34;
    /* 0xC38 */ f32 mCurTime;
    /* 0xC3C */ f32 mNextTime;
    /* 0xC40 */ f32 mTimeAdv;
    /* 0xC44 */ f32 field_0xc44;
    /* 0xC48 */ void* field_0xc48;
    /* 0xC4C */ void* field_0xc4c;
    /* 0xC50 */ u32 mMoyaSE;
    /* 0xC54 */ void* field_0xc54;
    /* 0xC58 */ void* field_0xc58;
    /* 0xC5C */ void* field_0xc5c;
    /* 0xC60 */ int mDiceWeatherCounter;
    /* 0xC64 */ int mRainCountOrig;
    /* 0xC68 */ void* field_0xc68;
    /* 0xC6C */ int mPlayerPLightIdx;
    /* 0xC70 */ int mPlayerEflightIdx;
    /* 0xC74 */ void* field_0xc74;
    /* 0xC78 */ void* field_0xc78;
    /* 0xC7C */ int mSchbitTimer;
    /* 0xC80 */ u16 mFogAdjCenter;
    /* 0xC82 */ u16 mDayOfWeek;
    /* 0xC84 */ u8 mColpatPrev;
    /* 0xC85 */ u8 mColpatCurr;
    /* 0xC86 */ u8 mColpatPrevGather;
    /* 0xC87 */ u8 mColpatCurrGather;
    /* 0xC88 */ u8 mEnvrIdxPrev;
    /* 0xC89 */ u8 mEnvrIdxCurr;
    /* 0xC8A */ u8 mColpatWeather;
    /* 0xC8B */ u8 mDiceWeatherMode;
    /* 0xC8C */ u8 mDiceWeatherState;
    /* 0xC8D */ u8 mDiceWeatherCurrPattern;
    /* 0xC8E */ u8 field_0xc8e;
    /* 0xC8F */ u8 mColPatMode;
    /* 0xC90 */ u8 mColPatModeGather;
    /* 0xC91 */ u8 mFogAdjEnable;
    /* 0xC92 */ u8 mFogAdjTableType;
    /* 0xC93 */ u8 mItemGetCol_chg;
    /* 0xC94 */ u8 mInitAnimTimer;
    /* 0xC95 */ u8 mSchbit;
    /* 0xC96 */ u8 mbVrboxInvisible;
    /* 0xC97 */ u8 mbContrastFlag;
    /* 0xC98 */ u8 field_0xc98;
    /* 0xC99 */ u8 mbDayNightTactStop;
    /* 0xC9A */ u8 field_0xc9a;
    /* 0xC9B */ u8 field_0xc9b;
};  // Size = 0xC9C

extern dScnKy_env_light_c g_env_light;

STATIC_ASSERT(sizeof(dScnKy_env_light_c) == 0xC9C);

inline dScnKy_env_light_c& dKy_getEnvlight() {
    return g_env_light;
}

enum dKy_dice_wether_mode {
    /* 0 */ DICE_MODE_SUNNY_e,
    /* 1 */ DICE_MODE_CLOUDY_e,
    /* 2 */ DICE_MODE_RAIN_LIGHT_e,
    /* 3 */ DICE_MODE_RAIN_HEAVY_e,
    /* 4 */ DICE_MODE_THUNDER_LIGHT_e,
    /* 5 */ DICE_MODE_THUNDER_HEAVY_e,
    DICE_MODE_DONE_e = 0xFF,
};

enum dKy_dice_wether_state {
    /* 0 */ DICE_STATE_RESET_e,
    /* 1 */ DICE_STATE_INIT_e,
    /* 2 */ DICE_STATE_EXEC_e,
    /* 3 */ DICE_STATE_NEXT_e,
};

class sub_kankyo__class;

int dKy_getdaytime_hour();
int dKy_getdaytime_minute();
int dKy_get_dayofweek();
BOOL dKy_checkEventNightStop();
void dKy_set_nexttime(f32);
void dKy_Sound_set(cXyz i_pos, int param_1, unsigned int i_actorID, int param_3);
void dKy_itudemo_se();
void dKy_actor_addcol_set(s16, s16, s16, f32);
void dKy_plight_set(LIGHT_INFLUENCE*);
void dKy_fog_startendz_set(f32, f32, f32);
void dKy_vrbox_addcol_set(s16, s16, s16, f32);
BOOL dKy_daynight_check();
void dKy_tevstr_init(dKy_tevstr_c*, s8, u8);
void dKy_Sound_init();
u8 dKy_pship_existense_chk();
void dKy_Itemgetcol_chg_move();
void dKy_arrowcol_chg_move();
void dKy_setLight_init();
void GxXFog_set();
void dKy_set_vrboxsoracol_ratio(f32 ratio);
void dKy_set_vrboxkumocol_ratio(f32 ratio);
cXyz dKy_get_orion_pos();
cXyz dKy_get_hokuto_pos();

/* 80197AB8-80197FE4       .text dKankyo_DayProc__Fv */
static void dKankyo_DayProc() {
    /* Nonmatching */
}

#endif /* D_KANKYO_D_KANKYO_H */
