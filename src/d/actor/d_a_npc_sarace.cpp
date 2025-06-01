/**
 * d_a_npc_sarace.cpp
 * NPC - Loot the Sailor (Boating Course)
 */

#include "d/actor/d_a_npc_sarace.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
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
        /* Radius */ 30.0f,
        /* Height */ 80.0f,
    },
};


/* 000000EC-00000198       .text __ct__18daNpc_Sarace_HIO_cFv */
daNpc_Sarace_HIO_c::daNpc_Sarace_HIO_c() {
    /* Nonmatching */
}

/* 00000198-00000328       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000364-00000478       .text initTexPatternAnm__14daNpc_Sarace_cFb */
void daNpc_Sarace_c::initTexPatternAnm(bool) {
    /* Nonmatching */
}

/* 00000478-00000504       .text playTexPatternAnm__14daNpc_Sarace_cFv */
void daNpc_Sarace_c::playTexPatternAnm() {
    /* Nonmatching */
}

/* 00000504-0000060C       .text setAnm__14daNpc_Sarace_cFScf */
void daNpc_Sarace_c::setAnm(signed char, float) {
    /* Nonmatching */
}

/* 0000060C-00000760       .text chkAttention__14daNpc_Sarace_cF4cXyzs */
void daNpc_Sarace_c::chkAttention(cXyz, short) {
    /* Nonmatching */
}

/* 00000760-000007D8       .text eventOrder__14daNpc_Sarace_cFv */
void daNpc_Sarace_c::eventOrder() {
    /* Nonmatching */
}

/* 000007D8-000008E8       .text checkOrder__14daNpc_Sarace_cFv */
void daNpc_Sarace_c::checkOrder() {
    /* Nonmatching */
}

/* 000008E8-00000A6C       .text next_msgStatus__14daNpc_Sarace_cFPUl */
void daNpc_Sarace_c::next_msgStatus(unsigned long*) {
    /* Nonmatching */
}

/* 00000A6C-00000B50       .text getMsg__14daNpc_Sarace_cFv */
void daNpc_Sarace_c::getMsg() {
    /* Nonmatching */
}

/* 00000B50-00000BEC       .text anmAtr__14daNpc_Sarace_cFUs */
void daNpc_Sarace_c::anmAtr(unsigned short) {
    /* Nonmatching */
}

/* 00000BEC-00000E24       .text CreateInit__14daNpc_Sarace_cFv */
void daNpc_Sarace_c::CreateInit() {
    /* Nonmatching */
}

/* 00000E24-00000E68       .text setAttention__14daNpc_Sarace_cFv */
void daNpc_Sarace_c::setAttention() {
    /* Nonmatching */
}

/* 00000E68-00000FF4       .text lookBack__14daNpc_Sarace_cFv */
void daNpc_Sarace_c::lookBack() {
    /* Nonmatching */
}

/* 00000FF4-00001024       .text wait01__14daNpc_Sarace_cFv */
void daNpc_Sarace_c::wait01() {
    /* Nonmatching */
}

/* 00001024-000014B8       .text talk01__14daNpc_Sarace_cFv */
void daNpc_Sarace_c::talk01() {
    /* Nonmatching */
}

/* 000014B8-000014E0       .text dummy_action__14daNpc_Sarace_cFPv */
void daNpc_Sarace_c::dummy_action(void*) {
    /* Nonmatching */
}

/* 000014E0-000015BC       .text wait_action__14daNpc_Sarace_cFPv */
void daNpc_Sarace_c::wait_action(void*) {
    /* Nonmatching */
}

/* 000015BC-0000173C       .text event_endCheck_action__14daNpc_Sarace_cFPv */
void daNpc_Sarace_c::event_endCheck_action(void*) {
    /* Nonmatching */
}

/* 0000173C-000017E0       .text set_mtx__14daNpc_Sarace_cFv */
void daNpc_Sarace_c::set_mtx() {
    /* Nonmatching */
}

/* 000017E0-00001938       .text _draw__14daNpc_Sarace_cFv */
bool daNpc_Sarace_c::_draw() {
    /* Nonmatching */
}

/* 00001938-00001A68       .text _execute__14daNpc_Sarace_cFv */
bool daNpc_Sarace_c::_execute() {
    /* Nonmatching */
}

/* 00001A68-00001AE0       .text _delete__14daNpc_Sarace_cFv */
bool daNpc_Sarace_c::_delete() {
    /* Nonmatching */
}

/* 00001AE0-00001B00       .text CallbackCreateHeap__FP10fopAc_ac_c */
static BOOL CallbackCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00001B00-00001D1C       .text _create__14daNpc_Sarace_cFv */
cPhs_State daNpc_Sarace_c::_create() {
    /* Nonmatching */
}

/* 000020CC-00002498       .text CreateHeap__14daNpc_Sarace_cFv */
void daNpc_Sarace_c::CreateHeap() {
    /* Nonmatching */
}

/* 00002498-000024B8       .text daNpc_Sarace_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Sarace_Create(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000024B8-000024D8       .text daNpc_Sarace_Delete__FP14daNpc_Sarace_c */
static BOOL daNpc_Sarace_Delete(daNpc_Sarace_c*) {
    /* Nonmatching */
}

/* 000024D8-000024F8       .text daNpc_Sarace_Execute__FP14daNpc_Sarace_c */
static BOOL daNpc_Sarace_Execute(daNpc_Sarace_c*) {
    /* Nonmatching */
}

/* 000024F8-00002518       .text daNpc_Sarace_Draw__FP14daNpc_Sarace_c */
static BOOL daNpc_Sarace_Draw(daNpc_Sarace_c*) {
    /* Nonmatching */
}

/* 00002518-00002520       .text daNpc_Sarace_IsDelete__FP14daNpc_Sarace_c */
static BOOL daNpc_Sarace_IsDelete(daNpc_Sarace_c*) {
    /* Nonmatching */
}

static actor_method_class l_daNpc_Sarace_Method = {
    (process_method_func)daNpc_Sarace_Create,
    (process_method_func)daNpc_Sarace_Delete,
    (process_method_func)daNpc_Sarace_Execute,
    (process_method_func)daNpc_Sarace_IsDelete,
    (process_method_func)daNpc_Sarace_Draw,
};

actor_process_profile_definition g_profile_NPC_SARACE = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_SARACE,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Sarace_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_SARACE,
    /* Actor SubMtd */ &l_daNpc_Sarace_Method,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_12_e,
};
