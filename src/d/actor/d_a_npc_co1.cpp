#pragma weak_inline off
#include "d/dolzel_rel.h"
#pragma weak_inline on
#include "d/actor/d_a_npc_co1.h"
#include "d/d_snap.h"
#include "d/d_item_data.h"
#include "d/res/res_co.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_kankyo.h"
#include "d/d_drawlist.h"
#include <math.h>

#define mpBtpRes m_hed_tex_pttrn
#define mpBtkRes m_prl_btk

// Event sentinels
#define EVT_NO_EVENT 0xFF
#define EVT_NO_TARGET 0xFFFF

// Attention system
#define ATTN_FLAGS 10
#define ATTN_DIST_SPOKEN 0x46
#define ATTN_DIST_ACTION 0x45

// BAM angles
#define BAM_45DEG 0x800
#define BAM_90DEG 0x2000

// Param mask for character type
#define CHAR_TYPE_MASK 0xFF

// Event bits
#define EVTBIT_PRL_FLW_DONE 0xF04
#define EVTBIT_GREETED 0xF08
#define EVTBIT_CONTACT_DONE 0x1810

// Message IDs
#define MSG_CO_GREETING 0x1839
#define MSG_CO_ALREADY_MET 0x183A
#define MSG_CO_GOT_ITEM 0x183B
#define MSG_CO_GOT_LETTER 0x183C
#define MSG_CO_HAS_LETTER 0x183E
#define MSG_CO_GIVE_LETTER 0x183F
#define MSG_CO_GAVE_LETTER 0x1840
#define MSG_CO_LETTER_PASSED 0x1841
#define MSG_CO_LETTER_PASSED_1 0x1842
#define MSG_CO_LETTER_PASSED_2 0x1843
#define MSG_CO_LETTER_PASSED_3 0x1844
#define MSG_CO_LETTER_PASSED_4 0x1845
#define MSG_CO_LETTER_PASSED_5 0x1846
#define MSG_CO_LETTER_PASSED_6 0x1847
#define MSG_CO_LETTER_DONE 0x1848
#define MSG_CO_DELIVERED_START 0x1849
#define MSG_CO_DELIVERED_END 0x184A
#define MSG_CO_ENDING 0x184B

static daNpc_Co1_HIO_c l_HIO;

static u32 a_prm_tbl[11] = {
    0x20002328, 0xE000DCD8, 0x00000000, 0x00000000,
    0x04000400, 0x42B60000, 0x000000FF, 0x00960000,
    0x42200000, 0x41A00000, 0x02000040,
};

static daNpc_Co1_c::anm_prm_c a_anm_tbl1[12] = {
    { 0, 0, 0, 0, 8.0f, 1.0f, 2 }, { 1, 4, 0, 0, 8.0f, 1.0f, 2 },
    { 2, 6, 0, 0, 8.0f, 1.0f, 0 }, { 3, 5, 0, 0, 8.0f, 1.0f, 0 },
    { 4, 4, 0, 0, 8.0f, 1.0f, 2 }, { 5, 0, 0, 0, 8.0f, 1.0f, 2 },
    { 6, 3, 0, 0, 8.0f, 1.0f, 2 }, { 7, 4, 0, 0, 8.0f, 1.0f, 2 },
    { 8, 0, 0, 0, 8.0f, 1.0f, 0 }, { 9, 5, 0, 0, 8.0f, 1.0f, 0 },
    { 10, 6, 0, 0, 8.0f, 1.0f, 0 }, { 7, 0, 0, 0, 8.0f, 1.0f, 2 },
};

static daNpc_Co1_c::anm_prm_c a_anm_tbl2[8] = {
    { -1, 0, 0, 0, 0.0f, 0.0f, -1 }, { 1, 4, 0, 0, 8.0f, 1.0f, 2 },
    { -1, 0, 0, 0, 0.0f, 0.0f, -1 }, { 3, 5, 0, 0, 8.0f, 1.0f, 0 },
    { 7, 0, 0, 0, 8.0f, 1.0f, 2 }, { -1, 0, 0, 0, 0.0f, 0.0f, -1 },
    { 4, 4, 0, 0, 8.0f, 1.0f, 2 }, { 10, 6, 0, 0, 8.0f, 1.0f, 0 },
};

static daNpc_Co1_c::anm_prm_c a_anm_tbl3[14] = {
    { 0, 0, 0, 0, 8.0f, 1.0f, 2 }, { 1, 4, 0, 0, 8.0f, 1.0f, 2 },
    { 3, 5, 0, 0, 8.0f, 1.0f, 0 }, { 8, 0, 0, 0, 8.0f, 1.0f, 0 },
    { 5, 0, 0, 0, 8.0f, 1.0f, 2 }, { 6, 3, 0, 0, 8.0f, 1.0f, 2 },
    { 7, 4, 0, 0, 8.0f, 1.0f, 2 }, { 2, 6, 0, 0, 8.0f, 1.0f, 0 },
    { 10, 6, 0, 0, 8.0f, 1.0f, 0 }, { 9, 5, 0, 0, 8.0f, 1.0f, 0 },
    { 4, 4, 0, 0, 8.0f, 1.0f, 2 }, { 5, 4, 0, 0, 8.0f, 1.0f, 2 },
    { 5, 0, 0, 0, 8.0f, 1.0f, 2 }, { 6, 3, 0, 0, 8.0f, 1.0f, 2 },
};

static const char* l_evn_tbl[3] = {
    "Prl_Flw", "Contact", "Red_Ltr",
};

daNpc_Co1_HIO_c::daNpc_Co1_HIO_c() {
    memcpy(&mNpc, a_prm_tbl, sizeof(mNpc));
    mNo = -1;
    mNo2 = -1;
}

static BOOL nodeCallBack_Co1(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daNpc_Co1_c* co1Actor = (daNpc_Co1_c*)(model->getUserArea());
        if (co1Actor) {
            co1Actor->nodeCo1Control(i_node, model);
        }
    }
    return TRUE;
}

