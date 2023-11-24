#ifndef D_A_MOZO_H
#define D_A_MOZO_H

#include "f_op/f_op_actor.h"

class daMozo_c : public fopAc_ac_c {
public:
    void setProcess(void (daMozo_c::*)()) {}

    void set_mtx();
    void anime_proc();
    void wait_proc_init();
    void wait_proc();
    void search_beam_proc_init();
    void search_beam_proc();
    void search_fire_proc_init();
    void search_fire_proc();
    void towait_proc_init();
    void towait_proc();
    void checkRange(int);
    void setAnm(int, float);
    void getBeamActor(u32);
    void event_move();

public:
    /* Place member variables here */
};

#endif /* D_A_MOZO_H */
