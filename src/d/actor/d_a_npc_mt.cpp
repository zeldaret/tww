/**
 * d_a_npc_mt.cpp
 * NPC - Carlov
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_mt.h"
#include "d/d_com_lib_game.h"
#include "d/d_com_inf_game.h"
#include "d/d_snap.h"
#include "d/d_picture_box.h"
#include "res/Object/Niten.h"

#define TOTAL_FIGURE_COUNT 0x86

const char daNpcMt_c::m_arcname[] = "Niten";

static char* l_npc_staff_id[] = {
    "Mt"
};

static const char* l_arcname_tbl[] = {
    "Niten"
};

static const int l_bmd_ix_tbl[] = {
    dRes_ID_NITEN_BDL_MT_e,
};

static const int l_bck_ix_tbl[] = {
    dRes_ID_NITEN_BCK_MT_WAIT01_e,
    dRes_ID_NITEN_BCK_MT_TALK01_e,
    dRes_ID_NITEN_BCK_MT_TALK02_e,
    dRes_ID_NITEN_BCK_MT_TALK03_e,
    dRes_ID_NITEN_BCK_MT_TALK04_e,
    dRes_ID_NITEN_BCK_MT_TUKURU_e,
};

static const int l_btp_ix_tbl[] = {
    dRes_ID_NITEN_BTP_MT_MABA_e,
};

static sMtAnmDat l_npc_anm_wait[] = {
    {
        0x00,
        0x08,
        0xFF,
    },
};

static sMtAnmDat l_npc_anm_talk[] = {
    {
        0x01,
        0x08,
        0xFF,
    },
};

static sMtAnmDat l_npc_anm_talk2[] = {
    {
        0x02,
        0x08,
        0xFF,
    },
};

static sMtAnmDat l_npc_anm_talk3[] = {
    {
        0x03,
        0x08,
        0xFF,
    },
};

static sMtAnmDat l_npc_anm_talk4[] = {
    {
        0x04,
        0x08,
        0xFF,
    },
};

static sMtAnmDat l_npc_anm_talk5[] = {
    {
        0x04,
        0x08,
        0x02,
    },

    {
        0x01,
        0x08,
        0xFF,
    },
};

static sMtAnmDat l_npc_anm_tukuru[] = {
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

static NpcDatStruct l_npc_dat[] = {
    {
    0x0FA0,
    0x1B58,
    0,
    0,
    0xF448,
    0xE4A8,
    0,
    0,
    0x01F4,
    0,
    0,
    190.0f,
    150.0f,
    250.0f,
    400.0f,
    0x4000,
    0x0800,
    0x0190,
    0,
    60.0f,
    0.5f,
    3.0f,
    0x0006,
    0x0400,
    0x003C,
    0x005A,
    0x00C8,
    0x012C,
    0x001E,
    false,
    true,
    },
};

static u32 l_msg_mt_1st_talk[] = {
    0x365E,
    0x365F,
    0x3660,
    0x3661,
    0x3662,
    0x3663,
    0x3664,
    0x0000,
};

static u32 l_msg_mt_2nd_talk[] = {
    0x3665,
    0x3666,
    0x3667,
    0x0000,
};

static u32 l_msg_mt_3rd_talk[] = {
    0x3668,
    0x0000,
};

static u32 l_msg_mt_4th_talk[] = {
    0x3669,
    0x0000,
};

static u32 l_msg_mt_making[] = {
    0x3654,
    0x0000,
};

static u32 l_msg_mt_1st_kansei[] = {
    0x364D,
    0x364E,
    0x3650,
    0x0001,
    0x0000,
};

static u32 l_msg_mt_2nd_kansei[] = {
    0x364D,
    0x364F,
    0x3650,
    0x0001,
    0x0000,
};

static u32 l_msg_mt_room[] = {
    0x366B,
    0x366B,
    0x366C,
    0x366D,
    0x366E,
    0x366F,
    0x3670,
    0x3671,
};

static u32 l_msg_mt_gallery[] = {
    0x3651,
    0x0000,
};

static u32 l_msg_mt_room_in[] = {
    0x3652,
    0x0000,
};

static u32 l_msg_mt_kansei_end[] = {
    0x3653,
    0x0000,
};

static u32 l_msg_mt_no_color[] = {
    0x3655,
    0x0000,
};

static u32 l_msg_mt_no_figure[] = {
    0x3656,
    0x0000,
};

static u32 l_msg_mt_maked[] = {
    0x3658,
    0x0000,
};

static u32 l_msg_mt_face_ng[] = {
    0x3659,
    0x0000,
};

static u32 l_msg_mt_body_ng[] = {
    0x365A,
    0x0000,
};

static u32 l_msg_mt_make_1st[] = {
    0x365B,
    0x3674,
    0x365C,
    0x0002,
};

static u32 l_msg_mt_make_2nd[] = {
    0x365B,
    0x3674,
    0x365D,
    0x0002,
};

static u32 l_msg_mt_make_1st_mt[] = {
    0x3672,
    0x3674,
    0x365C,
    0x0002,
};

static u32 l_msg_mt_make_2nd_mt[] = {
    0x3672,
    0x3674,
    0x365D,
    0x0002,
};

static u32 l_msg_mt_make_1st_mn[] = {
    0x3673,
    0x3674,
    0x365C,
    0x0002,
};

static u32 l_msg_mt_make_2nd_mn[] = {
    0x3673,
    0x3674,
    0x365D,
    0x0002,
};

static u32* l_msg_mt_make[] = {
    l_msg_mt_make_1st,
    l_msg_mt_make_2nd,
};

static u32* l_msg_mt_make_mt[] = {
    l_msg_mt_make_1st_mt,
    l_msg_mt_make_2nd_mt,
};

static u32* l_msg_mt_make_mn[] = {
    l_msg_mt_make_1st_mn,
    l_msg_mt_make_2nd_mn,
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

static char* l_figure_room_name[] = {
    "Pfigure",
    "figureA",
    "figureB",
    "figureC",
    "figureD",
    "figureE",
    "figureF",
    "figureG",
};

/* 00000078-00000228       .text __ct__9daNpcMt_cFv */
daNpcMt_c::daNpcMt_c() {
    mNpcNo = getPrmNpcNo();
    m747 = 0;
    m746 = 0;
    m718 = 0.0f;
    m72C = 0;
    m71C = -1.0f;
    m74F = 0;
    m728 = 1;
    m732 = home.angle.y;
    m74A = 0;
    m736 = 0;
}

