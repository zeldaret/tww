/**
 * d_a_npc_mk.cpp
 * NPC - Ivan
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_mk.h"
#include "m_Do/m_Do_ext.h"
#include "res/Object/Mk.h"
#include "d/actor/d_a_player_main.h"
#include "m_Do/m_Do_lib.h"
#include "d/actor/d_a_npc_uk.h"
#include "d/d_snap.h"

static fpc_ProcID l_msgId;
static msg_class* l_msg;

static const int l_bck_ix_tbl[] = {
    dRes_INDEX_MK_BCK_MK_WAIT_e,
    dRes_INDEX_MK_BCK_MK_TALK01_e,
    dRes_INDEX_MK_BCK_MK_TALK02_e,
    dRes_INDEX_MK_BCK_MK_TIRABARE_e,
    dRes_INDEX_MK_BCK_MK_WALK_e,
    dRes_INDEX_MK_BCK_MK_RUN_e,
    dRes_INDEX_MK_BCK_MK_KEIKAI_e,
    dRes_INDEX_MK_BCK_MK_JIDA01_e,
    dRes_INDEX_MK_BCK_MK_JIDA02_e,
    dRes_INDEX_MK_BCK_MK_DA_e,
    dRes_INDEX_MK_BCK_MK_JUMP_e,
    dRes_INDEX_MK_BCK_MK_LAND_e,
};

static const int l_btp_ix_tbl[] = {
    dRes_INDEX_MK_BTP_MK_MABA_e
};

/* 00000078-00000230       .text nodeCallBack_Mk__FP7J3DNodei */
static BOOL nodeCallBack_Mk(J3DNode* node, int calcTiming) {
    cXyz temp;
    cXyz temp2;
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daNpc_Mk_c* i_this = (daNpc_Mk_c*)model->getUserArea();
        J3DJoint* joint = (J3DJoint*)node;
        int jntNo = joint->getJntNo();

        if(i_this != NULL) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            if (jntNo == i_this->getHeadJntNum()) {
                temp.setall(0.0f);
                mDoMtx_XrotM(*calc_mtx, (s16)i_this->getHead_y());
                mDoMtx_ZrotM(*calc_mtx, (s16)i_this->getHead_x());
                MtxPosition(&temp, &temp2);
                i_this->setAttentionBasePos(temp2);
                temp.set(20.0f, -20.0f, 0.0f);

                MtxPosition(&temp, &temp2);
                i_this->setEyePos(temp2);
                i_this->incAttnSetCount();

            } else if (jntNo == i_this->getBackboneJntNum()) {
                mDoMtx_XrotM(*calc_mtx, i_this->getBackbone_y());
                mDoMtx_ZrotM(*calc_mtx, i_this->getBackbone_x());
            }
            cMtx_copy(*calc_mtx, J3DSys::mCurrentMtx);
            model->setAnmMtx(jntNo, *calc_mtx);
        }
    }
    return TRUE;
}

/* 00000230-00000344       .text initTexPatternAnm__10daNpc_Mk_cFb */
BOOL daNpc_Mk_c::initTexPatternAnm(bool i_modify) {
    J3DModelData* modelData = mpMorf->getModel()->getModelData();

    m_head_tex_pattern = (J3DAnmTexPattern*)dComIfG_getObjectRes("Mk", l_btp_ix_tbl[mTexPatternIdx]);
    JUT_ASSERT(366, m_head_tex_pattern != NULL);

    if (!mBtpAnm.init(modelData, m_head_tex_pattern, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, i_modify, FALSE)) {
        return FALSE;
    }

    mBlinkFrame = 0;
    mBlinkTimer = 0;
    return TRUE;
}

/* 00000344-000003D0       .text playTexPatternAnm__10daNpc_Mk_cFv */
void daNpc_Mk_c::playTexPatternAnm() {
    if (cLib_calcTimer(&mBlinkTimer) == 0) {
        if (mBlinkFrame >= m_head_tex_pattern->getFrameMax()) {
            mBlinkFrame -= m_head_tex_pattern->getFrameMax();
            mBlinkTimer = cM_rndF(100.0f) + 30.0f;
        } else {
            mBlinkFrame++;
        }
    }
}

/* 000003D0-00000470       .text setAnm__10daNpc_Mk_cFSc */
void daNpc_Mk_c::setAnm(s8 newAnmIdx) {
    f32 morf = 8.0f;

    if (newAnmIdx == 5 && mAnmIdx == 11) {
        morf = 0.0f;
    }

    if (newAnmIdx != mAnmIdx && newAnmIdx != -1) {
        mAnmIdx = newAnmIdx;
        mAnmTimer = 0.0f;
        dNpc_setAnm(mpMorf, J3DFrameCtrl::EMode_NULL, morf, 1.0f, l_bck_ix_tbl[mAnmIdx], -1, "Mk");
    }

}

/* 00000470-000004E4       .text setAnmStatus__10daNpc_Mk_cFv */
void daNpc_Mk_c::setAnmStatus() {
    switch(mState) {
        case STATE_DEMO01:
            setAnm(2);
            break;
        case STATE_CLIMB01:
        case STATE_RUNAWAY:
            setAnm(6);
            break;
        case STATE_JITANDA02:
            break;
        default:
            setAnm(0);
            break;

    }
}

/* 000004E4-00000598       .text chkAttentionLocal__10daNpc_Mk_cFv */
bool daNpc_Mk_c::chkAttentionLocal() {
    dAttention_c& attention = dComIfGp_getAttention();

    if (chkFlag(0x1)) {
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

/* 00000598-00000634       .text chkAttention__10daNpc_Mk_cFv */
void daNpc_Mk_c::chkAttention() {
    bool temp = chkFlag(0x4);

    if(chkAttentionLocal()) {
        setFlag(0x4);
    } else {
        clrFlag(0x4);
    }

    if(temp != chkFlag(0x4) && temp == true) {
        m_jnt.setTrn();
    }
}

/* 00000634-00000678       .text eventOrder__10daNpc_Mk_cFv */
void daNpc_Mk_c::eventOrder() {
    if (ChkOrder(3)) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if(ChkOrder(2)){
            fopAcM_orderSpeakEvent(this);
        }
    }
}

/* 00000678-000006D4       .text checkOrder__10daNpc_Mk_cFv */
void daNpc_Mk_c::checkOrder() {
    if (eventInfo.mCommand == dEvtCmd_INTALK_e && ChkOrder(3)) {
        setFlag(1);
        talkInit();
    }
    ClrOrder(0xFF);
}

/* 000006D4-00000750       .text next_msgStatus__10daNpc_Mk_cFPUl */
u16 daNpc_Mk_c::next_msgStatus(u32* pMsgNo) {
    u16 msgStatus = fopMsgStts_MSG_CONTINUES_e;

    switch (*pMsgNo) {
        case 0x26BD:
        case 0x26C5:
        case 0x26C6:
        case 0x26C7:
        case 0x26C8:
        case 0x26C9:
        case 0x26CB:
        case 0x26CD:
        case 0x26D0:
        case 0x26D1:
        case 0x26D3:
        case 0x26D4:
        case 0x26D8:
            *pMsgNo += 1;
            break;
        case 0x26CA:
            if (mMsgSelectNum == 0) {
                setFlag(0x8);
                msgStatus = fopMsgStts_MSG_ENDS_e;
            } else {
                field_0x6A4 = 1;
                *pMsgNo = 0x26CB;
            }
            break;
        default:
            msgStatus = fopMsgStts_MSG_ENDS_e;
            break;
    }
    return msgStatus;
}

/* 00000750-000008A8       .text getMsg__10daNpc_Mk_cFv */
u32 daNpc_Mk_c::getMsg() {
    u32 msgNo = 0;
    clrFlag(0x8);
    switch(mType) {
        case TYPE_NORMAL:
            if(mState == STATE_DEMO01 || mState == STATE_DEMO02 || mState == STATE_DEMO03) {
                msgNo = mMsgNo;
            } else if(dComIfGs_isTmpBit(dSv_event_tmp_flag_c::UNK_0040)) {
                msgNo = 0x26B5;
            } else if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1340)) {
                msgNo = 0x26AD;
            } else if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1380)) {
                msgNo = 0x26C5;
            } else if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1210)) {
                msgNo = 0x26B9;
            } else {
                msgNo = 0x26BD;
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_1210);
            }
            break;
        case TYPE_MINIGAME:
            if (dComIfGs_isTmpBit(dSv_event_tmp_flag_c::UNK_0020)) {
                msgNo = 0x26B5;
            } else {
                msgNo = 0x26B1;
                dComIfGs_onTmpBit(dSv_event_tmp_flag_c::UNK_0020);
            }
            break;
    }
    return msgNo;
}

