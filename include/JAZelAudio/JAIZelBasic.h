#ifndef JAZELAUDIO_JAIZELBASIC_H
#define JAZELAUDIO_JAIZELBASIC_H

#include "dolphin/types.h"
#include "JAZelAudio/JAZelAudio_SE.h"
#include "JAZelAudio/JAZelAudio_BGM.h"
#include "dolphin/mtx/mtx.h"

class JAISound;
class JKRSolidHeap;

class JAIZelBasic {
public:
    JAIZelBasic();

    void zeldaGFrameWork();
    void heartGaugeOn();
    void processHeartGaugeSound();
    void gframeProcess();
    void resetProcess();
    void resetRecover();
    void bgmStreamPrepare(u32);
    void bgmStreamPlay();
    void bgmStart(u32, u32, s32);
    void bgmStop(u32, s32);
    void mainBgmStopOnly(u32);
    void subBgmStart(u32);
    void subBgmStop();
    void subBgmStopInner();
    void bgmNowBattle(f32);
    void bgmBattleGFrame();
    void stopBattleBgm();
    void bgmNowKaitengiri();
    void bgmHitSound(s32);
    void bgmSetSwordUsing(s32);
    void onEnemyDamage();
    void mbossBgmMuteProcess();
    void mbossBgmNearByProcess(f32);
    void checkBgmPlaying();
    void checkPlayingMainBgmFlag();
    void checkSubBgmPlaying();
    void checkPlayingSubBgmFlag();
    void checkPlayingStreamBgmFlag();
    void changeBgmStatus(s32);
    void changeSubBgmStatus(s32);
    void bgmMuteMtDragon();
    void enemyNearBy();
    void enemyNearByGFrame();
    void bgmAllMute(u32);
    void taktModeMute();
    void taktModeMuteOff();
    void cbPracticePlay(Vec*);
    void cbPracticeProcess();
    void cbPracticeStop();
    BOOL checkCbPracticePlay();
    void prepareLandingDemo(s32);
    void startLandingDemo();
    void endLandingDemo();
    void initSe();
    void seStart(u32, Vec*, u32, s8, f32, f32, f32, f32, u8);
    void seStop(u32, s32);
    void checkSePlaying(u32);
    void seStopActor(Vec*, u32);
    void seDeleteObject(Vec*);
    u8 getLinkVoiceVowel(u32);
    void linkVoiceStart(u32, Vec*, u8, s8);
    void monsSeInit();
    void monsSeStart(u32, Vec*, u32, u32, s8);
    void kuroboMotionPlay(u32, Vec*, u32, s8);
    void kuroboVoicePlay(u32, Vec*, s8);
    void setLevObjSE(u32, Vec*, s8);
    void processLevObjSE();
    void initLevObjSE();
    void charVoicePlay(s32, s32, Vec*, s8);
    void messageSePlay(u16, Vec*, s8);
    void shipCruiseSePlay(Vec*, f32);
    void setShipSailState(s32);
    void init(JKRSolidHeap*, u32);
    void setOutputMode(u32);
    void talkIn();
    void talkOut();
    void menuIn();
    void menuOut();
    void getCameraInfo(Vec*, Mtx, u32);
    void getCameraMapInfo(u32);
    void setCameraPolygonPos(Vec*);
    void setCameraGroupInfo(u8);
    void changeSeaBgm();
    void startIsleBgm();
    void setLinkGroupInfo(u8);
    void setScene(s32, s32, s32, s32);
    void expandSceneBgmNum(u32);
    void checkLinkOnSea();
    void checkLinkOnBoardSea();
    void setSceneName(char*, s32, s32);
    void spotNameToId(char*);
    void sceneChange(u32, u32, u32, s32);
    void sceneBgmStart();
    void load1stDynamicWave();
    BOOL check1stDynamicWave();
    void load2ndDynamicWave();
    void loadStaticWaves();
    BOOL checkFirstWaves();
    void setLinkHp(s32, s32);
    void setLinkSwordType(s32, s32);
    void setLinkShieldType(s32, s32);
    void setLinkBootsType(s32);
    void setLinkOnBoard(s32);
    void bgmMute(JAISound**, u32, s32, u32);
    void checkStreamPlaying(u32);
    void stWaterLevelUp();
    void stWaterLevelDown();
    void stSkyCloisters();
    void stSkyCloistersProcess();
    void getRandomU32(u32);
    void setEventBit(void*);
    void checkEventBit(u16);
    void checkDayTime();
    void processTime();
    void processMorningToNormal();
    void checkOnOuterSea(f32*);
    void checkSeqIDDemoPlaying(u32);
    void checkDemoFanfarePlaying();
    void processDemoFanfareMute();
    void muteMainBgmAll();
    void unmuteMainBgmAll();
    void demoBgmStop(u32);
    void isDemo();
    void checkSeaBgmID();
    void initSeaEnvPos();
    void registSeaEnvPos(Vec*);
    void seaEnvSePlay(u32, s8);
    void calcPosPanLR(Vec*);
    void calcPosPanSR(Vec*, f32);
    void calcPosVolume(Vec*, f32);
    void seaShoreSE(u32, Vec*, u32, s8);
    void initRiverPos();
    void registRiverPos(Vec*);
    void riverSePlay(u8, s8);
    void waterfallSePlay(u8, Vec*, s8);
    void initWindowPos();
    void registWindowPos(Vec*);
    void rainPlay(s32);

