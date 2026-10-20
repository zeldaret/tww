/**
 * d_a_npc_sv.cpp
 * NPC - Salvage Corp group members
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_sv.h"
#include "d/d_com_lib_game.h"
#include "res/Object/Sv.h"

enum {
    TALK_FLAG_1ST = 0x01,
    TALK_FLAG_2ND = 0x02,
    TALK_FLAG_P2 = 0x04,
    TALK_FLAG_P3 = 0x08,
    TALK_FLAG_P4 = 0x10,
    TALK_FLAG_GOT_CHART = 0x20,
};

static char* l_npc_staff_id[] = { "Sv0", "Sv1", "Sv2", "Sv3" };

static const char* l_arcname_tbl[] = { "Sv", "Sv", "Sv", "Sv" };

static const int l_bmd_ix_tbl[] = {
    dRes_ID_SV_BDL_SV_e,
    dRes_ID_SV_BDL_SV_e,
    dRes_ID_SV_BDL_SV_e,
    dRes_ID_SV_BDL_SV_e,
};

static const int l_bck_ix_tbl[][6] = { { dRes_ID_SV_BCK_SV_WAIT01_e,
                                         dRes_ID_SV_BCK_SV_TALK01_e,
                                         dRes_ID_SV_BCK_SV_TALK02_e,
                                         dRes_ID_SV_BCK_SV_TALK03_e,
                                         dRes_ID_SV_BCK_SV_YA_e,
                                         dRes_ID_SV_BCK_SV_MAWASI_e },
                                       { dRes_ID_SV_BCK_SV_WAIT02_e,
                                         dRes_ID_SV_BCK_SV_KYORO_e,
                                         dRes_ID_SV_BCK_SV_UNAZUKU_e,
                                         dRes_ID_SV_BCK_SV_HARAU_e,
                                         dRes_ID_SV_BCK_SV_BYE_e,
                                         dRes_ID_SV_BCK_SV_SHI_e },
                                       { dRes_ID_SV_BCK_SV_WAIT02_e,
                                         dRes_ID_SV_BCK_SV_KYORO_e,
                                         dRes_ID_SV_BCK_SV_UNAZUKU_e,
                                         dRes_ID_SV_BCK_SV_HARAU_e,
                                         dRes_ID_SV_BCK_SV_BYE_e,
                                         dRes_ID_SV_BCK_SV_SHI_e },
                                       { dRes_ID_SV_BCK_SV_WAIT02_e,
                                         dRes_ID_SV_BCK_SV_KYORO_e,
                                         dRes_ID_SV_BCK_SV_UNAZUKU_e,
                                         dRes_ID_SV_BCK_SV_HARAU_e,
                                         dRes_ID_SV_BCK_SV_BYE_e,
                                         dRes_ID_SV_BCK_SV_SHI_e } };

static sSvAnmDat l_npc_anm_wait = { 0, 0x08, 0xFF };

static sSvAnmDat l_npc_anm_talk = {
    1,
    0x08,
    0xFF,
};

static sSvAnmDat l_npc_anm_talk2 = {
    2,
    0x08,
    0xFF,
};

static sSvAnmDat l_npc_anm_talk3 = {
    3,
    0x08,
    0xFF,
};

static sSvAnmDat l_npc_anm_ya1[] = { {
                                         4,
                                         0x08,
                                         1,
                                     },
                                     {
                                         0,
                                         0x08,
                                         0xFF,
                                     } };

static sSvAnmDat l_npc_anm_ya2[] = { {
                                         4,
                                         0x08,
                                         1,
                                     },
                                     {
                                         1,
                                         0x08,
                                         0xFF,
                                     } };

static sSvAnmDat l_npc_anm_mawasi = {
    5,
    0x00,
    0xFF,
};

static sSvAnmDat l_npc_anm_kyoro = {
    1,
    0x08,
    0xFF,
};

static sSvAnmDat l_npc_anm_unun[] = { {
                                          2,
                                          0x08,
                                          1,
                                      },
                                      {
                                          0xFF,
                                          0x08,
                                          0,
                                      } };

static sSvAnmDat l_npc_anm_sisi[] = { {
                                          3,
                                          0x08,
                                          1,
                                      },
                                      {
                                          0xFF,
                                          0x08,
                                          0,
                                      } };

static sSvAnmDat l_npc_anm_byebye[] = { {
                                            4,
                                            0x08,
                                            1,
                                        },
                                        {
                                            0xFF,
                                            0x08,
                                            0,
                                        } };

static sSvAnmDat l_npc_anm_shi[] = { {
                                         5,
                                         0x08,
                                         1,
                                     },
                                     {
                                         0xFF,
                                         0x08,
                                         0,
                                     } };

static sSvAnmDat* l_npc_anm_sv1_tbl[] = {
    &l_npc_anm_wait, &l_npc_anm_kyoro, l_npc_anm_unun, l_npc_anm_sisi, l_npc_anm_byebye, l_npc_anm_shi,
};

static u32 l_npc_se_sv1_tbl[] = { 0, 0, JA_SE_CV_SALV_CRUE_AGREE, JA_SE_CV_SALV_CRUE_SI, JA_SE_CV_SALV_CRUE_BYE, 0 };

static NpcDatStruct l_npc_dat[] = {
    {
        0x0FA0, 0x1770, 0x0000, 0x1F40, 0x0000,  0xE890, 0xF448, 0xE0C0, 0x03E8, 0x0000, 0.0f, -5.0f, 0.0f,
        0.0f,   185.0f, 150.0f, 600.0f, 1500.0f, 0x7FFF, 0x03E8, 60.0f,  150.0f, 0x001E, 0x01, 0x01,
    },
    {
        0x1000, 0x0000, 0x0000, 0x0000, 0xF000, 0x0000, 0x0000, 0x0000, 0x0800, 0x0000, 0.0f, 0.0f, 0.0f,
        0.0f,   180.0f, 150.0f, 0.0f,   0.0f,   0x7FFF, 0x0800, 60.0f,  150.0f, 0x001E, 0x00, 0x01,
    },
    {
        0x1000, 0x0000, 0x0000, 0x0000, 0xF000, 0x0000, 0x0000, 0x0000, 0x0800, 0x0000, 0.0f, 0.0f, 0.0f,
        0.0f,   180.0f, 150.0f, 0.0f,   0.0f,   0x7FFF, 0x0800, 60.0f,  150.0f, 0x001E, 0x00, 0x01,
    },
    {
        0x1000, 0x0000, 0x0000, 0x0000, 0xF000, 0x0000, 0x0000, 0x0000, 0x0800, 0x0000, 0.0f, 0.0f, 0.0f,
        0.0f,   180.0f, 150.0f, 0.0f,   0.0f,   0x4000, 0x0800, 60.0f,  150.0f, 0x001E, 0x00, 0x01,
    },
};

static u32 l_msg_sv_p1_1st_talk1[] = { 0x34BD, 0x34BE, 0x34BF, 0x34C0, 0x0002, 0x34C1, 0x34C2, 0x34C3, 0x0001, 0x34C4, 0x34E8, 0x0002, 0x34C5, 0x0004, 0x0000 };
static u32 l_msg_sv_p1_1st_talk2[] = { 0x34BD, 0x34BE, 0x34BF, 0x34C0, 0x0002, 0x34C1, 0x34C2, 0x34C3, 0x0001, 0x34C6, 0x34E9, 0x0002, 0x34C7, 0x0004, 0x0000 };

static u32 l_msg_sv_p1_2nd_talk1[] = { 0x34C8, 0x34C9, 0x34EA, 0x0002, 0x34CA, 0x0004, 0x0000 };
static u32 l_msg_sv_p1_2nd_talk2[] = { 0x34C8, 0x34CB, 0x0002, 0x34CC, 0x0004, 0x0000 };

static u32 l_msg_sv_p1_3rd_talk1[] = { 0x34CD, 0x34D0, 0x0002, 0x34D1, 0x0003, 0x0000 };
static u32 l_msg_sv_p1_3rd_talk2[] = { 0x34CD, 0x34CE, 0x0002, 0x34CF, 0x0003, 0x0000 };

static u32 l_msg_sv_p2_1st_talk[] = { 0x34D9, 0x34DA, 0x34DB, 0x0002, 0x34DC, 0x0004, 0x0000 };
static u32 l_msg_sv_p2_2nd_talk[] = { 0x34DD, 0x34DE, 0x0002, 0x34DF, 0x0003, 0x0000 };

static u32 l_msg_sv_p3_1st_talk[] = { 0x34D2, 0x34D3, 0x34D4, 0x0002, 0x34D5, 0x0004, 0x0000 };
static u32 l_msg_sv_p3_2nd_talk[] = { 0x34D6, 0x34D7, 0x0002, 0x34D8, 0x0003, 0x0000 };

static u32 l_msg_sv_p4_1st_talk[] = { 0x34E0, 0x34E1, 0x34E2, 0x34E3, 0x34E4, 0x0005, 0x0000 };
static u32 l_msg_sv_p4_2nd_talk[] = { 0x34E5, 0x34E6, 0x34E7, 0x0005, 0x0000 };

static u32* l_msg_sv_talk_tbl[] = { l_msg_sv_p1_1st_talk1, l_msg_sv_p1_1st_talk2, l_msg_sv_p1_2nd_talk1, l_msg_sv_p1_2nd_talk2,
                                    l_msg_sv_p1_3rd_talk1, l_msg_sv_p1_3rd_talk2, l_msg_sv_p2_1st_talk,  l_msg_sv_p2_2nd_talk,
                                    l_msg_sv_p3_1st_talk,  l_msg_sv_p3_2nd_talk,  l_msg_sv_p4_1st_talk,  l_msg_sv_p4_2nd_talk };

static u16 l_msg_sv_flag_tbl[] = {
    TALK_FLAG_1ST, TALK_FLAG_1ST, TALK_FLAG_2ND, TALK_FLAG_2ND, 0, 0, TALK_FLAG_P2, 0, TALK_FLAG_P3, 0, TALK_FLAG_P4, 0,
};

static s16 l_event_id_tbl[] = { 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02 };

static u32 l_get_item_no[] = { dItemNo_COLLECT_MAP_26_e };

typedef int (daNpcSv_c::*ExecuteInit_t)();
static ExecuteInit_t l_execute_init[] = {
    &daNpcSv_c::executeWaitInit,
    &daNpcSv_c::executeTalkInit,
};

typedef void (daNpcSv_c::*MoveProc_t)();
static MoveProc_t moveProc[] = {
    &daNpcSv_c::executeWait,
    &daNpcSv_c::executeTalk,
};

/* 00000078-0000021C       .text __ct__9daNpcSv_cFv */
daNpcSv_c::daNpcSv_c() {
    mNpcNo = getPrmNpcNo();
    mResFlag = 0;
    mMoveState = 0;
    mAnmMorfOverride = -1.0f;
    field_0x741 = 0;
    field_0x71C = 1;
    field_0x742 = 1;
    field_0x728 = home.angle.y;
    mBckIdx = 0;
    mTalkFlags = 0;
    field_0x718 = 0;

    if (dComIfGs_checkGetItem(dItemNo_COLLECT_MAP_26_e)) {
        mTalkFlags |= TALK_FLAG_GOT_CHART;
    }
}

