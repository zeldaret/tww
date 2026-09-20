/**
 * d_a_npc_mn.cpp
 * NPC - Manny
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_mn.h"
#include "d/actor/d_a_obj_figure.h"
#include "d/actor/d_a_obj_ohatch.h"
#include "d/d_a_obj.h"
#include "d/d_com_lib_game.h"
#include "d/d_snap.h"
#include "d/d_scope.h"
#include "res/Object/Mn.h"
#include "SSystem/SComponent/c_phase.h"

const char daNpcMn_c::m_arcname[] = "Mn";

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

static sMnAnmDat l_npc_anm_wait = { daNpcMn_c::BCK_WAIT01, 0x08, 0xFF };

static sMnAnmDat l_npc_anm_wait2 = { daNpcMn_c::BCK_WAIT02, 0x08, 0xFF };

static sMnAnmDat l_npc_anm_talk = {
    daNpcMn_c::BCK_TALK01,
    0x08,
    0xFF,
};

static sMnAnmDat l_npc_anm_talk2 = {
    daNpcMn_c::BCK_TALK02,
    0x08,
    0xFF,
};

static sMnAnmDat l_npc_anm_walk = {
    daNpcMn_c::BCK_WALK,
    0x08,
    0xFF,
};

static sMnAnmDat l_npc_anm_bikkuri[] = {
    {
        daNpcMn_c::BCK_BIKKURI,
        0x08,
        0x01,
    },
    {
        daNpcMn_c::BCK_WAIT01,
        0x08,
        0xFF,
    },
};

static sMnAnmDat l_npc_anm_jump1[] = {
    {
        daNpcMn_c::BCK_JUMP01,
        0x08,
        0x01,
    },
    {
        daNpcMn_c::BCK_NULL,
        0x08,
        0x00,
    },
};

static sMnAnmDat l_npc_anm_jump2 = {
    daNpcMn_c::BCK_JUMP02,
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

/* 00000078-00000230       .text __ct__9daNpcMn_cFv */
daNpcMn_c::daNpcMn_c() {
    mResFlag = 0;
    mMoveState = MOVE_PROC_WAIT;
    mTargetSpeedF = 0.0f;
    mWaitTimer = 0;
    mAnmMorfOverride = -1.0f;
    mLookMode = LOOK_MODE_NONE;
    mHeadOnlyFollow = true;
    mHomeYRot = home.angle.y;
    mBckIdx = BCK_WAIT01;
    mEtcFlag = 0;
    mPosFlag = chkPosNo();
    mNpcNo = getPrmNpcNo();
}

/* 000005E0-000006F8       .text daNpc_Mn_nodeCallBack__FP7J3DNodei */
static BOOL daNpc_Mn_nodeCallBack(J3DNode* i_node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daNpcMn_c* i_this = (daNpcMn_c*)model->getUserArea();
        J3DJoint* joint = (J3DJoint*)i_node;

        u16 jointNo = joint->getJntNo();
        MTXCopy(model->getAnmMtx(jointNo), *calc_mtx);

        if (jointNo == i_this->m_jnt.getHeadJntNum()) {
            cMtx_XrotM(*calc_mtx, (s16)i_this->m_jnt.getHead_y());
            cMtx_ZrotM(*calc_mtx, (s16)-i_this->m_jnt.getHead_x());
        }

        if (jointNo == i_this->m_jnt.getBackboneJntNum()) {
            cMtx_XrotM(*calc_mtx, (s16)i_this->m_jnt.getBackbone_y());
            cMtx_ZrotM(*calc_mtx, (s16)-i_this->m_jnt.getBackbone_x());
        }
        Mtx* src = calc_mtx;
        MTXCopy(*src, model->getAnmMtx(jointNo));
        MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
    }
    return TRUE;
}

/* 000006F8-00000718       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpcMn_c*)i_this)->createHeap();
}

/* 00000718-0000085C       .text phase_1__FP9daNpcMn_c */
static cPhs_State phase_1(daNpcMn_c* i_this) {
    fopAcM_ct(i_this, daNpcMn_c);

    switch (i_this->mPosFlag) {
        case 0:
            dComIfGs_setEventReg(dSv_event_flag_c::UNK_870F, 0);
            if (fopAcM_isSwitch(i_this, i_this->getPrmSwitchBit())) {
                return cPhs_STOP_e;
            }
            break;
        default:
            u8 eventReg = dComIfGs_getEventReg(dSv_event_flag_c::UNK_870F);
            if (i_this->isChangePos(eventReg)) {
                if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_3A01)) {
                    eventReg = i_this->getPosNo();
                } else {
                    eventReg = 1;
                }
                dComIfGs_setEventReg(dSv_event_flag_c::UNK_870F, eventReg);
            }
            u8 posFlag = i_this->mPosFlag;
            if (eventReg != posFlag) {
                return cPhs_STOP_e;
            }
    }
    i_this->setResFlag(1);
    return cPhs_NEXT_e;
}

/* 0000085C-000008D4       .text phase_2__FP9daNpcMn_c */
static cPhs_State phase_2(daNpcMn_c* i_this) {
    cPhs_State state = dComIfG_resLoad(i_this->getPhaseP(), l_arcname_tbl[0]);

    if(state == cPhs_COMPLEATE_e) {
        if(fopAcM_entrySolidHeap(i_this, CheckCreateHeap, 0)){
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
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectIDRes(l_arcname_tbl[0], l_bmd_ix_tbl[0]);
    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL,
        NULL,
        (J3DAnmTransform*)dComIfG_getObjectIDRes(l_arcname_tbl[0], l_bck_ix_tbl[mBckIdx]),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0x80000,
        0x15021222
    );

    m_jnt.setHeadJntNum(modelData->getJointTree().getJointName()->getIndex("head"));
    JUT_ASSERT(DEMO_SELECT(0x3E3, 0x3E4), m_jnt.getHeadJntNum() >= 0);
    m_jnt.setBackboneJntNum(modelData->getJointTree().getJointName()->getIndex("backbone"));
    JUT_ASSERT(DEMO_SELECT(0x3E7, 0x3E8), m_jnt.getBackboneJntNum() >= 0);

    if (initTexPatternAnm(false) == FALSE) {
        return FALSE;
    }

    for (u16 jntIdx = 0; jntIdx < modelData->getJointNum(); jntIdx++) {
        if (jntIdx == m_jnt.getHeadJntNum() || jntIdx == m_jnt.getBackboneJntNum()) {
            modelData->getJointTree().getJointNodePointer(jntIdx)->setCallBack(daNpc_Mn_nodeCallBack);
        }
    }
    mpMorf->getModel()->setUserArea((u32)this);
    mAcchCir.SetWall(30.0f, 30.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this),
        fopAcM_GetOldPosition_p(this),
        this,
        1,
        &mAcchCir,
        fopAcM_GetSpeed_p(this),
        fopAcM_GetAngle_p(this),
        fopAcM_GetShapeAngle_p(this)
    );

    J3DModelData* etc_modelData = (J3DModelData*)dComIfG_getObjectIDRes(l_arcname_tbl[0], l_etc_bmd_ix_tbl[0]);
    mpModel = mDoExt_J3DModel__create(etc_modelData, 0x80000, 0x11000002);
    if (mpModel == NULL) {
        return FALSE;
    }
    mShoulderRJoint = modelData->getJointTree().getJointName()->getIndex("shoulderR");
    return TRUE;
}

