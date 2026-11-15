/**
 * d_a_npc_ac1.cpp
 * NPC - Prince Komali (after Dragon Roost Cavern)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_ac1.h"
#include "d/d_com_inf_game.h"
#include "d/d_snap.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"
#include "m_Do/m_Do_mtx.h"
#include "res/Object/Ac.h"

class daNpc_Ac1_HIO_c : public mDoHIO_entry_c {
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
        /* 0x1C */ s16 m1C;
        /* 0x20 */ f32 m20;
        /* 0x24 */ f32 m24;
        /* 0x28 */ f32 m28;
        /* 0x2C */ f32 m2C;
    };  // Size: 0x30

    daNpc_Ac1_HIO_c();
    virtual ~daNpc_Ac1_HIO_c() {}
    void genMessage(JORMContext* ctx) { UNUSED(ctx); }

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ int m8;
    /* 0x0C */ hio_prm_c mPrm;
};  // Size: 0x3C

/* 000000EC-00000150       .text __ct__15daNpc_Ac1_HIO_cFv */
daNpc_Ac1_HIO_c::daNpc_Ac1_HIO_c() {
    static hio_prm_c a_prm_tbl = {
        /* mMaxHeadX       */ 0x2000,
        /* mMaxHeadY       */ 0x2710,
        /* mMinHeadX       */ -0x1000,
        /* mMinHeadY       */ -0x2710,
        /* mMaxBackboneX   */ 0x0000,
        /* mMaxBackboneY   */ 0x1770,
        /* mMinBackboneX   */ 0x0000,
        /* mMinBackboneY   */ -0x1770,
        /* mMaxTurnStep    */ 0x0708,
        /* mMaxHeadTurnVel */ 0x0578,
        /* mAttPosOffsetY  */ 150.0f,
        /* m18             */ 0,
        /* m1A             */ 6,
        /* m1C             */ 0x400,
        /* m20             */ 0.5f,
        /* m24             */ 3.0f,
        /* m28             */ 0.1f,
        /* m2C             */ 40.0f,
    };
    memcpy(&mPrm, &a_prm_tbl, sizeof(hio_prm_c));
    mNo = -1;
    m8 = -1;
}

static daNpc_Ac1_HIO_c l_HIO;
static fopAc_ac_c* l_check_inf[20];
static int l_check_wrk;

