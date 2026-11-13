/**
 * d_a_npc_kf1.cpp
 * NPC - Mila's Father (rich)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_kf1.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_tsubo.h"
#include "d/d_com_inf_game.h"
#include "d/d_snap.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"
#include "m_Do/m_Do_lib.h"
#include "res/Object/Kf.h"
#include "SSystem/SComponent/c_counter.h"

class daNpc_Kf1_HIO_c : public mDoHIO_entry_c {
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
        /* 0x2C */ f32 m2C;
    };  // Size: 0x30

    daNpc_Kf1_HIO_c();
    virtual ~daNpc_Kf1_HIO_c() {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ int m08;
    /* 0x0C */ hio_prm_c mPrm;
};  // Size: 0x3C

static daNpc_Kf1_HIO_c l_HIO;
static fopAc_ac_c* l_check_inf[20];
static int l_check_wrk;

/* 000000EC-00000150       .text __ct__15daNpc_Kf1_HIO_cFv */
daNpc_Kf1_HIO_c::daNpc_Kf1_HIO_c() {
    static hio_prm_c a_prm_tbl = {
        /* mMaxHeadX        */ 0x2000,
        /* mMaxHeadY        */ 0x07D0,
        /* mMinHeadX        */ -0x03E8,
        /* mMinHeadY        */ -0x07D0,
        /* mMaxBackBoneX    */ 0x0000,
        /* mMaxBackBoneY    */ 0x1388,
        /* mMinBackBoneX    */ -0x0FA0,
        /* mMinBackBoneY    */ -0x1388,
        /* mMaxTurnStep     */ 0x05DC,
        /* mMaxHeadTurnVel  */ 0x04B0,
        /* mAttPosOffsetY   */ 200.0f,
        /* m18              */ 0,
        /* mWalkTurnScale   */ 10,
        /* mWalkTurnMaxStep */ 0x0400,
        /* mWalkAnmRate     */ 0.5f,
        /* mWalkSpeed       */ 2.0f,
        /* mWalkAccel       */ 0.2f,
        /* m2C              */ 8.0f,
    };
    memcpy(&mPrm, &a_prm_tbl, sizeof(hio_prm_c));
    mNo = -1;
    m08 = -1;
}

static const char* l_evn_tbl[] = {
    "angry",
    "rupee_age",
    "bensyou",
};

/* 00000198-000001E4       .text nodeCB_Head__FP7J3DNodei */
static BOOL nodeCB_Head(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In && j3dSys.getModel()->getUserArea() != 0) {
        daNpc_Kf1_c* actor_p = (daNpc_Kf1_c*)j3dSys.getModel()->getUserArea();
        actor_p->_nodeCB_Head(i_node, j3dSys.getModel());
    }
    return TRUE;
}

/* 000001E4-000002D8       .text _nodeCB_Head__11daNpc_Kf1_cFP7J3DNodeP8J3DModel */
void daNpc_Kf1_c::_nodeCB_Head(J3DNode* i_node, J3DModel* i_model) {
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
        daNpc_Kf1_c* actor_p = (daNpc_Kf1_c*)j3dSys.getModel()->getUserArea();
        actor_p->_nodeCB_Neck(i_node, j3dSys.getModel());
    }
    return TRUE;
}

/* 00000360-00000400       .text _nodeCB_Neck__11daNpc_Kf1_cFP7J3DNodeP8J3DModel */
void daNpc_Kf1_c::_nodeCB_Neck(J3DNode* i_node, J3DModel* i_model) {
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
        daNpc_Kf1_c* actor_p = (daNpc_Kf1_c*)j3dSys.getModel()->getUserArea();
        actor_p->_nodeCB_BackBone(i_node, j3dSys.getModel());
    }
    return TRUE;
}

/* 0000044C-000004EC       .text _nodeCB_BackBone__11daNpc_Kf1_cFP7J3DNodeP8J3DModel */
void daNpc_Kf1_c::_nodeCB_BackBone(J3DNode* i_node, J3DModel* i_model) {
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
    return ((daNpc_Kf1_c*)i_this)->CreateHeap();
}

/* 0000050C-0000059C       .text searchActor_Tsubo__FPvPv */
static void* searchActor_Tsubo(void* i_actor, void*) {
    if (l_check_wrk < ARRAY_SSIZE(l_check_inf) && fopAc_IsActor(i_actor) && fopAcM_GetName(i_actor) == fpcNm_TSUBO_e) {
        if (((daTsubo::Act_c*)i_actor)->prm_get_type() == 0xE) {
            l_check_inf[l_check_wrk] = (fopAc_ac_c*)i_actor;
            l_check_wrk++;
        }
    }
    return NULL;
}

/* 0000059C-0000061C       .text init_KF1_0__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::init_KF1_0() {
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2D01)) {
        set_action(&daNpc_Kf1_c::wait_action1, NULL);
        return true;
    }
    return false;
}

/* 0000061C-0000083C       .text createInit__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::createInit() {
    for (int i = 0; i < ARRAY_SSIZE(mEventIDTbl); i++) {
        mEventIDTbl[i] = dComIfGp_evmng_getEventIdx(l_evn_tbl[i]);
    }
    mEventCut.setActorInfo2("Kf1", this);
    mSwitchNo = (fopAcM_GetParam(this) >> 8) & 0xFF;

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

    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xAB;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xAB;
    gravity = -4.5f;
    mBckNum = BCKNUM_NULL_e;

    bool init_result;
    switch (mType) {
    case 0:
        init_result = init_KF1_0();
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

/* 0000083C-000008E4       .text play_animation__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::play_animation() {
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

/* 000008E4-00000A20       .text setMtx__11daNpc_Kf1_cFb */
void daNpc_Kf1_c::setMtx(bool i_setEyePos) {
    mpMorf->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(mAngle);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());

    mpMorf->calc();

    if (mpHairModel) {
        mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(m_hed_jnt_num));
        mDoMtx_stack_c::transM(33.87f, 3.26f, 0.0f);
        mDoMtx_stack_c::XYZrotM(-0x4000, -0x4000, 0);
        mpHairModel->setBaseTRMtx(mDoMtx_stack_c::get());
        mpHairModel->calc();
    }
    setAttention(i_setEyePos);
}

