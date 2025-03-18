#ifndef D_A_OBJ_SHMRGRD_H
#define D_A_OBJ_SHMRGRD_H

#include "f_op/f_op_actor.h"

class J3DNode;

class daObjShmrgrd_c : public fopAc_ac_c {
public:
    void get_mode() {}
    void is_switch() const {}
    void on_switch() const {}
    void prm_get_swSave() const {}

    daObjShmrgrd_c();
    void solidHeapCB(fopAc_ac_c*);
    void create_heap();
    cPhs_State _create();
    bool _delete();
    void search_target_next(daObjShmrgrd_c*);
    void register_list();
    void leave_list();
    void search_gap();
    void set_gap_co();
    void init_mtx();
    void set_mtx();
    void check_player_angle(fopAc_ac_c*);
    void set_damage();
    void vib_start(short, float);
    void vib_proc();
    void crush_start();
    void crush_proc();
    void eff_crush();
    void calc_top_pos();
    static BOOL jnodeCB(J3DNode*, int);
    void mode_upper_init();
    void mode_upper();
    void mode_u_l_init();
    void mode_u_l();
    void mode_lower_init();
    void mode_lower();
    bool _execute();
    bool _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_SHMRGRD_H */