void daNpc_Co1_c::nodeCo1Control(J3DNode* i_node, J3DModel* i_model) {
    static cXyz a_att_pos_offst(14.0f, 18.0f, 0.0f);
    int jointIdx = ((J3DJoint*)i_node)->getJntNo();

    mDoMtx_stack_c::copy(i_model->getAnmMtx(jointIdx));

    if (jointIdx == m_hed_jnt_num) {
        mDoMtx_stack_c::XrotM(m_jnt.getHead_y());
        mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
        PSMTXMultVec(mDoMtx_stack_c::get(), &a_att_pos_offst, &mHeadPos);
    }

    if (jointIdx == m_bbone_jnt_num) {
        mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
        mDoMtx_stack_c::ZrotM(-m_jnt.getBackbone_x());
    }

    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    i_model->setAnmMtx(jointIdx, mDoMtx_stack_c::get());
}

BOOL daNpc_Co1_c::init_CO1_0() {
    u32 isSym = dComIfGs_isSymbol(1);
    u32 result = isSym ? 0 : 1;
    if ((u8)result) {
        actor_status &= ~fopAcStts_NOCULLEXEC_e;
        actor_status |= fopAcStts_UNK4000_e;
        set_action(&daNpc_Co1_c::wait_action1, NULL);
    }
    return (BOOL)(result);
}

BOOL daNpc_Co1_c::createInit() {
    for (int i = 0; i < 3; i++) {
        mEventIdx[i] = dComIfGp_evmng_getEventIdx(l_evn_tbl[i], EVT_NO_EVENT);
    }

    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = ATTN_DIST_SPOKEN;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = ATTN_DIST_ACTION;
    gravity = -4.5f;
    mEventPos = current.pos;

    mInitDone = TRUE;
    mDemoEventCut.setActorInfo2("Co1", this);

    mCurrAnmNum = 11;

    int initResult;
    switch (mInitStep) {
    case 0:
        initResult = init_CO1_0();
        break;
    default:
        initResult = 0;
        break;
    }

    if ((u8)initResult) {
        shape_angle = current.angle;
    } else {
        return 0;
    }
        
    mStts.Init(0xFF, 0xFF, this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);

    mpMorf->setMorf(0.0f);
    setMtx(TRUE);
    return 1;
}

void daNpc_Co1_c::setMtx(bool i_init) {
    if (!mDemo) {
        plyTexPttrnAnm();
        mMorfEnd = mpMorf->play(&eyePos, 0, 0);

        mpPrlMorf->setFrame(mpMorf->getFrame());

        if (mpMorf->getFrame() < mPrevMorfFrame) {
            mMorfEnd = TRUE;
        }
        mPrevMorfFrame = mpMorf->getFrame();

        mObjAcch.CrrPos(*dComIfG_Bgsp());

        switch (mCurrAnmNum) {
        case 8:
            mDrawHandR = (mpMorf->getFrame() >= 15.0f);
            break;
        case 4:
            mDrawHandR = TRUE;
            break;
        default:
            mDrawHandR = FALSE;
            break;
        }
    }

    dBgS* bgsp = dComIfG_Bgsp();
    tevStr.mRoomNo = bgsp->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = bgsp->GetPolyColor(mObjAcch.m_gnd);

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();

    PSMTXCopy(mpMorf->getModel()->getAnmMtx(m_bbone_jnt_num), mDoMtx_stack_c::get());
    mpPrlMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpPrlMorf->calc();

    if (mDrawHandR) {
        PSMTXCopy(mpMorf->getModel()->getAnmMtx(m_hnd_R_jnt_num), mDoMtx_stack_c::get());
        mpItmModel->setBaseTRMtx(mDoMtx_stack_c::get());
        mpItmModel->calc();
    }

    cMtx_copy(mpPrlMorf->getModel()->getAnmMtx(m_prl_jnt_num), mDoMtx_stack_c::get());
    mCurPos.x = mDoMtx_stack_c::get()[0][3];
    mCurPos.y = mDoMtx_stack_c::get()[1][3];
    mCurPos.z = mDoMtx_stack_c::get()[2][3];

    mPrevPos = mCurPos;

    mPrevPos2[0] = l_HIO.mNpc.mPrevPosOfsX;
    mPrevPos2[1] = l_HIO.mNpc.mPrevPosOfsY;
    mPrevPos2[2] = l_HIO.mNpc.mPrevPosOfsZ;

    mSinAngle += l_HIO.mNpc.mOscAngVel;

    mOscillation = fabs(cM_ssin(mSinAngle));

    f32 diff = l_HIO.mNpc.mOscMaxOfs - l_HIO.mNpc.mOscMinOfs;
    f32 clamped1 = cLib_minLimit<f32>(diff, 0.0f);

    mFloatVal = cLib_minLimit<f32>(clamped1 * mOscillation + l_HIO.mNpc.mOscMinOfs, 0.001f);

    setAttention(i_init);
}

static const int a_bck_resID_tbl[11] = {
    0x10, 0x11, 0x09, 0x0A, 0x0B, 0x0D, 0x0E, 0x0C, 0x0F, 0x0A, 0x09,
};

static const int a_bck_resID_prl_tbl[11] = {
    0x07, 0x08, 0x00, 0x01, 0x02, 0x04, 0x05, 0x03, 0x06, 0x01, 0x00,
};

static const int a_btp_resID_tbl[7] = {
    0x16, 0x17, 0x1A, 0x1C, 0x19, 0x1B, 0x18,
};

s32 daNpc_Co1_c::anmNum_toResID(int i_idx) {
    return a_bck_resID_tbl[i_idx];
}

s32 daNpc_Co1_c::anmNum_toResID_prl(int i_idx) {
    return a_bck_resID_prl_tbl[i_idx];
}

s32 daNpc_Co1_c::btpNum_toResID(int i_idx) {
    return a_btp_resID_tbl[i_idx];
}

