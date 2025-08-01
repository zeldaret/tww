//
// Generated by dtk
// Translation Unit: d_a_ykgr.cpp
//

#include "d/actor/d_a_ykgr.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 000000EC-00000134       .text draw__17dPa_YkgrPcallBackFP14JPABaseEmitterP15JPABaseParticle */
void dPa_YkgrPcallBack::draw(JPABaseEmitter*, JPABaseParticle*) {
    /* Nonmatching */
}

/* 00000134-00000234       .text setParam__17dPa_YkgrPcallBackFf */
void dPa_YkgrPcallBack::setParam(float) {
    /* Nonmatching */
}

/* 00000234-00000408       .text getPosRate__8daYkgr_cFv */
void daYkgr_c::getPosRate() {
    /* Nonmatching */
}

/* 00000408-00000428       .text daYkgrCreate__FPv */
static cPhs_State daYkgrCreate(void* i_this) {
    return ((daYkgr_c*)i_this)->_create();
}

/* 00000428-00000680       .text _create__8daYkgr_cFv */
cPhs_State daYkgr_c::_create() {
    /* Nonmatching */
}

/* 00000680-00000688       .text daYkgrDelete__FPv */
static BOOL daYkgrDelete(void*) {
    return TRUE;
}

/* 00000688-000007F4       .text daYkgrExecute__FPv */
static BOOL daYkgrExecute(void*) {
    /* Nonmatching */
}

/* 000007F4-000008F4       .text daYkgrDraw__FPv */
static BOOL daYkgrDraw(void*) {
    /* Nonmatching */
}

/* 000008F4-000008FC       .text daYkgrIsDelete__FPv */
static BOOL daYkgrIsDelete(void*) {
    return TRUE;
}

static actor_method_class daYkgrMethodTable = {
    (process_method_func)daYkgrCreate,
    (process_method_func)daYkgrDelete,
    (process_method_func)daYkgrExecute,
    (process_method_func)daYkgrIsDelete,
    (process_method_func)daYkgrDraw,
};

actor_process_profile_definition g_profile_Ykgr = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Ykgr,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daYkgr_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Ykgr,
    /* Actor SubMtd */ &daYkgrMethodTable,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