/* 000008A8-00000940       .text setCollision__10daNpc_Mk_cFv */
void daNpc_Mk_c::setCollision() {
    cXyz temp(0.0f, 0.0f, 0.0f); // unused
    cXyz centerPos(current.pos);
    f32 cylCollisionRadius = 40.0f;
    f32 height = 80.0f;
    mCyl.SetC(centerPos);
    mCyl.SetR(cylCollisionRadius);
    mCyl.SetH(height);
    dComIfG_Ccsp()->Set(&mCyl);
}

/* 00000940-00000A48       .text msgAnm__10daNpc_Mk_cFUc */
void daNpc_Mk_c::msgAnm(u8 param_1) {
    if(mMsgAnmIdx != param_1) {
        mMsgAnmIdx = param_1;
        switch(mMsgAnmIdx) {
            case 0:
                setAnm(0);
                break;
            case 1:
                setAnm(1);
                break;
            case 2:
                setAnm(2);
                break;
            case 3:
                mDoAud_seStart(JA_SE_START_WHISTLE);
                setAnm(3);
                break;
            case 4:
                setAnm(7);
                break;
            case 5:
                setAnm(4);
                break;
            case 6:
                setAnm(5);
                break;
            case 7:
                setAnm(6);
                break;
            case 8:
                setAnm(9);
                break;
        }
    }
}

/* 00000A48-00000A5C       .text talkInit__10daNpc_Mk_cFv */
void daNpc_Mk_c::talkInit() {
    mTalkState = TALK_INIT;
    mMsgAnmIdx = 0xFF;
}

/* 00000A5C-00000A80       .text msgPushButton__10daNpc_Mk_cFv */
void daNpc_Mk_c::msgPushButton() {
    if ((s32)mCurrMsgNo != 0x26CA) {
        return;
    }
    mMsgSelectNum = l_msg->mSelectNum;
}

/* 00000A80-00000C04       .text talk__10daNpc_Mk_cFv */
u16 daNpc_Mk_c::talk() {
    u16 msgStatus = 0xFF;
    if (mTalkState == TALK_INIT) {
        l_msgId = fpcM_ERROR_PROCESS_ID_e;
        mCurrMsgNo = getMsg();
        mTalkState = TALK_MSG_CREATE;
    } else if (mTalkState == TALK_FINISHED) {
        msgStatus = 0xFE;
    } else if (l_msgId == fpcM_ERROR_PROCESS_ID_e) {
        l_msgId = fopMsgM_messageSet(mCurrMsgNo, this);
    } else {
        if(!chkFlag(0x100)) {
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
                break;
        }
    }
    return msgStatus;
}

/* 00000C04-00000C70       .text checkDemoStart__10daNpc_Mk_cFv */
BOOL daNpc_Mk_c::checkDemoStart() {
    mStaffIdx = dComIfGp_evmng_getMyStaffId(mpName);
    if(mStaffIdx != -1) {
        mEventAction = getNowEventAction();
        return TRUE;
    }
    return FALSE;
}

/* 00000C70-00000CB8       .text getNowEventAction__10daNpc_Mk_cFv */
s32 daNpc_Mk_c::getNowEventAction() {
    static char* action_table[] = {
        "WAIT",
        "TALK",
        "HOME",
        "RUN",
        "RUN3",
        "SPEAK",
        "PARTNER",
        "JUMP",
        "JUMP2",
        "JITABATA",
        "LOOK_P",
        "HIND",
        "DISP",
        "MAKEITEM",
        "GAMESET",
        "WARP",
        "TURN"
    };
    return dComIfGp_evmng_getMyActIdx(mStaffIdx, action_table, ARRAY_SIZE(action_table), FALSE, 0);
}

/* 00000CB8-0000127C       .text init__10daNpc_Mk_cFv */
BOOL daNpc_Mk_c::init() {
    attention_info.flags = fopAc_Attn_ACTION_SPEAK_e|fopAc_Attn_LOCKON_TALK_e;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xA9;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xA9;
    gravity = -30.0f;

    J3DModel* pModel = mpMorf->getModel();
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    pModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    mStts.Init(0xA0, 0xFF, this);
    mCyl.Set(dNpc_cyl_src);
    mCyl.SetStts(&mStts);
    fopAcM_SetStatusMap(this, 0x27);
    fopAcM_OnStatus(this, fopAcStts_SHOWMAP_e);
    switch(mType) {
        case TYPE_NORMAL:
            if(dComIfGs_isTmpBit(dSv_event_tmp_flag_c::UNK_0040) &&  !dComIfGs_isTmpBit(dSv_event_tmp_flag_c::UNK_0020)) {
                if(setAction(&daNpc_Mk_c::hind_action, NULL)) {
                    setFlag(0x10);

                    fopAcM_OffStatus(this, fopAcStts_SHOWMAP_e);
                }
            } else {
                if(setAction(&daNpc_Mk_c::visit_action, NULL)) {
                    if(dComIfGs_isTmpBit(dSv_event_tmp_flag_c::UNK_0580)) {
                        fopAcM_OnStatus(this, fopAcStts_UNK4000_e);
                    }

                }
            }
            field_0x688.setInf(getPath(), fopAcM_GetRoomNo(this), true);
            if (field_0x688.getPath() == NULL) {
                return FALSE;
            }

            field_0x690.setInfDrct(field_0x688.nextPath(fopAcM_GetRoomNo(this)));
            if(field_0x690.getPath() == NULL) {
                return FALSE;
            }

            field_0x698.setInfDrct(field_0x690.nextPath(fopAcM_GetRoomNo(this)));
            if(field_0x698.getPath() == NULL) {
                return FALSE;
            }
            break;
        case TYPE_MINIGAME:
            mStts.SetWeight(0xFE);
            field_0x688.setInf(getPath(), fopAcM_GetRoomNo(this), true);
            if (field_0x688.getPath() == NULL) {
                return FALSE;
            }
            
            if(dComIfGs_isTmpBit(dSv_event_tmp_flag_c::UNK_0040) &&  !dComIfGs_isTmpBit(dSv_event_tmp_flag_c::UNK_0020)) {
                setAction(&daNpc_Mk_c::seek_action, NULL);
            } else {
                if(setAction(&daNpc_Mk_c::hind_action, NULL)) {
                    setFlag(0x10);
                }
                fopAcM_OffStatus(this, fopAcStts_SHOWMAP_e);
            }
            fopAcM_OnStatus(this, fopAcStts_UNK40_e);
            break;
        
        default:
            setAction(&daNpc_Mk_c::wait_action, NULL);
            break;
    }
    mAttnBasePos.set(current.pos);
    mEyePos.set(current.pos);

    if (mDoLib_clipper::getFar() > 1.0f) {
        fopAcM_setCullSizeFar(this, 5000.0f / mDoLib_clipper::getFar());
    }

    mMtrlSndId = 0;
    mReverb = dComIfGp_getReverb(fopAcM_GetRoomNo(this));
    return TRUE;
}

