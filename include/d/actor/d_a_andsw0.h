#ifndef D_A_ANDSW0_H
#define D_A_ANDSW0_H

#include "f_op/f_op_actor.h"

class andsw0_class : public fopAc_ac_c {
public:
    /* 0x290 */ u8 m290[0x298 - 0x290];
    /* 0x298 */ d_a_andsw0__States mState;
    /* 0x299 */ u8 mNumSwitchesToCheck;
    /* 0x29A */ u8 mBehaviorType;
    /* 0x29B */ u8 mSwitchToSet;
    /* 0x29C */ u8 mFirstSwitchToCheck;
    /* 0x29D */ u8 m29D[0x29E - 0x29D];
    /* 0x29E */ s16 mTimer;
    /* 0x2A0 */ s16 mEventEventListDatIndex;
    /* 0x2A2 */ u8 mEventEVNTIndex;
    /* 0x2A3 */ u8 m2A3;
};

#endif /* D_A_ANDSW0_H */
