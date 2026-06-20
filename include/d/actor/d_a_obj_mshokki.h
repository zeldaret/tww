#ifndef D_A_OBJ_MSHOKKI_H
#define D_A_OBJ_MSHOKKI_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "d/d_a_obj.h"

class daObjMshokki_c : public fopAc_ac_c {
public:
    enum Param_e {
        PRM_ARG_W = 2,
        PRM_ARG_S = 0,
    };

    s32 param_get_arg() const { return daObj::PrmAbstract(this, PRM_ARG_W, PRM_ARG_S); }

    void set_mtx();
    static BOOL solidHeapCB(fopAc_ac_c*);
    bool create_heap();
    bool checkCollision();
    static void co_hitCallback(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*);
    void break_proc();
    void set_se();
    cPhs_State _create();
    bool _delete();
    bool _execute();
    bool _draw();

public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mModel;
    /* 0x29C */ dBgS_ObjAcch mAcch;
    /* 0x460 */ dBgS_AcchCir mAcchCir;
    /* 0x4A0 */ dCcD_Stts mStts;
    /* 0x4DC */ dCcD_Cyl mCyl;
    /* 0x60C */ s32 m60C;
    /* 0x610 */ u8 m610[0x612 - 0x610];
    /* 0x612 */ s16 m612;
    /* 0x614 */ s32 m614;
    /* 0x618 */ s32 m618;
    /* 0x61C */ s16 m61C;
}; // size = 0x620

#endif /* D_A_OBJ_MSHOKKI_H */
