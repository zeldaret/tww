#ifndef D_A_OBJ_TNTRAP_H
#define D_A_OBJ_TNTRAP_H

#include "f_op/f_op_actor.h"

class daObjTnTrap_c : public fopAc_ac_c {
public:
    void param_get_arg0() const {}
    void param_get_mapType() const {}
    void param_get_swSave() const {}
    void param_get_swSave2() const {}

    void chk_appear();
    void set_mtx();
    void solidHeapCB(fopAc_ac_c*);
    void create_heap();
    void particle_set(int, float);
    void particle_delete(int);
    void set_se();
    void set_tri(int);
    void chk_event_flg();
    void set_em_set_offsetY();
    void _create();
    void _delete();
    void trap_off_wait_act_proc();
    void trap_on_wait_act_proc();
    void demo_regist_wait_act_proc();
    void demo_wait_act_proc();
    void demo_wait2_act_proc();
    void demo_end_wait_act_proc();
    void hide_wait_act_proc();
    void dummy_proc();
    void trap_off_wait_act_init_proc();
    void trap_on_wait_act_init_proc();
    void demo_regist_wait_act_init_proc();
    void demo_wait2_act_init_proc();
    void demo_end_wait_act_init_proc();
    void setup_action(int);
    void _execute();
    void _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_TNTRAP_H */
