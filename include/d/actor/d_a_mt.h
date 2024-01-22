#ifndef D_A_MT_H
#define D_A_MT_H

#include "f_op/f_op_actor.h"

class mt_class : public fopEn_enemy_c {
public:
    /* Place member variables here */
    /* 0x02AC */ u8 m2AC[0x0454 - 0x02AC];
    /* 0x0454 */ u8 m454;
    /* 0x0455 */ u8 m455[0x1CC0 - 0x0455];
};

class daMt_HIO_c {
public:
    daMt_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_MT_H */
