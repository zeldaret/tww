/**
 * d_a_npc_tt.cpp
 * NPC - Tott
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_tt.h"
#include "m_Do/m_Do_ext.h"
#include "res/Object/Tt.h"
#include "d/d_snap.h"
#include "d/actor/d_a_player_main.h"

static fpc_ProcID l_msgId;
static msg_class* l_msg;

/* 00000078-00000098       .text daNpc_tt_XyCheckCB__FPvi */
static s16 daNpc_tt_XyCheckCB(void* i_this, int i_itemBtn) {
    return ((daNpc_Tt_c*)i_this)->XyCheckCB(i_itemBtn);
}

/* 00000098-000000BC       .text XyCheckCB__10daNpc_Tt_cFi */
s16 daNpc_Tt_c::XyCheckCB(int i_itemBtn) {
    return dComIfGp_getSelectItem(i_itemBtn) == dItemNo_WIND_WAKER_e ? TRUE : FALSE;
}

/* 000000BC-00000108       .text daNpc_tt_XyEventCB__FPvi */
static s16 daNpc_tt_XyEventCB(void* i_this, int i_itemBtn) {
    daNpc_Tt_c* a_this = (daNpc_Tt_c*)i_this;
    a_this->mEventIdx = dComIfGp_evmng_getEventIdx("TACT_TT10");
    return a_this->mEventIdx;
}

/* 00000108-000002D8       .text nodeCallBack_Tt__FP7J3DNodei */
static BOOL nodeCallBack_Tt(J3DNode* node, int calcTiming) {
    cXyz temp;
    cXyz temp2;
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daNpc_Tt_c* i_this = (daNpc_Tt_c*)model->getUserArea();
        J3DJoint* joint = (J3DJoint*)node;
        int jntNo = joint->getJntNo();

        if(i_this != NULL) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            if (jntNo == i_this->m_head_jnt_num) {
                temp.setall(0.0f);
                cMtx_YrotM(*calc_mtx, -i_this->getHead_y());
                cMtx_ZrotM(*calc_mtx, -i_this->getHead_x() - i_this->mHeadAnm.field_0x00);
                MtxPosition(&temp, &temp2);
                i_this->setAttentionBasePos(temp2);
                temp.set(20.0f, -20.0f, 0.0f);

                MtxPosition(&temp, &temp2);
                i_this->setEyePos(temp2);
                i_this->incAttnSetCount();

            } else if (jntNo == i_this->m_backbone_jnt_num) {
                mDoMtx_XrotM(*calc_mtx, i_this->getBackbone_y());
                mDoMtx_ZrotM(*calc_mtx, i_this->m_jnt.getBackbone_x());
            }
            cMtx_copy(*calc_mtx, J3DSys::mCurrentMtx);
            model->setAnmMtx(jntNo, *calc_mtx);
        }
    }
    return TRUE;
}

/* 000002D8-00000368       .text setAnmStatus__10daNpc_Tt_cFv */
void daNpc_Tt_c::setAnmStatus() {
    switch(mState) {
        case 1:
        case 2:
            if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_0C40)) {
                danceInit(0);
            } else {
                setAnm(4);
            }
            break;
        case 3:
            break;
        default:
            setAnm(0);
            break;
    }
}

//probably unused JUT_ASSERT
static void dummy() {
    OSReport("Tt");
    OSReport("d_a_npc_tt.cpp");
    OSReport("0");
    OSReport("Halt");
}

#include "d/actor/d_a_npc_tt_anm.inc"

/* 00000368-000003DC       .text eventOrder__10daNpc_Tt_cFv */
void daNpc_Tt_c::eventOrder() {
    if (ChkOrder(1)) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        fopAcM_orderSpeakEvent(this);
    }
    if (ChkOrder(2)) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
    }
    if (ChkOrder(4)) {
        eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
    }
}

/* 000003DC-00000484       .text checkOrder__10daNpc_Tt_cFv */
void daNpc_Tt_c::checkOrder() {
    if (eventInfo.mCommand != dEvtCmd_INDEMO_e) {
        if (eventInfo.mCommand == dEvtCmd_INTALK_e && ChkOrder(7)) {
            if (dComIfGp_event_chkTalkXY()) {
                setFlag(0x4);
            } else {
                setFlag(0x2);
            }
            talkInit();
        }
    }
    ClrOrder();
}

