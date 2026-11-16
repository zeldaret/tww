/**
 * d_a_npc_ob1.cpp
 * NPC - Rose
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_ob1.h"
#include "d/actor/d_a_kb.h"
#include "d/d_com_inf_game.h"
#include "d/d_path.h"
#include "d/d_snap.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"
#include "m_Do/m_Do_mtx.h"
#include "res/Object/Ob.h"

class daNpc_Ob1_HIO_c : public mDoHIO_entry_c {
public:
    struct hio_prm_c {
        /* 0x00 */ s16 mMaxHeadX;
        /* 0x02 */ s16 mMaxHeadY;
        /* 0x04 */ s16 mMinHeadX;
        /* 0x06 */ s16 mMinHeadY;
        /* 0x08 */ s16 mMaxBackboneX;
        /* 0x0A */ s16 mMaxBackboneY;
        /* 0x0C */ s16 mMinBackboneX;
        /* 0x0E */ s16 mMinBackboneY;
        /* 0x10 */ s16 mMaxTurnStep;
        /* 0x12 */ s16 mMaxHeadTurnVel;
        /* 0x14 */ f32 mAttPosOffsetY;
        /* 0x18 */ u8 m18;
        /* 0x1A */ s16 m1A;
        /* 0x1C */ s16 mWalkTurnStep;
        /* 0x20 */ f32 mWalkAnmRate;
        /* 0x24 */ f32 mWalkSpeed;
        /* 0x28 */ f32 mWalkAccel;
        /* 0x2C */ f32 mPassDist;
    };  // Size: 0x30

    daNpc_Ob1_HIO_c();
    virtual ~daNpc_Ob1_HIO_c() {}
    void genMessage(JORMContext* ctx) { UNUSED(ctx); }

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ int m8;
    /* 0x0C */ hio_prm_c mPrm;
};  // Size: 0x3C

/* 000000EC-00000150       .text __ct__15daNpc_Ob1_HIO_cFv */
daNpc_Ob1_HIO_c::daNpc_Ob1_HIO_c() {
    static hio_prm_c a_prm_tbl = {
        /* mMaxHeadX       */ 0x2000,
        /* mMaxHeadY       */ 0x1388,
        /* mMinHeadX       */ -0x03E8,
        /* mMinHeadY       */ -0x1388,
        /* mMaxBackboneX   */ 0x05DC,
        /* mMaxBackboneY   */ 0x1F40,
        /* mMinBackboneX   */ -0x07D0,
        /* mMinBackboneY   */ -0x1F40,
        /* mMaxTurnStep    */ 0x04B0,
        /* mMaxHeadTurnVel */ 0x04B0,
        /* mAttPosOffsetY  */ 170.0f,
        /* m18             */ 0,
        /* m1A             */ 6,
        /* mWalkTurnStep   */ 0x400,
        /* mWalkAnmRate    */ 0.5f,
        /* mWalkSpeed      */ 3.0f,
        /* mWalkAccel      */ 0.1f,
        /* mPassDist       */ 40.0f,
    };
    memcpy(&mPrm, &a_prm_tbl, sizeof(hio_prm_c));
    mNo = -1;
    m8 = -1;
}

static daNpc_Ob1_HIO_c l_HIO;
static fopAc_ac_c* l_check_inf[20];
static int l_check_wrk;
static u8 l_check_flg;

static char* l_evn_tbl[] = {
    "Get_Rupee",
};

/* 00000198-00000240       .text searchActor_Kb__FPvPv */
static void* searchActor_Kb(void* i_actor, void*) {
    if (l_check_wrk < ARRAY_SSIZE(l_check_inf) && fopAc_IsActor(i_actor) && fopAcM_GetName(i_actor) == fpcNm_KB_e) {
        u8 flag = ((kb_class*)i_actor)->m405;
        if (flag != 0) {
            l_check_flg |= flag;
        }
        l_check_inf[l_check_wrk] = (fopAc_ac_c*)i_actor;
        l_check_wrk++;
    }
    return NULL;
}

/* 00000240-0000028C       .text nodeCallBack_Ob1__FP7J3DNodei */
static BOOL nodeCallBack_Ob1(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        if (j3dSys.getModel()->getUserArea() != 0) {
            ((daNpc_Ob1_c*)j3dSys.getModel()->getUserArea())->nodeOb1Control(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 0000028C-000003DC       .text nodeOb1Control__11daNpc_Ob1_cFP7J3DNodeP8J3DModel */
void daNpc_Ob1_c::nodeOb1Control(J3DNode* i_node, J3DModel* i_model) {
    static cXyz a_eye_pos_off(20.0f, -20.0f, 0.0f);

    s32 jnt_no = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));
    if (jnt_no == m_hed_jnt_num) {
        mDoMtx_stack_c::YrotM(-m_jnt.getHead_y());
        mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
        mDoMtx_stack_c::multVec(&a_eye_pos_off, &mTransformedEyePos);
    }
    if (jnt_no == m_bbone_jnt_num) {
        mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
        mDoMtx_stack_c::ZrotM(m_jnt.getBackbone_x());
    }
    cMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* 00000418-00000498       .text init_OB1_0__11daNpc_Ob1_cFv */
bool daNpc_Ob1_c::init_OB1_0() {
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0520)) {
        set_action(&daNpc_Ob1_c::wait_action1, NULL);
        return true;
    }
    return false;
}

/* 00000498-0000053C       .text init_OB1_1__11daNpc_Ob1_cFv */
bool daNpc_Ob1_c::init_OB1_1() {
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0520) && dKy_daynight_check() == 0) {
        fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
        set_action(&daNpc_Ob1_c::wait_action2, NULL);
        return true;
    }
    return false;
}

/* 0000053C-000005D4       .text init_OB1_2__11daNpc_Ob1_cFv */
bool daNpc_Ob1_c::init_OB1_2() {
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0520) && dKy_daynight_check() == 1) {
        set_action(&daNpc_Ob1_c::wait_action2, NULL);
        return true;
    }
    return false;
}

