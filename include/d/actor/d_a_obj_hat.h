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
        PRM_HAT_NO_W = 8,
        PRM_HAT_NO_S = 0,
    };

    daObjHat_c();

    cPhs_State _create();
    BOOL createHeap();
    cPhs_State createInit();
    BOOL _delete();
    BOOL _draw();
    BOOL _execute();
    void executeNormal();
    u32 getPrmHatNo();
    void setMtx();
    void setSpeed(cXyz);

public:
    typedef void(daObjHat_c::*MoveFunc_t)();

    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29c */ mDoExt_McaMorf* mpMorf;
    /* 0x2a0 */ Mtx mMtx;

    /* 0x2d0 */ dBgS_ObjAcch mAcch;
    /* 0x494 */ dBgS_AcchCir mAcchCir;
    /* 0x4d4 */ dCcD_Stts mStts;
    /* 0x510 */ dCcD_Cyl mCyl;

    /* 0x640 */ cXyz mMoveNorm;
    /* 0x64c */ u8 mState;
    /* 0x64d */ u8 mHatNo;
}; /* size: 0x650 */

#endif /* D_A_OBJ_HAT_H */
