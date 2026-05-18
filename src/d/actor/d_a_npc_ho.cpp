/**
 * d_a_npc_ho.cpp
 * NPC - Mrs. Marie (Windfall Island teacher)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_ho.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/res/res_ho.h"
#include "d/d_snap.h"
#include "m_Do/m_Do_controller_pad.h"

static fpc_ProcID l_msgId;
static msg_class* l_msg;

static const int l_bck_ix_tbl[] = {
    HO_BCK_HO_WAIT01,
    HO_BCK_HO_TALK01,
    HO_BCK_HO_TALK02,
    HO_BCK_HO_GLAD,
    HO_BCK_HO_TALK02,
};

static const int l_btp_ix_tbl[] = {
    HO_BTP_HO_MABA01
};

/* 00000078-0000022C       .text nodeCallBack_Ho__FP7J3DNodei */
static BOOL nodeCallBack_Ho(J3DNode* node, int calcTiming) {
    cXyz temp;
    cXyz temp2;
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daNpc_Ho_c* i_this = (daNpc_Ho_c*)model->getUserArea();
        J3DJoint* joint = (J3DJoint*)node;
        int jntNo = joint->getJntNo();

        if(i_this != NULL) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            if (jntNo == i_this->getHeadJntNum()) {
                temp.setall(0.0f);
                cMtx_YrotM(*calc_mtx, -i_this->getHead_y());
                cMtx_ZrotM(*calc_mtx, -i_this->getHead_x());
                MtxPosition(&temp, &temp2);
                i_this->setAttentionBasePos(temp2);
                temp.set(20.0f, -20.0f, 0.0f);

                MtxPosition(&temp, &temp2);
                i_this->setEyePos(temp2);
                i_this->incAttnSetCount();

            } else if (jntNo == i_this->getBackboneJntNum()) {
                mDoMtx_XrotM(*calc_mtx, i_this->getBackbone_y());
            }
            cMtx_copy(*calc_mtx, J3DSys::mCurrentMtx);
            model->setAnmMtx(jntNo, *calc_mtx);
        }
    }
    return TRUE;
}

/* 0000022C-0000024C       .text daNpc_ho_XyCheckCB__FPvi */
static s16 daNpc_ho_XyCheckCB(void* i_this, int i_itemBtn) {
    return ((daNpc_Ho_c*)i_this)->XyCheckCB(i_itemBtn);
}

/* 0000024C-00000254       .text XyChedaNpc_Ho_c::XyCheckCBckCB__10daNpc_Ho_cFi */
s16 daNpc_Ho_c::XyCheckCB(int) {
    return 1;
}

/* 00000254-000002F8       .text receivePendant__10daNpc_Ho_cFi */
void daNpc_Ho_c::receivePendant(int numPendantsGiven) {
    int totalGiven = dComIfGs_getEventReg(dSv_event_flag_c::UNK_C0FF);
    dComIfGp_setItemBeastNumCount(7, -numPendantsGiven);
    totalGiven += numPendantsGiven;

    if(totalGiven > 99) {
#if VERSION > VERSION_DEMO
        dComIfGp_setItemBeastNumCount(7, totalGiven - 99);
#endif
        totalGiven = 99;
    }
    dComIfGs_setEventReg(dSv_event_flag_c::UNK_C0FF, totalGiven);
}

/* 000002F8-0000040C       .text initTexPatternAnm__10daNpc_Ho_cFb */
BOOL daNpc_Ho_c::initTexPatternAnm(bool i_modify) {
    J3DModelData* modelData = mpMorf->getModel()->getModelData();

    m_head_tex_pattern = (J3DAnmTexPattern*)dComIfG_getObjectRes("Ho", l_btp_ix_tbl[mTexPatternIdx]);
    JUT_ASSERT(DEMO_SELECT(317, 320), m_head_tex_pattern != NULL);

    if (!mBtpAnm.init(modelData, m_head_tex_pattern, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, i_modify, FALSE)) {
        return FALSE;
    }

    mBlinkFrame = 0;
    mBlinkTimer = 0;
    return TRUE;
}

/* 0000040C-00000498       .text playTexPatternAnm__10daNpc_Ho_cFv */
void daNpc_Ho_c::playTexPatternAnm() {
    if (cLib_calcTimer(&mBlinkTimer) == 0) {
        if (mBlinkFrame >= m_head_tex_pattern->getFrameMax()) {
            mBlinkFrame -= m_head_tex_pattern->getFrameMax();
            mBlinkTimer = cM_rndF(100.0f) + 30.0f;
        } else {
            mBlinkFrame++;
        }
    }
}

