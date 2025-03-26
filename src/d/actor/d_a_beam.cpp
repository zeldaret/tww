//
// Generated by dtk
// Translation Unit: d_a_beam.cpp
//

#include "d/actor/d_a_beam.h"
#include "d/d_cc_d.h"
#include "d/d_procname.h"

/* 000000EC-00000118       .text __ct__12daBeam_HIO_cFv */
daBeam_HIO_c::daBeam_HIO_c() {
    /* Nonmatching */
}

/* 00000118-000003B0       .text set_mtx__8daBeam_cFv */
void daBeam_c::set_mtx() {
    /* Nonmatching */
}

/* 000003B0-000003D0       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000003D0-00000688       .text CreateHeap__8daBeam_cFv */
void daBeam_c::CreateHeap() {
    /* Nonmatching */
}

/* 00000688-00000864       .text daBeam_AtHitCallback__FP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
void daBeam_AtHitCallback(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*) {
    /* Nonmatching */
}

/* 00000864-00000A00       .text daBeam_AtHitDummyCallback__FP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
void daBeam_AtHitDummyCallback(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*) {
    /* Nonmatching */
}

/* 00000A00-00000AA0       .text daBeam_checkHitCallback__FP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
void daBeam_checkHitCallback(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*) {
    /* Nonmatching */
}

/* 00000AA0-00000F24       .text CreateInit__8daBeam_cFv */
void daBeam_c::CreateInit() {
    /* Nonmatching */
}

/* 00000F24-000015A4       .text _execute__8daBeam_cFv */
bool daBeam_c::_execute() {
    /* Nonmatching */
}

/* 000015A4-000017EC       .text checkRange__8daBeam_cFP5csXyz */
void daBeam_c::checkRange(csXyz*) {
    /* Nonmatching */
}

/* 000017EC-00001A10       .text move_search__8daBeam_cFv */
void daBeam_c::move_search() {
    /* Nonmatching */
}

/* 00001A10-00001A14       .text fix_search__8daBeam_cFv */
void daBeam_c::fix_search() {
    /* Nonmatching */
}

/* 00001A14-00001BC0       .text timer_change__8daBeam_cFv */
void daBeam_c::timer_change() {
    /* Nonmatching */
}

/* 00001BC0-00001C84       .text wait_proc__8daBeam_cFv */
void daBeam_c::wait_proc() {
    /* Nonmatching */
}

/* 00001C84-00001CA4       .text daBeamCreate__FPv */
static s32 daBeamCreate(void*) {
    /* Nonmatching */
}

/* 00001CA4-00001D34       .text _create__8daBeam_cFv */
cPhs_State daBeam_c::_create() {
    /* Nonmatching */
}

/* 0000291C-0000298C       .text daBeamDelete__FPv */
static BOOL daBeamDelete(void*) {
    /* Nonmatching */
}

/* 0000298C-000029B0       .text daBeamExecute__FPv */
static BOOL daBeamExecute(void*) {
    /* Nonmatching */
}

/* 000029B0-00002AA0       .text daBeamDraw__FPv */
static BOOL daBeamDraw(void*) {
    /* Nonmatching */
}

/* 00002AA0-00002AA8       .text daBeamIsDelete__FPv */
static BOOL daBeamIsDelete(void*) {
    /* Nonmatching */
}

static actor_method_class daBeamMethodTable = {
    (process_method_func)daBeamCreate,
    (process_method_func)daBeamDelete,
    (process_method_func)daBeamExecute,
    (process_method_func)daBeamIsDelete,
    (process_method_func)daBeamDraw,
};

actor_process_profile_definition g_profile_Beam = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Beam,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daBeam_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x00DC,
    /* Actor SubMtd */ &daBeamMethodTable,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
