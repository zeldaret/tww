#ifndef D_A_KYTAG04_H
#define D_A_KYTAG04_H

#include "f_op/f_op_actor.h"

class kytag04_class : public fopAc_ac_c {
public:
    /* 0x290 */ u8 mState;
    /* 0x291 */ u8 mOffColPat;
    /* 0x292 */ u8 mOnColPat;
    /* 0x293 */ u8 mSwitchId;
    /* 0x294 */ int mTimer;
    /* 0x298 */ int mTimerThreshold;
    /* 0x29C */ f32 mScaleX;
    /* 0x2A0 */ f32 mScaleY;
};

#endif /* D_A_KYTAG04_H */
