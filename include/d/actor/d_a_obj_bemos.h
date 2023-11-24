#ifndef D_A_OBJ_BEMOS_H
#define D_A_OBJ_BEMOS_H

#include "f_op/f_op_actor.h"

class daBemos_c : public fopAc_ac_c {
public:
    void _create() {}
    void _delete() {}
    void _draw() {}
    void _execute() {}
    void checkEyeProc(int (daBemos_c::*)()) {}
    void setEyeProc(int (daBemos_c::*)()) {}

    void set_mtx();
    void CreateHeap1();
    void CreateHeap2();
    void CreateHeap3();
    void CreateHeap();
    void CreateInit1();
    void CreateInit2();
    void CreateInit3();
    void CreateInit();
    void blue_range_check(int, csXyz*);
    void red_range_check(int, csXyz*);
    void yellow_range_check(int, csXyz*);
    void blue_eye_wait_init();
    void blue_eye_wait();
    void blue_eye_charge_init();
    void blue_eye_charge();
    void blue_eye_search_init();
    void blue_eye_search();
    void red_eye_wait_init();
    void red_eye_wait();
    void red_eye_charge_init();
    void red_eye_charge();
    void red_eye_search_init();
    void red_eye_search();
    void eye_break_init();
    void eye_break();
    void eye_dummy();
    void yellow_eye_wait_init();
    void yellow_eye_wait();
    void yellow_eye_search_init();
    void yellow_eye_search();
    void event_move();
    void guard_proc();
    void getBeamActor();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_BEMOS_H */
