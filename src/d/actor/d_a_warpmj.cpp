//
// Generated by dtk
// Translation Unit: d_a_warpmj.cpp
//

#include "d/actor/d_a_warpmj.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 00000078-000000A8       .text _delete__10daWarpmj_cFv */
bool daWarpmj_c::_delete() {
    /* Nonmatching */
}

/* 000000A8-000000C8       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000000C8-00000454       .text CreateHeap__10daWarpmj_cFv */
void daWarpmj_c::CreateHeap() {
    /* Nonmatching */
}

/* 0000049C-00000630       .text CreateInit__10daWarpmj_cFv */
void daWarpmj_c::CreateInit() {
    /* Nonmatching */
}

/* 00000630-00000778       .text _create__10daWarpmj_cFv */
cPhs_State daWarpmj_c::_create() {
    /* Nonmatching */
}

/* 00000778-0000084C       .text set_mtx__10daWarpmj_cFv */
void daWarpmj_c::set_mtx() {
    /* Nonmatching */
}

/* 0000084C-00000990       .text _execute__10daWarpmj_cFv */
bool daWarpmj_c::_execute() {
    /* Nonmatching */
}

/* 00000990-000009D4       .text normal_execute__10daWarpmj_cFv */
void daWarpmj_c::normal_execute() {
    /* Nonmatching */
}

/* 000009D4-00000A60       .text demo_execute__10daWarpmj_cFv */
void daWarpmj_c::demo_execute() {
    /* Nonmatching */
}

/* 00000A60-00000B7C       .text demo_proc__10daWarpmj_cFv */
void daWarpmj_c::demo_proc() {
    /* Nonmatching */
}

/* 00000B7C-00000B80       .text initWait__10daWarpmj_cFi */
void daWarpmj_c::initWait(int) {
    /* Nonmatching */
}

/* 00000B80-00000BA4       .text actWait__10daWarpmj_cFi */
void daWarpmj_c::actWait(int) {
    /* Nonmatching */
}

/* 00000BA4-00000C14       .text initWarp__10daWarpmj_cFi */
void daWarpmj_c::initWarp(int) {
    /* Nonmatching */
}

/* 00000C14-00000C38       .text actWarp__10daWarpmj_cFi */
void daWarpmj_c::actWarp(int) {
    /* Nonmatching */
}

/* 00000C38-00000C94       .text initWarpArrive__10daWarpmj_cFi */
void daWarpmj_c::initWarpArrive(int) {
    /* Nonmatching */
}

/* 00000C94-00000CB8       .text actWarpArrive__10daWarpmj_cFi */
void daWarpmj_c::actWarpArrive(int) {
    /* Nonmatching */
}

/* 00000CB8-00000D14       .text eventOrder__10daWarpmj_cFv */
void daWarpmj_c::eventOrder() {
    /* Nonmatching */
}

/* 00000D14-00000DD0       .text checkOrder__10daWarpmj_cFv */
void daWarpmj_c::checkOrder() {
    /* Nonmatching */
}

/* 00000DD0-00000E10       .text animPlay__10daWarpmj_cFv */
void daWarpmj_c::animPlay() {
    /* Nonmatching */
}

/* 00000E10-00000E8C       .text setEndAnm__10daWarpmj_cFv */
void daWarpmj_c::setEndAnm() {
    /* Nonmatching */
}

/* 00000E8C-00000EE0       .text getSeaY__10daWarpmj_cF4cXyz */
void daWarpmj_c::getSeaY(cXyz) {
    /* Nonmatching */
}

/* 00000EE0-00000FDC       .text check_warp__10daWarpmj_cFv */
void daWarpmj_c::check_warp() {
    /* Nonmatching */
}

/* 00000FDC-0000114C       .text _draw__10daWarpmj_cFv */
bool daWarpmj_c::_draw() {
    /* Nonmatching */
}

/* 0000114C-0000116C       .text daWarpmj_Create__FPv */
static cPhs_State daWarpmj_Create(void* i_this) {
    return ((daWarpmj_c*)i_this)->_create();
}

/* 0000116C-00001190       .text daWarpmj_Delete__FPv */
static BOOL daWarpmj_Delete(void* i_this) {
    return ((daWarpmj_c*)i_this)->_delete();
}

/* 00001190-000011B4       .text daWarpmj_Draw__FPv */
static BOOL daWarpmj_Draw(void* i_this) {
    return ((daWarpmj_c*)i_this)->_draw();
}

/* 000011B4-000011D8       .text daWarpmj_Execute__FPv */
static BOOL daWarpmj_Execute(void* i_this) {
    return ((daWarpmj_c*)i_this)->_execute();
}

/* 000011D8-000011E0       .text daWarpmj_IsDelete__FPv */
static BOOL daWarpmj_IsDelete(void*) {
    return TRUE;
}

static actor_method_class daWarpmjMethodTable = {
    (process_method_func)daWarpmj_Create,
    (process_method_func)daWarpmj_Delete,
    (process_method_func)daWarpmj_Execute,
    (process_method_func)daWarpmj_IsDelete,
    (process_method_func)daWarpmj_Draw,
};

actor_process_profile_definition g_profile_WARPMAJYUU = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_WARPMAJYUU,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daWarpmj_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_WARPMAJYUU,
    /* Actor SubMtd */ &daWarpmjMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
