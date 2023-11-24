#ifndef D_A_DEKU_ITEM_H
#define D_A_DEKU_ITEM_H

#include "f_op/f_op_actor.h"

class daDekuItem_c : public fopAc_ac_c {
public:
    void _delete();
    void CreateHeap();
    void CreateInit();
    void _create();
    void set_mtx();
    void _execute();
    void mode_proc_call();
    void mode_wait();
    void mode_getdemo_init();
    void mode_getdemo_wait();
    void mode_getdemo();
    void eventOrder();
    void checkOrder();
    void _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_DEKU_ITEM_H */
