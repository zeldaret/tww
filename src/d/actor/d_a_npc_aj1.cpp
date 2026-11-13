/**
 * d_a_npc_aj1.cpp
 * NPC - Sturgeon
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_aj1.h"
#include "d/actor/d_a_player.h"
#include "d/d_com_inf_game.h"
#include "d/d_detect.h"
#include "d/d_snap.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"
#include "m_Do/m_Do_lib.h"
#include "res/Object/Aj.h"
#include "SSystem/SComponent/c_counter.h"

class daNpc_Aj1_HIO_c : public mDoHIO_entry_c {
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
        /* 0x1C */ f32 mCallDist;
        /* 0x20 */ s16 mCallAngle;
        /* 0x24 */ f32 mTalkDist;
        /* 0x28 */ s16 mTalkAngle;
        /* 0x2A */ s16 mSurpriseTime;
        /* 0x2C */ s16 mLookTime;
    };  // Size: 0x30

    daNpc_Aj1_HIO_c();
    virtual ~daNpc_Aj1_HIO_c() {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ int m08;
    /* 0x0C */ hio_prm_c mPrm;
};  // Size: 0x3C

static daNpc_Aj1_HIO_c l_HIO;

/* 000000EC-00000150       .text __ct__15daNpc_Aj1_HIO_cFv */
daNpc_Aj1_HIO_c::daNpc_Aj1_HIO_c() {
    static hio_prm_c a_prm_tbl = {
        /* mMaxHeadX       */ 0x2000,
        /* mMaxHeadY       */ 0x1F40,
        /* mMinHeadX       */ 0x01F4,
        /* mMinHeadY       */ -0x32C8,
        /* mMaxBackBoneX   */ 0x0000,
        /* mMaxBackBoneY   */ 0x1C70,
        /* mMinBackBoneX   */ -0x05DC,
        /* mMinBackBoneY   */ -0x0096,
        /* mMaxTurnStep    */ 0x0400,
        /* mMaxHeadTurnVel */ 0x0400,
        /* mAttPosOffsetY  */ 150.0f,
        /* m18             */ 0,
        /* mCallDist       */ 1500.0f,
        /* mCallAngle      */ 0x5208,
        /* mTalkDist       */ 550.0f,
        /* mTalkAngle      */ 0x61A8,
        /* mSurpriseTime   */ 30,
        /* mLookTime       */ 20,
    };
    memcpy(&mPrm, &a_prm_tbl, sizeof(hio_prm_c));
    mNo = -1;
    m08 = -1;
}

static const char* l_evn_tbl[] = {
    "angry",
};

/* .text nodeCB_Head */
static BOOL nodeCB_Head(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In && j3dSys.getModel()->getUserArea() != 0) {
        daNpc_Aj1_c* actor_p = (daNpc_Aj1_c*)j3dSys.getModel()->getUserArea();
        actor_p->_nodeCB_Head(i_node, j3dSys.getModel());
    }
    return TRUE;
}

/* .text _nodeCB_Head */
void daNpc_Aj1_c::_nodeCB_Head(J3DNode* i_node, J3DModel* i_model) {
    static cXyz a_eye_pos_off(24.0f, -16.0f, 0.0f);

    J3DJoint* jnt_p = (J3DJoint*)i_node;
    s32 jnt_no = jnt_p->getJntNo();

    mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));

    mHeadPos.x = mDoMtx_stack_c::get()[0][3];
    mHeadPos.y = mDoMtx_stack_c::get()[1][3];
    mHeadPos.z = mDoMtx_stack_c::get()[2][3];

    mDoMtx_stack_c::YrotM(-m_jnt.getHead_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
    mDoMtx_stack_c::multVec(&a_eye_pos_off, &mTransformedEyePos);

    mDoMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    i_model->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* .text nodeCB_BackBone */
static BOOL nodeCB_BackBone(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In && j3dSys.getModel()->getUserArea() != 0) {
        daNpc_Aj1_c* actor_p = (daNpc_Aj1_c*)j3dSys.getModel()->getUserArea();
        actor_p->_nodeCB_BackBone(i_node, j3dSys.getModel());
    }
    return TRUE;
}

/* .text _nodeCB_BackBone */
void daNpc_Aj1_c::_nodeCB_BackBone(J3DNode* i_node, J3DModel* i_model) {
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
    return ((daNpc_Aj1_c*)i_this)->CreateHeap();
}

/* .text daNpc_Aj1_XyCheck_CB */
static s16 daNpc_Aj1_XyCheck_CB(void* i_this, int i_itemBtn) {
    return ((daNpc_Aj1_c*)i_this)->_XyCheckCB(i_itemBtn);
}

/* .text _XyCheckCB */
s16 daNpc_Aj1_c::_XyCheckCB(int i_itemBtn) {
    return dComIfGp_getSelectItem(i_itemBtn) == dItemNo_KNIGHTS_CREST_e;
}

/* .text init_AJ1_0 */
bool daNpc_Aj1_c::init_AJ1_0() {
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0E20) && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_0502)) {
        attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0x1A;
        set_action(&daNpc_Aj1_c::wait_action1, NULL);
        return true;
    }

    if (mSwitchNo != 0xFF && !dComIfGs_isSwitch(mSwitchNo, fopAcM_GetRoomNo(this))) {
        dComIfGs_onSwitch(mSwitchNo, fopAcM_GetRoomNo(this));
    }
    return false;
}

/* .text init_AJ1_1 */
bool daNpc_Aj1_c::init_AJ1_1() {
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0520)) {
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_0502);
        set_action(&daNpc_Aj1_c::wait_action2, NULL);
        fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
        fopAcM_OnStatus(this, fopAcStts_UNK4000_e);
        return true;
    }
    return false;
}

/* .text init_AJ1_2 */
bool daNpc_Aj1_c::init_AJ1_2() {
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0520)) {
        eventInfo.setXyCheckCB(daNpc_Aj1_XyCheck_CB);
        set_action(&daNpc_Aj1_c::wait_action2, NULL);
        return true;
    }
    return false;
}

