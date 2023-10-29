#ifndef JASOSCILLATOR_H
#define JASOSCILLATOR_H

#include "dolphin/types.h"

namespace JASystem {
    class TOscillator {
    public:
        struct Osc_ {
            /* 0x00 */ u8 field_0x0;
            /* 0x04 */ f32 field_0x4;
            /* 0x08 */ void* table;
            /* 0x0C */ void* rel_table;
            /* 0x10 */ f32 field_0x10;
            /* 0x14 */ f32 field_0x14;
        };

        TOscillator() { init(); }
        ~TOscillator() {}
        void init();
        void initStart();
        f32 getOffset();
        bool forceStop();
        bool release();
        void calc(s16*);

        /* 0x00 */ const Osc_* field_0x0;
        /* 0x04 */ u8 field_0x4;
        /* 0x05 */ u8 field_0x5;
        /* 0x06 */ short field_0x6;
        /* 0x08 */ f32 field_0x8;
        /* 0x0C */ f32 field_0xc;
        /* 0x10 */ f32 field_0x10;
        /* 0x14 */ f32 field_0x14;
        /* 0x18 */ u16 field_0x18;
        /* 0x1C */ f32 field_0x1c;
    };
}

#endif /* JASOSCILLATOR_H */
