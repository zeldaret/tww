/**
 * d_a_npc_nz.cpp
 * NPC - Rat (shopkeeper)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_nz.h"
#include "d/res/res_nz.h"
#include "d/res/res_npcnz.h"
#include "d/actor/d_a_player.h"
#include "d/d_com_inf_game.h"
#include "d/d_lib.h"
#include "d/d_item.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

class daNpc_Nz_HIO_c : public JORReflexible {
public:
    daNpc_Nz_HIO_c();
    virtual ~daNpc_Nz_HIO_c() {}

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x00 - vtable */
    /* 0x04 */ s8 mNo;
    /* 0x06 */ s16 field_0x06;
    /* 0x08 */ s16 field_0x08;
    /* 0x0A */ s16 field_0x0A;
    /* 0x0C */ s16 field_0x0C;
    /* 0x0E */ s16 field_0x0E;
    /* 0x10 */ s16 field_0x10;
    /* 0x12 */ s16 field_0x12;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ s16 field_0x18;
    /* 0x1A */ s8 field_0x1A;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
}; // Size: 0x28

const char daNpc_Nz_c::m_arc_name[] = "NZ";
const char daNpc_Nz_c::m_bdl_arc_name[] = "Npcnz";

/* 000000EC-00000128       .text daNpcNz_NodeCallBack__FP7J3DNodei */
static BOOL daNpcNz_NodeCallBack(J3DNode* node, int calcTiming) {
    return reinterpret_cast<daNpc_Nz_c*>(j3dSys.getModel()->getUserArea())->NodeCallBack(node, calcTiming);
}

/* 00000128-0000024C       .text NodeCallBack__10daNpc_Nz_cFP7J3DNodei */
BOOL daNpc_Nz_c::NodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));

        if(jntNo == m_jnt.getHeadJntNum()) {
            cXyz temp(0.0f, 0.0f, 0.0f);
            mDoMtx_stack_c::YrotM(m_jnt.getHead_y());
            mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
            mDoMtx_stack_c::multVec(&temp, &eyePos);
        }
        if(jntNo == m_jnt.getBackboneJntNum()) {
            mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
            mDoMtx_stack_c::ZrotM(-m_jnt.getBackbone_x());
        }

        model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
        cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    }

    return true;
}

/* 00000288-000002C4       .text daNpcNz_TailNodeCallBack__FP7J3DNodei */
static BOOL daNpcNz_TailNodeCallBack(J3DNode* node, int calcTiming) {
    return reinterpret_cast<daNpc_Nz_c*>(j3dSys.getModel()->getUserArea())->TailNodeCallBack(node, calcTiming);
}

/* 000002C4-000003A4       .text TailNodeCallBack__10daNpc_Nz_cFP7J3DNodei */
BOOL daNpc_Nz_c::TailNodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        s32 idx = 0;
        J3DModel* model = j3dSys.getModel();

        if(jntNo == 9) {
            idx = 1;
        }

        static cXyz offset(cXyz::Zero);

        mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));
        mDoMtx_stack_c::multVec(&offset, &field_0xA64[idx]);
    }

    return true;
}

/* 000003A4-00000978       .text TailControl__10daNpc_Nz_cFv */
void daNpc_Nz_c::TailControl() {
    cXyz sp64;
    cXyz sp58;
    cXyz sp4C;
    cXyz sp40;
    sp58.set(0.0f, 0.0f, 5.0f);
    field_0x974[0] = field_0xA64[0];
    sp64 = field_0xA64[1] - field_0xA64[0];
    s32 angle = cM_atan2s(sp64.x, sp64.z);
    f32 dist = sp64.absXZ();
    s16 angle2 = -cM_atan2s(sp64.y, dist);
    mDoMtx_stack_c::YrotS(angle);
    mDoMtx_stack_c::XrotM(angle2);
    mDoMtx_stack_c::multVec(&sp58, &sp40);

    int i;
    s16 temp9;
    int temp7;
    cXyz* r19 = &field_0x974[1];
    cXyz* r18 = &field_0x9EC[1];
    cXyz* r17 = field_0x934.getPos(0);
    dBgS_GndChk gndChk;
    for(i = 1; i < 10; i++, r19++, r18++) {
        f32 temp3 = 1.0f - (i-1) * 0.1f;
        cXyz sp34;
        sp34.x = r18[0].x + sp40.x * temp3;
        sp34.y = r18[0].y + sp40.y * temp3;
        sp34.z = r18[0].z + sp40.z * temp3;
        f32 temp5 = r19[0].y + sp34.y - 2.0f;
        if(temp5 < home.pos.y + 5.0f) {
            temp5 = home.pos.y + 5.0f;
        }
        sp64.y = temp5 - r19[-1].y;
        sp64.x = sp34.x + (r19[0].x - r19[-1].x);
        sp64.z = sp34.z + (r19[0].z - r19[-1].z);
        temp7 = cM_atan2s(sp64.x, sp64.z);
        dist = sp64.absXZ();
        temp9 = -cM_atan2s(sp64.y, dist);
        sp58.set(0.0f, 0.0f, 20.0f);
        mDoMtx_stack_c::YrotS(temp7);
        mDoMtx_stack_c::XrotM(temp9);
        mDoMtx_stack_c::multVec(&sp58, &sp4C);
        r18[0] = r19[0];
        r19[0].x = r19[-1].x + sp4C.x;
        r19[0].y = r19[-1].y + sp4C.y;
        r19[0].z = r19[-1].z + sp4C.z;
        r18[0].x = (r19[0].x - r18[0].x) * 0.8f;
        r18[0].y = (r19[0].y - r18[0].y) * 0.8f;
        r18[0].z = (r19[0].z - r18[0].z) * 0.8f;
    }

    cXyz* r3 = field_0x974;
    for(int i = 0; i < 10; i++, r3++, r17++) {
        *r17 = r3[0];
    }
}

