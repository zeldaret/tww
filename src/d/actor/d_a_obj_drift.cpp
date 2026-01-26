/**
 * d_a_obj_drift.cpp
 * Object - Floating tree platform
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_drift.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 000000EC-000001A0       .text CreateHeap__Q210daObjDrift5Act_cFv */
BOOL daObjDrift::Act_c::CreateHeap() {
    /* Nonmatching */
}

/* 000001A0-00000370       .text Create__Q210daObjDrift5Act_cFv */
BOOL daObjDrift::Act_c::Create() {
    /* Nonmatching */
}

/* 00000370-0000050C       .text Mthd_Create__Q210daObjDrift5Act_cFv */
cPhs_State daObjDrift::Act_c::Mthd_Create() {
    /* Nonmatching */
}

/* 0000075C-000007EC       .text make_flower__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::make_flower() {
    /* Nonmatching */
}

/* 000007EC-00000890       .text calc_flower_param__Q210daObjDrift5Act_cFP4cXyzP5csXyz */
void daObjDrift::Act_c::calc_flower_param(cXyz*, csXyz*) {
    /* Nonmatching */
}

/* 00000890-00000954       .text set_flower_current__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::set_flower_current() {
    /* Nonmatching */
}

/* 00000954-0000095C       .text Delete__Q210daObjDrift5Act_cFv */
BOOL daObjDrift::Act_c::Delete() {
    /* Nonmatching */
}

/* 0000095C-000009A8       .text Mthd_Delete__Q210daObjDrift5Act_cFv */
BOOL daObjDrift::Act_c::Mthd_Delete() {
    /* Nonmatching */
}

/* 000009A8-000009C0       .text mode_wait_init__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::mode_wait_init() {
    /* Nonmatching */
}

/* 000009C0-00000A80       .text mode_wait__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::mode_wait() {
    /* Nonmatching */
}

/* 00000A80-00000B38       .text mode_rot_init__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::mode_rot_init() {
    /* Nonmatching */
}

/* 00000B38-00000C3C       .text mode_rot__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::mode_rot() {
    /* Nonmatching */
}

/* 00000C3C-00000D18       .text set_mtx__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::set_mtx() {
    /* Nonmatching */
}

/* 00000D18-00000D54       .text init_mtx__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::init_mtx() {
    /* Nonmatching */
}

/* 00000D54-00000EC4       .text rideCB__Q210daObjDrift5Act_cFP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void daObjDrift::Act_c::rideCB(dBgW*, fopAc_ac_c*, fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000EC4-00001104       .text set_current__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::set_current() {
    /* Nonmatching */
}

/* 00001104-000011D0       .text Execute__Q210daObjDrift5Act_cFPPA3_A4_f */
BOOL daObjDrift::Act_c::Execute(Mtx**) {
    /* Nonmatching */
}

/* 000011D0-00001270       .text Draw__Q210daObjDrift5Act_cFv */
BOOL daObjDrift::Act_c::Draw() {
    /* Nonmatching */
}

namespace daObjDrift {
namespace {
/* 00001270-00001290       .text Mthd_Create__Q210daObjDrift27@unnamed@d_a_obj_drift_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjDrift::Act_c*)i_this)->Mthd_Create();
}

/* 00001290-000012B0       .text Mthd_Delete__Q210daObjDrift27@unnamed@d_a_obj_drift_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjDrift::Act_c*)i_this)->Mthd_Delete();
}

/* 000012B0-000012D0       .text Mthd_Execute__Q210daObjDrift27@unnamed@d_a_obj_drift_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjDrift::Act_c*)i_this)->MoveBGExecute();
}

/* 000012D0-000012FC       .text Mthd_Draw__Q210daObjDrift27@unnamed@d_a_obj_drift_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjDrift::Act_c*)i_this)->Draw();
}

/* 000012FC-00001328       .text Mthd_IsDelete__Q210daObjDrift27@unnamed@d_a_obj_drift_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return ((daObjDrift::Act_c*)i_this)->IsDelete();
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjDrift

actor_process_profile_definition g_profile_Obj_Drift = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0002,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Drift,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjDrift::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Drift,
    /* Actor SubMtd */ &daObjDrift::Mthd_Table,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
