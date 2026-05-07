#ifndef D_A_KYTAG04_H
#define D_A_KYTAG04_H

#include "f_op/f_op_actor.h"

struct kytag04_class {
    /* 0x000 */ fopAc_ac_c actor;
    /* 0x290 */ u8 mState;
    /* 0x291 */ u8 mOffColPat;
    /* 0x292 */ u8 mOnColPat;
    /* 0x293 */ u8 mSwitchNo;
    /* 0x294 */ int mTimer;
    /* 0x298 */ int mTimerThreshold;
    /* 0x29C */ f32 mScaleX;
    /* 0x2A0 */ f32 mScaleY;
};

#endif /* D_A_KYTAG04_H */
