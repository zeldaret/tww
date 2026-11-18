#ifndef D_A_OBJ_FIREWALL_H
#define D_A_OBJ_FIREWALL_H

#include "f_op/f_op_actor.h"
#include "d/d_a_obj.h"
#include "d/d_cc_d.h"
#include "d/d_kankyo.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"

class dBgW;
class JPABaseEmitter;

class daObjFirewall_c : public fopAc_ac_c {
public:
    enum Param_e {
        PRM_SWSAVE_W = 8,
        PRM_SWSAVE_S = 0,
    };

    typedef void (daObjFirewall_c::*ActProc)();

    int param_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
    void init_mtx();
    static BOOL solidHeapCB(fopAc_ac_c*);
    bool create_heap();
    void registCollisionTable();
    void setPointLight();
    void particle_set();
    void particle_delete();
    void seStart(unsigned long);
    void set_se(bool);
    void seDelete();
    void set_pl_se();
    void setup_burn_up();
    void setup_put_the_fire_out();
    cPhs_State _create();
    bool _delete();
    void wait_act_proc();
    void wait2_act_proc();
    void wait3_act_proc();
    void appear_act_proc();
    void demo_end_wait_act_proc();
    void burn_wait_act_proc();
    void retire_act_proc();
    bool _execute();
    bool _draw();

public:
    /* 0x0290 */ request_of_phase_process_class mPhase;
    /* 0x0298 */ dCcD_Stts mStts;
    /* 0x02D4 */ dCcD_Cyl mCyl;
    /* 0x0404 */ J3DModel* mpModel;
    /* 0x0408 */ dBgW* mpBgW;
    /* 0x040C */ mDoExt_btkAnm mBtk;
    /* 0x0420 */ mDoExt_brkAnm mBrk;
    /* 0x0438 */ JPABaseEmitter* mpEmitter0[6];
    /* 0x0450 */ JPABaseEmitter* mpEmitter1[5];
    /* 0x0464 */ JPABaseEmitter* mpEmitter2;
    /* 0x0468 */ int mSwSave;
    /* 0x046C */ LIGHT_INFLUENCE mLight[0x40];
    /* 0x0C6C */ cXyz mLightPos[0x40];
    /* 0x0F6C */ u8 field_0xf6c[0x106C - 0xF6C];
    /* 0x106C */ f32 mLightPower;
    /* 0x1070 */ ActProc mActProc;
    /* 0x107C */ s16 mEventIdx;
    /* 0x107E */ u8 mSeOn;
    /* 0x107F */ u8 field_0x107f;
    /* 0x1080 */ cXyz mSePos[8];
    /* 0x10E0 */ u8 mSePosInit;
    /* 0x10E1 */ u8 mBurning;
    /* 0x10E2 */ u8 field_0x10e2[0x10E4 - 0x10E2];
    /* 0x10E4 */ int mBurned;
    /* 0x10E8 */ int mVoiceIdx;
}; // Size: 0x10EC

#endif /* D_A_OBJ_FIREWALL_H */
