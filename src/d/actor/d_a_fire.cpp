//
// Generated by dtk
// Translation Unit: d_a_fire.cpp
//

#include "d/actor/d_a_fire.h"
#include "d/d_procname.h"

/* 00000078-000000F8       .text _delete__8daFire_cFv */
bool daFire_c::_delete() {
    /* Nonmatching */
}

/* 000000F8-00000518       .text CreateInit__8daFire_cFv */
void daFire_c::CreateInit() {
    /* Nonmatching */
}

/* 00000518-00000758       .text _create__8daFire_cFv */
cPhs_State daFire_c::_create() {
    /* Nonmatching */
}

/* 000009F0-00000A70       .text _execute__8daFire_cFv */
bool daFire_c::_execute() {
    /* Nonmatching */
}

/* 00000A70-00000AD8       .text search_wind__8daFire_cFv */
void daFire_c::search_wind() {
    /* Nonmatching */
}

/* 00000AD8-00000E8C       .text ctrlEffect__8daFire_cFv */
void daFire_c::ctrlEffect() {
    /* Nonmatching */
}

/* 00000E8C-0000102C       .text demo_proc__8daFire_cFv */
void daFire_c::demo_proc() {
    /* Nonmatching */
}

/* 0000102C-00001030       .text normal_proc__8daFire_cFv */
void daFire_c::normal_proc() {
    /* Nonmatching */
}

/* 00001030-000011A8       .text eventOrder__8daFire_cFv */
void daFire_c::eventOrder() {
    /* Nonmatching */
}

/* 000011A8-000012AC       .text checkOrder__8daFire_cFv */
void daFire_c::checkOrder() {
    /* Nonmatching */
}

/* 000012AC-0000131C       .text execStopFire__8daFire_cFv */
void daFire_c::execStopFire() {
    /* Nonmatching */
}

/* 0000131C-00001398       .text execStopNowFire__8daFire_cFv */
void daFire_c::execStopNowFire() {
    /* Nonmatching */
}

/* 00001398-00001408       .text execPlayFire__8daFire_cFv */
void daFire_c::execPlayFire() {
    /* Nonmatching */
}

/* 00001408-000014E4       .text setDirParticle__8daFire_cFP4cXyz */
void daFire_c::setDirParticle(cXyz*) {
    /* Nonmatching */
}

/* 000014E4-000015A4       .text checkCol__8daFire_cFv */
void daFire_c::checkCol() {
    /* Nonmatching */
}

/* 000015A4-000015AC       .text _draw__8daFire_cFv */
bool daFire_c::_draw() {
    /* Nonmatching */
}

/* 000015AC-000015CC       .text daFire_Create__FPv */
static cPhs_State daFire_Create(void*) {
    /* Nonmatching */
}

/* 000015CC-000015F0       .text daFire_Delete__FPv */
static BOOL daFire_Delete(void*) {
    /* Nonmatching */
}

/* 000015F0-00001614       .text daFire_Draw__FPv */
static BOOL daFire_Draw(void*) {
    /* Nonmatching */
}

/* 00001614-00001638       .text daFire_Execute__FPv */
static BOOL daFire_Execute(void*) {
    /* Nonmatching */
}

/* 00001638-00001640       .text daFire_IsDelete__FPv */
static BOOL daFire_IsDelete(void*) {
    /* Nonmatching */
}

static actor_method_class daFireMethodTable = {
    (process_method_func)daFire_Create,
    (process_method_func)daFire_Delete,
    (process_method_func)daFire_Execute,
    (process_method_func)daFire_IsDelete,
    (process_method_func)daFire_Draw,
};

actor_process_profile_definition g_profile_Fire = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Fire,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daFire_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x0192,
    /* Actor SubMtd */ &daFireMethodTable,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
