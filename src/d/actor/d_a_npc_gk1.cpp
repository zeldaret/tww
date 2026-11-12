/**
 * d_a_npc_gk1.cpp
 * NPC - Mila's Father (poor)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_gk1.h"
#include "d/d_com_inf_game.h"
#include "d/d_snap.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_lib.h"
#include "m_Do/m_Do_hostIO.h"
#include "res/Object/Gk.h"

class daNpc_Gk1_HIO_c : public mDoHIO_entry_c {
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
    };  // Size: 0x1C

    daNpc_Gk1_HIO_c();
    virtual ~daNpc_Gk1_HIO_c() {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ int m08;
    /* 0x0C */ hio_prm_c mPrm;
};  // Size: 0x28

static daNpc_Gk1_HIO_c l_HIO;
static fopAc_ac_c* l_check_inf[20];
static int l_check_wrk;

/* 000000EC-00000150       .text __ct__15daNpc_Gk1_HIO_cFv */
daNpc_Gk1_HIO_c::daNpc_Gk1_HIO_c() {
    static hio_prm_c a_prm_tbl = {
        /* mMaxHeadX       */ 0x2000,
        /* mMaxHeadY       */ 0x0FA0,
        /* mMinHeadX       */ -0x1194,
        /* mMinHeadY       */ -0x0FA0,
        /* mMaxBackBoneX   */ 0x0000,
        /* mMaxBackBoneY   */ 0x0DAC,
        /* mMinBackBoneX   */ -0x03E8,
        /* mMinBackBoneY   */ -0x0DAC,
        /* mMaxTurnStep    */ 0x0578,
        /* mMaxHeadTurnVel */ 0x03E8,
        /* mAttPosOffsetY  */ 200.0f,
        /* m18             */ 0,
    };
    memcpy(&mPrm, &a_prm_tbl, sizeof(hio_prm_c));
    mNo = -1;
    m08 = -1;
}

static const char* l_evn_tbl[] = {
    "dummy",
};

/* 00000198-000001E4       .text nodeCB_Head__FP7J3DNodei */
static BOOL nodeCB_Head(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In && j3dSys.getModel()->getUserArea() != 0) {
        daNpc_Gk1_c* actor_p = (daNpc_Gk1_c*)j3dSys.getModel()->getUserArea();
        actor_p->_nodeCB_Head(i_node, j3dSys.getModel());
    }
    return TRUE;
}

/* 000001E4-000002D8       .text _nodeCB_Head__11daNpc_Gk1_cFP7J3DNodeP8J3DModel */
void daNpc_Gk1_c::_nodeCB_Head(J3DNode* i_node, J3DModel* i_model) {
    static cXyz a_eye_pos_off(30.0f, 30.0f, 0.0f);

    J3DJoint* jnt_p = (J3DJoint*)i_node;
    s32 jnt_no = jnt_p->getJntNo();

    mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));

    mHeadPos.x = mDoMtx_stack_c::get()[0][3];
    mHeadPos.y = mDoMtx_stack_c::get()[1][3];
    mHeadPos.z = mDoMtx_stack_c::get()[2][3];

    mDoMtx_stack_c::multVec(&a_eye_pos_off, &mTransformedEyePos);

    mDoMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    i_model->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* 00000314-00000360       .text nodeCB_Neck__FP7J3DNodei */
static BOOL nodeCB_Neck(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In && j3dSys.getModel()->getUserArea() != 0) {
        daNpc_Gk1_c* actor_p = (daNpc_Gk1_c*)j3dSys.getModel()->getUserArea();
        actor_p->_nodeCB_Neck(i_node, j3dSys.getModel());
    }
    return TRUE;
}

/* 00000360-00000400       .text _nodeCB_Neck__11daNpc_Gk1_cFP7J3DNodeP8J3DModel */
void daNpc_Gk1_c::_nodeCB_Neck(J3DNode* i_node, J3DModel* i_model) {
    J3DJoint* jnt_p = (J3DJoint*)i_node;
    s32 jnt_no = jnt_p->getJntNo();

    mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));
    mDoMtx_stack_c::XrotM(m_jnt.getHead_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());

    mDoMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* 00000400-0000044C       .text nodeCB_BackBone__FP7J3DNodei */
