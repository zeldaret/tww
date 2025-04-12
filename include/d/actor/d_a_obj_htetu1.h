#ifndef D_A_OBJ_HTETU1_H
#define D_A_OBJ_HTETU1_H

#include "f_op/f_op_actor.h"

class daObjHtetu1_c : public fopAc_ac_c {
public:
    // TODO: this function is marked as weak in the REL symbol map, but it does not get inlined for some reason?
    // void check_sw() {}
    void check_sw();

    void solidHeapCB(fopAc_ac_c*);
    void create_heap();
    cPhs_State _create();
    bool _delete();
    void init_mtx();
    void unlock();
    void get_water_h();
    void splash_manager();
    bool _execute();
    bool _draw();

public:
    /* Place member variables here */
};

class daObjHtetu1Splash_c {
public:
    void chk_stop() {}
    void delete_s() {}
    void get_timer() {}
    void play_particle() {}
    void set_pos_y(float) {}
    void stop_particle() {}
    void sub_timer() {}
    void timer_play_particle(short) {}

    void create_s(unsigned short, cXyz*, csXyz*, dKy_tevstr_c*);
};

#endif /* D_A_OBJ_HTETU1_H */
