/**
 * d_a_lstair.cpp
 * Object - Tower of the Gods - Glowing stairs
 */

#include "d/actor/d_a_lstair.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 00000078-000000D4       .text _delete__10daLStair_cFv */
bool daLStair_c::_delete() {
    /* Nonmatching */
}

/* 000000D4-000000F4       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000000F4-000004F8       .text CreateHeap__10daLStair_cFv */
void daLStair_c::CreateHeap() {
    /* Nonmatching */
}

/* 000004F8-00000638       .text CreateInit__10daLStair_cFv */
void daLStair_c::CreateInit() {
    /* Nonmatching */
}

/* 00000638-00000758       .text _create__10daLStair_cFv */
cPhs_State daLStair_c::_create() {
    /* Nonmatching */
}

/* 00000910-00000998       .text set_mtx__10daLStair_cFv */
void daLStair_c::set_mtx() {
    /* Nonmatching */
}

/* 00000998-00000A1C       .text setMoveBGMtx__10daLStair_cFv */
void daLStair_c::setMoveBGMtx() {
    /* Nonmatching */
}

/* 00000A1C-00000ACC       .text _execute__10daLStair_cFv */
bool daLStair_c::_execute() {
    /* Nonmatching */
}

/* 00000ACC-00000B8C       .text demoMove__10daLStair_cFv */
void daLStair_c::demoMove() {
    /* Nonmatching */
}

/* 00000B8C-00000C88       .text checkAppear__10daLStair_cFv */
void daLStair_c::checkAppear() {
    /* Nonmatching */
}

/* 00000C88-00000D78       .text moveBG__10daLStair_cFv */
void daLStair_c::moveBG() {
    /* Nonmatching */
}

/* 00000D78-00000F74       .text appear_stair__10daLStair_cFv */
void daLStair_c::appear_stair() {
    /* Nonmatching */
}

/* 00000F74-0000103C       .text disappear_stair__10daLStair_cFv */
void daLStair_c::disappear_stair() {
    /* Nonmatching */
}

/* 0000103C-000010D4       .text set_on_se__10daLStair_cFv */
void daLStair_c::set_on_se() {
    /* Nonmatching */
}

/* 000010D4-00001144       .text set_off_se__10daLStair_cFv */
void daLStair_c::set_off_se() {
    /* Nonmatching */
}

/* 00001144-00001164       .text daLStair_Create__FPv */
static cPhs_State daLStair_Create(void* i_this) {
    return ((daLStair_c*)i_this)->_create();
}

/* 00001164-00001188       .text daLStair_Delete__FPv */
static BOOL daLStair_Delete(void* i_this) {
    return ((daLStair_c*)i_this)->_delete();
}

/* 00001188-0000128C       .text daLStair_Draw__FPv */
static BOOL daLStair_Draw(void*) {
    /* Nonmatching */
}

/* 0000128C-000012B0       .text daLStair_Execute__FPv */
static BOOL daLStair_Execute(void* i_this) {
    return ((daLStair_c*)i_this)->_execute();
}

/* 000012B0-000012B8       .text daLStair_IsDelete__FPv */
static BOOL daLStair_IsDelete(void*) {
    return TRUE;
}

static actor_method_class daLStairMethodTable = {
    (process_method_func)daLStair_Create,
    (process_method_func)daLStair_Delete,
    (process_method_func)daLStair_Execute,
    (process_method_func)daLStair_IsDelete,
    (process_method_func)daLStair_Draw,
};

actor_process_profile_definition g_profile_LIGHTSTAIR = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_LIGHTSTAIR,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daLStair_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_LIGHTSTAIR,
    /* Actor SubMtd */ &daLStairMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
