#ifndef D_A_OBJ_ICE_H
#define D_A_OBJ_ICE_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_a_obj.h"
#include "f_op/f_op_actor_mng.h"

class dBgW;
class dBgS;

class daObjIce_c : public fopAc_ac_c {
    typedef void (daObjIce_c::*memberFuncPtr)();

    enum Param_e {
        PRM_SWSAVE_W = 8,
        PRM_SWSAVE_S = 0,
    };

public:
    s32 param_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
    void param_on_swSave() const {
        const s32 sw = param_get_swSave();
        if (sw != 0xFF) {
            fopAcM_onSwitch((fopAc_ac_c*)this, sw);
        }
    }
    inline void setEffectMtx();

    u8 chk_appear();
    void set_mtx();
    void init_mtx();
    static BOOL solidHeapCB(fopAc_ac_c*);
    bool create_heap();
    static void tg_hitCallback(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*);
    cPhs_State _create();
    bool _delete();
    void wait_act_proc();
    void fade_out_retire_act_proc();
    bool _execute();
    bool _draw();

public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mModel;
    /* 0x29C */ dCcD_Stts mStts;
    /* 0x2D8 */ dCcD_Cyl mCyl;
    /* 0x408 */ dBgW* mBgw;
    /* 0x40C */ Mtx m40C;
    /* 0x43C */ memberFuncPtr m43C;
    /* 0x448 */ u8 m448;
    /* 0x44C */ f32 m44C;
    /* 0x450 */ f32 m450;
    /* 0x454 */ f32 m454;
    /* 0x458 */ s32 m458;
    /* 0x45C */ s32 m45C;
}; // size = 0x460

#endif /* D_A_OBJ_ICE_H */