/* .text createInit */
bool daNpc_Aj1_c::createInit() {
    mSwitchNo = (fopAcM_GetParam(this) >> 8) & 0xFF;
    mEventIDTbl[0] = dComIfGp_evmng_getEventIdx(l_evn_tbl[0]);
    mEventCut.setActorInfo2("Aj1", this);
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xAD;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xAD;
    mBckNum = BCKNUM_NULL_e;

    bool init_result;
    switch (mType) {
    case 0:
        init_result = init_AJ1_0();
        break;
    case 1:
        init_result = init_AJ1_1();
        break;
    case 2:
        init_result = init_AJ1_2();
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
    gravity = -4.5f;

    mStts.Init(0xFF, 0xFF, this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);

    play_animation();
    mObjAcch.CrrPos(*dComIfG_Bgsp());

    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    mpMorf->setMorf(0.0f);
    setMtx(true);

    return true;
}

/* .text play_animation */
void daNpc_Aj1_c::play_animation() {
    u32 snd_id = 0;

    play_texPttrnAnm();

    if (mObjAcch.ChkGroundHit()) {
        snd_id = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
    }

    mbMorfAnimStopped = mpMorf->play(&eyePos, snd_id, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));

    if (mpMorf->getFrame() < mPrevMorfFrame) {
        mbMorfAnimStopped = true;
    }

    mPrevMorfFrame = mpMorf->getFrame();
}

/* .text ctrl_WAITanm */
void daNpc_Aj1_c::ctrl_WAITanm() {
    switch (mBckNum) {
    case BCKNUM_WAIT01_e:
        if (cLib_calcTimer(&mWaitTimer) == 0 && mbMorfAnimStopped && chk_parts_notMov()) {
            setAnm_NUM(1, 1);
        }
        break;
    case BCKNUM_WAIT02_e:
        if (mbMorfAnimStopped) {
            setAnm_NUM(0, 1);
            mWaitTimer = cLib_getRndValue(90, 180);
        }
        break;
    }
}

/* .text ctrl_TIREanm */
void daNpc_Aj1_c::ctrl_TIREanm() {
    if (mBckNum == BCKNUM_TIRE_e) {
        if (mbMorfAnimStopped && cLib_calcTimer(&mTireTimer) == 0) {
            setAnm_NUM(0, 1);
            mpMorf->setMorf(20.0f);
        }
    } else {
        mTireTimer = 0;
    }
}

/* .text setMtx */
void daNpc_Aj1_c::setMtx(bool i_setEyePos) {
    mpMorf->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(mAngle);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());

    mpMorf->calc();

    if (mpStickModel) {
        mpStickModel->setBaseTRMtx(mpMorf->getModel()->getAnmMtx(m_hnd_L_jnt_num));
        mpStickModel->calc();
    }
    setAttention(i_setEyePos);
}

/* .text bckResID */
int daNpc_Aj1_c::bckResID(int i_bckNum) {
    static const int a_res_id_tbl[] = {
        dRes_ID_AJ_BCK_WAIT01_e,
        dRes_ID_AJ_BCK_WAIT02_e,
        dRes_ID_AJ_BCK_ANGRY_e,
        dRes_ID_AJ_BCK_JAMP_e,
        dRes_ID_AJ_BCK_SHOCK_e,
        dRes_ID_AJ_BCK_LOOK_e,
        dRes_ID_AJ_BCK_TIRE_e,
        dRes_ID_AJ_BCK_CALL_e,
        dRes_ID_AJ_BCK_NOBI_e,
    };
    return a_res_id_tbl[i_bckNum];
}

/* .text btpResID */
int daNpc_Aj1_c::btpResID(int i_btpNum) {
    static const int a_res_id_tbl[] = {
        dRes_ID_AJ_BTP_MABA_e,
    };
    return a_res_id_tbl[i_btpNum];
}

/* .text init_texPttrnAnm */
bool daNpc_Aj1_c::init_texPttrnAnm(s8 i_btpNum, bool i_bModify) {
    J3DModel* morf_model_p = mpMorf->getModel();

    if (i_btpNum < 0) {
        return false;
    }

    J3DAnmTexPattern* a_btp = (J3DAnmTexPattern*)dComIfG_getObjectIDRes("Aj", btpResID(i_btpNum));
    JUT_ASSERT(0x213, a_btp != NULL);
    mBtpNum = i_btpNum;
    mBtpFrame = 0;
    mBlinkTimer = 0;

    return mBtpAnm.init(morf_model_p->getModelData(), a_btp, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, i_bModify, 0) != 0;
}

/* .text play_texPttrnAnm */
void daNpc_Aj1_c::play_texPttrnAnm() {
    if (mBtpNum != BTPNUM_MABA_e || cLib_calcTimer(&mBlinkTimer) == 0) {
        mBtpFrame++;
        if (mBtpFrame >= mBtpAnm.getBtpAnm()->getFrameMax()) {
            if (mBtpNum != BTPNUM_MABA_e) {
                mBtpFrame = mBtpAnm.getBtpAnm()->getFrameMax();
            } else {
                mBlinkTimer = cLib_getRndValue(60, 90);
                mBtpFrame = 0;
            }
        }
    }
}

/* .text setAnm_anm */
void daNpc_Aj1_c::setAnm_anm(anm_prm_c* i_anmPrmP) {
    if (i_anmPrmP->bckNum < 0 || mBckNum == i_anmPrmP->bckNum) {
        return;
    }

    dNpc_setAnmIDRes(mpMorf, i_anmPrmP->loopMode, i_anmPrmP->morf, i_anmPrmP->speed, bckResID(i_anmPrmP->bckNum), -1, "Aj");
    mBckNum = i_anmPrmP->bckNum;
    mbMorfAnimStopped = false;
    m759 = 0;
    mPrevMorfFrame = 0.0f;

    switch (mBckNum) {
    case BCKNUM_ANGRY_e:
        set_pa_pun();
        set_pa_aka();
        set_pa_don();
        break;
    default:
        if (mpAkaEmitter != NULL) {
            mpAkaEmitter->stopCreateParticle();
            mbDelAka = true;
        }
        del_pa(&mpPunEmitter);
        del_pa(&mpDonEmitter);
        break;
    }
}

