#ifndef D_A_OBJ_RFLW_H
#define D_A_OBJ_RFLW_H

#include "f_op/f_op_actor.h"

class daObjRflw_c : public fopAc_ac_c {
public:
    void _create() {}
    void _delete() {}
    void _draw() {}
    void _execute() {}

    void CreateHeap();
    void CreateInit();
    void set_mtx();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_RFLW_H */
