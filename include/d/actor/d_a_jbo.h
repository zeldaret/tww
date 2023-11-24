#ifndef D_A_JBO_H
#define D_A_JBO_H

#include "f_op/f_op_actor.h"

class jbo_class : public fopAc_ac_c {
public:
    /* 0x290 */ u8 m290[0x2BE - 0x290];
    /* 0x2BE */ s16 m2BE;
    /* 0x2C0 */ u8 m2C0[0x438 - 0x2C0];
};

#endif /* D_A_JBO_H */
