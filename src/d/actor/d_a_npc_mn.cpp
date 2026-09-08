/**
 * d_a_npc_mn.cpp
 * NPC - Manny
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_mn.h"
#include "d/d_a_obj.h"
#include "d/d_com_lib_game.h"
#include "res/Object/Mn.h"

static char* l_npc_staff_id[] = {
    "Mn"
};

static const char* l_arcname_tbl[] = {"Mn"};

static const int l_bmd_ix_tbl[] = {
    dRes_ID_MN_BDL_MN_e,
};

static const int l_etc_bmd_ix_tbl[] = {
    dRes_ID_MN_BDL_MN_BAG_e
};

static const int l_bck_ix_tbl[] = {
    dRes_ID_MN_BCK_MN_WAIT01_e,
    dRes_ID_MN_BCK_MN_WAIT02_e,
    dRes_ID_MN_BCK_MN_TALK01_e,
    dRes_ID_MN_BCK_MN_TALK02_e,
    dRes_ID_MN_BCK_MN_WALK_e,
    dRes_ID_MN_BCK_MN_BIKKURI_e,
    dRes_ID_MN_BCK_MN_JUMP01_e,
    dRes_ID_MN_BCK_MN_JUMP02_e,
};

static const int l_btp_ix_tbl[] = {
    dRes_ID_MN_BTP_MN_MABA_e,
};

static sMnAnmDat l_npc_anm_wait = {
    0x00,
    0x08,
    0xFF
};

static sMnAnmDat l_npc_anm_wait2 = {
    0x01,
    0x08,
    0xFF
};

static sMnAnmDat l_npc_anm_talk = {
    0x02,
    0x08,
    0xFF,
};

static sMnAnmDat l_npc_anm_talk2 = {
    0x03,
    0x08,
    0xFF,
};

static sMnAnmDat l_npc_anm_walk = {
    0x04,
    0x08,
    0xFF,
};

static sMnAnmDat l_npc_anm_bikkuri[] = {
    {
        0x05,
        0x08,
        0x01,
    },
    {
        0x00,
        0x08,
        0xFF,
    },
};

static sMnAnmDat l_npc_anm_jump1[] = {
    {
        0x06,
        0x08,
        0x01,
    },
    {
        0xFF,
        0x08,
        0x00,
    },
};

static sMnAnmDat l_npc_anm_jump2 = {
    0x07,
    0x08,
    0xFF,
};

static NpcDatStruct l_npc_dat[] = {
{
        0x0FA0, 0x2710, 0x0000, 0x1770,
        0xF830, 0xD8F0, 0xE890, 0xF060,
        0x05DC, 0x0000, 0.0f  , 150.0f  ,
        120.0f, 250.0f, 0.0f, 0x7FFF,
        0x0514, 0x0190, 0x0000, 60.0f,
        0.5f, 3.0f , 0x0006, 0x0400  ,
        0x003C, 0x005A, 0x00C8, 0x012C,
        0x001E, 0x01, 0x01,
    },
    {
        0x0FA0, 0x2710, 0x0000, 0x1770,
        0xF830, 0xD8F0, 0xE890, 0xF060,
        0x05DC, 0x0000, 0.0f  , 150.0f  ,
        120.0f, 250.0f, 0.0f, 0x7FFF,
        0x0514, 0x0190, 0x0000, 60.0f,
        0.5f, 1.5f , 0x0006, 0x0400  ,
        0x003C, 0x005A, 0x00C8, 0x012C,
        0x001E, 0x01, 0x01,
    },
};

static u32 l_msg_mn_1st_talk[] = {
    0x35E9,
    0x35EA,
    0x35EB,
    0x0000
};

static u32 l_msg_mn_2nd_talk[] = {
    0x35EC,
    0x35ED,
    0x35EE,
    0x0000
};

static u32 l_msg_mn_1st_talk_in[] = {
    0x35F1,
    0x0000
};

static u32 l_msg_mn_2nd_talk_in[] = {
    0x35F2,
    0x0000
};

static u32 l_msg_mn_3rd_talk_in[] = {
    0x35F0,
    0x0000
};

static u32 l_msg_mn_comp_1st[] = {
    0x35F3,
    0x35F4,
    0x35F5,
    0x0000
};

static u32 l_msg_mn_comp_2nd[] = {
    0x35F6,
    0x0000
};

static u32 l_msg_mn_figure[] = {
    0x35F7,
    0x35F8,
    0x35F9,
    0x35FA,
    0x35FB,
    0x35FC,
    0x35FD,
    0x35FE,
    0x35FF,
    0x3600,
};

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsEnemy_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 40.0f,
        /* Height */ 160.0f,
    }},
};

