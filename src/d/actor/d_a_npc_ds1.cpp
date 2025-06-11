/**
 * d_a_npc_ds1.cpp
 * NPC - Doc Bandam (Windfall Potion Shop shopkeeper)
 */

#include "d/actor/d_a_npc_ds1.h"
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


/* 000000EC-00000108       .text __ct__20daNpc_Ds1_childHIO_cFv */
daNpc_Ds1_childHIO_c::daNpc_Ds1_childHIO_c() {
    /* Nonmatching */
}

/* 00000108-00000194       .text daNpc_Ds1_checkCreateDrugChuchu__FUc */
void daNpc_Ds1_checkCreateDrugChuchu(unsigned char) {
    /* Nonmatching */
}

/* 00000194-00000298       .text __ct__15daNpc_Ds1_HIO_cFv */
daNpc_Ds1_HIO_c::daNpc_Ds1_HIO_c() {
    /* Nonmatching */
}

/* 000002F8-00000318       .text daNpc_Ds1_XyEventCB__FPvi */
static s16 daNpc_Ds1_XyEventCB(void*, int) {
    /* Nonmatching */
}

/* 00000318-00000550       .text XyEventCB__11daNpc_Ds1_cFi */
void daNpc_Ds1_c::XyEventCB(int) {
    /* Nonmatching */
}

/* 00000550-00000718       .text nodeCallBack_Ds__FP7J3DNodei */
static BOOL nodeCallBack_Ds(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000718-00000824       .text initTexPatternAnm__11daNpc_Ds1_cFb */
void daNpc_Ds1_c::initTexPatternAnm(bool) {
    /* Nonmatching */
}

/* 00000824-000008B0       .text playTexPatternAnm__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::playTexPatternAnm() {
    /* Nonmatching */
}

/* 000008B0-000009A8       .text setAnm__11daNpc_Ds1_cFScf */
void daNpc_Ds1_c::setAnm(signed char, float) {
    /* Nonmatching */
}

/* 000009A8-000009EC       .text setTexAnm__11daNpc_Ds1_cFSc */
void daNpc_Ds1_c::setTexAnm(signed char) {
    /* Nonmatching */
}

/* 000009EC-00000CAC       .text setAnmFromMsgTag__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::setAnmFromMsgTag() {
    /* Nonmatching */
}

/* 00000CAC-00000DB0       .text chkAttention__11daNpc_Ds1_cF4cXyzs */
void daNpc_Ds1_c::chkAttention(cXyz, short) {
    /* Nonmatching */
}

/* 00000DB0-00000EAC       .text eventOrder__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::eventOrder() {
    /* Nonmatching */
}

/* 00000EAC-000011F8       .text checkOrder__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::checkOrder() {
    /* Nonmatching */
}

/* 000011F8-00001698       .text next_msgStatus__11daNpc_Ds1_cFPUl */
void daNpc_Ds1_c::next_msgStatus(unsigned long*) {
    /* Nonmatching */
}

/* 00001698-00001794       .text getMsg__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::getMsg() {
    /* Nonmatching */
}

/* 00001794-00001850       .text setCollision__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::setCollision() {
    /* Nonmatching */
}

/* 00001850-0000185C       .text talkInit__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::talkInit() {
    /* Nonmatching */
}

/* 0000185C-00001884       .text daNpc_Ds1_shopMsgCheck__FUl */
void daNpc_Ds1_shopMsgCheck(unsigned long) {
    /* Nonmatching */
}

/* 00001884-000018AC       .text daNpc_Ds1_shopStickMoveMsgCheck__FUl */
void daNpc_Ds1_shopStickMoveMsgCheck(unsigned long) {
    /* Nonmatching */
}

/* 000018AC-00001B04       .text normal_talk__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::normal_talk() {
    /* Nonmatching */
}

/* 00001B04-00001C4C       .text shop_talk__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::shop_talk() {
    /* Nonmatching */
}

/* 00001C4C-00001E84       .text talk__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::talk() {
    /* Nonmatching */
}

/* 00001E84-00002158       .text CreateInit__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::CreateInit() {
    /* Nonmatching */
}

/* 00002158-000021A8       .text setAttention__11daNpc_Ds1_cFb */
void daNpc_Ds1_c::setAttention(bool) {
    /* Nonmatching */
}

/* 000021A8-00002524       .text lookBack__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::lookBack() {
    /* Nonmatching */
}

/* 00002524-00002578       .text wait01__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::wait01() {
    /* Nonmatching */
}

/* 00002578-00002760       .text talk01__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::talk01() {
    /* Nonmatching */
}

/* 00002760-00002A04       .text getdemo_action__11daNpc_Ds1_cFPv */
void daNpc_Ds1_c::getdemo_action(void*) {
    /* Nonmatching */
}

/* 00002A04-00002BD0       .text privateCut__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::privateCut() {
    /* Nonmatching */
}

/* 00002BD0-00002E00       .text evn_setAnm_init__11daNpc_Ds1_cFi */
void daNpc_Ds1_c::evn_setAnm_init(int) {
    /* Nonmatching */
}

/* 00002E00-000030A0       .text evn_Anm__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::evn_Anm() {
    /* Nonmatching */
}