/* 00000498-0000051C       .text setAnm__10daNpc_Ho_cFSc */
void daNpc_Ho_c::setAnm(s8 newAnmIdx) {
    f32 morf = 8.0f;
    if (newAnmIdx != mCurrAnmIdx && newAnmIdx != -1) {
        mCurrAnmIdx = newAnmIdx;
        mAnmTimer = 0.0f;
        dNpc_setAnm(mpMorf, J3DFrameCtrl::EMode_NULL, morf, 1.0f, l_bck_ix_tbl[mCurrAnmIdx], -1, "Ho");
    }
}

/* 0000051C-00000540       .text setAnmStatus__10daNpc_Ho_cFv */
void daNpc_Ho_c::setAnmStatus() {
    setAnm(0);
}

/* 00000540-000005F4       .text chkAttentionLocal__10daNpc_Ho_cFv */
bool daNpc_Ho_c::chkAttentionLocal() {
    dAttention_c& attention = dComIfGp_getAttention();

    if (chkFlag(HO_FLAG_00000001 | HO_FLAG_00000010)) {
        return true;
    }

    if (mAttentionTimer != 0) {
        mAttentionTimer--;
        return true;
    }

    if(attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    }

    return this == attention.ActionTarget(0);
}

/* 000005F4-00000690       .text chkAttention__10daNpc_Ho_cFv */
void daNpc_Ho_c::chkAttention() {
    bool temp = chkFlag(HO_FLAG_00000004);

    if(chkAttentionLocal()) {
        setFlag(HO_FLAG_00000004);
    } else {
        clrFlag(HO_FLAG_00000004);
    }

    if(temp != chkFlag(HO_FLAG_00000004) && temp == true) {
        m_jnt.setTrn();
    }
}

/* 00000690-00000708       .text eventOrder__10daNpc_Ho_cFv */
void daNpc_Ho_c::eventOrder() {
    if (ChkOrder(1)) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
    }
    if (ChkOrder(2)) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        fopAcM_orderSpeakEvent(this);
    }
    if (ChkOrder(4)) {
        eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
    }
}

/* 00000708-000007A8       .text checkOrder__10daNpc_Ho_cFv */
void daNpc_Ho_c::checkOrder() {
    if (eventInfo.mCommand == dEvtCmd_INTALK_e && ChkOrder(7)) {
        if (dComIfGp_event_chkTalkXY()) {
            setFlag(HO_FLAG_00000010);
        } else {
            setFlag(HO_FLAG_00000001);
        }
        talkInit();
    }
    ClrOrder();
}

/* 000007A8-00000884       .text next_msg_sub0__10daNpc_Ho_cFUl */
u32 daNpc_Ho_c::next_msg_sub0(u32 msgNo) {
    switch(mMsgSelectNum) {
        case 0:
            if(msgNo == 0x2712) {
                if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_2201)) {
                    if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_1340)) {
                        if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_1F80)) {
                            return 0x2720;
                        }

                        dComIfGs_onEventBit(dSv_event_flag_c::UNK_1F80);
#if VERSION > VERSION_DEMO
                        if(!dKy_daynight_check()) {
                            dComIfGs_onTmpBit(dSv_event_tmp_flag_c::UNK_0580);
                        }
#else
                        dComIfGs_onTmpBit(dSv_event_tmp_flag_c::UNK_0580);
#endif
                        return 0x271E;
                    } 
                    return 0x271D;
                }
                return 0x2716;
            }
            return 0x272B;
        default:
            return 0x2714;
    }
}