/* 000005D8-000006F4       .text daNpc_Mt_nodeCallBack__FP7J3DNodei */
static BOOL daNpc_Mt_nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == 0) {
        J3DModel* model = j3dSys.getModel();
        daNpcMt_c* i_this = (daNpcMt_c*)model->getUserArea();
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        
        MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);

        if(jntNo == i_this->m_jnt.getHeadJntNum()) {
            cMtx_XrotM(*calc_mtx, (s16)i_this->m_jnt.getHead_y());
            cMtx_ZrotM(*calc_mtx, (s16)-i_this->m_jnt.getHead_x());
        }

        else if(jntNo == i_this->m_jnt.getBackboneJntNum()) {
            cMtx_XrotM(*calc_mtx, (s16)i_this->m_jnt.getBackbone_y());
            cMtx_ZrotM(*calc_mtx, (s16)-i_this->m_jnt.getBackbone_x());
        }

        model->setAnmMtx(jntNo, *calc_mtx);
        MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
    }
    return TRUE;
}

/* 000006F4-00000714       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daNpcMt_c*>(i_this)->createHeap();
}

/* 00000714-00000858       .text phase_1__FP9daNpcMt_c */
static cPhs_State phase_1(daNpcMt_c* i_this) {
    BOOL bVar1 = FALSE;
    cPhs_State phase_state = cPhs_NEXT_e;
    
    fopAcM_ct(i_this, daNpcMt_c);
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_3D08)) {
        bVar1 = TRUE;
    }
    else if (!dComIfGp_getStartStagePoint()) {
        if (i_this->isComp()) {
            bVar1 = TRUE;
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_3D08);
        }
        else {
            dComIfGs_offTmpBit(dSv_event_tmp_flag_c::UNK_0202);
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_4080)) {
                dComIfGs_offEventBit(dSv_event_flag_c::UNK_3080);
                dComIfGs_offEventBit(dSv_event_flag_c::UNK_2F01);
                dComIfGs_offEventBit(dSv_event_flag_c::UNK_4080);
                dComIfGs_offEventBit(dSv_event_flag_c::UNK_3F01);
                dComIfGs_offEventBit(dSv_event_flag_c::UNK_4040);
            }
        }
    }
    
    if (bVar1) {
        i_this->setFigure(0x40);
        phase_state = cPhs_STOP_e;
    }
    else {
        i_this->setResFlag(1);
        phase_state = cPhs_NEXT_e;
    }
    return phase_state;
}

/* 00000858-000008D8       .text phase_2__FP9daNpcMt_c */
static cPhs_State phase_2(daNpcMt_c* i_this) {
    cPhs_State phase_state = dComIfG_resLoad(i_this->getPhaseP(), l_arcname_tbl[i_this->getNpcNo()]);
    if (phase_state == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(i_this, CheckCreateHeap, 0x2900)) {
            return i_this->createInit();
        } else {
#if VERSION > VERSION_DEMO
            i_this->mpMorf = NULL;
#endif
            return cPhs_ERROR_e;
        }
    }
    return phase_state;
}

/* 000008D8-00000908       .text _create__9daNpcMt_cFv */
cPhs_State daNpcMt_c::_create() {
    static cPhs__Handler l_method[] = {
        (cPhs__Handler)phase_1,
        (cPhs__Handler)phase_2,
        NULL,
    };
    return dComLbG_PhaseHandler(&mPhs, l_method, this);
}

/* 00000908-00000B98       .text createHeap__9daNpcMt_cFv */
BOOL daNpcMt_c::createHeap() {
    J3DModelData* modelData = (J3DModelData *)dComIfG_getObjectIDRes(l_arcname_tbl[mNpcNo], l_bmd_ix_tbl[mNpcNo]);
    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL, NULL,
        (J3DAnmTransform*)dComIfG_getObjectIDRes(l_arcname_tbl[mNpcNo], l_bck_ix_tbl[m74A]),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, NULL,
        0x80000, 0x11020022
    );

    m_jnt.setHeadJntNum(modelData->getJointName()->getIndex("head"));
    JUT_ASSERT(DEMO_SELECT(904, 905), m_jnt.getHeadJntNum() >= 0);
    m_jnt.setBackboneJntNum(modelData->getJointName()->getIndex("backbone"));
    JUT_ASSERT(DEMO_SELECT(908, 909), m_jnt.getBackboneJntNum() >= 0);

    if (!initTexPatternAnm(false)) {
        return FALSE;
    }

    for(u16 i = 0; i < modelData->getJointNum(); i++) {
        if(i == m_jnt.getHeadJntNum() || i == m_jnt.getBackboneJntNum()) {
            modelData->getJointNodePointer(i)->setCallBack(daNpc_Mt_nodeCallBack);
        }
    }

    mpMorf->getModel()->setUserArea((u32)this);
    mAcchCir.SetWall(30.0f, 30.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this), fopAcM_GetAngle_p(this), fopAcM_GetShapeAngle_p(this));
    return TRUE;
}