/* 00000198-000001E4       .text nodeCallBack_Wng__FP7J3DNodei */
static BOOL nodeCallBack_Wng(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        if (j3dSys.getModel()->getUserArea() != 0) {
            ((daNpc_Ac1_c*)j3dSys.getModel()->getUserArea())->nodeWngControl(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 000001E4-000002A4       .text nodeWngControl__11daNpc_Ac1_cFP7J3DNodeP8J3DModel */
void daNpc_Ac1_c::nodeWngControl(J3DNode* i_node, J3DModel* i_model) {
    s32 jnt_no = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));
    if (jnt_no == m_wngL1_jnt_num) {
        cMtx_copy(mLeftArmMtx, j3dSys.mCurrentMtx);
        i_model->setAnmMtx(jnt_no, mLeftArmMtx);
    }
    if (jnt_no == m_wngR1_jnt_num) {
        cMtx_copy(mRightArmMtx, j3dSys.mCurrentMtx);
        i_model->setAnmMtx(jnt_no, mRightArmMtx);
    }
}

/* 000002A4-000002F0       .text nodeCallBack_Arm__FP7J3DNodei */
static BOOL nodeCallBack_Arm(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        if (j3dSys.getModel()->getUserArea() != 0) {
            ((daNpc_Ac1_c*)j3dSys.getModel()->getUserArea())->nodeArmControl(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 000002F0-000003B0       .text nodeArmControl__11daNpc_Ac1_cFP7J3DNodeP8J3DModel */
void daNpc_Ac1_c::nodeArmControl(J3DNode* i_node, J3DModel* i_model) {
    s32 jnt_no = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));
    if (jnt_no == m_armL1_jnt_num) {
        cMtx_copy(mLeftArmMtx, j3dSys.mCurrentMtx);
        i_model->setAnmMtx(jnt_no, mLeftArmMtx);
    }
    if (jnt_no == m_armR1_jnt_num) {
        cMtx_copy(mRightArmMtx, j3dSys.mCurrentMtx);
        i_model->setAnmMtx(jnt_no, mRightArmMtx);
    }
}

/* 000003B0-000003FC       .text nodeCallBack_Ac1__FP7J3DNodei */
static BOOL nodeCallBack_Ac1(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        if (j3dSys.getModel()->getUserArea() != 0) {
            ((daNpc_Ac1_c*)j3dSys.getModel()->getUserArea())->nodeAc1Control(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 000003FC-0000058C       .text nodeAc1Control__11daNpc_Ac1_cFP7J3DNodeP8J3DModel */
void daNpc_Ac1_c::nodeAc1Control(J3DNode* i_node, J3DModel* i_model) {
    static cXyz a_eye_pos_off(20.0f, 18.0f, 0.0f);

    s32 jnt_no = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));
    if (jnt_no == m_hed_jnt_num) {
        mDoMtx_stack_c::XrotM(m_jnt.getHead_y());
        mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
        mDoMtx_stack_c::multVec(&a_eye_pos_off, &mTransformedEyePos);
    }
    if (jnt_no == m_bbone_jnt_num) {
        mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
        mDoMtx_stack_c::ZrotM(-m_jnt.getBackbone_x());
    }
    if (jnt_no == m_arm_L_jnt_num) {
        cMtx_copy(mDoMtx_stack_c::get(), mLeftArmMtx);
    }
    if (jnt_no == m_arm_R_jnt_num) {
        cMtx_copy(mDoMtx_stack_c::get(), mRightArmMtx);
    }
    cMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* 0000058C-00000638       .text init_AC1_0__11daNpc_Ac1_cFv */
bool daNpc_Ac1_c::init_AC1_0() {
    bool ret = dComIfGs_isEventBit(dSv_event_flag_c::UNK_2E04) != 0;
    if (ret) {
        dComIfGs_isEventBit(dSv_event_flag_c::UNK_1580);
        set_action(&daNpc_Ac1_c::wait_action1, NULL);
    }
    return ret;
}

/* 00000638-000007DC       .text createInit__11daNpc_Ac1_cFv */
bool daNpc_Ac1_c::createInit() {
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xA9;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xA9;
    gravity = -4.5f;
    mLookPos = current.pos;

    u8 path_no = (fopAcM_GetParam(this) >> 16) & 0xFF;
    if (path_no != 0xFF) {
        mPath.setInf(path_no, fopAcM_GetRoomNo(this), true);
        if (mPath.isPath()) {
            fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
        } else {
            return false;
        }
    }

    mEventCut.setActorInfo2("Ac1", this);
    mAnmNum = 4;

    bool init_result;
    switch (mType) {
    case 0:
        init_result = init_AC1_0();
        break;
    default:
        init_result = false;
        break;
    }

    if (init_result) {
        shape_angle = current.angle;
    } else {
        return false;
    }
    mStts.Init(0xFF, 0xFF, this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);
    mpMorf->setMorf(0.0f);
    if (mbHasArms) {
        mpArmMorf->setMorf(0.0f);
    } else {
        mpWingMorf->setMorf(0.0f);
    }
    setMtx(true);
    return true;
}

/* 000007DC-00000954       .text setMtx__11daNpc_Ac1_cFb */
void daNpc_Ac1_c::setMtx(bool i_setEyePos) {
    if (!mbDemo) {
        plyTexPttrnAnm();
        mbMorfAnimStopped = mpMorf->play(&eyePos, 0, 0);
        if (mpMorf->getFrame() < mPrevMorfFrame) {
            mbMorfAnimStopped = true;
        }
        mPrevMorfFrame = mpMorf->getFrame();
        if (mbHasArms) {
            mpArmMorf->play(&eyePos, 0, 0);
        } else {
            mpWingMorf->play(&eyePos, 0, 0);
        }
        mObjAcch.CrrPos(*dComIfG_Bgsp());
    }
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    if (!mbHasArms) {
        mpWingMorf->calc();
    } else {
        mpArmMorf->calc();
    }
    if (mpItemModel && mbHasArms) {
        mpItemModel->setBaseTRMtx(mpArmMorf->getModel()->getAnmMtx(m_hnd_R_jnt_num));
        mpItemModel->calc();
    }
    setAttention(i_setEyePos);
}

/* 00000954-00000968       .text anmNum_toResID__11daNpc_Ac1_cFi */
int daNpc_Ac1_c::anmNum_toResID(int i_anmNum) {
    static const int a_bck_resID_tbl[] = {
        dRes_ID_AC_BCK_AC_WAIT01_e,
        dRes_ID_AC_BCK_AC_TALK01_e,
        dRes_ID_AC_BCK_AC_TALK02_e,
        dRes_ID_AC_BCK_AC_WAIT02_e,
    };
    return a_bck_resID_tbl[i_anmNum];
}

/* 00000968-0000097C       .text wingAnmNum_toResID__11daNpc_Ac1_cFi */
int daNpc_Ac1_c::wingAnmNum_toResID(int i_anmNum) {
    static const int a_bck_resID_tbl[] = {
        dRes_ID_AC_BCK_ACARM_WAIT01_e,
        dRes_ID_AC_BCK_ACARM_TALK01_e,
        dRes_ID_AC_BCK_ACARM_TALK02_e,
        dRes_ID_AC_BCK_ACARM_WAIT02_e,
    };
    return a_bck_resID_tbl[i_anmNum];
}

/* 0000097C-00000990       .text btpNum_toResID__11daNpc_Ac1_cFi */
int daNpc_Ac1_c::btpNum_toResID(int i_btpNum) {
    static const int a_btp_resID_tbl[] = {
        dRes_ID_AC_BTP_MABA_e,
        dRes_ID_AC_BTP_KOMARI_e,
        dRes_ID_AC_BTP_WARAI_e,
    };
    return a_btp_resID_tbl[i_btpNum];
}

/* 00000990-00000AA0       .text setBtp__11daNpc_Ac1_cFbi */
bool daNpc_Ac1_c::setBtp(bool i_modify, int i_btpNum) {
    J3DModelData* model_data = mpMorf->getModel()->getModelData();
    m_hed_tex_pttrn = (J3DAnmTexPattern*)dComIfG_getObjectIDRes("Ac", btpNum_toResID(i_btpNum));
    JUT_ASSERT(0x216, m_hed_tex_pttrn != NULL);

    bool ret = mBtpAnm.init(model_data, m_hed_tex_pttrn, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, i_modify, 0) == 1;
    if (ret) {
        mBtpFrame = 0;
        mBlinkTimer = 0;
    }
    return ret;
}

/* 00000AA0-00000AC8       .text iniTexPttrnAnm__11daNpc_Ac1_cFb */
bool daNpc_Ac1_c::iniTexPttrnAnm(bool i_modify) {
    return setBtp(i_modify, mBtpNum);
}

/* 00000AC8-00000B74       .text plyTexPttrnAnm__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::plyTexPttrnAnm() {
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

/* 00000B74-00000BB0       .text setAnm_tex__11daNpc_Ac1_cFSc */
void daNpc_Ac1_c::setAnm_tex(s8 i_btpNum) {
    if (mBtpNum != i_btpNum) {
        mBtpNum = i_btpNum;
        iniTexPttrnAnm(true);
    }
}

/* 00000BB0-00000D0C       .text setAnm_anm__11daNpc_Ac1_cFPQ211daNpc_Ac1_c9anm_prm_c */
BOOL daNpc_Ac1_c::setAnm_anm(anm_prm_c* i_anmPrmP) {
    if (mAnmNum == i_anmPrmP->mAnmNum) {
        return TRUE;
    }
    mAnmNum = i_anmPrmP->mAnmNum;
    dNpc_setAnmIDRes(mpMorf, i_anmPrmP->mLoopMode, i_anmPrmP->mMorf, i_anmPrmP->mSpeed, anmNum_toResID(mAnmNum), -1, "Ac");
    int wing_res_id = wingAnmNum_toResID(mAnmNum);
    mbHasArms = i_anmPrmP->mHasArms == 1;
    if (mbHasArms) {
        dNpc_setAnmIDRes(mpArmMorf, i_anmPrmP->mLoopMode, i_anmPrmP->mMorf, i_anmPrmP->mSpeed, wing_res_id, -1, "Ac");
    } else {
        dNpc_setAnmIDRes(mpWingMorf, i_anmPrmP->mLoopMode, i_anmPrmP->mMorf, i_anmPrmP->mSpeed, wing_res_id, -1, "Ac");
    }
    mPrevMorfFrame = 0.0f;
    m859 = 0;
    mbMorfAnimStopped = 0;
    return TRUE;
}

/* 00000D0C-00000D8C       .text setAnm__11daNpc_Ac1_cFv */
BOOL daNpc_Ac1_c::setAnm() {
    static anm_prm_c a_anm_prm_tbl[3] = {
        {-1, -1, 0.0f, 0.0f, -1, -1},
        {0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 1},
        {-1, -1, 0.0f, 0.0f, -1, -1},
    };
    if (a_anm_prm_tbl[mStt].mBtpNum >= 0) {
        setAnm_tex(a_anm_prm_tbl[mStt].mBtpNum);
    }
    if (a_anm_prm_tbl[mStt].mAnmNum >= 0) {
        setAnm_anm(&a_anm_prm_tbl[mStt]);
    }
    return TRUE;
}

/* 00000D8C-00000D90       .text chg_anmTag__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::chg_anmTag() {}

/* 00000D90-00000D94       .text control_anmTag__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::control_anmTag() {}

/* 00000D94-00000DD8       .text chg_anmAtr__11daNpc_Ac1_cFUc */
void daNpc_Ac1_c::chg_anmAtr(u8 i_atr) {
    if (i_atr >= 6 || i_atr == mAnmAtr) {
        return;
    }
    mAnmAtr = i_atr;
    setAnm_ATR(1);
}

/* 00000DD8-00000DE4       .text control_anmAtr__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::control_anmAtr() {
    switch (mAnmAtr) {
    case 6:
        break;
    }
}

/* 00000DE4-00000E4C       .text setAnm_ATR__11daNpc_Ac1_cFi */
void daNpc_Ac1_c::setAnm_ATR(int i_setBtp) {
    static anm_prm_c a_anm_prm_tbl[6] = {
        {0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 1},
        {1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 1},
        {2, 1, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 1},
        {3, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 1},
        {1, 2, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 1},
        {1, 1, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP, 1},
    };
    if (i_setBtp != 0) {
        setAnm_tex(a_anm_prm_tbl[mAnmAtr].mBtpNum);
    }
    setAnm_anm(&a_anm_prm_tbl[mAnmAtr]);
}

/* 00000E4C-00000F10       .text anmAtr__11daNpc_Ac1_cFUs */
void daNpc_Ac1_c::anmAtr(u16 i_msgStatus) {
    u32 mesg_anime_tag;
    switch (i_msgStatus) {
    case fopMsgStts_MSG_TYPING_e:
        if (mMsgCount == 0) {
            mAnmAtr = 0xFF;
            chg_anmAtr(dComIfGp_getMesgAnimeAttrInfo());
            mMsgCount++;
        }
        mesg_anime_tag = dComIfGp_getMesgAnimeTagInfo();
        dComIfGp_clearMesgAnimeTagInfo();
        if (mesg_anime_tag != 0xFF && mMesgAnimeTag != mesg_anime_tag) {
            mMesgAnimeTag = mesg_anime_tag;
            chg_anmTag();
        }
        break;
    case fopMsgStts_MSG_DISPLAYED_e:
        mMsgCount = 0;
        break;
    default:
        break;
    }
    control_anmTag();
    control_anmAtr();
}

/* 00000F10-00000F60       .text eventOrder__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::eventOrder() {
    if (mOrder == 1 || mOrder == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (mOrder == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    }
}

/* 00000F60-00000FA0       .text checkOrder__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
    } else if (eventInfo.checkCommandTalk()) {
        if (mOrder == 1 || mOrder == 2) {
            mOrder = 0;
            mbTalkReq = true;
        }
    }
}

/* 00000FA0-0000104C       .text chk_talk__11daNpc_Ac1_cFv */
bool daNpc_Ac1_c::chk_talk() {
    bool ret = true;
    mItemNo = 0xFF;
    if (dComIfGp_event_chkTalkXY()) {
        if (dComIfGp_evmng_ChkPresentEnd()) {
            mItemNo = dComIfGp_event_getPreItemNo();
        } else {
            ret = false;
        }
    }
    return ret;
}

/* 0000104C-0000108C       .text chk_partsNotMove__11daNpc_Ac1_cFv */
bool daNpc_Ac1_c::chk_partsNotMove() {
    return mJointHeadY == m_jnt.getHead_y() && mJointBackboneY == m_jnt.getBackbone_y() && mActorAngleY == current.angle.y;
}

/* 0000108C-0000122C       .text lookBack__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::lookBack() {
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

/* 0000122C-00001294       .text next_msgStatus__11daNpc_Ac1_cFPUl */
u16 daNpc_Ac1_c::next_msgStatus(u32* o_msgNoP) {
    u16 ret = fopMsgStts_MSG_CONTINUES_e;
    switch (*o_msgNoP) {
    case 0x184C:
        *o_msgNoP = 0x184D;
        break;
    case 0x184D:
        *o_msgNoP = 0x184E;
        break;
    case 0x1850:
        *o_msgNoP = 0x1851;
        break;
    case 0x1851:
        *o_msgNoP = 0x1852;
        break;
    default:
        ret = fopMsgStts_MSG_ENDS_e;
        break;
    }
    return ret;
}

/* 00001294-000012AC       .text getBitMask__11daNpc_Ac1_cFv */
s8 daNpc_Ac1_c::getBitMask() {
    s8 mask = 0;
    switch (mType) {
    case 0:
        mask = 0x10;
        break;
    }
    return mask;
}

static inline void ac1_setReg(int i_no) {
    dComIfGs_setEventReg(dSv_event_flag_c::UNK_B8FF, i_no);
}

/* 000012AC-0000137C       .text getMsg_AC1_0__11daNpc_Ac1_cFv */
u32 daNpc_Ac1_c::getMsg_AC1_0() {
    s8 reg = dComIfGs_getEventReg(dSv_event_flag_c::UNK_B8FF);
    s8 mask = getBitMask();
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1580)) {
        if (mask & reg) {
            return 0x1853;
        }
        ac1_setReg(reg |= mask);
        return 0x1850;
    }
    if (mask & reg) {
        return 0x184F;
    }
    ac1_setReg(reg |= mask);
    return 0x184C;
}

/* 0000137C-000013B8       .text getMsg__11daNpc_Ac1_cFv */
u32 daNpc_Ac1_c::getMsg() {
    u32 msg = 0;
    switch (mType) {
    case 0:
        msg = getMsg_AC1_0();
        break;
    }
    return msg;
}

/* 000013B8-00001438       .text chkAttention__11daNpc_Ac1_cFv */
bool daNpc_Ac1_c::chkAttention() {
    dAttention_c& attention = dComIfGp_getAttention();
    if (attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    }
    return this == attention.ActionTarget(0);
}

/* 00001438-00001494       .text setAttention__11daNpc_Ac1_cFb */
void daNpc_Ac1_c::setAttention(bool i_setEyePos) {
    attention_info.position.set(current.pos.x, current.pos.y + l_HIO.mPrm.mAttPosOffsetY, current.pos.z);

    if (!mbSetEyePos && !i_setEyePos) {
        return;
    }

    eyePos.set(mTransformedEyePos.x, mTransformedEyePos.y, mTransformedEyePos.z);
}

/* 00001494-000014B0       .text charDecide__11daNpc_Ac1_cFi */
bool daNpc_Ac1_c::charDecide(int) {
    mHioType = 0;
    mType = -1;
    mType = 0;
    return true;
}

/* 000014B0-000014FC       .text event_actionInit__11daNpc_Ac1_cFi */
void daNpc_Ac1_c::event_actionInit(int i_staffIdx) {
    int* act_no_p = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "ActNo");
    if (act_no_p != NULL) {
        mActNo = *act_no_p;
    }
}

/* 000014FC-00001528       .text event_action__11daNpc_Ac1_cFv */
bool daNpc_Ac1_c::event_action() {
    switch (mActNo) {
    case 0:
        return true;
    default:
        return true;
    }
}

/* 00001528-00001614       .text privateCut__11daNpc_Ac1_cFi */
void daNpc_Ac1_c::privateCut(int i_staffIdx) {
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

/* 00001614-00001634       .text endEvent__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::endEvent() {
    dComIfGp_event_reset();
    mAnmAtr = 0xFF;
}

/* 00001634-0000166C       .text isEventEntry__11daNpc_Ac1_cFv */
int daNpc_Ac1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName(), NULL);
}

