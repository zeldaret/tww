/**
 * d_a_gy.cpp
 * Enemy - Gyorg
 */

#include "d/actor/d_a_gy.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

static dCcD_SrcSph l_sph_head_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_UNK800,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_GrpAll_e,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
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
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 180.0f,
    },
};


static dCcD_SrcSph l_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_GrpAll_e,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
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
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 180.0f,
    },
};


static dCcD_SrcCps l_cps_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_GrpAll_e,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
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
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCpsS
    {
        /* Start  */ 0.0f, 0.0f, 0.0f,
        /* End    */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 60.0f,
    },
};


/* 000000EC-000003CC       .text __ct__10daGy_HIO_cFv */
daGy_HIO_c::daGy_HIO_c() {
    /* Nonmatching */
}

/* 00000450-0000049C       .text nodeControl_CB__FP7J3DNodei */
static BOOL nodeControl_CB(J3DNode*, int) {
    /* Nonmatching */
}

/* 0000049C-00000888       .text _nodeControl__6daGy_cFP7J3DNodeP8J3DModel */
void daGy_c::_nodeControl(J3DNode*, J3DModel*) {
    /* Nonmatching */
}

/* 00000888-000008A8       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000008A8-00000AAC       .text _createHeap__6daGy_cFv */
void daGy_c::_createHeap() {
    /* Nonmatching */
}

/* 00000AAC-00000C30       .text setMtx__6daGy_cFv */
void daGy_c::setMtx() {
    /* Nonmatching */
}

/* 00000C30-00000C7C       .text setAnm__6daGy_cFv */
void daGy_c::setAnm() {
    /* Nonmatching */
}

/* 00000C7C-00000E74       .text setAtCollision__6daGy_cFv */
void daGy_c::setAtCollision() {
    /* Nonmatching */
}

/* 00000E74-00000F3C       .text setCollision__6daGy_cFv */
void daGy_c::setCollision() {
    /* Nonmatching */
}

/* 00000F3C-00000FC4       .text setAimSpeedF__6daGy_cFv */
void daGy_c::setAimSpeedF() {
    /* Nonmatching */
}

/* 00000FC4-00000FDC       .text modeDiveInit__6daGy_cFv */
void daGy_c::modeDiveInit() {
    /* Nonmatching */
}

/* 00000FDC-000012DC       .text modeDive__6daGy_cFv */
void daGy_c::modeDive() {
    /* Nonmatching */
}

/* 000012DC-0000141C       .text modeCircleInit__6daGy_cFv */
void daGy_c::modeCircleInit() {
    /* Nonmatching */
}

/* 0000141C-000016E4       .text modeCircle__6daGy_cFv */
void daGy_c::modeCircle() {
    /* Nonmatching */
}

/* 000016E4-00001788       .text modeWithCircleInit__6daGy_cFv */
void daGy_c::modeWithCircleInit() {
    /* Nonmatching */
}

/* 00001788-000019AC       .text modeWithCircle__6daGy_cFv */
void daGy_c::modeWithCircle() {
    /* Nonmatching */
}

/* 000019AC-00001A14       .text modeAttackInit__6daGy_cFv */
void daGy_c::modeAttackInit() {
    /* Nonmatching */
}

/* 00001A14-00001A74       .text modeWithAttackInit__6daGy_cFv */
void daGy_c::modeWithAttackInit() {
    /* Nonmatching */
}

/* 00001A74-00001D60       .text modeWithAttack__6daGy_cFv */
void daGy_c::modeWithAttack() {
    /* Nonmatching */
}

/* 00001D60-00001F20       .text modeAttack__6daGy_cFv */
void daGy_c::modeAttack() {
    /* Nonmatching */
}

/* 00001F20-00001F40       .text modeAttackPlayerInit__6daGy_cFv */
void daGy_c::modeAttackPlayerInit() {
    /* Nonmatching */
}

/* 00001F40-000022F8       .text modeAttackPlayer__6daGy_cFv */
void daGy_c::modeAttackPlayer() {
    /* Nonmatching */
}

/* 000022F8-00002400       .text modeAttackBackInit__6daGy_cFv */
void daGy_c::modeAttackBackInit() {
    /* Nonmatching */
}

