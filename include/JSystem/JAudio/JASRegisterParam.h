#ifndef JASREGISTERPARAM_H
#define JASREGISTERPARAM_H

#include "dolphin/types.h"

namespace JASystem {
    class TRegisterParam {
    public:
        TRegisterParam();
        void init();
        void inherit(const TRegisterParam&);
        u8 getBankNumber() const;
        u8 getProgramNumber() const;

        /* 0x00 */ short field_0x0;
        /* 0x02 */ short field_0x2;
        /* 0x04 */ short field_0x4;
        /* 0x06 */ short field_0x6;
        /* 0x08 */ short field_0x8;
        /* 0x0A */ short field_0xa;
        /* 0x0C */ u16 field_0xc;
        /* 0x0E */ u16 field_0xe;
        /* 0x10 */ u16 field_0x10[5];
        /* 0x1A */ u16 field_0x1a;
        /* 0x1C */ int field_0x1c;
        /* 0x20 */ int field_0x20;
        /* 0x24 */ int field_0x24;
        /* 0x28 */ int field_0x28;
        /* 0x2C */ int field_0x2c;
    };
}

#endif /* JASREGISTERPARAM_H */
