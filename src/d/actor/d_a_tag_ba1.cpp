//
// Generated by dtk
// Translation Unit: d_a_tag_ba1.cpp
//

#include "d/actor/d_a_tag_ba1.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 000000EC-00000144       .text __ct__15daTag_Ba1_HIO_cFv */
daTag_Ba1_HIO_c::daTag_Ba1_HIO_c() {
    /* Nonmatching */
}

/* 00000144-00000164       .text daTag_Ba1_XyCheck_cB__FPvi */
void daTag_Ba1_XyCheck_cB(void*, int) {
    /* Nonmatching */
}

/* 00000164-00000184       .text XyCheck_cB__11daTag_Ba1_cFi */
void daTag_Ba1_c::XyCheck_cB(int) {
    /* Nonmatching */
}

/* 00000184-000001A4       .text daTag_Ba1_XyEvent_cB__FPvi */
void daTag_Ba1_XyEvent_cB(void*, int) {
    /* Nonmatching */
}

/* 000001A4-000001C0       .text XyEvent_cB__11daTag_Ba1_cFi */
void daTag_Ba1_c::XyEvent_cB(int) {
    /* Nonmatching */
}

/* 000001C0-00000288       .text createInit__11daTag_Ba1_cFv */
void daTag_Ba1_c::createInit() {
    /* Nonmatching */
}

/* 00000288-00000290       .text _draw__11daTag_Ba1_cFv */
BOOL daTag_Ba1_c::_draw() {
    /* Nonmatching */
}

/* 00000290-00000340       .text _execute__11daTag_Ba1_cFv */
BOOL daTag_Ba1_c::_execute() {
    /* Nonmatching */
}

/* 00000340-00000394       .text _delete__11daTag_Ba1_cFv */
BOOL daTag_Ba1_c::_delete() {
    /* Nonmatching */
}

/* 00000394-00000454       .text _create__11daTag_Ba1_cFv */
cPhs_State daTag_Ba1_c::_create() {
    /* Nonmatching */
}

/* 00000454-00000474       .text daTag_Ba1_Create__FP10fopAc_ac_c */
static cPhs_State daTag_Ba1_Create(fopAc_ac_c* i_this) {
    return ((daTag_Ba1_c*)i_this)->_create();
}

/* 00000474-00000494       .text daTag_Ba1_Delete__FP11daTag_Ba1_c */
static BOOL daTag_Ba1_Delete(daTag_Ba1_c* i_this) {
    return ((daTag_Ba1_c*)i_this)->_delete();
}

/* 00000494-000004B4       .text daTag_Ba1_Execute__FP11daTag_Ba1_c */
static BOOL daTag_Ba1_Execute(daTag_Ba1_c* i_this) {
    return ((daTag_Ba1_c*)i_this)->_execute();
}

/* 000004B4-000004D4       .text daTag_Ba1_Draw__FP11daTag_Ba1_c */
static BOOL daTag_Ba1_Draw(daTag_Ba1_c* i_this) {
    return ((daTag_Ba1_c*)i_this)->_draw();
}

/* 000004D4-000004DC       .text daTag_Ba1_IsDelete__FP11daTag_Ba1_c */
static BOOL daTag_Ba1_IsDelete(daTag_Ba1_c*) {
    return TRUE;
}

static actor_method_class l_daTag_Ba1_Method = {
    (process_method_func)daTag_Ba1_Create,
    (process_method_func)daTag_Ba1_Delete,
    (process_method_func)daTag_Ba1_Execute,
    (process_method_func)daTag_Ba1_IsDelete,
    (process_method_func)daTag_Ba1_Draw,
};

actor_process_profile_definition g_profile_TAG_BA1 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_TAG_BA1,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daTag_Ba1_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_TAG_BA1,
    /* Actor SubMtd */ &l_daTag_Ba1_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
