#ifndef D_A_MANT_H
#define D_A_MANT_H

#include "f_op/f_op_actor.h"

class mant_class : public fopAc_ac_c {
public:
    /* 0x0290 */ u8 m0290[0x1BEC - 0x0290];
    /* 0x1BEC */ cXyz m1BEC;
    /* 0x1BF8 */ u8 m1BF8[0x283C - 0x1BF8];
};

#endif /* D_A_MANT_H */
