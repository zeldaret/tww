/**
 * d_a_obj_auzu.cpp
 * Object - Big Octo/Jabun's cave whirlpool
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_auzu.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 00000078-0000009C       .text solidHeapCB__Q29daObjAuzu5Act_cFP10fopAc_ac_c */
void daObjAuzu::Act_c::solidHeapCB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 0000009C-000001F8       .text create_heap__Q29daObjAuzu5Act_cFv */
void daObjAuzu::Act_c::create_heap() {
    /* Nonmatching */
}

/* 000001F8-000003B8       .text _create__Q29daObjAuzu5Act_cFv */
cPhs_State daObjAuzu::Act_c::_create() {
    /* Nonmatching */
}

/* 0000045C-00000498       .text _delete__Q29daObjAuzu5Act_cFv */
bool daObjAuzu::Act_c::_delete() {
    /* Nonmatching */
}

/* 00000498-000004E8       .text is_exist__Q29daObjAuzu5Act_cCFv */
void daObjAuzu::Act_c::is_exist() const {
    /* Nonmatching */
}

/* 000004E8-00000554       .text set_mtx__Q29daObjAuzu5Act_cFv */
void daObjAuzu::Act_c::set_mtx() {
    /* Nonmatching */
}

/* 00000554-000005B8       .text init_mtx__Q29daObjAuzu5Act_cFv */
void daObjAuzu::Act_c::init_mtx() {
    /* Nonmatching */
}

/* 000005B8-00000624       .text set_state_map__Q29daObjAuzu5Act_cFv */
void daObjAuzu::Act_c::set_state_map() {
    /* Nonmatching */
}

/* 00000624-00000788       .text ship_whirl__Q29daObjAuzu5Act_cFv */
void daObjAuzu::Act_c::ship_whirl() {
    /* Nonmatching */
}

/* 00000788-000007DC       .text bgm_start__Q29daObjAuzu5Act_cFv */
void daObjAuzu::Act_c::bgm_start() {
    /* Nonmatching */
}

/* 000007DC-00000AF8       .text _execute__Q29daObjAuzu5Act_cFv */
bool daObjAuzu::Act_c::_execute() {
    /* Nonmatching */
}

/* 00000AF8-00000B88       .text set_material__Q29daObjAuzu5Act_cFP11J3DMaterialUc */
void daObjAuzu::Act_c::set_material(J3DMaterial*, unsigned char) {
    /* Nonmatching */
}

/* 00000B88-00000C38       .text _draw__Q29daObjAuzu5Act_cFv */
bool daObjAuzu::Act_c::_draw() {
    /* Nonmatching */
}

namespace daObjAuzu {
namespace {
/* 00000C38-00000C58       .text Mthd_Create__Q29daObjAuzu26@unnamed@d_a_obj_auzu_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjAuzu::Act_c*)i_this)->_create();
}

/* 00000C58-00000C7C       .text Mthd_Delete__Q29daObjAuzu26@unnamed@d_a_obj_auzu_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjAuzu::Act_c*)i_this)->_delete();
}

/* 00000C7C-00000CA0       .text Mthd_Execute__Q29daObjAuzu26@unnamed@d_a_obj_auzu_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjAuzu::Act_c*)i_this)->_execute();
}

/* 00000CA0-00000CC4       .text Mthd_Draw__Q29daObjAuzu26@unnamed@d_a_obj_auzu_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjAuzu::Act_c*)i_this)->_draw();
}

/* 00000CC4-00000CCC       .text Mthd_IsDelete__Q29daObjAuzu26@unnamed@d_a_obj_auzu_cpp@FPv */
BOOL Mthd_IsDelete(void*) {
    return TRUE;
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjAuzu

actor_process_profile_definition g_profile_Obj_Auzu = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Auzu,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjAuzu::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Auzu,
    /* Actor SubMtd */ &daObjAuzu::Mthd_Table,
    /* Status       */ 0x06 | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