/* 0000166C-000016C4       .text event_proc__11daNpc_Ac1_cFi */
void daNpc_Ac1_c::event_proc(int i_staffIdx) {
    if (!mEventCut.cutProc()) {
        privateCut(i_staffIdx);
    }
    lookBack();
}

/* 000016C4-00001770       .text set_action__11daNpc_Ac1_cFM11daNpc_Ac1_cFPCvPvPv_iPv */
BOOL daNpc_Ac1_c::set_action(ProcFunc i_newProcFunc, void* i_argsP) {
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

/* 00001770-000017D4       .text setStt__11daNpc_Ac1_cFSc */
void daNpc_Ac1_c::setStt(s8 i_stt) {
    u8 prev_stt = mStt;
    mTalkTimer = 0;
    mStt = i_stt;
    switch (mStt) {
    case 1:
        break;
    case 2:
        mAnmAtr = 0xFF;
        mLookMode = 1;
        mPrevStt = prev_stt;
        m_jnt.setTrn();
        return;
    }
    setAnm();
}

/* 000017D4-0000189C       .text wait_1__11daNpc_Ac1_cFv */
BOOL daNpc_Ac1_c::wait_1() {
    if (mOrder == 1 || mOrder >= 3) {
        return TRUE;
    }

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
        mLookMode = 3;
        mTargetAngleY = mHomeAngle.y;
        m_jnt.setTrn();
    }
    return TRUE;
}

