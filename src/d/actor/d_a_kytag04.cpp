/**
 * d_a_kytag04.cpp
 */

#include "d/actor/d_a_kytag04.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "dolphin/types.h"

static BOOL daKytag04_Draw(kytag04_class*) {
    return true;
}

/* 00000080-00000138       .text daKytag04_Execute__FP13kytag04_class */
static BOOL daKytag04_Execute(kytag04_class* i_this) {
    if (i_this->mSwitchId != 0xff && dComIfGs_isSwitch(i_this->mSwitchId, dComIfGp_roomControl_getStayNo())) {
        if (i_this->mState == 0) {
            if (i_this->mTimer >= i_this->mTimerThreshold) {
                i_this->mTimer = 0;
                dKy_change_colpat(i_this->mOnColPat);
                i_this->mState = 1;
            } else {
                i_this->mTimer = i_this->mTimer + 1;
            }
        }
    } else if(i_this->mState == 1) {
        dKy_change_colpat(i_this->mOffColPat);
        i_this->mState = 0;
    }

    return TRUE;
}

/* 00000138-00000160       .text daKytag04_IsDelete__FP13kytag04_class */
static BOOL daKytag04_IsDelete(kytag04_class* i_this) {
    dKy_change_colpat(i_this->mOffColPat);
    return true;
}

/* 00000160-00000168       .text daKytag04_Delete__FP13kytag04_class */
static BOOL daKytag04_Delete(kytag04_class*) {
    return true;
}

/* 00000168-00000208       .text daKytag04_Create__FP10fopAc_ac_c */
static int daKytag04_Create(fopAc_ac_c* i_this)  {
    fopAcM_SetupActor(i_this, kytag04_class);
    kytag04_class* a_this = (kytag04_class*)i_this;
    a_this->mState = 0;
    a_this->mOffColPat = a_this->mBase.mParameters;
    a_this->mOnColPat = a_this->mBase.mParameters >> 8;
    a_this->mSwitchId = a_this->current.angle.x;
    a_this->mScaleX = a_this->mScale.x * 100.0f;
    a_this->mScaleY = a_this->mScale.y * 100.0f;
    a_this->mTimer = 0;
    a_this->mTimerThreshold = 5;
    return 4;
}

static actor_method_class l_daKytag04_Method = {
    (process_method_func)daKytag04_Create,
    (process_method_func)daKytag04_Delete,
    (process_method_func)daKytag04_Execute,
    (process_method_func)daKytag04_IsDelete,
    (process_method_func)daKytag04_Draw,
};

actor_process_profile_definition g_profile_KYTAG04 = {
    fpcLy_CURRENT_e,
    7,
    fpcLy_CURRENT_e,
    PROC_KYTAG04,
    &g_fpcLf_Method.mBase,
    sizeof(kytag04_class),
    0,
    0,
    &g_fopAc_Method.base,
    0xA4,
    &l_daKytag04_Method,
    fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    fopAc_ACTOR_e,
    fopAc_CULLBOX_0_e,
};
