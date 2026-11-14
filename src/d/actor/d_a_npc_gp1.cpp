/**
 * d_a_npc_gp1.cpp
 * NPC - Maggie's Father (rich)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_gp1.h"
#include "d/d_com_inf_game.h"
#include "d/d_path.h"
#include "d/d_snap.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"
#include "m_Do/m_Do_mtx.h"
#include "res/Object/Gp.h"
#include "SSystem/SComponent/c_counter.h"

class daNpc_Gp1_HIO_c : public mDoHIO_entry_c {
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
        /* 0x1C */ f32 mForceTalkDist;
        /* 0x20 */ s16 mWalkTurnScale;
        /* 0x22 */ s16 mWalkTurnMaxStep;
        /* 0x24 */ f32 mWalkAnmRate;
        /* 0x28 */ f32 mWalkSpeed;
        /* 0x2C */ f32 mWalkAccel;
        /* 0x30 */ f32 mPassDist;
    };  // Size: 0x34

    daNpc_Gp1_HIO_c();
    virtual ~daNpc_Gp1_HIO_c() {}
    void genMessage(JORMContext* ctx) { UNUSED(ctx); }

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ int m8;
    /* 0x0C */ hio_prm_c mPrm;
};  // Size: 0x40

/* 000000EC-00000150       .text __ct__15daNpc_Gp1_HIO_cFv */
daNpc_Gp1_HIO_c::daNpc_Gp1_HIO_c() {
    static hio_prm_c a_prm_tbl = {
        /* mMaxHeadX        */ 0x2000,
        /* mMaxHeadY        */ 0x2A00,
        /* mMinHeadX        */ -0x0DAC,
        /* mMinHeadY        */ -0x2A00,
        /* mMaxBackboneX    */ 0x0000,
        /* mMaxBackboneY    */ 0x1C00,
        /* mMinBackboneX    */ 0x0000,
        /* mMinBackboneY    */ -0x1C00,
        /* mMaxTurnStep     */ 0x0400,
        /* mMaxHeadTurnVel  */ 0x0400,
        /* mAttPosOffsetY   */ 233.0f,
        /* m18              */ 0,
        /* mForceTalkDist   */ 300.0f,
        /* mWalkTurnScale   */ 6,
        /* mWalkTurnMaxStep */ 0x400,
        /* mWalkAnmRate     */ 0.4f,
        /* mWalkSpeed       */ 3.0f,
        /* mWalkAccel       */ 0.2f,
        /* mPassDist        */ 20.0f,
    };
    memcpy(&mPrm, &a_prm_tbl, sizeof(hio_prm_c));
    mNo = -1;
    m8 = -1;
}

static daNpc_Gp1_HIO_c l_HIO;
static fopAc_ac_c* l_check_inf[20];
static int l_check_wrk;

static char* l_evn_tbl[] = {
    "Kaere_Kaere",
    "Gp1_Get_Itm",
    "Giv_Rupee",
};

/* 00000198-00000210       .text searchActor_Bm__FPvPv */
static void* searchActor_Bm(void* i_actor, void*) {
    if (l_check_wrk < ARRAY_SSIZE(l_check_inf) && fopAc_IsActor(i_actor) && fopAcM_GetName(i_actor) == fpcNm_NPC_BM4_e) {
        l_check_inf[l_check_wrk] = (fopAc_ac_c*)i_actor;
        l_check_wrk++;
    }
    return NULL;
}

