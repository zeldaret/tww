#ifndef D_A_BWDS_H
#define D_A_BWDS_H

#include "f_op/f_op_actor.h"

class bwds_class : public fopAc_ac_c {
public:
    /* Place member variables here */
    /* 0x0290 */ u8 m0290[0x04F4 - 0x0290];
    /* 0x04F4 */ u8 m04F4;
    /* 0x04F5 */ u8 m04F5[0x18CC - 0x04F5];
};

class daBwds_HIO_c {
public:
    daBwds_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_BWDS_H */
