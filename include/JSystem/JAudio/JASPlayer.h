#ifndef JASPLAYER_H
#define JASPLAYER_H

#include "JSystem/JAudio/JASOscillator.h"
#include "dolphin/types.h"

namespace JASystem {
    namespace Player {
        s16 extend8to16(u8 param_1);
        f32 pitchToCent(f32 param_1, f32 param_2);
        s32 getRandomS32();

        extern const f32 s_key_table[];
        extern const TOscillator::Osc_ sAdsrDef;
        extern const TOscillator::Osc_ sEnvelopeDef;
        extern const TOscillator::Osc_ sVibratoDef;
        extern const TOscillator::Osc_ sTremoroDef;
        extern s16 CUTOFF_TO_IIR_TABLE[];
        extern s16 sAdsTable[];
        extern s16 sRelTable[];
        extern s16 sVibTable[];
        extern s16 sTreTable[];
    }
}

#endif /* JASPLAYER_H */
