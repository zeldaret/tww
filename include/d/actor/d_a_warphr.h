#ifndef D_A_WARPHR_H
#define D_A_WARPHR_H

#include "f_op/f_op_actor.h"

class daWarphr_c : public fopAc_ac_c {
public:
    void set_mtx(); // weak but not inlined?

    bool _delete();
    void CreateHeap();
    void CreateInit();
    s32 _create();
    bool _execute();
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
    void eventOrder();
    void checkOrder();
    void anim_play(int);
    void set_end_anim();
    void get_return_count();
    void check_warp();
    bool _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_WARPHR_H */