/* 0000189C-00001974       .text talk_1__11daNpc_Ac1_cFv */
BOOL daNpc_Ac1_c::talk_1() {
    BOOL res = chk_partsNotMove();
    if (mpCurrMsg != NULL) {
        mPrevMsgStatus = mpCurrMsg->mStatus;
    } else {
        mPrevMsgStatus = 0;
    }
    fopNpc_npc_c::talk(1);
    if (mpCurrMsg != NULL) {
        switch (mpCurrMsg->mStatus) {
        case fopMsgStts_BOX_OPENING_e:
        case fopMsgStts_MSG_TYPING_e:
            break;
        case fopMsgStts_MSG_DESTROYED_e:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_3F02);
            mItemNo = 0xFF;
            mbTalkReq = false;
            setStt(mPrevStt);
            mTalkTimer = 60;
            endEvent();
            break;
        }
    }
    return res;
}

/* 00001974-00001A48       .text wait_action1__11daNpc_Ac1_cFPv */
BOOL daNpc_Ac1_c::wait_action1(void*) {
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
        }
        lookBack();
        break;
    default:
        break;
    }
    return TRUE;
}

/* 00001A48-00001B88       .text demo__11daNpc_Ac1_cFv */
bool daNpc_Ac1_c::demo() {
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
        J3DAnmTexPattern* demo_btp_p = demo_actor_p->getP_BtpData("Ac");
        if (demo_btp_p) {
            m_hed_tex_pttrn = demo_btp_p;
            if (mBtpAnm.init(mpMorf->getModel()->getModelData(), m_hed_tex_pttrn, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, FALSE)) {
                mBtpNum = 3;
                mBtpFrame = 0;
            }
        }
        dDemo_setDemoData(this, 0x6A, mpMorf, "Ac");
    }
    return mbDemo;
}

