#ifndef D_A_DEKU_ITEM_H
#define D_A_DEKU_ITEM_H

#include "f_op/f_op_actor.h"

class daDekuItem_c : public fopAc_ac_c {
public:
    BOOL _delete();
    void CreateHeap();
    void CreateInit();
    s32 _create();
    void set_mtx();
    BOOL _execute();
    void mode_proc_call();
    void mode_wait();
    void mode_getdemo_init();
    void mode_getdemo_wait();
    void mode_getdemo();
    void eventOrder();
    void checkOrder();
    BOOL _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_DEKU_ITEM_H */
