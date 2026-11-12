/**
 * d_a_npc_zk1.cpp
 * NPC - Zk1
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_zk1.h"
#include "res/Object/Zk.h"
#include "d/d_snap.h"

class daNpc_Zk1_HIO_c : public mDoHIO_entry_c{
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

    daNpc_Zk1_HIO_c();
    virtual ~daNpc_Zk1_HIO_c() {};

    void genMessage(JORMContext* ctx) { UNUSED(ctx); }

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
        /* field_12          */ 0x04B0,
        /* mAttentionYOffset */ 240.0f,
        /* field_18          */ 0.0f,
    };
    memcpy(&mPrmTbl, &a_prm_tbl, sizeof(hio_prm_c));
    mNo = -1;
    field_0x8 = -1;
}

static const char* l_evn_tbl[1] = {
    "dummy"
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

    s32 jointIdx = ((J3DJoint*)(i_node))->getJntNo();
    mDoMtx_stack_c::copy(i_pModel->getAnmMtx(jointIdx));

    mDoMtx_stack_c::multVecZero(&field_0x768);
    mDoMtx_stack_c::multVec(&a_eye_pos_off, &field_0x744);
    mDoMtx_stack_c::XrotM(m_jnt.getHead_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    i_pModel->setAnmMtx(jointIdx, mDoMtx_stack_c::get());
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
    s32 jointIdx = ((J3DJoint*)(i_node))->getJntNo();
    mDoMtx_stack_c::copy(i_pModel->getAnmMtx(jointIdx));
    mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getBackbone_x());
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    i_pModel->setAnmMtx(jointIdx, mDoMtx_stack_c::get());
}

/* 0000042C-0000044C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* ac) {
    return ((daNpc_Zk1_c*)ac)->CreateHeap();
}

/* 0000044C-00000498       .text init_ZK1_0__11daNpc_Zk1_cFv */
bool daNpc_Zk1_c::init_ZK1_0() {
    if (dComIfGs_isSymbol(1)) {
        set_action(&daNpc_Zk1_c::wait_action1, NULL);
        m797 = dComIfGs_isEventBit(0x1802) == TRUE;
        m798 = dComIfGs_isEventBit(0x1C01) == TRUE;
        return true;
    }
    return false;
}

