#ifndef D_A_BTD_H
#define D_A_BTD_H

#include "f_op/f_op_actor.h"

class btd_class : public fopAc_ac_c {
public:
    /* Place member variables here */
    /* 0x0290 */ u8 field_0x0290[0x2e4 - 0x290];
    /* 0x02E4 */ s16 field_0x2e4;
    /* 0x02E6 */ u8 field_0x02E6[0x02F6 - 0x2e6];
    /* 0x02F6 */ bool field_0x2F6;
    /* 0x02F7 */ u8 field_0x02F7[0x0320 - 0x02F7];
    /* 0x0320 */ cXyz field_0x320;
    /* 0x032C */ cXyz field_0x32C;
    /* 0x0338 */ u8 field_0x0338[0x0360 - 0x0338];
    /* 0x0360 */ f32 field_0x360;
    /* 0x0364 */ u8 field_0x0364[0x6E16 - 0x0364];
    /* 0x6E16 */ s16 field_0x6e16;
};

class daBtd_HIO_c {
public:
    daBtd_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_BTD_H */
