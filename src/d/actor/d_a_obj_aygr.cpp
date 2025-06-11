/**
 * d_a_obj_aygr.cpp
 * Object - Lookout Platform
 */

#include "d/actor/d_a_obj_aygr.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 00000078-000002A4       .text CreateHeap__Q29daObjAygr5Act_cFv */
BOOL daObjAygr::Act_c::CreateHeap() {
    /* Nonmatching */
}

/* 000002A4-00000310       .text Create__Q29daObjAygr5Act_cFv */
BOOL daObjAygr::Act_c::Create() {
    /* Nonmatching */
}

/* 00000310-000004D4       .text Mthd_Create__Q29daObjAygr5Act_cFv */
cPhs_State daObjAygr::Act_c::Mthd_Create() {
    /* Nonmatching */
}

/* 000004D4-000004DC       .text Delete__Q29daObjAygr5Act_cFv */
BOOL daObjAygr::Act_c::Delete() {
    /* Nonmatching */
}

/* 000004DC-0000054C       .text Mthd_Delete__Q29daObjAygr5Act_cFv */
BOOL daObjAygr::Act_c::Mthd_Delete() {
    /* Nonmatching */
}

/* 0000054C-000005F8       .text set_mtx__Q29daObjAygr5Act_cFv */
void daObjAygr::Act_c::set_mtx() {
    /* Nonmatching */
}

/* 000005F8-00000674       .text init_mtx__Q29daObjAygr5Act_cFv */
void daObjAygr::Act_c::init_mtx() {
    /* Nonmatching */
}

/* 00000674-000006B0       .text Execute__Q29daObjAygr5Act_cFPPA3_A4_f */
BOOL daObjAygr::Act_c::Execute(Mtx**) {
    /* Nonmatching */
}

/* 000006B0-0000079C       .text Draw__Q29daObjAygr5Act_cFv */
BOOL daObjAygr::Act_c::Draw() {
    /* Nonmatching */
}

namespace daObjAygr {
namespace {
/* 0000079C-000007BC       .text Mthd_Create__Q29daObjAygr26@unnamed@d_a_obj_aygr_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjAygr::Act_c*)i_this)->Mthd_Create();
}

/* 000007BC-000007DC       .text Mthd_Delete__Q29daObjAygr26@unnamed@d_a_obj_aygr_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjAygr::Act_c*)i_this)->Mthd_Delete();
}

/* 000007DC-000007FC       .text Mthd_Execute__Q29daObjAygr26@unnamed@d_a_obj_aygr_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjAygr::Act_c*)i_this)->MoveBGExecute();
}

/* 000007FC-00000828       .text Mthd_Draw__Q29daObjAygr26@unnamed@d_a_obj_aygr_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjAygr::Act_c*)i_this)->Draw();
}

/* 00000828-00000854       .text Mthd_IsDelete__Q29daObjAygr26@unnamed@d_a_obj_aygr_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return ((daObjAygr::Act_c*)i_this)->IsDelete();
}

static actor_method_class Mthd_Aygr = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjAygr

actor_process_profile_definition g_profile_Obj_Aygr = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Aygr,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjAygr::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Aygr,
    /* Actor SubMtd */ &daObjAygr::Mthd_Aygr,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