/* 00000498-00000618       .text createInit__11daNpc_Zk1_cFv */
bool daNpc_Zk1_c::createInit() {
    bool ret;
    for(int i = 0; i < ARRAY_SSIZE(l_evn_tbl); i++) {
        mEventIdx[i] = dComIfGp_evmng_getEventIdx(l_evn_tbl[i]);
    }
    mEventCut.setActorInfo2("Zk1", this);
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    
    switch(field_0x7C6) {
        case 0:
        break;
    }

    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xA9;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xA9;

    gravity = 0.0f;
    field_0x7C0 = 4;

    switch(field_0x7C6) {
        case 0:
            ret = init_ZK1_0();
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

/* 00000618-000006C8       .text play_animation__11daNpc_Zk1_cFv */
void daNpc_Zk1_c::play_animation() {
    u32 mtrlSndId = 0;
    play_btp_anm();
    if(mObjAcch.ChkGroundHit()) {
        mtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
    }

    field_0x7AC = mpMorf->play(&eyePos, mtrlSndId, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
    if(mpMorf->getFrame() < mFrame) {
        field_0x7AC = 1;
    }
    mFrame = mpMorf->getFrame();
}

/* 000006C8-00000778       .text setMtx__11daNpc_Zk1_cFb */
void daNpc_Zk1_c::setMtx(bool param_1) {
    mpMorf->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(field_0x736);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    setAttention(param_1);
}

/* 00000778-0000078C       .text bckResID__11daNpc_Zk1_cFi */
int daNpc_Zk1_c::bckResID(int idx) {
    static const int a_resID_tbl[] = {
        dRes_ID_ZK_BCK_ZK_WAIT01_e,
        dRes_ID_ZK_BCK_ZK_WAIT02_e,
        dRes_ID_ZK_BCK_ZK_TALK01_e,
        dRes_ID_ZK_BCK_ZK_TALK02_e,
    };
    return a_resID_tbl[idx];
}

/* 0000078C-000007A0       .text btpResID__11daNpc_Zk1_cFi */
int daNpc_Zk1_c::btpResID(int idx) {
    static const int a_resID_tbl[] = {
        dRes_ID_ZK_BTP_MABA_e,
    };
    return a_resID_tbl[idx];
}

/* 000007B4-000008B8       .text setBtp__11daNpc_Zk1_cFScb */
bool daNpc_Zk1_c::setBtp(s8 param_1, bool param_2) {
    J3DModel* model = mpMorf->getModel();
    if(param_1 < 0) {
        return false;
    }
    int resID = btpResID(param_1);
    J3DAnmTexPattern* a_btp = (J3DAnmTexPattern *)dComIfG_getObjectIDRes(mArcName, resID);
    JUT_ASSERT(0x18f, a_btp != NULL);
    field_0x7BE = param_1;
    mBtpAnmFrame = 0;
    mTimer1 = 0;

    return mBtpAnm.init(model->getModelData(), a_btp,J3DFrameCtrl::EMode_RESET, 0, 1.0f, 0, -1, param_2, 0) != 0;
}

/* 000009B8-00000A24       .text init_texPttrnAnm__11daNpc_Zk1_cFScb */
bool daNpc_Zk1_c::init_texPttrnAnm(s8 param_1, bool param_2) {
    return setBtp(param_1, param_2);
}

/* 00000A24-00000AC0       .text play_btp_anm__11daNpc_Zk1_cFv */
void daNpc_Zk1_c::play_btp_anm() {
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

/* 00000AEC-00000B88       .text setAnm_anm__11daNpc_Zk1_cFPQ211daNpc_Zk1_c9anm_prm_c */
void daNpc_Zk1_c::setAnm_anm(daNpc_Zk1_c::anm_prm_c* param_1) {
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

/* 00000BF8-00000C64       .text setAnm__11daNpc_Zk1_cFv */
void daNpc_Zk1_c::setAnm() {
    static daNpc_Zk1_c::anm_prm_c a_anm_prm_tbl[3] = {
        {-1, -1, 0.0f, 0.0f, -1},
        {0, 0, 8.0f, 1.0f, 2},
        {-1, -1, 0.0f, 0.0f, -1}
    };
    init_texPttrnAnm(a_anm_prm_tbl[field_0x7C2].field_0x1, true);
    setAnm_anm(&a_anm_prm_tbl[field_0x7C2]);
}

/* 00000C64-00000C68       .text chngAnmTag__11daNpc_Zk1_cFv */
void daNpc_Zk1_c::chngAnmTag() {
}

/* 00000C68-00000C6C       .text ctrlAnmTag__11daNpc_Zk1_cFv */
void daNpc_Zk1_c::ctrlAnmTag() {
}

/* 00000C6C-00000CAC       .text chngAnmAtr__11daNpc_Zk1_cFUc */
void daNpc_Zk1_c::chngAnmAtr(u8 param_1) {
    if(param_1 == field_0x7BC || param_1 > 4) {
        return;
    }
    field_0x7BC = param_1;
    setAnm_ATR();
}

/* 00000CAC-00000CB8       .text ctrlAnmAtr__11daNpc_Zk1_cFv */
void daNpc_Zk1_c::ctrlAnmAtr() {
    if(field_0x7BC == (s8)4) {
        return;
    }
}

/* 00000CB8-00000D1C       .text setAnm_ATR__11daNpc_Zk1_cFv */
void daNpc_Zk1_c::setAnm_ATR() {
    static daNpc_Zk1_c::anm_prm_c a_anm_prm_tbl[4] = {
        {0, 0, 8.0f, 1.0f, 2},
        {1, 0, 8.0f, 1.0f, 2},
        {2, 0, 8.0f, 1.0f, 2},
        {3, 0, 8.0f, 1.0f, 2},
    };
    init_texPttrnAnm(a_anm_prm_tbl[field_0x7BC].field_0x1, true);
    setAnm_anm(&a_anm_prm_tbl[field_0x7BC]);
}

/* 00000D1C-00000DD8       .text anmAtr__11daNpc_Zk1_cFUs */
void daNpc_Zk1_c::anmAtr(u16 i_msgStatus) {
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

/* 00000DD8-00000DE0       .text next_msgStatus__11daNpc_Zk1_cFPUl */
u16 daNpc_Zk1_c::next_msgStatus(u32* pMsgNo) {
    u16 status = fopMsgStts_MSG_CONTINUES_e;
    switch (*pMsgNo) {
    case 0x17A2:
        *pMsgNo = 0x17A3;
        break;
    case 0x17A3:
        *pMsgNo = 0x17A4;
        break;
    case 0x17A4:
        *pMsgNo = 0x17A5;
        break;
    case 0x17A5:
        *pMsgNo = 0x17A6;
        break;
    case 0x17A8:
        *pMsgNo = 0x17A9;
        break;
    case 0x17A9:
        *pMsgNo = 0x17AA;
        break;
    case 0x17AA:
        *pMsgNo = 0x17AB;
        break;
    case 0x17AD:
        if (dKy_daynight_check()) {
            *pMsgNo = 0x17AF;
        } else {
            *pMsgNo = 0x17AE;
        }
        break;
    default:
        status = fopMsgStts_MSG_ENDS_e;
        break;
    }
    return status;
}

/* 00000DE0-00000DE8       .text getMsg_ZK1_0__11daNpc_Zk1_cFv */
u32 daNpc_Zk1_c::getMsg_ZK1_0() {
    if (!dComIfGs_isEventBit(0x1A80)) {
        return dComIfGs_isEventBit(0x1802) ? 0x17A7 : 0x17A2;
    }
    if (!m797) {
        return dComIfGs_isEventBit(0x1802) ? 0x17AC : 0x17A8;
    }
    if (!m798) {
        return dComIfGs_isEventBit(0x1C01) ? 0x17B0 : 0x17AD;
    }
    return dComIfGs_isEventBit(0x1D80) ? 0x17B2 : 0x17B1;
}

/* 00000DE8-00000E24       .text getMsg__11daNpc_Zk1_cFv */
    u32 daNpc_Zk1_c::getMsg() {
        u32 msgNo = 0;

    switch(field_0x7C6) {
        case 0:
            msgNo = getMsg_ZK1_0();
            break;
        default:
            break;
    }
    return msgNo;
}

/* 00000E24-00000EB0       .text eventOrder__11daNpc_Zk1_cFv */
void daNpc_Zk1_c::eventOrder() {
    if(field_0x7C1 == 1 || field_0x7C1 == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);

        if(field_0x7C1 == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if(field_0x7C1 >= 3) {
        field_0x796 = field_0x7C1 - 3;
        fopAcM_orderOtherEventId(this, mEventIdx[field_0x796]);
    }
}

/* 00000EB0-00000F64       .text checkOrder__11daNpc_Zk1_cFv */
void daNpc_Zk1_c::checkOrder() {
    if(eventInfo.checkCommandDemoAccrpt()) {
        if(dComIfGp_evmng_startCheck(mEventIdx[field_0x796]) && field_0x7C1 >= 3) {
            field_0x7C1 = 0;
            field_0x7BC = 0xff;
            field_0x7BD = 0xff;
        }
    } else if(eventInfo.checkCommandTalk() && (field_0x7C1 == 1 || field_0x7C1 == 2)) {
        field_0x7C1 = 0;
        field_0x7B7 = true;
    }
}

/* 00000F64-00000FFC       .text chk_talk__11daNpc_Zk1_cFv */
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

/* 00000FFC-0000103C       .text chk_parts_notMov__11daNpc_Zk1_cFv */
bool daNpc_Zk1_c::chk_parts_notMov() {
    return field_0x788.y != m_jnt.getHead_y() || 
        field_0x788.z != m_jnt.getBackbone_y() ||
        field_0x788.x != current.angle.y;
}

/* 0000103C-00001090       .text searchByID__11daNpc_Zk1_cFUiPi */
fopAc_ac_c* daNpc_Zk1_c::searchByID(fpc_ProcID pid, int* param_2) {
    fopAc_ac_c* actor = NULL;
    *param_2 = 0;
    
    int temp = fopAcM_SearchByID(pid, &actor);
    if(temp == 0) {
        *param_2 = 1;
    }
    return actor;
}

/* 00001090-00001254       .text lookBack__11daNpc_Zk1_cFv */
void daNpc_Zk1_c::lookBack() {
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

/* 00001254-000012D4       .text chkAttention__11daNpc_Zk1_cFv */
bool daNpc_Zk1_c::chkAttention() {
    dAttention_c& attention = dComIfGp_getAttention();

    if(attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    }

    return this == attention.ActionTarget(0);
}

/* 000012D4-0000132C       .text setAttention__11daNpc_Zk1_cFb */
void daNpc_Zk1_c::setAttention(bool param_1) {
    attention_info.position.set(current.pos.x, current.pos.y + l_HIO.mPrmTbl.mAttentionYOffset, current.pos.z);
    if(field_0x790 == 0 && !param_1) {
        return;
    }
    eyePos.set(field_0x744.x, field_0x744.y, field_0x744.z);
}

/* 0000132C-000013B4       .text decideType__11daNpc_Zk1_cFi */
bool daNpc_Zk1_c::decideType(int param_1) {
    bool temp;
    if(field_0x7C5 > 0) {
        temp = true;
    } else {
        field_0x7C5 = 1;
        field_0x7C6 = 0;
        strcpy(mArcName,"Zk");
        temp = false;
        if((field_0x7C5 != -1) && (field_0x7C6 != -1)) {
            temp = true;
        }
    }
    return temp;
}

/* 000013B4-00001454       .text privateCut__11daNpc_Zk1_cFi */
void daNpc_Zk1_c::privateCut(int i_staffIdx) {
    static char* a_cut_tbl[] = {
        "DUMMY"
    };

    if(i_staffIdx != -1) {
        mActIdx = dComIfGp_evmng_getMyActIdx(i_staffIdx, a_cut_tbl, ARRAY_SIZE(a_cut_tbl), TRUE, 0);

        if(mActIdx == -1) {
            dComIfGp_evmng_cutEnd(i_staffIdx);
        } else {
#if VERSION == VERSION_DEMO
            bool temp;
            if(dComIfGp_evmng_getIsAddvance(i_staffIdx)) {

                switch(mActIdx) {
                    case 0:
                        // to match codegen
                        speedF = speedF;
                        break;
                }
            }
            
            switch(mActIdx) {
                case 0:
                    break;
                default:
                    temp = true;
                    break;

            }
            
            if(temp) {
                dComIfGp_evmng_cutEnd(i_staffIdx);
            }
#else
            dComIfGp_evmng_getIsAddvance(i_staffIdx);
            dComIfGp_evmng_cutEnd(i_staffIdx);
#endif
        }
    }
}

/* 00001454-00001478       .text endEvent__11daNpc_Zk1_cFv */
void daNpc_Zk1_c::endEvent() {
    dComIfGp_event_reset();
    field_0x7BC = 0xff;
    field_0x7BD = 0xff;
}

/* 00001478-000014B0       .text isEventEntry__11daNpc_Zk1_cFv */
int daNpc_Zk1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName());
}

/* 000014B0-00001534       .text event_proc__11daNpc_Zk1_cFi */
void daNpc_Zk1_c::event_proc(int i_staffIdx) {    
    if(dComIfGp_evmng_endCheck(mEventIdx[field_0x796])) {
        endEvent();
    } else {
        if(!mEventCut.cutProc()) {
            privateCut(i_staffIdx);
        }
    }
}

/* 00001534-000015E0       .text set_action__11daNpc_Zk1_cFM11daNpc_Zk1_cFPCvPvPv_iPv */
bool daNpc_Zk1_c::set_action(ActionFunc i_action, void* param_2) {
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

/* 000015E0-00001654       .text setStt__11daNpc_Zk1_cFSc */
void daNpc_Zk1_c::setStt(s8 param_1) {
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

/* 00001654-000017D4       .text wait_1__11daNpc_Zk1_cFv */
BOOL daNpc_Zk1_c::wait_1() {
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

        if(dNpc_chkAttn(this, dComIfGp_getPlayer(0)->current.pos, 200.0f, 50.0f, 76.0f, field_0x7C4 == 1) ){
            return TRUE;
        }
        field_0x7C4 = 0;
        field_0x7B9 = true;
    }
    return TRUE;
}

/* 000017D4-0000189C       .text talk_1__11daNpc_Zk1_cFv */
BOOL daNpc_Zk1_c::talk_1() {
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
            switch (mCurrMsgNo) {
            case 0x17A6:
            case 0x17AB:
                dComIfGs_onEventBit(0x1802);
                break;
            case 0x17AE:
            case 0x17AF:
                dComIfGs_onEventBit(0x1C01);
                break;
            case 0x17B1:
                dComIfGs_onEventBit(0x1D80);
                break;
            }
            mItemNo = 0xFF;
            field_0x7B7 = false;
            setStt(field_0x7C3);
            mTimer2 = cLib_getRndValue(0xf, 0x1e);
            endEvent();
            break;
    }
    return ret;
}

/* 0000189C-00001958       .text wait_action1__11daNpc_Zk1_cFPv */
int daNpc_Zk1_c::wait_action1(void*) {
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

/* 00001958-00001B34       .text demo__11daNpc_Zk1_cFv */
u8 daNpc_Zk1_c::demo() {
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

        dDemo_setDemoData(this, dDemo_actor_c::ENABLE_TRANS_e | dDemo_actor_c::ENABLE_ROTATE_e | dDemo_actor_c::ENABLE_ANM_e | dDemo_actor_c::ENABLE_ANM_FRAME_e, mpMorf, mArcName);
    }
    return field_0x7BA;
}

/* 00001B34-00001BC4       .text shadowDraw__11daNpc_Zk1_cFv */
void daNpc_Zk1_c::shadowDraw() {
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

/* 00001BC4-00001CB4       .text _draw__11daNpc_Zk1_cFv */
BOOL daNpc_Zk1_c::_draw() {
    J3DModel* pModel = mpMorf->getModel();
    J3DModelData* modelData = pModel->getModelData();

    if(field_0x7B2 || field_0x7B4) {
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(pModel, &tevStr);
    mBtpAnm.entry(modelData, mBtpAnmFrame);
    mpMorf->entryDL();
    mBtpAnm.remove(modelData);
    shadowDraw();
    dSnap_RegistFig(DSNAP_TYPE_UNK8C, this, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 00001CB4-00001EDC       .text _execute__11daNpc_Zk1_cFv */
BOOL daNpc_Zk1_c::_execute() {
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

        if(dComIfGp_event_runCheck() && eventInfo.checkCommandTalk() == false) {
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
        setCollision(80.0f, 220.0f);
    }
    return TRUE;
}

/* 00001EDC-00001F30       .text _delete__11daNpc_Zk1_cFv */
BOOL daNpc_Zk1_c::_delete() {
    if(DEMO_SELECT(mStateIsComplaete, true)){
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

/* 00001F30-0000205C       .text _create__11daNpc_Zk1_cFv */
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
    mStateIsComplaete = state == cPhs_COMPLEATE_e;
    if(!mStateIsComplaete) {
        return state;
    } 
#if VERSION == VERSION_DEMO
    l_HIO.entryHIO("ハイラル王");
#endif
    fopAcM_ct_Demo(this, daNpc_Zk1_c);
    
    if(!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_siz_tbl[field_0x7C5])) {
#if VERSION == VERSION_DEMO
        mStateIsComplaete = false;
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

/* 000024F4-00002768       .text bodyCreateHeap__11daNpc_Zk1_cFv */
BOOL daNpc_Zk1_c::bodyCreateHeap() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes(mArcName, dRes_ID_ZK_BDL_ZK_e);
    JUT_ASSERT(1459, a_mdl_dat != NULL);
    mpMorf = new mDoExt_McaMorf(
        a_mdl_dat,
        NULL, NULL, NULL,
        J3DFrameCtrl::EMode_NULL, 1.0f, 0, -1, 1, NULL,
        0x80000, 0x11020022
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
    JUT_ASSERT(1479, m_hed_jnt_num >= 0);
    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(1481, m_bbone_jnt_num >= 0);

    mpMorf->getModel()->getModelData()->getJointNodePointer(m_hed_jnt_num)->setCallBack(nodeCB_Head);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_bbone_jnt_num)->setCallBack(nodeCB_BackBone);
    mpMorf->getModel()->setUserArea((uintptr_t)this);

    return TRUE;
}

/* 00002768-000027EC       .text CreateHeap__11daNpc_Zk1_cFv */
BOOL daNpc_Zk1_c::CreateHeap() {
    if(!bodyCreateHeap()) {
        return FALSE;
    }
    mAcchCir.SetWall(30.0f, 80.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this));
    return TRUE;
}

/* 000027EC-0000280C       .text daNpc_Zk1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Zk1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Zk1_c*)i_this)->_create();
}

/* 0000280C-0000282C       .text daNpc_Zk1_Delete__FP11daNpc_Zk1_c */
static BOOL daNpc_Zk1_Delete(daNpc_Zk1_c* i_this) {
    return ((daNpc_Zk1_c*)i_this)->_delete();
}

/* 0000282C-0000284C       .text daNpc_Zk1_Execute__FP11daNpc_Zk1_c */
static BOOL daNpc_Zk1_Execute(daNpc_Zk1_c* i_this) {
    return ((daNpc_Zk1_c*)i_this)->_execute();
}

/* 0000284C-0000286C       .text daNpc_Zk1_Draw__FP11daNpc_Zk1_c */
static BOOL daNpc_Zk1_Draw(daNpc_Zk1_c* i_this) {
    return ((daNpc_Zk1_c*)i_this)->_draw();
}

/* 0000286C-00002874       .text daNpc_Zk1_IsDelete__FP11daNpc_Zk1_c */
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
