#ifndef D_A_KYTAG04_H
#define D_A_KYTAG04_H

#include "f_op/f_op_actor.h"

class kytag04_class : public fopAc_ac_c {
public:
    /* 0x290 */ u8 mState;
    /* 0x291 */ u8 mOffColPat;
    /* 0x292 */ u8 mOnColPat;
    /* 0x293 */ u8 mSwitchID;
    /* 0x294 */ int mTimer;
    /* 0x298 */ int mTimerThresh;
    /* 0x29C */ f32 m29C;
    /* 0x2A0 */ f32 m2A0;
};

#endif /* D_A_KYTAG04_H */
