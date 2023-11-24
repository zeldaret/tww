#ifndef D_A_ACORN_LEAF_H
#define D_A_ACORN_LEAF_H

#include "f_op/f_op_actor.h"

class daAleaf_c : public fopAc_ac_c {
public:
    void _delete() {}

    void CreateHeap();
    void CreateInit();
    void create_acorn();
    void create_acorn_sub(bool);
    void _create();
    void set_mtx();
    void _execute();
    void _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_ACORN_LEAF_H */
