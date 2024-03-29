#ifndef D_A_YGCWP_H
#define D_A_YGCWP_H

#include "f_op/f_op_actor.h"

class daYgcwp_c : public fopAc_ac_c {
public:
    void check_ev() const; // weak but not inlined?
    void off_ev() const; // weak but not inlined?

    void solidHeapCB(fopAc_ac_c*);
    void create_heap();
    s32 _create();
    BOOL _delete();
    void init_mtx();
    void make_shine();
    void set_timer();
    BOOL _execute();
    BOOL _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_YGCWP_H */
