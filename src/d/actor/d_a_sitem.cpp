//
// Generated by dtk
// Translation Unit: d_a_sitem.cpp
//

#include "d/actor/d_a_sitem.h"
#include "d/d_procname.h"

/* 000000EC-000001FC       .text hand_draw__FP11sitem_class */
void hand_draw(sitem_class*) {
    /* Nonmatching */
}

/* 000001FC-00000248       .text daSitem_Draw__FP11sitem_class */
static BOOL daSitem_Draw(sitem_class*) {
    /* Nonmatching */
}

/* 00000248-0000034C       .text hand_mtx_set__FP11sitem_class */
void hand_mtx_set(sitem_class*) {
    /* Nonmatching */
}

/* 00000388-00000410       .text control3__FP11sitem_class */
void control3(sitem_class*) {
    /* Nonmatching */
}

/* 00000410-00000748       .text control1__FP11sitem_class */
void control1(sitem_class*) {
    /* Nonmatching */
}

/* 00000748-000009E8       .text control2__FP11sitem_class */
void control2(sitem_class*) {
    /* Nonmatching */
}

/* 000009E8-00000E2C       .text cut_control1__FP11sitem_class */
void cut_control1(sitem_class*) {
    /* Nonmatching */
}

/* 00000E2C-00001058       .text my_break__FP11sitem_class */
void my_break(sitem_class*) {
    /* Nonmatching */
}

/* 00001094-000015C0       .text cut_control2__FP11sitem_class */
void cut_control2(sitem_class*) {
    /* Nonmatching */
}

/* 000015C0-00002304       .text hand_move__FP11sitem_class */
void hand_move(sitem_class*) {
    /* Nonmatching */
}

/* 00002684-000026F4       .text daSitem_Execute__FP11sitem_class */
static BOOL daSitem_Execute(sitem_class*) {
    /* Nonmatching */
}

/* 000026F4-000026FC       .text daSitem_IsDelete__FP11sitem_class */
static BOOL daSitem_IsDelete(sitem_class*) {
    /* Nonmatching */
}

/* 000026FC-00002760       .text daSitem_Delete__FP11sitem_class */
static BOOL daSitem_Delete(sitem_class*) {
    /* Nonmatching */
}

/* 00002760-00002824       .text useHeapInit__FP11sitem_class */
void useHeapInit(sitem_class*) {
    /* Nonmatching */
}

/* 00002824-00002844       .text daSitem_solidHeapCB__FP10fopAc_ac_c */
static BOOL daSitem_solidHeapCB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00002844-00002C04       .text daSitem_Create__FP10fopAc_ac_c */
static s32 daSitem_Create(fopAc_ac_c*) {
    /* Nonmatching */
}

static actor_method_class l_daSitem_Method = {
    (process_method_func)daSitem_Create,
    (process_method_func)daSitem_Delete,
    (process_method_func)daSitem_Execute,
    (process_method_func)daSitem_IsDelete,
    (process_method_func)daSitem_Draw,
};

actor_process_profile_definition g_profile_SITEM = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_SITEM,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(sitem_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x00F3,
    /* Actor SubMtd */ &l_daSitem_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
