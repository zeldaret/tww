//
// Generated by dtk
// Translation Unit: d_a_tpota.cpp
//

#include "d/actor/d_a_tpota.h"
#include "d/d_procname.h"

/* 00000078-000001D0       .text _create__9daTpota_cFv */
cPhs_State daTpota_c::_create() {
    /* Nonmatching */
}

/* 00000250-00000298       .text _delete__9daTpota_cFv */
bool daTpota_c::_delete() {
    /* Nonmatching */
}

/* 00000298-000002FC       .text make_ripple__9daTpota_cF4cXyz */
void daTpota_c::make_ripple(cXyz) {
    /* Nonmatching */
}

/* 000002FC-00000354       .text check_water_h__9daTpota_cFP15JPABaseParticlef */
void daTpota_c::check_water_h(JPABaseParticle*, float) {
    /* Nonmatching */
}

/* 00000354-00000380       .text clear_splash__9daTpota_cFv */
void daTpota_c::clear_splash() {
    /* Nonmatching */
}

/* 00000380-000003F4       .text renew_splash__9daTpota_cFv */
void daTpota_c::renew_splash() {
    /* Nonmatching */
}

/* 000003F4-000004C8       .text _execute__9daTpota_cFv */
bool daTpota_c::_execute() {
    /* Nonmatching */
}

/* 000004C8-000004D0       .text _draw__9daTpota_cFv */
bool daTpota_c::_draw() {
    /* Nonmatching */
}

namespace {
/* 000004D0-000004F0       .text Mthd_Create__23@unnamed@d_a_tpota_cpp@FPv */
cPhs_State Mthd_Create(void*) {
    /* Nonmatching */
}

/* 000004F0-00000514       .text Mthd_Delete__23@unnamed@d_a_tpota_cpp@FPv */
BOOL Mthd_Delete(void*) {
    /* Nonmatching */
}

/* 00000514-00000538       .text Mthd_Execute__23@unnamed@d_a_tpota_cpp@FPv */
BOOL Mthd_Execute(void*) {
    /* Nonmatching */
}

/* 00000538-0000055C       .text Mthd_Draw__23@unnamed@d_a_tpota_cpp@FPv */
BOOL Mthd_Draw(void*) {
    /* Nonmatching */
}

/* 0000055C-00000564       .text Mthd_IsDelete__23@unnamed@d_a_tpota_cpp@FPv */
BOOL Mthd_IsDelete(void*) {
    /* Nonmatching */
}

static actor_method_class Tpota_Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace

actor_process_profile_definition g_profile_Tpota = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Tpota,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daTpota_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x00F8,
    /* Actor SubMtd */ &Tpota_Mthd_Table,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
