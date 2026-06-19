#ifndef D_A_OBJ_LEAVES_H
#define D_A_OBJ_LEAVES_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_a_obj.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor_mng.h"

class dBgW;

class daObjLeaves_c : public fopAc_ac_c {
    typedef void (daObjLeaves_c::*MemberFunc)();

    enum Param_e {
        PRM_ITEM_SAVE_BIT_NO_W = 7,
        PRM_ITEM_SAVE_BIT_NO_S = 6,

        PRM_ITEM_NO_W = 6,
        PRM_ITEM_NO_S = 0,

        PRM_SWSAVE_W = 8,
        PRM_SWSAVE_S = 13,
    };

public:
    s32 param_get_itemNo() const { return daObj::PrmAbstract(this, PRM_ITEM_NO_W, PRM_ITEM_NO_S); }
    s32 param_get_itemSaveBitNo() const { return daObj::PrmAbstract(this, PRM_ITEM_SAVE_BIT_NO_W, PRM_ITEM_SAVE_BIT_NO_S); }
    s32 param_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
    void param_on_swSave() const {
        const s32 swSave = param_get_swSave();
        if (swSave != 0xFF) {
            fopAcM_onSwitch((fopAc_ac_c*)this, swSave);
        }
    }

    bool chk_appear();
    void setPEmitter(JPABaseEmitter*);
    void init_mtx();
    void birthEffect(int, cXyz*, csXyz*, GXColor*);
    static BOOL solidHeapCB(fopAc_ac_c*);
    bool create_heap();
    static void tg_hitCallback(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*);
    bool checkCollision();
    void registFireCollision();
    cPhs_State _create();
    bool _delete();
    void wait_proc();
    void alpha_calc_start_wait_proc();
    void item_set_wait_proc();
    void retire_wait_proc();
    void retire_wait_without_particle_proc();
    bool _execute();
    bool _draw();

public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mModel;
    /* 0x29C */ dBgW* mpBgW;
    /* 0x2A0 */ dCcD_Stts mStts;
    /* 0x2DC */ dCcD_Sph mSph;
#if VERSION <= VERSION_JPN
    /* 0x408 */ dCcD_Cyl mCyl;
    /* 0x538 */ u8 m538;
#endif
    /* 0x408 */ f32 m408;
    /* 0x40C */ f32 m40C;
#if VERSION == VERSION_DEMO
    /* 0x544 */ JPABaseEmitter* m_emitter_p;
#endif
    /* 0x410 */ dPa_smokeEcallBack mSmokeCallback;
#if VERSION == VERSION_DEMO
    /* 0x430 */ f32 m430;
#else
    /* 0x430 */ s32 m430;
    /* 0x434 */ s32 m434;
#endif
    /* 0x438 */ s32 m438;
    /* 0x43C */ bool m43C;
    /* 0x440 */ MemberFunc mMemberFunc;
#if VERSION > VERSION_JPN
    /* 0x44C */ bool m44C;
#endif
}; // size = 0x450, demo size = 0x580

#endif /* D_A_OBJ_LEAVES_H */
