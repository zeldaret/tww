/**
 * d_a_obj_Vds.cpp
 * Object - Earth Temple - Face statue (lights up when eyes are hit with Mirror Shield)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_Vds.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 00000078-00000134       .text SetLoopJointAnimation__Q28daObjVds5Act_cFP18J3DAnmTransformKeyP18J3DAnmTransformKeyff */
void daObjVds::Act_c::SetLoopJointAnimation(J3DAnmTransformKey*, J3DAnmTransformKey*, float, float) {
    /* Nonmatching */
}

/* 00000134-00000188       .text PlayLoopJointAnimation__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::PlayLoopJointAnimation() {
    /* Nonmatching */
}

/* 00000188-000001E8       .text set_first_process__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::set_first_process() {
    /* Nonmatching */
}

/* 000001E8-00000214       .text ds_search_switchCB__8daObjVdsFPvPv */
void daObjVds::ds_search_switchCB(void*, void*) {
    /* Nonmatching */
}

/* 00000214-000002B0       .text search_switchCB__Q28daObjVds5Act_cFP10fopAc_ac_c */
void daObjVds::Act_c::search_switchCB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000002EC-000003C8       .text process_off_init__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::process_off_init() {
    /* Nonmatching */
}

/* 000003C8-00000474       .text process_off_main__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::process_off_main() {
    /* Nonmatching */
}

/* 00000474-000004F0       .text process_on_init__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::process_on_init() {
    /* Nonmatching */
}

/* 000004F0-000004F4       .text process_on_main__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::process_on_main() {
    /* Nonmatching */
}

/* 000004F4-000005C0       .text process_init__Q28daObjVds5Act_cFi */
void daObjVds::Act_c::process_init(int) {
    /* Nonmatching */
}

/* 000005C0-0000065C       .text process_main__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::process_main() {
    /* Nonmatching */
}

/* 0000065C-000007EC       .text process_common__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::process_common() {
    /* Nonmatching */
}

/* 000007EC-0000087C       .text create_point_light__Q28daObjVds5Act_cFiP4cXyz */
void daObjVds::Act_c::create_point_light(int, cXyz*) {
    /* Nonmatching */
}

/* 0000087C-00000900       .text execute_point_light__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::execute_point_light() {
    /* Nonmatching */
}

/* 00000900-00000954       .text delete_point_light__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::delete_point_light() {
    /* Nonmatching */
}

/* 00000954-00000968       .text Event_init__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::Event_init() {
    /* Nonmatching */
}

/* 00000968-00000A28       .text Event_exe__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::Event_exe() {
    /* Nonmatching */
}

/* 00000A28-00000A4C       .text solidHeapCB__Q28daObjVds5Act_cFP10fopAc_ac_c */
void daObjVds::Act_c::solidHeapCB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000A4C-00001020       .text create_heap__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::create_heap() {
    /* Nonmatching */
}

/* 00001020-000011EC       .text _create__Q28daObjVds5Act_cFv */
cPhs_State daObjVds::Act_c::_create() {
    /* Nonmatching */
}

/* 000012D4-00001368       .text _delete__Q28daObjVds5Act_cFv */
bool daObjVds::Act_c::_delete() {
    /* Nonmatching */
}

/* 00001368-00001420       .text set_mtx__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::set_mtx() {
    /* Nonmatching */
}

/* 00001420-000014EC       .text _execute__Q28daObjVds5Act_cFv */
bool daObjVds::Act_c::_execute() {
    /* Nonmatching */
}

/* 000014EC-000015A8       .text _draw__Q28daObjVds5Act_cFv */
bool daObjVds::Act_c::_draw() {
    /* Nonmatching */
}

namespace daObjVds {
namespace {
/* 000015A8-000015C8       .text Mthd_Create__Q28daObjVds25@unnamed@d_a_obj_Vds_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjVds::Act_c*)i_this)->_create();
}

/* 000015C8-000015EC       .text Mthd_Delete__Q28daObjVds25@unnamed@d_a_obj_Vds_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjVds::Act_c*)i_this)->_delete();
}

/* 000015EC-00001610       .text Mthd_Execute__Q28daObjVds25@unnamed@d_a_obj_Vds_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjVds::Act_c*)i_this)->_execute();
}

/* 00001610-00001634       .text Mthd_Draw__Q28daObjVds25@unnamed@d_a_obj_Vds_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjVds::Act_c*)i_this)->_draw();
}

/* 00001634-0000163C       .text Mthd_IsDelete__Q28daObjVds25@unnamed@d_a_obj_Vds_cpp@FPv */
BOOL Mthd_IsDelete(void*) {
    return TRUE;
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjVds

actor_process_profile_definition g_profile_Obj_Vds = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Vds,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjVds::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Vds,
    /* Actor SubMtd */ &daObjVds::Mthd_Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