/* 00000884-00000C0C       .text next_msgStatus__10daNpc_Ho_cFPUl */
u16 daNpc_Ho_c::next_msgStatus(u32* pMsgNo) {
    u16 msgStatus = fopMsgStts_MSG_CONTINUES_e;
    switch (*pMsgNo) {
        case 0x2712:
        case 0x2713:
            *pMsgNo = next_msg_sub0(*pMsgNo);
            break;
        case 0x2718:
            switch(mMsgSelectNum) {
                case 0:
                    *pMsgNo = 0x271A;
                    dComIfGs_onEventBit(dSv_event_flag_c::UNK_1380);
                    break;
                default:
                    *pMsgNo = 0x2719;
                    break;
            }
            break;
        case 0x271E:
            mNextMessageId = 0x2748;
            mItemNum = dItem_PURPLE_RUPEE_e;
            *pMsgNo = *pMsgNo + 1;
            mState = HO_STATE_TALK_03;
            break;
        case 0x272B:
            switch(mMsgSelectNum) {
                case 0:
                    *pMsgNo = 0x272C;
                    break;
                case 1:
                    *pMsgNo = 0x272E;
                    break;
                default:
                    *pMsgNo = 0x2732;
                    break;
            }
            break;
        case 0x2732:
            *pMsgNo = 0x2736;
            break;
        case 0x272C:
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1C04)) {
                *pMsgNo = 0x2758;
            } else if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1C08)) {
                *pMsgNo = 0x2759;
            } else {
                *pMsgNo = 0x272D;
            }
            break;
        case 0x2725:
            setFlag(HO_FLAG_00000020);
            mNextMessageId = 0x2726;
            msgStatus = fopMsgStts_MSG_ENDS_e;
            break;
        case 0x2716:
        case 0x2717:
        case 0x271A:
        case 0x271B:
        case 0x2720:
        case 0x2724:
        case 0x2726:
        case 0x2727:
        case 0x2728:
        case 0x272E:
        case 0x272F:
        case 0x2730:
        case 0x2736:
        case 0x2737:
            *pMsgNo += 1;
            break;
        case 0x273D:
            *pMsgNo = 0x275B;
            receivePendant(1);
            break;
        case 0x273E:
            if (dComIfGs_getBeastNum(7) >= 0x14) {
                *pMsgNo = 0x2741;
            } else {
                *pMsgNo = 0x273F;
            }
            break;
        case 0x2749:
            *pMsgNo = 0x273E;
            break;
        case 0x275C:
            mNextMessageId = 0x275D;
            mItemNum = dItem_RED_RUPEE_e;
            msgStatus = fopMsgStts_MSG_ENDS_e;
            break;
        case 0x2742:
            *pMsgNo = 0x2743;
            receivePendant(0x14);
            break;
        case 0x2743:
            mNextMessageId = 0x2744;
            mItemNum = COTTAGE_PAPER;
            msgStatus = fopMsgStts_MSG_ENDS_e;
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_1C08);
            dComIfGs_onTmpBit(dSv_event_tmp_flag_c::UNK_0104);
            break;
        case 0x274B:
            *pMsgNo = 0x274D;
            break;
        case 0x274D:
            *pMsgNo = 0x274E;
            receivePendant(dComIfGs_getBeastNum(7));
            break;
        case 0x274E:
            if (dComIfGs_getEventReg(dSv_event_flag_c::UNK_C0FF) >= 0x28 && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_1C04)) {
                *pMsgNo = 0x274F;
            } else {
                msgStatus = fopMsgStts_MSG_ENDS_e;
            }
            break;
        case 0x2754:
            *pMsgNo = 0x2755;
            int numPendantsGiven = dComIfGs_getBeastNum(7);
            receivePendant(numPendantsGiven);
            if (numPendantsGiven < 3) {
                mItemNum = dItem_RED_RUPEE_e;
            } else if (numPendantsGiven < 5) {
                mItemNum = dItem_PURPLE_RUPEE_e;
            } else {
                mItemNum = dItem_ORANGE_RUPEE_e;
            }
            mNextMessageId = 0x2757;
            break;
        case 0x2751:
            mNextMessageId = 0x2752;
            mItemNum = dItem_HEROS_CHARM_e;
            msgStatus = fopMsgStts_MSG_ENDS_e;
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_1C04);
            break;
        case 0x2756:
            msgStatus = fopMsgStts_MSG_ENDS_e;
            break;
        case 0x273A:
        case 0x274C:
            *pMsgNo += 1;
            break;
        case 0x273B:
        case 0x273C:
        case 0x273F:
        case 0x2741:
        case 0x2744:
        case 0x2745:
        case 0x2746:
        case 0x2747:
        case 0x274A:
        case 0x274F:
        case 0x2750:
        case 0x2752:
        case 0x2755:
        case 0x275B:
            *pMsgNo += 1;
            break;
        default:
            msgStatus = fopMsgStts_MSG_ENDS_e;
            break;
    }
    return msgStatus;
}