BOOL daNpc_Co1_c::setBtp(bool i_inherit, int i_texNum) {
    J3DModelData* modelData = mpMorf->getModel()->getModelData();
    int btpNum = btpNum_toResID(i_texNum);
    J3DAnmTexPattern* btpRes = (J3DAnmTexPattern*)dComIfG_getObjectIDRes("Co", btpNum);
    mpBtpRes = btpRes;
    JUT_ASSERT(0x1CE, m_hed_tex_pttrn != 0);

    int initRes = mBtpAnm.init(modelData, mpBtpRes, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, i_inherit, FALSE);
    int notRes = 1 - initRes;
    u32 result = notRes ? 0 : 1;
    if ((u8)result) {
        mBtpFrame = 0;
        mBtpTimer = 0;
    }
    return (BOOL)(result);
}

BOOL daNpc_Co1_c::setBtk(bool i_inherit) {
    J3DModelData* modelData = mpPrlMorf->getModel()->getModelData();
    J3DAnmTextureSRTKey* btkRes = (J3DAnmTextureSRTKey*)dComIfG_getObjectIDRes("Co", CO_BTK_CO_PEAL);
    mpBtkRes = btkRes;
    JUT_ASSERT(0x1EA, m_prl_btk != 0);

    int initRes = mBtkAnm.init(modelData, mpBtkRes, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, i_inherit);
    int notRes = 1 - initRes;
    u32 result = notRes ? 0 : 1;
    if ((u8)result) {
        mBtkFrame = 0;
    }
    return (BOOL)(result);
}

BOOL daNpc_Co1_c::iniTexPttrnAnm(bool i_inherit) {
    return setBtp(i_inherit, mTexPatternNum);
}

void daNpc_Co1_c::plyTexPttrnAnm() {
    mBtkFrame++;
    if (mBtkFrame >= mpBtkRes->getFrameMax()) {
        mBtkFrame = 0;
    }

    if (mTexPatternNum == 6 || mTexPatternNum == 5 || cLib_calcTimer(&mBtpTimer) == 0) {
        mBtpFrame++;
        if (mBtpFrame >= mpBtpRes->getFrameMax()) {
            if (mTexPatternNum == 6 || mTexPatternNum == 5) {
                mBtpFrame = mpBtpRes->getFrameMax();
            } else {
                mBtpTimer = cM_rndF(60.0f) + 30.0f;
                mBtpFrame = 0;
            }
        }
    }
}

void daNpc_Co1_c::setAnm_tex(signed char i_idx) {
    if (mTexPatternNum != i_idx) {
        mTexPatternNum = i_idx;
        iniTexPttrnAnm(TRUE);
    }
}

BOOL daNpc_Co1_c::setAnm_anm(anm_prm_c* i_anm) {
    if (mCurrAnmNum == i_anm->mBckResIndex) {
        return TRUE;
    }

    mCurrAnmNum = i_anm->mBckResIndex;
    int bckRes = anmNum_toResID(mCurrAnmNum);
    dNpc_setAnmIDRes(mpMorf, i_anm->mLoopMode, i_anm->mMorf, i_anm->mSpeed, bckRes, -1, "Co");

    int prlBckRes = anmNum_toResID_prl(mCurrAnmNum);
    dNpc_setAnmIDRes(mpPrlMorf, i_anm->mLoopMode, 0.0f, 0.0f, prlBckRes, -1, "Co");

    mPrevMorfFrame = 0.0f;
    mAnmLoaded = FALSE;
    mMorfEnd = FALSE;
    return TRUE;
}

void daNpc_Co1_c::setAnm_NUM(int i_idx, int i_texFlag) {
    if (i_texFlag != 0) {
        setAnm_tex(a_anm_tbl1[i_idx].mResIndex);
    }
    setAnm_anm(&a_anm_tbl1[i_idx]);
}

BOOL daNpc_Co1_c::setAnm() {
    if (a_anm_tbl2[mAnmTagIndex].mResIndex >= 0) {
        setAnm_tex(a_anm_tbl2[mAnmTagIndex].mResIndex);
    }
    if (a_anm_tbl2[mAnmTagIndex].mBckResIndex >= 0) {
        setAnm_anm(&a_anm_tbl2[mAnmTagIndex]);
    }
    return TRUE;
}

void daNpc_Co1_c::chg_anmTag() {
}

void daNpc_Co1_c::control_anmTag() {
}

void daNpc_Co1_c::chg_anmAtr(unsigned char i_atr) {
    if (i_atr >= ARRAY_SIZE(a_anm_tbl3) || i_atr == mCurrAnmAtr) {
        return;
    }
    mActionIndex = 1;
    switch (i_atr) {
    case 3:
    case 4:
    case 5:
    case 7:
    case 11:
        mActionIndex = 0;
        break;
    case 13:
        set_target(1);
        break;
    }
    mCurrAnmAtr = i_atr;
    setAnm_ATR(TRUE);
}

void daNpc_Co1_c::control_anmAtr() {
    switch (mCurrAnmAtr) {
    case 0:
    case 1:
    case 4:
    case 5:
    case 6:
    case 10:
    case 11:
    case 12:
    case 13:
        break;
    case 2:
        if (mMorfEnd) {
            setAnm_NUM(7, TRUE);
            mCurrAnmAtr = 6;
        }
        break;
    case 3:
        if (mMorfEnd) {
            setAnm_NUM(4, TRUE);
            mCurrAnmAtr = 10;
        }
        break;
    case 7:
        if (mMorfEnd) {
            setAnm_NUM(6, TRUE);
            mCurrAnmAtr = 5;
        }
        break;
    case 8:
        if (mMorfEnd) {
            setAnm_NUM(7, TRUE);
            mCurrAnmAtr = 6;
        }
        break;
    case 9:
        if (mMorfEnd) {
            setAnm_NUM(1, TRUE);
            mCurrAnmAtr = 1;
        }
        break;
    }
}

