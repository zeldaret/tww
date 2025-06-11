/**
 * d_a_demo_dk.cpp
 * NPC - Helmaroc King (Forsaken Fortress 1 exterior)
 */

#include "d/actor/d_a_demo_dk.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 00000078-000000E8       .text daDEMO_DK_Draw__FP13demo_dk_class */
static BOOL daDEMO_DK_Draw(demo_dk_class*) {
    /* Nonmatching */
}

/* 000000E8-00000210       .text anm_init__FP13demo_dk_classifUcfi */
void anm_init(demo_dk_class*, int, float, unsigned char, float, int) {
    /* Nonmatching */
}

/* 00000210-000002EC       .text mode_wait__FP13demo_dk_class */
void mode_wait(demo_dk_class*) {
    /* Nonmatching */
}

/* 000002EC-00000378       .text mode_akubi__FP13demo_dk_class */
void mode_akubi(demo_dk_class*) {
    /* Nonmatching */
}

/* 00000378-000004C0       .text daDEMO_DK_Execute__FP13demo_dk_class */
static BOOL daDEMO_DK_Execute(demo_dk_class*) {
    /* Nonmatching */
}

/* 000004C0-000004C8       .text daDEMO_DK_IsDelete__FP13demo_dk_class */
static BOOL daDEMO_DK_IsDelete(demo_dk_class*) {
    return TRUE;
}

/* 000004C8-000004F8       .text daDEMO_DK_Delete__FP13demo_dk_class */
static BOOL daDEMO_DK_Delete(demo_dk_class*) {
    /* Nonmatching */
}

/* 000004F8-000005FC       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000005FC-00000714       .text daDEMO_DK_Create__FP10fopAc_ac_c */
static cPhs_State daDEMO_DK_Create(fopAc_ac_c*) {
    /* Nonmatching */
}

static actor_method_class l_daDEMO_DK_Method = {
    (process_method_func)daDEMO_DK_Create,
    (process_method_func)daDEMO_DK_Delete,
    (process_method_func)daDEMO_DK_Execute,
    (process_method_func)daDEMO_DK_IsDelete,
    (process_method_func)daDEMO_DK_Draw,
};

actor_process_profile_definition g_profile_DEMO_DK = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_DEMO_DK,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(demo_dk_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_DEMO_DK,
    /* Actor SubMtd */ &l_daDEMO_DK_Method,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENV_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
