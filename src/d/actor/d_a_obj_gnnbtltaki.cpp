/**
 * d_a_obj_gnnbtltaki.cpp
 * Object - Ganondorf Fight - Background waterfalls (during fight)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_gnnbtltaki.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 00000078-00000098       .text solidHeapCB__15daObjGnnbtaki_cFP10fopAc_ac_c */
void daObjGnnbtaki_c::solidHeapCB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000098-000001F4       .text create_heap__15daObjGnnbtaki_cFv */
void daObjGnnbtaki_c::create_heap() {
    /* Nonmatching */
}

/* 000001F4-00000348       .text _create__15daObjGnnbtaki_cFv */
cPhs_State daObjGnnbtaki_c::_create() {
    /* Nonmatching */
}

/* 000003EC-0000041C       .text _delete__15daObjGnnbtaki_cFv */
bool daObjGnnbtaki_c::_delete() {
    /* Nonmatching */
}

/* 0000041C-0000043C       .text init_mtx__15daObjGnnbtaki_cFv */
void daObjGnnbtaki_c::init_mtx() {
    /* Nonmatching */
}

/* 0000043C-00000548       .text _execute__15daObjGnnbtaki_cFv */
bool daObjGnnbtaki_c::_execute() {
    /* Nonmatching */
}

/* 00000548-000005CC       .text _draw__15daObjGnnbtaki_cFv */
bool daObjGnnbtaki_c::_draw() {
    /* Nonmatching */
}

namespace {
/* 000005CC-000005EC       .text Mthd_Create__32@unnamed@d_a_obj_gnnbtltaki_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjGnnbtaki_c*)i_this)->_create();
}

/* 000005EC-00000610       .text Mthd_Delete__32@unnamed@d_a_obj_gnnbtltaki_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjGnnbtaki_c*)i_this)->_delete();
}

/* 00000610-00000634       .text Mthd_Execute__32@unnamed@d_a_obj_gnnbtltaki_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjGnnbtaki_c*)i_this)->_execute();
}

/* 00000634-00000658       .text Mthd_Draw__32@unnamed@d_a_obj_gnnbtltaki_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjGnnbtaki_c*)i_this)->_draw();
}

/* 00000658-00000660       .text Mthd_IsDelete__32@unnamed@d_a_obj_gnnbtltaki_cpp@FPv */
BOOL Mthd_IsDelete(void*) {
    return TRUE;
}

static actor_method_class Gnnbtaki_Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace

actor_process_profile_definition g_profile_Obj_Gnnbtaki = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Gnnbtaki,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjGnnbtaki_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Gnnbtaki,
    /* Actor SubMtd */ &Gnnbtaki_Mthd_Table,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
