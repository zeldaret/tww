#ifndef JASRATE_H
#define JASRATE_H

#include "dolphin/types.h"

namespace JASystem {
    namespace Kernel {
        extern f32 gDacRate;
        extern u32 gSubFrames;
        extern u32 gFrameSamples;
        extern u32 gDacSize;
        extern int gOutputRate;
        extern int gAiSetting;

        inline f32 getDacRate() { return gDacRate; }
        inline u32 getSubFrames() { return gSubFrames; }
        inline u32 getFrameSamples() { return gFrameSamples; }
        inline u32 getDacSize() { return gDacSize; }
        inline int getOutputRate() { return gOutputRate; }
        inline int getAiSetting() { return gAiSetting; }
    }
}

#endif /* JASRATE_H */
