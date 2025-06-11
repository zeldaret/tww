/**
 * d_a_obj_nest.cpp
 * Object - Kargaroc nest
 */

#include "d/actor/d_a_obj_nest.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 00000078-0000012C       .text CreateHeap__Q29daObjNest5Act_cFv */
BOOL daObjNest::Act_c::CreateHeap() {
    /* Nonmatching */
}

/* 0000012C-000001F0       .text Create__Q29daObjNest5Act_cFv */
BOOL daObjNest::Act_c::Create() {
    /* Nonmatching */
}

/* 000001F0-000002E8       .text Mthd_Create__Q29daObjNest5Act_cFv */
cPhs_State daObjNest::Act_c::Mthd_Create() {
    /* Nonmatching */
}

/* 000002E8-000002F0       .text Delete__Q29daObjNest5Act_cFv */
BOOL daObjNest::Act_c::Delete() {
    /* Nonmatching */
}

/* 000002F0-0000033C       .text Mthd_Delete__Q29daObjNest5Act_cFv */
BOOL daObjNest::Act_c::Mthd_Delete() {
    /* Nonmatching */
}

/* 0000033C-000003D4       .text set_mtx__Q29daObjNest5Act_cFv */
void daObjNest::Act_c::set_mtx() {
    /* Nonmatching */
}

/* 000003D4-00000410       .text init_mtx__Q29daObjNest5Act_cFv */
void daObjNest::Act_c::init_mtx() {
    /* Nonmatching */
}

/* 00000410-00000498       .text rideCB__Q29daObjNest5Act_cFP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void daObjNest::Act_c::rideCB(dBgW*, fopAc_ac_c*, fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000498-00000544       .text vib_set__Q29daObjNest5Act_cFf */
void daObjNest::Act_c::vib_set(float) {
    /* Nonmatching */
}

/* 00000544-0000070C       .text vib_proc__Q29daObjNest5Act_cFv */
void daObjNest::Act_c::vib_proc() {
    /* Nonmatching */
}

/* 0000070C-0000075C       .text Execute__Q29daObjNest5Act_cFPPA3_A4_f */
BOOL daObjNest::Act_c::Execute(Mtx**) {
    /* Nonmatching */
}

/* 0000075C-000007FC       .text Draw__Q29daObjNest5Act_cFv */
BOOL daObjNest::Act_c::Draw() {
    /* Nonmatching */
}

namespace daObjNest {
namespace {
/* 000007FC-0000081C       .text Mthd_Create__Q29daObjNest26@unnamed@d_a_obj_nest_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjNest::Act_c*)i_this)->Mthd_Create();
}

/* 0000081C-0000083C       .text Mthd_Delete__Q29daObjNest26@unnamed@d_a_obj_nest_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjNest::Act_c*)i_this)->Mthd_Delete();
}

/* 0000083C-0000085C       .text Mthd_Execute__Q29daObjNest26@unnamed@d_a_obj_nest_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjNest::Act_c*)i_this)->MoveBGExecute();
}

/* 0000085C-00000888       .text Mthd_Draw__Q29daObjNest26@unnamed@d_a_obj_nest_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjNest::Act_c*)i_this)->Draw();
}

/* 00000888-000008B4       .text Mthd_IsDelete__Q29daObjNest26@unnamed@d_a_obj_nest_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return ((daObjNest::Act_c*)i_this)->IsDelete();
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjNest

actor_process_profile_definition g_profile_Obj_Nest = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Nest,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjNest::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Nest,
    /* Actor SubMtd */ &daObjNest::Mthd_Table,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLSPHERE_CUSTOM_e,
};