/* 00000A20-00000A34       .text bckResID__11daNpc_Kf1_cFi */
int daNpc_Kf1_c::bckResID(int i_bckNum) {
    static const int a_resID_tbl[] = {
        dRes_ID_KF_BCK_KF_WAIT01_e,
        dRes_ID_KF_BCK_KF_WALK_e,
        dRes_ID_KF_BCK_KF_TALK01_e,
        dRes_ID_KF_BCK_KF_TALK02_e,
        dRes_ID_KF_BCK_KF_TALK03_e,
        dRes_ID_KF_BCK_KF_TALK04_e,
        dRes_ID_KF_BCK_KF_OKORU_e,
        dRes_ID_KF_BCK_KF_BAKUHATU_e,
        dRes_ID_KF_BCK_KF_BARAMAKU_e,
        dRes_ID_KF_BCK_KF_WAIT02_e,
    };
    return a_resID_tbl[i_bckNum];
}

/* 00000A34-00000A48       .text btpResID__11daNpc_Kf1_cFi */
int daNpc_Kf1_c::btpResID(int i_btpNum) {
    static const int a_resID_tbl[] = {
        dRes_ID_KF_BTP_KF_e,
        dRes_ID_KF_BTP_CLOSE_e,
    };
    return a_resID_tbl[i_btpNum];
}

/* 00000A48-00000B4C       .text setBtp__11daNpc_Kf1_cFScb */
bool daNpc_Kf1_c::setBtp(s8 i_btpNum, bool i_bModify) {
    J3DModel* morf_model_p = mpMorf->getModel();

    if (i_btpNum < 0) {
        return false;
    }

    J3DAnmTexPattern* a_btp = (J3DAnmTexPattern*)dComIfG_getObjectIDRes(mArcName, btpResID(i_btpNum));
    JUT_ASSERT(0x20A, a_btp != NULL);
    mBtpNum = i_btpNum;
    mBtpFrame = 0;
    mBlinkTimer = 0;

    return mBtpAnm.init(morf_model_p->getModelData(), a_btp, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, i_bModify, 0) != 0;
}

/* 00000B4C-00000B6C       .text init_texPttrnAnm__11daNpc_Kf1_cFScb */
bool daNpc_Kf1_c::init_texPttrnAnm(s8 i_btpNum, bool i_bModify) {
    return setBtp(i_btpNum, i_bModify);
}

/* 00000B6C-00000C08       .text play_btp_anm__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::play_btp_anm() {
    u8 frame_max = mBtpAnm.getBtpAnm()->getFrameMax();
    if (mBtpNum != BTPNUM_KF_e || cLib_calcTimer(&mBlinkTimer) == 0) {
        mBtpFrame++;
        if (mBtpFrame >= frame_max) {
            if (mBtpNum != BTPNUM_KF_e) {
                mBtpFrame = frame_max;
            } else {
                mBlinkTimer = cLib_getRndValue(60, 90);
                mBtpFrame = 0;
            }
        }
    }
}

/* 00000C08-00000CA4       .text setAnm_anm__11daNpc_Kf1_cFPQ211daNpc_Kf1_c9anm_prm_c */
void daNpc_Kf1_c::setAnm_anm(anm_prm_c* i_anmPrmP) {
    if (i_anmPrmP->bckNum < 0 || mBckNum == i_anmPrmP->bckNum) {
        return;
    }

    dNpc_setAnmIDRes(mpMorf, i_anmPrmP->loopMode, i_anmPrmP->morf, i_anmPrmP->speed, bckResID(i_anmPrmP->bckNum), -1, mArcName);
    mBckNum = i_anmPrmP->bckNum;
    mbMorfAnimStopped = false;
    m79D = 0;
    mPrevMorfFrame = 0.0f;
}

