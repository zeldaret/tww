/**
 * d_a_npc_kg1.cpp
 * NPC - Squid-Hunt minigame host
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_kg1.h"
#include "d/actor/d_a_mgameboard.h"
#include "d/actor/d_a_player.h"
#include "d/d_camera.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "d/d_lib.h"
#include "d/d_snap.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_camera.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_audio.h"
#include "m_Do/m_Do_controller_pad.h"
#include "SSystem/SComponent/c_lib.h"
#include "SSystem/SComponent/c_math.h"

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

/* 000000EC-000001E0       .text __ct__15daNpc_Kg1_HIO_cFv */
daNpc_Kg1_HIO_c::daNpc_Kg1_HIO_c() {
    mNo = -1;
    mChildCount = -1;
    mNpc[0].m04 = 0.0f;
    mNpc[0].mMaxHeadX = 0x9C4;
    mNpc[0].mMaxHeadY = 0x1B58;
    mNpc[0].mMaxBackboneX = 0x7D0;
    mNpc[0].mMaxBackboneY = 0x1F40;
    mNpc[0].mMinHeadX = -0x9C4;
    mNpc[0].mMinHeadY = -0x1B58;
    mNpc[0].mMinBackboneX = -0x7D0;
    mNpc[0].mMinBackboneY = -0x1F40;
    mNpc[0].mMaxTurnStep = 0x3E8;
    mNpc[0].mMaxHeadTurnVel = 0x7D0;
    mNpc[0].mAttnYOffset = 35.0f;
    mNpc[0].mMaxAttnAngleY = 0x4000;
    mNpc[0].m22 = 0;
    mNpc[0].mMaxAttnDistXZ = 400.0f;
    m0C = 0;
    m38 = 0;
    m39 = 0;
}

const char daNpc_Kg1_c::m_arcname[] = "Kg";
const f32 daNpc_Kg1_c::m_camera_fovy = 40.0f;
cXyz daNpc_Kg1_c::m_camera_ctr(-200.0f, 140.0f, 85.0f);
cXyz daNpc_Kg1_c::m_camera_eye(-117.0f, 92.0f, 344.0f);

static const int l_btp_ix_tbl[] = {9, 11, 13, 12};

static daNpc_Kg1_HIO_c l_HIO;

/* 000001E0-00000428       .text daNpc_Kg1_nodeCallBack__FP7J3DNodei */
static BOOL daNpc_Kg1_nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daNpc_Kg1_c* i_this = (daNpc_Kg1_c*)model->getUserArea();
        u16 jntNo = ((J3DJoint*)node)->getJntNo();
        mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));
        if (jntNo == i_this->m_jnt.getHeadJntNum()) {
            mDoMtx_stack_c::XrotM(i_this->m_jnt.getHead_y());
            mDoMtx_stack_c::ZrotM(-i_this->m_jnt.getHead_x());
            static cXyz l_offsetAttPos(24.0f, 5.0f, 0.0f);
            static cXyz l_offsetEyePos(24.0f, -16.0f, 0.0f);
            mDoMtx_stack_c::multVec(&l_offsetAttPos, &i_this->m740);
            mDoMtx_stack_c::XrotM(i_this->m_jnt.getHead_y());
            mDoMtx_stack_c::ZrotM(-i_this->m_jnt.getHead_x());
            mDoMtx_stack_c::multVec(&l_offsetEyePos, &i_this->m734);
            mDoMtx_stack_c::multVec(&l_offsetAttPos, &i_this->attention_info.position);
            i_this->attention_info.position.y += l_HIO.mNpc[0].mAttnYOffset;
        }
        if (jntNo == i_this->m_jnt.getBackboneJntNum()) {
            mDoMtx_stack_c::XrotM(i_this->m_jnt.getBackbone_y());
            mDoMtx_stack_c::ZrotM(-i_this->m_jnt.getBackbone_x());
        }
        model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
        cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
        if (jntNo == 8) {
            mDoMtx_stack_c::transM(23.46f, -22.26f, -47.05f);
            mDoMtx_stack_c::XYZrotM(0x1F4B, -0x4F00, 0x1F4B);
            i_this->mpItemModel->setBaseTRMtx(mDoMtx_stack_c::get());
        }
    }
    return TRUE;
}

