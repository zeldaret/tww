/**
 * d_a_npc_ac1.cpp
 * NPC - Prince Komali (after Dragon Roost Cavern)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_ac1.h"
#include "d/d_snap.h"
#include "m_Do/m_Do_hostIO.h"
#include "res/Object/Ac.h"

class daNpc_Ac1_HIO_c : public mDoHIO_entry_c {
public:
    daNpc_Ac1_HIO_c();
    virtual ~daNpc_Ac1_HIO_c() {
    }
    void genMessage(JORMContext* ctx) {
        UNUSED(ctx);
    }

public:
    /* 0x04 */ s8 field_0x04;
    /* 0x05 */ u8 field_0x05[0x08 - 0x05];
    /* 0x08 */ s32 field_0x08;
    /* 0x0C */ s16 mMaxHeadX;
    /* 0x0E */ s16 mMaxHeadY;
    /* 0x10 */ s16 mMinHeadX;
    /* 0x12 */ s16 mMinHeadY;
    /* 0x14 */ s16 mMaxBackboneX;
    /* 0x16 */ s16 mMaxBackboneY;
    /* 0x18 */ s16 mMinBackboneX;
    /* 0x1A */ s16 mMinBackboneY;
    /* 0x1C */ s16 mMaxTurnStep;
    /* 0x1E */ s16 mCalcAngleTarget;
    /* 0x20 */ f32 mAttPosOffsetY;
    /* 0x24 */ u8 field_0x24[0x3C - 0x24];
}; // Size: 0x3C

static daNpc_Ac1_HIO_c l_HIO;
static fopAc_ac_c* l_check_inf[20];
static s32 l_check_wrk = 0;

/* 000000EC-00000150       .text __ct__15daNpc_Ac1_HIO_cFv */
daNpc_Ac1_HIO_c::daNpc_Ac1_HIO_c() {
    static u32 a_prm_tbl[] = { 0x20002710, 0xF000D8F0, 0x00001770, 0x0000E890, 0x07080578, 0x43160000,
                               0x00000006, 0x04000000, 0x3F000000, 0x40400000, 0x3DCCCCCD, 0x42200000 };
    memcpy(&mMaxHeadX, a_prm_tbl, 0x30);
    field_0x04 = -1;
    field_0x08 = -1;
}