/* 00000C0C-00000DA8       .text getMsg__10daNpc_Ho_cFv */
u32 daNpc_Ho_c::getMsg() {
    switch(mState) {
        case HO_STATE_TALK_01:
            if (dKy_checkEventNightStop()) {
                return 0x2722;
            }

            if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_1E01)) {
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_1E01);
                return 0x2711;
            }

            return (dComIfGs_getEventReg(dSv_event_flag_c::UNK_C0FF) == 0 ? 0 : 1) + 0x2712;

        case HO_STATE_TALK_03:
            if(dComIfGp_event_getPreItemNo() != dItem_JOY_PENDANT_e || !dComIfGs_isEventBit(DEMO_SELECT(dSv_event_flag_c::UNK_1E02, dSv_event_flag_c::UNK_1E04))) {
                return 0x2739;
            } 

            if (dComIfGs_getEventReg(dSv_event_flag_c::UNK_C0FF) == 0) {
                return 0x273A;
            }
            
            if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_1C08)) {
                return 0x2749;
            }
            
            if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_1C04)) {
                if(dComIfGs_isTmpBit(dSv_event_tmp_flag_c::UNK_0104)) {
                    return 0x274A;
                }
                return 0x274C;
            } 

            if(dComIfGs_getEventReg(dSv_event_flag_c::UNK_C0FF) >= 0x63) {
                return 0x275E;
            }
            return 0x2754;
                
        case HO_STATE_TALK_03_CONTINUE: 
            return mNextMessageId;
    }
    return 0;
}

/* 00000DA8-00000E4C       .text setCollision__10daNpc_Ho_cFv */
void daNpc_Ho_c::setCollision() {
    cXyz temp(0.0f, 0.0f, 0.0f); // unused
    
    cXyz centerPos(current.pos);
    f32 cylCollision = mCylCollisionRadius;
    f32 height = 140.0f;
    mCyl.SetC(centerPos);
    mCyl.SetR(cylCollision);
    mCyl.SetH(height);
    dComIfG_Ccsp()->Set(&mCyl);
}

/* 00000E4C-00000E90       .text msgPushButton__10daNpc_Ho_cFv */
void daNpc_Ho_c::msgPushButton() {
    switch(mCurrMsgNo) {
        case 0x2712:
        case 0x2713:
        case 0x2718:
        case 0x272B:
            mMsgSelectNum = l_msg->mSelectNum;
            break;
    }
}

/* 00000E90-00000EF0       .text msgAnm__10daNpc_Ho_cFUc */
void daNpc_Ho_c::msgAnm(u8 param_1) {
    static s8 msg_anm_table[] = {
        0, 1, 2, 3, 4
    };

    if (mMsgAnmIdx != param_1) {
        mMsgAnmIdx = param_1;
        if (mMsgAnmIdx < 5) {
            setAnm(msg_anm_table[mMsgAnmIdx]);
        }
        mAnmLoopCount = 0;
    }
}

/* 00000EF0-00000F04       .text talkInit__10daNpc_Ho_cFv */
void daNpc_Ho_c::talkInit() {
    mTalkState = TALK_INIT;
    mMsgAnmIdx = 0xff;
}

/* 00000F04-000010EC       .text talk__10daNpc_Ho_cFv */
u16 daNpc_Ho_c::talk() {
    u16 msgStatus = 0xFF;
    if (mTalkState == TALK_INIT) {
        l_msgId = fpcM_ERROR_PROCESS_ID_e;
        mCurrMsgNo = getMsg();
        mTalkState = TALK_MSG_CREATE;
    } else if (mTalkState != TALK_FINISHED) {
        if(l_msgId == fpcM_ERROR_PROCESS_ID_e) {
            l_msgId = fopMsgM_messageSet(mCurrMsgNo, this);
        } else {
            if (!chkFlag(HO_FLAG_00000008)) {
                msgAnm(dComIfGp_getMesgAnimeAttrInfo());
            }
            switch(mTalkState) {
                case 1:
                    l_msg = fopMsgM_SearchByID(l_msgId);
                    if (l_msg != NULL) {
                        mTalkState = TALK_ACTIVE;
                    }
                    break;
                case 2:
                    msgStatus = l_msg->mStatus;
                    if (msgStatus == fopMsgStts_MSG_DISPLAYED_e) {
                        msgPushButton();
                        l_msg->mStatus = next_msgStatus(&mCurrMsgNo);
                        if(l_msg->mStatus == fopMsgStts_MSG_CONTINUES_e) {
                            fopMsgM_messageSet(mCurrMsgNo);
                        }
                    } else if (msgStatus == fopMsgStts_BOX_CLOSED_e) {
                        l_msg->mStatus = fopMsgStts_MSG_DESTROYED_e;
                        mTalkState = TALK_FINISHED;
                    }

                    if (msgStatus == fopMsgStts_MSG_CONTINUES_e && (CPad_CHECK_TRIG_A(0) || CPad_CHECK_TRIG_B(0))) {
                        switch (mCurrMsgNo) {
                        case 0x274D:
                        case 0x273E:
                        case 0x273B:
                        case 0x2755:
                            dComIfGp_evmng_CancelPresent();
                            break;
                        }
                    }
                    break;
            }
        }
    }
    return msgStatus;
}

