/**
 * d_a_npc_kp1.cpp
 * NPC - Maggie (rich)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_kp1.h"
#include "d/d_com_inf_game.h"
#include "d/d_snap.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"
#include "res/Object/Kp.h"

class daNpc_Kp1_HIO_c : public mDoHIO_entry_c {
public:
    struct hio_prm_c {
        s16 field_0;
        s16 field_2;
        s16 field_4;
        s16 field_6;
        s16 field_8;
        s16 field_A;
        s16 field_C;
        s16 field_E;
        s16 field_10;
        s16 field_12;
        f32 mAttentionArrowYOffset;
        f32 field_18;
    };  // Size: 0x1C

    daNpc_Kp1_HIO_c();
    virtual ~daNpc_Kp1_HIO_c() {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ int field_0x8;
    /* 0x0C */ hio_prm_c mPrmTbl;
};

static daNpc_Kp1_HIO_c l_HIO;

/* 000000EC-00000150       .text __ct__15daNpc_Kp1_HIO_cFv */
daNpc_Kp1_HIO_c::daNpc_Kp1_HIO_c() {
    static hio_prm_c a_prm_tbl = {
        /* field_0                */ 0x1FFE,
        /* field_2                */ 0x38E0,
        /* field_4                */ 0xF448,
        /* field_6                */ 0xC720,
        /* field_8                */ 0x0000,
        /* field_A                */ 0x0000,
        /* field_C                */ 0x0000,
        /* field_E                */ 0x0000,
        /* field_10               */ 0x05DC,
        /* field_12               */ 0x0400,
        /* mAttentionArrowYOffset */ 170.0f,
        /* field_18               */ 0.0f,
    };
    memcpy(&mPrmTbl, &a_prm_tbl, sizeof(hio_prm_c));
    mNo = -1;
    field_0x8 = -1;
}

/* 00000198-0000035C       .text nodeCallBack_Kp__FP7J3DNodei */
static BOOL nodeCallBack_Kp(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daNpc_Kp1_c* i_this = (daNpc_Kp1_c*)(model->getUserArea());
        if (i_this) {
            static cXyz a_att_pos_offst(0.0f, 0.0f, 0.0f);
            static cXyz a_eye_pos_offst(20.0f, -20.0f, 0.0f);
            u16 jointIdx = ((J3DJoint*)(i_node))->getJntNo();
            mDoMtx_stack_c::copy(model->getAnmMtx(jointIdx));
            if (jointIdx == i_this->getHeadJntNum()) {
                mDoMtx_stack_c::multVec(&a_att_pos_offst, i_this->getAttPos());
                mDoMtx_stack_c::YrotM(-i_this->getHead_y());
                mDoMtx_stack_c::ZrotM(-i_this->getHead_x());
                mDoMtx_stack_c::multVec(&a_eye_pos_offst, i_this->getEyePos());
            } else if (jointIdx == i_this->getBackboneJntNum()) {
                mDoMtx_stack_c::XrotM(i_this->getBackbone_y());
                mDoMtx_stack_c::ZrotM(-i_this->getBackbone_x());
            }
            cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
            model->setAnmMtx(jointIdx, mDoMtx_stack_c::get());
        }
    }
    return TRUE;
}

/* 000003A4-000004D4       .text createInit__11daNpc_Kp1_cFv */
bool daNpc_Kp1_c::createInit() {
    if (!dComIfGs_isEventBit(0x2D01)) {
        return false;
    }
    mEventCut.setActorInfo2("Kp1", this);
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xAB;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xAB;
    gravity = -4.0f;
    mPreItemNo = 0xFF;
    mLookPos = current.pos;
    set_action(&daNpc_Kp1_c::wait_action1, NULL);
    shape_angle = current.angle;
    mStts.Init(0xFF, 0xFF, this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);
    mpMorf->setMorf(0.0f);
    mUpdateEye = 1;
    setMtx();
    return true;
}

/* 000004D4-00000664       .text setMtx__11daNpc_Kp1_cFv */
void daNpc_Kp1_c::setMtx() {
    if (mDemo == 0) {
        playTexPatternAnm();
        mAnmEnd = mpMorf->play(&eyePos, 0, 0);
        if (mpMorf->getFrame() < mFrame) {
            mAnmEnd = 1;
        }
        mFrame = mpMorf->getFrame();
        mObjAcch.CrrPos(*dComIfG_Bgsp());
    }

    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();

    mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(m_handL_jnt_num));
    mpLetterModel[0]->setBaseTRMtx(mDoMtx_stack_c::get());
    mpLetterModel[0]->calc();
    mpLetterModel[1]->setBaseTRMtx(mDoMtx_stack_c::get());
    mpLetterModel[1]->calc();
    setAttention();
}