static char* l_room_name[] = {
    "sea",
    "Pfigure",
    "figureA",
    "figureB",
    "figureC",
    "figureD",
    "figureE",
    "figureF",
    "figureG",
    "K_Testb",
};

static u16 l_figure_comp[] = {
    dSv_event_flag_c::UNK_95FF,
    dSv_event_flag_c::UNK_94FF,
    dSv_event_flag_c::UNK_93FF,
    dSv_event_flag_c::UNK_92FF,
    dSv_event_flag_c::UNK_91FF,
    dSv_event_flag_c::UNK_90FF,
    dSv_event_flag_c::UNK_8FFF,
    dSv_event_flag_c::UNK_8EFF,
    dSv_event_flag_c::UNK_8DFF,
    dSv_event_flag_c::UNK_8CFF,
    dSv_event_flag_c::UNK_B1FF,
    dSv_event_flag_c::UNK_9CFF,
    dSv_event_flag_c::UNK_84FF,
    dSv_event_flag_c::UNK_83FF,
    dSv_event_flag_c::UNK_82FF,
    dSv_event_flag_c::UNK_81FF,
    dSv_event_flag_c::UNK_80FF,
};

enum MoveProcIdx {
    MOVE_PROC_WAIT,
    MOVE_PROC_TALK,
    MOVE_PROC_TALK3,
    MOVE_PROC_WALK,
    MOVE_PROC_TURN,
};

/* 00000078-00000230       .text __ct__9daNpcMn_cFv */
daNpcMn_c::daNpcMn_c() {
    field_0x7B5 = 0;
    mMoveState = 0;
    field_0x77C = 0.0f;
    field_0x798 = 0;
    field_0x780 = -1.0f;
    field_0x7BD = 0;
    mHeadOnlyFollow = true;
    field_0x7A0 = home.angle.y;
    mBckIdx = 0;
    field_0x7A4 = 0;
    field_0x7C1 = chkPosNo();
    mNpcNo = getPrmNpcNo();
}

/* 000005E0-000006F8       .text daNpc_Mn_nodeCallBack__FP7J3DNodei */
static BOOL daNpc_Mn_nodeCallBack(J3DNode* i_node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* l_model = j3dSys.getModel();
        daNpcMn_c* i_this = (daNpcMn_c*)l_model->getUserArea();
        J3DJoint* l_joint = (J3DJoint*)i_node;

        u16 l_jointNo = l_joint->getJntNo();
        MTXCopy(l_model->getAnmMtx(l_jointNo), *calc_mtx);

        if (l_jointNo == i_this->m_jnt.getHeadJntNum()){
            cMtx_XrotM(*calc_mtx, (s16)i_this->m_jnt.getHead_y());
            cMtx_ZrotM(*calc_mtx, (s16)-i_this->m_jnt.getHead_x());
        }

        if (l_jointNo == i_this->m_jnt.getBackboneJntNum()){
            cMtx_XrotM(*calc_mtx, (s16)i_this->m_jnt.getBackbone_y());
            cMtx_ZrotM(*calc_mtx, (s16)-i_this->m_jnt.getBackbone_x());
        }
        MTXCopy(*calc_mtx, l_model->getAnmMtx(l_jointNo));
        MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
    }
    return TRUE;
}

/* 000006F8-00000718       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpcMn_c*)i_this)->createHeap();
}

/* 00000718-0000085C       .text phase_1__FP9daNpcMn_c */
cPhs__Handler phase_1(daNpcMn_c*) {
    /* Nonmatching */
}

/* 0000085C-000008D4       .text phase_2__FP9daNpcMn_c */
cPhs__Handler phase_2(daNpcMn_c*) {
    /* Nonmatching */
}

