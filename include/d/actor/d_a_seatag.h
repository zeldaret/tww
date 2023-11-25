#ifndef D_A_SEATAG_H
#define D_A_SEATAG_H

#include "f_op/f_op_actor.h"

class daSeatag_c : public fopAc_ac_c {
public:
    inline s32 create();
    inline BOOL draw();
    inline BOOL execute();

public:
    /* 0x290 */ u8 m290[0x298 - 0x290];
};

#endif /* D_A_SEATAG_H */
