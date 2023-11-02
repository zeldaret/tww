#ifndef JASINST_H
#define JASINST_H

#include "JSystem/JAudio/JASOscillator.h"
#include "dolphin/types.h"

namespace JASystem {
    struct TInstParam {
        /* 0x00 */ u8 field_0x0;
        /* 0x04 */ int field_0x4;
        /* 0x08 */ TOscillator::Osc_** field_0x8;
        /* 0x0C */ int field_0xc;
        /* 0x10 */ f32 field_0x10;
        /* 0x14 */ f32 field_0x14;
        /* 0x18 */ f32 field_0x18;
        /* 0x1C */ f32 field_0x1c;
        /* 0x20 */ f32 field_0x20;
        /* 0x24 */ u8 field_0x24[0x2C - 0x24];
        /* 0x2C */ f32 field_0x2c;
        /* 0x30 */ f32 field_0x30;
        /* 0x34 */ f32 field_0x34;
        /* 0x38 */ u8 field_0x38;
        /* 0x3A */ short field_0x3a;
        /* 0x3C */ int field_0x3c;
    };
    class TInst {
    public:
        TInst() {}
        virtual ~TInst() {}
        virtual bool getParam(int, int, TInstParam*) const = 0;
        virtual u32 getType() const = 0;
        virtual int getKeymapIndex(int) const = 0;
    };
}

#endif /* JASINST_H */
