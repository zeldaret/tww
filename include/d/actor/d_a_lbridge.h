#ifndef D_A_LBRIDGE_H
#define D_A_LBRIDGE_H

#include "f_op/f_op_actor.h"

class daLbridge_c : public fopAc_ac_c {
public:
    void _delete() {}

    void CreateHeap();
    void CreateInit();
    void _create();
    void set_mtx();
    void setMoveBGMtx();
    void _execute();
    void sw_check();
    void demo();
    void appear_bridge();
    void disappear_bridge();
    void set_on_se();
    void set_off_se();
    void _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_LBRIDGE_H */
