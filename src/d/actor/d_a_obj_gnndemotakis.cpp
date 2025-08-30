/**
 * d_a_obj_gnndemotakis.cpp
 * Object - Ganondorf Fight - Background waterfalls (before fight)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_gnndemotakis.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 00000078-00000098       .text solidHeapCB__15daObjGnntakis_cFP10fopAc_ac_c */
void daObjGnntakis_c::solidHeapCB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000098-000001F4       .text create_heap__15daObjGnntakis_cFv */
void daObjGnntakis_c::create_heap() {
    /* Nonmatching */
}

/* 000001F4-00000308       .text _create__15daObjGnntakis_cFv */
cPhs_State daObjGnntakis_c::_create() {
    /* Nonmatching */
}

/* 000003AC-000003DC       .text _delete__15daObjGnntakis_cFv */
bool daObjGnntakis_c::_delete() {
    /* Nonmatching */
}

/* 000003DC-000003FC       .text init_mtx__15daObjGnntakis_cFv */
void daObjGnntakis_c::init_mtx() {
    /* Nonmatching */
}

/* 000003FC-00000514       .text _execute__15daObjGnntakis_cFv */
bool daObjGnntakis_c::_execute() {
    /* Nonmatching */
}

/* 00000514-0000058C       .text _draw__15daObjGnntakis_cFv */
bool daObjGnntakis_c::_draw() {
    /* Nonmatching */
}

namespace {
/* 0000058C-000005AC       .text Mthd_Create__34@unnamed@d_a_obj_gnndemotakis_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjGnntakis_c*)i_this)->_create();
}

/* 000005AC-000005D0       .text Mthd_Delete__34@unnamed@d_a_obj_gnndemotakis_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjGnntakis_c*)i_this)->_delete();
}

/* 000005D0-000005F4       .text Mthd_Execute__34@unnamed@d_a_obj_gnndemotakis_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjGnntakis_c*)i_this)->_execute();
}

/* 000005F4-00000618       .text Mthd_Draw__34@unnamed@d_a_obj_gnndemotakis_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjGnntakis_c*)i_this)->_draw();
}

/* 00000618-00000620       .text Mthd_IsDelete__34@unnamed@d_a_obj_gnndemotakis_cpp@FPv */
BOOL Mthd_IsDelete(void*) {
    return TRUE;
}

static actor_method_class Gnntakis_Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace

actor_process_profile_definition g_profile_Obj_Gnntakis = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Gnntakis,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjGnntakis_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Gnntakis,
    /* Actor SubMtd */ &Gnntakis_Mthd_Table,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
