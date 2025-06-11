/**
 * d_a_kokiie.cpp
 * Object - Forbidden Woods - Hanging flower house
 */

#include "d/actor/d_a_kokiie.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 000000B4-00000154       .text daKokiie_Draw__FP12kokiie_class */
static BOOL daKokiie_Draw(kokiie_class*) {
    /* Nonmatching */
}

/* 00000154-00000884       .text kokiie_move__FP12kokiie_class */
void kokiie_move(kokiie_class*) {
    /* Nonmatching */
}

/* 00000884-00000A18       .text himo_create__FP12kokiie_class */
void himo_create(kokiie_class*) {
    /* Nonmatching */
}

/* 00000A18-00000E98       .text demo_camera__FP12kokiie_class */
void demo_camera(kokiie_class*) {
    /* Nonmatching */
}

/* 00000E98-0000107C       .text daKokiie_Execute__FP12kokiie_class */
static BOOL daKokiie_Execute(kokiie_class*) {
    /* Nonmatching */
}

/* 0000107C-00001084       .text daKokiie_IsDelete__FP12kokiie_class */
static BOOL daKokiie_IsDelete(kokiie_class*) {
    return TRUE;
}

/* 00001084-000010E4       .text daKokiie_Delete__FP12kokiie_class */
static BOOL daKokiie_Delete(kokiie_class*) {
    /* Nonmatching */
}

/* 000010E4-00001250       .text CallbackCreateHeap__FP10fopAc_ac_c */
static BOOL CallbackCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00001250-000014E4       .text daKokiie_Create__FP10fopAc_ac_c */
static cPhs_State daKokiie_Create(fopAc_ac_c*) {
    /* Nonmatching */
}

static actor_method_class l_daKokiie_Method = {
    (process_method_func)daKokiie_Create,
    (process_method_func)daKokiie_Delete,
    (process_method_func)daKokiie_Execute,
    (process_method_func)daKokiie_IsDelete,
    (process_method_func)daKokiie_Draw,
};

actor_process_profile_definition g_profile_KOKIIE = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_KOKIIE,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(kokiie_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_KOKIIE,
    /* Actor SubMtd */ &l_daKokiie_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