/* 00000464-00000688       .text lookBack__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::lookBack() {
    cXyz diff = dComIfGp_getPlayer(0)->current.pos - current.pos;
    f32 dist = diff.absXZ();
    cXyz* dstPos = NULL;
    cXyz pos;
    if (mEventCut.getAttnFlag()) {
        m_jnt.setTrn();
        pos = mEventCut.getAttnPos();
        dstPos = &pos;
        m731 = 1;
    } else if (mAnmPrmIdx == 8) {
        pos = m_camera_eye;
        dstPos = &pos;
    } else if (dist < l_HIO.mNpc[0].mMaxAttnDistXZ) {
        pos = dNpc_playerEyePos(l_HIO.mNpc[0].m04);
        dstPos = &pos;
        m731 = chkAttention();
    } else {
        m731 = 0;
    }
    if (m_jnt.trnChk()) {
        s16 target = l_HIO.mNpc[0].mMaxHeadTurnVel;
        if (mEventCut.getTurnSpeed() != 0) {
            target = mEventCut.getTurnSpeed();
        }
        cLib_addCalcAngleS2(&mHeadTurnVel, target, 4, 0x800);
    } else {
        mHeadTurnVel = 0;
    }
    cXyz eye = eyePos;
    m_jnt.lookAtTarget(&shape_angle.y, dstPos, eye, shape_angle.y, mHeadTurnVel, true);
}

/* 00000688-000007D8       .text chkAttention__11daNpc_Kg1_cFv */
BOOL daNpc_Kg1_c::chkAttention() {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    cXyz diff = player->current.pos - current.pos;
    f32 dist = diff.absXZ();
    s16 maxAngle = l_HIO.mNpc[0].mMaxAttnAngleY;
    if (dist < l_HIO.mNpc[0].mMaxAttnDistXZ) {
        f32 dx = player->current.pos.x - current.pos.x;
        f32 dz = player->current.pos.z - current.pos.z;
        s16 angle = cM_atan2s(dx, dz);
        if (abs((s16)(angle - (s16)(shape_angle.y + (m_jnt.getHead_y() + m_jnt.getBackbone_y())))) < maxAngle) {
            return TRUE;
        }
    }
    return FALSE;
}

/* 000007D8-000008D8       .text initTexPatternAnm__11daNpc_Kg1_cFib */
BOOL daNpc_Kg1_c::initTexPatternAnm(int idx, bool modify) {
    J3DModelData* modelData = mpMorf->getModel()->getModelData();
    m_eye_tex_pattern = (J3DAnmTexPattern*)dComIfG_getObjectRes(m_arcname, l_btp_ix_tbl[idx]);
    JUT_ASSERT(0x1CC, m_eye_tex_pattern != 0);
    if (!mEyeBtp.init(modelData, m_eye_tex_pattern, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, modify, 0)) {
        return FALSE;
    }
    mEyeFrame = 0;
    mEyeTimer = 0;
    return TRUE;
}

