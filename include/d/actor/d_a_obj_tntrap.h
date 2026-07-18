#ifndef D_A_OBJ_TNTRAP_H
#define D_A_OBJ_TNTRAP_H

#include "JSystem/JParticle/JPAEmitter.h"
#include "d/d_a_obj.h"
#include "d/d_bg_w.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"



struct ParticleData {
    Mtx calcMtx;
    JPABaseEmitter* emitterPairs[2][2];  
    JPABaseEmitter* emitterPairs2[1][3];  
};

class daObjTnTrap_c : public fopAc_ac_c {

typedef bool(daObjTnTrap_c::*ActProcFunc)();
typedef void(daObjTnTrap_c::*InitProcFunc)();

public:
    enum Param_e{
        PRM_SWSAVE_W = 0x08,
        PRM_SWSAVE_S = 0x00,

        PRM_SWSAVE2_W = 0x08,
        PRM_SWSAVE2_S = 0x08,

        PRM_ARG0_W   = 0x01,
        PRM_ARG0_S   = 0x10,

        PRM_MAPTYPE_W  = 0x2,
        PRM_MAPTYPE_S  = 0x11,
    };
    int param_get_arg0() const {return daObj::PrmAbstract<Param_e>(this,PRM_ARG0_W,PRM_ARG0_S);}
    int param_get_mapType() const {return daObj::PrmAbstract<Param_e>(this,PRM_MAPTYPE_W,PRM_MAPTYPE_S);}
    int param_get_swSave() const {return daObj::PrmAbstract<Param_e>(this,PRM_SWSAVE_W,PRM_SWSAVE_S);}
    int param_get_swSave2() const {return daObj::PrmAbstract<Param_e>(this,PRM_SWSAVE2_W,PRM_SWSAVE2_S);}

    BOOL chk_appear();
    void set_mtx();
    static int solidHeapCB(fopAc_ac_c*);
    bool create_heap();
    void particle_set(int, float);
    void particle_delete(int);
    void set_se();
    void set_tri(int);
    bool chk_event_flg();
    void set_em_set_offsetY();
    cPhs_State _create();
    bool _delete();
    bool trap_off_wait_act_proc();
    bool trap_on_wait_act_proc();
    bool demo_regist_wait_act_proc();
    bool demo_wait_act_proc();
    bool demo_wait2_act_proc();
    bool demo_end_wait_act_proc();
    bool hide_wait_act_proc();
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
    /* 0x290 */ request_of_phase_process_class mPhaseProcess;
    /* 0x298 */ s32 mEventState;
    /* 0x29C */ dCcD_Stts mStts;
    /* 0x2D8 */ dCcD_Tri mTri[2][4];
    /* 0xD58 */ dBgW* mpCollision;
    /* 0xD5C */ ParticleData mParticleData;
    /* 0xDA8 */ u8 pad_0xDA8[0xC];          //Perhaps Unused PTMF?
    /* 0xDB4 */ ActProcFunc mpActionFunc;
    /* 0xDC0 */ s32 mActionIdx;
    /* 0xDC4 */ u8 field_0xDC4;
    /* 0xDC8 */ s32 mSwSave;
    /* 0xDCC */ s32 mSwSave2;
    /* 0xDD0 */ s32 mArg0;
    /* 0xDD4 */ s32 mMapType;
    /* 0xDD8 */ s16 mEventIdxTbl[4];
    /* 0xDE0 */ bool mEmValidTbl[4];
    /* 0xDE4 */ f32 mEmSetOffsetY[2];
};  // Size: 0xDEC

#if VERSION == VERSION_DEMO
class daObjTnTrap_HIO_c : public JORReflexible{
public:
    daObjTnTrap_HIO_c();
    virtual ~daObjTnTrap_HIO_c(){};
public:
    s8    mNo;
    f32   mTrapActivateDist;
    f32   mTriYOffset;
    f32   mTriZOffset;
    f32   mMtxZOffset;
    f32   mTrapOnWaitF3;
    f32   mTrapOnWaitF2;
    bool  mExtraEventCheck;
    bool  mTogglePhantomGanonFlag;
    bool  mUnusedBool;
    bool  mUnusedBool2;
};
#endif

#endif /* D_A_OBJ_TNTRAP_H */
