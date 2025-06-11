/**
 * d_a_mdoor.cpp
 * Object - Wooden/Metal bars (Forbidden Woods, Cabana Maze, Dragon Roost Cavern, Earth Temple, etc.)
 */

#include "d/actor/d_a_mdoor.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 00000078-00000084       .text getSwbit__9daMdoor_cFv */
void daMdoor_c::getSwbit() {
    /* Nonmatching */
}

/* 00000084-00000090       .text getType__9daMdoor_cFv */
void daMdoor_c::getType() {
    /* Nonmatching */
}

/* 00000090-0000009C       .text getToolId__9daMdoor_cFv */
void daMdoor_c::getToolId() {
    /* Nonmatching */
}

/* 0000009C-000000A8       .text getShapeType__9daMdoor_cFv */
void daMdoor_c::getShapeType() {
    /* Nonmatching */
}

/* 000000A8-000000C8       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000000C8-00000230       .text CreateHeap__9daMdoor_cFv */
void daMdoor_c::CreateHeap() {
    /* Nonmatching */
}

/* 00000230-0000029C       .text calcMtx__9daMdoor_cFv */
void daMdoor_c::calcMtx() {
    /* Nonmatching */
}

/* 0000029C-00000344       .text smokeInit__9daMdoor_cFv */
void daMdoor_c::smokeInit() {
    /* Nonmatching */
}

/* 00000344-00000370       .text smokeEnd__9daMdoor_cFv */
void daMdoor_c::smokeEnd() {
    /* Nonmatching */
}

/* 00000370-000005E0       .text CreateInit__9daMdoor_cFv */
void daMdoor_c::CreateInit() {
    /* Nonmatching */
}

/* 000005E0-00000698       .text create__9daMdoor_cFv */
cPhs_State daMdoor_c::create() {
    /* Nonmatching */
}

/* 00000698-00000958       .text demoProc__9daMdoor_cFv */
void daMdoor_c::demoProc() {
    /* Nonmatching */
}

/* 00000958-00000960       .text daMdoor_actionWait__FP9daMdoor_c */
void daMdoor_actionWait(daMdoor_c*) {
    /* Nonmatching */
}

/* 00000960-000009E8       .text daMdoor_actionDemoWait__FP9daMdoor_c */
void daMdoor_actionDemoWait(daMdoor_c*) {
    /* Nonmatching */
}

/* 000009E8-00000A4C       .text daMdoor_actionDemo__FP9daMdoor_c */
void daMdoor_actionDemo(daMdoor_c*) {
    /* Nonmatching */
}

/* 00000A4C-00000AF4       .text daMdoor_actionGenocide__FP9daMdoor_c */
void daMdoor_actionGenocide(daMdoor_c*) {
    /* Nonmatching */
}

/* 00000AF4-00000C6C       .text daMdoor_actionOpen__FP9daMdoor_c */
void daMdoor_actionOpen(daMdoor_c*) {
    /* Nonmatching */
}

/* 00000C6C-00000CE8       .text daMdoor_actionSwitch__FP9daMdoor_c */
void daMdoor_actionSwitch(daMdoor_c*) {
    /* Nonmatching */
}

/* 00000CE8-00000DD0       .text daMdoor_actionReady__FP9daMdoor_c */
void daMdoor_actionReady(daMdoor_c*) {
    /* Nonmatching */
}

/* 00000DD0-00000E60       .text daMdoor_actionReadyOpen__FP9daMdoor_c */
void daMdoor_actionReadyOpen(daMdoor_c*) {
    /* Nonmatching */
}

/* 00000E60-00000ED4       .text daMdoor_actionEvent__FP9daMdoor_c */
void daMdoor_actionEvent(daMdoor_c*) {
    /* Nonmatching */
}

/* 00000ED4-00000F34       .text daMdoor_Draw__FP9daMdoor_c */
static BOOL daMdoor_Draw(daMdoor_c*) {
    /* Nonmatching */
}

/* 00000F34-00000F84       .text daMdoor_Execute__FP9daMdoor_c */
static BOOL daMdoor_Execute(daMdoor_c*) {
    /* Nonmatching */
}

/* 00000F84-00000F8C       .text daMdoor_IsDelete__FP9daMdoor_c */
static BOOL daMdoor_IsDelete(daMdoor_c*) {
    return TRUE;
}

/* 00000F8C-00001054       .text daMdoor_Delete__FP9daMdoor_c */
static BOOL daMdoor_Delete(daMdoor_c*) {
    /* Nonmatching */
}

/* 00001054-00001074       .text daMdoor_Create__FP10fopAc_ac_c */
static cPhs_State daMdoor_Create(fopAc_ac_c* i_this) {
    return ((daMdoor_c*)i_this)->create();
}

static actor_method_class l_daMdoor_Method = {
    (process_method_func)daMdoor_Create,
    (process_method_func)daMdoor_Delete,
    (process_method_func)daMdoor_Execute,
    (process_method_func)daMdoor_IsDelete,
    (process_method_func)daMdoor_Draw,
};

actor_process_profile_definition g_profile_MDOOR = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_MDOOR,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daMdoor_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_MDOOR,
    /* Actor SubMtd */ &l_daMdoor_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_6_e,
};