/* 00000528-00000640       .text daNpc_People_nodeCallBack__FP7J3DNodei */
static BOOL daNpc_People_nodeCallBack(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)i_node;
        J3DModel* model = j3dSys.getModel();
        daNpcSv_c* i_this = (daNpcSv_c*)model->getUserArea();

        s32 jntNo = joint->getJntNo();
        MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);

        if (jntNo == i_this->m_jnt.getHeadJntNum()) {
            cMtx_XrotM(*calc_mtx, (s16)i_this->m_jnt.getHead_y());
            cMtx_ZrotM(*calc_mtx, (s16)-i_this->m_jnt.getHead_x());
        }
        if (jntNo == i_this->m_jnt.getBackboneJntNum()) {
            cMtx_XrotM(*calc_mtx, (s16)i_this->m_jnt.getBackbone_y());
            cMtx_ZrotM(*calc_mtx, (s16)-i_this->m_jnt.getBackbone_x());
        }

        model->setAnmMtx(jntNo, *calc_mtx);
        MTXCopy(*calc_mtx, j3dSys.mCurrentMtx);
    }

    return true;
}

/* 00000640-00000660       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpcSv_c*)i_this)->createHeap();
}

/* 00000660-000006B8       .text phase_1__FP9daNpcSv_c */
cPhs_State phase_1(daNpcSv_c* i_this) {
    fopAcM_ct(i_this, daNpcSv_c);
    i_this->setResFlag(1);
    return cPhs_NEXT_e;
}