static BOOL nodeCB_BackBone(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In && j3dSys.getModel()->getUserArea() != 0) {
        daNpc_Gk1_c* actor_p = (daNpc_Gk1_c*)j3dSys.getModel()->getUserArea();
        actor_p->_nodeCB_BackBone(i_node, j3dSys.getModel());
    }
    return TRUE;
}

/* 0000044C-000004EC       .text _nodeCB_BackBone__11daNpc_Gk1_cFP7J3DNodeP8J3DModel */
void daNpc_Gk1_c::_nodeCB_BackBone(J3DNode* i_node, J3DModel* i_model) {
    J3DJoint* jnt_p = (J3DJoint*)i_node;
    s32 jnt_no = jnt_p->getJntNo();

    mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));
    mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getBackbone_x());

    mDoMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* 000004EC-0000050C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Gk1_c*)i_this)->CreateHeap();
}

/* 0000050C-0000058C       .text init_GK1_0__11daNpc_Gk1_cFv */
bool daNpc_Gk1_c::init_GK1_0() {
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2D01)) {
        set_action(&daNpc_Gk1_c::wait_action1, NULL);
        return true;
    }
    return false;
}

/* 0000058C-00000720       .text createInit__11daNpc_Gk1_cFv */
bool daNpc_Gk1_c::createInit() {
    mEventIDTbl[0] = dComIfGp_evmng_getEventIdx(l_evn_tbl[0]);
    mEventCut.setActorInfo2("Gk1", this);
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    fopAcM_setCullSizeFar(this, 12000.0f / mDoLib_clipper::getFar());

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
        init_result = init_GK1_0();
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

    mStts.Init(0xFF, 0xFF, this);
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

/* 00000720-000007C8       .text play_animation__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::play_animation() {
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

/* 000007C8-00000930       .text setMtx__11daNpc_Gk1_cFb */
void daNpc_Gk1_c::setMtx(bool i_setEyePos) {
    mpMorf->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(mAngle);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());

    mpMorf->calc();

    if (mpHairModel) {
        mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(m_hed_jnt_num));
        mpHairModel->setBaseTRMtx(mDoMtx_stack_c::get());
        mpHairModel->calc();
    }
    if (mpHatModel) {
        mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(m_hed_jnt_num));
        mpHatModel->setBaseTRMtx(mDoMtx_stack_c::get());
        mpHatModel->calc();
    }
    setAttention(i_setEyePos);
}

/* 00000930-00000944       .text bckResID__11daNpc_Gk1_cFi */
int daNpc_Gk1_c::bckResID(int i_bckNum) {
    static const int a_resID_tbl[] = {
        dRes_ID_GK_BCK_GK_WAIT01_e,
        dRes_ID_GK_BCK_GK_WALK_e,
        dRes_ID_GK_BCK_GK_TALK01_e,
        dRes_ID_GK_BCK_GK_TALK02_e,
        dRes_ID_GK_BCK_GK_TALK03_e,
    };
    return a_resID_tbl[i_bckNum];
}

/* 00000944-00000958       .text btpResID__11daNpc_Gk1_cFi */
int daNpc_Gk1_c::btpResID(int i_btpNum) {
    static const int a_resID_tbl[] = {
        dRes_ID_GK_BTP_GK_e,
    };
    return a_resID_tbl[i_btpNum];
}

/* 00000958-00000A5C       .text setBtp__11daNpc_Gk1_cFScb */
bool daNpc_Gk1_c::setBtp(s8 i_btpNum, bool i_bModify) {
    J3DModel* morf_model_p = mpMorf->getModel();

    if (i_btpNum < 0) {
        return false;
    }

    J3DAnmTexPattern* a_btp = (J3DAnmTexPattern*)dComIfG_getObjectIDRes(mArcName, btpResID(i_btpNum));
    JUT_ASSERT(0x1C3, a_btp != NULL);
    mBtpNum = i_btpNum;
    mBtpFrame = 0;
    mBlinkTimer = 0;

    return mBtpAnm.init(morf_model_p->getModelData(), a_btp, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, i_bModify, 0) != 0;
}

/* 00000A5C-00000A7C       .text init_texPttrnAnm__11daNpc_Gk1_cFScb */
bool daNpc_Gk1_c::init_texPttrnAnm(s8 i_btpNum, bool i_bModify) {
    return setBtp(i_btpNum, i_bModify);
}

