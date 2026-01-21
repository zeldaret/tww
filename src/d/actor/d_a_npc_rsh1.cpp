/**
 * d_a_npc_rsh1.cpp
 * NPC - Zunari
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_rsh1.h"
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
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG,
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
        /* Radius */ 60.0f,
        /* Height */ 80.0f,
    }},
};

char daNpc_Rsh1_c::m_arcname[] = "Rsh";

static daNpc_Rsh1_HIO_c l_HIO;
static s32 l_msgId;
static s32 l_msg;

static cXyz l_in_chk_pos1_tbl[4] = {
    cXyz( 919.0f, 670.0f, -205111.0f),
    cXyz(1466.0f, 670.0f, -204723.0f),
    cXyz(1090.0f, 670.0f, -204173.0f),
    cXyz( 603.0f, 670.0f, -204461.0f)
};

static cXyz l_in_chk_pos2_tbl[4] = {
    cXyz(1466.0f, 670.0f, -204723.0f),
    cXyz(1700.0f, 670.0f, -204518.0f),
    cXyz(1423.0f, 670.0f, -204174.0f),
    cXyz(1125.0f, 670.0f, -204337.0f)
};

static void dummy() {
    strcmp(__FILE__, NULL);
    strcmp("m_head_tex_pattern != 0", NULL);
    strcmp("Halt", NULL);
}

/* 000000EC-0000021C       .text __ct__16daNpc_Rsh1_HIO_cFv */
daNpc_Rsh1_HIO_c::daNpc_Rsh1_HIO_c() {
    field_0x0C.m04 = -20.0;
    field_0x0C.mMaxHeadX = 0x200;
    field_0x0C.mMaxHeadY = 0x200;
    field_0x0C.mMaxBackboneX = 5000;
    field_0x0C.mMaxBackboneY = 6000;
    field_0x0C.mMinHeadX = -0x200;
    field_0x0C.mMinHeadY = -0x200;
    field_0x0C.mMinBackboneX = -5000;
    field_0x0C.mMinBackboneY = -6000;
    field_0x0C.mMaxTurnStep = 0x1000;
    field_0x0C.mMaxHeadTurnVel = 0x800;
    field_0x0C.mAttnYOffset = 80.0;
    field_0x0C.mMaxAttnAngleY = 0x4000;
    field_0x0C.m22 = 0;
    field_0x0C.mMaxAttnDistXZ = 400.0;
    field_0x34 = 1.0;
    field_0x38 = 0.9;
    field_0x3C = 0.5;
    field_0x40 = 40.0;
    field_0x44 = 30.0;
    field_0x48 = 7.5;
    field_0x4C = 1300.0;
    field_0x50 = 100.0;
    field_0x54 = 180.0;
    field_0x58 = 190.0;
    field_0x68 = 0;
    field_0x69 = 0;
    field_0x6A = 0;
    field_0x6B = 0;
    field_0x5C = 0;
    field_0x5D = 0;
    field_0x5E = 0;
    field_0x5F = 0;
    field_0x60 = 0;
    field_0x61 = 0;
    field_0x62 = 0;
    field_0x63 = 0;
    field_0x64 = 0;
    field_0x65 = 0;
    field_0x66 = 0;
    field_0x67 = 0;
    field_0x04 = -1;
    field_0x08 = -1;
}

daNpc_Rsh1_HIO_c::~daNpc_Rsh1_HIO_c() {}

/* 0000021C-0000045C       .text checkCreateInShopPlayer__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::checkCreateInShopPlayer() {
    /* Nonmatching */
}

/* 00000498-00000710       .text daNpc_Rsh1_checkRotenBaseTalkArea__Fv */
static void daNpc_Rsh1_checkRotenBaseTalkArea() {
    /* Nonmatching */
}

/* 00000710-000007A0       .text daNpc_Rsh1_countShop__Fv */
static void daNpc_Rsh1_countShop() {
    /* Nonmatching */
}

/* 000007A0-0000080C       .text daNpc_Rsh1_RotenItemNumInBag__Fv */
static void daNpc_Rsh1_RotenItemNumInBag() {
    /* Nonmatching */
}