/* 000005D4-000007A8       .text createInit__11daNpc_Ob1_cFv */
bool daNpc_Ob1_c::createInit() {
    mEventIdTbl[0] = dComIfGp_evmng_getEventIdx(l_evn_tbl[0], 0xFF);

    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xAC;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xAC;
    gravity = -4.5f;
    mHomeAngle = current.angle;
    mHomePos = current.pos;
    mLookPos = mHomePos;

    int weight = 0xFF;
    u8 path_no = (fopAcM_GetParam(this) >> 16) & 0xFF;
    if (path_no != 0xFF) {
        mPath.setInf(path_no, fopAcM_GetRoomNo(this), true);
        if (!mPath.isPath()) {
            return false;
        }
        fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
        weight = 0xD9;
    }

    mEventCut.setActorInfo2("Ob1", this);
    mAnmNum = 8;

    bool init_result;
    switch (mType) {
    case 0:
        init_result = init_OB1_0();
        break;
    case 1:
        init_result = init_OB1_1();
        break;
    case 2:
        init_result = init_OB1_2();
        break;
    default:
        init_result = false;
        break;
    }

    if (init_result) {
        mAngle = current.angle;
        shape_angle = mAngle;
    } else {
        return false;
    }
    mStts.Init(weight, 0xFF, this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);
    mpMorf->setMorf(0.0f);
    setMtx(true);
    return true;
}

/* 000007A8-000008B8       .text setMtx__11daNpc_Ob1_cFb */
void daNpc_Ob1_c::setMtx(bool i_setEyePos) {
    if (!mbDemo) {
        plyTexPttrnAnm();
        mbMorfAnimStopped = mpMorf->play(&eyePos, 0, 0);
        if (mpMorf->getFrame() < mPrevMorfFrame) {
            mbMorfAnimStopped = true;
        }
        mPrevMorfFrame = mpMorf->getFrame();
        mObjAcch.CrrPos(*dComIfG_Bgsp());
    }
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(mAngle.y);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    mpHeadModel->setBaseTRMtx(mpMorf->getModel()->getAnmMtx(m_hed_jnt_num));
    mpHeadModel->calc();
    setAttention(i_setEyePos);
}

/* 000008B8-000008CC       .text anmNum_toResID__11daNpc_Ob1_cFi */
int daNpc_Ob1_c::anmNum_toResID(int i_anmNum) {
    static const int a_bck_resID_tbl[] = {
        dRes_ID_OB_BCK_WAIT_e,
        dRes_ID_OB_BCK_TALK_e,
        dRes_ID_OB_BCK_THANK_e,
        dRes_ID_OB_BCK_WALK_e,
        dRes_ID_OB_BCK_THANK02_e,
        dRes_ID_OB_BCK_LAUGH_e,
        dRes_ID_OB_BCK_SHUTUP01_e,
        dRes_ID_OB_BCK_SHUTUP02_e,
    };
    return a_bck_resID_tbl[i_anmNum];
}

/* 000008CC-000008E0       .text btpNum_toResID__11daNpc_Ob1_cFi */
int daNpc_Ob1_c::btpNum_toResID(int i_btpNum) {
    static const int a_btp_resID_tbl[] = {
        dRes_ID_OB_BTP_MABA_A_e,
        dRes_ID_OB_BTP_MABA_A_e,
    };
    return a_btp_resID_tbl[i_btpNum];
}

/* 00000780-00000890       .text setBtp__11daNpc_Ob1_cFbi */
bool daNpc_Ob1_c::setBtp(bool i_modify, int i_btpNum) {
    J3DModelData* model_data = mpHeadModel->getModelData();
    m_hed_tex_pttrn = (J3DAnmTexPattern*)dComIfG_getObjectIDRes("Ob", btpNum_toResID(i_btpNum));
    JUT_ASSERT(0x1FF, m_hed_tex_pttrn != NULL);

    if (mBtpAnm.init(model_data, m_hed_tex_pttrn, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, i_modify, 0)) {
        mBtpFrame = 0;
        mBlinkTimer = 0;
        return true;
    }
    return false;
}

/* 00000890-000008B8       .text iniTexPttrnAnm__11daNpc_Ob1_cFb */
bool daNpc_Ob1_c::iniTexPttrnAnm(bool i_modify) {
    return setBtp(i_modify, mBtpNum);
}

/* 000008B8-00000964       .text plyTexPttrnAnm__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::plyTexPttrnAnm() {
    if (mBtpNum != 0 || !cLib_calcTimer(&mBlinkTimer)) {
        mBtpFrame++;
        if (mBtpFrame >= m_hed_tex_pttrn->getFrameMax()) {
            if (mBtpNum != 0) {
                mBtpFrame = m_hed_tex_pttrn->getFrameMax();
            } else {
                mBlinkTimer = 30.0f + cM_rndF(60.0f);
                mBtpFrame = 0;
            }
        }
    }
}

/* 00000964-000009A0       .text setAnm_tex__11daNpc_Ob1_cFSc */
void daNpc_Ob1_c::setAnm_tex(s8 i_btpNum) {
    if (mBtpNum != i_btpNum) {
        mBtpNum = i_btpNum;
        iniTexPttrnAnm(true);
    }
}

/* 00000B4C-00000BF0       .text setAnm_anm__11daNpc_Ob1_cFPQ211daNpc_Ob1_c9anm_prm_c */
BOOL daNpc_Ob1_c::setAnm_anm(anm_prm_c* i_anmPrmP) {
    if (mAnmNum == i_anmPrmP->mAnmNum) {
        return TRUE;
    }
    mAnmNum = i_anmPrmP->mAnmNum;
    dNpc_setAnmIDRes(mpMorf, i_anmPrmP->mLoopMode, i_anmPrmP->mMorf, i_anmPrmP->mSpeed, anmNum_toResID(mAnmNum), -1, "Ob");
    mPrevMorfFrame = mLoopCount = mbMorfAnimStopped = 0;
    return TRUE;
}

/* 00000BF0-00000C5C       .text setAnm_NUM__11daNpc_Ob1_cFii */
void daNpc_Ob1_c::setAnm_NUM(int i_anmNum, int i_setBtp) {
    static anm_prm_c a_anm_prm_tbl[8] = {
        {0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 0},
        {1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 0},
        {2, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE, 0},
        {3, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 0},
        {4, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 0},
        {5, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 0},
        {6, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE, 0},
        {7, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 0},
    };
    if (i_setBtp) {
        setAnm_tex(a_anm_prm_tbl[i_anmNum].mBtpNum);
    }
    setAnm_anm(&a_anm_prm_tbl[i_anmNum]);
}