/* 000008D8-00000944       .text playTexPatternAnm__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::playTexPatternAnm() {
    if (cLib_calcTimer(&mEyeTimer) == 0) {
        if (mEyeFrame >= m_eye_tex_pattern->getFrameMax()) {
            mEyeFrame -= m_eye_tex_pattern->getFrameMax();
            mEyeTimer = 120;
        } else {
            mEyeFrame++;
        }
    }
}

/* 00000944-000009E8       .text set_mtx__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::set_mtx() {
    J3DModel* model = mpMorf->getModel();
    model->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpItemModel->setBaseScale(scale);
}

/* 000009E8-00000A08       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Kg1_c*)i_this)->CreateHeap();
}

/* 00000A08-00000D34       .text CreateHeap__11daNpc_Kg1_cFv */
BOOL daNpc_Kg1_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, 5);
    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL, NULL,
        (J3DAnmTransform*)dComIfG_getObjectRes(m_arcname, 0x11),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, NULL,
        0x80000, 0x11020022
    );
    if (mpMorf == NULL || mpMorf->getModel() == NULL) {
        return FALSE;
    }
    m_jnt.setHeadJntNum(modelData->getJointName()->getIndex("head"));
    JUT_ASSERT(0x223, m_jnt.getHeadJntNum() >= 0);
    m_jnt.setBackboneJntNum(modelData->getJointName()->getIndex("backbone2"));
    JUT_ASSERT(0x228, m_jnt.getBackboneJntNum() >= 0);
    if (!initTexPatternAnm(3, false)) {
        return FALSE;
    }
    initTexPatternAnm(0, true);
    mpItemModel = mDoExt_J3DModel__create((J3DModelData*)dComIfG_getObjectRes(m_arcname, 6), 0x80000, 0x11020022);
    if (mpItemModel == NULL) {
        return FALSE;
    }
    J3DAnmTexPattern* btp = (J3DAnmTexPattern*)dComIfG_getObjectRes(m_arcname, 0xA);
    if (!mItemBtp.init((J3DModelData*)dComIfG_getObjectRes(m_arcname, 6), btp, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0)) {
        return FALSE;
    }
    for (u16 jntNo = 0; jntNo < modelData->getJointNum(); jntNo++) {
        if (jntNo == m_jnt.getHeadJntNum() || jntNo == m_jnt.getBackboneJntNum() || jntNo == 8) {
            modelData->getJointNodePointer(jntNo)->setCallBack(daNpc_Kg1_nodeCallBack);
        }
    }
    mpMorf->getModel()->setUserArea((uintptr_t)this);
    mAcchCir.SetWall(30.0f, 30.0f);
    mObjAcch.Set(&current.pos, &old.pos, this, 1, &mAcchCir, &speed, &current.angle, &shape_angle);
    return TRUE;
}

/* 00000D34-00000EF0       .text CreateInit__11daNpc_Kg1_cFv */
cPhs_State daNpc_Kg1_c::CreateInit() {
    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);
    setCollision(60.0f, 150.0f);
    gravity = -9.0f;
    mEventCut.setActorInfo2("Kg1", this);
    set_mtx();
    mHeadTurnVel = 0;
    m730 = 0;
    m731 = 0;
    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    wait_action_init();
    if (l_HIO.mChildCount < 0) {
        l_HIO.mNo = mDoHIO_createChild("\x8a\x43\x90\xed\x83\x51\x81\x5b\x83\x80\x89\xae", &l_HIO);
    }
    l_HIO.mChildCount++;
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    m784 = dComIfGp_evmng_getEventIdx("MINIGAME_START");
    m786 = dComIfGp_evmng_getEventIdx("MINIGAME_END");
    m788 = dComIfGp_evmng_getEventIdx("KAISEN_GETITEM");
    mOldAnmPrmIdx = 0;
    mAnmPrmIdx = 2;
    setAnm();
    m_jnt.onHeadLock();
    m_jnt.onBackBoneLock();
    m750 = 1;
    m734 = current.pos;
    return cPhs_COMPLEATE_e;
}

