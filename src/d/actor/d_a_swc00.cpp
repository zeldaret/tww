//
// Generated by dtk
// Translation Unit: d_a_swc00.cpp
//

#include "d/actor/d_a_swc00.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_com_inf_game.h"

/* 00000078-00000180       .text daSwc00_Execute__FP11swc00_class */
static BOOL daSwc00_Execute(swc00_class* i_this) {
    s32 enable_sw = daSwc00_getSw2No(i_this);
    fopAc_ac_c* actor = i_this;
    if(enable_sw == 0xFF || dComIfGs_isSwitch(enable_sw, fopAcM_GetRoomNo(i_this))) {
        s32 swBit = daSwc00_getSw1No(i_this);

        f32 xz_dist2 = fopAcM_searchPlayerDistanceXZ2(i_this);
        f32 y_diff = fopAcM_searchPlayerDistanceY(i_this);
        if(xz_dist2 < i_this->scale.x && (-100.0f < y_diff && y_diff < i_this->scale.y)) {
            dComIfGs_onSwitch(swBit, fopAcM_GetRoomNo(i_this));

            if(daSwc00_getType(i_this) != 0) {
                fopAcM_delete(actor);
            }
        }
        else if(daSwc00_getType(i_this) == 0) {
            dComIfGs_offSwitch(swBit, fopAcM_GetRoomNo(i_this));
        }
    }

    return TRUE;
}

/* 00000180-00000188       .text daSwc00_IsDelete__FP11swc00_class */
static BOOL daSwc00_IsDelete(swc00_class* i_this) {
    return TRUE;
}

/* 00000188-00000190       .text daSwc00_Delete__FP11swc00_class */
static BOOL daSwc00_Delete(swc00_class* i_this) {
    return TRUE;
}

/* 00000190-00000274       .text daSwc00_Create__FP10fopAc_ac_c */
static cPhs_State daSwc00_Create(fopAc_ac_c* i_actor) {
    fopAcM_SetupActor(i_actor, swc00_class);

    swc00_class* i_this = (swc00_class*)i_actor;

    if(dComIfGs_isSwitch(daSwc00_getSw1No(i_this), fopAcM_GetRoomNo(i_this))) {
        if(daSwc00_getType(i_this) == 0) {
            s32 swBit = daSwc00_getSw1No(i_this);
            dComIfGs_offSwitch(swBit, fopAcM_GetRoomNo(i_this));
        }
        else {
            return cPhs_ERROR_e;
        }
    }

    i_this->scale.x *= 100.0f;
    i_this->scale.x += 30.0f;
    i_this->scale.x *= i_this->scale.x;
    i_this->scale.y *= 100.0f;

    return cPhs_COMPLEATE_e;
}

static actor_method_class l_daSwc00_Method = {
    (process_method_func)daSwc00_Create,
    (process_method_func)daSwc00_Delete,
    (process_method_func)daSwc00_Execute,
    (process_method_func)daSwc00_IsDelete,
    (process_method_func)NULL,
};

actor_process_profile_definition g_profile_SWC00 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_SWC00,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(swc00_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_SWC00,
    /* Actor SubMtd */ &l_daSwc00_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
