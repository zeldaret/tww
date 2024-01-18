#ifndef D_A_OBJ_VTIL_H
#define D_A_OBJ_VTIL_H

#include "f_op/f_op_actor.h"

class daObjVtil_c : public fopAc_ac_c {
public:
    void camera_off() {}
    void check_ev_bit() const; // weak but not inlined?
    void prm_get_type() const {}

    void solidHeapCB(fopAc_ac_c*);
    void create_heap();
    s32 _create();
    BOOL _delete();
    void tell_agb_attack();
    void tell_agb_sink();
    void init_mtx();
    void init_co();
    void init_bgc();
    void renew_attention_pos();
    void make_smoke();
    void se_smoke();
    void make_splash();
    void se_splash();
    void set_sound(int, int) const;
    void to_wait_mode();
    void mode_wait();
    void to_carry_mode();
    void mode_carry();
    void to_throw_mode();
    void calc_throw(float*, float*, float*) const;
    void mode_throw();
    void to_sink_mode();
    void mode_sink();
    void hit_co();
    void check_sink();
    void check_sink_end();
    void hit_bg();
    void make_vib();
    void check_circle();
    BOOL _execute();
    BOOL _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_VTIL_H */