/* 00000C5C-00000CDC       .text setAnm__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::setAnm() {
    static anm_prm_c a_anm_prm_tbl[7] = {
        {-1, -1, 0.0f, 0.0f, -1, 0},
        {0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 0},
        {-1, -1, 0.0f, 0.0f, -1, 0},
        {3, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 0},
        {0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 0},
        {1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 0},
        {-1, -1, 0.0f, 0.0f, -1, 0},
    };
    if (a_anm_prm_tbl[mStt].mBtpNum >= 0) {
        setAnm_tex(a_anm_prm_tbl[mStt].mBtpNum);
    }
    if (a_anm_prm_tbl[mStt].mAnmNum >= 0) {
        setAnm_anm(&a_anm_prm_tbl[mStt]);
    }
    return TRUE;
}

/* 00000CDC-00000CE0       .text chg_anmTag__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::chg_anmTag() {
    switch (mMesgAnimeTag) {
    case 0xFF:
        break;
    }
}

/* 00000CE0-00000CE4       .text control_anmTag__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::control_anmTag() {
    switch (mMesgAnimeTag) {
    case 0xFF:
        break;
    }
}

/* 00000CE4-00000DF4       .text chg_anmAtr__11daNpc_Ob1_cFUc */
void daNpc_Ob1_c::chg_anmAtr(u8 i_atr) {
    if (mManzaiMsgNo != -1) {
        switch (mManzaiMsgNo) {
        case 0xAFC:
        case 0xAFD:
        case 0xAFF:
        case 0xB02:
        case 0xB05:
        case 0xB06:
        case 0xB09:
        case 0xB0C:
        case 0xB0D:
        case 0xB5D:
        case 0xB61:
        case 0xB64:
        case 0xB65:
            mLookMode = 1;
            mbHeadOnly = false;
            m_jnt.setTrn();
            break;
        case 0xAFE:
            break;
        }
    }
    if (i_atr >= 7 || i_atr == mAnmAtr) {
        return;
    }
    mAnmAtr = i_atr;
    setAnm_ATR(1);
}

/* 00000DF4-00000E8C       .text control_anmAtr__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::control_anmAtr() {
    switch (mAnmAtr) {
    case 3:
        if (mbMorfAnimStopped) {
            setAnm_NUM(4, 1);
            mAnmAtr = 7;
        }
        break;
    case 6:
        if (mbMorfAnimStopped) {
            setAnm_NUM(7, 1);
            mAnmAtr = 7;
        }
        break;
    case 2:
        break;
    }
}

/* 00000E8C-00000EF4       .text setAnm_ATR__11daNpc_Ob1_cFi */
void daNpc_Ob1_c::setAnm_ATR(int i_setBtp) {
    static anm_prm_c a_anm_prm_tbl[7] = {
        {0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 0},
        {1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 0},
        {2, 1, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE, 0},
        {2, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE, 0},
        {4, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 0},
        {5, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 0},
        {6, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE, 0},
    };
    if (i_setBtp != 0) {
        setAnm_tex(a_anm_prm_tbl[mAnmAtr].mBtpNum);
    }
    setAnm_anm(&a_anm_prm_tbl[mAnmAtr]);
}

/* 00000EF4-00000FF0       .text anmAtr__11daNpc_Ob1_cFUs */
void daNpc_Ob1_c::anmAtr(u16 i_msgStatus) {
    dComIfG_MesgCamInfo_c* caminfo = dComIfGp_getMesgCameraInfo();
    if (mManzaiState == 2 && this != caminfo->mActor[caminfo->mBasicID - 1]) {
        control_anmTag();
        control_anmAtr();
        return;
    }

    switch (i_msgStatus) {
    case fopMsgStts_MSG_TYPING_e: {
        if (mMsgCount == 0) {
            mAnmAtr = 0xFF;
            chg_anmAtr(dComIfGp_getMesgAnimeAttrInfo());
            mMsgCount++;
        }
        u32 mesg_anime_tag = dComIfGp_getMesgAnimeTagInfo();
        dComIfGp_clearMesgAnimeTagInfo();
        if (mesg_anime_tag != 0xFF && mMesgAnimeTag != mesg_anime_tag) {
            mMesgAnimeTag = mesg_anime_tag;
            chg_anmTag();
        }
        break;
    }
    case fopMsgStts_MSG_DISPLAYED_e:
        mMsgCount = 0;
        break;
    }
    control_anmTag();
    control_anmAtr();
}

/* 00000E2C-00000EC4       .text eventOrder__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::eventOrder() {
    s8 order = mOrder;
    if (order == 1 || order == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
                if (mOrder == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (order >= 3) {
        mEventIdx = order - 3;
        fopAcM_orderOtherEventId(this, mEventIdTbl[mEventIdx]);
    }
}

/* 00000EC4-00000F5C       .text checkOrder__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (dComIfGp_evmng_startCheck(mEventIdTbl[mEventIdx])) {
            mOrder = 0;
        }
    } else if (eventInfo.checkCommandTalk()) {
        if (mOrder == 1 || mOrder == 2) {
            mOrder = 0;
            mbTalkReq = true;
        }
    }
}

/* 00001130-000011B8       .text chk_talk__11daNpc_Ob1_cFv */
bool daNpc_Ob1_c::chk_talk() {
    bool ret = false;
    if (dComIfGp_event_chkTalkXY()) {
        if (dComIfGp_evmng_ChkPresentEnd()) {
            mItemNo = dComIfGp_event_getPreItemNo();
            ret = true;
        }
    } else {
        mItemNo = 0xFF;
        ret = true;
    }
    return ret;
}

/* 00001008-00001048       .text chk_partsNotMove__11daNpc_Ob1_cFv */
bool daNpc_Ob1_c::chk_partsNotMove() {
    return mJointHeadY == m_jnt.getHead_y() && mJointBackboneY == m_jnt.getBackbone_y() && mActorAngleY == current.angle.y;
}