/* .text setAnm_NUM */
void daNpc_Aj1_c::setAnm_NUM(int i_anmNum, int i_setBtp) {
    static anm_prm_c a_anm_prm_tbl[9] = {
        {BCKNUM_WAIT01_e, BTPNUM_MABA_e, 0.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_WAIT02_e, BTPNUM_MABA_e, 0.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_ANGRY_e, BTPNUM_MABA_e, 0.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_JAMP_e, BTPNUM_MABA_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {BCKNUM_SHOCK_e, BTPNUM_MABA_e, 0.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {BCKNUM_LOOK_e, BTPNUM_MABA_e, 5.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {BCKNUM_TIRE_e, BTPNUM_MABA_e, 0.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_CALL_e, BTPNUM_MABA_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_NOBI_e, BTPNUM_MABA_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
    };

    if (i_setBtp) {
        init_texPttrnAnm(a_anm_prm_tbl[i_anmNum].btpNum, true);
    }
    setAnm_anm(&a_anm_prm_tbl[i_anmNum]);
}

/* .text setAnm */
void daNpc_Aj1_c::setAnm() {
    static anm_prm_c a_anm_prm_tbl[5] = {
        {-1, -1, 0.0f, 0.0f, J3DFrameCtrl::EMode_NULL},
        {BCKNUM_WAIT01_e, BTPNUM_MABA_e, 0.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_CALL_e, BTPNUM_MABA_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {-1, -1, 0.0f, 0.0f, J3DFrameCtrl::EMode_NULL},
        {BCKNUM_WAIT01_e, BTPNUM_MABA_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };

    init_texPttrnAnm(a_anm_prm_tbl[mStt].btpNum, true);
    setAnm_anm(&a_anm_prm_tbl[mStt]);
}

/* .text chngAnmTag */
void daNpc_Aj1_c::chngAnmTag() {
}

/* .text ctrlAnmTag */
void daNpc_Aj1_c::ctrlAnmTag() {
}

/* .text chngAnmAtr */
void daNpc_Aj1_c::chngAnmAtr(u8 i_atr) {
    if (i_atr == mAnmAtr || i_atr > 9) {
        return;
    }
    mAnmAtr = i_atr;
    setAnm_ATR();
    switch (mAnmAtr) {
    case 8:
        mTireTimer = 3;
        break;
    }
}

/* .text ctrlAnmAtr */
void daNpc_Aj1_c::ctrlAnmAtr() {
    switch (mAnmAtr) {
    case 1:
        break;
    case 6:
        break;
    case 2:
        ctrl_WAITanm();
        break;
    case 5:
        if (mbMorfAnimStopped) {
            mAnmAtr = 0;
            setAnm_NUM(0, 1);
        }
        break;
    }
    ctrl_TIREanm();
}

/* .text setAnm_ATR */
void daNpc_Aj1_c::setAnm_ATR() {
    static anm_prm_c a_anm_prm_tbl[9] = {
        {BCKNUM_WAIT01_e, BTPNUM_MABA_e, 0.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_WAIT02_e, BTPNUM_MABA_e, 0.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_WAIT01_e, BTPNUM_MABA_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_ANGRY_e, BTPNUM_MABA_e, 0.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_JAMP_e, BTPNUM_MABA_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {BCKNUM_WAIT02_e, BTPNUM_MABA_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_SHOCK_e, BTPNUM_MABA_e, 0.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {BCKNUM_LOOK_e, BTPNUM_MABA_e, 5.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {BCKNUM_TIRE_e, BTPNUM_MABA_e, 0.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };

    init_texPttrnAnm(a_anm_prm_tbl[mAnmAtr].btpNum, true);
    setAnm_anm(&a_anm_prm_tbl[mAnmAtr]);
}

/* .text anmAtr */
void daNpc_Aj1_c::anmAtr(u16 i_msgStatus) {
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

/* .text next_msgStatus */
u16 daNpc_Aj1_c::next_msgStatus(u32* o_msgNoP) {
    u16 msg_status = fopMsgStts_MSG_CONTINUES_e;
    switch (*o_msgNoP) {
    case 0x9C6:
        *o_msgNoP = 0x9C7;
        break;
    case 0x9C7:
        *o_msgNoP = 0x9C8;
        break;
    case 0x9C9:
        *o_msgNoP = 0x9CA;
        break;
    case 0x9C8:
    case 0x9CA:
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0001) && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_3704)) {
            *o_msgNoP = 0x9DA;
        } else {
            msg_status = fopMsgStts_MSG_ENDS_e;
        }
        break;
    case 0x9DB:
        if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0504)) {
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2A80)) {
                *o_msgNoP = 0x9DC;
            } else {
                *o_msgNoP = 0x9CB;
            }
        } else {
            *o_msgNoP = 0x9CF;
        }
        break;
    case 0x9CB:
    case 0x9DC:
        *o_msgNoP = 0x9CC;
        break;
    case 0x9CD:
        *o_msgNoP = 0x9CE;
        break;
    case 0x9CF:
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0001) && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_3704)) {
            *o_msgNoP = 0x9DD;
        } else {
            msg_status = fopMsgStts_MSG_ENDS_e;
        }
        break;
    case 0x9D0:
        if (!dComIfGs_isEventBit(dSv_event_flag_c::GRANDMA_HEALED)) {
            *o_msgNoP = 0x9D1;
        } else if (dKy_daynight_check() == 0) {
            *o_msgNoP = 0x9D2;
        } else {
            *o_msgNoP = 0x9D3;
        }
        break;
    default:
        msg_status = fopMsgStts_MSG_ENDS_e;
        break;
    }
    return msg_status;
}

/* .text getMsg_AJ1_0 */
u32 daNpc_Aj1_c::getMsg_AJ1_0() {
    return dComIfGs_isEventBit(dSv_event_flag_c::UNK_0510) ? 0x9C9 : 0x9C6;
}

/* .text getMsg_AJ1_1 */
u32 daNpc_Aj1_c::getMsg_AJ1_1() {
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0E20) && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_3702)) {
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_3702);
        return 0x9DB;
    }
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0504)) {
        return 0x9CF;
    }
    return dComIfGs_isEventBit(dSv_event_flag_c::UNK_2A80) ? 0x9DC : 0x9CB;
}

