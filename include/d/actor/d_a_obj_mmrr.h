#ifndef D_A_OBJ_MMRR_H
#define D_A_OBJ_MMRR_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "m_Do/m_Do_ext.h"

class J3DModel;

namespace daObjMmrr {

class Eff_c : public dPa_followEcallBack {
public:
    Eff_c() : dPa_followEcallBack(0, 0) {}
    void end();
    void remove();
};

class Act_c : public fopAc_ac_c {
public:
    void setup(const cXyz* i_pos) {
        current.pos = *i_pos;
        mBF8 = 1;
    }

    static BOOL solidHeapCB(fopAc_ac_c*);
    bool create_heap();
    void init_cc();
    void set_cc_rec_pos();
    void set_cc_trans_pos();
    void set_cull();
    cPhs_State _create();
    bool _delete();
    void set_mtx();
    void init_mtx();
    bool chk_light();
    void eff_start();
    void eff_stop();
    void eff_remove();
    bool _execute();
    bool _draw();

    static const char M_arcname[];
    static const dCcD_SrcTri M_tri_src;
    static const dCcD_SrcCps M_cps_src;

public:
    /* 0x290 */ request_of_phase_process_class mResLoad;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ J3DModel* mpModelYssmr;
    /* 0x2A0 */ mDoExt_btkAnm mBtkAnm0;
    /* 0x2B4 */ mDoExt_btkAnm mBtkAnm1;
    /* 0x2C8 */ dCcD_Tri mTri[5];
    /* 0x958 */ dCcD_Stts mStts[5];
    /* 0xA84 */ dCcD_Cps mCps;
    /* 0xBBC */ dCcD_Stts mCpsStts;
    /* 0xBF8 */ u8 mBF8;
    /* 0xBF9 */ bool mBF9;
    /* 0xBFA */ u8 pad_0xBFA[2];
    /* 0xBFC */ f32 mLightIntensity;
    /* 0xC00 */ f32 mBeamLength;
    /* 0xC04 */ Eff_c mEff;
};  // Size: 0xC18

};  // namespace daObjMmrr

#endif /* D_A_OBJ_MMRR_H */
