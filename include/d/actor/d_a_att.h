#ifndef D_A_ATT_H
#define D_A_ATT_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

class att_class : public fopAc_ac_c {
public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ u8 m298[0x02B5 - 0x0298];
    /* 0x2B5 */ u8 m2B5;
    /* 0x2B6 */ u8 m2B6[0x02B8 - 0x02B6];
    /* 0x2B8 */ dCcD_Stts mStts;
    /* 0x2F4 */ dCcD_Cyl mCyl;
    /* 0x424 */ dCcD_Sph mSph;
    /* 0x550 */ s8 m550;
};

#endif /* D_A_ATT_H */