/* 000030A0-00003168       .text evn_talk_init__11daNpc_Ds1_cFi */
void daNpc_Ds1_c::evn_talk_init(int) {
    /* Nonmatching */
}

/* 00003168-000031D0       .text evn_continue_talk_init__11daNpc_Ds1_cFi */
void daNpc_Ds1_c::evn_continue_talk_init(int) {
    /* Nonmatching */
}

/* 000031D0-000033AC       .text evn_talk__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::evn_talk() {
    /* Nonmatching */
}

/* 000033AC-00003478       .text evn_jnt_lock_init__11daNpc_Ds1_cFi */
void daNpc_Ds1_c::evn_jnt_lock_init(int) {
    /* Nonmatching */
}

/* 00003478-0000350C       .text evn_player_hide_init__11daNpc_Ds1_cFi */
void daNpc_Ds1_c::evn_player_hide_init(int) {
    /* Nonmatching */
}

/* 0000350C-000035B8       .text evn_head_swing_init__11daNpc_Ds1_cFi */
void daNpc_Ds1_c::evn_head_swing_init(int) {
    /* Nonmatching */
}

/* 000035B8-0000361C       .text evn_ItemModel_init__11daNpc_Ds1_cFi */
void daNpc_Ds1_c::evn_ItemModel_init(int) {
    /* Nonmatching */
}

/* 0000361C-000036D4       .text evn_move_pos_init__11daNpc_Ds1_cFi */
void daNpc_Ds1_c::evn_move_pos_init(int) {
    /* Nonmatching */
}

/* 000036D4-000037F0       .text evn_move_pos__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::evn_move_pos() {
    /* Nonmatching */
}

/* 000037F0-000038F4       .text evn_init_pos_init__11daNpc_Ds1_cFi */
void daNpc_Ds1_c::evn_init_pos_init(int) {
    /* Nonmatching */
}

/* 000038F4-00003AF8       .text event_action__11daNpc_Ds1_cFPv */
void daNpc_Ds1_c::event_action(void*) {
    /* Nonmatching */
}

/* 00003AF8-00003BF0       .text wait_action__11daNpc_Ds1_cFPv */
void daNpc_Ds1_c::wait_action(void*) {
    /* Nonmatching */
}

/* 00003BF0-00003C0C       .text dummy_action__11daNpc_Ds1_cFPv */
void daNpc_Ds1_c::dummy_action(void*) {
    /* Nonmatching */
}

/* 00003C0C-00003EE4       .text RoomEffectSet__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::RoomEffectSet() {
    /* Nonmatching */
}

/* 00003EE4-00003F20       .text RoomEffectDelete__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::RoomEffectDelete() {
    /* Nonmatching */
}

/* 00003F20-000041D0       .text _draw__11daNpc_Ds1_cFv */
BOOL daNpc_Ds1_c::_draw() {
    /* Nonmatching */
}

/* 000041D0-00004554       .text _execute__11daNpc_Ds1_cFv */
BOOL daNpc_Ds1_c::_execute() {
    /* Nonmatching */
}

/* 00004554-0000465C       .text _delete__11daNpc_Ds1_cFv */
BOOL daNpc_Ds1_c::_delete() {
    /* Nonmatching */
}

/* 0000465C-0000467C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 0000467C-000047BC       .text _create__11daNpc_Ds1_cFv */
cPhs_State daNpc_Ds1_c::_create() {
    /* Nonmatching */
}

/* 00004E08-000052D4       .text CreateHeap__11daNpc_Ds1_cFv */
void daNpc_Ds1_c::CreateHeap() {
    /* Nonmatching */
}

/* 000052D4-000052F4       .text daNpc_Ds1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Ds1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Ds1_c*)i_this)->_create();
}

/* 000052F4-00005314       .text daNpc_Ds1_Delete__FP11daNpc_Ds1_c */
static BOOL daNpc_Ds1_Delete(daNpc_Ds1_c* i_this) {
    return ((daNpc_Ds1_c*)i_this)->_delete();
}

/* 00005314-00005334       .text daNpc_Ds1_Execute__FP11daNpc_Ds1_c */
static BOOL daNpc_Ds1_Execute(daNpc_Ds1_c* i_this) {
    return ((daNpc_Ds1_c*)i_this)->_execute();
}

/* 00005334-00005354       .text daNpc_Ds1_Draw__FP11daNpc_Ds1_c */
static BOOL daNpc_Ds1_Draw(daNpc_Ds1_c* i_this) {
    return ((daNpc_Ds1_c*)i_this)->_draw();
}

/* 00005354-0000535C       .text daNpc_Ds1_IsDelete__FP11daNpc_Ds1_c */
static BOOL daNpc_Ds1_IsDelete(daNpc_Ds1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Ds1_Method = {
    (process_method_func)daNpc_Ds1_Create,
    (process_method_func)daNpc_Ds1_Delete,
    (process_method_func)daNpc_Ds1_Execute,
    (process_method_func)daNpc_Ds1_IsDelete,
    (process_method_func)daNpc_Ds1_Draw,
};

actor_process_profile_definition g_profile_NPC_DS1 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_DS1,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Ds1_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_DS1,
    /* Actor SubMtd */ &l_daNpc_Ds1_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_12_e,
};