/* 0000080C-0000084C       .text daNpc_Rsh1_shopMsgCheck__FUl */
static void daNpc_Rsh1_shopMsgCheck(unsigned long) {
    /* Nonmatching */
}

/* 0000084C-0000087C       .text daNpc_Rsh1_shopStickMoveMsgCheck__FUl */
static void daNpc_Rsh1_shopStickMoveMsgCheck(unsigned long) {
    /* Nonmatching */
}

/* 0000087C-00000A44       .text nodeCallBack_Rsh__FP7J3DNodei */
static BOOL nodeCallBack_Rsh(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000A44-00000B50       .text initTexPatternAnm__12daNpc_Rsh1_cFb */
BOOL daNpc_Rsh1_c::initTexPatternAnm(bool) {
    /* Nonmatching */
}

/* 00000B50-00000BDC       .text playTexPatternAnm__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::playTexPatternAnm() {
    /* Nonmatching */
}

/* 00000BDC-00000C64       .text setAnm__12daNpc_Rsh1_cFSc */
void daNpc_Rsh1_c::setAnm(signed char) {
    /* Nonmatching */
}

/* 00000C64-00000CA8       .text setTexAnm__12daNpc_Rsh1_cFSc */
void daNpc_Rsh1_c::setTexAnm(signed char) {
    /* Nonmatching */
}

/* 00000CA8-00000DDC       .text setAnmFromMsgTag__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::setAnmFromMsgTag() {
    /* Nonmatching */
}

/* 00000DDC-00000F50       .text chkAttention__12daNpc_Rsh1_cF4cXyzs */
void daNpc_Rsh1_c::chkAttention(cXyz, short) {
    /* Nonmatching */
}

/* 00000F50-00001038       .text eventOrder__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::eventOrder() {
    /* Nonmatching */
}

/* 00001038-0000126C       .text checkOrder__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::checkOrder() {
    /* Nonmatching */
}

/* 0000126C-00001650       .text next_msgStatus__12daNpc_Rsh1_cFPUl */
void daNpc_Rsh1_c::next_msgStatus(unsigned long*) {
    /* Nonmatching */
}

/* 00001650-00001808       .text getMsg__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::getMsg() {
    /* Nonmatching */
}

/* 00001808-000018EC       .text setCollision__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::setCollision() {
    /* Nonmatching */
}

/* 000018EC-000018F8       .text talkInit__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::talkInit() {
    field_0x961 = 0;
}

/* 000018F8-00001CB4       .text normal_talk__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::normal_talk() {
    /* Nonmatching */
}

/* 00001CB4-00001DE4       .text shop_talk__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::shop_talk() {
    /* Nonmatching */
}

/* 00001DE4-00001FE0       .text talk__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::talk() {
    /* Nonmatching */
}

/* 00001FE0-00002358       .text CreateInit__12daNpc_Rsh1_cFv */
BOOL daNpc_Rsh1_c::CreateInit() {
    /* Nonmatching */
}

/* 00002358-000023A8       .text daNpc_Rsh1_checkRotenItemGet__Fi */
static void daNpc_Rsh1_checkRotenItemGet(int) {
    /* Nonmatching */
}

/* 000023A8-00002568       .text createShopList__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::createShopList() {
    /* Nonmatching */
}

/* 00002568-000025C0       .text setAttention__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::setAttention() {
    /* Nonmatching */
}

/* 000025C0-00002868       .text lookBack__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::lookBack() {
    /* Nonmatching */
}

/* 00002868-00002930       .text pathGet__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::pathGet() {
    /* Nonmatching */
}

/* 00002930-00002B60       .text getAimShopPosIdx__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::getAimShopPosIdx() {
    /* Nonmatching */
}

/* 00002B60-00002C2C       .text shopPosMove__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::shopPosMove() {
    /* Nonmatching */
}

/* 00002C2C-00002E00       .text pathMove__12daNpc_Rsh1_cFPi */
void daNpc_Rsh1_c::pathMove(int*) {
    /* Nonmatching */
}