/* 00000EF0-00000FE8       .text eventOrder__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::eventOrder() {
    switch (m732) {
    case 1:
    case 2:
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (m732 == 2) {
            fopAcM_orderSpeakEvent(this);
        }
        break;
    case 3:
        fopAcM_orderOtherEventId(this, m784, 0xFF, 0xFFFF, 0, 1);
        eventInfo.onCondition(dEvtCnd_UNK2_e);
        break;
    case 4:
        fopAcM_orderOtherEventId(this, m786, 0xFF, 0xFFFF, 0, 1);
        eventInfo.onCondition(dEvtCnd_UNK2_e);
        break;
    case 5:
        fopAcM_orderOtherEventId(this, m788, 0xFF, 0xFFFF, 0, 1);
        eventInfo.onCondition(dEvtCnd_UNK2_e);
        break;
    }
}

/* 00000FE8-000010C4       .text checkOrder__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::checkOrder() {
    switch (eventInfo.getCommand()) {
    case dEvtCmd_INDEMO_e:
        if (dComIfGp_evmng_startCheck(m784) && m732 == 3) {
            m732 = 0;
        }
        if (dComIfGp_evmng_endCheck(m784)) {
            m732 = 0;
        }
        if (dComIfGp_evmng_startCheck(m788) && m732 == 5) {
            m732 = 0;
        }
        break;
    case dEvtCmd_INTALK_e:
        if (m732 == 2 || m732 == 1) {
            m730 = 1;
        }
        break;
    }
}

/* 000010C4-00001188       .text kg1_talk_camera__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::kg1_talk_camera() {
    camera_process_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    if (m751 && camera != NULL) {
        camera->mCamera.Stay();
        camera->mCamera.Set(m_camera_ctr, m_camera_eye, m_camera_fovy, 0);
        camera->mCamera.Reset();
        camera->mCamera.SetTrimSize(1);
    }
}

/* 00001188-000011D4       .text wait_action_init__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::wait_action_init() {
    clr_seq_flag();
    setAction(&daNpc_Kg1_c::wait_action);
}

/* 000011D4-00001858       .text wait_action__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::wait_action() {
    int staffIdx = dComIfGp_evmng_getMyStaffId("Kg1");
    daMgBoard_c* board = (daMgBoard_c*)fopAcM_SearchByName(fpcNm_MGBOARD_e);
    switch (mWaitMode) {
    case 0:
        m751 = 0;
        m_jnt.onHeadLock();
        m_jnt.onBackBoneLock();
        if (board != NULL) {
            board->clrGInfoDraw();
        }
        clr_seq_flag();
        if (m731) {
            m732 = 1;
        } else {
            m732 = 0;
        }
        if (!m730) {
            break;
        }
        mWaitMode = 1;
        mItemBtp.setFrame(0.0f);
    case 1: {
        u16 status = talk(1);
        if (mCurrMsgNo < 0x1D56 && mAnmPrmIdx == 4) {
            m_jnt.offHeadLock();
        } else {
            m_jnt.onHeadLock();
        }
        if (mCurrMsgNo == 0x1D5B) {
            m750 = 0;
        } else if ((mCurrMsgNo == 0x1D5C && status == fopMsgStts_MSG_DISPLAYED_e) || (mCurrMsgNo == 0x1D57 && status == fopMsgStts_MSG_DISPLAYED_e)) {
            m750 = 1;
        }
        if (status == fopMsgStts_BOX_CLOSED_e) {
            dComIfGp_event_reset();
            if (m772) {
                m732 = 3;
                mWaitMode = 2;
                m751 = 0;
            } else {
                mAnmPrmIdx = 2;
                mWaitMode = 0;
            }
            m730 = 0;
        }
        break;
    }
    case 2:
        m751 = 0;
        if (board != NULL) {
            board->reqStartGame();
            board->setGInfoDraw();
        }
        mWaitMode = 3;
        mDoAud_seStart(0x8A8, &eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        mEndGameTimer = 60;
        break;
    case 3:
        if (m732 == 0 && board != NULL) {
            mbGameEnd = board->checkEndGame();
            if (mbGameEnd && cLib_calcTimer(&mEndGameTimer) == 0) {
                mbDidClearGame = board->checkClearGame();
                if (mbDidClearGame) {
                    mGameBoardScore = board->getScore();
                } else {
                    mAnmPrmIdx = 4;
                }
                mEndGameTimer = 90;
                m778 = 0;
                mWaitMode = 4;
                dComIfGp_event_offHindFlag(2);
                m779 = 1;
            }
        }
        break;
    case 4:
        if (CPad_CHECK_TRIG_A(0)) {
            m779 = 0;
            dComIfGs_onEventBit(0x2540);
            if (board != NULL) {
                board->mbForceEnd = 1;
            }
            if (board != NULL) {
                board->clrGInfoDraw();
            }
            mWaitMode = 5;
            m732 = 2;
            dComIfGp_evmng_cutEnd(staffIdx);
            dComIfGp_event_reset();
        }
        break;
    case 5:
        if (m730 == 1) {
            m751 = 1;
            if (talk(1) == fopMsgStts_BOX_CLOSED_e) {
                m732 = 0;
                dComIfGp_event_reset();
                m730 = 0;
                if (mbDidClearGame) {
                    m732 = 5;
                    mWaitMode = 6;
                } else if (m772) {
                    m732 = 3;
                    mWaitMode = 2;
                } else {
                    mAnmPrmIdx = 2;
                    mWaitMode = 0;
                }
            }
        }
        break;
    case 6:
        if (m732 == 0) {
            m751 = 0;
            u8 itemTbl[] = {0x07, 0xCC, 0x05};
            u8 idx = dComIfGs_getEventReg(0xFE07) - 1;
            mItemId = fopAcM_createItemForPresentDemo(&current.pos, itemTbl[idx], 0, -1, current.roomNo);
            if (mItemId != fpcM_ERROR_PROCESS_ID_e) {
                dComIfGp_event_setItemPartnerId(mItemId);
            }
            mWaitMode = 7;
        }
        break;
    case 7:
        if (dComIfGp_evmng_endCheck(m788)) {
            dComIfGp_event_reset();
            m775 = 1;
            m732 = 2;
            mWaitMode = 8;
            mAnmPrmIdx = 11;
        }
        break;
    case 8:
        m_jnt.onBackBoneLock();
        m_jnt.onHeadLock();
        if (m730 == 1) {
            m751 = 1;
            if (talk(1) == fopMsgStts_BOX_CLOSED_e) {
                dComIfGp_event_reset();
                m730 = 0;
                m732 = 0;
                if (m777) {
                    m732 = 5;
                    mWaitMode = 9;
                } else {
                    mAnmPrmIdx = 2;
                    mWaitMode = 0;
                }
            }
        }
        break;
    case 9:
        if (m732 == 0) {
            m751 = 0;
            u8 itemTbl[] = {0xF1, 0x06};
            u8 idx = dComIfGs_getEventReg(0xFF07) - 1;
            if (idx > 1) {
                idx = 1;
            }
            mItemId = fopAcM_createItemForPresentDemo(&current.pos, itemTbl[idx], 0, -1, current.roomNo);
            if (mItemId != fpcM_ERROR_PROCESS_ID_e) {
                dComIfGp_event_setItemPartnerId(mItemId);
            }
            mWaitMode = 10;
        }
        break;
    case 10:
        if (dComIfGp_evmng_endCheck(m788)) {
            dComIfGp_event_reset();
            m776 = 1;
            m732 = 2;
            mWaitMode = 11;
        }
        break;
    case 11:
        if (m730 == 1) {
            m751 = 1;
            if (talk(1) == fopMsgStts_BOX_CLOSED_e) {
                dComIfGp_event_reset();
                m732 = 0;
                m730 = 0;
                mWaitMode = 0;
                mAnmPrmIdx = 2;
            }
        }
        break;
    }
    kg1_talk_camera();
}

/* 00001858-00001878       .text clr_seq_flag__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::clr_seq_flag() {
    m772 = 0;
    mbDidClearGame = 0;
    mbGameEnd = 0;
    m775 = 0;
    m776 = 0;
    m777 = 0;
}

/* 00001878-000019B4       .text getMsg__11daNpc_Kg1_cFv */
u32 daNpc_Kg1_c::getMsg() {
    if (mbGameEnd) {
        if (mbDidClearGame) {
            if (m775 && !m776) {
                if (dComIfGs_getEventReg(0xBEFF) > mGameBoardScore) {
                    dComIfGs_onEventBit(0x0E04);
                    dComIfGs_setEventReg(0xBEFF, mGameBoardScore);
                    u8 reg = dComIfGs_getEventReg(0xFF07);
                    if (reg < 3) {
                        dComIfGs_setEventReg(0xFF07, reg + 1);
                    }
                    m777 = 1;
                    return 0x1D63;
                }
                return 0x1D64;
            }
            if (m775 && m776) {
                return 0x1D64;
            }
            return 0x1D5F;
        }
        return 0x1D5D;
    }
    if (m770 == 0) {
        return 0x1D4D;
    }
    return 0x1D4E;
}