/* 00001168-00001308       .text lookBack__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::lookBack() {
    cXyz dstPos;
    cXyz* dstPos_p;
    cXyz src_pos;
    s16 desiredYrot;
    mJointHeadY = m_jnt.getHead_y();
    mJointBackboneY = m_jnt.getBackbone_y();
    mActorAngleY = current.angle.y;
    src_pos.x = current.pos.x;
    src_pos.y = current.pos.y;
    src_pos.z = current.pos.z;
    src_pos.y = eyePos.y;
    dstPos.set(0.0f, 0.0f, 0.0f);
    dstPos_p = NULL;
    desiredYrot = current.angle.y;
    bool headOnlyFollow = mbHeadOnly;

    switch (mLookMode) {
    case 1:
        dstPos = dNpc_playerEyePos(-20.0f);
        dstPos_p = &dstPos;
        src_pos.x = current.pos.x;
        src_pos.y = current.pos.y;
        src_pos.z = current.pos.z;
        src_pos.y = eyePos.y;
        break;
    case 2:
        dstPos.set(mLookPos);
        dstPos_p = &dstPos;
        src_pos.x = current.pos.x;
        src_pos.y = current.pos.y;
        src_pos.z = current.pos.z;
        src_pos.y = eyePos.y;
        break;
    case 3:
        desiredYrot = mTargetAngleY;
        break;
    }
    cLib_addCalcAngleS2(&mLookAtMaxVel, l_HIO.mPrm.mMaxHeadTurnVel, 4, 0x800);
    if (!m_jnt.trnChk()) {
        mLookAtMaxVel = 0;
    }
    m_jnt.lookAtTarget(&current.angle.y, dstPos_p, src_pos, desiredYrot, mLookAtMaxVel, headOnlyFollow);
}

/* 00001398-000014BC       .text next_msgStatus__11daNpc_Ob1_cFPUl */
u16 daNpc_Ob1_c::next_msgStatus(u32* o_msgNoP) {
    u16 ret = fopMsgStts_MSG_CONTINUES_e;
    switch (*o_msgNoP) {
    case 0xA8D:
        *o_msgNoP = 0xA8E;
        break;
    case 0xA90:
        *o_msgNoP = 0xA91;
        break;
    case 0xA93:
        *o_msgNoP = 0xA94;
        break;
    case 0xA97:
        *o_msgNoP = 0xA98;
        break;
    case 0xA92:
    case 0xA96:
    case 0xA9B:
    case 0xA9D:
    case 0xAA0:
    case 0xAA2:
    case 0xAA3:
    case 0xAA4:
    case 0xAA5:
    case 0xAA6:
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0E20) && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_0308)) {
            *o_msgNoP = 0xAA7;
            break;
        }
        goto msg_end;
    case 0xAA8:
        if (dKy_daynight_check() == 0) {
            *o_msgNoP = 0xAA9;
        } else {
            *o_msgNoP = 0xAAA;
        }
        break;
    case 0xAAD:
    case 0xAAE:
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0304)) {
            *o_msgNoP = 0xA8F;
        } else {
            *o_msgNoP = 0xA8D;
        }
        break;
    default:
    msg_end:
        ret = fopMsgStts_MSG_ENDS_e;
        break;
    }
    return ret;
}

/* 000014BC-000017EC       .text getMsg_OB1_0__11daNpc_Ob1_cFv */
u32 daNpc_Ob1_c::getMsg_OB1_0() {
    u32 msg = 0;
    if (mFoundPigNum != 0 || mPigNum != 0) {
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0302)) {
            if (mNewPigNum != 0) {
                if (mPigNum == 2) {
                    if (mMsgStep != 0) {
                        msg = 0xAA2;
                        mMsgStep = 0;
                    } else {
                        msg = 0xAA1;
                        mMsgStep = 1;
                    }
                } else {
                    switch (mNewPigNum) {
                    case 1:
                        if (mMsgStep == 1) {
                            msg = 0xA9D;
                            mMsgStep = 0;
                        } else {
                            msg = 0xA9C;
                            mMsgStep = 1;
                        }
                        break;
                    case 2:
                        if (mMsgStep == 2) {
                            msg = 0xA9F;
                            mMsgStep = 1;
                        } else if (mMsgStep == 1) {
                            msg = 0xAA0;
                            mMsgStep = 0;
                        } else {
                            msg = 0xA9E;
                            mMsgStep = 2;
                        }
                        break;
                    }
                }
            } else if (mPigNum > mFoundPigNum) {
                msg = 0xAA3;
            } else {
                switch (mFoundPigNum) {
                case 1:
                    msg = 0xAA4;
                    break;
                case 2:
                    msg = 0xAA5;
                    break;
                default:
                    msg = 0xAA6;
                    break;
                }
            }
        } else {
            switch (mNewPigNum) {
            case 1:
                if (mMsgStep == 1) {
                    msg = 0xA92;
                    mMsgStep = 0;
                } else {
                    msg = 0xA90;
                    mMsgStep = 1;
                }
                break;
            case 2:
                if (mMsgStep == 2) {
                    msg = 0xA95;
                    mMsgStep = 1;
                } else if (mMsgStep == 1) {
                    msg = 0xA96;
                    mMsgStep = 0;
                } else {
                    msg = 0xA93;
                    mMsgStep = 2;
                }
                break;
            case 3:
                if (mMsgStep == 3) {
                    msg = 0xA99;
                    mMsgStep = 2;
                } else if (mMsgStep == 2) {
                    msg = 0xA9A;
                    mMsgStep = 1;
                } else if (mMsgStep == 1) {
                    msg = 0xA9B;
                    mMsgStep = 0;
                } else {
                    msg = 0xA97;
                    mMsgStep = 3;
                }
                break;
            }
            m7EC = true;
        }
        return msg;
    }

    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2A80)) {
        if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2C40)) {
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_2C40);
            return 0xAAD;
        }
    } else if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2C80)) {
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_2C80);
        return 0xAAE;
    }
    return dComIfGs_isEventBit(dSv_event_flag_c::UNK_0304) ? 0xA8F : 0xA8D;
}

/* 000017EC-0000184C       .text getMsg_OB1_1__11daNpc_Ob1_cFv */
u32 daNpc_Ob1_c::getMsg_OB1_1() {
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2C20)) {
        return 0xAA8;
    }
    return (dComIfGs_getEventReg(dSv_event_flag_c::UNK_B6FF) != 0 ? -1 : 0) + 0xAAC;
}

/* 0000184C-0000186C       .text getMsg_OB1_2__11daNpc_Ob1_cFv */
u32 daNpc_Ob1_c::getMsg_OB1_2() {
    return getMsg_OB1_1();
}

/* 0000186C-000018E8       .text getMsg__11daNpc_Ob1_cFv */
u32 daNpc_Ob1_c::getMsg() {
    u32 msg = 0;
    switch (mType) {
    case 0:
        msg = getMsg_OB1_0();
        break;
    case 1:
        msg = getMsg_OB1_1();
        break;
    case 2:
        msg = getMsg_OB1_2();
        break;
    }
    return msg;
}

/* 000016A8-00001728       .text chkAttention__11daNpc_Ob1_cFv */
bool daNpc_Ob1_c::chkAttention() {
    dAttention_c& attention = dComIfGp_getAttention();
    if (attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    }
    return this == attention.ActionTarget(0);
}