/* 000010EC-000012B8       .text init__10daNpc_Ho_cFv */
BOOL daNpc_Ho_c::init() {
    attention_info.flags = fopAc_Attn_ACTION_SPEAK_e|fopAc_Attn_LOCKON_TALK_e;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0x6F;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0x6F;
    gravity = -30.0f;

    switch(mType) {
        case 0:
            if(setAction(&daNpc_Ho_c::wait_action, NULL)) {
                eventInfo.setXyCheckCB(daNpc_ho_XyCheckCB);
            }
            break;
    }

    mAttnBasePos.set(current.pos);
    mAttnBasePos.y += 100.0f;
    mEyePos.set(mAttnBasePos);
    eyePos.set(mEyePos);
    attention_info.position.set(mAttnBasePos.x, mAttnBasePos.y + 50.0f, mAttnBasePos.z);

    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(dNpc_cyl_src);
    mCyl.SetStts(&mStts);
    mCylCollisionRadius = 40.0f;
    mtrlSndId = 0;
    mReverb = dComIfGp_getReverb(fopAcM_GetRoomNo(this));
    return TRUE;
}

/* 000012B8-0000130C       .text setAttention__10daNpc_Ho_cFb */
void daNpc_Ho_c::setAttention(bool param_1) {
    if (!param_1 && mAttnSetCount >= 2) {
        return;
    }

    eyePos.set(mEyePos.x, mEyePos.y, mEyePos.z);
    attention_info.position.set(mAttnBasePos.x, mAttnBasePos.y + 90.0f, mAttnBasePos.z);
}

/* 0000130C-00001498       .text lookBack__10daNpc_Ho_cFv */
void daNpc_Ho_c::lookBack() {
    cXyz temp2;
    cXyz temp(0.0f, 0.0f, 0.0f);
    cXyz* dstPos = NULL;
    s16 desiredYRot = current.angle.y;
    bool headOnlyFollow = false;

    switch(mState) {
        case HO_STATE_WAIT_01:
            if (chkFlag(HO_FLAG_00000004)) {
                temp2 = dNpc_playerEyePos(-20.0f);
                dstPos = &temp2;
                temp.set(current.pos);
                temp.y = eyePos.y;
                headOnlyFollow = true;
            } else {
                desiredYRot = home.angle.y;
            }
            break;
        default:
            m_jnt.setTrn();
            temp2 = dNpc_playerEyePos(-20.0f);
            dstPos = &temp2;
            temp.set(current.pos);
            temp.y = eyePos.y;
            break;
    }

    if (m_jnt.trnChk()) {
        cLib_addCalcAngleS2(&mMaxHeadTurnVelocity, 0x5DC, 4, 0x800);
    } else {
        mMaxHeadTurnVelocity = 0;
    }

    m_jnt.lookAtTarget(&current.angle.y, dstPos, temp, desiredYRot, mMaxHeadTurnVelocity, headOnlyFollow);
    shape_angle.y = current.angle.y;
}

/* 00001498-0000157C       .text wait01__10daNpc_Ho_cFv */
bool daNpc_Ho_c::wait01() {
    if (chkFlag(HO_FLAG_00000010)) {
        mPrevState = mState;
        mState = HO_STATE_TALK_02;
        setAnmStatus();
        mItemNum = dItem_NONE_e;
    } else if (chkFlag(HO_FLAG_00000001)) {
        mPrevState = mState;
        mState = HO_STATE_TALK_01;
        setAnmStatus();
    } else {
        SetOrder(HO_FLAG_00000001);
        if (dComIfGs_isEventBit(DEMO_SELECT(dSv_event_flag_c::UNK_1E02, dSv_event_flag_c::UNK_1E04)) && !dKy_checkEventNightStop()) {
            SetOrder(HO_FLAG_00000004);
        }
    }
    return mpMorf->isMorf();
}

