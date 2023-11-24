#ifndef D_A_TOGE_H
#define D_A_TOGE_H

#include "f_op/f_op_actor.h"

class daToge_c : public fopAc_ac_c {
public:
    void set_mtx() {}

    BOOL _delete();
    void CreateHeap();
    s32 Create();
    s32 _create();
    BOOL _execute();
    void set_collision();
    void search_wind();
    void toge_move();
    void toge_seStart(unsigned long);
    BOOL _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_TOGE_H */
