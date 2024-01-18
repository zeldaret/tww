#ifndef D_A_WARPDM20_H
#define D_A_WARPDM20_H

#include "f_op/f_op_actor.h"

class daWarpdm20_c : public fopAc_ac_c {
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
    void initWait2(int);
    void actWait2(int);
    void initWarp(int);
    void actWarp(int);
    void initWaitDead(int);
    void actWaitDead(int);
    void initDead(int);
    void actDead(int);
    void initReturnWait(int);
    void actReturnWait(int);
    void eventOrder();
    void checkOrder();
    void animPlay();
    void setEndAnm();
    void getSeaY(cXyz);
    void set_effect(unsigned short);
    void set_wpsenko();
    void init_bck_anm(int);
    void check_warp();
    BOOL _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_WARPDM20_H */