/* 00000A7C-00000B18       .text play_btp_anm__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::play_btp_anm() {
    u8 frame_max = mBtpAnm.getBtpAnm()->getFrameMax();
    if (mBtpNum != BTPNUM_GK_e || cLib_calcTimer(&mBlinkTimer) == 0) {
        mBtpFrame++;
        if (mBtpFrame >= frame_max) {
            if (mBtpNum != BTPNUM_GK_e) {
                mBtpFrame = frame_max;
            } else {
                mBlinkTimer = cLib_getRndValue(60, 90);
                mBtpFrame = 0;
            }
        }
    }
}

/* 00000B18-00000BB4       .text setAnm_anm__11daNpc_Gk1_cFPQ211daNpc_Gk1_c9anm_prm_c */
void daNpc_Gk1_c::setAnm_anm(anm_prm_c* i_anmPrmP) {
    if (i_anmPrmP->bckNum < 0 || mBckNum == i_anmPrmP->bckNum) {
        return;
    }

    dNpc_setAnmIDRes(mpMorf, i_anmPrmP->loopMode, i_anmPrmP->morf, i_anmPrmP->speed, bckResID(i_anmPrmP->bckNum), -1, mArcName);
    mBckNum = i_anmPrmP->bckNum;
    mbMorfAnimStopped = false;
    m79D = 0;
    mPrevMorfFrame = 0.0f;
}

/* 00000BB4-00000C10       .text setAnm__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::setAnm() {
    static anm_prm_c a_anm_prm_tbl[3] = {
        {-1, -1, 0.0f, 0.0f, J3DFrameCtrl::EMode_NULL},
        {BCKNUM_WAIT01_e, BTPNUM_GK_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {-1, -1, 0.0f, 0.0f, J3DFrameCtrl::EMode_NULL},
    };

    init_texPttrnAnm(a_anm_prm_tbl[mStt].btpNum, true);
    setAnm_anm(&a_anm_prm_tbl[mStt]);
}

/* 00000C10-00000C14       .text chngAnmTag__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::chngAnmTag() {
}

/* 00000C14-00000C18       .text ctrlAnmTag__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::ctrlAnmTag() {
}

/* 00000C18-00000C64       .text chngAnmAtr__11daNpc_Gk1_cFUc */
void daNpc_Gk1_c::chngAnmAtr(u8 i_atr) {
    if (i_atr == mAnmAtr || i_atr > 5) {
        return;
    }
    mAnmAtr = i_atr;
    setAnm_ATR();
}

/* 00000C64-00000C68       .text ctrlAnmAtr__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::ctrlAnmAtr() {
    switch (mAnmAtr) {
    case 5:
        break;
    }
}

/* 00000C68-00000CC0       .text setAnm_ATR__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::setAnm_ATR() {
    static anm_prm_c a_anm_prm_tbl[5] = {
        {BCKNUM_WAIT01_e, BTPNUM_GK_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_WALK_e, BTPNUM_GK_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_TALK01_e, BTPNUM_GK_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_TALK02_e, BTPNUM_GK_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_TALK03_e, BTPNUM_GK_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };

    init_texPttrnAnm(a_anm_prm_tbl[mAnmAtr].btpNum, true);
    setAnm_anm(&a_anm_prm_tbl[mAnmAtr]);
}

/* 00000CC0-00000D7C       .text anmAtr__11daNpc_Gk1_cFUs */
void daNpc_Gk1_c::anmAtr(u16 i_msgStatus) {
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

/* 00000D7C-00000EAC       .text next_msgStatus__11daNpc_Gk1_cFPUl */
u16 daNpc_Gk1_c::next_msgStatus(u32* o_msgNoP) {
    u16 msg_status = fopMsgStts_MSG_CONTINUES_e;
    switch (*o_msgNoP) {
    case 0x28A1:
        *o_msgNoP = 0x28A2;
        break;
    case 0x28A2:
        *o_msgNoP = 0x28A3;
        break;
    case 0x28A3:
        *o_msgNoP = 0x28A4;
        break;
    case 0x28A4:
        *o_msgNoP = 0x28A5;
        break;
    case 0x28A6:
        *o_msgNoP = 0x28A7;
        break;
    case 0x28A7:
        *o_msgNoP = 0x28A8;
        break;
    case 0x28A8:
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1640)) {
            msg_status = fopMsgStts_MSG_ENDS_e;
        } else {
            *o_msgNoP = 0x28A9;
        }
        break;
    case 0x28A9:
        *o_msgNoP = 0x28AA;
        break;
    case 0x28AB:
        *o_msgNoP = 0x28AC;
        break;
    case 0x28AC:
        *o_msgNoP = 0x28AD;
        break;
    case 0x28AD:
        *o_msgNoP = 0x28AE;
        break;
    case 0x28AF:
        *o_msgNoP = 0x28B0;
        break;
    default:
        msg_status = fopMsgStts_MSG_ENDS_e;
        break;
    }
    return msg_status;
}

