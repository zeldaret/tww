/**
 * d_a_npc_kamome.cpp
 * Player - Hyoi Seagull
 */

#include "d/actor/d_a_npc_kamome.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "m_Do/m_Do_hostIO.h"
#include "d/d_item_data.h"
#include "d/actor/d_a_player_main.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_controller_pad.h"
#include "d/d_npc.h"
#include "d/d_snap.h"
#include "d/d_camera.h"

// Needed for the .data section to match.
static f32 dummy1[3] = {1.0f, 1.0f, 1.0f};
static f32 dummy2[3] = {1.0f, 1.0f, 1.0f};
static u8 dummy3[4] = {0x02, 0x00, 0x02, 0x01};
static f64 dummy4[2] = {3.0, 0.5};

static char* l_staff_name = "HyoiKam";
static u8 temp[0x4C]; // TODO
static daNpc_kam_HIO_c l_HIO;
static int l_hio_counter;
static uint l_msgId;
static msg_class* l_msg;
static daNpc_kam_c* l_act;
static s16 l_demo_start_chk_cnt;
static s16 l_demo_start_chk_flag;
static cXyz l_ms_at_local_vec(0.0f, 0.0f, -1.0f);
static cXyz l_ms_at_local_start(100.0f, 20.0f, 0.0f);
static cXyz l_ms_at_local_end(-100.0f, 20.0f, 0.0f);
static cXyz l_line_bg_local_end(0.0f, 0.0f, 500.0f);
static cXyz l_call_local_kyori(0.0f, 0.0f, 500.0f);

enum KAMOME_RES_FILE_ID { // IDs and indexes are synced
    /* BAS */
    KAMOME_BAS_KA_FLY1=0x5,
    KAMOME_BAS_KA_LAND1=0x6,
    KAMOME_BAS_KA_MOVE1=0x7,
    KAMOME_BAS_KA_WAIT1=0x8,
    KAMOME_BAS_KA_WAIT2=0x9,
    
    /* BCK */
    KAMOME_BCK_KA_EAT1=0xC,
    KAMOME_BCK_KA_FLY1=0xD,
    KAMOME_BCK_KA_LAND1=0xE,
    KAMOME_BCK_KA_MOVE1=0xF,
    KAMOME_BCK_KA_SING1=0x10,
    KAMOME_BCK_KA_SING2=0x11,
    KAMOME_BCK_KA_WAIT1=0x12,
    KAMOME_BCK_KA_WAIT2=0x13,
    KAMOME_BCK_KA_WAIT3=0x14,
    
    /* BDL */
    KAMOME_BDL_KA=0x17,
    KAMOME_BDL_KA_HYOI=0x18,
};

/* 000000EC-00000174       .text __ct__16daNpc_kam_HIO1_cFv */
daNpc_kam_HIO1_c::daNpc_kam_HIO1_c() {
    mSpeedF = 17.0f;
    mUnused08 = 0.1f;
    mGlidingAngVelY = 0x2000;
    mGlidingAngVelX = 0x0AAA;
    mMaxAngleZ = 0x2000;
    mAccelF = 0.7f;
    mFlappingSpeedF = 23.0f;
    mFlappingAngVelY = 0x2710;
    mFlappingAngVelX = 0x1555;
    mAngVelStepScale = 5;
    mAngVelMaxStep = 0x1000;
    mAngVelMinStep = 0x0400;
    mFlapDuration = 30;
    mFlapExhaustedDuration = 150;
    mFlapEnergyDuration = 150;
}

/* 00000174-000001F8       .text __ct__15daNpc_kam_HIO_cFv */
daNpc_kam_HIO_c::daNpc_kam_HIO_c() {
    mChildID = -1;
    static const hio_prm_c init_data = {
        /* m08 */ 3000.0f,
        /* m0C */ 1000.0f,
        /* m10 */ 250.0f,
        /* m14 */ 0.0f,
        /* m18 */ 0.0f,
        /* m1C */ 0x4000,
        /* m1E */ 0,
    };
    prm = init_data;
}

/* 00000240-00000260       .text daNpc_kam_XyCheckCB__FPvi */
static s16 daNpc_kam_XyCheckCB(void* i_this, int equippedItemIdx) {
    return ((daNpc_kam_c*)i_this)->XyCheckCB(equippedItemIdx);
}

/* 00000260-000002A4       .text XyCheckCB__11daNpc_kam_cFi */
s16 daNpc_kam_c::XyCheckCB(int equippedItemIdx) {
    if (dComIfGp_getSelectItem(equippedItemIdx) == dItem_HYOI_PEAR_e) {
        return callDemoStartCheck();
    } else {
        return FALSE;
    }
}

/* 000002A4-000004F0       .text callDemoStartCheck__11daNpc_kam_cFv */
int daNpc_kam_c::callDemoStartCheck() {
    if (l_demo_start_chk_cnt != 0) {
        return l_demo_start_chk_flag;
    }
    
    l_demo_start_chk_cnt += 1;
    l_demo_start_chk_flag = 0;
    
    daPy_lk_c* link = daPy_getPlayerLinkActorClass();
    cXyz hyoi_pear_pos = link->getHeadTopPos();
    hyoi_pear_pos.y += 20.0f;
    
    cXyz descend_start_pos;
    cXyz line_start_pos;
    cXyz line_end_pos;
    
    s16 angle = link->shape_angle.y + 0x8000;
    mLinChk.OnBackFlag();
    
    line_end_pos = hyoi_pear_pos;
    
    // Check if there are any straight lines from any angle around the Hyoi Pear that the Hyoi Seagull can descend from.
    for (int i = 0; i < 0x10; i++) {
        mDoMtx_stack_c::YrotS(angle + 0x8000);
        mDoMtx_stack_c::multVec(&l_call_local_kyori, &line_end_pos);
        mDoMtx_stack_c::YrotS(angle);
        mDoMtx_stack_c::multVec(&l_call_local_kyori, &line_start_pos);
        mDoMtx_stack_c::XrotM(-0x1555);
        mDoMtx_stack_c::multVec(&l_call_local_kyori, &descend_start_pos);
        
        line_end_pos += hyoi_pear_pos;
        line_start_pos += hyoi_pear_pos;
        descend_start_pos += line_start_pos;
        
        mLinChk.Set(&descend_start_pos, &line_start_pos, this);
        if (!dComIfG_Bgsp()->LineCross(&mLinChk)) {
            mLinChk.Set(&line_start_pos, &line_end_pos, this);
            if (!dComIfG_Bgsp()->LineCross(&mLinChk)) {
                // Found a direction with no collisions.
                mDescendStartPos = descend_start_pos;
                mDescendStartPosUnangled = line_start_pos; // Unused
                mDescendStartAngle.set(0x1555, angle + 0x8000, 0);
                mLinChk.OffBackFlag();
                l_demo_start_chk_flag = 1;
                return 1;
            }
        }
        
        angle = angle + 0x2000;
    }
    
    mLinChk.OffBackFlag();
    
    return 0;
}

