#ifndef D_A_BDKOBJ_H
#define D_A_BDKOBJ_H

#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "d/d_bg_s_lin_chk.h"
#include "f_op/f_op_actor.h"

class dBgW;

struct bdo_eff_s {
    /* 0x000 */ s8 m000;
    /* 0x004 */ J3DModel* mpModel;
    /* 0x008 */ cXyz m008;
    /* 0x014 */ cXyz m014;
    /* 0x020 */ f32 m020;
    /* 0x024 */ f32 m024;
    /* 0x028 */ f32 m028; //SCALE
    /* 0x02C */ f32 m02C;
    /* 0x030 */ csXyz m030;
    /* 0x036 */ csXyz m036;
    /* 0x054 */ dCcD_Stts mStts;
    /* 0x078 */ dCcD_Sph mSph;
    /* 0x1A4 */ f32 m1A4;
    /* 0x1A8 */ s16 m1A8;
    /* 0x1AA */ s16 m1AA;
    /* 0x1AC */ s16 m1AC;
}; // size = 0x1B0

class bdkobj_class : public fopAc_ac_c {
public:
    request_of_phase_process_class mPhase;
    /* 0x298 */ u8 m298;
    /* 0x299 */ s8 m299;
    /* 0x29C */ bdo_eff_s mEffs[3];
    /* 0x7AC */ dCcD_Stts mStts;
    /* 0x7E8 */ dCcD_Cyl mCyl;
    /* 0x918 */ dPa_smokeEcallBack m918;
#if VERSION == VERSION_DEMO
    /* 0x938 */ JPABaseEmitter* m938_demo;
#endif
    /* 0x938 */ u8 m938;
    /* 0x93C */ Mtx mMtx;
    /* 0x96C */ dBgW* pm_bgw;
}; // size = 0x970

#endif /* D_A_BDKOBJ_H */