/* 000006B8-00000738       .text phase_2__FP9daNpcSv_c */
cPhs_State phase_2(daNpcSv_c* i_this) {
    cPhs_State state = dComIfG_resLoad(i_this->getPhaseP(), l_arcname_tbl[i_this->getNpcNo()]);

    if (state == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(i_this, CheckCreateHeap, 0x3800)) {
            state = i_this->createInit();
        } else {
#if VERSION > VERSION_DEMO
            i_this->mpMorf = NULL;
#endif
            return cPhs_ERROR_e;
        }
    }
    return state;
}

/* 00000738-00000768       .text _create__9daNpcSv_cFv */
cPhs_State daNpcSv_c::_create() {
    static cPhs__Handler l_method[] = { (cPhs__Handler)&phase_1, (cPhs__Handler)&phase_2, (cPhs__Handler)NULL };

    return dComLbG_PhaseHandler(&mPhaseCreate, l_method, this);
}

/* 00000768-00000A04       .text createHeap__9daNpcSv_cFv */
BOOL daNpcSv_c::createHeap() {
    /* Nonmatching */
}

/* 00000A04-00000C74       .text createInit__9daNpcSv_cFv */
cPhs_State daNpcSv_c::createInit() {
    /* Nonmatching */
    return cPhs_COMPLEATE_e;
}

