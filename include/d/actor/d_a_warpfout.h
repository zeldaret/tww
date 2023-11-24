#ifndef D_A_WARPFOUT_H
#define D_A_WARPFOUT_H

#include "f_op/f_op_actor.h"

class daWarpfout_c : public fopAc_ac_c {
public:
    void _draw() {}

    void _delete();
    void CreateInit();
    void _create();
    void _execute();
    void checkOrder();
    void eventOrder();
    void demo_proc();
    void initWarp1(int);
    void actWarp1(int);
    void initWarp2(int);
    void actWarp2(int);
    void initWarp3(int);
    void actWarp3(int);
    void initWarp4(int);
    void actWarp4(int);
    void initEnd(int);
    void actEnd(int);
    void set_effect_wind01(cXyz, short);
    void get_effect_angle();

public:
    /* Place member variables here */
};

#endif /* D_A_WARPFOUT_H */
