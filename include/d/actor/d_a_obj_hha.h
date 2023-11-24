#ifndef D_A_OBJ_HHA_H
#define D_A_OBJ_HHA_H

#include "f_op/f_op_actor.h"

class daObjHha_c : public fopAc_ac_c {
public:
    void check_sw() {}

    void solidHeapCB(fopAc_ac_c*);
    void create_heap();
    s32 _create();
    BOOL _delete();
    void set_tex(float, float, int);
    void init_mtx();
    void init_co();
    void get_water_h();
    void set_splash_bottom_h();
    void set_splash_bottom_r();
    void set_splash_bottom_stop_r();
    void water_manager();
    void part_manager();
    void ygush_manager();
    BOOL _execute();
    BOOL _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_HHA_H */