/* 00000C74-00000CD8       .text _delete__9daNpcSv_cFv */
bool daNpcSv_c::_delete() {
    dComIfG_resDeleteDemo(&mPhase, l_arcname_tbl[mNpcNo]);
    if (heap != NULL && mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }
    return true;
}

/* 00000CD8-00000DAC       .text _draw__9daNpcSv_cFv */
bool daNpcSv_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpMorf->getModel(), &tevStr);
    mpMorf->updateDL();

    cXyz pos(current.pos.x, current.pos.y + 150.0f, current.pos.z);
    mShadowId = dComIfGd_setShadow(
        mShadowId,
        1,
        mpMorf->getModel(),
        &pos,
        800.0f,
        20.0f,
        current.pos.y,
        mObjAcch.GetGroundH(),
        mObjAcch.m_gnd,
        &tevStr,
        0,
        1.0f,
        dDlst_shadowControl_c::getSimpleTex()
    );
    return true;
}

/* 00000DAC-00000F90       .text _execute__9daNpcSv_cFv */
bool daNpcSv_c::_execute() {
    /* Nonmatching */
}

/* 00000F90-00000FB8       .text executeCommon__9daNpcSv_cFv */
void daNpcSv_c::executeCommon() {
    /* Nonmatching */
}

/* 00000FB8-00001000       .text executeSetMode__9daNpcSv_cFUc */
void daNpcSv_c::executeSetMode(u8 i_mode) {
    mMoveState = (this->*l_execute_init[i_mode])();
}

/* 00001000-00001080       .text executeWaitInit__9daNpcSv_cFv */
BOOL daNpcSv_c::executeWaitInit() {
    /* Nonmatching */
}

/* 00001080-0000131C       .text executeWait__9daNpcSv_cFv */
void daNpcSv_c::executeWait() {
    /* Nonmatching */
}

