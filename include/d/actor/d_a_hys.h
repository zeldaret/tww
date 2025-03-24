#ifndef D_A_HYS_H
#define D_A_HYS_H

#include "d/d_bg_s_movebg_actor.h"

class daHys_c : public dBgS_MoveBgActor {
public:
    inline cPhs_State _create();
    void set_mtx();

    virtual BOOL Delete();
    virtual BOOL CreateHeap();
    virtual BOOL Create();
    virtual BOOL Execute(Mtx**);
    void mode_proc_call();
    void mode_wait();
    void mode_sw_on_init();
    void mode_sw_on();
    void mode_wait_init();
    virtual BOOL Draw();

public:
    /* Place member variables here */
};

#endif /* D_A_HYS_H */
