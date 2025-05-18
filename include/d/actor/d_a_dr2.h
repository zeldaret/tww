#ifndef D_A_DR2_H
#define D_A_DR2_H

#include "f_op/f_op_actor.h"

class dr2_class : public fopAc_ac_c {
public:
    /* 0x290 */ u8 field_0x290[0x3B0 - 0x290];
    /* 0x3B0 */ cXyz field_0x3B0;
    /* 0x3BC */ u8 field_0x3BC[0x4BA - 0x3BC];
    /* 0x4BA */ s16 field_0x4BA;
    /* 0x4BC */ u8 field_0x4BC[0x50C - 0x4BC];
};

class daDr2_HIO_c {
public:
    daDr2_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_DR2_H */
