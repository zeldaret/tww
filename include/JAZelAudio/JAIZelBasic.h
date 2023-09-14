#ifndef JAZELAUDIO_JAIZELBASIC_H
#define JAZELAUDIO_JAIZELBASIC_H

#include "dolphin/types.h"

class Vec;
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
    void checkCbPracticePlay();
    void prepareLandingDemo(s32);
    void startLandingDemo();
    void endLandingDemo();
    void initSe();
    void seStart(u32, Vec*, u32, s8, f32, f32, f32, f32, u8);
    void seStop(u32, s32);
    void checkSePlaying(u32);
    void seStopActor(Vec*, u32);
    void seDeleteObject(Vec*);
    void getLinkVoiceVowel(u32);
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
    void getCameraInfo(Vec*, f32*[][][][], u32);
    void getCameraMapInfo(u32);
    void setCameraPolygonPos(Vec*);
    void setCameraGroupInfo(u8);
    void changeSeaBgm();
    void startIsleBgm();
    void setLinkGroupInfo(u8);
    void getMapInfoFxline(u32);
    void getMapInfoFxParameter(u32);
    void getMapInfoGround(u32);
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
    void checkFirstWaves();
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
    void makeSound(u32);
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

    static JAIZelBasic* getInterface() { return zel_basic; }

    static JAIZelBasic* zel_basic;

    /* 0x0 */ u8 field_0x0[0x20F4];
};

class JAIZelAnime {
public:
    /* 0x0 */ u8 field_0x0[0x98];
};

#endif /* JAZELAUDIO_JAIZELBASIC_H */