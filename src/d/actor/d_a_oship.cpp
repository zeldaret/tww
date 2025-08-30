/**
 * d_a_oship.cpp
 * Enemy - Warship (Great Sea enemy ship)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_oship.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

const dCcD_SrcCyl daOship_c::m_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG,
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
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 75.0f,
        /* Height */ 115.0f,
    }},
};


/* 000000EC-00000234       .text __ct__13daOship_HIO_cFv */
daOship_HIO_c::daOship_HIO_c() {
    /* Nonmatching */
}

/* 000002B8-000002D8       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000002D8-00000324       .text nodeControl_CB__FP7J3DNodei */
static BOOL nodeControl_CB(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000324-00000410       .text _nodeControl__9daOship_cFP7J3DNodeP8J3DModel */
void daOship_c::_nodeControl(J3DNode*, J3DModel*) {
    /* Nonmatching */
}

/* 0000044C-00000488       .text pathMove_CB__FP4cXyzP4cXyzP4cXyzPv */
void pathMove_CB(cXyz*, cXyz*, cXyz*, void*) {
    /* Nonmatching */
}

/* 00000488-00000718       .text _pathMove__9daOship_cFP4cXyzP4cXyzP4cXyz */
void daOship_c::_pathMove(cXyz*, cXyz*, cXyz*) {
    /* Nonmatching */
}

/* 00000718-000007E4       .text pathMove__9daOship_cFv */
void daOship_c::pathMove() {
    /* Nonmatching */
}

/* 000007E4-000008A0       .text plFireRepeat__9daOship_cFv */
void daOship_c::plFireRepeat() {
    /* Nonmatching */
}

/* 000008A0-000008F8       .text lineCheck__9daOship_cFP4cXyzP4cXyz */
void daOship_c::lineCheck(cXyz*, cXyz*) {
    /* Nonmatching */
}

/* 000008F8-00000990       .text changeModeByRange__9daOship_cFv */
void daOship_c::changeModeByRange() {
    /* Nonmatching */
}

/* 00000990-00000C08       .text createWave__9daOship_cFv */
void daOship_c::createWave() {
    /* Nonmatching */
}

/* 00000C08-00000E50       .text setWave__9daOship_cFv */
void daOship_c::setWave() {
    /* Nonmatching */
}

/* 00000E50-00001184       .text checkTgHit__9daOship_cFv */
void daOship_c::checkTgHit() {
    /* Nonmatching */
}

/* 00001184-000011F4       .text setAttention__9daOship_cFv */
void daOship_c::setAttention() {
    /* Nonmatching */
}

/* 000011F4-00001330       .text setCollision__9daOship_cFv */
void daOship_c::setCollision() {
    /* Nonmatching */
}

/* 00001330-000014D4       .text attackCannon__9daOship_cFi */
void daOship_c::attackCannon(int) {
    /* Nonmatching */
}

/* 000014D4-000017CC       .text setMtx__9daOship_cFv */
void daOship_c::setMtx() {
    /* Nonmatching */
}

/* 000017CC-000017EC       .text modeWaitInit__9daOship_cFv */
void daOship_c::modeWaitInit() {
    /* Nonmatching */
}

/* 000017EC-0000180C       .text modeWait__9daOship_cFv */
void daOship_c::modeWait() {
    /* Nonmatching */
}

/* 0000180C-00001820       .text modeRangeAInit__9daOship_cFv */
void daOship_c::modeRangeAInit() {
    /* Nonmatching */
}

/* 00001820-00001900       .text modeRangeA__9daOship_cFv */
void daOship_c::modeRangeA() {
    /* Nonmatching */
}

/* 00001900-00001934       .text modeRangeBInit__9daOship_cFv */
void daOship_c::modeRangeBInit() {
    /* Nonmatching */
}

/* 00001934-00001A14       .text modeRangeB__9daOship_cFv */
void daOship_c::modeRangeB() {
    /* Nonmatching */
}

/* 00001A14-00001A28       .text modeRangeCInit__9daOship_cFv */
void daOship_c::modeRangeCInit() {
    /* Nonmatching */
}

/* 00001A28-00001AFC       .text modeRangeC__9daOship_cFv */
void daOship_c::modeRangeC() {
    /* Nonmatching */
}

/* 00001AFC-00001B00       .text modeRangeDInit__9daOship_cFv */
void daOship_c::modeRangeDInit() {
    /* Nonmatching */
}

/* 00001B00-00001B7C       .text modeRangeD__9daOship_cFv */
void daOship_c::modeRangeD() {
    /* Nonmatching */
}

/* 00001B7C-00001B90       .text modeDamageInit__9daOship_cFv */
void daOship_c::modeDamageInit() {
    /* Nonmatching */
}

/* 00001B90-00001C98       .text modeDamage__9daOship_cFv */
void daOship_c::modeDamage() {
    /* Nonmatching */
}

/* 00001C98-00001EC8       .text modeAttackInit__9daOship_cFv */
void daOship_c::modeAttackInit() {
    /* Nonmatching */
}

/* 00001EC8-00002044       .text modeAttack__9daOship_cFv */
void daOship_c::modeAttack() {
    /* Nonmatching */
}

/* 00002044-00002104       .text modeDeleteInit__9daOship_cFv */
void daOship_c::modeDeleteInit() {
    /* Nonmatching */
}

/* 00002104-00002414       .text modeDelete__9daOship_cFv */
void daOship_c::modeDelete() {
    /* Nonmatching */
}

/* 00002414-0000263C       .text modeProc__9daOship_cFQ29daOship_c6Proc_ei */
void daOship_c::modeProc(daOship_c::Proc_e, int) {
    /* Nonmatching */
}

/* 0000263C-00002AD4       .text _execute__9daOship_cFv */
bool daOship_c::_execute() {
    /* Nonmatching */
}

/* 00002AD4-00002B54       .text _draw__9daOship_cFv */
bool daOship_c::_draw() {
    /* Nonmatching */
}

/* 00002B54-00002DFC       .text createInit__9daOship_cFv */
void daOship_c::createInit() {
    /* Nonmatching */
}

/* 00002DFC-00002F44       .text _createHeap__9daOship_cFv */
void daOship_c::_createHeap() {
    /* Nonmatching */
}

/* 00002F44-00002F90       .text getArg__9daOship_cFv */
void daOship_c::getArg() {
    /* Nonmatching */
}

/* 00002F90-000030EC       .text _create__9daOship_cFv */
cPhs_State daOship_c::_create() {
    /* Nonmatching */
}

/* 00003E78-00003F20       .text _delete__9daOship_cFv */
bool daOship_c::_delete() {
    /* Nonmatching */
}

/* 00003F20-00003F40       .text daOshipCreate__FPv */
static cPhs_State daOshipCreate(void* i_this) {
    return ((daOship_c*)i_this)->_create();
}

/* 00003F40-00003F64       .text daOshipDelete__FPv */
static BOOL daOshipDelete(void* i_this) {
    return ((daOship_c*)i_this)->_delete();
}

/* 00003F64-00003F88       .text daOshipExecute__FPv */
static BOOL daOshipExecute(void*) {
    /* Nonmatching */
}

/* 00003F88-00003FAC       .text daOshipDraw__FPv */
static BOOL daOshipDraw(void* i_this) {
    return ((daOship_c*)i_this)->_draw();
}

/* 00003FAC-00003FB4       .text daOshipIsDelete__FPv */
static BOOL daOshipIsDelete(void*) {
    return TRUE;
}

static actor_method_class daOshipMethodTable = {
    (process_method_func)daOshipCreate,
    (process_method_func)daOshipDelete,
    (process_method_func)daOshipExecute,
    (process_method_func)daOshipIsDelete,
    (process_method_func)daOshipDraw,
};

actor_process_profile_definition g_profile_OSHIP = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_OSHIP,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daOship_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_OSHIP,
    /* Actor SubMtd */ &daOshipMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
