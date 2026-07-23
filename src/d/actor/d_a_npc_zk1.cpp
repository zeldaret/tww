/**
 * d_a_npc_zk1.cpp
 * NPC - Rito Chieftain
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_zk1.h"
#include "d/d_lib.h"
#include "d/d_snap.h"
#include "res/Object/Zk.h"


class daNpc_Zk1_HIO_c : public mDoHIO_entry_c {
public:
    struct hio_prm_c {
        s16 mMaxHeadX;
        s16 mMaxHeadY;
        s16 mMinHeadX;
        s16 mMinHeadY;
        s16 mMaxBackboneX;
        s16 mMaxBackboneY;
        s16 mMinBackboneX;
        s16 mMinBackboneY;
        s16 mMaxTurnStep;
        s16 mCalcAngleTarget;
        f32 mAttPosOffsetY;
        f32 field_18;
    };  // Size: 0x1C

    daNpc_Zk1_HIO_c();
    virtual ~daNpc_Zk1_HIO_c() {};

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ s8 field_0x5;
    /* 0x06 */ s8 field_0x6;
    /* 0x07 */ s8 field_0x7;
    /* 0x08 */ int field_0x8;
    /* 0x0C */ hio_prm_c mPrmTbl;
};

static daNpc_Zk1_HIO_c l_HIO;
static fopAc_ac_c* l_check_inf[20];
static int l_check_wrk;

/* 000000EC-00000150       .text __ct__15daNpc_Zk1_HIO_cFv */
daNpc_Zk1_HIO_c::daNpc_Zk1_HIO_c() {

    static hio_prm_c a_prm_tbl = {
        /* mMaxHeadX         */ 0x1FFE,
        /* mMaxHeadY         */ 0x251C,
        /* mMinHeadX         */ 0xF448,
        /* mMinHeadY         */ 0xDAE4,
        /* mMaxBackboneX     */ 0x0000,
        /* mMaxBackboneY     */ 0x1194,
        /* mMinBackboneX     */ 0xFD44,
        /* mMinBackboneY     */ 0xEE6C,
        /* mMaxTurnStep      */ 0x0640,
        /* mCalcAngleTarget          */ 0x04B0,
        /* mAttPosOffsetY */ 240.0f,
        /* field_18          */ 0.0f,
    };
    memcpy(&mPrmTbl, &a_prm_tbl, sizeof(hio_prm_c));
    mNo = -1;
    field_0x8 = -1;
}

static const char* l_evn_tbl[1] = {
    "dummy",
};

