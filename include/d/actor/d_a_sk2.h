#ifndef D_A_SK2_H
#define D_A_SK2_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_acch.h"

class mDoExt_McaMorf;
class dBgWDeform;

struct sk2_class {
    /* 0x000 */ fopEn_enemy_c actor;
    /* 0x2AC */ request_of_phase_process_class mPhase;
    /* 0x2B4 */ u8 m2B4;
    /* 0x2B5 */ u8 m2B5;
    /* 0x2B6 */ u8 m2B6;
    /* 0x2B8 */ u8 m2B8[0x2BA - 0x2B8];
    /* 0x2BA */ s16 m2BA;
    /* 0x2BC */ s16 m2BC;
    /* 0x2C0 */ f32 m2C0;
    /* 0x2C4 */ f32 m2C4;
    /* 0x2C8 */ mDoExt_McaMorf* mpMorf;
    /* 0x2CC */ s16 m2CC;
    /* 0x2CE */ csXyz m2CE[4];
    /* 0x2E8 */ cXyz m2E8[4];
    /* 0x318 */ u8 m318[0x31C - 0x318];
    /* 0x31C */ dBgWDeform* mpBgW;
    /* 0x320 */ dBgS_AcchCir mAcchCir;
    /* 0x360 */ dBgS_ObjAcch mAcch;
}; // size = 0x524

#endif /* D_A_SK2_H */
