#ifndef D_A_FLOOR_H
#define D_A_FLOOR_H

#include "f_op/f_op_actor.h"

class daFloor_c : public fopAc_ac_c {
public:
    BOOL Delete();
    void CreateHeap();
    s32 Create();
    s32 _create();
    void set_mtx();
    void Execute(float(**)[3][4]);
    void set_effect();
    BOOL Draw();

public:
    /* Place member variables here */
};

#endif /* D_A_FLOOR_H */