void daNpc_Co1_c::setAnm_ATR(int i_updateTex) {
    if (i_updateTex != 0) {
        setAnm_tex(a_anm_tbl3[mCurrAnmAtr].mResIndex);
    }
    setAnm_anm(&a_anm_tbl3[mCurrAnmAtr]);
}

void daNpc_Co1_c::anmAtr(u16 i_msgStatus) {
    switch (i_msgStatus) {
    case fopMsgStts_MSG_TYPING_e: {
        if (mMsgAttrCount == 0) {
            mCurrAnmAtr = 0xFF;
            chg_anmAtr(dComIfGp_getMesgAnimeAttrInfo());
            ++mMsgAttrCount;
        }
        u8 tag = dComIfGp_getMesgAnimeTagInfo();
        dComIfGp_clearMesgAnimeTagInfo();
        if (tag != 0xFF && mCurrAnmTag != tag) {
            mCurrAnmTag = (s8)tag;
            chg_anmTag();
        }
        break;
    }
    case fopMsgStts_MSG_DISPLAYED_e:
        mMsgAttrCount = 0;
        break;
    }
    control_anmTag();
    control_anmAtr();
}

void daNpc_Co1_c::eventOrder() {
    s8 state = mEventState;
    if (state == 1 || state == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
        if (mEventState == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (state >= 3) {
        mEvtIdxSel = state - 3;
        s16 evtIdx = mEventIdx[mEvtIdxSel];
        fopAcM_orderOtherEventId(this, evtIdx, EVT_NO_EVENT, EVT_NO_TARGET, 0, 1);
    }
}

void daNpc_Co1_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (dComIfGp_evmng_startCheck(mEventIdx[mEvtIdxSel])) {
            switch (mEvtIdxSel) {
            case 0:
                break;
            case 1:
                actor_status &= ~fopAcStts_UNK4000_e;
                break;
            case 2:
                mActionIndex = 0;
                break;
            default:
                break;
            }
            mEventState = 0;
        }
    } else if (eventInfo.checkCommandTalk()) {
        if (mEventState == 1 || mEventState == 2) {
            mEventState = 0;
            mHide = TRUE;
        }
    }
}

void daNpc_Co1_c::setCollision_SP_() {
    if (mHide) return;

    cXyz pos;
    f32 radius, height;
    if (mCurrAnmNum == 1) {
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::YrotM(current.angle.y);
        cXyz off;
        off.x = 0.0f;
        off.y = 0.0f;
        off.z = -20.0f;
        radius = 70.0f;
        height = 60.0f;
        MTXMultVec(mDoMtx_stack_c::get(), &off, &pos);
    } else {
        pos.set(current.pos.x, current.pos.y, current.pos.z);
        radius = 40.0f;
        height = 90.0f;
    }

    mCyl.SetC(pos);
    mCyl.SetR(radius);
    mCyl.SetH(height);
    dComIfG_Ccsp()->Set(&mCyl);
}

void daNpc_Co1_c::set_target(int i_type) {
    switch (i_type) {
    case 0:
        mActionIndex = 0;
        break;
    case 1: {
        cXyz vec = dNpc_playerEyePos(-20.0f);
        f32 dist = fopAcM_searchActorDistance(this, dComIfGp_getPlayer(0));
        s16 angle = fopAcM_searchActorAngleY(this, dComIfGp_getPlayer(0));
        angle -= BAM_90DEG;
        mDoMtx_stack_c::transS(current.pos.x, vec.y, current.pos.z);
        mDoMtx_YrotM(mDoMtx_stack_c::get(), angle);
        vec.x = 0.0f;
        vec.y = 0.0f;
        vec.z = dist;
        MTXMultVec(mDoMtx_stack_c::get(), &vec, &mEventPos);
        mActionIndex = 2;
        break;
    }
    }
}

u8 daNpc_Co1_c::chk_talk() {
    u8 ret = 1;
    mGetItem = dItem_NONE_e;
    if (dComIfGp_event_chkTalkXY()) {
        if (dComIfGp_evmng_ChkPresentEnd()) {
            mGetItem = dComIfGp_event_getPreItemNo();
        } else {
            ret = 0;
        }
    }
    return ret;
}

BOOL daNpc_Co1_c::chk_partsNotMove() {
    BOOL ret = FALSE;
    if (mPrevJntHeadX == m_jnt.getHead_y() &&
        mPrevJntBackboneX == m_jnt.getBackbone_y() &&
        mPrevAngleY == current.angle.y) {
        ret = TRUE;
    }
    return ret;
}

void daNpc_Co1_c::lookBack() {
    mPrevJntHeadX = m_jnt.getHead_y();
    mPrevJntBackboneX = m_jnt.getBackbone_y();
    mPrevAngleY = current.angle.y;

    cXyz dstPos;
    cXyz srcPos = current.pos;
    srcPos.y = eyePos.y;
    dstPos.x = 0.0f;
    dstPos.y = 0.0f;
    dstPos.z = 0.0f;
    cXyz* dstPtr = NULL;
    s16 targetY = current.angle.y;
    bool headOnlyFollow = mInitDone;

    switch (mActionIndex) {
    case 1:
        dstPos = dNpc_playerEyePos(-20.0f);
        dstPtr = &dstPos;
        srcPos = current.pos;
        srcPos.y = eyePos.y;
        break;
    case 2:
        dstPos = mEventPos;
        dstPtr = &dstPos;
        srcPos = current.pos;
        srcPos.y = eyePos.y;
        break;
    case 3:
        targetY = mDesiredYRot;
        break;
    }

    cLib_addCalcAngleS2(&mHeadAngle, l_HIO.mNpc.mMaxTurnVel, 4, BAM_45DEG);
    if (!m_jnt.trnChk()) {
        mHeadAngle = 0;
    }

    m_jnt.lookAtTarget(&current.angle.y, dstPtr, srcPos, targetY, mHeadAngle, headOnlyFollow);
}

