#ifndef D_A_MDOOR_H
#define D_A_MDOOR_H

#include "f_op/f_op_actor.h"

class daMdoor_c : public fopAc_ac_c {
public:
    void chkFlag(unsigned short) {}
    void clrFlag(unsigned short) {}
    void draw() {}
    void execute() {}
    void nextAction() {}
    void setAction(unsigned char) {}
    void setFlag(unsigned short) {}

    void getSwbit();
    void getType();
    void getToolId();
    void getShapeType();
    void CreateHeap();
    void calcMtx();
    void smokeInit();
    void smokeEnd();
    void CreateInit();
    void create();
    void demoProc();

public:
    /* Place member variables here */
};

#endif /* D_A_MDOOR_H */
