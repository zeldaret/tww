/**
 * d_a_obj_jump.cpp
 * Object - Wind Temple - Iron Boots springboard
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_jump.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 00000078-00000184       .text CreateHeap__Q29daObjJump5Act_cFv */
BOOL daObjJump::Act_c::CreateHeap() {
    /* Nonmatching */
}

/* 00000184-0000033C       .text Create__Q29daObjJump5Act_cFv */
BOOL daObjJump::Act_c::Create() {
    /* Nonmatching */
}

/* 0000033C-00000544       .text Mthd_Create__Q29daObjJump5Act_cFv */
cPhs_State daObjJump::Act_c::Mthd_Create() {
    /* Nonmatching */
}

/* 00000A04-00000A0C       .text Delete__Q29daObjJump5Act_cFv */
BOOL daObjJump::Act_c::Delete() {
    /* Nonmatching */
}

/* 00000A0C-00000A58       .text Mthd_Delete__Q29daObjJump5Act_cFv */
BOOL daObjJump::Act_c::Mthd_Delete() {
    /* Nonmatching */
}

/* 00000A58-00000B78       .text set_mtx__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::set_mtx() {
    /* Nonmatching */
}

/* 00000B78-00000BB4       .text init_mtx__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::init_mtx() {
    /* Nonmatching */
}

/* 00000BB4-00000D9C       .text set_push_flag__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::set_push_flag() {
    /* Nonmatching */
}

/* 00000D9C-00000DB4       .text clear_push_flag__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::clear_push_flag() {
    /* Nonmatching */
}

/* 00000DB4-00000E1C       .text calc_vib_pos__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::calc_vib_pos() {
    /* Nonmatching */
}

/* 00000E1C-00000E74       .text rideCB__Q29daObjJump5Act_cFP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void daObjJump::Act_c::rideCB(dBgW*, fopAc_ac_c*, fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000E74-00000F48       .text jnodeCB_lower__Q29daObjJump5Act_cFP7J3DNodei */
BOOL daObjJump::Act_c::jnodeCB_lower(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000F48-00000F64       .text mode_wait_init__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_wait_init() {
    /* Nonmatching */
}

/* 00000F64-0000108C       .text mode_wait__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_wait() {
    /* Nonmatching */
}

/* 0000108C-000010B4       .text mode_w_l_init__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_w_l_init() {
    /* Nonmatching */
}

/* 000010B4-000010E8       .text mode_w_l__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_w_l() {
    /* Nonmatching */
}

/* 000010E8-000010FC       .text mode_lower_init__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_lower_init() {
    /* Nonmatching */
}

/* 000010FC-00001200       .text mode_lower__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_lower() {
    /* Nonmatching */
}

/* 00001200-00001228       .text mode_l_u_init__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_l_u_init() {
    /* Nonmatching */
}

/* 00001228-00001290       .text mode_l_u__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_l_u() {
    /* Nonmatching */
}

/* 00001290-000012B8       .text mode_upper_init__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_upper_init() {
    /* Nonmatching */
}

/* 000012B8-000012EC       .text mode_upper__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_upper() {
    /* Nonmatching */
}

/* 000012EC-00001304       .text mode_u_w_init__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_u_w_init() {
    /* Nonmatching */
}

/* 00001304-00001338       .text mode_u_w__Q29daObjJump5Act_cFv */
void daObjJump::Act_c::mode_u_w() {
    /* Nonmatching */
}

/* 00001338-000014B0       .text Execute__Q29daObjJump5Act_cFPPA3_A4_f */
BOOL daObjJump::Act_c::Execute(Mtx**) {
    /* Nonmatching */
}

/* 000014B0-00001594       .text Draw__Q29daObjJump5Act_cFv */
BOOL daObjJump::Act_c::Draw() {
    /* Nonmatching */
}

namespace daObjJump {
namespace {
/* 00001594-000015B4       .text Mthd_Create__Q29daObjJump26@unnamed@d_a_obj_jump_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjJump::Act_c*)i_this)->Mthd_Create();
}

/* 000015B4-000015D4       .text Mthd_Delete__Q29daObjJump26@unnamed@d_a_obj_jump_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjJump::Act_c*)i_this)->Mthd_Delete();
}

/* 000015D4-000015F4       .text Mthd_Execute__Q29daObjJump26@unnamed@d_a_obj_jump_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjJump::Act_c*)i_this)->MoveBGExecute();
}

/* 000015F4-00001620       .text Mthd_Draw__Q29daObjJump26@unnamed@d_a_obj_jump_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjJump::Act_c*)i_this)->Draw();
}

/* 00001620-0000164C       .text Mthd_IsDelete__Q29daObjJump26@unnamed@d_a_obj_jump_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return ((daObjJump::Act_c*)i_this)->IsDelete();
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjJump

actor_process_profile_definition g_profile_Obj_Jump = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0004,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Jump,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjJump::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Jump,
    /* Actor SubMtd */ &daObjJump::Mthd_Table,
    /* Status       */ 0x04 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