    virtual void makeSound(u32);
    virtual void getMapInfoFxline(u32);
    virtual void getMapInfoGround(u32);
    virtual void getMapInfoFxParameter(u32);

    void setHour(s32 i_hour) { mHour = i_hour; }
    void setMinute(s32 i_minute) { mMinute = i_minute; }
    void setWeekday(s32 i_weekday) { mWeekday = i_weekday; }

    static JAIZelBasic* getInterface() { return zel_basic; }

    static JAIZelBasic* zel_basic;

    // static m_bgm_mute_state;

    // static charVoiceTable;
    // static linkVoiceTable;

    // static m_bgm_wave_info;
    // static m_dy_wave_set_1st;
    // static m_dy_wave_set_2nd;
    // static m_scene_info;
    // static m_isle_info;
    // static spot_dir_name;
    // static mIsleArea;

    /* 0x0004 */ u8 field_0x0004[0x0020 - 0x0004];
    /* 0x0020 */ u8 field_0x0020;
    /* 0x0021 */ u8 field_0x0021;
    /* 0x0022 */ u8 field_0x0022[0x0024 - 0x0022];
    /* 0x0024 */ int field_0x0024;
    /* 0x0028 */ u8 field_0x0028[0x002C - 0x0028];
    /* 0x002C */ u8 mHour;
    /* 0x002D */ u8 mMinute;
    /* 0x002E */ u8 mWeekday;
    /* 0x002F */ u8 field_0x002f;
    /* 0x0030 */ s16 field_0x0030;
    /* 0x0032 */ u8 field_0x0032;
    /* 0x0033 */ u8 field_0x0033[0x0034 - 0x0033];
    /* 0x0034 */ int field_0x0034;
    /* 0x0038 */ int field_0x0038;
    /* 0x003C */ f32 field_0x003c;
    /* 0x0040 */ u8 field_0x0040[0x0041 - 0x0040];
    /* 0x0041 */ u8 field_0x0041;
    /* 0x0042 */ u8 field_0x0042;
    /* 0x0043 */ u8 field_0x0043;
    /* 0x0044 */ u8 field_0x0044;
    /* 0x0045 */ u8 field_0x0045;
    /* 0x0046 */ u8 field_0x0046;
    /* 0x0047 */ u8 field_0x0047;
    /* 0x0048 */ f32 field_0x0048;
    /* 0x004C */ f32 field_0x004c;
    /* 0x0050 */ f32 field_0x0050;
    /* 0x0054 */ f32 field_0x0054;
    /* 0x0058 */ f32 field_0x0058;
    /* 0x005C */ f32 field_0x005c;
    /* 0x0060 */ u8 mbLandingDemoStarted;
    /* 0x0061 */ u8 field_0x0061[0x0062 - 0x0061];
    /* 0x0062 */ u8 field_0x0062;
    /* 0x0063 */ u8 field_0x0063;
    /* 0x0064 */ u8 field_0x0064[0x0066 - 0x0064];
    /* 0x0066 */ u8 field_0x0066;
    /* 0x0067 */ u8 field_0x0067[0x0070 - 0x0067];
    /* 0x0070 */ JAISound* mpSound;
    /* 0x0074 */ int field_0x0074;
    /* 0x0078 */ u32 field_0x0078;
    /* 0x007C */ u32 field_0x007c;
    /* 0x0080 */ f32 field_0x0080;
    /* 0x0084 */ f32 field_0x0084;
    /* 0x0088 */ f32 field_0x0088;
    /* 0x008C */ f32 field_0x008c;
    /* 0x0090 */ f32 field_0x0090;
    /* 0x0094 */ f32 field_0x0094;
    /* 0x0098 */ f32 field_0x0098;
    /* 0x009C */ f32 field_0x009c;
    /* 0x00A0 */ f32 field_0x00a0;
    /* 0x00A4 */ f32 field_0x00a4;
    /* 0x00A8 */ f32 field_0x00a8;
    /* 0x00AC */ f32 field_0x00ac;
    /* 0x00B0 */ int field_0x00b0;
    /* 0x00B4 */ u8 field_0x00B4[0x00B5 - 0x00B4];
    /* 0x00B5 */ u8 mSomeSpecialBGMFlag;
    /* 0x00B6 */ u8 mLastMinibossSubBGMType;
    /* 0x00B7 */ u8 field_0x00B7[0x00BC - 0x00B7];
    /* 0x00BC */ u8 field_0x00bc;
    /* 0x00BD */ u8 field_0x00BD[0x00BE - 0x00BD];
    /* 0x00BE */ u8 field_0x00be;
    /* 0x00BF */ u8 field_0x00BF[0x00CA - 0x00BF];
    /* 0x00CA */ u8 field_0x00ca;
    /* 0x00CB */ u8 field_0x00CB[0x01F9 - 0x00CB];
    /* 0x01F9 */ u8 field_0x01f9;
    /* 0x01FA */ u8 field_0x01FA[0x0201 - 0x01FA];
    /* 0x0201 */ u8 field_0x0201;
    /* 0x0202 */ u8 field_0x0202[0x021C - 0x0202];
    /* 0x021C */ u8 mCameraSeaFloorGroupInfo;
    /* 0x021D */ u8 mLinkSeaFloorGroupInfo;
    /* 0x021E */ u8 field_0x021e;
    /* 0x021F */ u8 field_0x021F[0x0224 - 0x021F];
    /* 0x0224 */ int field_0x0224;
    /* 0x0228 */ u32 mNextSceneBgmId;
    /* 0x022C */ u8 field_0x022C[0x022D - 0x022C];
    /* 0x022D */ u8 field_0x022d;
    /* 0x022E */ u8 field_0x022e;
    /* 0x022F */ u8 field_0x022f;
    /* 0x0230 */ u8 field_0x0230;
    /* 0x0231 */ u8 field_0x0231;
    /* 0x0232 */ u8 mFirstDynamicSceneWaveIndex;
    /* 0x0233 */ u8 field_0x0233;
    /* 0x0234 */ u8 mSetNum;
    /* 0x0235 */ u8 mSecondDynamicSceneWaveIndex;
    /* 0x0236 */ u8 field_0x0236;
    /* 0x0237 */ u8 field_0x0237;
    /* 0x0238 */ u8 mIslandRoomNo;
    /* 0x0239 */ u8 field_0x0239[0x1F3D - 0x0239];
    /* 0x1F3D */ u8 mIsSailing;
    /* 0x1F3E */ u8 field_0x1F3E[0x1F40 - 0x1F3E];
    /* 0x1F40 */ f32 field_0x1f40;
    /* 0x1F44 */ u8 field_0x1F44[0x20F4 - 0x1F44];
};

#endif /* JAZELAUDIO_JAIZELBASIC_H */