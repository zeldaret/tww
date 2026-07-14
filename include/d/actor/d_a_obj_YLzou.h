#ifndef D_A_OBJ_YLZOU_H
#define D_A_OBJ_YLZOU_H

#include "f_op/f_op_actor.h"
#include "d/actor/d_a_obj_movebox.h"

class daObjYLzou_c : public fopAc_ac_c {
public:
    enum Param_e {
        PARAM_SWSAVE_W = 8,
        PARAM_SWSAVE_S = 0,
    };

    typedef void (daObjYLzou_c::*ProcFunc)();

    s32 param_get_swSave() const { return daObj::PrmAbstract(this, PARAM_SWSAVE_W, PARAM_SWSAVE_S); }

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
    /* 0x290 */ request_of_phase_process_class field_0x290;
    /* 0x298 */ J3DModel* field_0x298;
    /* 0x29C */ dBgW* field_0x29C;
    /* 0x2A0 */ Mtx field_0x2A0;
    /* 0x2D0 */ void (daObjYLzou_c::*field_0x2D0)();
    /* 0x2DC */ int field_0x2DC;
    /* 0x2E0 */ int field_0x2E0;
    /* 0x2E4 */ s16 field_0x2E4;
    /* 0x2E6 */ u8 field_0x2E6[0x2E8 - 0x2E6];
    /* 0x2E8 */ BOOL field_0x2E8;
    /* 0x2EC */ int field_0x2EC;
    /* 0x2F0 */ daObjMovebox::EffSmokeCB mSmokeCbs[2];
    /* 0x358 */ s16 field_0x358;
    /* 0x35A */ u8 field_0x35A[0x35C - 0x35A];
    /* 0x35C */ f32 field_0x35C;
    /* 0x360 */ u8 field_0x360;
    /* 0x361 */ u8 field_0x361;
    /* 0x362 */ u8 field_0x362[0x364 - 0x362];
    /* 0x364 */ int field_0x364;
    /* 0x368 */ int field_0x368;
}; // Size: 0x36C

#endif /* D_A_OBJ_YLZOU_H */