/* 000008D4-00000904       .text _create__9daNpcMn_cFv */
cPhs_State daNpcMn_c::_create() {
    static cPhs__Handler l_method[] = {
        (cPhs__Handler) &phase_1,
        (cPhs__Handler) &phase_2,
        (cPhs__Handler) NULL
    };

    return dComLbG_PhaseHandler(&mPhsMethod, l_method, this);
}

/* 00000904-00000BE0       .text createHeap__9daNpcMn_cFv */
BOOL daNpcMn_c::createHeap() {
    /* Nonmatching */
}

/* 00000BE0-00000C00       .text daNpcMn_XyCheckCB__FPvi */
static s16 daNpcMn_XyCheckCB(daNpcMn_c* i_this, int i_itemBtn) {
    return i_this->XyCheckCB(i_itemBtn);
}

/* 00000C00-00000F3C       .text createInit__9daNpcMn_cFv */
void daNpcMn_c::createInit() {
    /* Nonmatching */
}

/* 00000F3C-00000FE4       .text _delete__9daNpcMn_cFv */
bool daNpcMn_c::_delete() {
    /* Nonmatching */
}

/* 00000FE4-00001154       .text _draw__9daNpcMn_cFv */
bool daNpcMn_c::_draw() {
    /* Nonmatching */
}

typedef int(daNpcMn_c::*ExecuteInit_t)();
static ExecuteInit_t l_execute_init[] = {
    &daNpcMn_c::executeWaitInit,
    &daNpcMn_c::executeTalkInit,
    &daNpcMn_c::executeTalk3Init,
    &daNpcMn_c::executeWalkInit,
    &daNpcMn_c::executeTurnInit,

};

typedef void(daNpcMn_c::*MoveProc_t)();
static MoveProc_t moveProc[]={
    &daNpcMn_c::executeWait,
    &daNpcMn_c::executeTalk,
    &daNpcMn_c::executeTalk3,
    &daNpcMn_c::executeWalk,
    &daNpcMn_c::executeTurn,
};

/* 00001154-00001344       .text _execute__9daNpcMn_cFv */
bool daNpcMn_c::_execute() {
    /* Nonmatching */
}

/* 00001344-000013B4       .text executeCommon__9daNpcMn_cFv */
u8 daNpcMn_c::executeCommon() {
    if (field_0x7B1) {
        field_0x7B2 = true;
    } else {
        field_0x7B2 = false;
    }

    if (field_0x7B0 == 1 && mMoveState != MOVE_PROC_TALK) {
        executeSetMode(MOVE_PROC_TALK);
    }
    return field_0x7B0;
}

/* 000013B4-0000140C       .text executeSetMode__9daNpcMn_cFUc */
void daNpcMn_c::executeSetMode(unsigned char) {
    /* Nonmatching */
}

/* 0000140C-00001518       .text executeWaitInit__9daNpcMn_cFv */
int daNpcMn_c::executeWaitInit() {
    /* Nonmatching */
}

/* 00001518-000017CC       .text executeWait__9daNpcMn_cFv */
void daNpcMn_c::executeWait() {
    /* Nonmatching */
}

/* 000017CC-000017D4       .text executeTalkInit__9daNpcMn_cFv */
int daNpcMn_c::executeTalkInit() {
    return 1;
}

/* 000017D4-0000184C       .text executeTalk__9daNpcMn_cFv */
void daNpcMn_c::executeTalk() {
    /* Nonmatching */
}

/* 0000184C-0000185C       .text executeTalk3Init__9daNpcMn_cFv */
int daNpcMn_c::executeTalk3Init() {
    field_0x7C3 = 0;
    return 4;
}

/* 0000185C-0000191C       .text executeTalk3__9daNpcMn_cFv */
void daNpcMn_c::executeTalk3() {
    /* Nonmatching */
}

/* 0000191C-00001948       .text executeWalkInit__9daNpcMn_cFv */
int daNpcMn_c::executeWalkInit() {
    setAnmTbl(&l_npc_anm_walk);
    return 2;
}

/* 00001948-00001BD4       .text executeWalk__9daNpcMn_cFv */
void daNpcMn_c::executeWalk() {
    /* Nonmatching */
}

