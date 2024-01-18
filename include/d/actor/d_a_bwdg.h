#ifndef D_A_BWDG_H
#define D_A_BWDG_H

#include "f_op/f_op_actor.h"

class bwdg_class : public fopAc_ac_c {
public:
    /* Place member variables here */
};

class daBwdg_packet_c {
public:
    void getMtx() {}
    void getNrm() {}
    void getPos() {}
    void setTevStr(dKy_tevstr_c*) {}

    void draw();
};

#endif /* D_A_BWDG_H */
