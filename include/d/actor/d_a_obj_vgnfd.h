#ifndef D_A_OBJ_VGNFD_H
#define D_A_OBJ_VGNFD_H

#include "f_op/f_op_actor.h"

class daObjVgnfd_c : public fopAc_ac_c {
public:
    void check_boss(int) {}
    void check_ev_init(int); // weak but not inlined?
    void on_door_ev(int) {}

    void solidHeapCB(fopAc_ac_c*);
    void create_bdl_brk(int);
    void create_heap();
    s32 _create();
    BOOL _delete();
    void get_start_demo_idx();
    void check_fin();
    void on_fin();
    void init_mtx();
    void set_timer();
    BOOL _execute();
    BOOL _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_VGNFD_H */