/* 00000BE0-00000C00       .text daNpcMn_XyCheckCB__FPvi */
static s16 daNpcMn_XyCheckCB(void* i_this, int i_itemBtn) {
    return static_cast<daNpcMn_c*>(i_this)->XyCheckCB(i_itemBtn);
}

/* 00000C00-00000F3C       .text createInit__9daNpcMn_cFv */
cPhs_State daNpcMn_c::createInit() {
    int weight = 0xFF;
    u8 railID = getPrmRailID();
    if (railID != 0xFF) {
        mPathRun.setInf(railID, fopAcM_GetRoomNo(this), true);
        if (mPathRun.getPath() == NULL) {
            return cPhs_ERROR_e;
        }
        dPath_GetNextRoomPath(mPathRun.getPath(), -1);
        fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);

        u8 currPointIdx = 0;
        while (currPointIdx < mPathRun.maxPoint()) {
            if (mPathRun.getPath()->m_points[currPointIdx].mArg0 == 0) {
                break;
            }
            currPointIdx++;
        }
        if (currPointIdx == mPathRun.maxPoint()) {
            currPointIdx = 0;
        }
        mPathRun.setIdx(currPointIdx);
        old.pos = mPathRun.getPoint(currPointIdx);
        current.pos = old.pos;
        mPathRun.incIdxLoop();
        mWaitTimer = 1;
        weight = 0xFE;
    }

#if VERSION == VERSION_DEMO
    mStts.Init(weight, 0xFF, this);
    mCyl.Set(dNpc_cyl_src);
    mCyl.SetStts(&mStts);
    setCollision(&mCyl, current.pos, l_npc_dat[mNpcNo].mCylRadius, 150.0f);
#endif
    fopAcM_SetGravity(this, -9.0f);
    setAnmTbl(&l_npc_anm_wait);
    mHatchEventIdx = dComIfGp_evmng_getEventIdx("FIGURE_HATCH_OPEN");
    eventInfo.setXyCheckCB(daNpcMn_XyCheckCB);
    mEventCut.setActorInfo2(l_npc_staff_id[0], this);
    mTurnVel = 0;
    mTalkOrder = 0;
    mbPlayerAttention = 0;
    mbNearPlayer = 0;
    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -70.0f, 0.0f, -70.0f, 70.0f, 200.0f, 70.0f);
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xAA;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xAA;
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
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
    mbAllowBodyTurn = l_npc_dat[mNpcNo].mbAllowBodyTurn;
    mbLookOnly = l_npc_dat[mNpcNo].mbLookOnly;
    mAttnDist = l_npc_dat[mNpcNo].mAttnDist;
    mAttnAngle = l_npc_dat[mNpcNo].mAttnAngle;

    mObjAcch.CrrPos(*dComIfG_Bgsp());
#if VERSION == VERSION_DEMO
    current.pos.y = home.pos.y = mObjAcch.GetGroundH();
    setMtx();
#else
    if (-G_CM3D_F_INF != mObjAcch.GetGroundH()) {
        current.pos.y = home.pos.y = mObjAcch.GetGroundH();
    }

    setMtx();
    mpMorf->getModel()->calc();
    mStts.Init(weight, 0xFF, this);
    mCyl.Set(dNpc_cyl_src);
    mCyl.SetStts(&mStts);
    setCollision(&mCyl, current.pos, l_npc_dat[mNpcNo].mCylRadius, 150.0f);
#endif
    return cPhs_COMPLEATE_e;
}

/* 00000F3C-00000FE4       .text _delete__9daNpcMn_cFv */
bool daNpcMn_c::_delete() {
#if VERSION == VERSION_DEMO
    if (mResFlag != 0) {
        dComIfG_resDeleteDemo(&mPhs, l_arcname_tbl[0]);
    }
    if (mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }
#else
    dComIfG_resDeleteDemo(&mPhs, l_arcname_tbl[0]);
    if (heap != NULL && mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }
#endif

    if (dComIfGp_isEnableNextStage() && strcmp(dComIfGp_getNextStageName(), "sea") == 0) {
        dComIfGs_setEventReg(dSv_event_flag_c::UNK_870F, 0);
    }
    return TRUE;
}

