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

        void getAddress(int) const {}
        void getBendSense() const {}
        void getFlag() const {}
        void getPanPowerBank() const {}
        void getPanPowerExt() const {}
        void getPanPowerOsc() const {}
        void getPanPowerParent() const {}
        void getPanPowerTrack() const {}
        void getPriority() const {}
        void setAddress(int, u32) {}
        void setFlag(u16) {}
        void setPanPower(int i, u16 power) { mPanPower[i] = power; }

        /* 0x00 */ u16 field_0x0[6];
        /* 0x0C */ u16 field_0xc;
        /* 0x0E */ u16 field_0xe;
        /* 0x10 */ u16 mPanPower[5];
        /* 0x1A */ u16 field_0x1a;
        /* 0x1C */ int field_0x1c;
        /* 0x20 */ int field_0x20;
        /* 0x24 */ int field_0x24;
        /* 0x28 */ int field_0x28;
        /* 0x2C */ int field_0x2c;
    };
}

#endif /* JASREGISTERPARAM_H */