/* 00001BD4-00001D18       .text executeTurnInit__9daNpcMn_cFv */
int daNpcMn_c::executeTurnInit() {
    /* Nonmatching */
}

/* 00001D18-00001DE8       .text executeTurn__9daNpcMn_cFv */
void daNpcMn_c::executeTurn() {
    /* Nonmatching */
}

/* 00001DE8-00001E80       .text checkOrder__9daNpcMn_cFv */
void daNpcMn_c::checkOrder() {
    /* Nonmatching */
}

/* 00001E80-00001F00       .text eventOrder__9daNpcMn_cFv */
void daNpcMn_c::eventOrder() {
    /* Nonmatching */
}

/* 00001F00-00001F74       .text eventMove__9daNpcMn_cFv */
void daNpcMn_c::eventMove() {
    /* Nonmatching */
}

/* 00001F74-00002194       .text privateCut__9daNpcMn_cFv */
void daNpcMn_c::privateCut() {
    /* Nonmatching */
    static char* cut_name_tbl[] = {
        "MES_SET",
        "GET_ITEM",
        "WAIT",
        "HATCH",
        "BIKKURI",
        "TURN",
        "WALK",
        "LOOK",
        "JUMP",
        "SWON",
    };
}

/* 00002194-0000226C       .text eventMesSetInit__9daNpcMn_cFi */
void daNpcMn_c::eventMesSetInit(int) {
    /* Nonmatching */
}

/* 0000226C-000022A0       .text eventMesSet__9daNpcMn_cFv */
u32 daNpcMn_c::eventMesSet() {
    return (0x12 - talk2(0)) == false;
}

/* 000022A0-000022F8       .text eventGetItemInit__9daNpcMn_cFv */
void daNpcMn_c::eventGetItemInit() {
    /* Nonmatching */
}

/* 000022F8-00002358       .text eventWaitInit__9daNpcMn_cFi */
void daNpcMn_c::eventWaitInit(int) {
    /* Nonmatching */
}

/* 00002358-000023E8       .text eventWait__9daNpcMn_cFi */
void daNpcMn_c::eventWait(int) {
    /* Nonmatching */
}

/* 000023E8-00002448       .text eventSwOnInit__9daNpcMn_cFi */
void daNpcMn_c::eventSwOnInit(int) {
    /* Nonmatching */
}

/* 00002448-000024AC       .text eventSwOn__9daNpcMn_cFv */
void daNpcMn_c::eventSwOn() {
    /* Nonmatching */
}

/* 000024AC-00002540       .text eventHatchInit__9daNpcMn_cFv */
void daNpcMn_c::eventHatchInit() {
    /* Nonmatching */
}

/* 00002540-00002578       .text eventHatch__9daNpcMn_cFv */
void daNpcMn_c::eventHatch() {
    /* Nonmatching */
}

/* 00002578-000025EC       .text eventBikkuriInit__9daNpcMn_cFi */
void daNpcMn_c::eventBikkuriInit(int) {
    /* Nonmatching */
}

/* 000025EC-00002644       .text eventBikkuri__9daNpcMn_cFv */
void daNpcMn_c::eventBikkuri() {
    /* Nonmatching */
}

/* 00002644-0000266C       .text eventTurnInit__9daNpcMn_cFv */
void daNpcMn_c::eventTurnInit() {
    setAnmTbl(&l_npc_anm_wait);
}

/* 0000266C-000027B4       .text eventTurn__9daNpcMn_cFi */
void daNpcMn_c::eventTurn(int) {
    /* Nonmatching */
}

/* 000027B4-000027DC       .text eventWalkInit__9daNpcMn_cFv */
void daNpcMn_c::eventWalkInit() {
    setAnmTbl(&l_npc_anm_walk);
}

/* 000027DC-0000293C       .text eventWalk__9daNpcMn_cFv */
void daNpcMn_c::eventWalk() {
    /* Nonmatching */
}

/* 0000293C-00002964       .text eventLookInit__9daNpcMn_cFv */
void daNpcMn_c::eventLookInit() {
    setAnmTbl(l_npc_anm_jump1);
}

/* 00002964-00002988       .text eventLook__9daNpcMn_cFv */
bool daNpcMn_c::eventLook() {
    return mpMorf->getFrame() >= 72.0f;
}

