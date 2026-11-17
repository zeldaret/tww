/**
 * d_a_npc_ac1.cpp
 * NPC - Prince Komali (after Dragon Roost Cavern)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_ac1.h"

static daNpc_Ac1_HIO_c l_HIO;

/* 000000EC-00000150       .text __ct__15daNpc_Ac1_HIO_cFv */
daNpc_Ac1_HIO_c::daNpc_Ac1_HIO_c() {
    static u32 a_prm_tbl[] = { 0x20002710, 0xF000D8F0, 0x00001770, 0x0000E890, 0x07080578, 0x43160000,
                               0x00000006, 0x04000000, 0x3F000000, 0x40400000, 0x3DCCCCCD, 0x42200000 };
    memcpy(&field_0x0C, a_prm_tbl, 0x30);
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
    s32 uVar1 = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(uVar1));
    if (uVar1 == m_wngL1_jnt_num) {
        cMtx_copy(mLeftArmMtx, j3dSys.mCurrentMtx);
        i_model->setAnmMtx(uVar1, mLeftArmMtx);
    }
    if (uVar1 == m_wngR1_jnt_num) {
        cMtx_copy(mRightArmMtx, j3dSys.mCurrentMtx);
        i_model->setAnmMtx(uVar1, mRightArmMtx);
    }
}