/* 00000FE4-00001154       .text _draw__9daNpcMn_cFv */
bool daNpcMn_c::_draw() {
    if (dComIfGs_isTmpBit(dSv_event_tmp_flag_c::UNK_0408)) {
        return TRUE;
    }

    J3DModel* morfModel = mpMorf->getModel();
    J3DModelData* morfModelData = morfModel->getModelData();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(morfModel, &tevStr);
    mBtpAnm.entry(morfModelData, mBtpFrame);
    mpMorf->updateDL();
    mBtpAnm.remove(morfModelData);

    J3DModelData* _ = mpModel->getModelData();
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mpModel->setBaseTRMtx(morfModel->getAnmMtx(mShoulderRJoint));
    mDoExt_modelUpdateDL(mpModel);

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
    dSnap_RegistFig(DSNAP_TYPE_NPC_MN, this, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

typedef int(daNpcMn_c::*ExecuteInit_t)();
static ExecuteInit_t l_execute_init[] = {
    &daNpcMn_c::executeWaitInit,
    &daNpcMn_c::executeTalkInit,
    &daNpcMn_c::executeWalkInit,
    &daNpcMn_c::executeTurnInit,
    &daNpcMn_c::executeTalk3Init,
};

typedef void(daNpcMn_c::*MoveProc_t)();
static MoveProc_t moveProc[]={
    &daNpcMn_c::executeWait,
    &daNpcMn_c::executeTalk,
    &daNpcMn_c::executeWalk,
    &daNpcMn_c::executeTurn,
    &daNpcMn_c::executeTalk3,
};

/* 00001154-00001344       .text _execute__9daNpcMn_cFv */
bool daNpcMn_c::_execute() {
    chkAttention();
    checkOrder();

    if (!dComIfGp_event_runCheck() || eventInfo.checkCommandTalk() || mTalk3State != TALK3_INIT) {
        (this->*moveProc[mMoveState])();
    } else {
        eventMove();
    }

    eventOrder();
    playTexPatternAnm();
    playAnm();

    if (mBckIdx == BCK_WALK) {
        cLib_chaseF(&speedF, mTargetSpeedF, 0.3f);
        f32 speed = speedF * l_npc_dat[mNpcNo].mWalkAnmRate;
        if (speed < 0.5f) {
            speed = 0.5f;
        }
        mpMorf->setPlaySpeed(speed);
    } else {
        cLib_chaseF(&speedF, mTargetSpeedF, 0.1f);
    }

    fopAcM_posMoveF(this, mStts.GetCCMoveP());

    mObjAcch.CrrPos(*dComIfG_Bgsp());

    setCollision(&mCyl, current.pos, l_npc_dat[mNpcNo].mCylRadius, 150.0f);
    attention_info.position.set(current.pos.x, current.pos.y + l_npc_dat[mNpcNo].mAttnPosOfsY, current.pos.z);
    eyePos.set(current.pos.x, current.pos.y + l_npc_dat[mNpcNo].mEyePosOfsY, current.pos.z);

    lookBack();
    setMtx();
    return false;
}

/* 00001344-000013B4       .text executeCommon__9daNpcMn_cFv */
u8 daNpcMn_c::executeCommon() {
    if (mbPlayerAttention) {
        mEvtOrderType = true;
    } else {
        mEvtOrderType = false;
    }

    if (mTalkOrder == 1 && mMoveState != MOVE_PROC_TALK) {
        executeSetMode(MOVE_PROC_TALK);
    }
    return mTalkOrder;
}

/* 000013B4-0000140C       .text executeSetMode__9daNpcMn_cFUc */
void daNpcMn_c::executeSetMode(u8 i_initIdx) {
    mTargetSpeedF = 0.0f;
    fopAcM_SetSpeedF(this, 0.0f);
    mMoveState = (this->*l_execute_init[i_initIdx])();
}

/* 0000140C-00001518       .text executeWaitInit__9daNpcMn_cFv */
int daNpcMn_c::executeWaitInit() {
    fopAcM_SetSpeedF(this, 0.0f);
    if (mbLookFigure) {
        setAnmTbl(&l_npc_anm_wait2);
        mWaitTimer = cM_rndF(30.0f) + 150.0f;
    } else {
        setAnmTbl(&l_npc_anm_wait);
        mWaitTimer = l_npc_dat[mNpcNo].mWaitTimerMin + cM_rndF(l_npc_dat[mNpcNo].mWaitTimerMax - l_npc_dat[mNpcNo].mWaitTimerMin);
    }
    return MOVE_PROC_WAIT;
}

/* 00001518-000017CC       .text executeWait__9daNpcMn_cFv */
void daNpcMn_c::executeWait() {
    if (!executeCommon()) {
        if (mPosFlag == 0) {
            if (dComIfGp_checkPlayerStatus0(0, daPyStts0_TELESCOPE_LOOK_e)) {
                mAttnDist = (s16)(l_npc_dat[mNpcNo].mAttnDist * 2.0f);
            } else {
                mAttnDist = l_npc_dat[mNpcNo].mAttnDist;
                mEtcFlag &= 0xFFFE;
            }
            if (mbPlayerAttention && dComIfGs_isEventBit(dSv_event_flag_c::UNK_2F08) && dComIfGp_checkPlayerStatus0(0, daPyStts0_TELESCOPE_LOOK_e)) {
                dComIfGp_setScopeType(dScpTyp_PICTO_BOX_e);
                if (dComIfGp_getMesgStatus() == fopMsgStts_SCOPE_ACTIVE_e && !(mEtcFlag & 1)) {
                    mEtcFlag |= 1;
                    executeSetMode(MOVE_PROC_TALK3);
                }
            }

            if (!(mSwitchFlag & 1) && fopAcM_isSwitch(this, getPrmSwitchBit())) {
                fopAcM_onSwitch(this, getPrmSwitchBit());
                mSwitchFlag |= 1;
                mbAllowBodyTurn = 0;
                mbLookOnly = 0;
                mEvtOrderType = 3;
            }
        } else if (mbLookFigure) {
            if (mWaitTimer == 0) {
                mbLookFigure = 0;
                executeSetMode(MOVE_PROC_TURN);
            } else {
                mWaitTimer--;
                daObjFigure_c* figure = (daObjFigure_c*)fopAcM_searchFromName("Figure", 0xFF, mFigureArg);
                if (figure != NULL && figure->mbDisplay) {
                    mLookAtPos = figure->eyePos;
                    mLookMode = LOOK_MODE_ATTN;
                    mHeadOnlyFollow = false;
                    m_jnt.setTrn();
                }
            }
        } else {
            if (mPathRun.isPath() && mWaitTimer && !mbPlayerAttention && !mbNearPlayer) {
                mWaitTimer--;
                if (!mWaitTimer) {
                    mbLookFigure = 0;
                    executeSetMode(MOVE_PROC_TURN);
                }
            }
        }
    }
}

/* 000017CC-000017D4       .text executeTalkInit__9daNpcMn_cFv */
int daNpcMn_c::executeTalkInit() {
    return MOVE_PROC_TALK;
}

/* 000017D4-0000184C       .text executeTalk__9daNpcMn_cFv */
void daNpcMn_c::executeTalk() {
    executeCommon();
    if (talk2(1) == 0x12) {
        mTalkOrder = 0;
        executeSetMode(MOVE_PROC_WAIT);
        dComIfGp_event_onEventFlag(8);
    } else {
        setAnmFromMsgTag();
    }
}

/* 0000184C-0000185C       .text executeTalk3Init__9daNpcMn_cFv */
int daNpcMn_c::executeTalk3Init() {
    mTalk3State = TALK3_INIT;
    return MOVE_PROC_TALK3;
}

/* 0000185C-0000191C       .text executeTalk3__9daNpcMn_cFv */
void daNpcMn_c::executeTalk3() {
    switch (mTalk3State) {
        case TALK3_INIT:
        case TALK3_ORDER:
            if (eventInfo.checkCommandDemoAccrpt()) {
                mTalk3State = TALK3_TALK;
            } else {
                fopAcM_orderPotentialEvent(this, dEvtFlag_STAFF_ALL_e | dEvtFlag_UNK8_e, 0, 0);
                eventInfo.onCondition(dEvtCnd_UNK2_e);
                mTalk3State = TALK3_ORDER;
            }
            break;
        case TALK3_TALK:
            if (talk3(1) == 0x12) {
                mTalk3State = TALK3_INIT;
                executeSetMode(MOVE_PROC_WAIT);
                dComIfGp_event_onEventFlag(8);
            }
            break;
    }
}

/* 0000191C-00001948       .text executeWalkInit__9daNpcMn_cFv */
int daNpcMn_c::executeWalkInit() {
    setAnmTbl(&l_npc_anm_walk);
    return MOVE_PROC_WALK;
}

/* 00001948-00001BD4       .text executeWalk__9daNpcMn_cFv */
void daNpcMn_c::executeWalk() {
    if (!executeCommon()) {
        bool reachedEnd = false;
        if (mPathRun.chkPointPass(current.pos, mPathRun.getDir())) {
            mFigureArg = mPathRun.pointArg(mPathRun.getIdx());
            if (mFigureArg != 0xFF) {
                daObjFigure_c* figure = (daObjFigure_c*)fopAcM_searchFromName("Figure", 0xFF, mFigureArg);
                if (figure != NULL && figure->isDispFigure()) {
                    mFigureMsgIdx = getRand(5);
                    mbLookFigure = 1;
                    executeSetMode(MOVE_PROC_WAIT);
                }
            }
            if (!mPathRun.nextIdxAuto()) {
                reachedEnd = true;
            }
        }

        if (mbPlayerAttention || mbNearPlayer) {
            mbLookFigure = 0;
            executeSetMode(MOVE_PROC_WAIT);
        } else {
            if (!reachedEnd) {
                if (mbLookFigure != 0) {
                    return;
                }
                cXyz point = mPathRun.getPoint(mPathRun.getIdx());
                s16 angle;
                dNpc_calc_DisXZ_AngY(current.pos, point, NULL, &angle);
                mTargetYRot = mHomeYRot = angle;
                mHeadOnlyFollow = false;
                mLookAtMaxVel = l_npc_dat[mNpcNo].mWalkLookAtMaxVel;
                mLookMode = LOOK_MODE_TURN;
                m_jnt.setTrn();
                mTargetSpeedF = l_npc_dat[mNpcNo].mWalkSpeed;
            } else {
                mPathRun.turnDir();
                cXyz point = mPathRun.getPoint(mPathRun.getIdx());
                s16 angle;
                dNpc_calc_DisXZ_AngY(current.pos, point, NULL, &angle);
                mHomeYRot = angle;
                mPathRun.setInf(0xFF, fopAcM_GetRoomNo(this), true);
                executeSetMode(MOVE_PROC_WAIT);
                return;
            }
        }
    }
}

/* 00001BD4-00001D18       .text executeTurnInit__9daNpcMn_cFv */
int daNpcMn_c::executeTurnInit() {
    cXyz point = mPathRun.getPoint(mPathRun.getIdx());
    s16 angle;
    dNpc_calc_DisXZ_AngY(current.pos, point, NULL, &angle);
    if (angle == current.angle.y) {
        setAnmTbl(&l_npc_anm_walk);
        mWaitTimer = l_npc_dat[mNpcNo].mTurnWaitMin + cM_rndF(l_npc_dat[mNpcNo].mTurnWaitMax - l_npc_dat[mNpcNo].mTurnWaitMin);
        return MOVE_PROC_WALK;
    } else {
        return MOVE_PROC_TURN;
    }
}

/* 00001D18-00001DE8       .text executeTurn__9daNpcMn_cFv */
void daNpcMn_c::executeTurn() {
    if (!executeCommon()) {
        cXyz point = mPathRun.getPoint(mPathRun.getIdx());
        s16 angle;
        dNpc_calc_DisXZ_AngY(current.pos, point, NULL, &angle);
        mTargetYRot = angle;
        mHeadOnlyFollow = false;
        mLookMode = LOOK_MODE_TURN;
        m_jnt.setTrn();

        if (current.angle.y == angle) {
            executeSetMode(MOVE_PROC_WALK);
        }
    }
}

/* 00001DE8-00001E80       .text checkOrder__9daNpcMn_cFv */
void daNpcMn_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (dComIfGp_evmng_startCheck(mHatchEventIdx) && mEvtOrderType == 3) {
            mEvtOrderType = 0;
        }
    } else if (eventInfo.checkCommandTalk() && (mEvtOrderType == 2 || mEvtOrderType == 1)) {
        mTalkOrder = 1;
        executeSetMode(MOVE_PROC_TALK);
    }
}