/* 00000EAC-00000F6C       .text getMsg_GK1_0__11daNpc_Gk1_cFv */
u32 daNpc_Gk1_c::getMsg_GK1_0() {
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B02) && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_1680)) {
        return 0x28A1;
    }
    if (dKy_daynight_check() == 0) {
        return dComIfGs_isEventBit(dSv_event_flag_c::UNK_1640) ? 0x28A7 : 0x28A6;
    }
    return dComIfGs_isEventBit(dSv_event_flag_c::UNK_0E08) ? 0x28AF : 0x28AB;
}

/* 00000F6C-00000FB0       .text getMsg__11daNpc_Gk1_cFv */
u32 daNpc_Gk1_c::getMsg() {
    u32 result = 0;
    switch (mType) {
    case 0:
        result = getMsg_GK1_0();
        break;
    }
    return result;
}

/* 00000FB0-00001038       .text eventOrder__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::eventOrder() {
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

/* 00001038-000010EC       .text checkOrder__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (dComIfGp_evmng_startCheck(mEventIDTbl[mEventIndex]) && mOrder >= 3) {
            mOrder = 0;
            mAnmAtr = 0xFF;
            mMesgAnimeTag = 0xFF;
        }
    } else if (eventInfo.checkCommandTalk()) {
        if (mOrder == 1 || mOrder == 2) {
            mOrder = 0;
            mbTalkReq = true;
        }
    }
}

/* 000010EC-00001184       .text chk_talk__11daNpc_Gk1_cFv */
bool daNpc_Gk1_c::chk_talk() {
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

/* 00001184-000011C4       .text chk_parts_notMov__11daNpc_Gk1_cFv */
bool daNpc_Gk1_c::chk_parts_notMov() {
    return mJointHeadY != m_jnt.getHead_y() ||
        mJointBackboneY != m_jnt.getBackbone_y() ||
        mActorAngleY != current.angle.y;
}

/* 000011C4-00001218       .text searchByID__11daNpc_Gk1_cFUiPi */
fopAc_ac_c* daNpc_Gk1_c::searchByID(fpc_ProcID i_PID, int* o_notFound) {
    fopAc_ac_c* actor_p;

    actor_p = NULL;
    *o_notFound = 0;
    if (!fopAcM_SearchByID(i_PID, &actor_p)) {
        *o_notFound = 1;
    }

    return actor_p;
}

/* 00001218-000013D8       .text lookBack__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::lookBack() {
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
    bool head_only = m7A6;

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

/* 000013D8-00001458       .text chkAttention__11daNpc_Gk1_cFv */
bool daNpc_Gk1_c::chkAttention() {
    dAttention_c& attention = dComIfGp_getAttention();
    if (attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    } else {
        return this == attention.ActionTarget(0);
    }
}

/* 00001458-000014B0       .text setAttention__11daNpc_Gk1_cFb */
void daNpc_Gk1_c::setAttention(bool i_setEyePos) {
    attention_info.position.set(current.pos.x, current.pos.y + l_HIO.mPrm.mAttPosOffsetY, current.pos.z);

    if (!mbSetEyePos && !i_setEyePos) {
        return;
    }

    eyePos.set(mTransformedEyePos.x, mTransformedEyePos.y, mTransformedEyePos.z);
}

/* 000014B0-00001540       .text decideType__11daNpc_Gk1_cFi */
bool daNpc_Gk1_c::decideType(int i_type) {
    if (m7B2 > 0) {
        return true;
    }

    m7B2 = 1;
    mType = 0;

    strcpy(mArcName, "Gk");
    return m7B2 != -1 && mType != -1;
}

/* 00001540-000015F8       .text privateCut__11daNpc_Gk1_cFi */
void daNpc_Gk1_c::privateCut(int i_staffIdx) {
    static char* a_cut_tbl[] = {
        "dummy",
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

/* 000015F8-0000161C       .text endEvent__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::endEvent() {
    dComIfGp_event_reset();
    mAnmAtr = 0xFF;
    mMesgAnimeTag = 0xFF;
}

/* 0000161C-00001654       .text isEventEntry__11daNpc_Gk1_cFv */
int daNpc_Gk1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName());
}

/* 00001654-000016D4       .text event_proc__11daNpc_Gk1_cFi */
void daNpc_Gk1_c::event_proc(int i_staffIdx) {
    if (dComIfGp_evmng_endCheck(mEventIDTbl[mEventIndex])) {
        endEvent();
    } else {
        if (mEventCut.cutProc()) {
            return;
        }
        privateCut(i_staffIdx);
    }
}

/* 000016D4-00001780       .text set_action__11daNpc_Gk1_cFM11daNpc_Gk1_cFPCvPvPv_iPv */
BOOL daNpc_Gk1_c::set_action(ProcFunc i_newProcFunc, void* i_argsP) {
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

/* 00001780-00001810       .text setStt__11daNpc_Gk1_cFSc */
void daNpc_Gk1_c::setStt(s8 i_stt) {
    u8 prev_stt = mStt;
    mStt = i_stt;
    switch (mStt) {
    case 0:
        break;
    case 1:
        mOrder = 0;
        speedF = 0.0f;
        break;
    case 2:
        mOrder = 0;
        mAnmAtr = 0xFF;
        mMesgAnimeTag = 0xFF;
        mMsgCount = 0;
        mPrevStt = prev_stt;
        break;
    }
    setAnm();
}

/* 00001810-000019E0       .text chk_attn__11daNpc_Gk1_cFv */
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

bool daNpc_Gk1_c::chk_attn() {
    f32 dist = (current.pos - dComIfGp_getPlayer(0)->current.pos).absXZ();
    f32 dy = current.pos.y - dComIfGp_getPlayer(0)->current.pos.y;
    s16 angle = cLib_targetAngleY(&current.pos, &dComIfGp_getPlayer(0)->current.pos) - current.angle.y;

    if (mLookMode == 1) {
        return chk_area(dist, dy, angle, 90.0f);
    }
    return chk_area(dist, dy, angle, 60.0f);
}

/* 000019E0-00001B74       .text wait_1__11daNpc_Gk1_cFv */
BOOL daNpc_Gk1_c::wait_1() {
    f32 dist = (current.pos - dComIfGp_getPlayer(0)->current.pos).absXZ();
    mbTurnHome = dist > 300.0f;
    if (mbTurnHome) {
        cLib_addCalcAngleS(&current.angle.y, mHomeAngle.y, 4, 0x800, 0x80);
    }

    if (mbTalkReq) {
        if (chk_talk()) {
            setStt(2);
            mLookMode = 1;
            m7A6 = false;
            mbTurnHome = false;
            m_jnt.setTrn();
        }
        return TRUE;
    }

    mOrder = 2;
    m7A6 = true;
    if (chk_attn()) {
        mLookMode = 1;
        return TRUE;
    }
    mLookMode = 0;
    return TRUE;
}

/* 00001B74-00001C68       .text talk_1__11daNpc_Gk1_cFv */
BOOL daNpc_Gk1_c::talk_1() {
    BOOL res = chk_parts_notMov();
    fopNpc_npc_c::talk(1);
    if (mpCurrMsg == NULL) {
        return TRUE;
    }
    switch (mpCurrMsg->mStatus) {
    case fopMsgStts_BOX_OPENING_e:
    case fopMsgStts_MSG_TYPING_e:
        break;
    case fopMsgStts_MSG_DESTROYED_e:
        switch (mCurrMsgNo) {
        case 0x28A5:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_1680);
            break;
        case 0x28AA:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_1640);
            break;
        }
        mItemNo = 0xFF;
        mbTalkReq = false;
        setStt(mPrevStt);
        mTalkTimer = cLib_getRndValue(15, 30);
        endEvent();
        break;
    }
    return res;
}

