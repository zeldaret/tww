#ifndef D_A_KANBAN_H
#define D_A_KANBAN_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"

class kanban_class : public fopAc_ac_c {
public:
    /* 0x290 */ u8 m290[0x2C0 - 0x290];
    /* 0x2C0 */ s16 m2C0;
    /* 0x2C2 */ u8 m2C2[0x310 - 0x2C2];
    /* 0x310 */ dBgS_AcchCir m310;
    /* 0x350 */ dBgS_Acch m350;
    /* 0x514 */ u8 m514[0x574 - 0x514];
    /* 0x574 */ dCcD_Stts m574;
    /* 0x5B0 */ dCcD_Cyl m5B0;
};

class daKanban_HIO_c {
public:
    daKanban_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_KANBAN_H */
