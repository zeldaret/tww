#ifndef M_DO_AUDIO_H
#define M_DO_AUDIO_H

#include "JAZelAudio/JAIZelBasic.h"
#include "JAZelAudio/JAIZelInst.h"

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
    static void offInitFlag() { mInitFlag = false; }

    static bool isBgmSet() { return mBgmSet; }
    static void offBgmSet() { mBgmSet = false; }

    static void setLoadTimer(u8 i_timer) { mLoadTimer = i_timer; }
    static u8 getLoadTimer() { return mLoadTimer; }

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
int mDoAud_load1stDynamicWave();

extern JKRSolidHeap* g_mDoAud_audioHeap;

inline void mDoAud_bgmStart(u32 param_0) {
    mDoAud_zelAudio_c::getInterface()->bgmStart(param_0, 0, 0);
}

inline void mDoAud_subBgmStart(u32 param_0) {
    mDoAud_zelAudio_c::getInterface()->subBgmStart(param_0);
}

inline void mDoAud_bgmStreamPrepare(u32 id) {
    mDoAud_zelAudio_c::getInterface()->bgmStreamPrepare(id);
}

inline void mDoAud_bgmStreamPlay() {
    mDoAud_zelAudio_c::getInterface()->bgmStreamPlay();
}

inline void mDoAud_bgmStop(u32 param_0) {
    mDoAud_zelAudio_c::getInterface()->bgmStop(param_0, 0);
}

inline void mDoAud_prepareLandingDemo(u32 idx) {
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

inline void mDoAud_load2ndDynamicWave() {
    mDoAud_zelAudio_c::getInterface()->load2ndDynamicWave();
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

inline void mDoAud_seStart(u32 i_sfxID, Vec* i_sePos = NULL, u32 param_2 = 0, s8 i_reverb = 0) {
    mDoAud_zelAudio_c::getInterface()->seStart(i_sfxID, i_sePos, param_2, i_reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
}

inline void mDoAud_bgmSetSwordUsing(s32 param_1) {
    mDoAud_zelAudio_c::getInterface()->bgmSetSwordUsing(param_1);
}

inline void mDoAud_seStop(u32 i_sfxID, s32 param_2) {
    mDoAud_zelAudio_c::getInterface()->seStop(i_sfxID, param_2);
}

inline void mDoAud_seStopActor(Vec* param_1, u32 param_2) {
    mDoAud_zelAudio_c::getInterface()->seStopActor(param_1, param_2);
}

inline void mDoAud_seDeleteObject(Vec* i_sePos) {
    mDoAud_zelAudio_c::getInterface()->seDeleteObject(i_sePos);
}

inline u8 mDoAud_getLinkVoiceVowel(u32 param_1) {
    return mDoAud_zelAudio_c::getInterface()->getLinkVoiceVowel(param_1);
}

inline void mDoAud_linkVoiceStart(u32 i_sfxID, Vec* i_sePos, u8 param_3, s8 param_4) {
    mDoAud_zelAudio_c::getInterface()->linkVoiceStart(i_sfxID, i_sePos, param_3, param_4);
}

inline void mDoAud_monsSeStart(u32 param_0, Vec* param_1, u32 param_2, u32 param_3, s8 i_reverb) {
    mDoAud_zelAudio_c::getInterface()->monsSeStart(param_0, param_1, param_2, param_3, i_reverb);
}

inline void mDoAud_onEnemyDamage() {
    mDoAud_zelAudio_c::getInterface()->onEnemyDamage();
}

inline void mDoAud_bgmMuteMtDragon() {
    mDoAud_zelAudio_c::getInterface()->bgmMuteMtDragon();
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

inline void mDoAud_rainPlay(s32 param_0) {
    mDoAud_zelAudio_c::getInterface()->rainPlay(param_0);
}

inline f32 mDoAud_tact_getMelodyPattern(s32 melody_no, s32 note_no, s32 * pattern) {
    return mDoAud_zelAudio_c::mTact.getMelodyPattern(melody_no, note_no, pattern);
}

inline BOOL mDoAud_checkCbPracticePlay() {
    return mDoAud_zelAudio_c::getInterface()->checkCbPracticePlay();
}

inline void mDoAud_cbPracticePlay(Vec* pos) {
    mDoAud_zelAudio_c::getInterface()->cbPracticePlay(pos);
}

inline void mDoAud_cbPracticeStop() {
    mDoAud_zelAudio_c::getInterface()->cbPracticeStop();
}

#endif /* M_DO_AUDIO_H */