u16 daNpc_Co1_c::next_msgStatus(u32* pMsgNo) {
    u16 ret = fopMsgStts_MSG_CONTINUES_e;
    switch (*pMsgNo) {
        case MSG_CO_HAS_LETTER: *pMsgNo = MSG_CO_GIVE_LETTER; break;
        case MSG_CO_GIVE_LETTER: *pMsgNo = MSG_CO_GAVE_LETTER; break;
        case MSG_CO_LETTER_PASSED: *pMsgNo = MSG_CO_LETTER_PASSED_1; break;
        case MSG_CO_LETTER_PASSED_1: *pMsgNo = MSG_CO_LETTER_PASSED_2; break;
        case MSG_CO_LETTER_PASSED_2: *pMsgNo = MSG_CO_LETTER_PASSED_3; break;
        case MSG_CO_LETTER_PASSED_3: *pMsgNo = MSG_CO_LETTER_PASSED_4; break;
        case MSG_CO_LETTER_PASSED_4: *pMsgNo = MSG_CO_LETTER_PASSED_5; break;
        case MSG_CO_LETTER_PASSED_5: *pMsgNo = MSG_CO_LETTER_PASSED_6; break;
        case MSG_CO_LETTER_PASSED_6: *pMsgNo = MSG_CO_LETTER_DONE; break;
        case MSG_CO_DELIVERED_START: *pMsgNo = MSG_CO_DELIVERED_END; break;
        case MSG_CO_DELIVERED_END: *pMsgNo = MSG_CO_ENDING; break;
    default: ret = fopMsgStts_MSG_ENDS_e; break;
    }
    return ret;
}

u32 daNpc_Co1_c::getMsg_CO1_0() {
    if (mGetItem == dItem_FATHER_LETTER_e) {
        return MSG_CO_GOT_LETTER;
    }
    if (mGetItem != dItem_NONE_e) {
        return MSG_CO_GOT_ITEM;
    }

    if (mHasLetter) {
        return MSG_CO_HAS_LETTER;
    }

    if (dNpc_chkLetterPassed()) {
        if (dComIfGs_isEventBit(EVTBIT_PRL_FLW_DONE)) {
            return MSG_CO_DELIVERED_START;
        }
        return MSG_CO_LETTER_PASSED;
    }

    if (dComIfGs_isEventBit(EVTBIT_GREETED)) {
        return MSG_CO_ALREADY_MET;
    }
    return MSG_CO_GREETING;
}

u32 daNpc_Co1_c::getMsg() {
    u32 ret = 0;
    switch (mInitStep) {
    case 0:
        ret = getMsg_CO1_0();
        break;
    }
    return ret;
}

BOOL daNpc_Co1_c::chkAttention() {
    dAttention_c& attention = dComIfGp_getAttention();
    if (attention.LockonTruth()) {
        return this == attention.LockonTarget(0) ? TRUE : FALSE;
    }
    return this == attention.ActionTarget(0) ? TRUE : FALSE;
}

void daNpc_Co1_c::setAttention(bool i_forceUpdate) {
    if (mCurrAnmNum == 1) {
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::YrotM(current.angle.y);
        cXyz off(0.0f, 60.0f, -50.0f);
        MTXMultVec(mDoMtx_stack_c::get(), &off, &attention_info.position);
    } else {
        attention_info.position.set(current.pos.x, current.pos.y + l_HIO.mNpc.mAttnYOff, current.pos.z);
    }

    if (mAttnScratch || i_forceUpdate) {
        eyePos.set(mHeadPos.x, mHeadPos.y, mHeadPos.z);
    }
}

BOOL daNpc_Co1_c::charDecide(int i_type) {
    mType = 0;
    mInitStep = -1; // dead store - compiler artifact, do not remove
    mInitStep = 0;
    return TRUE;
}

void daNpc_Co1_c::eInit_MDR_() {
    setAnm_NUM(10, TRUE);
    mActionIndex = 0;
}

void daNpc_Co1_c::eInit_RED_LTR_() {
    setAnm_NUM(8, TRUE);
}

void daNpc_Co1_c::event_actionInit(int i_staffIdx) {
    int* actNo = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "ActNo");
    if (actNo != NULL) {
        mEventActNo = *actNo;
        switch (mEventActNo) {
        case 0:
            eInit_MDR_();
            break;
        case 1:
            eInit_RED_LTR_();
            break;
        }
    }
}

BOOL daNpc_Co1_c::eMove_MDR_() {
    int frame = (int)mpMorf->getFrame();
    u32 result = frame ? 0 : 1;
    if ((u8)result) {
        setAnm_NUM(11, TRUE);
    }
    return (BOOL)(result);
}

BOOL daNpc_Co1_c::eMove_RED_LTR_() {
    BOOL ret = FALSE;
    if (mMorfEnd) {
        switch (mCurrAnmNum) {
        case 8:
            setAnm_NUM(4, TRUE);
            break;
        case 4:
            mNextAnmNum = 7;
            setStt(2);
            ret = TRUE;
            break;
        default:
            setAnm_NUM(8, TRUE);
            break;
        }
    }
    return ret;
}

BOOL daNpc_Co1_c::event_action() {
    switch (mEventActNo) {
    case 0:
        return eMove_MDR_();
    case 1:
        return eMove_RED_LTR_();
    default:
        return TRUE;
    }
}

void daNpc_Co1_c::privateCut(int staffIdx) {
    if (staffIdx == -1) return;

    static char* a_cut_tbl[] = {"ACTION"};

    int actIdx = dComIfGp_evmng_getMyActIdx(staffIdx, a_cut_tbl, 1, TRUE, 0);
    mCurActIdx = actIdx;

    if (mCurActIdx == -1) {
        dComIfGp_evmng_cutEnd(staffIdx);
        return;
    }

    if (dComIfGp_evmng_getIsAddvance(staffIdx)) {
        switch (mCurActIdx) {
        case 0:
            event_actionInit(staffIdx);
            break;
        }
    }

    u32 done;
    switch (mCurActIdx) {
    case 0:
        done = event_action();
        break;
    default:
        done = TRUE;
        break;
    }

    if ((u8)done) {
        dComIfGp_evmng_cutEnd(staffIdx);
    }
}

