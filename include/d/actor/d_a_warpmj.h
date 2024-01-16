#ifndef D_A_WARPMJ_H
#define D_A_WARPMJ_H

#include "f_op/f_op_actor.h"

class daWarpmj_c : public fopAc_ac_c {
public:
    void set_mtx(); // weak but not inlined?

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
    void initWarp(int);
    void actWarp(int);
    void initWarpArrive(int);
    void actWarpArrive(int);
    void eventOrder();
    void checkOrder();
    void animPlay();
    void setEndAnm();
    void getSeaY(cXyz);
    void check_warp();
    BOOL _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_WARPMJ_H */