/* 00000198-000001E4       .text nodeCB_Head__FP7J3DNodei */
static BOOL nodeCB_Head(J3DNode* i_node, int i_param) {
    if(i_param == 0) {
        daNpc_Zk1_c* actor = (daNpc_Zk1_c*)j3dSys.getModel()->getUserArea();
        if(actor != NULL) {
            actor->_nodeCB_Head(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 000001E4-00000304       .text _nodeCB_Head__11daNpc_Zk1_cFP7J3DNodeP8J3DModel */
void daNpc_Zk1_c::_nodeCB_Head(J3DNode* i_node, J3DModel* i_pModel) {
    static cXyz a_eye_pos_off(14.0f, 18.0f, 0.0f);

    J3DJoint* jnt_p = ((J3DJoint*)(i_node));
    s32 jnt_no = jnt_p->getJntNo();
    mDoMtx_stack_c::copy(i_pModel->getAnmMtx(jnt_no));

    mDoMtx_stack_c::multVecZero(&field_0x750);
    mDoMtx_stack_c::multVec(&a_eye_pos_off, &mTransformedEyePos);
    mDoMtx_stack_c::XrotM(m_jnt.getHead_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    i_pModel->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* 00000340-0000038C       .text nodeCB_BackBone__FP7J3DNodei */
static BOOL nodeCB_BackBone(J3DNode* i_node, int i_param) {
    if(i_param == 0) {
        daNpc_Zk1_c* actor = (daNpc_Zk1_c*)j3dSys.getModel()->getUserArea();
        if(actor != NULL) {
            actor->_nodeCB_BackBone(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 0000038C-0000042C       .text _nodeCB_BackBone__11daNpc_Zk1_cFP7J3DNodeP8J3DModel */
void daNpc_Zk1_c::_nodeCB_BackBone(J3DNode* i_node, J3DModel* i_pModel) {
    J3DJoint* jnt_p = ((J3DJoint*)(i_node));
    s32 jnt_no = jnt_p->getJntNo();
    mDoMtx_stack_c::copy(i_pModel->getAnmMtx(jnt_no));
    mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getBackbone_x());
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    i_pModel->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* 0000042C-0000044C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* ac) {
    return ((daNpc_Zk1_c*)ac)->CreateHeap();
}

/* 0000044C-00000518       .text init_ZK1_0__11daNpc_Zk1_cFv */
bool daNpc_Zk1_c::init_ZK1_0() {

    if(dComIfGs_isSymbol(1)) {
        set_action(&daNpc_Zk1_c::wait_action1, NULL);
        field_0x797 = dComIfGs_isEventBit(dSv_event_flag_c::UNK_1802) == true;
        field_0x798 = dComIfGs_isEventBit(dSv_event_flag_c::UNK_1C01) == true;
        return true;
    }
    return false;
}

/* 00000518-00000698       .text createInit__11daNpc_Zk1_cFv */
bool daNpc_Zk1_c::createInit() {

    bool ret;
    int temp = 0xff;

    for(int i = 0; i < ARRAY_SIZE(l_evn_tbl); i++) {
        mEventIDTbl[i] = dComIfGp_evmng_getEventIdx(l_evn_tbl[i]);
    }

    mEventCut.setActorInfo2("Zk1", this);
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;

    // Not sure why this is here, but it won't match without.
    // NPC Hi1 seems to have the same thing going on
    switch(mSpecificType) {
        case 0:
        break;
    }

    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xA9;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xA9;
    gravity = 0.0f;
    mBckNum = 4;
    switch(mSpecificType) {
        case 0:
            ret = init_ZK1_0();
            break;
        default:
            ret = false;
    }
    if(!ret) {
        return false;
    }

    mAngle = current.angle;
    shape_angle = mAngle;
    mStts.Init(temp, 0xff, this);
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

/* 00000698-00000740       .text play_animation__11daNpc_Zk1_cFv */
void daNpc_Zk1_c::play_animation() {

    u32 snd_id = 0;
    play_btp_anm();
    if(mObjAcch.ChkGroundHit()) {
        snd_id = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
    }
    mbMorfAnimStopped = mpMorf->play(
        &eyePos, 
        snd_id, 
        dComIfGp_getReverb(
            fopAcM_GetRoomNo(this)
        )
    );

    if (mpMorf->getFrame() < mPrevMorfFrame) {
        mbMorfAnimStopped = true;
    }
    mPrevMorfFrame = mpMorf->getFrame();
}

/* 00000740-000007F0       .text setMtx__11daNpc_Zk1_cFb */
void daNpc_Zk1_c::setMtx(bool i_setEyePos) {
    mpMorf->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(mAngle);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    setAttention(i_setEyePos);
}

/* 000007F0-00000804       .text bckResID__11daNpc_Zk1_cFi */
int daNpc_Zk1_c::bckResID(int i_bckNum) {

    static const int a_resID_tbl[] = {
        dRes_ID_ZK_BCK_ZK_WAIT01_e,
        dRes_ID_ZK_BCK_ZK_WAIT02_e,
        dRes_ID_ZK_BCK_ZK_TALK01_e,
        dRes_ID_ZK_BCK_ZK_TALK02_e,
    };
    return a_resID_tbl[i_bckNum];
}

/* 00000804-00000818       .text btpResID__11daNpc_Zk1_cFi */
int daNpc_Zk1_c::btpResID(int i_btpNum) {

    static const int a_resID_tbl[] = {
        dRes_ID_ZK_BTP_MABA_e
    };
    return a_resID_tbl[i_btpNum];
}

/* 00000818-0000091C       .text setBtp__11daNpc_Zk1_cFScb */
bool daNpc_Zk1_c::setBtp(s8 i_btpNum, bool i_bModify) {

    J3DModel* morf_model_p = mpMorf->getModel();
    if(i_btpNum < 0) {
        return false;
    }
    J3DAnmTexPattern* a_btp = (J3DAnmTexPattern *)dComIfG_getObjectIDRes(mArcName, btpResID(i_btpNum));
    JUT_ASSERT(399, a_btp != NULL);
    mBtpNum = i_btpNum;
    mBtpFrame = 0;
    mTimer1 = 0;

    return mBtpAnm.init(
        morf_model_p->getModelData(), 
        a_btp,TRUE, 
        J3DFrameCtrl::EMode_NONE,
        1.0f, 0, -1, 
        i_bModify, 0
    ) != 0;
}

/* 0000091C-0000093C       .text init_texPttrnAnm__11daNpc_Zk1_cFScb */
bool daNpc_Zk1_c::init_texPttrnAnm(s8 i_btpNum, bool i_bModify) {

    return setBtp(i_btpNum, i_bModify);
}

/* 0000093C-000009D8       .text play_btp_anm__11daNpc_Zk1_cFv */
void daNpc_Zk1_c::play_btp_anm() {
    u8 frame_max = mBtpAnm.getBtpAnm()->getFrameMax();
    if (mBtpNum != 0 || cLib_calcTimer(&mTimer1) == 0) {
        mBtpFrame++;
        if (mBtpFrame >= frame_max) {
            if (mBtpNum != 0) {
                mBtpFrame = frame_max;
            } else {
                mTimer1 = cLib_getRndValue(60, 90);
                mBtpFrame = 0;
            }
        }
    }
}

/* 000009D8-00000A74       .text setAnm_anm__11daNpc_Zk1_cFPQ211daNpc_Zk1_c9anm_prm_c */
void daNpc_Zk1_c::setAnm_anm(anm_prm_c* i_anmPrmP) {

    if(i_anmPrmP->bckNum < 0 || mBckNum == i_anmPrmP->bckNum) {
        return;
    }
    dNpc_setAnmIDRes(mpMorf,
        i_anmPrmP->loopMode,
        i_anmPrmP->morf,
        i_anmPrmP->speed,
        bckResID(i_anmPrmP->bckNum),
        -1,
        mArcName
    );
    mBckNum = i_anmPrmP->bckNum;
    mbMorfAnimStopped = 0;
    field_0x795 = 0;
    mPrevMorfFrame = 0.0f;
}

/* 00000A74-00000AE0       .text setAnm__11daNpc_Zk1_cFv */
void daNpc_Zk1_c::setAnm() {

    static daNpc_Zk1_c::anm_prm_c a_anm_prm_tbl[3] = {
        {-1, -1, 0,0.0, 0.0, J3DFrameCtrl::EMode_NULL},
        {0, 0, 0,8.0, 1.0, J3DFrameCtrl::EMode_LOOP},
        {-1, -1, 0,0.0, 0.0, J3DFrameCtrl::EMode_NULL},
    };
    init_texPttrnAnm(a_anm_prm_tbl[mStatus].btpNum, true);
    setAnm_anm(&a_anm_prm_tbl[mStatus]);
}

/* 00000AE0-00000AE4       .text chngAnmTag__11daNpc_Zk1_cFv */
void daNpc_Zk1_c::chngAnmTag() {
}

/* 00000AE4-00000AE8       .text ctrlAnmTag__11daNpc_Zk1_cFv */
void daNpc_Zk1_c::ctrlAnmTag() {
}

/* 00000AE8-00000B28       .text chngAnmAtr__11daNpc_Zk1_cFUc */
void daNpc_Zk1_c::chngAnmAtr(u8 param_1) {
    if(param_1 == field_0x7A6 || param_1 > 4) {
        return;
    }
    field_0x7A6 = param_1;
    setAnm_ATR();
    
}

/* 00000B28-00000B34       .text ctrlAnmAtr__11daNpc_Zk1_cFv */
void daNpc_Zk1_c::ctrlAnmAtr() {


    switch (field_0x7A6) {
        case 4:
            break;
    }
    return;
}

/* 00000B34-00000B98       .text setAnm_ATR__11daNpc_Zk1_cFv */
void daNpc_Zk1_c::setAnm_ATR() {

    static daNpc_Zk1_c::anm_prm_c a_anm_prm_tbl[4] = {
        {0, 0, 0, 8., 1., J3DFrameCtrl::EMode_LOOP},
        {1, 0, 0, 8., 1., J3DFrameCtrl::EMode_LOOP},
        {2, 0, 0, 8., 1., J3DFrameCtrl::EMode_LOOP},
        {3, 0, 0, 8., 1., J3DFrameCtrl::EMode_LOOP},
    };
    init_texPttrnAnm(a_anm_prm_tbl[field_0x7A6].btpNum, true);
    setAnm_anm(&a_anm_prm_tbl[field_0x7A6]);
}

/* 00000B98-00000C54       .text anmAtr__11daNpc_Zk1_cFUs */
void daNpc_Zk1_c::anmAtr(u16 i_msgStatus) {
    u8 mesg_anime_tag;
    switch (i_msgStatus) {
        // Enums seen in Hi1
        case fopMsgStts_MSG_TYPING_e: {
            if (field_0x7B1 == 0) {
                chngAnmAtr(dComIfGp_getMesgAnimeAttrInfo());
                field_0x7B1++;
            }
            mesg_anime_tag = dComIfGp_getMesgAnimeTagInfo();
            if(mesg_anime_tag != 0xFF && mesg_anime_tag != mMesgAnimeTag) {
                dComIfGp_clearMesgAnimeTagInfo();
                mMesgAnimeTag = mesg_anime_tag;
                chngAnmTag();
            }
            break;
        }
        case fopMsgStts_MSG_DISPLAYED_e:
            field_0x7B1 = 0;
            break;
    }
    ctrlAnmAtr();
    ctrlAnmTag();
}

/* 00000C54-00000D30       .text next_msgStatus__11daNpc_Zk1_cFPUl */
u16 daNpc_Zk1_c::next_msgStatus(u32* pMsgNo) {

    u16 ret = fopMsgStts_MSG_CONTINUES_e;
    switch(*pMsgNo) {
        case 0x17a2:
            *pMsgNo = 0x17a3;
            break;
        case 0x17a3:
            *pMsgNo = 0x17a4;
            break;
        case 0x17a4:
            *pMsgNo = 0x17a5;
            break;
        case 0x17a5:
            *pMsgNo = 0x17a6;
            break;
        case 0x17a8:
            *pMsgNo = 0x17a9;
            break;
        case 0x17a9:
            *pMsgNo = 0x17aa;
            break;
        case 0x17aa:
            *pMsgNo = 0x17ab;
            break;
        case 0x17ad:
            if (dKy_daynight_check()) {
                *pMsgNo = 0x17af;
            } else {
                *pMsgNo = 0x17ae;
            }
            break;
        default:
            ret = fopMsgStts_MSG_ENDS_e;
            break;
    }
    return ret;

}

/* 00000D30-00000E10       .text getMsg_ZK1_0__11daNpc_Zk1_cFv */
u32 daNpc_Zk1_c::getMsg_ZK1_0() {
    if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_1A80)) {
        return dComIfGs_isEventBit(dSv_event_flag_c::UNK_1802) != 0 ? 0x17A7 : 0x17A2;

    } else if (!field_0x797) {
        return dComIfGs_isEventBit(dSv_event_flag_c::UNK_1802) != 0 ? 0x17AC : 0x17A8;
    } else if (!field_0x798) {
        return dComIfGs_isEventBit(dSv_event_flag_c::UNK_1C01) != 0 ? 0x17B0 : 0x17AD;
    } else {
        return dComIfGs_isEventBit(dSv_event_flag_c::UNK_1D80) != 0 ? 0x17B2 : 0x17B1;
    }
}

/* 00000E10-00000E4C       .text getMsg__11daNpc_Zk1_cFv */
u32 daNpc_Zk1_c::getMsg() {
    u32 temp = 0;
    switch(mSpecificType) {
        case 0:
            temp = getMsg_ZK1_0();
            break;
        default:
            break;
    }
    return temp;
}

/* 00000E4C-00000ED8       .text eventOrder__11daNpc_Zk1_cFv */
void daNpc_Zk1_c::eventOrder() {
    if(field_0x7AA == 1 || field_0x7AA == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if(field_0x7AA == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (field_0x7AA >= 3) {
        mEventIndex = field_0x7AA - 3;
        fopAcM_orderOtherEventId(this, mEventIDTbl[mEventIndex]);
    }
}

/* 00000ED8-00000F8C       .text checkOrder__11daNpc_Zk1_cFv */
void daNpc_Zk1_c::checkOrder() {
    if(eventInfo.checkCommandDemoAccrpt()) {
        if(dComIfGp_evmng_startCheck(mEventIDTbl[mEventIndex]) && field_0x7AA >= 3) {
            field_0x7AA = 0;
            field_0x7A6 = 0xFF;
            mMesgAnimeTag = 0xFF;
        }
    }else if(eventInfo.getCommand() == dEvtCmd_INTALK_e && (field_0x7AA == 1 || field_0x7AA == 2)) {
        field_0x7AA = 0;
        field_0x7A1 = true;
    }
}

/* 00000F8C-00001024       .text chk_talk__11daNpc_Zk1_cFv */
bool daNpc_Zk1_c::chk_talk() {
    if(dComIfGp_event_chkTalkXY()) {
        if(dComIfGp_evmng_ChkPresentEnd()) {
            mItemNo = dComIfGp_event_getPreItemNo();
            return true;
        }
        return false;

    }
    mItemNo = 0xff;
    return true;
}

/* 00001024-00001064       .text chk_parts_notMov__11daNpc_Zk1_cFv */
bool daNpc_Zk1_c::chk_parts_notMov() {
    return mJointHeadY != m_jnt.getHead_y() || 
        mJointBackboneY != m_jnt.getBackbone_y() ||
        mActorAngleY != current.angle.y;
}

/* 00001064-000010B8       .text searchByID__11daNpc_Zk1_cFUiPi */
fopAc_ac_c* daNpc_Zk1_c::searchByID(fpc_ProcID i_PID, int* param_2) {    
    fopAc_ac_c* actor_p;

    actor_p = NULL;
    *param_2 = 0;
    if (!fopAcM_SearchByID(i_PID, &actor_p)) {
        *param_2 = 1;
    }

    return actor_p;
}

/* 000010B8-0000127C       .text lookBack__11daNpc_Zk1_cFv */
void daNpc_Zk1_c::lookBack() {
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
    bool temp_m7A2 = field_0x7A2;

    switch (mLookBackState) {
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
            target_y = field_0x792;
            break;
        case 4:
            {
                int param;
                fopAc_ac_c* actor_p = searchByID(mProcId2, &param);
                if (actor_p && param == 0) {
                    mPlayerEyePos = actor_p->current.pos;
                    mPlayerEyePos.y = actor_p->eyePos.y;
                    player_eye_pos = mPlayerEyePos;
                    player_eye_pos_p = &player_eye_pos;
                }
            }
            break;
        default:
            break;
    }

    m_jnt.lookAtTarget_2(&current.angle.y, player_eye_pos_p, current_pos, target_y, l_HIO.mPrmTbl.mCalcAngleTarget, temp_m7A2);

}

/* 0000127C-000012FC       .text chkAttention__11daNpc_Zk1_cFv */
bool daNpc_Zk1_c::chkAttention() {
    dAttention_c& attention = dComIfGp_getAttention();
    if (attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    } else {
        return this == attention.ActionTarget(0);
    }
}

/* 000012FC-00001354       .text setAttention__11daNpc_Zk1_cFb */
void daNpc_Zk1_c::setAttention(bool i_setEyePos) {
    attention_info.position.set(
        current.pos.x,
        current.pos.y + l_HIO.mPrmTbl.mAttPosOffsetY,
        current.pos.z
    );

    if (!mbSetEyePos && !i_setEyePos) {
        return;
    }

    eyePos.set(
        mTransformedEyePos.x,
        mTransformedEyePos.y,
        mTransformedEyePos.z
    );
}

/* 00001354-000013DC       .text decideType__11daNpc_Zk1_cFi */
bool daNpc_Zk1_c::decideType(int i_type) {
    UNUSED(i_type);
    bool ret;
    if (mType > 0) {
        ret = true;

    } else {
        mType = 1;
        mSpecificType = 0;
        strcpy(mArcName,"Zk");
        ret = false;
        if((mType != -1) && (mSpecificType != -1)) {
            ret = true;
        }
    }
    return ret;
}

/* 000013DC-0000147C       .text privateCut__11daNpc_Zk1_cFi */
void daNpc_Zk1_c::privateCut(int i_staffIdx) {

    static char* a_cut_tbl[] = {
        "DUMMY"
    };

    if(i_staffIdx != -1) {
        mActIdx = dComIfGp_evmng_getMyActIdx(i_staffIdx, a_cut_tbl, ARRAY_SIZE(a_cut_tbl), TRUE, 0);

        if(mActIdx == -1) {
            dComIfGp_evmng_cutEnd(i_staffIdx);
        } else {
             bool temp;
            if(dComIfGp_evmng_getIsAddvance(i_staffIdx)) {
#if VERSION == VERSION_DEMO
                switch(mActIdx) {
                    case 0:
                        speedF = speedF;    //TODO: Fake Match
                        break;
                }
            }
            switch(mActIdx) {
                case 0:
                    break;
                default:
                    temp = true;
                    break;
#endif
            }   
            if(DEMO_SELECT(temp,TRUE)) {
                dComIfGp_evmng_cutEnd(i_staffIdx);
            }
        }
    }
}

/* 0000147C-000014A0       .text endEvent__11daNpc_Zk1_cFv */
void daNpc_Zk1_c::endEvent() {
    dComIfGp_event_reset();
    field_0x7A6 = 0xff;
    mMesgAnimeTag = 0xff;
}

/* 000014A0-000014D8       .text isEventEntry__11daNpc_Zk1_cFv */
int daNpc_Zk1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName());

}

/* 000014D8-0000155C       .text event_proc__11daNpc_Zk1_cFi */
void daNpc_Zk1_c::event_proc(int i_staffIdx) {
    if(dComIfGp_evmng_endCheck(mEventIDTbl[mEventIndex])) {
        endEvent();
    } else {
        if(!mEventCut.cutProc()) {
            privateCut(i_staffIdx);
        }
    }
}

/* 0000155C-00001608       .text set_action__11daNpc_Zk1_cFM11daNpc_Zk1_cFPCvPvPv_iPv */
bool daNpc_Zk1_c::set_action(ProcFunc i_newProcFunc, void* i_argsP) {

    if(mCurrProcFunc != i_newProcFunc){
        if(mCurrProcFunc != 0){
            field_0x7B0 = 9;
            (this->*mCurrProcFunc)(i_argsP);
        }
        mCurrProcFunc = i_newProcFunc;
        field_0x7B0 = 0;
        (this->*mCurrProcFunc)(i_argsP);
    }
    return true;
}

/* 00001608-0000167C       .text setStt__11daNpc_Zk1_cFSc */
void daNpc_Zk1_c::setStt(s8 param_1) {
    s8 temp = mStatus;
    mStatus = param_1;

    switch(mStatus) {
        case 0:
            break;
        case 1:
            field_0x7AA = 0;
            break;
        case 2:
            field_0x7AA = 0;
            field_0x7A6 = 0xff;
            mMesgAnimeTag = 0xff;
            field_0x7B1 = 0;
            field_0x7AC = temp;
            break;

    }
    setAnm();
}

/* 0000167C-000017FC       .text wait_1__11daNpc_Zk1_cFv */
BOOL daNpc_Zk1_c::wait_1() {
    s16 timer = 0;
    if (field_0x7A3) {
        cLib_addCalcAngleS(&current.angle.y, field_0x718.y, 4, 0x800, 0x80);
        timer = field_0x718.y - current.angle.y;
    }
    if(field_0x7A1) {
        if(chk_talk()) {
            setStt(2);
            mLookBackState = 1;
            field_0x7A2 = false;
            field_0x7A3 = false;
            m_jnt.setTrn();
        }
        return TRUE;
    }
    field_0x7AA = 2;
    mLookBackState = 0;
    field_0x7A2 = true;

    if(timer == 0) {
        if(mHasAttention) {
            mTimer2 = cLib_getRndValue(15,30);
        }

        timer = cLib_calcTimer(&mTimer2);
        if(timer != 0) {
            mLookBackState = 1;
        }

        if(dNpc_chkAttn(this, dComIfGp_getPlayer(0)->current.pos, 200.0f, 50.0f,76.0f, mLookBackState == 1) ){
            return TRUE;
        }
        mLookBackState = 0;
        field_0x7A3 = true;
    }
    return TRUE;
}

/* 000017FC-00001920       .text talk_1__11daNpc_Zk1_cFv */
BOOL daNpc_Zk1_c::talk_1() {

    BOOL ret = chk_parts_notMov();
    talk(1);
    if(mpCurrMsg == NULL) {
        return TRUE;
    }
        switch (mpCurrMsg->mStatus) {
    case fopMsgStts_BOX_OPENING_e:
    case fopMsgStts_MSG_TYPING_e:
        break;
    case fopMsgStts_MSG_DESTROYED_e:
        switch (mCurrMsgNo) {
        case 0x17A6:
        case 0x17AB:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_1802);
            break;
        case 0x17AE:
        case 0x17AF:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_1C01);
            break;
        case 0x17B1:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_1D80);
        }
        mItemNo = 0xFF;
        field_0x7A1 = false;
        setStt(field_0x7AC);
        mTimer2 = cLib_getRndValue(15, 30);
        endEvent();
        break;  
    }
    return ret;
}

/* 00001920-000019DC       .text wait_action1__11daNpc_Zk1_cFPv */
BOOL daNpc_Zk1_c::wait_action1(void* param_1) {
    UNUSED(param_1);

    switch(field_0x7B0) {
        case 0:
            setStt(1);
            field_0x7A3 = 1;
            field_0x7B0++;
            break;
        case 1:
        case 2:
        case 3:
            mHasAttention = chkAttention();
            switch(mStatus) {
                case 1:
                    mbSetEyePos = wait_1();
                    break;
                case 2:
                    mbSetEyePos = talk_1();
                    break;
            }
        case 9: 
            break;
    }

    return TRUE;
}

/* 000019DC-00001B1C       .text demo__11daNpc_Zk1_cFv */
u8 daNpc_Zk1_c::demo() {
    if (demoActorID == 0) {
        if (field_0x7A4 != 0) {
            field_0x7A4 = FALSE;
        }
    } else {
        if(!field_0x7A4) {
            field_0x7A4 = 1;
            field_0x79D = 0;
            m_jnt.setHead_y(0);
            m_jnt.setHead_x(0);
            m_jnt.setBackBone_y(0);
            m_jnt.setBackBone_x(0);

        }
        dDemo_actor_c* demo_actor = dComIfGp_demo_getActor(demoActorID);
        
        J3DAnmTexPattern* btp = mBtpAnm.getBtpAnm();
        if(btp != NULL) {
            s16 frame = btp->getFrameMax() & 0xff;
            mBtpFrame++;
            if((u16)mBtpFrame >= (u16)frame) {
                mBtpFrame = frame;
            }
        }

        btp = demo_actor->getP_BtpData(mArcName);
        if(btp != NULL) {
            mBtpAnm.init(mpMorf->getModel()->getModelData(), btp, 1, 0, 1.0f, 0, -1, true, 0);
            mBtpNum = 1;
            mBtpFrame = 0;
        }

        dDemo_setDemoData(this,
            dDemo_actor_c::ENABLE_TRANS_e | dDemo_actor_c::ENABLE_ROTATE_e | dDemo_actor_c::ENABLE_ANM_e | dDemo_actor_c::ENABLE_ANM_FRAME_e,
            mpMorf, 
            mArcName
        );
    }
    return field_0x7A4;
}

/* 00001B1C-00001BAC       .text shadowDraw__11daNpc_Zk1_cFv */
void daNpc_Zk1_c::shadowDraw() {
    cXyz pos(current.pos.x,current.pos.y+150.0f,current.pos.z);

    mShadowId = dComIfGd_setShadow(
        mShadowId, 
        1,
        mpMorf->getModel(), 
        &pos, 800.0f, 40.0f, current.pos.y, 
        mObjAcch.GetGroundH(), mObjAcch.m_gnd, 
        &tevStr, 0, 1.0f, dDlst_shadowControl_c::getSimpleTex()
    );
}


static void dummy() {
    const GXColor dummy1 = { 0xFF, 0x00, 0x00, 0x80 };
    const GXColor dummy2 = { 0x00, 0x00, 0xFF, 0x80 };

}
    

/* 00001BAC-00001C80       .text _draw__11daNpc_Zk1_cFv */
BOOL daNpc_Zk1_c::_draw() {

    J3DModel* pModel = mpMorf->getModel();
    J3DModelData* modelData = pModel->getModelData();

    if(field_0x79C || field_0x79E) {
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(pModel, &tevStr);
    mBtpAnm.entry(modelData, mBtpFrame);
    mpMorf->entryDL();
    mBtpAnm.remove(modelData);
    shadowDraw();
    dSnap_RegistFig(DSNAP_TYPE_NPC_ZK1, this, 1.0, 1.0, 1.0);
    return TRUE;
}

/* 00001C80-00001EA8       .text _execute__11daNpc_Zk1_cFv */
BOOL daNpc_Zk1_c::_execute() {

    if(!field_0x79F) {
        field_0x70C = current.pos;
        field_0x718 = current.angle;
        field_0x79F = TRUE;
    }
    m_jnt.setParam(
        l_HIO.mPrmTbl.mMaxBackboneX,
        l_HIO.mPrmTbl.mMaxBackboneY,
        l_HIO.mPrmTbl.mMinBackboneX,
        l_HIO.mPrmTbl.mMinBackboneY,
        l_HIO.mPrmTbl.mMaxHeadX,
        l_HIO.mPrmTbl.mMaxHeadY,
        l_HIO.mPrmTbl.mMinHeadX,
        l_HIO.mPrmTbl.mMinHeadY,
        l_HIO.mPrmTbl.mMaxTurnStep
    );

    if (field_0x79C && demoActorID == 0) {
        return TRUE;
    }
    checkOrder();
    if (!demo()) {
        int staff_id = -1;
        if (dComIfGp_event_runCheck() && eventInfo.checkCommandTalk() == false) {
            staff_id = isEventEntry();
        }

        if (staff_id >= 0 || field_0x79A) {
            event_proc(staff_id);
        } else {
            (this->*mCurrProcFunc)(NULL);
        }

        lookBack();

        fopAcM_posMoveF(this, mStts.GetCCMoveP());
        mObjAcch.CrrPos(*dComIfG_Bgsp());

        play_animation();
    } else {
        field_0x79C = false;
    }
    eventOrder();
    mAngle = current.angle;
    if (!field_0x79D) {
        shape_angle = current.angle;
    }
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    setMtx(false);

    if (!field_0x7A4) {
        setCollision(80.0f, 220.0f);
    }

    return TRUE;

}

/* 00001EA8-00001EFC       .text _delete__11daNpc_Zk1_cFv */
BOOL daNpc_Zk1_c::_delete() {

    if(DEMO_SELECT(mbResLoadIsComplete,TRUE)){
#if VERSION == VERSION_DEMO
        l_HIO.removeHIO();
#endif
        dComIfG_resDelete(&mPhs, mArcName);
    
        if (DEMO_SELECT(mpMorf, heap && mpMorf)) {
            mpMorf->stopZelAnime();
        }
    }
    return TRUE;
}

/* 00001EFC-00002148       .text _create__11daNpc_Zk1_cFv */
cPhs_State daNpc_Zk1_c::_create() {

        static int a_siz_tbl[] = {
        0,
        0
    };

    cPhs_State state;
    fopAcM_ct_Retail(this, daNpc_Zk1_c);
    if(!decideType(fopAcM_GetParam(this) & 0xFF)) {
        return cPhs_ERROR_e;
    }

    state = dComIfG_resLoad(&mPhs, mArcName);
    mbResLoadIsComplete = state == cPhs_COMPLEATE_e;
    if(!mbResLoadIsComplete) {
        return state;
    } 
#if VERSION == VERSION_DEMO
    l_HIO.entryHIO("親方様"); //Chief
#endif
    fopAcM_ct_Demo(this,daNpc_Zk1_c);
    if(!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_siz_tbl[mType])) {
#if VERSION == VERSION_DEMO
        mbResLoadIsComplete = 0;
#endif
        return cPhs_ERROR_e;
    }
    fopAcM_SetMtx(this, this->mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -70.0f, -20.0f, -70.0f, 70.0f, 240.0f, 70.0f);

    if(createInit() == 0) {
        return cPhs_ERROR_e;
    }
    return state;
}


/* 00002414-00002688       .text bodyCreateHeap__11daNpc_Zk1_cFv */
BOOL daNpc_Zk1_c::bodyCreateHeap() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes(mArcName, dRes_ID_ZK_BDL_ZK_e);
    JUT_ASSERT(DEMO_SELECT(0x5B5,0x5B3), a_mdl_dat != NULL);
    mpMorf = new mDoExt_McaMorf(
        a_mdl_dat,
        NULL, NULL,
         NULL,
        J3DFrameCtrl::EMode_NULL, 
        1.0f, 0, -1, 1, 
        NULL,
        0x80000, 
        0x11020022
    );

    if(!mpMorf){
        return FALSE;
    } else if(mpMorf->getModel() == NULL) {
        mpMorf = NULL;
        return FALSE;
    }
    
    if(!init_texPttrnAnm(0, false)) {
        mpMorf = NULL;
        return FALSE;
    }
    m_hed_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
    JUT_ASSERT(DEMO_SELECT(0x5C9,0x5C7), m_hed_jnt_num >= 0);
    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(DEMO_SELECT(0x5CB,0x5C9), m_bbone_jnt_num >= 0);

    mpMorf->getModel()->getModelData()->getJointNodePointer(m_hed_jnt_num & 0xffff)->setCallBack(nodeCB_Head);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_bbone_jnt_num & 0xffff)->setCallBack(nodeCB_BackBone);
    mpMorf->getModel()->setUserArea((u32)(this));

    return TRUE;
}

/* 00002688-0000270C       .text CreateHeap__11daNpc_Zk1_cFv */
BOOL daNpc_Zk1_c::CreateHeap() {

    if(!bodyCreateHeap()) {
        return FALSE;
    }
    mAcchCir.SetWall(30.0f, 80.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this));
    return TRUE;
}

/* 0000270C-0000272C       .text daNpc_Zk1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Zk1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Zk1_c*)i_this)->_create();
}

/* 0000272C-0000274C       .text daNpc_Zk1_Delete__FP11daNpc_Zk1_c */
static BOOL daNpc_Zk1_Delete(daNpc_Zk1_c* i_this) {
    return ((daNpc_Zk1_c*)i_this)->_delete();
}

/* 0000274C-0000276C       .text daNpc_Zk1_Execute__FP11daNpc_Zk1_c */
static BOOL daNpc_Zk1_Execute(daNpc_Zk1_c* i_this) {
    return ((daNpc_Zk1_c*)i_this)->_execute();
}

/* 0000276C-0000278C       .text daNpc_Zk1_Draw__FP11daNpc_Zk1_c */
static BOOL daNpc_Zk1_Draw(daNpc_Zk1_c* i_this) {
    return ((daNpc_Zk1_c*)i_this)->_draw();
}

/* 0000278C-00002794       .text daNpc_Zk1_IsDelete__FP11daNpc_Zk1_c */
static BOOL daNpc_Zk1_IsDelete(daNpc_Zk1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Zk1_Method = {
    (process_method_func)daNpc_Zk1_Create,
    (process_method_func)daNpc_Zk1_Delete,
    (process_method_func)daNpc_Zk1_Execute,
    (process_method_func)daNpc_Zk1_IsDelete,
    (process_method_func)daNpc_Zk1_Draw,
};

actor_process_profile_definition g_profile_NPC_ZK1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_ZK1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Zk1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_ZK1_e,
    /* Actor SubMtd */ &l_daNpc_Zk1_Method,
    /* Status       */ 0x08 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