/* .text getMsg_AJ1_2 */
u32 daNpc_Aj1_c::getMsg_AJ1_2() {
    if (mItemNo == dItemNo_KNIGHTS_CREST_e) {
        if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_3701)) {
            return 0x9D7;
        }
        return dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B20) ? 0x9D8 : 0x9D9;
    }
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_3708)) {
        return 0x9D0;
    }
    if (!dComIfGs_isEventBit(dSv_event_flag_c::GRANDMA_HEALED)) {
        return 0x9D4;
    }
    return dKy_daynight_check() == 0 ? 0x9D5 : 0x9D6;
}

/* .text getMsg */
u32 daNpc_Aj1_c::getMsg() {
    u32 result = 0;
    switch (mType) {
    case 0:
        result = getMsg_AJ1_0();
        break;
    case 1:
        result = getMsg_AJ1_1();
        break;
    case 2:
        result = getMsg_AJ1_2();
        break;
    }
    return result;
}

/* .text eventOrder */
void daNpc_Aj1_c::eventOrder() {
    if (mOrder == 1 || mOrder == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (mType == 2) {
            eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
        }
        if (mOrder == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (mOrder >= 3) {
        mEventIndex = mOrder - 3;
        fopAcM_orderOtherEventId(this, mEventIDTbl[mEventIndex]);
    }
}

/* .text checkOrder */
void daNpc_Aj1_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (dComIfGp_evmng_startCheck(mEventIDTbl[mEventIndex])) {
            switch (mEventIndex) {
            case 0:
                fopAcM_OffStatus(this, fopAcStts_UNK4000_e);
                break;
            }
            mOrder = 0;
        }
    } else if (eventInfo.checkCommandTalk()) {
        if (mOrder == 1 || mOrder == 2) {
            mOrder = 0;
            mbTalkReq = true;
        }
    }
}