/* 00001C68-00001D30       .text wait_action1__11daNpc_Gk1_cFPv */
BOOL daNpc_Gk1_c::wait_action1(void*) {
    switch (mActionState) {
    case 9:
        break;
    case 0:
        setStt(1);
        mbTurnHome = true;
        mActionState++;
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
        }
        break;
    default:
        break;
    }
    return TRUE;
}

/* 00001D30-00001E80       .text demo__11daNpc_Gk1_cFv */
bool daNpc_Gk1_c::demo() {
    if (demoActorID == 0) {
        if (mbDemo) {
            mbDemo = false;
        }
    } else {
        if (!mbDemo) {
            mbDemo = true;
            m7A1 = false;
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

/* 00001E80-00001F5C       .text shadowDraw__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::shadowDraw() {
    cXyz pos(current.pos.x, current.pos.y + 150.0f, current.pos.z);

    mShadowID = dComIfGd_setShadow(mShadowID, 1, mpMorf->getModel(), &pos, 800.0f, 40.0f, current.pos.y, mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr);

    if (mShadowID != 0) {
        if (mpHairModel) {
            dComIfGd_addRealShadow(mShadowID, mpHairModel);
        }
        if (mpHatModel) {
            dComIfGd_addRealShadow(mShadowID, mpHatModel);
        }
    }
}

static void dummy() {
    const GXColor dummy1 = {0xFF, 0x00, 0x00, 0x80};
    const GXColor dummy2 = {0x00, 0x00, 0xFF, 0x80};
    const GXColor dummy3 = {0xFF, 0xFF, 0x00, 0x80};
}

/* 00001F5C-00002064       .text _draw__11daNpc_Gk1_cFv */
BOOL daNpc_Gk1_c::_draw() {
    J3DModel* morf_model_p = mpMorf->getModel();
    J3DModelData* morf_model_info_p = morf_model_p->getModelData();

    if (m7A0 || m7A2 != 0) {
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(morf_model_p, &tevStr);

    mBtpAnm.entry(morf_model_info_p, mBtpFrame);
    mpMorf->entryDL();
    mBtpAnm.remove(morf_model_info_p);

    if (mpHairModel) {
        g_env_light.setLightTevColorType(mpHairModel, &tevStr);
        mDoExt_modelEntryDL(mpHairModel);
    }
    if (mpHatModel) {
        g_env_light.setLightTevColorType(mpHatModel, &tevStr);
        mDoExt_modelEntryDL(mpHatModel);
    }

    shadowDraw();
    dSnap_RegistFig(DSNAP_TYPE_UNK59, this, 1.0f, 1.0f, 1.0f);

    return TRUE;
}

/* 00002064-0000229C       .text _execute__11daNpc_Gk1_cFv */
BOOL daNpc_Gk1_c::_execute() {
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

    if (m7A0 && demoActorID == 0) {
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

        lookBack();
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
        mObjAcch.CrrPos(*dComIfG_Bgsp());
        play_animation();
    } else {
        m7A0 = false;
    }

    eventOrder();
    mAngle = current.angle;
    if (!m7A1) {
        shape_angle = current.angle;
    }

    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    setMtx(false);

    if (!mbDemo) {
        setCollision(90.0f, 200.0f);
    }

    return TRUE;
}

/* 0000229C-000022F0       .text _delete__11daNpc_Gk1_cFv */
BOOL daNpc_Gk1_c::_delete() {
    dComIfG_resDelete(&mPhs, mArcName);
    if (heap && mpMorf) {
        mpMorf->stopZelAnime();
    }
    return TRUE;
}

/* 000022F0-0000256C       .text _create__11daNpc_Gk1_cFv */
cPhs_State daNpc_Gk1_c::_create() {
    static int a_siz_tbl[] = {
        0,
        0,
    };

    cPhs_State state;

    fopAcM_ct(this, daNpc_Gk1_c);

    if (!decideType(fopAcM_GetParam(this) & 0xFF)) {
        return cPhs_ERROR_e;
    }

    state = dComIfG_resLoad(&mPhs, mArcName);
    mbResLoadIsComplete = state == cPhs_COMPLEATE_e;
    if (!mbResLoadIsComplete) {
        return state;
    }

    if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_siz_tbl[m7B2])) {
        return cPhs_ERROR_e;
    }

    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -90.0f, -20.0f, -80.0f, 90.0f, 200.0f, 80.0f);

    if (!createInit()) {
        return cPhs_ERROR_e;
    }

    return state;
}

/* 0000280C-00002C1C       .text bodyCreateHeap__11daNpc_Gk1_cFv */
BOOL daNpc_Gk1_c::bodyCreateHeap() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes(mArcName, dRes_ID_GK_BDL_GK_e);
    JUT_ASSERT(0x611, a_mdl_dat != NULL);

    mpMorf = new mDoExt_McaMorf(a_mdl_dat, NULL, NULL, NULL, J3DFrameCtrl::EMode_NULL, 1.0f, 0, -1, 1, NULL, 0x80000, 0x11020022);

    if (!mpMorf) {
        return FALSE;
    } else if (!mpMorf->getModel()) {
        mpMorf = NULL;
        return FALSE;
    }

    if (!init_texPttrnAnm(BTPNUM_GK_e, false)) {
        mpMorf = NULL;
        return FALSE;
    }

    m_hed_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
    JUT_ASSERT(0x625, m_hed_jnt_num >= 0);

    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(0x627, m_bbone_jnt_num >= 0);

    m_nck_jnt_num = a_mdl_dat->getJointName()->getIndex("neck");
    JUT_ASSERT(0x629, m_nck_jnt_num >= 0);

    mpMorf->getModel()->getModelData()->getJointNodePointer(m_hed_jnt_num)->setCallBack(nodeCB_Head);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_bbone_jnt_num)->setCallBack(nodeCB_BackBone);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_nck_jnt_num)->setCallBack(nodeCB_Neck);
    mpMorf->getModel()->setUserArea((uintptr_t)this);

    return TRUE;
}

