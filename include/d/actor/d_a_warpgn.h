#ifndef D_A_WARPGN_H
#define D_A_WARPGN_H

#include "f_op/f_op_actor.h"

class daWarpgn_c : public fopAc_ac_c {
public:
    void set_mtx() {}

    BOOL _delete();
    void CreateHeap();
    void CreateInit();
    s32 _create();
    BOOL _execute();
    void normal_execute();
    void demo_execute();
    void demo_proc();
    void initWait(int);
    void actWait(int);
    void initStartWarp(int);
    void actStartWarp(int);
    void initWarp(int);
    void actWarp(int);
    void initWarpArrive(int);
    void actWarpArrive(int);
    void initWarpArriveEnd(int);
    void actWarpArriveEnd(int);
    void initAppear(int);
    void actAppear(int);
    void eventOrder();
    void checkOrder();
    void anim_play(int);
    void set_end_anim();
    void check_warp();
    void checkValidWarp();
    BOOL _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_WARPGN_H */
