#ifndef D_A_JBO_H
#define D_A_JBO_H

#include "d/d_cc_d.h"
#include "f_op/f_op_actor.h"

class mDoExt_McaMorf;

enum daJbo_Type {
    daJbo_Type_NORMAL_e = 0,
    daJbo_Type_POPS_UP_e = 1,
    daJbo_Type_UNK_2_e = 2,
    daJbo_Type_APPEAR_AFTER_DEKU_TREE_e = 3,
};

struct jbo_class {
    /* 0x000 */ fopAc_ac_c actor;
    /* 0x290 */ u8 m290[0x2AC - 0x290];
    /* 0x2AC */ request_of_phase_process_class mPhs;
    /* 0x2B4 */ mDoExt_McaMorf* mpMorf;
    /* 0x2B8 */ u8 mType;
    /* 0x2B9 */ u8 m2B9[0x2B9 - 0x2B8];
    /* 0x2BA */ u8 m2BA;
    /* 0x2BB */ u8 m2BB;
    /* 0x2BC */ u8 mMode;
    /* 0x2BE */ s16 mFramesUntilJump;
    /* 0x2C0 */ s16 mAnimRotation;
    /* 0x2C2 */ s16 mAnimationSpeed;
    /* 0x2C4 */ cXyz mParticlePos;
    /* 0x2D0 */ dCcD_Stts mStts;
    /* 0x30C */ dCcD_Sph mCoSph;
};

STATIC_ASSERT(sizeof(jbo_class) == 0x438);

#endif /* D_A_JBO_H */