/* 00002C1C-00002CF4       .text itemCreateHeap__11daNpc_Gk1_cFv */
BOOL daNpc_Gk1_c::itemCreateHeap() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes(mArcName, dRes_ID_GK_BDL_GK_HAIR_e);
    JUT_ASSERT(0x63E, a_mdl_dat != NULL);

    mpHairModel = mDoExt_J3DModel__create(a_mdl_dat, 0x80000, 0x11000022);

    if (!mpHairModel) {
        return FALSE;
    }

    return TRUE;
}

/* 00002CF4-00002DCC       .text hat_CreateHeap__11daNpc_Gk1_cFv */
BOOL daNpc_Gk1_c::hat_CreateHeap() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes(mArcName, dRes_ID_GK_BDL_GK_HAT_e);
    JUT_ASSERT(0x64E, a_mdl_dat != NULL);

    mpHatModel = mDoExt_J3DModel__create(a_mdl_dat, 0x80000, 0x11000022);

    if (!mpHatModel) {
        return FALSE;
    }

    return TRUE;
}

/* 00002DCC-00002E90       .text CreateHeap__11daNpc_Gk1_cFv */
BOOL daNpc_Gk1_c::CreateHeap() {
    if (!bodyCreateHeap()) {
        return FALSE;
    }

    if (!itemCreateHeap()) {
        mpMorf = NULL;
        return FALSE;
    }

    if (!hat_CreateHeap()) {
        mpMorf = NULL;
        return FALSE;
    }

    mAcchCir.SetWall(30.0f, 90.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this), NULL, NULL);

    return TRUE;
}