/* .text chk_talk */
bool daNpc_Aj1_c::chk_talk() {
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
bool daNpc_Aj1_c::chk_parts_notMov() {
    bool ret = false;
    if (mJointHeadY == m_jnt.getHead_y() && mJointBackboneY == m_jnt.getBackbone_y() && mActorAngleY == current.angle.y) {
        ret = true;
    }
    return ret;
}

/* .text lookBack */
void daNpc_Aj1_c::lookBack() {
    cXyz look_pos;
    cXyz current_pos;

    mJointHeadY = m_jnt.getHead_y();
    mJointBackboneY = m_jnt.getBackbone_y();
    mActorAngleY = current.angle.y;

    current_pos = current.pos;
    current_pos.y = eyePos.y;

    look_pos.set(0.0f, 0.0f, 0.0f);

    cXyz* look_pos_p = NULL;
    s16 target_y = current.angle.y;
    bool head_only = m76A;

    switch (mLookMode) {
    case 1:
        look_pos = dNpc_playerEyePos(-20.0f);
        look_pos_p = &look_pos;
        break;
    case 2:
        look_pos = mLookPos;
        look_pos_p = &look_pos;
        break;
    case 3:
        target_y = mTargetAngleY;
        break;
    }

    cLib_addCalcAngleS2(&mHeadTurnVel, l_HIO.mPrm.mMaxHeadTurnVel, 4, 0x800);
    if (!m_jnt.trnChk()) {
        mHeadTurnVel = 0;
    }

    m_jnt.lookAtTarget(&current.angle.y, look_pos_p, current_pos, target_y, mHeadTurnVel, head_only);
}

/* .text chkAttention */
bool daNpc_Aj1_c::chkAttention() {
    dAttention_c& attention = dComIfGp_getAttention();
    if (attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    } else {
        return this == attention.ActionTarget(0);
    }
}

/* .text setAttention */
void daNpc_Aj1_c::setAttention(bool i_setEyePos) {
    attention_info.position.set(current.pos.x, current.pos.y + l_HIO.mPrm.mAttPosOffsetY, current.pos.z);

    if (!mbSetEyePos && !i_setEyePos) {
        return;
    }

    eyePos.set(mTransformedEyePos.x, mTransformedEyePos.y, mTransformedEyePos.z);
}

/* .text decideType */
bool daNpc_Aj1_c::decideType(int i_type) {
    m7BE = 0;
    mType = -1;

    switch (i_type) {
    case 0:
        mType = 0;
        break;
    case 1:
        mType = 1;
        break;
    case 2:
        mType = 2;
        break;
    }

    return m7BE != -1 && mType != -1;
}

/* .text cut_init_AJ1_TLK */
void daNpc_Aj1_c::cut_init_AJ1_TLK() {
    mAnmAtr = 0xFF;
    mMesgAnimeTag = 0xFF;
    mMsgCount = 0;
}

/* .text cut_move_AJ1_TLK */
bool daNpc_Aj1_c::cut_move_AJ1_TLK() {
    if (talk(1) == fopMsgStts_BOX_CLOSED_e) {
        mAnmAtr = 0xFF;
        mMesgAnimeTag = 0xFF;
        mMsgCount = 0;
        return true;
    }
    return false;
}

/* .text cut_init_INI_ANGRY */
void daNpc_Aj1_c::cut_init_INI_ANGRY() {
    setAnm_NUM(0, 1);
    mpMorf->setMorf(8.0f);
}

/* .text cut_move_INI_ANGRY */
bool daNpc_Aj1_c::cut_move_INI_ANGRY() {
    return true;
}

/* .text cut_init_VIVRATE */
void daNpc_Aj1_c::cut_init_VIVRATE() {
}

/* .text cut_move_VIVRATE */
bool daNpc_Aj1_c::cut_move_VIVRATE() {
    if (mbMorfAnimStopped) {
        mDoAud_seStart(JA_SE_CM_JI_BODY_ATTACK, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        dComIfGp_getVibration().StartShock(5, -0x11, cXyz(0.0f, 1.0f, 0.0f));
        setAnm_NUM(3, 1);
        return true;
    }
    return false;
}

/* .text cut_init_JMP */
void daNpc_Aj1_c::cut_init_JMP() {
}

/* .text cut_move_JMP */
bool daNpc_Aj1_c::cut_move_JMP() {
    if (mbMorfAnimStopped) {
        dComIfGp_getDetect().set_quake(NULL);
        mCutTimer = 20;
        return true;
    }
    return false;
}

/* .text cut_init_SPPRISE */
void daNpc_Aj1_c::cut_init_SPPRISE() {
}

/* .text cut_move_SPPRISE */
bool daNpc_Aj1_c::cut_move_SPPRISE() {
    if (cLib_calcTimer(&mCutTimer) == 0) {
        setAnm_NUM(4, 1);
        mCutTimer = l_HIO.mPrm.mSurpriseTime;
        return true;
    }
    return false;
}

/* .text cut_init_LOK */
void daNpc_Aj1_c::cut_init_LOK() {
}

/* .text cut_move_LOK */
bool daNpc_Aj1_c::cut_move_LOK() {
    if (mbMorfAnimStopped && cLib_calcTimer(&mCutTimer) == 0) {
        setAnm_NUM(5, 1);
        mDoAud_seStart(JA_SE_CV_AJ_ANGRY, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        mCutTimer = l_HIO.mPrm.mLookTime;
        return true;
    }
    return false;
}

/* .text cut_init_DAN */
void daNpc_Aj1_c::cut_init_DAN() {
}

/* .text cut_move_DAN */
bool daNpc_Aj1_c::cut_move_DAN() {
    if (mbMorfAnimStopped && cLib_calcTimer(&mCutTimer) == 0) {
        setAnm_NUM(2, 1);
        return true;
    }
    return false;
}

/* .text cut_init_INVIT */
void daNpc_Aj1_c::cut_init_INVIT() {
    mDoAud_seStart(JA_SE_CV_AJ_INVITE, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
}

/* .text cut_move_INVIT */
bool daNpc_Aj1_c::cut_move_INVIT() {
    return true;
}

/* .text privateCut */
void daNpc_Aj1_c::privateCut(int i_staffIdx) {
    static char* a_cut_tbl[] = {
        "AJ1_TLK",
        "INI_ANGRY",
        "VIVRATE",
        "JMP",
        "SPPRISE",
        "LOK",
        "DAN",
        "INVITE",
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
            cut_init_AJ1_TLK();
            break;
        case 1:
            cut_init_INI_ANGRY();
            break;
        case 2:
            cut_init_VIVRATE();
            break;
        case 3:
            cut_init_JMP();
            break;
        case 4:
            cut_init_SPPRISE();
            break;
        case 5:
            cut_init_LOK();
            break;
        case 6:
            cut_init_DAN();
            break;
        case 7:
            cut_init_INVIT();
            break;
        }
    }

    bool cut_end;
    switch (mActionIndex) {
    case 0:
        cut_end = cut_move_AJ1_TLK();
        break;
    case 1:
        cut_end = cut_move_INI_ANGRY();
        break;
    case 2:
        cut_end = cut_move_VIVRATE();
        break;
    case 3:
        cut_end = cut_move_JMP();
        break;
    case 4:
        cut_end = cut_move_SPPRISE();
        break;
    case 5:
        cut_end = cut_move_LOK();
        break;
    case 6:
        cut_end = cut_move_DAN();
        break;
    case 7:
        cut_end = cut_move_INVIT();
        break;
    default:
        cut_end = true;
        break;
    }

    if (cut_end) {
        dComIfGp_evmng_cutEnd(i_staffIdx);
    }
}

/* .text endEvent */
void daNpc_Aj1_c::endEvent() {
    dComIfGp_event_reset();
    mAnmAtr = 0xFF;
    mMesgAnimeTag = 0xFF;
}

/* .text isEventEntry */
int daNpc_Aj1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName());
}

/* .text event_proc */
void daNpc_Aj1_c::event_proc(int i_staffIdx) {
    if (dComIfGp_evmng_endCheck(mEventIDTbl[mEventIndex])) {
        switch (mEventIndex) {
        case 0:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_0508);
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_0504);
            break;
        }
        endEvent();
    } else {
        if (!mEventCut.cutProc()) {
            privateCut(i_staffIdx);
        }
        lookBack();
    }
}

/* .text set_pa_pun */
void daNpc_Aj1_c::set_pa_pun() {
    mpPunEmitter = dComIfGp_particle_set(dPa_name::ID_IT_SN_AOJI_PUNPUN00, &current.pos, NULL, NULL, 0xFF, NULL, fopAcM_GetRoomNo(this));
    if (mpPunEmitter != NULL) {
        mPunTimer = 0;
    }
}

/* .text set_pa_aka */
void daNpc_Aj1_c::set_pa_aka() {
    if (mpAkaEmitter != NULL) {
        mpAkaEmitter->becomeInvalidEmitter();
    }
    mpAkaEmitter = dComIfGp_particle_set(dPa_name::ID_IT_SN_AOJI_AKAAKA00, &current.pos, NULL, NULL, 0xFF, NULL, fopAcM_GetRoomNo(this));
}

/* .text set_pa_don */
void daNpc_Aj1_c::set_pa_don() {
    cXyz offset(37.3f, 0.0f, 13.8f);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mDoMtx_stack_c::multVec(&offset, &mDonPos);
    mpDonEmitter = dComIfGp_particle_set(dPa_name::ID_IT_SN_AOJI_DONDON00, &mDonPos, NULL, NULL, 0xFF, NULL, fopAcM_GetRoomNo(this));
}

