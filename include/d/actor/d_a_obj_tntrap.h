#ifndef D_A_OBJ_TNTRAP_H
#define D_A_OBJ_TNTRAP_H

#include "JSystem/JParticle/JPAEmitter.h"
#include "d/d_a_obj.h"
#include "d/d_bg_w.h"
#include "f_op/f_op_actor.h"

struct SomeStruct {
    Mtx calcMtx;
    JPABaseEmitter* emitterPairs[2][2];  
    JPABaseEmitter* emitterPairs2[1][3];  
};

class daObjTnTrap_c : public fopAc_ac_c {
public:
    enum Prm_e{
        PRM_SWSAVE_W = 0x08,
        PRM_SWSAVE_S = 0x00,

        PRM_SWSAVE2_W = 0x08,
        PRM_SWSAVE2_S = 0x08,

        PRM_ARG0_W   = 0x01,
        PRM_ARG0_S   = 0x10,

        PRM_MAPTYPE_W  = 0x2,
        PRM_MAPTYPE_S  = 0x11,
    };
    int param_get_arg0() const {return daObj::PrmAbstract<Prm_e>(this,PRM_ARG0_W,PRM_ARG0_S);}
    int param_get_mapType() const {return daObj::PrmAbstract<Prm_e>(this,PRM_MAPTYPE_W,PRM_MAPTYPE_S);}
    int param_get_swSave() const {return daObj::PrmAbstract<Prm_e>(this,PRM_SWSAVE_W,PRM_SWSAVE_S);}
    int param_get_swSave2() const {return daObj::PrmAbstract<Prm_e>(this,PRM_SWSAVE2_W,PRM_SWSAVE2_S);}

    BOOL chk_appear();
    void set_mtx();
    int solidHeapCB(fopAc_ac_c*);
    bool create_heap();
    void particle_set(int, float);
    void particle_delete(int);
    void set_se();
    void set_tri(int);
    void chk_event_flg();
    void set_em_set_offsetY();
    cPhs_State _create();
    bool _delete();
    void trap_off_wait_act_proc();
    void trap_on_wait_act_proc();
    void demo_regist_wait_act_proc();
    void demo_wait_act_proc();
    void demo_wait2_act_proc();
    void demo_end_wait_act_proc();
    void hide_wait_act_proc();
    void dummy_proc();
    void trap_off_wait_act_init_proc();
    void trap_on_wait_act_init_proc();
    void demo_regist_wait_act_init_proc();
    void demo_wait2_act_init_proc();
    void demo_end_wait_act_init_proc();
    void setup_action(int);
    bool _execute();
    bool _draw();

public:
    /* 0x290 */ u8 field_0x290[0x298 - 0x290];
    /* 0x298 */ s32 field_0x298;
    /* 0x29C */ u8 field_0x29C[0xD58 - 0x29C];
    /* 0xD58 */ dBgW* field_0xD58;
    /* 0xD5C */ SomeStruct field_0xD5C;
    ///* 0xD8C */ JPABaseEmitter** field_0xD8C;
    /* 0xD90 */ u8 field_0xDAB[0xDC0 - 0xDAB];
    /* 0xDC0 */ int field_0xDC0;
    /* 0xDC4 */ u8 field_0xDC4[0xDC8 - 0xDC4];
    /* 0xDC8 */ int field_0xDC8;
    /* 0xDCC */ int field_0xDCC;
    /* 0xDD0 */ int field_0xDD0;
    /* 0xDD4 */ s32 field_0xDD4;
    /* 0xDD8 */ u8 field_0xDD8[0xDE0 - 0xDD8];
    /* 0xDE0 */ u8 field_0xDE0[4];
    /* 0xDE4 */ f32 field_0xDE4[2];
    /* 0xDE8 */ //u8 field_0xDE8[0xDEC - 0xDE8];
};  // Size: 0xDEC


#endif /* D_A_OBJ_TNTRAP_H */
