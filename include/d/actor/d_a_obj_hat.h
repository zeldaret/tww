#ifndef D_A_OBJ_HAT_H
#define D_A_OBJ_HAT_H

#include "SSystem/SComponent/c_phase.h"
#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

class daObjHat_c : public fopAc_ac_c {
public:
    enum Prm_e {
        PRM_SWSAVE_W = 8,
        PRM_SWSAVE_S = 0,

        PRM_SCL_W = 2,
        PRM_SCL_S = 8,

        PRM_ALWAYS_W = 1,
        PRM_ALWAYS_S = 12,

        PRM_ARG0_W = 4,
        PRM_ARG0_S = 16,
    };

    daObjHat_c();

    s32 _create();
    int createHeap();
    s32 createInit();
    bool _delete();
    bool _draw();
    bool _execute();
    void executeNormal();
    u32 getPrmHatNo();
    void setMtx();
    void setSpeed(cXyz);

public:
    typedef void(daObjHat_c::*MoveFunc_t)();


    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* model;
    /* 0x29c */ mDoExt_McaMorf* mpMorf;
    /* 0x2a0 */ Mtx mMtx;

    /* 0x2d0 */ dBgS_ObjAcch acch;
    /* 0x494 */ dBgS_AcchCir acch_cir;
    /* 0x4d4 */ dCcD_Stts stts;
    /* 0x510 */ dCcD_Cyl cyl;

    /* 0x640 */ cXyz angle;
    /* 0x64c */ u8 procid;
    /* 0x64d */ u8 id;
    /* 0x64e */ u8 byte2;
    /* 0x64f */ u8 byte3;
    /* Place member variables here */
};

#endif /* D_A_OBJ_HAT_H */
