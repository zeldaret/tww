#ifndef D_A_WALL_H
#define D_A_WALL_H

#include "f_op/f_op_actor.h"

class daWall_c : public fopAc_ac_c {
public:
    void _delete();
    void CreateHeap();
    void CreateInit();
    void _create();
    void set_mtx();
    void setMoveBGMtx();
    void _execute();
    void mode_wait();
    void mode_break();
    void set_tri();
    void set_effect();
    void set_se();
    void _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_WALL_H */