/* 000019B4-00001C7C       .text next_msgStatus__11daNpc_Kg1_cFPUl */
u16 daNpc_Kg1_c::next_msgStatus(u32* pMsgNo) {
    u16 ret = fopMsgStts_MSG_CONTINUES_e;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    switch (*pMsgNo) {
    case 0x1D4D:
        if (!dComIfGs_isEventBit(0x0E04)) {
            *pMsgNo = 0x1D52;
        } else if (dLib_getIplDaysFromSaveTime() < 4) {
            *pMsgNo = 0x1D4F;
        } else if (dComIfGs_isTmpBit(0x0101)) {
            *pMsgNo = 0x1D50;
        } else {
            dComIfGs_onTmpBit(0x0101);
            *pMsgNo = 0x1D51;
        }
        m770 = 1;
        break;
    case 0x1D4E:
    case 0x1D4F:
    case 0x1D50:
    case 0x1D51:
        *pMsgNo = 0x1D52;
        break;
    case 0x1D52:
    case 0x1D5E:
        clr_seq_flag();
        switch (mpCurrMsg->mSelectNum) {
        case 0:
            if (dComIfGs_getRupee() < 10) {
                *pMsgNo = 0x1D54;
            } else {
                mAnmPrmIdx = 1;
                dComIfGp_setItemRupeeCount(-10);
                m751 = 1;
                m_jnt.onHeadLock();
                cXyz pos(0.0f, 0.0f, 250.0f);
                player->setPlayerPosAndAngle(&pos, 0x2000);
                *pMsgNo = 0x1D55;
            }
            break;
        case 1:
            *pMsgNo = 0x1D53;
            break;
        }
        break;
    case 0x1D55:
        if (m771 == 0) {
            *pMsgNo = 0x1D56;
        } else {
            *pMsgNo = 0x1D5C;
        }
        m772 = 1;
        break;
    case 0x1D56:
    case 0x1D57:
    case 0x1D58:
    case 0x1D59:
    case 0x1D5D:
        (*pMsgNo)++;
        break;
    case 0x1D5A:
        switch (mpCurrMsg->mSelectNum) {
        case 0:
            *pMsgNo = 0x1D5C;
            break;
        case 1:
            *pMsgNo = 0x1D5B;
            break;
        }
        break;
    case 0x1D5B:
        *pMsgNo = 0x1D57;
        break;
    case 0x1D5F: {
        u8 reg = dComIfGs_getEventReg(0xFE07);
        switch (reg) {
        case 0:
            *pMsgNo = 0x1D60;
            break;
        case 1:
            *pMsgNo = 0x1D61;
            break;
        default:
            *pMsgNo = 0x1D62;
            break;
        }
        if (reg < 3) {
            reg++;
        }
        dComIfGs_setEventReg(0xFE07, reg);
        break;
    }
    case 0x1D5C:
        m771 = 1;
        ret = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x1D53:
    case 0x1D54:
    default:
        ret = fopMsgStts_MSG_ENDS_e;
        break;
    }
    return ret;
}