/* 0000127C-00001288       .text getType__10daNpc_Mk_cFv */
u8 daNpc_Mk_c::getType() {
    return fopAcM_GetParam(this) & 0xFF;
}

/* 00001288-00001294       .text getPath__10daNpc_Mk_cFv */
u8 daNpc_Mk_c::getPath() {
    return fopAcM_GetParam(this) >> 8 & 0xFF;
}

/* 00001294-00001574       .text nextVisitMode__10daNpc_Mk_cFv */
u8 daNpc_Mk_c::nextVisitMode() {
    cXyz dist;
    daPy_lk_c* pLink = (daPy_lk_c*)daPy_getPlayerLinkActorClass();
    switch(mVisitMode) {
        case VISIT_START:
            return VISIT_WALK_PATH;
        case VISIT_TALK: // idk if correct
            if (field_0x6A4 != 0) {
                return VISIT_WALK_PATH_FAST;
            }
            return VISIT_RUN_LINK;
        case VISIT_WALK_PATH:
            dist = pLink->current.pos - current.pos;
            if(dist.abs2XZ() < 160000.0f && field_0x698.chkInside(&pLink->current.pos)) {
                return VISIT_NOTICE_LINK;
            }
            return VISIT_WALK_PATH;

        case VISIT_RUN_LINK:
            if (!field_0x690.chkInside(&pLink->current.pos)) {
                return VISIT_LEFT_PATH;
            }

            dist = pLink->current.pos - current.pos;
            if (dist.abs2XZ() < 22500.0f) {
                return VISIT_REACHED_LINK;
            }
            return VISIT_RUN_LINK;

        case VISIT_WALK_AROUND_LINK:
        case VISIT_REACHED_LINK:
            if (!field_0x690.chkInside(&pLink->current.pos)) {
                return VISIT_LEFT_PATH;
            }
            dist = pLink->current.pos - current.pos;

            if (dist.abs2XZ() > 32400.0f) {
                return VISIT_RUN_LINK;
            }
            
            if (mVisitMode == VISIT_REACHED_LINK) {
                if (mRunAroundLinkTimer != 0) {
                    mRunAroundLinkTimer--;
                } else {
                    return VISIT_WALK_AROUND_LINK;
                }
            }
            return mVisitMode;

        case VISIT_NOTICE_LINK:
        case VISIT_LEFT_PATH:
            if (mWaitTimer != 0) {
                mWaitTimer--;
                break;
            }
            dist = pLink->current.pos - current.pos;

            if (dist.abs2XZ() < 160000.0f && field_0x698.chkInside(&pLink->current.pos)) {
                return VISIT_RUN_LINK;
            }
            return VISIT_WALK_PATH;
            
        case VISIT_WALK_PATH_FAST:
            if (field_0x6A4 != 0) {
                field_0x6A4--;
                break;
            }
            return VISIT_WALK_PATH_IGNORE_LINK;

        case VISIT_WALK_PATH_IGNORE_LINK:
            if (field_0x6A4 != 0) {
                field_0x6A4--;
                break;
            }
            return VISIT_WALK_PATH;
    }
    return mVisitMode;
}

/* 00001574-000016F8       .text visitInit__10daNpc_Mk_cFUc */
void daNpc_Mk_c::visitInit(u8 i_nextVisitMode) {
    switch(i_nextVisitMode) {
        case VISIT_WALK_PATH:
            field_0x688.setNearPathIndx(&current.pos, 100.0f);
            setAnm(4);
            break;
        case VISIT_RUN_LINK:
            setAnm(5);
            if (mVisitMode == 6) {
                mTimerToReachLink = 55;
            } else {
                mTimerToReachLink = 0;
            }
            break;
        case VISIT_WALK_AROUND_LINK:
            setAnm(4);
            break;
        case VISIT_REACHED_LINK:
            mRunAroundLinkTimer = mTimerToReachLink;
            setAnm(5);
            break;
        case VISIT_NOTICE_LINK:
            setAnm(0);
            speedF = 0.0f;
            mWaitTimer = 0xF;
            break;
        case VISIT_LEFT_PATH:
            setAnm(0);
            speedF = 0.0f;
            mWaitTimer = 0x19;
            break;
        case VISIT_WALK_PATH_FAST:
            field_0x688.setNearPathIndx(&current.pos, 100.0f);
            setAnm(5);
            field_0x6A4 = 0x64;
            break;
        case VISIT_WALK_PATH_IGNORE_LINK:
            setAnm(4);
            field_0x6A4 = 0x258;
            break;
        default:
            JUT_ASSERT(0x452, 0);
            break;
    }
    mVisitMode = i_nextVisitMode;
}

/* 000016F8-000017A8       .text visitProc__10daNpc_Mk_cFv */
void daNpc_Mk_c::visitProc() {
    switch(mVisitMode) {
        case VISIT_WALK_PATH:
        case VISIT_WALK_PATH_IGNORE_LINK:
            walkPath(0);
            break;
        case VISIT_WALK_PATH_FAST:
            walkPath(2);
            break;
        case VISIT_RUN_LINK:
            runLink();
            if (mTimerToReachLink < 55){
                mTimerToReachLink++;
            }
            break;
        case VISIT_WALK_AROUND_LINK:
        case VISIT_REACHED_LINK:
            aroundLink();
            break;
        case VISIT_NOTICE_LINK:
        case VISIT_LEFT_PATH:
            setFlag(0x20);
            break;
    }
}

