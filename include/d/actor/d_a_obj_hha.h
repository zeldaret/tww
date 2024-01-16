#ifndef D_A_OBJ_HHA_H
#define D_A_OBJ_HHA_H

#include "f_op/f_op_actor.h"

class daObjHha_c : public fopAc_ac_c {
public:
    void check_sw(); // weak but not inline?

    void solidHeapCB(fopAc_ac_c*);
    void create_heap();
    s32 _create();
    BOOL _delete();
    void set_tex(float, float, int);
    void init_mtx();
    void init_co();
    void get_water_h();
    void set_splash_bottom_h();
    void set_splash_bottom_r();
    void set_splash_bottom_stop_r();
    void water_manager();
    void part_manager();
    void ygush_manager();
    BOOL _execute();
    BOOL _draw();

public:
    /* Place member variables here */
};

class daObjHhaPart_c {
public:
    void draw(daObjHha_c*) {}
    void execute(daObjHha_c*) {}
    void setExeProc(void (daObjHhaPart_c::*)(daObjHha_c*)) {}
    void start_move() {}

    void init_data(float, float, unsigned short, unsigned char, unsigned char);
    void set_mdl_area(const char*, int);
    void set_bgw(const char*, int);
    void init_mtx(cXyz, csXyz, cXyz);
    void exe_normal(daObjHha_c*);
    void exe_move(daObjHha_c*);
    void draw_normal(daObjHha_c*);
};

class daObjHhaSplash_c {
public:
    void chk_stop() {}
    void delete_s() {}
    void get_base_pos() {}
    void get_pos() {}
    void get_pos_y() {}
    void play_particle() {}
    void set_pos(cXyz*) {}
    void set_pos_y(float) {}
    void stop_particle() {}

    void create_s(unsigned short, cXyz*, float, float, csXyz*);
};

class daObjHhaYgush_c {
public:
    void anm_play() {}
    void check_draw() {}
    void disp_off() {}
    void disp_on() {}
    void get_base_pos() {}
    void set_pos(cXyz) {}

    void create_area(const char*);
    void init_data(cXyz*, float, csXyz*, cXyz*, dKy_tevstr_c*, unsigned char);
    void init_mtx();
    BOOL draw();
};

#endif /* D_A_OBJ_HHA_H */
