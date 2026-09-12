/**
 * d_a_pz.cpp
 * NPC - Princess Zelda
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_pz.h"
#include "d/actor/d_a_arrow.h"
#include "d/actor/d_a_player.h"
#include "d/d_s_play.h"
#include "d/d_cc_d.h"
#include "d/d_cc_uty.h"
#include "d/d_material.h"
#include "d/d_snap.h"
#include "d/actor/d_a_gnd.h"
#include "d/actor/d_a_item.h"

static daPz_HIO_c l_HIO;

const s32 daPz_c::m_heapsize = 0xA740;
const char daPz_c::m_arc_name[] = "PZ";
const f32 daPz_c::m_smoke_ef = 1.25f;
const f32 daPz_c::m_grass_ef = 1.5f;
const f32 daPz_c::m_splash_ef = 1.0f;

const dCcD_SrcCyl daPz_c::m_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ DEMO_SELECT(cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IGrpAll_e | cCcD_CoSPrm_VsGrpAll_e,
                                            cCcD_CoSPrm_Set_e | cCcD_CoSPrm_VsGrpAll_e),
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ dCcG_SE_UNK23,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 0.0f,
        /* Height */ 0.0f,
    }},
};


/* 000000EC-00000310       .text __ct__10daPz_HIO_cFv */
daPz_HIO_c::daPz_HIO_c() {
    m02C = 0;
    mbEnableAttack = 1;
    mbDoSideStep = 0;
    mbWarpToPlayer = 0;
    for (int i = 0; i < 10; i++) {
        mDbgFlags[i] = 0;
    }

    mNpcHIO.m04 = -20.0f;
    mNpcHIO.mMaxHeadX = 8190;
    mNpcHIO.mMaxHeadY = 10000;
    mNpcHIO.mMaxBackboneX = 7000;
    s16 maxY = 13000;
    mNpcHIO.mMaxBackboneY = maxY;
    mNpcHIO.mMinHeadX = -2500;
    mNpcHIO.mMinHeadY = -10000;
    mNpcHIO.mMinBackboneX = -7000;
    mNpcHIO.mMinBackboneY = -13000;
    mNpcHIO.mMaxTurnStep = 4096;
    mNpcHIO.mMaxHeadTurnVel = 2048;
    mNpcHIO.mAttnYOffset = 50.0f;
    mNpcHIO.mMaxAttnAngleY = maxY;
    mNpcHIO.m22 = 0;
    mNpcHIO.mMaxAttnDistXZ = 400.0f;

    mAttnYOffset = 60.0f;
    mForceAnmId = 0;
    mEyeAreaAngle = 8192;
    mEyeAreaDist = 200.0f;
    mRunAnmRate = 1.2f;
    mRunAnmRateMin = 0.9f;
    mRunAnmRateMax = 2.0f;
    mRunSpeed = 10.0f;
    m031 = 0;
    mAimOffsetMax[PHASE_SHOOT_GND_e] = 100.0f;
    mAimPlayerRate[PHASE_SHOOT_GND_e] = 0.0f;
    mAimStraightRate[PHASE_SHOOT_GND_e] = 100.0f;
    mRetreatTime[PHASE_SHOOT_GND_e] = 30;
    mMoveTimeBase[PHASE_SHOOT_GND_e] = 300;
    mMoveTimeRand[PHASE_SHOOT_GND_e] = 0;
    mAttackTimeBase[PHASE_SHOOT_GND_e] = 30;
    mAttackTimeRand[PHASE_SHOOT_GND_e] = 0;
    mCircleRadius[PHASE_SHOOT_GND_e] = 1000.0f;
#if VERSION > VERSION_DEMO
    mTalkTime[PHASE_SHOOT_GND_e] = 60;
    mTalkDist[PHASE_SHOOT_GND_e] = 3000.0f;
#endif
    mAimOffsetMax[PHASE_SHOOT_PLAYER_e] = 100.0f;
    mAimPlayerRate[PHASE_SHOOT_PLAYER_e] = 100.0f;
    mAimStraightRate[PHASE_SHOOT_PLAYER_e] = 80.0f;
    mRetreatTime[PHASE_SHOOT_PLAYER_e] = 30;
    mMoveTimeBase[PHASE_SHOOT_PLAYER_e] = 100;
    mMoveTimeRand[PHASE_SHOOT_PLAYER_e] = 100;
    mAttackTimeBase[PHASE_SHOOT_PLAYER_e] = 30;
    mAttackTimeRand[PHASE_SHOOT_PLAYER_e] = 60;
    mCircleRadius[PHASE_SHOOT_PLAYER_e] = 1000.0f;
#if VERSION > VERSION_DEMO
    mTalkTime[PHASE_SHOOT_PLAYER_e] = 600;
    mTalkDist[PHASE_SHOOT_PLAYER_e] = 800.0f;
#endif
    mCircleWobble = 100.0f;
    mGndHitTrigger = 4;
    mGndAttackNum = 6;
    mPlayerHitTrigger = 4;
    mPlayerAttackNum = 6;
    mGravity = -2.5f;
    f32 stepDistance = 20.0f;
    mBackStepJumpY = stepDistance;
    mBackStepSpeed = stepDistance;
    mSideStepJumpY = stepDistance;
    mSideStepSpeed = stepDistance;
    mDownJumpY = 4.0f;
    mDownSpeed = 15.0f;
    mDownTime = 14;
    mTurnDirChangeRate = 30.0f;
    s16 unknownDebugValue = 40;
    m0DC = unknownDebugValue;
    m0DE = unknownDebugValue;
    mDamageTime = 5;
    mRetreatDist = 600.0f;
    mFollowDist = 800.0f;
    mFallSplashYOffset = 15.0f;
    mDam01Morf = 2.0f;
    mDam02Morf = 1.0f;
}

daPz_HIO_c::~daPz_HIO_c() {}

#if VERSION > VERSION_DEMO
/* 00000310-00000340       .text stealItem_CB__FPv */
static BOOL stealItem_CB(void* i_actor) {
    if (i_actor != NULL) {
        fopAc_ac_c* actor = (fopAc_ac_c*)i_actor;
        actor->scale.set(1.0f, 1.0f, 1.0f);
        ((daItem_c*)actor)->mFlag |= 0x40;
    }
    return TRUE;
}
#endif

/* 00000340-0000038C       .text nodeHeadControl_CB__FP7J3DNodei */
static BOOL nodeHeadControl_CB(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daPz_c* actor = (daPz_c*)model->getUserArea();
        if (actor != NULL) {
            actor->_nodeHeadControl(node, model);
        }
    }
    return TRUE;
}

/* 0000038C-000004FC       .text _nodeHeadControl__6daPz_cFP7J3DNodeP8J3DModel */
void daPz_c::_nodeHeadControl(J3DNode* node, J3DModel* model) {
    J3DJoint* joint = (J3DJoint*)node;
    int jntNo = joint->getJntNo();

    mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));

    static cXyz l_offsetAttPos(0.0f, 0.0f, 0.0f);
    static cXyz l_offsetEyePos(24.0f, -16.0f, 0.0f);
    mDoMtx_stack_c::multVec(&l_offsetAttPos, &mAttentionPos);
    mDoMtx_stack_c::YrotM(-m_jnt.getHead_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
    mDoMtx_stack_c::multVec(&l_offsetEyePos, &mEyePos);

    MtxP now = mDoMtx_stack_c::get();
    mHeadPos.x = now[0][3];
    mHeadPos.y = now[1][3];
    mHeadPos.z = now[2][3];

    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
}

/* 00000538-00000584       .text nodeWaistControl_CB__FP7J3DNodei */
static BOOL nodeWaistControl_CB(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daPz_c* actor = (daPz_c*)model->getUserArea();
        if (actor != NULL) {
            actor->_nodeWaistControl(node, model);
        }
    }
    return TRUE;
}

/* 00000584-00000710       .text _nodeWaistControl__6daPz_cFP7J3DNodeP8J3DModel */
void daPz_c::_nodeWaistControl(J3DNode* node, J3DModel* model) {
    J3DJoint* joint = (J3DJoint*)node;
    int jntNo = joint->getJntNo();

    static s16 tmp_angle;
    tmp_angle += 0x1000;

    mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));

    if (isAnm(ANM_RELORD_e) || isAnm(ANM_WAIT03_e) || isAnm(ANM_SHOOT_e)) {
        mDoMtx_stack_c::ZrotM(0xdac);
        mDoMtx_stack_c::YrotM(0x5dc);
    }

    if (REG12_S(6) != 0) {
        mDoMtx_stack_c::XrotM(tmp_angle);
    } else {
        mDoMtx_XrotM(mDoMtx_stack_c::get(), m_jnt.getBackbone_y());
        mDoMtx_stack_c::ZrotM(-m_jnt.getBackbone_x());
    }

    if (isAnm(ANM_RELORD_e) || isAnm(ANM_WAIT03_e) || isAnm(ANM_SHOOT_e)) {
        mDoMtx_stack_c::YrotM(-0x5dc);
        mDoMtx_stack_c::ZrotM(-0xdac);
    }

    cMtx_copy(mDoMtx_stack_c::get(), mWaistMtx);
    MtxP now = mDoMtx_stack_c::get();
    mWaistPos.x = now[0][3];
    mWaistPos.y = now[1][3];
    mWaistPos.z = now[2][3];

    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
}

/* 00000710-0000075C       .text nodeWaist2Control_CB__FP7J3DNodei */
static BOOL nodeWaist2Control_CB(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daPz_c* actor = (daPz_c*)model->getUserArea();
        if (actor != NULL) {
            actor->_nodeWaist2Control(node, model);
        }
    }
    return TRUE;
}

/* 0000075C-000007F4       .text _nodeWaist2Control__6daPz_cFP7J3DNodeP8J3DModel */
void daPz_c::_nodeWaist2Control(J3DNode* node, J3DModel* model) {
    J3DJoint* joint = (J3DJoint*)node;
    int jntNo = joint->getJntNo();

    mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));
    mDoMtx_stack_c::YrotM(mWaistRotY);
    mDoMtx_stack_c::ZrotM(mWaistRotZ);

    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
}

/* 000007F4-00000840       .text nodeSkirtControl_CB__FP7J3DNodei */
static BOOL nodeSkirtControl_CB(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daPz_c* actor = (daPz_c*)model->getUserArea();
        if (actor != NULL) {
            actor->_nodeSkirtControl(node, model);
        }
    }
    return TRUE;
}

/* 00000840-00000920       .text _nodeSkirtControl__6daPz_cFP7J3DNodeP8J3DModel */
void daPz_c::_nodeSkirtControl(J3DNode* node, J3DModel* model) {
    J3DJoint* joint = (J3DJoint*)node;
    int jntNo = joint->getJntNo();

    mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));

    s16 m = mWaistRotZ;
    if (m > mWaistRotY) {
        m = mWaistRotY;
    }

    mDoMtx_stack_c::XrotM(REG12_S(2));
    mDoMtx_stack_c::YrotM(REG12_S(3));
    mDoMtx_stack_c::ZrotM(-(m + REG12_S(4)));

    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
}

/* 00000920-00000940       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c* i_this) {
    return ((daPz_c*)i_this)->_createHeap();
}

/* 00000940-00000D54       .text bodyCreateHeap__6daPz_cFv */
BOOL daPz_c::bodyCreateHeap() {
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arc_name, dRes_INDEX_PZ_BDL_PZ_e));
    JUT_ASSERT(DEMO_SELECT(551, 574), modelData != NULL);

    for (u16 i = 0; i < modelData->getMaterialNum(); i++) {
        J3DMaterial* material = modelData->getMaterialNodePointer(i);
        material->setMaterialAnm(new daPz_matAnm_c());
    }

    mpMorf = new mDoExt_McaMorf(modelData, NULL, NULL, NULL, J3DFrameCtrl::EMode_NULL, 1.0f, 0, -1,
                                 TRUE, NULL, 0x00080000, 0x11020222);
    if (mpMorf == NULL || mpMorf->getModel() == NULL) {
        return FALSE;
    }
    mpMorf->getModel()->setUserArea((u32)this);

    if (!mInvisibleModel.create(mpMorf->getModel())) {
        return FALSE;
    }

    m_jnt.setHeadJntNum(PZ_JNT_HEAD_e);
    modelData->getJointNodePointer(PZ_JNT_HEAD_e)->setCallBack(nodeHeadControl_CB);
    m_jnt.setBackboneJntNum(PZ_JNT_STOMACH_e);
    modelData->getJointNodePointer(PZ_JNT_STOMACH_e)->setCallBack(nodeWaistControl_CB);
    modelData->getJointNodePointer(PZ_JNT_WAIST_e)->setCallBack(nodeWaist2Control_CB);
    modelData->getJointNodePointer(PZ_JNT_SKIRT_2_e)->setCallBack(nodeSkirtControl_CB);

    J3DAnmTexPattern* btp = static_cast<J3DAnmTexPattern*>(dComIfG_getObjectRes(m_arc_name, dRes_INDEX_PZ_BTP_MABA_A_e));
    JUT_ASSERT(DEMO_SELECT(608, 631), btp != NULL);
    if (!mBtpAnm.init(modelData, btp, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0)) {
        return FALSE;
    }

    J3DAnmTextureSRTKey* btk = static_cast<J3DAnmTextureSRTKey*>(dComIfG_getObjectRes(m_arc_name, dRes_INDEX_PZ_BTK_MABA_A_e));
    JUT_ASSERT(DEMO_SELECT(614, 637), btk != NULL);
    if (!mBtkAnm.init(modelData, btk, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0)) {
        return FALSE;
    }

    u16 num = mBtkAnm.getBtkAnm()->getUpdateMaterialNum();
    for (u16 i = 0; i < num; i++) {
        u16 materialID = mBtkAnm.getBtkAnm()->getUpdateMaterialID(i);
        mpMatAnm[i] = modelData->getMaterialNodePointer(materialID)->getMaterialAnm();
    }

    J3DAnmTevRegKey* brk = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(m_arc_name, dRes_INDEX_PZ_BRK_TRI_TEST_e));
    JUT_ASSERT(DEMO_SELECT(631, 654), brk != NULL);
    if (!mBrkAnm.init(modelData, brk, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0)) {
        return FALSE;
    }

    return TRUE;
}