/* 000017A8-00001900       .text runawayInit__10daNpc_Mk_cFv */
void daNpc_Mk_c::runawayInit() {
    switch(mMkStatic.m0) {
        case 1:
        case 2:
        case 5:
            if (mAnmIdx == 6) {
                fopAcM_seStart(this, JA_SE_CV_TR_KO_A_FOUND, 0);
            }
            speedF = 0.0f;
            setAnm(5);
            break;
        case 3:
            speedF = 0.0f;
            setAnm(6);
            break;
        case 4:
            speed.y = 25.0f;
            gravity = -3.3f;
            speedF = 8.0f;
            setFlag(0x40);
            setAnm(9);
            mState = STATE_JUMP;
            current.angle.y = field_0x6F0;
            fopAcM_seStart(this, JA_SE_CV_TR_KO_A_CAUGHT, 0);
            break;
    }
}

/* 00001900-00001950       .text walkPath__10daNpc_Mk_cFUc */
void daNpc_Mk_c::walkPath(u8 param_1) {
    if (mMkStatic.walkPath(this, &field_0x688, param_1)) {
        setFlag(0x80);
    }
}

/* 00001950-000019DC       .text runLink__10daNpc_Mk_cFv */
void daNpc_Mk_c::runLink() {
    daPy_lk_c* pLink = (daPy_lk_c*)daPy_getPlayerLinkActorClass();
    s16 temp;
    dNpc_calc_DisXZ_AngY(current.pos, pLink->current.pos, NULL, &temp);
    cLib_addCalcAngleS2(&current.angle.y, temp, 8, 0x800);
}

/* 000019DC-00001A14       .text aroundLink__10daNpc_Mk_cFv */
void daNpc_Mk_c::aroundLink() {
    daPy_lk_c* pLink = (daPy_lk_c*)daPy_getPlayerLinkActorClass();
    // this makes the codegen work for all versions there might be an inline instead that doesnt need this?
    speedF = speedF;
    mMkStatic.aroundWalk(this, pLink, mRunAroundLinkTimer);
}

/* 00001A14-00001A68       .text remove_Um2__10daNpc_Mk_cFv */
void daNpc_Mk_c::remove_Um2() {
    daNpc_Uk_c* ac = (daNpc_Uk_c*)fopAcM_searchFromName("Um2", 0, 0);
    if(ac != NULL) {
        fopAcM_SetParam(ac, fopAcM_GetParam(ac) | 0x80000000);
        fopAcM_OnStatus(ac, fopAcStts_UNK800_e);
    }
}

/* 00001A68-00001BA4       .text demoInitCom__10daNpc_Mk_cFv */
void daNpc_Mk_c::demoInitCom() {
    int* a_intP = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "RM_Um2");
    if(a_intP != NULL) {
        remove_Um2();
    }
    a_intP = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "SOUND");
    if(a_intP != NULL) {
        switch(*a_intP) {
            case 1:
                fopAcM_seStart(this, JA_SE_CV_TR_KO_A_RUN_AWAY, 0);
                break;
            case 2:
                fopAcM_seStart(this, JA_SE_CV_TR_KO_A_FOUND, 0);
                break;

        }

    }
}

/* 00001BA4-000024C8       .text demoProc__10daNpc_Mk_cFv */
bool daNpc_Mk_c::demoProc() {
    daPy_lk_c* pLink = (daPy_lk_c*)daPy_getPlayerLinkActorClass();
    BOOL temp = FALSE;
    cXyz* a_xyz;
    int* a_intP;
    if(dComIfGp_evmng_getIsAddvance(mStaffIdx)) {
        demoInitCom();
        switch(mEventAction) {
            case 0:
                speedF = 0.0f;
                setAnm(0);
                break;
            case 1:
            case 10:
                speedF = 0.0f;
                setAnm(0);
                break;
            case 2:
                speedF = 0.0f;
                old.pos = home.pos;
                current.pos = home.pos;
                current.angle.y = home.angle.y;
                break;
            case 3:
            case 4: {
                if (mAnmIdx == 5) {
                    speedF = 12.0f;
                } else if (mAnmIdx == 11) {
                    speedF = 6.0f;
                    setAnm(5);
                } else {
                    setAnm(5);
                }

                a_xyz = dComIfGp_evmng_getMyXyzP(mStaffIdx, "Pos");
                JUT_ASSERT(1299, a_xyz);
                field_0x6D0 = current.pos;
                field_0x6DC = *a_xyz;
                int* pTimer = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "Timer");

                if (pTimer != NULL) {
                    field_0x6E8 = *pTimer;
                } else {
                    field_0x6E8 = -1;
                }
                break;
            }
            case 5:
                talkInit();
                dComIfGp_event_setTalkPartner(this);

                a_intP = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "MsgNo");
                JUT_ASSERT(1313, a_intP);

                mMsgNo = *a_intP;
                temp = TRUE;
                break;
            case 6:
                dComIfGp_event_setTalkPartner(this);
                break;
            case 8:
                setFlag(0x2);
                gravity = -3.3f;
                speed.y = 20.0f;
                speedF = 8.0f;
                setFlag(0x40);
                setAnm(10);
                break;
            case 7:
                setFlag(0x2);
                gravity = -2.1f;
                speed.y = 30.0f;
                speedF = 10.0f;
                setFlag(0x40);
                setAnm(10);
                break;
            case 9:
                setFlag(0x2);
                setAnm(7);
                break;
            case 11:
                speedF = 0.0f;
                setFlag(0x10);
                fopAcM_OffStatus(this, fopAcStts_SHOWMAP_e);
                mPrevState = 13;
                break;
            case 12:
                mCurrActionFunc = NULL;
                setAction(&daNpc_Mk_c::visit_action, NULL);
                mPrevState = mState;
                mState = STATE_DEMO01;
                clrFlag(0x10);
                fopAcM_OnStatus(this, fopAcStts_SHOWMAP_e);
                break;
            case 13: {
                fpc_ProcID itemID = fopAcM_createItemForPresentDemo(&current.pos, dItemNo_HEART_PIECE_e);

                if (itemID != fpcM_ERROR_PROCESS_ID_e) {
                    dComIfGp_event_setItemPartnerId(itemID);
                }
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_1340);
                break;
            }
            case 14:
                dComIfGs_offTmpBit(dSv_event_tmp_flag_c::UNK_0040);
                dComIfGs_onTmpBit(dSv_event_tmp_flag_c::UNK_0120);
                break;
            case 15:
                speedF = 0.0f;
                a_xyz = dComIfGp_evmng_getMyXyzP(mStaffIdx, "Pos");
                JUT_ASSERT(1379, a_xyz);


                current.pos = *a_xyz;
                old.pos = *a_xyz;

                a_intP = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "Angle");
                JUT_ASSERT(1385, a_intP);

                current.angle.y = *a_intP;
                shape_angle.y = *a_intP;
                break;
            case 16:
                a_intP = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "Angle");
                JUT_ASSERT(1391, a_intP);
                field_0x6F0 = *a_intP;
                break;
        }
    }
    switch(mEventAction) {
        case 3:
        case 4:
            f32 temp2;
            s16 temp3;
            dNpc_calc_DisXZ_AngY(current.pos, field_0x6DC, &temp2, &temp3);
            if(temp2 < speedF || mMkStatic.chkPointPass(&field_0x6D0, &field_0x6DC, &current.pos) != 0) {
                if(mEventAction == 4) {
                    current.pos.x = field_0x6DC.x;
                    current.pos.z = field_0x6DC.z;
                    speedF = 0.0f;
                }
                dComIfGp_evmng_cutEnd(mStaffIdx);
            } else {
                cLib_addCalcAngleS(&current.angle.y, temp3, 8, 0x1000, 0x400);
                cLib_chaseF(&speedF, 12.0f, 1.1f);
                if (field_0x6E8 > 0) {
                    field_0x6E8--;
                }
                if (field_0x6E8 == 0) {
                    dComIfGp_evmng_cutEnd(mStaffIdx);
                }
            }
            return true;
            
        case 5: {
            u16 temp4 = talk();
            if (temp4 == fopMsgStts_BOX_CLOSED_e || temp4 == 0xFE) {
                dComIfGp_evmng_cutEnd(mStaffIdx);
            }
            setFlag(0x20);
            break;
        }
        case 2:
        case 6:
        case 15:
            dComIfGp_evmng_cutEnd(mStaffIdx);
            return true;
            case 1:
            setFlag(0x20);
            dComIfGp_evmng_cutEnd(mStaffIdx);
            break;
        case 10:
            setFlag(0x200);
            dComIfGp_evmng_cutEnd(mStaffIdx);
            break;
        case 7:
        case 8:
            if (!chkFlag(0x40)) {
                setAnm(11);
                gravity = -30.0f;
                speedF = 0.0f;
                if (chkFlag(0x2)) {
                    clrFlag(0x2);
                    if (mEventAction == 7) {
                        dComIfGp_getVibration().StartShock(4, -0x21, cXyz(0.0f, 1.0f, 0.0f));

                    }
                } else if (mAnmEnded != 0) {
                    dComIfGp_evmng_cutEnd(mStaffIdx);
                }
            }
            return true;
        case 9:
            if (chkFlag(0x2)) {
                if (mAnmEnded != 0) {
                    dComIfGp_evmng_cutEnd(mStaffIdx);
                    clrFlag(0x2);
                }
            } else {
                dComIfGp_evmng_cutEnd(mStaffIdx);
            }
            break;

        case 16:
            if (cLib_addCalcAngleS(&current.angle.y, field_0x6F0, 8, 0x1000, 0x400) == 0) {
                dComIfGp_evmng_cutEnd(mStaffIdx);
            }
            break;
        default:
            dComIfGp_evmng_cutEnd(mStaffIdx);
            break;
    }

    if (temp) {
        return true;
    } 
    return mpMorf->isMorf();
}