/* 00000484-000004F4       .text next_msgStatus__10daNpc_Tt_cFPUl */
u16 daNpc_Tt_c::next_msgStatus(u32* pMsgNo) {
    u16 msgStatus = fopMsgStts_MSG_CONTINUES_e;

    switch (*pMsgNo) {
        case 0x22C5:
        case 0x22C7:
        case 0x22C8:
        case 0x22D5:
        case 0x22D6:
            (*pMsgNo)++;
            break;

        case 0x22C6:
            *pMsgNo = 0x22D5;
            break;
        case 0x22D7:
            *pMsgNo = 0x22C7;
            break;

        default:
            msgStatus = fopMsgStts_MSG_ENDS_e;
            break;
    }
    return msgStatus;
}


/* 000004F4-000005D0       .text getMsg__10daNpc_Tt_cFv */
u32 daNpc_Tt_c::getMsg() {
    u32 msgNo;
    clrFlag(0x20);
    switch(mState) {
        case 2:
            if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_0C40)) {
                msgNo = 0x22CB;
            } else {
                if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B08)) {
                    msgNo = 0x22CA;
                    setFlag(0x20);
                } else {
                    dComIfGs_onEventBit(dSv_event_flag_c::UNK_0B08);
                    msgNo = 0x22C5;
                    setFlag(0x20);
                }
            }
            break;
        default:
            msgNo = mMsgNo;
            switch(msgNo) {
                case 0x5B3:
                    dComIfGp_setMelodyNum(5);
                    break;
            }
    }
    return msgNo;
}

/* 000005D0-00000650       .text setCollision__10daNpc_Tt_cFv */
void daNpc_Tt_c::setCollision() {
    
    cXyz centerPos(current.pos);
    f32 cylCollisionRadius = 48.0f;
    f32 height = 140.0f;
    mCyl.SetC(centerPos);
    mCyl.SetR(cylCollisionRadius);
    mCyl.SetH(height);
    dComIfG_Ccsp()->Set(&mCyl);
}

/* 00000650-00000664       .text talkInit__10daNpc_Tt_cFv */
void daNpc_Tt_c::talkInit() {
    mTalkState = TALK_INIT;;
    mMsgAnmIdx = 0xFF;
}

/* 00000664-00000718       .text msgAnm__10daNpc_Tt_cFv */
void daNpc_Tt_c::msgAnm() {
    if(mMsgAnmIdx != dComIfGp_getMesgAnimeAttrInfo()) {
        mMsgAnmIdx = dComIfGp_getMesgAnimeAttrInfo();
        switch(mMsgAnmIdx) {
            case 0:
                setAnm(0);
                break;
            case 1:
                setAnm(1);
                break;
            case 2:
                setAnm(3);
                break;
            case 3:
                setAnm(4);
                break;
            case 4:
                danceInit(0);
                break;
            case 5:
                setAnm(2);
                break;
        }
<<<<<<< HEAD

=======
>>>>>>> 6f09bf28ce1a2f1cdea62b931cbbdb40e7f821ec
    }
}

/* 00000718-00000730       .text msgPushButton__10daNpc_Tt_cFv */
void daNpc_Tt_c::msgPushButton() {
    if ((s32)mCurrMsgNo != 0x22C6) {
        return;
    }
    mNoticeLinkTimer = 0xF;
}

/* 00000730-00000778       .text msgContinue__10daNpc_Tt_cFv */
void daNpc_Tt_c::msgContinue() {
    switch(mCurrMsgNo) {
        case 0x22D5:
            if (mNoticeLinkTimer > 0) {
                mNoticeLinkTimer--;
            } else {
                fopMsgM_messageSendOn();
            }
            break;
    }
}