/* 00002E90-00002EB0       .text daNpc_Gk1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Gk1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Gk1_c*)i_this)->_create();
}

/* 00002EB0-00002ED0       .text daNpc_Gk1_Delete__FP11daNpc_Gk1_c */
static BOOL daNpc_Gk1_Delete(daNpc_Gk1_c* i_this) {
    return ((daNpc_Gk1_c*)i_this)->_delete();
}

/* 00002ED0-00002EF0       .text daNpc_Gk1_Execute__FP11daNpc_Gk1_c */
static BOOL daNpc_Gk1_Execute(daNpc_Gk1_c* i_this) {
    return ((daNpc_Gk1_c*)i_this)->_execute();
}

/* 00002EF0-00002F10       .text daNpc_Gk1_Draw__FP11daNpc_Gk1_c */
static BOOL daNpc_Gk1_Draw(daNpc_Gk1_c* i_this) {
    return ((daNpc_Gk1_c*)i_this)->_draw();
}

/* 00002F10-00002F18       .text daNpc_Gk1_IsDelete__FP11daNpc_Gk1_c */
static BOOL daNpc_Gk1_IsDelete(daNpc_Gk1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Gk1_Method = {
    (process_method_func)daNpc_Gk1_Create,
    (process_method_func)daNpc_Gk1_Delete,
    (process_method_func)daNpc_Gk1_Execute,
    (process_method_func)daNpc_Gk1_IsDelete,
    (process_method_func)daNpc_Gk1_Draw,
};

actor_process_profile_definition g_profile_NPC_GK1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_GK1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Gk1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_GK1_e,
    /* Actor SubMtd */ &l_daNpc_Gk1_Method,
    /* Status       */ 0x08 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
