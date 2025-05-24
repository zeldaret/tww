#ifndef D_A_BTD_H
#define D_A_BTD_H

#include "f_op/f_op_actor.h"

class btd_class : public fopAc_ac_c {
public:
    /* Place member variables here */
    /* 0x0290 */ u8 field_0x290[0x2e4 - 0x290];
    /* 0x02E4 */ s16 field_0x2e4;
    /* 0x02E6 */ u8 field_0x2e6[0x6e16 - 0x2e6];
    /* 0x6E16 */ s16 field_0x6e16;
};

class daBtd_HIO_c {
public:
    daBtd_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_BTD_H */