void daNpc_Co1_c::endEvent() {
    dComIfGp_event_reset();
    mCurrAnmAtr = 0xFF;
}

s32 daNpc_Co1_c::isEventEntry() {
    char* name = mDemoEventCut.getActorName();
    return dComIfGp_evmng_getMyStaffId(name, NULL, 0);
}

void daNpc_Co1_c::event_proc(int staffIdx) {
    s16 evtIdx = mEventIdx[mEvtIdxSel];
    if (dComIfGp_evmng_endCheck(evtIdx)) {
        switch (mEvtIdxSel) {
        case 0:
            dComIfGs_onEventBit(EVTBIT_PRL_FLW_DONE);
            setStt(4);
            break;
        case 1:
            dComIfGs_onEventBit(EVTBIT_CONTACT_DONE);
            break;
        case 2:
            mEventState = 1;
            break;
        default:
            break;
        }
        endEvent();
    } else {
        if (!mDemoEventCut.cutProc()) {
            privateCut(staffIdx);
        }
        lookBack();
    }
}

BOOL daNpc_Co1_c::set_action(ActionFunc i_action, void* i_param) {
    if (mCurrActionFunc != i_action) {
        if (mCurrActionFunc != NULL) {
            mActionState = 9;
            (this->*mCurrActionFunc)(i_param);
        }
        mCurrActionFunc = i_action;
        mActionState = 0;
        (this->*mCurrActionFunc)(i_param);
    }
    return TRUE;
}

void daNpc_Co1_c::setStt(signed char i_stt) {
    mTimer = 0;
    mAnmTagIndex = i_stt;
    switch (mAnmTagIndex) {
    case 0:
    case 1:
        break;
    case 2:
        mCurrAnmAtr = 0xFF;
        mActionIndex = 1;
        break;
    case 7:
        mActionIndex = 0;
        break;
    }
    setAnm();
}

BOOL daNpc_Co1_c::wait_1() {
    if (mEventState == 1 || mEventState >= 3) {
        return TRUE;
    }

    if (mHide) {
        if (chk_talk()) {
            mNextAnmNum = 4;
            setStt(3);
        }
        return TRUE;
    }

    mEventState = 2;
    return TRUE;
}

BOOL daNpc_Co1_c::wait_2() {
    if (mHide) {
        if (chk_talk()) {
            if (dNpc_chkLetterPassed()) {
                mNextAnmNum = 7;
            } else {
                mNextAnmNum = 4;
            }
            setStt(2);
        }
        return TRUE;
    }

    mEventState = 2;

    if (mAttnFlag) {
        mTimer = 60;
    }

    if (cLib_calcTimer(&mTimer) != 0) {
        mActionIndex = 1;
    } else {
        mActionIndex = 0;
    }

    return TRUE;
}

BOOL daNpc_Co1_c::wakeup() {
    if (mMorfEnd) {
        mNextAnmNum = 4;
        setStt(2);
    }
    return TRUE;
}

BOOL daNpc_Co1_c::talk_1() {
    u8 partsNotMove = chk_partsNotMove();

    if (mEventState == 1 || mEventState >= 3) {
        return TRUE;
    }

    if (dNpc_chkLetterPassed() && !mHasLetter && !dComIfGs_isEventBit(EVTBIT_PRL_FLW_DONE)) {
        if (mEventState != 3) {
            mGetItem = dItem_NONE_e;
            mHide = FALSE;
            endEvent();
            mEventState = 3;
        }
        return TRUE;
    }

    talk(1);

    if (mpCurrMsg != NULL) {
        switch (mpCurrMsg->mStatus) {
        case fopMsgStts_MSG_DESTROYED_e:
            switch ((s32)mCurrMsgNo) {
            case MSG_CO_GREETING:
                dComIfGs_onEventBit(EVTBIT_GREETED);
                break;
            case MSG_CO_LETTER_DONE:
                dComIfGs_onEventBit(EVTBIT_PRL_FLW_DONE);
                break;
            case MSG_CO_GAVE_LETTER:
                mHasLetter = FALSE;
                break;
            }
            if (mGetItem == dItem_FATHER_LETTER_e) {
                mEventState = 5;
                dComIfGp_evmng_CancelPresent();
                dComIfGs_setReserveItemEmpty();
                endEvent();
                mHasLetter = TRUE;
            } else {
                setStt(mNextAnmNum);
                if (mNextAnmNum != 7) {
                    mHide = FALSE;
                    endEvent();
                }
            }
            mGetItem = dItem_NONE_e;
            mTimer = 60;
            break;
        case fopMsgStts_BOX_OPENING_e:
        case fopMsgStts_MSG_TYPING_e:
            if (mCurrMsgNo == MSG_CO_ENDING) {
                mActionIndex = 0;
            }
            break;
        }
    }

    return partsNotMove;
}

BOOL daNpc_Co1_c::toru_1() {
    if (mHide) {
        if (mGetItem == dItem_FATHER_LETTER_e) {
            mGetItem = dItem_NONE_e;
            setAnm_NUM(8, TRUE);
        }
        if (mMorfEnd) {
            setStt(6);
        }
    }
    return FALSE;
}

BOOL daNpc_Co1_c::read_1() {
    if (mMorfEnd) {
        mNextAnmNum = 7;
        setStt(2);
    }
    return FALSE;
}

BOOL daNpc_Co1_c::modoru() {
    if ((s32)mpMorf->getFrame() == 0) { // (s32) cast forces fctiwz float-to-int conversion
        setStt(4);
        mHide = FALSE;
        endEvent();
    }
    return TRUE;
}