/* 00001968-000019C4       .text setAttention__11daNpc_Ob1_cFb */
void daNpc_Ob1_c::setAttention(bool i_setEyePos) {
    attention_info.position.set(current.pos.x, current.pos.y + l_HIO.mPrm.mAttPosOffsetY, current.pos.z);

    if (!mbSetEyePos && !i_setEyePos) {
        return;
    }

    eyePos.set(mTransformedEyePos.x, mTransformedEyePos.y, mTransformedEyePos.z);
}

/* 00001790-000017C4       .text searchByID__11daNpc_Ob1_cFUi */
fopAc_ac_c* daNpc_Ob1_c::searchByID(fpc_ProcID i_procID) {
    fopAc_ac_c* actor_p = NULL;
    fopAcM_SearchByID(i_procID, &actor_p);
    return actor_p;
}

/* 000019F8-000019FC       .text partner_srch__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::partner_srch() {
    if (mActionState == 1) {
        return;
    }
}

/* 000019FC-00001A34       .text bitCount__11daNpc_Ob1_cFUc */
s8 daNpc_Ob1_c::bitCount(u8 i_bits) {
    s8 count = 0;
    for (int i = 0; i < 8; i++) {
        if (i_bits & 1) {
            count += 1;
        }
        i_bits = i_bits >> 1;
    }
    return count;
}

/* 00001A34-00001B1C       .text set_pigCnt__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::set_pigCnt() {
    mPigNum = bitCount(dComIfGs_getEventReg(dSv_event_flag_c::UNK_B6FF));
    l_check_wrk = 0;
    l_check_flg = 0;
    for (int i = 0; i < ARRAY_SSIZE(l_check_inf); i++) {
        l_check_inf[i] = NULL;
    }
    fpcM_Search(searchActor_Kb, this);
    mFoundPigNum = bitCount(l_check_flg);
    mNewPigNum = bitCount(l_check_flg & ~dComIfGs_getEventReg(dSv_event_flag_c::UNK_B6FF));
    mMsgStep = 0;
}

/* 00001B1C-00001BC4       .text ob_setPthPos__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::ob_setPthPos() {
    if (mPath.isPath()) {
        current.pos = mPath.getPoint(mPath.getIdx());
        mPath.nextIdxAuto();
        cXyz next = mPath.getPoint(mPath.getIdx());
        current.angle.y = cLib_targetAngleY(&current.pos, &next);
    }
}

/* 00001BC4-00001C44       .text get_attPos__11daNpc_Ob1_cFv */
cXyz daNpc_Ob1_c::get_attPos() {
    cXyz pos;
    dPath* path = mPath.nextPath(fopAcM_GetRoomNo(this));
    if (path != NULL) {
        u8 idx = mPath.getIdx();
        if (idx == 0) {
            idx = mPath.maxPoint();
        }
        dPnt* pnt = &path->m_points[(u8)(idx - 1)];
        pos.set(pnt->m_position.x, pnt->m_position.y, pnt->m_position.z);
    }
    return pos;
}

/* 000019AC-00001B1C       .text ob_movPass__11daNpc_Ob1_cFv */
int daNpc_Ob1_c::ob_movPass() {
    int ret = 0;
    if (mPath.getPath() != NULL && dPath_ChkClose(mPath.getPath())) {
        if (mPath.chkPointPass(current.pos, mPath.getDir())) {
            mPath.nextIdxAuto();
            ret = 1;
        }
        return ret;
    }

    if ((mTargetPos - current.pos).absXZ() <= mPassDist) {
        ret = 1;
        if (mPath.getPath() != NULL && !mPath.nextIdxAuto()) {
            ret = 2;
        }
    }
    return ret;
}

/* 00001DB4-00001E44       .text ob_clcMovSpd__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::ob_clcMovSpd() {
    (mTargetPos - current.pos).abs2XZ();
    cLib_chaseAngleS(&current.angle.y, cLib_targetAngleY(&current.pos, &mTargetPos), l_HIO.mPrm.mWalkTurnStep);
    cLib_chaseF(&speedF, mTargetSpeed, mAccel);
}

/* 00001E44-00001F24       .text ob_nMove__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::ob_nMove() {
    f32 rate;
    switch (mMoveMode) {
    case 1:
        ob_clcMovSpd();
        if (mMoveMode == 1) {
            rate = speedF * l_HIO.mPrm.mWalkAnmRate;
        }
        if (rate < 0.5f) {
            rate = 0.5f;
        }
        mpMorf->setPlaySpeed(rate);
        switch (ob_movPass()) {
        case 1:
            mbPassed = true;
            break;
        case 2:
            mbPassed = true;
            mMoveMode = 0;
            break;
        }
        break;
    }
    if (mbPassed) {
        mbNoMove = true;
    }
}

/* 00001F24-00001F78       .text charDecide__11daNpc_Ob1_cFi */
bool daNpc_Ob1_c::charDecide(int i_type) {
    mHioType = 0;
    mType = -1;
    switch (i_type) {
    case 1:
        mType = 1;
        break;
    case 2:
        mType = 2;
        break;
    default:
        mType = 0;
        break;
    }
    return true;
}

/* 00001F78-00001FC4       .text event_actionInit__11daNpc_Ob1_cFi */
void daNpc_Ob1_c::event_actionInit(int i_staffIdx) {
    int* act_no_p = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "ActNo");
    if (act_no_p != NULL) {
        mActNo = *act_no_p;
    }
}

/* 00001FC4-00001FCC       .text event_action__11daNpc_Ob1_cFv */
bool daNpc_Ob1_c::event_action() {
    switch (mActNo) {
    case 0:
        break;
    }
    return true;
}

/* 00001FF4-000020E0       .text privateCut__11daNpc_Ob1_cFi */
void daNpc_Ob1_c::privateCut(int i_staffIdx) {
    static char* a_cut_tbl[] = {
        "ACTION",
    };

    if (i_staffIdx == -1) {
        return;
    }

    mActionIndex = dComIfGp_evmng_getMyActIdx(i_staffIdx, a_cut_tbl, ARRAY_SIZE(a_cut_tbl), TRUE, 0);
    if (mActionIndex == -1) {
        dComIfGp_evmng_cutEnd(i_staffIdx);
    } else {
        if (dComIfGp_evmng_getIsAddvance(i_staffIdx)) {
            switch (mActionIndex) {
            case 0:
                event_actionInit(i_staffIdx);
                break;
            }
        }
        bool end_cut;
        switch (mActionIndex) {
        case 0:
            end_cut = event_action();
            break;
        default:
            end_cut = true;
            break;
        }
        if (end_cut) {
            dComIfGp_evmng_cutEnd(i_staffIdx);
        }
    }
}