/* 00001B88-00001CB4       .text shadowDraw__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::shadowDraw() {
    cXyz pos(current.pos.x, current.pos.y + 150.0f, current.pos.z);

    mShadowID = dComIfGd_setShadow(mShadowID, 1, mpMorf->getModel(), &pos, 800.0f, 40.0f, current.pos.y, mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr, 0, 1.0f, dDlst_shadowControl_c::getSimpleTex());
    if (mShadowID != 0) {
        if (mbHasArms) {
            dComIfGd_addRealShadow(mShadowID, mpArmMorf->getModel());
        } else {
            dComIfGd_addRealShadow(mShadowID, mpWingMorf->getModel());
        }
        if (mpItemModel) {
            dComIfGd_addRealShadow(mShadowID, mpItemModel);
        }
    }
}

static void dummy() {
    const GXColor dummy1 = {0xFF, 0x00, 0x00, 0x80};
    const GXColor dummy2 = {0x00, 0x00, 0xFF, 0x80};
}

/* 00001CB4-00001E04       .text _draw__11daNpc_Ac1_cFv */
BOOL daNpc_Ac1_c::_draw() {
    J3DModel* model = mpMorf->getModel();
    J3DModelData* model_data = model->getModelData();

    if (mbHide || m861) {
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(model, &tevStr);

    mBtpAnm.entry(model_data, mBtpFrame);
    mpMorf->entryDL();
    mBtpAnm.remove(model_data);

    if (mbHasArms) {
        g_env_light.setLightTevColorType(mpArmMorf->getModel(), &tevStr);
        mpArmMorf->entryDL();
    } else {
        g_env_light.setLightTevColorType(mpWingMorf->getModel(), &tevStr);
        mpWingMorf->entryDL();
    }

    if (mpItemModel && mbHasArms) {
        g_env_light.setLightTevColorType(mpItemModel, &tevStr);
        mDoExt_modelEntryDL(mpItemModel);
    }

    shadowDraw();
    dSnap_RegistFig(DSNAP_TYPE_UNK8B, this, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 00001E04-00001FD4       .text _execute__11daNpc_Ac1_cFv */
BOOL daNpc_Ac1_c::_execute() {
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
            fopAcM_posMoveF(this, mStts.GetCCMoveP());
        }
        if (!m85F) {
            shape_angle = current.angle;
        }
    }
    eventOrder();
    setMtx(false);
    if (!mbDemo) {
        setCollision(50.0f, 140.0f);
    }
    return TRUE;
}

/* 00001FD4-00002058       .text _delete__11daNpc_Ac1_cFv */
BOOL daNpc_Ac1_c::_delete() {
    dComIfG_resDelete(&mPhs, "Ac");
    if (heap != NULL) {
        if (mpMorf != NULL) {
            mpMorf->stopZelAnime();
        }
        if (mpWingMorf != NULL) {
            mpWingMorf->stopZelAnime();
        }
        if (mpArmMorf != NULL) {
            mpArmMorf->stopZelAnime();
        }
    }
    return TRUE;
}

/* 00002058-00002078       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Ac1_c*)i_this)->CreateHeap();
}

daNpc_Ac1_c::daNpc_Ac1_c() {}

/* 00002078-00002198       .text _create__11daNpc_Ac1_cFv */
cPhs_State daNpc_Ac1_c::_create() {
    static int a_size_tbl[] = {
        0x272E0,
    };

    fopAcM_ct(this, daNpc_Ac1_c);
    cPhs_State state = dComIfG_resLoad(&mPhs, "Ac");
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
    fopAcM_setCullSizeBox(this, -50.0f, -20.0f, -50.0f, 50.0f, 140.0f, 50.0f);
    if (!createInit()) {
        return cPhs_ERROR_e;
    }
    return state;
}

/* 00002578-00002824       .text create_Anm__11daNpc_Ac1_cFv */
J3DModelData* daNpc_Ac1_c::create_Anm() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Ac", dRes_ID_AC_BDL_AC_e);
    JUT_ASSERT(0x6BE, a_mdl_dat != NULL);
    mpMorf = new mDoExt_McaMorf(
        a_mdl_dat, NULL, NULL, (J3DAnmTransform*)dComIfG_getObjectIDRes("Ac", dRes_ID_AC_BCK_AC_WAIT01_e),
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
    JUT_ASSERT(0x6D2, m_hed_jnt_num >= 0);
    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(0x6D5, m_bbone_jnt_num >= 0);
    m_arm_L_jnt_num = a_mdl_dat->getJointName()->getIndex("armL");
    JUT_ASSERT(0x6D8, m_arm_L_jnt_num >= 0);
    m_arm_R_jnt_num = a_mdl_dat->getJointName()->getIndex("armR");
    JUT_ASSERT(0x6DB, m_arm_R_jnt_num >= 0);

    return a_mdl_dat;
}

/* 00002824-00002A38       .text create_wng_Anm__11daNpc_Ac1_cFv */
J3DModelData* daNpc_Ac1_c::create_wng_Anm() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Ac", dRes_ID_AC_BDL_ACWING_e);
    JUT_ASSERT(0x6EA, a_mdl_dat != NULL);
    mpWingMorf = new mDoExt_McaMorf(
        a_mdl_dat, NULL, NULL, (J3DAnmTransform*)dComIfG_getObjectIDRes("Ac", dRes_ID_AC_BCK_ACARM_WAIT01_e),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, NULL, 0x80000, 0x11000002
    );
    if (mpWingMorf == NULL) {
        return NULL;
    }
    if (mpWingMorf->getModel() == NULL) {
        mpWingMorf = NULL;
        return NULL;
    }

    m_wngL1_jnt_num = a_mdl_dat->getJointName()->getIndex("wingL_loc");
    JUT_ASSERT(0x6FF, m_wngL1_jnt_num >= 0);
    m_wngR1_jnt_num = a_mdl_dat->getJointName()->getIndex("wingR_loc");
    JUT_ASSERT(0x702, m_wngR1_jnt_num >= 0);

    return a_mdl_dat;
}