/* 00000664-0000075C       .text anmResID__11daNpc_Kp1_cFiPiPi */
bool daNpc_Kp1_c::anmResID(int i_num, int* o_bck_num, int* o_bas_num) {
    static const int a_anm_idx_tbl[6][2] = {
        {dRes_ID_KP_BCK_WAIT01_e, -1},
        {dRes_ID_KP_BCK_HAPPY_e, -1},
        {dRes_ID_KP_BCK_HAND_e, -1},
        {dRes_ID_KP_BCK_READ_e, -1},
        {dRes_ID_KP_BCK_PRAY_e, -1},
        {dRes_ID_KP_BCK_THINK_e, -1},
    };
    JUT_ASSERT(298, 0 <= i_num && i_num < ANM_END);
    JUT_ASSERT(299, o_bck_num && o_bas_num);
    *o_bck_num = a_anm_idx_tbl[i_num][0];
    *o_bas_num = a_anm_idx_tbl[i_num][1];
    return true;
}

/* 0000075C-000007F8       .text BtpNum2ResID__11daNpc_Kp1_cFiPi */
void daNpc_Kp1_c::BtpNum2ResID(int i_num, int* o_btp_num) {
    static const int a_btp_arc_ix_tbl[2] = {dRes_ID_KP_BTP_MABA01_e, dRes_ID_KP_BTP_MABA01_e};
    JUT_ASSERT(0x141, 0 <= i_num && i_num < TEXPATTERN_END);
    *o_btp_num = a_btp_arc_ix_tbl[i_num];
}

/* 000007F8-0000083C       .text setAnm_tex__11daNpc_Kp1_cFSc */
void daNpc_Kp1_c::setAnm_tex(s8 i_param_1) {
    if (i_param_1 >= 0 && i_param_1 != mTexNum) {
        mTexNum = i_param_1;
        initTexPatternAnm(true);
    }
}

/* 0000083C-00000958       .text init_btp__11daNpc_Kp1_cFbi */
bool daNpc_Kp1_c::init_btp(bool param_1, int param_2) {
    int iVar3;
    J3DModelData* pJVar4;

    pJVar4 = mpMorf->getModel()->getModelData();
    if (param_2 >= 0) {
        int btpId;
        BtpNum2ResID(param_2, &btpId);
        J3DAnmTexPattern* pVVar1 = (J3DAnmTexPattern*)dComIfG_getObjectIDRes("Kp", btpId);
        m_head_tex_pattern = pVVar1;
        JUT_ASSERT(0x162, m_head_tex_pattern != NULL);
        iVar3 = mBtpAnm.init(pJVar4, m_head_tex_pattern, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, param_1, FALSE);

        if (iVar3 == 0) {
            return false;
        }
        mBtpFrame = 0;
        mBlinkTimer = 0;
        if (mTexNum == 1) {
            mBtpFrame = 1;
        }
    }
    return true;
}

/* 00000958-0000099C       .text initTexPatternAnm__11daNpc_Kp1_cFb */
bool daNpc_Kp1_c::initTexPatternAnm(bool param_1) {
    bool var_31 = false;
    if (init_btp(param_1, mTexNum)) {
        var_31 = true;
    }
    return var_31;
}

/* 0000099C-00000A68       .text playTexPatternAnm__11daNpc_Kp1_cFv */
void daNpc_Kp1_c::playTexPatternAnm() {
    bool var_r4 = true;
    if (mTexNum == 1) {
        return;
    }
    if (mTexNum == 0) {
        var_r4 = !cLib_calcTimer(&mBlinkTimer);
    }
    if (!var_r4) {
        return;
    }

    if ((mBtpFrame += 1) < m_head_tex_pattern->getFrameMax()) {
        return;
    }

    if (mTexNum) {
        mBtpFrame = m_head_tex_pattern->getFrameMax();
    } else {
        mBtpFrame = 0;
        mBlinkTimer = cM_rndF(60.0) + 30.0f;
    }
}

/* 00000A68-00000B34       .text setAnm_anm__11daNpc_Kp1_cFPQ211daNpc_Kp1_c9anm_prm_c */
s32 daNpc_Kp1_c::setAnm_anm(daNpc_Kp1_c::anm_prm_c* i_anm_ptr) {
    u32 uVar2 = 0;
    int local_18;
    int local_14;

    if (i_anm_ptr->field_0x0 >= 0 && mAnmNum != i_anm_ptr->field_0x0) {
        mAnmNum = i_anm_ptr->field_0x0;
        if (mpMorf != NULL) {
            anmResID(mAnmNum, &local_18, &local_14);
            if (local_18 >= 0) {
                dNpc_setAnmIDRes(mpMorf, i_anm_ptr->field_0xC, i_anm_ptr->field_0x4, i_anm_ptr->field_0x8, local_18,
                                 local_14, "Kp");
            }
            uVar2 = 1;
        }
        mFrame = 0;
        mLoopCount = 0;
        mAnmEnd = 0;
    }
    return uVar2;
}