/* 00002400-00002560       .text modeAttackBack__6daGy_cFv */
void daGy_c::modeAttackBack() {
    /* Nonmatching */
}

/* 00002560-000025F0       .text modeDamageInit__6daGy_cFv */
void daGy_c::modeDamageInit() {
    /* Nonmatching */
}

/* 000025F0-00002754       .text modeDamage__6daGy_cFv */
void daGy_c::modeDamage() {
    /* Nonmatching */
}

/* 00002754-000028B8       .text modeDeleteInit__6daGy_cFv */
void daGy_c::modeDeleteInit() {
    /* Nonmatching */
}

/* 000028B8-00002998       .text modeDelete__6daGy_cFv */
void daGy_c::modeDelete() {
    /* Nonmatching */
}

/* 00002998-00002A70       .text modeDeleteBombInit__6daGy_cFv */
void daGy_c::modeDeleteBombInit() {
    /* Nonmatching */
}

/* 00002A70-00002CBC       .text modeDeleteBomb__6daGy_cFv */
void daGy_c::modeDeleteBomb() {
    /* Nonmatching */
}

/* 00002CBC-00002E24       .text modeProcCall__6daGy_cFv */
void daGy_c::modeProcCall() {
    /* Nonmatching */
}

/* 00002E24-00003004       .text createWave__6daGy_cFv */
void daGy_c::createWave() {
    /* Nonmatching */
}

/* 00003004-00003268       .text setWave__6daGy_cFv */
void daGy_c::setWave() {
    /* Nonmatching */
}

/* 00003268-000032E4       .text lineCheck__6daGy_cFP4cXyzP4cXyz */
void daGy_c::lineCheck(cXyz*, cXyz*) {
    /* Nonmatching */
}

/* 000032E4-000038EC       .text checkTgHit__6daGy_cFv */
void daGy_c::checkTgHit() {
    /* Nonmatching */
}

/* 000038EC-000039AC       .text getWaterY__6daGy_cFv */
void daGy_c::getWaterY() {
    /* Nonmatching */
}

/* 000039AC-00004264       .text _execute__6daGy_cFv */
bool daGy_c::_execute() {
    /* Nonmatching */
}

/* 00004264-00004560       .text drawDebug__6daGy_cFv */
void daGy_c::drawDebug() {
    /* Nonmatching */
}

/* 00004560-000046C8       .text _draw__6daGy_cFv */
bool daGy_c::_draw() {
    /* Nonmatching */
}

/* 000046C8-00004920       .text createInit__6daGy_cFv */
void daGy_c::createInit() {
    /* Nonmatching */
}

/* 00004920-00004A80       .text _create__6daGy_cFv */
cPhs_State daGy_c::_create() {
    /* Nonmatching */
}

/* 00005A80-00005AD4       .text _delete__6daGy_cFv */
bool daGy_c::_delete() {
    /* Nonmatching */
}

/* 00005AD4-00005AF4       .text daGyCreate__FPv */
static s32 daGyCreate(void* i_this) {
    return ((daGy_c*)i_this)->_create();
}

/* 00005AF4-00005B18       .text daGyDelete__FPv */
static BOOL daGyDelete(void* i_this) {
    return ((daGy_c*)i_this)->_delete();
}

/* 00005B18-00005B3C       .text daGyExecute__FPv */
static BOOL daGyExecute(void* i_this) {
    return ((daGy_c*)i_this)->_execute();
}

/* 00005B3C-00005B60       .text daGyDraw__FPv */
static BOOL daGyDraw(void* i_this) {
    return ((daGy_c*)i_this)->_draw();
}

/* 00005B60-00005B68       .text daGyIsDelete__FPv */
static BOOL daGyIsDelete(void*) {
    return TRUE;
}

static actor_method_class daGyMethodTable = {
    (process_method_func)daGyCreate,
    (process_method_func)daGyDelete,
    (process_method_func)daGyExecute,
    (process_method_func)daGyIsDelete,
    (process_method_func)daGyDraw,
};

actor_process_profile_definition g_profile_GY = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_GY,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daGy_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_GY,
    /* Actor SubMtd */ &daGyMethodTable,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_4_e,
};
