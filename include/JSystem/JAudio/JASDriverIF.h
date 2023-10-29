#ifndef JASDSPDRIVERIF_H
#define JASDSPDRIVERIF_H

#include "dolphin/types.h"

namespace JASystem {
    namespace Driver {
        struct PanMatrix_ {
            /* 0x00 */ f32 field_0x0;
            /* 0x04 */ f32 field_0x4;
            /* 0x08 */ f32 field_0x8;
        };

        void init();
        void setMixerLevel(f32, f32);
        u16 getChannelLevel();
        u16 getAutoLevel();
        void setOutputMode(u32);
        u32 getOutputMode();
        u8 getUpdateInterval();

        extern u16 MAX_MIXERLEVEL;
        extern u16 MAX_AUTOMIXERLEVEL;
        extern u32 JAS_SYSTEM_OUTPUT_MODE;
        extern u8 JAS_UPDATE_INTERVAL;
    };
}

#endif /* JASDSPDRIVERIF_H */
