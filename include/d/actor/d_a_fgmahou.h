#ifndef D_A_FGMAHOU_H
#define D_A_FGMAHOU_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "m_do/m_Do_ext.h"
#include "d/d_particle.h"

class fgmahou_class : public fopAc_ac_c {
public:
    u8 field_0x290[0x2AC - 0x290];
    request_of_phase_process_class mPhs;
    u8 field_0x2b4;
    mDoExt_McaMorf* mpMorf;
    mDoExt_btkAnm* mpBtk;
    mDoExt_brkAnm* mpBrk;
    s16 field_0x2C4;
    s16 field_0x2C6;
    cXyz field_0x2C8;
    s16 field_0x2D4;
    s16 field_0x2D6;
    s16 field_0x2D8;
    s16 field_0x2DA[2];
    s16 field_0x2DE;
    s16 field_0x2E0;
    s16 field_0x2E2;
    JPABaseEmitter* mpEmitter;
    dBgS_AcchCir mCir;
    /* do these */ dBgS_ObjAcch mAcch;
    dCcD_Stts mStts;
    /* do these */ dCcD_Sph mSph;
    /* do these */ dCcD_Sph mSph2;
    s8 field_0x780;
};

#endif /* D_A_FGMAHOU_H */
