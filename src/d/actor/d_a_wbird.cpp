//
// Generated by dtk
// Translation Unit: d_a_wbird.cpp
//

#include "d/actor/d_a_wbird.h"
#include "d/d_procname.h"

/* 00000078-000000AC       .text calcMtx__9daWbird_cFv */
void daWbird_c::calcMtx() {
    /* Nonmatching */
}

/* 000000AC-00000324       .text setStartPos__9daWbird_cFv */
void daWbird_c::setStartPos() {
    /* Nonmatching */
}

/* 00000324-00000388       .text CreateInit__9daWbird_cFv */
void daWbird_c::CreateInit() {
    /* Nonmatching */
}

/* 00000388-000003E0       .text create__9daWbird_cFv */
s32 daWbird_c::create() {
    /* Nonmatching */
}

/* 000003E0-000003E4       .text actionWait__9daWbird_cFv */
void daWbird_c::actionWait() {
    /* Nonmatching */
}

/* 000003E4-00000474       .text actionEnd__9daWbird_cFv */
void daWbird_c::actionEnd() {
    /* Nonmatching */
}

/* 00000474-000005DC       .text actionMove__9daWbird_cFv */
void daWbird_c::actionMove() {
    /* Nonmatching */
}

/* 000005DC-00000850       .text actionSelect__9daWbird_cFv */
void daWbird_c::actionSelect() {
    /* Nonmatching */
}

/* 00000850-00000858       .text daWbird_Draw__FP9daWbird_c */
static BOOL daWbird_Draw(daWbird_c*) {
    /* Nonmatching */
}

/* 00000858-000008D0       .text daWbird_Execute__FP9daWbird_c */
static BOOL daWbird_Execute(daWbird_c*) {
    /* Nonmatching */
}

/* 000008D0-000008D8       .text daWbird_IsDelete__FP9daWbird_c */
static BOOL daWbird_IsDelete(daWbird_c*) {
    /* Nonmatching */
}

/* 000008D8-00000908       .text daWbird_Delete__FP9daWbird_c */
static BOOL daWbird_Delete(daWbird_c*) {
    /* Nonmatching */
}

/* 00000908-00000928       .text daWbird_Create__FP10fopAc_ac_c */
static s32 daWbird_Create(fopAc_ac_c*) {
    /* Nonmatching */
}

static actor_method_class l_daWbird_Method = {
    (process_method_func)daWbird_Create,
    (process_method_func)daWbird_Delete,
    (process_method_func)daWbird_Execute,
    (process_method_func)daWbird_IsDelete,
    (process_method_func)daWbird_Draw,
};

actor_process_profile_definition g_profile_WBIRD = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_WBIRD,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daWbird_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x00B7,
    /* Actor SubMtd */ &l_daWbird_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_6_e,
};
