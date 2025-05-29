/**
 * d_a_sss.cpp
 * Enemy - Dexivine (Forbidden Woods, Wind Temple)
 */

#include "d/actor/d_a_sss.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 000000EC-000001F0       .text hand_draw__FP9sss_class */
void hand_draw(sss_class*) {
    /* Nonmatching */
}

/* 000001F0-00000248       .text daSss_Draw__FP9sss_class */
static BOOL daSss_Draw(sss_class*) {
    /* Nonmatching */
}

/* 00000248-000002C8       .text hand_close__FP9sss_class */
void hand_close(sss_class*) {
    /* Nonmatching */
}

/* 000002C8-00000348       .text hand_open__FP9sss_class */
void hand_open(sss_class*) {
    /* Nonmatching */
}

/* 00000348-00000444       .text hand_mtx_set__FP9sss_class */
void hand_mtx_set(sss_class*) {
    /* Nonmatching */
}

/* 00000444-000004CC       .text control3__FP9sss_class */
void control3(sss_class*) {
    /* Nonmatching */
}

/* 000004CC-00000804       .text control1__FP9sss_class */
void control1(sss_class*) {
    /* Nonmatching */
}

/* 00000840-00000B0C       .text control2__FP9sss_class */
void control2(sss_class*) {
    /* Nonmatching */
}

/* 00000B0C-00000F78       .text cut_control1__FP9sss_class */
void cut_control1(sss_class*) {
    /* Nonmatching */
}

/* 00000F78-000014F4       .text cut_control2__FP9sss_class */
void cut_control2(sss_class*) {
    /* Nonmatching */
}

/* 000014F4-00002614       .text hand_move__FP9sss_class */
void hand_move(sss_class*) {
    /* Nonmatching */
}

/* 00002614-00002618       .text hand_main__FP9sss_class */
void hand_main(sss_class*) {
    /* Nonmatching */
}

/* 00002618-0000269C       .text daSss_Execute__FP9sss_class */
static BOOL daSss_Execute(sss_class*) {
    /* Nonmatching */
}

/* 0000269C-000026A4       .text daSss_IsDelete__FP9sss_class */
static BOOL daSss_IsDelete(sss_class*) {
    /* Nonmatching */
}

/* 000026A4-00002720       .text daSss_Delete__FP9sss_class */
static BOOL daSss_Delete(sss_class*) {
    /* Nonmatching */
}

/* 00002720-000028A0       .text useHeapInit__FP9sss_class */
void useHeapInit(sss_class*) {
    /* Nonmatching */
}

/* 000028A0-000028C0       .text daSss_solidHeapCB__FP10fopAc_ac_c */
static BOOL daSss_solidHeapCB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000028C0-00002BB4       .text daSss_Create__FP10fopAc_ac_c */
static cPhs_State daSss_Create(fopAc_ac_c*) {
    /* Nonmatching */
}

static actor_method_class l_daSss_Method = {
    (process_method_func)daSss_Create,
    (process_method_func)daSss_Delete,
    (process_method_func)daSss_Execute,
    (process_method_func)daSss_IsDelete,
    (process_method_func)daSss_Draw,
};

actor_process_profile_definition g_profile_SSS = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_SSS,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(sss_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_SSS,
    /* Actor SubMtd */ &l_daSss_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
