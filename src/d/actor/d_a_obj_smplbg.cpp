//
// Generated by dtk
// Translation Unit: d_a_obj_smplbg.cpp
//

#include "d/actor/d_a_obj_smplbg.h"
#include "d/d_procname.h"

/* 00000078-00000144       .text CreateHeap__Q211daObjSmplbg5Act_cFv */
void daObjSmplbg::Act_c::CreateHeap() {
    /* Nonmatching */
}

/* 00000144-0000032C       .text Create__Q211daObjSmplbg5Act_cFv */
s32 daObjSmplbg::Act_c::Create() {
    /* Nonmatching */
}

/* 0000032C-00000474       .text Mthd_Create__Q211daObjSmplbg5Act_cFv */
void daObjSmplbg::Act_c::Mthd_Create() {
    /* Nonmatching */
}

/* 00000474-0000047C       .text Delete__Q211daObjSmplbg5Act_cFv */
BOOL daObjSmplbg::Act_c::Delete() {
    /* Nonmatching */
}

/* 0000047C-000004D8       .text Mthd_Delete__Q211daObjSmplbg5Act_cFv */
void daObjSmplbg::Act_c::Mthd_Delete() {
    /* Nonmatching */
}

/* 000004D8-00000558       .text set_mtx__Q211daObjSmplbg5Act_cFv */
void daObjSmplbg::Act_c::set_mtx() {
    /* Nonmatching */
}

/* 00000558-00000594       .text init_mtx__Q211daObjSmplbg5Act_cFv */
void daObjSmplbg::Act_c::init_mtx() {
    /* Nonmatching */
}

/* 00000594-0000061C       .text exec_qtkhd__Q211daObjSmplbg5Act_cFv */
void daObjSmplbg::Act_c::exec_qtkhd() {
    /* Nonmatching */
}

/* 0000061C-000006CC       .text Execute__Q211daObjSmplbg5Act_cFPPA3_A4_f */
void daObjSmplbg::Act_c::Execute(float(**)[3][4]) {
    /* Nonmatching */
}

/* 000006CC-00000764       .text Draw__Q211daObjSmplbg5Act_cFv */
BOOL daObjSmplbg::Act_c::Draw() {
    /* Nonmatching */
}

namespace daObjSmplbg {
namespace {
/* 00000764-00000784       .text Mthd_Create__Q211daObjSmplbg28@unnamed@d_a_obj_smplbg_cpp@FPv */
void Mthd_Create(void*) {
    /* Nonmatching */
}

/* 00000784-000007A4       .text Mthd_Delete__Q211daObjSmplbg28@unnamed@d_a_obj_smplbg_cpp@FPv */
void Mthd_Delete(void*) {
    /* Nonmatching */
}

/* 000007A4-000007C4       .text Mthd_Execute__Q211daObjSmplbg28@unnamed@d_a_obj_smplbg_cpp@FPv */
void Mthd_Execute(void*) {
    /* Nonmatching */
}

/* 000007C4-000007F0       .text Mthd_Draw__Q211daObjSmplbg28@unnamed@d_a_obj_smplbg_cpp@FPv */
void Mthd_Draw(void*) {
    /* Nonmatching */
}

/* 000007F0-0000081C       .text Mthd_IsDelete__Q211daObjSmplbg28@unnamed@d_a_obj_smplbg_cpp@FPv */
void Mthd_IsDelete(void*) {
    /* Nonmatching */
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjSmplbg

actor_process_profile_definition g_profile_Obj_Smplbg = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Smplbg,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjSmplbg::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x0032,
    /* Actor SubMtd */ &daObjSmplbg::Mthd_Table,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
