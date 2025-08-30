/**
 * d_a_npc_bms1.cpp
 * NPC - Bomb-Master Cannon (Windfall Bomb Shop shopkeeper)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_bms1.h"
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
        /* Radius */ 30.0f,
        /* Height */ 80.0f,
    }},
};


/* 000000EC-00000108       .text __ct__21daNpc_Bms1_childHIO_cFv */
daNpc_Bms1_childHIO_c::daNpc_Bms1_childHIO_c() {
    /* Nonmatching */
}

/* 00000108-00000148       .text daNpc_Bms1_shopMsgCheck__FUl */
void daNpc_Bms1_shopMsgCheck(unsigned long) {
    /* Nonmatching */
}

/* 00000148-00000188       .text daNpc_Bms1_shopStickMoveMsgCheck__FUl */
void daNpc_Bms1_shopStickMoveMsgCheck(unsigned long) {
    /* Nonmatching */
}

/* 00000188-000002A0       .text __ct__16daNpc_Bms1_HIO_cFv */
daNpc_Bms1_HIO_c::daNpc_Bms1_HIO_c() {
    /* Nonmatching */
}

/* 00000300-000004C4       .text nodeCallBack_Bms__FP7J3DNodei */
static BOOL nodeCallBack_Bms(J3DNode*, int) {
    /* Nonmatching */
}

/* 000004C4-00000A00       .text nodeCallBack_BmsHead__FP7J3DNodei */
static BOOL nodeCallBack_BmsHead(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000A00-00000C4C       .text set_mtx__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::set_mtx() {
    /* Nonmatching */
}

/* 00000C4C-00000D54       .text initTexPatternAnm__12daNpc_Bms1_cFb */
void daNpc_Bms1_c::initTexPatternAnm(bool) {
    /* Nonmatching */
}

/* 00000D54-00000DE0       .text playTexPatternAnm__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::playTexPatternAnm() {
    /* Nonmatching */
}

/* 00000DE0-00000E78       .text setAnm__12daNpc_Bms1_cFScf */
void daNpc_Bms1_c::setAnm(signed char, float) {
    /* Nonmatching */
}

/* 00000E78-00000EBC       .text setTexAnm__12daNpc_Bms1_cFSc */
void daNpc_Bms1_c::setTexAnm(signed char) {
    /* Nonmatching */
}

/* 00000EBC-00001100       .text setAnmFromMsgTag__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::setAnmFromMsgTag() {
    /* Nonmatching */
}

/* 00001100-000011D8       .text chkAttention__12daNpc_Bms1_cF4cXyzs */
void daNpc_Bms1_c::chkAttention(cXyz, short) {
    /* Nonmatching */
}

/* 000011D8-00001278       .text eventOrder__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::eventOrder() {
    /* Nonmatching */
}

/* 00001278-000014AC       .text checkOrder__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::checkOrder() {
    /* Nonmatching */
}

/* 000014AC-000017FC       .text next_msgStatus__12daNpc_Bms1_cFPUl */
void daNpc_Bms1_c::next_msgStatus(unsigned long*) {
    /* Nonmatching */
}

/* 000017FC-00001860       .text getMsg__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::getMsg() {
    /* Nonmatching */
}

/* 00001860-0000191C       .text setCollision__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::setCollision() {
    /* Nonmatching */
}

/* 0000191C-00001928       .text talkInit__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::talkInit() {
    /* Nonmatching */
}

/* 00001928-00001A34       .text normal_talk__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::normal_talk() {
    /* Nonmatching */
}

/* 00001A34-00001B88       .text shop_talk__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::shop_talk() {
    /* Nonmatching */
}

/* 00001B88-00001D68       .text talk__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::talk() {
    /* Nonmatching */
}

/* 00001D68-00002104       .text CreateInit__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::CreateInit() {
    /* Nonmatching */
}

/* 00002104-00002144       .text setAttention__12daNpc_Bms1_cFb */
void daNpc_Bms1_c::setAttention(bool) {
    /* Nonmatching */
}

/* 00002144-000021F4       .text checkPlayerLanding__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::checkPlayerLanding() {
    /* Nonmatching */
}

/* 000021F4-00002424       .text lookBack__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::lookBack() {
    /* Nonmatching */
}

/* 00002424-0000249C       .text wait01__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::wait01() {
    /* Nonmatching */
}

/* 0000249C-00002590       .text talk01__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::talk01() {
    /* Nonmatching */
}

/* 00002590-00002764       .text getdemo_action__12daNpc_Bms1_cFPv */
void daNpc_Bms1_c::getdemo_action(void*) {
    /* Nonmatching */
}

/* 00002764-00002918       .text wait_action__12daNpc_Bms1_cFPv */
void daNpc_Bms1_c::wait_action(void*) {
    /* Nonmatching */
}

