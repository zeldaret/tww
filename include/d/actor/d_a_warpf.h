#ifndef D_A_WARPF_H
#define D_A_WARPF_H

#include "f_op/f_op_actor.h"

class daWarpf_c : public fopAc_ac_c {
public:
    void CreateHeap();
    void _delete();
    void checkEndDemo();
    void onEndDemo();
    void CreateInit();
    void _create();
    void _execute();
    void eventOrder();
    void checkOrder();
    void demo_proc();
    void initWait(int);
    void actWait(int);
    void initWarpStart(int);
    void actWarpStart(int);
    void initWarpMode_1(int);
    void actWarpMode_1(int);
    void initWarpMode_2(int);
    void actWarpMode_2(int);
    void initWarpMode_3(int);
    void actWarpMode_3(int);
    void initEndWait(int);
    void actEndWait(int);
    void check_warp_event();
    void get_distance();
    void get_earth_pos();
    void set_effect();
    void set_effect_wind00();
    void get_angle_wind01();
    void anim_play();
    void setEndAnim();
    void set_se();
    void set_mtx();
    void _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_WARPF_H */
