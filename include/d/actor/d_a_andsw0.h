#ifndef D_A_ANDSW0_H
#define D_A_ANDSW0_H

#include "f_op/f_op_actor.h"

class andsw0_class : public fopAc_ac_c {
public:
    /* 0x290 */ u32 _pad[2];
    /* 0x298 */ s8 mAction;
    /* 0x299 */ u8 mNumSwitchesToCheck;
    /* 0x29A */ u8 mBehaviorType;
    /* 0x29B */ u8 mSwitchToSet;
    /* 0x29C */ u8 mFirstSwitchToCheck;
    /* 0x29E */ u16 mTimer;
    /* 0x2A0 */ s16 mEventIdx;
    /* 0x2A2 */ u8 mEventNo;
    /* 0x2A3 */ s8 mEventState;
};

#endif /* D_A_ANDSW0_H */