static daNpc_Nz_HIO_c l_HIO;

/* 00000CF8-00000D18       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Nz_c*>(i_this)->_createHeap();
}

/* 00000D18-00000F98       .text _createHeap__10daNpc_Nz_cFv */
BOOL daNpc_Nz_c::_createHeap() {
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_bdl_arc_name, NPCNZ_BDL_NZ));
    JUT_ASSERT(0xD0, modelData != NULL);

    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL, NULL,
        NULL,
        -1, 1.0f, 0, -1, 1,
        NULL,
        0x00080000,
        0x37441422
    );

    if(mpMorf == NULL || mpMorf->getModel() == NULL) {
        return false;
    }

    mpMorf->getModel()->setUserArea((u32)this);

    m_jnt.setHeadJntNum(modelData->getJointName()->getIndex("head"));
    JUT_ASSERT(0xDA, m_jnt.getHeadJntNum() >= 0);

    m_jnt.setBackboneJntNum(modelData->getJointName()->getIndex("mune"));
    JUT_ASSERT(0xDD, m_jnt.getBackboneJntNum() >= 0);

    for(u16 i = 0; i < modelData->getJointNum(); i++) {
        if(i == m_jnt.getHeadJntNum() || i == m_jnt.getBackboneJntNum()) {
            modelData->getJointNodePointer(i)->setCallBack(daNpcNz_NodeCallBack);
        }
        if(i == 1 || i == 9) {
            modelData->getJointNodePointer(i)->setCallBack(daNpcNz_TailNodeCallBack);
        }
    }

    ResTIMG* img = static_cast<ResTIMG*>(dComIfG_getObjectRes(m_arc_name, NZ_BTI_SIPPO));
    if (field_0x934.init(1, 10, img, FALSE)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 00000F98-00001010       .text __ct__14daNpc_Nz_HIO_cFv */
daNpc_Nz_HIO_c::daNpc_Nz_HIO_c() {
    mNo = -1;
    field_0x06 = 0x1F40;
    field_0x08 = 0x1F40;
    field_0x0A = 0;
    field_0x0C = 0x1F40;
    field_0x0E = -0xBB8;
    field_0x10 = -0x1F40;
    field_0x12 = 0;
    field_0x14 = -0x1F40;
    field_0x16 = 0x7D0;
    field_0x18 = 0x640;
    field_0x1A = 0;
    field_0x1C = 100.0f;
    field_0x20 = 250.0f;
    field_0x24 = 250.0f;
}

/* 00001010-000011A0       .text daNpc_Nz_XyCheckCB__FPvi */
static s16 daNpc_Nz_XyCheckCB(void* i_actor, int i_itemBtn) {
    daNpc_Nz_c* i_this = static_cast<daNpc_Nz_c*>(i_actor);

    if(dComIfGp_getSelectItem(i_itemBtn) == dItem_BIRD_BAIT_5_e) {
        f32 temp2 = l_HIO.field_0x20;
        daPy_py_c* player = daPy_getPlayerActorClass();
        cXyz temp(player->current.pos);
        temp.x += temp2 * cM_ssin(player->current.angle.y);
        temp.z += temp2 * cM_scos(player->current.angle.y);
        cXyz temp3 = i_this->field_0x6C4 - temp;
        if(temp3.absXZ() < l_HIO.field_0x24) {
            return true;
        }

        return false;
    }

    return false;
}

/* 000011A0-000011C0       .text daNpc_Nz_XyEventCB__FPvi */
static s16 daNpc_Nz_XyEventCB(void* i_this, int param_1) {
    return static_cast<daNpc_Nz_c*>(i_this)->XyEventCB(param_1);
}

/* 000011C0-00001210       .text XyEventCB__10daNpc_Nz_cFi */
s16 daNpc_Nz_c::XyEventCB(int) {
    field_0x8FA = dComIfGp_evmng_getEventIdx("DEFAULT_NPC_NZ_ESA");
    return field_0x8FA;
}

#include "d/actor/d_a_npc_nz_cut.inc"

/* 00001210-00001268       .text eventOrder__10daNpc_Nz_cFv */
void daNpc_Nz_c::eventOrder() {
    if(field_0x8F8 == 1 || field_0x8F8 == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
        if (field_0x8F8 == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    }
}

/* 00001268-000012D0       .text checkOrder__10daNpc_Nz_cFv */
void daNpc_Nz_c::checkOrder() {
    if(eventInfo.checkCommandTalk() && (field_0x8F8 == 1 || field_0x8F8 == 2)) {
        if(field_0x8F8 == 2) {
            modeProcInit(1);
        }

        field_0x8F8 = 0;
    }
}

/* 000012D0-000012F4       .text setAttention__10daNpc_Nz_cFv */
void daNpc_Nz_c::setAttention() {
    attention_info.position = current.pos;
    attention_info.position.y = eyePos.y;
}

/* 000012F4-000013E8       .text LookBack__10daNpc_Nz_cFv */
void daNpc_Nz_c::LookBack() {
    cXyz* dstTemp;
    s16 targetY = current.angle.y;
    cXyz dstPos = dNpc_playerEyePos(0.0f);
    dstTemp = &dstPos;

    s16 maxFollowRotVel;
    if (m_jnt.trnChk()) {
        maxFollowRotVel = l_HIO.field_0x18;
    }
    else {
        maxFollowRotVel = 0;
    }

    m_jnt.setParam(l_HIO.field_0x0A, l_HIO.field_0x0C, l_HIO.field_0x12, l_HIO.field_0x14, l_HIO.field_0x06, l_HIO.field_0x08, l_HIO.field_0x0E, l_HIO.field_0x10, l_HIO.field_0x16);
    m_jnt.lookAtTarget(&current.angle.y, dstTemp, eyePos, targetY, maxFollowRotVel, true);
}

/* 000013E8-0000146C       .text setAnm__10daNpc_Nz_cFScb */
void daNpc_Nz_c::setAnm(s8 param_1, bool param_2) {
    static const dLib_anm_idx_c a_anm_idx_tbl[] = {
        {0x23, 0x12},
        {0x15, 0x07},
        {0x16, -1},
        {0x17, 0x08},
        {0x18, 0x09},
        {0x19, 0x0A},
        {0x1A, 0x0B},
        {0x1B, 0x0C},
        {0x1C, 0x0D},
        {0x1D, 0x0E},
        {0x1F, 0x10},
        {0x20, 0x11},
        {0x1E, 0x11},
        {0x21, -1},
        {0x22, -1}
    };
    static const dLib_anm_prm_c a_anm_prm_tbl[] = {
        {0x00,   -1, 0x00, 8.0f, 1.0f, 2},
        {0x01,   -1, 0x00, 8.0f, 1.0f, 0},
        {0x02,   -1, 0x00, 8.0f, 1.0f, 0},
        {0x03,   -1, 0x00, 8.0f, 1.0f, 0},
        {0x04,   -1, 0x00, 8.0f, 1.0f, 0},
        {0x05,   -1, 0x00, 8.0f, 1.0f, 0},
        {0x06,   -1, 0x00, 8.0f, 1.0f, 2},
        {0x07,   -1, 0x00, 8.0f, 1.0f, 2},
        {0x08,   -1, 0x00, 8.0f, 1.0f, 0},
        {0x09,   -1, 0x00, 8.0f, 1.0f, 0},
        {0x0A,   -1, 0x00, 8.0f, 1.0f, 2},
        {0x0B,   -1, 0x00, 8.0f, 1.0f, 2},
        {0x0C,   -1, 0x00, 8.0f, 1.0f, 0},
        {0x0D,   -1, 0x00, 8.0f, 1.0f, 0},
        {0x0E,   -1, 0x00, 8.0f, 1.0f, 0},
    };

    if(param_1 != 0xF) {
        field_0x6D5 = param_1;
    }

    if(field_0x6D5 == 0) {
        m_jnt.offHeadLock();
        m_jnt.offBackBoneLock();
    }
    else {
        m_jnt.onHeadLock();
        m_jnt.onBackBoneLock();
    }

    dLib_setAnm(m_arc_name, mpMorf, &field_0x6D4, &field_0x6D5, &field_0x6D6, a_anm_idx_tbl, a_anm_prm_tbl, param_2);
}

/* 0000146C-000017E0       .text setMtx__10daNpc_Nz_cFv */
void daNpc_Nz_c::setMtx() {
    mpMorf->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());

    if(field_0x6D5 != 0xC && field_0x6D5 != 0xB) {
        return;
    }

    daShopItem_c* item = getShopItem(field_0x909);
    if(item) {
        cXyz* pScale = item->getScaleP();
        field_0xA90 = cLib_maxLimit<int>(field_0xA90 + 1, 20);
        f32 temp4 = 0.0f;

        f32 scaleX;
        f32 scaleY;
        f32 multX1 = 0.85f;
        f32 multY1 = 1.4f;
        f32 multX2 = 1.1f;
        f32 multY2 = 0.8f;
        f32 multX3 = 1.0f;
        f32 multY3 = 1.0f;
        if(field_0xA90 < 12) {
            scaleX = field_0xA90 / 12.0f;
            scaleY = field_0xA90 / 12.0f;
            scaleX *= multX1;
            scaleY *= multY1;
        }
        else if(field_0xA90 < 16) {
            scaleX = (field_0xA90 - 12) / 4.0f;
            scaleY = (field_0xA90 - 12) / 4.0f;
            scaleX = (scaleX * multX2) + (1.0f - scaleX) * multX1;
            scaleY = (scaleY * multY2) + (1.0f - scaleY) * multY1;
        }
        else {
            scaleX = (field_0xA90 - 16) / 2.0f;
            scaleY = (field_0xA90 - 16) / 2.0f;
            scaleX = (scaleX * multX3) + (1.0f - scaleX) * multX2;
            scaleY = (scaleY * multY3) + (1.0f - scaleY) * multY2;
        }

        pScale->z = scaleX;
        pScale->x = scaleX;
        pScale->y = scaleY;

        J3DModel* pModel = mpMorf->getModel();
        mDoMtx_stack_c::copy(pModel->getAnmMtx(0x12));
        cXyz temp;
        mDoMtx_stack_c::multVec(&cXyz::Zero, &temp);
        mDoMtx_stack_c::copy(pModel->getAnmMtx(0x15));
        cXyz temp2;
        mDoMtx_stack_c::multVec(&cXyz::Zero, &temp2);
        cXyz temp3 = temp + temp2;

        switch(field_0x908) {
            case dItem_BIRD_BAIT_5_e:
                temp4 = -15.0f;
                break;
            case dItem_HYOI_PEAR_e:
                temp4 = -5.0f;
                break;
            case dItem_RED_POTION_e:
            case dItem_BLUE_POTION_e:
                temp4 = -5.0f;
                break;
            case dItem_BOMB_10_e:
            case dItem_BOMB_30_e:
                temp4 = -15.0f;
                break;
            case dItem_ARROW_10_e:
            case dItem_ARROW_30_e:
                temp4 = -10.0f;
                break;
        }

        temp3 *= 0.5f;
        temp3.y += scaleY * 20.0f + -20.0f;
        temp3.y += temp4;
        item->getPosP()->set(temp3);
    }
}

/* 000017E0-000017E4       .text modeWaitInit__10daNpc_Nz_cFv */
void daNpc_Nz_c::modeWaitInit() {
    return;
}

/* 000017E4-000017F0       .text modeWait__10daNpc_Nz_cFv */
void daNpc_Nz_c::modeWait() {
    field_0x8F8 = 2;
}

/* 000017F0-000017F4       .text modeEventEsaInit__10daNpc_Nz_cFv */
void daNpc_Nz_c::modeEventEsaInit() {
    return;
}

/* 000017F4-000018EC       .text modeEventEsa__10daNpc_Nz_cFv */
void daNpc_Nz_c::modeEventEsa() {
    if(!mEventCut.cutProc()) {
        cutProc();
    }

    if(dComIfGp_evmng_endCheck(field_0x8FA)) {
        dComIfGp_event_reset();

        field_0x8FA = -1;
        deleteShopItem();
        field_0x8FC = false;

        old.pos = home.pos;
        current.pos = old.pos;
        shape_angle = home.angle;
        current.angle = shape_angle;

        modeProcInit(0);
    }
}

/* 000018EC-000019DC       .text modeProc__10daNpc_Nz_cFQ210daNpc_Nz_c6Proc_ei */
void daNpc_Nz_c::modeProc(daNpc_Nz_c::Proc_e proc, int newMode) {
    typedef void(daNpc_Nz_c::*mode_func_t)(void);
    struct mode_entry_t {
        mode_func_t init;
        mode_func_t run;
        const char* name;
    };

    static mode_entry_t mode_tbl[] = {
        {
            &daNpc_Nz_c::modeWaitInit,
            &daNpc_Nz_c::modeWait,
            "WAIT",
        },
        {
            &daNpc_Nz_c::modeEventEsaInit,
            &daNpc_Nz_c::modeEventEsa,
            "WAIT",
        }
    };

    if(proc == PROC_INIT) {
        mCurMode = newMode;
        (this->*mode_tbl[mCurMode].init)();
    }
    else if(proc == PROC_EXEC) {
        (this->*mode_tbl[mCurMode].run)();
    }
}

/* 000019DC-00001B38       .text daNpcNz_getShopBoughtMsg__FUc */
static u32 daNpcNz_getShopBoughtMsg(u8 itemNo) {
    int messageRupee = dComIfGp_getMessageRupee();
    if(dComIfGs_getRupee() < messageRupee) {
        return 0x3405;
    }

    if((itemNo == dItem_RED_POTION_e || itemNo == dItem_BLUE_POTION_e) && !dComIfGs_checkEmptyBottle()) {
        return 0x3406;
    }

    if(isBomb(itemNo) && dComIfGs_getBombNum() == dComIfGs_getBombMax()) {
        return 0x3407;
    }

    if(isArrow(itemNo) && dComIfGs_getArrowNum() == dComIfGs_getArrowMax()) {
        return 0x3407;
    }

    if((itemNo == dItem_BIRD_BAIT_5_e || itemNo == dItem_HYOI_PEAR_e) && !dComIfGs_checkBaitItemEmpty()) {
        return 0x3407;
    }

    int itemTemp = itemNo; // probably fake
    if(checkItemGet(itemTemp, 0)) {
        dComIfGp_setItemRupeeCount(-messageRupee);
        execItemGet(itemTemp);
        return 0x3403;
    }

    return 0;
}

/* 00001B38-00001B70       .text daNpc_Nz_ShopItemCreateCB__FPv */
static cPhs_State daNpc_Nz_ShopItemCreateCB(void* i_item) {
    daShopItem_c* i_this = static_cast<daShopItem_c*>(i_item);
    i_this->hide();
    i_this->setTevType(TEV_TYPE_ACTOR);

    return cPhs_COMPLEATE_e;
}

/* 00001B70-00001C14       .text createShopItem__10daNpc_Nz_cFUcUc */
void daNpc_Nz_c::createShopItem(u8 itemNo1, u8 itemNo2) {
    if(field_0xA88 == fpcM_ERROR_PROCESS_ID_e) {
        field_0xA88 = fopAcM_createShopItem(&current.pos, itemNo1, &current.angle, fopAcM_GetRoomNo(this), 0, daNpc_Nz_ShopItemCreateCB);
    }
    if(field_0xA8C == fpcM_ERROR_PROCESS_ID_e) {
        field_0xA8C = fopAcM_createShopItem(&current.pos, itemNo2, &current.angle, fopAcM_GetRoomNo(this), 0, daNpc_Nz_ShopItemCreateCB);
    }
}

/* 00001C14-00001C6C       .text getShopItem__10daNpc_Nz_cFi */
daShopItem_c* daNpc_Nz_c::getShopItem(int param_1) {
    if(param_1 == 0) {
        return (daShopItem_c*)fopAcM_SearchByID(field_0xA88);
    }
    else {
        return (daShopItem_c*)fopAcM_SearchByID(field_0xA8C);
    }
}

/* 00001C6C-00001CF0       .text deleteShopItem__10daNpc_Nz_cFv */
void daNpc_Nz_c::deleteShopItem() {
    if(field_0xA88 != fpcM_ERROR_PROCESS_ID_e) {
        daShopItem_c* item = getShopItem(0);
        if(item) {
            fopAcM_delete(item);
            field_0xA88 = fpcM_ERROR_PROCESS_ID_e;
        }
    }
    if(field_0xA8C != fpcM_ERROR_PROCESS_ID_e) {
        daShopItem_c* item = getShopItem(1);
        if(item) {
            fopAcM_delete(item);
            field_0xA8C = fpcM_ERROR_PROCESS_ID_e;
        }
    }
}

/* 00001CF0-00002038       .text next_msgStatus__10daNpc_Nz_cFPUl */
u16 daNpc_Nz_c::next_msgStatus(u32* pMsgNo) {
    u16 msgStatus = fopMsgStts_MSG_CONTINUES_e;

    static const u32 shop_next_msg_tbl[4][2] = {
        {
            0x33FB,
            0x33FC,
        },
        {
            0x33FD,
            0x33FE,
        },
        {
            0x33FF,
            0x3400,
        },
        {
            0x3401,
            0x3402,
        },
    };

    const u8 itemArr1[4][2] = {
        {
            dItem_BIRD_BAIT_5_e,
            dItem_HYOI_PEAR_e,
        },
        {
            dItem_RED_POTION_e,
            dItem_BLUE_POTION_e,
        },
        {
            dItem_BOMB_10_e,
            dItem_BOMB_30_e,
        },
        {
            dItem_ARROW_10_e,
            dItem_ARROW_30_e,
        },
    };

    int temp = 1;
    switch(*pMsgNo) {
        case 0x33F5:
            *pMsgNo = 0x33F6;
            break;
        case 0x33F6:
            if(dComIfGs_checkGetBottle()) {
                temp += 1;
            }
            if(dComIfGs_checkGetItem(dItem_BOMB_BAG_e)) {
                temp += 1;
            }
            if(dComIfGs_getItem(dInvSlot_BOW_e) != dItem_NONE_e) {
                temp += 1;
            }

            field_0x904 = cM_rndF(temp);
            *pMsgNo = field_0x904 + 0x33F7;
            createShopItem(itemArr1[field_0x904][0], itemArr1[field_0x904][1]);
            field_0x900 = *pMsgNo;
            break;
        case 0x33F7:
        case 0x33F8:
        case 0x33F9:
        case 0x33FA:
            switch(mpCurrMsg->mSelectNum) {
                case 0:
                case 1:
                    field_0x908 = itemArr1[field_0x904][mpCurrMsg->mSelectNum];
                    *pMsgNo = shop_next_msg_tbl[field_0x904][mpCurrMsg->mSelectNum];
                    field_0x909 = mpCurrMsg->mSelectNum;
                    break;
                case 2:
                    *pMsgNo = 0x3404;
                    break;
            }

            break;
        case 0x33FB:
        case 0x33FC:
        case 0x33FD:
        case 0x33FE:
        case 0x33FF:
        case 0x3400:
        case 0x3401:
        case 0x3402:
            switch(mpCurrMsg->mSelectNum) {
                case 0: {
                    u32 msgNo = daNpcNz_getShopBoughtMsg(field_0x908);
                    if(msgNo != 0) {
                        *pMsgNo = msgNo;
                        break;
                    }

                    daShopItem_c* item = getShopItem(field_0x909);
                    if(item) {
                        item->hide();
                    }

                    setAnm(0, false);
                    dComIfGp_setItemRupeeCount(-dComIfGp_getMessageRupee());
                    field_0x8F8 = 3;
                    field_0x8FA = dComIfGp_evmng_getEventIdx("DEFAULT_NPC_NZ_GETITEM");
                    dComIfGp_event_setGtItm(field_0x908);
                    msgStatus = fopMsgStts_MSG_ENDS_e;
                    break;
                }
                case 1:
                    *pMsgNo = field_0x900;
                    break;
                default:
                    break;
            }

            break;
        case 0x3404:
        case 0x3405:
        case 0x3406:
        case 0x3407:
            *pMsgNo = 0x3403;
            break;
        default:
            msgStatus = fopMsgStts_MSG_ENDS_e;
    }

    return msgStatus;
}

/* 00002038-000022C0       .text anmAtr__10daNpc_Nz_cFUs */
void daNpc_Nz_c::anmAtr(u16) {
    if(field_0x6D5 == 9 && mpMorf->checkFrame(mpMorf->getEndFrame() - 1.0f)) {
        setAnm(0, false);
    }
    else if(field_0x6D5 == 0xC && mpMorf->checkFrame(mpMorf->getEndFrame() - 1.0f)) {
        setAnm(0xB, false);
    }

    if(dComIfGp_checkMesgSendButton()) {
        if (mpCurrMsg->mStatus == fopMsgStts_BOX_CLOSING_e ||
            mpCurrMsg->mStatus == fopMsgStts_BOX_CLOSED_e ||
            mpCurrMsg->mStatus == fopMsgStts_MSG_ENDS_e
        ) {
            return;
        }

        daShopItem_c* item;
        switch(mpCurrMsg->mMsgNo) {
            case 0x33F5:
            case 0x33F6:
                break;
            case 0x33F7:
            case 0x33F8:
            case 0x33F9:
            case 0x33FA:
                item = getShopItem(field_0x909);
                if(item) {
                    item->hide();
                }

                setAnm(0, false);
                break;
            case 0x33FB:
            case 0x33FC:
            case 0x33FD:
            case 0x33FE:
            case 0x33FF:
            case 0x3400:
            case 0x3401:
            case 0x3402:
                item = getShopItem(field_0x909);
                if(item) {
                    item->show();
                }

                field_0xA90 = 0;
                fopAcM_seStart(this, JA_SE_CV_M_NZ_TALK_IN, 0);
                setAnm(0xC, false);
                break;
            case 0x3405:
            case 0x3406:
            case 0x3407:
                item = getShopItem(field_0x909);
                if(item) {
                    item->hide();
                }

                setAnm(0, false);
                break;
            case 0x3404:
                item = getShopItem(field_0x909);
                if(item) {
                    item->hide();
                }

                setAnm(0, false);
                break;
            case 0x3403:
                item = getShopItem(field_0x909);
                if(item) {
                    item->hide();
                }

                setAnm(0, false);
                break;
        }
    }
}

/* 000022C0-00002390       .text _execute__10daNpc_Nz_cFv */
bool daNpc_Nz_c::_execute() {
    cLib_addCalc2(&speedF, field_0x6EC, 0.3f, 4.0f);
    checkOrder();
    modeProc(PROC_EXEC, 2);
    LookBack();
    eventOrder();
    setAttention();
    mpMorf->play(NULL, 0, 0);
    mpMorf->calc();
    TailControl();
    mAcch.CrrPos(*dComIfG_Bgsp());
    mpBait = NULL;
    field_0x910 = FLOAT_MAX;
    setMtx();

    return false;
}

/* 00002390-0000254C       .text _draw__10daNpc_Nz_cFv */
bool daNpc_Nz_c::_draw() {
    if(!field_0x8FC) {
        return true;
    }
    else {
        J3DModel* pModel = mpMorf->getModel();
        J3DModelData* pModelData = pModel->getModelData();

        J3DJoint* rootJoint = pModelData->getJointNodePointer(0);
        J3DShape* matShape = pModelData->getMaterialNodePointer(0)->getShape();
        J3DShape* matShape2 = pModelData->getMaterialNodePointer(1)->getShape();
        J3DShape* matShape3 = pModelData->getMaterialNodePointer(2)->getShape();
        matShape->hide();

        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
        g_env_light.setLightTevColorType(pModel, &tevStr);

        mpMorf->entryDL();

        dComIfGd_setListMaskOff();

        matShape->show();
        pModel->getMatPacket(0)->unlock();
        matShape2->hide();
        matShape3->hide();
        rootJoint->entryIn();
        matShape2->show();
        matShape3->show();

        dComIfGd_setList();

        GXColor unusedColor_5609 = {255, 255, 0, 128};
        GXColor unusedColor_5611 = {255, 0, 0, 128};
        GXColor color = {200, 200, 200, 255};
        field_0x934.update(10, scale.x * 5.0f, color, 6, &tevStr);
        dComIfGd_set3DlineMat(&field_0x934);
    }

    return true;
}

/* 0000254C-00002768       .text createInit__10daNpc_Nz_cFv */
BOOL daNpc_Nz_c::createInit() {
    setAnm(0, false);
    modeProcInit(0);

    mAcchCir.SetWall(30.0f, 10.0f);
    mAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this),  this, 1, &mAcchCir, fopAcM_GetSpeed_p(this));
    mAcch.OnLineCheckNone();
    mAcch.SetWallNone();
    mAcch.SetRoofNone();
    gravity = 0.0f;
    mAcch.CrrPos(*dComIfG_Bgsp());

    setMtx();
    mpMorf->calc();
    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -450.0f, -50.0f, -450.0f, 450.0f, 750.0f, 450.0f);
    fopAcM_setCullSizeFar(this, 10.0f);
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xB1;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xB1;
    attention_info.flags = fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_TALKFLAG_NOTALK_e;
    eventInfo.setXyCheckCB(&daNpc_Nz_XyCheckCB);
    eventInfo.setXyEventCB(&daNpc_Nz_XyEventCB);
    mEventCut.setActorInfo2("NpcNz", this);

    field_0x8F8 = 0;
    field_0x8FC = false;
    field_0x906 = 0;
    field_0x6C4 = home.pos;
    home.pos.x -= cM_ssin(home.angle.y) * 50.0f;
    home.pos.z -= cM_scos(home.angle.y) * 50.0f;
    current.pos = home.pos;
    field_0xA88 = -1;
    field_0xA8C = -1;

    return true;
}