/* .text set_pa_smk */
void daNpc_Aj1_c::set_pa_smk() {
    GXColor color = {0xA0, 0xA0, 0x80, 0xC8};

    mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(m_fot_L_jnt_num));
    mSmokePos.x = mDoMtx_stack_c::get()[0][3];
    mSmokePos.y = mDoMtx_stack_c::get()[1][3];
    mSmokePos.z = mDoMtx_stack_c::get()[2][3];

    mSmokeCb.remove();
    mpSmkEmitter = dComIfGp_particle_setToon(dPa_name::ID_AK_JT_ELEMENTSMOKE01, &mSmokePos, &current.angle, NULL, 0xC8, &mSmokeCb, fopAcM_GetRoomNo(this));
    if (mpSmkEmitter != NULL) {
        mpSmkEmitter->setGlobalParticleScale(JGeometry::TVec3<f32>(0.3f, 0.3f, 1.0f));
        mpSmkEmitter->setGlobalDynamicsScale(JGeometry::TVec3<f32>(0.1f, 0.1f, 0.1f));
        mpSmkEmitter->setLifeTime(40);
        mpSmkEmitter->setRate(3.0f);
        mpSmkEmitter->setMaxFrame(1);
        mpSmkEmitter->setDirectionalSpeed(120.0f);
        mpSmkEmitter->setEmitterScale(JGeometry::TVec3<f32>(1.0f, 0.1f, 1.0f));
        mSmokeCb.setColor(color);
    }
}

