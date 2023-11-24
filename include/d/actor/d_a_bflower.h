#ifndef D_A_BFLOWER_H
#define D_A_BFLOWER_H

#include "f_op/f_op_actor.h"

class daBFlower_c : public fopAc_ac_c {
public:
    void _delete() {}

    void CreateHeap();
    void CreateInit();
    void init_bck_anm(short);
    void _create();
    void set_mtx();
    void _execute();
    void actLive();
    void actDead();
    void animPlay();
    void setCollision();
    void _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_BFLOWER_H */