/* 000020E0-00002100       .text endEvent__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::endEvent() {
    dComIfGp_event_reset();
    mAnmAtr = 0xFF;
}

/* 00002100-00002138       .text isEventEntry__11daNpc_Ob1_cFv */
int daNpc_Ob1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName(), NULL);
}

/* 000020F0-0000216C       .text event_proc__11daNpc_Ob1_cFi */
void daNpc_Ob1_c::event_proc(int i_staffIdx) {
    if (dComIfGp_evmng_endCheck(mEventIdTbl[mEventIdx])) {
        mOrder = 1;
        endEvent();
        return;
    }

    if (!mEventCut.cutProc()) {
        privateCut(i_staffIdx);
    }
    lookBack();
}

/* 00002268-00002314       .text set_action__11daNpc_Ob1_cFM11daNpc_Ob1_cFPCvPvPv_iPv */
BOOL daNpc_Ob1_c::set_action(ProcFunc i_newProcFunc, void* i_argsP) {
    if (mCurrProcFunc != i_newProcFunc) {
        if (mCurrProcFunc) {
            mActionState = 0;
            (this->*mCurrProcFunc)(i_argsP);
        }
        mCurrProcFunc = i_newProcFunc;
        mActionState = 0;
        (this->*mCurrProcFunc)(i_argsP);
    }
    return TRUE;
}

/* 00002218-00002234       .text clrSpd__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::clrSpd() {
    mTargetSpeed = 0.0f;
    mAccel = 0.0f;
    speedF = 0.0f;
    gravity = -4.5f;
}

/* 00002234-00002488       .text setStt__11daNpc_Ob1_cFSc */
void daNpc_Ob1_c::setStt(s8 i_stt) {
    searchByID(mPartnerID);
    s8 prev_stt = mStt;
    mTalkTimer = 0;
    mStt = i_stt;
    switch (mStt) {
    case 0:
        break;
    case 4:
        mWaitTimer = cLib_getRndValue(90, 180);
    case 1:
    case 5:
        if (prev_stt != 2) {
            switch (mStt) {
            case 1:
                mLookMode = 3;
                mTargetAngleY = mHomeAngle.y;
                break;
            case 4:
                mLookMode = 2;
                mLookPos = get_attPos();
                break;
            case 5:
                mLookMode = 1;
                break;
            }
            m_jnt.setTrn();
            mbHeadOnly = false;
        }
        mOrder = 0;
        mMoveMode = 0;
        clrSpd();
        break;
    case 2:
        mLookMode = 1;
        m_jnt.setTrn();
        mbHeadOnly = false;
        mOrder = 0;
        mMoveMode = 0;
        clrSpd();
        mAnmAtr = 0xFF;
        if (prev_stt != 5) {
            mPrevStt = prev_stt;
        }
        set_pigCnt();
        break;
    case 3:
        mTargetPos = mPath.getPoint(mPath.getIdx());
        mLookMode = 0;
        mbHeadOnly = true;
        mOrder = 0;
        mMoveMode = 1;
        mbPassed = false;
        gravity = -4.5f;
        mTargetSpeed = l_HIO.mPrm.mWalkSpeed;
        mAccel = l_HIO.mPrm.mWalkAccel;
        mPassDist = l_HIO.mPrm.mPassDist;
        break;
    case 6:
        mAnmAtr = 0xFF;
        mPrevStt = prev_stt;
        return;
    }
    setAnm();
}

