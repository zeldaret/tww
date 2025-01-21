#ifndef D_A_OBJ_HHA_H
#define D_A_OBJ_HHA_H

#include "SSystem/SComponent/c_xyz.h"
#include "d/d_bg_w.h"
#include "d/d_particle.h"
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

    void init_data(float, float, u16, u8, u8);
    bool set_mdl_area(const char*, int);
    bool set_bgw(const char*, int);
    void init_mtx(cXyz, csXyz, cXyz);
    static void exe_normal(daObjHha_c*);
    void exe_move(daObjHha_c*);
    static void draw_normal(daObjHha_c*);
public: 
    typedef void utype0(daObjHha_c*);
    struct utype1 {
        int i0;
        int i4;
        utype0* m8; 
    };

    /* 0x00 */ J3DModel* mpModel;
    /* 0x04 */ dBgW* mpBgw;
    /* 0x08 */ cXyz m08;
    /* 0x14 */ cXyz m14;
    /* 0x20 */ cXyz m20;
    /* 0x2C */ float f2C;
    /* 0x30 */ u8 u30;
    /* 0x31 */ u8 u31;
    /* 0x34 */ utype1 m34;
    /* 0x40 */ utype1 m40;
};

class daObjHhaSplash_c : dPa_followEcallBack {
public:
    daObjHhaSplash_c() {}
    ~daObjHhaSplash_c() {}

    void chk_stop() {}
    void delete_s() {}
    virtual void get_base_pos() {}
    virtual void get_pos() {}
    void get_pos_y() {}
    void play_particle() {}
    void set_pos(cXyz*) {}
    void set_pos_y(float) {}
    void stop_particle() {}

    void create_s(unsigned short, cXyz, float, float, csXyz);

public:
    /* 0x14 */ cXyz m14;
    /* 0x20 */ cXyz m20;
    /* 0x2C */ csXyz m2C;
    /* 0x32 */ bool b32;
};

class daObjHhaYgush_c {
public:
    void anm_play() {}
    void check_draw() {}
    void disp_off() {}
    void disp_on() {}
    void get_base_pos() {}
    void set_pos(cXyz) {}

    bool create_area(const char*);
    void init_data(cXyz, f32, csXyz, cXyz, dKy_tevstr_c, u8);
    void init_mtx();
    BOOL draw();

public:
    /* 0x000 */ J3DModel* mpModel;
    /* 0x004 */ mDoExt_btkAnm mBtk;
    /* 0x018 */ mDoExt_bckAnm mBck;
    /* 0x028 */ dKy_tevstr_c m28;
    /* 0x0D8 */ cXyz mD8;
    /* 0x0E4 */ cXyz mTransMtx;
    /* 0x0F0 */ cXyz mScale;
    /* 0x0FC */ csXyz mRotMtx;
    /* 0x102 */ u8 u102;
};

#endif /* D_A_OBJ_HHA_H */
