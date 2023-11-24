#ifndef D_A_OBJ_CAFELMP_H
#define D_A_OBJ_CAFELMP_H

#include "f_op/f_op_actor.h"

class daObjCafelmp_c : public fopAc_ac_c {
public:
    void _create() {}
    void _delete() {}
    void _draw() {}
    void _execute() {}

    void CreateInit();
    void set_mtx();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_CAFELMP_H */
