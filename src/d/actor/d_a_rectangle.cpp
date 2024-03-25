/**
 * d_a_rectangle.cpp
 * Unused Dummy Actor
 */

#include "d/actor/d_a_rectangle.h"
#include "f_op/f_op_actor.h"
#include "d/d_procname.h"
#include "SSystem/SComponent/c_phase.h"

/* 00000078-00000080       .text daRct_Draw__FP15RECTANGLE_class */
static BOOL daRct_Draw(RECTANGLE_class* i_this) {
    return TRUE;
}

/* 00000080-00000088       .text daRct_Execute__FP15RECTANGLE_class */
static BOOL daRct_Execute(RECTANGLE_class* i_this) {
    return TRUE;
}

/* 00000088-00000090       .text daRct_IsDelete__FP15RECTANGLE_class */
static BOOL daRct_IsDelete(RECTANGLE_class* i_this) {
    return TRUE;
}

/* 00000090-00000098       .text daRct_Delete__FP15RECTANGLE_class */
static BOOL daRct_Delete(RECTANGLE_class* i_this) {
    return TRUE;
}

/* 00000098-000000A0       .text daRct_Create__FP10fopAc_ac_c */
static int daRct_Create(fopAc_ac_c* i_this) {
    return cPhs_COMPLEATE_e;
}

static actor_method_class l_daRct_Method = {
    (process_method_func)daRct_Create,
    (process_method_func)daRct_Delete,
    (process_method_func)daRct_Execute,
    (process_method_func)daRct_IsDelete,
    (process_method_func)daRct_Draw,
};

actor_process_profile_definition g_profile_RECTANGLE = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 7,
    /* ListPrio     */ fpcLy_CURRENT_e,
    /* ProcName     */ PROC_RECTANGLE,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(RECTANGLE_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x9F,
    /* Actor SubMtd */ &l_daRct_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