/* 00000CA4-00000D14       .text setAnm_NUM__11daNpc_Kf1_cFii */
void daNpc_Kf1_c::setAnm_NUM(int i_anmNum, int i_setBtp) {
    static anm_prm_c a_anm_prm_tbl[10] = {
        {BCKNUM_WAIT01_e, BTPNUM_KF_e, 15.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_WALK_e, BTPNUM_CLOSE_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_TALK01_e, BTPNUM_KF_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_TALK02_e, BTPNUM_KF_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_TALK03_e, BTPNUM_KF_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_TALK04_e, BTPNUM_KF_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_OKORU_e, BTPNUM_KF_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_BAKUHATU_e, BTPNUM_KF_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {BCKNUM_BARAMAKU_e, BTPNUM_KF_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {BCKNUM_WAIT02_e, BTPNUM_CLOSE_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };

    if (i_setBtp) {
        init_texPttrnAnm(a_anm_prm_tbl[i_anmNum].btpNum, true);
    }
    setAnm_anm(&a_anm_prm_tbl[i_anmNum]);
}

/* 00000D14-00000D70       .text setAnm__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::setAnm() {
    static anm_prm_c a_anm_prm_tbl[4] = {
        {-1, -1, 0.0f, 0.0f, J3DFrameCtrl::EMode_NULL},
        {-1, -1, 0.0f, 0.0f, J3DFrameCtrl::EMode_NULL},
        {-1, -1, 0.0f, 0.0f, J3DFrameCtrl::EMode_NULL},
        {BCKNUM_WALK_e, BTPNUM_CLOSE_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };

    init_texPttrnAnm(a_anm_prm_tbl[mStt].btpNum, true);
    setAnm_anm(&a_anm_prm_tbl[mStt]);
}

/* 00000D70-00000D74       .text chngAnmTag__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::chngAnmTag() {
}

/* 00000D74-00000D78       .text ctrlAnmTag__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::ctrlAnmTag() {
}

/* 00000D78-00000DEC       .text chngAnmAtr__11daNpc_Kf1_cFUc */
void daNpc_Kf1_c::chngAnmAtr(u8 i_atr) {
    switch (mCurrMsgNo) {
    case 0x1C2E:
        dComIfGp_event_offHindFlag(0x80);
        break;
    }

    if (i_atr == mAnmAtr || i_atr > 11) {
        return;
    }
    mAnmAtr = i_atr;
    setAnm_ATR();
}

/* 00000DEC-00000E60       .text ctrlAnmAtr__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::ctrlAnmAtr() {
    switch (mAnmAtr) {
    case 7:
    case 9:
        if (mbMorfAnimStopped) {
            setAnm_NUM(0, 1);
            mAnmAtr = 0;
        }
        break;
    case 5:
        break;
    case 6:
        break;
    case 8:
        break;
    case 10:
        break;
    }
}

/* 00000E60-00000EB8       .text setAnm_ATR__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::setAnm_ATR() {
    static anm_prm_c a_anm_prm_tbl[11] = {
        {BCKNUM_WAIT01_e, BTPNUM_KF_e, 15.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_WALK_e, BTPNUM_CLOSE_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_TALK01_e, BTPNUM_KF_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_TALK02_e, BTPNUM_KF_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_TALK03_e, BTPNUM_KF_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_TALK04_e, BTPNUM_KF_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_OKORU_e, BTPNUM_KF_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_BAKUHATU_e, BTPNUM_KF_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {BCKNUM_BARAMAKU_e, BTPNUM_KF_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {BCKNUM_TALK02_e, BTPNUM_KF_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_WAIT02_e, BTPNUM_CLOSE_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };

    init_texPttrnAnm(a_anm_prm_tbl[mAnmAtr].btpNum, true);
    setAnm_anm(&a_anm_prm_tbl[mAnmAtr]);
}

/* 00000EB8-00000F74       .text anmAtr__11daNpc_Kf1_cFUs */
void daNpc_Kf1_c::anmAtr(u16 i_msgStatus) {
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

/* 00000F74-000010E8       .text next_msgStatus__11daNpc_Kf1_cFPUl */
u16 daNpc_Kf1_c::next_msgStatus(u32* o_msgNoP) {
    u16 msg_status = fopMsgStts_MSG_CONTINUES_e;
    switch (*o_msgNoP) {
    case 0x1C23:
        switch (mpCurrMsg->mSelectNum) {
        case 0:
            *o_msgNoP = 0x1C24;
            break;
        case 1:
            *o_msgNoP = 0x1C25;
            break;
        }
        break;
    case 0x1C28:
        switch (mpCurrMsg->mSelectNum) {
        case 0:
            *o_msgNoP = 0x1C2A;
            break;
        case 1:
            *o_msgNoP = 0x1C29;
            break;
        }
        break;
    case 0x1C24:
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_0B02);
        msg_status = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x1C2B:
        m7A0 = true;
        msg_status = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x1C21:
        *o_msgNoP = 0x1C22;
        break;
    case 0x1C22:
        *o_msgNoP = 0x1C34;
        break;
    case 0x1C34:
        *o_msgNoP = 0x1C23;
        break;
    case 0x1C27:
        *o_msgNoP = 0x1C28;
        break;
    case 0x1C2A:
        *o_msgNoP = 0x1C2B;
        break;
    case 0x1C30:
        *o_msgNoP = 0x1C31;
        break;
    case 0x1C2D:
        *o_msgNoP = 0x1C2E;
        break;
    case 0x1C33:
        *o_msgNoP = mRupee >= mBrokenNum * 10 ? 0x1C2F : 0x1C30;
        break;
    case 0x1C36:
        *o_msgNoP = 0x1C37;
        break;
    default:
        msg_status = fopMsgStts_MSG_ENDS_e;
        break;
    }
    return msg_status;
}

/* 000010E8-000011DC       .text getMsg_KF1_0__11daNpc_Kf1_cFv */
u32 daNpc_Kf1_c::getMsg_KF1_0() {
    if (mbPaid) {
        return 0x1C38;
    }
    if (dComIfGs_isEventBit(dSv_event_flag_c::ENDLESS_NIGHT) && !dComIfGs_isSymbol(0)) {
        return 0x1C3B;
    }
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B02)) {
        u8 reg = dComIfGs_getEventReg(dSv_event_flag_c::UNK_BCFF);
        if (dKy_daynight_check() == 1 || !dComIfGs_isEventBit(dSv_event_flag_c::UNK_2780) || (reg & 1)) {
            return 0x1C26;
        }
        return 0x1C27;
    }
    return 0x1C21;
}

/* 000011DC-00001220       .text getMsg__11daNpc_Kf1_cFv */
u32 daNpc_Kf1_c::getMsg() {
    u32 result = 0;
    switch (mType) {
    case 0:
        result = getMsg_KF1_0();
        break;
    }
    return result;
}

/* 00001220-000012A8       .text eventOrder__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::eventOrder() {
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

/* 000012A8-00001384       .text checkOrder__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (dComIfGp_evmng_startCheck(mEventIDTbl[mEventIndex]) && mOrder >= 3) {
            switch (mEventIndex) {
            case 0:
                daPy_getPlayerActorClass()->changeDemoMoveAngle(dComIfGp_getPlayer(0)->current.angle.y);
                break;
            case 1:
            case 2:
                break;
            }
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

/* 00001384-0000141C       .text chk_talk__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::chk_talk() {
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

/* 0000141C-00001470       .text searchByID__11daNpc_Kf1_cFUiPi */
fopAc_ac_c* daNpc_Kf1_c::searchByID(fpc_ProcID i_PID, int* o_notFound) {
    fopAc_ac_c* actor_p;

    actor_p = NULL;
    *o_notFound = 0;
    if (!fopAcM_SearchByID(i_PID, &actor_p)) {
        *o_notFound = 1;
    }

    return actor_p;
}

/* 00001470-0000156C       .text srch_Tsubo__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::srch_Tsubo() {
    bool ret = false;

    if (mActionState != 1) {
        return false;
    }

    m700 = fpcM_ERROR_PROCESS_ID_e;
    l_check_wrk = 0;
    for (int i = 0; i < ARRAY_SSIZE(l_check_inf); i++) {
        l_check_inf[i] = NULL;
    }

    fpcM_Search(searchActor_Tsubo, this);

    if (l_check_wrk >= 8) {
        mTsuboNum = 0;
        for (int i = 0; i < 8; i++) {
            mTsuboIDs[i] = fopAcM_GetID(l_check_inf[i]);
            mTsuboNum++;
        }
        ret = true;
        mActionState++;
    }
    return ret;
}

static inline s16 kf1_deg2s(s16 i_deg) {
    return i_deg * (32767.0f / 180.0f);
}

/* 0000156C-000017E8       .text create_rupee__11daNpc_Kf1_cF4cXyzi */
void daNpc_Kf1_c::create_rupee(cXyz i_pos, int i_num) {
    cXyz a_scale(0.2f, 0.2f, 0.2f);
    csXyz a_angle(0, 0, 0);
    int i;
    int cnt = g_Counter.mCounter0;

    for (i = 0; i < i_num; i++, cnt++) {
        f32 a_ang_tbl[] = {-30.0f, 0.0f, 30.0f};
        a_angle.y = current.angle.y + kf1_deg2s((s16)(a_ang_tbl[cnt % 3] + (cM_rndF(30.0f) - 15.0f)));

        fopAc_ac_c* a_actor_p = fopAcM_createItemForKP2(&i_pos, dItemNo_RED_RUPEE_e, fopAcM_GetRoomNo(this), NULL, NULL, 13.0f + cM_rndFX(2.0f), 31.0f + cM_rndFX(4.0f), -2.0f, 1);
        JUT_ASSERT(0x412, a_actor_p != NULL);

        if (a_actor_p != NULL) {
            fopAcM_OnStatus(a_actor_p, fopAcStts_UNK4000_e);
            fopAcM_OffStatus(a_actor_p, fopAcStts_NOCULLEXEC_e);
            a_actor_p->scale = a_scale;
            a_actor_p->shape_angle = a_angle;
            a_actor_p->current.angle = a_actor_p->shape_angle;
            mRupeeIDs[i] = fopAcM_GetID(a_actor_p);
        }
    }
}

/* 000017E8-00001A08       .text ready_kutaniCamera__11daNpc_Kf1_cFii */
void daNpc_Kf1_c::ready_kutaniCamera(int i_idx, int i_set) {
    int i_flg;
    fopAc_ac_c* a_actor = searchByID(mItemID, &i_flg);
    if (a_actor != NULL && i_flg == 0) {
        fopAcM_delete(a_actor);
    }

    if (i_set) {
        cXyz a_scale(0.1f, 0.1f, 0.1f);
        csXyz a_angle(0, 0, 0);

        a_actor = searchByID(mCamTsuboIDs[i_idx], &i_flg);
        JUT_ASSERT(0x432, 0 != a_actor && 0 == i_flg);

        dComIfGp_event_setItemPartner(a_actor);
        a_angle.y = a_actor->current.angle.y;
        cXyz a_pos = a_actor->current.pos;
        a_pos.y = 180.0f + a_pos.y;

        a_actor = fopAcM_createItemForKP2(&a_pos, dItemNo_RED_RUPEE_e, fopAcM_GetRoomNo(this), NULL, NULL, 0.0f, 0.0f, -4.0f, 1);
        JUT_ASSERT(0x43E, 0 != a_actor);

        fopAcM_OnStatus(a_actor, fopAcStts_UNK4000_e);
        fopAcM_OffStatus(a_actor, fopAcStts_NOCULLEXEC_e);
        a_actor->scale = a_scale;
        a_actor->current.angle = a_angle;
        mItemID = fopAcM_GetID(a_actor);
    }
}

/* 00001A08-00001BC8       .text lookBack__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::lookBack() {
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
    bool head_only = m7AD;

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

/* 00001BC8-00001C48       .text chkAttention__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::chkAttention() {
    dAttention_c& attention = dComIfGp_getAttention();
    if (attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    } else {
        return this == attention.ActionTarget(0);
    }
}

/* 00001C48-00001CA0       .text setAttention__11daNpc_Kf1_cFb */
void daNpc_Kf1_c::setAttention(bool i_setEyePos) {
    attention_info.position.set(current.pos.x, current.pos.y + l_HIO.mPrm.mAttPosOffsetY, current.pos.z);

    if (!mbSetEyePos && !i_setEyePos) {
        return;
    }

    eyePos.set(mTransformedEyePos.x, mTransformedEyePos.y, mTransformedEyePos.z);
}

/* 00001CA0-00001D30       .text decideType__11daNpc_Kf1_cFi */
bool daNpc_Kf1_c::decideType(int i_type) {
    if (m7FB > 0) {
        return true;
    }

    m7FB = 1;
    mType = 0;

    strcpy(mArcName, "Kf");
    return m7FB != -1 && mType != -1;
}

/* 00001D30-00001E00       .text cut_init_ANGRY_START__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_ANGRY_START(int i_staffIdx) {
    cXyz* pos_p = dComIfGp_evmng_getMyXyzP(i_staffIdx, "Pos");
    if (pos_p != NULL) {
        current.pos.set(pos_p->x, pos_p->y, pos_p->z);
        mObjAcch.SetOld();
    }

    mPlayerEyePos.set(0.0f, eyePos.y, 0.0f);
    mLookMode = 2;
    current.angle.y = cLib_targetAngleY(&current.pos, &mPlayerEyePos);
    speedF = 0.0f;
    setAnm_NUM(0, 1);
}

/* 00001E00-00001E08       .text cut_move_ANGRY_START__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_ANGRY_START() {
    return TRUE;
}

/* 00001E08-00001E64       .text cut_init_BENSYOU_START__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_BENSYOU_START(int i_staffIdx) {
    cut_init_ANGRY_START(i_staffIdx);
    cXyz goal(0.0f, 0.0f, 700.0f);
    dComIfGp_evmng_setGoal(&goal);
}

/* 00001E64-00001E6C       .text cut_move_BENSYOU_START__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_BENSYOU_START() {
    return TRUE;
}

/* 00001E6C-00001EC0       .text cut_init_TSUBO_CNT__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_TSUBO_CNT(int) {
    mBrokenNum = mTsuboNum - chk_tsubo();
    m_jnt.setBackBone_x(0);
    m_jnt.setBackBone_y(0);
    m_jnt.setHead_x(0);
    m_jnt.setHead_y(0);
    mLookMode = 0;
}

/* 00001EC0-00001EC8       .text cut_move_TSUBO_CNT__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_TSUBO_CNT() {
    return TRUE;
}

/* 00001EC8-00001EF0       .text cut_init_BENSYOU__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_BENSYOU(int) {
    mRupee = dComIfGs_getRupee();
    dComIfGp_setItemRupeeCount(-(mBrokenNum * 10));
}

/* 00001EF0-00001EF8       .text cut_move_BENSYOU__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_BENSYOU() {
    return TRUE;
}

/* 00001EF8-00001FE4       .text cut_init_GET_OUT__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_GET_OUT(int i_staffIdx) {
    int* timer_p = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "Timer");
    mCutTimer = 0;
    if (timer_p != NULL) {
        mCutTimer = *timer_p;
    }

    ((daPy_py_c*)dComIfGp_getPlayer(0))->changeDemoMoveAngle(0);
    ((daPy_py_c*)dComIfGp_getPlayer(0))->changeOriginalDemo();

    if (mRupee >= mBrokenNum * 10) {
        cXyz goal(0.0f, 0.0f, 999.0f);
        cLib_targetAngleY(&dComIfGp_getPlayer(0)->current.pos, &goal);
        ((daPy_py_c*)dComIfGp_getPlayer(0))->changeDemoMode(daPy_demo_c::DEMO_N_DASH_e);
    } else {
        ((daPy_py_c*)dComIfGp_getPlayer(0))->changeDemoParam0(1);
        ((daPy_py_c*)dComIfGp_getPlayer(0))->changeDemoMode(daPy_demo_c::DEMO_LDAM_e);
    }
}

/* 00001FE4-00002044       .text cut_move_GET_OUT__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_GET_OUT() {
    if (cLib_calcTimer(&mCutTimer) == 0) {
        dComIfGp_setNextStage("sea", 3, 11, -1, 0.0f, 0, TRUE, 0);
    }
    return FALSE;
}

/* 00002044-00002060       .text cut_init_DSP_RUPEE_CNT__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_DSP_RUPEE_CNT(int) {
    dComIfGp_event_offHindFlag(0x80);
}

/* 00002060-00002068       .text cut_move_DSP_RUPEE_CNT__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_DSP_RUPEE_CNT() {
    return TRUE;
}

/* 00002068-000020B0       .text cut_init_PLYER_TRN__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_PLYER_TRN(int) {
    daPy_getPlayerActorClass()->changeDemoMoveAngle(cLib_targetAngleY(&dComIfGp_getPlayer(0)->current.pos, &current.pos));
}

/* 000020B0-000020B8       .text cut_move_PLYER_TRN__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_PLYER_TRN() {
    return TRUE;
}

/* 000020B8-000020BC       .text cut_init_RUPEE_CNT_END__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_RUPEE_CNT_END(int) {
}

/* 000020BC-000020EC       .text cut_move_RUPEE_CNT_END__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_RUPEE_CNT_END() {
    if ((u16)dComIfGs_getRupee() == dComIfGp_getItemNowRupee()) {
        dComIfGp_event_onHindFlag(0x80);
        return TRUE;
    }
    return FALSE;
}

/* 000020EC-00002168       .text cut_init_START_AGE__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_START_AGE(int) {
    mPlayerEyePos.set(0.0f, eyePos.y, 0.0f);
    shape_angle.y = cLib_targetAngleY(&current.pos, &mPlayerEyePos);
    m7A8 = true;
    mLookMode = 3;
    mTargetAngleY = shape_angle.y;
    m_jnt.setTrn();
    setAnm_NUM(0, 1);
}

/* 00002168-00002178       .text cut_move_START_AGE__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_START_AGE() {
    return m_jnt.trnChk() == false;
}

/* 00002178-00002284       .text cut_init_PLYER_MOV__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_PLYER_MOV(int) {
    s16 angle = cLib_targetAngleY(&current.pos, &dComIfGp_getPlayer(0)->current.pos) - current.angle.y;
    if (abs(angle) > 0x2000) {
        dComIfGp_evmng_setGoal(&dComIfGp_getPlayer(0)->current.pos);
    } else {
        cXyz goal;
        cXyz offset(0.0f, 0.0f, 0.0f);
        angle = angle > 0 ? 0x2800 : -0x2800;
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::YrotM(current.angle.y + angle);
        offset.z = 150.0f;
        mDoMtx_stack_c::multVec(&offset, &goal);
        dComIfGp_evmng_setGoal(&goal);
    }
}

/* 00002284-0000228C       .text cut_move_PLYER_MOV__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_PLYER_MOV() {
    return TRUE;
}

/* 0000228C-000023E0       .text cut_init_RUPEE_SET__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_RUPEE_SET(int) {
    if (mTsuboNum == 8) {
        u8 a_used[8] = {0, 0, 0, 0, 0, 0, 0, 0};
        int idx;
        for (int i = 0; i < 3; i++) {
            do {
                idx = cM_rndF(32.0f) / 4.0f;
            } while (a_used[idx] != 0);

            fpc_ProcID id = mTsuboIDs[idx];
            fopAc_ac_c* a_tsubo_actor = (fopAc_ac_c*)fopAcM_Search(fpcSch_JudgeByID, &id);
            JUT_ASSERT(0x5C3, 0 != a_tsubo_actor);

            fopAcM_SetParam(a_tsubo_actor, (fopAcM_GetParam(a_tsubo_actor) & ~0x3F) | dItemNo_RED_RUPEE_e);
            dComIfGp_event_setItemPartner(a_tsubo_actor);
            mCamTsuboIDs[i] = mTsuboIDs[idx];
            a_used[idx] = 1;
        }
    }
    setAnm_NUM(8, 1);
}

/* 000023E0-00002608       .text cut_move_RUPEE_SET__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_RUPEE_SET() {
    int i;
    int count = 0;
    int not_found;

    if (!mbMorfAnimStopped) {
        if (mpMorf->checkFrame(68.0f)) {
            cXyz offset(0.0f, 40.0f, 40.0f);
            cXyz pos;
            mDoAud_seStart(JA_SE_OBJ_LUPY_OUT, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
            mDoMtx_stack_c::transS(current.pos);
            mDoMtx_stack_c::YrotM(current.angle.y);
            mDoMtx_stack_c::multVec(&offset, &pos);
            create_rupee(pos, 3);
        } else if (68.0f < mpMorf->getFrame()) {
            for (int i = 0; i < 3; i++) {
                fopAc_ac_c* actor_p = searchByID(mRupeeIDs[i], &not_found);
                if (actor_p != NULL && not_found == 0) {
                    eyePos = actor_p->current.pos;
                }
            }
            mbSetEyePos = FALSE;
        }
        return FALSE;
    }

    for (i = 0; i < 3; i++) {
        fopAc_ac_c* actor_p = searchByID(mRupeeIDs[i], &not_found);
        if (actor_p != NULL) {
            fopAcM_delete(actor_p);
            count++;
        } else if (not_found != 0) {
            count++;
        }
    }

    if (count == i) {
        ready_kutaniCamera(0, 1);
        mbSetEyePos = TRUE;
        setAnm_NUM(0, 1);
        return TRUE;
    }
    return FALSE;
}

/* 00002608-000026B4       .text cut_init_TSUBO_ATN__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_TSUBO_ATN(int i_staffIdx) {
    int* timer_p = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "Timer");
    int* count_p = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "Count");

    mCutTimer = 0;
    if (timer_p != NULL) {
        mCutTimer = *timer_p;
    }
    mCutCount = 0;
    if (count_p != NULL) {
        mCutCount = *count_p;
    }
}

/* 000026B4-00002794       .text cut_move_TSUBO_ATN__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_TSUBO_ATN() {
    if (cLib_calcTimer(&mCutTimer) == 0) {
        if (mCutCount >= 0 && mCutCount <= 3) {
            switch (mCutCount) {
            case 0:
            case 1:
            case 2:
                ready_kutaniCamera(mCutCount, 1);
                break;
            case 3:
            default:
                ready_kutaniCamera(0, 0);
                break;
            }
        }
        return TRUE;
    }

    if (mCutTimer == 20) {
        mDoAud_seStart(JA_SE_OBJ_LUPY_IN_POT, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
    }
    return FALSE;
}

/* 00002794-000028F0       .text cut_init_TLK_MSG__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_TLK_MSG(int i_staffIdx) {
    int* msg_num_p = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "MsgNum");
    int* end_msg_p = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "EndMsg");

    mAnmAtr = 0xFF;
    mMesgAnimeTag = 0xFF;
    mMsgCount = 0;
    mCurrMsgNo = 0;
    mEndMsgNo = -1;
    if (end_msg_p != NULL) {
        mEndMsgNo = *end_msg_p;
    }

    if (msg_num_p != NULL) {
        mCurrMsgNo = *msg_num_p;
        switch (mCurrMsgNo) {
        case 0x1C2D:
            dComIfGp_setMessageCountNumber(mBrokenNum * 10);
            break;
        case 0x1C2E:
            break;
        case 0x1C2F:
        case 0x1C30:
            mCurrMsgNo = mRupee >= mBrokenNum * 10 ? 0x1C2F : 0x1C30;
            break;
        case 0x1C39:
            dComIfGp_getVibration().StartShock(5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            break;
        }
    }
    mCurrMsgBsPcId = fpcM_ERROR_PROCESS_ID_e;
}

/* 000028F0-00002950       .text cut_init_CONTNUE_TLK__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_CONTNUE_TLK(int i_staffIdx) {
    int* end_msg_p = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "EndMsg");
    mEndMsgNo = -1;
    if (end_msg_p != NULL) {
        mEndMsgNo = *end_msg_p;
    }
}

/* 00002950-000029D8       .text cut_move_TLK_MSG__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_TLK_MSG() {
    u16 status = talk(0);
    if (status == fopMsgStts_BOX_CLOSED_e) {
        mAnmAtr = 0xFF;
        mMesgAnimeTag = 0xFF;
        mMsgCount = 0;
        return TRUE;
    }
    if (status == fopMsgStts_BOX_OPENING_e || status == fopMsgStts_MSG_TYPING_e) {
        return mCurrMsgNo == mEndMsgNo;
    }
    return FALSE;
}

/* 000029D8-00002C5C       .text privateCut__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::privateCut(int i_staffIdx) {
    static char* a_cut_tbl[] = {
        "ANGRY_START",
        "BENSYOU_START",
        "TSUBO_CNT",
        "BENSYOU",
        "GET_OUT",
        "DSP_RUPEE_CNT",
        "PLYER_TRN",
        "RUPEE_CNT_END",
        "START_AGE",
        "PLYER_MOV",
        "RUPEE_SET",
        "TSUBO_ATN",
        "TLK_MSG",
        "CONTNUE_TLK",
    };

    if (i_staffIdx == -1) {
        return;
    }

    mActionIndex = dComIfGp_evmng_getMyActIdx(i_staffIdx, a_cut_tbl, ARRAY_SSIZE(a_cut_tbl), TRUE, 0);

    if (mActionIndex == -1) {
        dComIfGp_evmng_cutEnd(i_staffIdx);
        return;
    }

    if (dComIfGp_evmng_getIsAddvance(i_staffIdx)) {
        switch (mActionIndex) {
        case 0:
            cut_init_ANGRY_START(i_staffIdx);
            break;
        case 1:
            cut_init_BENSYOU_START(i_staffIdx);
            break;
        case 2:
            cut_init_TSUBO_CNT(i_staffIdx);
            break;
        case 3:
            cut_init_BENSYOU(i_staffIdx);
            break;
        case 4:
            cut_init_GET_OUT(i_staffIdx);
            break;
        case 5:
            cut_init_DSP_RUPEE_CNT(i_staffIdx);
            break;
        case 6:
            cut_init_PLYER_TRN(i_staffIdx);
            break;
        case 7:
            cut_init_RUPEE_CNT_END(i_staffIdx);
            break;
        case 8:
            cut_init_START_AGE(i_staffIdx);
            break;
        case 9:
            cut_init_PLYER_MOV(i_staffIdx);
            break;
        case 10:
            cut_init_RUPEE_SET(i_staffIdx);
            break;
        case 11:
            cut_init_TSUBO_ATN(i_staffIdx);
            break;
        case 12:
            cut_init_TLK_MSG(i_staffIdx);
            break;
        case 13:
            cut_init_CONTNUE_TLK(i_staffIdx);
            break;
        }
    }

    bool cut_end;
    switch (mActionIndex) {
    case 0:
        cut_end = cut_move_ANGRY_START();
        break;
    case 1:
        cut_end = cut_move_BENSYOU_START();
        break;
    case 2:
        cut_end = cut_move_TSUBO_CNT();
        break;
    case 3:
        cut_end = cut_move_BENSYOU();
        break;
    case 4:
        cut_end = cut_move_GET_OUT();
        break;
    case 5:
        cut_end = cut_move_DSP_RUPEE_CNT();
        break;
    case 6:
        cut_end = cut_move_PLYER_TRN();
        break;
    case 7:
        cut_end = cut_move_RUPEE_CNT_END();
        break;
    case 8:
        cut_end = cut_move_START_AGE();
        break;
    case 9:
        cut_end = cut_move_PLYER_MOV();
        break;
    case 10:
        cut_end = cut_move_RUPEE_SET();
        break;
    case 11:
        cut_end = cut_move_TSUBO_ATN();
        break;
    case 12:
        cut_end = cut_move_TLK_MSG();
        break;
    case 13:
        cut_end = cut_move_TLK_MSG();
        break;
    default:
        cut_end = true;
        break;
    }

    if (cut_end) {
        dComIfGp_evmng_cutEnd(i_staffIdx);
    }
}

/* 00002C5C-00002C80       .text endEvent__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::endEvent() {
    dComIfGp_event_reset();
    mAnmAtr = 0xFF;
    mMesgAnimeTag = 0xFF;
}

/* 00002C80-00002CB8       .text isEventEntry__11daNpc_Kf1_cFv */
int daNpc_Kf1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName());
}

