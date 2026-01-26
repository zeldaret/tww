#ifndef D_A_SK_H
#define D_A_SK_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

class mDoExt_McaMorf;

struct sk_class {
    /* 0x000 */ fopEn_enemy_c actor;
    /* 0x2AC */ request_of_phase_process_class mPhase;
    /* 0x2B4 */ u8 m2B4;
    /* 0x2B5 */ u8 m2B5;
    /* 0x2B8 */ mDoExt_McaMorf* mpMorf;
    /* 0x2BC */ bool m2BC;
    /* 0x2BE */ s16 m2BE;
#if VERSION > VERSION_DEMO
    /* 0x2C0 */ s16 m2C0;
#endif
    /* 0x2C2 */ csXyz m2C2[4];
    /* 0x2DC */ cXyz m2DC[4];
    /* 0x30C */ dCcD_Stts mStts;
    /* 0x348 */ dCcD_Sph m348[5];
#if VERSION > VERSION_DEMO
    /* 0x924 */ JntHit_c* m924;
#endif
}; // size = 0x928

#endif /* D_A_SK_H */
