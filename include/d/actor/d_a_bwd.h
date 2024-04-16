#ifndef D_A_BWD_H
#define D_A_BWD_H

#include "f_op/f_op_actor.h"

class bwd_class : public fopAc_ac_c {
public:
    /* Place member variables here */
    /* 0x0290 */ u8 m0290[0x17C8 - 0x0290];
    /* 0x17C8 */ cXyz m17C8;
    /* 0x17D4 */ f32 m17D4;
    /* 0x17D8 */ s16 m17D8;
    /* 0x17DC */ f32 m17DC;
    /* 0x17E0 */ f32 m17E0;
};

class daBwd_HIO_c {
public:
    daBwd_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_BWD_H */
