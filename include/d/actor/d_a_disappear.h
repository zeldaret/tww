#ifndef D_A_DISAPPEAR_H
#define D_A_DISAPPEAR_H

#include "f_op/f_op_actor.h"

class disappear_class : public fopAc_ac_c {
public:
    /* 0x290 */ u8 m290[0x298 - 0x290];
    /* 0x298 */ s32 mSwitchNo;
    /* 0x29C */ s16 mTimer;
};

#endif /* D_A_DISAPPEAR_H */
