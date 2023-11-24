#ifndef D_A_ACORN_LEAF_H
#define D_A_ACORN_LEAF_H

#include "f_op/f_op_actor.h"

class daAleaf_c : public fopAc_ac_c {
public:
    inline BOOL _delete();

    void CreateHeap();
    void CreateInit();
    void create_acorn();
    void create_acorn_sub(bool);
    s32 _create();
    void set_mtx();
    BOOL _execute();
    BOOL _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_ACORN_LEAF_H */