/* 00002E00-00002F5C       .text wait01__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::wait01() {
    /* Nonmatching */
}

/* 00002F5C-00003154       .text talk01__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::talk01() {
    /* Nonmatching */
}

/* 00003154-00003358       .text getdemo_action__12daNpc_Rsh1_cFPv */
void daNpc_Rsh1_c::getdemo_action(void*) {
    /* Nonmatching */
}

/* 00003358-00003424       .text wait_action__12daNpc_Rsh1_cFPv */
void daNpc_Rsh1_c::wait_action(void*) {
    /* Nonmatching */
}

/* 00003424-00003840       .text pl_shop_out_action__12daNpc_Rsh1_cFPv */
void daNpc_Rsh1_c::pl_shop_out_action(void*) {
    /* Nonmatching */
}

/* 00003840-000038A4       .text evn_setAnm_init__12daNpc_Rsh1_cFi */
void daNpc_Rsh1_c::evn_setAnm_init(int) {
    /* Nonmatching */
}

/* 000038A4-0000396C       .text evn_talk_init__12daNpc_Rsh1_cFi */
void daNpc_Rsh1_c::evn_talk_init(int) {
    /* Nonmatching */
}

/* 0000396C-000039D4       .text evn_continue_talk_init__12daNpc_Rsh1_cFi */
void daNpc_Rsh1_c::evn_continue_talk_init(int) {
    /* Nonmatching */
}

/* 000039D4-00003B04       .text evn_talk__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::evn_talk() {
    /* Nonmatching */
}

/* 00003B04-00003B88       .text evn_turn_init__12daNpc_Rsh1_cFi */
void daNpc_Rsh1_c::evn_turn_init(int) {
    /* Nonmatching */
}

/* 00003B88-00003C10       .text evn_turn__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::evn_turn() {
    /* Nonmatching */
}

/* 00003C10-00003D80       .text privateCut__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::privateCut() {
    /* Nonmatching */
}

/* 00003D80-00003EEC       .text event_action__12daNpc_Rsh1_cFPv */
void daNpc_Rsh1_c::event_action(void*) {
    /* Nonmatching */
}

/* 00003EEC-00003F08       .text dummy_action__12daNpc_Rsh1_cFPv */
bool daNpc_Rsh1_c::dummy_action(void* i_unusedP) {
    UNUSED(i_unusedP);
    if (field_0x960 == 0) {
        field_0x960++;
    }
    return true;
}

/* 00003F08-00004040       .text _draw__12daNpc_Rsh1_cFv */
BOOL daNpc_Rsh1_c::_draw() {
    /* Nonmatching */
}

/* 00004040-0000427C       .text _execute__12daNpc_Rsh1_cFv */
BOOL daNpc_Rsh1_c::_execute() {
    /* Nonmatching */
}

/* 0000427C-00004308       .text _delete__12daNpc_Rsh1_cFv */
BOOL daNpc_Rsh1_c::_delete() {
    /* Nonmatching */
}

/* 00004308-00004328       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Rsh1_c*)i_this)->CreateHeap();
}

/* 00004328-00004464       .text _create__12daNpc_Rsh1_cFv */
cPhs_State daNpc_Rsh1_c::_create() {
    /* Apparent match */
    fopAcM_SetupActor(this, daNpc_Rsh1_c);

    cPhs_State state = dComIfG_resLoad(&field_0x290, m_arcname);

    if (state == cPhs_COMPLEATE_e) {
        field_0x95E = (fopAcM_GetParam(this) >> 0x14) & 0xF;

        switch (field_0x95E) {
            case 0:
                field_0x95E = 0;
                break;
            default:
                field_0x95E = 0;
                break;
        }
        
        if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x6100)) {
            return cPhs_ERROR_e;
        }

        cullMtx = field_0x298->getModel()->getBaseTRMtx();

        if (l_HIO.field_0x08 < 0) {
            l_HIO.field_0x04 = mDoHIO_createChild("露店の社長", &l_HIO); // "Stall owner"
        }
        l_HIO.field_0x08++;

        if (!CreateInit()) {
            return cPhs_ERROR_e;
        }
    }

    return state;
}

