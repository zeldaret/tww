#ifndef D_A_SWITEM_H
#define D_A_SWITEM_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

class daSwItem_c : public fopAc_ac_c {
public:
    /* 0x290 */ u8 m290[0x29C - 0x290];
    /* 0x29C */ dCcD_Stts mStts;
    /* 0x2D8 */ dCcD_Cyl mCyl;
    /* 0x408 */ u8 mAtTypeTrigger;
    /* 0x409 */ bool m409;
    /* 0x40A */ u8 m40A[0x40C - 0x40A];
};

#endif /* D_A_SWITEM_H */
