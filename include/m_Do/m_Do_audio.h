#ifndef M_DO_AUDIO_H
#define M_DO_AUDIO_H

#include "JAZelAudio/JAIZelBasic.h"

class mDoAud_zelAudio_c : public JAIZelBasic {
public:
    mDoAud_zelAudio_c() {}

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
};

extern mDoAud_zelAudio_c g_mDoAud_zelAudio;

void mDoAud_setSceneName(const char*, s32, s32);
void mDoAud_Execute();
BOOL mDoAud_isUsedHeapForStreamBuffer();
int mDoAud_load1stDynamicWave();

extern JKRSolidHeap* g_mDoAud_audioHeap;

inline void mDoAud_bgmStop(u32 param_0) {
    mDoAud_zelAudio_c::getInterface()->bgmStop(param_0, 0);
}

inline void mDoAud_sceneBgmStart() {
    mDoAud_zelAudio_c::getInterface()->sceneBgmStart();
}

inline void mDoAud_load2ndDynamicWave() {
    mDoAud_zelAudio_c::getInterface()->load2ndDynamicWave();
}

inline void mDoAud_resetProcess() {
    if (mDoAud_zelAudio_c::isResetFlag()) {
        mDoAud_zelAudio_c::getInterface()->resetProcess();
        mDoAud_zelAudio_c::onResetFlag();
    }
}

inline void mDoAud_seStart(u32 i_sfxID, Vec* i_sePos, u32 param_2, s8 i_reverb) {
    mDoAud_zelAudio_c::getInterface()->seStart(i_sfxID, i_sePos, param_2, i_reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
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

#endif /* M_DO_AUDIO_H */