/* 00001E80-00001F00       .text eventOrder__9daNpcMn_cFv */
void daNpcMn_c::eventOrder() {
    if (mEvtOrderType == 2 || mEvtOrderType == 1) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (mEvtOrderType == 2) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (mEvtOrderType == 3) {
        fopAcM_orderChangeEventId(dComIfGp_getPlayer(0), this, mHatchEventIdx, 0, 0xFFFF);
    }
}

/* 00001F00-00001F74       .text eventMove__9daNpcMn_cFv */
void daNpcMn_c::eventMove() {
    if (!chkEndEvent()) {
        bool attn = mEventCut.getAttnFlag();
        if (mEventCut.cutProc()) {
            if (!mEventCut.getAttnFlag()) {
                mEventCut.setAttnFlag(attn);
            }
        } else {
            privateCut();
            setAnmFromMsgTag();
        }
    }
}

/* 00001F74-00002194       .text privateCut__9daNpcMn_cFv */
void daNpcMn_c::privateCut() {
    static char* cut_name_tbl[] = {
        "MES_SET", "GET_ITEM", "WAIT", "HATCH", "BIKKURI", "TURN", "WALK", "LOOK", "JUMP", "SWON",
    };
    int staffIdx = dComIfGp_evmng_getMyStaffId(l_npc_staff_id[0]);
    if (staffIdx != -1) {
        mActIdx = dComIfGp_evmng_getMyActIdx(staffIdx, cut_name_tbl, 10, TRUE, 0);
        if (mActIdx == -1) {
            dComIfGp_evmng_cutEnd(staffIdx);
        } else {
            if (dComIfGp_evmng_getIsAddvance(staffIdx)) {
                switch (mActIdx) {
                    case 0:
                        eventMesSetInit(staffIdx);
                        break;
                    case 1:
                        eventGetItemInit();
                        break;
                    case 2:
                        eventWaitInit(staffIdx);
                        break;
                    case 3:
                        eventHatchInit();
                        break;
                    case 4:
                        eventBikkuriInit(staffIdx);
                        break;
                    case 5:
                        eventTurnInit();
                        break;
                    case 6:
                        eventWalkInit();
                        break;
                    case 7:
                        eventLookInit();
                        break;
                    case 8:
                        eventJumpInit(staffIdx);
                        break;
                    case 9:
                        eventSwOnInit(staffIdx);
                        break;
                }
            }
            bool shouldEnd;
            switch (mActIdx) {
                case 0:
                    shouldEnd = eventMesSet();
                    break;
                case 2:
                    shouldEnd = eventWait(staffIdx);
                    break;
                case 3:
                    shouldEnd = eventHatch();
                    break;
                case 4:
                    shouldEnd = eventBikkuri();
                    break;
                case 5:
                    shouldEnd = eventTurn(staffIdx);
                    break;
                case 6:
                    shouldEnd = eventWalk();
                    break;
                case 7:
                    shouldEnd = eventLook();
                    break;
                case 8:
                    shouldEnd = eventJump();
                    break;
                case 9:
                    shouldEnd = eventSwOn();
                    break;
                default:
                    shouldEnd = true;
                    break;
            }
            if (shouldEnd) {
                dComIfGp_evmng_cutEnd(staffIdx);
            }
        }
    }
}

