#ifndef D_A_LEAFLIFT_H
#define D_A_LEAFLIFT_H

#include "f_op/f_op_actor.h"

class daLlift_c : public fopAc_ac_c {
public:
    void _delete();
    void CreateHeap();
    void CreateInit();
    void _create();
    void set_mtx();
    void setMoveBGMtx();
    void _execute();
    void emitterCtrl();
    void MoveDownLift();
    void _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_LEAFLIFT_H */
