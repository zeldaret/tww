#ifndef D_A_OBJ_STAIR_H
#define D_A_OBJ_STAIR_H

#include "f_op/f_op_actor.h"

class daObj_Stair_c : public fopAc_ac_c {
public:
    void _create() {}
    void _delete() {}
    void _draw() {}
    void _execute() {}
    void set_mtx() {}

    void CreateHeap();
    void Create();
    void Execute(float(**)[3][4]);
    void Draw();
    void Delete();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_STAIR_H */
