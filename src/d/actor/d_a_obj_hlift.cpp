/**
 * d_a_obj_hlift.cpp
 * Object - Wooden platforms (Pirate ship rope minigame 1)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_hlift.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 00000078-000001BC       .text CreateHeap__Q210daObjHlift5Act_cFv */
BOOL daObjHlift::Act_c::CreateHeap() {
    /* Nonmatching */
}

/* 000001BC-000002D0       .text Create__Q210daObjHlift5Act_cFv */
BOOL daObjHlift::Act_c::Create() {
    /* Nonmatching */
}

/* 000002D0-00000408       .text Mthd_Create__Q210daObjHlift5Act_cFv */
cPhs_State daObjHlift::Act_c::Mthd_Create() {
    /* Nonmatching */
}

/* 00000408-00000430       .text Delete__Q210daObjHlift5Act_cFv */
BOOL daObjHlift::Act_c::Delete() {
    /* Nonmatching */
}

/* 00000430-0000047C       .text Mthd_Delete__Q210daObjHlift5Act_cFv */
BOOL daObjHlift::Act_c::Mthd_Delete() {
    /* Nonmatching */
}

/* 0000047C-00000490       .text mode_lower_init__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::mode_lower_init() {
    /* Nonmatching */
}

/* 00000490-000004F0       .text mode_lower__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::mode_lower() {
    /* Nonmatching */
}

/* 000004F0-000005B8       .text mode_l_u_init__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::mode_l_u_init() {
    /* Nonmatching */
}

/* 000005B8-00000724       .text mode_l_u__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::mode_l_u() {
    /* Nonmatching */
}

/* 00000724-00000778       .text mode_upper_init__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::mode_upper_init() {
    /* Nonmatching */
}

/* 00000778-000007D8       .text mode_upper__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::mode_upper() {
    /* Nonmatching */
}

/* 000007D8-000008A0       .text mode_u_l_init__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::mode_u_l_init() {
    /* Nonmatching */
}

/* 000008A0-000009DC       .text mode_u_l__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::mode_u_l() {
    /* Nonmatching */
}

/* 000009DC-00000AB0       .text mode_demoreq_init__Q210daObjHlift5Act_cFQ310daObjHlift5Act_c6Mode_e */
void daObjHlift::Act_c::mode_demoreq_init(daObjHlift::Act_c::Mode_e) {
    /* Nonmatching */
}

/* 00000AB0-00000B28       .text mode_demoreq__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::mode_demoreq() {
    /* Nonmatching */
}

/* 00000B28-00000BE8       .text set_mtx__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::set_mtx() {
    /* Nonmatching */
}

/* 00000BE8-00000C40       .text init_mtx__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::init_mtx() {
    /* Nonmatching */
}

/* 00000C40-00000C8C       .text rot_set__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::rot_set() {
    /* Nonmatching */
}

/* 00000C8C-00000CA8       .text vib_set__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::vib_set() {
    /* Nonmatching */
}

/* 00000CA8-00000D70       .text vib_proc__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::vib_proc() {
    /* Nonmatching */
}

/* 00000D70-00000DE8       .text chk_demo_end__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::chk_demo_end() {
    /* Nonmatching */
}

/* 00000DE8-00000E74       .text se_whole__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::se_whole() {
    /* Nonmatching */
}

/* 00000E74-00000FD4       .text Execute__Q210daObjHlift5Act_cFPPA3_A4_f */
BOOL daObjHlift::Act_c::Execute(Mtx**) {
    /* Nonmatching */
}

/* 00000FD4-00001090       .text Draw__Q210daObjHlift5Act_cFv */
BOOL daObjHlift::Act_c::Draw() {
    /* Nonmatching */
}

namespace daObjHlift {
namespace {
/* 00001090-000010B0       .text Mthd_Create__Q210daObjHlift27@unnamed@d_a_obj_hlift_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjHlift::Act_c*)i_this)->Mthd_Create();
}

/* 000010B0-000010D0       .text Mthd_Delete__Q210daObjHlift27@unnamed@d_a_obj_hlift_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjHlift::Act_c*)i_this)->Mthd_Delete();
}

/* 000010D0-000010F0       .text Mthd_Execute__Q210daObjHlift27@unnamed@d_a_obj_hlift_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjHlift::Act_c*)i_this)->MoveBGExecute();
}

/* 000010F0-0000111C       .text Mthd_Draw__Q210daObjHlift27@unnamed@d_a_obj_hlift_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjHlift::Act_c*)i_this)->Draw();
}

/* 0000111C-00001148       .text Mthd_IsDelete__Q210daObjHlift27@unnamed@d_a_obj_hlift_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return ((daObjHlift::Act_c*)i_this)->IsDelete();
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjHlift

actor_process_profile_definition g_profile_Obj_Hlift = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Hlift,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjHlift::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Hlift,
    /* Actor SubMtd */ &daObjHlift::Mthd_Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
