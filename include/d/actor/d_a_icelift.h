#ifndef D_A_ICELIFT_H
#define D_A_ICELIFT_H

#include "f_op/f_op_actor.h"

class daIlift_c : public fopAc_ac_c {
public:
    void _delete();
    void CreateHeap();
    void CreateInit();
    void _create();
    void set_mtx();
    void _execute();
    void lift_wave();
    void path_move();
    void lift_normal_move();
    void set_next_pnt();
    void _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_ICELIFT_H */
