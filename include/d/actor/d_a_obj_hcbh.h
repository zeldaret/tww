#ifndef D_A_OBJ_HCBH_H
#define D_A_OBJ_HCBH_H

#include "d/d_a_obj.h"
#include "d/d_bg_s_acch.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

class dBgW;

class daObjHcbh_c : public fopAc_ac_c {
public:
    enum Param_e {
        PRM_ITEMNO_W = 0x06,
        PRM_ITEMNO_S = 0x00,
        PRM_ITEMBIT_W = 0x07,
        PRM_ITEMBIT_S = 0x06,
        PRM_SWSAVE_W = 0x08,
        PRM_SWSAVE_S = 0x0D,
    };

    int param_get_itemNo() const { return daObj::PrmAbstract(this, PRM_ITEMNO_W, PRM_ITEMNO_S); }
    int param_get_itemSaveBitNo() const { return daObj::PrmAbstract(this, PRM_ITEMBIT_W, PRM_ITEMBIT_S); }
    int param_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
    void param_on_swSave() const {
        const int saveParam = param_get_swSave();
        if (saveParam != 0xFF) {
            fopAcM_onSwitch(const_cast<daObjHcbh_c*>(this), saveParam);
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

private:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mModel;
    /* 0x29C */ J3DModel* mBdlModels[4];
    /* 0x2AC */ dBgW* mBgW;
    /* 0x2B0 */ dBgW* mBdlBgW;
    /* 0x2B4 */ dBgS_ObjAcch mAcch;
    /* 0x478 */ dBgS_AcchCir mCircle;
    /* 0x4B8 */ dCcD_Stts mStts;
    /* 0x4F4 */ dCcD_Cyl mCyl;
    /* 0x624 */ dCcD_Sph mSph[6];
    /* 0xD2C */ f32 mCurY;
    /* 0xD30 */ f32 mVertStep;
    /* 0xD34 */ s16 mPitch;
    /* 0xD36 */ s16 mPitchStep;
    /* 0xD38 */ cXyz mBdlPos[4];
    /* 0xD68 */ f32 mBdlYStep[4];
    /* 0xD78 */ s16 mBdlPitch[4];
    /* 0xD80 */ s16 mBdlYaw[4];
    /* 0xD88 */ s16 mBdlPitchStep[4];
    /* 0xD90 */ int mFallTimer[4];
    /* 0xDA0 */ s16 mYaw;
    /* 0xDA4 */ int mBrokenBy;
    /* 0xDA8 */ dPa_smokeEcallBack mSmokeCallback;
    /* 0xDC8 */ u8 mAppear;
    /* 0xDCC */ void (daObjHcbh_c::*mProcFunc)(void);
};

#endif /* D_A_OBJ_HCBH_H */
