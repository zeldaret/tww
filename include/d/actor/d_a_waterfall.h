#ifndef D_A_WATERFALL_H
#define D_A_WATERFALL_H

#include "f_op/f_op_actor.h"

class daWfall_c : public fopAc_ac_c {
public:
    void _draw() {}

    void _delete();
    void CreateHeap();
    void CreateInit();
    void _create();
    void set_mtx();
    void set_gate_mtx();
    void set_minamo_mtx();
    void _execute();
    void mode_proc_call();
    void mode_wtr_on_init();
    void mode_wtr_on();
    void mode_wtr_off_init();
    void mode_wtr_off();
    void setEmitter00Pos();
    void setEmitter01Pos();
    void getWaterScaleFromGatePos();
    void getWaterHeight();
    void set_se();

public:
    /* Place member variables here */
};

#endif /* D_A_WATERFALL_H */