/* 000024C8-0000251C       .text setAttention__10daNpc_Mk_cFb */
void daNpc_Mk_c::setAttention(bool param_1) {
    if (!param_1 && mAttnSetCount >= 2) {
        return;
    }

    eyePos.set(mEyePos.x, mEyePos.y, mEyePos.z);
    attention_info.position.set(mAttnBasePos.x, mAttnBasePos.y + 45.0f, mAttnBasePos.z);
}

/* 0000251C-000025CC       .text getLookBackMode__10daNpc_Mk_cFv */
u8 daNpc_Mk_c::getLookBackMode() {
    if (chkFlag(0x200)) {
        return 3;
    }

    if (chkFlag(0x20)) {
        return 0;
    }

    if (field_0x6A4 != 0) {
        return 2;
    }

    if (chkFlag(0x400) || mAnmIdx == 7 || mAnmIdx == 8) {
        return 2;
    }

    if (chkFlag(0x4)) {
        return 1;
    }

    if (mState == STATE_VISIT && (mVisitMode == VISIT_WALK_AROUND_LINK || mVisitMode == VISIT_REACHED_LINK)) {
        return 1;
    }
    return 2;
}

/* 000025CC-000027C8       .text lookBack__10daNpc_Mk_cFv */
void daNpc_Mk_c::lookBack() {
    cXyz temp2;
    cXyz temp(0.0f, 0.0f, 0.0f);
    cXyz* dstPos = NULL;
    s16 desiredYRot = current.angle.y;
    bool headOnlyFollow = false;

    switch(getLookBackMode()) {
        case 0:
            m_jnt.setTrn();
            temp2 = dNpc_playerEyePos(-20.0f);
            dstPos = &temp2;
            temp.set(current.pos);
            temp.y = eyePos.y;
            break;
        case 1:
            temp2 = dNpc_playerEyePos(-20.0f);
            dstPos = &temp2;
            temp.set(current.pos);
            temp.y = eyePos.y;
            headOnlyFollow = true;

            break;
        case 2:
            desiredYRot = current.angle.y;
            headOnlyFollow = true;
            break;
        case 3:
            daPy_lk_c* pLink = (daPy_lk_c*)daPy_getPlayerLinkActorClass();
            pLink = (daPy_lk_c*)fopAcM_getTalkEventPartner(pLink);

            if(pLink == NULL) {
                pLink = (daPy_lk_c*)daPy_getPlayerLinkActorClass();
            }
            m_jnt.setTrn();
            temp2 = pLink->eyePos;
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
}

/* 000027C8-0000284C       .text wait01__10daNpc_Mk_cFv */
bool daNpc_Mk_c::wait01() {
    if (chkFlag(0x1)) {
        mPrevState = mState;
        mState = STATE_TALK01;
        setAnmStatus();
    } else {
        SetOrder(0x1);
    }
    return mpMorf->isMorf();

}

/* 0000284C-0000297C       .text talk01__10daNpc_Mk_cFv */
bool daNpc_Mk_c::talk01() {
    if(talk() == fopMsgStts_BOX_CLOSED_e) {
        if(chkFlag(0x8)) {
            mEventIdx = dComIfGp_evmng_getEventIdx("MK_GAMESTART");
            fopAcM_orderChangeEventId(this, mEventIdx, 0, 0xFFFF);
            mState = STATE_DEMO02;
            setFlag(0x400);
            dComIfGs_onTmpBit(dSv_event_tmp_flag_c::UNK_0040);
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_2201);

        } else {
            mState = mPrevState;
            setAnmStatus();
            dComIfGp_event_reset();
            clrFlag(0x1);
            mAttentionTimer = 5;
        }

    }
    setFlag(0x20);
    return mpMorf->isMorf();
}

/* 0000297C-00002AC0       .text talk02__10daNpc_Mk_cFv */
bool daNpc_Mk_c::talk02() {
    if(talk() == fopMsgStts_BOX_CLOSED_e) {
        if(!mMkStatic.chkGameSet()) {
            mState = mPrevState;
            setAnmStatus();
            dComIfGp_event_reset();
        } else {
            mEventIdx = dComIfGp_evmng_getEventIdx("MK_GAMESET");
            fopAcM_orderChangeEventId(this, mEventIdx, 0, 0xFFFF);
            mDoAud_seStart(JA_SE_END_WHISTLE);
            mState = STATE_DEMO02;
            setFlag(0x400);
        }
        clrFlag(0x1);
        mAttentionTimer = 5;
    }
    setFlag(0x20);
    return mpMorf->isMorf();
}