/* 00001C7C-00001CB8       .text anmAtr__11daNpc_Kg1_cFUs */
void daNpc_Kg1_c::anmAtr(u16 param_1) {
    static const u8 anm_atr[] = {1, 2, 4, 5, 6, 7, 8, 9, 10};
    if (param_1 == 6 && dComIfGp_getMesgAnimeAttrInfo() < 9) {
        mAnmPrmIdx = anm_atr[dComIfGp_getMesgAnimeAttrInfo()];
        dComIfGp_clearMesgAnimeAttrInfo();
    }
}

/* 00001CB8-00001E60       .text daNpc_Kg1_bcks_setAnm__FPCcP14mDoExt_McaMorfPScPScPScPCiPC14dLib_anm_prm_c */
static void daNpc_Kg1_bcks_setAnm(const char* arcName, mDoExt_McaMorf* morf, s8* pAnmIdx, s8* pPrmIdx, s8* pOldPrmIdx, const int* bcksTbl, const dLib_anm_prm_c* anmPrmTbl) {
    if (*pOldPrmIdx != *pPrmIdx) {
        s8 anmIdx = anmPrmTbl[*pPrmIdx].mAnmIdx;
        if (anmIdx != -1) {
            *pAnmIdx = anmIdx;
            const dLib_anm_prm_c* prm = &anmPrmTbl[*pPrmIdx];
            morf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes(arcName, bcksTbl[*pAnmIdx]), prm->mLoopMode, prm->mMorf, prm->mPlaySpeed, 0.0f, -1.0f, NULL);
            if (anmPrmTbl[*pPrmIdx].mPlaySpeed < 0.0f) {
                morf->setFrame((s16)morf->getEndFrame());
            }
        }
    }
    *pOldPrmIdx = *pPrmIdx;
    if (morf->isStop()) {
        const dLib_anm_prm_c* prm = &anmPrmTbl[*pPrmIdx];
        if (prm->mNextPrmIdx != -1 && prm->mLoopMode == J3DFrameCtrl::EMode_NONE) {
            *pPrmIdx = prm->mNextPrmIdx;
        }
    }
}