/* 00000B98-00000BB8       .text daNpcMt_XyCheckCB__FPvi */
static s16 daNpcMt_XyCheckCB(void* i_this, int i_itemBtn) {
    return ((daNpcMt_c*)i_this)->XyCheckCB(i_itemBtn);
}

/* 00000BB8-00000DEC       .text createInit__9daNpcMt_cFv */
cPhs_State daNpcMt_c::createInit() {
#if VERSION == VERSION_DEMO
    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(dNpc_cyl_src);
    mCyl.SetStts(&mStts);
    setCollision(&mCyl, current.pos, l_npc_dat[mNpcNo].field_0x30, 150.0f);
#endif
    gravity = -9.0f;
    setAnmTbl(l_npc_anm_wait);
    mMtGetItemEventIdx = dComIfGp_evmng_getEventIdx("MT_GET_ITEM", 0xff);
    eventInfo.mpCheckCB = daNpcMt_XyCheckCB;
    mEventCut.setActorInfo2(l_npc_staff_id[mNpcNo], this);
#if VERSION == VERSION_DEMO
    setMtx();
#endif
    m73E = 0;
    m742 = 0;
    m743 = 0;
    m752 = 0;
    attnOff();
    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -70.0f, 0.0f, -70.0f, 70.0f, 200.0f, 70.0f);
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0x6E;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0x6E;
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_UNK1000000_e;
    m_jnt.setParam( 
        l_npc_dat[mNpcNo].mMax_backbone_x, 
        l_npc_dat[mNpcNo].mMax_backbone_y,
        l_npc_dat[mNpcNo].mMin_backbone_x, 
        l_npc_dat[mNpcNo].mMin_backbone_y,
        l_npc_dat[mNpcNo].mMax_head_x, 
        l_npc_dat[mNpcNo].mMax_head_y,
        l_npc_dat[mNpcNo].mMin_head_x,
        l_npc_dat[mNpcNo].mMin_head_y,
        l_npc_dat[mNpcNo].mMax_turn_step
    );
    m750 = l_npc_dat[mNpcNo].field_0x4A;
    m751 = l_npc_dat[mNpcNo].field_0x4B;
    m720 = l_npc_dat[mNpcNo].field_0x20;
    m730 = l_npc_dat[mNpcNo].field_0x28;
    mObjAcch.CrrPos(*dComIfG_Bgsp());
#if VERSION > VERSION_DEMO
    setMtx();
    mpMorf->getModel()->calc();
    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(dNpc_cyl_src);
    mCyl.SetStts(&mStts);
    setCollision(&mCyl, current.pos, l_npc_dat[mNpcNo].field_0x30, 150.0f);
#endif
    return cPhs_COMPLEATE_e;
}

/* 00000DEC-00000F6C       .text _delete__9daNpcMt_cFv */
bool daNpcMt_c::_delete() {
#if VERSION == VERSION_DEMO
    if (m747 != 0) {
        dComIfG_resDeleteDemo(&mPhsArcname, l_arcname_tbl[mNpcNo]);
    }
    if(mpMorf != NULL){
        mpMorf->stopZelAnime();
    }
#else
    dComIfG_resDeleteDemo(&mPhsArcname, l_arcname_tbl[mNpcNo]);
    if(heap != NULL && mpMorf != NULL){
        mpMorf->stopZelAnime();
    }
#endif

    if(dComIfGp_isEnableNextStage()){
        int roomId;
        for(roomId = 1; roomId <= 7; roomId++) {
            if(!strcmp(dComIfGp_getNextStageName(), l_figure_room_name[roomId])) {
                break;
            }
        }
        if (roomId <= 7) {
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_4080)) {
                int temp = dSnap_GetFigRoomId(dComIfGs_getEventReg(dSv_event_flag_c::UNK_A9FF));
                if(temp == roomId) {
                    dComIfGs_onEventBit(dSv_event_flag_c::UNK_3F01);
                }
            }
        } else {
            dComIfGs_offTmpBit(dSv_event_tmp_flag_c::UNK_0202);
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_4080)) {
                dComIfGs_offEventBit(dSv_event_flag_c::UNK_3080);
                dComIfGs_offEventBit(dSv_event_flag_c::UNK_2F01);
                dComIfGs_offEventBit(dSv_event_flag_c::UNK_4080);
                dComIfGs_offEventBit(dSv_event_flag_c::UNK_3F01);
                dComIfGs_offEventBit(dSv_event_flag_c::UNK_4040);
            }
        }
    }


    return true;
}

/* 00000F6C-0000107C       .text _draw__9daNpcMt_cFv */
bool daNpcMt_c::_draw() {
    J3DModel* model = mpMorf->getModel();
    J3DModelData *model_data = model->getModelData();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(model, &tevStr);
    mBtpAnm.entry(model_data, mFrame);
    mpMorf->updateDL();
    mBtpAnm.remove(model_data);

    cXyz shadowPos(
        current.pos.x,
        current.pos.y + 150.0f,
        current.pos.z
    );

    mShadowId = dComIfGd_setShadow(
        mShadowId, 1, mpMorf->getModel(), &shadowPos, 800.0f, 20.0f,
        current.pos.y, mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr
    );

    dSnap_RegistFig(DSNAP_TYPE_NPC_MT, this, 1.0f, 1.0f, 1.0f);
    return true;
}

static daNpcMt_c::InitFunc_t l_execute_init[] = {
    &daNpcMt_c::executeWaitInit,
    &daNpcMt_c::executeTalkInit,
};

