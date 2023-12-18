#ifndef JASAICTRL_H
#define JASAICTRL_H

#include "dolphin/types.h"

namespace JASystem {
    namespace Kernel {
        void init();
        void initSystem();
        void registerMixCallback(s16* (*)(s32), u8);
        void vframeWork();
        void updateDac();
        void mixMonoTrack(s16*, s32, s16* (*)(s32));
        void mixMonoTrackWide(s16*, s32, s16* (*)(s32));
        void mixExtraTrack(s16*, s32, s16* (*)(s32));
        void mixInterleaveTrack(s16*, s32, s16* (*)(s32));

        extern s16* dac[3];
        extern int JASUniversalDacCounter;
        extern s16* lastRspMadep;
        extern s16* useRspMadep;
        extern int vframeWorkRunning;
        extern void (*dacCallbackFunc)(s16*, u32);
        extern int JASVframeCounter;
        extern s16* (*extMixCallback)(s32);
        extern u8 extMixMode;

        inline void JASAiMixLimit16(s32) {} // TODO
    }
}

#endif /* JASAICTRL_H */