/* 0000157C-00001678       .text talk01__10daNpc_Ho_cFv */
bool daNpc_Ho_c::talk01() {
    if (talk() == fopMsgStts_BOX_CLOSED_e) {
        if (chkFlag(HO_FLAG_00000020)) {
            mState = HO_STATE_PREACH;
            fopAcM_orderChangeEvent(dComIfGp_getLinkPlayer(), this, "HO_PREACH", 0, 0xFFFF);
            clrFlag(HO_FLAG_00000020);

        } else {
            mState = mPrevState;
            setAnmStatus();
            dComIfGp_event_reset();
            clrFlag(HO_FLAG_00000001 | HO_FLAG_00000010);

            mAttentionTimer = 5;
            mCylCollisionRadius = 40.0f;
        }
    }
    return mpMorf->isMorf();
}

/* 00001678-000016E8       .text talk02__10daNpc_Ho_cFv */
bool daNpc_Ho_c::talk02() {
    if (dComIfGp_evmng_ChkPresentEnd()) {
        mState = HO_STATE_TALK_03;
    }
    if (mCylCollisionRadius < 90.0f) {
        mCylCollisionRadius += 5.0f;
    }
    return false;
}

/* 000016E8-000017D4       .text talk03__10daNpc_Ho_cFv */
bool daNpc_Ho_c::talk03() {
    if (talk() == fopMsgStts_BOX_CLOSED_e) {
        if (mItemNum != dItem_NONE_e) {
            mState = HO_STATE_GIVE_01;
            fopAcM_orderChangeEvent(dComIfGp_getLinkPlayer(), this, "DEFAULT_GIVEITEM", 0, 0xFFFF);
        } else {
            mState = mPrevState;
            setAnmStatus();
            dComIfGp_event_reset();
            clrFlag(HO_FLAG_00000001 | HO_FLAG_00000010);
            mAttentionTimer = 5;
            mCylCollisionRadius = 40.0f;
        }
    }

    return mpMorf->isMorf();
}

/* 000017D4-00001884       .text give01__10daNpc_Ho_cFv */
bool daNpc_Ho_c::give01() {
    if (dComIfGp_event_giveItemCut(mItemNum) != 0) {
        mState = HO_STATE_GIVE_02;
    } else {
        JUT_ASSERT(DEMO_SELECT(1220, 1233), NULL);
    }
    return mpMorf->isMorf();
}

/* 00001884-0000193C       .text give02__10daNpc_Ho_cFv */
bool daNpc_Ho_c::give02() {
    if (dComIfGp_evmng_endCheck("DEFAULT_GIVEITEM")) {
        fopAcM_orderChangeEvent(dComIfGp_getLinkPlayer(), this, "DEFAULT_TALK", 0, 0xFFFF);
        mState = HO_STATE_TALK_03_CONTINUE;
        mItemNum = dItem_NONE_e;
        talkInit();
    }
    return mpMorf->isMorf();
}

/* 0000193C-00001A00       .text preach__10daNpc_Ho_cFv */
bool daNpc_Ho_c::preach() {
    setFlag(HO_FLAG_00000004);

    if (dComIfGp_evmng_endCheck("HO_PREACH")) {
        fopAcM_orderChangeEvent(dComIfGp_getLinkPlayer(), this, "DEFAULT_TALK", 0, 0xFFFF);
        mItemNum = dItem_NONE_e;
        mState = HO_STATE_TALK_03_CONTINUE;
        talkInit();
    }
    return mpMorf->isMorf();
}

/* 00001A00-00001B2C       .text wait_action__10daNpc_Ho_cFPv */
BOOL daNpc_Ho_c::wait_action(void*) {
    if(mActionStatus == ACTION_STARTING) {
        mState = HO_STATE_WAIT_01;
        setAnmStatus();
        mActionStatus++; // set to ACTION_ONGOING
    } else if(mActionStatus != ACTION_ENDING) {
        chkAttention();
        bool temp;

        switch(mState) {
            case HO_STATE_WAIT_01:
                temp = wait01();
                break;
            case HO_STATE_TALK_01:
                temp = talk01();
                break;
            case HO_STATE_TALK_02:
                temp = talk02();
                break;
            case HO_STATE_TALK_03:
                temp = talk03();
                break;
            case HO_STATE_TALK_03_CONTINUE:
                temp = talk03();
                break;
            case HO_STATE_GIVE_01:
                temp = give01();
                break;
            case HO_STATE_GIVE_02:
                temp = give02();
                break;
            case HO_STATE_PREACH:
                temp = preach();
                break;
            default:
                temp = false;
                break;
        }
        lookBack();
        setAttention(temp);
    }
    return TRUE;
}

