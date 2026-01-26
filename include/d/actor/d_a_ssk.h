#ifndef D_A_SSK_H
#define D_A_SSK_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"

class mDoExt_McaMorf;
class JntHit_c;

struct ssk_class {
    /* 0x000 */ fopEn_enemy_c actor;
    /* 0x2AC */ request_of_phase_process_class mPhase;
    /* 0x2B4 */ u8 m2B4;
    /* 0x2B5 */ u8 m2B5;
    /* 0x2B6 */ u8 m2B6;
    /* 0x2B7 */ bool m2B7;
    /* 0x2B8 */ s16 m2B8;
    /* 0x2BA */ s16 m2BA;
    /* 0x2BC */ s16 m2BC;
    /* 0x2C0 */ f32 m2C0;
    /* 0x2C4 */ f32 m2C4;
    /* 0x2C8 */ mDoExt_McaMorf* mpMorf1;
    /* 0x2CC */ mDoExt_McaMorf* mpMorf2;
    /* 0x2D0 */ dPa_smokeEcallBack m2D0;
    /* 0x2F0 */ s16 m2F0;
    /* 0x2F2 */ s16 m2F2;
    /* 0x2F4 */ csXyz m2F4[5];
    /* 0x314 */ cXyz m314[5];
    /* 0x350 */ cXyz m350;
    /* 0x35C */ u8 m35C[0x398 - 0x35C];
    /* 0x398 */ dBgS_AcchCir mAcchCir;
    /* 0x3D8 */ dBgS_ObjAcch mAcch;
    /* 0x5A0 */ dCcD_Stts mStts;
    /* 0x5D8 */ dCcD_Cyl mCyl;
#if VERSION > VERSION_DEMO
    /* 0x708 */ JntHit_c* m708;
#endif
}; // size = 0x70C

#endif /* D_A_SSK_H */
