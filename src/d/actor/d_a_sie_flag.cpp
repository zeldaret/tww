//
// Generated by dtk
// Translation Unit: d_a_sie_flag.cpp
//

#include "d/actor/d_a_sie_flag.h"
#include "d/d_procname.h"

/* 000000EC-00000118       .text __ct__16daSie_Flag_HIO_cFv */
daSie_Flag_HIO_c::daSie_Flag_HIO_c() {
    /* Nonmatching */
}

/* 00000118-000001C4       .text set_mtx__12daSie_Flag_cFv */
void daSie_Flag_c::set_mtx() {
    /* Nonmatching */
}

/* 000001C4-000001E4       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000001E4-0000030C       .text CreateHeap__12daSie_Flag_cFv */
void daSie_Flag_c::CreateHeap() {
    /* Nonmatching */
}

/* 0000030C-000003D4       .text CreateInit__12daSie_Flag_cFv */
void daSie_Flag_c::CreateInit() {
    /* Nonmatching */
}

/* 000003D4-00000488       .text _create__12daSie_Flag_cFv */
cPhs_State daSie_Flag_c::_create() {
    /* Nonmatching */
}

/* 00000814-00000864       .text _delete__12daSie_Flag_cFv */
bool daSie_Flag_c::_delete() {
    /* Nonmatching */
}

/* 00000864-00000B08       .text _execute__12daSie_Flag_cFv */
bool daSie_Flag_c::_execute() {
    /* Nonmatching */
}

/* 00000B08-00000B94       .text _draw__12daSie_Flag_cFv */
bool daSie_Flag_c::_draw() {
    /* Nonmatching */
}

/* 00000B94-00000BB4       .text daSie_FlagCreate__FPv */
static s32 daSie_FlagCreate(void*) {
    /* Nonmatching */
}

/* 00000BB4-00000BD8       .text daSie_FlagDelete__FPv */
static BOOL daSie_FlagDelete(void*) {
    /* Nonmatching */
}

/* 00000BD8-00000BFC       .text daSie_FlagExecute__FPv */
static BOOL daSie_FlagExecute(void*) {
    /* Nonmatching */
}

/* 00000BFC-00000C20       .text daSie_FlagDraw__FPv */
static BOOL daSie_FlagDraw(void*) {
    /* Nonmatching */
}

/* 00000C20-00000C28       .text daSie_FlagIsDelete__FPv */
static BOOL daSie_FlagIsDelete(void*) {
    /* Nonmatching */
}

static actor_method_class daSie_FlagMethodTable = {
    (process_method_func)daSie_FlagCreate,
    (process_method_func)daSie_FlagDelete,
    (process_method_func)daSie_FlagExecute,
    (process_method_func)daSie_FlagIsDelete,
    (process_method_func)daSie_FlagDraw,
};

actor_process_profile_definition g_profile_Sie_Flag = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Sie_Flag,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daSie_Flag_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x006D,
    /* Actor SubMtd */ &daSie_FlagMethodTable,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e | fopAcStts_UNK200000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
