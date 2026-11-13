/**
 * d_a_npc_pf1.cpp
 * NPC - Maggie's Father (poor)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_pf1.h"
#include "d/actor/d_a_tama.h"
#include "d/d_com_inf_game.h"
#include "d/d_snap.h"
#include "c/c_dylink.h"
#include "f_op/f_op_msg_mng.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"
#include "m_Do/m_Do_lib.h"
#include "res/Object/Pf.h"
#include "SSystem/SComponent/c_counter.h"

class daNpc_Pf1_HIO_c : public mDoHIO_entry_c {
public:
    struct hio_prm_c {
        /* 0x00 */ s16 mMaxHeadX;
        /* 0x02 */ s16 mMaxHeadY;
        /* 0x04 */ s16 mMinHeadX;
        /* 0x06 */ s16 mMinHeadY;
        /* 0x08 */ s16 mMaxBackBoneX;
        /* 0x0A */ s16 mMaxBackBoneY;
        /* 0x0C */ s16 mMinBackBoneX;
        /* 0x0E */ s16 mMinBackBoneY;
        /* 0x10 */ s16 mMaxTurnStep;
        /* 0x12 */ s16 mMaxHeadTurnVel;
        /* 0x14 */ f32 mAttPosOffsetY;
        /* 0x18 */ u8 m18;
        /* 0x1A */ s16 mWalkTurnScale;
        /* 0x1C */ s16 mWalkTurnMaxStep;
        /* 0x20 */ f32 mWalkAnmRate;
        /* 0x24 */ f32 mWalkSpeed;
        /* 0x28 */ f32 mWalkAccel;
        /* 0x2C */ f32 mAttkAnmRate;
        /* 0x30 */ f32 mAttkSpeed;
        /* 0x34 */ f32 mAttkAccel;
        /* 0x38 */ f32 mAttkStartDist;
        /* 0x3C */ f32 mAttkEndDist;
    };  // Size: 0x40

    daNpc_Pf1_HIO_c();
    virtual ~daNpc_Pf1_HIO_c() {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ int m08;
    /* 0x0C */ hio_prm_c mPrm;
};  // Size: 0x4C

static daNpc_Pf1_HIO_c l_HIO;
static fopAc_ac_c* l_check_inf[20];
static int l_check_wrk;

/* 000000EC-00000150       .text __ct__15daNpc_Pf1_HIO_cFv */
daNpc_Pf1_HIO_c::daNpc_Pf1_HIO_c() {
    static hio_prm_c a_prm_tbl = {
        /* mMaxHeadX        */ 0x2000,
        /* mMaxHeadY        */ 0x38E0,
        /* mMinHeadX        */ -0x1388,
        /* mMinHeadY        */ -0x38E0,
        /* mMaxBackBoneX    */ 0x0000,
        /* mMaxBackBoneY    */ 0x1C70,
        /* mMinBackBoneX    */ 0x0000,
        /* mMinBackBoneY    */ -0x1C70,
        /* mMaxTurnStep     */ 0x0400,
        /* mMaxHeadTurnVel  */ 0x0400,
        /* mAttPosOffsetY   */ 70.0f,
        /* m18              */ 0,
        /* mWalkTurnScale   */ 8,
        /* mWalkTurnMaxStep */ 0x0400,
        /* mWalkAnmRate     */ 1.0f,
        /* mWalkSpeed       */ 0.9f,
        /* mWalkAccel       */ 0.3f,
        /* mAttkAnmRate     */ 0.2f,
        /* mAttkSpeed       */ 9.5f,
        /* mAttkAccel       */ 0.6f,
        /* mAttkStartDist   */ 900.0f,
        /* mAttkEndDist     */ 1050.0f,
    };
    memcpy(&mPrm, &a_prm_tbl, sizeof(hio_prm_c));
    mNo = -1;
    m08 = -1;
}

static const char* l_evn_tbl[] = {
    "dummy",
};

/* .text nodeCB_Head */
static BOOL nodeCB_Head(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In && j3dSys.getModel()->getUserArea() != 0) {
        daNpc_Pf1_c* actor_p = (daNpc_Pf1_c*)j3dSys.getModel()->getUserArea();
        actor_p->_nodeCB_Head(i_node, j3dSys.getModel());
    }
    return TRUE;
}

/* .text _nodeCB_Head__11daNpc_Pf1_cFP7J3DNodeP8J3DModel */
void daNpc_Pf1_c::_nodeCB_Head(J3DNode* i_node, J3DModel* i_model) {
    static cXyz a_eye_pos_off(20.0f, -30.0f, 0.0f);

    J3DJoint* jnt_p = (J3DJoint*)i_node;
    s32 jnt_no = jnt_p->getJntNo();

    mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));

    mHeadPos.x = mDoMtx_stack_c::get()[0][3];
    mHeadPos.y = mDoMtx_stack_c::get()[1][3];
    mHeadPos.z = mDoMtx_stack_c::get()[2][3];

    mDoMtx_stack_c::multVec(&a_eye_pos_off, &mTransformedEyePos);
    mDoMtx_stack_c::YrotM(-m_jnt.getHead_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());

    mDoMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    i_model->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* .text nodeCB_BackBone */
static BOOL nodeCB_BackBone(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In && j3dSys.getModel()->getUserArea() != 0) {
        daNpc_Pf1_c* actor_p = (daNpc_Pf1_c*)j3dSys.getModel()->getUserArea();
        actor_p->_nodeCB_BackBone(i_node, j3dSys.getModel());
    }
    return TRUE;
}