/* 00002CB8-00002E14       .text event_proc__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::event_proc(int i_staffIdx) {
    if (dComIfGp_evmng_endCheck(mEventIDTbl[mEventIndex])) {
        switch (mEventIndex) {
        case 2:
            break;
        case 0:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_2780);
            mTsuboNum = chk_tsubo();
            break;
        case 1: {
            u8 reg = dComIfGs_getEventReg(dSv_event_flag_c::UNK_BCFF);
            reg |= 1;
            dComIfGs_setEventReg(dSv_event_flag_c::UNK_BCFF, reg);
            m7A8 = false;
            setStt(1);
            setAnm_NUM(0, 1);
            mWaitTimer = cLib_getRndValue(30, 60);
            mTalkTimer = cLib_getRndValue(15, 30);
            mbPaid = true;
            break;
        }
        }
        mWaitTimer = cLib_getRndValue(30, 60);
        endEvent();
    } else {
        if (mEventCut.cutProc()) {
            return;
        }
        privateCut(i_staffIdx);
    }
}

/* 00002E14-00002EC0       .text set_action__11daNpc_Kf1_cFM11daNpc_Kf1_cFPCvPvPv_iPv */
BOOL daNpc_Kf1_c::set_action(ProcFunc i_newProcFunc, void* i_argsP) {
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

/* 00002EC0-00002F88       .text setStt__11daNpc_Kf1_cFSc */
void daNpc_Kf1_c::setStt(s8 i_stt) {
    u8 prev_stt = mStt;
    mStt = i_stt;
    switch (mStt) {
    case 0:
        break;
    case 1:
        mOrder = 0;
        mWalkTimer = cLib_getRndValue(60, 90);
        speedF = 0.0f;
        break;
    case 2:
        mOrder = 0;
        mAnmAtr = 0xFF;
        mMesgAnimeTag = 0xFF;
        mMsgCount = 0;
        mPrevStt = prev_stt;
        break;
    case 3:
        mOrder = 0;
        mWalkTimer = cLib_getRndValue(90, 90);
        break;
    }
    setAnm();
}

/* 00002F88-00003030       .text set_pthPoint__11daNpc_Kf1_cFUc */
void daNpc_Kf1_c::set_pthPoint(u8 i_idx) {
    if (mPath.isPath()) {
        mPath.setIdx(i_idx);
        current.pos = mPath.getPoint(mPath.getIdx());
        if (mPath.nextIdx()) {
            cXyz next = mPath.getPoint(mPath.getIdx());
            current.angle.y = cLib_targetAngleY(&current.pos, &next);
        }
    }
}

/* 00003030-000030A4       .text chk_tsubo__11daNpc_Kf1_cFv */
s16 daNpc_Kf1_c::chk_tsubo() {
    s16 num = 0;
    for (int i = 0; i < 8; i++) {
        int not_found;
        searchByID(mTsuboIDs[i], &not_found);
        if (not_found == 0) {
            num++;
        }
    }
    return num;
}

/* 000030A4-0000317C       .text orderTsuboEvent__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::orderTsuboEvent() {
    if (mbTalkReq) {
        return FALSE;
    }

    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2780)) {
        if (mTsuboNum > chk_tsubo()) {
            mOrder = 3;
            return TRUE;
        }
    } else if (mSwitchNo != 0xFF && dComIfGs_isSwitch(mSwitchNo, fopAcM_GetRoomNo(this))) {
        if (mTsuboNum > chk_tsubo()) {
            mOrder = 5;
            return TRUE;
        }
    }
    return FALSE;
}

/* 0000317C-0000327C       .text wait_1__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::wait_1() {
    if (mbTalkReq) {
        if (chk_talk()) {
            setStt(2);
            mLookMode = 1;
            m7AD = false;
            m_jnt.setTrn();
        }
        return TRUE;
    }

    if (mOrder < 3) {
        mOrder = 2;
    }
    m7AD = true;

    if (mBckNum == BCKNUM_WAIT02_e) {
        mWaitTimer = 0;
    }

    if (cLib_calcTimer(&mWaitTimer) == 0) {
        if (mBckNum != BCKNUM_WAIT02_e) {
            setAnm_NUM(9, 1);
            mWalkTimer = 0;
        }
        if (cLib_calcTimer(&mWalkTimer) == 0) {
            setStt(3);
            return TRUE;
        }
    }

    mLookMode = 0;
    return TRUE;
}

/* 0000327C-000034BC       .text walk_1__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::walk_1() {
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
    if (cLib_calcTimer(&mWalkTimer) == 0 || mbTalkReq) {
        target_speed = 0.0f;
    }
    cLib_chaseF(&speedF, target_speed, l_HIO.mPrm.mWalkAccel);

    f32 rate = speedF * l_HIO.mPrm.mWalkAnmRate;
    f32 anm_speed = rate < 0.5f ? 0.5f : rate;
    mpMorf->setPlaySpeed(anm_speed);

    if ((int)target_speed == 0 && (int)speedF == 0) {
        if (mbTalkReq) {
            if (chk_talk()) {
                setStt(1);
                setAnm_NUM(9, 1);
                mLookMode = 1;
                m7AD = false;
                m_jnt.setTrn();
            }
            return TRUE;
        }
        setStt(1);
        setAnm_NUM(9, 1);
        return TRUE;
    }

    if (mOrder < 3) {
        mOrder = 2;
    }
    mLookMode = 0;
    m7AD = true;
    return TRUE;
}

/* 000034BC-000035CC       .text talk_1__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::talk_1() {
    bool order_age = false;
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
        case 0x1C2B:
            order_age = true;
            break;
        }
        mItemNo = 0xFF;
        mbTalkReq = false;
        setStt(mPrevStt);
        setAnm_NUM(0, 1);
        mWaitTimer = cLib_getRndValue(30, 60);
        mTalkTimer = cLib_getRndValue(15, 30);
        if (order_age) {
            mOrder = 4;
        }
        endEvent();
        break;
    }
    return mBckNum != BCKNUM_TALK03_e;
}

/* 000035CC-000036B0       .text wait_action1__11daNpc_Kf1_cFPv */
BOOL daNpc_Kf1_c::wait_action1(void*) {
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
        }
        if (mActionState > 1) {
            orderTsuboEvent();
        }
        break;
    default:
        break;
    }
    return TRUE;
}