/* 00001E60-00001F8C       .text setAnm__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::setAnm() {
    static const int a_anm_bck_tbl[] = {0x11, 0x1A, 0x16, 0x19, 0x14, 0x12, 0x13, 0x15, 0x17, 0x18};
    static const s16 a_anm_btp_tbl[] = {0, 0, 0, 0, 1, 0, 1, 1, 2, 3, 0, 0};
    dLib_anm_prm_c a_anm_prm_tbl[] = {
        {-1, -1, 0, 0.0f, 0.0f, J3DFrameCtrl::EMode_NONE},
        {0, -1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {1, -1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {2, -1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {3, -1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {4, 3, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {5, -1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {6, -1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {7, -1, 0, 6.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {8, -1, 0, 6.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {9, 8, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {4, 3, 0, 8.0f, -1.0f, J3DFrameCtrl::EMode_NONE},
    };

    if (mAnmPrmIdx != mOldAnmPrmIdx) {
        initTexPatternAnm(a_anm_btp_tbl[mAnmPrmIdx], true);
    }
    if (mBckIdx == 4 || mBckIdx == 2 || mBckIdx == 5 || mBckIdx == 6 || mBckIdx == 7 || mBckIdx == 8 || mBckIdx == 9) {
        m74F = 1;
        if (mBckIdx == 9 && 31.0f == mpMorf->getFrame()) {
            mItemBtp.setFrame(1.0f);
        }
    } else {
        m74F = 0;
    }
    daNpc_Kg1_bcks_setAnm(m_arcname, mpMorf, &mBckIdx, &mAnmPrmIdx, &mOldAnmPrmIdx, a_anm_bck_tbl, a_anm_prm_tbl);
}

/* 00001F8C-00001FAC       .text daNpc_Kg1Create__FPv */
static cPhs_State daNpc_Kg1Create(void* i_this) {
    return ((daNpc_Kg1_c*)i_this)->_create();
}

/* 00001FAC-0000203C       .text _create__11daNpc_Kg1_cFv */
cPhs_State daNpc_Kg1_c::_create() {
    fopAcM_ct(this, daNpc_Kg1_c);
    cPhs_State ret = dComIfG_resLoad(&mPhs, m_arcname);
    if (ret == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x10000)) {
            return CreateInit();
        }
        return cPhs_ERROR_e;
    }
    return ret;
}

/* 00002480-0000250C       .text daNpc_Kg1Delete__FPv */
static BOOL daNpc_Kg1Delete(void* i_this) {
    daNpc_Kg1_c* a_this = (daNpc_Kg1_c*)i_this;
    dComIfG_resDelete(&a_this->mPhs, daNpc_Kg1_c::m_arcname);
    if (a_this->heap != NULL && a_this->mpMorf != NULL) {
        a_this->mpMorf->stopZelAnime();
    }
    if (l_HIO.mChildCount >= 0) {
        if (--l_HIO.mChildCount < 0) {
            mDoHIO_deleteChild(l_HIO.mNo);
        }
    }
    return TRUE;
}