/* 00000778-00000900       .text talk__10daNpc_Tt_cFv */
u16 daNpc_Tt_c::talk() {
    u16 msgStatus = 0xFF;
    if (mTalkState == TALK_INIT) {
        l_msgId = fpcM_ERROR_PROCESS_ID_e;
        mCurrMsgNo = getMsg();
        mTalkState = TALK_MSG_CREATE;
    } else if (mTalkState != TALK_FINISHED) {
        if(l_msgId == fpcM_ERROR_PROCESS_ID_e) {
            l_msgId = fopMsgM_messageSet(mCurrMsgNo, this);
        } else {
            msgAnm();
<<<<<<< HEAD

=======
>>>>>>> 6f09bf28ce1a2f1cdea62b931cbbdb40e7f821ec
            switch(mTalkState) {
                case TALK_MSG_CREATE:
                    l_msg = fopMsgM_SearchByID(l_msgId);
                    if (l_msg != NULL) {
                        mTalkState = TALK_ACTIVE;
                    }
                    break;

                case TALK_ACTIVE:
                    if(l_msg != NULL) {
                        msgStatus = l_msg->mStatus;
                        if(msgStatus == fopMsgStts_MSG_CONTINUES_e) {
                            msgContinue();
                        } else if(msgStatus == fopMsgStts_MSG_DISPLAYED_e) {
                            msgPushButton();
                            l_msg->mStatus = next_msgStatus(&mCurrMsgNo);
                            if(l_msg->mStatus == fopMsgStts_MSG_CONTINUES_e) {
                                fopMsgM_messageSet(mCurrMsgNo);
                            }
                        } else if(msgStatus == fopMsgStts_BOX_CLOSED_e) {
                            l_msg->mStatus = fopMsgStts_MSG_DESTROYED_e;
                            l_msgId = fpcM_ERROR_PROCESS_ID_e;
                            l_msg = NULL;
                        }
                    }
                    break;
            }
        }
    }
<<<<<<< HEAD

=======
>>>>>>> 6f09bf28ce1a2f1cdea62b931cbbdb40e7f821ec
    return msgStatus;
}

/* 00000900-000009EC       .text demoInitChange__10daNpc_Tt_cFv */
void daNpc_Tt_c::demoInitChange() {
    int* a_intP = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "prm0");
    JUT_ASSERT(DEMO_SELECT(758, 758), a_intP);

    if(a_intP != NULL) {
        mEventIdx = dComIfGp_evmng_getEventIdx("TACT_TT11");
        setEvFlag(0x1);
        fopAcM_orderChangeEventId(daPy_getPlayerLinkActorClass(), this, mEventIdx, 0, 0xFFFF);
    }
}

/* 000009EC-00000B1C       .text demoProcTact1__10daNpc_Tt_cFv */
bool daNpc_Tt_c::demoProcTact1() {
    switch(daPy_getPlayerLinkActorClass()->getTactTimerCancel()) {
        case 1:
            mEventIdx = dComIfGp_evmng_getEventIdx("TACT_TT12");
            setEvFlag(0x1);
            fopAcM_orderChangeEventId(daPy_getPlayerLinkActorClass(), this, mEventIdx, 0, 0xFFFF);
            break;
        case 2:
            mEventIdx = dComIfGp_evmng_getEventIdx("TACT_TT13");
            setEvFlag(0x1);
            fopAcM_orderChangeEventId(daPy_getPlayerLinkActorClass(), this, mEventIdx, 0, 0xFFFF);
            break;
        default:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_0C40);
            dComIfGp_evmng_cutEnd(mStaffIdx);
            break;
<<<<<<< HEAD

    }
=======
    }

>>>>>>> 6f09bf28ce1a2f1cdea62b931cbbdb40e7f821ec
    return TRUE;
}

/* 00000B1C-00000BA0       .text demoInitPatten__10daNpc_Tt_cFv */
void daNpc_Tt_c::demoInitPatten() {
    setEvFlag(0x4);
    mSoundTimer = 0;
    danceInit(0);
    int* cnt = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "Cnt");
    if(cnt != NULL) {
        field_0xE7A = *cnt;
    } else {
        field_0xE7A = 2;
    }
}

/* 00000BA0-00000D40       .text demoProcPatten__10daNpc_Tt_cFv */
bool daNpc_Tt_c::demoProcPatten() {
    if (field_0xE7A == 0) {
        dComIfGp_evmng_cutEnd(mStaffIdx);
        clrEvFlag(0x4);
    } else {
        if(danceProc()) {
            field_0xE7A--;
        }
        if(mSoundTimer > 0) {
            mSoundTimer--;
            if(mSoundTimer == 0) {
                switch(mCurrAnmIdx) {
                    case 8:
                        fopAcM_seStart(this, JA_SE_CV_TT_DANCE_FIN, 0);
                        break;
                    case 9:
                        fopAcM_seStart(this, JA_SE_CV_TT_DANCE_2, 0);
                        break;
                    case 10:
                        fopAcM_seStart(this, JA_SE_CV_TT_DANCE_1, 0);
                        break;
                }

            }
        }
    }
    return FALSE;
}

