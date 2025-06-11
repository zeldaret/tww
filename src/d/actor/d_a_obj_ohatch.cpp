/**
 * d_a_obj_ohatch.cpp
 * Object - Hatch door leading to the Nintendo Gallery
 */

#include "d/actor/d_a_obj_ohatch.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 00000078-0000018C       .text set_mtx__13daObjOhatch_cFv */
void daObjOhatch_c::set_mtx() {
    /* Nonmatching */
}

/* 0000018C-0000027C       .text init_mtx__13daObjOhatch_cFv */
void daObjOhatch_c::init_mtx() {
    /* Nonmatching */
}

/* 0000027C-000002A0       .text solidHeapCB__13daObjOhatch_cFP10fopAc_ac_c */
void daObjOhatch_c::solidHeapCB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000002A0-000003CC       .text create_heap__13daObjOhatch_cFv */
void daObjOhatch_c::create_heap() {
    /* Nonmatching */
}

/* 000003CC-00000548       .text _create__13daObjOhatch_cFv */
cPhs_State daObjOhatch_c::_create() {
    /* Nonmatching */
}

/* 00000548-00000628       .text _delete__13daObjOhatch_cFv */
bool daObjOhatch_c::_delete() {
    /* Nonmatching */
}

/* 00000628-00000810       .text close_wait_act_proc__13daObjOhatch_cFv */
void daObjOhatch_c::close_wait_act_proc() {
    /* Nonmatching */
}

/* 00000810-000008A4       .text tremor_act_proc__13daObjOhatch_cFv */
void daObjOhatch_c::tremor_act_proc() {
    /* Nonmatching */
}

/* 000008A4-00000A00       .text open_act_proc__13daObjOhatch_cFv */
void daObjOhatch_c::open_act_proc() {
    /* Nonmatching */
}

/* 00000A00-00000A4C       .text vibrate_act_proc__13daObjOhatch_cFv */
void daObjOhatch_c::vibrate_act_proc() {
    /* Nonmatching */
}

/* 00000A4C-00000A50       .text open_wait_act_proc__13daObjOhatch_cFv */
void daObjOhatch_c::open_wait_act_proc() {
    /* Nonmatching */
}

/* 00000A50-00000B04       .text _execute__13daObjOhatch_cFv */
bool daObjOhatch_c::_execute() {
    /* Nonmatching */
}

/* 00000B04-00000B64       .text _draw__13daObjOhatch_cFv */
bool daObjOhatch_c::_draw() {
    /* Nonmatching */
}

/* 00000B64-00000B84       .text daObjOhatch_Create__FP10fopAc_ac_c */
static cPhs_State daObjOhatch_Create(fopAc_ac_c* i_this) {
    return ((daObjOhatch_c*)i_this)->_create();
}

/* 00000B84-00000BA8       .text daObjOhatch_Delete__FP13daObjOhatch_c */
static BOOL daObjOhatch_Delete(daObjOhatch_c* i_this) {
    return ((daObjOhatch_c*)i_this)->_delete();
}

/* 00000BA8-00000BCC       .text daObjOhatch_Execute__FP13daObjOhatch_c */
static BOOL daObjOhatch_Execute(daObjOhatch_c* i_this) {
    return ((daObjOhatch_c*)i_this)->_execute();
}

/* 00000BCC-00000BF0       .text daObjOhatch_Draw__FP13daObjOhatch_c */
static BOOL daObjOhatch_Draw(daObjOhatch_c* i_this) {
    return ((daObjOhatch_c*)i_this)->_draw();
}

/* 00000BF0-00000BF8       .text daObjOhatch_IsDelete__FP13daObjOhatch_c */
static BOOL daObjOhatch_IsDelete(daObjOhatch_c*) {
    return TRUE;
}

static actor_method_class l_daObjOhatch_Method = {
    (process_method_func)daObjOhatch_Create,
    (process_method_func)daObjOhatch_Delete,
    (process_method_func)daObjOhatch_Execute,
    (process_method_func)daObjOhatch_IsDelete,
    (process_method_func)daObjOhatch_Draw,
};

actor_process_profile_definition g_profile_Obj_Ohatch = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Ohatch,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjOhatch_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Ohatch,
    /* Actor SubMtd */ &l_daObjOhatch_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e | fopAcStts_UNK200000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_5_e,
};
