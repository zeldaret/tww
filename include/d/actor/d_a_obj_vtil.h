#ifndef D_A_OBJ_VTIL_H
#define D_A_OBJ_VTIL_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"

class daObjVtil_c : public fopAc_ac_c {
public:
    enum Mode {
        MODE_WAIT  = 0x0,
        MODE_CARRY = 0x1,
        MODE_THROW  = 0x2,
        MODE_SINK  = 0x3,
        MODE_VIB2  = 0x4,
        MODE_JUMP  = 0x5,
        MODE_WALK  = 0x6,
    };

    enum Prm_e {
        PRM_TYPE_W = 0x4,
        PRM_TYPE_S = 0x0,
    };

    BOOL check_ev_bit() const; // weak but not inlined?

    static BOOL solidHeapCB(fopAc_ac_c*);
    BOOL create_heap();
    cPhs_State _create();
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
    BOOL check_sink();
    BOOL check_sink_end();
    void hit_bg();
    void make_vib();
    BOOL check_circle();
    BOOL _execute();
    bool _draw();

    static const char M_arcname[];
    static const int l_daObjVtil_scene_no_table[];
    static const int l_daObjVtil_bdl_idx_table[];
    static const dCcD_SrcCyl M_co_cyl_data;

public:
    /* 0x290 */ J3DModel* mpModel;
    /* 0x294 */ request_of_phase_process_class mPhs;
    /* 0x29C */ dBgS_Acch mAcch;
    /* 0x460 */ dBgS_AcchCir mAcchCir;
    /* 0x4A0 */ dCcD_Stts mStts;
    /* 0x4DC */ dCcD_Cyl mCyl;
    /* 0x60C */ int m60C;
    /* 0x610 */ f32 mSpeedY;
    /* 0x614 */ Mode mMode;
    /* 0x615 */ u8 m615;
    /* 0x616 */ u8 m616;
    /* 0x617 */ u8 field_0x617[0x61C - 0x617];
    /* 0x61C */ LIGHT_INFLUENCE mPLight;
};  // Size: 0x63C

#endif /* D_A_OBJ_VTIL_H */