/* 00002768-0000282C       .text setSmokeParticle__10daNpc_Nz_cFv */
void daNpc_Nz_c::setSmokeParticle() {
    if(field_0x914.getEmitter() != NULL) {
        field_0x914.end();
    }

    if(field_0x914.getEmitter() == NULL) {
        JPABaseEmitter* emitter = dComIfGp_particle_setToon(dPa_name::ID_COMMON_2022, &current.pos, &current.angle, 0, 0xB9, &field_0x914, fopAcM_GetRoomNo(this));
        if(emitter) {
            emitter->setRate(3.0f);
            emitter->setSpread(0.2f);
            emitter->setAwayFromAxisSpeed(0.2f);
            emitter->setMaxFrame(3);
        }
    }
}

/* 0000282C-00002830       .text getArg__10daNpc_Nz_cFv */
void daNpc_Nz_c::getArg() {
    return;
}

/* 00002830-000028FC       .text _create__10daNpc_Nz_cFv */
cPhs_State daNpc_Nz_c::_create() {
    fopAcM_SetupActor(this, daNpc_Nz_c);

    getArg();

    cPhs_State result = dComIfG_resLoad(&mPhs1, m_arc_name);
    if(result != cPhs_COMPLEATE_e) {
        return result;
    }

    result = dComIfG_resLoad(&mPhs2, m_bdl_arc_name);
    if(result != cPhs_COMPLEATE_e) {
        return result;
    }

    if(!fopAcM_entrySolidHeap(this, createHeap_CB, 0x2FE0)) {
        return cPhs_ERROR_e;
    }

    BOOL success = createInit();
    if (!success) {
        // Fakematch?
        if (success) {
            return cPhs_ERROR_e;
        } else {
            return cPhs_ERROR_e;
        }
    } else {
        return cPhs_COMPLEATE_e;
    }
}