/* 0000052C-0000054C       .text daNpc_kam_XyEventCB__FPvi */
static s16 daNpc_kam_XyEventCB(void* i_this, int equippedItemIdx) {
    return ((daNpc_kam_c*)i_this)->XyEventCB(equippedItemIdx);
}

/* 0000054C-00000568       .text XyEventCB__11daNpc_kam_cFi */
s16 daNpc_kam_c::XyEventCB(int equippedItemIdx) {
    onEventAccept();
    mCurrEventIdxIdx = 1; // "kamome_call"
    return mEventIdxs[1];
}

/* 00000568-000009E4       .text __dt__11daNpc_kam_cFv */
daNpc_kam_c::~daNpc_kam_c() {
    if (l_act == this) {
        l_act = NULL;
    }
    
    dComIfG_resDelete(&mPhs, "Kamome");
    
    if (heap) {
        mpMorf->stopZelAnime();
    }
    
    if (l_HIO.mChildID >= 0) {
        mDoHIO_root.mDoHIO_deleteChild(l_HIO.mChildID);
        l_HIO.mChildID = -1;
    }
    
    offHyoiKamome();
}

/* 00000A6C-00000B20       .text setAttention__11daNpc_kam_cFbi */
void daNpc_kam_c::setAttention(bool param_1, int param_2) {
    if (param_1) {
        cXyz headTopPos = getHeadTopPos();
        eyePos.set(headTopPos.x, headTopPos.y - 20.0f, headTopPos.z);
        if (param_2) {
            attention_info.position.set(current.pos.x, current.pos.y, current.pos.z);
        } else {
            attention_info.position.set(home.pos.x, home.pos.y, home.pos.z);
        }
    }
}

/* 00000B20-00000C00       .text setBaseMtx__11daNpc_kam_cFv */
void daNpc_kam_c::setBaseMtx() {
    static cXyz l_offset(0.0f, 30.0f, 0.0f);
    J3DModel* model = mpMorf->getModel();
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mDoMtx_stack_c::transM(l_offset);
    model->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
}

/* 00000C00-00000CD0       .text headNodeCallBack__FP7J3DNodei */
static int headNodeCallBack(J3DNode* node, int param_1) {
    if (!param_1) {
        J3DJoint* joint = (J3DJoint*)node;
        J3DModel* model = j3dSys.getModel();
        daNpc_kam_c* i_this = (daNpc_kam_c*)model->getUserArea();
        if (i_this) {
            static cXyz l_offsetAttPos(0.0f, 20.0f, 0.0f);
            s32 jntNo = joint->getJntNo();
            mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));
            mDoMtx_stack_c::multVec(&l_offsetAttPos, i_this->getHeadTopPosP());
        }
    }
    return TRUE;
}

/* 00000CD0-00000EB8       .text createHeap__11daNpc_kam_cFv */
BOOL daNpc_kam_c::createHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Kamome", KAMOME_BDL_KA_HYOI);
    JUT_ASSERT(763, modelData != 0);
    
    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL, NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Kamome", KAMOME_BCK_KA_WAIT1),
        J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, 1,
        NULL,
        0x00080000,
        0x11000002
    );
    
    if (mpMorf == NULL || mpMorf->getModel() == NULL) {
        return FALSE;
    }
    
    s16 head1JntIdx = modelData->getJointName()->getIndex("j_ka_head1");
    if (head1JntIdx >= 0) {
        modelData->getJointNodePointer(head1JntIdx)->setCallBack(headNodeCallBack);
    }
    m_jnt_body = modelData->getJointName()->getIndex("j_ka_spin1");
    JUT_ASSERT(783, m_jnt_body >= 0);
    
    mpMorf->getModel()->setUserArea((u32)this);
    
    return TRUE;
}

/* 00000EB8-00000ED8       .text checkCreateHeap__FP10fopAc_ac_c */
static BOOL checkCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_kam_c*)i_this)->createHeap();
}

/* 00000ED8-0000101C       .text create__11daNpc_kam_cFv */
s32 daNpc_kam_c::create() {
    fopAcM_SetupActor(this, daNpc_kam_c);
    
    if (l_act != NULL && l_act != this) {
        return cPhs_ERROR_e;
    }
    l_act = this;
    
    static u32 l_heap_size = 0x1360;
    
    s32 phase_state = dComIfG_resLoad(&mPhs, "Kamome");
    
    if (phase_state == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(this, checkCreateHeap, l_heap_size)) {
            mpMorf = NULL;
            return cPhs_ERROR_e;
        }
        
        fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
        
        if (l_HIO.mChildID < 0) {
            l_HIO.mChildID = mDoHIO_root.mDoHIO_createChild("かもめ", &l_HIO); // "Seagull" (kamome)
            l_HIO.mpActor = this;
        }
        
        if (!init()) {
            phase_state = cPhs_ERROR_e;
        }
    }
    
    return phase_state;
}

static dCcD_SrcSph l_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_SWORD,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ AT_SPRM_SET | AT_SPRM_VS_OTHER,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ CO_SPRM_SET | CO_SPRM_IS_UNK8 | CO_SPRM_VSGRP,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 30.0f,
    },
};

static dCcD_SrcSph l_tg_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ TG_SPRM_SET | TG_SPRM_IS_PLAYER,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 30.0f,
    },
};

static dCcD_SrcCps l_kam_at_cps_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_SWORD,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ AT_SPRM_SET | AT_SPRM_VS_OTHER,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ G_AT_SPRM_NO_HIT_MARK,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCpsS
    {
        /* Start  */ 0.0f, 0.0f, 0.0f,
        /* End    */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 20.0f,
    },
};

static char* event_name_tbl[] = {
    "OPTION_CHAR_END",
    "kamome_call",
    "kamome_out_turn",
};

/* 00001B88-00001DBC       .text init__11daNpc_kam_cFv */
BOOL daNpc_kam_c::init() {
    offHyoiKamome();
    mUnusedC06 = 0;
    mEventState = -1;
    mCurrEventIdxIdx = -1;
    scale *= 1000.0f;
    mMaxY = home.pos.y + scale.y;
    mMinY = home.pos.y - scale.y;
    
    mTargetSpeedF = l_HIO.mHio1.mSpeedF;
    mAngVelY = l_HIO.mHio1.mGlidingAngVelY;
    mAngVelX = l_HIO.mHio1.mGlidingAngVelX;
    mTargetAngVelY = l_HIO.mHio1.mGlidingAngVelY;
    mTargetAngVelX = l_HIO.mHio1.mGlidingAngVelX;
    
    setNpcAction(&waitNpcAction, NULL);
    
    mAcchCirs[0].SetWall(20.0f, 50.0f);
    mAcchCirs[1].SetWall(-20.0f, 50.0f);
    mAcch.Set(&current.pos, &old.pos, this, ARRAY_SIZE(mAcchCirs), mAcchCirs, &speed);
    mAcch.ClrRoofNone();
    mAcch.SetRoofCrrHeight(20.0f);
    mAcch.OnLineCheck();
    mAcch.OnSeaCheckOn();
    mAcch.OnSeaWaterHeight();
    mStts.Init(100, 0xFF, this);
    mAtSph.Set(l_sph_src);
    mAtSph.SetStts(&mStts);
    mTgSph.Set(l_tg_sph_src);
    mTgSph.SetStts(&mStts);
    mCps.Set(l_kam_at_cps_src);
    mCps.SetStts(&mStts);
    
    setBaseMtx();
    
    attention_info.flags = 0;
    attention_info.distances[1] = 38;
    attention_info.distances[3] = 38;
    
    for (int i = 0; i < 3; i++) {
        mEventIdxs[i] = dComIfGp_evmng_getEventIdx(event_name_tbl[i], 0xFF);
    }
    
    eventInfo.setXyCheckCB(daNpc_kam_XyCheckCB);
    eventInfo.setXyEventCB(daNpc_kam_XyEventCB);
    
    return TRUE;
}

