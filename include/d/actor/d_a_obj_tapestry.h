#ifndef D_A_OBJ_TAPESTRY_H
#define D_A_OBJ_TAPESTRY_H

#include "f_op/f_op_actor.h"

class JPABaseEmitter;
class daObjTapestryDrawVtx_c;

class daObjTapestry_c {
public:
    void is_switch() const {}
    void on_switch() const {}
    void param_get_evId() const {}
    void param_get_swSave() const {}

    void chk_appear();
    void set_mtx();
    void init_mtx();
    void solidHeapCB(fopAc_ac_c*);
    void create_heap();
    void create_res_load();
    void init_cc();
    void set_cc_pos();
    void checkCollision();
    void set_eye_pos();
    s32 _create();
    BOOL _delete();
    void wait_act_proc();
    void demo_request_act_proc();
    void burn_act_proc();
    void burn_act_init_proc();
    void fine_act_init_proc();
    void setup_action(int);
    BOOL _execute();
    BOOL _draw();
};

class daObjTapestryPLight_c : public fopAc_ac_c {
public:
    void plight_delete();
    void plight_move(cXyz, csXyz);
    void plight_make();
    void setPointLight(cXyz, csXyz);

public:
    /* Place member variables here */
};

class daObjTapestryFireEff_c {
public:
    void get_pos() const {}
    void set_pos(const cXyz&) {}
    void set_spd(const cXyz&) {}

    void execute(JPABaseEmitter*);
};

class daObjTapestryDrawData_c {
public:
    daObjTapestryDrawData_c();

    void dl() const {}
    void dl_size() const {}
    void tex_coord() const {}

    void ct_tex();
    void ct_dl();
};

class daObjTapestryPacket_c {
public:
    daObjTapestryPacket_c();

    void set_wind_fun(const cXyz&) {}

    void init(daObjTapestry_c*);
    void update();
    void calc_acc_spring_sub(const cXyz*, const cXyz*, float, float);
    void calc_acc_spring(int, int);
    void calc_acc_gravity();
    void calc_acc_wave(int, int);
    void calc_acc_hit(int, int);
    void calc_spd(int, int);
    void calc_pos_crr(int, int);
    void calc_pos();
    void calc_nrm();
    void calc_wind();
    void calc_hit();
    void calc_fire_leap(int, int);
    void calc_fire();
    void calc(daObjTapestry_c*);
    void set_hit(cXyz, cXyz, float, float, bool);
    void get_now_pos(int, int);
    void eff_start(int, int);
    void eff_start_chk(int, int);
    void eff_end();
    void eff_pos();
    void eff_delete();
    void smokeCallback_init();
    void smoke_set();
    void smoke_move(fopAc_ac_c*);
    void setup_vtx(daObjTapestryDrawVtx_c*);
    void load_tex();
    void setup_rendar();
    void setup_tev_stage();
    void setup_tevColReg(daObjTapestry_c*);
    void draw();
};

class daObjTapestry_HIO_c {
public:
    daObjTapestry_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_TAPESTRY_H */
