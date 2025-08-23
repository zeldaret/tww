/**
 * d_a_kn.cpp
 * NPC - Crab
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_kn.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 00000078-00000120       .text daKN_Draw__FP8kn_class */
static BOOL daKN_Draw(kn_class*) {
    /* Nonmatching */
}

/* 00000120-00000248       .text anm_init__FP8kn_classifUcfi */
void anm_init(kn_class*, int, float, unsigned char, float, int) {
    /* Nonmatching */
}

/* 00000248-00000368       .text smoke_set__FP8kn_class */
void smoke_set(kn_class*) {
    /* Nonmatching */
}

/* 00000368-00000440       .text shibuki_set__FP8kn_class */
void shibuki_set(kn_class*) {
    /* Nonmatching */
}

/* 00000440-00000CE8       .text kn_move__FP8kn_class */
void kn_move(kn_class*) {
    /* Nonmatching */
}

/* 00000CE8-00000D64       .text BG_check__FP8kn_class */
void BG_check(kn_class*) {
    /* Nonmatching */
}

/* 00000D64-00000F80       .text daKN_Execute__FP8kn_class */
static BOOL daKN_Execute(kn_class*) {
    /* Nonmatching */
}

/* 00000F80-00000F88       .text daKN_IsDelete__FP8kn_class */
static BOOL daKN_IsDelete(kn_class*) {
    return TRUE;
}

/* 00000F88-00000FD8       .text daKN_Delete__FP8kn_class */
static BOOL daKN_Delete(kn_class*) {
    /* Nonmatching */
}

/* 00000FD8-000010E0       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000010E0-000012B0       .text daKN_Create__FP10fopAc_ac_c */
static cPhs_State daKN_Create(fopAc_ac_c*) {
    /* Nonmatching */
}

static actor_method_class l_daKN_Method = {
    (process_method_func)daKN_Create,
    (process_method_func)daKN_Delete,
    (process_method_func)daKN_Execute,
    (process_method_func)daKN_IsDelete,
    (process_method_func)daKN_Draw,
};

actor_process_profile_definition g_profile_KN = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_KN,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(kn_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_KN,
    /* Actor SubMtd */ &l_daKN_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENV_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