/* 00002AC0-00002BB4       .text visitTalkInit__10daNpc_Mk_cFv */
u8 daNpc_Mk_c::visitTalkInit() {
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1F80) && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_1E02)) {
        mEventIdx = eventInfo.mEventId;
        mState = STATE_DEMO03;
        demo03();
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_1E04);
        return 12;
    }
    if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_1208) && !dComIfGs_checkGetItem(dItemNo_PICTO_BOX_e) && !dComIfGs_checkGetItem(dItemNo_DELUXE_PICTO_BOX_e)) {
        mEventIdx = eventInfo.mEventId;
        mState = STATE_DEMO03;
        demo03();
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_1602);
        return 12;
    }
    return 1;
}

/* 00002BB4-00002C90       .text visitSetEvent__10daNpc_Mk_cFv */
void daNpc_Mk_c::visitSetEvent() {
    if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_1F80)) {
        if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_1E02)){
            eventInfo.setEventName("MK_TALK3");
            return;
        }
    }

    if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_1208) && !dComIfGs_checkGetItem(dItemNo_PICTO_BOX_e) && !dComIfGs_checkGetItem(dItemNo_DELUXE_PICTO_BOX_e)) {
        eventInfo.setEventName("MK_TALK2");
        return;
    }
    eventInfo.setEventName("MK_TALK");
}

/* 00002C90-00002F2C       .text visit01__10daNpc_Mk_cFv */
bool daNpc_Mk_c::visit01() {
    f32 temp;
    if (chkFlag(0x1)) {
        mPrevState = mState;
        mState = visitTalkInit();
        setAnmStatus();
        speedF = 0.0f;
        mVisitMode = VISIT_TALK;
        if (dComIfGs_isTmpBit(dSv_event_tmp_flag_c::UNK_0580)) {
            dComIfGs_offTmpBit(dSv_event_tmp_flag_c::UNK_0580);
            fopAcM_OffStatus(this, fopAcStts_UNK4000_e);
        }
    } else {
        if(checkDemoStart()) {
            mPrevState = mState;
            mState = STATE_DEMO01;
            setAnmStatus();
            speedF = 0.0f;
            mVisitMode = VISIT_TALK;
            demo01();
            
        } else {
            u8 nextvisitMode = nextVisitMode();
            if(nextvisitMode != mVisitMode) {
                visitInit(nextvisitMode);
            }
            visitProc();
            if (mAnmIdx == 4) {
                temp = 2.5f;
            } else if (mAnmIdx == 5) {
                if (mVisitMode == 5) {
                    temp = 9.0f;
                } else {
                    temp = 12.0f;
                }
            }

            if (speedF > temp) {
                cLib_chaseF(&speedF, temp, 2.8f);
            } else {
                cLib_chaseF(&speedF, temp, 1.1f);
            }
            SetOrder(0x1);
            
            if (mVisitMode == 4 || mVisitMode == 5) {
                daPy_lk_c* pLink = (daPy_lk_c*)daPy_getPlayerLinkActorClass();

                s16 angle = fopAcM_searchActorAngleY(pLink, this);
                angle -= pLink->shape_angle.y;
                if (angle < 0) {
                    angle = -angle;
                }
                if (angle > 0x1800) {
                    mOrderFlags &= ~0x01; // is this an inline?
                }
            }

            if (field_0x6A4 != 0) {
                mOrderFlags &= ~0x01; // is this an inline?
            }

            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1F80) && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_1E02) && dComIfGs_isTmpBit(dSv_event_flag_c::UNK_0580)) {
                SetOrder(0x2);
                eventInfo.setEventName("MK_TALK4");
            } else {
                if (ChkOrder(0x1)) {
                    visitSetEvent();
                }
            }
        }
    }
    return true;
}

/* 00002F2C-00003064       .text climb01__10daNpc_Mk_cFv */
bool daNpc_Mk_c::climb01() {
    daPy_lk_c* pLink = (daPy_lk_c*)daPy_getPlayerLinkActorClass();

    if (chkFlag(0x40)) {
        return false;
    }
    if (pLink->checkFrontRollCrash()) {
        f32 temp;
        dNpc_calc_DisXZ_AngY(current.pos, pLink->current.pos, &temp, NULL);
        if(temp < 200.0f) {
            mState = STATE_DROP01;
            mEventIdx = dComIfGp_evmng_getEventIdx("MK_DROP");
            fopAcM_orderOtherEventId(this, mEventIdx);
            dComIfGs_onTmpBit(dSv_event_tmp_flag_c::UNK_0002);
        }
    }
    return mpMorf->isMorf();
}

/* 00003064-00003108       .text drop01__10daNpc_Mk_cFv */
bool daNpc_Mk_c::drop01() {
    if (eventInfo.mCommand == dEvtCmd_INDEMO_e) {
        mPrevState = STATE_RUNAWAY;
        mState = STATE_DEMO03;
        mMkStatic.init(0x50, 0x12C);
        return demo03();
    }
    fopAcM_orderOtherEventId(this, mEventIdx);
    return mpMorf->isMorf();
}

/* 00003108-00003234       .text runaway__10daNpc_Mk_cFv */
bool daNpc_Mk_c::runaway() {
    u8 temp = mMkStatic.runAwayProc(this, &field_0x688, &mCyl, &field_0x6F0);
    if (temp != mMkStatic.m0) {
        if ((temp == 1 && mMkStatic.m0 == 2) || (temp == 2 && mMkStatic.m0 == 1)) {
            if (cM_rndF(1.0f) < 0.5f) {
                fopAcM_seStart(this, JA_SE_CV_TR_KO_A_TURN, 0);
            }
        }
        mMkStatic.m0 = temp;
        runawayInit();
    }

    if (temp == 3) {
        setFlag(0x20);
    }
    if (mAnmIdx == 5) {
        cLib_chaseF(&speedF, mMkStatic.getSpeedF(15.0f, 18.0f), 2.8f);
    }
    return true;
}

/* 00003234-000032CC       .text jump__10daNpc_Mk_cFv */
bool daNpc_Mk_c::jump() {
    if (!chkFlag(0x40)) {
        setAnm(0);
        gravity = -30.0f;
        speedF = 0.0f;
        if (mpMorf->isMorf()) {
            mState = STATE_JITANDA01;
            setAnm(7);
            SetOrder(0x2);
        }
    }
    return true;
}

/* 000032CC-0000330C       .text jitanda01__10daNpc_Mk_cFv */
bool daNpc_Mk_c::jitanda01() {
    if (chkFlag(0x1)) {
        setFlag(0x100);
        mPrevState = STATE_JITANDA02;
        mState = STATE_TALK02;
    } else {
        SetOrder(0x2);
    }
    return true;
}