static daNpcMt_c::MoveFunc_t moveProc[] = {
    &daNpcMt_c::executeWait,
    &daNpcMt_c::executeTalk,
};

/* 0000107C-000011D0       .text _execute__9daNpcMt_cFv */
bool daNpcMt_c::_execute() {
    chkAttention();
    checkOrder();

    if (!dComIfGp_event_runCheck() || eventInfo.checkCommandTalk()) {
        (this->*moveProc[m746])();
    } else {
        eventMove();
    }

    eventOrder();
    playTexPatternAnm();
    playAnm();

    setCollision(&mCyl, current.pos, l_npc_dat[mNpcNo].field_0x30, 150.0f);

    attention_info.position.set(current.pos.x, current.pos.y + l_npc_dat[mNpcNo].field_0x18, current.pos.z);
    eyePos.set(current.pos.x, current.pos.y + l_npc_dat[mNpcNo].field_0x1C, current.pos.z);

    lookBack();
    setMtx();
    return false;
}

/* 000011D0-00001240       .text executeCommon__9daNpcMt_cFv */
BOOL daNpcMt_c::executeCommon() {
    if (m743) {
        m744 = 1;
    }
    else {
        m744 = 0;
    }

    if (m742 == 1 && m746 != 1) {
        executeSetMode(1);
    }

    return m742;
}

/* 00001240-00001294       .text executeSetMode__9daNpcMt_cFUc */
void daNpcMt_c::executeSetMode(u8 param_1) {
    m718 = 0.0f;
    m746 = (this->*l_execute_init[param_1])();
}

/* 00001294-00001320       .text executeWaitInit__9daNpcMt_cFv */
s32 daNpcMt_c::executeWaitInit() {
    speedF = 0.0f;
    setAnmTbl(l_npc_anm_wait);
    m_jnt.setParam( 
        l_npc_dat[mNpcNo].mMax_backbone_x, 
        l_npc_dat[mNpcNo].mMax_backbone_y,
        l_npc_dat[mNpcNo].mMin_backbone_x, 
        l_npc_dat[mNpcNo].mMin_backbone_y,
        l_npc_dat[mNpcNo].mMax_head_x, 
        l_npc_dat[mNpcNo].mMax_head_y,
        l_npc_dat[mNpcNo].mMin_head_x,
        l_npc_dat[mNpcNo].mMin_head_y,
        l_npc_dat[mNpcNo].mMax_turn_step
    );
    return FALSE;
}

/* 00001320-00001368       .text executeWait__9daNpcMt_cFv */
void daNpcMt_c::executeWait() {
    executeCommon();
    if(m74A) {
        setAnmTbl(l_npc_anm_wait);
    }
}

/* 00001368-00001370       .text executeTalkInit__9daNpcMt_cFv */
s32 daNpcMt_c::executeTalkInit() {
    return TRUE;
}

/* 00001370-000013E8       .text executeTalk__9daNpcMt_cFv */
void daNpcMt_c::executeTalk() {
    executeCommon();
    if(talk2(1) == fopMsgStts_BOX_CLOSED_e) {
        m742 = 0;
        executeSetMode(0);
        dComIfGp_event_reset();
    }
    else {
        setAnmFromMsgTag();
    }
}

/* 000013E8-00001480       .text checkOrder__9daNpcMt_cFv */
void daNpcMt_c::checkOrder() {
    if(eventInfo.checkCommandDemoAccrpt()) {
        if(dComIfGp_evmng_startCheck(mMtGetItemEventIdx) && m744 == 3) {
            m744 = 0;
        }
    }
    else if (eventInfo.checkCommandTalk() && (m744 == 2 || m744 == 1)) {
        m742 = 1;
        executeSetMode(1);
    }
}

/* 00001480-0000150C       .text eventOrder__9daNpcMt_cFv */
void daNpcMt_c::eventOrder() {
    if(m744 == 2 || m744 == 1) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
        if(m744 == 2) {
            fopAcM_orderSpeakEvent(this);
        }
    }
    else if(m744 == 3) {
        fopAcM_orderChangeEventId(dComIfGp_getPlayer(0), this, mMtGetItemEventIdx, 0, 0xffff);
    }
}

/* 0000150C-00001580       .text eventMove__9daNpcMt_cFv */
void daNpcMt_c::eventMove() {
    if(!chkEndEvent()) {
        bool oldFlag = mEventCut.getAttnFlag();
        if(mEventCut.cutProc()) {
            if(!mEventCut.getAttnFlag()) {
                mEventCut.setAttnFlag(oldFlag);
            }
        }
        else {
            privateCut();
            setAnmFromMsgTag();
        }
    }
}

/* 00001580-000016B0       .text privateCut__9daNpcMt_cFv */
void daNpcMt_c::privateCut() {
    static char* cut_name_tbl[] = {
        "MES_SET",
        "GET_ITEM",
    };

    int staffIdx = dComIfGp_evmng_getMyStaffId(l_npc_staff_id[mNpcNo]);
    if(staffIdx != -1) {
        m74D = dComIfGp_evmng_getMyActIdx(staffIdx, cut_name_tbl, ARRAY_SIZE(cut_name_tbl), TRUE, 0);
        if(m74D == -1) {
            dComIfGp_evmng_cutEnd(staffIdx);
            return;
        }

        if(dComIfGp_evmng_getIsAddvance(staffIdx)) {
            switch(m74D) {
                case 0:
                    eventMesSetInit(staffIdx);
                    break;
                case 1:
                    eventGetItemInit();
                    break;
            }
        }

        bool temp;
        switch(m74D) {
            case 0:
                temp = eventMesSet();
                break;
            default:
                temp = true;
        }

        if(temp) {
            dComIfGp_evmng_cutEnd(staffIdx);
        }
    }
}