/* 00002988-00002A90       .text eventJumpInit__9daNpcMn_cFi */
void daNpcMn_c::eventJumpInit(int) {
    /* Nonmatching */
}

/* 00002A90-00002AE8       .text eventJump__9daNpcMn_cFv */
void daNpcMn_c::eventJump() {
    /* Nonmatching */
}

/* 00002AE8-00002C30       .text talk2__9daNpcMn_cFi */
u16 daNpcMn_c::talk2(int i1) {
    u16 l_status = 0xFF;
    if (mCurrMsgBsPcId == fpcM_ERROR_PROCESS_ID_e) {
        if (i1 == 1) {
            mCurrMsgNo = getMsg();
        }
        mCurrMsgBsPcId = fopMsgM_messageSet(mCurrMsgNo, this);
        mpCurrMsg = NULL;
        mLastMsgStatus = -1;
    } else if (mpCurrMsg) {
        l_status = mpCurrMsg->mStatus;
        switch (l_status) {
            case fopMsgStts_MSG_DISPLAYED_e:
                mpCurrMsg->mStatus = next_msgStatus(&mCurrMsgNo);
                if (mpCurrMsg->mStatus == fopMsgStts_MSG_CONTINUES_e) {
                    fopMsgM_messageSet(mCurrMsgNo);
                }
                break;
            case fopMsgStts_MSG_TYPING_e:
                if (mLastMsgStatus == fopMsgStts_MSG_CONTINUES_e) {
                    chkMsg();
                }
                break;
            case fopMsgStts_BOX_CLOSED_e:
                mpCurrMsg->mStatus = fopMsgStts_MSG_DESTROYED_e;
                mCurrMsgBsPcId = fpcM_ERROR_PROCESS_ID_e;
                break;
        }
        mLastMsgStatus = l_status;
        anmAtr(l_status);
    } else {
        mpCurrMsg = fopMsgM_SearchByID(mCurrMsgBsPcId);
    }
    return l_status;
}

/* 00002C30-00002D68       .text talk3__9daNpcMn_cFi */
void daNpcMn_c::talk3(int) {
    /* Nonmatching */
}

/* 00002D68-00002DB8       .text next_msgStatus__9daNpcMn_cFPUl */
u16 daNpcMn_c::next_msgStatus(unsigned long*) {
    /* Nonmatching */
}

/* 00002DB8-00002F7C       .text getMsg__9daNpcMn_cFv */
u32 daNpcMn_c::getMsg() {
    /* Nonmatching */
}

/* 00002F7C-00002F8C       .text getMsg3__9daNpcMn_cFv */
u32 daNpcMn_c::getMsg3() {
    mpMsgNo = 0;
    return 0x35EF;
}

/* 00002F8C-00002F90       .text chkMsg__9daNpcMn_cFv */
void daNpcMn_c::chkMsg() {
    return;
}

/* 00002F90-00002F98       .text setMessage__9daNpcMn_cFUl */
void daNpcMn_c::setMessage(u32 i_message) {
    mCurrMsgNo = i_message;
    return;
}

/* 00002F98-0000302C       .text setAnmFromMsgTag__9daNpcMn_cFv */
void daNpcMn_c::setAnmFromMsgTag() {
    /* Nonmatching */
}

/* 0000302C-0000303C       .text getPrmNpcNo__9daNpcMn_cFv */
bool daNpcMn_c::getPrmNpcNo() {
    return field_0x7C1 != false;
}

/* 0000303C-00003068       .text getPrmRailID__9daNpcMn_cFv */
u8 daNpcMn_c::getPrmRailID() {
    return daObj::PrmAbstract(this, PRM_RAIL_W, PRM_RAIL_S);
}

/* 00003068-00003094       .text getPrmSwitchBit__9daNpcMn_cFv */
u8 daNpcMn_c::getPrmSwitchBit() {
    return daObj::PrmAbstract(this, PRM_SWITCH_W, PRM_SWITCH_S);
}

/* 00003094-000030C0       .text getPrmSwitchBit2__9daNpcMn_cFv */
u8 daNpcMn_c::getPrmSwitchBit2() {
    return daObj::PrmAbstract(this, PRM_SWITCH2_W, PRM_SWITCH2_S);
}

