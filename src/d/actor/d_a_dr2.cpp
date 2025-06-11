/**
 * d_a_dr2.cpp
 * NPC - Gohma fight - Valoo (body & tail) + lava pit & ceiling rock
 */

#include "d/actor/d_a_dr2.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 000000EC-00000110       .text __ct__11daDr2_HIO_cFv */
daDr2_HIO_c::daDr2_HIO_c() {
    /* Nonmatching */
}

/* 00000110-00000380       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000380-000003F4       .text hahen_draw__FP9dr2_class */
void hahen_draw(dr2_class*) {
    /* Nonmatching */
}

/* 000003F4-0000048C       .text iwa_draw__FP9dr2_class */
void iwa_draw(dr2_class*) {
    /* Nonmatching */
}

/* 0000048C-00000594       .text dr_draw__FP9dr2_class */
void dr_draw(dr2_class*) {
    /* Nonmatching */
}

/* 00000594-0000064C       .text yuka_draw__FP9dr2_class */
void yuka_draw(dr2_class*) {
    /* Nonmatching */
}

/* 0000064C-000006D4       .text daDr2_Draw__FP9dr2_class */
static BOOL daDr2_Draw(dr2_class*) {
    /* Nonmatching */
}

/* 000006D4-00000720       .text s_a_d_sub__FPvPv */
void s_a_d_sub(void*, void*) {
    /* Nonmatching */
}

/* 00000720-00000884       .text hahen_move__FP9dr2_class */
void hahen_move(dr2_class*) {
    /* Nonmatching */
}

/* 00000884-0000130C       .text iwa_move__FP9dr2_class */
void iwa_move(dr2_class*) {
    /* Nonmatching */
}

/* 0000130C-0000172C       .text move__FP9dr2_class */
void move(dr2_class*) {
    /* Nonmatching */
}

/* 0000172C-00001810       .text dr_move__FP9dr2_class */
void dr_move(dr2_class*) {
    /* Nonmatching */
}

/* 00001810-000019B8       .text yuka_move__FP9dr2_class */
void yuka_move(dr2_class*) {
    /* Nonmatching */
}

/* 000019B8-00001B90       .text daDr2_Execute__FP9dr2_class */
static BOOL daDr2_Execute(dr2_class*) {
    /* Nonmatching */
}

/* 00001B90-00001B98       .text daDr2_IsDelete__FP9dr2_class */
static BOOL daDr2_IsDelete(dr2_class*) {
    return TRUE;
}

/* 00001B98-00001C58       .text daDr2_Delete__FP9dr2_class */
static BOOL daDr2_Delete(dr2_class*) {
    /* Nonmatching */
}

/* 00001C58-00002458       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000024A0-00002668       .text daDr2_Create__FP10fopAc_ac_c */
static cPhs_State daDr2_Create(fopAc_ac_c*) {
    /* Nonmatching */
}

static actor_method_class l_daDr2_Method = {
    (process_method_func)daDr2_Create,
    (process_method_func)daDr2_Delete,
    (process_method_func)daDr2_Execute,
    (process_method_func)daDr2_IsDelete,
    (process_method_func)daDr2_Draw,
};

actor_process_profile_definition g_profile_DR2 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_DR2,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(dr2_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_DR2,
    /* Actor SubMtd */ &l_daDr2_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
