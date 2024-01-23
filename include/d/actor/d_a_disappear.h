#ifndef D_A_DISAPPEAR_H
#define D_A_DISAPPEAR_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"

class disappear_class : public fopAc_ac_c {
public:
    /* 0x290 */ request_of_phase_process_class mPhase; // Unused
    /* 0x298 */ s32 mItemBitNo;
    /* 0x29C */ s16 mTimer;
};

#endif /* D_A_DISAPPEAR_H */
