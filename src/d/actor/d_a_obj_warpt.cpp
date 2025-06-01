/**
 * d_a_obj_warpt.cpp
 * Object - Warp pot
 */

#include "d/actor/d_a_obj_warpt.h"
#include "d/d_bg_w.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

const dCcD_SrcCyl daObj_Warpt_c::m_cyl_body_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_GrpAll_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsPlayer_e | cCcD_CoSPrm_VsOther_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 85.0f,
        /* Height */ 150.0f,
    },
};


const dCcD_SrcCyl daObj_Warpt_c::m_cyl_huta_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
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
        /* Radius */ 70.0f,
        /* Height */ 20.0f,
    },
};


/* 000000EC-00000190       .text __ct__17daObj_Warpt_HIO_cFv */
daObj_Warpt_HIO_c::daObj_Warpt_HIO_c() {
    /* Nonmatching */
}

/* 000001D8-000001F8       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000001F8-00000270       .text _createHeap__13daObj_Warpt_cFv */
void daObj_Warpt_c::_createHeap() {
    /* Nonmatching */
}

/* 00000270-00000488       .text createHutaHeap__13daObj_Warpt_cFv */
void daObj_Warpt_c::createHutaHeap() {
    /* Nonmatching */
}

/* 00000488-00000620       .text createBodyHeap__13daObj_Warpt_cFv */
void daObj_Warpt_c::createBodyHeap() {
    /* Nonmatching */
}