/* 00001DBC-00001E8C       .text setAction__11daNpc_kam_cFPM11daNpc_kam_cFPCvPvPv_iM11daNpc_kam_cFPCvPvPv_iPv */
BOOL daNpc_kam_c::setAction(ActionFunc* pCurrActionFunc, ActionFunc newActionFunc, void* arg) {
    if (*pCurrActionFunc != newActionFunc) {
        if (*pCurrActionFunc) {
            mActionStatus = ACTION_ENDING;
            (this->**pCurrActionFunc)(arg);
        }
        *pCurrActionFunc = newActionFunc;
        mActionStatus = ACTION_STARTING;
        mC08 = 0;
        mC0A = 0;
        mC0C = 0;
        mUnusedC0E = 0;
        mUnusedC14 = 0.0f;
        (this->**pCurrActionFunc)(arg);
    }
    return TRUE;
}

/* 00001E8C-00001F40       .text npcAction__11daNpc_kam_cFPv */
void daNpc_kam_c::npcAction(void* arg) {
    if (!mCurrNpcActionFunc) {
        speedF = 0.0f;
        offHyoiKamome();
        setNpcAction(&waitNpcAction, NULL);
#if VERSION != VERSION_JPN
        mDoAud_zelAudio_c::getInterface()->field_0x0062 = 0;
#endif
    }
    
    (this->*mCurrNpcActionFunc)(arg);
}

/* 00001F40-00001FA4       .text setNpcAction__11daNpc_kam_cFM11daNpc_kam_cFPCvPvPv_iPv */
void daNpc_kam_c::setNpcAction(ActionFunc actionFunc, void* arg) {
    mCurrPlayerActionFunc = NULL;
    setAction(&mCurrNpcActionFunc, actionFunc, arg);
}

/* 00001FA4-00002058       .text playerAction__11daNpc_kam_cFPv */
void daNpc_kam_c::playerAction(void* arg) {
    if (!mCurrPlayerActionFunc) {
        speedF = 0.0f;
        setPlayerAction(&waitPlayerAction, NULL);
    }
    
    dComIfGp_setRStatusForce(0x07); // Show "Return" on the R button
    dComIfGp_setDoStatus(0x23); // Show "Fly" on the A button
    dComIfGp_setAStatus(0x3E); // Do not display the B button icon at all
    
    (this->*mCurrPlayerActionFunc)(arg);
}

/* 00002058-000020BC       .text setPlayerAction__11daNpc_kam_cFM11daNpc_kam_cFPCvPvPv_iPv */
void daNpc_kam_c::setPlayerAction(ActionFunc actionFunc, void* arg) {
    mCurrNpcActionFunc = NULL;
    setAction(&mCurrPlayerActionFunc, actionFunc, arg);
}

/* 000020BC-00002100       .text returnLinkCheck__11daNpc_kam_cFv */
BOOL daNpc_kam_c::returnLinkCheck() {
    if (!dComIfGp_event_runCheck()) {
        if (CPad_CHECK_TRIG_R(0) || CPad_CHECK_TRIG_START(0)) {
            return TRUE;
        }
    }
    return FALSE;
}

/* 00002100-0000235C       .text changeAreaCheck__11daNpc_kam_cFv */
BOOL daNpc_kam_c::changeAreaCheck() {
    // Determine if Link is allowed to take control of a Hyoi Seagull depending on his current position.
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    cXyz delta;
    if (strcmp(dComIfGp_getStartStageName(), "sea") == 0 && fopAcM_GetRoomNo(this) == 41) {
        // Forest Haven sector on the sea.
        // Check if Link is standing on top of the rock formation with the Nintendo Gallery entrance on it.
        // If not, do not allow Link to control a Hyoi Seagull even if he's within its moveable range.
        static cXyz l_center(211555.0f, 1000.0f, 191870.0f);
        if (player->current.pos.y > l_center.y) {
            delta = player->current.pos - l_center;
            if (delta.absXZ() < 1300.0f) {
                offNpcNotChange();
                return TRUE;
            }
        }
    } else {
        // For all other sectors, simple check if Link is within the Hyoi Seagull's moveable range.
        delta = player->current.pos - home.pos;
        if (delta.absXZ() < scale.x) {
            offNpcNotChange();
            return TRUE;
        }
    }
    onNpcNotChange();
    return FALSE;
}

/* 0000235C-00002450       .text areaOutCheck__11daNpc_kam_cFv */
BOOL daNpc_kam_c::areaOutCheck() {
    cXyz delta = (current.pos - home.pos);
    return delta.absXZ() > scale.x ? TRUE : FALSE;
}

/* 00002450-000025B0       .text getStickAngY__11daNpc_kam_cFPsPs */
BOOL daNpc_kam_c::getStickAngY(s16* pTargetAngleY, s16* pTargetAngleZ) {
    BOOL isTurning = FALSE;
    s16 deltaAngleY = 0;
    s16 targetAngleZ = 0;
    
    f32 stickPosX = g_mDoCPd_cpadInfo[0].mMainStickPosX;
    if (stickPosX) {
        deltaAngleY = stickPosX * -mAngVelY;
        targetAngleZ = stickPosX * l_HIO.mHio1.mMaxAngleZ;
        isTurning = TRUE;
    } else if (wallHitCheck() >= 0) {
        if (isLeftLineHit()) {
            deltaAngleY = -0x4000;
            targetAngleZ = l_HIO.mHio1.mMaxAngleZ;
            isTurning = TRUE;
        } else if (isRightLineHit()) {
            deltaAngleY = 0x4000;
            targetAngleZ = -l_HIO.mHio1.mMaxAngleZ;
            isTurning = TRUE;
        } else if (isFrontLineHit()) {
            deltaAngleY = -0x4000;
            targetAngleZ = l_HIO.mHio1.mMaxAngleZ;
            isTurning = TRUE;
        }
    }
    
    s16 angleY = dCam_getControledAngleY(dComIfGp_getCamera(0));
    *pTargetAngleY = deltaAngleY + angleY;
    *pTargetAngleZ = targetAngleZ;
    return isTurning;
}

