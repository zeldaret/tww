/**
 * d_a_npc_p1.cpp
 * NPC - Gonzo, Senza, & Nudge
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_p1.h"
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
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 40.0f,
        /* Height */ 160.0f,
    }},
};


/* 000000EC-00000264       .text __ct__14daNpc_P1_HIO_cFv */
daNpc_P1_HIO_c::daNpc_P1_HIO_c() {
    /* Nonmatching */
}

/* 000002AC-000002BC       .text __ct__19daNpc_P1_childHIO_cFv */
daNpc_P1_childHIO_c::daNpc_P1_childHIO_c() {
    /* Nonmatching */
}

/* 000002BC-0000051C       .text setAnimFromMsg__10daNpc_P1_cFv */
void daNpc_P1_c::setAnimFromMsg() {
    /* Nonmatching */
}

/* 0000051C-00000AD0       .text setAnm__10daNpc_P1_cFif */
void daNpc_P1_c::setAnm(int, float) {
    /* Nonmatching */
}

/* 00000AD0-00000DEC       .text normalAction__10daNpc_P1_cFPv */
void daNpc_P1_c::normalAction(void*) {
    /* Nonmatching */
}

/* 00000DEC-00000F40       .text confuseAction__10daNpc_P1_cFPv */
void daNpc_P1_c::confuseAction(void*) {
    /* Nonmatching */
}

/* 00000F40-000013A4       .text talkAction__10daNpc_P1_cFPv */
void daNpc_P1_c::talkAction(void*) {
    /* Nonmatching */
}

/* 000013A4-000017A0       .text p1c_speakAction__10daNpc_P1_cFPv */
void daNpc_P1_c::p1c_speakAction(void*) {
    /* Nonmatching */
}

/* 000017A0-00001C60       .text speakAction__10daNpc_P1_cFPv */
void daNpc_P1_c::speakAction(void*) {
    /* Nonmatching */
}

/* 00001C60-00001CD4       .text explainAction__10daNpc_P1_cFPv */
void daNpc_P1_c::explainAction(void*) {
    /* Nonmatching */
}

/* 00001CD4-00001DE8       .text getNextMsgNo__10daNpc_P1_cFi */
void daNpc_P1_c::getNextMsgNo(int) {
    /* Nonmatching */
}

/* 00001DE8-00001E70       .text playTexPatternAnm__10daNpc_P1_cFv */
void daNpc_P1_c::playTexPatternAnm() {
    /* Nonmatching */
}

/* 00001E70-00002098       .text demo_end_init__10daNpc_P1_cFv */
void daNpc_P1_c::demo_end_init() {
    /* Nonmatching */
}

/* 00002098-000021E0       .text demo_move__10daNpc_P1_cFv */
void daNpc_P1_c::demo_move() {
    /* Nonmatching */
}

/* 000021E0-00002244       .text event_move__10daNpc_P1_cFv */
void daNpc_P1_c::event_move() {
    /* Nonmatching */
}

/* 00002244-000022E8       .text evn_setAnm_init__10daNpc_P1_cFi */
void daNpc_P1_c::evn_setAnm_init(int) {
    /* Nonmatching */
}

/* 000022E8-00002364       .text evn_talk_init__10daNpc_P1_cFi */
void daNpc_P1_c::evn_talk_init(int) {
    /* Nonmatching */
}

/* 00002364-00002464       .text evn_talk__10daNpc_P1_cFv */
void daNpc_P1_c::evn_talk() {
    /* Nonmatching */
}

/* 00002464-000027AC       .text minigameExplainCut__10daNpc_P1_cFv */
void daNpc_P1_c::minigameExplainCut() {
    /* Nonmatching */
}

/* 000027AC-00002920       .text privateCut__10daNpc_P1_cFv */
void daNpc_P1_c::privateCut() {
    /* Nonmatching */
}

/* 00002920-00002A7C       .text nodeCallBack1__FP7J3DNodei */
static BOOL nodeCallBack1(J3DNode*, int) {
    /* Nonmatching */
}

/* 00002A7C-00002A9C       .text daNpc_P1_Draw__FP10daNpc_P1_c */
static BOOL daNpc_P1_Draw(daNpc_P1_c* i_this) {
    return ((daNpc_P1_c*)i_this)->_draw();
}

/* 00002A9C-00002ABC       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00002ABC-00002B00       .text setAttentionPos__10daNpc_P1_cFP4cXyz */
void daNpc_P1_c::setAttentionPos(cXyz*) {
    /* Nonmatching */
}

/* 00002B00-00003484       .text _create__10daNpc_P1_cFv */
cPhs_State daNpc_P1_c::_create() {
    /* Nonmatching */
}

/* 00003834-00003D6C       .text CreateHeap__10daNpc_P1_cFv */
void daNpc_P1_c::CreateHeap() {
    /* Nonmatching */
}

/* 00003D6C-00003DF8       .text _delete__10daNpc_P1_cFv */
BOOL daNpc_P1_c::_delete() {
    /* Nonmatching */
}

/* 00003DF8-00003E70       .text getKajiID__10daNpc_P1_cFv */
void daNpc_P1_c::getKajiID() {
    /* Nonmatching */
}

/* 00003E70-000043CC       .text kaji_anm__10daNpc_P1_cFv */
void daNpc_P1_c::kaji_anm() {
    /* Nonmatching */
}

/* 000043CC-0000458C       .text _execute__10daNpc_P1_cFv */
BOOL daNpc_P1_c::_execute() {
    /* Nonmatching */
}

/* 0000458C-00004814       .text _draw__10daNpc_P1_cFv */
BOOL daNpc_P1_c::_draw() {
    /* Nonmatching */
}

/* 00004814-00004BA0       .text lookBack__10daNpc_P1_cFv */
void daNpc_P1_c::lookBack() {
    /* Nonmatching */
}

/* 00004BA0-00004BC4       .text daNpc_P1_Execute__FP10daNpc_P1_c */
static BOOL daNpc_P1_Execute(daNpc_P1_c* i_this) {
    ((daNpc_P1_c*)i_this)->_execute();
    return TRUE;
}

/* 00004BC4-00004BCC       .text daNpc_P1_IsDelete__FP10daNpc_P1_c */
static BOOL daNpc_P1_IsDelete(daNpc_P1_c*) {
    return TRUE;
}

/* 00004BCC-00004BEC       .text daNpc_P1_Delete__FP10daNpc_P1_c */
static BOOL daNpc_P1_Delete(daNpc_P1_c* i_this) {
    return ((daNpc_P1_c*)i_this)->_delete();
}

/* 00004BEC-00004C0C       .text daNpc_P1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_P1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_P1_c*)i_this)->_create();
}

static actor_method_class l_daNpc_P1_Method = {
    (process_method_func)daNpc_P1_Create,
    (process_method_func)daNpc_P1_Delete,
    (process_method_func)daNpc_P1_Execute,
    (process_method_func)daNpc_P1_IsDelete,
    (process_method_func)daNpc_P1_Draw,
};

actor_process_profile_definition g_profile_NPC_P1 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_P1,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_P1_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_P1,
    /* Actor SubMtd */ &l_daNpc_P1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