/* 0000131C-00001338       .text executeTalkInit__9daNpcSv_cFv */
BOOL daNpcSv_c::executeTalkInit() {
    if (field_0x742) {
        return TRUE;
    }
    return mMoveState;
}

/* 00001338-000013B8       .text executeTalk__9daNpcSv_cFv */
void daNpcSv_c::executeTalk() {
    /* Nonmatching */
}

/* 000013B8-000013EC       .text checkOrder__9daNpcSv_cFv */
void daNpcSv_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        return;
    }
    if (!eventInfo.checkCommandTalk()) {
        return;
    }
    if (mEvtOrderType != 2 && mEvtOrderType != 1) {
        return;
    }
    field_0x736 = 1;
}

/* 000013EC-00001458       .text eventOrder__9daNpcSv_cFv */
void daNpcSv_c::eventOrder() {
    if ((mEvtOrderType == 2 || mEvtOrderType == 1) && isTalkOK()) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (mEvtOrderType == 2) {
            fopAcM_orderSpeakEvent(this);
        }
    }
}

/* 00001458-00001570       .text eventMove__9daNpcSv_cFv */
void daNpcSv_c::eventMove() {
    if (dComIfGp_evmng_endCheck(field_0x71E[0]) || dComIfGp_evmng_endCheck(field_0x71E[1]) || dComIfGp_evmng_endCheck(field_0x71E[2])) {
        eventInfo.setEventId(field_0x71E[l_event_id_tbl[(getTalkNo() & 0xFF)]]);
        dComIfGp_event_onEventFlag(8);
        field_0x73C &= ~2;
        field_0x736 = 0;
        field_0x749 = 0;
        executeSetMode(0);
        return;
    }

    bool attn = mEventCut.getAttnFlag();
    if (mEventCut.cutProc()) {
        if (mEventCut.getAttnFlag()) {
            return;
        }
        mEventCut.setAttnFlag(attn);
    } else {
        privateCut();
        if (getNpcNo()) {
            return;
        }
        setAnmFromMsgTag();
        return;
    }
}

/* 00001570-00001744       .text privateCut__9daNpcSv_cFv */
void daNpcSv_c::privateCut() {
    /* Nonmatching */
    static char* cut_name_tbl[] = {
        "MES_SET", "GET_ITEM", "SET_ANGLE", "ATTENTION", "TURN_OK",
    };
}

/* 00001744-00001814       .text eventMesSetInit__9daNpcSv_cFi */
void daNpcSv_c::eventMesSetInit(int) {
    /* Nonmatching */
}

/* 00001814-0000184C       .text eventMesSet__9daNpcSv_cFv */
BOOL daNpcSv_c::eventMesSet() {
    return talk2(0, this) == fopMsgStts_BOX_CLOSED_e ? TRUE : FALSE;
}

/* 0000184C-000018F0       .text eventGetItemInit__9daNpcSv_cFi */
void daNpcSv_c::eventGetItemInit(int) {
    /* Nonmatching */
}

/* 000018F0-000018F8       .text eventGetItem__9daNpcSv_cFv */
bool daNpcSv_c::eventGetItem() {
    return true;
}

/* 000018F8-000019E0       .text eventSetAngleInit__9daNpcSv_cFv */
void daNpcSv_c::eventSetAngleInit() {
    /* Nonmatching */
}

/* 000019E0-00001A74       .text eventAttentionInit__9daNpcSv_cFi */
void daNpcSv_c::eventAttentionInit(int) {
    /* Nonmatching */
}

/* 00001A74-00001BC8       .text eventAttention__9daNpcSv_cFv */
void daNpcSv_c::eventAttention() {
    /* Nonmatching */
}

/* 00001BC8-00001BD4       .text eventTurnOkInit__9daNpcSv_cFv */
void daNpcSv_c::eventTurnOkInit() {
    field_0x743 = 1;
}