BOOL daNpc_Co1_c::wait_action1(void*) {
    s8 state = mActionState;
    switch (state) {
    case 0:
        if (dNpc_chkLetterPassed()) {
            setStt(4);
        } else {
            if (!dComIfGs_isEventBit(EVTBIT_CONTACT_DONE)) {
                mEventState = 4;
            }
            setStt(1);
        }
        
        mPrevPos = current.pos;
        mFloatVal = 0.0f;
        dKy_plight_set((LIGHT_INFLUENCE*)&mPrevPos);
        
        mActionState++;
        break;
    case 1:
    case 2:
    case 3:
        mAttnFlag = chkAttention();
        
        BOOL result;
        switch (mAnmTagIndex) {
        case 1:
            result = wait_1();
            break;
        case 2:
        case 3:
            result = talk_1();
            break;
        case 4:
            result = wakeup();
            break;
        case 5:
            result = wait_2();
            break;
        case 6:
            result = toru_1();
            break;
        case 7:
            result = read_1();
            break;
        case 0:
            result = modoru();
            break;
        }
        mAttnScratch = result;
        
        lookBack();
        break;
    case 9:
        break;
    }
    
    return TRUE;
}

u8 daNpc_Co1_c::demo() {
    if (demoActorID == 0) {
        if (mDemo) {
            mDemo = false;
        }
    } else {
        mDemo = true;

        dDemo_actor_c* demoActor = dComIfGp_demo_getActor(demoActorID);

        if (mpBtpRes != NULL) {
            mBtpFrame++;
            if (mBtpFrame >= mpBtpRes->getFrameMax()) {
                mBtpFrame = mpBtpRes->getFrameMax();
            }
        }
        J3DAnmTexPattern* btpData = demoActor->getP_BtpData("Co");
        if (btpData != NULL) {
            mpBtpRes = btpData;
            J3DModelData* modelData = mpMorf->getModel()->getModelData();
            if (mBtpAnm.init(modelData, mpBtpRes, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, TRUE, FALSE)) {
                mTexPatternNum = 7;
                mBtpFrame = 0;
            }
        }

#if VERSION != 0
        dDemo_setDemoData(this, 0x6A, mpMorf, "Co", 0, NULL, 0, 0);
#else
        dDemo_setDemoData(this, 0x6A, mpMorf, "Co", 0, NULL);
#endif
    }
    return mDemo;
}

void daNpc_Co1_c::shadowDraw() {
    cXyz pos(current.pos.x, current.pos.y + 150.0f, current.pos.z);
    J3DModel* model = mpMorf->getModel();

    mShadowIdx = dComIfGd_setShadow(mShadowIdx, 1, model, &pos, 800.0f, 40.0f,
                                     current.pos.y, mObjAcch.GetGroundH(),
                                     mObjAcch.m_gnd, &tevStr, 0, 1.0f);
}

BOOL daNpc_Co1_c::_draw() {
    J3DModel* mainModel = mpMorf->getModel();
    J3DModelData* mainModelData = mainModel->getModelData();
    J3DModel* prlModel = mpPrlMorf->getModel();
    J3DModelData* prlModelData = prlModel->getModelData();

    if (mInitFlags || mDemoFlags) {
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);

    dKy_tevstr_c& tr = tevStr;
    u8 alpha = l_HIO.mNpc.mAlpha;
    u8 alpha_calc = (255 - alpha) * mOscillation;
    tr.mLightObj.mInfo.mColor.r = alpha_calc + alpha;

    g_env_light.setLightTevColorType(mainModel, &tr);

    mBtpAnm.entry(mainModelData, mBtpFrame);
    mpMorf->entryDL();
    mainModelData->getMaterialTable().removeTexNoAnimator(mBtpAnm.getBtpAnm());

    g_env_light.setLightTevColorType(prlModel, &tevStr);

    mBtkAnm.entry(prlModelData, (f32)mBtkFrame);
    mpPrlMorf->entryDL();
    prlModelData->getMaterialTable().removeTexMtxAnimator(mBtkAnm.getBtkAnm());

    if (mDrawHandR) {
        g_env_light.setLightTevColorType(mpItmModel, &tevStr);
        mDoExt_modelEntryDL(mpItmModel);
    }

    shadowDraw();
    dSnap_RegistFig(DSNAP_TYPE_UNK8B, this, 1.0f, 1.0f, 1.0f);

    return TRUE;
}

BOOL daNpc_Co1_c::_execute() {
    if (!mExecStarted) {
        mBkPos = current.pos;
        mBkAngleX = current.angle.x;
        mBkAngleY = current.angle.y;
        mBkAngleZ = current.angle.z;
        mExecStarted = TRUE;
    }

    m_jnt.setParam(
        l_HIO.mNpc.mMaxBackboneX, l_HIO.mNpc.mMaxBackboneY,
        l_HIO.mNpc.mMinBackboneX, l_HIO.mNpc.mMinBackboneY,
        l_HIO.mNpc.mMaxHeadX, l_HIO.mNpc.mMaxHeadY,
        l_HIO.mNpc.mMinHeadX, l_HIO.mNpc.mMinHeadY,
        l_HIO.mNpc.mMaxTurnStep
    );

    if (mInitFlags) {
        if (demoActorID == 0) {
            return TRUE;
        }
    }

    mLookFlags = 0;
    mInitFlags = 0;

    checkOrder();

    if (demo() == 0) {
        int staffId = -1;
        if (dComIfGp_event_runCheck()) {
            if (!eventInfo.checkCommandTalk()) {
                staffId = isEventEntry();
            }
        }

        if (staffId >= 0) {
            event_proc(staffId);
        } else {
            (this->*mCurrActionFunc)(NULL);
        }

        if (!mLookFlags) {
            fopAcM_posMoveF(this, mStts.GetCCMoveP());
        }

        if (!mNoPosMove) {
            shape_angle = current.angle;
        }
    }

    eventOrder();
    setMtx(FALSE);

    if (!mDemo) {
        setCollision_SP_();
    }

    return TRUE;
}

BOOL daNpc_Co1_c::_delete() {
    dComIfG_resDelete(&mPhs, "Co");
    dKy_plight_cut((LIGHT_INFLUENCE*)&mPrevPos);

    if (heap != NULL && mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }

    return TRUE;
}