/* 00000D54-00000E74       .text bowCreateHeap__6daPz_cFv */
BOOL daPz_c::bowCreateHeap() {
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arc_name, dRes_INDEX_PZ_BDL_BOW_e));
    JUT_ASSERT(DEMO_SELECT(648, 671), modelData != NULL);

    mpBowMorf = new mDoExt_McaMorf(modelData, NULL, NULL, NULL, J3DFrameCtrl::EMode_NULL, 1.0f, 0, -1,
                                    TRUE, NULL, 0x00080000, 0x11000022);
    if (mpBowMorf == NULL || mpBowMorf->getModel() == NULL) {
        return FALSE;
    }
    mpBowMorf->getModel()->setUserArea((u32)this);
    return TRUE;
}

/* 00000E74-00000EC0       .text _createHeap__6daPz_cFv */
BOOL daPz_c::_createHeap() {
    if (!bodyCreateHeap()) {
        return false;
    }
    return bowCreateHeap() ? TRUE : FALSE;
}

/* 00000EC0-00000F20       .text __ct__13daPz_matAnm_cFv */
daPz_matAnm_c::daPz_matAnm_c() {
    mbMoveFlag = false;
    mOffset.x = 0.0f;
    mOffset.y = 0.0f;
}

/* 00000F20-00000FB4       .text calc__13daPz_matAnm_cCFP11J3DMaterial */
void daPz_matAnm_c::calc(J3DMaterial* material) const {
    J3DMaterialAnm::calc(material);
    for (u32 i = 0; i < 8; i++) {
        if (getTexMtxAnm(i) != NULL) {
            J3DTexMtx* texMtx = material->getTexGenBlock()->getTexMtx(i);
            if (mbMoveFlag) {
                texMtx->mSRT.mTranslationX = mOffset.x;
                texMtx->mSRT.mTranslationY = mOffset.y;
            }
        }
    }
}

/* 00000FB4-00001038       .text getGndPos__6daPz_cFv */
void daPz_c::getGndPos() {
    fopAc_ac_c* ganon;
    mbHasGanondorf = false;
    if (fopAcM_SearchByName(fpcNm_GND_e, &ganon)) {
        mGanondorfPosOld = ganon->eyePos;
        mGanondorfPos = ganon->current.pos;
        mbHasGanondorf = true;
    }
}

/* 00001038-0000114C       .text checkEyeArea__6daPz_cFR4cXyz */
BOOL daPz_c::checkEyeArea(cXyz& i_pos) {
    s16 targetAngle = cLib_targetAngleY(&current.pos, &i_pos);
    int angleDiff = cLib_distanceAngleS(shape_angle.y, targetAngle);
    f32 dist = (current.pos - i_pos).absXZ();

    if (angleDiff < l_HIO.mEyeAreaAngle && dist < l_HIO.mEyeAreaDist) {
        return TRUE;
    }
    return FALSE;
}

/* 0000114C-00001194       .text getMsg__6daPz_cFv */
u32 daPz_c::getMsg() {
    u32 msgNo = 0x3562;
    if (mPhase == PHASE_SHOOT_GND_e) {
        msgNo = 0x3562;
    } else if (mPhase == PHASE_SHOOT_PLAYER_e) {
        if (mbTalkedOnce == 0) {
            mbTalkedOnce = 1;
            msgNo = 0x3563;
        } else {
            msgNo = 0x3565;
        }
    }
    return msgNo;
}

/* 00001194-00001208       .text next_msgStatus__6daPz_cFPUl */
u16 daPz_c::next_msgStatus(unsigned long* io_msgNo) {
    u16 result = fopMsgStts_MSG_CONTINUES_e;
    switch ((s32)*io_msgNo) {
    case 0x3563:
        *io_msgNo = 0x3564;
        break;
    default:
        if (*io_msgNo == 0x3564) {
            fopAc_ac_c* ganon;
            if (fopAcM_SearchByName(fpcNm_GND_e, &ganon)) {
                if (ganon->stealItemBitNo == 0) {
                    ganon->stealItemBitNo = 35;
                }
            }
        }
        result = fopMsgStts_MSG_ENDS_e;
        break;
    }
    return result;
}

/* 00001208-00001288       .text anmAtr__6daPz_cFUs */
void daPz_c::anmAtr(u16 i_msgStatus) {
    static const s8 anm_atr[] = {ANM_TALK01_e, ANM_TALK02_e};

    switch (i_msgStatus) {
    case fopMsgStts_MSG_TYPING_e:
        if (mbAnmAtrSet == 0) {
            u8 anime_id = dComIfGp_getMesgAnimeAttrInfo();
            mbAnmAtrSet = 1;
            setAnm(anm_atr[anime_id], false, ANM_KEEP_e);
        }
        break;
    case fopMsgStts_MSG_DISPLAYED_e:
        mbAnmAtrSet = 0;
        break;
    }
}

/* 00001288-000012D4       .text eventOrder__6daPz_cFv */
void daPz_c::eventOrder() {
    if (mTalkRequest == 1 || mTalkRequest == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (mTalkRequest == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    }
}

/* 000012D4-00001338       .text checkOrder__6daPz_cFv */
void daPz_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        mTalkRequest = 0;
    } else if (eventInfo.checkCommandTalk()) {
        if (mTalkRequest == 1 || mTalkRequest == 2) {
            mTalkRequest = 0;
            modeProc(PROC_INIT_e, MODE_TALK_e);
        }
    }
}

// Note: dummy function is required to order the cLib_calcTimer instantiations. MWCC emits
// template instantiations in REVERSE order of first instantiation, so touching the u8 form
// here - ahead of setFallSplash, the first user of the int form - is what puts the two in the
// reference's order. Deadstripped at the REL link.
static void dummyTimer() {
    u8 timer = 0;
    cLib_calcTimer(&timer);
}

/* 00001338-0000151C       .text setFallSplash__6daPz_cFv */
void daPz_c::setFallSplash() {
    g_env_light.settingTevStruct(TEV_TYPE_BG1, &current.pos, &mTevStr);

    mFallSplashPos = mEyePos;
    mFallSplashPos.y += l_HIO.mFallSplashYOffset;

    if (mObjAcch.ChkGroundHit()) {
        if (dComIfG_Bgsp()->GetAttributeCode(mObjAcch.m_gnd) == dBgS_Attr_WATERFALL_e) {
            if (mFallSplashCb.getEmitter() == NULL) {
                dComIfGp_particle_set(dPa_name::ID_AK_JN_ELEMENTSHIBUKI00, &mFallSplashPos, &shape_angle, NULL, 0xff, &mFallSplashCb);
                if (mFallSplashCb.getEmitter() != NULL) {
                    mFallSplashCb.getEmitter()->setRate(4.0f);
                    mFallSplashCb.getEmitter()->setSpread(1.0f);
                    mFallSplashCb.getEmitter()->setGlobalPrmColor(mTevStr.mColorC0.r, mTevStr.mColorC0.g,
                                                                   mTevStr.mColorC0.b);
                }
            }
        } else {
            mFallSplashCb.end();
        }

        if (cLib_calcTimer(&mFallRippleTimer) == 0) {
            MtxP anmMtx = mpMorf->getModel()->getAnmMtx(PZ_JNT_WORLD_ROOT_e);
            cXyz pos;
            pos.x = anmMtx[0][3];
            pos.y = anmMtx[1][3];
            pos.z = anmMtx[2][3];
            static Vec fall_ripple_scale = {0.75f, 0.75f, 0.75f};
            dComIfGp_particle_setSingleRipple(dPa_name::ID_IT_JN_WP_HAMON03, &pos, NULL, (cXyz*)&fall_ripple_scale, 0xff);
            mFallRippleTimer = 15;
        }
    } else {
        mFallSplashCb.end();
    }
}

/* 0000151C-000015F4       .text setHeadSplash__6daPz_cFv */
void daPz_c::setHeadSplash() {
    g_env_light.settingTevStruct(TEV_TYPE_BG1, &current.pos, &mTevStr);

    if (mHeadSplashCb.getEmitter() == NULL) {
        dComIfGp_particle_set(dPa_name::ID_AK_SN_PZSHAKEHEADSPLASH00, &mHeadPos, NULL, NULL, 0xff, &mHeadSplashCb);
    }

    if (mHeadSplashCb.getEmitter() != NULL) {
        mHeadSplashCb.getEmitter()->setGlobalPrmColor(mTevStr.mColorC0.r, mTevStr.mColorC0.g,
                                                       mTevStr.mColorC0.b);
        mHeadSplashCb.getEmitter()->setGlobalRTMatrix(mpMorf->getModel()->getAnmMtx(PZ_JNT_HEAD_e));
    }
}

/* 000015F4-00001704       .text setRipple__6daPz_cFv */
void daPz_c::setRipple() {
    if (mObjAcch.ChkGroundHit()) {
        if (dComIfG_Bgsp()->GetAttributeCode(mObjAcch.m_gnd) == dBgS_Attr_WATER_e) {
            if (mRippleCb.getEmitter() == NULL) {
                static cXyz ripple_scale(0.8f, 0.8f, 0.8f);
                dComIfGp_particle_setShipTail(dPa_name::ID_AK_JN_HAMON00, &current.pos, NULL, &ripple_scale, 0xff, &mRippleCb);
                if (mRippleCb.getEmitter() != NULL) {
                    mRippleCb.setRate(0.0f);
                }
            }
        } else {
            mRippleCb.end();
        }
    }
}

/* 00001704-0000175C       .text setJntStatus__6daPz_cFv */
void daPz_c::setJntStatus() {
    m_jnt.setParam(l_HIO.mNpcHIO.mMaxBackboneX, l_HIO.mNpcHIO.mMaxBackboneY,
                   l_HIO.mNpcHIO.mMinBackboneX, l_HIO.mNpcHIO.mMinBackboneY,
                   l_HIO.mNpcHIO.mMaxHeadX, l_HIO.mNpcHIO.mMaxHeadY,
                   l_HIO.mNpcHIO.mMinHeadX, l_HIO.mNpcHIO.mMinHeadY,
                   l_HIO.mNpcHIO.mMaxTurnStep);
}

/* 0000175C-00001954       .text demo__6daPz_cFv */
bool daPz_c::demo() {
    if (demoActorID == 0) {
        if (mbInDemo != 0) {
            mbInDemo = 0;
        }
    } else {
        mbInDemo = 1;

        dDemo_actor_c* demoActor = dComIfGp_demo_getActor(demoActorID);

        for (int i = 0; i < 2; i++) {
            if (mpMatAnm[i] != NULL) {
                ((daPz_matAnm_c*)mpMatAnm[i])->clrMoveFlag();
            }
        }

        if (mBtpAnm.getBtpAnm() != NULL) {
            u8 maxFrame = (u8)mBtpAnm.getBtpAnm()->getFrameMax();
            mEyeBtpFrame++;
            if (mEyeBtpFrame >= maxFrame) {
                mEyeBtpFrame = maxFrame;
            }
        }

        J3DAnmTexPattern* btp = demoActor->getP_BtpData(m_arc_name);
        if (btp != NULL) {
            mBtpAnm.init(mpMorf->getModel()->getModelData(), btp, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE);
            mEyeBtpFrame = 0;
        }

        J3DAnmTextureSRTKey* btk = demoActor->getP_BtkData(m_arc_name);
        if (btk != NULL) {
            mBtkAnm.init(mpMorf->getModel()->getModelData(), btk, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE);
        }

        J3DAnmTevRegKey* brk = (J3DAnmTevRegKey*)demoActor->getP_BrkData(m_arc_name);
        if (brk != NULL) {
            mBrkAnm.init(mpMorf->getModel()->getModelData(), brk, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, FALSE);
        }

        dDemo_setDemoData(this,
                          dDemo_actor_c::ENABLE_TRANS_e | dDemo_actor_c::ENABLE_ROTATE_e |
                              dDemo_actor_c::ENABLE_ANM_e | dDemo_actor_c::ENABLE_ANM_FRAME_e,
                          mpMorf, m_arc_name);
    }

    return mbInDemo;
}