/* 00001BD4-00001CF0       .text talk2__9daNpcSv_cFiP10fopAc_ac_c */
u16 daNpcSv_c::talk2(int, fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00001CF0-00001DC8       .text next_msgStatus__9daNpcSv_cFPUl */
u16 daNpcSv_c::next_msgStatus(u32*) {
    /* Nonmatching */
}

/* 00001DC8-00001EB4       .text getMsg__9daNpcSv_cFv */
u32 daNpcSv_c::getMsg() {
    /* Nonmatching */
}

/* 00001EB4-00001EBC       .text setMessage__9daNpcSv_cFUl */
void daNpcSv_c::setMessage(u32 i_message) {
    mCurrMsgNo = i_message;
}

/* 00001EBC-00001F74       .text setAnmFromMsgTag__9daNpcSv_cFv */
void daNpcSv_c::setAnmFromMsgTag() {
    switch (dComIfGp_getMesgAnimeAttrInfo()) {
        case 0:
            setAnmTbl(&l_npc_anm_wait);
            break;
        case 1:
            setAnmTbl(l_npc_anm_ya1);
            break;
        case 2:
            setAnmTbl(&l_npc_anm_talk);
            break;
        case 3:
            setAnmTbl(&l_npc_anm_talk2);
            break;
        case 4:
            setAnmTbl(&l_npc_anm_talk3);
            break;
        case 5:
            setAnmTbl(l_npc_anm_ya2);
            break;
    }
    dComIfGp_setMesgAnimeAttrInfo(0xFF);
}

/* 00001F74-00001F94       .text getPrmNpcNo__9daNpcSv_cFv */
u8 daNpcSv_c::getPrmNpcNo() {
    if (0 <= argument && argument < 4) {
        return argument;
    }
    return 0;
}

/* 00001F94-0000209C       .text setMtx__9daNpcSv_cFv */
void daNpcSv_c::setMtx() {
    /* Nonmatching */
}

/* 0000209C-000023D4       .text chkAttention__9daNpcSv_cFv */
void daNpcSv_c::chkAttention() {
    /* Nonmatching */
}

/* 000023D4-00002520       .text lookBack__9daNpcSv_cFv */
void daNpcSv_c::lookBack() {
    /* Nonmatching */
}

/* 00002520-000025E8       .text playAnm__9daNpcSv_cFv */
void daNpcSv_c::playAnm() {
    mAnmFlag &= ~1;
    if (mpMorf->play(NULL, 0, 0) && mpAnmDat != NULL && mAnmLoopCnt > 0) {
        mAnmLoopCnt--;
        if (mAnmLoopCnt == 0) {
            mpAnmDat++;
            if (setAnmTbl(mpAnmDat)) {
                mAnmFlag |= 1;
            }
        } else {
            setAnm(mpAnmDat->mBckIdx, J3DFrameCtrl::EMode_NONE, 0.0f);
        }
    }
}

/* 000025E8-000026C8       .text setAnm__9daNpcSv_cFUcif */
void daNpcSv_c::setAnm(u8 i_bckIdx, int i_loopMode, f32 i_morf) {
    if (mAnmMorfOverride >= 0.0f) {
        i_morf = mAnmMorfOverride;
        mAnmMorfOverride = -1.0f;
    }
    J3DAnmTransformKey* pAnm = (J3DAnmTransformKey*)dComIfG_getObjectIDRes(l_arcname_tbl[mNpcNo], l_bck_ix_tbl[mNpcNo][i_bckIdx]);
    mpMorf->setAnm(pAnm, i_loopMode, i_morf, 1.0f, 0.0f, -1.0f, NULL);
    mBckIdx = i_bckIdx;
}

/* 000026C8-00002768       .text setAnmTbl__9daNpcSv_cFP9sSvAnmDat */
bool daNpcSv_c::setAnmTbl(sSvAnmDat* i_anmDat) {
    if (i_anmDat->mBckIdx == 0xFF) {
        mpAnmDat = NULL;
        return true;
    }
    mpAnmDat = i_anmDat;
    mAnmLoopCnt = mpAnmDat->mLoopCount;

    int loopMode = J3DFrameCtrl::EMode_LOOP;
    if (mAnmLoopCnt > 0) {
        loopMode = J3DFrameCtrl::EMode_NONE;
    }
    if (mBckIdx != mpAnmDat->mBckIdx || loopMode == J3DFrameCtrl::EMode_NONE) {
        setAnm(mpAnmDat->mBckIdx, loopMode, mpAnmDat->mMorf);
    }
    return false;
}

/* 00002768-000027E0       .text setCollision__9daNpcSv_cFP8dCcD_Cyl4cXyzff */
void daNpcSv_c::setCollision(dCcD_Cyl* i_cyl, cXyz i_center, f32 i_radius, f32 i_height) {
    i_cyl->SetC(i_center);
    i_cyl->SetR(i_radius);
    i_cyl->SetH(i_height);
    dComIfG_Ccsp()->Set(i_cyl);
}

/* 000027E0-0000293C       .text getTalkNo__9daNpcSv_cFv */
u8 daNpcSv_c::getTalkNo() {
    int isGrapplingHook;
    if (dComIfGs_checkGetItem(dItemNo_GRAPPLING_HOOK_e)) {
        isGrapplingHook = 1;
    } else {
        isGrapplingHook = 0;
    }

    mTalkNo = 0;
    if (!(mTalkFlags & TALK_FLAG_GOT_CHART)) {
        if (!(mTalkFlags & TALK_FLAG_1ST)) {
            if (isGrapplingHook) {
                mTalkNo = 1;
            } else {
                mTalkNo = 0;
            }
        } else if (!(mTalkFlags & TALK_FLAG_2ND)) {
            if (isGrapplingHook) {
                mTalkNo = 3;
            } else {
                mTalkNo = 2;
            }
        } else {
            if (isGrapplingHook) {
                mTalkNo = 5;
            } else {
                mTalkNo = 4;
            }
        }
    } else if (!isGrapplingHook) {
        if (!(mTalkFlags & TALK_FLAG_P2)) {
            mTalkNo = 6;
        } else {
            mTalkNo = 7;
        }
    } else if (!dComIfGs_isCollect(0, 1)) {
        if (!(mTalkFlags & TALK_FLAG_P3)) {
            mTalkNo = 8;
        } else {
            mTalkNo = 9;
        }
    } else if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2F80)) {
        mTalkNo = 10;
    } else {
        mTalkNo = 11;
    }
    return mTalkNo;
}