/* 00002194-0000226C       .text eventMesSetInit__9daNpcMn_cFi */
void daNpcMn_c::eventMesSetInit(int i_staffIdx) {
    int* pData = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "MsgNo");
    if (pData != NULL) {
        mpMsgNo = NULL;
        int msg = *pData;
        switch (msg) {
            case 1:
                break;
            case 0:
                msg = getMsg();
                setMessage(msg);
                break;
            default:
                setMessage(msg);
        }
        if (mpMsgNo != NULL) {
            setMessage(*mpMsgNo);
        }
    } else {
        mpMsgNo++;
        setMessage(*mpMsgNo);
    }
}

/* 0000226C-000022A0       .text eventMesSet__9daNpcMn_cFv */
bool daNpcMn_c::eventMesSet() {
    return talk2(0) == fopMsgStts_BOX_CLOSED_e;
}

/* 000022A0-000022F8       .text eventGetItemInit__9daNpcMn_cFv */
void daNpcMn_c::eventGetItemInit() {
    fpc_ProcID procItem = fopAcM_createItemForPresentDemo(&current.pos, mItemNo);
    if(procItem != fpcM_ERROR_PROCESS_ID_e){
        dComIfGp_event_setItemPartnerId(procItem);
    }
}

/* 000022F8-00002358       .text eventWaitInit__9daNpcMn_cFi */
void daNpcMn_c::eventWaitInit(int i_staffIdx) {
    int* timer = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "Timer");
    mEventTimer = 0;
    if (timer != NULL) {
        mEventTimer = *timer;
    }
}

/* 00002358-000023E8       .text eventWait__9daNpcMn_cFi */
bool daNpcMn_c::eventWait(int i_staffIdx) {
    if (mEventTimer != 0) {
        mEventTimer--;
        return false;
    }
    if (dComIfGp_evmng_getMyIntegerP(i_staffIdx, "SwOn") != NULL) {
        fopAcM_onSwitch(this, getPrmSwitchBit2());
    }
    return true;
}

/* 000023E8-00002448       .text eventSwOnInit__9daNpcMn_cFi */
void daNpcMn_c::eventSwOnInit(int i_staffIdx) {
    int* timer = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "Timer");
    mEventTimer = 0;
    if (timer != NULL) {
        mEventTimer = *timer;
    }
}

/* 00002448-000024AC       .text eventSwOn__9daNpcMn_cFv */
bool daNpcMn_c::eventSwOn() {
    if (mEventTimer) {
        mEventTimer--;
        return false;
    }
    fopAcM_onSwitch(this, getPrmSwitchBit2());
    return true;
}

/* 000024AC-00002540       .text eventHatchInit__9daNpcMn_cFv */
void daNpcMn_c::eventHatchInit() {
    daObjOhatch_c* hatch = (daObjOhatch_c*)fopAcM_searchFromName("Ohatch", 0, 0);
    if (hatch != NULL) {
        s16 angle;
        dNpc_calc_DisXZ_AngY(current.pos, hatch->current.pos, NULL, &angle);
        mHomeYRot = angle;
    }
}

/* 00002540-00002578       .text eventHatch__9daNpcMn_cFv */
bool daNpcMn_c::eventHatch() {
    mTargetYRot = mHomeYRot;
    mHeadOnlyFollow = false;
    mLookMode = LOOK_MODE_TURN;
    m_jnt.setTrn();
    if (mHomeYRot - current.angle.y == 0) {
        return true;
    }
    return false;
}

/* 00002578-000025EC       .text eventBikkuriInit__9daNpcMn_cFi */
void daNpcMn_c::eventBikkuriInit(int i_staffIdx) {
    int* timer = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "Timer");
    mEventTimer = 1;
    if (timer != NULL) {
        mEventTimer = *timer;
    }
    if (mEventTimer <= 0) {
        mEventTimer = 1;
    }
}

/* 000025EC-00002644       .text eventBikkuri__9daNpcMn_cFv */
bool daNpcMn_c::eventBikkuri() {
    if (mEventTimer != 0) {
        mEventTimer--;
        if (mEventTimer == 0) {
            setAnmTbl(l_npc_anm_bikkuri);
        }
        return false;
    }
    return mAnmFlag & 1;
}

/* 00002644-0000266C       .text eventTurnInit__9daNpcMn_cFv */
void daNpcMn_c::eventTurnInit() {
    setAnmTbl(&l_npc_anm_wait);
}