/* 00000D40-00000E04       .text demoInitSpeak__10daNpc_Tt_cFv */
void daNpc_Tt_c::demoInitSpeak() {
    talkInit();
    int* a_intP = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "MsgNo");
    JUT_ASSERT(882, a_intP);
    mMsgNo = *a_intP;
    switch(mMsgNo) {
        case 0x22CE:
            if(dKy_daynight_check() == dKy_TIME_NIGHT_e) {
                mMsgNo = 0x22CF;
            }
            break;
    }
<<<<<<< HEAD

=======
>>>>>>> 6f09bf28ce1a2f1cdea62b931cbbdb40e7f821ec
}

/* 00000E04-00000E5C       .text demoProcSpeak__10daNpc_Tt_cFv */
bool daNpc_Tt_c::demoProcSpeak() {
    u16 temp = talk();
    if (temp == fopMsgStts_BOX_CLOSED_e || temp == 0xFE) {
        dComIfGp_evmng_cutEnd(mStaffIdx);
    }
    return false;
}

/* 00000E5C-00000EC4       .text demoInitWait__10daNpc_Tt_cFv */
void daNpc_Tt_c::demoInitWait() {
    int* pTimer = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "Timer");
    if (pTimer != NULL) {
        mTimer = *pTimer;
    } else {
        mTimer = 0;
    }
}

/* 00000EC4-00000F14       .text demoProcWait__10daNpc_Tt_cFv */
bool daNpc_Tt_c::demoProcWait() {
    if (mTimer > 0) {
        mTimer--;
    } else {
        dComIfGp_evmng_cutEnd(mStaffIdx);
    }
    return FALSE;
}

/* 00000F14-00001020       .text demoInitCom__10daNpc_Tt_cFv */
void daNpc_Tt_c::demoInitCom() {
    daPy_lk_c* pLink = (daPy_lk_c*)daPy_getPlayerLinkActorClass();
    int* hidePl = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "HIDE_PL");
    if (hidePl != NULL) {
        if (*hidePl != 0) {
            pLink->onPlayerNoDraw();
        } else {
            pLink->offPlayerNoDraw();
        }
    }

    int* disp = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "DISP");
    if (disp != NULL) {
        if (*disp != 0) {
            clrEvFlag(0x2);
        } else {
            setEvFlag(0x2);
        }
    }

    int* anm = dComIfGp_evmng_getMyIntegerP(mStaffIdx,"Anm");
    if (anm != NULL) {
        setAnm(*anm & 0xff);
    }
}

/* 00001020-00001040       .text demoProcCom__10daNpc_Tt_cFv */
void daNpc_Tt_c::demoProcCom() {
    if (chkEvFlag(0x2)) {
        setFlag(0x8);
    }
}

/* 00001040-00001088       .text getNowEventAction__10daNpc_Tt_cFv */
s32 daNpc_Tt_c::getNowEventAction() {
    static char* action_table[] = {
        "WAIT",
        "SPEAK",
        "PATTEN",
        "CHANGE",
        "TACT0",
        "TACT1",
    };

    return dComIfGp_evmng_getMyActIdx(mStaffIdx, action_table, ARRAY_SIZE(action_table), FALSE, 1);
}

/* 00001088-00001238       .text demoProc__10daNpc_Tt_cFv */
bool daNpc_Tt_c::demoProc() {
    bool temp = false;

    if(chkEvFlag(0x1)) {
        mStaffIdx = dComIfGp_evmng_getMyStaffId("Tt");
        clrEvFlag(0x1);
    }
    s32 eventAction = getNowEventAction();
    if(dComIfGp_evmng_getIsAddvance(mStaffIdx)) {
        demoInitCom();
        setFlag(0x80);
        switch(eventAction) {
            case 1:
                demoInitSpeak();
                break;
            case 0:
                demoInitWait();
                break;
            case 2:
                demoInitPatten();
                temp = true;
                break;
            case 3:
                demoInitChange();
                break;
        }
    }

    switch(eventAction) {
        case 1:
            temp = demoProcSpeak();
            break;
        case 0:
            demoProcWait();
            break;
        case 2:
            demoProcPatten();
            break;
        case 3:
            break;
        case 4:
            dComIfGp_evmng_cutEnd(mStaffIdx);
            break;
        case 5:
            demoProcTact1();
            break;
        default:
            dComIfGp_evmng_cutEnd(mStaffIdx);
            break;
    }

    demoProcCom();
    if(eventAction != 2) {
        danceProc();
    }
    return temp;
}

