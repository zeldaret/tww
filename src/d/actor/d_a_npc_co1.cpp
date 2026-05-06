/**
 * d_a_npc_co1.cpp
 * NPC - Mailman (Postman)
 */

#include "d/dolzel_rel.h"
#include "d/actor/d_a_npc_co1.h"
#include "d/d_com_inf_game.h"
#include "d/d_snap.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_kankyo.h"
#include "d/d_drawlist.h"
#include <math.h>

// Reverse aliases: fields use original names, defines map modern→original
#define mpBtpRes m_hed_tex_pttrn
#define mpBtkRes m_prl_btk

static daNpc_Co1_HIO_c l_HIO;

static const u32 a_prm_tbl[11] = {
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

static const int a_bck_resID_tbl[11] = {
    0x10, 0x11, 0x09, 0x0A, 0x0B, 0x0D, 0x0E, 0x0C, 0x0F, 0x0A, 0x09,
};

static const int a_bck_resID_prl_tbl[11] = {
    0x07, 0x08, 0x00, 0x01, 0x02, 0x04, 0x05, 0x03, 0x06, 0x01, 0x00,
};

static const int a_btp_resID_tbl[7] = {
    0x16, 0x17, 0x1A, 0x1C, 0x19, 0x1B, 0x18,
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
    static cXyz a_att_pos_offst(0.0f, 0.0f, 0.0f);
    u16 jointIdx = ((J3DJoint*)i_node)->getJntNo();

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
    BOOL ret = isSym == 0 ? TRUE : FALSE;
    if (isSym == 0) {
        u32* flg = (u32*)((char*)this + 0x1C4);
        *flg &= ~0x00000080;
        *flg |= 0x4000;
        set_action(&daNpc_Co1_c::wait_action1, NULL);
    }
    return ret;
}

void daNpc_Co1_c::setStt(signed char i_stt) {
    mTimer = 0;
    mAnmTagIndex = i_stt;
    switch (mAnmTagIndex) {
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

BOOL daNpc_Co1_c::createInit() {
    for (int i = 0; i < 3; i++) {
        mEventIdx[i] = dComIfGp_evmng_getEventIdx(l_evn_tbl[i], 0xFF);
    }

    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 10;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0x46;
    gravity = -4.5f;
    mEventPos = current.pos;

    mInitDone = TRUE;
    mDemoEventCut.setActorInfo2("Co1", this);

    mCurrAnmNum = 11;

    if (mInitStep == 0) {
        if (!init_CO1_0()) {
            return FALSE;
        }
        shape_angle = current.angle;
    } else {
        return FALSE;
    }

    mStts.Init(0xFF, 0xFF, this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);

    mpMorf->setMorf(0.0f);
    setMtx(TRUE);
    return TRUE;
}

void daNpc_Co1_c::setMtx(bool param_1) {
    if (!mDemo) {
        plyTexPttrnAnm();
        mMorfEnd = mpMorf->play(NULL, 0, 0);

        if (mpMorf->getFrame() < mPrevMorfFrame) {
            mMorfEnd = TRUE;
        }
        mPrevMorfFrame = mpMorf->getFrame();

        mpPrlMorf->setFrame((f32)(s32)mpMorf->getFrame());

        if (mpMorf->getFrame() < mPrevMorfFrame) {
            mMorfEnd = TRUE;
        }
        mPrevMorfFrame = mpMorf->getFrame();

        mObjAcch.CrrPos(*dComIfG_Bgsp());

        if (mCurrAnmNum == 8) {
            mDrawHandR = (mpMorf->getFrame() >= 15.0f);
        } else if (mCurrAnmNum == 4) {
            mDrawHandR = TRUE;
        } else {
            mDrawHandR = FALSE;
        }
    }

    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();

    PSMTXCopy(mpMorf->getModel()->getAnmMtx(m_prl_jnt_num), mDoMtx_stack_c::get());
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

    mPrevPos2[0] = l_HIO.mNpc.mPrm26;
    mPrevPos2[1] = l_HIO.mNpc.mPrm28;
    mPrevPos2[2] = l_HIO.mNpc.mPrm2A;

    f32 sinVal = fabs(cM_ssin(mSinAngle));
    f32 diff = l_HIO.mNpc.mPrm2C - l_HIO.mNpc.mPrm30;
    if (diff < 0.0f) diff = 0.0f;
    f32 fVal = diff * sinVal + l_HIO.mNpc.mPrm30;
    if (fVal < 0.001f) fVal = 0.001f;
    mFloatVal = fVal;

    setAttention(param_1);
}

s32 daNpc_Co1_c::anmNum_toResID(int i_idx) {
    return a_bck_resID_tbl[i_idx];
}

s32 daNpc_Co1_c::anmNum_toResID_prl(int i_idx) {
    return a_bck_resID_prl_tbl[i_idx];
}

s32 daNpc_Co1_c::btpNum_toResID(int i_idx) {
    return a_btp_resID_tbl[i_idx];
}

BOOL daNpc_Co1_c::setBtp(bool param_1, int param_2) {
    J3DModelData* modelData = mpMorf->getModel()->getModelData();
    int btpNum = btpNum_toResID(param_2);
    J3DAnmTexPattern* btpRes = (J3DAnmTexPattern*)dComIfG_getObjectIDRes("Co", btpNum);
    mpBtpRes = btpRes;
    JUT_ASSERT(0x1CE, m_hed_tex_pttrn != 0);

    int result = mBtpAnm.init(modelData, mpBtpRes, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, param_1);
    if (result) {
        mBtpFrame = 0;
        mBtpTimer = 0;
    }
    return result != FALSE;
}

BOOL daNpc_Co1_c::setBtk(bool param_1) {
    J3DModelData* modelData = mpPrlMorf->getModel()->getModelData();
    J3DAnmTextureSRTKey* btkRes = (J3DAnmTextureSRTKey*)dComIfG_getObjectIDRes("Co", 0x15);
    mpBtkRes = btkRes;
    JUT_ASSERT(0x1EA, m_prl_btk != 0);

    int result = mBtkAnm.init(modelData, mpBtkRes, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, param_1);
    if (result) {
        mBtkFrame = 0;
    }
    return result != FALSE;
}

BOOL daNpc_Co1_c::iniTexPttrnAnm(bool param_1) {
    return setBtp(param_1, mTexPatternNum);
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
    if (i_atr >= 14) return;
    if (i_atr == mCurrAnmAtr) {
    } else {
        mActionIndex = 1;
        u32 idx = i_atr - 3;
        if (idx <= 10) {
            switch (idx) {
            case 0:
            case 1:
            case 2:
            case 4:
            case 8:
                mActionIndex = 0;
                break;
            case 10:
                set_target(1);
                break;
            }
        }

        mCurrAnmAtr = i_atr;
        setAnm_ATR(TRUE);
    }
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
        if ((s8)mMorfEnd) {
            setAnm_NUM(7, TRUE);
            mCurrAnmAtr = 6;
        }
        break;
    case 3:
        if ((s8)mMorfEnd) {
            setAnm_NUM(4, TRUE);
            mCurrAnmAtr = 10;
        }
        break;
    case 7:
        if ((s8)mMorfEnd) {
            setAnm_NUM(6, TRUE);
            mCurrAnmAtr = 5;
        }
        break;
    case 8:
        if ((s8)mMorfEnd) {
            setAnm_NUM(7, TRUE);
            mCurrAnmAtr = 6;
        }
        break;
    case 9:
        if ((s8)mMorfEnd) {
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
    if (i_msgStatus == fopMsgStts_MSG_DISPLAYED_e) {
        field_0x863 = 0;
    } else if (i_msgStatus == fopMsgStts_MSG_TYPING_e) {
        if (field_0x863 == 0) {
            mCurrAnmAtr = 0xFF;
            chg_anmAtr(dComIfGp_getMesgAnimeAttrInfo());
            field_0x863++;
        }
        u8 tag = dComIfGp_getMesgAnimeTagInfo();
        dComIfGp_clearMesgAnimeTagInfo();
        if (tag != 0xFF && tag != mCurrAnmTag) {
            mCurrAnmTag = tag;
            chg_anmTag();
        }
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
        fopAcM_orderOtherEventId(this, evtIdx, 0xFF, 0xFFFF, 0, 1);
    }
}

void daNpc_Co1_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (dComIfGp_evmng_startCheck(mEventIdx[mEvtIdxSel])) {
            switch (mEvtIdxSel) {
            case 0:
                break;
            case 1:
                *(u32*)((u8*)this + 0x1C4) &= ~0x4000;
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
        off.z = 0.0f;
        MTXMultVec(mDoMtx_stack_c::get(), &off, &pos);
        radius = 60.0f;
        height = 30.0f;
    } else {
        pos = current.pos;
        radius = 40.0f;
        height = 150.0f;
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
        cXyz vec;
        vec = dNpc_playerEyePos(-20.0f);
        f32 dist = fopAcM_searchActorDistance(this, dComIfGp_getPlayer(0));
        s16 angle = fopAcM_searchActorAngleY(this, dComIfGp_getPlayer(0));

        mDoMtx_stack_c::transS(current.pos.x, vec.y, current.pos.z);
        mDoMtx_stack_c::YrotM(angle - 0x2000);

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
    BOOL ret = TRUE;
    mGetItem = 0xFF;

    u8 status = dComIfGp_getMesgStatus();
    if (status >= 1 && status <= 3) {
        if (dComIfGp_evmng_ChkPresentEnd()) {
            mGetItem = dComIfGp_event_getPreItemNo();
        } else {
            ret = FALSE;
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

    cLib_addCalcAngleS2(&mHeadAngle, l_HIO.mNpc.mMaxTurnVel, 4, 0x800);
    if (!m_jnt.trnChk()) {
        mHeadAngle = 0;
    }

    m_jnt.lookAtTarget(&current.angle.y, dstPtr, srcPos, targetY, mHeadAngle, headOnlyFollow);
}

u16 daNpc_Co1_c::next_msgStatus(u32* pMsgNo) {
    u16 ret = fopMsgStts_MSG_CONTINUES_e;
    u32 base = *pMsgNo - 0x183E;
    if (base <= 12) {
        switch (base) {
        case 0: *pMsgNo = 0x183F; break;
        case 1: *pMsgNo = 0x1840; break;
        case 3: *pMsgNo = 0x1842; break;
        case 4: *pMsgNo = 0x1843; break;
        case 5: *pMsgNo = 0x1844; break;
        case 6: *pMsgNo = 0x1845; break;
        case 7: *pMsgNo = 0x1846; break;
        case 8: *pMsgNo = 0x1847; break;
        case 9: *pMsgNo = 0x1848; break;
        case 11: *pMsgNo = 0x184A; break;
        case 12: *pMsgNo = 0x184B; break;
        default: ret = fopMsgStts_MSG_ENDS_e; break;
        }
    } else {
        ret = fopMsgStts_MSG_ENDS_e;
    }
    return ret;
}

u32 daNpc_Co1_c::getMsg_CO1_0() {
    if (mGetItem == 0x98) {
        return 0x183C;
    }
    if (mGetItem != 0xFF) {
        return 0x183B;
    }

    if (mHasLetter) {
        return 0x183E;
    }

    if (dNpc_chkLetterPassed()) {
        if (dComIfGs_isEventBit(0xF04)) {
            return 0x1849;
        }
        return 0x1841;
    }

    if (dComIfGs_isEventBit(0xF08)) {
        return 0x183A;
    }
    return 0x1839;
}

u32 daNpc_Co1_c::getMsg() {
    if (mInitStep == 0) {
        return getMsg_CO1_0();
    }
    return 0;
}

BOOL daNpc_Co1_c::chkAttention() {
    dAttention_c& attention = dComIfGp_getAttention();
    if (attention.LockonTruth()) {
        return this == attention.LockonTarget(0) ? TRUE : FALSE;
    }
    return this == attention.ActionTarget(0) ? TRUE : FALSE;
}

void daNpc_Co1_c::setAttention(bool param_1) {
    if (mCurrAnmNum == 1) {
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::YrotM(current.angle.y);
        cXyz off(0.0f, 60.0f, -50.0f);
        MTXMultVec(mDoMtx_stack_c::get(), &off, &attention_info.position);
    } else {
        attention_info.position.set(current.pos.x, current.pos.y + l_HIO.mNpc.mAttnYOff, current.pos.z);
    }

    if ((s32)mpAttnActor != 0 || param_1) {
        eyePos.set(mHeadPos.x, mHeadPos.y, mHeadPos.z);
    }
}

BOOL daNpc_Co1_c::charDecide(int i_type) {
    mType = 0;
    mInitStep = -1;
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

void daNpc_Co1_c::event_actionInit(int param_1) {
    int* actNo = dComIfGp_evmng_getMyIntegerP(param_1, "ActNo");
    if (actNo != NULL) {
        mEventActNo = *actNo;
        if (mEventActNo == 0) {
            eInit_MDR_();
        } else if (mEventActNo == 1) {
            eInit_RED_LTR_();
        }
    }
}

BOOL daNpc_Co1_c::eMove_MDR_() {
    BOOL end = (mpMorf->getFrame() == 0.0f);
    if (end) {
        setAnm_NUM(11, TRUE);
    }
    return end;
}

BOOL daNpc_Co1_c::eMove_RED_LTR_() {
    BOOL ret = FALSE;
    if ((s8)mMorfEnd) {
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

    if (dComIfGp_evmng_getIsAddvance(staffIdx) && mCurActIdx == 0) {
        event_actionInit(staffIdx);
    }

    BOOL done;
    if (mCurActIdx == 0) {
        done = event_action();
    } else {
        done = TRUE;
    }

    if (done) {
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
        if (mEvtIdxSel == 0) {
            dComIfGs_onEventBit(0xF04);
            setStt(4);
        } else if (mEvtIdxSel == 1) {
            dComIfGs_onEventBit(0x1810);
        } else {
            mEventState = 1;
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

BOOL daNpc_Co1_c::wait_1() {
    if (mEventState == 1 || mEventState >= 3) {
        return TRUE;
    }

    if (mHide) {
    if ((u8)chk_talk()) {
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
        if ((u8)chk_talk()) {
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
    if ((s8)mMorfEnd) {
        mNextAnmNum = 4;
        setStt(2);
    }
    return TRUE;
}

u8 daNpc_Co1_c::talk_1() {
    u8 partsNotMove = chk_partsNotMove();

    if (mEventState == 1 || mEventState >= 3) {
        return TRUE;
    }

    if (dNpc_chkLetterPassed() && !mHasLetter && !dComIfGs_isEventBit(0xF04)) {
        if (mEventState != 3) {
            mGetItem = 0xFF;
            mHide = FALSE;
            endEvent();
            mEventState = 3;
        }
        return TRUE;
    }

    talk(1);

    if (mpCurrMsg != NULL) {
        u16 status = mpCurrMsg->mStatus;
        if (status == 2 || status == 6) {
            if ((s32)mCurrMsgNo == 0x184B) {
                mActionIndex = 0;
            }
        } else if (status == 19) {
            if ((s32)mCurrMsgNo == 0x1840) {
                mHasLetter = FALSE;
            } else if ((s32)mCurrMsgNo == 0x1848) {
                dComIfGs_onEventBit(0xF04);
            } else if ((s32)mCurrMsgNo == 0x1839) {
                dComIfGs_onEventBit(0xF08);
            }

            if (mGetItem == 0x98) {
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

            mGetItem = 0xFF;
            mTimer = 60;
        }
    }

    return partsNotMove;
}

BOOL daNpc_Co1_c::toru_1() {
    if (mHide) {
        if (mGetItem == 0x98) {
            mGetItem = 0xFF;
            setAnm_NUM(8, TRUE);
        }
        if ((s8)mMorfEnd) {
            setStt(6);
        }
    }
    return FALSE;
}

BOOL daNpc_Co1_c::read_1() {
    if ((s8)mMorfEnd) {
        mNextAnmNum = 7;
        setStt(2);
    }
    return FALSE;
}

BOOL daNpc_Co1_c::modoru() {
    if ((s32)mpMorf->getFrame() == 0) {
        setStt(4);
        mHide = FALSE;
        endEvent();
    }
    return TRUE;
}

int daNpc_Co1_c::wait_action1(void*) {
    switch (mActionState) {
    case 0:
        if (dNpc_chkLetterPassed()) {
            setStt(4);
        } else {
            if (!dComIfGs_isEventBit(0x1810)) {
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

        switch (mAnmTagIndex) {
        case 1:
            mpAttnActor = (fopAc_ac_c*)(int)wait_1();
            break;
        case 2:
        case 3:
            mpAttnActor = (fopAc_ac_c*)(int)talk_1();
            break;
        case 4:
            mpAttnActor = (fopAc_ac_c*)(int)wakeup();
            break;
        case 5:
            mpAttnActor = (fopAc_ac_c*)(int)wait_2();
            break;
        case 6:
            mpAttnActor = (fopAc_ac_c*)(int)toru_1();
            break;
        case 7:
            mpAttnActor = (fopAc_ac_c*)(int)read_1();
            break;
        case 8:
            mpAttnActor = (fopAc_ac_c*)(int)modoru();
            break;
        }

        lookBack();
        break;
    }

    return TRUE;
}

u8 daNpc_Co1_c::demo() {
    if (demoActorID == 0) {
        if (mDemo) {
            mDemo = FALSE;
        }
    } else {
        mDemo = TRUE;

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
            mBtpAnm.init(modelData, mpBtpRes, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, TRUE, FALSE);
            mTexPatternNum = 7;
            mBtpFrame = 0;
        }

        dDemo_setDemoData(this, 0x6A, mpMorf, "Co", 0, NULL, 0, 0);
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

    s16 hioAlpha = l_HIO.mNpc.mAlpha;
    u8 alpha = hioAlpha & 0xFF;
    u8 invAlpha = 0xFF - alpha;
    f32 alphaFactor = (f32)invAlpha;
    *((u8*)&tevStr + 0x18) = (u8)(alphaFactor * field_0x84C) + alpha;

    g_env_light.setLightTevColorType(mainModel, &tevStr);

    mBtpAnm.entry(mainModelData, mBtpFrame);
    mpMorf->entryDL();
    mainModelData->removeTexNoAnimator(mpBtpRes);

    g_env_light.setLightTevColorType(prlModel, &tevStr);

    mBtkAnm.entry(prlModelData, (f32)mBtkFrame);
    mpPrlMorf->entryDL();
    prlModelData->removeTexMtxAnimator(mpBtkRes);

    if (mDrawHandR) {
        g_env_light.setLightTevColorType(mpItmModel, &tevStr);
        mDoExt_modelEntryDL(mpItmModel);
    }

    shadowDraw();
    dSnap_RegistFig(0x8B, this, 1.0f, 1.0f, 1.0f);

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
    if (!fopAcM_CheckStatus(this, 0x08)) {
        fopAcM_SetupActor(this, daNpc_Co1_c);
    }

    cPhs_State resLoad = dComIfG_resLoad(&mPhs, "Co");
    if (resLoad != cPhs_COMPLEATE_e) {
        return resLoad;
    }

    if (!(u8)charDecide(fopAcM_GetParam(this) & 0xFF)) {
        return cPhs_ERROR_e;
    }

    static int a_size_tbl[] = { 0x272E0 };

    if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_size_tbl[mType])) {
        return cPhs_ERROR_e;
    }

    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -40.0f, -20.0f, -100.0f, 40.0f, 100.0f, 60.0f);

    if ((u8)createInit() == 0) {
        return cPhs_ERROR_e;
    }
    return resLoad;
}

J3DModelData* daNpc_Co1_c::create_Anm() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Co", 0x13);
    JUT_ASSERT(0x81F, a_mdl_dat != 0);

    mDoExt_McaMorf* morf = new mDoExt_McaMorf(
        a_mdl_dat, NULL, NULL,
        (J3DAnmTransform*)dComIfG_getObjectIDRes("Co", 0x10),
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
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Co", 0x14);
    JUT_ASSERT(0x848, a_mdl_dat != 0);

    mDoExt_McaMorf* morf = new mDoExt_McaMorf(
        a_mdl_dat, NULL, NULL,
        (J3DAnmTransform*)dComIfG_getObjectIDRes("Co", 0x07),
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

    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Co", 0x12);
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
        goto error;
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