/* 0000266C-000027B4       .text eventTurn__9daNpcMn_cFi */
bool daNpcMn_c::eventTurn(int i_staffIdx) {
    int* pData = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "TurnMode");
    int turnMode = 0;
    if (pData != NULL) {
        turnMode = *pData;
    }

    cXyz pos;
    daObjOhatch_c* hatch;
    switch (turnMode) {
        case 1:
            hatch = (daObjOhatch_c*)fopAcM_searchFromName("Ohatch", 0, 0);
            if (hatch != NULL) {
                pos = hatch->current.pos;
                break;
            }
        default:
            pos = mPathRun.getPoint(mPathRun.getIdx());
            break;
    }
    s16 angle;
    dNpc_calc_DisXZ_AngY(current.pos, pos, NULL, &angle);
    mTargetYRot = angle;
    mHeadOnlyFollow = false;
    mLookMode = LOOK_MODE_TURN;
    m_jnt.setTrn();
    if (current.angle.y == angle) {
        return true;
    }
    return false;
}

/* 000027B4-000027DC       .text eventWalkInit__9daNpcMn_cFv */
void daNpcMn_c::eventWalkInit() {
    setAnmTbl(&l_npc_anm_walk);
}

/* 000027DC-0000293C       .text eventWalk__9daNpcMn_cFv */
bool daNpcMn_c::eventWalk() {
    bool reachedEnd = false;
    if (mPathRun.chkPointPass(current.pos, mPathRun.getDir())) {
        if (mPathRun.nextIdxAuto() == NULL) {
            reachedEnd = true;
        }
    }
    if (!reachedEnd) {
        cXyz pos = mPathRun.getPoint(mPathRun.getIdx());
        s16 angle;
        dNpc_calc_DisXZ_AngY(current.pos, pos, NULL, &angle);
        mTargetYRot = mHomeYRot = angle;
        mHeadOnlyFollow = false;
        mLookAtMaxVel = l_npc_dat[mNpcNo].mWalkLookAtMaxVel;
        mLookMode = LOOK_MODE_TURN;
        m_jnt.setTrn();
        mTargetSpeedF = l_npc_dat[mNpcNo].mWalkSpeed;
    } else {
        fopAcM_SetSpeedF(this, 0.0f);
        mTargetSpeedF = 0.0f;
        return true;
    }
    return false;
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
void daNpcMn_c::eventJumpInit(int i_staffIdx) {
    f32* speedX = dComIfGp_evmng_getMyFloatP(i_staffIdx, "SpeedX");
    f32* speedY = dComIfGp_evmng_getMyFloatP(i_staffIdx, "SpeedY");
    f32* gravity = dComIfGp_evmng_getMyFloatP(i_staffIdx, "Gravity");

    if (speedX != NULL) {
        mTargetSpeedF = speedF = *speedX;
    } else {
        fopAcM_SetSpeedF(this, 3.0f);
        mTargetSpeedF = 3.0f;
    }
    if (speedY != NULL) {
        mJumpSpeedY = *speedY;
    } else {
        mJumpSpeedY = 200.0f;
    }
    if (gravity != NULL) {
        fopAcM_SetGravity(this, *gravity);
    }
    mTargetSpeedF = 40.0f;
    mJumpSpeedY = 25.0f;
    fopAcM_SetGravity(this, -1.0f);
}

/* 00002A90-00002AE8       .text eventJump__9daNpcMn_cFv */
bool daNpcMn_c::eventJump() {
    current.pos.y += mJumpSpeedY;
    mJumpSpeedY += gravity;
    if (mJumpSpeedY < 0.0f && mObjAcch.ChkGroundLanding()) {
        fopAcM_SetSpeedF(this, 0.0f);
        mTargetSpeedF = 0.0f;
        return true;
    }
    return false;
}

/* 00002AE8-00002C30       .text talk2__9daNpcMn_cFi */
u16 daNpcMn_c::talk2(int i_param) {
    u16 status = 0xFF;
    if (mCurrMsgBsPcId == fpcM_ERROR_PROCESS_ID_e) {
        if (i_param == 1) {
            mCurrMsgNo = getMsg();
        }
        mCurrMsgBsPcId = fopMsgM_messageSet(mCurrMsgNo, this);
        mpCurrMsg = NULL;
        mLastMsgStatus = -1;
    } else if (mpCurrMsg) {
        status = mpCurrMsg->mStatus;
        switch (status) {
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
        mLastMsgStatus = status;
        anmAtr(status);
    } else {
        mpCurrMsg = fopMsgM_SearchByID(mCurrMsgBsPcId);
    }
    return status;
}

/* 00002C30-00002D68       .text talk3__9daNpcMn_cFi */
u16 daNpcMn_c::talk3(int i_param) {
    u16 status = 0xFF;
    if (mCurrMsgBsPcId == fpcM_ERROR_PROCESS_ID_e) {
        if (i_param == 1) {
            mCurrMsgNo = getMsg3();
        }
        mCurrMsgBsPcId = fopMsgM_scopeMessageSet(mCurrMsgNo);
        mpCurrMsg = NULL;
        mLastMsgStatus = -1;
    } else if (mpCurrMsg != NULL) {
        status = dComIfGp_getScopeMesgStatus();
        switch (status) {
            case fopMsgStts_MSG_DISPLAYED_e:
                dComIfGp_setScopeMesgStatus(next_msgStatus(&mCurrMsgNo));
                if (dComIfGp_getScopeMesgStatus() == fopMsgStts_MSG_CONTINUES_e) {
                    fopMsgM_scopeMessageSet(mCurrMsgNo);
                }
                break;
            case fopMsgStts_MSG_TYPING_e:
                if (mLastMsgStatus == fopMsgStts_MSG_CONTINUES_e) {
                    chkMsg();
                }
                break;
            case fopMsgStts_BOX_CLOSED_e:
                dComIfGp_setScopeMesgStatus(fopMsgStts_BOX_CLOSING_e);
                mCurrMsgBsPcId = fpcM_ERROR_PROCESS_ID_e;
                break;
        }
        mLastMsgStatus = status;
        anmAtr(status);
    } else {
        mpCurrMsg = fopMsgM_SearchByID(mCurrMsgBsPcId);
    }
    return status;
}

/* 00002D68-00002DB8       .text next_msgStatus__9daNpcMn_cFPUl */
u16 daNpcMn_c::next_msgStatus(u32* i_msgNo) {
    u16 ret = fopMsgStts_MSG_CONTINUES_e;
    if (mpMsgNo != NULL) {
        mpMsgNo++;
        switch (*mpMsgNo) {
            case 0:
                mpMsgNo = 0;
                ret = fopNpc_npc_c::next_msgStatus(i_msgNo);
                break;
            default:
                *i_msgNo = *mpMsgNo;
                break;
        }
    } else {
        ret = fopNpc_npc_c::next_msgStatus(i_msgNo);
    }
    return ret;
}

/* 00002DB8-00002F7C       .text getMsg__9daNpcMn_cFv */
u32 daNpcMn_c::getMsg() {
    u32 msg = 0;
    mpMsgNo = NULL;

    if (!dComIfGp_event_chkTalkXY()) {
        if (!mPosFlag) {
            if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2F08)) {
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_2F08);
                mpMsgNo = l_msg_mn_1st_talk;
            } else {
                mpMsgNo = l_msg_mn_2nd_talk;
            }
        } else if (mPosFlag == 1 && dComIfGs_isEventBit(dSv_event_flag_c::UNK_3D08)) {
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_2F04);
            if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_3120)) {
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_3120);
                mpMsgNo = l_msg_mn_comp_1st;
            } else {
                mpMsgNo = l_msg_mn_comp_2nd;
            }
        } else {
            if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2F04)) {
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_2F04);
                mpMsgNo = l_msg_mn_1st_talk_in;
            } else if (mbLookFigure != 0) {
                msg = l_msg_mn_figure[mFigureMsgIdx];
            } else {
                if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_3A01)) {
                    mpMsgNo = l_msg_mn_2nd_talk_in;
                } else {
                    mpMsgNo = l_msg_mn_3rd_talk_in;
                }
            }
        }
    }
    if (mpMsgNo != NULL) {
        msg = *mpMsgNo;
    }
    return msg;
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
    switch (dComIfGp_getMesgAnimeAttrInfo()) {
        case 0:
            setAnmTbl(&l_npc_anm_wait);
            break;
        case 1:
            setAnmTbl(&l_npc_anm_talk);
            break;
        case 2:
            setAnmTbl(&l_npc_anm_talk2);
            break;
        case 3:
            setAnmTbl(&l_npc_anm_wait2);
            break;
    }
    dComIfGp_setMesgAnimeAttrInfo(0xFF);
}

