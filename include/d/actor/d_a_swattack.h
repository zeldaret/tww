#ifndef D_A_SWATTACK_H
#define D_A_SWATTACK_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

class daSwAt_c : public fopAc_ac_c {
public:
    void CreateInit();

public:
    /* 0x290 */ u8 m290[0x29C - 0x290];
    /* 0x29C */ dCcD_Stts mStts;
    /* 0x2D8 */ dCcD_Cyl mCyl;
    /* 0x408 */ u8 m408[0x410 - 0x408];
};

#endif /* D_A_SWATTACK_H */