/* 000028FC-00002AF0       .text __ct__10daNpc_Nz_cFv */
daNpc_Nz_c::daNpc_Nz_c() {
}

/* 00002E00-00002E6C       .text _delete__10daNpc_Nz_cFv */
bool daNpc_Nz_c::_delete() {
    if(field_0x914.getEmitter()) {
        field_0x914.end();
    }

    dComIfG_resDelete(&mPhs1, m_arc_name);
    dComIfG_resDelete(&mPhs2, m_bdl_arc_name);

    return true;
}

/* 00002E6C-00002E8C       .text daNpc_NzCreate__FPv */
static cPhs_State daNpc_NzCreate(void* i_this) {
    return static_cast<daNpc_Nz_c*>(i_this)->_create();
}

/* 00002E8C-00002EB0       .text daNpc_NzDelete__FPv */
static BOOL daNpc_NzDelete(void* i_this) {
    return static_cast<daNpc_Nz_c*>(i_this)->_delete();
}

/* 00002EB0-00002ED4       .text daNpc_NzExecute__FPv */
static BOOL daNpc_NzExecute(void* i_this) {
    return static_cast<daNpc_Nz_c*>(i_this)->_execute();
}

/* 00002ED4-00002EF8       .text daNpc_NzDraw__FPv */
static BOOL daNpc_NzDraw(void* i_this) {
    return static_cast<daNpc_Nz_c*>(i_this)->_draw();
}

/* 00002EF8-00002F00       .text daNpc_NzIsDelete__FPv */
static BOOL daNpc_NzIsDelete(void*) {
    return true;
}

static actor_method_class daNpc_NzMethodTable = {
    (process_method_func)daNpc_NzCreate,
    (process_method_func)daNpc_NzDelete,
    (process_method_func)daNpc_NzExecute,
    (process_method_func)daNpc_NzIsDelete,
    (process_method_func)daNpc_NzDraw,
};

actor_process_profile_definition g_profile_NPC_NZ = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_NZ,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Nz_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_NZ,
    /* Actor SubMtd */ &daNpc_NzMethodTable,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_4_e,
};