/* 00002A38-00002CA8       .text create_arm_Anm__11daNpc_Ac1_cFv */
J3DModelData* daNpc_Ac1_c::create_arm_Anm() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Ac", dRes_ID_AC_BDL_ACARM_e);
    JUT_ASSERT(0x711, a_mdl_dat != NULL);
    mpArmMorf = new mDoExt_McaMorf(
        a_mdl_dat, NULL, NULL, (J3DAnmTransform*)dComIfG_getObjectIDRes("Ac", dRes_ID_AC_BCK_ACARM_WAIT01_e),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, NULL, 0x80000, 0x11000002
    );
    if (mpArmMorf == NULL) {
        return NULL;
    }
    if (mpArmMorf->getModel() == NULL) {
        mpArmMorf = NULL;
        return NULL;
    }

    m_hnd_R_jnt_num = a_mdl_dat->getJointName()->getIndex("handR");
    JUT_ASSERT(0x726, m_hnd_R_jnt_num >= 0);
    m_armL1_jnt_num = a_mdl_dat->getJointName()->getIndex("armL_loc");
    JUT_ASSERT(0x729, m_armL1_jnt_num >= 0);
    m_armR1_jnt_num = a_mdl_dat->getJointName()->getIndex("armR_loc");
    JUT_ASSERT(0x72C, m_armR1_jnt_num >= 0);

    return a_mdl_dat;
}