/* .text flw_pa_pun */
void daNpc_Aj1_c::flw_pa_pun() {
    if (mpPunEmitter != NULL) {
        mpPunEmitter->setGlobalRTMatrix(mpMorf->getModel()->getAnmMtx(m_hed_jnt_num));
        if (cLib_calcTimer(&mPunTimer) == 0) {
            mDoAud_seStart(JA_SE_CM_AJ_ANGRY_STEAM, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
            mPunTimer = 5;
        }
    }
}

/* .text flw_pa_aka */
void daNpc_Aj1_c::flw_pa_aka() {
    if (mpAkaEmitter != NULL) {
        mpAkaEmitter->setGlobalRTMatrix(mpMorf->getModel()->getAnmMtx(m_hed_jnt_num));
    }
}

/* .text del_pa_aka */
void daNpc_Aj1_c::del_pa_aka() {
    if (!mbDelAka) {
        return;
    }
    if (mpAkaEmitter != NULL) {
        if (mpAkaEmitter->getParticleNumber() == 0) {
            mpAkaEmitter->becomeInvalidEmitter();
            mbDelAka = false;
            mpAkaEmitter = NULL;
        }
    } else {
        mbDelAka = false;
    }
}

/* .text del_pa */
void daNpc_Aj1_c::del_pa(JPABaseEmitter** i_emitterP) {
    if (*i_emitterP != NULL) {
        (*i_emitterP)->becomeInvalidEmitter();
        *i_emitterP = NULL;
    }
}

/* .text setSmoke */
void daNpc_Aj1_c::setSmoke() {
    if (mBckNum == BCKNUM_ANGRY_e) {
        if (mpMorf->checkFrame(0.0f) || mpMorf->checkFrame(9.0f)) {
            set_pa_smk();
        }
        if (mpMorf->checkFrame(0.0f) || mpMorf->checkFrame(10.0f)) {
            mDoAud_seStart(JA_SE_CM_AJ_STICK, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        }
    }
}

/* .text set_action */
BOOL daNpc_Aj1_c::set_action(ProcFunc i_newProcFunc, void* i_argsP) {
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

/* .text setStt */
void daNpc_Aj1_c::setStt(s8 i_stt) {
    u8 prev_stt = mStt;
    mStt = i_stt;
    switch (mStt) {
    case 0:
        break;
    case 1:
        mOrder = 0;
        mFarTimer = cLib_getRndValue(90, 120);
        break;
    case 2:
        mOrder = 0;
        break;
    case 3:
        mOrder = 0;
        mAnmAtr = 0xFF;
        mMesgAnimeTag = 0xFF;
        mMsgCount = 0;
        mPrevStt = prev_stt;
        break;
    case 4:
        mOrder = 0;
        mWaitTimer = cLib_getRndValue(90, 180);
        if (mBckNum == BCKNUM_WAIT02_e || mBckNum == BCKNUM_TIRE_e) {
            return;
        }
        break;
    }
    setAnm();
}

/* .text chk_areaIN */
bool daNpc_Aj1_c::chk_areaIN(f32 i_dist, s16 i_angle, cXyz i_pos) {
    f32 abs_xz = (dComIfGp_getPlayer(0)->current.pos - i_pos).absXZ();
    f32 dy = dComIfGp_getPlayer(0)->current.pos.y - i_pos.y;
    s16 angle = (s16)cLib_targetAngleY(&current.pos, &dComIfGp_getPlayer(0)->current.pos) - mHomeAngle.y;

    if (abs_xz < i_dist && std::fabsf(dy) < 500.0f && abs(angle) < i_angle) {
        return true;
    } else {
        return false;
    }
}

/* .text FARwai */
BOOL daNpc_Aj1_c::FARwai() {
    if (chk_areaIN(l_HIO.mPrm.mCallDist, l_HIO.mPrm.mCallAngle, current.pos)) {
        setStt(2);
        mLookMode = 1;
        m76A = false;
        m_jnt.setTrn();
        return TRUE;
    }

    if (mBckNum == BCKNUM_NOBI_e) {
        if (mbMorfAnimStopped) {
            setAnm_NUM(0, 1);
            mpMorf->setMorf(8.0f);
        }
        return TRUE;
    }

    if (cLib_calcTimer(&mFarTimer) == 0) {
        setAnm_NUM(8, 1);
        mFarTimer = cLib_getRndValue(90, 120);
    }
    return TRUE;
}

/* .text call_1 */
BOOL daNpc_Aj1_c::call_1() {
    if (mbTalkReq) {
        if (chk_talk()) {
            setStt(3);
            mLookMode = 1;
            m76A = false;
            m_jnt.setTrn();
        }
        return TRUE;
    }

    if (chk_areaIN(l_HIO.mPrm.mCallDist, l_HIO.mPrm.mCallAngle, current.pos) == false) {
        setStt(1);
        mpMorf->setMorf(15.0f);
        mLookMode = 3;
        mTargetAngleY = mHomeAngle.y;
        m76A = false;
        m_jnt.setTrn();
        return TRUE;
    }

    m_jnt.setTrn();
    if (chk_areaIN(l_HIO.mPrm.mTalkDist, l_HIO.mPrm.mTalkAngle, current.pos)) {
        mOrder = 2;
        if (mbAttention) {
            if (mBckNum != BCKNUM_WAIT01_e) {
                setAnm_NUM(0, 1);
                mpMorf->setMorf(15.0f);
            }
            return TRUE;
        }
        if (mBckNum != BCKNUM_CALL_e) {
            setAnm_NUM(7, 1);
        }
    }
    return TRUE;
}

/* .text wait_1 */
BOOL daNpc_Aj1_c::wait_1() {
    cLib_addCalcAngleS(&current.angle.y, mHomeAngle.y, 4, 0x400, 0);
    ctrl_WAITanm();
    if (mOrder == 1 || mOrder >= 3) {
        return TRUE;
    }

    ctrl_TIREanm();
    if (mbTalkReq) {
        if (chk_talk()) {
            setStt(3);
            mLookMode = 1;
            m76A = false;
            m_jnt.setTrn();
        }
        return TRUE;
    }

    mOrder = 2;
    if (mBckNum != BCKNUM_WAIT02_e && mbAttention) {
        mLookMode = 1;
        return TRUE;
    }
    mLookMode = 3;
    mTargetAngleY = mHomeAngle.y;
    return TRUE;
}

/* .text talk_1 */
BOOL daNpc_Aj1_c::talk_1() {
    BOOL res = chk_parts_notMov();
    fopNpc_npc_c::talk(1);
    if (mpCurrMsg == NULL) {
        return res;
    }
    switch (mpCurrMsg->mStatus) {
    case fopMsgStts_BOX_OPENING_e:
    case fopMsgStts_MSG_TYPING_e:
        break;
    case fopMsgStts_MSG_DESTROYED_e:
        switch (mCurrMsgNo) {
        case 0x9DA:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_3704);
            // fallthrough
        case 0x9C8:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_0510);
            break;
        case 0x9DD:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_3704);
            break;
        case 0x9D1:
        case 0x9D2:
        case 0x9D3:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_3708);
            break;
        case 0x9D7:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_3701);
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

/* .text wait_action1 */
BOOL daNpc_Aj1_c::wait_action1(void*) {
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
            mbSetEyePos = FARwai();
            break;
        case 2:
            mbSetEyePos = call_1();
            break;
        case 3:
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

/* .text wait_action2 */
BOOL daNpc_Aj1_c::wait_action2(void*) {
    switch (mActionState) {
    case 0:
        setStt(4);
        if (strcmp(dComIfGp_getStartStageName(), "Ojhous2") == 0 && mType == 1 && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_0508)) {
            mOrder = 3;
        }
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
            mbSetEyePos = wait_1();
            break;
        case 3:
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

/* .text demo */
bool daNpc_Aj1_c::demo() {
    if (demoActorID == 0) {
        if (mbDemo) {
            mbDemo = false;
        }
    } else {
        if (!mbDemo) {
            mbDemo = true;
            m75F = false;
            m_jnt.setHead_y(0);
            m_jnt.setHead_x(0);
            m_jnt.setBackBone_y(0);
            m_jnt.setBackBone_x(0);
        }

        dDemo_actor_c* demo_actor_p = dComIfGp_demo_getActor(demoActorID);
        if (mBtpAnm.getBtpAnm() != NULL) {
            mBtpFrame++;
            if (mBtpFrame >= mBtpAnm.getBtpAnm()->getFrameMax()) {
                mBtpFrame = mBtpAnm.getBtpAnm()->getFrameMax();
            }
        }

        J3DAnmTexPattern* demo_btp_p = demo_actor_p->getP_BtpData("Aj");
        if (demo_btp_p) {
            mBtpAnm.init(mpMorf->getModel()->getModelData(), demo_btp_p, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, 0);
            mBtpNum = BTPNUM_NULL_e;
            mBtpFrame = 0;
        }

        dDemo_setDemoData(this, 106, mpMorf, "Aj", 0, NULL, 0, 0);
    }

    return mbDemo;
}

/* .text shadowDraw */
void daNpc_Aj1_c::shadowDraw() {
    cXyz pos(current.pos.x, current.pos.y + 150.0f, current.pos.z);

    mShadowID = dComIfGd_setShadow(mShadowID, 1, mpMorf->getModel(), &pos, 800.0f, 40.0f, current.pos.y, mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr);

    if (mShadowID != 0) {
        if (mpStickModel) {
            dComIfGd_addRealShadow(mShadowID, mpStickModel);
        }
    }
}

static void dummy() {
    const GXColor dummy1 = {0xFF, 0x00, 0x00, 0x80};
    const GXColor dummy2 = {0x00, 0x00, 0xFF, 0x80};
    const GXColor dummy3 = {0xFF, 0xFF, 0x00, 0x80};
}

/* .text _draw */
BOOL daNpc_Aj1_c::_draw() {
    J3DModel* morf_model_p = mpMorf->getModel();
    J3DModelData* morf_model_info_p = morf_model_p->getModelData();

    if (m75E || m760 != 0) {
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(morf_model_p, &tevStr);

    mBtpAnm.entry(morf_model_info_p, mBtpFrame);
    mpMorf->entryDL();
    mBtpAnm.remove(morf_model_info_p);

    if (mpStickModel) {
        g_env_light.setLightTevColorType(mpStickModel, &tevStr);
        mDoExt_modelEntryDL(mpStickModel);
    }

    shadowDraw();

    // Does nothing
    if (l_HIO.mPrm.m18) {
        cXyz dummy = current.pos;
        dummy.y = eyePos.y;
    }

    dSnap_RegistFig(DSNAP_TYPE_UNK4C, this, 1.0f, 1.0f, 1.0f);

    return TRUE;
}

/* .text _execute */
BOOL daNpc_Aj1_c::_execute() {
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

    if (m75E && demoActorID == 0) {
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

        fopAcM_posMoveF(this, mStts.GetCCMoveP());
        play_animation();
        mObjAcch.CrrPos(*dComIfG_Bgsp());
    }

    eventOrder();
    mAngle = current.angle;
    if (!m75F) {
        shape_angle = current.angle;
    }

    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    setMtx(false);

    flw_pa_pun();
    del_pa_aka();
    flw_pa_aka();
    setSmoke();

    if (!mbDemo) {
        setCollision(60.0f, 140.0f);
    }

    return TRUE;
}

/* .text _delete */
BOOL daNpc_Aj1_c::_delete() {
    dComIfG_resDelete(&mPhs, "Aj");
    if (heap && mpMorf) {
        mpMorf->stopZelAnime();
    }
    del_pa(&mpPunEmitter);
    del_pa(&mpAkaEmitter);
    del_pa(&mpDonEmitter);
    mSmokeCb.remove();
    return TRUE;
}

/* .text _create */
cPhs_State daNpc_Aj1_c::_create() {
    static int a_siz_tbl[] = {
        0,
    };

    fopAcM_ct(this, daNpc_Aj1_c);

    cPhs_State state = dComIfG_resLoad(&mPhs, "Aj");
    if (state != cPhs_COMPLEATE_e) {
        return state;
    }

    if (!decideType(fopAcM_GetParam(this) & 0xFF)) {
        return cPhs_ERROR_e;
    }

    if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_siz_tbl[m7BE])) {
        return cPhs_ERROR_e;
    }

    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -60.0f, -20.0f, -60.0f, 80.0f, 260.0f, 100.0f);

    if (!createInit()) {
        return cPhs_ERROR_e;
    }

    return state;
}

/* .text bodyCreateHeap */
BOOL daNpc_Aj1_c::bodyCreateHeap() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Aj", dRes_ID_AJ_BDL_AJ_e);
    JUT_ASSERT(0x8BE, a_mdl_dat != NULL);

    mpMorf = new mDoExt_McaMorf(a_mdl_dat, NULL, NULL, NULL, J3DFrameCtrl::EMode_NULL, 1.0f, 0, -1, 1, NULL, 0x80000, 0x11020022);

    if (!mpMorf) {
        return FALSE;
    } else if (!mpMorf->getModel()) {
        mpMorf = NULL;
        return FALSE;
    }

    if (!init_texPttrnAnm(BTPNUM_MABA_e, false)) {
        mpMorf = NULL;
        return FALSE;
    }

    m_hed_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
    JUT_ASSERT(0x8D3, m_hed_jnt_num >= 0);

    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(0x8D5, m_bbone_jnt_num >= 0);

    m_hnd_L_jnt_num = a_mdl_dat->getJointName()->getIndex("handL");
    JUT_ASSERT(0x8D7, m_hnd_L_jnt_num >= 0);

    m_fot_L_jnt_num = a_mdl_dat->getJointName()->getIndex("footL");
    JUT_ASSERT(0x8D9, m_fot_L_jnt_num >= 0);

    mpMorf->getModel()->getModelData()->getJointNodePointer(m_hed_jnt_num)->setCallBack(nodeCB_Head);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_bbone_jnt_num)->setCallBack(nodeCB_BackBone);
    mpMorf->getModel()->setUserArea((uintptr_t)this);

    return TRUE;
}

