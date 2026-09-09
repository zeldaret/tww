#ifndef D_A_OBJ_HCBH_H
#define D_A_OBJ_HCBH_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "d/d_particle.h"
#include "d/d_a_obj.h"
#include "d/d_com_inf_game.h"

class daObjHcbh_c : public fopAc_ac_c {
public:
    enum Param_e {
        PRM_ITEM_NO_W = 6,
        PRM_ITEM_NO_S = 0,
        PRM_ITEM_SAVE_BIT_NO_W = 7,
        PRM_ITEM_SAVE_BIT_NO_S = 6,
        PRM_SWSAVE_W = 8,
        PRM_SWSAVE_S = 0xD,
    };

    int param_get_itemNo() const { return daObj::PrmAbstract(this, PRM_ITEM_NO_W, PRM_ITEM_NO_S); }
    int param_get_itemSaveBitNo() const { return daObj::PrmAbstract(this, PRM_ITEM_SAVE_BIT_NO_W, PRM_ITEM_SAVE_BIT_NO_S); }
    int param_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
    void param_on_swSave() {
        int swSave = param_get_swSave();
        if (swSave != 0xFF) {
            dComIfGs_onSwitch(swSave, home.roomNo);
        }
    }

    bool chk_appear();
    void set_mtx();
    void init_mtx();
    static BOOL solidHeapCB(fopAc_ac_c*);
    bool create_heap();
    void setup_break_condition(fopAc_ac_c*);
    void checkCollision();
    static void co_hitCallback(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*);
    void particle_set();
    void make_item();
    cPhs_State _create();
    bool _delete();
    void wait_act_proc();
    void fall_act_proc();
    bool _execute();
    bool _draw();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ J3DModel* mpFaceModel[4];
    /* 0x2AC */ dBgW* mpBgW1;
    /* 0x2B0 */ dBgW* mpBgW2;
    /* 0x2B4 */ dBgS_ObjAcch mAcch;
    /* 0x478 */ dBgS_AcchCir mAcchCir;
    /* 0x4B8 */ dCcD_Stts mStts;
    /* 0x4F4 */ dCcD_Cyl mCyl;
    /* 0x624 */ dCcD_Sph mSph[6];
    /* 0xD2C */ f32 mFallY;
    /* 0xD30 */ f32 mFallSpeed;
    /* 0xD34 */ s16 mTiltX;
    /* 0xD36 */ s16 mTiltSpeed;
    /* 0xD38 */ cXyz mFacePos[4];
    /* 0xD68 */ f32 mFaceFallSpeed[4];
    /* 0xD78 */ s16 mFaceAngX[4];
    /* 0xD80 */ s16 mFaceAngY[4];
    /* 0xD88 */ s16 mFaceRotSpeed[4];
    /* 0xD90 */ s32 mFaceTimer[4];
    /* 0xDA0 */ s16 mFaceDirY;
    /* 0xDA4 */ s32 mBreakMode;
    /* 0xDA8 */ dPa_smokeEcallBack mSmokeCallback;
    /* 0xDC8 */ u8 mAppear;
    /* 0xDCC */ void (daObjHcbh_c::*mActProc)();
};  // Size: 0xDD8

#endif /* D_A_OBJ_HCBH_H */