/* 000016B0-00001788       .text eventMesSetInit__9daNpcMt_cFi */
void daNpcMt_c::eventMesSetInit(int staffIdx) {
    int* pData = dComIfGp_evmng_getMyIntegerP(staffIdx, "MsgNo");
    if(pData) {
        mpMsgTbl = NULL;
        
        int msg = *pData;
        switch(msg){
            case 1:
                break;
            case 0:
                setMessage(getMsg());
                break;
            default:
                setMessage(msg);
        }

        if (mpMsgTbl != NULL) {
            setMessage(*mpMsgTbl);
        }
    }
    else {
        mpMsgTbl++;
        setMessage(*mpMsgTbl);
    }
}

/* 00001788-0000181C       .text eventMesSet__9daNpcMt_cFv */
bool daNpcMt_c::eventMesSet() {
    u16 temp = talk2(0);
    if (temp == fopMsgStts_BOX_CLOSED_e) {
        if(m749 & 1) {
            m749 &= ~1;
            mItemNo = 7;
            m744 = 3;
        }
        else if (m749 & 2) {
            m749 &= ~2;
            mItemNo = 5;
            m744 = 3;
        }
    }
    return temp == fopMsgStts_BOX_CLOSED_e;
}

/* 0000181C-00001874       .text eventGetItemInit__9daNpcMt_cFv */
void daNpcMt_c::eventGetItemInit() {
    fpc_ProcID itemID = fopAcM_createItemForPresentDemo(&current.pos, mItemNo, 0, -1, -1);
    if (itemID != fpcM_ERROR_PROCESS_ID_e) {
        dComIfGp_event_setItemPartnerId(itemID);
    }
}

/* 00001874-000019BC       .text talk2__9daNpcMt_cFi */
u16 daNpcMt_c::talk2(int i_param) {
    u16 status = 0xFF;
    if(mCurrMsgBsPcId == fpcM_ERROR_PROCESS_ID_e) {

        if(i_param == 1) {
            mCurrMsgNo = getMsg();
        }

        mCurrMsgBsPcId = fopMsgM_messageSet(mCurrMsgNo, this);
        mpCurrMsg = NULL;
        m734 = -1;
    }
    else if(mpCurrMsg) {
        status = mpCurrMsg->mStatus;
        switch(status) {
            case fopMsgStts_MSG_DISPLAYED_e:
                mpCurrMsg->mStatus = next_msgStatus(&mCurrMsgNo);
                
                if(mpCurrMsg->mStatus == fopMsgStts_MSG_CONTINUES_e) {
                    fopMsgM_messageSet(mCurrMsgNo);
                }
                break;

            case fopMsgStts_MSG_TYPING_e:
                if (m734 == fopMsgStts_MSG_CONTINUES_e) {
                    chkMsg();
                }
                break;
                
            case fopMsgStts_BOX_CLOSED_e:
                mpCurrMsg->mStatus = fopMsgStts_MSG_DESTROYED_e;
                mCurrMsgBsPcId = -1;
                break;
        }

        m734 = status;
        anmAtr(status);
    } else {
        mpCurrMsg = fopMsgM_SearchByID(mCurrMsgBsPcId);
    }
    return status;
}

/* 000019BC-00001A8C       .text next_msgStatus__9daNpcMt_cFPUl */
u16 daNpcMt_c::next_msgStatus(u32* pMsgNo) {
    u16 status = fopMsgStts_MSG_CONTINUES_e;
    if (mpMsgTbl) {
        mpMsgTbl++;
        switch(*mpMsgTbl) {
            case 2:
                dPb_erasePicture();
            case 0:
                mpMsgTbl = NULL;
                status = fopMsgStts_MSG_ENDS_e;
                break;
            case 1:
                *pMsgNo = l_msg_mt_room[dSnap_GetFigRoomId(dComIfGs_getEventReg(dSv_event_flag_c::UNK_A9FF))];
                break;
            default:
                *pMsgNo = *mpMsgTbl;
                break;
        }
    }
    else {
        status = fopMsgStts_MSG_ENDS_e;
    }

    return status;    
}