/* 00004698-000049A0       .text CreateHeap__12daNpc_Rsh1_cFv */
BOOL daNpc_Rsh1_c::CreateHeap() {
    /* Nonmatching */
    J3DModelData* model_p = (J3DModelData *) dComIfG_getObjectRes(m_arcname, 0x20);
    field_0x298 = new mDoExt_McaMorf(
        model_p, 
        NULL, NULL, 
        (J3DAnmTransform *) dComIfG_getObjectRes(m_arcname, 0x1B), 
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, 
        dComIfG_getObjectRes(m_arcname, 0xF), 
        0, 0x11020203
    );

    if (!field_0x298 || !field_0x298->getModel()) {
        field_0x298 = NULL;
        return FALSE;
    }

    m_head_jnt_num = model_p->getJointName()->getIndex("head");
    JUT_ASSERT(0x953, m_head_jnt_num >= 0);

    m_backbone_jnt_num = model_p->getJointName()->getIndex("backbone");
    JUT_ASSERT(0x956, m_backbone_jnt_num >= 0);

    switch (field_0x95E) {
        case 0:
            field_0x958 = 0;
            break;
    }

    if (!initTexPatternAnm(false)) {
        return FALSE;
    }

    for (u16 i = 0; i < model_p->getJointNum(); i++) {
        if (i == m_head_jnt_num || i == m_backbone_jnt_num) {
            field_0x298->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Rsh);
        }
    }

    field_0x298->getModel()->setUserArea((u32)this);
    field_0x488.SetWall(30.0f, 0.0f);
    field_0x2C4.Set(&current.pos, &old.pos, this, 1, &field_0x488, &speed);

    field_0x954 = ShopCursor_create(
        (J3DModelData *) dComIfG_getObjectRes(m_arcname, 0x23),
        (J3DAnmTevRegKey *) dComIfG_getObjectRes(m_arcname, 0x26),
        l_HIO.field_0x34
    );

    return field_0x954 != NULL ? TRUE : FALSE;
}

/* 000049A0-00004A28       .text set_mtx__12daNpc_Rsh1_cFv */
void daNpc_Rsh1_c::set_mtx() {
    /* Nonmatching */
}

/* 00004A28-00004A48       .text daNpc_Rsh1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Rsh1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Rsh1_c*)i_this)->_create();
}

/* 00004A48-00004A68       .text daNpc_Rsh1_Delete__FP12daNpc_Rsh1_c */
static BOOL daNpc_Rsh1_Delete(daNpc_Rsh1_c* i_this) {
    return ((daNpc_Rsh1_c*)i_this)->_delete();
}

/* 00004A68-00004A88       .text daNpc_Rsh1_Execute__FP12daNpc_Rsh1_c */
static BOOL daNpc_Rsh1_Execute(daNpc_Rsh1_c* i_this) {
    return ((daNpc_Rsh1_c*)i_this)->_execute();
}

/* 00004A88-00004AA8       .text daNpc_Rsh1_Draw__FP12daNpc_Rsh1_c */
static BOOL daNpc_Rsh1_Draw(daNpc_Rsh1_c* i_this) {
    return ((daNpc_Rsh1_c*)i_this)->_draw();
}

/* 00004AA8-00004AB0       .text daNpc_Rsh1_IsDelete__FP12daNpc_Rsh1_c */
static BOOL daNpc_Rsh1_IsDelete(daNpc_Rsh1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Rsh1_Method = {
    (process_method_func)daNpc_Rsh1_Create,
    (process_method_func)daNpc_Rsh1_Delete,
    (process_method_func)daNpc_Rsh1_Execute,
    (process_method_func)daNpc_Rsh1_IsDelete,
    (process_method_func)daNpc_Rsh1_Draw,
};

actor_process_profile_definition g_profile_NPC_RSH1 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_RSH1,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Rsh1_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_RSH1,
    /* Actor SubMtd */ &l_daNpc_Rsh1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_12_e,
};
