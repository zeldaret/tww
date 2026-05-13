/**
 * d_a_pz.cpp
 * NPC - Princess Zelda
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_pz.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"
#include "d/d_cc_uty.h"
#include "d/d_com_inf_game.h"
#include "d/d_lib.h"
#include "d/d_material.h"
#include "d/d_particle_name.h"
#include "d/d_s_play.h"
#include "d/res/res_pz.h"
#include "d/actor/d_a_arrow.h"
#include "d/actor/d_a_gnd.h"
#include "d/actor/d_a_item.h"
#include "d/actor/d_a_player.h"
#include "d/d_snap.h"
#include "f_op/f_op_actor_mng.h"
#include "JSystem/J3DGraphBase/J3DMaterial.h"
#include "JSystem/J3DGraphAnimator/J3DJoint.h"
#include "m_Do/m_Do_mtx.h"

const u32 daPz_c::m_heapsize = 0xA740;
const char daPz_c::m_arc_name[] = "PZ";
const f32 daPz_c::m_smoke_ef = 1.25f;
const f32 daPz_c::m_grass_ef = 1.5f;
const f32 daPz_c::m_splash_ef = 1.0f;
static daPz_HIO_c l_HIO;

const dCcD_SrcCyl daPz_c::m_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_VsGrpAll_e,
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
    m02D = 1;
    m032 = 0;
    m033 = 0;
    for (int i = 0; i < 10; i++) {
        m034[i] = 0;
    }

    mNpc.m04 = -20.0f;
    mNpc.mMaxHeadX = 0x1FFE;
    mNpc.mMaxHeadY = 0x2710;
    mNpc.mMaxBackboneX = 0x1B58;
    mNpc.mMaxBackboneY = 0x32C8;
    mNpc.mMinHeadX = -0x9C4;
    mNpc.mMinHeadY = -0x2710;
    mNpc.mMinBackboneX = -0x1B58;
    mNpc.mMinBackboneY = -0x32C8;
    mNpc.mMaxTurnStep = 0x1000;
    mNpc.mMaxHeadTurnVel = 0x800;
    mNpc.mAttnYOffset = 50.0f;
    mNpc.mMaxAttnAngleY = 0x32C8;
    mNpc.m22 = 0;
    mNpc.mMaxAttnDistXZ = 400.0f;

    m040 = 60.0f;
    m02F = 0;
    m054 = 0x2000;
    m058 = 200.0f;
    m044 = 1.2f;
    m04C = 0.9f;
    m048 = 2.0f;
    m050 = 10.0f;
    m031 = 0;

    mAttackAimRange[0] = 100.0f;
    mAttackShootChance[0] = 0.0f;
    mAttackAimZeroChance[0] = 100.0f;
    mAttackWaitTimer[0] = 30;
    mFollowTimerBase[0] = 300;
    mFollowTimerRange[0] = 0;
    mAttackTimerBase[0] = 30;
    mAttackTimerRange[0] = 0;
    mMoveRadius[0] = 1000.0f;
    mTalkTimer[0] = 60;
    m100 = 3000.0f;

    mAttackAimRange[2] = 100.0f;
    mAttackShootChance[2] = 100.0f;
    mAttackAimZeroChance[2] = 80.0f;
    mAttackWaitTimer[2] = 30;
    mFollowTimerBase[2] = 100;
    mFollowTimerRange[2] = 100;
    mAttackTimerBase[2] = 30;
    mAttackTimerRange[2] = 60;
    mMoveRadius[2] = 1000.0f;
    mTalkTimer[2] = 600;
    m108 = 800.0f;
    m0AC = 100.0f;
    m0E2[0] = 4;
    m0E2[1] = 6;
    m0E2[2] = 4;
    m0E2[3] = 6;

    m0B0 = -2.5f;
    mBackStepSpeedY = 20.0f;
    mBackStepSpeedF = 20.0f;
    mSideStepSpeedY = 20.0f;
    mSideStepSpeedF = 20.0f;
    mDownSpeedY = 4.0f;
    mDownSpeedF = 15.0f;
    mDownTimer = 14;
    m0D8 = 30.0f;
    m0DC = 40;
    m0DE = 40;
    m0E0 = 5;
    m0D0 = 600.0f;
    m0EC = 800.0f;
    m0D4 = 15.0f;
    m0F0 = 2.0f;
    m0F4 = 1.0f;
}

/* 00000310-00000340       .text stealItem_CB__FPv */
static BOOL stealItem_CB(void* actor) {
    if (actor != NULL) {
        daItem_c* item = (daItem_c*)actor;
        item->scale.setall(1.0f);
        item->setFlag(daItem_c::FLAG_HOOK);
    }
    return TRUE;
}

/* 00000340-0000038C       .text nodeHeadControl_CB__FP7J3DNodei */
static BOOL nodeHeadControl_CB(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == 0) {
        J3DModel* model = j3dSys.getModel();
        daPz_c* i_this = (daPz_c*)model->getUserArea();
        if (i_this != NULL) {
            i_this->_nodeHeadControl(i_node, model);
        }
    }
    return TRUE;
}

/* 0000038C-000004FC       .text _nodeHeadControl__6daPz_cFP7J3DNodeP8J3DModel */
void daPz_c::_nodeHeadControl(J3DNode* i_node, J3DModel* i_model) {
    u16 jnt_no = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));

    static cXyz top_offset(0.0f, 0.0f, 0.0f);
    static cXyz front_offset(24.0f, -16.0f, 0.0f);

    PSMTXMultVec(mDoMtx_stack_c::now, &top_offset, &mHeadTopPos);
    mDoMtx_stack_c::YrotM(-m_jnt.getHead_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
    PSMTXMultVec(mDoMtx_stack_c::now, &front_offset, &mHeadFrontPos);
    mHeadCenterPos.x = mDoMtx_stack_c::now[0][3];
    mHeadCenterPos.y = mDoMtx_stack_c::now[1][3];
    mHeadCenterPos.z = mDoMtx_stack_c::now[2][3];
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    PSMTXCopy(mDoMtx_stack_c::now, i_model->getAnmMtx(jnt_no));
}

/* 00000538-00000584       .text nodeWaistControl_CB__FP7J3DNodei */
static BOOL nodeWaistControl_CB(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == 0) {
        J3DModel* model = j3dSys.getModel();
        daPz_c* i_this = (daPz_c*)model->getUserArea();
        if (i_this != NULL) {
            i_this->_nodeWaistControl(i_node, model);
        }
    }
    return TRUE;
}

/* 00000584-00000710       .text _nodeWaistControl__6daPz_cFP7J3DNodeP8J3DModel */
void daPz_c::_nodeWaistControl(J3DNode* i_node, J3DModel* i_model) {
    static s16 tmp_angle;

    u16 jnt_no = ((J3DJoint*)i_node)->getJntNo();
    tmp_angle += 0x1000;
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));

    if (mAnmPrmIdx == 4 || mAnmPrmIdx == 5 || mAnmPrmIdx == 6) {
        mDoMtx_stack_c::ZrotM(0xDAC);
        mDoMtx_stack_c::YrotM(0x5DC);
    }

    if (REG12_S(6) != 0) {
        mDoMtx_stack_c::XrotM(tmp_angle);
    } else {
        MtxP mtx = mDoMtx_stack_c::now;
        mDoMtx_XrotM(mtx, m_jnt.getBackbone_y());
        mDoMtx_stack_c::ZrotM(-m_jnt.getBackbone_x());
    }

    if (mAnmPrmIdx == 4 || mAnmPrmIdx == 5 || mAnmPrmIdx == 6) {
        mDoMtx_stack_c::YrotM(-0x5DC);
        mDoMtx_stack_c::ZrotM(-0xDAC);
    }

    PSMTXCopy(mDoMtx_stack_c::now, mWaistMtx);
    mWaistPos.x = mDoMtx_stack_c::now[0][3];
    mWaistPos.y = mDoMtx_stack_c::now[1][3];
    mWaistPos.z = mDoMtx_stack_c::now[2][3];
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    PSMTXCopy(mDoMtx_stack_c::now, i_model->getAnmMtx(jnt_no));
}

/* 00000710-0000075C       .text nodeWaist2Control_CB__FP7J3DNodei */
static BOOL nodeWaist2Control_CB(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == 0) {
        J3DModel* model = j3dSys.getModel();
        daPz_c* i_this = (daPz_c*)model->getUserArea();
        if (i_this != NULL) {
            i_this->_nodeWaist2Control(i_node, model);
        }
    }
    return TRUE;
}

/* 0000075C-000007F4       .text _nodeWaist2Control__6daPz_cFP7J3DNodeP8J3DModel */
void daPz_c::_nodeWaist2Control(J3DNode* i_node, J3DModel* i_model) {
    u16 jnt_no = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));
    mDoMtx_stack_c::YrotM(mWaist2RotY);
    mDoMtx_stack_c::ZrotM(mWaist2RotZ);
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    PSMTXCopy(mDoMtx_stack_c::now, i_model->getAnmMtx(jnt_no));
}

/* 000007F4-00000840       .text nodeSkirtControl_CB__FP7J3DNodei */
static BOOL nodeSkirtControl_CB(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == 0) {
        J3DModel* model = j3dSys.getModel();
        daPz_c* i_this = (daPz_c*)model->getUserArea();
        if (i_this != NULL) {
            i_this->_nodeSkirtControl(i_node, model);
        }
    }
    return TRUE;
}

/* 00000840-00000920       .text _nodeSkirtControl__6daPz_cFP7J3DNodeP8J3DModel */
void daPz_c::_nodeSkirtControl(J3DNode* i_node, J3DModel* i_model) {
    u16 jnt_no = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));

    s16 rot_z = mWaist2RotZ;
    if (rot_z > mWaist2RotY) {
        rot_z = mWaist2RotY;
    }

    mDoMtx_stack_c::XrotM(REG12_S(2));
    mDoMtx_stack_c::YrotM(REG12_S(3));
    mDoMtx_stack_c::ZrotM(-(rot_z + REG12_S(4)));
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    PSMTXCopy(mDoMtx_stack_c::now, i_model->getAnmMtx(jnt_no));
}