/* 000036B0-00003800       .text demo__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::demo() {
    if (demoActorID == 0) {
        if (mbDemo) {
            mbDemo = false;
        }
    } else {
        if (!mbDemo) {
            mbDemo = true;
            m7A8 = false;
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

/* 00003800-0000389C       .text shadowDraw__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::shadowDraw() {
    cXyz pos(current.pos.x, current.pos.y + 150.0f, current.pos.z);

    mShadowID = dComIfGd_setShadow(mShadowID, 1, mpMorf->getModel(), &pos, 800.0f, 40.0f, current.pos.y, mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr);
}

static void dummy() {
    const GXColor dummy1 = {0xFF, 0x00, 0x00, 0x80};
    const GXColor dummy2 = {0x00, 0x00, 0xFF, 0x80};
    const GXColor dummy3 = {0xFF, 0xFF, 0x00, 0x80};
}

/* 0000389C-00003980       .text _draw__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::_draw() {
    J3DModel* morf_model_p = mpMorf->getModel();
    J3DModelData* morf_model_info_p = morf_model_p->getModelData();

    if (m7A7 || m7A9 != 0) {
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

    shadowDraw();
    dSnap_RegistFig(DSNAP_TYPE_UNK59, this, 1.0f, 1.0f, 1.0f);

    return TRUE;
}

/* 00003980-00003BE0       .text _execute__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::_execute() {
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

    if (m7A7 && demoActorID == 0) {
        return TRUE;
    }

    srch_Tsubo();
    checkOrder();
    if (!demo()) {
        int staff_id = -1;
        if (dComIfGp_event_runCheck() && eventInfo.checkCommandTalk() == false) {
            staff_id = isEventEntry();
        }

        if (staff_id >= 0 || m7A5) {
            event_proc(staff_id);
        } else {
            (this->*mCurrProcFunc)(NULL);
        }

        lookBack();
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
        mbGroundHit = mObjAcch.ChkGroundHit();
        mbWaterHit = mObjAcch.ChkWaterIn();
        mObjAcch.CrrPos(*dComIfG_Bgsp());
        play_animation();
    } else {
        m7A7 = false;
    }

    eventOrder();
    mAngle = current.angle;
    if (!m7A8) {
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

/* 00003BE0-00003C34       .text _delete__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::_delete() {
    dComIfG_resDelete(&mPhs, mArcName);
    if (heap && mpMorf) {
        mpMorf->stopZelAnime();
    }
    return TRUE;
}

/* 00003C34-00003EB0       .text _create__11daNpc_Kf1_cFv */
cPhs_State daNpc_Kf1_c::_create() {
    static int a_siz_tbl[] = {
        0,
        0,
    };

    cPhs_State state;

    fopAcM_ct(this, daNpc_Kf1_c);

    if (!decideType(fopAcM_GetParam(this) & 0xFF)) {
        return cPhs_ERROR_e;
    }

    state = dComIfG_resLoad(&mPhs, mArcName);
    mbResLoadIsComplete = state == cPhs_COMPLEATE_e;
    if (!mbResLoadIsComplete) {
        return state;
    }

    if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_siz_tbl[m7FB])) {
        return cPhs_ERROR_e;
    }

    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -90.0f, -20.0f, -80.0f, 90.0f, 200.0f, 80.0f);

    if (!createInit()) {
        return cPhs_ERROR_e;
    }

    return state;
}

