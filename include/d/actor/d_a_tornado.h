#ifndef D_A_TORNADO_H
#define D_A_TORNADO_H

#include "f_op/f_op_actor.h"

class daTornado_c : public fopAc_ac_c {
public:
    void getJointXPos(int) const {}
    void getJointYPos(int) const {}
    void getJointZPos(int) const {}
    void getScaleEnd() {}
    void getSmallScaleEnd() {}
    void setScaleOn() {}

    void jointCallBack(int);
    void draw();
    void execute();
    void tornado_delete();
    void createHeap();
    void create();

public:
    /* Place member variables here */
};

#endif /* D_A_TORNADO_H */