/* 00000198-000001E4       .text nodeCallBack_Wng__FP7J3DNodei */
static BOOL nodeCallBack_Wng(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        if (j3dSys.getModel()->getUserArea() != NULL) {
            reinterpret_cast<daNpc_Ac1_c*>(j3dSys.getModel()->getUserArea())->nodeWngControl(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 000001E4-00000294       .text nodeWngControl__11daNpc_Ac1_cFP7J3DNodeP8J3DModel */
void daNpc_Ac1_c::nodeWngControl(J3DNode* i_node, J3DModel* i_model) {
    s32 jntNo = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jntNo));
    if (jntNo == m_wngL1_jnt_num) {
        cMtx_copy(mLeftArmMtx, j3dSys.mCurrentMtx);
        i_model->setAnmMtx(jntNo, mLeftArmMtx);
    }
    if (jntNo == m_wngR1_jnt_num) {
        cMtx_copy(mRightArmMtx, j3dSys.mCurrentMtx);
        i_model->setAnmMtx(jntNo, mRightArmMtx);
    }
}

/* 00000294-000002E0       .text nodeCallBack_Arm__FP7J3DNodei */
static BOOL nodeCallBack_Arm(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        if (j3dSys.getModel()->getUserArea() != NULL) {
            reinterpret_cast<daNpc_Ac1_c*>(j3dSys.getModel()->getUserArea())->nodeArmControl(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 000002E0-00000390       .text nodeArmControl__11daNpc_Ac1_cFP7J3DNodeP8J3DModel */
void daNpc_Ac1_c::nodeArmControl(J3DNode* i_node, J3DModel* i_model) {
    s32 uVar1 = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(uVar1));
    if (uVar1 == m_armL1_jnt_num) {
        cMtx_copy(mLeftArmMtx, j3dSys.mCurrentMtx);
        i_model->setAnmMtx(uVar1, mLeftArmMtx);
    }
    if (uVar1 == m_armR1_jnt_num) {
        cMtx_copy(mRightArmMtx, j3dSys.mCurrentMtx);
        i_model->setAnmMtx(uVar1, mRightArmMtx);
    }
}

/* 00000390-000003DC       .text nodeCallBack_Ac1__FP7J3DNodei */
static BOOL nodeCallBack_Ac1(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        if (j3dSys.getModel()->getUserArea() != NULL) {
            reinterpret_cast<daNpc_Ac1_c*>(j3dSys.getModel()->getUserArea())->nodeAc1Control(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 000003DC-0000056C       .text nodeAc1Control__11daNpc_Ac1_cFP7J3DNodeP8J3DModel */
void daNpc_Ac1_c::nodeAc1Control(J3DNode* i_node, J3DModel* i_model) {
    static cXyz a_eye_pos_off(20.0f, 18.0f, 0.0f);
    s32 jntNo = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jntNo));
    if (jntNo == m_hed_jnt_num) {
        mDoMtx_stack_c::XrotM(m_jnt.getHead_y());
        mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
        mDoMtx_stack_c::multVec(&a_eye_pos_off, &mEyePos);
    }
    if (jntNo == m_bbone_jnt_num) {
        mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
        mDoMtx_stack_c::ZrotM(-m_jnt.getBackbone_x());
    }
    if (jntNo == m_arm_L_jnt_num) {
        cMtx_copy(mDoMtx_stack_c::get(), mLeftArmMtx);
    }
    if (jntNo == m_arm_R_jnt_num) {
        cMtx_copy(mDoMtx_stack_c::get(), mRightArmMtx);
    }
    cMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
}

/* 000005A8-00000640       .text init_AC1_0__11daNpc_Ac1_cFv */
bool daNpc_Ac1_c::init_AC1_0() {
    bool res = dComIfGs_isEventBit(dSv_event_flag_c::UNK_2E04) != FALSE;
    if (res) {
        dComIfGs_isEventBit(dSv_event_flag_c::UNK_1580);
        set_action(&daNpc_Ac1_c::wait_action1, NULL);
    }
    return res;
}

/* 00000640-000007C8       .text createInit__11daNpc_Ac1_cFv */
bool daNpc_Ac1_c::createInit() {
    attention_info.flags = fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_LOCKON_TALK_e;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xA9;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xA9;
    gravity = -4.5f;
    mLookAtPos = current.pos;
    if (((fopAcM_GetParam(this) >> 16) & 0xFF) != 0xFF) {
        mPathRun.setInf((fopAcM_GetParam(this) >> 16) & 0xFF, fopAcM_GetRoomNo(this), true);

        if (mPathRun.isPath()) {
            fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
        } else {
            return false;
        }
    }
    mEventCut.setActorInfo2("Ac1", this);
    mAnmNum = 4;

    bool init_success;
    switch (mSpecificType) {
        case 0:
            init_success = init_AC1_0();
            break;
        default:
            init_success = false;
            break;
    }

    if (init_success) {
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

/* 000007C8-00000988       .text setMtx__11daNpc_Ac1_cFb */
void daNpc_Ac1_c::setMtx(bool i_setEyePos) {

    if (mbInDemo == 0) {
        plyTexPttrnAnm();
        mbMorfAnimStopped = mpMorf->play(&eyePos, 0, 0);
        if (mpMorf->getFrame() < mFrame) {
            mbMorfAnimStopped = true;
        }
        mFrame = mpMorf->getFrame();
        if (mbHasArms) {
            mpArmMorf->play(&eyePos, 0, 0);
        } else {
            mpWingMorf->play(&eyePos, 0, 0);
        }
        mObjAcch.CrrPos(*dComIfG_Bgsp());
    }
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
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

/* 00000988-0000099C       .text anmNum_toResID__11daNpc_Ac1_cFi */
u32 daNpc_Ac1_c::anmNum_toResID(int i_idx) {
    static const u32 a_bck_resID_tbl[] = {
        dRes_ID_AC_BCK_AC_WAIT01_e,
        dRes_ID_AC_BCK_AC_TALK01_e,
        dRes_ID_AC_BCK_AC_TALK02_e,
        dRes_ID_AC_BCK_AC_WAIT02_e,
    };
    return a_bck_resID_tbl[i_idx];
}

/* 0000099C-000009B0       .text wingAnmNum_toResID__11daNpc_Ac1_cFi */
u32 daNpc_Ac1_c::wingAnmNum_toResID(int i_idx) {
    static const u32 a_bck_resID_tbl[] = {
        dRes_ID_AC_BCK_ACARM_WAIT01_e,
        dRes_ID_AC_BCK_ACARM_TALK01_e,
        dRes_ID_AC_BCK_ACARM_TALK02_e,
        dRes_ID_AC_BCK_ACARM_WAIT02_e,
    };
    return a_bck_resID_tbl[i_idx];
}

/* 000009B0-000009C4       .text btpNum_toResID__11daNpc_Ac1_cFi */
u32 daNpc_Ac1_c::btpNum_toResID(int i_idx) {
    static const u32 a_btp_resID_tbl[] = {
        dRes_ID_AC_BTP_MABA_e,
        dRes_ID_AC_BTP_KOMARI_e,
        dRes_ID_AC_BTP_WARAI_e,
    };
    return a_btp_resID_tbl[i_idx];
}

/* 000009C4-00000AD4       .text setBtp__11daNpc_Ac1_cFbi */
bool daNpc_Ac1_c::setBtp(bool i_modify, int i_btpNum) {
    J3DModelData* model_data = mpMorf->getModel()->getModelData();
    int resID = btpNum_toResID(i_btpNum);
    m_hed_tex_pttrn = reinterpret_cast<J3DAnmTexPattern*>(dComIfG_getObjectIDRes("Ac", resID));
    JUT_ASSERT(0x216, m_hed_tex_pttrn != NULL);
    int initVal = mBtpAnim.init(model_data, m_hed_tex_pttrn, 1, 2, 1.0f, 0, -1, i_modify, 0);
    bool o_retval = initVal == 1;
    if (o_retval) {
        mBlinkFrame = 0;
        mBlinkTimer = 0;
    }
    return o_retval;
}

/* 00000AD4-00000AFC       .text iniTexPttrnAnm__11daNpc_Ac1_cFb */
bool daNpc_Ac1_c::iniTexPttrnAnm(bool i_modify) {
    return setBtp(i_modify, mBtpNum);
}

/* 00000AFC-00000BA8       .text plyTexPttrnAnm__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::plyTexPttrnAnm() {
    if (mBtpNum != 0 || !cLib_calcTimer(&mBlinkTimer)) {
        mBlinkFrame += 1;
        if (mBlinkFrame >= m_hed_tex_pttrn->getFrameMax()) {
            if (mBtpNum != 0) {
                mBlinkFrame = m_hed_tex_pttrn->getFrameMax();
            } else {
                mBlinkTimer = cM_rndF(60.0f) + 30.0f;
                mBlinkFrame = 0;
            }
        }
    }
}

/* 00000BA8-00000BE4       .text setAnm_tex__11daNpc_Ac1_cFSc */
void daNpc_Ac1_c::setAnm_tex(s8 i_param1) {
    if (mBtpNum != i_param1) {
        mBtpNum = i_param1;
        iniTexPttrnAnm(true);
    }
}

/* 00000BE4-00000D0C       .text setAnm_anm__11daNpc_Ac1_cFPQ211daNpc_Ac1_c9anm_prm_c */
BOOL daNpc_Ac1_c::setAnm_anm(daNpc_Ac1_c::anm_prm_c* i_anmPrmP) {
    if (mAnmNum == i_anmPrmP->anmNum) {
        return TRUE;
    }
    mAnmNum = i_anmPrmP->anmNum;
    dNpc_setAnmIDRes(mpMorf, i_anmPrmP->loopMode, i_anmPrmP->morf, i_anmPrmP->speed, anmNum_toResID(mAnmNum), -1, "Ac");
    u32 wingAnmNum = wingAnmNum_toResID(mAnmNum);
    mbHasArms = i_anmPrmP->hasArms == 1;
    if (mbHasArms) {
        dNpc_setAnmIDRes(mpArmMorf, i_anmPrmP->loopMode, i_anmPrmP->morf, i_anmPrmP->speed, wingAnmNum, -1, "Ac");
    } else {
        dNpc_setAnmIDRes(mpWingMorf, i_anmPrmP->loopMode, i_anmPrmP->morf, i_anmPrmP->speed, wingAnmNum, -1, "Ac");
    }
    mFrame = 0.0f;
    field_0x859 = 0;
    mbMorfAnimStopped = false;
    return TRUE;
}

/* 00000D0C-00000D8C       .text setAnm__11daNpc_Ac1_cFv */
bool daNpc_Ac1_c::setAnm() {
    static anm_prm_c a_anm_prm_tbl[] = { { -1, -1, 0.0f, 0.0f, -1, -1 }, { 0, 0, 8.0f, 1.0f, 2, 1 }, { -1, -1, 0.0f, 0.0f, -1, -1 } };
    if (a_anm_prm_tbl[mStatus].btpNum >= 0) {
        setAnm_tex(a_anm_prm_tbl[mStatus].btpNum);
    }
    if (a_anm_prm_tbl[mStatus].anmNum >= 0) {
        setAnm_anm(&a_anm_prm_tbl[mStatus]);
    }
    return true;
}

/* 00000D8C-00000D90       .text chg_anmTag__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::chg_anmTag() {
    return;
}

/* 00000D90-00000D94       .text control_anmTag__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::control_anmTag() {
    return;
}

/* 00000D94-00000DD8       .text chg_anmAtr__11daNpc_Ac1_cFUc */
void daNpc_Ac1_c::chg_anmAtr(u8 i_param1) {
    if (i_param1 >= 6 || i_param1 == mAnmAtr) {
        return;
    }
    mAnmAtr = i_param1;
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
void daNpc_Ac1_c::setAnm_ATR(int i_param1) {
    static anm_prm_c a_anm_prm_tbl[] = { { 0, 0, 8.0f, 1.0f, 2, 1 }, { 1, 0, 8.0f, 1.0f, 2, 1 }, { 2, 1, 8.0f, 1.0f, 2, 1 },
                                         { 3, 0, 8.0f, 1.0f, 2, 1 }, { 1, 2, 8.0f, 1.0f, 2, 1 }, { 1, 1, 8.0f, 1.0f, 2, 1 } };
    if (i_param1) {
        setAnm_tex(a_anm_prm_tbl[mAnmAtr].btpNum);
    }
    setAnm_anm(&a_anm_prm_tbl[mAnmAtr]);
}

/* 00000E4C-00000F10       .text anmAtr__11daNpc_Ac1_cFUs */
void daNpc_Ac1_c::anmAtr(u16 i_param1) {
    switch (i_param1) {
        case 0x6:
            {
                if (field_0x87B == 0) {
                    mAnmAtr = -1;
                    chg_anmAtr(dComIfGp_getMesgAnimeAttrInfo());
                    field_0x87B++;
                }
                u32 tagInfo = dComIfGp_getMesgAnimeTagInfo();
                dComIfGp_clearMesgAnimeTagInfo();
                if (tagInfo != 0xFF && mAnmTag != tagInfo) {
                    mAnmTag = tagInfo;
                    chg_anmTag();
                }
                break;
            }
        case 0xE:
            field_0x87B = 0;
            break;
    }
    control_anmTag();
    control_anmAtr();
}

/* 00000F10-00000F60       .text eventOrder__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::eventOrder() {
    if (mTalkOrder == 1 || mTalkOrder == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (mTalkOrder == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    }
}

/* 00000F60-00000FA0       .text checkOrder__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        return;
    }
    if (!eventInfo.checkCommandTalk()) {
        return;
    }
    if (mTalkOrder != 1 && mTalkOrder != 2) {
        return;
    }
    mTalkOrder = 0;
    mbTalking = true;
}

/* 00000FA0-0000103C       .text chk_talk__11daNpc_Ac1_cFv */
bool daNpc_Ac1_c::chk_talk() {
    bool uVar3 = true;
    mItemNo = 0xFF;
    if (dComIfGp_event_chkTalkXY()) {
        if (dComIfGp_evmng_ChkPresentEnd()) {
            mItemNo = dComIfGp_event_getPreItemNo();
        } else {
            uVar3 = false;
        }
    }

    return uVar3;
}

/* 0000103C-0000107C       .text chk_partsNotMove__11daNpc_Ac1_cFv */
bool daNpc_Ac1_c::chk_partsNotMove() {
    return mPrevHeadY == m_jnt.getHead_y() && mPrevBackboneY == m_jnt.getBackbone_y() && mPrevAngleY == current.angle.y;
}

/* 0000107C-0000121C       .text lookBack__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::lookBack() {
    cXyz dstPos;
    cXyz* dstPos_p;
    cXyz src_pos;
    s16 desiredYrot;
    mPrevHeadY = m_jnt.getHead_y();
    mPrevBackboneY = m_jnt.getBackbone_y();
    mPrevAngleY = current.angle.y;
    src_pos.x = current.pos.x;
    src_pos.y = current.pos.y;
    src_pos.z = current.pos.z;
    src_pos.y = eyePos.y;
    dstPos.set(0.0f, 0.0f, 0.0f);
    dstPos_p = NULL;
    desiredYrot = current.angle.y;
    bool headOnlyFollow = mbHeadOnlyFollow;

    switch (mLookBackState) {
        case 1:
            dstPos = dNpc_playerEyePos(-20.0f);
            dstPos_p = &dstPos;
            src_pos.x = current.pos.x;
            src_pos.y = current.pos.y;
            src_pos.z = current.pos.z;
            src_pos.y = eyePos.y;
            break;
        case 2:
            dstPos = mLookAtPos;
            dstPos_p = &dstPos;
            src_pos.x = current.pos.x;
            src_pos.y = current.pos.y;
            src_pos.z = current.pos.z;
            src_pos.y = eyePos.y;
            break;
        case 3:
            desiredYrot = field_0x854;
            break;
    }
    cLib_addCalcAngleS2(&mHeadLookAtMaxVel, l_HIO.mCalcAngleTarget, 4, 0x800);
    if (!m_jnt.trnChk()) {
        mHeadLookAtMaxVel = 0;
    }
    m_jnt.lookAtTarget(&current.angle.y, dstPos_p, src_pos, desiredYrot, mHeadLookAtMaxVel, headOnlyFollow);
}

/* 0000121C-0000128C       .text next_msgStatus__11daNpc_Ac1_cFPUl */
u16 daNpc_Ac1_c::next_msgStatus(u32* i_msg_no) {
    u16 msg_status = fopMsgStts_MSG_CONTINUES_e;
    switch (*i_msg_no) {
        case 0x184C:
            *i_msg_no = 0x184D;
            break;
        case 0x184D:
            *i_msg_no = 0x184E;
            break;
        case 0x1850:
            *i_msg_no = 0x1851;
            break;
        case 0x1851:
            *i_msg_no = 0x1852;
            break;
        default:
            msg_status = fopMsgStts_MSG_ENDS_e;
            break;
    }
    return msg_status;
}

/* 0000128C-000012AC       .text getBitMask__11daNpc_Ac1_cFv */
s8 daNpc_Ac1_c::getBitMask() {
    s8 ret = 0;
    switch (mSpecificType) {
        case 0:
            ret = 0x10;
            break;
    }
    return ret;
}

/* 000012AC-00001380       .text getMsg_AC1_0__11daNpc_Ac1_cFv */
u32 daNpc_Ac1_c::getMsg_AC1_0() {
    s8 reg = dComIfGs_getEventReg(dSv_event_flag_c::UNK_B8FF);
    s8 mask = getBitMask();
    u16 i_no;
    u32 ret;
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1580)) {
        if (mask & reg) {
            ret = 0x1853;
        } else {
            i_no = reg | mask;
            dComIfGs_setEventReg(dSv_event_flag_c::UNK_B8FF, i_no);
            ret = 0x1850;
        }
    } else {
        if (mask & reg) {
            ret = 0x184F;
        } else {
            i_no = reg | mask;
            dComIfGs_setEventReg(dSv_event_flag_c::UNK_B8FF, i_no);
            ret = 0x184C;
        }
    }
    return ret;
}

/* 00001380-000013BC       .text getMsg__11daNpc_Ac1_cFv */
u32 daNpc_Ac1_c::getMsg() {
    u32 o_retval = 0;
    switch (mSpecificType) {
        case 0:
            o_retval = getMsg_AC1_0();
            break;
    }
    return o_retval;
}

/* 000013BC-0000143C       .text chkAttention__11daNpc_Ac1_cFv */
bool daNpc_Ac1_c::chkAttention() {
    dAttention_c& attention = dComIfGp_getAttention();
    if (attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    } else {
        return this == attention.ActionTarget(0);
    }
}

/* 0000143C-00001494       .text setAttention__11daNpc_Ac1_cFb */
void daNpc_Ac1_c::setAttention(bool i_setEyePos) {
    f32 offset = l_HIO.mAttPosOffsetY;
    attention_info.position.set(current.pos.x, current.pos.y + offset, current.pos.z);
    if (!mbSetEyePos && !i_setEyePos) {
        return;
    }

    eyePos.set(mEyePos.x, mEyePos.y, mEyePos.z);
}

/* 00001494-000014B0       .text charDecide__11daNpc_Ac1_cFi */
bool daNpc_Ac1_c::charDecide(int) {
    mType = 0;
    mSpecificType = -1;
    mSpecificType = 0;
    return true;
}

/* 000014B0-00001508       .text event_actionInit__11daNpc_Ac1_cFi */
void daNpc_Ac1_c::event_actionInit(int i_param1) {
    int* actNo = dComIfGp_evmng_getMyIntegerP(i_param1, "ActNo");
    if (actNo != NULL) {
        mActNo = *actNo;
    }
}

/* 00001508-00001528       .text event_action__11daNpc_Ac1_cFv */
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
    static char* a_cut_tbl[] = { "ACTION" };
    if (i_staffIdx != -1) {
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
            bool action;
            switch (mActionIndex) {
                case 0:
                    action = event_action();
                    break;
                default:
                    action = true;
                    break;
            }
            if (action) {
                dComIfGp_evmng_cutEnd(i_staffIdx);
            }
        }
    }
}

/* 00001614-00001634       .text endEvent__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::endEvent() {
    dComIfGp_event_reset();
    mAnmAtr = -1;
}

/* 00001634-0000166C       .text isEventEntry__11daNpc_Ac1_cFv */
BOOL daNpc_Ac1_c::isEventEntry() {
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
BOOL daNpc_Ac1_c::set_action(ActionFunc i_action, void* i_param2) {
    if (mCurrActionFunc != i_action) {
        if (mCurrActionFunc) {
            mActionPhase = 9;
            (this->*mCurrActionFunc)(i_param2);
        }
        mCurrActionFunc = i_action;
        mActionPhase = 0;
        (this->*mCurrActionFunc)(i_param2);
    }
    return TRUE;
}

/* 00001770-000017D4       .text setStt__11daNpc_Ac1_cFSc */
void daNpc_Ac1_c::setStt(s8 i_status) {
    s8 previous_status = mStatus;
    mTimer = 0;
    mStatus = i_status;
    switch (mStatus) {
        case 2:
            mAnmAtr = -1;
            mLookBackState = 1;
            mPrevStatus = previous_status;
            m_jnt.setTrn();
            break;
        case 1:
        default:
            setAnm();
            break;
    }
}

/* 000017D4-0000189C       .text wait_1__11daNpc_Ac1_cFv */
BOOL daNpc_Ac1_c::wait_1() {
    if (mTalkOrder == 1 || mTalkOrder >= 3) {
        return TRUE;
    }
    if (mbTalking) {
        if (chk_talk()) {
            setStt(2);
        }
        return TRUE;
    }
    mTalkOrder = 2;
    if (mbAttention) {
        mTimer = 0x3C;
    }
    if (cLib_calcTimer(&mTimer)) {
        mLookBackState = 1;
    } else {
        mLookBackState = 3;
        field_0x854 = mInitialAngle.y;
        m_jnt.setTrn();
    }
    return TRUE;
}

/* 0000189C-00001978       .text talk_1__11daNpc_Ac1_cFv */
BOOL daNpc_Ac1_c::talk_1() {
    u8 notMove = chk_partsNotMove();
    if (mpCurrMsg != NULL) {
        field_0x856 = mpCurrMsg->mStatus;
    } else {
        field_0x856 = fopMsgStts_MSG_UNK0_e;
    }
    talk(1);

    if (mpCurrMsg != NULL) {
        switch (mpCurrMsg->mStatus) {
            case fopMsgStts_MSG_TYPING_e:
            case fopMsgStts_BOX_OPENING_e:
                break;
            case fopMsgStts_MSG_DESTROYED_e:
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_3F02);
                mItemNo = -1;
                mbTalking = false;
                setStt(mPrevStatus);
                mTimer = 0x3C;
                endEvent();
        }
    }
    return notMove;
}

/* 00001978-00001A34       .text wait_action1__11daNpc_Ac1_cFPv */
BOOL daNpc_Ac1_c::wait_action1(void*) {
    switch (mActionPhase) {
        case 0:
            setStt(1);
            mActionPhase++;
            break;
        case 1:
        case 2:
        case 3:
            mbAttention = chkAttention();
            switch (mStatus) {
                case 1:
                    mbSetEyePos = wait_1();
                    break;
                case 2:
                    mbSetEyePos = talk_1();
                    break;
            }
            lookBack();
            break;
        case 9:
            break;
    }
    return TRUE;
}

/* 00001A34-00001B74       .text demo__11daNpc_Ac1_cFv */
bool daNpc_Ac1_c::demo() {
    if (demoActorID == 0) {
        if (mbInDemo != 0) {
            mbInDemo = 0;
        }
    } else {
        mbInDemo = 1;
        dDemo_actor_c* demo_actor = dComIfGp_demo_getActor(demoActorID);
        if (m_hed_tex_pttrn) {
            mBlinkFrame += 1;
            if (mBlinkFrame >= m_hed_tex_pttrn->getFrameMax()) {
                mBlinkFrame = m_hed_tex_pttrn->getFrameMax();
            }
        }
        J3DAnmTexPattern* demopattern = demo_actor->getP_BtpData("Ac");
        if (demopattern) {
            m_hed_tex_pttrn = demopattern;
            if (mBtpAnim.init(mpMorf->getModel()->getModelData(), m_hed_tex_pttrn, 1, 2, 1.0f, 0, -1, true, FALSE)) {
                mBtpNum = 3;
                mBlinkFrame = 0;
            }
        }
        dDemo_setDemoData(this, 0x6A, mpMorf, "Ac");
    }
    return mbInDemo;
}

/* 00001B74-00001C70       .text shadowDraw__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::shadowDraw() {
    cXyz local_18(current.pos.x, current.pos.y + 150.0f, current.pos.z);

    mShadowID = dComIfGd_setShadow(
        mShadowID,
        1,
        mpMorf->getModel(),
        &local_18,
        800.0f,
        40.0f,
        current.pos.y,
        mObjAcch.GetGroundH(),
        mObjAcch.m_gnd,
        &tevStr,
        0,
        1.0,
        dDlst_shadowControl_c::getSimpleTex()
    );

    if (mShadowID) {
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

/* 00001C70-00001DC4       .text _draw__11daNpc_Ac1_cFv */
BOOL daNpc_Ac1_c::_draw() {
    J3DModel* model = mpMorf->getModel();
    J3DModelData* model_data = model->getModelData();
    if (field_0x85D || field_0x861) {
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(model, &tevStr);
    mBtpAnim.entry(model_data, mBlinkFrame);
    mpMorf->entryDL();
    model_data->getMaterialTable().removeTexNoAnimator(mBtpAnim.getBtpAnm());

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
    dSnap_RegistFig(DSNAP_TYPE_NPC_AC1, this, 1.0f, 1.0f, 1.0f);

    // Debug:
    (GXColor){ 0xFF, 0x00, 0x00, 0x80 };
    (GXColor){ 0x00, 0x00, 0xFF, 0x80 };

    return TRUE;
}

/* 00001DC4-00001F80       .text _execute__11daNpc_Ac1_cFv */
BOOL daNpc_Ac1_c::_execute() {
    if (!mbRanExecute) {
        mInitialPos = current.pos;
        mInitialAngle = current.angle;
        mbRanExecute = true;
    }
    m_jnt.setParam(
        l_HIO.mMaxBackboneX,
        l_HIO.mMaxBackboneY,
        l_HIO.mMinBackboneX,
        l_HIO.mMinBackboneY,
        l_HIO.mMaxHeadX,
        l_HIO.mMaxHeadY,
        l_HIO.mMinHeadX,
        l_HIO.mMinHeadY,
        l_HIO.mMaxTurnStep
    );
    if (field_0x85D && demoActorID == 0) {
        return TRUE;
    }
    field_0x860 = 0;
    field_0x85D = 0;
    checkOrder();
    if (!demo()) {
        s32 staffIdx = -1;
        if (dComIfGp_event_runCheck() && eventInfo.checkCommandTalk() == 0) {
            staffIdx = isEventEntry();
        }
        if (staffIdx >= 0) {
            event_proc(staffIdx);
        } else {
            (this->*mCurrActionFunc)(NULL);
        }
        if (!field_0x860) {
            fopAcM_posMoveF(this, mStts.GetCCMoveP());
        }

        if (!mbSetShapeAngle) {
            shape_angle = current.angle;
        }
    }
    eventOrder();
    setMtx(false);
    if (!mbInDemo) {
        setCollision(50.0f, 140.0f);
    }
    return TRUE;
}

/* 00001F80-00001FFC       .text _delete__11daNpc_Ac1_cFv */
BOOL daNpc_Ac1_c::_delete() {
    dComIfG_resDelete(&mPhase, "Ac");
#if VERSION > VERSION_DEMO
    if (heap != NULL)
#endif
    {
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
#if VERSION == VERSION_DEMO
    l_HIO.removeHIO();
#endif
    return TRUE;
}

/* 00001FFC-0000201C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Ac1_c*>(i_this)->CreateHeap();
}

/* 0000201C-0000213C       .text _create__11daNpc_Ac1_cFv */
cPhs_State daNpc_Ac1_c::_create() {
    fopAcM_ct_Retail(this, daNpc_Ac1_c);
    static u32 a_size_tbl[] = { 0x272E0 };
    cPhs_State state = dComIfG_resLoad(&mPhase, "Ac");
    if (state != cPhs_COMPLEATE_e) {
        return state;
    }
    u32 tmp = fopAcM_GetParam(this) & 0xFF;
    if (!charDecide(tmp)) {
        return cPhs_ERROR_e;
    }
#if VERSION == VERSION_DEMO
    l_HIO.entryHIO("コモリ成長");
    fopAcM_ct(this, daNpc_Ac1_c);
#endif
    if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_size_tbl[mType])) {
        return cPhs_ERROR_e;
    }

    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -50.0, -20.0, -50.0, 50.0, 140.0, 50.0);

    if (!createInit()) {
        return cPhs_ERROR_e;
    }
    return state;
}

/* 0000256C-00002838       .text create_Anm__11daNpc_Ac1_cFv */
J3DModelData* daNpc_Ac1_c::create_Anm() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Ac", dRes_ID_AC_BDL_AC_e);
    JUT_ASSERT(0x6BE, a_mdl_dat != NULL);
    mpMorf = new mDoExt_McaMorf(
        a_mdl_dat,
        NULL,
        NULL,
        (J3DAnmTransform*)dComIfG_getObjectIDRes("Ac", dRes_ID_AC_BCK_AC_WAIT01_e),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        TRUE,
        NULL,
        0x80000,
        0x11020022
    );
    if (mpMorf == NULL) {
        return NULL;
    } else if (mpMorf->getModel() == NULL) {
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

/* 00002838-00002A4C       .text create_wng_Anm__11daNpc_Ac1_cFv */
J3DModelData* daNpc_Ac1_c::create_wng_Anm() {

    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Ac", dRes_ID_AC_BDL_ACWING_e);
    JUT_ASSERT(0x6EA, a_mdl_dat != NULL);
    mpWingMorf = new mDoExt_McaMorf(
        a_mdl_dat,
        NULL,
        NULL,
        (J3DAnmTransform*)dComIfG_getObjectIDRes("Ac", dRes_ID_AC_BCK_ACARM_WAIT01_e),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        TRUE,
        NULL,
        0x80000,
        0x11000002
    );
    if (!mpWingMorf) {
        return NULL;
    }
    if (!mpWingMorf->getModel()) {
        mpWingMorf = NULL;
        return NULL;
    }
    m_wngL1_jnt_num = a_mdl_dat->getJointName()->getIndex("wingL_loc");
    JUT_ASSERT(0x6FF, m_wngL1_jnt_num >= 0);
    m_wngR1_jnt_num = a_mdl_dat->getJointName()->getIndex("wingR_loc");
    JUT_ASSERT(0x702, m_wngR1_jnt_num >= 0);
    return a_mdl_dat;
}

/* 00002A4C-00002CBC       .text create_arm_Anm__11daNpc_Ac1_cFv */
J3DModelData* daNpc_Ac1_c::create_arm_Anm() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Ac", dRes_ID_AC_BDL_ACARM_e);
    JUT_ASSERT(0x711, a_mdl_dat != NULL);
    mpArmMorf = new mDoExt_McaMorf(
        a_mdl_dat,
        NULL,
        NULL,
        (J3DAnmTransform*)dComIfG_getObjectIDRes("Ac", dRes_ID_AC_BCK_ACARM_WAIT01_e),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        TRUE,
        NULL,
        0x80000,
        0x11000002
    );
    if (!mpArmMorf) {
        return NULL;
    }
    if (!mpArmMorf->getModel()) {
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

/* 00002CBC-00002DC8       .text create_itm_Mdl__11daNpc_Ac1_cFv */
bool daNpc_Ac1_c::create_itm_Mdl() {
    mpItemModel = NULL;
    J3DModelData* a_mdl_dat;
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1580)) {
        a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Ac", dRes_ID_AC_BDL_AC_FLOWER02_e);
    } else {
        a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Ac", dRes_ID_AC_BDL_AC_FLOWER_e);
    }
    JUT_ASSERT(0x744, a_mdl_dat != NULL);
    mpItemModel = mDoExt_J3DModel__create(a_mdl_dat, 0x80000, 0x11000022);
    return true;
}

/* 00002DC8-00003044       .text CreateHeap__11daNpc_Ac1_cFv */
BOOL daNpc_Ac1_c::CreateHeap() {
    J3DModelData* modeldat;
    J3DModelData* anm_model = create_Anm();
    if (!anm_model) {
        return FALSE;
    }
    mBtpNum = 0;
    if (!iniTexPttrnAnm(false)) {
        mpMorf = NULL;
        return FALSE;
    }
    modeldat = create_wng_Anm();
    if (!modeldat) {
        mpMorf = NULL;
        return FALSE;
    }
    J3DModelData* arm_anmdata = create_arm_Anm();
    if (arm_anmdata != NULL && create_itm_Mdl()) {
        for (u16 i = 0; i < modeldat->getJointNum(); i++) {
            if ((i == m_wngL1_jnt_num) || (i == m_wngR1_jnt_num)) {
                mpWingMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Wng);
            }
        }
        mpWingMorf->getModel()->setUserArea((uintptr_t)this);
        for (u16 i = 0; i < arm_anmdata->getJointNum(); i++) {
            if ((i == m_armL1_jnt_num) || (i == m_armR1_jnt_num)) {
                mpArmMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Arm);
            }
        }
        mpArmMorf->getModel()->setUserArea((uintptr_t)this);
        for (u16 i = 0; i < anm_model->getJointNum(); i++) {
            if ((i == m_hed_jnt_num) || (i == m_bbone_jnt_num) || (i == m_arm_L_jnt_num) || i == m_arm_R_jnt_num) {
                mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Ac1);
            }
        }
        mpMorf->getModel()->setUserArea((uintptr_t)this);
        mAcchCir.SetWall(30.0f, 50.0f);
        mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this), NULL, NULL);
        return TRUE;
    } else {
        mpMorf = NULL;
        mpWingMorf = NULL;
        return FALSE;
    }
}

/* 00003044-00003064       .text daNpc_Ac1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Ac1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Ac1_c*)i_this)->_create();
}

/* 00003064-00003084       .text daNpc_Ac1_Delete__FP11daNpc_Ac1_c */
static BOOL daNpc_Ac1_Delete(daNpc_Ac1_c* i_this) {
    return ((daNpc_Ac1_c*)i_this)->_delete();
}

/* 00003084-000030A4       .text daNpc_Ac1_Execute__FP11daNpc_Ac1_c */
static BOOL daNpc_Ac1_Execute(daNpc_Ac1_c* i_this) {
    return ((daNpc_Ac1_c*)i_this)->_execute();
}

/* 000030A4-000030C4       .text daNpc_Ac1_Draw__FP11daNpc_Ac1_c */
static BOOL daNpc_Ac1_Draw(daNpc_Ac1_c* i_this) {
    return ((daNpc_Ac1_c*)i_this)->_draw();
}

/* 000030C4-000030CC       .text daNpc_Ac1_IsDelete__FP11daNpc_Ac1_c */
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
