#ifndef D_A_KN_H
#define D_A_KN_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_acch.h"
#include "d/d_particle.h"

class mDoExt_McaMorf;

struct kn_class {
    /* 0x000 */ fopEn_enemy_c actor;
    /* 0x2AC */ request_of_phase_process_class mPhase;
    /* 0x2B4 */ u8 m2B4;
    /* 0x2B5 */ u8 m2B5;
    /* 0x2B6 */ u8 m2B6[0x2B8 - 0x2B6];
    /* 0x2B8 */ mDoExt_McaMorf* mpMorf;
    /* 0x2BC */ u8 m2BC;
    /* 0x2BD */ u8 m2BD;
    /* 0x2BE */ u8 m2BE;
    /* 0x2BF */ u8 m2BF;
    /* 0x2C0 */ u8 m2C0;
    /* 0x2C1 */ u8 m2C1[0x2C2 - 0x2C1];
    /* 0x2C2 */ s16 m2C2[4];
    /* 0x2CA */ s16 m2CA;
    /* 0x2CC */ f32 m2CC;
    /* 0x2D0 */ s16 m2D0;
    /* 0x2D2 */ s16 m2D2;
    /* 0x2D4 */ s16 m2D4;
    /* 0x2D6 */ u8 m2D6[0x2DC - 0x2D6];
    /* 0x2DC */ f32 m2DC;
    /* 0x2E0 */ f32 m2E0;
    /* 0x2E4 */ f32 m2E4;
    /* 0x2E8 */ f32 m2E8;
    /* 0x2EC */ cXyz m2EC;
    /* 0x2F8 */ csXyz m2F8;
    /* 0x2FE */ u8 m2FE[0x300 - 0x2FE];
    /* 0x300 */ cXyz m300;
    /* 0x30C */ u8 m30C[0x314 - 0x30C];
    /* 0x314 */ dPa_smokeEcallBack m314;
    /* 0x334 */ JPABaseEmitter* m334;
    /* 0x338 */ dBgS_AcchCir mAcchCir;
    /* 0x378 */ dBgS_ObjAcch mAcch;
}; // size = 0x53C

#endif /* D_A_KN_H */