/* 00001238-00001420       .text init__10daNpc_Tt_cFv */
BOOL daNpc_Tt_c::init() {
    attention_info.flags = fopAc_Attn_ACTION_SPEAK_e|fopAc_Attn_LOCKON_TALK_e;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xAB;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xAB;
    gravity = -30.0f;
    fopAcM_SetStatusMap(this, 0x27);
    fopAcM_OnStatus(this, fopAcStts_SHOWMAP_e);

<<<<<<< HEAD

    switch(mType) {
        case 0:
            if(setAction(&daNpc_Tt_c::wait_action, NULL)) {
                // nothing?
            }
=======
    switch(mType) {
        case 0:
            setAction(&daNpc_Tt_c::wait_action, NULL);
>>>>>>> 6f09bf28ce1a2f1cdea62b931cbbdb40e7f821ec
            break;
    }

    mAttnBasePos.set(current.pos);
    mEyePos.set(current.pos);

    J3DModel* model = mpMorf->getModel();
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    model->setBaseTRMtx(mDoMtx_stack_c::get());
    ke_execute();
    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(dNpc_cyl_src);
    mCyl.SetStts(&mStts);
    eventInfo.setXyCheckCB(daNpc_tt_XyCheckCB);
    eventInfo.setXyEventCB(daNpc_tt_XyEventCB);
    mMtrlSndId = 0;
    mReverb = dComIfGp_getReverb(fopAcM_GetRoomNo(this));
    return TRUE;
}

/* 00001420-00001474       .text setAttention__10daNpc_Tt_cFb */
void daNpc_Tt_c::setAttention(bool param_1) {
    if (!param_1 && mAttnSetCount >= 2) {
        return;
    }

    eyePos.set(mEyePos.x, mEyePos.y, mEyePos.z);
    attention_info.position.set(mAttnBasePos.x, mAttnBasePos.y + 65.0f, mAttnBasePos.z);
}

/* 00001474-000015D8       .text lookBack__10daNpc_Tt_cFv */
void daNpc_Tt_c::lookBack() {
    cXyz temp2;
    cXyz temp(0.0f, 0.0f, 0.0f);
    cXyz* dstPos = NULL;
    s16 desiredYRot = current.angle.y;
    bool headOnlyFollow = false;

    switch(mState) {
        case 1:
            desiredYRot = home.angle.y;
            if(desiredYRot != current.angle.y) {
                m_jnt.setTrn();
            } else {
                m_jnt.clrTrn();
            }
            break;

        default:
            if (chkFlag(0x20)) {
                desiredYRot = home.angle.y;
                m_jnt.clrTrn();
            } else {
                m_jnt.setTrn();
                temp2 = dNpc_playerEyePos(-20.0f);
                dstPos = &temp2;
                temp.set(current.pos);
                temp.y = eyePos.y;
            }
            break;
<<<<<<< HEAD

=======
>>>>>>> 6f09bf28ce1a2f1cdea62b931cbbdb40e7f821ec
    }

    if (m_jnt.trnChk()) {
        cLib_addCalcAngleS2(&mMaxHeadTurnVelocity, 0x800, 4, 0x800);
    } else {
        mMaxHeadTurnVelocity = 0;
    }

    m_jnt.lookAtTarget(&current.angle.y, dstPos, temp, desiredYRot, mMaxHeadTurnVelocity, headOnlyFollow);
    shape_angle.y = current.angle.y;
}

/* 000015D8-00001734       .text wait01__10daNpc_Tt_cFv */
bool daNpc_Tt_c::wait01() {
    if(chkFlag(0x4)) {
        mReturnToState = mState;
        mState = 3;
        setAnmStatus();
        mTimer = 0x14;
        setEvFlag(0x1);
        fopAcM_seStart(this, JA_SE_PRE_TAKT, 0);
        return demoProc();

    } else if(chkFlag(0x2)) {
        mReturnToState = mState;
        mState = 2;
        setAnmStatus();
    } else {
        SetOrder(0x2);
        if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0C40) && dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B08)) {
            SetOrder(0x4);
        }
    }
    danceProc();
    return mpMorf->isMorf();
}