/* 000025B0-00002664       .text getAngleX__11daNpc_kam_cFv */
s16 daNpc_kam_c::getAngleX() {
    s16 angle;
    if (current.pos.y < mMinY || mAcch.ChkGroundHit() || isWaterHit()) {
        // Turn up.
        angle = -mAngVelX;
        mLockAngleXTimer = 30;
    } else if (current.pos.y > mMaxY || mAcch.ChkRoofHit()) {
        // Turn down.
        angle = mAngVelX;
        mLockAngleXTimer = 30;
    } else {
        angle = g_mDoCPd_cpadInfo[0].mMainStickPosY * mAngVelX;
    }
    return angle;
}

/* 00002664-000026AC       .text wallHitCheck__11daNpc_kam_cFv */
int daNpc_kam_c::wallHitCheck() {
    if (mAcch.ChkWallHit()) {
        for (int i = 0; i < ARRAY_SIZE(mAcchCirs); i++) {
            if (mAcchCirs[i].ChkWallHit()) {
                return i;
            }
        }
    }
    return -1;
}

/* 000026AC-0000270C       .text npcTurnCheck__11daNpc_kam_cFPs */
BOOL daNpc_kam_c::npcTurnCheck(s16* pTargetAngleY) {
    BOOL isTurning = FALSE;
    if (isLeftLineHit()) {
        *pTargetAngleY = current.angle.y - 0x2000;
        isTurning = TRUE;
    } else if (isRightLineHit()) {
        *pTargetAngleY = current.angle.y + 0x2000;
        isTurning = TRUE;
    } else if (isFrontLineHit()) {
        *pTargetAngleY = current.angle.y - 0x2000;
        isTurning = TRUE;
    }
    return isTurning;
}

/* 0000270C-00002AF4       .text waitNpcAction__11daNpc_kam_cFPv */
int daNpc_kam_c::waitNpcAction(void*) {
    if (mActionStatus == ACTION_STARTING) {
        mActionStatus++; // ACTION_ONGOING_1
        setAnm(ANM_WAIT2);
        
        speedF = l_HIO.mHio1.mSpeedF;
        mTargetSpeedF = l_HIO.mHio1.mSpeedF;
        mAngVelY = l_HIO.mHio1.mGlidingAngVelY;
        mAngVelX = l_HIO.mHio1.mGlidingAngVelX;
        mTargetAngVelY = l_HIO.mHio1.mGlidingAngVelY;
        mTargetAngVelX = l_HIO.mHio1.mGlidingAngVelX;
        
        mC08 = cLib_getRndValue(90, 60);
        mC0C = cLib_getRndValue(10, 80);
    } else if (mActionStatus != ACTION_ENDING) {
        if (changeAreaCheck()) {
            attention_info.flags |= fopAc_Attn_ACTION_TALK_e | fopAc_Attn_TALKFLAG_NOTALK_e;
            mEventState = 6;
        } else {
            attention_info.flags &= ~(fopAc_Attn_ACTION_TALK_e | fopAc_Attn_TALKFLAG_NOTALK_e);
            mEventState = -1;
        }
        
        // Elements are randomly chosen from these arrays, except for the last two elements, which are never chosen.
        static const s16 l_turn_angleY[] = {0x1000, 0xF400, 0xF000, 0x0800, 0x0C00, 0xF800};
        static const int l_anm_type[] = {
            ANM_WAIT2, ANM_WAIT2, ANM_WAIT2, ANM_WAIT2, ANM_WAIT2, ANM_WAIT2, ANM_WAIT2, ANM_WAIT2,
            ANM_WAIT2, ANM_WAIT2, ANM_WAIT1, ANM_WAIT1, ANM_SING, ANM_WAIT1, ANM_SING, ANM_WAIT1,
        };
        s16 targetAngleX = 0;
        s16 targetAngleY = current.angle.y;
        if (mActionStatus == ACTION_ONGOING_1) {
            if (areaOutCheck()) {
                mActionStatus = ACTION_ONGOING_2;
                mC08 = 60;
                setAnm(ANM_WAIT1);
            } else {
                if (cLib_calcTimer(&mC0C) == 0) {
                    mC0C = cLib_getRndValue(10, 80);
                    setAnm(l_anm_type[cLib_getRndValue(0, (int)ARRAY_SIZE(l_anm_type)-2)]);
                }
                if (!npcTurnCheck(&targetAngleY) && cLib_calcTimer(&mC08) == 0) {
                    mActionStatus = ACTION_ONGOING_3;
                    mC08 = cLib_getRndValue(60, 60);
                    mC0A = l_turn_angleY[cLib_getRndValue(0, (int)ARRAY_SIZE(l_turn_angleY)-2)];
                }
            }
        } else if (mActionStatus == ACTION_ONGOING_2) {
            targetAngleY = cLib_targetAngleY(&current.pos, &home.pos);
            if (cLib_calcTimer(&mC08) == 0 && !areaOutCheck()) {
                mActionStatus = ACTION_ONGOING_1;
                setAnm(ANM_WAIT2);
                mC08 = cLib_getRndValue(90, 60);
            }
        } else if (mActionStatus == ACTION_ONGOING_3) {
            if (npcTurnCheck(&targetAngleY)) {
                mActionStatus = ACTION_ONGOING_1;
                mC08 = cLib_getRndValue(90, 60);
            } else {
                targetAngleY = mC0A;
                if (cLib_calcTimer(&mC08) == 0) {
                    mActionStatus = ACTION_ONGOING_1;
                    mC08 = cLib_getRndValue(90, 60);
                }
            }
        }
        
        if (mAnmIdx == ANM_SING && mpMorf->checkFrame(8.0f)) {
            fopAcM_seStart(this, JA_SE_CV_KAMOME, 0);
        }
        
        if (current.pos.y < home.pos.y) {
            targetAngleX = -l_HIO.mHio1.mGlidingAngVelX;
        }
        
        s16 angleDiffY = current.angle.y - targetAngleY;
        if (abs(angleDiffY) > 0x200) {
            cLib_addCalcAngleS(&current.angle.y, targetAngleY, 30, 0x2000, 0x100);
            shape_angle.y = current.angle.y;
            if (angleDiffY > l_HIO.mHio1.mMaxAngleZ) {
                angleDiffY = l_HIO.mHio1.mMaxAngleZ;
            } else if (angleDiffY < -l_HIO.mHio1.mMaxAngleZ) {
                angleDiffY = -l_HIO.mHio1.mMaxAngleZ;
            }
        }
        
        cLib_addCalcAngleS(&current.angle.x, targetAngleX, 8, 0x2000, 0x400);
        cLib_addCalcAngleS(&current.angle.z, angleDiffY, 8, 0x2000, 0x400);
        setAttention(true, 0);
    }
    
    return 1;
}