/* 0000330C-0000339C       .text jitanda02__10daNpc_Mk_cFv */
bool daNpc_Mk_c::jitanda02() {
    if(chkFlag(0x1)) {
        mPrevState = 9;
        mState = STATE_TALK02;
    } else {
        if(checkDemoStart()) {
            mPrevState = mState;
            mState = STATE_DEMO01;
            speedF = 0.0f;
            demo01();
        } else {
            SetOrder(0x1);
        }
    }
    return true;
}

/* 0000339C-000033F0       .text demo01__10daNpc_Mk_cFv */
bool daNpc_Mk_c::demo01() {
    if(!checkDemoStart()) {
        mState = mPrevState;
        setAnmStatus();
        return true;
    }
    return demoProc();
}

/* 000033F0-00003564       .text demo02__10daNpc_Mk_cFv */
bool daNpc_Mk_c::demo02() {
    if(dComIfGp_evmng_endCheck(mEventIdx)) {
        dComIfGp_event_reset();
        setAction(&daNpc_Mk_c::hind_action, NULL);
        setFlag(0x10);
        fopAcM_OffStatus(this, fopAcStts_SHOWMAP_e);
        clrFlag(0x1);
        clrFlag(0x400);
        return true;
    }

    if(!checkDemoStart()) {
        JUT_ASSERT(2058, NULL);
    }

    return demoProc();
}

/* 00003564-00003638       .text demo03__10daNpc_Mk_cFv */
bool daNpc_Mk_c::demo03() {
    if(dComIfGp_evmng_endCheck(mEventIdx)) {
        mState = mPrevState;
        setAnmStatus();
        dComIfGp_event_reset();
        clrFlag(0x1);
        mAttentionTimer = 5;
        return true;
    }

    if(!checkDemoStart()) {
        JUT_ASSERT(2077, NULL);
    }

    return demoProc();
}