/* 00000B34-00000BA0       .text setAnm_NUM__11daNpc_Kp1_cFii */
void daNpc_Kp1_c::setAnm_NUM(int i_idx, int i_setTex) {
    static daNpc_Kp1_c::anm_prm_c a_anm_prm_tbl[6] = {
        {ANM_WAIT, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {ANM_HAPPY, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {ANM_HAND, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {ANM_READ, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {ANM_PRAY, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {ANM_THINK, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };
    if (i_setTex != 0) {
        setAnm_tex(a_anm_prm_tbl[i_idx].field_0x1);
    }
    setAnm_anm(&a_anm_prm_tbl[i_idx]);
}

/* 00000BA0-00000C08       .text setAnm__11daNpc_Kp1_cFv */
void daNpc_Kp1_c::setAnm() {
    static daNpc_Kp1_c::anm_prm_c a_anm_prm_tbl[3] = {
        {-1, -1, 0.0f, 0.0f, -1},
        {ANM_WAIT, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {-1, -1, 0.0f, 0.0f, -1},
    };
    setAnm_tex(a_anm_prm_tbl[mStt].field_0x1);
    setAnm_anm(&a_anm_prm_tbl[mStt]);
}

/* 00000C08-00000C14       .text chngAnmTag__11daNpc_Kp1_cFv */
void daNpc_Kp1_c::chngAnmTag() {
    switch (mTag) {
    case 0:
        break;
    }
}

/* 00000C14-00000C20       .text ctrlAnmTag__11daNpc_Kp1_cFv */
void daNpc_Kp1_c::ctrlAnmTag() {
    switch (mAtr) {
    case 0:
        break;
    }
}

/* 00000C20-00000CA4       .text chngAnmAtr__11daNpc_Kp1_cFUc */
void daNpc_Kp1_c::chngAnmAtr(u8 param_1) {
    if (param_1 < 7 && param_1 != mAtr) {
        mItemType = 0;
        if (param_1 == 2) {
            mItemType = 2;
        } else if (param_1 == 3) {
            mItemType = 1;
        }
        mAtr = param_1;
        setAnm_ATR(1);
    }
}

/* 00000CA4-00000D54       .text ctrlAnmAtr__11daNpc_Kp1_cFv */
void daNpc_Kp1_c::ctrlAnmAtr() {
    switch (mAtr) {
    case 0:
        break;
    case 1:
        if (mAnmEnd) {
            if (++mLoopCount >= 2) {
                mAtr = 0;
                setAnm_NUM(0, 1);
            }
        }
        break;
    case 6:
        if (mAnmEnd) {
            if (++mLoopCount >= 1) {
                mAtr = 0;
                setAnm_NUM(0, 1);
            }
        }
        break;
    }
}

/* 00000D54-00000DBC       .text setAnm_ATR__11daNpc_Kp1_cFi */
void daNpc_Kp1_c::setAnm_ATR(int param_1) {
    static daNpc_Kp1_c::anm_prm_c a_anm_prm_tbl[7] = {
        {ANM_WAIT, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {ANM_HAPPY, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {ANM_HAND, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {ANM_READ, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {ANM_PRAY, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {ANM_THINK, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {ANM_HAPPY, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };
    if (param_1 != 0) {
        setAnm_tex(a_anm_prm_tbl[mAtr].field_0x1);
    }
    setAnm_anm(&a_anm_prm_tbl[mAtr]);
}

/* 00000DBC-00000E78       .text anmAtr__11daNpc_Kp1_cFUs */
void daNpc_Kp1_c::anmAtr(u16 i_msgStatus) {
    if (i_msgStatus == fopMsgStts_MSG_TYPING_e) {
        if (mMsgCount == 0) {
            mTag = 0xFF;
            chngAnmAtr(dComIfGp_getMesgAnimeAttrInfo());
            mMsgCount += 1;
        }
        u8 uVar1 = dComIfGp_getMesgAnimeTagInfo();
        if (uVar1 != 0xFF && uVar1 != mTag) {
            dComIfGp_clearMesgAnimeTagInfo();
            mTag = uVar1;
            chngAnmTag();
        }
    } else if (i_msgStatus == fopMsgStts_MSG_DISPLAYED_e) {
        mMsgCount = 0;
    }
    ctrlAnmAtr();
    ctrlAnmTag();
}

/* 00000E78-00000EE0       .text setStt__11daNpc_Kp1_cFSc */
void daNpc_Kp1_c::setStt(s8 param_1) {
    s8 prev = mStt;
    mItemType = 0;
    mStt = param_1;
    switch ((s8)mStt) {
    case 2:
        mLookMode = 1;
        m_jnt.setTrn();
        mAtr = 0xFF;
        mPrevStt = prev;
        mPresentCancel = 0;
        break;
    default:
    case 1:
        setAnm();
        break;
    }
}

/* 00000EE0-0000102C       .text next_msgStatus__11daNpc_Kp1_cFPUl */
u16 daNpc_Kp1_c::next_msgStatus(u32* pMsgNo) {
    u16 status = fopMsgStts_MSG_CONTINUES_e;
    switch (*pMsgNo) {
    case 0x1E84:
        *pMsgNo = 0x1E85;
        break;
    case 0x1E85:
        *pMsgNo = 0x1E86;
        break;
    case 0x1E88:
        *pMsgNo = 0x1E89;
        break;
    case 0x1E8A:
        *pMsgNo = 0x1E8B;
        break;
    case 0x1E8B:
        *pMsgNo = 0x1E8C;
        break;
    case 0x1E8C:
        *pMsgNo = 0x1E8D;
        break;
    case 0x1E8D:
        *pMsgNo = 0x1E8E;
        break;
    case 0x1E8E:
        *pMsgNo = 0x1E8F;
        break;
    case 0x1E8F:
        switch (mpCurrMsg->mSelectNum) {
        case 0:
            *pMsgNo = 0x1E91;
            break;
        case 1:
            *pMsgNo = 0x1E90;
            break;
        }
        break;
    case 0x1E96:
        *pMsgNo = 0x1E97;
        mPresentCancel = 1;
        break;
    case 0x1E97:
        *pMsgNo = 0x1E98;
        break;
    case 0x1E98:
        *pMsgNo = 0x1E99;
        break;
    case 0x1E99:
        *pMsgNo = 0x1E9A;
        break;
    case 0x1E9A:
        *pMsgNo = 0x1E9B;
        break;
    case 0x1E9B:
        *pMsgNo = 0x1E9C;
        break;
    case 0x1E9C:
        *pMsgNo = 0x1E9D;
        break;
    case 0x1E91:
        mOrder = 3;
        goto ends;
    case 0x1E9D:
        mOrder = 4;
        goto ends;
    case 0x1E90:
        mTalkedBefore = 1;
    default:
    ends:
        status = fopMsgStts_MSG_ENDS_e;
        break;
    }
    return status;
}

/* 0000102C-00001174       .text getMsg__11daNpc_Kp1_cFv */
u32 daNpc_Kp1_c::getMsg() {
    if (mPreItemNo != 0xFF) {
        if (mPreItemNo == 0x9B) {
            return 0x1E96;
        }
        return mPreItemNo == 0x45 ? 0x1EA0 : 0x1E9F;
    }
    if (mGotLetter) {
        mGotLetter = 0;
        return 0x1E92;
    }
    if (mGotHeart) {
        mGotHeart = 0;
        return 0x1E9E;
    }
    if (dComIfGs_isGetItemReserve(0xF) && !dComIfGs_checkReserveItem(0x9B)) {
        return dComIfGs_getEventReg(dSv_event_flag_c::UNK_CCFF) >= 1 ? 0x1E83 : 0x1E82;
    }
    if (dComIfGs_isGetItemReserve(0xE)) {
        return dComIfGs_isGetItemBeast(0) ? 0x1E87 : 0x1E88;
    }
    return mTalkedBefore ? 0x1E93 : 0x1E8A;
}

/* 00001174-00001204       .text eventOrder__11daNpc_Kp1_cFv */
void daNpc_Kp1_c::eventOrder() {
    static char* a_demo_name_tbl[] = {
        "GET_MAGYS_LTTR",
        "GET_KAKERA_HRT",
    };

    if (mOrder == 1 || mOrder == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
        if (mOrder == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (mOrder >= 3) {
        fopAcM_orderOtherEvent2(this, a_demo_name_tbl[mOrder - 3], dEvtFlag_NOPARTNER_e);
    }
}

/* 00001204-000012E4       .text checkOrder__11daNpc_Kp1_cFv */
void daNpc_Kp1_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (dComIfGp_evmng_startCheck("GET_MAGYS_LTTR") && mOrder == 3) {
            mOrder = 0;
        } else if (dComIfGp_evmng_startCheck("GET_KAKERA_HRT") && mOrder == 4) {
            mOrder = 0;
        }
    } else if (eventInfo.checkCommandTalk()) {
        if (mOrder == 1 || mOrder == 2) {
            mOrder = 0;
            mTalkReq = 1;
        }
    }
}

/* 000012E4-00001474       .text lookBack__11daNpc_Kp1_cFv */
void daNpc_Kp1_c::lookBack() {
    cXyz vec1;
    cXyz vec2 = current.pos;
    vec2.y = eyePos.y;

    vec1.set(0.0f, 0.0f, 0.0f);

    cXyz* dstPos = NULL;
    s16 targetY = current.angle.y;
    bool headOnlyFollow = mHeadOnlyFollow;
    s8 state = mLookMode;

    switch (state) {
    case 0:
        break;
    case 1:
        vec1 = dNpc_playerEyePos(-20.0);
        dstPos = &vec1;
        vec2 = current.pos;
        vec2.y = eyePos.y;
        break;
    case 2:
        vec1 = mLookPos;
        dstPos = &vec1;
        vec2 = current.pos;
        vec2.y = eyePos.y;
        break;
    case 3:
        targetY = mTargetAngleY;
        break;
    }
    if (m_jnt.trnChk() != 0) {
        cLib_addCalcAngleS2(&mTurnSpeed, l_HIO.mPrmTbl.field_12, 4, 0x800);
    } else {
        mTurnSpeed = 0;
    }
    m_jnt.lookAtTarget(&current.angle.y, dstPos, vec2, targetY, mTurnSpeed, headOnlyFollow);
}

/* 00001474-000014F4       .text chkAttention__11daNpc_Kp1_cFv */
bool daNpc_Kp1_c::chkAttention() {
    dAttention_c& attention = dComIfGp_getAttention();
    if (attention.LockonTruth() != 0) {
        return this == attention.LockonTarget(0);
    } else {
        return this == attention.ActionTarget(0);
    }
}

/* 000014F4-00001558       .text setAttention__11daNpc_Kp1_cFv */
void daNpc_Kp1_c::setAttention() {
    f32 f1 = current.pos.z;
    f32 f2 = current.pos.y + l_HIO.mPrmTbl.mAttentionArrowYOffset;

    attention_info.position.set(current.pos.x, f2, f1);
    if (!mUpdateEye && !mActionRet) {
        return;
    }
    f2 = getEyePos()->z;
    f1 = getEyePos()->y;
    eyePos.set(getEyePos()->x, f1, f2);
    mUpdateEye = 0;
}

/* 00001558-000015F0       .text chk_talk__11daNpc_Kp1_cFv */
bool daNpc_Kp1_c::chk_talk() {
    bool ret = true;
    mPreItemNo = 0xFF;
    if (dComIfGp_event_chkTalkXY()) {
        if (dComIfGp_evmng_ChkPresentEnd()) {
            mPreItemNo = dComIfGp_event_getPreItemNo();
        } else {
            ret = false;
        }
    }
    return ret;
}

/* 000015F0-0000161C       .text decideType__11daNpc_Kp1_cFi */
bool daNpc_Kp1_c::decideType(int) {
    mType = 0xFF;
    switch (fopAcM_GetName(this)) {
    case fpcNm_NPC_KP1_e:
        mType = 0;
        m7DC = 0;
        break;
    }
    return true;
}

/* 0000161C-000016A4       .text event_actionInit__11daNpc_Kp1_cFi */
void daNpc_Kp1_c::event_actionInit(int i_staffIdx) {
    int* puVar1 = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "ActNo");
    dComIfGp_evmng_getMyIntegerP(i_staffIdx, "Timer");
    if (puVar1 != NULL) {
        mActNo = *puVar1;
    }
}

/* 000016A4-00001774       .text event_action__11daNpc_Kp1_cFv */
bool daNpc_Kp1_c::event_action() {
    bool ret = false;
    fpc_ProcID itemId;
    switch (mActNo) {
    case 0:
        itemId = fopAcM_createItemForPresentDemo(&current.pos, 0x9A, 0, -1, -1, NULL, NULL);
        if (itemId != fpcM_ERROR_PROCESS_ID_e) {
            dComIfGp_event_setItemPartnerId(itemId);
            ret = true;
        }
        break;
    case 1:
        itemId = fopAcM_createItemForPresentDemo(&current.pos, 0x07, 0, -1, -1, NULL, NULL);
        if (itemId != fpcM_ERROR_PROCESS_ID_e) {
            dComIfGp_event_setItemPartnerId(itemId);
            ret = true;
        }
        break;
    default:
        ret = true;
        break;
    }
    return ret;
}

/* 00001774-00001880       .text privateCut__11daNpc_Kp1_cFv */
void daNpc_Kp1_c::privateCut() {
    static char* cut_name_tbl[] = {"ACTION"};

    int staffIdx = dComIfGp_evmng_getMyStaffId("Kp1", NULL, 0);
    if (staffIdx != -1) {
        int uVar1 = dComIfGp_evmng_getMyActIdx(staffIdx, cut_name_tbl, ARRAY_SIZE(cut_name_tbl), TRUE, 0);
        mActIdx = uVar1;
        if (mActIdx == -1) {
            dComIfGp_evmng_cutEnd(staffIdx);
            return;
        }
        if (dComIfGp_evmng_getIsAddvance(staffIdx)) {
            switch (mActIdx) {
            case 0:
                event_actionInit(staffIdx);
                break;
            }
        }
        bool bVar1;
        switch (mActIdx) {
        case 0:
            bVar1 = event_action();
            break;
        default:
            bVar1 = 1;
            break;
        }

        if (bVar1) {
            dComIfGp_evmng_cutEnd(staffIdx);
        }
    }
}

/* 00001880-000018A0       .text endEvent__11daNpc_Kp1_cFv */
void daNpc_Kp1_c::endEvent() {
    dComIfGp_event_reset();
    mAtr = 0xFF;
}

/* 000018A0-00001998       .text event_proc__11daNpc_Kp1_cFv */
void daNpc_Kp1_c::event_proc() {
    if (dComIfGp_evmng_endCheck("GET_MAGYS_LTTR")) {
        endEvent();
        mOrder = 1;
        mGotLetter = 1;
    } else if (dComIfGp_evmng_endCheck("GET_KAKERA_HRT")) {
        dComIfGs_setEventReg(dSv_event_flag_c::UNK_CCFF, 0);
        endEvent();
        mOrder = 1;
        mGotHeart = 1;
    } else {
        if (!mEventCut.cutProc()) {
            privateCut();
        }
        lookBack();
    }
    shape_angle = current.angle;
}

/* 00001998-00001A44       .text set_action__11daNpc_Kp1_cFM11daNpc_Kp1_cFPCvPvPv_iPv */
bool daNpc_Kp1_c::set_action(ActionFunc i_action, void* param_2) {
    if (mAction != i_action) {
        if (mAction != 0) {
            mActionState = 0xFF;
            (this->*mAction)(param_2);
        }
        mAction = i_action;
        mActionState = 0;
        (this->*mAction)(param_2);
    }
    return true;
}

/* 00001A44-00001AF8       .text wait01__11daNpc_Kp1_cFv */
BOOL daNpc_Kp1_c::wait01() {
    if (mOrder == 3 || mOrder == 4 || mOrder == 1) {
        return TRUE;
    }
    if (mTalkReq) {
        if (chk_talk()) {
            setStt(2);
        }
    } else {
        mOrder = 2;
        if (mHasAttention) {
            mLookMode = 1;
            m_jnt.setTrn();
        } else {
            mLookMode = 3;
            mTargetAngleY = mHomeAngle.y;
            m_jnt.setTrn();
        }
    }
    return TRUE;
}

/* 00001AF8-00001BCC       .text talk01__11daNpc_Kp1_cFv */
BOOL daNpc_Kp1_c::talk01() {
    talk(1);
    if (mpCurrMsg != NULL) {
        switch (mpCurrMsg->mStatus) {
        case 19:
            switch (mCurrMsgNo) {
            case 0x1E9D:
                dComIfGs_setReserveItemEmpty();
                break;
            }
            mPreItemNo = 0xFF;
            setStt(mPrevStt);
            m7D0 = 0;
            mTalkReq = 0;
            endEvent();
            break;
        case 6:
        case 2:
            if (mPresentCancel) {
                dComIfGp_evmng_CancelPresent();
                mPresentCancel = 0;
            }
            break;
        }
    }
    return TRUE;
}

/* 00001BCC-00001C80       .text wait_action1__11daNpc_Kp1_cFPv */
int daNpc_Kp1_c::wait_action1(void*) {
    if (mActionState == 0) {
        setStt(1);
        mActionState += 1;
    } else if (mActionState != -1) {
        mHasAttention = chkAttention();
        switch (mStt) {
        case 2:
            mActionRet = talk01();
            break;
        case 1:
            mActionRet = wait01();
            break;
        default:
            mActionRet = 0;
            break;
        }
        lookBack();
    }
    return 1;
}

/* 00001C80-00001DB0       .text demo__11daNpc_Kp1_cFv */
u8 daNpc_Kp1_c::demo() {
    if (demoActorID == 0) {
        if (mDemo != 0) {
            mDemo = 0;
        }
    } else {
        mDemo = 1;
        dDemo_actor_c* demoActor = dComIfGp_demo_getActor(demoActorID);
        if (++mBtpFrame >= m_head_tex_pattern->getFrameMax()) {
            mBtpFrame = m_head_tex_pattern->getFrameMax();
        }
        J3DAnmTexPattern* btp = demoActor->getP_BtpData("Kp");
        if (btp != NULL) {
            m_head_tex_pattern = btp;
            if (mBtpAnm.init(mpMorf->getModel()->getModelData(), m_head_tex_pattern, TRUE,
                             J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, FALSE))
            {
                mBtpFrame = 0;
            }
        }
        dDemo_setDemoData(this,
                          dDemo_actor_c::ENABLE_TRANS_e | dDemo_actor_c::ENABLE_ROTATE_e |
                              dDemo_actor_c::ENABLE_ANM_e | dDemo_actor_c::ENABLE_ANM_FRAME_e,
                          mpMorf, "Kp");
    }
    return mDemo;
}

/* 00001DB0-00001E9C       .text shadowDraw__11daNpc_Kp1_cFv */
void daNpc_Kp1_c::shadowDraw() {
    cXyz pos(current.pos.x, current.pos.y + 150.0f, current.pos.z);
    mShadowId = dComIfGd_setShadow(mShadowId, 1, mpMorf->getModel(), &pos, 800.0f, 40.0f, current.pos.y,
                                   mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr, 0, 1.0f,
                                   dDlst_shadowControl_c::getSimpleTex());
    if (mShadowId != 0) {
        switch (mItemType) {
        case 1:
            dComIfGd_addRealShadow(mShadowId, mpLetterModel[0]);
            break;
        case 2:
            dComIfGd_addRealShadow(mShadowId, mpLetterModel[1]);
            break;
        }
    }
}

/* 00001E9C-00001FA4       .text _draw__11daNpc_Kp1_cFv */
BOOL daNpc_Kp1_c::_draw() {
    J3DModel* model = mpMorf->getModel();
    J3DModelData* model_data = model->getModelData();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(model, &tevStr);
    mBtpAnm.entry(model_data, mBtpFrame);
    mpMorf->entryDL();
    mBtpAnm.remove(model_data);

    J3DModel* itemModel;
    switch (mItemType) {
    case 1:
        itemModel = mpLetterModel[0];
        break;
    case 2:
        itemModel = mpLetterModel[1];
        break;
    default:
        itemModel = NULL;
        break;
    }
    if (itemModel != NULL) {
        g_env_light.setLightTevColorType(itemModel, &tevStr);
        mDoExt_modelEntryDL(itemModel);
    }

    shadowDraw();
    dSnap_RegistFig(DSNAP_TYPE_UNK5A, this, 1.0f, 1.0f, 1.0f);

    // Color literals for debug drawing. Unused in non-debug builds.
    (GXColor){0xFF, 0x00, 0x00, 0x80};
    (GXColor){0x00, 0x00, 0xFF, 0x80};

    return TRUE;
}

/* 00001FA4-00002104       .text _execute__11daNpc_Kp1_cFv */
BOOL daNpc_Kp1_c::_execute() {
    if (mInitDone == 0) {
        mHomePos = current.pos;
        mHomeAngle = current.angle;
        mInitDone = 1;
    }
    m_jnt.setParam(l_HIO.mPrmTbl.field_8, l_HIO.mPrmTbl.field_A, l_HIO.mPrmTbl.field_C, l_HIO.mPrmTbl.field_E,
                   l_HIO.mPrmTbl.field_0, l_HIO.mPrmTbl.field_2, l_HIO.mPrmTbl.field_4, l_HIO.mPrmTbl.field_6,
                   l_HIO.mPrmTbl.field_10);
    checkOrder();
    if (demo() == 0) {
        if (dComIfGp_event_runCheck() && !eventInfo.checkCommandTalk()) {
            event_proc();
        } else {
            (this->*mAction)(NULL);
            shape_angle = current.angle;
        }
    }
    eventOrder();
    if (mDemo == 0) {
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
    }
    setMtx();
    setCollision(60.0f, 170.0f);
    return TRUE;
}

/* 00002104-00002154       .text _delete__11daNpc_Kp1_cFv */
BOOL daNpc_Kp1_c::_delete() {
    dComIfG_resDelete(&mPhs, "Kp");
    if (heap != NULL && mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }
    return TRUE;
}

/* 00002154-00002174       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* actor) {
    return ((daNpc_Kp1_c*)actor)->CreateHeap();
}

/* 00002174-000022A0       .text _create__11daNpc_Kp1_cFv */
cPhs_State daNpc_Kp1_c::_create() {
    static int a_heap_size_tbl[] = {
        0x272E0,
    };

    fopAcM_ct(this, daNpc_Kp1_c);

    cPhs_State ret = dComIfG_resLoad(&mPhs, "Kp");
    if (ret != cPhs_COMPLEATE_e) {
        return ret;
    }
    if (!decideType(fopAcM_GetParam(this) & 0xFF)) {
        return cPhs_ERROR_e;
    }
    if (fopAcM_entrySolidHeap(this, CheckCreateHeap, a_heap_size_tbl[mType])) {
        fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
        fopAcM_setCullSizeBox(this, -50.0f, -20.0f, -50.0f, 50.0f, 170.0f, 50.0f);
    } else {
        return cPhs_ERROR_e;
    }
    if (!createInit()) {
        ret = cPhs_ERROR_e;
    }
    return ret;
}

/* 0000270C-00002B10       .text CreateHeap__11daNpc_Kp1_cFv */
BOOL daNpc_Kp1_c::CreateHeap() {
    static u8 a_tex_pattern_num_tbl[1] = {TEXPATTERN_MABA};
    J3DModelData* a_mdl_data;

    a_mdl_data = (J3DModelData*)dComIfG_getObjectIDRes("Kp", dRes_ID_KP_BDL_KP_e);
    JUT_ASSERT(0x62C, a_mdl_data != NULL);
    mpMorf = new mDoExt_McaMorf(
        a_mdl_data, NULL, NULL, (J3DAnmTransform*)dComIfG_getObjectIDRes("Kp", dRes_ID_KP_BCK_WAIT01_e),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, NULL, 0x80000, 0x11020002
    );
    if (mpMorf) {
        if (mpMorf->getModel()) {
            m_head_jnt_num = a_mdl_data->getJointName()->getIndex("head");
            JUT_ASSERT(0x63F, m_head_jnt_num >= 0);
            m_backbone_jnt_num = a_mdl_data->getJointName()->getIndex("backbone");
            JUT_ASSERT(0x641, m_backbone_jnt_num >= 0);
            m_handL_jnt_num = a_mdl_data->getJointName()->getIndex("handL");
            JUT_ASSERT(0x643, m_handL_jnt_num >= 0);
            mTexNum = a_tex_pattern_num_tbl[mType];
            if (initTexPatternAnm(false) != 0) {
                J3DModelData* a_itm_mdl_data = (J3DModelData*)dComIfG_getObjectIDRes("Kp", dRes_ID_KP_BDL_LT_01_e);
                JUT_ASSERT(0x655, a_itm_mdl_data != NULL);
                mpLetterModel[0] = mDoExt_J3DModel__create(a_itm_mdl_data, 0x80000, 0x11000002);
                if (mpLetterModel[0] != NULL) {
                    a_itm_mdl_data = (J3DModelData*)dComIfG_getObjectIDRes("Kp", dRes_ID_KP_BDL_LT_02_e);
                    JUT_ASSERT(0x65F, a_itm_mdl_data != NULL);
                    mpLetterModel[1] = mDoExt_J3DModel__create(a_itm_mdl_data, 0x80000, 0x11000002);
                    if (mpLetterModel[1] != NULL) {
                        for (u16 i = 0; i < a_mdl_data->getJointNum(); i += 1) {
                            if ((i == m_head_jnt_num) || (i == m_backbone_jnt_num)) {
                                mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Kp);
                            }
                        }
                        mpMorf->getModel()->setUserArea((uintptr_t)this);
                        mAcchCir.SetWall(30.0f, 60.0f);
                        mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir,
                                     fopAcM_GetSpeed_p(this));
                        return TRUE;
                    }
                }
            }
        }
        mpMorf = NULL;
    }
    return FALSE;
}

/* 00002B10-00002B30       .text daNpc_Kp1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Kp1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Kp1_c*)i_this)->_create();
}

/* 00002B30-00002B50       .text daNpc_Kp1_Delete__FP11daNpc_Kp1_c */
static BOOL daNpc_Kp1_Delete(daNpc_Kp1_c* i_this) {
    return ((daNpc_Kp1_c*)i_this)->_delete();
}

/* 00002B50-00002B70       .text daNpc_Kp1_Execute__FP11daNpc_Kp1_c */
static BOOL daNpc_Kp1_Execute(daNpc_Kp1_c* i_this) {
    return ((daNpc_Kp1_c*)i_this)->_execute();
}

/* 00002B70-00002B90       .text daNpc_Kp1_Draw__FP11daNpc_Kp1_c */
static BOOL daNpc_Kp1_Draw(daNpc_Kp1_c* i_this) {
    return ((daNpc_Kp1_c*)i_this)->_draw();
}

/* 00002B90-00002B98       .text daNpc_Kp1_IsDelete__FP11daNpc_Kp1_c */
static BOOL daNpc_Kp1_IsDelete(daNpc_Kp1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Kp1_Method = {
    (process_method_func)daNpc_Kp1_Create,
    (process_method_func)daNpc_Kp1_Delete,
    (process_method_func)daNpc_Kp1_Execute,
    (process_method_func)daNpc_Kp1_IsDelete,
    (process_method_func)daNpc_Kp1_Draw,
};

actor_process_profile_definition g_profile_NPC_KP1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_KP1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Kp1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_KP1_e,
    /* Actor SubMtd */ &l_daNpc_Kp1_Method,
    /* Status       */ 0x08 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
