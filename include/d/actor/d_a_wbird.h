#ifndef D_A_WBIRD_H
#define D_A_WBIRD_H

#include "f_op/f_op_actor.h"

class daWbird_c : public fopAc_ac_c {
public:
    void draw() {}
    void execute() {}
    void setAction(unsigned char) {}

    void calcMtx();
    void setStartPos();
    void CreateInit();
    void create();
    void actionWait();
    void actionEnd();
    void actionMove();
    void actionSelect();

public:
    /* Place member variables here */
};

#endif /* D_A_WBIRD_H */