/* .text _nodeCB_BackBone */
void daNpc_Pf1_c::_nodeCB_BackBone(J3DNode* i_node, J3DModel* i_model) {
    J3DJoint* jnt_p = (J3DJoint*)i_node;
    s32 jnt_no = jnt_p->getJntNo();

    mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));
    mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
    mDoMtx_stack_c::ZrotM(m_jnt.getBackbone_x());

    mDoMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* .text CheckCreateHeap */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Pf1_c*)i_this)->CreateHeap();
}

/* .text init_KF1_0 */
bool daNpc_Pf1_c::init_PF1_0() {
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2D01)) {
        set_action(&daNpc_Pf1_c::wait_action1, NULL);
        return true;
    }
    return false;
}

/* .text createInit__11daNpc_Pf1_cFv */
bool daNpc_Pf1_c::createInit() {
    mEventIDTbl[0] = dComIfGp_evmng_getEventIdx(l_evn_tbl[0]);
    mEventCut.setActorInfo2("Pf1", this);

    int weight = 0xFF;
    u8 path_no = (fopAcM_GetParam(this) >> 16) & 0xFF;
    if (path_no != 0xFF) {
        mPath.setInf(path_no, fopAcM_GetRoomNo(this), true);
        if (mPath.isPath()) {
            fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
            weight = 0xD9;
            set_pthPoint(0);
        } else {
            return false;
        }
    }
    if (!mPath.isPath()) {
        return false;
    }

    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;

    switch (mType) {
    case 0:
        break;
    }

    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xA9;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xA9;
    gravity = -4.5f;
    mBckNum = BCKNUM_NULL_e;

    bool init_result;
    switch (mType) {
    case 0:
        init_result = init_PF1_0();
        break;
    default:
        init_result = false;
        break;
    }

    if (!init_result) {
        return false;
    }

    mAngle = current.angle;
    shape_angle = mAngle;

    mStts.Init(weight, 0xFF, this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);

    mObjAcch.CrrPos(*dComIfG_Bgsp());
    play_animation();

    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    mpMorf->setMorf(0.0f);
    setMtx(true);

    return true;
}

/* .text play_animation */
void daNpc_Pf1_c::play_animation() {
    u32 snd_id = 0;

    play_btp_anm();

    if (mObjAcch.ChkGroundHit()) {
        snd_id = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
    }

    mbMorfAnimStopped = mpMorf->play(&eyePos, snd_id, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));

    if (mpMorf->getFrame() < mPrevMorfFrame) {
        mbMorfAnimStopped = true;
    }

    mPrevMorfFrame = mpMorf->getFrame();
}

/* .text setMtx__11daNpc_Pf1_cFb */
void daNpc_Pf1_c::setMtx(bool i_setEyePos) {
    mpMorf->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(mAngle);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());

    mpMorf->calc();
    setAttention(i_setEyePos);
}

/* .text bckResID__11daNpc_Pf1_cFi */
int daNpc_Pf1_c::bckResID(int i_bckNum) {
    static const int a_resID_tbl[] = {
        dRes_ID_PF_BCK_WAIT01_e,
        dRes_ID_PF_BCK_WALK01_e,
        dRes_ID_PF_BCK_WALK02_e,
        dRes_ID_PF_BCK_CRY_e,
        dRes_ID_PF_BCK_REGRET_e,
        dRes_ID_PF_BCK_SPIT_e,
        dRes_ID_PF_BCK_WISH_e,
        dRes_ID_PF_BCK_TALK01_e,
    };
    return a_resID_tbl[i_bckNum];
}

/* .text btpResID__11daNpc_Pf1_cFi */
int daNpc_Pf1_c::btpResID(int i_btpNum) {
    static const int a_resID_tbl[] = {
        dRes_ID_PF_BTP_MABA01_e,
        dRes_ID_PF_BTP_MABA01_e,
    };
    return a_resID_tbl[i_btpNum];
}

/* .text setBtp__11daNpc_Pf1_cFScb */
bool daNpc_Pf1_c::setBtp(s8 i_btpNum, bool i_bModify) {
    J3DModel* morf_model_p = mpMorf->getModel();

    if (i_btpNum < 0) {
        return false;
    }

    J3DAnmTexPattern* a_btp = (J3DAnmTexPattern*)dComIfG_getObjectIDRes(mArcName, btpResID(i_btpNum));
    JUT_ASSERT(0x1CE, a_btp != NULL);
    mBtpNum = i_btpNum;
    if (mBtpNum == BTPNUM_MABA02_e) {
        mBtpFrame = 2;
    } else {
        mBtpFrame = 0;
    }
    mBlinkTimer = 0;

    return mBtpAnm.init(morf_model_p->getModelData(), a_btp, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, i_bModify, 0) != 0;
}

/* .text init_texPttrnAnm */
bool daNpc_Pf1_c::init_texPttrnAnm(s8 i_btpNum, bool i_bModify) {
    return setBtp(i_btpNum, i_bModify);
}

/* .text play_btp_anm__11daNpc_Pf1_cFv */
void daNpc_Pf1_c::play_btp_anm() {
    u8 frame_max = mBtpAnm.getBtpAnm()->getFrameMax();
    if (mBtpNum == BTPNUM_MABA02_e) {
        return;
    }
    if (mBtpNum != BTPNUM_MABA01_e || cLib_calcTimer(&mBlinkTimer) == 0) {
        mBtpFrame++;
        if (mBtpFrame >= frame_max) {
            if (mBtpNum != BTPNUM_MABA01_e) {
                mBtpFrame = frame_max;
            } else {
                mBlinkTimer = cLib_getRndValue(60, 90);
                mBtpFrame = 0;
            }
        }
    }
}

