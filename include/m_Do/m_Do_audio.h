#ifndef M_DO_AUDIO_H
#define M_DO_AUDIO_H

#include "JAZelAudio/JAIZelBasic.h"
#include "JAZelAudio/JAIZelInst.h"
#include "SSystem/SComponent/c_xyz.h"

class mDoAud_zelAudio_c : public JAIZelBasic {
public:
    mDoAud_zelAudio_c() {}
    ~mDoAud_zelAudio_c() {}

    void reset();

    static void calcLoadTimer();

    static bool isResetFlag() { return mResetFlag; }
    static void onResetFlag() { mResetFlag = true; }
    static void offResetFlag() { mResetFlag = false; }

    static bool isInitFlag() { return mInitFlag; }
    static void onInitFlag() { mInitFlag = true; }
    static void offInitFlag() { mInitFlag = false; }

    static bool isBgmSet() { return mBgmSet; }
    static void onBgmSet() { mBgmSet = true; }
    static void offBgmSet() { mBgmSet = false; }

    static void setLoadTimer(u8 i_timer) { mLoadTimer = i_timer; }
    static u8 getLoadTimer() { return mLoadTimer; }

    static JAIZelInst& getTact() { return mTact; }

    static void getMode() {}
    static void setMode(u8) {}

    static bool mInitFlag;
    static bool mResetFlag;
    static bool mBgmSet;
    static u8 mLoadTimer;

    static JAIZelInst mTact;
};

extern mDoAud_zelAudio_c g_mDoAud_zelAudio;

void mDoAud_setSceneName(const char*, s32, s32);
void mDoAud_Execute();
BOOL mDoAud_isUsedHeapForStreamBuffer();
int mDoAud_getTactDirection(int stick, int ret);

extern JKRSolidHeap* g_mDoAud_audioHeap;

inline void mDoAud_bgmStart(u32 param_0) {
    mDoAud_zelAudio_c::getInterface()->bgmStart(param_0, 0, 0);
}

inline void mDoAud_subBgmStart(u32 param_0) {
    mDoAud_zelAudio_c::getInterface()->subBgmStart(param_0);
}

inline void mDoAud_subBgmStop() {
    mDoAud_zelAudio_c::getInterface()->subBgmStop();
}

inline void mDoAud_changeBgmStatus(s32 status) {
    mDoAud_zelAudio_c::getInterface()->changeBgmStatus(status);
}

inline void mDoAud_changeSubBgmStatus(s32 status) {
    mDoAud_zelAudio_c::getInterface()->changeSubBgmStatus(status);
}

inline void mDoAud_bgmStreamPrepare(u32 id) {
    mDoAud_zelAudio_c::getInterface()->bgmStreamPrepare(id);
}

inline void mDoAud_bgmStreamPlay() {
    mDoAud_zelAudio_c::getInterface()->bgmStreamPlay();
}

inline void mDoAud_bgmStop(u32 i_fadeTime) {
    mDoAud_zelAudio_c::getInterface()->bgmStop(i_fadeTime, 0);
}

inline void mDoAud_bgmAllMute(u32 param_0) {
    mDoAud_zelAudio_c::getInterface()->bgmAllMute(param_0);
}

inline int mDoAud_checkPlayingMainBgmFlag() {
    return mDoAud_zelAudio_c::getInterface()->checkPlayingMainBgmFlag();
}

inline int mDoAud_checkPlayingSubBgmFlag() {
    return mDoAud_zelAudio_c::getInterface()->checkPlayingSubBgmFlag();
}

inline s32 mDoAud_checkFirstWaves() {
    return mDoAud_zelAudio_c::getInterface()->checkFirstWaves();
}

inline void mDoAud_loadStaticWaves() {
    mDoAud_zelAudio_c::getInterface()->loadStaticWaves();
}

int mDoAud_load1stDynamicWave();

inline void mDoAud_load2ndDynamicWave() {
    mDoAud_zelAudio_c::getInterface()->load2ndDynamicWave();
}

inline void mDoAud_check1stDynamicWave() {}

inline bool mDoAud_checkAllWaveLoadStatus() {
    return mDoAud_zelAudio_c::getInterface()->checkAllWaveLoadStatus();
}

inline void mDoAud_prepareLandingDemo(s32 idx) {
    mDoAud_zelAudio_c::getInterface()->prepareLandingDemo(idx);
}