/* 00002AF4-00002C04       .text keyProc__11daNpc_kam_cFv */
BOOL daNpc_kam_c::keyProc() {
    if (cLib_calcTimer(&mFlapExhaustedTimer) == 0) {
        if (CPad_CHECK_TRIG_A(0)) {
            mFlapTimer = l_HIO.mHio1.mFlapDuration;
        }
        if (cLib_calcTimer(&mFlapTimer) != 0) {
            // Flapping.
            mTargetSpeedF = l_HIO.mHio1.mFlappingSpeedF;
            mTargetAngVelY = l_HIO.mHio1.mFlappingAngVelY;
            mTargetAngVelX = l_HIO.mHio1.mFlappingAngVelX;
            
            if (cLib_calcTimer(&mFlapEnergyTimer) == 0) {
                // If flapping for too long without rest, become exhausted.
                mFlapExhaustedTimer = l_HIO.mHio1.mFlapExhaustedDuration;
            }
        } else {
            // Gliding.
            mTargetSpeedF = l_HIO.mHio1.mSpeedF;
            mTargetAngVelY = l_HIO.mHio1.mGlidingAngVelY;
            mTargetAngVelX = l_HIO.mHio1.mGlidingAngVelX;
            
            // Gradually build up energy to flap while gliding.
            mFlapEnergyTimer++;
            if (mFlapEnergyTimer > l_HIO.mHio1.mFlapEnergyDuration) {
                mFlapEnergyTimer = l_HIO.mHio1.mFlapEnergyDuration;
            }
        }
    } else {
        mFlapTimer = 0;
        mFlapEnergyTimer = l_HIO.mHio1.mFlapEnergyDuration;
    }
    return TRUE;
}

/* 00002C04-00002F08       .text waitPlayerAction__11daNpc_kam_cFPv */
int daNpc_kam_c::waitPlayerAction(void*) {
    if (mActionStatus == ACTION_STARTING) {
        mActionStatus++; // ACTION_ONGOING_1
        onHyoiKamome();
        setAnm(ANM_WAIT1);
        speedF = l_HIO.mHio1.mSpeedF;
        mTargetSpeedF = l_HIO.mHio1.mSpeedF;
        mAngVelY = l_HIO.mHio1.mGlidingAngVelY;
        mAngVelX = l_HIO.mHio1.mGlidingAngVelX;
        mTargetAngVelY = l_HIO.mHio1.mGlidingAngVelY;
        mTargetAngVelX = l_HIO.mHio1.mGlidingAngVelX;
        mC08 = cLib_getRndValue(60, 90);
        mC0A = 0;
        mFlapTimer = 0;
        mFlapExhaustedTimer = 0;
        mFlapEnergyTimer = l_HIO.mHio1.mFlapEnergyDuration;
    } else if (mActionStatus == ACTION_ENDING) {
        offHyoiKamome();
    } else {
        keyProc();
        cLib_calcTimer(&mLockAngleXTimer);
        if (!dComIfGp_event_runCheck() && areaOutCheck()) {
            mEventState = 2;
        }
        
        s16 targetAngleZ = 0;
        s16 targetAngleY = 0;
        if (getStickAngY(&targetAngleY, &targetAngleZ)) {
            cLib_addCalcAngleS(&current.angle.y, targetAngleY, 8, 0x2000, 0x400);
        }
        shape_angle.y = current.angle.y;
        
        if (mLockAngleXTimer == 0) {
            mTargetAngleX = getAngleX();
        }
        
        cLib_addCalcAngleS(&current.angle.x, mTargetAngleX, 8, 0x2000, 0x400);
        cLib_addCalcAngleS(&current.angle.z, targetAngleZ, 8, 0x2000, 0x400);
        setAttention(true, 1);
        
        if (mAnmIdx != ANM_WAIT2) {
            if (mFlapTimer != 0) {
                setAnm(ANM_WAIT2);
            } else {
                if (cLib_calcTimer(&mC08) == 0) {
                    mC08 = cLib_getRndValue(90, 90);
                    setAnm(ANM_SING);
                }
            }
            
            if (mAnmIdx == ANM_SING) {
                if (mReachedAnimEnd) {
                    setAnm(ANM_WAIT1);
                }
                
                if (mAnmIdx == ANM_SING && mpMorf->checkFrame(8.0f)) {
                    fopAcM_seStart(this, JA_SE_CV_KAMOME, 0);
                }
            }
        } else if (mReachedAnimEnd && mFlapTimer == 0) {
            setAnm(ANM_SING);
        }
        
        if (mTgSph.ChkTgHit()) {
            setPlayerAction(&damagePlayerAction, NULL);
        }
    }
    return TRUE;
}

/* 00002F08-00003058       .text damagePlayerAction__11daNpc_kam_cFPv */
BOOL daNpc_kam_c::damagePlayerAction(void*) {
    if (mActionStatus == ACTION_STARTING) {
        dComIfGp_getVibration().StartShock(5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        setDamageFogTimer(150);
        mActionStatus++; // ACTION_ONGOING_1
        onHyoiKamome();
        setAnm(ANM_WAIT1);
        speedF = 0.0f;
        fopAcM_seStart(this, JA_SE_CV_KAMOME, 0);
        mC08 = 30;
    } else if (mActionStatus == ACTION_ENDING) {
        offHyoiKamome();
    } else {
        shape_angle.y += 0x2000;
        current.angle.y = shape_angle.y;
        setAttention(true, 1);
        if (cLib_calcTimer(&mC08) == 0) {
            returnLink();
        }
    }
    return TRUE;
}

/* 00003058-0000315C       .text eventOrder__11daNpc_kam_cFv */
void daNpc_kam_c::eventOrder() {
    if (isEventAccept()) {
        return;
    }
    if (mEventState == 5 || mEventState == 4) {
        if (dComIfGp_getPlayer(0) != this) {
            eventInfo.onCondition(dEvtCnd_CANTALK_e);
            if (mEventState == 5) {
                fopAcM_orderSpeakEvent(this);
            }
        } else {
            mEventState = -1;
        }
    } else if (mEventState == 6) {
        if (dComIfGp_getPlayer(0) != this) {
            eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
            eventInfo.onCondition(dEvtCnd_CANTALK_e);
        } else {
            mEventState = -1;
        }
    } else if (mEventState != -1 && mEventState < 3) {
        mCurrEventIdxIdx = mEventState;
        fopAcM_orderOtherEventId(this, mEventIdxs[mCurrEventIdxIdx]);
    }
}

/* 0000315C-00003194       .text checkOrder__11daNpc_kam_cFv */
void daNpc_kam_c::checkOrder() {
    if (!eventInfo.checkCommandTalk()) {
        return;
    }
    if (mEventState != 5 && mEventState != 4 && mEventState != 6) {
        return;
    }
    mEventState = -1;
}

/* 00003194-00003200       .text checkCommandTalk__11daNpc_kam_cFv */
BOOL daNpc_kam_c::checkCommandTalk() {
    if (eventInfo.checkCommandTalk()) {
        if (dComIfGp_event_chkTalkXY()) {
            if (mEventState == 6) {
                mEventState = -1;
            }
            return FALSE;
        }
        return TRUE;
    }
    return FALSE;
}

/* 00003200-00003248       .text returnLinkPlayer__11daNpc_kam_cFv */
void daNpc_kam_c::returnLinkPlayer() {
    changePlayer(dComIfGp_getLinkPlayer());
    offHyoiKamome();
#if VERSION != VERSION_JPN
    mDoAud_zelAudio_c::getInterface()->field_0x0062 = 0;
#endif
}

static daNpc_kam_c::EventActionInitFunc event_init_tbl[] = {
    &daNpc_kam_c::initialWaitEvent,
    &daNpc_kam_c::initialChangeEvent,
    &daNpc_kam_c::initialDescendEvent,
    &daNpc_kam_c::initialAreaOutTurn,
};

static daNpc_kam_c::EventActionFunc event_action_tbl[] = {
    &daNpc_kam_c::actionWaitEvent,
    &daNpc_kam_c::actionDefault,
    &daNpc_kam_c::actionDescendEvent,
    &daNpc_kam_c::actionAreaOutTurn,
};

static char* cut_name_tbl[] = {
    "wait",
    "change",
    "descend",
    "out_turn",
};

/* 00003248-000034A8       .text eventProc__11daNpc_kam_cFv */
BOOL daNpc_kam_c::eventProc() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (mEventState != -1) {
            if (mEventState == 0) {
                if (dComIfGp_evmng_startCheck("OPTION_CHAR_END") || dComIfGp_evmng_endCheck("OPTION_CHAR_END")) {
                    dComIfGp_event_setTalkPartner(dComIfGp_getLinkPlayer());
                    mDoAud_seStart(JA_SE_CTRL_NPC_TO_LINK);
                } else {
                    offReturnLink();
                    mEventState = -1;
                }
            }
            if (mEventState != -1) {
                onEventAccept();
                mEventState = -1;
            }
        }
    }
    
    int staffId = dComIfGp_evmng_getMyStaffId(l_staff_name);
    if (dComIfGp_event_runCheck() && !checkCommandTalk()) {
        if (staffId != -1) {
            int actIdx = dComIfGp_evmng_getMyActIdx(staffId, cut_name_tbl, ARRAY_SIZE(cut_name_tbl), 1, 0);
            if (actIdx == -1) {
                dComIfGp_evmng_cutEnd(staffId);
            } else {
                if (dComIfGp_evmng_getIsAddvance(staffId)) {
                    (this->*event_init_tbl[actIdx])(staffId);
                }
                if ((this->*event_action_tbl[actIdx])(staffId)) {
                    dComIfGp_evmng_cutEnd(staffId);
                }
            }
        }
        
        if (isEventAccept()) {
            if (dComIfGp_evmng_endCheck(mEventIdxs[mCurrEventIdxIdx])) {
                eventEnd();
            }
            return TRUE;
        } else {
            return TRUE;
        }
    }
    
    return FALSE;
}