/* 00002488-00002560       .text wait_1__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::wait_1() {
    if (mbTalkReq) {
        if (chk_talk()) {
            setStt(2);
        }
        return TRUE;
    }

    if (mManzaiState == 1) {
        mManzaiState = 2;
        setStt(6);
        mLookMode = 3;
        mTargetAngleY = mHomeAngle.y;
        return TRUE;
    }

    mOrder = 2;
    if (mbAttention) {
        mTalkTimer = 60;
    }
    if (cLib_calcTimer(&mTalkTimer) != 0) {
        mLookMode = 1;
    } else {
        mLookMode = 3;
        mTargetAngleY = mHomeAngle.y;
        m_jnt.setTrn();
    }
    return TRUE;
}

/* 00002560-00002648       .text wait_2__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::wait_2() {
    if (mbTalkReq) {
        if (chk_talk()) {
            setStt(2);
        }
        return TRUE;
    }

    mOrder = 2;
    if (mbAttention) {
        mTalkTimer = 60;
    }
    if (cLib_calcTimer(&mTalkTimer) != 0) {
        mLookMode = 1;
    } else {
        if (cLib_calcTimer(&mWaitTimer) == 0) {
            setStt(3);
            return TRUE;
        }
        mLookMode = 2;
        mLookPos = get_attPos();
        m_jnt.setTrn();
    }
    return TRUE;
}

/* 00002648-000026EC       .text wait_3__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::wait_3() {
    if (mbTalkReq) {
        if (chk_talk()) {
            setStt(2);
        }
        return TRUE;
    }

    if (mbMorfAnimStopped) {
        mLoopCount++;
        if (mLoopCount > 3) {
            setStt(mPrevStt);
            return TRUE;
        }
    }

    mOrder = 2;
    mLookMode = 1;
    m_jnt.setTrn();
    return TRUE;
}

/* 000026EC-00002804       .text walk_1__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::walk_1() {
    if (mbTalkReq) {
        setAnm_NUM(0, 1);
        speedF = 0.0f;
        if (chk_talk()) {
            setStt(2);
        }
        return TRUE;
    }

    mOrder = 2;
    if (mbAttention) {
        mTalkTimer = 20;
    }
    if (cLib_calcTimer(&mTalkTimer) != 0) {
        mLookMode = 1;
    } else {
        mLookMode = 0;
    }

    if (mbPassed) {
        if (mPath.getIdx() == 0) {
            mPath.nextIdxAuto();
        }
        setStt(4);
        return TRUE;
    }

    mbPassed = false;
    mTargetPos = mPath.getPoint(mPath.getIdx());
    return TRUE;
}

/* 00002804-00002A50       .text talk_1__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::talk_1() {
    BOOL res = chk_partsNotMove();
    if (mOrder == 1 || mOrder >= 3) {
        return TRUE;
    }

    if (mpCurrMsg != NULL) {
        mPrevMsgStatus = mpCurrMsg->mStatus;
    } else {
        mPrevMsgStatus = 0;
    }

    if (m7ED && mCurrMsgBsPcId == fpcM_ERROR_PROCESS_ID_e) {
        mCurrMsgNo = getMsg();
        mCurrMsgBsPcId = fopMsgM_messageSet(mCurrMsgNo, dComIfGp_getMesgCameraInfo()->mActor[0]);
        mpCurrMsg = NULL;
    } else {
        mManzaiMsgNo = -1;
        fopNpc_npc_c::talk(1);
    }

    if (mpCurrMsg != NULL) {
        switch (mpCurrMsg->mStatus) {
        case fopMsgStts_BOX_OPENING_e:
        case fopMsgStts_MSG_TYPING_e:
            break;
        case fopMsgStts_MSG_DESTROYED_e:
            if (mMsgStep != 0) {
                mOrder = 3;
                setAnm_NUM(0, 1);
                endEvent();
                return res;
            }
            l_check_flg |= dComIfGs_getEventReg(dSv_event_flag_c::UNK_B6FF);
            dComIfGs_setEventReg(dSv_event_flag_c::UNK_B6FF, l_check_flg);
            switch (mCurrMsgNo) {
            case 0xA8E:
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_0304);
                break;
            case 0xAA7:
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_0308);
                break;
            case 0xAA9:
            case 0xAAA:
            case 0xAAB:
            case 0xAAC:
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_2C20);
                break;
            }
            if (m7EC) {
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_0302);
            }
            mItemNo = 0xFF;
            mbTalkReq = false;
            switch (mType) {
            case 0:
                setStt(5);
                break;
            default:
                setStt(mPrevStt);
                mTalkTimer = 60;
                break;
            }
            endEvent();
            break;
        }
    }
    return res;
}

/* 00002A50-00002B58       .text manzai__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::manzai() {
    dComIfG_MesgCamInfo_c* caminfo = dComIfGp_getMesgCameraInfo();
    switch (mManzaiState) {
    case 2: {
        fopNpc_npc_c* partner_p = (fopNpc_npc_c*)searchByID(mManzaiPartnerID);
        if (this != caminfo->mActor[caminfo->mBasicID - 1]) {
            if (mAnmAtr != 0xFF) {
                mLookMode = 3;
                mTargetAngleY = mHomeAngle.y;
                m_jnt.setTrn();
                mStt = mPrevStt;
                setAnm();
                mStt = 6;
                mAnmAtr = 0xFF;
            }
        } else {
            mManzaiMsgNo = partner_p->mCurrMsgNo;
            anmAtr(partner_p->mManzaiMsgStatus);
        }
        break;
    }
    case 3:
        fopAcM_OffStatus(this, fopAcStts_UNK4000_e);
        setStt(mPrevStt);
        mManzaiState = 0;
        break;
    }
    return TRUE;
}

/* 00002B58-00002C44       .text wait_action1__11daNpc_Ob1_cFPv */
BOOL daNpc_Ob1_c::wait_action1(void*) {
    switch (mActionState) {
    case 0:
        ob_setPthPos();
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
        case 4:
            mbSetEyePos = wait_2();
            break;
        case 5:
            mbSetEyePos = wait_3();
            break;
        case 3:
            mbSetEyePos = walk_1();
            break;
        case 2:
            mbSetEyePos = talk_1();
            break;
        }
        lookBack();
        break;
    default:
        break;
    }
    return TRUE;
}

/* 00002C44-00002D18       .text wait_action2__11daNpc_Ob1_cFPv */
BOOL daNpc_Ob1_c::wait_action2(void*) {
    switch (mActionState) {
    case 0:
        setStt(1);
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
        case 6:
            mbSetEyePos = manzai();
            break;
        }
        lookBack();
        break;
    default:
        break;
    }
    return TRUE;
}

/* 00002B2C-00002C6C       .text demo__11daNpc_Ob1_cFv */
bool daNpc_Ob1_c::demo() {
    if (demoActorID == 0) {
        if (mbDemo) {
            mbDemo = false;
        }
    } else {
        mbDemo = true;
        dDemo_actor_c* demo_actor_p = dComIfGp_demo_getActor(demoActorID);
        if (m_hed_tex_pttrn) {
            mBtpFrame++;
            if (mBtpFrame >= m_hed_tex_pttrn->getFrameMax()) {
                mBtpFrame = m_hed_tex_pttrn->getFrameMax();
            }
        }
        J3DAnmTexPattern* demo_btp_p = demo_actor_p->getP_BtpData("Ob");
        if (demo_btp_p) {
            m_hed_tex_pttrn = demo_btp_p;
            if (mBtpAnm.init(mpHeadModel->getModelData(), m_hed_tex_pttrn, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, FALSE)) {
                mBtpNum = 2;
                mBtpFrame = 0;
            }
        }
        dDemo_setDemoData(this, 0x6A, mpMorf, "Ob");
    }
    return mbDemo;
}

