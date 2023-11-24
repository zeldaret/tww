#ifndef D_A_KYTAG04_H
#define D_A_KYTAG04_H

#include "f_op/f_op_actor.h"

class kytag04_class : public fopAc_ac_c {
public:
    /* 0x00 */ u8 mState;
    /* 0x01 */ u8 mOffColPat;
    /* 0x02 */ u8 mOnColPat;
    /* 0x03 */ u8 mSwitchId;
    /* 0x04 */ int mTimer;
    /* 0x08 */ int mTimerThreshold;
    /* 0x0C */ f32 mScaleX;
    /* 0x10 */ f32 mScaleY;
};  /* size = 0x2A0 */

#endif /* D_A_KYTAG04_H */
