#ifndef JASREGISTERPARAM_H
#define JASREGISTERPARAM_H

#include "dolphin/types.h"
#include "JSystem/JUtility/JUTAssert.h"

namespace JASystem {
    class TRegisterParam {
    public:
        enum {
            /* 0x23 */ PARAM_REG_XY = 0x23,
            /* 0x28 */ PARAM_REG_AR0 = 0x28,
            /* 0x29 */ PARAM_REG_AR1 = 0x29,
            /* 0x2A */ PARAM_REG_AR2 = 0x2A,
            /* 0x2B */ PARAM_REG_AR3 = 0x2B,
        };

        TRegisterParam();
        void init();
        void inherit(const TRegisterParam&);
        u8 getBankNumber() const;
        u8 getProgramNumber() const;

        u32 getAddress(int index) const {
            JUT_ASSERT(130, index >= 0);
            JUT_ASSERT(131, index < 4);
            return mAddress[index];
        }
        void setAddress(int index, u32 value) {
            JUT_ASSERT(124, index >= 0);
            JUT_ASSERT(125, index < 4);
            mAddress[index] = value;
        }

        u16 getPanPowerBank() const {
            return mPanPower[0];
        }
        u16 getPanPowerExt() const {
            return mPanPower[1];
        }
        u16 getPanPowerOsc() const {
            return mPanPower[2];
        }
        u16 getPanPowerParent() const {
            return mPanPower[3];
        }
        u16 getPanPowerTrack() const {
            return mPanPower[4];
        }
        void setPanPower(int i, u16 power) { mPanPower[i] = power; }

        u16 getFlag() const { return field_0x0[3]; }
        void setFlag(u16 flag) { field_0x0[3] = flag; }

        // TODO
        void getBendSense() const {}
        void getPriority() const {}

    // private:
        /* 0x00 */ u16 field_0x0[6]; // TODO unsure how long this array really is
        /* 0x0C */ u16 field_0xc;
        /* 0x0E */ u16 field_0xe; // BendSense?
        /* 0x10 */ u16 mPanPower[5];
        /* 0x1A */ u16 field_0x1a; // Priority?
        /* 0x1C */ int field_0x1c;
        /* 0x20 */ u32 mAddress[4];
    };
}

#endif /* JASREGISTERPARAM_H */
