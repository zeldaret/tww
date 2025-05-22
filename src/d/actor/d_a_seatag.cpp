/*
 * d_a_seatag.cpp
 */
#include "d/actor/d_a_seatag.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 00000078-00000080       .text daSeatag_Draw__FP10daSeatag_c */
static BOOL daSeatag_Draw(daSeatag_c*) {
    return TRUE;
}

/* 00000080-00000088       .text daSeatag_Execute__FP10daSeatag_c */
static  BOOL daSeatag_Execute(daSeatag_c*) {
    return TRUE;
}

/* 00000088-00000090       .text daSeatag_IsDelete__FP10daSeatag_c */
static BOOL daSeatag_IsDelete(daSeatag_c*) {
    return TRUE;
}

/* 00000090-000000C0       .text daSeatag_Delete__FP10daSeatag_c */
static BOOL daSeatag_Delete(daSeatag_c* a_this) {
    a_this->~daSeatag_c();
    return TRUE;
}

/* 000000C0-00000110       .text daSeatag_Create__FP10fopAc_ac_c */
static cPhs_State daSeatag_Create(fopAc_ac_c* a_this) {
    fopAcM_SetupActor(a_this, daSeatag_c);
    return cPhs_COMPLEATE_e;
}

static actor_method_class l_daSeatag_Method = {
    (process_method_func)daSeatag_Create,
    (process_method_func)daSeatag_Delete,
    (process_method_func)daSeatag_Execute,
    (process_method_func)daSeatag_IsDelete,
    (process_method_func)daSeatag_Draw,
};

actor_process_profile_definition g_profile_SEATAG = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0002,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_SEATAG,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daSeatag_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_SEATAG,
    /* Actor SubMtd */ &l_daSeatag_Method,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
