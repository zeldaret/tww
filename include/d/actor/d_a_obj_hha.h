#ifndef D_A_OBJ_HHA_H
#define D_A_OBJ_HHA_H

#include "SSystem/SComponent/c_xyz.h"
#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"

class daObjHha_c;

class daObjHhaPart_c {
public:
    void draw(daObjHha_c*) {}
    void execute(daObjHha_c*) {}
    void setExeProc(void (daObjHhaPart_c::*)(daObjHha_c*)) {}
    void start_move() {}

    void init_data(float, float, u16, u8, u8);
    BOOL set_mdl_area(const char*, int);
    BOOL set_bgw(const char*, int);
    void init_mtx(cXyz, csXyz, cXyz);
    void exe_normal(daObjHha_c*);
    void exe_move(daObjHha_c*);
    void draw_normal(daObjHha_c*);
public: 
    typedef void (daObjHhaPart_c::*daObjHhaPartCallBack)(daObjHha_c*);

    /* 0x00 */ J3DModel* mpModel;
    /* 0x04 */ dBgW* mpBgw;
    /* 0x08 */ cXyz m08;
    /* 0x14 */ cXyz m14;
    /* 0x20 */ cXyz m20;
    /* 0x2C */ float f2C;
    /* 0x30 */ u8 partIdx;
    /* 0x31 */ u8 u31;
    /* 0x34 */ daObjHhaPartCallBack m34;
    /* 0x40 */ daObjHhaPartCallBack m40;
}; // 0x4C

class daObjHhaSplash_c : public dPa_followEcallBack {
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

    void create_s(unsigned short, cXyz*, float, float, csXyz*);

public:
    /* 0x14 */ cXyz m14;
    /* 0x20 */ cXyz mPos;
    /* 0x2C */ csXyz mAngle;
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

    BOOL create_area(const char*);
    void init_data(cXyz*, f32, csXyz*, cXyz*, dKy_tevstr_c*, u8);
    void init_mtx();
    BOOL draw();

public:
    /* 0x000 */ J3DModel* mpModel;
    /* 0x004 */ mDoExt_btkAnm mBtk;
    /* 0x018 */ mDoExt_bckAnm mBck;
    /* 0x028 */ dKy_tevstr_c mTev;
    /* 0x0D8 */ cXyz mD8;
    /* 0x0E4 */ cXyz mTrans;
    /* 0x0F0 */ cXyz mScale;
    /* 0x0FC */ csXyz mRot;
    /* 0x102 */ u8 bVisible;
};

class daObjHha_c : public fopAc_ac_c {
public:

    s32 check_sw(); // weak but not inline?

    static int solidHeapCB(fopAc_ac_c*);
    BOOL create_heap();
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
    static const dCcD_SrcCyl M_cyl_data;
    static const dCcD_SrcSph M_sph_data;
    static const char M_arcname[4];

    /* 0x290 */ J3DModel* mpModel;
    /* 0x294 */ mDoExt_btkAnm mBtkA[2];
    /* 0x2BC */ request_of_phase_process_class mPhs;
    /* 0x2C4 */ dCcD_Stts mCylStts;
    /* 0x300 */ dCcD_Cyl mCyl;
    /* 0x430 */ bool b430;
    /* 0x434 */ dCcD_Stts cSphStts;
    /* 0x470 */ dCcD_Sph mSph;
    /* 0x59C */ daObjHhaYgush_c mYgush;
    /* 0x6A0 */ daObjHhaPart_c mPartA[2];
    /* 0x738 */ daObjHhaSplash_c mSplashA[2];
    /* 0x7A0 */ cXyz m7A0;
    /* 0x7AC */ u32 iNo;
    /* 0x7B0 */ u8 i7B0;
    /* 0x7B2 */ short i7B2;
    /* 0x7B4 */ float f7B4;
    /* 0x7B8 */     u8 pad7B8[8];
    /* 0x7C0 */ short m7C0;
    /* 0x7C2 */ u8 i7C2;
    /* 0x7C3 */ u8 i7C3;
};

#endif /* D_A_OBJ_HHA_H */
