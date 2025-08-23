/**
 * d_a_obj_ashut.cpp
 * Object - Metal bars (Pirate Ship rope minigame)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_ashut.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 00000078-0000012C       .text CreateHeap__Q210daObjAshut5Act_cFv */
BOOL daObjAshut::Act_c::CreateHeap() {
    /* Nonmatching */
}

/* 0000012C-00000224       .text Create__Q210daObjAshut5Act_cFv */
BOOL daObjAshut::Act_c::Create() {
    /* Nonmatching */
}

/* 00000224-00000388       .text Mthd_Create__Q210daObjAshut5Act_cFv */
cPhs_State daObjAshut::Act_c::Mthd_Create() {
    /* Nonmatching */
}

/* 00000388-00000390       .text Delete__Q210daObjAshut5Act_cFv */
BOOL daObjAshut::Act_c::Delete() {
    /* Nonmatching */
}

/* 00000390-000003DC       .text Mthd_Delete__Q210daObjAshut5Act_cFv */
BOOL daObjAshut::Act_c::Mthd_Delete() {
    /* Nonmatching */
}

/* 000003DC-0000046C       .text set_mtx__Q210daObjAshut5Act_cFv */
void daObjAshut::Act_c::set_mtx() {
    /* Nonmatching */
}

/* 0000046C-000004A8       .text init_mtx__Q210daObjAshut5Act_cFv */
void daObjAshut::Act_c::init_mtx() {
    /* Nonmatching */
}

/* 000004A8-000005A4       .text chk_safe_area__Q210daObjAshut5Act_cCFv */
void daObjAshut::Act_c::chk_safe_area() const {
    /* Nonmatching */
}

/* 000005A4-000005BC       .text mode_upper_init__Q210daObjAshut5Act_cFv */
void daObjAshut::Act_c::mode_upper_init() {
    /* Nonmatching */
}

/* 000005BC-0000066C       .text mode_upper__Q210daObjAshut5Act_cFv */
void daObjAshut::Act_c::mode_upper() {
    /* Nonmatching */
}

/* 0000066C-00000700       .text mode_u_l_init__Q210daObjAshut5Act_cFv */
void daObjAshut::Act_c::mode_u_l_init() {
    /* Nonmatching */
}

/* 00000700-000007C0       .text mode_u_l__Q210daObjAshut5Act_cFv */
void daObjAshut::Act_c::mode_u_l() {
    /* Nonmatching */
}

/* 000007C0-000007D8       .text mode_lower_init__Q210daObjAshut5Act_cFv */
void daObjAshut::Act_c::mode_lower_init() {
    /* Nonmatching */
}

/* 000007D8-00000838       .text mode_lower__Q210daObjAshut5Act_cFv */
void daObjAshut::Act_c::mode_lower() {
    /* Nonmatching */
}

/* 00000838-000008D4       .text mode_l_u_init__Q210daObjAshut5Act_cFv */
void daObjAshut::Act_c::mode_l_u_init() {
    /* Nonmatching */
}

/* 000008D4-00000A50       .text mode_l_u__Q210daObjAshut5Act_cFv */
void daObjAshut::Act_c::mode_l_u() {
    /* Nonmatching */
}

/* 00000A50-00000B0C       .text mode_demoreq_init__Q210daObjAshut5Act_cFQ310daObjAshut5Act_c6Mode_e */
void daObjAshut::Act_c::mode_demoreq_init(daObjAshut::Act_c::Mode_e) {
    /* Nonmatching */
}

/* 00000B0C-00000BE4       .text mode_demoreq__Q210daObjAshut5Act_cFv */
void daObjAshut::Act_c::mode_demoreq() {
    /* Nonmatching */
}

/* 00000BE4-00000D0C       .text Execute__Q210daObjAshut5Act_cFPPA3_A4_f */
BOOL daObjAshut::Act_c::Execute(Mtx**) {
    /* Nonmatching */
}

/* 00000D0C-00000D6C       .text Draw__Q210daObjAshut5Act_cFv */
BOOL daObjAshut::Act_c::Draw() {
    /* Nonmatching */
}

namespace daObjAshut {
namespace {
/* 00000D6C-00000D8C       .text Mthd_Create__Q210daObjAshut27@unnamed@d_a_obj_ashut_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjAshut::Act_c*)i_this)->Mthd_Create();
}

/* 00000D8C-00000DAC       .text Mthd_Delete__Q210daObjAshut27@unnamed@d_a_obj_ashut_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjAshut::Act_c*)i_this)->Mthd_Delete();
}

/* 00000DAC-00000DCC       .text Mthd_Execute__Q210daObjAshut27@unnamed@d_a_obj_ashut_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjAshut::Act_c*)i_this)->MoveBGExecute();
}

/* 00000DCC-00000DF8       .text Mthd_Draw__Q210daObjAshut27@unnamed@d_a_obj_ashut_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjAshut::Act_c*)i_this)->Draw();
}

/* 00000DF8-00000E24       .text Mthd_IsDelete__Q210daObjAshut27@unnamed@d_a_obj_ashut_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return ((daObjAshut::Act_c*)i_this)->IsDelete();
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjAshut

actor_process_profile_definition g_profile_Obj_Ashut = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Ashut,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjAshut::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Ashut,
    /* Actor SubMtd */ &daObjAshut::Mthd_Table,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
