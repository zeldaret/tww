/**
 * d_a_kytag04.cpp
 * Tag - Weather Tag 4
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_kytag04.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 00000078-00000080       .text daKytag04_Draw__FP13kytag04_class */
static BOOL daKytag04_Draw(kytag04_class*) {
    return TRUE;
}

/* 00000080-00000138       .text daKytag04_Execute__FP13kytag04_class */
static BOOL daKytag04_Execute(kytag04_class* i_this) {
    if (i_this->mSwitchNo != 0xff && dComIfGs_isSwitch(i_this->mSwitchNo, dComIfGp_roomControl_getStayNo())) {
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
    return TRUE;
}

/* 00000160-00000168       .text daKytag04_Delete__FP13kytag04_class */
static BOOL daKytag04_Delete(kytag04_class*) {
    return TRUE;
}

/* 00000168-00000208       .text daKytag04_Create__FP10fopAc_ac_c */
static cPhs_State daKytag04_Create(fopAc_ac_c* i_this)  {
    fopAcM_SetupActor(i_this, kytag04_class);
    kytag04_class* a_this = (kytag04_class*)i_this;
    a_this->mState = 0;
    a_this->mOffColPat = fopAcM_GetParam(a_this) & 0xFF;
    a_this->mOnColPat = (fopAcM_GetParam(a_this) >> 8) & 0xFF;
    a_this->mSwitchNo = a_this->current.angle.x;
    a_this->mScaleX = a_this->scale.x * 100.0f;
    a_this->mScaleY = a_this->scale.y * 100.0f;
    a_this->mTimer = 0;
    a_this->mTimerThreshold = 5;
    return cPhs_COMPLEATE_e;
}

static actor_method_class l_daKytag04_Method = {
    (process_method_func)daKytag04_Create,
    (process_method_func)daKytag04_Delete,
    (process_method_func)daKytag04_Execute,
    (process_method_func)daKytag04_IsDelete,
    (process_method_func)daKytag04_Draw,
};

actor_process_profile_definition g_profile_KYTAG04 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_KYTAG04,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(kytag04_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_KYTAG04,
    /* Actor SubMtd */ &l_daKytag04_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
