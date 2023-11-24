#ifndef D_A_YGCWP_H
#define D_A_YGCWP_H

#include "f_op/f_op_actor.h"

class daYgcwp_c : public fopAc_ac_c {
public:
    void check_ev() const {}
    void off_ev() const {}

    void solidHeapCB(fopAc_ac_c*);
    void create_heap();
    void _create();
    void _delete();
    void init_mtx();
    void make_shine();
    void set_timer();
    void _execute();
    void _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_YGCWP_H */
