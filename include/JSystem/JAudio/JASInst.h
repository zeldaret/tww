#ifndef JASINST_H
#define JASINST_H

#include "JSystem/JAudio/JASOscillator.h"
#include "dolphin/types.h"

namespace JASystem {
    struct TInstParam {
        TInstParam() {
            field_0x0 = 0;
            field_0x4 = 0;
            mOscData = NULL;
            mOscCount = 0;
            field_0x10 = 1.0f;
            field_0x14 = 1.0f;
            field_0x18 = 1.0f;
            field_0x1c = 1.0f;
            field_0x20 = 0.5f;
            field_0x24 = 0.0f;
            field_0x28 = 0.0f;
            field_0x2c = 0.5f;
            field_0x30 = 0.0f;
            field_0x34 = 0.0f;
            field_0x38 = 0;
            field_0x3a = 0;
            field_0x3c = 0;
            field_0x40 = 0;
        }

        /* 0x00 */ u8 field_0x0;
        /* 0x04 */ int field_0x4;
        /* 0x08 */ TOscillator::Osc_** mOscData;
        /* 0x0C */ u32 mOscCount;
        /* 0x10 */ f32 field_0x10;
        /* 0x14 */ f32 field_0x14;
        /* 0x18 */ f32 field_0x18;
        /* 0x1C */ f32 field_0x1c;
        /* 0x20 */ f32 field_0x20;
        /* 0x24 */ f32 field_0x24;
        /* 0x28 */ f32 field_0x28;
        /* 0x2C */ f32 field_0x2c;
        /* 0x30 */ f32 field_0x30;
        /* 0x34 */ f32 field_0x34;
        /* 0x38 */ u8 field_0x38;
        /* 0x3A */ u16 field_0x3a;
        /* 0x3C */ int field_0x3c;
        /* 0x40 */ int field_0x40;
    };
    class TInst {
    public:
        TInst() {}
        virtual ~TInst() {}
        virtual bool getParam(int, int, TInstParam*) const = 0;
        virtual u32 getType() const = 0;
    };
}

#endif /* JASINST_H */
