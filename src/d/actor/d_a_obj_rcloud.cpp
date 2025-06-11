/**
 * d_a_obj_rcloud.cpp
 * Object - Dragon Roost Island - Clouds near Valoo
 */

#include "d/actor/d_a_obj_rcloud.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 00000078-000000E8       .text init_mtx__13daObjRcloud_cFv */
void daObjRcloud_c::init_mtx() {
    /* Nonmatching */
}

/* 000000E8-0000010C       .text solidHeapCB__13daObjRcloud_cFP10fopAc_ac_c */
void daObjRcloud_c::solidHeapCB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 0000010C-00000238       .text create_heap__13daObjRcloud_cFv */
void daObjRcloud_c::create_heap() {
    /* Nonmatching */
}

/* 00000238-000003B4       .text _create__13daObjRcloud_cFv */
cPhs_State daObjRcloud_c::_create() {
    /* Nonmatching */
}

/* 00000458-00000494       .text _delete__13daObjRcloud_cFv */
bool daObjRcloud_c::_delete() {
    /* Nonmatching */
}

/* 00000494-00000500       .text wait_act_proc__13daObjRcloud_cFv */
void daObjRcloud_c::wait_act_proc() {
    /* Nonmatching */
}

/* 00000500-00000568       .text clouds_lift_start_wait_act_proc__13daObjRcloud_cFv */
void daObjRcloud_c::clouds_lift_start_wait_act_proc() {
    /* Nonmatching */
}

/* 00000568-000005DC       .text clouds_lift_act_proc__13daObjRcloud_cFv */
void daObjRcloud_c::clouds_lift_act_proc() {
    /* Nonmatching */
}

/* 000005DC-00000678       .text setup_action__13daObjRcloud_cFi */
void daObjRcloud_c::setup_action(int) {
    /* Nonmatching */
}

/* 00000678-000006BC       .text _execute__13daObjRcloud_cFv */
bool daObjRcloud_c::_execute() {
    /* Nonmatching */
}

/* 000006BC-00000778       .text setTexMtx__13daObjRcloud_cFv */
void daObjRcloud_c::setTexMtx() {
    /* Nonmatching */
}

/* 00000778-00000848       .text _draw__13daObjRcloud_cFv */
bool daObjRcloud_c::_draw() {
    /* Nonmatching */
}

/* 00000848-00000868       .text daObjRcloud_Create__FP10fopAc_ac_c */
static cPhs_State daObjRcloud_Create(fopAc_ac_c* i_this) {
    return ((daObjRcloud_c*)i_this)->_create();
}

/* 00000868-0000088C       .text daObjRcloud_Delete__FP13daObjRcloud_c */
static BOOL daObjRcloud_Delete(daObjRcloud_c* i_this) {
    return ((daObjRcloud_c*)i_this)->_delete();
}

/* 0000088C-000008B0       .text daObjRcloud_Execute__FP13daObjRcloud_c */
static BOOL daObjRcloud_Execute(daObjRcloud_c* i_this) {
    return ((daObjRcloud_c*)i_this)->_execute();
}

/* 000008B0-000008D4       .text daObjRcloud_Draw__FP13daObjRcloud_c */
static BOOL daObjRcloud_Draw(daObjRcloud_c* i_this) {
    return ((daObjRcloud_c*)i_this)->_draw();
}

/* 000008D4-000008DC       .text daObjRcloud_IsDelete__FP13daObjRcloud_c */
static BOOL daObjRcloud_IsDelete(daObjRcloud_c*) {
    return TRUE;
}

static actor_method_class l_daObjRcloud_Method = {
    (process_method_func)daObjRcloud_Create,
    (process_method_func)daObjRcloud_Delete,
    (process_method_func)daObjRcloud_Execute,
    (process_method_func)daObjRcloud_IsDelete,
    (process_method_func)daObjRcloud_Draw,
};

actor_process_profile_definition g_profile_Obj_Rcloud = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Rcloud,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjRcloud_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Rcloud,
    /* Actor SubMtd */ &l_daObjRcloud_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