/* 00004150-00004560       .text bodyCreateHeap__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::bodyCreateHeap() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes(mArcName, dRes_ID_KF_BDL_KF_e);
    JUT_ASSERT(0x97F, a_mdl_dat != NULL);

    mpMorf = new mDoExt_McaMorf(a_mdl_dat, NULL, NULL, NULL, J3DFrameCtrl::EMode_NULL, 1.0f, 0, -1, 1, NULL, 0x80000, 0x11020022);

    if (!mpMorf) {
        return FALSE;
    } else if (!mpMorf->getModel()) {
        mpMorf = NULL;
        return FALSE;
    }

    if (!init_texPttrnAnm(BTPNUM_KF_e, false)) {
        mpMorf = NULL;
        return FALSE;
    }

    m_hed_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
    JUT_ASSERT(0x993, m_hed_jnt_num >= 0);

    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(0x995, m_bbone_jnt_num >= 0);

    m_nck_jnt_num = a_mdl_dat->getJointName()->getIndex("neck");
    JUT_ASSERT(0x997, m_nck_jnt_num >= 0);

    mpMorf->getModel()->getModelData()->getJointNodePointer(m_hed_jnt_num)->setCallBack(nodeCB_Head);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_bbone_jnt_num)->setCallBack(nodeCB_BackBone);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_nck_jnt_num)->setCallBack(nodeCB_Neck);
    mpMorf->getModel()->setUserArea((uintptr_t)this);

    return TRUE;
}

/* 00004560-00004638       .text itemCreateHeap__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::itemCreateHeap() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes(mArcName, dRes_ID_KF_BDL_KF_HAIR_e);
    JUT_ASSERT(0x9AC, a_mdl_dat != NULL);

    mpHairModel = mDoExt_J3DModel__create(a_mdl_dat, 0x80000, 0x11000022);

    if (!mpHairModel) {
        return FALSE;
    }

    return TRUE;
}

/* 00004638-000046D8       .text CreateHeap__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::CreateHeap() {
    if (!bodyCreateHeap()) {
        return FALSE;
    }

    if (!itemCreateHeap()) {
        mpMorf = NULL;
        return FALSE;
    }

    mAcchCir.SetWall(30.0f, 90.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this), NULL, NULL);

    return TRUE;
}

/* 000046D8-000046F8       .text daNpc_Kf1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Kf1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Kf1_c*)i_this)->_create();
}

/* 000046F8-00004718       .text daNpc_Kf1_Delete__FP11daNpc_Kf1_c */
static BOOL daNpc_Kf1_Delete(daNpc_Kf1_c* i_this) {
    return ((daNpc_Kf1_c*)i_this)->_delete();
}

/* 00004718-00004738       .text daNpc_Kf1_Execute__FP11daNpc_Kf1_c */
static BOOL daNpc_Kf1_Execute(daNpc_Kf1_c* i_this) {
    return ((daNpc_Kf1_c*)i_this)->_execute();
}

/* 00004738-00004758       .text daNpc_Kf1_Draw__FP11daNpc_Kf1_c */
static BOOL daNpc_Kf1_Draw(daNpc_Kf1_c* i_this) {
    return ((daNpc_Kf1_c*)i_this)->_draw();
}

/* 00004758-00004760       .text daNpc_Kf1_IsDelete__FP11daNpc_Kf1_c */
static BOOL daNpc_Kf1_IsDelete(daNpc_Kf1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Kf1_Method = {
    (process_method_func)daNpc_Kf1_Create,
    (process_method_func)daNpc_Kf1_Delete,
    (process_method_func)daNpc_Kf1_Execute,
    (process_method_func)daNpc_Kf1_IsDelete,
    (process_method_func)daNpc_Kf1_Draw,
};

actor_process_profile_definition g_profile_NPC_KF1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_KF1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Kf1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_KF1_e,
    /* Actor SubMtd */ &l_daNpc_Kf1_Method,
    /* Status       */ 0x08 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
