/**
 * d_a_goal_flag.cpp
 * Object - Big red finish line flag (Boating Course, Flight Control Platform)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_goal_flag.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 000000EC-00000210       .text setTexObj__16daGFlag_packet_cFUc */
void daGFlag_packet_c::setTexObj(unsigned char) {
    /* Nonmatching */
}

/* 00000210-00000330       .text setToonTexObj__16daGFlag_packet_cFv */
void daGFlag_packet_c::setToonTexObj() {
    /* Nonmatching */
}

/* 00000330-00000978       .text draw__16daGFlag_packet_cFv */
void daGFlag_packet_c::draw() {
    /* Nonmatching */
}

/* 00000978-00000A04       .text setBackNrm__16daGFlag_packet_cFv */
void daGFlag_packet_c::setBackNrm() {
    /* Nonmatching */
}

/* 00000A04-00000E78       .text setNrmVtx__16daGFlag_packet_cFP4cXyzii */
void daGFlag_packet_c::setNrmVtx(cXyz*, int, int) {
    /* Nonmatching */
}

/* 00000EB4-00000F80       .text getRacePath__13daGoal_Flag_cFUc */
void daGoal_Flag_c::getRacePath(unsigned char) {
    /* Nonmatching */
}

/* 00000F80-000010F4       .text RopeMove__13daGoal_Flag_cFv */
void daGoal_Flag_c::RopeMove() {
    /* Nonmatching */
}

/* 000010F4-0000123C       .text CreateBuoyRaces__13daGoal_Flag_cFv */
void daGoal_Flag_c::CreateBuoyRaces() {
    /* Nonmatching */
}

/* 0000123C-00001450       .text goal_check__13daGoal_Flag_cFv */
void daGoal_Flag_c::goal_check() {
    /* Nonmatching */
}

/* 00001450-0000183C       .text flag_move__13daGoal_Flag_cFv */
void daGoal_Flag_c::flag_move() {
    /* Nonmatching */
}

/* 0000183C-00001970       .text get_cloth_anim_sub_factor__FP4cXyzP4cXyzP4cXyzf */
void get_cloth_anim_sub_factor(cXyz*, cXyz*, cXyz*, float) {
    /* Nonmatching */
}

/* 00001970-00001CC0       .text get_cloth_anim_factor__13daGoal_Flag_cFP4cXyzP4cXyzP4cXyzii */
void daGoal_Flag_c::get_cloth_anim_factor(cXyz*, cXyz*, cXyz*, int, int) {
    /* Nonmatching */
}

/* 00001CC0-00001CE0       .text checkCreateHeap__FP10fopAc_ac_c */
static BOOL checkCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00001CE0-00001D74       .text CreateHeap__13daGoal_Flag_cFv */
void daGoal_Flag_c::CreateHeap() {
    /* Nonmatching */
}

/* 00001D74-00001DB4       .text getDemoAction__13daGoal_Flag_cFi */
void daGoal_Flag_c::getDemoAction(int) {
    /* Nonmatching */
}

/* 00001DB4-00001F60       .text RaceStart__13daGoal_Flag_cFv */
void daGoal_Flag_c::RaceStart() {
    /* Nonmatching */
}

/* 00001F60-00002290       .text TimerExecute__13daGoal_Flag_cFv */
void daGoal_Flag_c::TimerExecute() {
    /* Nonmatching */
}

/* 00002290-000023E0       .text RaceEnd__13daGoal_Flag_cFv */
void daGoal_Flag_c::RaceEnd() {
    /* Nonmatching */
}

/* 000023E0-00002400       .text daGoal_FlagCreate__FPv */
static cPhs_State daGoal_FlagCreate(void* i_this) {
    return ((daGoal_Flag_c*)i_this)->_create();
}

/* 00002400-00002968       .text _create__13daGoal_Flag_cFv */
cPhs_State daGoal_Flag_c::_create() {
    /* Nonmatching */
}

/* 000029CC-00002AAC       .text daGoal_FlagDelete__FPv */
static BOOL daGoal_FlagDelete(void*) {
    /* Nonmatching */
}

/* 00002AAC-00002B14       .text daGoal_FlagExecute__FPv */
static BOOL daGoal_FlagExecute(void*) {
    /* Nonmatching */
}

/* 00002B14-00002CA4       .text daGoal_FlagDraw__FPv */
static BOOL daGoal_FlagDraw(void*) {
    /* Nonmatching */
}

/* 00002CA4-00002CAC       .text daGoal_FlagIsDelete__FPv */
static BOOL daGoal_FlagIsDelete(void*) {
    return TRUE;
}

static actor_method_class daGoal_FlagMethodTable = {
    (process_method_func)daGoal_FlagCreate,
    (process_method_func)daGoal_FlagDelete,
    (process_method_func)daGoal_FlagExecute,
    (process_method_func)daGoal_FlagIsDelete,
    (process_method_func)daGoal_FlagDraw,
};

actor_process_profile_definition g_profile_Goal_Flag = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Goal_Flag,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daGoal_Flag_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Goal_Flag,
    /* Actor SubMtd */ &daGoal_FlagMethodTable,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