/* 00001734-00001804       .text talk01__10daNpc_Tt_cFv */
bool daNpc_Tt_c::talk01() {
    u16 temp = talk();
    if(mCurrMsgNo == 0x22C6 && dComIfGp_checkMesgSendButton()) {
        clrFlag(0x20);
    }

    if(temp == fopMsgStts_BOX_CLOSED_e) {
        mState = mReturnToState;
        setAnmStatus();
        dComIfGp_event_reset();
        clrFlag(0x2);
        clrFlag(0x4);
    }
    danceProc();
    return mpMorf->isMorf();
}

/* 00001804-00001894       .text tact00__10daNpc_Tt_cFv */
bool daNpc_Tt_c::tact00() {
    if(dComIfGp_evmng_endCheck(mEventIdx)) {
        mState = mReturnToState;
        setAnmStatus();
        dComIfGp_event_reset();
        clrFlag(0x2);
        clrFlag(0x4);
        return true;
    }
    return demoProc();
}

/* 00001894-00001970       .text wait_action__10daNpc_Tt_cFPv */
BOOL daNpc_Tt_c::wait_action(void*) {
    if(mActionStatus == ACTION_STARTING) {
        mState = 1;
        setAnmStatus();
        mActionStatus++; // set to ACTION_ONGOING
    } else if(mActionStatus != ACTION_ENDING) {
        bool temp;
        clrFlag(0x8);
        switch(mState) {
            case 1:
                temp = wait01();
                break;
            case 2:
                temp = talk01();
                break;
            case 3:
                temp = tact00();
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

/* 00001970-00001BAC       .text ke_control__7tt_ke_sFf */
void tt_ke_s::ke_control(f32 param_1) {
    int i;
    cXyz* temp2 = &field_0x00[1];
    cXyz* temp3 = &field_0x78[1];
    cXyz temp;
    cXyz temp6;
    cXyz temp4;
    temp.set(0.0f, 0.0f, 7.875f);

    f32 _065 = 0.65f;

    for(i = 1; i < 10; i++, temp2++, temp3++) {
        temp4.x = temp3->x + (temp2->x - (temp2 - 1)->x);
        temp4.z = temp3->z + (temp2->z - (temp2 - 1)->z);

        f32 temp7 = temp2->y + temp3->y +-3.0f;

        if(temp7 < param_1) {
            temp7 = param_1;
        }
        
        temp4.y = temp7 - (temp2-1)->y;
        mDoMtx_XrotS(*calc_mtx, -cM_atan2s(temp4.y, temp4.z));
        mDoMtx_YrotM(*calc_mtx, (s16)cM_atan2s(temp4.x, std::sqrtf(temp4.y * temp4.y + temp4.z * temp4.z)));
        MtxPosition(&temp, &temp6);
        *temp3 = *temp2;
        *temp2 = *(temp2-1) + temp6;
        temp3->x = (temp2->x - temp3->x) * _065;
        temp3->y = (temp2->y - temp3->y) * _065;
        temp3->z = (temp2->z - temp3->z) * _065;
    }
}

/* 00001BAC-00001BE4       .text ke_pos_set__7tt_ke_sFP4cXyz */
void tt_ke_s::ke_pos_set(cXyz* i_param) {
    for(int i = 0; i < 10; i_param++) {
        *i_param = field_0x00[i];
        i++;
    }
}

/* 00001BE4-00001D48       .text set_ke_root__10daNpc_Tt_cFiii */
void daNpc_Tt_c::set_ke_root(int param_1, int param_2, int param_3) {
    cXyz temp(0.0f, 0.0f, 0.0f);
    MTXCopy(mpMorf->getModel()->getAnmMtx(param_1), *calc_mtx);
    MtxPosition(&temp, &mLineKe.field_0x6C8[param_3].field_0x00[0]);

    MTXCopy(mpMorf->getModel()->getAnmMtx(param_2), *calc_mtx);
    MtxPosition(&temp, &mLineKe.field_0x6C8[param_3 + 3].field_0x00[0]);

    mLineKe.field_0x6C8[param_3+1].field_0x00[0] = (mLineKe.field_0x6C8[param_3 + 3].field_0x00[0] - mLineKe.field_0x6C8[param_3].field_0x00[0]) * 0.3333f + mLineKe.field_0x6C8[param_3].field_0x00[0];

    mLineKe.field_0x6C8[param_3+2].field_0x00[0] = (mLineKe.field_0x6C8[param_3 + 3].field_0x00[0] - mLineKe.field_0x6C8[param_3].field_0x00[0]) * 0.6667f + mLineKe.field_0x6C8[param_3].field_0x00[0];
}

/* 00001D48-00001E04       .text ke_execute__10daNpc_Tt_cFv */
void daNpc_Tt_c::ke_execute() {
    mpMorf->calc();

    set_ke_root(6, 7, 0);
    set_ke_root(10, 11, 4);
    int i;
    tt_ke_s* ke = mLineKe.field_0x6C8;
    f32 y = current.pos.y + 3.0f;

    for (i = 0; i < 8; i++, ke++) {
        ke->ke_control(y);
        ke->ke_pos_set(mLineKe.mLineMat.getPos(i));
    }
}

/* 00001E04-00001F84       .text _draw__10daNpc_Tt_cFv */
BOOL daNpc_Tt_c::_draw() {
    J3DModel* pModel = mpMorf->getModel();
    J3DModelData* pModelData = pModel->getModelData();
    if (chkFlag(0x8)) {
        return TRUE;
    }
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(pModel, &tevStr);
    mBtpAnm.entry(pModelData, mBlinkFrame);
    mpMorf->entryDL();
    mBtpAnm.remove(pModelData);
    f32 _100 = 100.0f;
    f32 _450 = 450.0f;
    cXyz shadowPos(current.pos.x, current.pos.y + _100, current.pos.z);

    mShadowId = dComIfGd_setShadow(
        mShadowId, 1, pModel, &shadowPos, _450, 20.0f,
        current.pos.y, mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr
    );

<<<<<<< HEAD
    mLineKe.mLineMat.update(10, 0.8f, (GXColor){0xC9, 0xCA, 0xE4, 0xFF}, 0, &tevStr);
=======
#ifdef __MWERKS__
    mLineKe.mLineMat.update(10, 0.8f, (GXColor){0xC9, 0xCA, 0xE4, 0xFF}, 0, &tevStr);
#else
    GXColor color = (GXColor){0xC9, 0xCA, 0xE4, 0xFF};
    mLineKe.mLineMat.update(10, 0.8f, color, 0, &tevStr);
#endif
>>>>>>> 6f09bf28ce1a2f1cdea62b931cbbdb40e7f821ec
    dComIfGd_set3DlineMat(&mLineKe.mLineMat);

    dSnap_RegistFig(DSNAP_TYPE_TT, this, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 00001F84-00002158       .text _execute__10daNpc_Tt_cFv */
BOOL daNpc_Tt_c::_execute() {
    m_jnt.setParam(
        /* mMaxBackboneX */ 0,
        /* mMaxBackboneY */ 0x1C70,
        /* mMinBackboneX */ 0,
        /* mMinBackboneY */ -0x1C70,
        /* mMaxHeadX */ 0x1FFE,
        /* mMaxHeadY */ 9000,
        /* mMinHeadX */ -0x1FFE,
        /* mMinHeadY */ -9000,
        /* mMaxTurnStep */ 0x1000
    );

    playTexPatternAnm();

    mAnmEnded = mpMorf->play(&eyePos, mMtrlSndId, mReverb);
    if(mpMorf->getFrame() < mAnmTimer) {
        mAnmEnded = 1;
    }

    mAnmTimer = mpMorf->getFrame();
    if (mAnmEnded != 0) {
        switch(mCurrAnmIdx) {
            case 3:
                if (mAnmLoopCount > 0) {
                    setAnm(0);
                } else {
                    mAnmLoopCount++;
                }
                break;
        }
    }
    mHeadAnm.move();
    checkOrder();
    (this->*mCurrActionFunc)(NULL);
    eventOrder();
    fopAcM_posMoveF(this, mStts.GetCCMoveP());
    mObjAcch.CrrPos(*dComIfG_Bgsp());
    mMtrlSndId = 0;

    if (!mObjAcch.ChkGroundHit()) {
        mMtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
    }

    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);

    J3DModel* pModel = mpMorf->getModel();
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    pModel->setBaseTRMtx(mDoMtx_stack_c::get());
    setCollision();
    ke_execute();
    return TRUE;
}

/* 00002158-000021A8       .text _delete__10daNpc_Tt_cFv */
BOOL daNpc_Tt_c::_delete() {
    dComIfG_resDelete(&mPhs, "Tt");
    if (mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }
    return TRUE;
}

/* 000021A8-000021C8       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Tt_c*)i_this)->CreateHeap();
}

/* 000021C8-0000241C       .text _create__10daNpc_Tt_cFv */
cPhs_State daNpc_Tt_c::_create() {
    fopAcM_ct_Retail(this, daNpc_Tt_c);
    cPhs_State state = dComIfG_resLoad(&mPhs, "Tt");
    if (state == cPhs_COMPLEATE_e) {
        fopAcM_ct_Demo(this, daNpc_Tt_c);
        switch(fopAcM_GetName(this)) {
            case fpcNm_NPC_TT_e:
                mType = 0;
                break;
            default:
                return cPhs_ERROR_e;
        }

        if (!fopAcM_entrySolidHeap(this, &CheckCreateHeap, 0xE880)) {
#if VERSION > VERSION_DEMO
            mpMorf = NULL;
#endif
            return cPhs_ERROR_e;
        }

        fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
        if(!init()) {
#if VERSION > VERSION_DEMO
            mpMorf = NULL;
#endif
            return cPhs_ERROR_e;
        }
    }
    return state;
}

/* 000027D0-00002AB0       .text CreateHeap__10daNpc_Tt_cFv */
BOOL daNpc_Tt_c::CreateHeap() {

    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Tt", dRes_INDEX_TT_BDL_TT_e);

    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL, NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Tt", dRes_INDEX_TT_BCK_WAIT01_e),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1,
        dComIfG_getObjectRes("Tt", dRes_INDEX_TT_BAS_WAIT01_e),
        0x80000,
        0x11020022
    );

    if (mpMorf == NULL || mpMorf->getModel() == NULL) {
        return FALSE;
    }

    m_head_jnt_num = modelData->getJointName()->getIndex("head");
    JUT_ASSERT(DEMO_SELECT(1706, 1708), m_head_jnt_num >= 0);

    m_backbone_jnt_num = modelData->getJointName()->getIndex("backbone1");
    JUT_ASSERT(DEMO_SELECT(1708, 1710), m_backbone_jnt_num >= 0);

    switch(mType) {
        case 0:
            mTexPatternIdx = false;
            break;
    }

#if VERSION == VERSION_DEMO
    initTexPatternAnm(false);
#else
    if (!initTexPatternAnm(false)) {
        return FALSE;
    }
#endif

    for(u16 i = 0; i < modelData->getJointNum(); i++) {
        if(i == m_head_jnt_num || i == m_backbone_jnt_num) {
            mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Tt);
        }
    }

    mpMorf->getModel()->setUserArea((u32)(this));

    mAcchCir.SetWall(30.0f, 0.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this));
    return mLineKe.mLineMat.init(8, 10, 0) == FALSE ? FALSE : TRUE;
}

/* 00002AB0-00002AD0       .text daNpc_Tt_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Tt_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Tt_c*)i_this)->_create();
}

/* 00002AD0-00002AF0       .text daNpc_Tt_Delete__FP10daNpc_Tt_c */
static BOOL daNpc_Tt_Delete(daNpc_Tt_c* i_this) {
    return ((daNpc_Tt_c*)i_this)->_delete();
}

/* 00002AF0-00002B10       .text daNpc_Tt_Execute__FP10daNpc_Tt_c */
static BOOL daNpc_Tt_Execute(daNpc_Tt_c* i_this) {
    return ((daNpc_Tt_c*)i_this)->_execute();
}

/* 00002B10-00002B30       .text daNpc_Tt_Draw__FP10daNpc_Tt_c */
static BOOL daNpc_Tt_Draw(daNpc_Tt_c* i_this) {
    return ((daNpc_Tt_c*)i_this)->_draw();
}

/* 00002B30-00002B38       .text daNpc_Tt_IsDelete__FP10daNpc_Tt_c */
static BOOL daNpc_Tt_IsDelete(daNpc_Tt_c*) {
    return TRUE;
}


static actor_method_class l_daNpc_Tt_Method = {
    (process_method_func)daNpc_Tt_Create,
    (process_method_func)daNpc_Tt_Delete,
    (process_method_func)daNpc_Tt_Execute,
    (process_method_func)daNpc_Tt_IsDelete,
    (process_method_func)daNpc_Tt_Draw,
};

actor_process_profile_definition g_profile_NPC_TT = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_TT_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Tt_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_TT_e,
    /* Actor SubMtd */ &l_daNpc_Tt_Method,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_12_e,
};
