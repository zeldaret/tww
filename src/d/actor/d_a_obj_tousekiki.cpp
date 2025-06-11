/**
 * d_a_obj_tousekiki.cpp
 * Object - Catapult (Tetra's Ship)
 */

#include "d/actor/d_a_obj_tousekiki.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 000000EC-0000010C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 0000010C-000002BC       .text CreateHeap__17daObj_Tousekiki_cFv */
void daObj_Tousekiki_c::CreateHeap() {
    /* Nonmatching */
}

/* 000002BC-000002DC       .text daObj_TousekikiCreate__FPv */
static s32 daObj_TousekikiCreate(void* i_this) {
    return ((daObj_Tousekiki_c*)i_this)->_create();
}

/* 000002DC-000004F4       .text _create__17daObj_Tousekiki_cFv */
cPhs_State daObj_Tousekiki_c::_create() {
    /* Nonmatching */
}

/* 000006E8-00000718       .text daObj_TousekikiDelete__FPv */
static BOOL daObj_TousekikiDelete(void*) {
    /* Nonmatching */
}

/* 00000718-000008A4       .text daObj_TousekikiExecute__FPv */
static BOOL daObj_TousekikiExecute(void*) {
    /* Nonmatching */
}

/* 000008A4-00000934       .text daObj_TousekikiDraw__FPv */
static BOOL daObj_TousekikiDraw(void*) {
    /* Nonmatching */
}

/* 00000934-0000093C       .text daObj_TousekikiIsDelete__FPv */
static BOOL daObj_TousekikiIsDelete(void*) {
    return TRUE;
}

static actor_method_class daObj_TousekikiMethodTable = {
    (process_method_func)daObj_TousekikiCreate,
    (process_method_func)daObj_TousekikiDelete,
    (process_method_func)daObj_TousekikiExecute,
    (process_method_func)daObj_TousekikiIsDelete,
    (process_method_func)daObj_TousekikiDraw,
};

actor_process_profile_definition g_profile_Obj_Tousekiki = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Tousekiki,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObj_Tousekiki_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Tousekiki,
    /* Actor SubMtd */ &daObj_TousekikiMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_4_e,
};
