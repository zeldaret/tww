#ifndef D_A_WINDMILL_H
#define D_A_WINDMILL_H

#include "f_op/f_op_actor.h"

class daWindMill_c : public fopAc_ac_c {
public:
    void getMaxRotSpeed() const {}
    void getRotSpeed() const {}
    void getType() const {}

    BOOL _delete();
    void CreateHeap();
    void CreateInit();
    void search_wind();
    s32 _create();
    void set_mtx();
    BOOL _execute();
    void hane_move();
    void set_at();
    void set_co();
    BOOL _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_WINDMILL_H */
