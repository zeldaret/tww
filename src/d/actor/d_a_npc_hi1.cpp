/**
 * d_a_npc_hi1.cpp
 * NPC - King of Hyrule
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_hi1.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/res/res_hi.h"

extern dCcD_SrcCyl dNpc_cyl_src;

class daNpc_Hi1_HIO_c : public mDoHIO_entry_c{
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
        s16 field_12;
        f32 mAttentionYOffset;
        f32 field_18;
    };  // Size: 0x1C

    daNpc_Hi1_HIO_c();
    virtual ~daNpc_Hi1_HIO_c() {};

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ s8 field_0x5;
    /* 0x06 */ s8 field_0x6;
    /* 0x07 */ s8 field_0x7;
    /* 0x08 */ int field_0x8;
    /* 0x0C */ hio_prm_c mPrmTbl;
    /* Place member variables here */
};

static daNpc_Hi1_HIO_c l_HIO;
static fopAc_ac_c* l_check_inf[20];
static int l_check_wrk;

/* 000000EC-00000150       .text __ct__15daNpc_Hi1_HIO_cFv */
daNpc_Hi1_HIO_c::daNpc_Hi1_HIO_c() {
    static hio_prm_c a_prm_tbl = {
        0x0000,
        0x1FFE,
        0xF600,
        0xE002,
        0x0000,
        0x0744,
        0xF9DA,
        0xF8BC,
        0x0258,
        0x0000,
        270.0f,
        0.0f
    };
    memcpy(&mPrmTbl,&a_prm_tbl,0x1c);
    mNo = -1;
    field_0x8 = -1;
}

static const char* l_evn_tbl = "dummy";

