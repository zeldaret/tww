#ifndef D_A_FIRE_H
#define D_A_FIRE_H

#include "f_op/f_op_actor.h"

class daFire_c : public fopAc_ac_c {
public:
    BOOL _delete();
    void CreateInit();
    s32 _create();
    BOOL _execute();
    void search_wind();
    void ctrlEffect();
    void demo_proc();
    void normal_proc();
    void eventOrder();
    void checkOrder();
    void execStopFire();
    void execStopNowFire();
    void execPlayFire();
    void setDirParticle(cXyz*);
    void checkCol();
    BOOL _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_FIRE_H */
