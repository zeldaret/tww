#ifndef JASDSPDRIVERIF_H
#define JASDSPDRIVERIF_H

#include "dolphin/types.h"

namespace JASystem {
    namespace Driver {
        struct PanMatrix_ {
            /* 0x00 */ f32 mSound;
            /* 0x04 */ f32 mEffect;
            /* 0x08 */ f32 mChannel;
        };

        void init();
        void setMixerLevel(f32, f32);
        u16 getChannelLevel();
        u16 getAutoLevel();
        void setOutputMode(u32);
        u32 getOutputMode();
        u8 getUpdateInterval();

        inline f32 Clamp01(f32 value) {
            if (value <= 0.0f) {
                return 0.0f;
            }
            if (value >= 1.0f) {
                return 1.0f;
            }
            return value;
        }

        // TODO
        inline void getMixerLevel() {}

        extern u8 calc_sw_table[][3];

        extern u16 MAX_MIXERLEVEL;
        extern u16 MAX_AUTOMIXERLEVEL;
        extern u32 JAS_SYSTEM_OUTPUT_MODE;
        extern u8 JAS_UPDATE_INTERVAL;
    };
}

#endif /* JASDSPDRIVERIF_H */
