//
// Generated by dtk
// Translation Unit: d_a_atdoor.cpp
//

#include "d/actor/d_a_atdoor.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 00000078-00000084       .text getSwbit__10daAtdoor_cFv */
void daAtdoor_c::getSwbit() {
    /* Nonmatching */
}

/* 00000084-000000A4       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000000A4-000001E8       .text CreateHeap__10daAtdoor_cFv */
void daAtdoor_c::CreateHeap() {
    /* Nonmatching */
}

/* 000001E8-00000258       .text calcMtx__10daAtdoor_cFv */
void daAtdoor_c::calcMtx() {
    /* Nonmatching */
}

/* 00000258-0000036C       .text CreateInit__10daAtdoor_cFv */
void daAtdoor_c::CreateInit() {
    /* Nonmatching */
}

/* 0000036C-00000418       .text create__10daAtdoor_cFv */
cPhs_State daAtdoor_c::create() {
    /* Nonmatching */
}

/* 00000418-00000420       .text daAtdoor_actionWait__FP10daAtdoor_c */
void daAtdoor_actionWait(daAtdoor_c*) {
    /* Nonmatching */
}

/* 00000420-000004CC       .text daAtdoor_actionCloseWait__FP10daAtdoor_c */
void daAtdoor_actionCloseWait(daAtdoor_c*) {
    /* Nonmatching */
}

/* 000004CC-00000530       .text daAtdoor_actionClose__FP10daAtdoor_c */
void daAtdoor_actionClose(daAtdoor_c*) {
    /* Nonmatching */
}

/* 00000530-00000594       .text daAtdoor_actionOpenWait__FP10daAtdoor_c */
void daAtdoor_actionOpenWait(daAtdoor_c*) {
    /* Nonmatching */
}

/* 00000594-000005F8       .text daAtdoor_actionOpen__FP10daAtdoor_c */
void daAtdoor_actionOpen(daAtdoor_c*) {
    /* Nonmatching */
}

/* 000005F8-00000658       .text daAtdoor_Draw__FP10daAtdoor_c */
static BOOL daAtdoor_Draw(daAtdoor_c*) {
    /* Nonmatching */
}

/* 00000658-00000694       .text daAtdoor_Execute__FP10daAtdoor_c */
static BOOL daAtdoor_Execute(daAtdoor_c*) {
    /* Nonmatching */
}

/* 00000694-0000069C       .text daAtdoor_IsDelete__FP10daAtdoor_c */
static BOOL daAtdoor_IsDelete(daAtdoor_c*) {
    return TRUE;
}

/* 0000069C-0000070C       .text daAtdoor_Delete__FP10daAtdoor_c */
static BOOL daAtdoor_Delete(daAtdoor_c*) {
    /* Nonmatching */
}

/* 0000070C-0000072C       .text daAtdoor_Create__FP10fopAc_ac_c */
static cPhs_State daAtdoor_Create(fopAc_ac_c* i_this) {
    return ((daAtdoor_c*)i_this)->create();
}

static actor_method_class l_daAtdoor_Method = {
    (process_method_func)daAtdoor_Create,
    (process_method_func)daAtdoor_Delete,
    (process_method_func)daAtdoor_Execute,
    (process_method_func)daAtdoor_IsDelete,
    (process_method_func)daAtdoor_Draw,
};

actor_process_profile_definition g_profile_ATDOOR = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_ATDOOR,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daAtdoor_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_ATDOOR,
    /* Actor SubMtd */ &l_daAtdoor_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_6_e,
};
