#ifndef D_A_DR_H
#define D_A_DR_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"
#include "m_Do/m_Do_hostIO.h"

class JPABaseEmitter;
class mDoExt_McaMorf;

class dr_class : public fopAc_ac_c {
public:
    void setQuakeInfo() { m2C8 = 1; }

public:
    /* 0x290 */ u8 m290[0x2AC - 0x290];
    /* 0x2AC */ request_of_phase_process_class mPhs;
    /* 0x2B4 */ mDoExt_McaMorf* mpMorf;
    /* 0x2B8 */ u8 mMode;
    /* 0x2B9 */ u8 m2B9[0x2BA - 0x2B9];
    /* 0x2BA */ s16 mCountDownTimers[3];
    /* 0x2C0 */ int mCurrBckIdx;
    /* 0x2C4 */ JPABaseEmitter* mpBreathEmitter;
    /* 0x2C8 */ s8 m2C8;
    /* 0x2C9 */ s8 m2C9;
    /* 0x2CA */ u8 m2CA[0x2CC - 0x2CA];
};

class daDr_HIO_c : public JORReflexible {
public:
    daDr_HIO_c();
    virtual ~daDr_HIO_c() {}

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ f32 mScale;
    /* 0x0C */ bool m0C;
    /* 0x0D */ u8 m0D[0x0E - 0x0D];
    /* 0x0E */ s16 m0E;
    /* 0x10 */ f32 mWait1Morf;
    /* 0x14 */ f32 mAkubi1Morf;
    /* 0x18 */ f32 mBiku1Morf;
    /* 0x1C */ f32 mAbare1Morf;
    /* 0x20 */ f32 mAbare2Morf;
    /* 0x24 */ f32 mHo1Morf;
};

#endif /* D_A_DR_H */
