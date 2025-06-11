/**
 * d_a_canon.cpp
 * Cannon Minigame
 */

#include "d/actor/d_a_canon.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

static dCcD_SrcCyl canon_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 75.0f,
        /* Height */ 50.0f,
    },
};


static dCcD_SrcCyl canon_cyl2_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_BOMB,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsEnemy_e | cCcD_AtSPrm_VsOther_e,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 300.0f,
        /* Height */ 500.0f,
    },
};


/* 000000EC-000002C8       .text set_mtx__9daCanon_cFv */
void daCanon_c::set_mtx() {
    /* Nonmatching */
}

/* 000002C8-00000340       .text bul_set_mtx__9daCanon_cFP4cXyz */
void daCanon_c::bul_set_mtx(cXyz*) {
    /* Nonmatching */
}

/* 00000340-00000448       .text getGridPos__9daCanon_cFii */
void daCanon_c::getGridPos(int, int) {
    /* Nonmatching */
}

/* 00000448-00000554       .text getBulEndPos__9daCanon_cFss */
void daCanon_c::getBulEndPos(short, short) {
    /* Nonmatching */
}

/* 00000554-000005A0       .text createCheck__9daCanon_cFiii */
void daCanon_c::createCheck(int, int, int) {
    /* Nonmatching */
}

/* 000005A0-00000628       .text daCanon_nodeCallBack__FP7J3DNodei */
static BOOL daCanon_nodeCallBack(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000628-0000063C       .text target_createCB__FPv */
void target_createCB(void*) {
    /* Nonmatching */
}

/* 0000063C-0000074C       .text createTargetObj__9daCanon_cFv */
void daCanon_c::createTargetObj() {
    /* Nonmatching */
}

/* 0000074C-000007F4       .text daCanon_BreakTarget__FPvPv */
void daCanon_BreakTarget(void*, void*) {
    /* Nonmatching */
}

/* 000007F4-00000820       .text breakAllObj__9daCanon_cFv */
void daCanon_c::breakAllObj() {
    /* Nonmatching */
}

/* 00000820-00000A8C       .text makeFireEffect__9daCanon_cFR4cXyzR5csXyzi */
void daCanon_c::makeFireEffect(cXyz&, csXyz&, int) {
    /* Nonmatching */
}

/* 00000A8C-00000AB8       .text wait_proc_init__9daCanon_cFv */
void daCanon_c::wait_proc_init() {
    /* Nonmatching */
}

/* 00000AB8-00000D14       .text wait_proc__9daCanon_cFv */
void daCanon_c::wait_proc() {
    /* Nonmatching */
}

/* 00000D14-00000DD4       .text game_start_proc_init__9daCanon_cFv */
void daCanon_c::game_start_proc_init() {
    /* Nonmatching */
}

/* 00000DD4-00000E08       .text game_start_proc__9daCanon_cFv */
void daCanon_c::game_start_proc() {
    /* Nonmatching */
}

/* 00000E08-00000E2C       .text game_proc_init__9daCanon_cFv */
void daCanon_c::game_proc_init() {
    /* Nonmatching */
}

/* 00000E2C-00000FA0       .text game_proc__9daCanon_cFv */
void daCanon_c::game_proc() {
    /* Nonmatching */
}

/* 00000FA0-00001074       .text fire_proc_init__9daCanon_cFv */
void daCanon_c::fire_proc_init() {
    /* Nonmatching */
}

/* 00001074-000013AC       .text fire_proc__9daCanon_cFv */
void daCanon_c::fire_proc() {
    /* Nonmatching */
}

/* 000013AC-00001654       .text pause_proc_init__9daCanon_cFv */
void daCanon_c::pause_proc_init() {
    /* Nonmatching */
}

/* 00001654-000016A8       .text pause_proc__9daCanon_cFv */
void daCanon_c::pause_proc() {
    /* Nonmatching */
}

/* 000016A8-00001714       .text end_proc_init__9daCanon_cFv */
void daCanon_c::end_proc_init() {
    /* Nonmatching */
}

/* 00001714-00001814       .text end_proc__9daCanon_cFv */
void daCanon_c::end_proc() {
    /* Nonmatching */
}

/* 00001814-00001A18       .text PadMove__9daCanon_cFv */
void daCanon_c::PadMove() {
    /* Nonmatching */
}

/* 00001A18-00001A38       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00001A38-00001E04       .text CreateHeap__9daCanon_cFv */
void daCanon_c::CreateHeap() {
    /* Nonmatching */
}

/* 00001E4C-00002074       .text GameInfo2DDraw__9daCanon_cFv */
void daCanon_c::GameInfo2DDraw() {
    /* Nonmatching */
}

/* 00002074-00002094       .text daCanonCreate__FPv */
static s32 daCanonCreate(void* i_this) {
    return ((daCanon_c*)i_this)->_create();
}

/* 00002094-000023C0       .text _create__9daCanon_cFv */
cPhs_State daCanon_c::_create() {
    /* Nonmatching */
}

/* 00002578-00002600       .text daCanonDelete__FPv */
static BOOL daCanonDelete(void*) {
    /* Nonmatching */
}

/* 00002600-0000274C       .text daCanonExecute__FPv */
static BOOL daCanonExecute(void*) {
    /* Nonmatching */
}

/* 0000274C-0000283C       .text daCanonDraw__FPv */
static BOOL daCanonDraw(void*) {
    /* Nonmatching */
}

/* 0000283C-00002844       .text daCanonIsDelete__FPv */
static BOOL daCanonIsDelete(void*) {
    return TRUE;
}

static actor_method_class daCanonMethodTable = {
    (process_method_func)daCanonCreate,
    (process_method_func)daCanonDelete,
    (process_method_func)daCanonExecute,
    (process_method_func)daCanonIsDelete,
    (process_method_func)daCanonDraw,
};

actor_process_profile_definition g_profile_Canon = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Canon,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daCanon_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Canon,
    /* Actor SubMtd */ &daCanonMethodTable,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