/* 00001B2C-00001C94       .text _draw__10daNpc_Ho_cFv */
BOOL daNpc_Ho_c::_draw() {
    J3DModel* pModel = mpMorf->getModel();
    J3DModelData* pModelData = pModel->getModelData();
    
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(pModel, &tevStr);
    g_env_light.setLightTevColorType(mpJoyPendentModel, &tevStr);
    mBtpAnm.entry(pModelData, mBlinkFrame);
    mpMorf->entry();
    mBtpAnm.remove(pModelData);
    mpJoyPendentModel->setBaseTRMtx(pModel->getAnmMtx(m_jnt.getBackboneJntNum()));
    if(dComIfGs_getEventReg(dSv_event_flag_c::UNK_C0FF) != 0) {
        mDoExt_modelUpdateDL(mpJoyPendentModel);
    }

    f32 _90 = 90.0f;
    f32 _420 = 420.0f;
    cXyz shadowPos(current.pos.x, current.pos.y + _90, current.pos.z);
    mShadowId = dComIfGd_setShadow(
        mShadowId, 1, pModel, &shadowPos, _420, 20.0f,
        current.pos.y, mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr
    );

    dSnap_RegistFig(DSNAP_TYPE_HO, this, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 00001C94-00001EB0       .text _execute__10daNpc_Ho_cFv */
BOOL daNpc_Ho_c::_execute() {
    m_jnt.setParam(
        /* mMaxBackboneX */ 200,
        /* mMaxBackboneY */ 0x9C4,
        /* mMinBackboneX */ -500,
        /* mMinBackboneY */ -0x9C4,
        /* mMaxHeadX */ 8000,
        /* mMaxHeadY */ 8000,
        /* mMinHeadX */ -0x9C4,
        /* mMinHeadY */ -8000,
        /* mMaxTurnStep */ 0x3E8
    );

    playTexPatternAnm();

    mAnmEnded = mpMorf->play(&eyePos, mtrlSndId, mReverb);
    if(mpMorf->getFrame() < mAnmTimer) {
        mAnmEnded = 1;
    }
    mAnmTimer = mpMorf->getFrame();
    if (mAnmEnded != 0) {
        switch(mCurrAnmIdx) {
            case 3:
                if (mAnmLoopCount < 2) {
                    mAnmLoopCount++;
                } else {
                    mAnmLoopCount = 0;
                    setAnm(2);
                }
                break;
            case 4:
                if (mAnmLoopCount < 2) {
                    mAnmLoopCount++;
                } else {
                    mAnmLoopCount = 0;
                    setAnm(0);
                }
                break;

        }
    }
    checkOrder();
    (this->*mCurrActionFunc)(NULL);
    eventOrder();
    shape_angle.y = current.angle.y;
    fopAcM_posMoveF(this, mStts.GetCCMoveP());
    mObjAcch.CrrPos(*dComIfG_Bgsp());
    mtrlSndId = 0;

    if (!mObjAcch.ChkGroundHit()) {
        mtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
    }

    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);

    J3DModel* pModel = mpMorf->getModel();
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    pModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    setCollision();
    return TRUE;
}

/* 00001EB0-00001EFC       .text _delete__10daNpc_Ho_cFv */
BOOL daNpc_Ho_c::_delete() {
    dComIfG_resDelete(&mPhs, "Ho");
    if (mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }
    return TRUE;
}

/* 00001EFC-00001F1C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Ho_c*)i_this)->CreateHeap();
}

/* 00001F1C-00002124       .text _create__10daNpc_Ho_cFv */
cPhs_State daNpc_Ho_c::_create() {
    fopAcM_ct_Retail(this, daNpc_Ho_c);
    cPhs_State state = dComIfG_resLoad(&mPhs, "Ho");

    if (state == cPhs_COMPLEATE_e) {
        fopAcM_ct_Demo(this, daNpc_Ho_c);

        switch(fopAcM_GetName(this)) {
            case PROC_NPC_HO:
                mType = 0;
                break;
            default:
                return cPhs_ERROR_e;
        }

        fopAcM_SetStatusMap(this, 0x28);
        fopAcM_OnStatus(this, fopAcStts_SHOWMAP_e);

        if (!fopAcM_entrySolidHeap(this, &CheckCreateHeap, 0xB7B0)) {
#if VERSION > VERSION_DEMO
            mpMorf = NULL;
#endif
            return cPhs_ERROR_e;
        }

        fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());

        if (!init()) {
#if VERSION > VERSION_DEMO
            mpMorf = NULL;
#endif
            return cPhs_ERROR_e;
        }
    }
    return state;
}

