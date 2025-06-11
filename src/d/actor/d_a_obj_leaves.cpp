/**
 * d_a_obj_leaves.cpp
 * Object - Pile of orange leaves (fades away when blown with Deku Leaf)
 */

#include "d/actor/d_a_obj_leaves.h"
#include "d/d_bg_w.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

class J3DMaterial;

/* 00000078-000000D8       .text chk_appear__13daObjLeaves_cFv */
void daObjLeaves_c::chk_appear() {
    /* Nonmatching */
}

/* 000000D8-00000148       .text init_mtx__13daObjLeaves_cFv */
void daObjLeaves_c::init_mtx() {
    /* Nonmatching */
}

/* 00000148-000002E4       .text birthEffect__13daObjLeaves_cFiP4cXyzP5csXyzP8_GXColor */
void daObjLeaves_c::birthEffect(int, cXyz*, csXyz*, GXColor*) {
    /* Nonmatching */
}

/* 000002E4-00000360       .text rideCallBack__FP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void rideCallBack(dBgW*, fopAc_ac_c*, fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000360-00000384       .text solidHeapCB__13daObjLeaves_cFP10fopAc_ac_c */
void daObjLeaves_c::solidHeapCB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000384-00000494       .text create_heap__13daObjLeaves_cFv */
void daObjLeaves_c::create_heap() {
    /* Nonmatching */
}

/* 00000494-000008C0       .text tg_hitCallback__13daObjLeaves_cFP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
void daObjLeaves_c::tg_hitCallback(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*) {
    /* Nonmatching */
}

/* 000008C0-00000B08       .text _create__13daObjLeaves_cFv */
cPhs_State daObjLeaves_c::_create() {
    /* Nonmatching */
}

/* 00000CC0-00000D74       .text _delete__13daObjLeaves_cFv */
bool daObjLeaves_c::_delete() {
    /* Nonmatching */
}

/* 00000D74-00000E84       .text wait_proc__13daObjLeaves_cFv */
void daObjLeaves_c::wait_proc() {
    /* Nonmatching */
}

/* 00000E84-00000EB4       .text alpha_calc_start_wait_proc__13daObjLeaves_cFv */
void daObjLeaves_c::alpha_calc_start_wait_proc() {
    /* Nonmatching */
}

/* 00000EB4-00000FB8       .text item_set_wait_proc__13daObjLeaves_cFv */
void daObjLeaves_c::item_set_wait_proc() {
    /* Nonmatching */
}

/* 00000FB8-00001010       .text retire_wait_proc__13daObjLeaves_cFv */
void daObjLeaves_c::retire_wait_proc() {
    /* Nonmatching */
}

/* 00001010-0000107C       .text _execute__13daObjLeaves_cFv */
bool daObjLeaves_c::_execute() {
    /* Nonmatching */
}

/* 0000107C-000011B0       .text set_material_sub__FP11J3DMaterialUc */
void set_material_sub(J3DMaterial*, unsigned char) {
    /* Nonmatching */
}

/* 000011B0-00001218       .text set_material__FP8J3DModelUc */
void set_material(J3DModel*, unsigned char) {
    /* Nonmatching */
}

/* 00001218-00001290       .text _draw__13daObjLeaves_cFv */
bool daObjLeaves_c::_draw() {
    /* Nonmatching */
}

/* 00001290-000012B0       .text daObjLeaves_Create__FP13daObjLeaves_c */
static cPhs_State daObjLeaves_Create(daObjLeaves_c* i_this) {
    return ((daObjLeaves_c*)i_this)->_create();
}

/* 000012B0-000012D4       .text daObjLeaves_Delete__FP13daObjLeaves_c */
static BOOL daObjLeaves_Delete(daObjLeaves_c* i_this) {
    return ((daObjLeaves_c*)i_this)->_delete();
}

/* 000012D4-000012F8       .text daObjLeaves_Execute__FP13daObjLeaves_c */
static BOOL daObjLeaves_Execute(daObjLeaves_c* i_this) {
    return ((daObjLeaves_c*)i_this)->_execute();
}

/* 000012F8-0000131C       .text daObjLeaves_Draw__FP13daObjLeaves_c */
static BOOL daObjLeaves_Draw(daObjLeaves_c* i_this) {
    return ((daObjLeaves_c*)i_this)->_draw();
}

/* 0000131C-00001324       .text daObjLeaves_IsDelete__FP13daObjLeaves_c */
static BOOL daObjLeaves_IsDelete(daObjLeaves_c*) {
    return TRUE;
}

static actor_method_class l_daObjLeaves_Method = {
    (process_method_func)daObjLeaves_Create,
    (process_method_func)daObjLeaves_Delete,
    (process_method_func)daObjLeaves_Execute,
    (process_method_func)daObjLeaves_IsDelete,
    (process_method_func)daObjLeaves_Draw,
};

actor_process_profile_definition g_profile_Obj_Leaves = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Leaves,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjLeaves_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Leaves,
    /* Actor SubMtd */ &l_daObjLeaves_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_3_e,
};
