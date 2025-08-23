/**
 * d_a_obj_htetu1.cpp
 * Object - Tower of the Gods - Large yellow gate (blocks room containing Small Key)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_htetu1.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 00000078-00000178       .text create_s__19daObjHtetu1Splash_cFUsP4cXyzP5csXyzP12dKy_tevstr_c */
void daObjHtetu1Splash_c::create_s(unsigned short, cXyz*, csXyz*, dKy_tevstr_c*) {
    /* Nonmatching */
}

/* 00000178-00000198       .text solidHeapCB__13daObjHtetu1_cFP10fopAc_ac_c */
void daObjHtetu1_c::solidHeapCB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000198-00000298       .text create_heap__13daObjHtetu1_cFv */
void daObjHtetu1_c::create_heap() {
    /* Nonmatching */
}

/* 00000298-00000460       .text _create__13daObjHtetu1_cFv */
cPhs_State daObjHtetu1_c::_create() {
    /* Nonmatching */
}

/* 00000508-00000610       .text _delete__13daObjHtetu1_cFv */
bool daObjHtetu1_c::_delete() {
    /* Nonmatching */
}

/* 00000610-00000648       .text check_sw__13daObjHtetu1_cFv */
void daObjHtetu1_c::check_sw() {
    /* Nonmatching */
}

/* 00000648-000006E4       .text init_mtx__13daObjHtetu1_cFv */
void daObjHtetu1_c::init_mtx() {
    /* Nonmatching */
}

/* 000006E4-000007F8       .text unlock__13daObjHtetu1_cFv */
void daObjHtetu1_c::unlock() {
    /* Nonmatching */
}

/* 000007F8-0000098C       .text get_water_h__13daObjHtetu1_cFv */
void daObjHtetu1_c::get_water_h() {
    /* Nonmatching */
}

/* 00000AB0-00000BCC       .text splash_manager__13daObjHtetu1_cFv */
void daObjHtetu1_c::splash_manager() {
    /* Nonmatching */
}

/* 00000BCC-0000101C       .text _execute__13daObjHtetu1_cFv */
bool daObjHtetu1_c::_execute() {
    /* Nonmatching */
}

/* 0000101C-0000107C       .text _draw__13daObjHtetu1_cFv */
bool daObjHtetu1_c::_draw() {
    /* Nonmatching */
}

namespace {
/* 0000107C-0000109C       .text Mthd_Create__28@unnamed@d_a_obj_htetu1_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjHtetu1_c*)i_this)->_create();
}

/* 0000109C-000010C0       .text Mthd_Delete__28@unnamed@d_a_obj_htetu1_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjHtetu1_c*)i_this)->_delete();
}

/* 000010C0-000010E4       .text Mthd_Execute__28@unnamed@d_a_obj_htetu1_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjHtetu1_c*)i_this)->_execute();
}

/* 000010E4-00001108       .text Mthd_Draw__28@unnamed@d_a_obj_htetu1_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjHtetu1_c*)i_this)->_draw();
}

/* 00001108-00001110       .text Mthd_IsDelete__28@unnamed@d_a_obj_htetu1_cpp@FPv */
BOOL Mthd_IsDelete(void*) {
    return TRUE;
}

static actor_method_class Htetu1_Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace

actor_process_profile_definition g_profile_Obj_Htetu1 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Htetu1,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjHtetu1_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Htetu1,
    /* Actor SubMtd */ &Htetu1_Mthd_Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
