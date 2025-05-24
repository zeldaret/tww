#ifndef JASREGISTERPARAM_H
#define JASREGISTERPARAM_H

#include "dolphin/types.h"
#include "JSystem/JUtility/JUTAssert.h"

namespace JASystem {
    class TRegisterParam {
    public:
        static const u8 PARAM_REG_XY = 0x23;
        static const u8 PARAM_REG_AR0 = 0x28;
        static const u8 PARAM_REG_AR3 = 0x2B;

        TRegisterParam();
        void init();
        void inherit(const TRegisterParam&);
        u8 getBankNumber() const;
        u8 getProgramNumber() const;

        u32 getAddress(int index) const {
            JUT_ASSERT(130, index >= 0);
            JUT_ASSERT(131, index < 4);
            return field_0x20[index];
        }
        void setAddress(int, u32) {}

        void getBendSense() const {}
        void getPanPowerBank() const {}
        void getPanPowerExt() const {}
        void getPanPowerOsc() const {}
        void getPanPowerParent() const {}
        void getPanPowerTrack() const {}
        void getPriority() const {}
        u16 getFlag() const { return field_0x0[3]; }
        void setFlag(u16 flag) { field_0x0[3] = flag; }
        void setPanPower(int i, u16 power) { mPanPower[i] = power; }

        /* 0x00 */ u16 field_0x0[6];
        /* 0x0C */ u16 field_0xc;
        /* 0x0E */ u16 field_0xe;
        /* 0x10 */ u16 mPanPower[5];
        /* 0x1A */ u16 field_0x1a;
        /* 0x1C */ int field_0x1c;
        /* 0x20 */ u32 field_0x20[4];
    };
}

#endif /* JASREGISTERPARAM_H */
