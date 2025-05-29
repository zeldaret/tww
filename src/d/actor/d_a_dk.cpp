/**
 * d_a_dk.cpp
 * NPC - Helmaroc King (Forsaken Fortress 1 tower, Outset Island)
 */

#include "d/actor/d_a_dk.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 000000EC-00000130       .text __ct__10daDk_HIO_cFv */
daDk_HIO_c::daDk_HIO_c() {
    /* Nonmatching */
}

/* 00000130-000001EC       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000228-00000720       .text tail_control__FP8dk_classP6tail_s */
void tail_control(dk_class*, tail_s*) {
    /* Nonmatching */
}

/* 00000720-00000820       .text tail_draw__FP8dk_classP6tail_s */
void tail_draw(dk_class*, tail_s*) {
    /* Nonmatching */
}

/* 00000820-00000938       .text kamen_draw__FP8dk_class */
void kamen_draw(dk_class*) {
    /* Nonmatching */
}

/* 00000938-00000A18       .text daDk_Draw__FP8dk_class */
static BOOL daDk_Draw(dk_class*) {
    /* Nonmatching */
}

/* 00000A18-00000A1C       .text move__FP8dk_class */
void move(dk_class*) {
    /* Nonmatching */
}

/* 00000A1C-00000A20       .text daDk_demoProc__FP8dk_class */
void daDk_demoProc(dk_class*) {
    /* Nonmatching */
}

/* 00000A20-00000A60       .text daDk_delete_Bdk__Fv */
void daDk_delete_Bdk() {
    /* Nonmatching */
}

/* 00000A60-00000D08       .text daDk_Execute__FP8dk_class */
static BOOL daDk_Execute(dk_class*) {
    /* Nonmatching */
}

/* 00000D08-00000D10       .text daDk_IsDelete__FP8dk_class */
static BOOL daDk_IsDelete(dk_class*) {
    /* Nonmatching */
}

/* 00000D10-00000D7C       .text daDk_Delete__FP8dk_class */
static BOOL daDk_Delete(dk_class*) {
    /* Nonmatching */
}

/* 00000D7C-00000FFC       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000FFC-000011EC       .text daDk_Create__FP10fopAc_ac_c */
static cPhs_State daDk_Create(fopAc_ac_c*) {
    /* Nonmatching */
}

static actor_method_class l_daDk_Method = {
    (process_method_func)daDk_Create,
    (process_method_func)daDk_Delete,
    (process_method_func)daDk_Execute,
    (process_method_func)daDk_IsDelete,
    (process_method_func)daDk_Draw,
};

actor_process_profile_definition g_profile_DK = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_DK,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(dk_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_DK,
    /* Actor SubMtd */ &l_daDk_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
