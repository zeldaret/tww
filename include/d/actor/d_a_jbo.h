#ifndef D_A_JBO_H
#define D_A_JBO_H

#include "d/d_cc_d.h"
#include "f_op/f_op_actor.h"

class mDoExt_McaMorf;

/**
 * Baba bulb
 * Only the lowest byte of fopAc_ac_c::base::mParameters is used,
 * It is expected to be:
 * - 0 - silently appears
 * - 1 - plays a popup sound and animation on spawn
 * - 2 - sets otherwise locally unused m2BA=1
 * - 3 - waits until an event bit is set, does nothing until then, after converts to 0
 * - 0xFF - converts to 0
 */
class jbo_class : public fopAc_ac_c {
public:
    /* 0x290 */ u8 m290[0x2AC - 0x290];
    /* 0x2AC */ request_of_phase_process_class mPhs;
    /* 0x2B4 */ mDoExt_McaMorf* mpMorf;

    /* 0x2B8 */ u8 mParam;
    /* 0x2B9 */ u8 m2B9[0x2B9 - 0x2B8];
    // FIXME: give following two fields names if external use is spotted
    /* 0x2BA */ u8 m2BA;
    /* 0x2BB */ u8 m2BB;
    /* 0x2BC */ u8 mState;
    /* 0x2BE */ s16 mFramesUntilJump;
    /* 0x2C0 */ s16 mAnimRotation;
    /* 0x2C2 */ s16 mAnimationSpeed;
    /* 0x2C4 */ cXyz mParticlePos;
    /* 0x2D0 */ dCcD_Stts mStts;
    /* 0x30C */ dCcD_Sph mSph;
};

STATIC_ASSERT(sizeof(jbo_class) == 0x438);

#endif /* D_A_JBO_H */
