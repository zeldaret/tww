/**
 * d_a_obj_magmarock.cpp
 * Object - Dragon Roost Cavern - Lava slab
 */

#include "d/actor/d_a_obj_magmarock.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 00000078-00000128       .text set_mtx__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::set_mtx() {
    /* Nonmatching */
}

/* 00000128-00000258       .text demo_move__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::demo_move() {
    /* Nonmatching */
}

/* 00000258-00000410       .text ControlEffect__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::ControlEffect() {
    /* Nonmatching */
}

/* 0000044C-00000560       .text play_anim__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::play_anim() {
    /* Nonmatching */
}

/* 00000560-0000058C       .text appear_proc_init__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::appear_proc_init() {
    /* Nonmatching */
}

/* 0000058C-000005EC       .text appear_proc__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::appear_proc() {
    /* Nonmatching */
}

/* 000005EC-00000618       .text wait_proc_init__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::wait_proc_init() {
    /* Nonmatching */
}

/* 00000618-00000644       .text wait_proc__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::wait_proc() {
    /* Nonmatching */
}

/* 00000644-000006E0       .text stay_proc_init__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::stay_proc_init() {
    /* Nonmatching */
}

/* 000006E0-00000720       .text stay_proc__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::stay_proc() {
    /* Nonmatching */
}

/* 00000720-000007B8       .text quake_proc_init__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::quake_proc_init() {
    /* Nonmatching */
}

/* 000007B8-0000084C       .text quake_proc__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::quake_proc() {
    /* Nonmatching */
}

/* 0000084C-00000878       .text vanish_proc_init__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::vanish_proc_init() {
    /* Nonmatching */
}

/* 00000878-000008F8       .text vanish_proc__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::vanish_proc() {
    /* Nonmatching */
}

/* 000008F8-00000AEC       .text ride_call_back__14daObjMagmarockFP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void daObjMagmarock::ride_call_back(dBgW*, fopAc_ac_c*, fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000AEC-00000B0C       .text CheckCreateHeap__14daObjMagmarockFP10fopAc_ac_c */
BOOL daObjMagmarock::CheckCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000B0C-00000DA0       .text CreateHeap__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::CreateHeap() {
    /* Nonmatching */
}

/* 00000DA0-000013B4       .text CreateInit__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::CreateInit() {
    /* Nonmatching */
}

/* 000013B4-00001560       .text LiftUpRequest__Q214daObjMagmarock5Act_cFR4cXyz */
void daObjMagmarock::Act_c::LiftUpRequest(cXyz&) {
    /* Nonmatching */
}

/* 00001560-0000167C       .text BeforeLiftRequest__Q214daObjMagmarock5Act_cFR4cXyz */
void daObjMagmarock::Act_c::BeforeLiftRequest(cXyz&) {
    /* Nonmatching */
}

/* 0000167C-000017DC       .text calc_ground_quat__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::calc_ground_quat() {
    /* Nonmatching */
}

/* 000017DC-0000198C       .text Create__Q214daObjMagmarock6MethodFPv */
cPhs_State daObjMagmarock::Method::Create(void*) {
    /* Nonmatching */
}

/* 00001A90-00001B14       .text Delete__Q214daObjMagmarock6MethodFPv */
BOOL daObjMagmarock::Method::Delete(void*) {
    /* Nonmatching */
}

/* 00001B14-00001B38       .text Execute__Q214daObjMagmarock6MethodFPv */
BOOL daObjMagmarock::Method::Execute(void*) {
    /* Nonmatching */
}

/* 00001B38-00001EC0       .text _execute__Q214daObjMagmarock5Act_cFv */
bool daObjMagmarock::Act_c::_execute() {
    /* Nonmatching */
}

/* 00001EC0-00002128       .text Draw__Q214daObjMagmarock6MethodFPv */
BOOL daObjMagmarock::Method::Draw(void*) {
    /* Nonmatching */
}

/* 00002128-00002130       .text IsDelete__Q214daObjMagmarock6MethodFPv */
BOOL daObjMagmarock::Method::IsDelete(void*) {
    /* Nonmatching */
}

actor_method_class daObjMagmarock::Method::Table = {
    (process_method_func)daObjMagmarock::Method::Create,
    (process_method_func)daObjMagmarock::Method::Delete,
    (process_method_func)daObjMagmarock::Method::Execute,
    (process_method_func)daObjMagmarock::Method::IsDelete,
    (process_method_func)daObjMagmarock::Method::Draw,
};

actor_process_profile_definition g_profile_Obj_Magmarock = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Magmarock,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjMagmarock::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Magmarock,
    /* Actor SubMtd */ &daObjMagmarock::Method::Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