/* 000034A8-00003514       .text eventEnd__11daNpc_kam_cFv */
void daNpc_kam_c::eventEnd() {
    dComIfGp_event_reset();
    offEventAccept();
    
    if (mCurrEventIdxIdx == 0) { // "OPTION_CHAR_END"
        returnLinkPlayer();
        offReturnLink();
    }
    mCurrEventIdxIdx = -1;
}

/* 00003514-0000351C       .text actionDefault__11daNpc_kam_cFi */
BOOL daNpc_kam_c::actionDefault(int evtStaffId) {
    return TRUE;
}

/* 0000351C-00003580       .text initialWaitEvent__11daNpc_kam_cFi */
void daNpc_kam_c::initialWaitEvent(int evtStaffId) {
    u32* timerP = dComIfGp_evmng_getMyIntegerP(evtStaffId, "timer");
    if (timerP) {
        mWaitTimer = *timerP;
    } else {
        mWaitTimer = 0;
    }
}

/* 00003580-000035C8       .text actionWaitEvent__11daNpc_kam_cFi */
BOOL daNpc_kam_c::actionWaitEvent(int evtStaffId) {
    setAttention(true, 1);
    return cLib_calcTimer(&mWaitTimer) == 0 ? TRUE : FALSE;
}

/* 000035C8-0000361C       .text initialChangeEvent__11daNpc_kam_cFi */
void daNpc_kam_c::initialChangeEvent(int evtStaffId) {
    fopAcM_SetRoomNo(this, fopAcM_GetHomeRoomNo(this));
    changePlayer(this);
    dComIfGs_setBaitItemEmpty();
    offNoBgCheck();
}

