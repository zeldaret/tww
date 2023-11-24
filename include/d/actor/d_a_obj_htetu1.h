#ifndef D_A_OBJ_HTETU1_H
#define D_A_OBJ_HTETU1_H

#include "f_op/f_op_actor.h"

class daObjHtetu1Splash_c : public fopAc_ac_c {
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

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_HTETU1_H */
