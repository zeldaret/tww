#ifndef D_A_WINDMILL_H
#define D_A_WINDMILL_H

#include "f_op/f_op_actor.h"

class daWindMill_c : public fopAc_ac_c {
public:
    void _delete();
    void CreateHeap();
    void CreateInit();
    void search_wind();
    void _create();
    void set_mtx();
    void _execute();
    void hane_move();
    void set_at();
    void set_co();
    void _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_WINDMILL_H */