static BOOL CheckCreateHeap(fopAc_ac_c* actor) {
    return ((daNpc_Co1_c*)actor)->CreateHeap();
}

cPhs_State daNpc_Co1_c::_create() {
    fopAcM_SetupActor(this, daNpc_Co1_c);

    cPhs_State resLoad = dComIfG_resLoad(&mPhs, "Co");
    if (resLoad != cPhs_COMPLEATE_e) {
        return resLoad;
    }

    u8 decResult = charDecide(fopAcM_GetParam(this) & CHAR_TYPE_MASK);
    if (!decResult) {
        return cPhs_ERROR_e;
    }

    static int a_size_tbl[] = { 0x272E0 };

    if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_size_tbl[mType])) {
        return cPhs_ERROR_e;
    }

    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -40.0f, -20.0f, -100.0f, 40.0f, 100.0f, 60.0f);

    u8 initResult = createInit();
    if (initResult == 0) {
        return cPhs_ERROR_e;
    }
    return resLoad;
}

J3DModelData* daNpc_Co1_c::create_Anm() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Co", CO_BDL_CO);
    JUT_ASSERT(0x81F, a_mdl_dat != 0);

    mDoExt_McaMorf* morf = new mDoExt_McaMorf(
        a_mdl_dat, NULL, NULL,
        (J3DAnmTransform*)dComIfG_getObjectIDRes("Co", CO_BCK_CO_WAIT01),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, NULL,
        0x80000, 0x11020022
    );

    mpMorf = morf;
    if (mpMorf == NULL) {
        return NULL;
    }

    if (mpMorf->getModel() == NULL) {
        mpMorf = NULL;
        return NULL;
    }

    m_hed_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
    JUT_ASSERT(0x833, m_hed_jnt_num >= 0);

    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(0x836, m_bbone_jnt_num >= 0);

    m_hnd_R_jnt_num = a_mdl_dat->getJointName()->getIndex("handR");
    JUT_ASSERT(0x839, m_hnd_R_jnt_num >= 0);

    return a_mdl_dat;
}

J3DModelData* daNpc_Co1_c::create_prl_Anm() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Co", CO_BDL_CO_PEAL);
    JUT_ASSERT(0x848, a_mdl_dat != 0);

    mDoExt_McaMorf* morf = new mDoExt_McaMorf(
        a_mdl_dat, NULL, NULL,
        (J3DAnmTransform*)dComIfG_getObjectIDRes("Co", CO_BCK_COPEAL_WAIT01),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, NULL,
        0x80000, 0x15021222
    );

    mpPrlMorf = morf;
    if (mpPrlMorf == NULL) {
        return NULL;
    }

    if (mpPrlMorf->getModel() == NULL) {
        mpPrlMorf = NULL;
        return NULL;
    }

    m_prl_jnt_num = a_mdl_dat->getJointName()->getIndex("co_pearl");
    JUT_ASSERT(0x85C, m_prl_jnt_num >= 0);

    return a_mdl_dat;
}

BOOL daNpc_Co1_c::create_itm_Mdl() {
    mpItmModel = NULL;

    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Co", CO_BDL_CO_LETTER);
    JUT_ASSERT(0x86E, a_mdl_dat != 0);

    mpItmModel = mDoExt_J3DModel__create(a_mdl_dat, 0x80000, 0x11000002);
    return TRUE;
}

BOOL daNpc_Co1_c::CreateHeap() {
    J3DModelData* modelData = create_Anm();
    if (modelData == NULL) {
        return FALSE;
    }

    mTexPatternNum = 6;

    if ((u8)iniTexPttrnAnm(FALSE) == 0) {
        mpMorf = NULL;
        return FALSE;
    }

    if (create_prl_Anm() == NULL) {
        mpMorf = NULL;
        return FALSE;
    }

    if ((u8)setBtk(FALSE) == 0) {
        mpMorf = NULL;
        mpPrlMorf = NULL;
        return FALSE;
    }

    if ((u8)create_itm_Mdl() == 0) {
        goto error; // cleanup path
    }

    for (u16 i = 0; i < modelData->getJointNum(); i++) {
        if (i == m_hed_jnt_num || i == m_bbone_jnt_num) {
            J3DNode* node = mpMorf->getModel()->getModelData()->getJointNodePointer(i);
            node->setCallBack(nodeCallBack_Co1);
        }
    }

    mpMorf->getModel()->setUserArea((u32)this);

    mAcchCir.SetWall(30.0f, 40.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this), NULL, NULL);

    return TRUE;

error:
    mpMorf = NULL;
    mpPrlMorf = NULL;
    return FALSE;
}

static cPhs_State daNpc_Co1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Co1_c*)i_this)->_create();
}

static BOOL daNpc_Co1_Delete(daNpc_Co1_c* i_this) {
    return i_this->_delete();
}

static BOOL daNpc_Co1_Execute(daNpc_Co1_c* i_this) {
    return i_this->_execute();
}

static BOOL daNpc_Co1_Draw(daNpc_Co1_c* i_this) {
    return i_this->_draw();
}

static BOOL daNpc_Co1_IsDelete(daNpc_Co1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Co1_Method = {
    (process_method_func)daNpc_Co1_Create,
    (process_method_func)daNpc_Co1_Delete,
    (process_method_func)daNpc_Co1_Execute,
    (process_method_func)daNpc_Co1_IsDelete,
    (process_method_func)daNpc_Co1_Draw,
};

actor_process_profile_definition g_profile_NPC_CO1 = {
    fpcLy_CURRENT_e,
    0x0007,
    fpcPi_CURRENT_e,
    PROC_NPC_CO1,
    &g_fpcLf_Method.base,
    sizeof(daNpc_Co1_c),
    0,
    0,
    &g_fopAc_Method.base,
    PRIO_NPC_CO1,
    &l_daNpc_Co1_Method,
    fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    fopAc_ACTOR_e,
    fopAc_CULLBOX_CUSTOM_e,
};
