#ifndef D_A_SEATAG_H
#define D_A_SEATAG_H

#include "f_op/f_op_actor.h"

class daSeatag_c : public fopAc_ac_c {
public:
    inline cPhs_State create();
    inline BOOL draw();
    inline BOOL execute();

public:
    /* 0x290 */ request_of_phase_process_class mPhase; // Unused
};

#endif /* D_A_SEATAG_H */
