#ifndef D_A_OBJ_YLZOU_H
#define D_A_OBJ_YLZOU_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_particle.h"
#include "d/d_a_obj.h"

class dBgW;

class EffSmokeCB : public dPa_smokeEcallBack {
public:
    EffSmokeCB() {}
    virtual ~EffSmokeCB() {}

public:
    /* 0x20 */ cXyz field_0x20;
    /* 0x2C */ csXyz field_0x2C;
};  // Size: 0x34

class daObjYLzou_c : public fopAc_ac_c {
public:
    typedef void (daObjYLzou_c::*ActionFunc)();

    enum Param_e {
        PRM_SWSAVE_W = 0x08,
        PRM_SWSAVE_S = 0x00,
    };

    s32 prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }

    void set_start_type();
    void set_mtx();
    void init_mtx();
    static BOOL solidHeapCB(fopAc_ac_c*);
    bool create_heap();
    void eff_set_slip_smoke_pos();
    void eff_smoke_slip_start();
    void eff_smoke_slip_end();
    void eff_smoke_slip_remove();
    void eff_smoke_proc();
    void vib_proc();
    cPhs_State _create();
    bool _delete();
    void move_ylzou_demo_start_wait_act_proc();
    void demo_regist_wait_act_proc();
    void demo_vib_start_wait_act_proc();
    void demo_vib_act_proc();
    void move_ylzou_demo_move_act_proc();
    void go_up_stairs_demo_move_act_proc();
    void demo_end_wait_act_proc();
    void wait_act_proc();
    void move_ylzou_demo_start_wait_act_init_proc();
    void demo_regist_wait_act_init_proc();
    void move_ylzou_demo_vib_start_wait_act_init_proc();
    void move_ylzou_demo_vib_act_init_proc();
    void move_ylzou_demo_move_act_init_proc();
    void demo_end_wait_act_init_proc();
    void open_wait_act_init_proc();
    void close_wait_act_init_proc();
    void go_up_stairs_demo_move_start_wait_act_init_proc();
    void go_up_stairs_demo_move_act_init_proc();
    void setup_action(int);
    bool _execute();
    bool _draw();

public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dBgW* mBgW;
    /* 0x2A0 */ Mtx mMtx;
    /* 0x2D0 */ ActionFunc mActProc;
    /* 0x2DC */ s32 mActionIdx;
    /* 0x2E0 */ s32 m2e0;
    /* 0x2E4 */ s16 m2e4;
    /* 0x2E6 */ u8 field_0x2e6[0x2e8 - 0x2e6];
    /* 0x2E8 */ s32 mType;
    /* 0x2EC */ s32 m2ec;
    /* 0x2F0 */ EffSmokeCB mSmoke[2];
    /* 0x358 */ s16 m358;
    /* 0x35A */ u8 field_0x35a[0x35c - 0x35a];
    /* 0x35C */ f32 m35c;
    /* 0x360 */ u8 m360;
    /* 0x361 */ u8 m361;
    /* 0x362 */ u8 field_0x362[0x364 - 0x362];
    /* 0x364 */ s32 m364;
    /* 0x368 */ s32 m368;
};

#endif /* D_A_OBJ_YLZOU_H */