/* .text setAnm_anm */
void daNpc_Pf1_c::setAnm_anm(anm_prm_c* i_anmPrmP) {
    if (i_anmPrmP->bckNum < 0 || mBckNum == i_anmPrmP->bckNum) {
        return;
    }

    dNpc_setAnmIDRes(mpMorf, i_anmPrmP->loopMode, i_anmPrmP->morf, i_anmPrmP->speed, bckResID(i_anmPrmP->bckNum), -1, mArcName);
    mBckNum = i_anmPrmP->bckNum;
    mbMorfAnimStopped = false;
    mLoopCount = 0;
    mPrevMorfFrame = 0.0f;
}

/* .text setAnm_NUM__11daNpc_Pf1_cFii */
void daNpc_Pf1_c::setAnm_NUM(int i_anmNum, int i_setBtp) {
    static anm_prm_c a_anm_prm_tbl[8] = {
        {BCKNUM_WAIT01_e, BTPNUM_MABA01_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_WALK01_e, BTPNUM_MABA01_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_WALK02_e, BTPNUM_MABA01_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_CRY_e, BTPNUM_MABA02_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_REGRET_e, BTPNUM_MABA01_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {BCKNUM_SPIT_e, BTPNUM_MABA01_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {BCKNUM_WISH_e, BTPNUM_MABA01_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_TALK01_e, BTPNUM_MABA01_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };

    if (i_setBtp) {
        init_texPttrnAnm(a_anm_prm_tbl[i_anmNum].btpNum, true);
    }
    setAnm_anm(&a_anm_prm_tbl[i_anmNum]);
}

/* .text setAnm__11daNpc_Pf1_cFv */
void daNpc_Pf1_c::setAnm() {
    static anm_prm_c a_anm_prm_tbl[8] = {
        {-1, -1, 0.0f, 0.0f, J3DFrameCtrl::EMode_NULL},
        {BCKNUM_WAIT01_e, BTPNUM_MABA01_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {-1, -1, 0.0f, 0.0f, J3DFrameCtrl::EMode_NULL},
        {BCKNUM_WALK01_e, BTPNUM_MABA01_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_REGRET_e, BTPNUM_MABA01_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {BCKNUM_WAIT01_e, BTPNUM_MABA01_e, 4.0f, 0.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_WAIT01_e, BTPNUM_MABA01_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_WAIT01_e, BTPNUM_MABA01_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };

    init_texPttrnAnm(a_anm_prm_tbl[mStt].btpNum, true);
    setAnm_anm(&a_anm_prm_tbl[mStt]);
}

/* .text chngAnmTag */
void daNpc_Pf1_c::chngAnmTag() {
}

/* .text ctrlAnmTag */
void daNpc_Pf1_c::ctrlAnmTag() {
}

/* .text chngAnmAtr__11daNpc_Pf1_cFUc */
void daNpc_Pf1_c::chngAnmAtr(u8 i_atr) {
    if (i_atr == mAnmAtr || i_atr > 6) {
        return;
    }
    mAnmAtr = i_atr;
    setAnm_ATR();
}

/* .text ctrlAnmAtr__11daNpc_Pf1_cFv */
void daNpc_Pf1_c::ctrlAnmAtr() {
    switch (mAnmAtr) {
    case 3:
        break;
    case 5:
        break;
    case 4:
        if (mbMorfAnimStopped) {
            if (++mLoopCount > 2) {
                mAnmAtr = 6;
                setAnm_NUM(0, 1);
            }
        }
        break;
    }
}

/* .text setAnm_ATR__11daNpc_Pf1_cFv */
void daNpc_Pf1_c::setAnm_ATR() {
    static anm_prm_c a_anm_prm_tbl[6] = {
        {BCKNUM_WAIT01_e, BTPNUM_MABA01_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_CRY_e, BTPNUM_MABA02_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_SPIT_e, BTPNUM_MABA01_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {BCKNUM_WISH_e, BTPNUM_MABA01_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_WISH_e, BTPNUM_MABA01_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_TALK01_e, BTPNUM_MABA01_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };

    init_texPttrnAnm(a_anm_prm_tbl[mAnmAtr].btpNum, true);
    setAnm_anm(&a_anm_prm_tbl[mAnmAtr]);
}

/* .text anmAtr */
void daNpc_Pf1_c::anmAtr(u16 i_msgStatus) {
    u8 mesg_anime_tag;
    switch (i_msgStatus) {
    case fopMsgStts_MSG_TYPING_e:
        if (mMsgCount == 0) {
            chngAnmAtr(dComIfGp_getMesgAnimeAttrInfo());
            mMsgCount++;
        }
        mesg_anime_tag = dComIfGp_getMesgAnimeTagInfo();
        if (mesg_anime_tag != 0xFF && mesg_anime_tag != mMesgAnimeTag) {
            dComIfGp_setMesgAnimeTagInfo(0xFF);
            mMesgAnimeTag = mesg_anime_tag;
            chngAnmTag();
        }
        break;
    case fopMsgStts_MSG_DISPLAYED_e:
        mMsgCount = 0;
        break;
    default:
        break;
    }
    ctrlAnmAtr();
    ctrlAnmTag();
}

/* .text next_msgStatus__11daNpc_Pf1_cFPUl */
u16 daNpc_Pf1_c::next_msgStatus(u32* o_msgNoP) {
    u16 msg_status = fopMsgStts_MSG_CONTINUES_e;
    switch (*o_msgNoP) {
    case 0x1B59:
        switch (mpCurrMsg->mSelectNum) {
        case 0:
            *o_msgNoP = 0x1B5A;
            break;
        case 1:
            *o_msgNoP = 0x1B5D;
            break;
        }
        mbTalked = true;
        break;
    case 0x1B5A:
        *o_msgNoP = 0x1B61;
        break;
    case 0x1B61:
        *o_msgNoP = 0x1B5B;
        break;
    case 0x1B5B:
        *o_msgNoP = 0x1B62;
        break;
    case 0x1B62:
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_0B04);
        msg_status = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x1B60:
        m7A4 = true;
        msg_status = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x1B5C:
        *o_msgNoP = 0x1B5F;
        break;
    case 0x1B5E:
        *o_msgNoP = 0x1B60;
        break;
    default:
        msg_status = fopMsgStts_MSG_ENDS_e;
        break;
    }
    return msg_status;
}

/* .text getMsg_PF1_0__11daNpc_Pf1_cFv */
u32 daNpc_Pf1_c::getMsg_PF1_0() {
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B04)) {
        return 0x1B5C;
    }
    return mbTalked ? 0x1B5E : 0x1B59;
}

/* .text getMsg */
u32 daNpc_Pf1_c::getMsg() {
    u32 result = 0;
    switch (mType) {
    case 0:
        result = getMsg_PF1_0();
        break;
    }
    return result;
}

/* .text eventOrder */
void daNpc_Pf1_c::eventOrder() {
    if (mOrder == 1 || mOrder == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (mOrder == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (mOrder >= 3) {
        mEventIndex = mOrder - 3;
        fopAcM_orderOtherEventId(this, mEventIDTbl[mEventIndex]);
    }
}

/* .text checkOrder */
void daNpc_Pf1_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (dComIfGp_evmng_startCheck(mEventIDTbl[mEventIndex]) && mOrder >= 3) {
            switch (mEventIndex) {
            case 0:
                break;
            }
            mOrder = 0;
            mAnmAtr = 0xFF;
            mMesgAnimeTag = 0xFF;
        }
        return;
    }
    if (eventInfo.checkCommandTalk()) {
        if (mOrder == 1 || mOrder == 2) {
            mOrder = 0;
            mbTalkReq = true;
        }
    }
}

/* .text chk_talk */
bool daNpc_Pf1_c::chk_talk() {
    if (dComIfGp_event_chkTalkXY()) {
        if (dComIfGp_evmng_ChkPresentEnd()) {
            mItemNo = dComIfGp_event_getPreItemNo();
            return true;
        }
        return false;
    }

    mItemNo = 0xFF;
    return true;
}

/* .text chk_parts_notMov */
bool daNpc_Pf1_c::chk_parts_notMov() {
    return mJointHeadY != m_jnt.getHead_y() ||
        mJointBackboneY != m_jnt.getBackbone_y() ||
        mActorAngleY != current.angle.y;
}

/* .text searchByID */
fopAc_ac_c* daNpc_Pf1_c::searchByID(fpc_ProcID i_PID, int* o_notFound) {
    fopAc_ac_c* actor_p;

    actor_p = NULL;
    *o_notFound = 0;
    if (!fopAcM_SearchByID(i_PID, &actor_p)) {
        *o_notFound = 1;
    }

    return actor_p;
}

/* .text lookBack */
void daNpc_Pf1_c::lookBack() {
    cXyz player_eye_pos;
    cXyz current_pos;

    mJointHeadY = m_jnt.getHead_y();
    mJointBackboneY = m_jnt.getBackbone_y();
    mActorAngleY = current.angle.y;

    current_pos = current.pos;
    current_pos.y = eyePos.y;

    player_eye_pos.set(0.0f, 0.0f, 0.0f);

    cXyz* player_eye_pos_p = NULL;
    s16 target_y = current.angle.y;
    bool head_only = m7AF;

    switch (mLookMode) {
    case 1:
        mPlayerEyePos = dNpc_playerEyePos(-20.0f);
        player_eye_pos = mPlayerEyePos;
        player_eye_pos_p = &player_eye_pos;
        break;
    case 2:
        player_eye_pos = mPlayerEyePos;
        player_eye_pos_p = &player_eye_pos;
        break;
    case 3:
        target_y = mTargetAngleY;
        break;
    case 4: {
        int not_found;
        fopAc_ac_c* actor_p = searchByID(mPartnerID, &not_found);
        if (actor_p && not_found == 0) {
            mPlayerEyePos = actor_p->current.pos;
            mPlayerEyePos.y = actor_p->eyePos.y;
            player_eye_pos = mPlayerEyePos;
            player_eye_pos_p = &player_eye_pos;
        }
        break;
    }
    }

    m_jnt.lookAtTarget_2(&current.angle.y, player_eye_pos_p, current_pos, target_y, l_HIO.mPrm.mMaxHeadTurnVel, head_only);
}

/* .text chkAttention */
bool daNpc_Pf1_c::chkAttention() {
    dAttention_c& attention = dComIfGp_getAttention();
    if (attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    } else {
        return this == attention.ActionTarget(0);
    }
}

/* .text setAttention__11daNpc_Pf1_cFb */
void daNpc_Pf1_c::setAttention(bool i_setEyePos) {
    attention_info.position.set(mHeadPos.x, mHeadPos.y + l_HIO.mPrm.mAttPosOffsetY, mHeadPos.z);

    if (!mbSetEyePos && !i_setEyePos) {
        return;
    }

    eyePos.set(mTransformedEyePos.x, mTransformedEyePos.y, mTransformedEyePos.z);
}

/* .text decideType */
bool daNpc_Pf1_c::decideType(int i_type) {
    if (m7BB > 0) {
        return true;
    }

    m7BB = 1;
    mType = 0;

    strcpy(mArcName, "Pf");
    return m7BB != -1 && mType != -1;
}

/* .text privateCut */
void daNpc_Pf1_c::privateCut(int i_staffIdx) {
    static char* a_cut_tbl[] = {
        "DUMMY",
    };

    if (i_staffIdx == -1) {
        return;
    }

    mActionIndex = dComIfGp_evmng_getMyActIdx(i_staffIdx, a_cut_tbl, ARRAY_SSIZE(a_cut_tbl), TRUE, 0);

    if (mActionIndex == -1) {
        dComIfGp_evmng_cutEnd(i_staffIdx);
        return;
    }

    dComIfGp_evmng_getIsAddvance(i_staffIdx);
    dComIfGp_evmng_cutEnd(i_staffIdx);
}

/* .text endEvent */
void daNpc_Pf1_c::endEvent() {
    dComIfGp_event_reset();
    mAnmAtr = 0xFF;
    mMesgAnimeTag = 0xFF;
}

/* .text isEventEntry */
int daNpc_Pf1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName());
}

/* .text event_proc */
void daNpc_Pf1_c::event_proc(int i_staffIdx) {
    if (dComIfGp_evmng_endCheck(mEventIDTbl[mEventIndex])) {
        switch (mEventIndex) {
        case 0:
            break;
        }
        endEvent();
    } else {
        if (mEventCut.cutProc()) {
            return;
        }
        privateCut(i_staffIdx);
    }
}

/* .text set_action */
BOOL daNpc_Pf1_c::set_action(ProcFunc i_newProcFunc, void* i_argsP) {
    if (mCurrProcFunc != i_newProcFunc) {
        if (mCurrProcFunc) {
            mActionState = 9;
            (this->*mCurrProcFunc)(i_argsP);
        }
        mCurrProcFunc = i_newProcFunc;
        mActionState = 0;
        (this->*mCurrProcFunc)(i_argsP);
    }
    return TRUE;
}

/* .text setStt__11daNpc_Pf1_cFSc */
void daNpc_Pf1_c::setStt(s8 i_stt) {
    u8 prev_stt = mStt;
    mStt = i_stt;
    switch (mStt) {
    case 0:
        break;
    case 1:
    case 4:
    case 6:
    case 7:
        mOrder = 0;
        speedF = 0.0f;
        break;
    case 2:
        mOrder = 0;
        speedF = 0.0f;
        mAnmAtr = 0xFF;
        mMesgAnimeTag = 0xFF;
        mMsgCount = 0;
        mPrevStt = prev_stt;
        break;
    case 3:
        mOrder = 0;
        mTimer = cLib_getRndValue(180, 90);
        break;
    case 5:
        mOrder = 0;
        mAttkTimer = 30;
        mTimer = 0;
        break;
    }
    setAnm();
}

/* .text createTama__11daNpc_Pf1_cFf */
void daNpc_Pf1_c::createTama(f32 i_dis) {
    csXyz a_angle(0, 0, 0);
    cXyz a_target;
    cXyz a_pos = eyePos;
    a_pos.y = 15.0f + eyePos.y;
    a_target = dNpc_playerEyePos(-20.0f);
    f32 dist = (a_target - eyePos).absXZ();

    a_angle.y = cLib_targetAngleY(&a_pos, &a_target);
    a_angle.x = cLib_targetAngleX(&a_pos, &a_target);

    daTama_c* a_tama = (daTama_c*)fopAcM_fastCreate(fpcNm_TAMA_e, 0, &eyePos, fopAcM_GetRoomNo(this), &a_angle);
    if (a_tama != NULL) {
        a_tama->setPartnerID(fopAcM_GetID(this));
        a_tama->setDis(i_dis);
        a_tama->setSpd(50.0f);
    }
}

/* .text chk_areaIN__11daNpc_Pf1_cFf4cXyz */
bool daNpc_Pf1_c::chk_areaIN(f32 i_dis, cXyz i_pos) {
    f32 dist = (dComIfGp_getLinkPlayer()->current.pos - i_pos).absXZ();
    bool ret = dist < i_dis;
    if (ret && g_Counter.mCounter0 % 3 == 0) {
        createTama(i_dis);
    }
    return ret;
}

/* .text endEvent_check__11daNpc_Pf1_cFv */
bool daNpc_Pf1_c::endEvent_check() {
    if (mbTalked) {
        return !dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B04);
    }
    return false;
}

/* .text startEvent_check__11daNpc_Pf1_cFv */
bool daNpc_Pf1_c::startEvent_check() {
    cXyz pos(mHomePos.x, 100.0f + mHomePos.y, mHomePos.z);
    if (chk_areaIN(l_HIO.mPrm.mAttkStartDist, pos)) {
        f32 dist = current.pos.abs(dComIfGp_getLinkPlayer()->current.pos);
        if (dist < 210.0f || field_0x6ba != 0) {
            return true;
        }
    }
    return false;
}

/* .text set_pthPoint */
void daNpc_Pf1_c::set_pthPoint(u8 i_idx) {
    if (mPath.isPath()) {
        mPath.setIdx(i_idx);
        current.pos = mPath.getPoint(mPath.getIdx());
        if (mPath.nextIdx()) {
            cXyz next = mPath.getPoint(mPath.getIdx());
            current.angle.y = cLib_targetAngleY(&current.pos, &next);
        }
    }
}

/* .text chk_attn */
static inline bool chk_xz(f32 dist, s16 angle, f32 max_angle) {
    bool ret = false;
    if (dist < 200.0f && abs(angle) / 182.04445f < max_angle) {
        ret = true;
    }
    return ret;
}

static inline bool chk_area(f32 dist, f32 dy, s16 angle, f32 max_angle) {
    bool ret = false;
    if (chk_xz(dist, angle, max_angle) && std::fabsf(dy) < 300.0f) {
        ret = true;
    }
    return ret;
}

bool daNpc_Pf1_c::chk_attn() {
    f32 dist = (current.pos - dComIfGp_getLinkPlayer()->current.pos).absXZ();
    f32 dy = current.pos.y - dComIfGp_getLinkPlayer()->current.pos.y;
    s16 angle = cLib_targetAngleY(&current.pos, &dComIfGp_getLinkPlayer()->current.pos) - current.angle.y;

    if (mLookMode == 1) {
        return chk_area(dist, dy, angle, 90.0f);
    }
    return chk_area(dist, dy, angle, 60.0f);
}

/* .text setBikon__11daNpc_Pf1_cF4cXyz */
void daNpc_Pf1_c::setBikon(cXyz i_offset) {
    cXyz pos;
    delBikon();
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mDoMtx_stack_c::multVec(&i_offset, &pos);
    dComIfGp_particle_set(dPa_name::ID_IT_SN_PF_BIKON00, &pos);
}

/* .text delBikon__11daNpc_Pf1_cFv */
void daNpc_Pf1_c::delBikon() {
}

/* .text wait_1__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::wait_1() {
    return TRUE;
}

/* .text regret__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::regret() {
    if (mbTalkReq) {
        if (chk_talk()) {
            setStt(2);
        }
        return TRUE;
    }

    if (!endEvent_check()) {
        mOrder = 0;
        if (startEvent_check()) {
            setStt(5);
        }
    } else {
        mOrder = 2;
    }

    mLookMode = 0;
    m7AF = true;
    if (mbMorfAnimStopped) {
        setStt(3);
    }
    return TRUE;
}

/* .text attk_1__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::attk_1() {
    f32 dist = (current.pos - dComIfGp_getLinkPlayer()->current.pos).absXZ();

    if (mbTalkReq) {
        if (chk_talk()) {
            setStt(6);
            setStt(2);
        }
        return TRUE;
    }

    mLookMode = 0;
    m7AF = true;

    if (mBckNum == BCKNUM_WAIT01_e) {
        if (mTimer == 0) {
            s16 angle = cLib_targetAngleY(&current.pos, &dComIfGp_getLinkPlayer()->current.pos);
            cLib_addCalcAngleS(&current.angle.y, angle, 4, 0x1000, 0x80);
            if (abs((s16)(current.angle.y - angle)) < 0x800) {
                cXyz offset(0.0f, -40.0f, 60.0f);
                mDoAud_seStart(JA_SE_CM_CMN_NOTICE, &current.pos);
                setBikon(offset);
                mTimer = 20;
            }
        } else if (cLib_calcTimer(&mTimer) == 0) {
            setAnm_NUM(2, 1);
        }
        return TRUE;
    }

    if (mOrder != 1 && dist < 210.0f) {
        mOrder = 1;
    }

    if (cLib_calcTimer(&mAttkTimer) == 0) {
        if (chk_areaIN(l_HIO.mPrm.mAttkEndDist, mHomePos) == false) {
            setStt(6);
            return TRUE;
        }
    }

    cLib_addCalcAngleS(&current.angle.y, cLib_targetAngleY(&current.pos, &dComIfGp_getLinkPlayer()->current.pos), l_HIO.mPrm.mWalkTurnScale, l_HIO.mPrm.mWalkTurnMaxStep, 0x80);
    cLib_chaseF(&speedF, l_HIO.mPrm.mAttkSpeed, l_HIO.mPrm.mAttkAccel);

    f32 rate = speedF * l_HIO.mPrm.mAttkAnmRate;
    f32 anm_speed = rate < 0.5f ? 0.5f : rate;
    mpMorf->setPlaySpeed(anm_speed);
    return TRUE;
}

/* .text walk_1__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::walk_1() {
    if (mPath.getPath() == NULL) {
        return TRUE;
    }

    if (dPath_ChkClose(mPath.getPath())) {
        if (mPath.chkPointPass(current.pos, mPath.getDir())) {
            mPath.nextIdxAuto();
        }
    } else {
        return TRUE;
    }

    cXyz point = mPath.getPoint(mPath.getIdx());
    cLib_addCalcAngleS(&current.angle.y, cLib_targetAngleY(&current.pos, &point), l_HIO.mPrm.mWalkTurnScale, l_HIO.mPrm.mWalkTurnMaxStep, 0x80);

    f32 target_speed = l_HIO.mPrm.mWalkSpeed;
    if (cLib_calcTimer(&mTimer) == 0 || mbTalkReq) {
        target_speed = 0.0f;
    }

    if (!endEvent_check() && startEvent_check()) {
        speedF = 0.0f;
        mTimer = 0;
        setStt(5);
        mLookMode = 0;
        m7AF = true;
        return TRUE;
    }

    cLib_chaseF(&speedF, target_speed, l_HIO.mPrm.mWalkAccel);

    f32 rate = speedF * l_HIO.mPrm.mWalkAnmRate;
    f32 anm_speed = rate < 0.5f ? 0.5f : rate;
    mpMorf->setPlaySpeed(anm_speed);

    if ((int)(0.5f + target_speed) == 0 && (int)speedF == 0) {
        if (mbTalkReq) {
            if (chk_talk()) {
                setStt(2);
            }
            return TRUE;
        }
        setStt(4);
        return TRUE;
    }

    mOrder = 0;
    if (endEvent_check()) {
        mOrder = 2;
    }
    mLookMode = 0;
    m7AF = true;
    return TRUE;
}

/* .text wait_2__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::wait_2() {
    if (mbTalkReq) {
        if (chk_talk()) {
            setStt(2);
        }
        return TRUE;
    }

    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B04) || chk_areaIN(l_HIO.mPrm.mAttkEndDist, mHomePos) == false) {
        mPath.setNearPathIndx(&current.pos, 0.0f);
        setStt(3);
        return TRUE;
    }

    mOrder = 2;
    m7AF = true;
    if (chk_attn()) {
        mLookMode = 1;
        return TRUE;
    }
    mLookMode = 0;
    return TRUE;
}

/* .text wait_3__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::wait_3() {
    f32 dist = (current.pos - dComIfGp_getLinkPlayer()->current.pos).absXZ();

    if (mbTalkReq) {
        if (chk_talk()) {
            setStt(2);
            m7B0 = false;
        }
        return TRUE;
    }

    m7B0 = dist > 300.0f;
    if (m7B0) {
        setStt(3);
        mLookMode = 0;
        m7AF = true;
        return TRUE;
    }

    mOrder = 2;
    m7AF = true;
    if (chk_attn()) {
        mLookMode = 1;
        return TRUE;
    }
    mLookMode = 0;
    return TRUE;
}

/* .text talk_1__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::talk_1() {
    BOOL res = chk_parts_notMov();
    cLib_addCalcAngleS(&current.angle.y, cLib_targetAngleY(&current.pos, &dComIfGp_getLinkPlayer()->current.pos), 4, l_HIO.mPrm.mMaxHeadTurnVel, 0x80);
    u16 status = fopNpc_npc_c::talk(1);
    if (mpCurrMsg == NULL) {
        return TRUE;
    }

    if (status == 10 && mbMorfAnimStopped && mCurrMsgNo == 0x1B60) {
        fopMsgM_messageSendOn();
    }

    switch (mpCurrMsg->mStatus) {
    case fopMsgStts_BOX_OPENING_e:
    case fopMsgStts_MSG_TYPING_e:
        break;
    case fopMsgStts_MSG_DESTROYED_e:
        mItemNo = 0xFF;
        mbTalkReq = false;
        setStt(mPrevStt);
        endEvent();
        break;
    }
    return res;
}

/* .text wait_action1__11daNpc_Pf1_cFPv */
BOOL daNpc_Pf1_c::wait_action1(void*) {
    switch (mActionState) {
    case 0:
        setStt(3);
        mActionState++;
        break;
    case 9:
        break;
    case 1:
    case 2:
    case 3:
        mbAttention = chkAttention();
        switch (mStt) {
        case 1:
            mbSetEyePos = wait_1();
            break;
        case 2:
            mbSetEyePos = talk_1();
            break;
        case 3:
            mbSetEyePos = walk_1();
            break;
        case 4:
            mbSetEyePos = regret();
            break;
        case 5:
            mbSetEyePos = attk_1();
            break;
        case 6:
            mbSetEyePos = wait_2();
            break;
        case 7:
            mbSetEyePos = wait_3();
            break;
        }
        break;
    default:
        break;
    }
    return TRUE;
}

/* .text demo */
bool daNpc_Pf1_c::demo() {
    if (demoActorID == 0) {
        if (mbDemo) {
            mbDemo = false;
        }
    } else {
        if (!mbDemo) {
            mbDemo = true;
            m7AA = false;
            m_jnt.setHead_y(0);
            m_jnt.setHead_x(0);
            m_jnt.setBackBone_y(0);
            m_jnt.setBackBone_x(0);
        }

        dDemo_actor_c* demo_actor_p = dComIfGp_demo_getActor(demoActorID);
        J3DAnmTexPattern* anm_pattern_p = mBtpAnm.getBtpAnm();
        if (anm_pattern_p) {
            u8 frame_max = anm_pattern_p->getFrameMax();
            mBtpFrame++;
            if (mBtpFrame >= frame_max) {
                mBtpFrame = frame_max;
            }
        }

        J3DAnmTexPattern* demo_btp_p = demo_actor_p->getP_BtpData(mArcName);
        if (demo_btp_p) {
            mBtpAnm.init(mpMorf->getModel()->getModelData(), demo_btp_p, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, 0);
            mBtpNum = BTPNUM_NULL_e;
            mBtpFrame = 0;
        }

        dDemo_setDemoData(this, 106, mpMorf, mArcName, 0, NULL, 0, 0);
    }

    return mbDemo;
}

/* .text shadowDraw */
void daNpc_Pf1_c::shadowDraw() {
    cXyz pos(current.pos.x, current.pos.y + 150.0f, current.pos.z);

    mShadowID = dComIfGd_setShadow(mShadowID, 1, mpMorf->getModel(), &pos, 800.0f, 40.0f, current.pos.y, mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr);
}

static void dummy() {
    const GXColor dummy1 = {0x00, 0xFF, 0x00, 0x80};
    const GXColor dummy2 = {0xFF, 0xFF, 0x00, 0x80};
    const GXColor dummy3 = {0xFF, 0x00, 0x00, 0x80};
    const GXColor dummy4 = {0x00, 0x00, 0xFF, 0x80};
}

/* .text _draw__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::_draw() {
    J3DModel* morf_model_p = mpMorf->getModel();
    J3DModelData* morf_model_info_p = morf_model_p->getModelData();

    if (m7A8 || m7AB != 0) {
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(morf_model_p, &tevStr);

    mBtpAnm.entry(morf_model_info_p, mBtpFrame);
    mpMorf->entryDL();
    mBtpAnm.remove(morf_model_info_p);

    shadowDraw();
    dSnap_RegistFig(DSNAP_TYPE_UNK5B, this, 1.0f, 1.0f, 1.0f);

    return TRUE;
}

/* .text _execute__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::_execute() {
    if (!mbInitDone) {
        mHomePos = current.pos;
        mHomeAngle = current.angle;
        mbInitDone = true;
    }
    m_jnt.setParam(
        l_HIO.mPrm.mMaxBackBoneX,
        l_HIO.mPrm.mMaxBackBoneY,
        l_HIO.mPrm.mMinBackBoneX,
        l_HIO.mPrm.mMinBackBoneY,
        l_HIO.mPrm.mMaxHeadX,
        l_HIO.mPrm.mMaxHeadY,
        l_HIO.mPrm.mMinHeadX,
        l_HIO.mPrm.mMinHeadY,
        l_HIO.mPrm.mMaxTurnStep
    );

    if (m7A8 && demoActorID == 0) {
        return TRUE;
    }

    checkOrder();
    if (!demo()) {
        int staff_id = -1;
        if (dComIfGp_event_runCheck() && eventInfo.checkCommandTalk() == false) {
            staff_id = isEventEntry();
        }

        if (staff_id >= 0) {
            event_proc(staff_id);
        } else {
            (this->*mCurrProcFunc)(NULL);
        }

        field_0x6ba = 0;
        lookBack();
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
        mObjAcch.CrrPos(*dComIfG_Bgsp());
        if (-1000000000.0f != mObjAcch.GetGroundH()) {
            cM3dGPla* pla = dComIfG_Bgsp()->GetTriPla(mObjAcch.m_gnd);
            if (pla != NULL) {
                mGndNormal = pla->mNormal;
            }
        }
        play_animation();
    } else {
        m7A8 = false;
    }

    eventOrder();
    mAngle = current.angle;
    if (!m7AA) {
        shape_angle = current.angle;
    }

    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    setMtx(false);

    if (!mbDemo) {
        setCollision(100.0f, 200.0f);
    }

    return TRUE;
}

/* .text _delete__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::_delete() {
    cDyl_Unlink(fpcNm_TAMA_e);
    dComIfG_resDelete(&mPhs, mArcName);
    delBikon();
    if (heap && mpMorf) {
        mpMorf->stopZelAnime();
    }
    return TRUE;
}

/* .text _create__11daNpc_Pf1_cFv */
cPhs_State daNpc_Pf1_c::_create() {
    static int a_siz_tbl[] = {
        0,
        0,
    };

    cPhs_State state;

    fopAcM_ct(this, daNpc_Pf1_c);

    if (!decideType(fopAcM_GetParam(this) & 0xFF)) {
        return cPhs_ERROR_e;
    }

    state = dComIfG_resLoad(&mPhs, mArcName);
    mbResLoadIsComplete = state == cPhs_COMPLEATE_e;
    if (!mbResLoadIsComplete) {
        return state;
    }

    cPhs_State link_state = cDyl_LinkASync(fpcNm_TAMA_e);
    if (link_state != cPhs_COMPLEATE_e) {
        return link_state;
    }

    if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_siz_tbl[m7BB])) {
        return cPhs_ERROR_e;
    }

    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -100.0f, -20.0f, -80.0f, 100.0f, 180.0f, 140.0f);

    if (!createInit()) {
        return cPhs_ERROR_e;
    }

    return state;
}