/* 000030C0-00003148       .text setMtx__9daNpcMn_cFv */
void daNpcMn_c::setMtx() {
    /* Nonmatching */
}

/* 00003148-00003478       .text chkAttention__9daNpcMn_cFv */
void daNpcMn_c::chkAttention() {
    /* Nonmatching */
}

/* 00003478-000035C4       .text lookBack__9daNpcMn_cFv */
void daNpcMn_c::lookBack() {
    /* Nonmatching */
}

/* 000035C4-000036D0       .text initTexPatternAnm__9daNpcMn_cFb */
void daNpcMn_c::initTexPatternAnm(bool) {
    /* Nonmatching */
}

/* 000036D0-0000373C       .text playTexPatternAnm__9daNpcMn_cFv */
void daNpcMn_c::playTexPatternAnm() {
    /* Nonmatching */
}

/* 0000373C-000037F8       .text playAnm__9daNpcMn_cFv */
void daNpcMn_c::playAnm() {
    /* Nonmatching */
}

/* 000037F8-000038C8       .text setAnm__9daNpcMn_cFUcif */
void daNpcMn_c::setAnm(unsigned char, int, float) {
    /* Nonmatching */
}

/* 000038C8-00003974       .text setAnmTbl__9daNpcMn_cFP9sMnAnmDat */
void daNpcMn_c::setAnmTbl(sMnAnmDat*) {
    /* Nonmatching */
}

/* 00003974-0000397C       .text XyCheckCB__9daNpcMn_cFi */
s16 daNpcMn_c::XyCheckCB(int) {
    return false;
}

/* 0000397C-000039E0       .text getRand__9daNpcMn_cFi */
void daNpcMn_c::getRand(int) {
    /* Nonmatching */
}

/* 000039E0-00003A58       .text setCollision__9daNpcMn_cFP8dCcD_Cyl4cXyzff */
void daNpcMn_c::setCollision(dCcD_Cyl*, cXyz, float, float) {
    /* Nonmatching */
}

/* 00003A58-00003AC4       .text chkEndEvent__9daNpcMn_cFv */
void daNpcMn_c::chkEndEvent() {
    /* Nonmatching */
}

/* 00003AC4-00003B38       .text chkPosNo__9daNpcMn_cFv */
u8 daNpcMn_c::chkPosNo() {
    /* Nonmatching */
}

/* 00003B38-00003CD8       .text getPosNo__9daNpcMn_cFv */
void daNpcMn_c::getPosNo() {
    /* Nonmatching */
}

/* 00003CD8-00003CE8       .text isChangePos__9daNpcMn_cFUc */
u32 daNpcMn_c::isChangePos(u8 i_posNo) {
    return i_posNo == false;
}

/* 00003CE8-00003D08       .text daNpc_MnCreate__FPv */
static cPhs_State daNpc_MnCreate(void* i_this) {
    return ((daNpcMn_c*)i_this)->_create();
}

/* 00003D08-00003D2C       .text daNpc_MnDelete__FPv */
static BOOL daNpc_MnDelete(void* i_this) {
    return ((daNpcMn_c*)i_this)->_delete();
}

/* 00003D2C-00003D50       .text daNpc_MnExecute__FPv */
static BOOL daNpc_MnExecute(void* i_this) {
    return ((daNpcMn_c*)i_this)->_execute();
}

/* 00003D50-00003D74       .text daNpc_MnDraw__FPv */
static BOOL daNpc_MnDraw(void* i_this) {
    return ((daNpcMn_c*)i_this)->_draw();
}

/* 00003D74-00003D7C       .text daNpc_MnIsDelete__FPv */
static BOOL daNpc_MnIsDelete(void*) {
    return TRUE;
}

static actor_method_class daNpc_MnMethodTable = {
    (process_method_func)daNpc_MnCreate,
    (process_method_func)daNpc_MnDelete,
    (process_method_func)daNpc_MnExecute,
    (process_method_func)daNpc_MnIsDelete,
    (process_method_func)daNpc_MnDraw,
};

actor_process_profile_definition g_profile_NPC_MN = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_MN_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpcMn_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_MN_e,
    /* Actor SubMtd */ &daNpc_MnMethodTable,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