/* 00000620-00000648       .text ride_CB__FP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void ride_CB(dBgW*, fopAc_ac_c*, fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000648-00000750       .text _ride__13daObj_Warpt_cFP10fopAc_ac_c */
void daObj_Warpt_c::_ride(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000750-00000758       .text isHuta__13daObj_Warpt_cFv */
void daObj_Warpt_c::isHuta() {
    /* Nonmatching */
}

/* 00000758-00000784       .text isSp__13daObj_Warpt_cFv */
void daObj_Warpt_c::isSp() {
    /* Nonmatching */
}

/* 00000784-0000080C       .text isOtherHuta__13daObj_Warpt_cFv */
void daObj_Warpt_c::isOtherHuta() {
    /* Nonmatching */
}

/* 0000080C-00000864       .text isRealHuta__13daObj_Warpt_cFv */
void daObj_Warpt_c::isRealHuta() {
    /* Nonmatching */
}

/* 00000864-000008E8       .text warp__13daObj_Warpt_cFi */
void daObj_Warpt_c::warp(int) {
    /* Nonmatching */
}

/* 000008E8-00000968       .text onWarpBit__13daObj_Warpt_cFUc */
void daObj_Warpt_c::onWarpBit(unsigned char) {
    /* Nonmatching */
}

/* 00000968-000009D0       .text isWarpBit__13daObj_Warpt_cFUc */
void daObj_Warpt_c::isWarpBit(unsigned char) {
    /* Nonmatching */
}

/* 000009D0-00000BB8       .text setMtx__13daObj_Warpt_cFv */
void daObj_Warpt_c::setMtx() {
    /* Nonmatching */
}

/* 00000BB8-00000C3C       .text initCollision__13daObj_Warpt_cFv */
void daObj_Warpt_c::initCollision() {
    /* Nonmatching */
}

/* 00000C3C-00000CCC       .text setCollision__13daObj_Warpt_cFv */
void daObj_Warpt_c::setCollision() {
    /* Nonmatching */
}

/* 00000CCC-00000E90       .text breakHuta__13daObj_Warpt_cFi */
void daObj_Warpt_c::breakHuta(int) {
    /* Nonmatching */
}

/* 00000E90-00000F40       .text openHuta__13daObj_Warpt_cFv */
void daObj_Warpt_c::openHuta() {
    /* Nonmatching */
}

/* 00000F40-000010E0       .text checkHitSE__13daObj_Warpt_cFv */
void daObj_Warpt_c::checkHitSE() {
    /* Nonmatching */
}

/* 000010E0-00001178       .text modeOpenInit__13daObj_Warpt_cFv */
void daObj_Warpt_c::modeOpenInit() {
    /* Nonmatching */
}

/* 00001178-000011E8       .text modeOpen__13daObj_Warpt_cFv */
void daObj_Warpt_c::modeOpen() {
    /* Nonmatching */
}

/* 000011E8-00001258       .text modeCloseInit__13daObj_Warpt_cFv */
void daObj_Warpt_c::modeCloseInit() {
    /* Nonmatching */
}

/* 00001258-00001388       .text modeClose__13daObj_Warpt_cFv */
void daObj_Warpt_c::modeClose() {
    /* Nonmatching */
}

/* 00001388-00001400       .text modeBreakFireInit__13daObj_Warpt_cFv */
void daObj_Warpt_c::modeBreakFireInit() {
    /* Nonmatching */
}

/* 00001400-0000149C       .text modeBreakFire__13daObj_Warpt_cFv */
void daObj_Warpt_c::modeBreakFire() {
    /* Nonmatching */
}

/* 0000149C-000014A0       .text modeEventWarpInit__13daObj_Warpt_cFv */
void daObj_Warpt_c::modeEventWarpInit() {
    /* Nonmatching */
}

/* 000014A0-00001634       .text modeEventWarp__13daObj_Warpt_cFv */
void daObj_Warpt_c::modeEventWarp() {
    /* Nonmatching */
}

/* 00001634-000016A4       .text normalWarp__13daObj_Warpt_cFv */
void daObj_Warpt_c::normalWarp() {
    /* Nonmatching */
}

/* 000016A4-000017D8       .text spWarp__13daObj_Warpt_cFv */
void daObj_Warpt_c::spWarp() {
    /* Nonmatching */
}

/* 000017D8-000017DC       .text modeEventOpenInit__13daObj_Warpt_cFv */
void daObj_Warpt_c::modeEventOpenInit() {
    /* Nonmatching */
}

/* 000017DC-00001858       .text modeEventOpen__13daObj_Warpt_cFv */
void daObj_Warpt_c::modeEventOpen() {
    /* Nonmatching */
}

/* 00001858-000019D8       .text modeProc__13daObj_Warpt_cFQ213daObj_Warpt_c6Proc_ei */
void daObj_Warpt_c::modeProc(daObj_Warpt_c::Proc_e, int) {
    /* Nonmatching */
}

/* 000019D8-00001BCC       .text _execute__13daObj_Warpt_cFv */
bool daObj_Warpt_c::_execute() {
    /* Nonmatching */
}

/* 00001BCC-00001D7C       .text _draw__13daObj_Warpt_cFv */
bool daObj_Warpt_c::_draw() {
    /* Nonmatching */
}

/* 00001D7C-00001F30       .text getArg__13daObj_Warpt_cFv */
void daObj_Warpt_c::getArg() {
    /* Nonmatching */
}

/* 00001F30-0000215C       .text createInit__13daObj_Warpt_cFv */
void daObj_Warpt_c::createInit() {
    /* Nonmatching */
}

/* 0000215C-00002378       .text _create__13daObj_Warpt_cFv */
cPhs_State daObj_Warpt_c::_create() {
    /* Nonmatching */
}

/* 00002728-00002858       .text _delete__13daObj_Warpt_cFv */
bool daObj_Warpt_c::_delete() {
    /* Nonmatching */
}

/* 00002858-00002878       .text daObj_WarptCreate__FPv */
static s32 daObj_WarptCreate(void*) {
    /* Nonmatching */
}

/* 00002878-0000289C       .text daObj_WarptDelete__FPv */
static BOOL daObj_WarptDelete(void*) {
    /* Nonmatching */
}

/* 0000289C-000028C0       .text daObj_WarptExecute__FPv */
static BOOL daObj_WarptExecute(void*) {
    /* Nonmatching */
}

/* 000028C0-000028E4       .text daObj_WarptDraw__FPv */
static BOOL daObj_WarptDraw(void*) {
    /* Nonmatching */
}

/* 000028E4-000028EC       .text daObj_WarptIsDelete__FPv */
static BOOL daObj_WarptIsDelete(void*) {
    /* Nonmatching */
}

static actor_method_class daObj_WarptMethodTable = {
    (process_method_func)daObj_WarptCreate,
    (process_method_func)daObj_WarptDelete,
    (process_method_func)daObj_WarptExecute,
    (process_method_func)daObj_WarptIsDelete,
    (process_method_func)daObj_WarptDraw,
};

actor_process_profile_definition g_profile_OBJ_WARPT = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_OBJ_WARPT,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObj_Warpt_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_OBJ_WARPT,
    /* Actor SubMtd */ &daObj_WarptMethodTable,
    /* Status       */ 0x17 | fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
