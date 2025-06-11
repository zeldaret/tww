/**
 * d_a_demo_kmm.cpp
 * NPC - Seagull (cutscenes)
 */

#include "d/actor/d_a_demo_kmm.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 00000078-00000098       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000098-00000190       .text CreateHeap__12daDemo_Kmm_cFv */
void daDemo_Kmm_c::CreateHeap() {
    /* Nonmatching */
}

/* 00000190-00000228       .text calcMtx__12daDemo_Kmm_cFv */
void daDemo_Kmm_c::calcMtx() {
    /* Nonmatching */
}

/* 00000228-000002D0       .text setAnime__12daDemo_Kmm_cFiiff */
void daDemo_Kmm_c::setAnime(int, int, float, float) {
    /* Nonmatching */
}

/* 000002D0-00000308       .text CreateInit__12daDemo_Kmm_cFv */
void daDemo_Kmm_c::CreateInit() {
    /* Nonmatching */
}

/* 00000308-000003A0       .text create__12daDemo_Kmm_cFv */
cPhs_State daDemo_Kmm_c::create() {
    /* Nonmatching */
}

/* 000003A0-000003A8       .text daDemo_Kmm_actionWait__FP12daDemo_Kmm_c */
void daDemo_Kmm_actionWait(daDemo_Kmm_c*) {
    /* Nonmatching */
}

/* 000003A8-0000040C       .text daDemo_Kmm_Draw__FP12daDemo_Kmm_c */
static BOOL daDemo_Kmm_Draw(daDemo_Kmm_c*) {
    /* Nonmatching */
}

/* 0000040C-000004A8       .text daDemo_Kmm_Execute__FP12daDemo_Kmm_c */
static BOOL daDemo_Kmm_Execute(daDemo_Kmm_c*) {
    /* Nonmatching */
}

/* 000004A8-000004B0       .text daDemo_Kmm_IsDelete__FP12daDemo_Kmm_c */
static BOOL daDemo_Kmm_IsDelete(daDemo_Kmm_c*) {
    return TRUE;
}

/* 000004B0-00000500       .text daDemo_Kmm_Delete__FP12daDemo_Kmm_c */
static BOOL daDemo_Kmm_Delete(daDemo_Kmm_c*) {
    /* Nonmatching */
}

/* 00000500-00000520       .text daDemo_Kmm_Create__FP10fopAc_ac_c */
static cPhs_State daDemo_Kmm_Create(fopAc_ac_c* i_this) {
    return ((daDemo_Kmm_c*)i_this)->create();
}

static actor_method_class l_daDemo_Kmm_Method = {
    (process_method_func)daDemo_Kmm_Create,
    (process_method_func)daDemo_Kmm_Delete,
    (process_method_func)daDemo_Kmm_Execute,
    (process_method_func)daDemo_Kmm_IsDelete,
    (process_method_func)daDemo_Kmm_Draw,
};

actor_process_profile_definition g_profile_DEMO_KMM = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_DEMO_KMM,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daDemo_Kmm_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_DEMO_KMM,
    /* Actor SubMtd */ &l_daDemo_Kmm_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_6_e,
};
