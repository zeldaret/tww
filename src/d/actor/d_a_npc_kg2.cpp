/**
 * d_a_npc_kg2.cpp
 * NPC - Salvatore (Cannon Minigame)
 */

#include "d/actor/d_a_npc_kg2.h"
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


/* 000000EC-00000194       .text __ct__15daNpc_Kg2_HIO_cFv */
daNpc_Kg2_HIO_c::daNpc_Kg2_HIO_c() {
    /* Nonmatching */
}

/* 00000194-00000368       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode*, int) {
    /* Nonmatching */
}

/* 000003A4-0000048C       .text set_mtx__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::set_mtx() {
    /* Nonmatching */
}

/* 0000048C-000005A0       .text initTexPatternAnm__11daNpc_Kg2_cFb */
void daNpc_Kg2_c::initTexPatternAnm(bool) {
    /* Nonmatching */
}

/* 000005A0-000006EC       .text playTexPatternAnm__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::playTexPatternAnm() {
    /* Nonmatching */
}

/* 000006EC-00000838       .text setAnm__11daNpc_Kg2_cFScf */
void daNpc_Kg2_c::setAnm(signed char, float) {
    /* Nonmatching */
}

/* 00000838-000009E8       .text subAnm__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::subAnm() {
    /* Nonmatching */
}

/* 000009E8-00000B3C       .text chkAttention__11daNpc_Kg2_cF4cXyzs */
void daNpc_Kg2_c::chkAttention(cXyz, short) {
    /* Nonmatching */
}

/* 00000B3C-00000BC0       .text eventOrder__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::eventOrder() {
    /* Nonmatching */
}

/* 00000BC0-00000CC4       .text checkOrder__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::checkOrder() {
    /* Nonmatching */
}

/* 00000CC4-00000E38       .text getMsg__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::getMsg() {
    /* Nonmatching */
}

/* 00000E38-00001028       .text next_msgStatus__11daNpc_Kg2_cFPUl */
void daNpc_Kg2_c::next_msgStatus(unsigned long*) {
    /* Nonmatching */
}

/* 00001028-000012EC       .text anmAtr__11daNpc_Kg2_cFUs */
void daNpc_Kg2_c::anmAtr(unsigned short) {
    /* Nonmatching */
}

/* 000012EC-00001308       .text setAttention__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::setAttention() {
    /* Nonmatching */
}

/* 00001308-00001448       .text lookBack__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::lookBack() {
    /* Nonmatching */
}

/* 00001448-00001468       .text CallbackCreateHeap__FP10fopAc_ac_c */
static BOOL CallbackCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00001468-0000180C       .text CreateHeap__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::CreateHeap() {
    /* Nonmatching */
}

/* 0000180C-00001A9C       .text CreateInit__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::CreateInit() {
    /* Nonmatching */
}

/* 00001A9C-00001BDC       .text wait01__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::wait01() {
    /* Nonmatching */
}

/* 00001BDC-00001CA4       .text talk01__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::talk01() {
    /* Nonmatching */
}

/* 00001CA4-00001D88       .text evn_setAnm_init__11daNpc_Kg2_cFi */
void daNpc_Kg2_c::evn_setAnm_init(int) {
    /* Nonmatching */
}

/* 00001D88-00001E4C       .text evn_setAnm__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::evn_setAnm() {
    /* Nonmatching */
}

/* 00001E4C-00001F14       .text evn_jnt_lock_init__11daNpc_Kg2_cFi */
void daNpc_Kg2_c::evn_jnt_lock_init(int) {
    /* Nonmatching */
}

/* 00001F14-00001F88       .text evn_talk_init__11daNpc_Kg2_cFi */
void daNpc_Kg2_c::evn_talk_init(int) {
    /* Nonmatching */
}

/* 00001F88-00001FBC       .text evn_talk__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::evn_talk() {
    /* Nonmatching */
}

/* 00001FBC-00002070       .text evn_createItem_init__11daNpc_Kg2_cFi */
void daNpc_Kg2_c::evn_createItem_init(int) {
    /* Nonmatching */
}

/* 00002070-000021EC       .text privateCut__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::privateCut() {
    /* Nonmatching */
}

/* 000021EC-00002250       .text processMove__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::processMove() {
    /* Nonmatching */
}

/* 00002250-00002334       .text wait_action__11daNpc_Kg2_cFPv */
void daNpc_Kg2_c::wait_action(void*) {
    /* Nonmatching */
}

/* 00002334-00002590       .text event_wait_action__11daNpc_Kg2_cFPv */
void daNpc_Kg2_c::event_wait_action(void*) {
    /* Nonmatching */
}

/* 00002590-000027BC       .text _create__11daNpc_Kg2_cFv */
cPhs_State daNpc_Kg2_c::_create() {
    /* Nonmatching */
}

/* 00002B6C-00002BFC       .text _delete__11daNpc_Kg2_cFv */
bool daNpc_Kg2_c::_delete() {
    /* Nonmatching */
}

/* 00002BFC-00002D14       .text _execute__11daNpc_Kg2_cFv */
bool daNpc_Kg2_c::_execute() {
    /* Nonmatching */
}

/* 00002D14-00002E74       .text _draw__11daNpc_Kg2_cFv */
bool daNpc_Kg2_c::_draw() {
    /* Nonmatching */
}

/* 00002E74-00002E94       .text daNpc_Kg2_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Kg2_Create(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00002E94-00002EB4       .text daNpc_Kg2_Delete__FP11daNpc_Kg2_c */
static BOOL daNpc_Kg2_Delete(daNpc_Kg2_c*) {
    /* Nonmatching */
}

/* 00002EB4-00002ED4       .text daNpc_Kg2_Execute__FP11daNpc_Kg2_c */
static BOOL daNpc_Kg2_Execute(daNpc_Kg2_c*) {
    /* Nonmatching */
}

/* 00002ED4-00002EF4       .text daNpc_Kg2_Draw__FP11daNpc_Kg2_c */
static BOOL daNpc_Kg2_Draw(daNpc_Kg2_c*) {
    /* Nonmatching */
}

/* 00002EF4-00002EFC       .text daNpc_Kg2_IsDelete__FP11daNpc_Kg2_c */
static BOOL daNpc_Kg2_IsDelete(daNpc_Kg2_c*) {
    /* Nonmatching */
}

static actor_method_class l_daNpc_Kg2_Method = {
    (process_method_func)daNpc_Kg2_Create,
    (process_method_func)daNpc_Kg2_Delete,
    (process_method_func)daNpc_Kg2_Execute,
    (process_method_func)daNpc_Kg2_IsDelete,
    (process_method_func)daNpc_Kg2_Draw,
};

actor_process_profile_definition g_profile_NPC_KG2 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_KG2,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Kg2_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_KG2,
    /* Actor SubMtd */ &l_daNpc_Kg2_Method,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_12_e,
};
