#ifndef D_A_KMON_H
#define D_A_KMON_H

#include "f_op/f_op_actor.h"

class daKmon_c : public fopAc_ac_c {
public:
    void _create() {}
    void _delete() {}
    void _draw() {}
    void _execute() {}

    void set_mtx();
    void CreateHeap();
    void CreateInit();
    void checkTalk();

public:
    /* Place member variables here */
};

#endif /* D_A_KMON_H */
