#ifndef D_A_PIRATE_FLAG_H
#define D_A_PIRATE_FLAG_H

#include "f_op/f_op_actor.h"

class daPirate_Flag_packet_c {
public:
    void changeCurrentPos() {}
    void getEscapeNrmAngle() {}
    void getMtx() {}
    void getNrm() {}
    void getOffsetVec() {}
    void getPos() {}
    void setNrmMtx() {}
    void setTevStr(dKy_tevstr_c*) {}

    void setCorrectNrmAngle(short, float);
    void setBackNrm();
    void setNrmVtx(cXyz*, int, int);
    void draw();
};

class pirate_flag_class : public fopAc_ac_c {
public:
    /* Place member variables here */
};

#endif /* D_A_PIRATE_FLAG_H */
