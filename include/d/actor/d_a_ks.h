#ifndef D_A_KS_H
#define D_A_KS_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_bg_s_poly_info.h"

class ks_class : public fopEn_enemy_c {
public:
    /* 0x2AC */ u8 m2AC[0x44C - 0x2AC];
    /* 0x44C */ cBgS_PolyInfo m44C;
    /* 0x45C */ u8 m45C[0xC88 - 0x45C];
};

#endif /* D_A_KS_H */