/* 00001954-00001EEC       .text checkTgHit__6daPz_cFv */
bool daPz_c::checkTgHit() {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    mStts.Move();

    if (cLib_calcTimer(&mDamageTimer) == 0) {
        if (mCyl.ChkTgHit()) {
            bool doKnockback = true;
            CcAtInfo at_info;
            cCcD_Obj* hitObj = mCyl.GetTgHitObj();
            mDamageTimer = l_HIO.mDamageTime;

            if (hitObj == NULL) {
                return false;
            }

            switch (((cCcD_ObjAt*)hitObj)->GetType())
            {
                case AT_TYPE_SWORD:
                case AT_TYPE_MACHETE:
                case AT_TYPE_UNK800:
                case AT_TYPE_DARKNUT_SWORD:
                case AT_TYPE_MOBLIN_SPEAR:
                    switch (player->getCutType())
                    {
                        case daPy_py_c::CUT_TYPE_BT_JUMPCUT:
                        case daPy_py_c::CUT_TYPE_CUT_EA:
                        case daPy_py_c::CUT_TYPE_CUT_EB:
                        case daPy_py_c::CUT_TYPE_CUT_TURN:
                        case daPy_py_c::CUT_TYPE_CUT_ROLL:
                        case daPy_py_c::CUT_TYPE_JUMPCUT_SWORD:
                        case daPy_py_c::CUT_TYPE_JUMPCUT_STICK:
                        case daPy_py_c::CUT_TYPE_JUMPCUT_MACHETE:
                        case daPy_py_c::CUT_TYPE_BT_ROLLCUT:
                        case daPy_py_c::CUT_TYPE_BT_VERTICALJUMPCUT:
                        case daPy_py_c::CUT_TYPE_JUMPCUT_CLUB:
                        case daPy_py_c::CUT_TYPE_JUMPCUT_DN_SWORD:
                        case daPy_py_c::CUT_TYPE_JUMPCUT_SPEAR:
                        case daPy_py_c::CUT_TYPE_CUT_EXA:
                        case daPy_py_c::CUT_TYPE_CUT_EXB:
                            mHitType = HIT_SWORD_e;
                            break;
                        default:
                            mHitType = HIT_NONE_e;
                            break;
                        }
                    break;
                case AT_TYPE_WIND:
                    doKnockback = false;
                    mHitType = HIT_WIND_e;
                    break;
                case AT_TYPE_BOOMERANG:
                case AT_TYPE_BOKO_STICK:
                    mHitType = HIT_BOOMERANG_e;
                    break;
                case AT_TYPE_HOOKSHOT:
                    mHitType = HIT_HOOKSHOT_e;
                    break;
                case AT_TYPE_SKULL_HAMMER:
                case AT_TYPE_STALFOS_MACE:
                    mHitType = HIT_HAMMER_e;
                    if (player->getCutType() == daPy_py_c::CUT_TYPE_HAMMER_SIDESWING) {
                        mHitType = HIT_HAMMER_SIDESWING_e;
                    }
                    break;
                case AT_TYPE_BOMB:
                    mHitType = HIT_BOMB_e;
                    break;
                case AT_TYPE_NORMAL_ARROW:
                case AT_TYPE_FIRE_ARROW:
                case AT_TYPE_ICE_ARROW:
                case AT_TYPE_LIGHT_ARROW:
                    mHitType = HIT_ARROW_e;
                    break;
#if VERSION > VERSION_DEMO
                case AT_TYPE_GRAPPLING_HOOK:
                    mHitType = HIT_GRAPPLING_HOOK_e;
                    doKnockback = false;
                    break;
#endif
            }

            fopAc_ac_c* atAc = mCyl.GetTgHitAc();
            if (fopAcM_GetName(atAc) == fpcNm_ARROW_e) {
                daArrow_c* arrow = (daArrow_c*)atAc;
                if (arrow->mbLinkReflect) {
                    mHitType = HIT_ARROW_e;
                } else if (arrow->mbSetByZelda) {
                    return false;
                }
            }

            if (doKnockback) {
                cXyz* hitPos = (cXyz*)mCyl.GetTgHitPosP();
                mKnockbackAngle = fopAcM_searchActorAngleY(this, atAc);
                at_info.mpObj = mCyl.GetTgHitObj();
                def_se_set(this, mCyl.GetTgHitObj(), 0x41);
                dKy_SordFlush_set(*hitPos, 0);

                if (mHitType == HIT_SWORD_e || mHitType == HIT_HAMMER_e ||
                    mHitType == HIT_HAMMER_SIDESWING_e) {
                    mKnockbackSpeed = 60.0f;
                } else {
                    mKnockbackSpeed = 40.0f;
                }

                dComIfGp_particle_set(dPa_name::ID_AK_JN_NG, hitPos, &player->shape_angle, NULL, 0xff, NULL);

                modeProc(PROC_INIT_e, MODE_DEFEND_e);

                if (fopAcM_GetName(atAc) == fpcNm_GND_e) {
                    mbHitFromPlayer = 0;
                    mKnockbackSpeed *= 1.5;
                    mHitWrk[0].m0 = 0;
                    mHitWrk[0].m8 = 0;
                    mHitWrk[1].m0++;
                    if (mHitWrk[1].m0 > l_HIO.mGndHitTrigger) {
                        mHitWrk[1].m0 = 0;
                        mHitWrk[1].m4 = l_HIO.mGndAttackNum;
                        mHitWrk[1].m8 = 1;
                    }
#if VERSION > VERSION_DEMO
                    if (cM_rndF(100.0f) < 60.0f) {
                        fopAcM_monsSeStart(this, JA_SE_CV_ZL_GN_DAMAGE, 0);
                    }
#endif
                } else {
                    mbHitFromPlayer = 1;
                    mHitWrk[1].m0 = 0;
                    mHitWrk[1].m8 = 0;
                    mHitWrk[0].m0++;
                    if (mHitWrk[0].m0 > l_HIO.mPlayerHitTrigger) {
                        mHitWrk[0].m0 = 0;
                        mHitWrk[0].m4 = l_HIO.mPlayerAttackNum;
                        mHitWrk[0].m8 = 1;
                    }
#if VERSION > VERSION_DEMO
                    if (cM_rndF(100.0f) < 30.0f) {
                        fopAcM_monsSeStart(this, JA_SE_CV_ZL_GN_DAMAGE, 0);
                    }
#endif
                }

                mHitPos = *hitPos;
#if VERSION > VERSION_DEMO
            } else if (mHitType == HIT_GRAPPLING_HOOK_e) {
                fopAcM_monsSeStart(this, JA_SE_CV_ZL_GN_DAMAGE, 0);

                int itemNo = dItemNo_HEART_e;
                if (dComIfGs_getLife() <= 0xc) {
                    itemNo = dItemNo_TRIPLE_HEART_e;
                }
                fopAcM_fastCreateItem(&current.pos, itemNo, fopAcM_GetRoomNo(this), &shape_angle, NULL,
                                       0.0f, 0.0f, -6.0f, -1, stealItem_CB);
                modeProc(PROC_INIT_e, MODE_DEFEND_e);
#endif
            }

            return true;
        }
    }

    return false;
}

/* 00001EEC-00001F10       .text getArg__6daPz_cFv */
void daPz_c::getArg() {
    mArg = fopAcM_GetParamBit(fopAcM_GetParam(this), 8, 8);
    if (mArg == 0xff) {
        mArg = 0;
    }
}

/* 00001F10-000020B8       .text setAttention__6daPz_cFv */
void daPz_c::setAttention() {
    attention_info.position = mAttentionPos;
    attention_info.position.y += l_HIO.mAttnYOffset;

    eyePos = mEyePos;

    f32 dist = (mEyePos - mTargetPos).absXZ();

    s16 targetAngle = cLib_targetAngleY(&mEyePos, &mTargetPos);
    cLib_distanceAngleS(shape_angle.y, targetAngle);

    s16 velY;
    if (m_jnt.trnChk()) {
        s16 cut_turn_speed = mEventCut.getTurnSpeed();
        if (cut_turn_speed != 0) {
            velY = cut_turn_speed;
        } else {
            velY = l_HIO.mNpcHIO.mMaxHeadTurnVel;
        }
    } else {
        velY = 0;
    }

    cLib_addCalcAngleS2(&mHeadTurnVel, velY, 4, 0x800);

    m_jnt.lookAtTarget(&shape_angle.y, &mTargetPos, mEyePos, shape_angle.y, mHeadTurnVel,
                        mbNoTurn);
}

