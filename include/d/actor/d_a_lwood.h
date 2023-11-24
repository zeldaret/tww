#ifndef D_A_LWOOD_H
#define D_A_LWOOD_H

#include "f_op/f_op_actor.h"

class daLwood_c : public fopAc_ac_c {
public:
    void _create() {}
    void _delete() {}
    void _draw() {}
    void _execute() {}
    void getYureScale() const {}
    void getYureTimer() const {}
    void setMoveBGMtx() {}
    void set_mtx() {}

    void CreateHeap();
    void CreateInit();

public:
    /* Place member variables here */
};

#endif /* D_A_LWOOD_H */