/* 00000920-00000940       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c* i_this) {
    return ((daPz_c*)i_this)->_createHeap();
}

/* 00000940-00000D54       .text bodyCreateHeap__6daPz_cFv */
int daPz_c::bodyCreateHeap() {
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arc_name, PZ_BDL_PZ));
    JUT_ASSERT(0x23e, modelData != NULL);

    for (u16 i = 0; i < modelData->getMaterialNum(); i++) {
        J3DMaterial* mat = modelData->getMaterialNodePointer(i);
        mat->setMaterialAnm(new daPz_matAnm_c());
    }

    mpMorf = new mDoExt_McaMorf(modelData, NULL, NULL, NULL, -1, 1.0f, 0, -1, TRUE, NULL, 0x80000,
                                0x11020222);
    if (mpMorf == NULL || mpMorf->getModel() == NULL) {
        return 0;
    }

    mpMorf->getModel()->setUserArea((u32)this);
    if (!mInvisibleModel.create(mpMorf->getModel())) {
        return 0;
    }

    m_jnt.setHeadJntNum(4);
    modelData->getJointNodePointer(4)->setCallBack(nodeHeadControl_CB);
    m_jnt.setBackboneJntNum(1);
    modelData->getJointNodePointer(1)->setCallBack(nodeWaistControl_CB);
    modelData->getJointNodePointer(0x15)->setCallBack(nodeWaist2Control_CB);
    modelData->getJointNodePointer(0x19)->setCallBack(nodeSkirtControl_CB);

    J3DAnmTexPattern* btp = static_cast<J3DAnmTexPattern*>(dComIfG_getObjectRes(m_arc_name, PZ_BTP_MABA_A));
    JUT_ASSERT(0x277, btp != NULL);
    if (!mBtpAnm.init(modelData, btp, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, FALSE)) {
        return 0;
    }

    J3DAnmTextureSRTKey* btk = static_cast<J3DAnmTextureSRTKey*>(dComIfG_getObjectRes(m_arc_name, PZ_BTK_MABA_A));
    JUT_ASSERT(0x27d, btk != NULL);
    if (!mBtkAnm.init(modelData, btk, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, FALSE)) {
        return 0;
    }

    u16 updateMaterialNum = mBtkAnm.getBtkAnm()->getUpdateMaterialNum();
    for (u16 i = 0; i < updateMaterialNum; i++) {
        u16 materialId = mBtkAnm.getBtkAnm()->getUpdateMaterialID(i);
        m08A8[i] = modelData->getMaterialNodePointer(materialId)->getMaterialAnm();
    }

    J3DAnmTevRegKey* brk = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(m_arc_name, PZ_BRK_TRI_TEST));
    JUT_ASSERT(0x28e, brk != NULL);
    if (!mBrkAnm.init(modelData, brk, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, FALSE)) {
        return 0;
    }

    return 1;
}

/* 00000D54-00000E74       .text bowCreateHeap__6daPz_cFv */
int daPz_c::bowCreateHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(m_arc_name, PZ_BDL_BOW);
    JUT_ASSERT(0x29f, modelData != NULL);

    mpBowMcaMorf = new mDoExt_McaMorf(modelData, NULL, NULL, NULL, -1, 1.0f, 0, -1, TRUE, NULL,
                                      0x80000, 0x11000022);
    if (mpBowMcaMorf == NULL || mpBowMcaMorf->getModel() == NULL) {
        return 0;
    }

    mpBowMcaMorf->getModel()->setUserArea((u32)this);
    return 1;
}

/* 00000E74-00000EC0       .text _createHeap__6daPz_cFv */
BOOL daPz_c::_createHeap() {
    if (bodyCreateHeap() == 0) {
        return FALSE;
    }
    return bowCreateHeap() ? TRUE : FALSE;
}

/* 00000EC0-00000F20       .text __ct__13daPz_matAnm_cFv */
daPz_matAnm_c::daPz_matAnm_c() {
    mMoveFlag = false;
    mNowOffsetX = 0.0f;
    mNowOffsetY = 0.0f;
}

/* 00000F20-00000FB4       .text calc__13daPz_matAnm_cCFP11J3DMaterial */
void daPz_matAnm_c::calc(J3DMaterial* i_material) const {
    J3DMaterialAnm::calc(i_material);

    for (u32 i = 0; i < 8; i++) {
        if (getTexMtxAnm(i) != NULL) {
            J3DTexMtx* tex_mtx = i_material->getTexMtx(i);
            if (mMoveFlag) {
                tex_mtx->getTexMtxInfo().mSRT.mTranslationX = mNowOffsetX;
                tex_mtx->getTexMtxInfo().mSRT.mTranslationY = mNowOffsetY;
            }
        }
    }
}

/* 00000FB4-00001038       .text getGndPos__6daPz_cFv */
void daPz_c::getGndPos() {
    mbHasGanondorf = false;

    fopAc_ac_c* ganondorf;
    if (fopAcM_SearchByName(PROC_GND, &ganondorf)) {
        mGanondorfPos4 = ganondorf->eyePos;
        mGanondorfPosCurrent = ganondorf->current.pos;
        mbHasGanondorf = true;
    }
}

/* 00001038-0000114C       .text checkEyeArea__6daPz_cFR4cXyz */
BOOL daPz_c::checkEyeArea(cXyz& i_pos) {
    s32 angle = cLib_distanceAngleS(shape_angle.y, cLib_targetAngleY(&current.pos, &i_pos));
    f32 dist = (current.pos - i_pos).absXZ();

    if (angle < l_HIO.m054 && dist < l_HIO.m058) {
        return TRUE;
    }
    return FALSE;
}

/* 0000114C-00001194       .text getMsg__6daPz_cFv */
u32 daPz_c::getMsg() {
    u32 msg_no = 0x3562;
    if (m08B0 == 0) {
        msg_no = 0x3562;
    } else if (m08B0 == 2) {
        if (!m0F65) {
            m0F65 = true;
            msg_no = 0x3563;
        } else {
            msg_no = 0x3565;
        }
    }
    return msg_no;
}

/* 00001194-00001208       .text next_msgStatus__6daPz_cFPUl */
u16 daPz_c::next_msgStatus(u32* pMsgNo) {
    u16 status = fopMsgStts_MSG_CONTINUES_e;
    u32 msgNo = *pMsgNo;

    switch (msgNo) {
    case 0x3563:
        *pMsgNo = 0x3564;
        break;
    default:
        if (msgNo == 0x3564) {
            fopAc_ac_c* ganondorf;
            if (fopAcM_SearchByName(PROC_GND, &ganondorf) && ganondorf->stealItemBitNo == 0) {
                ganondorf->stealItemBitNo = 0x23;
            }
        }

        status = fopMsgStts_MSG_ENDS_e;
        break;
    }

    return status;
}

/* 00001208-00001288       .text anmAtr__6daPz_cFUs */
void daPz_c::anmAtr(u16 i_msgStatus) {
    static const s8 anm_atr[] = {
        12, 13,
    };

    switch (i_msgStatus) {
    case 6:
        if (m06CC == 0) {
            u8 msg_attr = dComIfGp_getMesgAnimeAttrInfo();
            m06CC = 1;
            setAnm(anm_atr[msg_attr], false, 0xF);
        }
        break;
    case 0xE:
        m06CC = 0;
        break;
    }
}

