/**
 * d_a_obj_tenmado.cpp
 * Object - Earth Temple - Doors blocking ceiling light beam
 */

#include "d/actor/d_a_obj_tenmado.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 00000078-000001B4       .text CreateHeap__Q212daObjTenmado5Act_cFv */
BOOL daObjTenmado::Act_c::CreateHeap() {
    /* Nonmatching */
}

/* 000001B4-0000029C       .text Create__Q212daObjTenmado5Act_cFv */
BOOL daObjTenmado::Act_c::Create() {
    /* Nonmatching */
}

/* 0000029C-00000394       .text Mthd_Create__Q212daObjTenmado5Act_cFv */
cPhs_State daObjTenmado::Act_c::Mthd_Create() {
    /* Nonmatching */
}

/* 00000394-0000039C       .text Delete__Q212daObjTenmado5Act_cFv */
BOOL daObjTenmado::Act_c::Delete() {
    /* Nonmatching */
}

/* 0000039C-000003E8       .text Mthd_Delete__Q212daObjTenmado5Act_cFv */
BOOL daObjTenmado::Act_c::Mthd_Delete() {
    /* Nonmatching */
}

/* 000003E8-000004D8       .text set_mtx__Q212daObjTenmado5Act_cFv */
void daObjTenmado::Act_c::set_mtx() {
    /* Nonmatching */
}

/* 000004D8-00000530       .text init_mtx__Q212daObjTenmado5Act_cFv */
void daObjTenmado::Act_c::init_mtx() {
    /* Nonmatching */
}

/* 00000530-00000694       .text Execute__Q212daObjTenmado5Act_cFPPA3_A4_f */
BOOL daObjTenmado::Act_c::Execute(Mtx**) {
    /* Nonmatching */
}

/* 00000694-00000750       .text Draw__Q212daObjTenmado5Act_cFv */
BOOL daObjTenmado::Act_c::Draw() {
    /* Nonmatching */
}

namespace daObjTenmado {
namespace {
/* 00000750-00000770       .text Mthd_Create__Q212daObjTenmado29@unnamed@d_a_obj_tenmado_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjTenmado::Act_c*)i_this)->Mthd_Create();
}

/* 00000770-00000790       .text Mthd_Delete__Q212daObjTenmado29@unnamed@d_a_obj_tenmado_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjTenmado::Act_c*)i_this)->Mthd_Delete();
}

/* 00000790-000007B0       .text Mthd_Execute__Q212daObjTenmado29@unnamed@d_a_obj_tenmado_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjTenmado::Act_c*)i_this)->MoveBGExecute();
}

/* 000007B0-000007DC       .text Mthd_Draw__Q212daObjTenmado29@unnamed@d_a_obj_tenmado_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjTenmado::Act_c*)i_this)->Draw();
}

/* 000007DC-00000808       .text Mthd_IsDelete__Q212daObjTenmado29@unnamed@d_a_obj_tenmado_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return ((daObjTenmado::Act_c*)i_this)->IsDelete();
}

static actor_method_class Mthd_Tenmado = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjTenmado

actor_process_profile_definition g_profile_Obj_Tenmado = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Tenmado,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjTenmado::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Tenmado,
    /* Actor SubMtd */ &daObjTenmado::Mthd_Tenmado,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
