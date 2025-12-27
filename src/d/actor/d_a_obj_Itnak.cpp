/**
 * d_a_obj_Itnak.cpp
 * Object - Unused - Darknut statue
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_Itnak.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 00000078-0000009C       .text solidHeapCB__Q210daObjItnak5Act_cFP10fopAc_ac_c */
void daObjItnak::Act_c::solidHeapCB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 0000009C-0000016C       .text create_heap__Q210daObjItnak5Act_cFv */
void daObjItnak::Act_c::create_heap() {
    /* Nonmatching */
}

/* 0000016C-000003A0       .text _create__Q210daObjItnak5Act_cFv */
cPhs_State daObjItnak::Act_c::_create() {
    /* Nonmatching */
}

/* 00000D10-00000D40       .text _delete__Q210daObjItnak5Act_cFv */
bool daObjItnak::Act_c::_delete() {
    /* Nonmatching */
}

/* 00000D40-00000DEC       .text set_mtx__Q210daObjItnak5Act_cFv */
void daObjItnak::Act_c::set_mtx() {
    /* Nonmatching */
}

/* 00000DEC-00000EB0       .text set_co_se__Q210daObjItnak5Act_cFP8dCcD_Cyl */
void daObjItnak::Act_c::set_co_se(dCcD_Cyl*) {
    /* Nonmatching */
}

/* 00000EB0-00000F94       .text manage_draw_flag__Q210daObjItnak5Act_cFv */
void daObjItnak::Act_c::manage_draw_flag() {
    /* Nonmatching */
}

/* 00000F94-00001118       .text set_collision__Q210daObjItnak5Act_cFv */
void daObjItnak::Act_c::set_collision() {
    /* Nonmatching */
}

/* 00001118-00001158       .text _execute__Q210daObjItnak5Act_cFv */
bool daObjItnak::Act_c::_execute() {
    /* Nonmatching */
}

/* 00001158-0000123C       .text _draw__Q210daObjItnak5Act_cFv */
bool daObjItnak::Act_c::_draw() {
    /* Nonmatching */
}

namespace daObjItnak {
namespace {
/* 0000123C-0000125C       .text Mthd_Create__Q210daObjItnak27@unnamed@d_a_obj_Itnak_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjItnak::Act_c*)i_this)->_create();
}

/* 0000125C-00001280       .text Mthd_Delete__Q210daObjItnak27@unnamed@d_a_obj_Itnak_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjItnak::Act_c*)i_this)->_delete();
}

/* 00001280-000012A4       .text Mthd_Execute__Q210daObjItnak27@unnamed@d_a_obj_Itnak_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjItnak::Act_c*)i_this)->_execute();
}

/* 000012A4-000012C8       .text Mthd_Draw__Q210daObjItnak27@unnamed@d_a_obj_Itnak_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjItnak::Act_c*)i_this)->_draw();
}

/* 000012C8-000012D0       .text Mthd_IsDelete__Q210daObjItnak27@unnamed@d_a_obj_Itnak_cpp@FPv */
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
}; // namespace daObjItnak

actor_process_profile_definition g_profile_Obj_Itnak = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Itnak,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjItnak::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Itnak,
    /* Actor SubMtd */ &daObjItnak::Mthd_Table,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