/* 000020B8-00002114       .text setBowAnm__6daPz_cFScb */
void daPz_c::setBowAnm(signed char i_anmId, bool i_flag) {
    static const int a_anm_bcks_tbl[] = {
        dRes_INDEX_PZ_BCK_ARROW_RELORD_e,
        dRes_INDEX_PZ_BCK_ARROW_WAIT03_e,
        dRes_INDEX_PZ_BCK_ARROW_SHOOT_e,
    };
    // Indexed by BowAnm_e.
    static const dLib_anm_prm_c a_anm_prm_tbl[] = {
        {
            // BOW_SHOOT_STOP_e
            /* mAnmIdx     */ BOW_BCK_IDX_SHOOT_e,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 0.0f,
            /* mPlaySpeed  */ 0.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            // BOW_SHOOT_e
            /* mAnmIdx     */ BOW_BCK_IDX_SHOOT_e,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 0.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            // BOW_RELORD_e
            /* mAnmIdx     */ BOW_BCK_IDX_RELORD_e,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 0.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            // BOW_WAIT03_e
            /* mAnmIdx     */ BOW_BCK_IDX_WAIT03_e,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 0.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            // BOW_SHOOT_FIRE_e
            /* mAnmIdx     */ BOW_BCK_IDX_SHOOT_e,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 0.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
    };

    if (i_anmId != BOW_KEEP_e) {
        mBowAnmId = i_anmId;
    }
    dLib_bcks_setAnm(m_arc_name, mpBowMorf, (s8*)&mBowBckIdx, (s8*)&mBowAnmId, (s8*)&mOldBowAnmId,
                      a_anm_bcks_tbl, a_anm_prm_tbl, i_flag);
}

/* 00002114-00002184       .text setBowString__6daPz_cFb */
void daPz_c::setBowString(bool i_flag) {
    J3DMaterial* mesh =
        mpBowMorf->getModel()->getModelData()->getJointNodePointer(PZ_BOW_JNT_CL_BOW_e)->getMesh();
    J3DMaterial* string_a = mesh->getNext();
    J3DMaterial* string_b = string_a->getNext();

    if (i_flag) {
        string_a->getShape()->show();
        string_b->getShape()->hide();
    } else {
        string_a->getShape()->hide();
        string_b->getShape()->show();
    }
}

/* 00002184-0000246C       .text setAnm__6daPz_cFScbi */
void daPz_c::setAnm(signed char i_anmId, bool i_flag, int i_eyeAnm) {
    if (i_anmId != ANM_KEEP_e) {
        mAnmId = i_anmId;
    }

    // Indexed by the BCK id in a_anm_prm_tbl's first column, not by Anm_e.
    static const int a_anm_bcks_tbl[] = {
        dRes_INDEX_PZ_BCK_WAIT01_e, dRes_INDEX_PZ_BCK_WAIT02_e,
        dRes_INDEX_PZ_BCK_RUN01_e,  dRes_INDEX_PZ_BCK_RELORD_e,
        dRes_INDEX_PZ_BCK_WAIT03_e, dRes_INDEX_PZ_BCK_SHOOT_e,
        dRes_INDEX_PZ_BCK_DAM01_e,  dRes_INDEX_PZ_BCK_DAM02_e,
        dRes_INDEX_PZ_BCK_STAND_e,  dRes_INDEX_PZ_BCK_DEFEND_e,
        dRes_INDEX_PZ_BCK_WAIT04_e,
    };
    // Indexed by Anm_e.
    dLib_anm_prm_c a_anm_prm_tbl[15] = {
        {
            // ANM_WAIT01_e
            /* mAnmIdx     */ BCK_IDX_WAIT01_e,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            // ANM_WAIT01_B_e
            /* mAnmIdx     */ BCK_IDX_WAIT01_e,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            // ANM_WAIT02_e
            /* mAnmIdx     */ BCK_IDX_WAIT02_e,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            // ANM_RUN01_e
            /* mAnmIdx     */ BCK_IDX_RUN01_e,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            // ANM_RELORD_e
            /* mAnmIdx     */ BCK_IDX_RELORD_e,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 2.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            // ANM_WAIT03_e
            /* mAnmIdx     */ BCK_IDX_WAIT03_e,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            // ANM_SHOOT_e
            /* mAnmIdx     */ BCK_IDX_SHOOT_e,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 2.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            // ANM_DAM01_e - mMorf is overwritten from l_HIO.mDam01Morf below
            /* mAnmIdx     */ BCK_IDX_DAM01_e,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 4.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            // ANM_DAM02_e - mMorf is overwritten from l_HIO.mDam02Morf below
            /* mAnmIdx     */ BCK_IDX_DAM02_e,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 4.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            // ANM_STAND_e
            /* mAnmIdx     */ BCK_IDX_STAND_e,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            // ANM_DEFEND_e
            /* mAnmIdx     */ BCK_IDX_DEFEND_e,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            // ANM_WAIT04_e
            /* mAnmIdx     */ BCK_IDX_WAIT04_e,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            // ANM_TALK01_e
            /* mAnmIdx     */ BCK_IDX_WAIT02_e,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            // ANM_TALK02_e
            /* mAnmIdx     */ BCK_IDX_WAIT02_e,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            // ANM_TALK03_e
            /* mAnmIdx     */ BCK_IDX_WAIT03_e,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
    };
    // indexed by Anm_e: the eye animation that goes with each body animation
    static const s8 eye_anm[] = {
        EYE_MABA_A_e, EYE_MABA_A_e, EYE_MABA_B_e, EYE_MABA_B_e, EYE_BOW_WAIT_e,
        EYE_BOW_WAIT_e, EYE_BOW_WAIT_e, EYE_DAM01_e, EYE_DAM02_e, EYE_STAND_e,
        EYE_DEFEND_e, EYE_WAIT04_e, EYE_TALK01_e, EYE_TALK02_e, EYE_TALK01_e,
    };

    a_anm_prm_tbl[ANM_DAM01_e].mMorf = l_HIO.mDam01Morf;
    a_anm_prm_tbl[ANM_DAM02_e].mMorf = l_HIO.mDam02Morf;

    if (mOldAnmId != mAnmId) {
        if (mAnmId == ANM_RELORD_e) {
            fopAcM_monsSeStart(this, JA_SE_CV_ZL_DRAW_BOW, 0);
            setBowAnm(BOW_RELORD_e, false);
            mArrowID = fopAcM_createChild(fpcNm_ARROW_e, fopAcM_GetID(this), 0, &current.pos,
                                              fopAcM_GetRoomNo(this), NULL, NULL, -1, NULL);
        }

        if (mAnmId == ANM_WAIT03_e) {
            setBowAnm(BOW_WAIT03_e, true);
        }

        if (mAnmId == ANM_SHOOT_e) {
            fopAcM_monsSeStart(this, JA_SE_CV_ZL_SHOOT_BOW, 0);
            setBowAnm(BOW_SHOOT_FIRE_e, true);

            fopAc_ac_c* child;
            if (fopAcM_SearchByID(mArrowID, &child)) {
                fopAcM_SetParam(child, 1);
            }
        }

        if (mAnmId != ANM_RELORD_e && mAnmId != ANM_WAIT03_e) {
            fopAc_ac_c* child;
            if (fopAcM_SearchByID(mArrowID, &child)) {
                fopAcM_SetParam(child, 1);
            }
        }

        if (mAnmId == ANM_STAND_e) {
            setHeadSplash();
        } else {
            mHeadSplashCb.end();
        }

        if (mAnmId == ANM_RELORD_e || mAnmId == ANM_WAIT03_e || mAnmId == ANM_SHOOT_e) {
            setBowString(true);
        } else {
            setBowAnm(BOW_SHOOT_e, true);
            setBowString(false);
        }

        if (i_eyeAnm == ANM_KEEP_e) {
            setEyeAnm(eye_anm[mAnmId]);
        } else {
            setEyeAnm(eye_anm[i_eyeAnm]);
        }
    }

    dLib_bcks_setAnm(m_arc_name, mpMorf, &mBckIdx, &mAnmId, &mOldAnmId, a_anm_bcks_tbl,
                     a_anm_prm_tbl, i_flag);
}

/* 0000246C-00002684       .text setAnmRunSpeed__6daPz_cFv */
void daPz_c::setAnmRunSpeed() {
    if (mAnmId == ANM_RUN01_e) {
        f32 dist = (current.pos - old.pos).abs();

        f32 speed = dist / (10.0f + REG12_F(6));
        if (speed <= 0.0f) {
            speed = 0.0f;
        } else if (speed >= 1.0f) {
            speed = 1.0f;
        }

        speed *= l_HIO.mRunAnmRate;
        speed = cLib_minLimit(speed, l_HIO.mRunAnmRateMin);
        speed = cLib_maxLimit(speed, l_HIO.mRunAnmRateMax);

        mpMorf->setPlaySpeed(speed);

        int frame = (int)mpMorf->getFrame();
        if (frame == 7 || frame == 0xe) {
            static JGeometry::TVec3<f32> run_splash_scale(0.6f, 0.6f, 0.6f);

            int unused;
            JPABaseEmitter* emitter = dComIfGp_particle_setSimpleLand(
                mObjAcch.m_gnd, &current.pos, &shape_angle, 1.25f, 1.5f, 1.0f, &tevStr, &unused, 7);
            if (emitter != NULL) {
                emitter->setRate(18.0f);
                emitter->setSpread(1.0f);
                emitter->setGlobalScale(run_splash_scale);
            }
        }
    }
}

/* 00002684-0000274C       .text setEyeBtp__6daPz_cFi */
void daPz_c::setEyeBtp(int i_eyeBtp) {
    J3DModel* model = mpMorf->getModel();
    J3DAnmTexPattern* btp = (J3DAnmTexPattern*)dComIfG_getObjectRes(m_arc_name, i_eyeBtp);
    JUT_ASSERT(DEMO_SELECT(1590, 1667), btp != NULL);

    mEyeBtpFrame = 0;
    mBtpAnm.init(model->getModelData(), btp, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true);
}

/* 0000274C-00002810       .text setEyeBtk__6daPz_cFi */
void daPz_c::setEyeBtk(int i_eyeBtk) {
    J3DModel* model = mpMorf->getModel();
    J3DAnmTextureSRTKey* btk = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes(m_arc_name, i_eyeBtk);
    JUT_ASSERT(DEMO_SELECT(1604, 1681), btk != NULL);

    mBtkAnm.init(model->getModelData(), btk, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true);
}

/* 00002810-00002888       .text setEyeAnm__6daPz_cFSc */
void daPz_c::setEyeAnm(signed char i_eyeAnm) {
    // Indexed by EyeAnm_e: {BTP, BTK}, -1 meaning "leave that channel alone".
    static const int a_eye_tbl[][2] = {
        {dRes_INDEX_PZ_BTP_MABA_A_e,   dRes_INDEX_PZ_BTK_MABA_A_e},
        {dRes_INDEX_PZ_BTP_BOW_WAIT_e, dRes_INDEX_PZ_BTK_BOW_WAIT_e},
        {dRes_INDEX_PZ_BTP_DAM01_e,    -1},
        {dRes_INDEX_PZ_BTP_DAM02_e,    -1},
        {dRes_INDEX_PZ_BTP_STAND_e,    dRes_INDEX_PZ_BTK_STAND_e},
        {dRes_INDEX_PZ_BTP_DEFEND_e,   -1},
        {dRes_INDEX_PZ_BTP_WAIT04_e,   -1},
        {dRes_INDEX_PZ_BTP_MABA_B_e,   dRes_INDEX_PZ_BTK_MABA_A_e},
        {dRes_INDEX_PZ_BTP_TALK01_e,   -1},
        {dRes_INDEX_PZ_BTP_TALK02_e,   -1},
    };

    if (a_eye_tbl[i_eyeAnm][0] != -1) {
        setEyeBtp(a_eye_tbl[i_eyeAnm][0]);
    }
    if (a_eye_tbl[i_eyeAnm][1] != -1) {
        setEyeBtk(a_eye_tbl[i_eyeAnm][1]);
    }
    mCurEye = i_eyeAnm;
}

/* 00002888-00002AE0       .text ctrlEye__6daPz_cFv */
void daPz_c::ctrlEye() {
    mEyeTargetPos = mTargetPos;

    s16 pitchAngle = cLib_targetAngleX(&mEyePos, &mEyeTargetPos);

    s16 diffYaw = cLib_targetAngleY(&mEyePos, &mEyeTargetPos);
    diffYaw -= (s16)(shape_angle.y + m_jnt.getHead_y() + m_jnt.getBackbone_y());

    s16 diffPitch = pitchAngle - (s16)(m_jnt.getHead_x() + m_jnt.getBackbone_x());

    f32 pitchDeg = diffPitch / 8192.0f;
    f32 yawDeg = diffYaw / 8192.0f;

    f32 min = -0.1f;
    f32 max = 0.1f;

    pitchDeg = max * pitchDeg;
    yawDeg = max * yawDeg;

    u8 in_range = 0;
    if (pitchDeg >= min && pitchDeg <= max) {
        in_range = 1;
    }
    mbEyeInRange = in_range != 0;

    in_range = 0;
    if (yawDeg >= min && yawDeg <= max) {
        in_range = 1;
    }
    mbEyeInRange = in_range != 0;

    pitchDeg = cLib_minMaxLimit(pitchDeg, min, max);
    yawDeg = cLib_minMaxLimit(yawDeg, min, max);

    if (mMode == MODE_ATTACK_e) {
        yawDeg = max;
    }

    if (mpMatAnm[0] != NULL) {
        cLib_addCalc(((daPz_matAnm_c*)mpMatAnm[0])->getNowOffsetX(), yawDeg, 0.5f, 0.1f, 0.03f);
        cLib_addCalc(((daPz_matAnm_c*)mpMatAnm[0])->getNowOffsetY(), pitchDeg, 0.5f, 0.1f, 0.03f);
    }

    yawDeg *= -1.0f;

    if (mpMatAnm[1] != NULL) {
        cLib_addCalc(((daPz_matAnm_c*)mpMatAnm[1])->getNowOffsetX(), yawDeg, 0.5f, 0.1f, 0.03f);
        cLib_addCalc(((daPz_matAnm_c*)mpMatAnm[1])->getNowOffsetY(), pitchDeg, 0.5f, 0.1f, 0.03f);
    }
}

/* 00002AE0-00002D38       .text playEyeAnm__6daPz_cFv */
void daPz_c::playEyeAnm() {
    bool doCtrlEye = true;

    if (mCurEye == EYE_MABA_A_e || mCurEye == EYE_MABA_B_e) {
        if (cLib_calcTimer(&mBlinkTimer) == 0) {
            mEyeBtpFrame++;
            if ((f32)mEyeBtpFrame > mBtpAnm.getEndFrame()) {
                mBlinkTimer = (s16)(int)(cM_rndF(100.0f) + 100.0f);
                mEyeBtpFrame = 0;
            }
        }
    } else if (mCurEye == EYE_BOW_WAIT_e || mCurEye == EYE_DAM01_e || mCurEye == EYE_DEFEND_e || mCurEye == EYE_WAIT04_e) {
        mEyeBtpFrame = 1;
    } else {
        mEyeBtpFrame++;
        if ((f32)mEyeBtpFrame > mBtpAnm.getEndFrame()) {
            mBlinkTimer = (s16)(int)(cM_rndF(100.0f) + 100.0f);
            mEyeBtpFrame = (u8)(f32)mBtpAnm.getFrameCtrl()->getEnd();
        }
    }

    if (mCurEye == EYE_STAND_e) {
        doCtrlEye = false;
    }

    if (doCtrlEye) {
        for (int i = 0; i < 2; i++) {
            if (mpMatAnm[i] != NULL) {
                ((daPz_matAnm_c*)mpMatAnm[i])->setMoveFlag();
            }
        }
        ctrlEye();
    } else {
        for (int i = 0; i < 2; i++) {
            if (mpMatAnm[i] != NULL) {
                ((daPz_matAnm_c*)mpMatAnm[i])->clrMoveFlag();
            }
        }
        mBtkAnm.play();
    }
}

/* 00002D38-00002DC8       .text setMtx__6daPz_cFv */
void daPz_c::setMtx() {
    mpMorf->getModel()->setBaseScale(scale);

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00002DC8-00002E2C       .text modeWaitInit__6daPz_cFv */
void daPz_c::modeWaitInit() {
    mTargetSpeedF = 0.0f;
    setAnm(ANM_WAIT01_B_e, false, ANM_KEEP_e);
    m_jnt.clrTrn();
    mbNoTurn = 1;
    m_jnt.onHeadLock();
    m_jnt.onBackBoneLock();
    mTimer = 30;
}

/* 00002E2C-00002FE8       .text modeWait__6daPz_cFv */
void daPz_c::modeWait() {
    mTargetPos = dNpc_playerEyePos(l_HIO.mNpcHIO.m04);

    dEvent_manager_c& evtMng = g_dComIfG_gameInfo.play.getEvtManager();
    s16 eventIdx = evtMng.getEventIdx("btl_of_swroom", 0xff);
    if (evtMng.getEventData(eventIdx) != NULL) {
        int staffId = evtMng.getMyStaffId("p_zelda", NULL, 0);
        if (staffId != -1) {
            if (strcmp(evtMng.getMyNowCutName(staffId), "Turn") == 0) {
                mbNoTurn = 0;
                m_jnt.setTrn();
                m_jnt.offHeadLock();
                m_jnt.offBackBoneLock();
                if (cLib_calcTimer(&mTimer) == 0) {
                    evtMng.cutEnd(staffId);
                }
                return;
            } else if (strcmp(evtMng.getMyNowCutName(staffId), "Retire") == 0) {
                mBlinkTimer = 0;
                if (mEyeBtpFrame >= REG8_S(0) + 4) {
                    mEyeBtpFrame = (u8)(REG8_S(0) + 4);
                    mEnemyIce.mLightShrinkTimer = 1;
                    mBlinkTimer = 1000;
                    evtMng.cutEnd(staffId);
                }
                return;
            } else {
                if (mEnemyIce.mLightShrinkTimer == 0) {
                    mBlinkTimer = 1000;
                }
                m_jnt.clrTrn();
            }
        }
    } else {
        m_jnt.clrTrn();
        mbNoTurn = 1;
        m_jnt.onHeadLock();
        m_jnt.onBackBoneLock();
    }
}


/* 00002FE8-000031E8       .text modeMoveInit__6daPz_cFv */
void daPz_c::modeMoveInit() {
    cLib_onBit(attention_info.flags, (u32)fopAc_Attn_ACTION_SPEAK_e);
    cLib_onBit(attention_info.flags, (u32)fopAc_Attn_LOCKON_TALK_e);

    mTimer = (int)(l_HIO.mMoveTimeBase[mPhase] + cM_rndF(l_HIO.mMoveTimeRand[mPhase]));
    mRetreatTimer = 10;
    mStepWaitTimer = 120;

    setAnm(ANM_RUN01_e, false, ANM_KEEP_e);

    if (cM_rndF(100.0f) < l_HIO.mTurnDirChangeRate) {
        if (mTurnDir == 1) {
            mTurnDir = -1;
        } else {
            mTurnDir = 1;
        }
    }

    if (l_HIO.mbFixTarget == 0) {
        if (mbHasGanondorf) {
            mTargetPos = mGanondorfPosOld;
        }
    } else {
        mTargetPos = dNpc_playerEyePos(l_HIO.mNpcHIO.m04);
    }

    mCirclePath.mRadius = l_HIO.mCircleRadius[mPhase];
    mCirclePath.mWobbleAmplitude = l_HIO.mCircleWobble;

    mCirclePath.mAngleSpeed = (REG12_S(0) + 0x150) * mTurnDir;

    mCirclePath.mTranslation = mTargetPos;

    dLib_setCirclePath(&mCirclePath);

    mbNoTurn = 0;
    m_jnt.clrTrn();
    m_jnt.offHeadLock();
    m_jnt.offBackBoneLock();
}

/* 000031E8-0000395C       .text modeMove__6daPz_cFv */
void daPz_c::modeMove() {
    if (l_HIO.mbDoSideStep != 0) {
        l_HIO.mbDoSideStep = 0;
        modeProc(PROC_INIT_e, MODE_SIDE_STEP_e);
        return;
    }

    if (l_HIO.mDbgFlags[0] != 0) {
        l_HIO.mDbgFlags[0] = 0;
        modeProc(PROC_INIT_e, MODE_BACK_STEP_e);
        return;
    }

    bool path_blocked = false;

    mLinChk.Set(&current.pos, &mCirclePath.mPos, this);
    if (dComIfG_Bgsp()->LineCross(&mLinChk)) {
        path_blocked = true;
    }
    if (mObjAcch.ChkWallHit()) {
        path_blocked = true;
    }

    if (cLib_calcTimer(&mWallTurnTimer) == 0 && path_blocked) {
        mWallTurnTimer = 60;
        if (mTurnDir == 1) {
            mTurnDir = -1;
        } else {
            mTurnDir = 1;
        }
        mCirclePath.mAngleSpeed = (s16)((REG12_S(0) + 0x4000) * mTurnDir);

        if (cLib_calcTimer(&mStepWaitTimer) == 0) {
            dLib_setCirclePath(&mCirclePath);
            modeProc(PROC_INIT_e, MODE_SIDE_STEP_e);
        }
    }

    if (checkTgHit()) {
        return;
    }

    if (l_HIO.mbFixTarget == 0) {
        if (mbHasGanondorf) {
            mTargetPos = mGanondorfPosOld;
        }
    } else {
        mTargetPos = dNpc_playerEyePos(l_HIO.mNpcHIO.m04);
    }

    m_jnt.clrTrn();

    cLib_addCalc2(&mCirclePath.mRadius, l_HIO.mCircleRadius[mPhase], 0.1f, 10.0f);

    f32 dist_to_path_pos = (current.pos - mCirclePath.mPos).absXZ();
    f32 dist_to_target_unused = (current.pos - mTargetPos).absXZ();
    f32 distTargetPathed = (mTargetPos - mCirclePath.mPos).absXZ();

    if (dist_to_path_pos > 200.0f + REG12_F(7) || !mbGndInEyeArea) {
        mTargetSpeedF = l_HIO.mRunSpeed;
    } else {
        mTargetSpeedF = 0.0f;
    }

    if (path_blocked || dist_to_path_pos <= 200.0f ||
        distTargetPathed >= 2.0f * (l_HIO.mCircleRadius[mPhase]) || mbGndInEyeArea) {
        mCirclePath.mWobbleAmplitude = l_HIO.mCircleWobble;
        mCirclePath.mAngleSpeed = (s16)((REG12_S(0) + 0x150) * mTurnDir);
        mCirclePath.mTranslation = mTargetPos;
        dLib_setCirclePath(&mCirclePath);
    }

    if (cLib_calcTimer(&mRetreatTimer) == 0) {
        f32 distToGanondorf = 100000.0f;
        f32 dist_to_target = (current.pos - mTargetPos).absXZ();
        if (mbHasGanondorf) {
            distToGanondorf = (current.pos - mGanondorfPos).absXZ();
        }
        if (mbGndInEyeArea) {
            if (dist_to_target < l_HIO.mRetreatDist || distToGanondorf < l_HIO.mRetreatDist) {
                mPrevMode = mMode;
                modeProc(PROC_INIT_e, MODE_BACK_STEP_e);
                return;
            }
        }
    }

    s16 targetAngle = cLib_targetAngleY(&current.pos, &mCirclePath.mPos);
    cLib_addCalcAngleS2(&shape_angle.y, targetAngle, 8, 0x400);

    if (speedF < 0.5f) {
        setAnm(ANM_WAIT02_e, false, ANM_KEEP_e);
    } else {
        setAnm(ANM_RUN01_e, false, ANM_KEEP_e);
    }

#if VERSION > VERSION_DEMO
    if (mPhase == PHASE_SHOOT_PLAYER_e) {
        fopAc_ac_c* player = dComIfGp_getLinkPlayer();
        BOOL inFan = dLib_checkActorInFan(player->current.pos, this, player->shape_angle.y,
                                           0x2500, 30000.0f, 1000.0f);
        mbPlayerInFan = inFan;
    }
#endif

    if (l_HIO.mDbgFlags[1] == 0 && cLib_calcTimer(&mTimer) == 0) {
#if VERSION > VERSION_DEMO
        if (mPhase == PHASE_SHOOT_GND_e) {
            modeProc(PROC_INIT_e, MODE_ATTACK_WAIT_e);
        } else if (mPhase == PHASE_SHOOT_PLAYER_e) {
            if (mbTalkedOnce == 0) {
                mbPlayerInFan = 1;
            }
            if (mbPlayerInFan != 0) {
                modeProc(PROC_INIT_e, MODE_ATTACK_WAIT_e);
            }
        }
#else
        modeProc(PROC_INIT_e, MODE_ATTACK_WAIT_e);
#endif
    }

    mTalkRequest = 2;
}

/* 0000395C-000039C0       .text modeAttackWaitInit__6daPz_cFv */
void daPz_c::modeAttackWaitInit() {
    mTargetSpeedF = 0.0f;
    mTimer = 20;
    mRetreatTimer = 10;
    setAnm(ANM_WAIT02_e, false, ANM_KEEP_e);
    mbNoTurn = 0;
    m_jnt.offHeadLock();
    m_jnt.offBackBoneLock();
}

/* 000039C0-00003D88       .text modeAttackWait__6daPz_cFv */
void daPz_c::modeAttackWait() {
    if (checkTgHit()) {
        return;
    }

    if (l_HIO.mbFixTarget == 0) {
        if (mbHasGanondorf) {
            mTargetPos = mGanondorfPosOld;
        }
    } else {
        mTargetPos = dNpc_playerEyePos(l_HIO.mNpcHIO.m04);
    }

    if (cLib_calcTimer(&mRetreatTimer) == 0) {
        f32 distActor = (current.pos - mTargetPos).absXZ();
        f32 distGanon = 100000.0f;
        if (mbHasGanondorf) {
            distGanon = (current.pos - mGanondorfPos).absXZ();
        }

        if (mbGndInEyeArea &&
            (distActor < l_HIO.mRetreatDist || distGanon < l_HIO.mRetreatDist)) {
            mPrevMode = mMode;
            if (cM_rndF(100.0f) < 50.0f) {
                modeProc(PROC_INIT_e, MODE_BACK_STEP_e);
            } else {
                modeProc(PROC_INIT_e, MODE_SIDE_STEP_e);
            }
            return;
        }
    }

#if VERSION > VERSION_DEMO
    if (mPhase == PHASE_SHOOT_GND_e) {
        fopAc_ac_c* ganon;
        if (fopAcM_SearchByName(fpcNm_GND_e, &ganon) && ganon->health > 0x3c &&
            dComIfGs_getLife() >= 0xc && mHitWrk[0].m8 != 0) {
            mTargetPos = dNpc_playerEyePos(l_HIO.mNpcHIO.m04);
        }

        if (mHitWrk[1].m8 != 0 && mbHasGanondorf) {
            mTargetPos = mGanondorfPosOld;
        }
    } else
#endif
    {
        if (mHitWrk[0].m8 != 0) {
            mTargetPos = dNpc_playerEyePos(l_HIO.mNpcHIO.m04);
        }

        if (mHitWrk[1].m8 != 0 && mbHasGanondorf) {
            mTargetPos = mGanondorfPosOld;
        }
    }

    if (l_HIO.mbEnableAttack != 0) {
        if (cLib_calcTimer(&mTimer) == 0) {
            modeProc(PROC_INIT_e, MODE_ATTACK_e);
        }
    }

    m_jnt.setTrn();
}

/* 00003D88-00003F14       .text modeAttackInit__6daPz_cFv */
void daPz_c::modeAttackInit() {
    mStepWaitTimer = 30;

    int down_idx = mPhase;
    if (mbTalkedOnce == 0) {
        down_idx = PHASE_SHOOT_GND_e;
    }

    if (mAnmId != ANM_RELORD_e && mAnmId != ANM_WAIT03_e) {
        mTimer = (int)((f32)l_HIO.mAttackTimeBase[down_idx] +
                       cM_rndF((f32)l_HIO.mAttackTimeRand[down_idx]));
        mRetreatTimer = l_HIO.mRetreatTime[down_idx];
        setAnm(ANM_RELORD_e, false, ANM_KEEP_e);
    }

    if (cM_rndF(100.0f) < l_HIO.mAimPlayerRate[down_idx]) {
        mbAimAtPlayer = 1;
    } else {
        mbAimAtPlayer = 0;
        if (cM_rndF(100.0f) < l_HIO.mAimStraightRate[down_idx]) {
            mAimSpread = 0.0f;
        } else {
            mAimSpread = cM_rndF(l_HIO.mAimOffsetMax[down_idx]);
        }
    }

    mbNoTurn = 0;
    m_jnt.onHeadLock();
    m_jnt.offBackBoneLock();
}

/* 00003F14-0000445C       .text modeAttack__6daPz_cFv */
void daPz_c::modeAttack() {
    if (checkTgHit()) {
        return;
    }

    cXyz unused(mAimSpread, mAimSpread, mAimSpread);

    if (mbAimAtPlayer == 0) {
        if (mbHasGanondorf) {
            mTargetPos = mGanondorfPosOld;
        }
    } else {
        mTargetPos = dNpc_playerEyePos(l_HIO.mNpcHIO.m04);
    }

#if VERSION > VERSION_DEMO
    if (mPhase == PHASE_SHOOT_GND_e) {
        fopAc_ac_c* ganon;
        if (fopAcM_SearchByName(fpcNm_GND_e, &ganon) && ganon->health > 0x3c &&
            dComIfGs_getLife() >= 0xc && mHitWrk[0].m8 != 0) {
            mTargetPos = dNpc_playerEyePos(l_HIO.mNpcHIO.m04);
        }
        if (mHitWrk[1].m8 != 0 && mbHasGanondorf) {
            mTargetPos = mGanondorfPosOld;
        }
    } else
#endif
    {
        if (mHitWrk[0].m8 != 0) {
            mTargetPos = dNpc_playerEyePos(l_HIO.mNpcHIO.m04);
        }
        if (mHitWrk[1].m8 != 0 && mbHasGanondorf) {
            mTargetPos = mGanondorfPosOld;
        }
    }

    if (mAnmId == ANM_RELORD_e || mAnmId == ANM_WAIT03_e) {
        if (cLib_calcTimer(&mStepWaitTimer) == 0) {
            f32 distActor = (current.pos - mTargetPos).absXZ();
            f32 distGanon = 100000.0f;
            if (mbHasGanondorf) {
                distGanon = (current.pos - mGanondorfPos).absXZ();
            }

            if (mbGndInEyeArea &&
                (distActor < l_HIO.mRetreatDist || distGanon < l_HIO.mRetreatDist)) {
                mPrevMode = mMode;
                if (cM_rndF(100.0f) < 50.0f) {
                    modeProc(PROC_INIT_e, MODE_BACK_STEP_e);
                } else {
                    modeProc(PROC_INIT_e, MODE_SIDE_STEP_e);
                }
                return;
            }
        }
    }

    if (mAnmId == ANM_RELORD_e && mpMorf->isStop()) {
        m_jnt.setTrn();
        setAnm(ANM_WAIT03_e, false, ANM_KEEP_e);
    } else if (mAnmId == ANM_WAIT03_e) {
        m_jnt.setTrn();
        if (cLib_calcTimer(&mTimer) == 0) {
            setAnm(ANM_SHOOT_e, false, ANM_KEEP_e);
        }
    } else if (mAnmId == ANM_SHOOT_e) {
        if (mpMorf->isStop()) {
            m_jnt.clrTrn();

            if (mHitWrk[0].m8 != 0) {
                mHitWrk[0].m4--;
                if (cLib_calcTimer(&mHitWrk[0].m4) != 0) {
                    modeProc(PROC_INIT_e, MODE_ATTACK_WAIT_e);
                } else {
                    mHitWrk[0].m8 = 0;
                }
            } else if (mHitWrk[1].m8 != 0) {
                mHitWrk[1].m4--;
                if (cLib_calcTimer(&mHitWrk[1].m4) != 0) {
                    modeProc(PROC_INIT_e, MODE_ATTACK_WAIT_e);
                } else {
                    mHitWrk[1].m8 = 0;
                }
            } else if (cLib_calcTimer(&mRetreatTimer) == 0) {
                modeProc(PROC_INIT_e, MODE_MOVE_e);
            } else {
                mbNoTurn = 1;
            }
        }
    }
}

/* 0000445C-000044B4       .text modeDefendInit__6daPz_cFv */
void daPz_c::modeDefendInit() {
    setAnm(ANM_DEFEND_e, true, ANM_KEEP_e);
    mTimer = 30;
    m_jnt.clrTrn();
    m_jnt.onHeadLock();
    m_jnt.onBackBoneLock();
    mbNoTurn = 1;
}

/* 000044B4-00004630       .text modeDefend__6daPz_cFv */
void daPz_c::modeDefend() {
    mTargetSpeedF = 0.0f;
    m_jnt.clrTrn();

    s16 angle = cLib_targetAngleY(&current.pos, &mHitPos);
    cLib_addCalcAngleS2(&shape_angle.y, angle, 4, 0x1000);
    cLib_distanceAngleS(shape_angle.y, angle);

    if (mKnockbackSpeed > 0.01f) {
        int land_prm;
        cXyz offset(0.0f, 0.0f, -mKnockbackSpeed);
        cXyz move(0.0f, 0.0f, 0.0f);

        mDoMtx_stack_c::YrotS(mKnockbackAngle);
        mDoMtx_stack_c::multVec(&offset, &move);
        current.pos += move;

        cLib_addCalc0(&mKnockbackSpeed, 1.0f, 7.0f);
        dComIfGp_particle_setSimpleLand(mObjAcch.m_gnd, &current.pos, &shape_angle, 1.25f, 1.5f,
                                        1.0f, &tevStr, &land_prm, 7);
    } else if (mHitWrk[0].m8 != 0 || mHitWrk[1].m8 != 0) {
        modeProc(PROC_INIT_e, MODE_ATTACK_WAIT_e);
    } else if (cLib_calcTimer(&mTimer) == 0) {
        modeProc(PROC_INIT_e, MODE_MOVE_e);
    }

    if (checkTgHit()) {
        return;
    }
}

/* 00004630-0000470C       .text modeDownInit__6daPz_cFv */
void daPz_c::modeDownInit() {
    cLib_offBit(attention_info.flags, (u32)fopAc_Attn_ACTION_SPEAK_e);
    cLib_offBit(attention_info.flags, (u32)fopAc_Attn_LOCKON_TALK_e);

    setAnm(ANM_DAM01_e, true, ANM_KEEP_e);
    fopAcM_monsSeStart(this, JA_SE_CV_ZL_GN_DAMAGE, 0);

    mbNoTurn = 1;
    mTargetSpeedF = 0.0f;
    speedF = 0.0f;
    mbNoTurn = 0;

    m_jnt.clrTrn();
    m_jnt.onHeadLock();
    m_jnt.onBackBoneLock();

    speed.y = l_HIO.mDownJumpY;
    mStepSpeed = l_HIO.mDownSpeed;
    mTimer = l_HIO.mDownTime;
}

/* 0000470C-00004C20       .text modeDown__6daPz_cFv */
void daPz_c::modeDown() {
    int land_prm;

    mTargetSpeedF = 0.0f;
    speedF = 0.0f;
    m_jnt.clrTrn();

    if (mAnmId == ANM_DAM01_e && mpMorf->getMorfRatio() == 1.0f && mObjAcch.ChkGroundHit()) {
        setAnm(ANM_DAM02_e, false, ANM_KEEP_e);
    }

    if (cLib_calcTimer(&mTimer) != 0) {
        cXyz offset(mStepSpeed, 0.0f, 0.0f);
        cXyz move(0.0f, 0.0f, 0.0f);

        mDoMtx_stack_c::YrotS(shape_angle.y);
        mDoMtx_stack_c::multVec(&offset, &move);
        current.pos += move;

        if (mAnmId == ANM_DAM02_e && mpMorf->isStop()) {
            dComIfGp_particle_setSimpleLand(mObjAcch.m_gnd, &current.pos, &shape_angle, 1.25f, 1.5f,
                                             1.0f, &tevStr, &land_prm, 7);
        }
    }

    int frame = (int)mpMorf->getFrame();

    if (mAnmId == ANM_DAM02_e) {
        if ((f32)frame == 1.0f + REG12_F(10)) {
            static JGeometry::TVec3<f32> run_splash_scale(0.6f, 0.6f, 0.6f);
            JPABaseEmitter* emitter = dComIfGp_particle_setSimpleLand(
                mObjAcch.m_gnd, &current.pos, &shape_angle, 2.5f, 3.0f, 2.0f, &tevStr, &land_prm, 7);
            if (emitter != NULL) {
                emitter->setRate(18.0f);
                emitter->setSpread(1.0f);
                emitter->setGlobalScale(run_splash_scale);
            }
        }

        if ((f32)frame == 2.0f + REG12_F(10)) {
            static JGeometry::TVec3<f32> run_splash_scale(0.6f, 0.6f, 0.6f);
            JPABaseEmitter* emitter = dComIfGp_particle_setSimpleLand(
                mObjAcch.m_gnd, &mWaistPos, &shape_angle, 2.5f, 3.0f, 2.0f, &tevStr, &land_prm, 7);
            if (emitter != NULL) {
                emitter->setRate(18.0f);
                emitter->setSpread(1.0f);
                emitter->setGlobalScale(run_splash_scale);
            }
        }

        if ((f32)frame == 3.0f + REG12_F(10)) {
            static JGeometry::TVec3<f32> run_splash_scale(0.6f, 0.6f, 0.6f);
            JPABaseEmitter* emitter = dComIfGp_particle_setSimpleLand(
                mObjAcch.m_gnd, &mEyePos, &shape_angle, 2.5f, 3.0f, 2.0f, &tevStr, &land_prm, 7);
            if (emitter != NULL) {
                emitter->setRate(18.0f);
                emitter->setSpread(1.0f);
                emitter->setGlobalScale(run_splash_scale);
            }
        }
    }

    if (mAnmId == ANM_DAM02_e && mpMorf->isStop()) {
        mbNoTurn = 1;
    }

    if (mPhase == PHASE_DOWN_e) {
        return;
    }

    if (mAnmId == ANM_STAND_e) {
        if (mpMorf->isStop()) {
            mbNoTurn = 0;
            setAnm(ANM_WAIT02_e, false, ANM_KEEP_e);
        }
    } else if (mbMoveRequest) {
        mbMoveRequest = 0;
#if VERSION > VERSION_DEMO
        mTalkTimer = l_HIO.mTalkTime[PHASE_SHOOT_PLAYER_e];
        mbTalkDone = 0;
        mHitWrk[0].m8 = 0;
        mHitWrk[1].m8 = 0;
#endif
        modeProc(PROC_INIT_e, MODE_MOVE_e);
    } else {
        setAnm(ANM_STAND_e, false, ANM_KEEP_e);
    }
}

/* 00004C20-00004C78       .text modeAfraidInit__6daPz_cFv */
void daPz_c::modeAfraidInit() {
    setAnm(ANM_WAIT04_e, true, ANM_KEEP_e);
    mTargetSpeedF = 0.0f;
    speedF = 0.0f;
    mbNoTurn = 0;
    m_jnt.offHeadLock();
    m_jnt.offBackBoneLock();
}

/* 00004C78-00004E8C       .text modeAfraid__6daPz_cFv */
void daPz_c::modeAfraid() {
    fopAc_ac_c* gnd;

    mTargetSpeedF = 0.0f;
    speedF = 0.0f;
    mbNoTurn = 0;
    m_jnt.clrTrn();
    mbAfraidRequest = 0;
    m_jnt.offHeadLock();
    m_jnt.offBackBoneLock();

    if (fopAcM_SearchByName(fpcNm_GND_e, &gnd)) {
        if (REG12_S(9) == 1) {
            mTargetPos = gnd->current.pos;
            mTargetPos.y = mTargetPos.y + (1200.0f + REG12_F(10));
        } else if (REG12_S(9) == 2) {
            mTargetPos = gnd->eyePos;
            mTargetPos.y = mTargetPos.y + (800.0f + REG12_F(10));
        } else {
            mTargetPos = gnd->current.pos;

            f32 dist = (current.pos - gnd->current.pos).absXZ();
            f32 min_y = 50.0f + gnd->current.pos.y;
            mTargetPos.y = 8.0f * (gnd->eyePos.y - dist / 2.0f);

            if (mTargetPos.y <= min_y) {
                mTargetPos.y = min_y;
            }
        }

        cLib_addCalcAngleS2(&shape_angle.y, cLib_targetAngleY(&current.pos, &gnd->current.pos), 4,
                            0x400);
    }
}

/* 00004E8C-00004F08       .text modeSideStepInit__6daPz_cFv */
void daPz_c::modeSideStepInit() {
    if (mPrevMode != MODE_ATTACK_WAIT_e && mPrevMode != MODE_ATTACK_e) {
        setAnm(ANM_WAIT04_e, true, ANM_KEEP_e);
    }
    mTargetSpeedF = 0.0f;
    speedF = 0.0f;
    mbNoTurn = 0;
    speed.y = l_HIO.mSideStepJumpY;
    mStepSpeed = l_HIO.mSideStepSpeed;
}

/* 00004F08-00005098       .text modeSideStep__6daPz_cFv */
void daPz_c::modeSideStep() {
    if (checkTgHit()) {
        mWaistRotY = 0;
    } else {
        int land_prm;

        mTargetSpeedF = 0.0f;
        speedF = 0.0f;
        mbNoTurn = 0;
        m_jnt.setTrn();
        mbAfraidRequest = 0;

        cLib_addCalcAngleS2(&mWaistRotY, (s16)(mTurnDir * 0x1194), 4, 0x800);

        s16 angle = cLib_targetAngleY(&mEyePos, &mTargetPos);
        cXyz offset(mStepSpeed * mTurnDir, 0.0f, 0.0f);
        cXyz move(0.0f, 0.0f, 0.0f);

        mDoMtx_stack_c::YrotS(angle);
        mDoMtx_stack_c::multVec(&offset, &move);
        current.pos += move;

        if (mObjAcch.ChkGroundHit()) {
            mWaistRotY = 0;
            dComIfGp_particle_setSimpleLand(mObjAcch.m_gnd, &current.pos, &shape_angle, 1.25f,
                                            1.5f, 1.0f, &tevStr, &land_prm, 7);

            if (mPrevMode == MODE_ATTACK_WAIT_e || mPrevMode == MODE_ATTACK_e) {
                modeProc(PROC_INIT_e, MODE_ATTACK_e);
            } else {
                modeProc(PROC_INIT_e, MODE_MOVE_e);
            }
        }
    }
}

/* 00005098-00005114       .text modeBackStepInit__6daPz_cFv */
void daPz_c::modeBackStepInit() {
    if (mPrevMode != MODE_ATTACK_WAIT_e && mPrevMode != MODE_ATTACK_e) {
        setAnm(ANM_WAIT04_e, true, ANM_KEEP_e);
    }
    mTargetSpeedF = 0.0f;
    speedF = 0.0f;
    mbNoTurn = 0;
    speed.y = l_HIO.mBackStepJumpY;
    mStepSpeed = l_HIO.mBackStepSpeed;
}

/* 00005114-0000527C       .text modeBackStep__6daPz_cFv */
void daPz_c::modeBackStep() {
    if (checkTgHit()) {
        mWaistRotZ = 0;
    } else {
        int land_prm;

        mTargetSpeedF = 0.0f;
        speedF = 0.0f;
        mbNoTurn = 0;
        m_jnt.setTrn();
        mbAfraidRequest = 0;

        cLib_addCalcAngleS2(&mWaistRotZ, -0x1194, 4, 0x800);

        s16 angle = cLib_targetAngleY(&current.pos, &mTargetPos);
        cXyz offset(0.0f, 0.0f, -mStepSpeed);
        cXyz move(0.0f, 0.0f, 0.0f);

        mDoMtx_stack_c::YrotS(angle);
        mDoMtx_stack_c::multVec(&offset, &move);
        current.pos += move;

        if (mObjAcch.ChkGroundHit()) {
            mWaistRotZ = 0;
            dComIfGp_particle_setSimpleLand(mObjAcch.m_gnd, &current.pos, &shape_angle, 1.25f,
                                            1.5f, 1.0f, &tevStr, &land_prm, 7);

            if (mPrevMode == MODE_ATTACK_WAIT_e || mPrevMode == MODE_ATTACK_e) {
                modeProc(PROC_INIT_e, MODE_ATTACK_e);
            } else {
                modeProc(PROC_INIT_e, MODE_MOVE_e);
            }
        }
    }
}

/* 0000527C-00005304       .text modeTalkInit__6daPz_cFv */
void daPz_c::modeTalkInit() {
#if VERSION > VERSION_DEMO
    setAnm(ANM_WAIT02_e, true, ANM_KEEP_e);
#endif
    speedF = 0.0f;
    mTargetSpeedF = 0.0f;
    mbNoTurn = 0;
    m_jnt.offHeadLock();
    m_jnt.offBackBoneLock();
#if VERSION > VERSION_DEMO
    if (mPhase == PHASE_SHOOT_GND_e) {
        mbTalkDone = 1;
    } else {
        mTalkTimer = l_HIO.mTalkTime[mPhase];
    }
#endif
}

/* 00005304-0000539C       .text modeTalk__6daPz_cFv */
void daPz_c::modeTalk() {
    mTargetPos = dNpc_playerEyePos(l_HIO.mNpcHIO.m04);
    m_jnt.setTrn();

    if (talk(1) == fopMsgStts_BOX_CLOSED_e) {
        dComIfGp_event_reset();
        modeProc(PROC_INIT_e, MODE_ATTACK_WAIT_e);
    }
}

/* 0000539C-0000549C       .text modeFollowInit__6daPz_cFv */
void daPz_c::modeFollowInit() {
    cLib_onBit(attention_info.flags, (u32)fopAc_Attn_ACTION_SPEAK_e);
    cLib_onBit(attention_info.flags, (u32)fopAc_Attn_LOCKON_TALK_e);

    mTimer = (int)(l_HIO.mMoveTimeBase[mPhase] + cM_rndF(l_HIO.mMoveTimeRand[mPhase]));
    mRetreatTimer = 10;
    mStepWaitTimer = 120;

    setAnm(ANM_RUN01_e, false, ANM_KEEP_e);

    mbNoTurn = 0;
    m_jnt.clrTrn();
    m_jnt.offHeadLock();
    m_jnt.offBackBoneLock();
}

/* 0000549C-000059B8       .text modeFollow__6daPz_cFv */
void daPz_c::modeFollow() {
    bool flag = false;
    mLinChk.Set(&current.pos, &mFollowTargetPos, this);
    if (dComIfG_Bgsp()->LineCross(&mLinChk)) {
        flag = true;
    }
    if (mObjAcch.ChkWallHit()) {
        flag = true;
    }

    if (checkTgHit()) {
        return;
    }

    if (l_HIO.mbFixTarget == 0) {
        if (mbHasGanondorf) {
            mTargetPos = mGanondorfPosOld;
        }
    } else {
        mTargetPos = dNpc_playerEyePos(l_HIO.mNpcHIO.m04);
    }

    m_jnt.clrTrn();

    f32 dist = (current.pos - mFollowTargetPos).absXZ();

    if (dist > 200.0f && !mbGndInEyeArea && !flag) {
        mTargetSpeedF = l_HIO.mRunSpeed;
    } else if (mbGndInEyeArea) {
        mTargetSpeedF = 0.0f;
    } else if (flag) {
        mTargetSpeedF = 2.0f;
    } else {
        mTargetSpeedF = 1.0f;
    }

    f32 factor = l_HIO.mFollowDist;
    fopAc_ac_c* linkPlayer = dComIfGp_getLinkPlayer();

    mFollowTargetPos = mGanondorfPos;

    s16 angle = cLib_targetAngleY(&linkPlayer->current.pos, &mGanondorfPos);
    cLib_distanceAngleS(angle, shape_angle.y);

    mFollowTargetPos.x += factor * cM_ssin(REG12_S(0) + (angle + 0x4000));
    mFollowTargetPos.z += factor * cM_scos(REG12_S(0) + (angle + 0x4000));
    mFollowTargetPos.y += 200.0f;

    if (cLib_calcTimer(&mRetreatTimer) == 0) {
        f32 distGanon = 100000.0f;
        f32 distActor = (current.pos - mTargetPos).absXZ();
        if (mbHasGanondorf) {
            distGanon = (current.pos - mGanondorfPos).absXZ();
        }

        if (mbGndInEyeArea && (distActor < l_HIO.mRetreatDist || distGanon < l_HIO.mRetreatDist)) {
            mPrevMode = mMode;
            modeProc(PROC_INIT_e, MODE_BACK_STEP_e);
            return;
        }
    }

    cLib_addCalcAngleS2(&shape_angle.y, cLib_targetAngleY(&current.pos, &mFollowTargetPos), 8, 0x400);

    if (speedF < 0.5f) {
        setAnm(ANM_WAIT02_e, false, ANM_KEEP_e);
    } else {
        setAnm(ANM_RUN01_e, false, ANM_KEEP_e);
    }

    if (l_HIO.mDbgFlags[1] == 0 && cLib_calcTimer(&mTimer) == 0) {
        modeProc(PROC_INIT_e, MODE_ATTACK_WAIT_e);
    }

    mTalkRequest = 2;
}

/* 000059B8-00005C58       .text modeProc__6daPz_cFQ26daPz_c6Proc_ei */
void daPz_c::modeProc(daPz_c::Proc_e i_procType, int i_mode) {
    static const ModeEntry mode_tbl[11] = {
        {&daPz_c::modeWaitInit, &daPz_c::modeWait, "WAIT"},
        {&daPz_c::modeMoveInit, &daPz_c::modeMove, "MOVE"},
        {&daPz_c::modeAttackWaitInit, &daPz_c::modeAttackWait, "ATTACKWAIT"},
        {&daPz_c::modeAttackInit, &daPz_c::modeAttack, "ATTACK"},
        {&daPz_c::modeDefendInit, &daPz_c::modeDefend, "DEFEND"},
        {&daPz_c::modeDownInit, &daPz_c::modeDown, "DOWN"},
        {&daPz_c::modeAfraidInit, &daPz_c::modeAfraid, "AFRAID"},
        {&daPz_c::modeSideStepInit, &daPz_c::modeSideStep, "SIDE_STEP"},
        {&daPz_c::modeBackStepInit, &daPz_c::modeBackStep, "BACK_STEP"},
        {&daPz_c::modeTalkInit, &daPz_c::modeTalk, "TALK"},
        {&daPz_c::modeFollowInit, &daPz_c::modeFollow, "FOLLOW"},
    };

    if (i_procType == PROC_INIT_e) {
        mMode = i_mode;
        (this->*mode_tbl[mMode].mInitFunc)();
    } else if (i_procType == PROC_EXEC_e) {
        (this->*mode_tbl[mMode].mUpdFunc)();
    }
}

/* 00005C58-000060D8       .text _execute__6daPz_cFv */
bool daPz_c::_execute() {
    if (l_HIO.mbWarpToPlayer != 0) {
        modeProc(PROC_INIT_e, MODE_WAIT_e);

        fopAc_ac_c* player = dComIfGp_getLinkPlayer();
        current.pos = player->current.pos;
        current.pos.y += 50.0f;

        current.pos.x -= 200.0f * cM_ssin(player->shape_angle.y);
        current.pos.z -= 200.0f * cM_scos(player->shape_angle.y);
    }

    {
        setFallSplash();
        getGndPos();
        mbGndInEyeArea = 0;
        if (mbHasGanondorf) {
            mbGndInEyeArea = checkEyeArea(mGanondorfPos);
        }

        gravity = l_HIO.mGravity;
        if (mMode != MODE_AFRAID_e && mMode != MODE_DOWN_e && mbAfraidRequest) {
            modeProc(PROC_INIT_e, MODE_AFRAID_e);
        }

        setRipple();
        if (mMode != MODE_DOWN_e && mPhase == PHASE_DOWN_e) {
            modeProc(PROC_INIT_e, MODE_DOWN_e);
        }

        setJntStatus();

        if (demo()) {
            mBtkAnm.play();
            mBrkAnm.play();
            setMtx();
            g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
            return true;
        }

        current.angle = shape_angle;

        mpMorf->calc();
        enemy_fire(&mEnemyFire);
        if (enemy_ice(&mEnemyIce)) {
            J3DModel* model = mpMorf->getModel();
            model->setBaseTRMtx(mDoMtx_stack_c::get());
            return true;
        }

        if (mAnmId == ANM_STAND_e) {
            setHeadSplash();
        }

#if VERSION > VERSION_DEMO
        if ((mArg != 0 || (mPhase != PHASE_SHOOT_GND_e && mPhase != PHASE_SHOOT_PLAYER_e)) ||
            mbTalkDone != 0 || mMode == MODE_ATTACK_WAIT_e || mMode == MODE_ATTACK_e ||
            mMode == MODE_DOWN_e || mMode == MODE_TALK_e) {
            // skip auto-talk trigger
        } else if (cLib_calcTimer(&mTalkTimer) == 0) {
            fopAc_ac_c* ganon;
            if (fopAcM_SearchByName(fpcNm_GND_e, &ganon)) {
                fopAc_ac_c* ganonAc = ganon;
                f32 dist = fopAcM_searchActorDistanceXZ(this, dComIfGp_getPlayer(0));
                if (dist < l_HIO.mTalkDist[mPhase] &&
                    ((gnd_class*)ganonAc)->mAction == 0) {
                    mTalkRequest = 1;
                    modeProc(PROC_INIT_e, MODE_TALK_e);
                }
            }
        }
#endif

        checkOrder();
        modeProc(PROC_EXEC_e, MODE_NULL_e);
        eventOrder();
        setAttention();

        cLib_addCalc2(&speedF, mTargetSpeedF, 0.3f,
                      4.0f);

        s8 roomNo = fopAcM_GetRoomNo(this);
        int mtrlSndId;
        // The demo build materializes the ground-hit bit before testing it (extrwi.);
        // the retail build folds the test into the mask (rlwinm.).
#if VERSION > VERSION_DEMO
        if (mObjAcch.ChkGroundHit()) {
#else
        bool ground_hit = mObjAcch.ChkGroundHit();
        if (ground_hit) {
#endif
            mtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
        } else {
            mtrlSndId = 0;
        }
        mpMorf->play(&eyePos, mtrlSndId, dComIfGp_getReverb(roomNo));
        mpBowMorf->play(NULL, 0, 0);
        mBrkAnm.play();
        playEyeAnm();

        if (l_HIO.mForceAnmId != 0) {
            setAnm(l_HIO.mForceAnmId, false, ANM_KEEP_e);
        }

        fopAcM_posMoveF(this, NULL);
        mObjAcch.CrrPos(*dComIfG_Bgsp());
#if VERSION > VERSION_DEMO
        // mBgS is the first member of dComIfG_play_c, so the BG pointer doubles as the
        // play pointer; the original shares the one address between both uses.
        if (((dComIfG_play_c*)dComIfG_Bgsp())->getEvent()->getMode() == 0)
#endif
        {
            setCollision(30.0f, 130.0f);
        }

        setAnmRunSpeed();

        current.angle = shape_angle;

        setMtx();
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    }

    return true;
}

#if VERSION == VERSION_DEMO
/* 00005BC4-00005C84       .text debugDraw__6daPz_cFv */
void daPz_c::debugDraw() {
    GXColor color = {0x00, 0xFF, 0x00, 0x80};

    if (mbGndInEyeArea) {
        static const GXColor color_ng = {0xFF, 0x00, 0x00, 0x80};
        color = color_ng;
    }

    cXyz pos = current.pos;
    pos.y += 20.0f;

    dLib_debugDrawFan(pos, shape_angle.y, l_HIO.mEyeAreaAngle, l_HIO.mEyeAreaDist, color);
    dLib_debugDrawAxis(mWaistMtx, 50.0f);
}
#endif

static void dummy() {
#if VERSION > VERSION_DEMO
    static const GXColor color_ok = {0x00, 0xFF, 0x00, 0x80};
    static const GXColor color_ng = {0xFF, 0x00, 0x00, 0x80};
#endif
    GXColor c1 = {0xFF, 0xFF, 0x00, 0x80};
    GXColor c2 = {0xFF, 0x00, 0x00, 0x80};
    GXColor c3 = {0xFF, 0xFF, 0x00, 0x80};
    GXColor c4 = {0x00, 0x00, 0xFF, 0x80};
    GXColor c5 = {0xFF, 0x00, 0xFF, 0x80};
#if VERSION > VERSION_DEMO
    f32 debug_dist[1] = {10000.0f};
#endif
}

/* 000060D8-00006154       .text bowDraw__6daPz_cFv */
void daPz_c::bowDraw() {
    g_env_light.setLightTevColorType(mpBowMorf->getModel(), &tevStr);

    mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(PZ_JNT_HAND_L1_e));
    mpBowMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpBowMorf->updateDL();
}

/* 00006154-00006600       .text bodyDraw__6daPz_cFv */
void daPz_c::bodyDraw() {
    J3DModel* model = mpMorf->getModel();
    J3DModelData* modelData = model->getModelData();

    g_env_light.setLightTevColorType(model, &tevStr);
    mpMorf->calc();
    model->unlock();

    if (mArg != 0) {
        mBrkAnm.entry(modelData);
    }

    dComIfGd_setListP0();
    mBtpAnm.entry(modelData, mEyeBtpFrame);
    j3dSys.getDrawBuffer(0)->entryImm(&mOnCupOffAupPacket1, 0);

    for (u16 i = 0; i < modelData->getMaterialNum(); i++) {
        J3DMaterial* mat = modelData->getMaterialNodePointer(i);
        if (i != MAT_EYE0_e && i != MAT_EYE1_e && i != MAT_EYEBROW0_e &&
            i != MAT_EYEBROW1_e) {
            mat->getShape()->hide();
        } else {
            mat->getShape()->show();
        }
    }

    mpMaterial[0]->makeDisplayList();
    j3dSys.getDrawBuffer(0)->entryImm(&mOffCupOnAupPacket1, 0);

    mBtkAnm.entry(modelData);

    mpShape[0]->hide();
    mpShape[3]->hide();
    mpShape[2]->show();
    mpShape[5]->show();
    mpShape[6]->hide();
    mpShape[9]->hide();
    mpShape[8]->show();
    mpShape[11]->show();

    mpMaterial[0]->makeDisplayList();
    mBtkAnm.remove(modelData);

    mpShape[2]->hide();
    mpShape[5]->hide();
    mpShape[8]->hide();
    mpShape[11]->hide();

    for (int i = 0; i < 4; i++) {
        mpShape[12 + i]->show();
    }

    mpMaterial[0]->makeDisplayList();
    j3dSys.getDrawBuffer(0)->entryImm(&mOnCupOffAupPacket0, 0);

    for (int i = 0; i < 4; i++) {
        mpShape[12 + i]->hide();
    }

    mpShape[1]->show();
    mpShape[4]->show();
    mpShape[7]->show();
    mpShape[10]->show();

    mpMaterial[0]->makeDisplayList();
    j3dSys.getDrawBuffer(0)->entryImm(&mOffCupOnAupPacket0, 0);

    mpShape[1]->hide();
    mpShape[4]->hide();
    mpShape[7]->hide();
    mpShape[10]->hide();

    dComIfGd_setListP1();

    for (u16 i = 0; i < modelData->getMaterialNum(); i++) {
        if (i == 3) continue;
        if (i == 2) continue;
        if (i == 1) continue;
        if (i == 6) continue;
        if (i == 5) continue;
        if (i == 4) continue;
        if (i == 0xd) continue;
        if (i == 0xc) continue;
        if (i == 0xb) continue;
        if (i == 0x10) continue;
        if (i == 0xf) continue;
        if (i == 0xe) continue;
        if (i == 0x12) continue;
        if (i == 0x13) continue;
        if (i == 8) continue;
        if (i == 7) continue;
        modelData->getMaterialNodePointer(i)->getShape()->show();
    }

    mpMorf->entryDL();
    dComIfGd_setList();

    for (u16 i = 0; i < modelData->getMaterialNum(); i++) {
        modelData->getMaterialNodePointer(i)->getShape()->show();
    }

    mBtpAnm.remove(modelData);

    if (mArg != 0) {
        mBrkAnm.remove(modelData);
    }
}

/* 00006600-000066D8       .text drawShadow__6daPz_cFv */
void daPz_c::drawShadow() {
    cXyz shadow_pos;

    shadow_pos.set(current.pos.x, 100.0f + current.pos.y + REG8_F(18), current.pos.z);
    mShadowKey = dComIfGd_setShadow(mShadowKey, 1, mpMorf->getModel(), &shadow_pos,
                                    250.0f + REG8_F(19), 40.0f, current.pos.y,
                                    mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr, 0, 1.0f);

    if (mbHasBow != 0 && mShadowKey != 0) {
        dComIfGd_addRealShadow(mShadowKey, mpBowMorf->getModel());
    }
}

/* 000066D8-0000676C       .text _draw__6daPz_cFv */
bool daPz_c::_draw() {
#if VERSION == VERSION_DEMO
    if (l_HIO.mNpcHIO.m22 != 0) {
        debugDraw();
    }
#endif

    if (mEnemyIce.mFreezeTimer > 20) {
        dMat_control_c::iceEntryDL(mpMorf, -1, &mInvisibleModel);
    } else {
        bodyDraw();
    }

    if (mbHasBow != 0) {
        bowDraw();
    }

    drawShadow();
    dSnap_RegistFig(DSNAP_TYPE_PZ, this, 1.0f, 1.0f, 1.0f);
    return true;
}

/* 0000676C-00006974       .text bodyCreateInit__6daPz_cFv */
void daPz_c::bodyCreateInit() {
    static u8 l_eyeMatNo[6] = {3, 2, 1, 6, 5, 4};
    static u8 l_eyeblowMatNo[6] = {13, 12, 11, 16, 15, 14};
    static u8 l_faceMatNo[4] = {18, 19, 8, 7};

    if (strcmp(dComIfGp_getStartStageName(), "GTower") == 0) {
        eventInfo.setEventId(dComIfGp_evmng_getEventIdx("PZ_TALK", 0xff));
    }

    J3DModelData* modelData = mpMorf->getModel()->getModelData();
    // Deliberately the joint node itself, reinterpreted - NOT ->getMesh(). The idiomatic
    // getMesh() form (used in setBowString above, and in three other TUs) compiles to a
    // different instruction and breaks the match, so the original really did store the
    // J3DJoint* here and later call J3DMaterial::makeDisplayList() through it.
    mpMaterial[0] = (J3DMaterial*)modelData->getJointNodePointer(PZ_JNT_WORLD_ROOT_e);

    for (int i = 0; i < 6; i++) {
        mpMaterial[1 + i] = modelData->getMaterialNodePointer(l_eyeMatNo[i]);
        mpShape[i] = mpMaterial[1 + i]->getShape();
    }

    for (int i = 0; i < 6; i++) {
        mpMaterial[7 + i] = modelData->getMaterialNodePointer(l_eyeblowMatNo[i]);
        mpShape[6 + i] = mpMaterial[7 + i]->getShape();
    }

    for (int i = 0; i < 4; i++) {
        mpMaterial[13 + i] = modelData->getMaterialNodePointer(l_faceMatNo[i]);
        mpShape[12 + i] = mpMaterial[13 + i]->getShape();
    }

    J3DMaterialAnm* anm;

    anm = mpMaterial[3]->getMaterialAnm();
    mpMaterial[2]->setMaterialAnm(anm);
    mpMaterial[1]->setMaterialAnm(anm);

    anm = mpMaterial[6]->getMaterialAnm();
    mpMaterial[5]->setMaterialAnm(anm);
    mpMaterial[4]->setMaterialAnm(anm);

    anm = mpMaterial[9]->getMaterialAnm();
    mpMaterial[8]->setMaterialAnm(anm);
    mpMaterial[7]->setMaterialAnm(anm);

    anm = mpMaterial[12]->getMaterialAnm();
    mpMaterial[11]->setMaterialAnm(anm);
    mpMaterial[10]->setMaterialAnm(anm);
}

/* 00006974-00006BAC       .text createInit__6daPz_cFv */
void daPz_c::createInit() {
    static u8 fire_j[10] = {7, 2, 12, 13, 17, 18, 22, 23, 25, 26};
    static f32 fire_sc[10] = {2.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};

    max_health = 30;
    health = max_health;
#if VERSION > VERSION_DEMO
    stealItemLeft = 10;
#endif

    mEnemyFire.mpMcaMorf = mpMorf;
    mEnemyFire.mpActor = this;

    for (int i = 0; i < 10; i++) {
        mEnemyFire.mFlameJntIdxs[i] = fire_j[i];
        mEnemyFire.mParticleScale[i] = fire_sc[i];
    }

    mEnemyIce.mpActor = this;
    mEnemyIce.m00C = 1;
    mEnemyIce.mWallRadius = 50.0f;
    mEnemyIce.mCylHeight = 250.0f;

    mPhase = PHASE_SHOOT_GND_e;
#if VERSION > VERSION_DEMO
    mTalkTimer = l_HIO.mTalkTime[PHASE_SHOOT_GND_e];
    mbTalkDone = 0;
#endif

    bodyCreateInit();

    if (mArg == 0) {
        mbHasBow = 1;
        modeProc(PROC_INIT_e, MODE_MOVE_e);
        attention_info.distances[fopAc_Attn_TYPE_TALK_e] = DEMO_SELECT(0xB1, 3);
        attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = DEMO_SELECT(0xB1, 3);
        cLib_onBit(attention_info.flags, (u32)fopAc_Attn_ACTION_SPEAK_e);
        cLib_onBit(attention_info.flags, (u32)fopAc_Attn_LOCKON_TALK_e);
    } else {
        attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
        modeProc(PROC_INIT_e, MODE_WAIT_e);
    }

    mTurnDir = 1;
    cullMtx = mpMorf->getModel()->getBaseTRMtx();

    fopAcM_setCullSizeBox(this, -60.0f, -50.0f, -60.0f, 60.0f, 1800.0f, 60.0f);

    mAcchCir.SetWall(80.0f, 60.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir,
                 fopAcM_GetSpeed_p(this), NULL, NULL);
    mObjAcch.SetRoofNone();

    gravity = l_HIO.mGravity;

    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(m_cyl_src);
    mCyl.SetStts(&mStts);
    setCollision(30.0f, 130.0f);

#if VERSION > VERSION_DEMO
    dKy_tevstr_init(&mTevStr, fopAcM_GetHomeRoomNo(this), 0xFF);
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
#endif
}

/* 00006BAC-00006CB0       .text _create__6daPz_cFv */
cPhs_State daPz_c::_create() {
    cPhs_State phase = dComIfG_resLoad(&mPhs, m_arc_name);
    fopAcM_ct(this, daPz_c);

    if (phase == cPhs_COMPLEATE_e) {
        getArg();

        if (mArg != DEMO_SELECT(1, 0) && strcmp(dComIfGp_getStartStageName(), "kenroom") == 0 &&
            dComIfGs_isEventBit(dSv_event_flag_c::UNK_3520) == 1) {
            return cPhs_ERROR_e;
        }

        if (!fopAcM_entrySolidHeap(this, createHeap_CB, m_heapsize)) {
            return cPhs_ERROR_e;
        }

        createInit();
    }

    return phase;
}

/* 00007DA0-00007E20       .text _delete__6daPz_cFv */
bool daPz_c::_delete() {
    dComIfG_resDelete(&mPhs, m_arc_name);
    mRippleCb.end();
    mFallSplashCb.end();
    mHeadSplashCb.end();
#if VERSION > VERSION_DEMO
    if (heap != NULL) {
        mpMorf->stopZelAnime();
    }
#endif
    return true;
}

/* 00007E20-00007E40       .text daPzCreate__FPv */
static cPhs_State daPzCreate(void* i_this) {
    return ((daPz_c*)i_this)->_create();
}

/* 00007E40-00007E64       .text daPzDelete__FPv */
static BOOL daPzDelete(void* i_this) {
    return ((daPz_c*)i_this)->_delete();
}

/* 00007E64-00007E88       .text daPzExecute__FPv */
static BOOL daPzExecute(void* i_this) {
    return ((daPz_c*)i_this)->_execute();
}

/* 00007E88-00007EAC       .text daPzDraw__FPv */
static BOOL daPzDraw(void* i_this) {
    return ((daPz_c*)i_this)->_draw();
}

/* 00007EAC-00007EB4       .text daPzIsDelete__FPv */
static BOOL daPzIsDelete(void*) {
    return TRUE;
}

static actor_method_class daPzMethodTable = {
    (process_method_func)daPzCreate,
    (process_method_func)daPzDelete,
    (process_method_func)daPzExecute,
    (process_method_func)daPzIsDelete,
    (process_method_func)daPzDraw,
};

actor_process_profile_definition g_profile_PZ = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_PZ_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daPz_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_PZ_e,
    /* Actor SubMtd */ &daPzMethodTable,
    /* Status       */ 0x08 | fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
