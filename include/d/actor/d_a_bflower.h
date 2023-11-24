#ifndef D_A_BFLOWER_H
#define D_A_BFLOWER_H

#include "f_op/f_op_actor.h"

class daBFlower_c : public fopAc_ac_c {
public:
    inline BOOL _delete();

    void CreateHeap();
    void CreateInit();
    void init_bck_anm(short);
    s32 _create();
    void set_mtx();
    BOOL _execute();
    void actLive();
    void actDead();
    void animPlay();
    void setCollision();
    BOOL _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_BFLOWER_H */
