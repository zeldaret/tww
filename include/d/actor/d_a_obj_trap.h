#ifndef D_A_OBJ_TRAP_H
#define D_A_OBJ_TRAP_H

#include "f_op/f_op_actor.h"

class daObjTrap_c : public fopAc_ac_c {
public:
    void start_shine() {}
    void stop_shine() {}

    void solidHeapCB(fopAc_ac_c*);
    void create_heap();
    void _create();
    void _delete();
    void init_mtx();
    void set_co_pos();
    void get_ground();
    void circle_search();
    void set_move_info();
    void check_arrival();
    void check_wall();
    void check_block_target_pos(cXyz*);
    void check_block(cXyz);
    void set_vib_mode();
    void vibrate();
    void bound();
    void set_shine();
    void shine_move();
    void _execute();
    void _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_TRAP_H */