/* 00002CA8-00002DB4       .text create_itm_Mdl__11daNpc_Ac1_cFv */
bool daNpc_Ac1_c::create_itm_Mdl() {
    J3DModelData* a_mdl_dat;
    mpItemModel = NULL;
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1580)) {
        a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Ac", dRes_ID_AC_BDL_AC_FLOWER02_e);
    } else {
        a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Ac", dRes_ID_AC_BDL_AC_FLOWER_e);
    }
    JUT_ASSERT(0x744, a_mdl_dat != NULL);
    mpItemModel = mDoExt_J3DModel__create(a_mdl_dat, 0x80000, 0x11000022);
    return true;
}

/* 00002DB4-00003024       .text CreateHeap__11daNpc_Ac1_cFv */
BOOL daNpc_Ac1_c::CreateHeap() {
    J3DModelData* a_mdl_dat = create_Anm();
    if (!a_mdl_dat) {
        return FALSE;
    }
    mBtpNum = 0;
    if (!iniTexPttrnAnm(false)) {
        mpMorf = NULL;
        return FALSE;
    }
    J3DModelData* wng_mdl_dat = create_wng_Anm();
    if (!wng_mdl_dat) {
        mpMorf = NULL;
        return FALSE;
    }
    J3DModelData* arm_mdl_dat = create_arm_Anm();
    if (arm_mdl_dat && create_itm_Mdl()) {
        for (u16 i = 0; i < wng_mdl_dat->getJointNum(); i++) {
            if (i == m_wngL1_jnt_num || i == m_wngR1_jnt_num) {
                mpWingMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Wng);
            }
        }
        mpWingMorf->getModel()->setUserArea((uintptr_t)this);
        for (u16 i = 0; i < arm_mdl_dat->getJointNum(); i++) {
            if (i == m_armL1_jnt_num || i == m_armR1_jnt_num) {
                mpArmMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Arm);
            }
        }
        mpArmMorf->getModel()->setUserArea((uintptr_t)this);
        for (u16 i = 0; i < a_mdl_dat->getJointNum(); i++) {
            if (i == m_hed_jnt_num || i == m_bbone_jnt_num || i == m_arm_L_jnt_num || i == m_arm_R_jnt_num) {
                mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Ac1);
            }
        }
        mpMorf->getModel()->setUserArea((uintptr_t)this);
        mAcchCir.SetWall(30.0f, 50.0f);
        mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this), NULL, NULL);
        return TRUE;
    }
    mpMorf = NULL;
    mpWingMorf = NULL;
    return FALSE;
}

