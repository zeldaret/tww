/**
 * d_a_obj_pirateship.cpp
 * Object - Pirate Ship
 */

#include "d/actor/d_a_obj_pirateship.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

class dBgW;

/* 000000EC-000000FC       .text ride_call_back__FP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void ride_call_back(dBgW*, fopAc_ac_c*, fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000000FC-00000220       .text path_move_call_back__FP4cXyzP4cXyzP4cXyzPv */
void path_move_call_back(cXyz*, cXyz*, cXyz*, void*) {
    /* Nonmatching */
}

/* 0000025C-000003B0       .text set_mtx__Q215daObjPirateship5Act_cFv */
void daObjPirateship::Act_c::set_mtx() {
    /* Nonmatching */
}

/* 000003B0-00000448       .text pirateCreate__Q215daObjPirateship5Act_cFPi */
void daObjPirateship::Act_c::pirateCreate(int*) {
    /* Nonmatching */
}

/* 00000448-00000814       .text partsCreate__Q215daObjPirateship5Act_cFv */
void daObjPirateship::Act_c::partsCreate() {
    /* Nonmatching */
}

/* 00000814-0000095C       .text sound_proc__Q215daObjPirateship5Act_cFv */
void daObjPirateship::Act_c::sound_proc() {
    /* Nonmatching */
}

/* 0000095C-00000A50       .text CreateHeap__Q215daObjPirateship5Act_cFv */
BOOL daObjPirateship::Act_c::CreateHeap() {
    /* Nonmatching */
}

/* 00000A50-00000B9C       .text CreateWave__Q215daObjPirateship5Act_cFv */
void daObjPirateship::Act_c::CreateWave() {
    /* Nonmatching */
}

/* 00000B9C-00000CEC       .text SetWave__Q215daObjPirateship5Act_cFv */
void daObjPirateship::Act_c::SetWave() {
    /* Nonmatching */
}

/* 00000CEC-00000D38       .text DeleteWave__Q215daObjPirateship5Act_cFv */
void daObjPirateship::Act_c::DeleteWave() {
    /* Nonmatching */
}

/* 00000D38-00000DA4       .text Create__Q215daObjPirateship5Act_cFv */
BOOL daObjPirateship::Act_c::Create() {
    /* Nonmatching */
}

/* 00000DA4-00000DB4       .text Execute__Q215daObjPirateship5Act_cFPPA3_A4_f */
BOOL daObjPirateship::Act_c::Execute(Mtx**) {
    /* Nonmatching */
}

/* 00000DB4-00000E68       .text Draw__Q215daObjPirateship5Act_cFv */
BOOL daObjPirateship::Act_c::Draw() {
    /* Nonmatching */
}

/* 00000E68-00000E70       .text Delete__Q215daObjPirateship5Act_cFv */
BOOL daObjPirateship::Act_c::Delete() {
    /* Nonmatching */
}

/* 00000E70-00000EF0       .text demo_move__Q215daObjPirateship5Act_cFv */
void daObjPirateship::Act_c::demo_move() {
    /* Nonmatching */
}

/* 00000EF0-00000F10       .text Create__Q215daObjPirateship6MethodFPv */
cPhs_State daObjPirateship::Method::Create(void*) {
    /* Nonmatching */
}

/* 00000F10-000012A4       .text _create__Q215daObjPirateship5Act_cFv */
cPhs_State daObjPirateship::Act_c::_create() {
    /* Nonmatching */
}

/* 000012A4-000017E0       .text _execute__Q215daObjPirateship5Act_cFv */
bool daObjPirateship::Act_c::_execute() {
    /* Nonmatching */
}

/* 00001E8C-00001F50       .text Delete__Q215daObjPirateship6MethodFPv */
BOOL daObjPirateship::Method::Delete(void*) {
    /* Nonmatching */
}

/* 00001F50-00001F74       .text Execute__Q215daObjPirateship6MethodFPv */
BOOL daObjPirateship::Method::Execute(void*) {
    /* Nonmatching */
}

/* 00001F74-00001FAC       .text Draw__Q215daObjPirateship6MethodFPv */
BOOL daObjPirateship::Method::Draw(void*) {
    /* Nonmatching */
}

/* 00001FAC-00001FB4       .text IsDelete__Q215daObjPirateship6MethodFPv */
BOOL daObjPirateship::Method::IsDelete(void*) {
    /* Nonmatching */
}

actor_method_class daObjPirateship::Method::Table = {
    (process_method_func)daObjPirateship::Method::Create,
    (process_method_func)daObjPirateship::Method::Delete,
    (process_method_func)daObjPirateship::Method::Execute,
    (process_method_func)daObjPirateship::Method::IsDelete,
    (process_method_func)daObjPirateship::Method::Draw,
};

actor_process_profile_definition g_profile_Obj_Pirateship = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Pirateship,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjPirateship::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Pirateship,
    /* Actor SubMtd */ &daObjPirateship::Method::Table,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