/* 0000293C-00002958       .text isTalkOK__9daNpcSv_cFv */
BOOL daNpcSv_c::isTalkOK() {
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SWIM_e)) {
        return FALSE;
    }
    return TRUE;
}

/* 00002958-00002978       .text daNpc_PeopleCreate__FPv */
static cPhs_State daNpc_PeopleCreate(void* i_this) {
    return ((daNpcSv_c*)i_this)->_create();
}

/* 00002978-0000299C       .text daNpc_PeopleDelete__FPv */
static BOOL daNpc_PeopleDelete(void* i_this) {
    return ((daNpcSv_c*)i_this)->_delete();
}

/* 0000299C-000029C0       .text daNpc_PeopleExecute__FPv */
static BOOL daNpc_PeopleExecute(void* i_this) {
    return ((daNpcSv_c*)i_this)->_execute();
}

/* 000029C0-000029E4       .text daNpc_PeopleDraw__FPv */
static BOOL daNpc_PeopleDraw(void* i_this) {
    return ((daNpcSv_c*)i_this)->_draw();
}

/* 000029E4-000029EC       .text daNpc_PeopleIsDelete__FPv */
static BOOL daNpc_PeopleIsDelete(void*) {
    return TRUE;
}

static actor_method_class daNpc_PeopleMethodTable = {
    (process_method_func)daNpc_PeopleCreate,   (process_method_func)daNpc_PeopleDelete, (process_method_func)daNpc_PeopleExecute,
    (process_method_func)daNpc_PeopleIsDelete, (process_method_func)daNpc_PeopleDraw,
};

actor_process_profile_definition g_profile_NPC_SV = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_SV_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpcSv_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_SV_e,
    /* Actor SubMtd */ &daNpc_PeopleMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