/* 00001A8C-00001FC8       .text getMsg__9daNpcMt_cFv */
u32 daNpcMt_c::getMsg() {
    u8 uVar2;
    
    u32 msgNo = 0;
    mpMsgTbl = NULL;
    if (g_dComIfG_gameInfo.play.getEvent()->chkPhoto()){
        uVar2 = changePhotoNo(dComIfGp_getPictureResult());
        if ((uVar2 <= 0x48) || (uVar2 >= 0xcf)) {
            uVar2 = 0xff;
        }
        else {
            uVar2 = dSnap_PhotoIndex2TableIndex(uVar2) & 0xff;
        }
        if (dComIfGp_getPictureFormat() == 0 || dComIfGp_getPictureFormat() == 1) {
            mpMsgTbl = l_msg_mt_no_color;
        }
        else if (uVar2 == 0xff) {
            mpMsgTbl = l_msg_mt_no_figure;
        }
        else if (isFigureGet(uVar2)) {
            mpMsgTbl = l_msg_mt_maked;
        }
        else if (dComIfGp_getPictureResultDetail() == 1) {
            mpMsgTbl = l_msg_mt_face_ng;
        }
        else if (dComIfGp_getPictureResultDetail() == 2) {
            mpMsgTbl = l_msg_mt_body_ng;
        }
        else {
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_2F01);
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_3401);
            dComIfGs_setEventReg(dSv_event_flag_c::UNK_A9FF, uVar2);
            s32 bVar1 = 0;
            if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_3A01)) {
                bVar1 = 1;
            }
            switch(uVar2) {
                case 0x5e:
                    mpMsgTbl = l_msg_mt_make_mt[bVar1];
                    break;
                case 0x5f:
                    mpMsgTbl = l_msg_mt_make_mn[bVar1];
                    break;
                default:
                    mpMsgTbl = l_msg_mt_make[bVar1];                
            }
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_4080)) {
                dComIfGs_offEventBit(dSv_event_flag_c::UNK_3080);
                dComIfGs_offEventBit(dSv_event_flag_c::UNK_4080);
                dComIfGs_offEventBit(dSv_event_flag_c::UNK_3F01);
                dComIfGs_offEventBit(dSv_event_flag_c::UNK_4040);
            }
        }
    }
    else if (dComIfGp_event_chkTalkXY()) {
            
    } else if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_3080)) {
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_4080) == 0) {
            if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_3A01)) {
                mpMsgTbl = l_msg_mt_1st_kansei;
            }
            else {
                mpMsgTbl = l_msg_mt_2nd_kansei;
            }

            u8 evReg = dComIfGs_getEventReg(dSv_event_flag_c::UNK_A9FF);
            setFigure(evReg);
    
            if (evReg == (u8)dSnap_PhotoIndex2TableIndex(0x4a)) {
                setFigure(dSnap_PhotoIndex2TableIndex(0x49));
            }
            else if (evReg == (u8)dSnap_PhotoIndex2TableIndex(0x72)) {
                setFigure(dSnap_PhotoIndex2TableIndex(0x73));
                setFigure(dSnap_PhotoIndex2TableIndex(0x74));
                setFigure(dSnap_PhotoIndex2TableIndex(0x75));
                setFigure(dSnap_PhotoIndex2TableIndex(0x76));
                setFigure(dSnap_PhotoIndex2TableIndex(0x77));
                setFigure(dSnap_PhotoIndex2TableIndex(0x78));
            }
#if VERSION > VERSION_DEMO
            else if (evReg == (u8)dSnap_PhotoIndex2TableIndex(0x8c)) {
                setFigure(dSnap_PhotoIndex2TableIndex(0x8d));
            }
            else if (evReg == (u8)dSnap_PhotoIndex2TableIndex(0x88)) {
                setFigure(dSnap_PhotoIndex2TableIndex(0x87));
            }
#endif
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_4080);
            dComIfGs_offEventBit(dSv_event_flag_c::UNK_2F01);
        }
        else if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_3F01)) {
            mpMsgTbl = l_msg_mt_gallery;
        }
        else if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_4040) == 0) {
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_4040);
            mpMsgTbl = l_msg_mt_room_in;
        }
        else {
            mpMsgTbl = l_msg_mt_kansei_end;
            dComIfGs_offEventBit(dSv_event_flag_c::UNK_3080);
            dComIfGs_offEventBit(dSv_event_flag_c::UNK_4080);
            dComIfGs_offEventBit(dSv_event_flag_c::UNK_3F01);
            dComIfGs_offEventBit(dSv_event_flag_c::UNK_4040);
            dComIfGs_onTmpBit(dSv_event_tmp_flag_c::UNK_0202);
        }
    }
    else if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2F01)) {
        mpMsgTbl = l_msg_mt_making;
    }
    else if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2F02)) {
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_2F02);
        mpMsgTbl = l_msg_mt_1st_talk;
    }
    else if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_3A01)) {
        mpMsgTbl = l_msg_mt_2nd_talk;
    }
    else if(!dComIfGs_isTmpBit(dSv_event_tmp_flag_c::UNK_0202)) {
        dComIfGs_onTmpBit(dSv_event_tmp_flag_c::UNK_0202);
        mpMsgTbl = l_msg_mt_3rd_talk; 
    }
    else {
        mpMsgTbl = l_msg_mt_4th_talk;
    }

    if (mpMsgTbl != NULL) {
        msgNo = *mpMsgTbl;
    }

    return msgNo;
}

/* 00001FC8-00001FCC       .text chkMsg__9daNpcMt_cFv */
void daNpcMt_c::chkMsg() {
    return;
}

/* 00001FCC-00001FD4       .text setMessage__9daNpcMt_cFUl */
void daNpcMt_c::setMessage(u32 msgNo) {
    mCurrMsgNo = msgNo;
}

/* 00001FD4-00002084       .text setAnmFromMsgTag__9daNpcMt_cFv */
void daNpcMt_c::setAnmFromMsgTag() {
    switch(dComIfGp_getMesgAnimeAttrInfo()) {
        case 0:
            setAnmTbl(l_npc_anm_wait);
            break;
        case 1:
            setAnmTbl(l_npc_anm_talk);
            break;
        case 2:
            setAnmTbl(l_npc_anm_talk2);
            break;
        case 3:
            setAnmTbl(l_npc_anm_talk3);
            break;
        case 4:
            setAnmTbl(l_npc_anm_talk4);
            break;
        case 5:
            setAnmTbl(l_npc_anm_talk5);
            break;
        case 6:
            setAnmTbl(l_npc_anm_tukuru);
        }
        dComIfGp_setMesgAnimeAttrInfo(0xff);
}

/* 00002084-000020A4       .text getPrmNpcNo__9daNpcMt_cFv */
u8 daNpcMt_c::getPrmNpcNo() {
    if(0 <= argument && argument < 1) {
        return argument;
    }
    return 0;
}