/* 00000198-000001E4       .text nodeCB_Head__FP7J3DNodei */
static BOOL nodeCB_Head(J3DNode* i_node, int i_param) {
    if(i_param == 0) {
        daNpc_Hi1_c* actor = (daNpc_Hi1_c*)j3dSys.getModel()->getUserArea();
        if(actor != NULL) {
            actor->_nodeCB_Head(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 000001E4-00000304       .text _nodeCB_Head__11daNpc_Hi1_cFP7J3DNodeP8J3DModel */
void daNpc_Hi1_c::_nodeCB_Head(J3DNode* i_node, J3DModel* i_pModel) {
    static cXyz a_eye_pos_off(20.0f, 30.0f, 0.0f);

    u16 jointIdx = ((J3DJoint*)(i_node))->getJntNo();
    mDoMtx_stack_c::copy(i_pModel->getAnmMtx(jointIdx));

    mDoMtx_stack_c::multVecZero(&field_0x768);
    mDoMtx_stack_c::multVec(&a_eye_pos_off, &field_0x744);
    mDoMtx_stack_c::XrotM(m_jnt.getHead_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    MTXCopy(mDoMtx_stack_c::get(), i_pModel->getAnmMtx(jointIdx));
}

/* 00000340-0000038C       .text nodeCB_BackBone__FP7J3DNodei */
static BOOL nodeCB_BackBone(J3DNode* i_node, int i_param) {
    if(i_param == 0) {
        daNpc_Hi1_c* actor = (daNpc_Hi1_c*)j3dSys.getModel()->getUserArea();
        if(actor != NULL) {
            actor->_nodeCB_BackBone(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 0000038C-0000042C       .text _nodeCB_BackBone__11daNpc_Hi1_cFP7J3DNodeP8J3DModel */
void daNpc_Hi1_c::_nodeCB_BackBone(J3DNode* i_node, J3DModel* i_pModel) {
    u16 jointIdx = ((J3DJoint*)(i_node))->getJntNo();
    mDoMtx_stack_c::copy(i_pModel->getAnmMtx(jointIdx));
    mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getBackbone_x());
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    MTXCopy(mDoMtx_stack_c::get(), i_pModel->getAnmMtx(jointIdx));
}

/* 0000042C-0000044C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* ac) {
    return ((daNpc_Hi1_c*)ac)->CreateHeap();
}

/* 0000044C-00000498       .text init_HI1_0__11daNpc_Hi1_cFv */
bool daNpc_Hi1_c::init_HI1_0() {
    set_action(&daNpc_Hi1_c::wait_action1,NULL);
    return true;
}

/* 00000498-00000618       .text createInit__11daNpc_Hi1_cFv */
bool daNpc_Hi1_c::createInit() {
    bool ret;

    mEventIdx[0] = dComIfGp_evmng_getEventIdx(l_evn_tbl, 0xff);
    mEventCut.setActorInfo2("Hi1", this);
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    
    switch(field_0x7C6) {
        case 0:
        break;
    }

    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xA9;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xA9;

    gravity = 0.0f;
    field_0x7C0 = 2;

    switch(field_0x7C6) {
        case 0:
            ret = init_HI1_0();
            break;
        default:
            ret = false;
    }
    if(!ret) {
        return false;
    }

    field_0x736 = current.angle;
    shape_angle = field_0x736;
    mStts.Init(0xff, 0xff, this);
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

/* 00000618-000006C8       .text play_animation__11daNpc_Hi1_cFv */
void daNpc_Hi1_c::play_animation() {
    u32 mtrlSndId = 0;
    play_btp_anm();
    play_btk_anm();
    if(mObjAcch.ChkGroundHit()) {
        mtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
    }

    field_0x7AC = mpMorf->play(&eyePos, mtrlSndId, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
    if(mpMorf->getFrame() < mFrame) {
        field_0x7AC = 1;
    }
    mFrame = mpMorf->getFrame();
}

/* 000006C8-00000778       .text setMtx__11daNpc_Hi1_cFb */
void daNpc_Hi1_c::setMtx(bool param_1) {
    mpMorf->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(field_0x736);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    setAttention(param_1);
}

/* 00000778-0000078C       .text bckResID__11daNpc_Hi1_cFi */
int daNpc_Hi1_c::bckResID(int idx) {
    static const int a_resID_tbl[] = {
        1,
        0
    };
    return a_resID_tbl[idx];
}

/* 0000078C-000007A0       .text btpResID__11daNpc_Hi1_cFi */
int daNpc_Hi1_c::btpResID(int idx) {
    static const int a_resID_tbl[] = {
        3
    };
    return a_resID_tbl[idx];
}

/* 000007A0-000007B4       .text btkResID__11daNpc_Hi1_cFi */
int daNpc_Hi1_c::btkResID(int idx) {
    static const int a_resID_tbl[] = {
        4
    };
    return a_resID_tbl[idx];
}

/* 000007B4-000008B8       .text setBtp__11daNpc_Hi1_cFScb */
bool daNpc_Hi1_c::setBtp(s8 param_1, bool param_2) {
    J3DModel* model = mpMorf->getModel();
    if(param_1 < 0) {
        return false;
    }
    int resID = btpResID((int)param_1) ;
    J3DAnmTexPattern* a_btp = (J3DAnmTexPattern *)dComIfG_getObjectIDRes(mArcName, resID);
    JUT_ASSERT(0x192, a_btp != NULL);
    field_0x7BE = param_1;
    mBtpAnmFrame = 0;
    mTimer1 = 0;

    return mBtpAnm.init(model->getModelData(), a_btp,J3DFrameCtrl::EMode_RESET, 0, 1.0f, 0, -1, param_2, 0) != 0;
}

/* 000008B8-000009B8       .text setBtk__11daNpc_Hi1_cFScb */
bool daNpc_Hi1_c::setBtk(s8 param_1, bool param_2) {
    J3DModel* model = mpMorf->getModel();
    if(param_1 < 0) {
        return false;
    }
    int resID = btkResID((int)param_1);
    J3DAnmTextureSRTKey* a_btk = (J3DAnmTextureSRTKey *)dComIfG_getObjectIDRes(mArcName, resID);

    JUT_ASSERT(0x1aa, a_btk != NULL);
    field_0x7BF  = param_1;
    mBtkAnmFrame = 0;
    return mBtkAnm.init(model->getModelData(), a_btk,J3DFrameCtrl::EMode_RESET, 0, 1.0f, 0, -1, param_2, 0) != 0;
}

/* 000009B8-00000A24       .text init_texPttrnAnm__11daNpc_Hi1_cFScb */
bool daNpc_Hi1_c::init_texPttrnAnm(s8 param_1, bool param_2) {
    static const u8 a_btk_num_tbl[] = {
        0
    };

    if(setBtp(param_1, param_2) == false) {
        return false;
    }
    return setBtk(a_btk_num_tbl[param_1], param_2);

}

/* 00000A24-00000AC0       .text play_btp_anm__11daNpc_Hi1_cFv */
void daNpc_Hi1_c::play_btp_anm() {
    u16 frame = mBtpAnm.getBtpAnm()->getFrameMax() & 0xff;
    if(field_0x7BE != 0 || cLib_calcTimer(&mTimer1) == 0) {
        mBtpAnmFrame ++;
        if((u16)mBtpAnmFrame >= frame) {
            if(field_0x7BE != 0) {
                mBtpAnmFrame = frame;
            } else {
                mTimer1 = cLib_getRndValue(0x3c,0x5a);
                mBtpAnmFrame = 0;
            }
        }
    }
}

/* 00000AC0-00000AEC       .text play_btk_anm__11daNpc_Hi1_cFv */
void daNpc_Hi1_c::play_btk_anm() {
    u16 frame = mBtkAnm.getBtkAnm()->getFrameMax() & 0xff;
    mBtkAnmFrame++;
    if((u16)mBtkAnmFrame >= frame) {
        mBtkAnmFrame = frame;
    }
}

/* 00000AEC-00000B88       .text setAnm_anm__11daNpc_Hi1_cFPQ211daNpc_Hi1_c9anm_prm_c */
void daNpc_Hi1_c::setAnm_anm(daNpc_Hi1_c::anm_prm_c* param_1) {
    s8 temp = param_1->field_0x0;
    if(temp < 0 || field_0x7C0 == temp) {
        return;
    }
    dNpc_setAnmIDRes(mpMorf,
        param_1->field_0xC,
        param_1->field_0x4,
        param_1->field_0x8,
        bckResID(temp),
        -1,
        mArcName
    );
    field_0x7C0 = param_1->field_0x0;
    field_0x7AC = 0;
    field_0x7AD = 0;
    mFrame = 0.0f;
}

/* 00000B88-00000BF8       .text setAnm_NUM__11daNpc_Hi1_cFii */
void daNpc_Hi1_c::setAnm_NUM(int param_1, int param_2) {
    static daNpc_Hi1_c::anm_prm_c a_anm_prm_tbl[2] = {
        {0, 0, 8.0f, 1.0f, 2},
        {1, 0, 8.0f, 1.0f, 2},
    };
    
    if(param_2 != 0) {
        init_texPttrnAnm(a_anm_prm_tbl[param_1].field_0x1, true);
    }
    setAnm_anm(&a_anm_prm_tbl[param_1]);
}

/* 00000BF8-00000C64       .text setAnm__11daNpc_Hi1_cFv */
void daNpc_Hi1_c::setAnm() {
    static daNpc_Hi1_c::anm_prm_c a_anm_prm_tbl[3] = {
        {-1, -1, 0.0f, 0.0f, -1},
        {0, 0, 8.0f, 1.0f, 2},
        {-1, -1, 0.0f, 0.0f, -1}
    };
    init_texPttrnAnm(a_anm_prm_tbl[field_0x7C2].field_0x1, true);
    setAnm_anm(&a_anm_prm_tbl[field_0x7C2]);
}

/* 00000C64-00000C68       .text chngAnmTag__11daNpc_Hi1_cFv */
void daNpc_Hi1_c::chngAnmTag() {
}

/* 00000C68-00000C6C       .text ctrlAnmTag__11daNpc_Hi1_cFv */
void daNpc_Hi1_c::ctrlAnmTag() {
}

/* 00000C6C-00000CAC       .text chngAnmAtr__11daNpc_Hi1_cFUc */
void daNpc_Hi1_c::chngAnmAtr(u8 param_1) {
    if(param_1 == field_0x7BC || param_1 > 2) {
        return;
    }
    field_0x7BC = param_1;
    setAnm_ATR();
}

/* 00000CAC-00000CB8       .text ctrlAnmAtr__11daNpc_Hi1_cFv */
void daNpc_Hi1_c::ctrlAnmAtr() {
    if(field_0x7BC == (s8)2) {
        return;
    }
}

/* 00000CB8-00000D1C       .text setAnm_ATR__11daNpc_Hi1_cFv */
void daNpc_Hi1_c::setAnm_ATR() {
    static daNpc_Hi1_c::anm_prm_c a_anm_prm_tbl[2] = {
        {0, 0, 8.0f, 1.0f, 2},
        {1, 0, 8.0f, 1.0f, 2},
    };
    init_texPttrnAnm(a_anm_prm_tbl[field_0x7BC].field_0x1, true);
    setAnm_anm(&a_anm_prm_tbl[field_0x7BC]);
}

/* 00000D1C-00000DD8       .text anmAtr__11daNpc_Hi1_cFUs */
void daNpc_Hi1_c::anmAtr(u16 i_msgStatus) {
    switch (i_msgStatus) {
        case fopMsgStts_MSG_TYPING_e: {
            if(field_0x7C8 == 0) {
                chngAnmAtr(dComIfGp_getMesgAnimeAttrInfo());
                field_0x7C8++;
            }
            u8 tagInfo = dComIfGp_getMesgAnimeTagInfo();
            if(tagInfo != 0xFF && tagInfo != field_0x7BD){
                dComIfGp_clearMesgAnimeTagInfo();
                field_0x7BD = tagInfo;
                chngAnmTag();
            }
            break;
        }
        case fopMsgStts_MSG_DISPLAYED_e:
            field_0x7C8 = 0;
            break;
        default:
            break;
    }
    ctrlAnmAtr();
    ctrlAnmTag();
}

/* 00000DD8-00000DE0       .text next_msgStatus__11daNpc_Hi1_cFPUl */
u16 daNpc_Hi1_c::next_msgStatus(u32* pMsgNo) {
    return fopMsgStts_MSG_ENDS_e;
}

/* 00000DE0-00000DE8       .text getMsg_HI1_0__11daNpc_Hi1_cFv */
u32 daNpc_Hi1_c::getMsg_HI1_0() {
    return 0;
}

/* 00000DE8-00000E24       .text getMsg__11daNpc_Hi1_cFv */
    u32 daNpc_Hi1_c::getMsg() {
        u32 msgNo = 0;

    switch(field_0x7C6) {
        case 0:
            msgNo = getMsg_HI1_0();
            break;
        default:
            break;
    }
    return msgNo;
}

/* 00000E24-00000EB0       .text eventOrder__11daNpc_Hi1_cFv */
void daNpc_Hi1_c::eventOrder() {
    if(field_0x7C1 == 1 || field_0x7C1 == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);

        if(field_0x7C1 == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if(field_0x7C1 >= 3) {
        mEventIdx[1] = field_0x7C1 - 3;
        fopAcM_orderOtherEventId(this, mEventIdx[mEventIdx[1]]);
    }
}

/* 00000EB0-00000F64       .text checkOrder__11daNpc_Hi1_cFv */
void daNpc_Hi1_c::checkOrder() {
    if(eventInfo.checkCommandDemoAccrpt()) {
        if(dComIfGp_evmng_startCheck(mEventIdx[mEventIdx[1]]) && field_0x7C1 >= 3) {
            field_0x7C1 = 0;
            field_0x7BC = 0xff;
            field_0x7BD = 0xff;
        }
    } else if(eventInfo.mCommand == dEvtCmd_INTALK_e && (field_0x7C1 == 1 || field_0x7C1 == 2)) {
        field_0x7C1 = 0;
        field_0x7B7 = true;
    }
}

/* 00000F64-00000FFC       .text chk_talk__11daNpc_Hi1_cFv */
bool daNpc_Hi1_c::chk_talk() {
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

/* 00000FFC-0000103C       .text chk_parts_notMov__11daNpc_Hi1_cFv */
bool daNpc_Hi1_c::chk_parts_notMov() {
    bool ret = false;
    if(field_0x788.y != m_jnt.getHead_y() ||
        field_0x788.z != m_jnt.getBackbone_y() ||
        field_0x788.x != current.angle.y) {
        ret = true;
    }
    return ret;
}

/* 0000103C-00001090       .text searchByID__11daNpc_Hi1_cFUiPi */
fopAc_ac_c* daNpc_Hi1_c::searchByID(fpc_ProcID pid, int* param_2) {
    fopAc_ac_c* actor = NULL;
    *param_2 = 0;
    
    int temp = fopAcM_SearchByID(pid, &actor);
    if(temp == 0) {
        *param_2 = 1;
    }
    return actor;
}

/* 00001090-00001254       .text lookBack__11daNpc_Hi1_cFv */
void daNpc_Hi1_c::lookBack() {
    int temp3;
    field_0x788.y = m_jnt.getHead_y();
    field_0x788.z = m_jnt.getBackbone_y();
    field_0x788.x = current.angle.y;
    cXyz temp5;
    cXyz temp(current.pos);
    temp.y = eyePos.y;
    temp5.set(0.0f, 0.0f, 0.0f);
    cXyz* temp2 = NULL;
    s16 targetY = current.angle.y;
    bool temp4 = field_0x7B8;

    switch(field_0x7C4) {
        case 1:
            field_0x750.set(dNpc_playerEyePos(-20.0f));
            temp5 = field_0x750;
            temp2 = &temp5;
            break;
        case 2:
            temp5.set(field_0x750);
            temp2 = &temp5;
            break;
        case 3:
            targetY = field_0x7AA;
            break;
        case 4:
            fopAc_ac_c* actor = searchByID(mPId, &temp3);
            if(actor != NULL && temp3 == 0) {
                field_0x750.set(actor->current.pos);
                field_0x750.y = actor->eyePos.y;
                temp5.set(field_0x750);
                temp2 = &temp5;
            }
            break;
    }

    m_jnt.lookAtTarget_2(&current.angle.y, temp2, temp, targetY, l_HIO.mPrmTbl.field_12, temp4);
}

/* 00001254-000012D4       .text chkAttention__11daNpc_Hi1_cFv */
bool daNpc_Hi1_c::chkAttention() {
    if(dComIfGp_getAttention().LockonTruth()) {
        return this == dComIfGp_getAttention().LockonTarget(0);

    }
    return this == dComIfGp_getAttention().ActionTarget(0);
}

/* 000012D4-0000132C       .text setAttention__11daNpc_Hi1_cFb */
void daNpc_Hi1_c::setAttention(bool param_1) {
    attention_info.position.set(current.pos.x, current.pos.y + l_HIO.mPrmTbl.mAttentionYOffset, current.pos.z);
    if(field_0x790 == 0 && !param_1) {
        return;
    }
    eyePos.set(field_0x744.x, field_0x744.y, field_0x744.z);
}

/* 0000132C-000013B4       .text decideType__11daNpc_Hi1_cFi */
bool daNpc_Hi1_c::decideType(int param_1) {
    bool temp;
    if(field_0x7C5 > 0) {
        temp = true;
    } else {
        field_0x7C5 = 1;
        field_0x7C6 = 0;
        strcpy(mArcName,"Hi");
        temp = false;
        if((field_0x7C5 != -1) && (field_0x7C6 != -1)) {
            temp = true;
        }
    }
    return temp;
}

/* 000013B4-00001454       .text privateCut__11daNpc_Hi1_cFi */
void daNpc_Hi1_c::privateCut(int i_staffIdx) {
    static char* a_cut_tbl[] = {
        "DUMMY"
    };

    if(i_staffIdx != -1) {
        mActIdx = dComIfGp_evmng_getMyActIdx(i_staffIdx, a_cut_tbl, 1, TRUE, 0);

        if(mActIdx == -1) {
            dComIfGp_evmng_cutEnd(i_staffIdx);
        } else {
            dComIfGp_evmng_getIsAddvance(i_staffIdx);
            dComIfGp_evmng_cutEnd(i_staffIdx);
        }
    }
}

/* 00001454-00001478       .text endEvent__11daNpc_Hi1_cFv */
void daNpc_Hi1_c::endEvent() {
    dComIfGp_event_reset();
    field_0x7BC = 0xff;
    field_0x7BD = 0xff;
}

/* 00001478-000014B0       .text isEventEntry__11daNpc_Hi1_cFv */
int daNpc_Hi1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName());
}

/* 000014B0-00001534       .text event_proc__11daNpc_Hi1_cFi */
void daNpc_Hi1_c::event_proc(int i_staffIdx) {    
    if(dComIfGp_evmng_endCheck(mEventIdx[mEventIdx[1]])) {
        endEvent();
    } else {
        if(!mEventCut.cutProc()) {
            privateCut(i_staffIdx);
        }
    }
}

/* 00001534-000015E0       .text set_action__11daNpc_Hi1_cFM11daNpc_Hi1_cFPCvPvPv_iPv */
bool daNpc_Hi1_c::set_action(ActionFunc i_action, void* param_2) {
    if(mCurrActionFunc != i_action){
        if(mCurrActionFunc != 0){
            field_0x7C7 = 9;
            (this->*mCurrActionFunc)(param_2);
        }
        mCurrActionFunc = i_action;
        field_0x7C7 = 0;
        (this->*mCurrActionFunc)(param_2);
    }
    return true;
}

/* 000015E0-00001654       .text setStt__11daNpc_Hi1_cFSc */
void daNpc_Hi1_c::setStt(s8 param_1) {
    s8 temp = field_0x7C2;
    field_0x7C2 = param_1;

    switch(field_0x7C2) {
        case 0:
            break;
        case 1:
            field_0x7C1 = 0;
            break;
        case 2:
            field_0x7C1 = 0;
            field_0x7BC = 0xff;
            field_0x7BD = 0xff;
            field_0x7C8 = 0;
            field_0x7C3 = temp;
            break;

    }
    setAnm();
}

/* 00001654-000017D4       .text wait_1__11daNpc_Hi1_cFv */
BOOL daNpc_Hi1_c::wait_1() {
    s16 timer = 0;
    if(field_0x7B9) {
        cLib_addCalcAngleS(&current.angle.y, field_0x730.y, 4, 0x800, 0x80);
        timer = field_0x730.y - current.angle.y;
    }

    if(field_0x7B7) {
        if(chk_talk()) {
            setStt(2);
            field_0x7C4 = 1;
            field_0x7B8 = false;
            field_0x7B9 = false;
            m_jnt.setTrn();
        }
        return TRUE;
    }
    field_0x7C1 = 2;
    field_0x7C4 = 0;
    field_0x7B8 = true;

    if(timer == 0) {
        if(mHasAttention) {
            mTimer2 = cLib_getRndValue(0xf,0x1e);
        }

        timer = cLib_calcTimer(&mTimer2);
        if(timer != 0) {
            field_0x7C4 = 1;
        }

        if(dNpc_chkAttn(this, dComIfGp_getPlayer(0)->current.pos, 200.0f, 50.0f, 55.0f, field_0x7C4 == 1) ){
            return TRUE;
        }
        field_0x7C4 = 0;
        field_0x7B9 = true;
    }
    return TRUE;
}

/* 000017D4-0000189C       .text talk_1__11daNpc_Hi1_cFv */
BOOL daNpc_Hi1_c::talk_1() {
    BOOL ret = chk_parts_notMov();
    talk(1);
    if(mpCurrMsg == NULL) {
        return TRUE;
    }
    switch(mpCurrMsg->mStatus) {
        case 6:
        case 2:
            break;
        case 19:
            mItemNo = 0xFF;
            field_0x7B7 = false;
            setStt(field_0x7C3);
            setAnm_NUM(0, 1);
            mTimer2 = cLib_getRndValue(0xf, 0x1e);
            endEvent();
            break;
    }
    return ret;
}

/* 0000189C-00001958       .text wait_action1__11daNpc_Hi1_cFPv */
int daNpc_Hi1_c::wait_action1(void*) {
    switch (field_0x7C7) {
        case 0:
            setStt(1);
            field_0x7B9 = true;
            field_0x7C7++;
            break;
        case 1:
        case 2:
        case 3:
            mHasAttention = chkAttention();
            switch (field_0x7C2) {
            case 1:
                field_0x790 = wait_1();
                break;
            case 2:
                field_0x790 = talk_1();
                break;
            }
        case 9:
            break;
    }
    return 1;
}

/* 00001958-00001B34       .text demo__11daNpc_Hi1_cFv */
u8 daNpc_Hi1_c::demo() {
    if(demoActorID == 0) {
        if(field_0x7BA){
            field_0x7BA = false;
        }
    } else {
        if(!field_0x7BA){
            field_0x7BA = true;
            field_0x7B3 = false;
            m_jnt.setHead_y(0);
            m_jnt.setHead_x(0);
            m_jnt.setBackBone_y(0);
            m_jnt.setBackBone_x(0);   
        }

        dDemo_actor_c* demo_actor = dComIfGp_demo_getActor(demoActorID);

        J3DAnmTexPattern* btp = mBtpAnm.getBtpAnm();
        if(btp != NULL) {
            s16 frame = btp->getFrameMax() & 0xff;
            mBtpAnmFrame++;
            if((u16)mBtpAnmFrame >= (u16)frame) {
                mBtpAnmFrame = frame;
            }
        }

        btp = demo_actor->getP_BtpData(mArcName);
        if(btp != NULL) {
            mBtpAnm.init(mpMorf->getModel()->getModelData(), btp, 1, 0, 1.0f, 0, -1, true, 0);
            field_0x7BE = 1;
            mBtpAnmFrame = 0;
        }

        J3DAnmTextureSRTKey* btk = mBtkAnm.getBtkAnm();
        if(btk != NULL) {
            s16 frame = (btk->getFrameMax() & 0xff);
            mBtkAnmFrame++;
            if((u16)mBtkAnmFrame >= (u16)frame) {
                mBtkAnmFrame = frame;
            }
        }

        btk = demo_actor->getP_BtkData(mArcName);
        if(btk != NULL) {
            mBtkAnm.init(mpMorf->getModel()->getModelData(), btk, 1, 0, 1.0f, 0, -1, true, 0);
            field_0x7BF = 1;
            mBtkAnmFrame = 0;
        }
        dDemo_setDemoData(this, 0x6a, mpMorf, mArcName);
    }
    return field_0x7BA;
}

/* 00001B34-00001BC4       .text shadowDraw__11daNpc_Hi1_cFv */
void daNpc_Hi1_c::shadowDraw() {
    cXyz pos(current.pos.x,current.pos.y+150.0f,current.pos.z);

    mShadowId = dComIfGd_setShadow(
        mShadowId, 1, mpMorf->getModel(), 
        &pos, 800.0f, 40.0f, current.pos.y, 
        mObjAcch.GetGroundH(), mObjAcch.m_gnd, 
        &tevStr, 0, 1.0f, dDlst_shadowControl_c::getSimpleTex()
    );
}

const u32 unused[] = {
    0xFF000080,
    0x0000FF80,
};

/* 00001BC4-00001CB4       .text _draw__11daNpc_Hi1_cFv */
BOOL daNpc_Hi1_c::_draw() {
    J3DModel* pModel = mpMorf->getModel();
    J3DModelData* modelData = pModel->getModelData();

    if(field_0x7B2 || field_0x7B4) {
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(pModel, &tevStr);
    mBtpAnm.entry(modelData, mBtpAnmFrame);
    mBtkAnm.entry(modelData, mBtkAnmFrame);
    mpMorf->entryDL();
    mBtkAnm.remove(modelData);
    mBtpAnm.remove(modelData);
    shadowDraw();
    return TRUE;
    /* Nonmatching */
}

/* 00001CB4-00001EDC       .text _execute__11daNpc_Hi1_cFv */
BOOL daNpc_Hi1_c::_execute() {
    if(!field_0x7B5) {
        field_0x724 = current.pos;
        field_0x730 = current.angle;
        field_0x7B5 = 1;
    }

    m_jnt.setParam(
    l_HIO.mPrmTbl.mMaxBackboneX, l_HIO.mPrmTbl.mMaxBackboneY, l_HIO.mPrmTbl.mMinBackboneX,
    l_HIO.mPrmTbl.mMinBackboneY, l_HIO.mPrmTbl.mMaxHeadX, l_HIO.mPrmTbl.mMaxHeadY,
    l_HIO.mPrmTbl.mMinHeadX, l_HIO.mPrmTbl.mMinHeadY, l_HIO.mPrmTbl.mMaxTurnStep);

    if(field_0x7B2 && demoActorID == 0) {
        return TRUE;
    }

    checkOrder();
    if(!demo()) {
        int temp = -1;

        if(dComIfGp_event_runCheck() && !eventInfo.checkCommandTalk()) {
            temp = isEventEntry();
        }

        if(temp >= 0 || field_0x7B0) {
            event_proc(temp);
        } else {
            (this->*mCurrActionFunc)(NULL);
        }

        lookBack();
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
        mObjAcch.CrrPos(*dComIfG_Bgsp());
        play_animation();
        
    } else {
        field_0x7B2 = false;
    }

    eventOrder();
    field_0x736 = current.angle;
    if(!field_0x7B3) {
        shape_angle = current.angle;
    }

    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    setMtx(false);

    if(!field_0x7BA){
        setCollision(110.0f, 260.0f);
    }
    return TRUE;
}

/* 00001EDC-00001F30       .text _delete__11daNpc_Hi1_cFv */
BOOL daNpc_Hi1_c::_delete() {
    fopAcM_GetID(this);
    dComIfG_resDeleteDemo(&mPhs, mArcName);
    if(heap && mpMorf) {
        mpMorf->stopZelAnime();
    }
    return TRUE;
}

/* 00001F30-0000205C       .text _create__11daNpc_Hi1_cFv */
cPhs_State daNpc_Hi1_c::_create() {

    static int a_siz_tbl[] = {
        0,
        0
    };

    cPhs_State state;
    fopAcM_ct(this, daNpc_Hi1_c);
    if(!decideType(fopAcM_GetParam(this) & 0xFF)) {
        return cPhs_ERROR_e;
    }

    state = dComIfG_resLoad(&mPhs, mArcName);
    mStateIsComplaete = state == cPhs_COMPLEATE_e;
    if(!mStateIsComplaete) {
        return state;
    } 
    
    if(!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_siz_tbl[field_0x7C5])) {
        return cPhs_ERROR_e;
    }
    fopAcM_SetMtx(this, this->mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -110.0f, -20.0f, -100.0f, 110.0f, 280.0f, 100.0f);

    if(createInit() == 0) {
        return cPhs_ERROR_e;
    }
    return state;
}

/* 000024F4-00002768       .text bodyCreateHeap__11daNpc_Hi1_cFv */
BOOL daNpc_Hi1_c::bodyCreateHeap() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes(mArcName, HI_BDL_HI);
    JUT_ASSERT(0x5BB, a_mdl_dat != NULL);
    mpMorf = new mDoExt_McaMorf(
        a_mdl_dat,
        NULL, NULL, NULL,
        J3DFrameCtrl::EMode_NULL, 1.0f, 0, -1, 1, NULL,
        0x80000, 0x11020222
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
    JUT_ASSERT(0x5CF, m_hed_jnt_num >= 0);
    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone1");
    JUT_ASSERT(0x5D1, m_bbone_jnt_num >= 0);

    mpMorf->getModel()->getModelData()->getJointNodePointer(m_hed_jnt_num & 0xffff)->setCallBack(nodeCB_Head);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_bbone_jnt_num & 0xffff)->setCallBack(nodeCB_BackBone);
    mpMorf->getModel()->setUserArea((u32)(this));

    return TRUE;
}

/* 00002768-000027EC       .text CreateHeap__11daNpc_Hi1_cFv */
BOOL daNpc_Hi1_c::CreateHeap() {
    if(!bodyCreateHeap()) {
        return FALSE;
    }
    mAcchCir.SetWall(30.0f, 110.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this));
    return TRUE;
}

/* 000027EC-0000280C       .text daNpc_Hi1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Hi1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Hi1_c*)i_this)->_create();
}

/* 0000280C-0000282C       .text daNpc_Hi1_Delete__FP11daNpc_Hi1_c */
static BOOL daNpc_Hi1_Delete(daNpc_Hi1_c* i_this) {
    return ((daNpc_Hi1_c*)i_this)->_delete();
}

/* 0000282C-0000284C       .text daNpc_Hi1_Execute__FP11daNpc_Hi1_c */
static BOOL daNpc_Hi1_Execute(daNpc_Hi1_c* i_this) {
    return ((daNpc_Hi1_c*)i_this)->_execute();
}

/* 0000284C-0000286C       .text daNpc_Hi1_Draw__FP11daNpc_Hi1_c */
static BOOL daNpc_Hi1_Draw(daNpc_Hi1_c* i_this) {
    return ((daNpc_Hi1_c*)i_this)->_draw();
}

/* 0000286C-00002874       .text daNpc_Hi1_IsDelete__FP11daNpc_Hi1_c */
static BOOL daNpc_Hi1_IsDelete(daNpc_Hi1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Hi1_Method = {
    (process_method_func)daNpc_Hi1_Create,
    (process_method_func)daNpc_Hi1_Delete,
    (process_method_func)daNpc_Hi1_Execute,
    (process_method_func)daNpc_Hi1_IsDelete,
    (process_method_func)daNpc_Hi1_Draw,
};

actor_process_profile_definition g_profile_NPC_HI1 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_HI1,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Hi1_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_HI1,
    /* Actor SubMtd */ &l_daNpc_Hi1_Method,
    /* Status       */ 0x08 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
