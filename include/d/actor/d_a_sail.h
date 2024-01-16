#ifndef D_A_SAIL_H
#define D_A_SAIL_H

#include "f_op/f_op_actor.h"

class sail_class : public fopAc_ac_c {
public:
    /* Place member variables here */
};

class daSail_packet_c {
public:
    void getMtx() {}
    void getNrm() {}
    void getPos() {}
    void getPosSpd() {}
    void getStickMtx() {}
    void getTexMtx() {}
    void setTevStr(dKy_tevstr_c*) {}

    void setCorrectNrmAngle(short, float);
    void setNrmMtx();
    void setBackNrm();
    void setNrmVtx(cXyz*, int, int);
    void draw();
};

#endif /* D_A_SAIL_H */
