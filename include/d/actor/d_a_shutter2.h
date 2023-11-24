#ifndef D_A_SHUTTER2_H
#define D_A_SHUTTER2_H

#include "f_op/f_op_actor.h"

class daShutter2_c : public fopAc_ac_c {
public:
    BOOL Delete();
    void CreateHeap();
    s32 Create();
    s32 _create();
    void set_mtx();
    void Execute(float(**)[3][4]);
    void shutter_move();
    void demo();
    BOOL Draw();

public:
    /* Place member variables here */
};

#endif /* D_A_SHUTTER2_H */