/* .text itemCreateHeap */
BOOL daNpc_Aj1_c::itemCreateHeap() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Aj", dRes_ID_AJ_BDL_AJ_STICK_e);
    JUT_ASSERT(0x8F3, a_mdl_dat != NULL);

    mpStickModel = mDoExt_J3DModel__create(a_mdl_dat, 0x80000, 0x11000022);

    if (!mpStickModel) {
        return FALSE;
    }

    return TRUE;
}

/* .text CreateHeap */
BOOL daNpc_Aj1_c::CreateHeap() {
    if (!bodyCreateHeap()) {
        return FALSE;
    }

    if (!itemCreateHeap()) {
        mpMorf = NULL;
        return FALSE;
    }

    mAcchCir.SetWall(30.0f, 60.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this), NULL, NULL);

    return TRUE;
}

/* 000046D8-000046F8       .text daNpc_Aj1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Aj1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Aj1_c*)i_this)->_create();
}

/* 000046F8-00004718       .text daNpc_Aj1_Delete__FP11daNpc_Aj1_c */
static BOOL daNpc_Aj1_Delete(daNpc_Aj1_c* i_this) {
    return ((daNpc_Aj1_c*)i_this)->_delete();
}

/* 00004718-00004738       .text daNpc_Aj1_Execute__FP11daNpc_Aj1_c */
static BOOL daNpc_Aj1_Execute(daNpc_Aj1_c* i_this) {
    return ((daNpc_Aj1_c*)i_this)->_execute();
}

/* 00004738-00004758       .text daNpc_Aj1_Draw__FP11daNpc_Aj1_c */
static BOOL daNpc_Aj1_Draw(daNpc_Aj1_c* i_this) {
    return ((daNpc_Aj1_c*)i_this)->_draw();
}

/* 00004758-00004760       .text daNpc_Aj1_IsDelete__FP11daNpc_Aj1_c */
static BOOL daNpc_Aj1_IsDelete(daNpc_Aj1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Aj1_Method = {
    (process_method_func)daNpc_Aj1_Create,
    (process_method_func)daNpc_Aj1_Delete,
    (process_method_func)daNpc_Aj1_Execute,
    (process_method_func)daNpc_Aj1_IsDelete,
    (process_method_func)daNpc_Aj1_Draw,
};

actor_process_profile_definition g_profile_NPC_AJ1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_AJ1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Aj1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_AJ1_e,
    /* Actor SubMtd */ &l_daNpc_Aj1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
