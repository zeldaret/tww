#ifndef D_A_HYS_H
#define D_A_HYS_H

#include "f_op/f_op_actor.h"

class daHys_c : public fopAc_ac_c {
public:
    inline s32 _create();
    void set_mtx() {}

    BOOL Delete();
    void CreateHeap();
    s32 Create();
    void Execute(float(**)[3][4]);
    void mode_proc_call();
    void mode_wait();
    void mode_sw_on_init();
    void mode_sw_on();
    void mode_wait_init();
    BOOL Draw();

public:
    /* Place member variables here */
};

#endif /* D_A_HYS_H */
