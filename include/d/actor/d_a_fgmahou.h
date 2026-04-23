#ifndef D_A_FGMAHOU_H
#define D_A_FGMAHOU_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_particle.h"

class fgmahou_class : public fopAc_ac_c {
public:
    /* 0x290 */ u8 field_0x290[0x2AC - 0x290];
    /* 0x2AC */ request_of_phase_process_class mPhs;
    /* 0x2B4 */ u8 mOrbNumber; // which of Phantom Ganon's 8 orbs this is
    /* 0x2B8 */ mDoExt_McaMorf* mpMorf;
    /* 0x2BC */ mDoExt_btkAnm* mpBtk;
    /* 0x2C0 */ mDoExt_brkAnm* mpBrk;
    /* 0x2C4 */ s16 mAge;
    /* 0x2C6 */ s16 mState;
    /* 0x2C8 */ cXyz mTargetPos;
    /* 0x2D4 */ s16 field_0x2D4;
    /* 0x2D6 */ s16 field_0x2D6;
    /* 0x2D8 */ s16 field_0x2D8;
    /* 0x2DA */ s16 mTimers[2];
    /* 0x2DE */ s16 field_0x2DE;
    /* 0x2E0 */ s16 field_0x2E0;
    /* 0x2E2 */ s16 field_0x2E2;
    /* 0x2E4 */ JPABaseEmitter* mpEmitter;
    /* 0x2E8 */ dBgS_AcchCir mCir;
    /* 0x328 */ dBgS_ObjAcch mAcch;
    /* 0x4EC */ dCcD_Stts mStts;
    /* 0x528 */ dCcD_Sph mAtSph;
    /* 0x654 */ dCcD_Sph mTgSph;
    /* 0x780 */ s8 field_0x780;
}; // Size: 0x784

#endif /* D_A_FGMAHOU_H */
