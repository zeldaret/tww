#ifndef D_A_OBJ_HTETU1_H
#define D_A_OBJ_HTETU1_H

#include "f_op/f_op_actor.h"

class daObjHtetu1_c : public fopAc_ac_c {
public:
    void check_sw();

    void solidHeapCB(fopAc_ac_c*);
    void create_heap();
    cPhs_State _create();
    bool _delete();
    void init_mtx();
    void unlock();
    void get_water_h();
    void splash_manager();
    bool _execute();
    bool _draw();

public:
    /* 0x290 */ u8 field_0x290[0xC];
    /* 0x29C */ int mSwitchNo;
    /* 0x2A0 */ u8 field_0x2A0[0x88];
};  // Size: 0x328

STATIC_ASSERT(sizeof(daObjHtetu1_c) == 0x328);

class daObjHtetu1Splash_c {
public:
    void chk_stop() {}
    void delete_s() {}
    void get_timer() {}
    void play_particle() {}
    void set_pos_y(float) {}
    void stop_particle() {}
    void sub_timer() {}
    void timer_play_particle(short) {}

    void create_s(unsigned short, cXyz*, csXyz*, dKy_tevstr_c*);
};

#endif /* D_A_OBJ_HTETU1_H */