inline void mDoAud_startLandingDemo() {
    mDoAud_zelAudio_c::getInterface()->startLandingDemo();
}

inline void mDoAud_endLandingDemo() {
    mDoAud_zelAudio_c::getInterface()->endLandingDemo();
}

inline void mDoAud_sceneBgmStart() {
    mDoAud_zelAudio_c::getInterface()->sceneBgmStart();
}

inline void mDoAud_taktModeMute() {
    mDoAud_zelAudio_c::getInterface()->taktModeMute();
}

inline void mDoAud_taktModeMuteOff() {
    mDoAud_zelAudio_c::getInterface()->taktModeMuteOff();
}

inline void mDoAud_resetProcess() {
    if (mDoAud_zelAudio_c::isResetFlag()) {
        mDoAud_zelAudio_c::getInterface()->resetProcess();
        mDoAud_zelAudio_c::onResetFlag();
    }
}

inline void mDoAud_seStart(u32 i_seNum, Vec* i_sePos, u32 param_2, s8 i_reverb) {
    mDoAud_zelAudio_c::getInterface()->seStart(i_seNum, i_sePos, param_2, i_reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
}

inline void mDoAud_seStart(u32 i_seNum, Vec* i_sePos, u32 param_2) {
    mDoAud_zelAudio_c::getInterface()->seStart(i_seNum, i_sePos, param_2, 0, 1.0f, 1.0f, -1.0f, -1.0f, 0);
}

inline void mDoAud_seStart(u32 i_seNum, Vec* i_sePos) {
    mDoAud_zelAudio_c::getInterface()->seStart(i_seNum, i_sePos, 0, 0, 1.0f, 1.0f, -1.0f, -1.0f, 0);
}

inline void mDoAud_seStart(u32 i_seNum) {
    mDoAud_zelAudio_c::getInterface()->seStart(i_seNum, NULL, 0, 0, 1.0f, 1.0f, -1.0f, -1.0f, 0);
}

inline void mDoAud_messageSePlay(u16 i_seNum, Vec* i_sePos = NULL, s8 i_reverb = 0) {
    mDoAud_zelAudio_c::getInterface()->messageSePlay(i_seNum, i_sePos, i_reverb);
}

inline void mDoAud_bgmSetSwordUsing(s32 param_1) {
    mDoAud_zelAudio_c::getInterface()->bgmSetSwordUsing(param_1);
}

inline void mDoAud_seStop(u32 i_seNum, s32 param_2) {
    mDoAud_zelAudio_c::getInterface()->seStop(i_seNum, param_2);
}

inline void mDoAud_seStop(u32 i_seNum) {
    mDoAud_zelAudio_c::getInterface()->seStop(i_seNum, 0);
}

inline void mDoAud_seStopActor(Vec* param_1, u32 param_2) {
    mDoAud_zelAudio_c::getInterface()->seStopActor(param_1, param_2);
}

inline void mDoAud_seStopActor(Vec* param_0) {
    mDoAud_zelAudio_c::getInterface()->seStopActor(param_0, -1);
}

inline void mDoAud_seDeleteObject(Vec* i_sePos) {
    mDoAud_zelAudio_c::getInterface()->seDeleteObject(i_sePos);
}

inline u8 mDoAud_getLinkVoiceVowel(u32 param_1) {
    return mDoAud_zelAudio_c::getInterface()->getLinkVoiceVowel(param_1);
}

inline void mDoAud_linkVoiceStart(u32 param_0, Vec* i_sePos, u8 param_3, s8 param_4) {
    mDoAud_zelAudio_c::getInterface()->linkVoiceStart(param_0, i_sePos, param_3, param_4);
}

inline void mDoAud_setLinkSwordType(s32 param_0, s32 param_1) {
    mDoAud_zelAudio_c::getInterface()->setLinkSwordType(param_0, param_1);
}

inline void mDoAud_setLinkShieldType(s32 param_0, s32 param_1) {
    mDoAud_zelAudio_c::getInterface()->setLinkShieldType(param_0, param_1);
}

inline void mDoAud_setLinkBootsType(s32 param_0) {
    mDoAud_zelAudio_c::getInterface()->setLinkBootsType(param_0);
}

inline void mDoAud_setLinkGroupInfo(u8 param_0) {
    mDoAud_zelAudio_c::getInterface()->setLinkGroupInfo(param_0);
}

inline void mDoAud_setLinkOnBoard(s32 param_0) {
    mDoAud_zelAudio_c::getInterface()->setLinkOnBoard(param_0);
}

inline void mDoAud_setLinkHp(s32 param_0, s32 param_1) {
    mDoAud_zelAudio_c::getInterface()->setLinkHp(param_0, param_1);
}

inline void mDoAud_bgmNowKaitengiri() {
    mDoAud_zelAudio_c::getInterface()->bgmNowKaitengiri();
}

inline void mDoAud_getCameraMapInfo(u32 param_0) {
    mDoAud_zelAudio_c::getInterface()->getCameraMapInfo(param_0);
}

inline void mDoAud_setCameraGroupInfo(u8 param_0) {
    mDoAud_zelAudio_c::getInterface()->setCameraGroupInfo(param_0);
}

inline void mDoAud_getCameraInfo(Vec* param_0, MtxP param_1, u32 param_2) {
    mDoAud_zelAudio_c::getInterface()->getCameraInfo(param_0, param_1, param_2);
}

inline void mDoAud_setShipSailState(s32 state) {
    mDoAud_zelAudio_c::getInterface()->setShipSailState(state);
}

inline void mDoAud_shipCruiseSePlay(cXyz* i_sePos, f32 param_1) {
    mDoAud_zelAudio_c::getInterface()->shipCruiseSePlay(i_sePos, param_1);
}

inline void mDoAud_monsSeInit() {
    mDoAud_zelAudio_c::getInterface()->monsSeInit();
}

inline void mDoAud_monsSeStart(u32 i_seNum, Vec* param_1, u32 param_2, u32 param_3) {
    mDoAud_zelAudio_c::getInterface()->monsSeStart(i_seNum, param_1, param_2, param_3, 0);
}

inline void mDoAud_monsSeStart(u32 i_seNum, Vec* param_1, u32 param_2, u32 param_3, s8 i_reverb) {
    mDoAud_zelAudio_c::getInterface()->monsSeStart(i_seNum, param_1, param_2, param_3, i_reverb);
}

inline void mDoAud_onEnemyDamage() {
    mDoAud_zelAudio_c::getInterface()->onEnemyDamage();
}

inline void mDoAud_bgmMuteMtDragon() {
    mDoAud_zelAudio_c::getInterface()->bgmMuteMtDragon();
}

inline void mDoAud_bgmHitSound(s32 param_0) {
    mDoAud_zelAudio_c::getInterface()->bgmHitSound(param_0);
}

inline void mDoAud_stSkyCloisters() {
    mDoAud_zelAudio_c::getInterface()->stSkyCloisters();
}

inline void mDoAud_setHour(s32 hour) {
    mDoAud_zelAudio_c::getInterface()->setHour(hour);
}

inline void mDoAud_setMinute(s32 min) {
    mDoAud_zelAudio_c::getInterface()->setMinute(min);
}

inline void mDoAud_setWeekday(s32 day) {
    mDoAud_zelAudio_c::getInterface()->setWeekday(day);
}

inline void mDoAud_setOutputMode(u32 mode) {
    mDoAud_zelAudio_c::getInterface()->setOutputMode(mode);
}

inline void mDoAud_rainPlay(s32 param_0) {
    mDoAud_zelAudio_c::getInterface()->rainPlay(param_0);
}

inline f32 mDoAud_tact_getMelodyPattern(s32 melody_no, s32 note_no, s32 * pattern) {
    return mDoAud_zelAudio_c::mTact.getMelodyPattern(melody_no, note_no, pattern);
}

inline void mDoAud_tact_reset() {
    mDoAud_zelAudio_c::getTact().reset();
}

inline u8 mDoAud_tact_getBeat() {
    return mDoAud_zelAudio_c::getTact().getBeat();
}

inline void mDoAud_tact_setBeat(s32 beat) {
    mDoAud_zelAudio_c::getTact().setBeat(beat);
}

inline f32 mDoAud_tact_getBeatFrames() {
    return mDoAud_zelAudio_c::getTact().getBeatFrames();
}

inline void mDoAud_tact_setVolume(f32 volume) {
    mDoAud_zelAudio_c::getTact().setVolume(volume);
}

inline void mDoAud_tact_play() {
    mDoAud_zelAudio_c::getTact().play();
}

inline void mDoAud_tact_ambientPlay() {
    mDoAud_zelAudio_c::getTact().ambientPlay();
}

inline void mDoAud_tact_setStickPos(s32 mainStick, s32 cStick) {
    mDoAud_zelAudio_c::getTact().setStickPos(mainStick, cStick);
}

inline void mDoAud_tact_playArmSwing(s32 mainStick, s32 cStick) {
    mDoAud_zelAudio_c::getTact().playArmSwing(mainStick, cStick);
}

inline void mDoAud_tact_stopArmSwing() {
    mDoAud_zelAudio_c::getTact().stopArmSwing();
}

inline s32 mDoAud_tact_judge(s32 param_1, s32 param_2) {
    return mDoAud_zelAudio_c::getTact().judge(param_1, param_2);
}

inline void mDoAud_tact_armSoundPlay(s32 param_1) {
    return mDoAud_zelAudio_c::getTact().armSoundPlay(param_1);
}

inline void mDoAud_tact_metronomePlay(s32 param_1, s32 param_2) {
    return mDoAud_zelAudio_c::getTact().metronomePlay(param_1, param_2);
}

inline void mDoAud_tact_melodyPlay(s32 param_1) {
    return mDoAud_zelAudio_c::getTact().melodyPlay(param_1);
}

inline void mDoAud_tact_melodyStop() {}

inline BOOL mDoAud_checkCbPracticePlay() {
    return mDoAud_zelAudio_c::getInterface()->checkCbPracticePlay();
}

inline void mDoAud_cbPracticePlay(Vec* pos) {
    mDoAud_zelAudio_c::getInterface()->cbPracticePlay(pos);
}

inline void mDoAud_cbPracticeStop() {
    mDoAud_zelAudio_c::getInterface()->cbPracticeStop();
}

inline void mDoAud_stWaterLevelUp() {
    mDoAud_zelAudio_c::getInterface()->stWaterLevelUp();
}

inline void mDoAud_stWaterLevelDown() {
    mDoAud_zelAudio_c::getInterface()->stWaterLevelDown();
}

inline void mDoAud_bgmNowBattle(f32 distance) {
    mDoAud_zelAudio_c::getInterface()->bgmNowBattle(distance);
}

inline void mDoAud_initSeaEnvPos() {
    mDoAud_zelAudio_c::getInterface()->initSeaEnvPos();
}

inline void mDoAud_registSeaEnvPos(Vec* param_0) {
    mDoAud_zelAudio_c::getInterface()->registSeaEnvPos(param_0);
}

inline void mDoAud_seaEnvSePlay(u32 param_0) {
    mDoAud_zelAudio_c::getInterface()->seaEnvSePlay(param_0, 0);
}

inline void mDoAud_startSeaShoreSE(Vec* param_0, u32 param_1) {
    mDoAud_zelAudio_c::getInterface()->seaShoreSE(param_1, param_0, 0, 0);
}

inline void mDoAud_continueSeaShoreSE(Vec* param_0, u32 param_1) {
    mDoAud_zelAudio_c::getInterface()->seaShoreSE(param_1, param_0, 1, 0);
}

inline void mDoAud_initRiverPos() {
    mDoAud_zelAudio_c::getInterface()->initRiverPos();
}

inline void mDoAud_registRiverPos(cXyz* param_0) {
    mDoAud_zelAudio_c::getInterface()->registRiverPos(param_0);
}

inline void mDoAud_riverSePlay(u8 param_0, s8 param_1) {
    mDoAud_zelAudio_c::getInterface()->riverSePlay(param_0, param_1);
}

inline void mDoAud_waterfallSePlay(u8 param_0, cXyz* param_1, s8 param_2) {
    mDoAud_zelAudio_c::getInterface()->waterfallSePlay(param_0, param_1, param_2);
}

inline void mDoAud_initWindowPos() {
    mDoAud_zelAudio_c::getInterface()->initWindowPos();
}

inline void mDoAud_registWindowPos(Vec* param_0) {
    mDoAud_zelAudio_c::getInterface()->registWindowPos(param_0);
}

inline void mDoAud_talkIn() {
    mDoAud_zelAudio_c::getInterface()->talkIn();
}

inline void mDoAud_talkOut() {
    mDoAud_zelAudio_c::getInterface()->talkOut();
}

inline void mDoAud_checkSePlaying(u32 param_0) {}
inline void mDoAud_heartGaugeOn() {}
inline void mDoAud_resetRecover() {}

#endif /* M_DO_AUDIO_H */