/* 0000302C-0000303C       .text getPrmNpcNo__9daNpcMn_cFv */
bool daNpcMn_c::getPrmNpcNo() {
    return mPosFlag != false;
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
    J3DModel* model = mpMorf->getModel();
    model->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    cMtx_YrotM(mDoMtx_stack_c::get(), current.angle.y);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00003148-00003478       .text chkAttention__9daNpcMn_cFv */
void daNpcMn_c::chkAttention() {
    mbNearPlayer = 0;
    if (mEventCut.getAttnFlag()) {
        mLookAtPos = mEventCut.getAttnPos();
        mLookMode = LOOK_MODE_ATTN;
        if (mbAllowBodyTurn) {
            mHeadOnlyFollow = false;
            m_jnt.setTrn();
        } else {
            mHeadOnlyFollow = true;
        }
        if (mbPlayerAttention == 0) {
            mbPlayerAttention = 1;
        }
    } else {
        fopAc_ac_c* player = dComIfGp_getLinkPlayer();
        f32 maxDist = mAttnDist;
        int maxAngle = mAttnAngle;

        f32 dist;
        s16 angle;
        dNpc_calc_DisXZ_AngY(current.pos, player->current.pos, &dist, &angle);
        if (mbPlayerAttention != 0) {
            maxDist += 40.0f;
            maxAngle += 0x71C;
        }
        angle -= shape_angle.y;

        if (maxDist > dist && maxAngle > abs(angle)) {
            mLookAtPos = dNpc_playerEyePos(l_npc_dat[mNpcNo].mPlayerEyeOfsY);
            mLookMode = LOOK_MODE_ATTN;
            if (mbAllowBodyTurn) {
                mHeadOnlyFollow = false;
            } else {
                mHeadOnlyFollow = true;
            }

            if (mbLookOnly == 0) {
                mTargetYRot = mHomeYRot;
                mHeadOnlyFollow = false;
                mLookMode = LOOK_MODE_TURN;
                m_jnt.setTrn();
            }
            if (mbPlayerAttention == 0) {
                mbPlayerAttention = 1;
            }
        } else {
            if (mbPlayerAttention == 1) {
                mbPlayerAttention = 0;
                mLookResetTimer = l_npc_dat[mNpcNo].mLookResetTimer;
            }
            if (l_npc_dat[mNpcNo].mNearDist > dist) {
                mLookAtPos = dNpc_playerEyePos(l_npc_dat[mNpcNo].mPlayerEyeOfsY);
                mLookMode = LOOK_MODE_ATTN;
                if (mbAllowBodyTurn != 0) {
                    mHeadOnlyFollow = false;
                } else {
                    mHeadOnlyFollow = true;
                }

                if (mbLookOnly == 0) {
                    mTargetYRot = mHomeYRot;
                    mHeadOnlyFollow = false;
                    mLookMode = LOOK_MODE_TURN;
                    m_jnt.setTrn();
                }
                mbNearPlayer = 1;
            } else {
                mLookMode = LOOK_MODE_NONE;
                if (!mPathRun.isPath()) {
                    if (mLookResetTimer != 0) {
                        mLookResetTimer--;
                    } else {
                        mTargetYRot = mHomeYRot;
                        mHeadOnlyFollow = false;
                        mLookMode = LOOK_MODE_TURN;
                        m_jnt.setTrn();
                    }
                }
            }
        }
    }
    mLookAtMaxVel = l_npc_dat[mNpcNo].mLookAtMaxVel;
}

/* 00003478-000035C4       .text lookBack__9daNpcMn_cFv */
void daNpcMn_c::lookBack() {
    s16 maxVel = mLookAtMaxVel;
    s16 desiredYRot = current.angle.y;

    cXyz* dstTemp = NULL;
    cXyz temp2;
    cXyz dstPos = eyePos;
    bool headOnlyFollow = mHeadOnlyFollow;
    switch (mLookMode) {
        case LOOK_MODE_ATTN:
            temp2 = mLookAtPos;
            dstTemp = &temp2;
            break;
        case LOOK_MODE_TURN:
            desiredYRot = mTargetYRot;
            break;
        case LOOK_MODE_NONE:
        default:
            break;
    }
    if (mTalkOrder && mbAllowBodyTurn) {
        headOnlyFollow = false;
        m_jnt.setTrn();
    }
    if (m_jnt.trnChk()) {
        if (mEventCut.getTurnSpeed() != 0) {
            maxVel = mEventCut.getTurnSpeed();
        }
        cLib_addCalcAngleS2(&mTurnVel, maxVel, 4, 0x800);
    } else {
        mTurnVel = 0;
    }
    m_jnt.lookAtTarget(&current.angle.y, dstTemp, dstPos, desiredYRot, mTurnVel, headOnlyFollow);
    shape_angle = current.angle;
}

/* 000035C4-000036D0       .text initTexPatternAnm__9daNpcMn_cFb */
BOOL daNpcMn_c::initTexPatternAnm(bool modify) {
    J3DModelData* modelData = mpMorf->getModel()->getModelData();
    m_head_tex_pattern = (J3DAnmTexPattern*)dComIfG_getObjectIDRes(l_arcname_tbl[0], l_btp_ix_tbl[0]);
    JUT_ASSERT(DEMO_SELECT(0xA0E, 0xA19), m_head_tex_pattern != NULL);
    BOOL ret = mBtpAnm.init(modelData, m_head_tex_pattern, 1, 2, 1.0, 0, -1, modify, FALSE);
    if (ret == FALSE)
        return FALSE;
    else {
        mBtpFrame = 0;
        mBtpTimer = 0;
        return TRUE;
    }
}

/* 000036D0-0000373C       .text playTexPatternAnm__9daNpcMn_cFv */
void daNpcMn_c::playTexPatternAnm() {
    if (!cLib_calcTimer(&mBtpTimer)) {
        if (mBtpFrame >= m_head_tex_pattern->getFrameMax()) {
            mBtpFrame -= m_head_tex_pattern->getFrameMax();
            mBtpTimer = 0x78;
        } else {
            mBtpFrame++;
        }
    }
}

/* 0000373C-000037F8       .text playAnm__9daNpcMn_cFv */
void daNpcMn_c::playAnm() {
    if (mpMorf->play(NULL, 0, 0) && mpAnmDat != NULL && mAnmLoopCnt > 0) {
        mAnmLoopCnt--;
        if (mAnmLoopCnt == 0) {
            mpAnmDat++;
            if (setAnmTbl(mpAnmDat)) {
                mAnmFlag |= 1;
            }
        } else {
            setAnm(mpAnmDat->mBckIdx, 0, 0.0f);
        }
    }
}

/* 000037F8-000038C8       .text setAnm__9daNpcMn_cFUcif */
void daNpcMn_c::setAnm(u8 i_bckIdx, int i_loopMode, float i_morf) {
    if (mAnmMorfOverride >= 0.0f) {
        i_morf = mAnmMorfOverride;
        mAnmMorfOverride = -1.0f;
    }
    J3DAnmTransformKey* pAnm = (J3DAnmTransformKey*)dComIfG_getObjectIDRes(l_arcname_tbl[0], l_bck_ix_tbl[i_bckIdx]);
    mpMorf->setAnm(pAnm, i_loopMode, i_morf, 1.0f, 0.0f, -1.0f, NULL);
    mBckIdx = i_bckIdx;
}

/* 000038C8-00003974       .text setAnmTbl__9daNpcMn_cFP9sMnAnmDat */
bool daNpcMn_c::setAnmTbl(sMnAnmDat* i_anmDat) {
    mAnmFlag &= 0xFE;
    if (i_anmDat->mBckIdx == BCK_NULL) {
        mpAnmDat = NULL;
        return TRUE;
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
    return FALSE;
}

/* 00003974-0000397C       .text XyCheckCB__9daNpcMn_cFi */
s16 daNpcMn_c::XyCheckCB(int) {
    return false;
}

/* 0000397C-000039E0       .text getRand__9daNpcMn_cFi */
int daNpcMn_c::getRand(int i_max) {
    int rnd = cM_rndF(i_max);
    if (rnd == i_max) {
        rnd = 0;
    }
    return rnd;
}

/* 000039E0-00003A58       .text setCollision__9daNpcMn_cFP8dCcD_Cyl4cXyzff */
void daNpcMn_c::setCollision(dCcD_Cyl* i_cyl, cXyz i_center, float i_radius, float i_height) {
    i_cyl->SetC(i_center);
    i_cyl->SetR(i_radius);
    i_cyl->SetH(i_height);
    dComIfG_Ccsp()->Set(i_cyl);
}

/* 00003A58-00003AC4       .text chkEndEvent__9daNpcMn_cFv */
BOOL daNpcMn_c::chkEndEvent() {
    if (dComIfGp_evmng_endCheck(mHatchEventIdx)) {
        dComIfGp_event_onEventFlag(8);
        fopAcM_delete(this);
        return TRUE;
    }
    return FALSE;
}

/* 00003AC4-00003B38       .text chkPosNo__9daNpcMn_cFv */
u8 daNpcMn_c::chkPosNo() {
    u8 posNo = 0;
    while (posNo < 10) {
        if (strcmp(dComIfGp_getNextStageName(), l_room_name[posNo]) != 0) {
            posNo++;
        } else {
            break;
        }
    }
    return posNo;
}

/* 00003B38-00003CD8       .text getPosNo__9daNpcMn_cFv */
u8 daNpcMn_c::getPosNo() {
    int roomCnt[8];
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_3D08) && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_3120)) {
        return 1;
    }

    roomCnt[0] = 1;
    for (int i = 1; i < 8; i++) {
        roomCnt[i] = 0;
    }

    for (int fig = 0; fig < 0x86; fig++) {
        if (fig / 8 < 0x11) {
            int bit = fig % 8;
            u8 reg = dComIfGs_getEventReg(l_figure_comp[fig / 8]);
            if (reg & (1 << bit)) {
                int roomId = dSnap_GetFigRoomId(fig);
                if (roomId != 0xFF && roomId < 8) {
                    roomCnt[roomId]++;
                }
            }
        }
    }

    int nonZero = 0;
    for (int i = 0; i < 8; i++) {
        if (roomCnt[i] != 0) {
            nonZero++;
        }
    }

    int rnd = getRand(nonZero);
    for (int i = 0; i < 8; i++) {
        if (roomCnt[i] != 0) {
            if (rnd) {
                rnd--;
            } else {
                return i + 1;
            }
        }
    }
    return 1;
}

/* 00003CD8-00003CE8       .text isChangePos__9daNpcMn_cFUc */
BOOL daNpcMn_c::isChangePos(u8 i_posNo) {
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
