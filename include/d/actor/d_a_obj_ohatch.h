#ifndef D_A_OBJ_OHATCH_H
#define D_A_OBJ_OHATCH_H

#include "f_op/f_op_actor.h"

class daObjOhatch_c : public fopAc_ac_c {
public:
    void param_get_swSave() const {}

    void set_mtx();
    void init_mtx();
    void solidHeapCB(fopAc_ac_c*);
    void create_heap();
    cPhs_State _create();
    bool _delete();
    void close_wait_act_proc();
    void tremor_act_proc();
    void open_act_proc();
    void vibrate_act_proc();
    void open_wait_act_proc();
    bool _execute();
    bool _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_OHATCH_H */
