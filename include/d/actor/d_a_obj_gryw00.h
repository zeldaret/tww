#ifndef D_A_OBJ_GRYW00_H
#define D_A_OBJ_GRYW00_H

#include "JSystem/JParticle/JPAEmitter.h"

#include "m_Do/m_Do_ext.h"
#include "f_op/f_op_actor.h"

#include "d/d_a_obj.h"
#include "d/d_bg_s_movebg_actor.h"

class daObjGryw00_c : public dBgS_MoveBgActor {
public:
    enum Param_e {
        PRM_SWSAVE_W = 0x08,
        PRM_SWSAVE_S = 0x00,
    };
    typedef void (daObjGryw00_c::*ModeFunc)();

    s32 param_get_swSave() const {
        return daObj::PrmAbstract<Param_e>(this, PRM_SWSAVE_W, PRM_SWSAVE_S);
    }

    f32 get_draw_water_lv(void*);
    BOOL setup_high_water_level_btk_anm();
    void particle_set();
    void particle_move();
    void particle_delete();
    void set_se();
    virtual BOOL CreateHeap();
    virtual BOOL Create();
    cPhs_State Mthd_Create();
    virtual BOOL Delete();
    BOOL Mthd_Delete();
    void switch_wait_act_proc();
    void spread_water_face_act_proc();
    void water_level_move_wait_act_proc();
    void anime_loop_start_wait_act_proc();
    void high_water_level_act_proc();
    virtual BOOL Execute(Mtx**);
    virtual BOOL Draw();

public:
    /* 0x2C8 */ request_of_phase_process_class mPhs;
    /* 0x2D0 */ J3DModel* mpModel;
    /* 0x2D4 */ Mtx mMtx;
    /* 0x304 */ mDoExt_btkAnm mBtk;
    /* 0x318 */ mDoExt_bckAnm mBck;
    /* 0x328 */ s32 mActivationSwitch;
    /* 0x32C */ void (daObjGryw00_c::*modeFunc)();
    /* 0x338 */ BOOL mIsHidden;
    /* 0x33C */ f32 mWaterLv;
    /* 0x340 */ f32 mWaterMaxLv;
    /* 0x344 */ f32 mWaterLvIncrement;
    /* 0x348 */ f32 mWaveAmplitude;
    /* 0x34C */ f32 mWaveMaxAmplitude;
    /* 0x350 */ f32 mWaveAmplitudeIncrement;
    /* 0x354 */ f32 mWaterLvFinalYPos;  // never read ? at least by this class
    /* 0x358 */ BOOL mShouldPlaySe;
    /* 0x35C */ s32 mGeyserSeRemaining;
    /* 0x360 */ JPABaseEmitter* mpEmitters[2];
};

#endif /* D_A_OBJ_GRYW00_H */
