/**
 * d_a_obj_trap.cpp
 * Enemy - Blade Trap (normal)
 */

#include "d/actor/d_a_obj_trap.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 000000EC-0000010C       .text solidHeapCB__11daObjTrap_cFP10fopAc_ac_c */
void daObjTrap_c::solidHeapCB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 0000010C-000002A4       .text create_heap__11daObjTrap_cFv */
void daObjTrap_c::create_heap() {
    /* Nonmatching */
}

/* 000002A4-00000510       .text _create__11daObjTrap_cFv */
cPhs_State daObjTrap_c::_create() {
    /* Nonmatching */
}

/* 00000DF0-00000E84       .text _delete__11daObjTrap_cFv */
bool daObjTrap_c::_delete() {
    /* Nonmatching */
}

/* 00000E84-00000F20       .text init_mtx__11daObjTrap_cFv */
void daObjTrap_c::init_mtx() {
    /* Nonmatching */
}

/* 00000F20-00000F70       .text set_co_pos__11daObjTrap_cFv */
void daObjTrap_c::set_co_pos() {
    /* Nonmatching */
}

/* 00000F70-00000FF4       .text get_ground__11daObjTrap_cFv */
void daObjTrap_c::get_ground() {
    /* Nonmatching */
}

/* 00000FF4-0000112C       .text circle_search__11daObjTrap_cFv */
void daObjTrap_c::circle_search() {
    /* Nonmatching */
}

/* 0000112C-0000122C       .text set_move_info__11daObjTrap_cFv */
void daObjTrap_c::set_move_info() {
    /* Nonmatching */
}

/* 0000122C-000013E4       .text check_arrival__11daObjTrap_cFv */
void daObjTrap_c::check_arrival() {
    /* Nonmatching */
}

/* 000013E4-000018E4       .text check_wall__11daObjTrap_cFv */
void daObjTrap_c::check_wall() {
    /* Nonmatching */
}

/* 00001C88-00001D7C       .text check_block_target_pos__11daObjTrap_cFP4cXyz */
void daObjTrap_c::check_block_target_pos(cXyz*) {
    /* Nonmatching */
}

/* 00001D7C-000023D4       .text check_block__11daObjTrap_cF4cXyz */
void daObjTrap_c::check_block(cXyz) {
    /* Nonmatching */
}

/* 000023D4-0000250C       .text set_vib_mode__11daObjTrap_cFv */
void daObjTrap_c::set_vib_mode() {
    /* Nonmatching */
}

/* 0000250C-0000255C       .text vibrate__11daObjTrap_cFv */
void daObjTrap_c::vibrate() {
    /* Nonmatching */
}

/* 0000255C-00002678       .text bound__11daObjTrap_cFv */
void daObjTrap_c::bound() {
    /* Nonmatching */
}

/* 00002678-0000270C       .text set_shine__11daObjTrap_cFv */
void daObjTrap_c::set_shine() {
    /* Nonmatching */
}

/* 0000270C-00002758       .text shine_move__11daObjTrap_cFv */
void daObjTrap_c::shine_move() {
    /* Nonmatching */
}

/* 00002758-00002CB0       .text _execute__11daObjTrap_cFv */
bool daObjTrap_c::_execute() {
    /* Nonmatching */
}

/* 00002CB0-00002D54       .text _draw__11daObjTrap_cFv */
bool daObjTrap_c::_draw() {
    /* Nonmatching */
}

namespace {
/* 00002D54-00002D74       .text Mthd_Create__26@unnamed@d_a_obj_trap_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjTrap_c*)i_this)->_create();
}

/* 00002D74-00002D98       .text Mthd_Delete__26@unnamed@d_a_obj_trap_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjTrap_c*)i_this)->_delete();
}

/* 00002D98-00002DBC       .text Mthd_Execute__26@unnamed@d_a_obj_trap_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjTrap_c*)i_this)->_execute();
}

/* 00002DBC-00002DE0       .text Mthd_Draw__26@unnamed@d_a_obj_trap_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjTrap_c*)i_this)->_draw();
}

/* 00002DE0-00002DE8       .text Mthd_IsDelete__26@unnamed@d_a_obj_trap_cpp@FPv */
BOOL Mthd_IsDelete(void*) {
    return TRUE;
}

static actor_method_class Trap_Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace

actor_process_profile_definition g_profile_Obj_Trap = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Trap,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjTrap_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Trap,
    /* Actor SubMtd */ &Trap_Mthd_Table,
    /* Status       */ fopAcStts_SHOWMAP_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