/* 000023F0-00002784       .text CreateHeap__10daNpc_Ho_cFv */
BOOL daNpc_Ho_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Ho", HO_BDL_HO);
    JUT_ASSERT(DEMO_SELECT(1566, 1581), modelData);

    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL, NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Ho", HO_BCK_HO_WAIT01),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1,
        NULL,
        0x80000,
        0x11020022
    );

    if (mpMorf == NULL || mpMorf->getModel() == NULL) {
        return FALSE;
    }

    J3DModel* pModel = mpMorf->getModel();
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    pModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();

    m_jnt.setHeadJntNum(modelData->getJointName()->getIndex("head"));
    JUT_ASSERT(DEMO_SELECT(1601, 1616), m_jnt.getHeadJntNum() >= 0);

    m_jnt.setBackboneJntNum(modelData->getJointName()->getIndex("backbone"));
    JUT_ASSERT(DEMO_SELECT(1606, 1621), m_jnt.getBackboneJntNum() >= 0);

    J3DModelData* penModelData = (J3DModelData*)dComIfG_getObjectRes("Ho", HO_BDL_HO_PEND);
    JUT_ASSERT(DEMO_SELECT(1612, 1627), penModelData);

    mpJoyPendentModel = mDoExt_J3DModel__create(penModelData, 0, 0x11020203);

    if(mpJoyPendentModel == NULL) {
        return FALSE;
    }

    mTexPatternIdx = 0;

#if VERSION == VERSION_DEMO
    initTexPatternAnm(false);
#else
    if (!initTexPatternAnm(false)) {
        return FALSE;
    }
#endif

    for(u16 i = 0; i < modelData->getJointNum(); i++) {
        if(i == m_jnt.getHeadJntNum() || i == m_jnt.getBackboneJntNum()) {
            mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Ho);
        }
    }

    mpMorf->getModel()->setUserArea((u32)(this));

    mAcchCir.SetWall(30.0f, 30.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this),  this, 1, &mAcchCir, fopAcM_GetSpeed_p(this));

    return TRUE;
}

/* 00002784-000027A4       .text daNpc_Ho_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Ho_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Ho_c*)i_this)->_create();
}

/* 000027A4-000027C4       .text daNpc_Ho_Delete__FP10daNpc_Ho_c */
static BOOL daNpc_Ho_Delete(daNpc_Ho_c* i_this) {
    return ((daNpc_Ho_c*)i_this)->_delete();
}

/* 000027C4-000027E4       .text daNpc_Ho_Execute__FP10daNpc_Ho_c */
static BOOL daNpc_Ho_Execute(daNpc_Ho_c* i_this) {
    return ((daNpc_Ho_c*)i_this)->_execute();
}

/* 000027E4-00002804       .text daNpc_Ho_Draw__FP10daNpc_Ho_c */
static BOOL daNpc_Ho_Draw(daNpc_Ho_c* i_this) {
    return ((daNpc_Ho_c*)i_this)->_draw();
}

/* 00002804-0000280C       .text daNpc_Ho_IsDelete__FP10daNpc_Ho_c */
static BOOL daNpc_Ho_IsDelete(daNpc_Ho_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Ho_Method = {
    (process_method_func)daNpc_Ho_Create,
    (process_method_func)daNpc_Ho_Delete,
    (process_method_func)daNpc_Ho_Execute,
    (process_method_func)daNpc_Ho_IsDelete,
    (process_method_func)daNpc_Ho_Draw,
};

actor_process_profile_definition g_profile_NPC_HO = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_HO,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Ho_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_HO,
    /* Actor SubMtd */ &l_daNpc_Ho_Method,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_12_e,
};