/* 0000361C-00003730       .text initialDescendEvent__11daNpc_kam_cFi */
void daNpc_kam_c::initialDescendEvent(int evtStaffId) {
    current.pos = mDescendStartPos;
    current.angle = mDescendStartAngle;
    shape_angle = current.angle;
    
    mTargetSpeedF = speedF = l_HIO.mHio1.mSpeedF;
    mAngVelY = l_HIO.mHio1.mGlidingAngVelY;
    mAngVelX = l_HIO.mHio1.mGlidingAngVelX;
    mTargetAngVelY = l_HIO.mHio1.mGlidingAngVelY;
    mTargetAngVelX = l_HIO.mHio1.mGlidingAngVelX;
    
    mDoAud_seStart(JA_SE_HYOI_USE_DEMO, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
#if VERSION != VERSION_JPN
    mDoAud_zelAudio_c::getInterface()->field_0x0062 = 1;
#endif
    
    onNoBgCheck();
    
    mWaitTimer = 30*30;
}

// Needed for the .rodata section to match.
static const f32 dummy5[] = {40.0f};

/* 00003730-00003864       .text actionDescendEvent__11daNpc_kam_cFi */
BOOL daNpc_kam_c::actionDescendEvent(int evtStaffId) {
    daPy_lk_c* link = daPy_getPlayerLinkActorClass();
    cXyz linkHeadTopPos = link->getHeadTopPos();
    linkHeadTopPos.y += 20.0f;
    
    setAttention(true, 1);
    
    if (current.pos.y < linkHeadTopPos.y) {
        current.pos.y = linkHeadTopPos.y;
    }
    if (current.pos.y < linkHeadTopPos.y + 50.0f) {
        cLib_addCalcAngleS(&current.angle.x, 0, 30, 0x2000, 0x400);
        shape_angle.x = current.angle.x;
    }
    
    cXyz delta = linkHeadTopPos - current.pos;
    if (delta.abs2XZ() < 100.0f*100.0f) {
        return TRUE;
    }
    
    return cLib_calcTimer(&mWaitTimer) == 0 ? TRUE : FALSE;
}

/* 00003864-00003884       .text initialAreaOutTurn__11daNpc_kam_cFi */
void daNpc_kam_c::initialAreaOutTurn(int evtStaffId) {
    mWaitTimer = 10;
    mAreaOutTimer = 180*30;
    current.angle.x = 0;
    current.angle.z = 0;
}

/* 00003884-000039E8       .text actionAreaOutTurn__11daNpc_kam_cFi */
BOOL daNpc_kam_c::actionAreaOutTurn(int evtStaffId) {
    if (cLib_calcTimer(&mWaitTimer) == 0) {
        onNoBgCheck();
        speedF = 0.0f;
        
        s16 targetAngle = cLib_targetAngleY(&current.pos, &home.pos);
        s16 angleDiff = current.angle.y - targetAngle;
        if (abs(angleDiff) != 0) {
            cLib_addCalcAngleS(&current.angle.y, targetAngle, 16, 0x2000, 0x400);
        } else {
            speedF = l_HIO.mHio1.mSpeedF;
        }
        shape_angle.y = current.angle.y;
        
        current.angle.z = angleDiff;
        if (current.angle.z > l_HIO.mHio1.mMaxAngleZ) {
            current.angle.z = l_HIO.mHio1.mMaxAngleZ;
        } else if (current.angle.z < -l_HIO.mHio1.mMaxAngleZ) {
            current.angle.z = -l_HIO.mHio1.mMaxAngleZ;
        }
        
        if (!areaOutCheck()) {
            offNoBgCheck();
            return TRUE;
        }
    }
    
    cLib_addCalcAngleS(&shape_angle.x, current.angle.x, 8, 0x2000, 0x400);
    cLib_addCalcAngleS(&shape_angle.z, current.angle.z, 8, 0x2000, 0x400);
    
    setAttention(true, 1);
    
    return cLib_calcTimer(&mAreaOutTimer) == 0 ? TRUE : FALSE;
}

struct anmPrm_c {
    /* 0x00 */ s8 mAnmTblIdx;
    /* 0x04 */ int mLoopMode;
    /* 0x08 */ f32 mMorf;
    /* 0x0C */ f32 mPlaySpeed;
    /* 0x10 */ int m10;
};
struct anmTbl_c {
    /* 0x00 */ s8 mBckFileIdx;
    /* 0x01 */ s8 mSoundFileIdx;
};

/* 000039E8-00003B14       .text setAnm__11daNpc_kam_cFi */
void daNpc_kam_c::setAnm(int anmIdx) {
    static anmTbl_c l_anmTbl[] = {
        {KAMOME_BCK_KA_WAIT1, KAMOME_BAS_KA_WAIT1},
        {KAMOME_BCK_KA_WAIT2, KAMOME_BAS_KA_WAIT2},
        {KAMOME_BCK_KA_SING1, -1},
    };
    static anmPrm_c l_anmPrm[] = {
        {
            /* mAnmTblIdx */ 0,
            /* mLoopMode  */ J3DFrameCtrl::LOOP_REPEAT_e,
            /* mMorf      */ 8.0f,
            /* mPlaySpeed */ 1.0f,
            /* m10        */ 0,
        },
        {
            /* mAnmTblIdx */ 1,
            /* mLoopMode  */ J3DFrameCtrl::LOOP_REPEAT_e,
            /* mMorf      */ 8.0f,
            /* mPlaySpeed */ 1.0f,
            /* m10        */ 0,
        },
        {
            /* mAnmTblIdx */ 2,
            /* mLoopMode  */ J3DFrameCtrl::LOOP_ONCE_e,
            /* mMorf      */ 8.0f,
            /* mPlaySpeed */ 1.0f,
            /* m10        */ 0,
        },
    };
    
    mAnmIdx = anmIdx;
    anmPrm_c* anmPrm = &l_anmPrm[anmIdx];
    
    f32 playSpeed = anmPrm->mPlaySpeed;
    
    if (anmPrm->mAnmTblIdx == mAnmTblIdx && anmPrm->mPlaySpeed == mpMorf->getPlaySpeed()) {
        return;
    }
    
    mAnmTblIdx = anmPrm->mAnmTblIdx;
    anmTbl_c* anmTbl = &l_anmTbl[mAnmTblIdx];
    
    mPrevMorfFrame = 0.0f;
    mReachedAnimEnd = false;
    dNpc_setAnm(
        mpMorf, anmPrm->mLoopMode,
        anmPrm->mMorf, playSpeed,
        anmTbl->mBckFileIdx, anmTbl->mSoundFileIdx,
        "Kamome"
    );
    
    if (anmPrm->m10 < 0) {
        mpMorf->setFrame(mpMorf->getEndFrame());
    }
}

/* 00003B14-00003C80       .text setCollision__11daNpc_kam_cFv */
void daNpc_kam_c::setCollision() {
    MtxP mtx = mpMorf->getModel()->getAnmMtx(m_jnt_body);
    cXyz center;
    center.set(mtx[0][3], mtx[1][3], mtx[2][3]);
    
    mAtSph.SetC(center);
    dComIfG_Ccsp()->Set(&mAtSph);
    
    mTgSph.SetC(center);
    dComIfG_Ccsp()->Set(&mTgSph);
    
    mDoMtx_stack_c::ZXYrotS(shape_angle);
    cXyz at_global_start;
    cXyz at_global_end;
    cXyz at_global_vec;
    mDoMtx_stack_c::multVec(&l_ms_at_local_start, &at_global_start);
    mDoMtx_stack_c::multVec(&l_ms_at_local_end, &at_global_end);
    mDoMtx_stack_c::multVecSR(&l_ms_at_local_vec, &at_global_vec);
    at_global_start += center;
    at_global_end += center;
    
    mCps.SetStartEnd(at_global_start, at_global_end);
    mCps.SetAtVec(at_global_vec);
    dComIfG_Ccsp()->Set(&mCps);
}

/* 00003C80-00003E4C       .text setLineBgCheck__11daNpc_kam_cFv */
void daNpc_kam_c::setLineBgCheck() {
    offLineHit();
    csXyz lineAngle = shape_angle;
    cXyz lineEndPos;
    
    mDoMtx_stack_c::ZXYrotS(lineAngle);
    mDoMtx_stack_c::multVec(&l_line_bg_local_end, &lineEndPos);
    lineEndPos += current.pos;
    mLinChk.Set(&current.pos, &lineEndPos, this);
    if (dComIfG_Bgsp()->LineCross(&mLinChk)) {
        onFrontLineHit();
    }
    
    lineAngle.y = shape_angle.y + 0x2000;
    mDoMtx_stack_c::ZXYrotS(lineAngle);
    mDoMtx_stack_c::multVec(&l_line_bg_local_end, &lineEndPos);
    lineEndPos += current.pos;
    mLinChk.Set(&current.pos, &lineEndPos, this);
    if (dComIfG_Bgsp()->LineCross(&mLinChk)) {
        onLeftLineHit();
    }
    
    lineAngle.y = shape_angle.y - 0x2000;
    mDoMtx_stack_c::ZXYrotS(lineAngle);
    mDoMtx_stack_c::multVec(&l_line_bg_local_end, &lineEndPos);
    lineEndPos += current.pos;
    mLinChk.Set(&current.pos, &lineEndPos, this);
    if (dComIfG_Bgsp()->LineCross(&mLinChk)) {
        onRightLineHit();
    }
}

/* 00003E4C-00003F2C       .text animationPlay__11daNpc_kam_cFv */
void daNpc_kam_c::animationPlay() {
    u32 mtrlSndId = 0;
    if (mAcch.ChkGroundHit() && dComIfG_Bgsp()->ChkPolySafe(mAcch.m_gnd)) {
        mtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(mAcch.m_gnd);
    }
    
    mReachedAnimEnd = mpMorf->play(&eyePos, mtrlSndId, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
    
    f32 frame = mpMorf->getFrame();
    if (mpMorf->getPlaySpeed() < 0.0f) {
        if (frame > mPrevMorfFrame) {
            mReachedAnimEnd = true;
        }
    } else if (frame < mPrevMorfFrame) {
        mReachedAnimEnd = true;
    }
    
    mPrevMorfFrame = frame;
}

/* 00003F2C-0000445C       .text execute__11daNpc_kam_cFv */
BOOL daNpc_kam_c::execute() {
    l_demo_start_chk_cnt = 0;
    
    static JGeometry::TVec3<f32> splash_scale(0.6f, 0.6f, 0.6f);
    static JGeometry::TVec3<f32> ripple_scale(1.0f, 1.0f, 1.0f);
    
    fopAcM_OffStatus(this, fopAcStts_SHOWMAP_e);
    executeDamageFog();
    
    if (!isReturnLink()) {
        if (checkNowPosMove(l_staff_name)) {
            mAccelF = l_HIO.mHio1.mAccelF;
            
            if (speedF < mTargetSpeedF) {
                speedF += mAccelF;
                if (speedF > mTargetSpeedF) {
                    speedF = mTargetSpeedF;
                }
            } else if (speedF > mTargetSpeedF) {
                speedF -= mAccelF;
                if (speedF < mTargetSpeedF) {
                    speedF = mTargetSpeedF;
                }
            }
            
            cLib_addCalcAngleS(&mAngVelY, mTargetAngVelY, l_HIO.mHio1.mAngVelStepScale, l_HIO.mHio1.mAngVelMaxStep, l_HIO.mHio1.mAngVelMinStep);
            cLib_addCalcAngleS(&mAngVelX, mTargetAngVelX, l_HIO.mHio1.mAngVelStepScale, l_HIO.mHio1.mAngVelMaxStep, l_HIO.mHio1.mAngVelMinStep);
            
            f32 cosXSpeed = speedF * cM_scos(current.angle.x);
            speed.y = speedF * -cM_ssin(current.angle.x);
            speed.x = cosXSpeed * cM_ssin(current.angle.y);
            speed.z = cosXSpeed * cM_scos(current.angle.y);
            
            fopAcM_posMove(this, mStts.GetCCMoveP());
        }
        
        if (!isNoBgCheck()) {
            mAcch.CrrPos(*dComIfG_Bgsp());
            if (mAcch.GetGroundH() != -1000000000.0f) {
                s8 roomNo = dComIfG_Bgsp()->GetRoomId(mAcch.m_gnd);
                fopAcM_SetRoomNo(this, roomNo);
                tevStr.mRoomNo = roomNo;
                tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mAcch.m_gnd);
                mStts.SetRoomId(roomNo);
                mPolyInfo.SetPolyInfo(mAcch.m_gnd);
            }
            
            if (mAcch.ChkSeaIn()) {
                if (!isWaterHit()) {
                    onWaterHit();
                    
                    JPABaseEmitter* splashEmitter = dComIfGp_particle_set(0x40, &current.pos);
                    if (splashEmitter) {
                        splashEmitter->setRate(15.0f);
                        splashEmitter->setGlobalScale(splash_scale);
                    }
                    
                    JPABaseEmitter* rippleEmitter = dComIfGp_particle_setSingleRipple(0x3D, &current.pos);
                    if (rippleEmitter) {
                        rippleEmitter->setGlobalScale(ripple_scale);
                    }
                }
            } else {
                offWaterHit();
            }
        }
        
        setLineBgCheck();
        
        if (checkNowPosMove(l_staff_name)) {
            animationPlay();
        }
    }
    
    BOOL inEvent = eventProc();
    
    if (!inEvent) {
        if (dComIfGp_getPlayer(0) == this) {
            fopAcM_SetStatusMap(this, 0x14);
            
            if (isReturnLink()) {
                mEventState = 0;
            } else {
                playerAction(NULL);
                if (returnLinkCheck()) {
                    returnLink();
                }
            }
        } else {
            checkOrder();
            npcAction(NULL);
        }
        
        cLib_addCalcAngleS(&shape_angle.x, current.angle.x, 8, 0x2000, 0x400);
        cLib_addCalcAngleS(&shape_angle.z, current.angle.z, 8, 0x2000, 0x400);
    }
    
    eventOrder();
    setBaseMtx();
    
    if (!inEvent && dComIfGp_getPlayer(0) == this) {
        setCollision();
    }
    
    mAtSph.ClrCoHit();
    mTgSph.ClrTgHit();
    mCps.ClrAtHit();
    mStts.ClrCcMove();
    
    return TRUE;
}

/* 0000445C-00004548       .text draw__11daNpc_kam_cFv */
BOOL daNpc_kam_c::draw() {
    J3DModel* model = mpMorf->getModel();
    
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    
    drawDamageFog();
    
    g_env_light.setLightTevColorType(model, &tevStr);
    
    mpMorf->entryDL();
    
    cXyz shadowPos(current.pos.x, current.pos.y, current.pos.z);
    mShadowId = dComIfGd_setShadow(
        mShadowId, 1, model, &shadowPos, 800.0f, 20.0f,
        current.pos.y, mAcch.GetGroundH(), mAcch.m_gnd, &tevStr,
        0, 1.0f, dDlst_shadowControl_c::getSimpleTex()
    );
    
    dSnap_RegistFig(DSNAP_TYPE_KAMOME, this, 1.0f, 1.0f, 1.0f);
    
    return TRUE;
}

/* 00004548-00004568       .text daNpc_kam_Draw__FP11daNpc_kam_c */
static BOOL daNpc_kam_Draw(daNpc_kam_c* i_this) {
    return i_this->draw();
}

/* 00004568-00004588       .text daNpc_kam_Execute__FP11daNpc_kam_c */
static BOOL daNpc_kam_Execute(daNpc_kam_c* i_this) {
    return i_this->execute();
}

/* 00004588-00004590       .text daNpc_kam_IsDelete__FP11daNpc_kam_c */
static BOOL daNpc_kam_IsDelete(daNpc_kam_c* i_this) {
    return TRUE;
}

/* 00004590-000045B8       .text daNpc_kam_Delete__FP11daNpc_kam_c */
static BOOL daNpc_kam_Delete(daNpc_kam_c* i_this) {
    i_this->~daNpc_kam_c();
    return TRUE;
}

/* 000045B8-000045D8       .text daNpc_kam_Create__FP10fopAc_ac_c */
static s32 daNpc_kam_Create(fopAc_ac_c* i_this) {
    return ((daNpc_kam_c*)i_this)->create();
}

static actor_method_class l_daNpc_kam_Method = {
    (process_method_func)daNpc_kam_Create,
    (process_method_func)daNpc_kam_Delete,
    (process_method_func)daNpc_kam_Execute,
    (process_method_func)daNpc_kam_IsDelete,
    (process_method_func)daNpc_kam_Draw,
};

actor_process_profile_definition g_profile_NPC_KAM = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 7,
    /* ListPrio     */ fpcLy_CURRENT_e,
    /* ProcName     */ PROC_NPC_KAM,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_kam_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x00B6,
    /* Actor SubMtd */ &l_daNpc_kam_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLSPHERE_2_e,
};