/* .text bodyCreateHeap__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::bodyCreateHeap() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes(mArcName, dRes_ID_PF_BDL_PF_e);
    JUT_ASSERT(0x803, a_mdl_dat != NULL);

    mpMorf = new mDoExt_McaMorf(a_mdl_dat, NULL, NULL, NULL, J3DFrameCtrl::EMode_NULL, 1.0f, 0, -1, 1, NULL, 0x80000, 0x11020022);

    if (!mpMorf) {
        return FALSE;
    } else if (!mpMorf->getModel()) {
        mpMorf = NULL;
        return FALSE;
    }

    if (!init_texPttrnAnm(BTPNUM_MABA01_e, false)) {
        mpMorf = NULL;
        return FALSE;
    }

    m_hed_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
    JUT_ASSERT(0x817, m_hed_jnt_num >= 0);

    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone1");
    JUT_ASSERT(0x819, m_bbone_jnt_num >= 0);

    mpMorf->getModel()->getModelData()->getJointNodePointer(m_hed_jnt_num)->setCallBack(nodeCB_Head);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_bbone_jnt_num)->setCallBack(nodeCB_BackBone);
    mpMorf->getModel()->setUserArea((uintptr_t)this);

    return TRUE;
}

/* .text CreateHeap__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::CreateHeap() {
    if (!bodyCreateHeap()) {
        return FALSE;
    }

    mAcchCir.SetWall(30.0f, 100.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this), NULL, NULL);

    return TRUE;
}

/* 000046D8-000046F8       .text daNpc_Pf1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Pf1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Pf1_c*)i_this)->_create();
}

/* 000046F8-00004718       .text daNpc_Pf1_Delete__FP11daNpc_Pf1_c */
static BOOL daNpc_Pf1_Delete(daNpc_Pf1_c* i_this) {
    return ((daNpc_Pf1_c*)i_this)->_delete();
}

/* 00004718-00004738       .text daNpc_Pf1_Execute__FP11daNpc_Pf1_c */
static BOOL daNpc_Pf1_Execute(daNpc_Pf1_c* i_this) {
    return ((daNpc_Pf1_c*)i_this)->_execute();
}

/* 00004738-00004758       .text daNpc_Pf1_Draw__FP11daNpc_Pf1_c */
static BOOL daNpc_Pf1_Draw(daNpc_Pf1_c* i_this) {
    return ((daNpc_Pf1_c*)i_this)->_draw();
}

/* 00004758-00004760       .text daNpc_Pf1_IsDelete__FP11daNpc_Pf1_c */
static BOOL daNpc_Pf1_IsDelete(daNpc_Pf1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Pf1_Method = {
    (process_method_func)daNpc_Pf1_Create,
    (process_method_func)daNpc_Pf1_Delete,
    (process_method_func)daNpc_Pf1_Execute,
    (process_method_func)daNpc_Pf1_IsDelete,
    (process_method_func)daNpc_Pf1_Draw,
};

actor_process_profile_definition g_profile_NPC_PF1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_PF1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Pf1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_PF1_e,
    /* Actor SubMtd */ &l_daNpc_Pf1_Method,
    /* Status       */ 0x08 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