/* 0000250C-00002648       .text daNpc_Kg1Execute__FPv */
static BOOL daNpc_Kg1Execute(void* i_this) {
    daNpc_Kg1_c* a_this = (daNpc_Kg1_c*)i_this;
    a_this->m_jnt.setParam(
        l_HIO.mNpc[0].mMaxBackboneX, l_HIO.mNpc[0].mMaxBackboneY,
        l_HIO.mNpc[0].mMinBackboneX, l_HIO.mNpc[0].mMinBackboneY,
        l_HIO.mNpc[0].mMaxHeadX, l_HIO.mNpc[0].mMaxHeadY,
        l_HIO.mNpc[0].mMinHeadX, l_HIO.mNpc[0].mMinHeadY,
        l_HIO.mNpc[0].mMaxTurnStep
    );
    a_this->checkOrder();
    (a_this->*(a_this->mAction))();
    a_this->eventOrder();
    a_this->playTexPatternAnm();
    a_this->setAnm();
    if (a_this->m750) {
        a_this->mpMorf->play(NULL, 0, 0);
    }
    a_this->mObjAcch.CrrPos(*dComIfG_Bgsp());
    a_this->setCollision(60.0f, 150.0f);
    a_this->attention_info.position.x = a_this->current.pos.x;
    a_this->attention_info.position.y = 190.0f + a_this->current.pos.y;
    a_this->attention_info.position.z = a_this->current.pos.z;
    a_this->eyePos.x = a_this->current.pos.x;
    a_this->eyePos.y = 150.0f + a_this->current.pos.y;
    a_this->eyePos.z = a_this->current.pos.z;
    a_this->lookBack();
    a_this->set_mtx();
    return FALSE;
}

/* 00002648-000027CC       .text daNpc_Kg1Draw__FPv */
static BOOL daNpc_Kg1Draw(void* i_this) {
    daNpc_Kg1_c* a_this = (daNpc_Kg1_c*)i_this;
    dSnap_RegistFig(0x81, a_this, 1.0f, 1.0f, 1.0f);
    J3DModelData* modelData = a_this->mpMorf->getModel()->getModelData();
    dKy_tevstr_c* tevStr = &a_this->tevStr;
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &a_this->current.pos, tevStr);
    g_env_light.setLightTevColorType(a_this->mpMorf->getModel(), tevStr);
    g_env_light.setLightTevColorType(a_this->mpItemModel, tevStr);
    a_this->mEyeBtp.entry(modelData, a_this->mEyeFrame);
    a_this->mpMorf->updateDL();
    modelData->getMaterialTable().removeTexNoAnimator(a_this->m_eye_tex_pattern);
    if (a_this->m74F) {
        a_this->mItemBtp.entry(a_this->mpItemModel->getModelData(), a_this->mItemBtp.getFrame());
        mDoExt_modelUpdateDL(a_this->mpItemModel);
    }
    cXyz shadowPos(a_this->current.pos.x, 150.0f + a_this->current.pos.y, a_this->current.pos.z);
    a_this->mShadowId = dComIfGd_setShadow(
        a_this->mShadowId, 1, a_this->mpMorf->getModel(), &shadowPos, 800.0f, 20.0f,
        a_this->current.pos.y, a_this->mObjAcch.GetGroundH(), a_this->mObjAcch.m_gnd, tevStr,
        0, 1.0f, dDlst_shadowControl_c::getSimpleTex()
    );
    if (a_this->m779) {
        dComIfGp_setDoStatus(0x19);
    }
    return TRUE;
}

/* 000027CC-000027D4       .text daNpc_Kg1IsDelete__FPv */
static BOOL daNpc_Kg1IsDelete(void*) {
    return TRUE;
}

static actor_method_class daNpc_Kg1MethodTable = {
    (process_method_func)daNpc_Kg1Create,
    (process_method_func)daNpc_Kg1Delete,
    (process_method_func)daNpc_Kg1Execute,
    (process_method_func)daNpc_Kg1IsDelete,
    (process_method_func)daNpc_Kg1Draw,
};

actor_process_profile_definition g_profile_NPC_KG1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_KG1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Kg1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_KG1_e,
    /* Actor SubMtd */ &daNpc_Kg1MethodTable,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_0_e,
};
