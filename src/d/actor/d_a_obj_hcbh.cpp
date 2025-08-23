/**
 * d_a_obj_hcbh.cpp
 * Object - Tower of the Gods - Pillar with Companion Statue's face on it.
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_hcbh.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 00000078-000000D8       .text chk_appear__11daObjHcbh_cFv */
void daObjHcbh_c::chk_appear() {
    /* Nonmatching */
}

/* 000000D8-0000029C       .text set_mtx__11daObjHcbh_cFv */
void daObjHcbh_c::set_mtx() {
    /* Nonmatching */
}

/* 0000029C-0000030C       .text init_mtx__11daObjHcbh_cFv */
void daObjHcbh_c::init_mtx() {
    /* Nonmatching */
}

/* 0000030C-00000330       .text solidHeapCB__11daObjHcbh_cFP10fopAc_ac_c */
void daObjHcbh_c::solidHeapCB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000330-00000500       .text create_heap__11daObjHcbh_cFv */
void daObjHcbh_c::create_heap() {
    /* Nonmatching */
}

/* 00000500-000005E8       .text setup_break_condition__11daObjHcbh_cFP10fopAc_ac_c */
void daObjHcbh_c::setup_break_condition(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000005E8-00000724       .text checkCollision__11daObjHcbh_cFv */
void daObjHcbh_c::checkCollision() {
    /* Nonmatching */
}

/* 00000724-0000077C       .text co_hitCallback__11daObjHcbh_cFP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
void daObjHcbh_c::co_hitCallback(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*) {
    /* Nonmatching */
}

/* 0000077C-000008F8       .text particle_set__11daObjHcbh_cFv */
void daObjHcbh_c::particle_set() {
    /* Nonmatching */
}

/* 000008F8-000009E4       .text make_item__11daObjHcbh_cFv */
void daObjHcbh_c::make_item() {
    /* Nonmatching */
}

/* 00000A20-00000E30       .text _create__11daObjHcbh_cFv */
cPhs_State daObjHcbh_c::_create() {
    /* Nonmatching */
}

/* 000011F4-000012F4       .text _delete__11daObjHcbh_cFv */
bool daObjHcbh_c::_delete() {
    /* Nonmatching */
}

/* 000012F4-000013BC       .text wait_act_proc__11daObjHcbh_cFv */
void daObjHcbh_c::wait_act_proc() {
    /* Nonmatching */
}

/* 000013BC-000017D8       .text fall_act_proc__11daObjHcbh_cFv */
void daObjHcbh_c::fall_act_proc() {
    /* Nonmatching */
}

/* 000017D8-000018D8       .text _execute__11daObjHcbh_cFv */
bool daObjHcbh_c::_execute() {
    /* Nonmatching */
}

/* 000018D8-0000197C       .text _draw__11daObjHcbh_cFv */
bool daObjHcbh_c::_draw() {
    /* Nonmatching */
}

/* 0000197C-0000199C       .text daObjHcbh_Create__FP10fopAc_ac_c */
static cPhs_State daObjHcbh_Create(fopAc_ac_c* i_this) {
    return ((daObjHcbh_c*)i_this)->_create();
}

/* 0000199C-000019C0       .text daObjHcbh_Delete__FP11daObjHcbh_c */
static BOOL daObjHcbh_Delete(daObjHcbh_c* i_this) {
    return ((daObjHcbh_c*)i_this)->_delete();
}

/* 000019C0-000019E4       .text daObjHcbh_Execute__FP11daObjHcbh_c */
static BOOL daObjHcbh_Execute(daObjHcbh_c* i_this) {
    return ((daObjHcbh_c*)i_this)->_execute();
}

/* 000019E4-00001A08       .text daObjHcbh_Draw__FP11daObjHcbh_c */
static BOOL daObjHcbh_Draw(daObjHcbh_c* i_this) {
    return ((daObjHcbh_c*)i_this)->_draw();
}

/* 00001A08-00001A10       .text daObjHcbh_IsDelete__FP11daObjHcbh_c */
static BOOL daObjHcbh_IsDelete(daObjHcbh_c*) {
    return TRUE;
}

static actor_method_class l_daObjHcbh_Method = {
    (process_method_func)daObjHcbh_Create,
    (process_method_func)daObjHcbh_Delete,
    (process_method_func)daObjHcbh_Execute,
    (process_method_func)daObjHcbh_IsDelete,
    (process_method_func)daObjHcbh_Draw,
};

actor_process_profile_definition g_profile_Obj_Hcbh = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Hcbh,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjHcbh_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Hcbh,
    /* Actor SubMtd */ &l_daObjHcbh_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