/* 00001288-000012D4       .text eventOrder__6daPz_cFv */
void daPz_c::eventOrder() {
    if (m0F82 == 1 || m0F82 == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (m0F82 == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    }
}

/* 000012D4-00001338       .text checkOrder__6daPz_cFv */
void daPz_c::checkOrder() {
    if (eventInfo.getCommand() == dEvtCmd_INDEMO_e) {
        m0F82 = 0;
    } else if (eventInfo.getCommand() == dEvtCmd_INTALK_e && (m0F82 == 1 || m0F82 == 2)) {
        m0F82 = 0;
        modeProc((Proc_e)0, 9);
    }
}

/* 00001338-0000151C       .text setFallSplash__6daPz_cFv */
void daPz_c::setFallSplash() {
    g_env_light.settingTevStruct(TEV_TYPE_BG1, &current.pos, &mTevstr);

    mFallSplashPos = mHeadFrontPos;
    mFallSplashPos.y += l_HIO.m0D4;

    if (mObjAcch.ChkGroundHit()) {
        if (dComIfG_Bgsp()->GetAttributeCode(mObjAcch.m_gnd) == dBgS_Attr_WATERFALL_e) {
            if (mFallSplash.getEmitter() == NULL) {
                dComIfGp_particle_set(dPa_name::ID_AK_JN_ELEMENTSHIBUKI00, &mFallSplashPos, &shape_angle,
                                      NULL, 0xFF, &mFallSplash);
                if (mFallSplash.getEmitter() != NULL) {
                    mFallSplash.getEmitter()->setRate(4.0f);
                    mFallSplash.getEmitter()->setSpread(1.0f);
                    mFallSplash.getEmitter()->setGlobalPrmColor(mTevstr.mColorC0.r, mTevstr.mColorC0.g,
                                                                mTevstr.mColorC0.b);
                }
            }
        } else {
            mFallSplash.end();
        }

        if (cLib_calcTimer(&mFallRippleTimer) == 0) {
            static Vec fall_ripple_scale = {0.75f, 0.75f, 0.75f};
            cXyz pos;
            MtxP mtx = mpMorf->getModel()->getAnmMtx(0);
            pos.x = mtx[0][3];
            pos.y = mtx[1][3];
            pos.z = mtx[2][3];
            dComIfGp_particle_setShipTail(dPa_name::ID_IT_JN_WP_HAMON03, &pos, NULL,
                                          (cXyz*)&fall_ripple_scale, 0xFF,
                                          &dPa_control_c::mSingleRippleEcallBack);
            mFallRippleTimer = 15;
        }
    } else {
        mFallSplash.end();
    }
}

/* 0000151C-000015F4       .text setHeadSplash__6daPz_cFv */
void daPz_c::setHeadSplash() {
    g_env_light.settingTevStruct(TEV_TYPE_BG1, &current.pos, &mTevstr);
    if (mHeadSplash.getEmitter() == NULL) {
        dComIfGp_particle_set(
            dPa_name::ID_AK_SN_PZSHAKEHEADSPLASH00, &mHeadCenterPos, NULL, NULL, 0xFF, &mHeadSplash
        );
    }

    JPABaseEmitter* emitter = mHeadSplash.getEmitter();
    if (emitter != NULL) {
        emitter->setGlobalPrmColor(mTevstr.mColorC0.r, mTevstr.mColorC0.g, mTevstr.mColorC0.b);
        MtxP mtx = mpMorf->getModel()->getAnmMtx(4);
        mHeadSplash.getEmitter()->setGlobalRTMatrix(mtx);
    }
}

/* 000015F4-00001704       .text setRipple__6daPz_cFv */
void daPz_c::setRipple() {
    if (mObjAcch.ChkGroundHit()) {
        if (dComIfG_Bgsp()->GetAttributeCode(mObjAcch.m_gnd) == dBgS_Attr_WATER_e) {
            if (mRipple.getEmitter() == NULL) {
                static cXyz ripple_scale(0.8f, 0.8f, 0.8f);
                dComIfGp_particle_setShipTail(
                    dPa_name::ID_AK_JN_HAMON00, &current.pos, NULL, &ripple_scale, 0xFF, &mRipple
                );
                if (mRipple.getEmitter() != NULL) {
                    mRipple.setRate(0.0f);
                }
            }
        } else {
            mRipple.end();
        }
    }
}

/* 00001704-0000175C       .text setJntStatus__6daPz_cFv */
void daPz_c::setJntStatus() {
    m_jnt.setParam(
        l_HIO.mNpc.mMaxBackboneX, l_HIO.mNpc.mMaxBackboneY,
        l_HIO.mNpc.mMinBackboneX, l_HIO.mNpc.mMinBackboneY,
        l_HIO.mNpc.mMaxHeadX, l_HIO.mNpc.mMaxHeadY,
        l_HIO.mNpc.mMinHeadX, l_HIO.mNpc.mMinHeadY,
        l_HIO.mNpc.mMaxTurnStep
    );
}

/* 0000175C-00001954       .text demo__6daPz_cFv */
u8 daPz_c::demo() {
    if (demoActorID == 0) {
        if (m0F66) {
            m0F66 = false;
        }
    } else {
        m0F66 = true;
        dDemo_actor_c* demo_actor = dComIfGp_demo_get()->getObject()->getActor(demoActorID);

        for (int i = 0; i < 2; i++) {
            if (m08A8[i] != NULL) {
                ((daPz_matAnm_c*)m08A8[i])->clrMoveFlag();
            }
        }

        if (mBtpAnm.getBtpAnm() != NULL) {
            u8 frame_max = mBtpAnm.getBtpAnm()->getFrameMax();
            mEyeBtpState++;
            if (mEyeBtpState >= frame_max) {
                mEyeBtpState = frame_max;
            }
        }

        J3DAnmTexPattern* btp = demo_actor->getP_BtpData(m_arc_name);
        if (btp != NULL) {
            mBtpAnm.init(mpMorf->getModel()->getModelData(), btp, TRUE, J3DFrameCtrl::EMode_NONE,
                         1.0f, 0, -1, true, FALSE);
            mEyeBtpState = 0;
        }

        J3DAnmTextureSRTKey* btk = demo_actor->getP_BtkData(m_arc_name);
        if (btk != NULL) {
            mBtkAnm.init(mpMorf->getModel()->getModelData(), btk, TRUE, J3DFrameCtrl::EMode_NONE,
                         1.0f, 0, -1, true, FALSE);
        }

        J3DAnmTevRegKey* brk = (J3DAnmTevRegKey*)demo_actor->getP_BrkData(m_arc_name);
        if (brk != NULL) {
            mBrkAnm.init(mpMorf->getModel()->getModelData(), brk, TRUE, J3DFrameCtrl::EMode_LOOP,
                         1.0f, 0, -1, true, FALSE);
        }

        dDemo_setDemoData(this, 0x6A, mpMorf, m_arc_name, 0, NULL, 0, 0);
    }
    return m0F66;
}

/* 00001954-00001EEC       .text checkTgHit__6daPz_cFv */
BOOL daPz_c::checkTgHit() {
    daPy_py_c* player = daPy_getPlayerActorClass();

    mStts.Move();
    if (cLib_calcTimer(&m06D0) != 0) {
        goto fail;
    }

    if (!mCyl.ChkTgHit()) {
        goto fail;
    }

    bool do_damage = true;
    cCcD_Obj* hit_obj = mCyl.GetTgHitObj();
    m06D0 = l_HIO.m0E0;
    if (hit_obj == NULL) {
        return FALSE;
    }

    switch (hit_obj->GetAtType()) {
    case AT_TYPE_SWORD:
    case AT_TYPE_MACHETE:
    case AT_TYPE_UNK800:
    case AT_TYPE_DARKNUT_SWORD:
    case AT_TYPE_MOBLIN_SPEAR:
        switch (player->mCutType) {
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
            m06D1 = 1;
            break;
        default:
            m06D1 = 0;
            break;
        }
        break;
    case AT_TYPE_WIND:
        do_damage = FALSE;
        m06D1 = 3;
        break;
    case AT_TYPE_BOOMERANG:
    case AT_TYPE_BOKO_STICK:
        m06D1 = 4;
        break;
    case AT_TYPE_HOOKSHOT:
        m06D1 = 0x0C;
        break;
    case AT_TYPE_SKULL_HAMMER:
    case AT_TYPE_STALFOS_MACE:
        m06D1 = 7;
        if (player->mCutType == daPy_py_c::CUT_TYPE_HAMMER_SIDESWING) {
            m06D1 = 8;
        }
        break;
    case AT_TYPE_BOMB:
        m06D1 = 6;
        break;
    case AT_TYPE_NORMAL_ARROW:
    case AT_TYPE_FIRE_ARROW:
    case AT_TYPE_ICE_ARROW:
    case AT_TYPE_LIGHT_ARROW:
        m06D1 = 5;
        break;
    case AT_TYPE_GRAPPLING_HOOK:
        m06D1 = 0x0E;
        do_damage = FALSE;
        break;
    default:
        break;
    }

    fopAc_ac_c* hit_actor = mCyl.GetTgHitAc();
    if (fopAcM_GetName(hit_actor) == PROC_ARROW) {
        daArrow_c* arrow = (daArrow_c*)hit_actor;
        if (arrow->isLinkReflect()) {
            m06D1 = 5;
        } else if (arrow->isSetByZelda()) {
            return FALSE;
        }
    }

    if (do_damage) {
        cXyz* hit_pos = mCyl.GetTgHitPosP();
        m0F6C = fopAcM_searchActorAngleY(this, hit_actor);
        // Original damage-info temp; the sound helper does its own hit-object lookup.
        CcAtInfo atInfo;
        atInfo.mpObj = mCyl.GetTgHitObj();
        def_se_set(this, mCyl.GetTgHitObj(), 0x41);

        dKy_SordFlush_set(*hit_pos, 0);

        if (m06D1 == 1 || m06D1 == 7 || m06D1 == 8) {
            m0F68 = 60.0f;
        } else {
            m0F68 = 40.0f;
        }

        dComIfGp_particle_set(
            dCcg_TgHitMark_Purple_e, hit_pos, &player->shape_angle, NULL, 0xFF, NULL, -1, NULL, NULL, NULL
        );
        modeProc(PROC_INIT_e, 4);

        if (fopAcM_GetName(hit_actor) == PROC_GND) {
            m0744 = 0;
            m0F68 *= 1.5;
            m0754 = 0;
            m075C = 0;
            m0760++;
            if (m0760 > l_HIO.m0E2[0]) {
                m0760 = 0;
                m0764 = l_HIO.m0E2[1];
                m0768 = 1;
            }

            if (cM_rndF(100.0f) < 60.0f) {
                fopAcM_monsSeStart(this, JA_SE_CV_ZL_GN_DAMAGE, 0);
            }
        } else {
            m0744 = 1;
            m0760 = 0;
            m0768 = 0;
            m0754++;
            if (m0754 > l_HIO.m0E2[2]) {
                m0754 = 0;
                m0758 = l_HIO.m0E2[3];
                m075C = 1;
            }

            if (cM_rndF(100.0f) < 30.0f) {
                fopAcM_monsSeStart(this, JA_SE_CV_ZL_GN_DAMAGE, 0);
            }
        }

        m0748 = *hit_pos;
    } else if (m06D1 == 0x0E) {
        fopAcM_monsSeStart(this, JA_SE_CV_ZL_GN_DAMAGE, 0);

        int item_no = 0;
        if (dComIfGs_getLife() <= 0x0C) {
            item_no = 0x1E;
        }

        fopAcM_fastCreateItem(
            &current.pos, item_no, fopAcM_GetRoomNo(this), &shape_angle, NULL, 0.0f, 0.0f, -6.0f, -1,
            stealItem_CB
        );
        modeProc(PROC_INIT_e, 4);
    }

    return TRUE;

fail:
    return FALSE;
}

/* 00001EEC-00001F10       .text getArg__6daPz_cFv */
void daPz_c::getArg() {
    mArg = (fopAcM_GetParam(this) >> 8) & 0xFF;
    if (mArg == 0xFF) {
        mArg = 0;
    }
}

/* 00001F10-000020B8       .text setAttention__6daPz_cFv */
void daPz_c::setAttention() {
    attention_info.position = mHeadTopPos;
    attention_info.position.y += l_HIO.m040;
    eyePos = mHeadFrontPos;

    f32 dist_xz = (mHeadFrontPos - m08C4).absXZ();
    (void)dist_xz;

    cLib_distanceAngleS(shape_angle.y, cLib_targetAngleY(&mHeadFrontPos, &m08C4));

    s16 max_turn_vel;
    if (m_jnt.trnChk()) {
        s16 turn_speed = mEventCut.getTurnSpeed();
        if (turn_speed != 0) {
            max_turn_vel = turn_speed;
        } else {
            max_turn_vel = l_HIO.mNpc.mMaxHeadTurnVel;
        }
    } else {
        max_turn_vel = 0;
    }

    cLib_addCalcAngleS2(&m08E8, max_turn_vel, 4, 0x800);
    m_jnt.lookAtTarget(&shape_angle.y, &m08C4, mHeadFrontPos, shape_angle.y, m08E8, m08EA);
}

/* 000020B8-00002114       .text setBowAnm__6daPz_cFScb */
void daPz_c::setBowAnm(s8 i_anm, bool i_force) {
    static const int a_anm_bcks_tbl[] = {
        PZ_BCK_ARROW_RELORD,
        PZ_BCK_ARROW_WAIT03,
        PZ_BCK_ARROW_SHOOT,
    };

    static const dLib_anm_prm_c a_anm_prm_tbl[] = {
        {2, -1, 0, 0.0f, 0.0f, J3DFrameCtrl::EMode_NONE},
        {2, -1, 0, 0.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {0, -1, 0, 0.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {1, -1, 0, 0.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {2, -1, 0, 0.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
    };

    if (i_anm != 5) {
        mBowAnmPrmIdx = i_anm;
    }

    dLib_bcks_setAnm(m_arc_name, mpBowMcaMorf, &mBowBckIdx, &mBowAnmPrmIdx,
                     &mBowOldAnmPrmIdx, a_anm_bcks_tbl, a_anm_prm_tbl, i_force);
}

/* 00002114-00002184       .text setBowString__6daPz_cFb */
void daPz_c::setBowString(bool i_show) {
    J3DMaterial* mat = mpBowMcaMorf->getModel()->getModelData()->getJointNodePointer(0)->getMesh()->getNext();
    J3DMaterial* string_mat = mat->getNext();
    if (i_show) {
        mat->getShape()->show();
        string_mat->getShape()->hide();
    } else {
        mat->getShape()->hide();
        string_mat->getShape()->show();
    }
}

/* 00002184-0000246C       .text setAnm__6daPz_cFScbi */
void daPz_c::setAnm(s8 i_anm, bool i_force, int i_eye) {
    static const int a_anm_bcks_tbl[] = {
        PZ_BCK_WAIT01,
        PZ_BCK_WAIT02,
        PZ_BCK_RUN01,
        PZ_BCK_RELORD,
        PZ_BCK_WAIT03,
        PZ_BCK_SHOOT,
        PZ_BCK_DAM01,
        PZ_BCK_DAM02,
        PZ_BCK_STAND,
        PZ_BCK_DEFEND,
        PZ_BCK_WAIT04,
    };

    if (i_anm != 15) {
        mAnmPrmIdx = i_anm;
    }

    dLib_anm_prm_c a_anm_prm_tbl[] = {
        {0, -1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {0, -1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {1, -1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {2, -1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {3, -1, 0, 2.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {4, -1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {5, -1, 0, 2.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {6, -1, 0, 4.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {7, -1, 0, 4.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {8, -1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {9, -1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {10, -1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {1, -1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {1, -1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {4, -1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };
    static const u8 eye_anm[] = {
        0, 0, 7, 7, 1, 1, 1, 2, 3, 4, 5, 6, 8, 9, 8,
    };

    a_anm_prm_tbl[7].mMorf = l_HIO.m0F0;
    a_anm_prm_tbl[8].mMorf = l_HIO.m0F4;

    if (mOldAnmPrmIdx != mAnmPrmIdx) {
        if (mAnmPrmIdx == 4) {
            fopAcM_monsSeStart(this, JA_SE_CV_ZL_DRAW_BOW, 0);
            setBowAnm(2, false);
            mArrowId = fopAcM_createChild(PROC_ARROW, fopAcM_GetID(this), 0, &current.pos,
                                          fopAcM_GetRoomNo(this), NULL, NULL, -1, NULL);
        }

        if (mAnmPrmIdx == 5) {
            setBowAnm(3, true);
        }

        if (mAnmPrmIdx == 6) {
            fopAcM_monsSeStart(this, JA_SE_CV_ZL_SHOOT_BOW, 0);
            setBowAnm(4, true);

            fopAc_ac_c* arrow;
            if (fopAcM_SearchByID(mArrowId, &arrow)) {
                fpcM_SetParam(arrow, 1);
            }
        }

        if (mAnmPrmIdx != 4 && mAnmPrmIdx != 5) {
            fopAc_ac_c* arrow;
            if (fopAcM_SearchByID(mArrowId, &arrow)) {
                fpcM_SetParam(arrow, 1);
            }
        }

        if (mAnmPrmIdx == 9) {
            setHeadSplash();
        } else {
            mHeadSplash.remove();
        }

        if (mAnmPrmIdx == 4 || mAnmPrmIdx == 5 || mAnmPrmIdx == 6) {
            setBowString(true);
        } else {
            setBowAnm(1, true);
            setBowString(false);
        }

        if (i_eye == 15) {
            setEyeAnm(eye_anm[mAnmPrmIdx]);
        } else {
            setEyeAnm(eye_anm[i_eye]);
        }
    }

    dLib_bcks_setAnm(m_arc_name, mpMorf, &mBckIdx, &mAnmPrmIdx, &mOldAnmPrmIdx,
                     a_anm_bcks_tbl, a_anm_prm_tbl, i_force);
}

/* 0000246C-00002684       .text setAnmRunSpeed__6daPz_cFv */
void daPz_c::setAnmRunSpeed() {
    if (mAnmPrmIdx == 3) {
        f32 run_speed = (current.pos - old.pos).abs() / (10.0f + REG12_F(6));
        if (run_speed <= 0.0f) {
            run_speed = 0.0f;
        } else if (run_speed >= 1.0f) {
            run_speed = 1.0f;
        }

        f32 play_speed = run_speed * l_HIO.m044;
        play_speed = play_speed < l_HIO.m04C ? l_HIO.m04C : play_speed;
        play_speed = play_speed > l_HIO.m048 ? l_HIO.m048 : play_speed;
        mpMorf->setPlaySpeed(play_speed);

        int frame = mpMorf->getFrame();
        if (frame == 7 || frame == 14) {
            static s8 run_splash_scale_init;
            static Vec run_splash_scale;
            if (!run_splash_scale_init) {
                run_splash_scale.x = 0.6f;
                run_splash_scale.y = 0.6f;
                run_splash_scale.z = 0.6f;
                run_splash_scale_init = true;
            }

            int land_id;
            JPABaseEmitter* emitter = dComIfGp_particle_setSimpleLand(
                mObjAcch.m_gnd, &current.pos, &shape_angle, 1.25f, 1.5f, 1.0f,
                &tevStr, &land_id, 7
            );

            if (emitter != NULL) {
                emitter->setRate(18.0f);
                emitter->setSpread(1.0f);
                emitter->mGlobalDynamicsScale.x = run_splash_scale.x;
                emitter->mGlobalDynamicsScale.y = run_splash_scale.y;
                emitter->mGlobalDynamicsScale.z = run_splash_scale.z;
                emitter->mGlobalParticleScale.x = run_splash_scale.x;
                emitter->mGlobalParticleScale.y = run_splash_scale.y;
                emitter->mGlobalParticleScale.z = run_splash_scale.z;
            }
        }
    }
}

/* 00002684-0000274C       .text setEyeBtp__6daPz_cFi */
void daPz_c::setEyeBtp(int i_btp) {
    J3DModel* model = mpMorf->getModel();
    J3DAnmTexPattern* btp = (J3DAnmTexPattern*)dComIfG_getObjectRes(m_arc_name, i_btp);
    JUT_ASSERT(0x683, btp != NULL);
    mEyeBtpState = 0;
    mBtpAnm.init(model->getModelData(), btp, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE);
}

/* 0000274C-00002810       .text setEyeBtk__6daPz_cFi */
void daPz_c::setEyeBtk(int i_btk) {
    J3DModel* model = mpMorf->getModel();
    J3DAnmTextureSRTKey* btk = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes(m_arc_name, i_btk);
    JUT_ASSERT(0x691, btk != NULL);
    mBtkAnm.init(model->getModelData(), btk, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, FALSE);
}

/* 00002810-00002888       .text setEyeAnm__6daPz_cFSc */
void daPz_c::setEyeAnm(signed char i_eye) {
    static const int a_eye_tbl[][2] = {
        {0x27, 0x1F},
        {0x23, 0x1E},
        {0x24, -1},
        {0x25, -1},
        {0x29, 0x20},
        {0x26, -1},
        {0x2C, -1},
        {0x28, 0x1F},
        {0x2A, -1},
        {0x2B, -1},
    };

    int btp = a_eye_tbl[i_eye][0];
    if (btp != -1) {
        setEyeBtp(btp);
    }
    int btk = a_eye_tbl[i_eye][1];
    if (btk != -1) {
        setEyeBtk(btk);
    }
    mCurEye = i_eye;
}

/* 00002888-00002AE0       .text ctrlEye__6daPz_cFv */
void daPz_c::ctrlEye() {
    mEyeTarget = m08C4;
    s16 target_x = cLib_targetAngleX(&mHeadFrontPos, &mEyeTarget);
    s16 target_y = cLib_targetAngleY(&mHeadFrontPos, &mEyeTarget);

    s16 eye_yaw = target_y;
    eye_yaw -= (s16)(shape_angle.y + m_jnt.getHead_y() + m_jnt.getBackbone_y());
    s16 eye_pitch = target_x;
    eye_pitch -= (s16)(m_jnt.getHead_x() + m_jnt.getBackbone_x());

    f32 eye_y_rate = (s16)eye_pitch / 8192.0f;
    f32 eye_x_rate = (s16)eye_yaw / 8192.0f;
    f32 mult = 0.1f;
    f32 y_offset = eye_y_rate;
    f32 x_offset = eye_x_rate;
    y_offset = mult * y_offset;
    x_offset = mult * x_offset;

    m06DC = (int)cLib_checkMinMaxLimit(y_offset, -0.1f, 0.1f);
    m06DC = (int)cLib_checkMinMaxLimit(x_offset, -0.1f, 0.1f);

    y_offset = cLib_minMaxLimit(y_offset, -0.1f, 0.1f);
    x_offset = cLib_minMaxLimit(x_offset, -0.1f, 0.1f);

    if (mMode == 3) {
        x_offset = 0.1f;
    }

    if (m08A8[0] != NULL) {
        cLib_addCalc(((daPz_matAnm_c*)m08A8[0])->getNowOffsetXP(), x_offset, 0.5f, 0.1f, 0.03f);
        cLib_addCalc(((daPz_matAnm_c*)m08A8[0])->getNowOffsetYP(), y_offset, 0.5f, 0.1f, 0.03f);
    }

    x_offset *= -1.0f;
    if (m08A8[1] != NULL) {
        cLib_addCalc(((daPz_matAnm_c*)m08A8[1])->getNowOffsetXP(), x_offset, 0.5f, 0.1f, 0.03f);
        cLib_addCalc(((daPz_matAnm_c*)m08A8[1])->getNowOffsetYP(), y_offset, 0.5f, 0.1f, 0.03f);
    }
}

/* 00002AE0-00002D38       .text playEyeAnm__6daPz_cFv */
void daPz_c::playEyeAnm() {
    bool move_eye = true;

    if (mCurEye == 0 || mCurEye == 7) {
        if (cLib_calcTimer(&mEyeTimer) == 0) {
            mEyeBtpState++;
            if (mEyeBtpState > mBtpAnm.getEndFrame()) {
                mEyeTimer = (s16)(100.0f + cM_rndF(100.0f));
                mEyeBtpState = 0;
            }
        }
    } else if (mCurEye == 1 || mCurEye == 2 || mCurEye == 5 || mCurEye == 6) {
        mEyeBtpState = 1;
    } else {
        mEyeBtpState++;
        if (mEyeBtpState > mBtpAnm.getEndFrame()) {
            mEyeTimer = (s16)(100.0f + cM_rndF(100.0f));
            mEyeBtpState = mBtpAnm.getEndFrame();
        }
    }

    if (mCurEye == 4) {
        move_eye = false;
    }

    if (move_eye) {
        for (int i = 0; i < 2; i++) {
            if (m08A8[i] != NULL) {
                ((daPz_matAnm_c*)m08A8[i])->setMoveFlag();
            }
        }
        ctrlEye();
    } else {
        for (int i = 0; i < 2; i++) {
            if (m08A8[i] != NULL) {
                ((daPz_matAnm_c*)m08A8[i])->clrMoveFlag();
            }
        }
        mBtkAnm.play();
    }
}

/* 00002D38-00002DC8       .text setMtx__6daPz_cFv */
void daPz_c::setMtx() {
    mpMorf->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00002DC8-00002E2C       .text modeWaitInit__6daPz_cFv */
void daPz_c::modeWaitInit() {
    m0924 = 0.0f;
    setAnm(1, false, 0xF);
    m_jnt.mbTrn = false;
    m08EA = true;
    m_jnt.mbHeadLock = true;
    m_jnt.mbBackBoneLock = true;
    m08EC = 30;
}

/* 00002E2C-00002FE8       .text modeWait__6daPz_cFv */
void daPz_c::modeWait() {
    m08C4 = dNpc_playerEyePos(l_HIO.mNpc.m04);

    dEvent_manager_c* evt_mgr = dComIfGp_getPEvtManager();
    if (evt_mgr->getEventData(evt_mgr->getEventIdx("btl_of_swroom", 0xFF)) != NULL) {
        int staff_id = evt_mgr->getMyStaffId("p_zelda", NULL, 0);
        if (staff_id != -1) {
            if (strcmp(evt_mgr->getMyNowCutName(staff_id), "Turn") == 0) {
                m08EA = false;
                m_jnt.mbTrn = true;
                m_jnt.mbHeadLock = false;
                m_jnt.mbBackBoneLock = false;
                if (cLib_calcTimer(&m08EC) == 0) {
                    evt_mgr->cutEnd(staff_id);
                }
            } else if (strcmp(evt_mgr->getMyNowCutName(staff_id), "Retire") == 0) {
                mEyeTimer = 0;
                if (mEyeBtpState >= REG8_S(0) + 4) {
                    mEyeBtpState = REG8_S(0) + 4;
                    getEventIce()->mLightShrinkTimer = 1;
                    mEyeTimer = 1000;
                    evt_mgr->cutEnd(staff_id);
                }
            } else {
                if (!getEventIce()->mLightShrinkTimer) {
                    mEyeTimer = 1000;
                }
                m_jnt.mbTrn = false;
            }
        }
    } else {
        m_jnt.mbTrn = false;
        m08EA = true;
        m_jnt.mbHeadLock = true;
        m_jnt.mbBackBoneLock = true;
    }
}

/* 00002FE8-000031E8       .text modeMoveInit__6daPz_cFv */
void daPz_c::modeMoveInit() {
    attention_info.flags |= 8;
    attention_info.flags |= 2;
    m08EC = l_HIO.mFollowTimerBase[m08B0] + cM_rndF(l_HIO.mFollowTimerRange[m08B0]);
    m08F0 = 10;
    m08F4 = 120;
    setAnm(3, false, 0xF);

    if (cM_rndF(100.0f) < l_HIO.m0D8) {
        if (m0920 == 1) {
            m0920 = -1;
        } else {
            m0920 = 1;
        }
    }

    if (l_HIO.m030 == 0) {
        if (mbHasGanondorf) {
            m08C4 = mGanondorfPos4;
        }
    } else {
        m08C4 = dNpc_playerEyePos(l_HIO.mNpc.m04);
    }

    mMovePath.mRadius = l_HIO.mMoveRadius[m08B0];
    mMovePath.mWobbleAmplitude = l_HIO.m0AC;
    mMovePath.mAngleSpeed = (REG12_S(0) + 0x150) * m0920;
    mMovePath.mTranslation = m08C4;
    dLib_setCirclePath(&mMovePath);

    m08EA = false;
    m_jnt.mbTrn = false;
    m_jnt.mbHeadLock = false;
    m_jnt.mbBackBoneLock = false;
}

/* 000031E8-0000395C       .text modeMove__6daPz_cFv */
void daPz_c::modeMove() {
    if (l_HIO.m032) {
        l_HIO.m032 = 0;
        modeProc(PROC_INIT_e, 7);
        return;
    }

    if (l_HIO.m034[0]) {
        l_HIO.m034[0] = 0;
        modeProc(PROC_INIT_e, 8);
        return;
    }

    bool blocked = false;
    m083C.Set(&current.pos, &mMovePath.mPos, this);
    if (dComIfG_Bgsp()->LineCross(&m083C)) {
        blocked = true;
    }
    if (mObjAcch.ChkWallHit()) {
        blocked = true;
    }

    if (cLib_calcTimer(&m08F8) == 0 && blocked) {
        m08F8 = 60;
        if (m0920 == 1) {
            m0920 = -1;
        } else {
            m0920 = 1;
        }
        mMovePath.mAngleSpeed = (REG12_S(0) + 0x4000) * m0920;
        if (cLib_calcTimer(&m08F4) == 0) {
            dLib_setCirclePath(&mMovePath);
            modeProc(PROC_INIT_e, 7);
        }
    }

    if ((u8)checkTgHit()) {
        return;
    }

    if (l_HIO.m030 == 0) {
        if (mbHasGanondorf) {
            m08C4 = mGanondorfPos4;
        }
    } else {
        m08C4 = dNpc_playerEyePos(l_HIO.mNpc.m04);
    }

    m_jnt.mbTrn = false;
    cLib_addCalc2(&mMovePath.mRadius, l_HIO.mMoveRadius[m08B0], 0.1f, 10.0f);

    f32 move_dist = (current.pos - mMovePath.mPos).absXZ();

    f32 eye_dist = (current.pos - m08C4).absXZ();
    (void)eye_dist;

    f32 target_dist = (m08C4 - mMovePath.mPos).absXZ();

    if (move_dist > 200.0f + REG12_F(7) || !mbEyesFollowGanondorf) {
        m0924 = l_HIO.m050;
    } else {
        m0924 = 0.0f;
    }

    if (blocked || move_dist <= 200.0f || target_dist >= 2.0f * l_HIO.mMoveRadius[m08B0] ||
        mbEyesFollowGanondorf)
    {
        mMovePath.mWobbleAmplitude = l_HIO.m0AC;
        mMovePath.mAngleSpeed = (REG12_S(0) + 0x150) * m0920;
        mMovePath.mTranslation = m08C4;
        dLib_setCirclePath(&mMovePath);
    }

    if (cLib_calcTimer(&m08F0) == 0) {
        f32 dist = 100000.0f;
        f32 dist_to_target = (current.pos - m08C4).absXZ();

        if (mbHasGanondorf) {
            dist = (current.pos - mGanondorfPosCurrent).absXZ();
        }

        if (mbEyesFollowGanondorf && (dist_to_target < l_HIO.m0D0 || dist < l_HIO.m0D0)) {
            m06C8 = mMode;
            modeProc(PROC_INIT_e, 8);
            return;
        }
    }

    cLib_addCalcAngleS2(&shape_angle.y, cLib_targetAngleY(&current.pos, &mMovePath.mPos), 8, 0x400);
    if (speedF < 0.5f) {
        setAnm(2, false, 0xF);
    } else {
        setAnm(3, false, 0xF);
    }

    if (m08B0 == 2) {
        fopAc_ac_c* player = dComIfGp_getLinkPlayer();
        m0F81[0] = dLib_checkActorInFan(player->current.pos, this, player->shape_angle.y, 0x2500, 30000.0f, 1000.0f);
    }

    if (!l_HIO.m034[1] && cLib_calcTimer(&m08EC) == 0) {
        if (m08B0 == 0) {
            modeProc(PROC_INIT_e, 2);
        } else if (m08B0 == 2) {
            if (!m0F65) {
                m0F81[0] = 1;
            }
            if (m0F81[0]) {
                modeProc(PROC_INIT_e, 2);
            }
        }
    }

    m0F82 = 2;
}

/* 0000395C-000039C0       .text modeAttackWaitInit__6daPz_cFv */
void daPz_c::modeAttackWaitInit() {
    m0924 = 0.0f;
    m08EC = 20;
    m08F0 = 10;
    setAnm(2, false, 0xF);
    m08EA = false;
    m_jnt.mbHeadLock = false;
    m_jnt.mbBackBoneLock = false;
}

/* 000039C0-00003D88       .text modeAttackWait__6daPz_cFv */
void daPz_c::modeAttackWait() {
    if ((u8)checkTgHit()) {
        return;
    }

    if (l_HIO.m030 == 0) {
        if (mbHasGanondorf) {
            m08C4 = mGanondorfPos4;
        }
    } else {
        m08C4 = dNpc_playerEyePos(l_HIO.mNpc.m04);
    }

    if (cLib_calcTimer(&m08F0) == 0) {
        f32 dist_to_target = (current.pos - m08C4).absXZ();

        f32 dist_to_ganondorf = 100000.0f;
        if (mbHasGanondorf) {
            dist_to_ganondorf = (current.pos - mGanondorfPosCurrent).absXZ();
        }

        if (mbEyesFollowGanondorf &&
            (dist_to_target < l_HIO.m0D0 || dist_to_ganondorf < l_HIO.m0D0))
        {
            m06C8 = mMode;
            if (cM_rndF(100.0f) < 50.0f) {
                modeProc(PROC_INIT_e, 8);
            } else {
                modeProc(PROC_INIT_e, 7);
            }
            return;
        }
    }

    if (m08B0 == 0) {
        fopAc_ac_c* ganondorf;
        if (fopAcM_SearchByName(PROC_GND, &ganondorf) && ganondorf->health > 60 &&
            dComIfGs_getLife() >= 12 && m075C)
        {
            m08C4 = dNpc_playerEyePos(l_HIO.mNpc.m04);
        }

        if (m0768 && mbHasGanondorf) {
            m08C4 = mGanondorfPos4;
        }
    } else {
        if (m075C) {
            m08C4 = dNpc_playerEyePos(l_HIO.mNpc.m04);
        }

        if (m0768 && mbHasGanondorf) {
            m08C4 = mGanondorfPos4;
        }
    }

    if (l_HIO.m02D && cLib_calcTimer(&m08EC) == 0) {
        modeProc(PROC_INIT_e, 3);
    }

    m_jnt.mbTrn = true;
}

/* 00003D88-00003F14       .text modeAttackInit__6daPz_cFv */
void daPz_c::modeAttackInit() {
    m08F4 = 30;

    int idx = m08B0;
    if (!m0F65) {
        idx = 0;
    }

    s8 cur_anm = mAnmPrmIdx;
    if (cur_anm != 4 && cur_anm != 5) {
        m08EC = l_HIO.mAttackTimerBase[idx] + cM_rndF(l_HIO.mAttackTimerRange[idx]);
        m08F0 = l_HIO.mAttackWaitTimer[idx];
        setAnm(4, false, 0xF);
    }

    if (cM_rndF(100.0f) < l_HIO.mAttackShootChance[idx]) {
        m0F48 = true;
    } else {
        m0F48 = false;
        if (cM_rndF(100.0f) < l_HIO.mAttackAimZeroChance[idx]) {
            m0F44 = 0.0f;
        } else {
            m0F44 = cM_rndF(l_HIO.mAttackAimRange[idx]);
        }
    }

    m08EA = false;
    m_jnt.mbHeadLock = true;
    m_jnt.mbBackBoneLock = false;
}

/* 00003F14-0000445C       .text modeAttack__6daPz_cFv */
void daPz_c::modeAttack() {
    if ((u8)checkTgHit()) {
        return;
    }

    // Original unused aim-spread temp.
    cXyz unused(m0F44, m0F44, m0F44);

    if (!m0F48) {
        if (mbHasGanondorf) {
            m08C4 = mGanondorfPos4;
        }
    } else {
        m08C4 = dNpc_playerEyePos(l_HIO.mNpc.m04);
    }

    if (m08B0 == 0) {
        fopAc_ac_c* ganondorf;
        if (fopAcM_SearchByName(PROC_GND, &ganondorf) && ganondorf->health > 60 &&
            dComIfGs_getLife() >= 12 && m075C)
        {
            m08C4 = dNpc_playerEyePos(l_HIO.mNpc.m04);
        }

        if (m0768 && mbHasGanondorf) {
            m08C4 = mGanondorfPos4;
        }
    } else {
        if (m075C) {
            m08C4 = dNpc_playerEyePos(l_HIO.mNpc.m04);
        }

        if (m0768 && mbHasGanondorf) {
            m08C4 = mGanondorfPos4;
        }
    }

    if ((mAnmPrmIdx == 4 || mAnmPrmIdx == 5) && cLib_calcTimer(&m08F4) == 0) {
        f32 dist_to_target = (current.pos - m08C4).absXZ();

        f32 dist_to_ganondorf = 100000.0f;
        if (mbHasGanondorf) {
            dist_to_ganondorf = (current.pos - mGanondorfPosCurrent).absXZ();
        }

        if (mbEyesFollowGanondorf &&
            (dist_to_target < l_HIO.m0D0 || dist_to_ganondorf < l_HIO.m0D0))
        {
            m06C8 = mMode;
            if (cM_rndF(100.0f) < 50.0f) {
                modeProc(PROC_INIT_e, 8);
            } else {
                modeProc(PROC_INIT_e, 7);
            }
            return;
        }
    }

    s8 anm_idx = mAnmPrmIdx;
    if (anm_idx == 4) {
        if (mpMorf->isStop()) {
            m_jnt.mbTrn = true;
            setAnm(5, false, 0xF);
            return;
        }
    }

    if ((s8)anm_idx == 5) {
        m_jnt.mbTrn = true;
        if (cLib_calcTimer(&m08EC) == 0) {
            setAnm(6, false, 0xF);
            return;
        }
    } else if ((s8)anm_idx == 6 && mpMorf->isStop()) {
        m_jnt.mbTrn = false;
        if (m075C) {
            m0758--;
            if (cLib_calcTimer(&m0758) != 0) {
                modeProc(PROC_INIT_e, 2);
                return;
            }
            m075C = 0;
        } else if (m0768) {
            m0764--;
            if (cLib_calcTimer(&m0764) != 0) {
                modeProc(PROC_INIT_e, 2);
                return;
            }
            m0768 = 0;
        } else {
            if (cLib_calcTimer(&m08F0) == 0) {
                modeProc(PROC_INIT_e, 1);
                return;
            }
            m08EA = true;
        }
    }
}

/* 0000445C-000044B4       .text modeDefendInit__6daPz_cFv */
void daPz_c::modeDefendInit() {
    setAnm(10, true, 0xF);
    m08EC = 30;
    m_jnt.mbTrn = false;
    m_jnt.mbHeadLock = true;
    m_jnt.mbBackBoneLock = true;
    m08EA = true;
}

/* 000044B4-00004630       .text modeDefend__6daPz_cFv */
void daPz_c::modeDefend() {
    m0924 = 0.0f;
    m_jnt.mbTrn = false;

    s16 target_angle = cLib_targetAngleY(&current.pos, &m0748);
    cLib_addCalcAngleS2(&shape_angle.y, target_angle, 4, 0x1000);
    cLib_distanceAngleS(shape_angle.y, target_angle);

    if (m0F68 > 0.01f) {
        cXyz offset(0.0f, 0.0f, -m0F68);
        cXyz rotated(0.0f, 0.0f, 0.0f);
        mDoMtx_stack_c::YrotS(m0F6C);
        mDoMtx_stack_c::multVec(&offset, &rotated);
        PSVECAdd(&current.pos, &rotated, &current.pos);
        cLib_addCalc0(&m0F68, 1.0f, 7.0f);

        int land_id;
        dComIfGp_particle_setSimpleLand(
            mObjAcch.m_gnd, &current.pos, &shape_angle, 1.25f, 1.5f, 1.0f, &tevStr, &land_id, 7
        );
    } else {
        if (m075C || m0768) {
            modeProc(PROC_INIT_e, 2);
        } else if (cLib_calcTimer(&m08EC) == 0) {
            modeProc(PROC_INIT_e, 1);
        }
    }

    if ((u8)checkTgHit()) {
        return;
    }
}

/* 00004630-0000470C       .text modeDownInit__6daPz_cFv */
void daPz_c::modeDownInit() {
    attention_info.flags &= ~8;
    attention_info.flags &= ~2;
    setAnm(7, true, 0xF);
    fopAcM_monsSeStart(this, JA_SE_CV_ZL_GN_DAMAGE, 0);
    setDown();
    m0924 = 0.0f;
    speedF = 0.0f;
    m08EA = false;
    m_jnt.mbTrn = false;
    m_jnt.mbHeadLock = true;
    m_jnt.mbBackBoneLock = true;
    speed.y = l_HIO.mDownSpeedY;
    m0F70 = l_HIO.mDownSpeedF;
    m08EC = l_HIO.mDownTimer;
}

/* 0000470C-00004C20       .text modeDown__6daPz_cFv */
void daPz_c::modeDown() {
    int land_id;

    m0924 = 0.0f;
    speedF = 0.0f;
    m_jnt.mbTrn = false;

    if (mAnmPrmIdx == 7 && mpMorf->getMorfRatio() == 1.0f && mObjAcch.ChkGroundHit()) {
        setAnm(8, false, 0xF);
    }

    if (cLib_calcTimer(&m08EC) != 0) {
        cXyz offset(m0F70, 0.0f, 0.0f);
        cXyz rotated(0.0f, 0.0f, 0.0f);
        mDoMtx_stack_c::YrotS(shape_angle.y);
        mDoMtx_stack_c::multVec(&offset, &rotated);
        PSVECAdd(&current.pos, &rotated, &current.pos);

        if (mAnmPrmIdx == 8 && mpMorf->isStop()) {
            dComIfGp_particle_setSimpleLand(
                mObjAcch.m_gnd, &current.pos, &shape_angle, 1.25f, 1.5f, 1.0f, &tevStr, &land_id, 7
            );
        }
    }

    int frame = mpMorf->getFrame();
    if (mAnmPrmIdx == 8) {
        if (frame == 1.0f + REG12_F(10)) {
            static s8 down_splash_scale_init;
            static Vec down_splash_scale;
            if (!down_splash_scale_init) {
                down_splash_scale.x = 0.6f;
                down_splash_scale.y = 0.6f;
                down_splash_scale.z = 0.6f;
                down_splash_scale_init = true;
            }

            JPABaseEmitter* emitter = dComIfGp_particle_setSimpleLand(
                mObjAcch.m_gnd, &current.pos, &shape_angle, 2.5f, 3.0f, 2.0f, &tevStr, &land_id, 7
            );

            if (emitter != NULL) {
                emitter->setRate(18.0f);
                emitter->setSpread(1.0f);
                emitter->mGlobalDynamicsScale.x = down_splash_scale.x;
                emitter->mGlobalDynamicsScale.y = down_splash_scale.y;
                emitter->mGlobalDynamicsScale.z = down_splash_scale.z;
                emitter->mGlobalParticleScale.x = down_splash_scale.x;
                emitter->mGlobalParticleScale.y = down_splash_scale.y;
                emitter->mGlobalParticleScale.z = down_splash_scale.z;
            }
        }

        if (frame == 2.0f + REG12_F(10)) {
            static s8 down_waist_splash_scale_init;
            static Vec down_waist_splash_scale;
            if (!down_waist_splash_scale_init) {
                down_waist_splash_scale.x = 0.6f;
                down_waist_splash_scale.y = 0.6f;
                down_waist_splash_scale.z = 0.6f;
                down_waist_splash_scale_init = true;
            }

            JPABaseEmitter* emitter = dComIfGp_particle_setSimpleLand(
                mObjAcch.m_gnd, &mWaistPos, &shape_angle, 2.5f, 3.0f, 2.0f, &tevStr, &land_id, 7
            );

            if (emitter != NULL) {
                emitter->setRate(18.0f);
                emitter->setSpread(1.0f);
                emitter->mGlobalDynamicsScale.x = down_waist_splash_scale.x;
                emitter->mGlobalDynamicsScale.y = down_waist_splash_scale.y;
                emitter->mGlobalDynamicsScale.z = down_waist_splash_scale.z;
                emitter->mGlobalParticleScale.x = down_waist_splash_scale.x;
                emitter->mGlobalParticleScale.y = down_waist_splash_scale.y;
                emitter->mGlobalParticleScale.z = down_waist_splash_scale.z;
            }
        }

        if (frame == 3.0f + REG12_F(10)) {
            static s8 down_head_splash_scale_init;
            static Vec down_head_splash_scale;
            if (!down_head_splash_scale_init) {
                down_head_splash_scale.x = 0.6f;
                down_head_splash_scale.y = 0.6f;
                down_head_splash_scale.z = 0.6f;
                down_head_splash_scale_init = true;
            }

            JPABaseEmitter* emitter = dComIfGp_particle_setSimpleLand(
                mObjAcch.m_gnd, &mHeadFrontPos, &shape_angle, 2.5f, 3.0f, 2.0f, &tevStr, &land_id, 7
            );

            if (emitter != NULL) {
                emitter->setRate(18.0f);
                emitter->setSpread(1.0f);
                emitter->mGlobalDynamicsScale.x = down_head_splash_scale.x;
                emitter->mGlobalDynamicsScale.y = down_head_splash_scale.y;
                emitter->mGlobalDynamicsScale.z = down_head_splash_scale.z;
                emitter->mGlobalParticleScale.x = down_head_splash_scale.x;
                emitter->mGlobalParticleScale.y = down_head_splash_scale.y;
                emitter->mGlobalParticleScale.z = down_head_splash_scale.z;
            }
        }
    }

    if (mAnmPrmIdx == 8 && mpMorf->isStop()) {
        m08EA = true;
    }

    if (m08B0 != 1) {
        if (mAnmPrmIdx == 9) {
            if (mpMorf->isStop()) {
                m08EA = false;
                setAnm(2, false, 0xF);
            }
        } else if (m0740[0]) {
            m0740[0] = 0;
            m0F7C = l_HIO.mTalkTimer[2];
            m0F80 = 0;
            m075C = 0;
            m0768 = 0;
            modeProc(PROC_INIT_e, 1);
        } else {
            setAnm(9, false, 0xF);
        }
    }
}

/* 00004C20-00004C78       .text modeAfraidInit__6daPz_cFv */
void daPz_c::modeAfraidInit() {
    setAnm(11, true, 0xF);
    m0924 = 0.0f;
    speedF = 0.0f;
    m08EA = false;
    m_jnt.mbHeadLock = false;
    m_jnt.mbBackBoneLock = false;
}

/* 00004C78-00004E8C       .text modeAfraid__6daPz_cFv */
void daPz_c::modeAfraid() {
    m0924 = 0.0f;
    speedF = 0.0f;
    m08EA = false;
    m_jnt.mbTrn = false;
    m073F = 0;
    m_jnt.mbHeadLock = false;
    m_jnt.mbBackBoneLock = false;

    fopAc_ac_c* ganondorf;
    if (fopAcM_SearchByName(PROC_GND, &ganondorf)) {
        if (REG12_S(9) == 1) {
            m08C4 = ganondorf->current.pos;
            m08C4.y += 1200.0f + REG12_F(10);
        } else if (REG12_S(9) == 2) {
            m08C4 = ganondorf->eyePos;
            m08C4.y += 800.0f + REG12_F(10);
        } else {
            m08C4 = ganondorf->current.pos;

            f32 dist = (current.pos - ganondorf->current.pos).absXZ();
            f32 min_y = ganondorf->current.pos.y + 50.0f;

            f32 dist_scale = 0.5f;
            m08C4.y = 8.0f * (ganondorf->eyePos.y - dist * dist_scale);
            if (m08C4.y <= min_y) {
                m08C4.y = min_y;
            }
        }

        cLib_addCalcAngleS2(&shape_angle.y, cLib_targetAngleY(&current.pos, &ganondorf->current.pos), 4, 0x400);
    }
}

/* 00004E8C-00004F08       .text modeSideStepInit__6daPz_cFv */
void daPz_c::modeSideStepInit() {
    if (m06C8 != 2 && m06C8 != 3) {
        setAnm(11, true, 0xF);
    }
    m0924 = 0.0f;
    speedF = 0.0f;
    m08EA = false;
    speed.y = l_HIO.mSideStepSpeedY;
    m0F70 = l_HIO.mSideStepSpeedF;
}

/* 00004F08-00005098       .text modeSideStep__6daPz_cFv */
void daPz_c::modeSideStep() {
    if ((u8)checkTgHit()) {
        mWaist2RotY = 0;
        return;
    }

    m0924 = 0.0f;
    speedF = 0.0f;
    m08EA = false;
    m_jnt.mbTrn = true;
    m073F = 0;
    cLib_addCalcAngleS2(&mWaist2RotY, m0920 * 0x1194, 4, 0x800);

    s16 angle = cLib_targetAngleY(&mHeadFrontPos, &m08C4);
    cXyz offset(m0F70 * (f32)m0920, 0.0f, 0.0f);
    cXyz rotated(0.0f, 0.0f, 0.0f);
    mDoMtx_stack_c::YrotS(angle);
    mDoMtx_stack_c::multVec(&offset, &rotated);
    PSVECAdd(&current.pos, &rotated, &current.pos);

    if (mObjAcch.ChkGroundHit()) {
        int land_id;
        mWaist2RotY = 0;
        dComIfGp_particle_setSimpleLand(
            mObjAcch.m_gnd, &current.pos, &shape_angle, 1.25f, 1.5f, 1.0f, &tevStr, &land_id, 7
        );

        if (m06C8 == 2 || m06C8 == 3) {
            modeProc(PROC_INIT_e, 3);
        } else {
            modeProc(PROC_INIT_e, 1);
        }
    }
}

/* 00005098-00005114       .text modeBackStepInit__6daPz_cFv */
void daPz_c::modeBackStepInit() {
    if (m06C8 != 2 && m06C8 != 3) {
        setAnm(11, true, 0xF);
    }
    m0924 = 0.0f;
    speedF = 0.0f;
    m08EA = false;
    speed.y = l_HIO.mBackStepSpeedY;
    m0F70 = l_HIO.mBackStepSpeedF;
}

/* 00005114-0000527C       .text modeBackStep__6daPz_cFv */
void daPz_c::modeBackStep() {
    if ((u8)checkTgHit()) {
        mWaist2RotZ = 0;
        return;
    }

    m0924 = 0.0f;
    speedF = 0.0f;
    m08EA = false;
    m_jnt.mbTrn = true;
    m073F = 0;
    cLib_addCalcAngleS2(&mWaist2RotZ, -0x1194, 4, 0x800);

    s16 angle = cLib_targetAngleY(&current.pos, &m08C4);
    cXyz offset(0.0f, 0.0f, -m0F70);
    cXyz rotated(0.0f, 0.0f, 0.0f);
    mDoMtx_stack_c::YrotS(angle);
    mDoMtx_stack_c::multVec(&offset, &rotated);
    PSVECAdd(&current.pos, &rotated, &current.pos);

    if (mObjAcch.ChkGroundHit()) {
        int land_id;
        mWaist2RotZ = 0;
        dComIfGp_particle_setSimpleLand(
            mObjAcch.m_gnd, &current.pos, &shape_angle, 1.25f, 1.5f, 1.0f, &tevStr, &land_id, 7
        );

        if (m06C8 == 2 || m06C8 == 3) {
            modeProc(PROC_INIT_e, 3);
        } else {
            modeProc(PROC_INIT_e, 1);
        }
    }
}

/* 0000527C-00005304       .text modeTalkInit__6daPz_cFv */
void daPz_c::modeTalkInit() {
    setAnm(2, true, 0xF);
    speedF = 0.0f;
    m0924 = 0.0f;
    m08EA = false;
    m_jnt.mbHeadLock = false;
    m_jnt.mbBackBoneLock = false;
    if (m08B0 == 0) {
        m0F80 = true;
    } else {
        m0F7C = l_HIO.mTalkTimer[m08B0];
    }
}

/* 00005304-0000539C       .text modeTalk__6daPz_cFv */
void daPz_c::modeTalk() {
    m08C4 = dNpc_playerEyePos(l_HIO.mNpc.m04);
    m_jnt.mbTrn = true;
    if (talk(1) == fopMsgStts_BOX_CLOSED_e) {
        dComIfGp_event_onEventFlag(dEvtFlag_UNK8_e);
        modeProc((Proc_e)0, 2);
    }
}

/* 0000539C-0000549C       .text modeFollowInit__6daPz_cFv */
void daPz_c::modeFollowInit() {
    attention_info.flags |= 8;
    attention_info.flags |= 2;
    m08EC = l_HIO.mFollowTimerBase[m08B0] + cM_rndF(l_HIO.mFollowTimerRange[m08B0]);
    m08F0 = 10;
    m08F4 = 120;
    setAnm(3, false, 0xF);
    m08EA = false;
    m_jnt.mbTrn = false;
    m_jnt.mbHeadLock = false;
    m_jnt.mbBackBoneLock = false;
}

/* 0000549C-000059B8       .text modeFollow__6daPz_cFv */
void daPz_c::modeFollow() {
    bool blocked = false;
    m083C.Set(&current.pos, &m0830, this);
    if (dComIfG_Bgsp()->LineCross(&m083C)) {
        blocked = true;
    }
    if (mObjAcch.ChkWallHit()) {
        blocked = true;
    }

    if ((u8)checkTgHit()) {
        return;
    }

    if (l_HIO.m030 == 0) {
        if (mbHasGanondorf) {
            m08C4 = mGanondorfPos4;
        }
    } else {
        m08C4 = dNpc_playerEyePos(l_HIO.mNpc.m04);
    }

    m_jnt.mbTrn = false;

    f32 follow_dist = (current.pos - m0830).absXZ();

    if (follow_dist > 200.0f && !mbEyesFollowGanondorf && !blocked) {
        m0924 = l_HIO.m050;
    } else {
        if (mbEyesFollowGanondorf) {
            m0924 = 0.0f;
        } else if (blocked) {
            m0924 = 2.0f;
        } else {
            m0924 = 1.0f;
        }
    }

    f32 offset = l_HIO.m0EC;
    fopAc_ac_c* player = dComIfGp_getLinkPlayer();
    m0830 = mGanondorfPosCurrent;
    s16 angle = cLib_targetAngleY(&player->current.pos, &mGanondorfPosCurrent);
    cLib_distanceAngleS(angle, shape_angle.y);
    m0830.x += offset * cM_ssin(REG12_S(0) + (angle + 0x4000));
    m0830.z += offset * cM_scos(REG12_S(0) + (angle + 0x4000));
    m0830.y += 200.0f;

    if (cLib_calcTimer(&m08F0) == 0) {
        f32 dist_to_ganondorf = 100000.0f;
        f32 dist_to_target = (current.pos - m08C4).absXZ();

        if (mbHasGanondorf) {
            dist_to_ganondorf = (current.pos - mGanondorfPosCurrent).absXZ();
        }

        if (mbEyesFollowGanondorf &&
            (dist_to_target < l_HIO.m0D0 || dist_to_ganondorf < l_HIO.m0D0))
        {
            m06C8 = mMode;
            modeProc(PROC_INIT_e, 8);
            return;
        }
    }

    cLib_addCalcAngleS2(&shape_angle.y, cLib_targetAngleY(&current.pos, &m0830), 8, 0x400);
    if (speedF < 0.5f) {
        setAnm(2, false, 0xF);
    } else {
        setAnm(3, false, 0xF);
    }

    if (!l_HIO.m034[1] && cLib_calcTimer(&m08EC) == 0) {
        modeProc(PROC_INIT_e, 2);
    }

    m0F82 = 2;
}

/* 000059B8-00005C58       .text modeProc__6daPz_cFQ26daPz_c6Proc_ei */
void daPz_c::modeProc(daPz_c::Proc_e proc, int mode) {
    typedef void (daPz_c::*ProcFunc)();
    struct ProcEntry {
        /* 0x00 */ ProcFunc init;
        /* 0x0C */ ProcFunc run;
        /* 0x18 */ const char* name;
    };

    static ProcEntry mode_tbl[] = {
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

    if (proc == PROC_INIT_e) {
        mMode = mode;
        (this->*mode_tbl[mMode].init)();
    } else if (proc == PROC_EXEC_e) {
        (this->*mode_tbl[mMode].run)();
    }
}

/* 00005C58-000060D8       .text _execute__6daPz_cFv */
bool daPz_c::_execute() {
    if (l_HIO.m033) {
        modeProc(PROC_INIT_e, 0);

        fopAc_ac_c* player = dComIfGp_getLinkPlayer();
        current.pos = player->current.pos;
        current.pos.y += 50.0f;
        current.pos.x -= 200.0f * cM_ssin(player->shape_angle.y);
        current.pos.z -= 200.0f * cM_scos(player->shape_angle.y);
    }

    setFallSplash();
    getGndPos();

    mbEyesFollowGanondorf = false;
    if (mbHasGanondorf) {
        mbEyesFollowGanondorf = checkEyeArea(mGanondorfPosCurrent);
    }

    gravity = l_HIO.m0B0;

    if (mMode != 6 && mMode != 5 && m073F) {
        modeProc(PROC_INIT_e, 6);
    }

    setRipple();

    if (mMode != 5 && m08B0 == 1) {
        modeProc(PROC_INIT_e, 5);
    }

    setJntStatus();

    if (demo()) {
        mBtkAnm.play();
        mBrkAnm.play();
        setMtx();
        g_env_light.settingTevStruct(0, &current.pos, &tevStr);
        return true;
    }

    current.angle = shape_angle;
    mpMorf->calc();
    enemy_fire(getEnemyFire());
    if (enemy_ice(getEventIce())) {
        J3DModel* model = mpMorf->getModel();
        PSMTXCopy(mDoMtx_stack_c::get(), model->getBaseTRMtx());
        return true;
    }

    if (mAnmPrmIdx == 9) {
        setHeadSplash();
    }

    if (mArg == 0 && (m08B0 == 0 || m08B0 == 2) && !m0F80 && mMode != 2 && mMode != 3 &&
        mMode != 5 && mMode != 9 && cLib_calcTimer(&m0F7C) == 0)
    {
        fopAc_ac_c* ganondorf;
        if (fopAcM_SearchByName(PROC_GND, &ganondorf)) {
            gnd_class* gnd = (gnd_class*)ganondorf;
            f32 dist = fopAcM_searchActorDistanceXZ(this, dComIfGp_getPlayer(0));
            if (dist < (&l_HIO.m100)[m08B0] && gnd->m02CE == 0) {
                m0F82 = 1;
                modeProc(PROC_INIT_e, 9);
            }
        }
    }

    checkOrder();
    modeProc(PROC_EXEC_e, 11);
    eventOrder();
    setAttention();

    cLib_addCalc2(&speedF, m0924, 0.3f, 4.0f);

    u8 room_no = current.roomNo;
    u32 mtrl_snd_id;
    if (mObjAcch.ChkGroundHit()) {
        mtrl_snd_id = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
    } else {
        mtrl_snd_id = 0;
    }

    s8 reverb = dComIfGp_getReverb((s8)room_no);
    mpMorf->play(&eyePos, mtrl_snd_id, reverb);
    mpBowMcaMorf->play(NULL, 0, 0);
    mBrkAnm.play();
    playEyeAnm();

    if (l_HIO.m02F) {
        setAnm(l_HIO.m02F, false, 0xF);
    }

    fopAcM_posMoveF(this, NULL);
    mObjAcch.CrrPos(*dComIfG_Bgsp());
    if (!dComIfGp_event_runCheck()) {
        setCollision(30.0f, 130.0f);
    }
    setAnmRunSpeed();

    current.angle = shape_angle;
    setMtx();
    g_env_light.settingTevStruct(0, &current.pos, &tevStr);
    return true;
}

/* 000060D8-00006154       .text bowDraw__6daPz_cFv */
void daPz_c::bowDraw() {
    g_env_light.setLightTevColorType(mpBowMcaMorf->getModel(), &tevStr);
    PSMTXCopy(mpMorf->getModel()->getAnmMtx(14), mDoMtx_stack_c::get());
    mpBowMcaMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpBowMcaMorf->updateDL();
}

/* 00006154-00006600       .text bodyDraw__6daPz_cFv */
void daPz_c::bodyDraw() {
    static const GXColor color_ok = {0x00, 0xFF, 0x00, 0x80};
    static const GXColor color_ng = {0xFF, 0x00, 0x00, 0x80};
    static const u32 debug_colors[] = {
        0xFFFF0080,
        0xFF000080,
        0xFFFF0080,
        0x0000FF80,
        0xFF00FF80,
        0x461C4000,
    };

    J3DModel* model = mpMorf->getModel();
    J3DModelData* modelData = model->getModelData();

    g_env_light.setLightTevColorType(model, &tevStr);
    mpMorf->calc();
    model->unlock();

    if (mArg != 0) {
        mBrkAnm.entry(modelData, mBrkAnm.getFrame());
    }

    j3dSys.setDrawBuffer(g_dComIfG_gameInfo.drawlist.mpOpaListP0, OPA_BUFFER);
    j3dSys.setDrawBuffer(g_dComIfG_gameInfo.drawlist.mpOpaListP0, XLU_BUFFER);
    mBtpAnm.entry(modelData, mEyeBtpState);
    m1084.entryOpa();

    for (u16 i = 0; i < modelData->getMaterialNum(); i++) {
        J3DMaterial* mat = modelData->getMaterialNodePointer(i);
        if (i != 3 && i != 6 && i != 0x0D && i != 0x10) {
            mat->getShape()->hide();
        } else {
            mat->getShape()->show();
        }
    }
    mRootJoint->entryIn();
    m1064.entryOpa();

    mBtkAnm.entry(modelData, mBtkAnm.getFrame());

    mEyeShape[0]->hide();
    mEyeShape[3]->hide();
    mEyeShape[2]->show();
    mEyeShape[5]->show();
    mEyebrowShape[0]->hide();
    mEyebrowShape[3]->hide();
    mEyebrowShape[2]->show();
    mEyebrowShape[5]->show();
    mRootJoint->entryIn();
    modelData->getMaterialTable().removeTexMtxAnimator(mBtkAnm.getBtkAnm());

    mEyeShape[2]->hide();
    mEyeShape[5]->hide();
    mEyebrowShape[2]->hide();
    mEyebrowShape[5]->hide();
    for (int i = 0; i < 4; i++) {
        mFaceShape[i]->show();
    }
    mRootJoint->entryIn();
    m1074.entryOpa();

    for (int i = 0; i < 4; i++) {
        mFaceShape[i]->hide();
    }
    mEyeShape[1]->show();
    mEyeShape[4]->show();
    mEyebrowShape[1]->show();
    mEyebrowShape[4]->show();
    mRootJoint->entryIn();
    m1054.entryOpa();

    mEyeShape[1]->hide();
    mEyeShape[4]->hide();
    mEyebrowShape[1]->hide();
    mEyebrowShape[4]->hide();

    j3dSys.setDrawBuffer(g_dComIfG_gameInfo.drawlist.mpOpaListP1, OPA_BUFFER);
    j3dSys.setDrawBuffer(g_dComIfG_gameInfo.drawlist.mpXluListP1, XLU_BUFFER);
    for (u16 i = 0; i < modelData->getMaterialNum(); i++) {
        if (i != 3 && i != 2 && i != 1 && i != 6 && i != 5 && i != 4 && i != 0x0D &&
            i != 0x0C && i != 0x0B && i != 0x10 && i != 0x0F && i != 0x0E && i != 0x12 &&
            i != 0x13 && i != 0x08 && i != 0x07)
        {
            modelData->getMaterialNodePointer(i)->getShape()->show();
        }
    }
    mpMorf->entryDL();

    j3dSys.setDrawBuffer(g_dComIfG_gameInfo.drawlist.mpOpaList, OPA_BUFFER);
    j3dSys.setDrawBuffer(g_dComIfG_gameInfo.drawlist.mpXluList, XLU_BUFFER);
    for (u16 i = 0; i < modelData->getMaterialNum(); i++) {
        modelData->getMaterialNodePointer(i)->getShape()->show();
    }

    modelData->getMaterialTable().removeTexNoAnimator(mBtpAnm.getBtpAnm());
    if (mArg != 0) {
        modelData->getMaterialTable().removeTevRegAnimator(mBrkAnm.getBrkAnm());
    }
}

/* 00006600-000066D8       .text drawShadow__6daPz_cFv */
void daPz_c::drawShadow() {
    cXyz shadowPos(
        current.pos.x,
        current.pos.y + 100.0f + REG8_F(18),
        current.pos.z
    );

    m0774 = dComIfGd_setShadow(
        m0774, 1, mpMorf->getModel(), &shadowPos, 250.0f + REG8_F(19), 40.0f,
        current.pos.y, mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr, 0, 1.0f,
        dDlst_shadowControl_c::getSimpleTex()
    );

    if (m0F88 && m0774 != 0) {
        dComIfGd_addRealShadow(m0774, mpBowMcaMorf->getModel());
    }
}

/* 000066D8-0000676C       .text _draw__6daPz_cFv */
bool daPz_c::_draw() {
    if (getEventIce()->mFreezeTimer > 20) {
        dMat_control_c::iceEntryDL(mpMorf, -1, &mInvisibleModel);
    } else {
        bodyDraw();
    }
    if (m0F88) {
        bowDraw();
    }
    drawShadow();
    dSnap_RegistFig(DSNAP_TYPE_UNK87, this, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 0000676C-00006974       .text bodyCreateInit__6daPz_cFv */
void daPz_c::bodyCreateInit() {
    static u8 l_eyeMatNo[] = {
        3, 2, 1, 6, 5, 4,
    };
    static u8 l_eyeblowMatNo[] = {
        0x0D, 0x0C, 0x0B, 0x10, 0x0F, 0x0E,
    };
    static u8 l_faceMatNo[] = {
        0x12, 0x13, 0x08, 0x07,
    };

    if (strcmp(dComIfGp_getStartStageName(), "GTower") == 0) {
        eventInfo.setEventId(dComIfGp_evmng_getEventIdx("PZ_TALK", 0xFF));
    }

    J3DModelData* modelData = mpMorf->getModel()->getModelData();
    mRootJoint = modelData->getJointNodePointer(0);

    for (int i = 0; i < 6; i++) {
        mEyeMat[i] = modelData->getMaterialNodePointer(l_eyeMatNo[i]);
        mEyeShape[i] = mEyeMat[i]->getShape();
    }

    for (int i = 0; i < 6; i++) {
        mEyebrowMat[i] = modelData->getMaterialNodePointer(l_eyeblowMatNo[i]);
        mEyebrowShape[i] = mEyebrowMat[i]->getShape();
    }

    for (int i = 0; i < 4; i++) {
        mFaceMat[i] = modelData->getMaterialNodePointer(l_faceMatNo[i]);
        mFaceShape[i] = mFaceMat[i]->getShape();
    }

    J3DMaterialAnm* mat_anm = mEyeMat[2]->getMaterialAnm();
    mEyeMat[1]->setMaterialAnm(mat_anm);
    mEyeMat[0]->setMaterialAnm(mat_anm);

    mat_anm = mEyeMat[5]->getMaterialAnm();
    mEyeMat[4]->setMaterialAnm(mat_anm);
    mEyeMat[3]->setMaterialAnm(mat_anm);

    mat_anm = mEyebrowMat[2]->getMaterialAnm();
    mEyebrowMat[1]->setMaterialAnm(mat_anm);
    mEyebrowMat[0]->setMaterialAnm(mat_anm);

    mat_anm = mEyebrowMat[5]->getMaterialAnm();
    mEyebrowMat[4]->setMaterialAnm(mat_anm);
    mEyebrowMat[3]->setMaterialAnm(mat_anm);
}

/* 00006974-00006BAC       .text createInit__6daPz_cFv */
void daPz_c::createInit() {
    static u8 fire_j[ARRAY_SIZE(mEnemyFire_mFlameJntIdxs)] = {
        0x07,
        0x02,
        0x0C,
        0x0D,
        0x11,
        0x12,
        0x16,
        0x17,
        0x19,
        0x1A,
    };
    static f32 fire_sc[ARRAY_SIZE(mEnemyFire_mParticleScale)] = {
        2.0f,
        2.0f,
        1.0f,
        1.0f,
        1.0f,
        1.0f,
        1.0f,
        1.0f,
        1.0f,
        1.0f,
    };

    max_health = 30;
    health = max_health;
    stealItemLeft = 10;

    mEnemyFire_mpMcaMorf = mpMorf;
    mEnemyFire_mpActor = this;
    for (int i = 0; i < ARRAY_SIZE(mEnemyFire_mFlameJntIdxs); i++) {
        mEnemyFire_mFlameJntIdxs[i] = fire_j[i];
        mEnemyFire_mParticleScale[i] = fire_sc[i];
    }

    mEventIce_mpActor = this;
    mEventIce_m00C = true;
    mEventIce_mWallRadius = 50.0f;
    mEventIce_mCylHeight = 250.0f;

    m08B0 = 0;
    m0F7C = l_HIO.mTalkTimer[0];
    m0F80 = 0;
    bodyCreateInit();

    if (mArg == 0) {
        m0F88 = true;
        modeProcInit(1);
        attention_info.distances[1] = 3;
        attention_info.distances[3] = 3;
        attention_info.flags |= fopAc_Attn_ACTION_SPEAK_e;
        attention_info.flags |= fopAc_Attn_LOCKON_TALK_e;
    } else {
        attention_info.flags = fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_LOCKON_TALK_e;
        modeProcInit(0);
    }

    m0920 = 1;
    cullMtx = mpMorf->getModel()->getBaseTRMtx();
    fopAcM_setCullSizeBox(this, -60.0f, -50.0f, -60.0f, 60.0f, 1800.0f, 60.0f);
    mAcchCir.SetWall(80.0f, 60.0f);
    mObjAcch.Set(&current.pos, &old.pos, this, 1, &mAcchCir, &speed, NULL, NULL);
    mObjAcch.SetRoofNone();
    gravity = l_HIO.m0B0;

    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(m_cyl_src);
    mCyl.SetStts(&mStts);
    setCollision(30.0f, 130.0f);

    dKy_tevstr_init(&mTevstr, home.roomNo, 0xFF);
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
}

/* 00006BAC-00006CB0       .text _create__6daPz_cFv */
cPhs_State daPz_c::_create() {
    cPhs_State phase_state = dComIfG_resLoad(&mPhs, m_arc_name);
    fopAcM_ct(this, daPz_c);

    if (phase_state == cPhs_COMPLEATE_e) {
        getArg();

        if (mArg != 0 && strcmp(dComIfGp_getStartStageName(), "kenroom") == 0 &&
            dComIfGs_isEventBit(0x3520) == TRUE)
        {
            return cPhs_ERROR_e;
        }

        if (!fopAcM_entrySolidHeap(this, createHeap_CB, m_heapsize)) {
            return cPhs_ERROR_e;
        }

        createInit();
    }

    return phase_state;
}

/* 00007DA0-00007E20       .text _delete__6daPz_cFv */
bool daPz_c::_delete() {
    dComIfG_resDelete(&mPhs, m_arc_name);
    mRipple.end();

    dPa_followEcallBack* follow_cb = &mFallSplash;
    follow_cb->end();
    follow_cb = &mHeadSplash;
    follow_cb->end();

    if (heap != NULL) {
        mpMorf->stopZelAnime();
    }
    return TRUE;
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
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_PZ,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daPz_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_PZ,
    /* Actor SubMtd */ &daPzMethodTable,
    /* Status       */ 0x08 | fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
