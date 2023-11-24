#ifndef D_A_KLFT_H
#define D_A_KLFT_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"

class klft_class : public fopAc_ac_c {
public:
    /* 0x000 */ fopAc_ac_c* m000;
    /* 0x004 */ u8 m004[0x33C - 0x004];
    /* 0x33C */ dBgW* m33C;
    /* 0x340 */ u8 m340[0x9F0 - 0x340];
};

#endif /* D_A_KLFT_H */