/* 000020A4-0000212C       .text setMtx__9daNpcMt_cFv */
void daNpcMt_c::setMtx() {
    mpMorf->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 0000212C-00002474       .text chkAttention__9daNpcMt_cFv */
void daNpcMt_c::chkAttention() {
    m752 = 0;

    if(mEventCut.getAttnFlag()) {
        mLookAtPos = mEventCut.getAttnPos();
        m74F = 1;
        if(m750 != 0) {
            m728 = false;
            m_jnt.setTrn();
        }
        else {
            m728 = true;
        }

        if(m743 == 0) {
            m743 = 1;
        }
    }
    else {
        fopAc_ac_c* player = dComIfGp_getLinkPlayer();

        f32 temp = m720;
        int temp2 = m730;
        f32 temp4;
        s16 temp5;

        dNpc_calc_DisXZ_AngY(current.pos, player->current.pos, &temp4, &temp5);
        
        if(m743 != 0) {
            temp += 40.0f;
            temp2 += 0x71C;
        }

        temp5 -= shape_angle.y;
        if(temp > temp4 && temp2 > abs(temp5)) {
            mLookAtPos = dNpc_playerEyePos(l_npc_dat[mNpcNo].field_0x14);
            m74F = 1;
            if(m750 != 0) {
                m728 = false;
            }
            else {
                m728 = true;
            }

            if(m751 == 0) {
                m740 = m732;
                m728 = false;
                m74F = 2;
                m_jnt.setTrn();
            }

            if (m743 == 0) {
                m743 = 1;
            }
        }
        else {
            if(m743 == 1) {
                m743 = 0;
                m72E = l_npc_dat[mNpcNo].field_0x48;
            }
            if(l_npc_dat[mNpcNo].field_0x24 > temp4 || m753 != 0){
                mLookAtPos = dNpc_playerEyePos(l_npc_dat[mNpcNo].field_0x14);
                m74F = 1;
                if (m750 != 0) {
                    m728 = 0;
                } else {
                    m728 = 1;
                }
                if (m751 == 0) {
                    m740 = m732;
                    m728 = 0;
                    m74F = 2;
                    m_jnt.setTrn();
                }
                m752 = 1;
            } else {
                m74F = 0;
                if(m6F0 == 0) {
                    if(m72E) {
                        m72E--;
                    }
                    else {
                        m740 = m732;
                        m728 = false;
                        m74F = 2;
                        m_jnt.setTrn();
                    }
                }
            }
        }
    }

    m73C = l_npc_dat[mNpcNo].field_0x2A;
}

/* 00002474-000025C0       .text lookBack__9daNpcMt_cFv */
void daNpcMt_c::lookBack() {
    short target = m73C;
    short desiredYRot = current.angle.y;
    cXyz* dstTemp = NULL;
    cXyz temp2;
    cXyz dstPos = eyePos;
    bool headOnlyFollow = m728;
    
    switch(m74F) {
        case 1:
            temp2 = mLookAtPos;
            dstTemp = &temp2;
            break;
        case 2:
            desiredYRot = m740;
            break;
        case 0:
        default:
            break;
    }
    
    if (m742 && m750) {
        headOnlyFollow = false;
        m_jnt.setTrn();
    }

    if (m_jnt.trnChk()) {
        if(mEventCut.getTurnSpeed() != 0) {
            target = mEventCut.getTurnSpeed();
        }
        cLib_addCalcAngleS2(&m73E, target, 4, 0x800);
    } else {
        m73E = 0;
    }
    
    m_jnt.lookAtTarget(&current.angle.y, dstTemp, dstPos, desiredYRot, m73E, headOnlyFollow);
    shape_angle = current.angle;
}

/* 000025C0-000026D8       .text initTexPatternAnm__9daNpcMt_cFb */
BOOL daNpcMt_c::initTexPatternAnm(bool i_modify) {
    J3DModelData *modelData = mpMorf->getModel()->getModelData();
    m_head_tex_pattern = (J3DAnmTexPattern*)dComIfG_getObjectIDRes(l_arcname_tbl[mNpcNo], l_btp_ix_tbl[mNpcNo]);
    JUT_ASSERT(DEMO_SELECT(2032, 2049), m_head_tex_pattern != NULL);
    
    if(!mBtpAnm.init(modelData, m_head_tex_pattern, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, i_modify, FALSE)) {
        return FALSE;
    }
    
    mFrame = 0;
    mTimer = 0;
    return TRUE;
}

/* 000026D8-00002744       .text playTexPatternAnm__9daNpcMt_cFv */
void daNpcMt_c::playTexPatternAnm() {
    if(cLib_calcTimer(&mTimer) == 0) {
        if(mFrame >= m_head_tex_pattern->getFrameMax()) {
            mFrame -= m_head_tex_pattern->getFrameMax();
            mTimer = 0x78;
        }
        else {
            mFrame++;
        }
    }
}

/* 00002744-0000280C       .text playAnm__9daNpcMt_cFv */
void daNpcMt_c::playAnm() {
    mAnmFlag &= ~1;
    if(mpMorf->play(0, 0, 0)) {
        if(mpAnmDat) {
            if(m74C > 0) {
                m74C--;
                if(m74C == 0) {
                    mpAnmDat++;
                    if(setAnmTbl(mpAnmDat)) {
                        mAnmFlag |= 1;
                    }
                }
                else {
                    setAnm(mpAnmDat->field_0x00, 0, 0.0f);
                }
            }
        }
    }
}

/* 0000280C-000028E4       .text setAnm__9daNpcMt_cFUcif */
void daNpcMt_c::setAnm(u8 param_1, int param_2, f32 morf) {
    if (m71C >= 0.0f) {
        morf = m71C;
        m71C = -1.0f;
    }

    mpMorf->setAnm(
        (J3DAnmTransformKey*)dComIfG_getObjectIDRes(l_arcname_tbl[mNpcNo], l_bck_ix_tbl[param_1]),
        param_2, morf, 1.0f, 0.0f, -1.0f, NULL
    );
    m74A = param_1;
}

/* 000028E4-00002984       .text setAnmTbl__9daNpcMt_cFP9sMtAnmDat */
bool daNpcMt_c::setAnmTbl(sMtAnmDat* anmDat) {
    if (anmDat->field_0x00 == 0xFF) {
        mpAnmDat = NULL;
        return true;
    }
    else {
        mpAnmDat = anmDat;
        m74C = mpAnmDat->field_0x02;

        int temp = 2;
        if (m74C > 0) {
            temp = 0;
        }

        if (m74A != mpAnmDat->field_0x00 || temp == 0) {
            setAnm(mpAnmDat->field_0x00, temp, mpAnmDat->field_0x01);
        }
        return false;
    }
}

/* 00002984-00002A28       .text XyCheckCB__9daNpcMt_cFi */
s16 daNpcMt_c::XyCheckCB(int i_itemBtn) { 
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2F02) && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_2F01)) {
        u8 itemNo = dComIfGp_getSelectItem(i_itemBtn);
        if(itemNo == dItemNo_PICTO_BOX_e || itemNo == dItemNo_DELUXE_PICTO_BOX_e){
            if(dComIfGs_getPictureNum()){
                return true;
            }
        }
    }
    return false;
}