/* 00000294-000002E0       .text nodeCallBack_Arm__FP7J3DNodei */
static BOOL nodeCallBack_Arm(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == 0) {
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
    field_0x814 = current.pos;
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
    switch (field_0x879) {
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

    if (field_0x85E) {
        field_0x708->setMorf(0.0f);
    } else {
        field_0x6FC->setMorf(0.0f);
    }
    setMtx(true);
    return true;
}

/* 000007C8-00000988       .text setMtx__11daNpc_Ac1_cFb */
void daNpc_Ac1_c::setMtx(bool i_setEyePos) {

    if (field_0x86B == 0) {
        plyTexPttrnAnm();
        mbMorfAnimStopped = mpMorf->play(&eyePos, 0, 0);
        if (mpMorf->getFrame() < mFrame) {
            mbMorfAnimStopped = true;
        }
        mFrame = mpMorf->getFrame();
        if (field_0x85E) {
            field_0x708->play(&eyePos, 0, 0);
        } else {
            field_0x6FC->play(&eyePos, 0, 0);
        }
        mObjAcch.CrrPos(*dComIfG_Bgsp());
    }
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    if (!field_0x85E) {
        field_0x6FC->calc();
    } else {
        field_0x708->calc();
    }
    if (field_0x6D4 && field_0x85E) {
        field_0x6D4->setBaseTRMtx(field_0x708->getModel()->getAnmMtx(m_hnd_R_jnt_num));
        field_0x6D4->calc();
    }
    setAttention(i_setEyePos);
}

/* 00000988-0000099C       .text anmNum_toResID__11daNpc_Ac1_cFi */
u32 daNpc_Ac1_c::anmNum_toResID(int i_idx) {
    static const u32 a_bck_resID_tbl[] = { 1, 12, 13, 14 };
    return a_bck_resID_tbl[i_idx];
}

/* 0000099C-000009B0       .text wingAnmNum_toResID__11daNpc_Ac1_cFi */
u32 daNpc_Ac1_c::wingAnmNum_toResID(int i_idx) {

    static const u32 a_bck_resID_tbl[] = { 0, 9, 10, 11 };
    return a_bck_resID_tbl[i_idx];
}

/* 000009B0-000009C4       .text btpNum_toResID__11daNpc_Ac1_cFi */
u32 daNpc_Ac1_c::btpNum_toResID(int i_idx) {
    static const u32 a_btp_resID_tbl[] = { 7, 6, 8 };
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
    field_0x85E = i_anmPrmP->field_0x10 == 1;
    if (field_0x85E) {
        dNpc_setAnmIDRes(field_0x708, i_anmPrmP->loopMode, i_anmPrmP->morf, i_anmPrmP->speed, wingAnmNum, -1, "Ac");
    } else {
        dNpc_setAnmIDRes(field_0x6FC, i_anmPrmP->loopMode, i_anmPrmP->morf, i_anmPrmP->speed, wingAnmNum, -1, "Ac");
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
    if (i_param1 >= 6 || i_param1 == field_0x86E) {
        return;
    }
    field_0x86E = i_param1;
    setAnm_ATR(1);
}

/* 00000DD8-00000DE4       .text control_anmAtr__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::control_anmAtr() {
    switch (field_0x86E) {
        case 6:
            break;
    }
}

/* 00000DE4-00000E4C       .text setAnm_ATR__11daNpc_Ac1_cFi */
void daNpc_Ac1_c::setAnm_ATR(int i_param1) {
    static anm_prm_c a_anm_prm_tbl[] = { { 0, 0, 8.0f, 1.0f, 2, 1 }, { 1, 0, 8.0f, 1.0f, 2, 1 }, { 2, 1, 8.0f, 1.0f, 2, 1 },
                                         { 3, 0, 8.0f, 1.0f, 2, 1 }, { 1, 2, 8.0f, 1.0f, 2, 1 }, { 1, 1, 8.0f, 1.0f, 2, 1 } };
    if (i_param1) {
        setAnm_tex(a_anm_prm_tbl[field_0x86E].btpNum);
    }
    setAnm_anm(&a_anm_prm_tbl[field_0x86E]);
}

/* 00000E4C-00000F10       .text anmAtr__11daNpc_Ac1_cFUs */
void daNpc_Ac1_c::anmAtr(u16 i_param1) {
    switch (i_param1) {
        case 0x6:
            {
                if (field_0x87B == 0) {
                    field_0x86E = -1;
                    chg_anmAtr(dComIfGp_getMesgAnimeAttrInfo());
                    field_0x87B++;
                }
                u32 tagInfo = dComIfGp_getMesgAnimeTagInfo();
                dComIfGp_clearMesgAnimeTagInfo();
                if (tagInfo != 0xFF && field_0x86F != tagInfo) {
                    field_0x86F = tagInfo;
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
    if (field_0x874 == 1 || field_0x874 == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (field_0x874 == 1) {
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
    if (field_0x874 != 1 && field_0x874 != 2) {
        return;
    }
    field_0x874 = 0;
    field_0x869 = 1;
}

/* 00000FA0-0000103C       .text chk_talk__11daNpc_Ac1_cFv */
bool daNpc_Ac1_c::chk_talk() {
    bool uVar3 = true;
    field_0x85B = 0xFF;
    if (dComIfGp_event_chkTalkXY()) {
        if (dComIfGp_evmng_ChkPresentEnd()) {
            field_0x85B = dComIfGp_event_getPreItemNo();
        } else {
            uVar3 = false;
        }
    }

    return uVar3;
}

/* 0000103C-0000107C       .text chk_partsNotMove__11daNpc_Ac1_cFv */
bool daNpc_Ac1_c::chk_partsNotMove() {
    return field_0x844 == m_jnt.getHead_y() && field_0x846 == m_jnt.getBackbone_y() && field_0x848 == current.angle.y;
}

/* 0000107C-0000121C       .text lookBack__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::lookBack() {
    /* Nonmatching */
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
    switch (field_0x879) {
        case 0:
            ret = 0x10;
            break;
    }
    return ret;
}

/* 000012AC-00001380       .text getMsg_AC1_0__11daNpc_Ac1_cFv */
u32 daNpc_Ac1_c::getMsg_AC1_0() {
    /* Nonmatching */
}

/* 00001380-000013BC       .text getMsg__11daNpc_Ac1_cFv */
u32 daNpc_Ac1_c::getMsg() {
    u32 o_retval = 0;
    switch (field_0x879) {
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
    attention_info.position.set(current.pos.x, current.pos.y + l_HIO.field_0x20, current.pos.z);
    if (!mbSetEyePos && !i_setEyePos) {
        return;
    }

    eyePos.set(mEyePos.x, mEyePos.y, mEyePos.z);
}

/* 00001494-000014B0       .text charDecide__11daNpc_Ac1_cFi */
BOOL daNpc_Ac1_c::charDecide(int) {
    field_0x878 = 0;
    field_0x879 = -1;
    field_0x879 = 0;
    return TRUE;
}

/* 000014B0-00001508       .text event_actionInit__11daNpc_Ac1_cFi */
void daNpc_Ac1_c::event_actionInit(int i_param1) {
    int* actNo = dComIfGp_evmng_getMyIntegerP(i_param1, "ActNo");
    if (actNo != NULL) {
        field_0x86D = *actNo;
    }
}

/* 00001508-00001528       .text event_action__11daNpc_Ac1_cFv */
bool daNpc_Ac1_c::event_action() {
    switch (field_0x86D) {
        case 0:
            return true;
        default:
            return true;
    }
}

/* 00001528-00001614       .text privateCut__11daNpc_Ac1_cFi */
void daNpc_Ac1_c::privateCut(int) {
    static char* a_cut_tbl[] = { "ACTION" };
    /* Nonmatching */
}

/* 00001614-00001634       .text endEvent__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::endEvent() {
    dComIfGp_event_reset();
    field_0x86E = -1;
}

/* 00001634-0000166C       .text isEventEntry__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::isEventEntry() {
    /* Nonmatching */
}

/* 0000166C-000016C4       .text event_proc__11daNpc_Ac1_cFi */
void daNpc_Ac1_c::event_proc(int) {
    /* Nonmatching */
}

/* 000016C4-00001770       .text set_action__11daNpc_Ac1_cFM11daNpc_Ac1_cFPCvPvPv_iPv */
void daNpc_Ac1_c::set_action(int (daNpc_Ac1_c::*)(void*), void*) {
    /* Nonmatching */
}

/* 00001770-000017D4       .text setStt__11daNpc_Ac1_cFSc */
void daNpc_Ac1_c::setStt(signed char) {
    /* Nonmatching */
}

/* 000017D4-0000189C       .text wait_1__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::wait_1() {
    /* Nonmatching */
}

/* 0000189C-00001978       .text talk_1__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::talk_1() {
    /* Nonmatching */
}

/* 00001978-00001A34       .text wait_action1__11daNpc_Ac1_cFPv */
BOOL daNpc_Ac1_c::wait_action1(void*) {
    /* Nonmatching */
}

/* 00001A34-00001B74       .text demo__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::demo() {
    /* Nonmatching */
}

/* 00001B74-00001C70       .text shadowDraw__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::shadowDraw() {
    /* Nonmatching */
}

/* 00001C70-00001DC4       .text _draw__11daNpc_Ac1_cFv */
BOOL daNpc_Ac1_c::_draw() {
    /* Nonmatching */
}

/* 00001DC4-00001F80       .text _execute__11daNpc_Ac1_cFv */
BOOL daNpc_Ac1_c::_execute() {
    /* Nonmatching */
}

/* 00001F80-00001FFC       .text _delete__11daNpc_Ac1_cFv */
BOOL daNpc_Ac1_c::_delete() {
    /* Nonmatching */
}

/* 00001FFC-0000201C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Ac1_c*>(i_this)->CreateHeap();
}

/* 0000201C-0000213C       .text _create__11daNpc_Ac1_cFv */
cPhs_State daNpc_Ac1_c::_create() {
    static u32 a_size_tbl[] = { 0x272E0 };
    /* Nonmatching */
}

/* 0000256C-00002838       .text create_Anm__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::create_Anm() {
    /* Nonmatching */
}

/* 00002838-00002A4C       .text create_wng_Anm__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::create_wng_Anm() {
    /* Nonmatching */
}

/* 00002A4C-00002CBC       .text create_arm_Anm__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::create_arm_Anm() {
    /* Nonmatching */
}

/* 00002CBC-00002DC8       .text create_itm_Mdl__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::create_itm_Mdl() {
    /* Nonmatching */
}

/* 00002DC8-00003044       .text CreateHeap__11daNpc_Ac1_cFv */
BOOL daNpc_Ac1_c::CreateHeap() {
    /* Nonmatching */
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