/* 00000210-0000025C       .text nodeCallBack_Gp1__FP7J3DNodei */
static BOOL nodeCallBack_Gp1(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        if (j3dSys.getModel()->getUserArea() != 0) {
            ((daNpc_Gp1_c*)j3dSys.getModel()->getUserArea())->nodeGp1Control(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 0000025C-000003AC       .text nodeGp1Control__11daNpc_Gp1_cFP7J3DNodeP8J3DModel */
void daNpc_Gp1_c::nodeGp1Control(J3DNode* i_node, J3DModel* i_model) {
    static cXyz a_eye_pos_off(24.0f, -24.0f, 0.0f);

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

/* 000003E8-00000468       .text init_GP1_0__11daNpc_Gp1_cFv */
bool daNpc_Gp1_c::init_GP1_0() {
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2D01)) {
        set_action(&daNpc_Gp1_c::wait_action1, NULL);
        return true;
    }
    return false;
}

/* 00000468-00000638       .text createInit__11daNpc_Gp1_cFv */
bool daNpc_Gp1_c::createInit() {
    int weight;
    for (int i = 0; i < ARRAY_SSIZE(mEventIdTbl); i++) {
        mEventIdTbl[i] = dComIfGp_evmng_getEventIdx(l_evn_tbl[i], 0xFF);
    }

    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xAB;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xAB;
    gravity = -4.5f;
    mLookPos = current.pos;

    weight = 0xFF;
    u8 path_no = (fopAcM_GetParam(this) >> 16) & 0xFF;
    if (path_no != 0xFF) {
        mPath.setInf(path_no, fopAcM_GetRoomNo(this), true);
        if (mPath.isPath()) {
            fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
            weight = 0xD9;
        } else {
            return false;
        }
    }

    mEventCut.setActorInfo2("Gp1", this);
    mAnmNum = 8;

    bool init_result;
    switch (mType) {
    case 0:
        init_result = init_GP1_0();
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

/* 00000638-00000758       .text setMtx__11daNpc_Gp1_cFb */
void daNpc_Gp1_c::setMtx(bool i_setEyePos) {
    if (!mbDemo) {
        plyTexPttrnAnm();
        mbMorfAnimStopped = mpMorf->play(&eyePos, 0, 0);
        if (mpMorf->getFrame() < mPrevMorfFrame) {
            mbMorfAnimStopped = true;
        }
        mPrevMorfFrame = mpMorf->getFrame();
        ctrl_WAITanm();
        mObjAcch.CrrPos(*dComIfG_Bgsp());
    }
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(mAngle.y);

    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    setAttention(i_setEyePos);
}

/* 00000758-0000076C       .text anmNum_toResID__11daNpc_Gp1_cFi */
int daNpc_Gp1_c::anmNum_toResID(int i_anmNum) {
    static const int a_bck_resID_tbl[] = {
        dRes_ID_GP_BCK_WAIT01_e,
        dRes_ID_GP_BCK_WAIT01_e,
        dRes_ID_GP_BCK_TALK02_e,
        dRes_ID_GP_BCK_TALK03_e,
        dRes_ID_GP_BCK_HAIR_e,
        dRes_ID_GP_BCK_GRIN_e,
        dRes_ID_GP_BCK_GIVE_e,
        dRes_ID_GP_BCK_WALK_e,
    };
    return a_bck_resID_tbl[i_anmNum];
}

/* 0000076C-00000780       .text btpNum_toResID__11daNpc_Gp1_cFi */
int daNpc_Gp1_c::btpNum_toResID(int i_btpNum) {
    static const int a_btp_resID_tbl[] = {
        dRes_ID_GP_BTP_MABA01_e,
    };
    return a_btp_resID_tbl[i_btpNum];
}

/* 00000780-00000890       .text setBtp__11daNpc_Gp1_cFbi */
bool daNpc_Gp1_c::setBtp(bool i_modify, int i_btpNum) {
    J3DModelData* model_data = mpMorf->getModel()->getModelData();
    m_hed_tex_pttrn = (J3DAnmTexPattern*)dComIfG_getObjectIDRes("Gp", btpNum_toResID(i_btpNum));
    JUT_ASSERT(0x1B3, m_hed_tex_pttrn != NULL);

    bool ret = mBtpAnm.init(model_data, m_hed_tex_pttrn, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, i_modify, 0) == 1;
    if (ret) {
        mBtpFrame = 0;
        mBlinkTimer = 0;
    }
    return ret;
}

/* 00000890-000008B8       .text iniTexPttrnAnm__11daNpc_Gp1_cFb */
bool daNpc_Gp1_c::iniTexPttrnAnm(bool i_modify) {
    return setBtp(i_modify, mBtpNum);
}

/* 000008B8-00000964       .text plyTexPttrnAnm__11daNpc_Gp1_cFv */
void daNpc_Gp1_c::plyTexPttrnAnm() {
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

/* 00000964-000009A0       .text setAnm_tex__11daNpc_Gp1_cFSc */
void daNpc_Gp1_c::setAnm_tex(s8 i_btpNum) {
    if (mBtpNum != i_btpNum) {
        mBtpNum = i_btpNum;
        iniTexPttrnAnm(true);
    }
}

/* 000009A0-00000A78       .text setAnm_anm__11daNpc_Gp1_cFPQ211daNpc_Gp1_c9anm_prm_c */
BOOL daNpc_Gp1_c::setAnm_anm(anm_prm_c* i_anmPrmP) {
    if (mAnmNum == i_anmPrmP->mAnmNum) {
        return TRUE;
    }
    mAnmNum = i_anmPrmP->mAnmNum;
    dNpc_setAnmIDRes(mpMorf, i_anmPrmP->mLoopMode, i_anmPrmP->mMorf, i_anmPrmP->mSpeed, anmNum_toResID(mAnmNum), -1, "Gp");
    if (mAnmNum == 0) {
        mWaitTimer = 180.0f + cM_rndF(120.0f);
    }
    mPrevMorfFrame = 0.0f;
    mLoopCount = 0;
    mbMorfAnimStopped = 0;
    return TRUE;
}

/* 00000A78-00000AE4       .text setAnm_NUM__11daNpc_Gp1_cFii */
void daNpc_Gp1_c::setAnm_NUM(int i_anmNum, int i_setBtp) {
    static anm_prm_c a_anm_prm_tbl[9] = {
        {0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {2, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {3, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {4, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {5, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {6, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
    };
    if (i_setBtp) {
        setAnm_tex(a_anm_prm_tbl[i_anmNum].mBtpNum);
    }
    setAnm_anm(&a_anm_prm_tbl[i_anmNum]);
}

/* 00000AE4-00000B64       .text setAnm__11daNpc_Gp1_cFv */
BOOL daNpc_Gp1_c::setAnm() {
    static anm_prm_c a_anm_prm_tbl[6] = {
        {-1, -1, 0.0f, 0.0f, -1},
        {0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {-1, -1, 0.0f, 0.0f, -1},
        {0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {7, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {4, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
    };
    if (a_anm_prm_tbl[mStt].mBtpNum >= 0) {
        setAnm_tex(a_anm_prm_tbl[mStt].mBtpNum);
    }
    if (a_anm_prm_tbl[mStt].mAnmNum >= 0) {
        setAnm_anm(&a_anm_prm_tbl[mStt]);
    }
    return TRUE;
}

/* 00000B64-00000B68       .text chg_anmTag__11daNpc_Gp1_cFv */
void daNpc_Gp1_c::chg_anmTag() {}

/* 00000B68-00000B6C       .text control_anmTag__11daNpc_Gp1_cFv */
void daNpc_Gp1_c::control_anmTag() {}

/* 00000B6C-00000BB0       .text chg_anmAtr__11daNpc_Gp1_cFUc */
void daNpc_Gp1_c::chg_anmAtr(u8 i_atr) {
    if (i_atr >= 7 || i_atr == mAnmAtr) {
        return;
    }
    mAnmAtr = i_atr;
    setAnm_ATR(1);
}

/* 00000BB0-00000D00       .text control_anmAtr__11daNpc_Gp1_cFv */
void daNpc_Gp1_c::control_anmAtr() {
    switch (mAnmAtr) {
    case 1:
        if (mbMorfAnimStopped) {
            mAnmAtr = 0;
            setAnm_NUM(0, 1);
        }
        break;
    case 5:
        if (!mbMorfAnimStopped) {
            if (mpMorf->checkFrame(80.0f)) {
                create_rupee();
                mDoAud_seStart(JA_SE_OBJ_LUPY_OUT, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
                mRupeeNum = 0;
            }
        } else {
            mAnmAtr = 0;
            setAnm_NUM(0, 1);
        }
        break;
    case 6:
        if (mbMorfAnimStopped) {
            if (++mLoopCount >= 2) {
                mAnmAtr = 0;
                setAnm_NUM(0, 1);
            }
        }
        break;
    case 0:
        break;
    }
}

/* 00000D00-00000D68       .text setAnm_ATR__11daNpc_Gp1_cFi */
void daNpc_Gp1_c::setAnm_ATR(int i_setBtp) {
    static anm_prm_c a_anm_prm_tbl[7] = {
        {0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {5, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {2, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {3, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {5, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {6, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {2, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };
    if (i_setBtp != 0) {
        setAnm_tex(a_anm_prm_tbl[mAnmAtr].mBtpNum);
    }
    setAnm_anm(&a_anm_prm_tbl[mAnmAtr]);
}

/* 00000D68-00000E2C       .text anmAtr__11daNpc_Gp1_cFUs */
void daNpc_Gp1_c::anmAtr(u16 i_msgStatus) {
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

/* 00000E2C-00000EC4       .text eventOrder__11daNpc_Gp1_cFv */
void daNpc_Gp1_c::eventOrder() {
    s8 order = mOrder;
    if (order == 1 || order == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
        if (mOrder == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (order >= 3) {
        mEventIdx = order - 3;
        fopAcM_orderOtherEventId(this, mEventIdTbl[mEventIdx]);
    }
}

/* 00000EC4-00000F5C       .text checkOrder__11daNpc_Gp1_cFv */
void daNpc_Gp1_c::checkOrder() {
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

/* 00000F5C-00001008       .text chk_talk__11daNpc_Gp1_cFv */
bool daNpc_Gp1_c::chk_talk() {
    bool ret = true;
    mItemNo = 0xFF;
    if (dComIfGp_event_chkTalkXY()) {
        if (dComIfGp_evmng_ChkPresentEnd()) {
            mItemNo = dComIfGp_event_getPreItemNo();
        } else {
            ret = false;
        }
        mItemNo = dComIfGp_event_getPreItemNo();
    }
    return ret;
}

// Stripped function, only its constant remains in .rodata
static bool dummy_chk_drct(f32 i_angle) {
    return 0 < cM_deg2s(i_angle);
}

/* 00001008-00001048       .text chk_partsNotMove__11daNpc_Gp1_cFv */
bool daNpc_Gp1_c::chk_partsNotMove() {
    return mJointHeadY == m_jnt.getHead_y() && mJointBackboneY == m_jnt.getBackbone_y() && mActorAngleY == current.angle.y;
}

/* 00001048-00001168       .text chk_forceTlkArea__11daNpc_Gp1_cFv */
bool daNpc_Gp1_c::chk_forceTlkArea() {
    f32 dist = (dComIfGp_getPlayer(0)->current.pos - current.pos).absXZ();
    f32 dy = dComIfGp_getPlayer(0)->current.pos.y - current.pos.y;
    bool ret = false;
    if (-1.0f < dy && dy <= 100.0f && dist < l_HIO.mPrm.mForceTalkDist) {
        ret = true;
    }
    return ret;
}

/* 00001168-00001308       .text lookBack__11daNpc_Gp1_cFv */
void daNpc_Gp1_c::lookBack() {
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

/* 00001308-00001504       .text next_msgStatus__11daNpc_Gp1_cFPUl */
u16 daNpc_Gp1_c::next_msgStatus(u32* o_msgNoP) {
    u16 ret = fopMsgStts_MSG_CONTINUES_e;
    s16 beast_num = dComIfGs_getBeastNum(0);
    switch (*o_msgNoP) {
    case 0x1E15:
        *o_msgNoP = 0x1E16;
        break;
    case 0x1E16:
        *o_msgNoP = 0x1E17;
        break;
    case 0x1E17:
        *o_msgNoP = 0x1E18;
        break;
    case 0x1E19:
        *o_msgNoP = 0x1E1A;
        break;
    case 0x1E1A:
        *o_msgNoP = 0x1E1B;
        break;
    case 0x1E1B:
        *o_msgNoP = 0x1E1C;
        break;
    case 0x1E29:
        *o_msgNoP = 0x1E2A;
        mGiveNum = beast_num;
        mbGive = true;
        break;
    case 0x1E2A:
        if (mGiveNum >= 16) {
            *o_msgNoP = 0x1E2D;
            mRupeeNum = 3;
        } else if (mGiveNum >= 6) {
            *o_msgNoP = 0x1E2C;
            mRupeeNum = 2;
        } else {
            *o_msgNoP = 0x1E2B;
            mRupeeNum = 1;
        }
        break;
    case 0x1E20:
        *o_msgNoP = 0x1E21;
        break;
    case 0x1E30:
        *o_msgNoP = 0x1E23;
        break;
    case 0x1E22:
    case 0x1E28:
        *o_msgNoP = 0x1E24;
        mbGive = true;
        mGiveNum = 20;
        break;
    case 0x1E24:
        *o_msgNoP = 0x1E25;
        break;
    case 0x1E26:
        *o_msgNoP = 0x1E27;
        break;
    case 0x1E21:
        if (beast_num >= 20) {
            *o_msgNoP = 0x1E22;
        } else {
            *o_msgNoP = 0x1E30;
        }
        break;
    case 0x1EE6:
        *o_msgNoP = 0x1EE7;
        break;
    case 0x1E23:
    case 0x1E25:
    case 0x1E27:
    default:
        ret = fopMsgStts_MSG_ENDS_e;
        break;
    }
    return ret;
}

/* 00001504-0000166C       .text getMsg_GP1_0__11daNpc_Gp1_cFv */
u32 daNpc_Gp1_c::getMsg_GP1_0() {
    if (mItemNo == 0x45) {
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1420)) {
            return 0x1E29;
        }
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1804)) {
            s16 num = dComIfGs_getBeastNum(0);
            return num >= 20 ? 0x1E28 : 0x1E30;
        }
        return 0x1E20;
    }
    if (mItemNo != 0xFF) {
        return 0x1E2F;
    }
    if (m7FA) {
        m7FA = 0;
        return 0x1E26;
    }
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_1501)) {
        return 0x1E15;
    }
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1808)) {
        if (dComIfGs_checkReserveItem(0x9B)) {
            return 0x1E1D;
        }
        return (dComIfGs_getEventReg(dSv_event_flag_c::UNK_C5FF) < 10 ? 0 : -1) + 0x1E1F;
    }
    return dComIfGs_isEventBit(dSv_event_flag_c::UNK_1920) ? 0x1E1B : 0x1E19;
}

/* 0000166C-000016A8       .text getMsg__11daNpc_Gp1_cFv */
u32 daNpc_Gp1_c::getMsg() {
    u32 msg = 0;
    switch (mType) {
    case 0:
        msg = getMsg_GP1_0();
        break;
    }
    return msg;
}

/* 000016A8-00001728       .text chkAttention__11daNpc_Gp1_cFv */
bool daNpc_Gp1_c::chkAttention() {
    dAttention_c& attention = dComIfGp_getAttention();
    if (attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    }
    return this == attention.ActionTarget(0);
}

/* 00001728-00001790       .text setAttention__11daNpc_Gp1_cFb */
void daNpc_Gp1_c::setAttention(bool i_setEyePos) {
    attention_info.position.set(current.pos.x, current.pos.y + l_HIO.mPrm.mAttPosOffsetY, current.pos.z);

    if (!mbSetEyePos && !i_setEyePos) {
        return;
    }

    eyePos.set(mTransformedEyePos.x, mTransformedEyePos.y, mTransformedEyePos.z);
    eyePos.y += mEyeOffsetY;
}

/* 00001790-000017C4       .text searchByID__11daNpc_Gp1_cFUi */
fopAc_ac_c* daNpc_Gp1_c::searchByID(fpc_ProcID i_procID) {
    fopAc_ac_c* actor_p = NULL;
    fopAcM_SearchByID(i_procID, &actor_p);
    return actor_p;
}

/* 000017C4-00001874       .text partner_srch_sub__11daNpc_Gp1_cFPFPvPv_Pv */
bool daNpc_Gp1_c::partner_srch_sub(void* (*i_searchFunc)(void*, void*)) {
    bool ret = false;
    mPartnerID = fpcM_ERROR_PROCESS_ID_e;
    l_check_wrk = 0;
    for (int i = 0; i < ARRAY_SSIZE(l_check_inf); i++) {
        l_check_inf[i] = NULL;
    }
    fpcM_Search(i_searchFunc, this);
    if (l_check_wrk != 0) {
        mPartnerID = fopAcM_GetID(l_check_inf[0]);
        ret = true;
    }
    return ret;
}

/* 00001874-00001918       .text partner_srch__11daNpc_Gp1_cFv */
void daNpc_Gp1_c::partner_srch() {
    if (mActionState == 1) {
        bool found;
        switch (mStt) {
        case 3:
            found = partner_srch_sub(searchActor_Bm);
            if (found) {
                fopAc_ac_c* partner_p = searchByID(mPartnerID);
                if (partner_p) {
                    current.angle.y = cLib_targetAngleY(&current.pos, &partner_p->current.pos);
                }
            }
            break;
        default:
            found = true;
            break;
        }
        if (found) {
            mActionState++;
        }
    }
}

/* 00001918-000019AC       .text ctrl_WAITanm__11daNpc_Gp1_cFv */
void daNpc_Gp1_c::ctrl_WAITanm() {
    switch (mAnmNum) {
    case 0:
        if (cLib_calcTimer(&mWaitTimer) == 0) {
            setAnm_NUM(4, 1);
        }
        break;
    case 4:
        if (mbMorfAnimStopped) {
            setAnm_NUM(0, 1);
            mpMorf->setMorf(0.0f);
        }
        break;
    }
}

/* 000019AC-00001B1C       .text gp_movPass__11daNpc_Gp1_cFv */
int daNpc_Gp1_c::gp_movPass() {
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

/* 00001B1C-00001B80       .text gp_clcMovSpd__11daNpc_Gp1_cFv */
void daNpc_Gp1_c::gp_clcMovSpd() {
    cLib_addCalcAngleS(&current.angle.y, cLib_targetAngleY(&current.pos, &mTargetPos), l_HIO.mPrm.mWalkTurnScale, l_HIO.mPrm.mWalkTurnMaxStep, 0);
    cLib_chaseF(&speedF, mTargetSpeed, mAccel);
}

/* 00001B80-00001C40       .text gp_nMove__11daNpc_Gp1_cFv */
void daNpc_Gp1_c::gp_nMove() {
    if (mbPassed) {
        mbNoMove = true;
        return;
    }

    switch (mMoveMode) {
    case 1: {
        gp_clcMovSpd();
        f32 rate = speedF * l_HIO.mPrm.mWalkAnmRate;
        if (rate < 0.5f) {
            rate = 0.5f;
        }
        mpMorf->setPlaySpeed(rate);
        switch (gp_movPass()) {
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
    }
}

/* 00001C40-00001ED8       .text create_rupee__11daNpc_Gp1_cFv */
bool daNpc_Gp1_c::create_rupee() {
    cXyz a_scale(0.2f, 0.2f, 0.2f);
    csXyz a_angle(0, 0, 0);
    mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(m_hnd_L_jnt_num));
    cXyz pos;
    pos.x = mDoMtx_stack_c::get()[0][3];
    pos.y = mDoMtx_stack_c::get()[1][3];
    pos.z = mDoMtx_stack_c::get()[2][3];

    int i;
    int cnt = g_Counter.mCounter0;
    for (i = 0; i < mRupeeNum; i++, cnt++) {
        f32 a_ang_tbl[] = {-30.0f, 0.0f, 30.0f};
        s16 ang = a_ang_tbl[cnt % 3] + (cM_rndF(30.0f) - 15.0f);
        s16 d = cM_deg2s(ang);
        a_angle.y = current.angle.y + d;

        fopAc_ac_c* a_actor_p = (fopAc_ac_c*)fopAcM_fastCreateItem(&pos, dItemNo_RED_RUPEE_e, fopAcM_GetRoomNo(this), NULL, NULL, 10.0f + cM_rndFX(3.0f), 33.0f + cM_rndFX(6.0f), -2.0f);
        if (a_actor_p == NULL) {
            break;
        }
        fopAcM_OnStatus(a_actor_p, fopAcStts_UNK4000_e);
        a_actor_p->scale = a_scale;
        a_actor_p->current.angle = a_angle;
        a_actor_p->shape_angle = a_angle;
    }
    return true;
}

/* 00001ED8-00001EF4       .text charDecide__11daNpc_Gp1_cFi */
bool daNpc_Gp1_c::charDecide(int) {
    mHioType = 0;
    mType = -1;
    mType = 0;
    return true;
}

/* 00001EF4-00001F40       .text eInit_INI_KAERE_KAERE___11daNpc_Gp1_cFv */
void daNpc_Gp1_c::eInit_INI_KAERE_KAERE_() {
    fopAc_ac_c* partner_p = searchByID(mPartnerID);
    if (partner_p) {
        dComIfGp_event_setItemPartner(partner_p);
    }
}

/* 00001F40-00001F4C       .text eInit_END_KAERE_KAERE___11daNpc_Gp1_cFv */
void daNpc_Gp1_c::eInit_END_KAERE_KAERE_() {
    current.angle.y = mHomeAngle.y;
}

/* 00001F4C-00001FE0       .text event_actionInit__11daNpc_Gp1_cFi */
void daNpc_Gp1_c::event_actionInit(int i_staffIdx) {
    int* act_no_p = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "ActNo");
    if (act_no_p != NULL) {
        mActNo = *act_no_p;
        mbSetEyePos = FALSE;
        switch (mActNo) {
        case 0:
            eInit_INI_KAERE_KAERE_();
            break;
        case 1:
            eInit_END_KAERE_KAERE_();
            break;
        }
    }
}

/* 00001FE0-00001FF4       .text event_action__11daNpc_Gp1_cFv */
bool daNpc_Gp1_c::event_action() {
    if (mActNo >= 2) {
        return true;
    }
    return true;
}

/* 00001FF4-000020E0       .text privateCut__11daNpc_Gp1_cFi */
void daNpc_Gp1_c::privateCut(int i_staffIdx) {
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

/* 000020E0-00002100       .text endEvent__11daNpc_Gp1_cFv */
void daNpc_Gp1_c::endEvent() {
    dComIfGp_event_reset();
    mAnmAtr = 0xFF;
}

/* 00002100-00002138       .text isEventEntry__11daNpc_Gp1_cFv */
int daNpc_Gp1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName(), NULL);
}

/* 00002138-00002268       .text event_proc__11daNpc_Gp1_cFi */
void daNpc_Gp1_c::event_proc(int i_staffIdx) {
    if (dComIfGp_evmng_endCheck(mEventIdTbl[mEventIdx])) {
        switch (mEventIdx) {
        case 0:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_1808);
            fopAcM_OnStatus(this, fopAcStts_NOCULLEXEC_e);
            setStt(1);
            mWalkTimer = 0;
            mWalkCount = (g_Counter.mCounter0 & 3) + 2;
            break;
        case 1:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_1420);
            mOrder = 1;
            m7FA = 1;
            break;
        case 2:
            setStt(1);
            break;
        }
        endEvent();
        return;
    }

    if (!mEventCut.cutProc()) {
        privateCut(i_staffIdx);
    }
    lookBack();
}

/* 00002268-00002314       .text set_action__11daNpc_Gp1_cFM11daNpc_Gp1_cFPCvPvPv_iPv */
BOOL daNpc_Gp1_c::set_action(ProcFunc i_newProcFunc, void* i_argsP) {
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

/* 00002314-0000240C       .text setStt__11daNpc_Gp1_cFSc */
void daNpc_Gp1_c::setStt(s8 i_stt) {
    u8 prev_stt = mStt;
    mTalkTimer = 0;
    mStt = i_stt;
    switch (mStt) {
    case 1:
        mWalkTimer = 90;
        break;
    case 2:
        mAnmAtr = 0xFF;
        mLookMode = 1;
        m_jnt.setTrn();
        mPrevStt = prev_stt;
        return;
    case 4:
        mLookMode = 0;
        mMoveMode = 1;
        mWalkTimer = 180.0f + cM_rndF(120.0f);
        mTargetSpeed = l_HIO.mPrm.mWalkSpeed;
        mAccel = l_HIO.mPrm.mWalkAccel;
        mPassDist = l_HIO.mPrm.mPassDist;
        break;
    case 5:
        mLookMode = 0;
        break;
    case 3:
        break;
    }
    setAnm();
}

/* 0000240C-0000255C       .text wait_1__11daNpc_Gp1_cFv */
BOOL daNpc_Gp1_c::wait_1() {
    mWaitTimer = 180.0f + cM_rndF(120.0f);

    if (mbTalkReq && mAnmNum != 4) {
        if (chk_talk()) {
            setStt(2);
            mbHeadOnly = false;
        }
        return TRUE;
    }

    if (mOrder != 1 && mOrder < 3) {
        mOrder = 2;
    }

    if (chk_forceTlkArea() || mbAttention) {
        mTalkTimer = 60;
    }

    if (cLib_calcTimer(&mTalkTimer) != 0) {
        mLookMode = 1;
        return TRUE;
    }

    if (cLib_calcTimer(&mWalkTimer) == 0) {
        setStt(4);
        return TRUE;
    }

    mLookMode = 2;
    mLookPos.set(-2.0f, eyePos.y, 940.0f);
    m_jnt.setTrn();
    return TRUE;
}

/* 0000255C-00002724       .text talk_1__11daNpc_Gp1_cFv */
BOOL daNpc_Gp1_c::talk_1() {
    BOOL res = chk_partsNotMove();
    fopNpc_npc_c::talk(1);
    if (mpCurrMsg != NULL) {
        switch (mpCurrMsg->mStatus) {
        case fopMsgStts_MSG_DESTROYED_e:
            switch (mCurrMsgNo) {
            case 0x1E18:
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_1501);
                break;
            case 0x1E1C:
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_1920);
                break;
            case 0x1E23:
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_1804);
                break;
            case 0x1E25:
                mOrder = 4;
                break;
            case 0x1E2B:
            case 0x1E2C:
            case 0x1E2D:
                mOrder = 5;
                break;
            }
            mItemNo = 0xFF;
            mbTalkReq = false;
            setStt(mPrevStt);
            mTalkTimer = 60;
            endEvent();
            break;
        case fopMsgStts_BOX_OPENING_e:
        case fopMsgStts_MSG_TYPING_e:
            if (mbGive) {
                dComIfGp_evmng_CancelPresent();
                if (mGiveNum != 0) {
                    int reg = dComIfGs_getEventReg(dSv_event_flag_c::UNK_C5FF);
                    dComIfGp_setItemBeastNumCount(0, -mGiveNum);
                    dComIfGs_setEventReg(dSv_event_flag_c::UNK_C5FF, reg + mGiveNum > 127 ? 127 : reg + mGiveNum);
                }
                mbGive = false;
            }
            break;
        }
    }
    return res;
}

/* 00002724-0000288C       .text walk_1__11daNpc_Gp1_cFv */
BOOL daNpc_Gp1_c::walk_1() {
    if (mbTalkReq || chk_forceTlkArea() || cLib_calcTimer(&mWalkTimer) == 0) {
        mTargetSpeed = 0.0f;
    }

    if (mOrder != 1 && mOrder < 3) {
        mOrder = 2;
    }

    if (mbPassed) {
        mbPassed = false;
        if (mMoveMode == 0) {
            mPath.setIdx(0);
            mMoveMode = 1;
        }
    }

    u8 idx = mPath.getIdx();
    mTargetPos = mPath.getPoint(idx);

    if ((int)mTargetSpeed == 0 && (int)speedF == 0) {
        if (mbTalkReq || cLib_calcTimer(&mWalkCount) != 0) {
            setStt(1);
        } else {
            setStt(5);
            mWalkCount = (g_Counter.mCounter0 & 3) + 2;
        }
        speedF = 0.0f;
        mAccel = 0.0f;
        mMoveMode = 0;
    }
    return TRUE;
}

/* 0000288C-00002930       .text hair_1__11daNpc_Gp1_cFv */
BOOL daNpc_Gp1_c::hair_1() {
    if (mbMorfAnimStopped) {
        if (mbTalkReq || chk_forceTlkArea()) {
            setStt(1);
            return TRUE;
        }
        setStt(4);
        return TRUE;
    }

    if (!mbTalkReq && mOrder != 1 && mOrder < 3) {
        mOrder = 2;
    }
    return TRUE;
}

/* 00002930-00002988       .text wait_2__11daNpc_Gp1_cFv */
BOOL daNpc_Gp1_c::wait_2() {
    if (mOrder != 1 && mOrder < 3) {
        f32 dy = dComIfGp_getPlayer(0)->current.pos.y - current.pos.y;
        mOrder = 0;
        if (dy > -1.0f) {
            mOrder = 3;
        }
    }
    return TRUE;
}

/* 00002988-00002B2C       .text wait_action1__11daNpc_Gp1_cFPv */
BOOL daNpc_Gp1_c::wait_action1(void*) {
    switch (mActionState) {
    case 0:
        if (dNpc_chkArasoi()) {
            fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
            setStt(3);
        } else {
            fopAcM_OnStatus(this, fopAcStts_NOCULLEXEC_e);
            setStt(1);
            mWalkCount = (g_Counter.mCounter0 & 3) + 2;
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
        case 1:
            mbSetEyePos = wait_1();
            break;
        case 2:
            mbSetEyePos = talk_1();
            break;
        case 4:
            mbSetEyePos = walk_1();
            break;
        case 5:
            mbSetEyePos = hair_1();
            break;
        case 3:
            mbSetEyePos = wait_2();
            break;
        }
        if (mOrder != 1 && mOrder < 3 && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_1501) && !mbTalkReq && chk_forceTlkArea()) {
            mOrder = 1;
        }
        lookBack();
        break;
    default:
        break;
    }
    return TRUE;
}

/* 00002B2C-00002C6C       .text demo__11daNpc_Gp1_cFv */
bool daNpc_Gp1_c::demo() {
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
        J3DAnmTexPattern* demo_btp_p = demo_actor_p->getP_BtpData("Gp");
        if (demo_btp_p) {
            m_hed_tex_pttrn = demo_btp_p;
            if (mBtpAnm.init(mpMorf->getModel()->getModelData(), m_hed_tex_pttrn, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, FALSE)) {
                mBtpNum = 1;
                mBtpFrame = 0;
            }
        }
        dDemo_setDemoData(this, 0x6A, mpMorf, "Gp");
    }
    return mbDemo;
}

static void dummy() {
    const GXColor dummy1 = {0xFF, 0x00, 0x00, 0x80};
    const GXColor dummy2 = {0x00, 0x00, 0xFF, 0x80};
    const GXColor dummy3 = {0x00, 0xFF, 0x00, 0x80};
    const GXColor dummy4 = {0x00, 0xFF, 0x00, 0x80};
}

/* 00002C6C-00002E24       .text _draw__11daNpc_Gp1_cFv */
BOOL daNpc_Gp1_c::_draw() {
    J3DModel* model = mpMorf->getModel();
    J3DModelData* model_data = model->getModelData();

    if (mbHide || m7FF) {
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(model, &tevStr);

    mBtpAnm.entry(model_data, mBtpFrame);
    mpMorf->entryDL();
    mBtpAnm.remove(model_data);

    dNpc_setShadowModel(mpShadowModel, model_data, model);
    cXyz pos(current.pos.x, current.pos.y + 150.0f, current.pos.z);
    mShadowID = dComIfGd_setRealShadow(mShadowID, 1, mpShadowModel, &pos, 800.0f, current.pos.y - mObjAcch.GetGroundH(), NULL);
    if (mShadowID == 0) {
        dComIfGd_setSimpleShadow(&current.pos, mObjAcch.GetGroundH(), 40.0f, &dComIfG_Bgsp()->GetTriPla(mObjAcch.m_gnd)->mNormal);
    }

    if (l_HIO.mPrm.m18 != 0) {
        cXyz dummy = current.pos;
        dummy.y = eyePos.y;
    }

    dSnap_RegistFig(DSNAP_TYPE_UNK5B, this, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 00002E24-00003008       .text _execute__11daNpc_Gp1_cFv */
BOOL daNpc_Gp1_c::_execute() {
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
            gp_nMove();
            fopAcM_posMoveF(this, mStts.GetCCMoveP());
        }
        if (!m7FD) {
            mAngle = current.angle;
            shape_angle = mAngle;
        }
    }
    eventOrder();
    setMtx(false);
    if (!mbDemo) {
        setCollision(70.0f, 230.0f);
    }
    return TRUE;
}

/* 00003008-00003064       .text _delete__11daNpc_Gp1_cFv */
BOOL daNpc_Gp1_c::_delete() {
    dComIfG_resDelete(&mPhs, "Gp");
    if (heap != NULL && mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }
    return TRUE;
}

/* 00003064-00003084       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Gp1_c*)i_this)->CreateHeap();
}

daNpc_Gp1_c::daNpc_Gp1_c() {}

/* 00003084-000031A4       .text _create__11daNpc_Gp1_cFv */
cPhs_State daNpc_Gp1_c::_create() {
    static int a_size_tbl[] = {
        0x272E0,
    };

    fopAcM_ct(this, daNpc_Gp1_c);
    cPhs_State state = dComIfG_resLoad(&mPhs, "Gp");
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
    fopAcM_setCullSizeBox(this, -70.0f, -20.0f, -70.0f, 50.0f, 240.0f, 50.0f);
    if (!createInit()) {
        return cPhs_ERROR_e;
    }
    return state;
}

/* 000035D4-00003844       .text create_Anm__11daNpc_Gp1_cFv */
J3DModelData* daNpc_Gp1_c::create_Anm() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Gp", dRes_ID_GP_BDL_GP_e);
    JUT_ASSERT(0x86F, a_mdl_dat != NULL);
    mpMorf = new mDoExt_McaMorf(
        a_mdl_dat, NULL, NULL, (J3DAnmTransform*)dComIfG_getObjectIDRes("Gp", dRes_ID_GP_BCK_WAIT01_e),
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
    JUT_ASSERT(0x883, m_hed_jnt_num >= 0);
    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(0x886, m_bbone_jnt_num >= 0);
    m_hnd_L_jnt_num = a_mdl_dat->getJointName()->getIndex("handL");
    JUT_ASSERT(0x889, m_hnd_L_jnt_num >= 0);

    return a_mdl_dat;
}

/* 00003844-000039A0       .text CreateHeap__11daNpc_Gp1_cFv */
BOOL daNpc_Gp1_c::CreateHeap() {
    J3DModelData* a_mdl_dat = create_Anm();
    if (!a_mdl_dat) {
        return FALSE;
    }
    mBtpNum = 0;
    if (!iniTexPttrnAnm(false)) {
        mpMorf = NULL;
        return FALSE;
    }
    mpShadowModel = mDoExt_J3DModel__create(a_mdl_dat, 0x20000, 0x11020203);
    if (mpShadowModel != NULL) {
        for (u16 i = 0; i < a_mdl_dat->getJointNum(); i++) {
            if (i == m_hed_jnt_num || i == m_bbone_jnt_num) {
                mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Gp1);
            }
        }
        mpMorf->getModel()->setUserArea((uintptr_t)this);
        mAcchCir.SetWall(30.0f, 70.0f);
        mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this), NULL, NULL);
        return TRUE;
    }
    mpMorf = NULL;
    return FALSE;
}

/* 000039A0-000039C0       .text daNpc_Gp1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Gp1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Gp1_c*)i_this)->_create();
}

/* 000039C0-000039E0       .text daNpc_Gp1_Delete__FP11daNpc_Gp1_c */
static BOOL daNpc_Gp1_Delete(daNpc_Gp1_c* i_this) {
    return ((daNpc_Gp1_c*)i_this)->_delete();
}

/* 000039E0-00003A00       .text daNpc_Gp1_Execute__FP11daNpc_Gp1_c */
static BOOL daNpc_Gp1_Execute(daNpc_Gp1_c* i_this) {
    return ((daNpc_Gp1_c*)i_this)->_execute();
}

/* 00003A00-00003A20       .text daNpc_Gp1_Draw__FP11daNpc_Gp1_c */
static BOOL daNpc_Gp1_Draw(daNpc_Gp1_c* i_this) {
    return ((daNpc_Gp1_c*)i_this)->_draw();
}

/* 00003A20-00003A28       .text daNpc_Gp1_IsDelete__FP11daNpc_Gp1_c */
static BOOL daNpc_Gp1_IsDelete(daNpc_Gp1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Gp1_Method = {
    (process_method_func)daNpc_Gp1_Create,
    (process_method_func)daNpc_Gp1_Delete,
    (process_method_func)daNpc_Gp1_Execute,
    (process_method_func)daNpc_Gp1_IsDelete,
    (process_method_func)daNpc_Gp1_Draw,
};

actor_process_profile_definition g_profile_NPC_GP1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_GP1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Gp1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_GP1_e,
    /* Actor SubMtd */ &l_daNpc_Gp1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
