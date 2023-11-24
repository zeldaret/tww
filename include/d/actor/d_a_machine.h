#ifndef D_A_MACHINE_H
#define D_A_MACHINE_H

#include "f_op/f_op_actor.h"

class daMachine_c : public fopAc_ac_c {
public:
    void _delete();
    void CreateHeap();
    void CreateInit();
    void path_move();
    void set_next_pnt();
    void search_wind_mill();
    void set_speed();
    void _create();
    void set_mtx();
    void _execute();
    void attack();
    void set_cube();
    void set_body();
    void set_at();
    void _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_MACHINE_H */