/* 00003638-0000370C       .text wait_action__10daNpc_Mk_cFPv */
BOOL daNpc_Mk_c::wait_action(void*) {
    if(mActionStatus == ACTION_STARTING) {
        mState = STATE_WAIT;
        setAnmStatus();
        mActionStatus++; // set to ACTION_ONGOING
    } else if(mActionStatus != ACTION_ENDING) {
        chkAttention();
        clrFlag(0x200 | 0x20);

        bool temp;
        switch(mState) {
            case STATE_WAIT:
                temp = wait01();
                break;
            case STATE_TALK01:
                temp = talk01();
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

/* 0000370C-00003964       .text seek_action__10daNpc_Mk_cFPv */
BOOL daNpc_Mk_c::seek_action(void*) {
    if(mActionStatus == ACTION_STARTING) {
        if(dComIfGs_isTmpBit(dSv_event_tmp_flag_c::UNK_0002)) {
            mState = STATE_RUNAWAY;
            mMkStatic.init(0x50, 0x12C);
            mMkStatic.setRndPathPos(this, &field_0x688);
        } else {
            mState = STATE_CLIMB01;
        }
        setAnmStatus();
        mActionStatus++; // set to ACTION_ONGOING
    } else if(mActionStatus != ACTION_ENDING) {
        chkAttention();
        clrFlag(0x200 | 0x20);

        bool temp;
        switch(mState) {
            case STATE_CLIMB01:
                temp = climb01();
                break;
            case STATE_DROP01:
                temp = drop01();
                break;
            case STATE_RUNAWAY:
                temp = runaway();
                break;
            case STATE_JUMP:
                temp = jump();
                break;
            case STATE_JITANDA01:
                temp = jitanda01();
                break;
            case STATE_JITANDA02:
                temp = jitanda02();
                break;
            case STATE_DEMO01:
                temp = demo01();
                break;
            case STATE_DEMO02:
                temp = demo02();
                break;
            case STATE_DEMO03:
                temp = demo03();
                break;
            case STATE_TALK02:
                temp = talk02();
                break;
            case STATE_13:
                temp = false;
                setAction(&daNpc_Mk_c::hind_action, NULL);
                break;
            default:
                temp = false;
                break;
        }
        lookBack();
        if(chkFlag(0x40)) {
            temp = true;
        }
        setAttention(temp);
    }
    return TRUE;
}

/* 00003964-00003B00       .text hind_action__10daNpc_Mk_cFPv */
BOOL daNpc_Mk_c::hind_action(void*) {
    if(mActionStatus == ACTION_STARTING) {
        mActionStatus++; // set to ACTION_ONGOING
    } else if(mActionStatus != ACTION_ENDING) {
        clrFlag(0x200 | 0x20);
        if(mType == TYPE_MINIGAME && dComIfGs_isTmpBit(dSv_event_tmp_flag_c::UNK_0040) &&  !dComIfGs_isTmpBit(dSv_event_tmp_flag_c::UNK_0020)) {
            if(setAction(&daNpc_Mk_c::seek_action, NULL)) {
                clrFlag(0x10);
                fopAcM_OnStatus(this, fopAcStts_SHOWMAP_e);
            }
        }
        if((mType == TYPE_NORMAL || mType == TYPE_MINIGAME) && checkDemoStart()) {
            bool temp = demoProc();
            lookBack();
            setAttention(temp);
        }
    }
    return TRUE;
}

/* 00003B00-00003C7C       .text visit_action__10daNpc_Mk_cFPv */
BOOL daNpc_Mk_c::visit_action(void*) {
    if(mActionStatus == ACTION_STARTING) {
        if (dComIfGs_isTmpBit(dSv_event_tmp_flag_c::UNK_0040)) {
            mState = STATE_JITANDA02;
            setAnm(7);
            mStts.SetWeight(0xFE);
        } else {
            mState = STATE_VISIT;
            setAnmStatus();
            mStts.SetWeight(0xA0);
        }
        mActionStatus++; // set to ACTION_ONGOING
        mVisitMode = 0;
    } else if (mActionStatus != ACTION_ENDING) {
        bool temp;
        chkAttention();
        clrFlag(0x200 | 0x20);
        switch(mState) {
            case STATE_VISIT:
                temp = visit01();
                break;
            case STATE_JITANDA02:
                temp = jitanda02();
                break;
            case STATE_TALK01:
                temp = talk01();
                break;
            case STATE_TALK02:
                temp = talk02();
                break;
            case STATE_DEMO01:
                temp = demo01();
                break;
            case STATE_DEMO02:
                temp = demo02();
                break;
            case STATE_DEMO03:
                temp = demo03();
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

/* 00003C7C-00003DA0       .text _draw__10daNpc_Mk_cFv */
BOOL daNpc_Mk_c::_draw() {
    J3DModel* pModel = mpMorf->getModel();
    J3DModelData* pModelData = pModel->getModelData();
    if (chkFlag(0x10)) {
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(pModel, &tevStr);
    mBtpAnm.entry(pModelData, mBlinkFrame);
    mpMorf->entry();
    mBtpAnm.remove(pModelData);

    cXyz shadowPos(current.pos.x, current.pos.y + 50.0f, current.pos.z);

    mShadowId = dComIfGd_setShadow(
        mShadowId, 1, pModel, &shadowPos, 300.0f, 20.0f,
        current.pos.y, mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr
    );

    dSnap_RegistFig(DSNAP_TYPE_MK, this, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 00003DA0-00004010       .text _execute__10daNpc_Mk_cFv */
BOOL daNpc_Mk_c::_execute() {
    m_jnt.setParam(
        /* mMaxBackboneX */ 0,
        /* mMaxBackboneY */ 7000,
        /* mMinBackboneX */ 0,
        /* mMinBackboneY */ -7000,
        /* mMaxHeadX */ 8000,
        /* mMaxHeadY */ 9000,
        /* mMinHeadX */ -2000,
        /* mMinHeadY */ -9000,
        /* mMaxTurnStep */ 1000
    );

    playTexPatternAnm();

    mAnmEnded = mpMorf->play(&eyePos, mMtrlSndId, mReverb);
    if(mpMorf->getFrame() < mAnmTimer) {
        mAnmEnded = 1;
    }

    mAnmTimer = mpMorf->getFrame();
    if (mAnmEnded != 0) {
        switch(mAnmIdx) {
            case 7:
                if(cM_rnd() < 0.4f) {
                    setAnm(8);
                }
                break;
            case 8:
                setAnm(7);
                break;
        }
    }
    checkOrder();
    (this->*mCurrActionFunc)(NULL);
    eventOrder();

    if(!chkFlag(0x80)) {
        shape_angle.y = current.angle.y;
    }
    clrFlag(0x80);
    mMtrlSndId = 0;

    if(!chkFlag(0x10)) {
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
        mObjAcch.CrrPos(*dComIfG_Bgsp());

        if (mObjAcch.ChkGroundHit()) {
            clrFlag(0x40);
            mMtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
        } else {
            setFlag(0x40);
        }

        tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
        tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    } else {
        setFlag(0x40);
    }

    J3DModel* pModel = mpMorf->getModel();
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    pModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();

    if(chkFlag(0x10)) {
        mCyl.OffCoSetBit();
    } else {
        mCyl.OnCoSetBit();
        setCollision();
    }
    return TRUE;
}

/* 00004010-0000405C       .text _delete__10daNpc_Mk_cFv */
BOOL daNpc_Mk_c::_delete() {
    dComIfG_resDelete(&mPhs, "Mk");
    if (mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }
    return TRUE;
}

/* 0000405C-0000407C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Mk_c*)i_this)->CreateHeap();
}

/* 0000407C-000042F8       .text _create__10daNpc_Mk_cFv */
cPhs_State daNpc_Mk_c::_create() {
    fopAcM_ct_Retail(this, daNpc_Mk_c);
    cPhs_State state = dComIfG_resLoad(&mPhs, "Mk");
    if (state == cPhs_COMPLEATE_e) {
        fopAcM_ct_Demo(this, daNpc_Mk_c);
        mpName = "Mk";

        switch(fopAcM_GetName(this)) {
            case fpcNm_NPC_MK_e:
                switch(getType()) {
                    case TYPE_NORMAL:
                        mType = TYPE_NORMAL;
                        break;
                    case TYPE_MINIGAME:
                        mType = TYPE_MINIGAME;
                        argument = 4;
                        mpName = "Mk2";
                        break;
                    default:
                        mType = TYPE_NONE;
                        break;
                }
                break;
            default:
                return cPhs_ERROR_e;

        }

        tevStr.mRoomNo = current.roomNo;
        if (!fopAcM_entrySolidHeap(this, &CheckCreateHeap, 0xB7B0)) {

#if VERSION > VERSION_DEMO
            mpMorf = NULL;
#endif
            return cPhs_ERROR_e;
        }

        fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
        fopAcM_setCullSizeBox(this, -35.0f, -10.0f, -35.0f, 35.0f, 100.0f, 35.0f);

        if(!init()) {
#if VERSION > VERSION_DEMO
            mpMorf = NULL;
#endif
            return cPhs_ERROR_e;
        }
    }
    return state;
}

/* 000046A8-00004954       .text CreateHeap__10daNpc_Mk_cFv */
BOOL daNpc_Mk_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Mk", dRes_INDEX_MK_BDL_MK_e);

    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL, NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Mk", dRes_INDEX_MK_BCK_MK_WAIT_e),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1,
        NULL,
        0x80000,
        0x11020022
    );

    if (mpMorf == NULL || mpMorf->getModel() == NULL) {
        return FALSE;
    }

    m_jnt.setHeadJntNum(modelData->getJointName()->getIndex("head2"));
    JUT_ASSERT(DEMO_SELECT(2574, 2576), m_jnt.getHeadJntNum() >= 0);

    m_jnt.setBackboneJntNum(modelData->getJointName()->getIndex("backbone"));
    JUT_ASSERT(DEMO_SELECT(2579, 2581), m_jnt.getBackboneJntNum() >= 0);

    mTexPatternIdx = 0;
    
#if VERSION == VERSION_DEMO
    initTexPatternAnm(false);
#else
    if (!initTexPatternAnm(false)) {
        return FALSE;
    }
#endif

    for(u16 i = 0; i < modelData->getJointNum(); i++) {
        if(i == getHeadJntNum() || i == getBackboneJntNum()) {
            mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Mk);
        }
    }

    mpMorf->getModel()->setUserArea((u32)(this));

    mAcchCir.SetWall(60.0f, 30.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this));
    mObjAcch.SetGroundCheckOffset(100.0f);
    fopAcM_SetMaxFallSpeed(this, -90.0f);
    mVisitMode = 0;
    return TRUE;
}

/* 00004954-00004974       .text daNpc_Mk_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Mk_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Mk_c*)i_this)->_create();
}

/* 00004974-00004994       .text daNpc_Mk_Delete__FP10daNpc_Mk_c */
static BOOL daNpc_Mk_Delete(daNpc_Mk_c* i_this) {
    return ((daNpc_Mk_c*)i_this)->_delete();
}

/* 00004994-000049B4       .text daNpc_Mk_Execute__FP10daNpc_Mk_c */
static BOOL daNpc_Mk_Execute(daNpc_Mk_c* i_this) {
    return ((daNpc_Mk_c*)i_this)->_execute();
}

/* 000049B4-000049D4       .text daNpc_Mk_Draw__FP10daNpc_Mk_c */
static BOOL daNpc_Mk_Draw(daNpc_Mk_c* i_this) {
    return ((daNpc_Mk_c*)i_this)->_draw();
}

/* 000049D4-000049DC       .text daNpc_Mk_IsDelete__FP10daNpc_Mk_c */
static BOOL daNpc_Mk_IsDelete(daNpc_Mk_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Mk_Method = {
    (process_method_func)daNpc_Mk_Create,
    (process_method_func)daNpc_Mk_Delete,
    (process_method_func)daNpc_Mk_Execute,
    (process_method_func)daNpc_Mk_IsDelete,
    (process_method_func)daNpc_Mk_Draw,
};

actor_process_profile_definition g_profile_NPC_MK = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0006,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_MK_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Mk_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_MK_e,
    /* Actor SubMtd */ &l_daNpc_Mk_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