/* 00002918-00002A98       .text event_action__12daNpc_Bms1_cFPv */
void daNpc_Bms1_c::event_action(void*) {
    /* Nonmatching */
}

/* 00002A98-00002B94       .text evn_talk_init__12daNpc_Bms1_cFi */
void daNpc_Bms1_c::evn_talk_init(int) {
    /* Nonmatching */
}

/* 00002B94-00002BFC       .text evn_continue_talk_init__12daNpc_Bms1_cFi */
void daNpc_Bms1_c::evn_continue_talk_init(int) {
    /* Nonmatching */
}

/* 00002BFC-00002DD8       .text evn_talk__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::evn_talk() {
    /* Nonmatching */
}

/* 00002DD8-00002E30       .text evn_viblation_init__12daNpc_Bms1_cFi */
void daNpc_Bms1_c::evn_viblation_init(int) {
    /* Nonmatching */
}

/* 00002E30-00002E68       .text evn_head_swing_init__12daNpc_Bms1_cFi */
void daNpc_Bms1_c::evn_head_swing_init(int) {
    /* Nonmatching */
}

/* 00002E68-00002FBC       .text privateCut__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::privateCut() {
    /* Nonmatching */
}

/* 00002FBC-000030A4       .text demo_move__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::demo_move() {
    /* Nonmatching */
}

/* 000030A4-000030B0       .text demo_end_init__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::demo_end_init() {
    /* Nonmatching */
}

/* 000030B0-00003314       .text _draw__12daNpc_Bms1_cFv */
BOOL daNpc_Bms1_c::_draw() {
    /* Nonmatching */
}

/* 00003314-00003474       .text _execute__12daNpc_Bms1_cFv */
BOOL daNpc_Bms1_c::_execute() {
    /* Nonmatching */
}

/* 00003474-00003514       .text _delete__12daNpc_Bms1_cFv */
BOOL daNpc_Bms1_c::_delete() {
    /* Nonmatching */
}

/* 00003514-00003534       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00003534-00003718       .text _create__12daNpc_Bms1_cFv */
cPhs_State daNpc_Bms1_c::_create() {
    /* Nonmatching */
}

/* 00003CE8-000043B8       .text CreateHeap__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::CreateHeap() {
    /* Nonmatching */
}

/* 000043B8-000043D8       .text daNpc_Bms1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Bms1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Bms1_c*)i_this)->_create();
}

/* 000043D8-000043F8       .text daNpc_Bms1_Delete__FP12daNpc_Bms1_c */
static BOOL daNpc_Bms1_Delete(daNpc_Bms1_c* i_this) {
    return ((daNpc_Bms1_c*)i_this)->_delete();
}

/* 000043F8-00004418       .text daNpc_Bms1_Execute__FP12daNpc_Bms1_c */
static BOOL daNpc_Bms1_Execute(daNpc_Bms1_c* i_this) {
    return ((daNpc_Bms1_c*)i_this)->_execute();
}

/* 00004418-00004438       .text daNpc_Bms1_Draw__FP12daNpc_Bms1_c */
static BOOL daNpc_Bms1_Draw(daNpc_Bms1_c* i_this) {
    return ((daNpc_Bms1_c*)i_this)->_draw();
}

/* 00004438-00004440       .text daNpc_Bms1_IsDelete__FP12daNpc_Bms1_c */
static BOOL daNpc_Bms1_IsDelete(daNpc_Bms1_c*) {
    return TRUE;
}

// /* 000047AC-000047C8       .text setEyePos__12daNpc_Bms1_cF4cXyz */
// void daNpc_Bms1_c::setEyePos(cXyz) {
//     /* Nonmatching */
// }

// /* 000047C8-000047E4       .text setAttentionBasePos__12daNpc_Bms1_cF4cXyz */
// void daNpc_Bms1_c::setAttentionBasePos(cXyz) {
//     /* Nonmatching */
// }

// /* 00004820-00004900       .text getItemZoomPos__16ShopCam_action_cFf */
// void ShopCam_action_c::getItemZoomPos(float) {
//     /* Nonmatching */
// }

static actor_method_class l_daNpc_Bms1_Method = {
    (process_method_func)daNpc_Bms1_Create,
    (process_method_func)daNpc_Bms1_Delete,
    (process_method_func)daNpc_Bms1_Execute,
    (process_method_func)daNpc_Bms1_IsDelete,
    (process_method_func)daNpc_Bms1_Draw,
};

actor_process_profile_definition g_profile_NPC_BMS1 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_BMS1,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Bms1_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_BMS1,
    /* Actor SubMtd */ &l_daNpc_Bms1_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_12_e,
};
