/**
 * d_a_obj_canon.cpp
 * Object - Great Sea enemy cannon
 */

#include "d/actor/d_a_obj_canon.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

const dCcD_SrcSph daObj_Canon_c::m_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ dCcG_SE_UNK23,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 75.0f,
    },
};


/* 000000EC-000001A0       .text __ct__17daObj_Canon_HIO_cFv */
daObj_Canon_HIO_c::daObj_Canon_HIO_c() {
    /* Nonmatching */
}

/* 000001E8-00000234       .text nodeControl_CB__FP7J3DNodei */
static BOOL nodeControl_CB(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000234-000003D8       .text _nodeControl__13daObj_Canon_cFP7J3DNodeP8J3DModel */
void daObj_Canon_c::_nodeControl(J3DNode*, J3DModel*) {
    /* Nonmatching */
}

/* 000003D8-000003F8       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000003F8-000004CC       .text _createHeap__13daObj_Canon_cFv */
void daObj_Canon_c::_createHeap() {
    /* Nonmatching */
}

/* 000004CC-000005AC       .text setEffect__13daObj_Canon_cFUs */
void daObj_Canon_c::setEffect(unsigned short) {
    /* Nonmatching */
}

/* 000005AC-0000082C       .text checkTgHit__13daObj_Canon_cFv */
void daObj_Canon_c::checkTgHit() {
    /* Nonmatching */
}

/* 0000082C-00000990       .text attackCannon__13daObj_Canon_cFv */
void daObj_Canon_c::attackCannon() {
    /* Nonmatching */
}

/* 00000990-00000B4C       .text lockonCannon__13daObj_Canon_cFv */
void daObj_Canon_c::lockonCannon() {
    /* Nonmatching */
}

/* 00000B4C-00000BA8       .text setAttention__13daObj_Canon_cFv */
void daObj_Canon_c::setAttention() {
    /* Nonmatching */
}

/* 00000BA8-00000C2C       .text setCollision__13daObj_Canon_cFv */
void daObj_Canon_c::setCollision() {
    /* Nonmatching */
}

/* 00000C2C-00000CB4       .text setMtx__13daObj_Canon_cFv */
void daObj_Canon_c::setMtx() {
    /* Nonmatching */
}

/* 00000CB4-00000CC8       .text modeWaitInit__13daObj_Canon_cFv */
void daObj_Canon_c::modeWaitInit() {
    /* Nonmatching */
}

/* 00000CC8-00001064       .text modeWait__13daObj_Canon_cFv */
void daObj_Canon_c::modeWait() {
    /* Nonmatching */
}

/* 00001064-00001078       .text modeAttackInit__13daObj_Canon_cFv */
void daObj_Canon_c::modeAttackInit() {
    /* Nonmatching */
}

/* 00001078-000010DC       .text modeAttack__13daObj_Canon_cFv */
void daObj_Canon_c::modeAttack() {
    /* Nonmatching */
}

/* 000010DC-00001174       .text modeDeleteInit__13daObj_Canon_cFv */
void daObj_Canon_c::modeDeleteInit() {
    /* Nonmatching */
}

/* 00001174-00001178       .text modeDelete__13daObj_Canon_cFv */
void daObj_Canon_c::modeDelete() {
    /* Nonmatching */
}

/* 00001178-00001194       .text modeSwWaitInit__13daObj_Canon_cFv */
void daObj_Canon_c::modeSwWaitInit() {
    /* Nonmatching */
}

/* 00001194-000011F4       .text modeSwWait__13daObj_Canon_cFv */
void daObj_Canon_c::modeSwWait() {
    /* Nonmatching */
}

/* 000011F4-0000121C       .text modeAppearInit__13daObj_Canon_cFv */
void daObj_Canon_c::modeAppearInit() {
    /* Nonmatching */
}

/* 0000121C-00001290       .text modeAppear__13daObj_Canon_cFv */
void daObj_Canon_c::modeAppear() {
    /* Nonmatching */
}

/* 00001290-00001410       .text modeProc__13daObj_Canon_cFQ213daObj_Canon_c6Proc_ei */
void daObj_Canon_c::modeProc(daObj_Canon_c::Proc_e, int) {
    /* Nonmatching */
}

/* 00001410-000015AC       .text _execute__13daObj_Canon_cFv */
bool daObj_Canon_c::_execute() {
    /* Nonmatching */
}

/* 000015AC-000015B0       .text debugDraw__13daObj_Canon_cFv */
void daObj_Canon_c::debugDraw() {
    /* Nonmatching */
}

/* 000015B0-00001688       .text _draw__13daObj_Canon_cFv */
bool daObj_Canon_c::_draw() {
    /* Nonmatching */
}

/* 00001688-00001804       .text createInit__13daObj_Canon_cFv */
void daObj_Canon_c::createInit() {
    /* Nonmatching */
}

/* 00001804-00001880       .text getArg__13daObj_Canon_cFv */
void daObj_Canon_c::getArg() {
    /* Nonmatching */
}

/* 00001880-000019D8       .text _create__13daObj_Canon_cFv */
cPhs_State daObj_Canon_c::_create() {
    /* Nonmatching */
}

/* 00001BEC-00001C50       .text _delete__13daObj_Canon_cFv */
bool daObj_Canon_c::_delete() {
    /* Nonmatching */
}

/* 00001C50-00001C70       .text daObj_CanonCreate__FPv */
static s32 daObj_CanonCreate(void*) {
    /* Nonmatching */
}

/* 00001C70-00001C94       .text daObj_CanonDelete__FPv */
static BOOL daObj_CanonDelete(void*) {
    /* Nonmatching */
}

/* 00001C94-00001CB8       .text daObj_CanonExecute__FPv */
static BOOL daObj_CanonExecute(void*) {
    /* Nonmatching */
}

/* 00001CB8-00001CDC       .text daObj_CanonDraw__FPv */
static BOOL daObj_CanonDraw(void*) {
    /* Nonmatching */
}

/* 00001CDC-00001CE4       .text daObj_CanonIsDelete__FPv */
static BOOL daObj_CanonIsDelete(void*) {
    /* Nonmatching */
}

static actor_method_class daObj_CanonMethodTable = {
    (process_method_func)daObj_CanonCreate,
    (process_method_func)daObj_CanonDelete,
    (process_method_func)daObj_CanonExecute,
    (process_method_func)daObj_CanonIsDelete,
    (process_method_func)daObj_CanonDraw,
};

actor_process_profile_definition g_profile_OBJ_CANON = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_OBJ_CANON,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObj_Canon_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_OBJ_CANON,
    /* Actor SubMtd */ &daObj_CanonMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