/* 00002E58-00002EF0       .text shadowDraw__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::shadowDraw() {
    cXyz pos(current.pos.x, current.pos.y + 150.0f, current.pos.z);

    mShadowID = dComIfGd_setShadow(mShadowID, 1, mpMorf->getModel(), &pos, 800.0f, 40.0f, current.pos.y, mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr, 0, 1.0f, dDlst_shadowControl_c::getSimpleTex());
    if (mShadowID != 0) {
        dComIfGd_addRealShadow(mShadowID, mpHeadModel);
    }
}

static void dummy() {
    const GXColor dummy1 = {0xFF, 0x00, 0x00, 0x80};
    const GXColor dummy2 = {0x00, 0x00, 0xFF, 0x80};
    const GXColor dummy3 = {0x00, 0xFF, 0x00, 0x80};
}

/* 00002EF0-00003014       .text _draw__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::_draw() {
    J3DModel* head_model_p = mpHeadModel;
    J3DModelData* head_model_data = head_model_p->getModelData();
    J3DModel* model = mpMorf->getModel();

    if (mbHide || m7F1) {
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(model, &tevStr);
    mpMorf->entryDL();

    mBtpAnm.entry(head_model_data, mBtpFrame);
    mDoExt_modelEntryDL(head_model_p);
    mBtpAnm.remove(head_model_data);
    g_env_light.setLightTevColorType(head_model_p, &tevStr);

    shadowDraw();
    dSnap_RegistFig(DSNAP_TYPE_UNK4F, this, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 00002E24-00003008       .text _execute__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::_execute() {
    if (!mbInitDone) {
        mHomePos = current.pos;
        mHomeAngle = current.angle;
        mbInitDone = true;
    }
    m_jnt.setParam(
        l_HIO.mPrm.mMaxBackboneX, l_HIO.mPrm.mMaxBackboneY, l_HIO.mPrm.mMinBackboneX, l_HIO.mPrm.mMinBackboneY,
        l_HIO.mPrm.mMaxHeadX, l_HIO.mPrm.mMaxHeadY, l_HIO.mPrm.mMinHeadX, l_HIO.mPrm.mMinHeadY,
        l_HIO.mPrm.mMaxTurnStep
    );
    if (mbHide && demoActorID == 0) {
        return TRUE;
    }
    mbNoMove = false;
    mbHide = false;
    partner_srch();
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
        if (!mbNoMove) {
            ob_nMove();
            fopAcM_posMoveF(this, mStts.GetCCMoveP());
        }
        if (!m7EF) {
            mAngle = current.angle;
            shape_angle = mAngle;
        }
    }
    eventOrder();
    setMtx(false);
    if (!mbDemo) {
        setCollision(80.0f, 160.0f);
    }
    return TRUE;
}

/* 00003008-00003064       .text _delete__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::_delete() {
    dComIfG_resDelete(&mPhs, "Ob");
    if (heap != NULL && mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }
    return TRUE;
}

/* 00003064-00003084       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Ob1_c*)i_this)->CreateHeap();
}

daNpc_Ob1_c::daNpc_Ob1_c() {}

/* 000032A8-000033C8       .text _create__11daNpc_Ob1_cFv */
cPhs_State daNpc_Ob1_c::_create() {
    static int a_size_tbl[] = {
        0x272E0,
    };

    fopAcM_ct(this, daNpc_Ob1_c);
    cPhs_State state = dComIfG_resLoad(&mPhs, "Ob");
    if (state != cPhs_COMPLEATE_e) {
        return state;
    }
    if (!charDecide(fopAcM_GetParam(this) & 0xFF)) {
        return cPhs_ERROR_e;
    }
    if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_size_tbl[mHioType])) {
        return cPhs_ERROR_e;
    }
    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -60.0f, -20.0f, -60.0f, 60.0f, 170.0f, 60.0f);
    if (!createInit()) {
        return cPhs_ERROR_e;
    }
    return state;
}

/* 000037F8-000039C4       .text create_Anm__11daNpc_Ob1_cFv */
J3DModelData* daNpc_Ob1_c::create_Anm() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Ob", dRes_ID_OB_BDL_OB_e);
    JUT_ASSERT(0x977, a_mdl_dat != NULL);
    mpMorf = new mDoExt_McaMorf(
        a_mdl_dat, NULL, NULL, (J3DAnmTransform*)dComIfG_getObjectIDRes("Ob", dRes_ID_OB_BCK_WAIT_e),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, NULL, 0x80000, 0x11020022
    );
    if (mpMorf == NULL) {
        return NULL;
    }
    if (mpMorf->getModel() == NULL) {
        mpMorf = NULL;
        return NULL;
    }

    m_hed_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
    JUT_ASSERT(0x98B, m_hed_jnt_num >= 0);
    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(0x98E, m_bbone_jnt_num >= 0);

    return a_mdl_dat;
}

/* 000039C4-00003A88       .text create_hed_Mdl__11daNpc_Ob1_cFv */
J3DModelData* daNpc_Ob1_c::create_hed_Mdl() {
    static int a_hed_mdl_resID_tbl[] = {
        dRes_ID_OB_BDL_OBA_HEAD_e,
    };

    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Ob", a_hed_mdl_resID_tbl[mHioType]);
    JUT_ASSERT(0x9A1, a_mdl_dat != NULL);
    mpHeadModel = mDoExt_J3DModel__create(a_mdl_dat, 0x80000, 0x11020022);
    return a_mdl_dat;
}

/* 00003A88-00003BE0       .text CreateHeap__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::CreateHeap() {
    J3DModelData* a_mdl_dat = create_Anm();
    if (!a_mdl_dat) {
        return FALSE;
    }
    if (!create_hed_Mdl()) {
        mpMorf = NULL;
        return FALSE;
    }
    s8 a_btp_num_tbl[] = {0};
    mBtpNum = a_btp_num_tbl[0];
    if (!iniTexPttrnAnm(false)) {
        mpMorf = NULL;
        return FALSE;
    }
    for (u16 i = 0; i < a_mdl_dat->getJointNum(); i++) {
        if (i == m_hed_jnt_num || i == m_bbone_jnt_num) {
            mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Ob1);
        }
    }
    mpMorf->getModel()->setUserArea((uintptr_t)this);
    mAcchCir.SetWall(30.0f, 80.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this), NULL, NULL);
    return TRUE;
}

/* 00003BE0-00003C00       .text daNpc_Ob1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Ob1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Ob1_c*)i_this)->_create();
}

/* 00003C00-00003C20       .text daNpc_Ob1_Delete__FP11daNpc_Ob1_c */
static BOOL daNpc_Ob1_Delete(daNpc_Ob1_c* i_this) {
    return ((daNpc_Ob1_c*)i_this)->_delete();
}

/* 00003C20-00003C40       .text daNpc_Ob1_Execute__FP11daNpc_Ob1_c */
static BOOL daNpc_Ob1_Execute(daNpc_Ob1_c* i_this) {
    return ((daNpc_Ob1_c*)i_this)->_execute();
}

/* 00003C40-00003C60       .text daNpc_Ob1_Draw__FP11daNpc_Ob1_c */
static BOOL daNpc_Ob1_Draw(daNpc_Ob1_c* i_this) {
    return ((daNpc_Ob1_c*)i_this)->_draw();
}

/* 00003C60-00003C68       .text daNpc_Ob1_IsDelete__FP11daNpc_Ob1_c */
static BOOL daNpc_Ob1_IsDelete(daNpc_Ob1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Ob1_Method = {
    (process_method_func)daNpc_Ob1_Create,
    (process_method_func)daNpc_Ob1_Delete,
    (process_method_func)daNpc_Ob1_Execute,
    (process_method_func)daNpc_Ob1_IsDelete,
    (process_method_func)daNpc_Ob1_Draw,
};

actor_process_profile_definition g_profile_NPC_OB1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_OB1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Ob1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_OB1_e,
    /* Actor SubMtd */ &l_daNpc_Ob1_Method,
    /* Status       */ 0x08 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