/* 00003024-00003044       .text daNpc_Ac1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Ac1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Ac1_c*)i_this)->_create();
}

/* 00003044-00003064       .text daNpc_Ac1_Delete__FP11daNpc_Ac1_c */
static BOOL daNpc_Ac1_Delete(daNpc_Ac1_c* i_this) {
    return ((daNpc_Ac1_c*)i_this)->_delete();
}

/* 00003064-00003084       .text daNpc_Ac1_Execute__FP11daNpc_Ac1_c */
static BOOL daNpc_Ac1_Execute(daNpc_Ac1_c* i_this) {
    return ((daNpc_Ac1_c*)i_this)->_execute();
}

/* 00003084-000030A4       .text daNpc_Ac1_Draw__FP11daNpc_Ac1_c */
static BOOL daNpc_Ac1_Draw(daNpc_Ac1_c* i_this) {
    return ((daNpc_Ac1_c*)i_this)->_draw();
}

/* 000030A4-000030AC       .text daNpc_Ac1_IsDelete__FP11daNpc_Ac1_c */
static BOOL daNpc_Ac1_IsDelete(daNpc_Ac1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Ac1_Method = {
    (process_method_func)daNpc_Ac1_Create,
    (process_method_func)daNpc_Ac1_Delete,
    (process_method_func)daNpc_Ac1_Execute,
    (process_method_func)daNpc_Ac1_IsDelete,
    (process_method_func)daNpc_Ac1_Draw,
};

actor_process_profile_definition g_profile_NPC_AC1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_AC1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Ac1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_AC1_e,
    /* Actor SubMtd */ &l_daNpc_Ac1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