/* 00002A28-00002AA0       .text setCollision__9daNpcMt_cFP8dCcD_Cyl4cXyzff */
void daNpcMt_c::setCollision(dCcD_Cyl* cyl, cXyz center, f32 radius, f32 height) {
    cyl->SetC(center);
    cyl->SetR(radius);
    cyl->SetH(height);
    dComIfG_Ccsp()->Set(cyl);
}

/* 00002AA0-00002AFC       .text chkEndEvent__9daNpcMt_cFv */
BOOL daNpcMt_c::chkEndEvent() {
    if (dComIfGp_evmng_endCheck(mMtGetItemEventIdx)) {
        g_dComIfG_gameInfo.play.getEvent()->onEventFlag(8);
        return TRUE;
    }
    return FALSE;
}

/* 00002AFC-00002B98       .text isFigureGet__9daNpcMt_cFUc */
u8 daNpcMt_c::isFigureGet(u8 figureNo) {
    if(figureNo >= TOTAL_FIGURE_COUNT){
        return false;
    }
    
    if(figureNo / 8 < 0x11) {
        int r31 = (figureNo % 8);
        u8 reg = dComIfGs_getEventReg(l_figure_comp[figureNo / 8]);
        u32 ret = reg & (1 << r31);
        return ret;
    }
    return false;
}

/* 00002B98-00002C38       .text setFigure__9daNpcMt_cFUc */
void daNpcMt_c::setFigure(u8 figure) {
    if(figure < TOTAL_FIGURE_COUNT) {
        u32 r28 = figure % 8;
        u8 reg = dComIfGs_getEventReg(l_figure_comp[figure / 8]);
        reg |= 1 << r28;
        dComIfGs_setEventReg(l_figure_comp[figure / 8], reg);
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_3A01);
    }
}

/* 00002C38-00002CA0       .text getFigureMakeNum__9daNpcMt_cFv */
int daNpcMt_c::getFigureMakeNum() {
    int num = 0;

    for(u8 i = 0; i < TOTAL_FIGURE_COUNT; i++) {
        if(isFigureGet(i)) {
            num++;
        }
    }

    return num;
}

/* 00002CA0-00002D08       .text isComp__9daNpcMt_cFv */
BOOL daNpcMt_c::isComp() {
    int ownedNum = getFigureMakeNum();
    int totalNum = 0x84;
    if(isFigureGet(0x32)) {
        totalNum = 0x85;
    }

    if(ownedNum >= totalNum) {
        return true;
    }

    return false;
}

/* 00002D08-00002D4C       .text changePhotoNo__9daNpcMt_cFUc */
u8 daNpcMt_c::changePhotoNo(u8 photoNo) {
    switch(photoNo) {
        case 2:
            photoNo = 0x69;
            break;
        case 4:
            photoNo = 0x67;
            break;
        case 6:
            photoNo = 0x6d;
    }
    return photoNo;
}

/* 00002D4C-00002D6C       .text daNpc_MtCreate__FPv */
static cPhs_State daNpc_MtCreate(void* i_this) {
    return ((daNpcMt_c*)i_this)->_create();
}

/* 00002D6C-00002D90       .text daNpc_MtDelete__FPv */
static BOOL daNpc_MtDelete(void* i_this) {
    return ((daNpcMt_c*)i_this)->_delete();
}

/* 00002D90-00002DB4       .text daNpc_MtExecute__FPv */
static BOOL daNpc_MtExecute(void* i_this) {
    return ((daNpcMt_c*)i_this)->_execute();
}

/* 00002DB4-00002DD8       .text daNpc_MtDraw__FPv */
static BOOL daNpc_MtDraw(void* i_this) {
    return ((daNpcMt_c*)i_this)->_draw();
}

/* 00002DD8-00002DE0       .text daNpc_MtIsDelete__FPv */
static BOOL daNpc_MtIsDelete(void*) {
    return TRUE;
}

static actor_method_class daNpc_MtMethodTable = {
    (process_method_func)daNpc_MtCreate,
    (process_method_func)daNpc_MtDelete,
    (process_method_func)daNpc_MtExecute,
    (process_method_func)daNpc_MtIsDelete,
    (process_method_func)daNpc_MtDraw,
};

actor_process_profile_definition g_profile_NPC_MT = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_MT_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpcMt_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_MT_e,
    /* Actor SubMtd */ &daNpc_MtMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
