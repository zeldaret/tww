#ifndef D_A_DR_H
#define D_A_DR_H

#include "f_op/f_op_actor.h"
#include "JSystem/JParticle/JPAEmitter.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"

class dr_class : public fopAc_ac_c {
public:
    void setQuakeInfo() {}

public:
    /* 0x290 */ u8 m290[0x2AC - 0x290];
    /* 0x2AC */ request_of_phase_process_class mPhs;
    /* 0x2B4 */ mDoExt_McaMorf* mpMorf;
    /* 0x2B8 */ u8 mState;
    /* 0x2B9 */ u8 m2B9[0x2BA - 0x2B9];
    /* 0x2BA */ s16 mCountDownTimers[3];
    /* 0x2C0 */ int mCurrBckIdx;
    /* 0x2C4 */ JPABaseEmitter* m2C4;
    /* 0x2C8 */ s8 m2C8;
    /* 0x2C9 */ s8 m2C9;
    /* 0x2CA */ u8 m2CA[0x2CC - 0x2CA];
};

#endif /* D_A_DR_H */
