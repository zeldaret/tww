#ifndef D_A_FIRE_H
#define D_A_FIRE_H

#include "f_op/f_op_actor.h"

class daFire_c : public fopAc_ac_c {
public:
    void _delete();
    void CreateInit();
    void _create();
    void _execute();
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
    void _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_FIRE_H */
