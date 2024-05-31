//
// Generated by dtk
// Translation Unit: d_a_npc_btsw2.cpp
//

#include "d/actor/d_a_npc_btsw2.h"
#include "d/res/res_btsw.h"
#include "d/d_com_inf_game.h"
#include "d/d_item.h"
#include "d/d_procname.h"
#include "d/d_snap.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"

// Needed for the .data section to match.
static f32 dummy1[3] = {1.0f, 1.0f, 1.0f};
static f32 dummy2[3] = {1.0f, 1.0f, 1.0f};
static u8 dummy3[4] = {0x02, 0x00, 0x02, 0x01};
static f64 dummy4[2] = {3.0, 0.5};

static u8 dummy[0x4C];

static daNpc_Btsw2_HIO_c l_HIO;

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ ~(AT_TYPE_BOOMERANG),
        /* SrcObjTg  SPrm    */ TG_SPRM_SET | TG_SPRM_IS_ENEMY,
        /* SrcObjCo  SPrm    */ CO_SPRM_SET | CO_SPRM_IS_UNK4 | CO_SPRM_VSGRP,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ G_TG_SPRM_NO_HIT_MARK,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 30.0f,
        /* Height */ 80.0f,
    },
};

/* 000000EC-000001A8       .text __ct__17daNpc_Btsw2_HIO_cFv */
daNpc_Btsw2_HIO_c::daNpc_Btsw2_HIO_c() {
    mNpc.m04 = 0.0f;
    mNpc.mMaxHeadX = 0x1F40;
    mNpc.mMaxHeadY = 0x1F40;
    mNpc.mMaxBackboneX = 0x0;
    mNpc.mMaxBackboneY = 0x1F40;
    mNpc.mMinHeadX = -0xBB8;
    mNpc.mMinHeadY = -0x1F40;
    mNpc.mMinBackboneX = 0x0;
    mNpc.mMinBackboneY = -0x1F40;
    mNpc.mMaxTurnStep = 0x3E8;
    mNpc.mMaxHeadTurnVel = 0x640;
    mNpc.mAttnYOffset = 40.0f;
    mNpc.mMaxAttnAngleY = 0x2000;
    mNpc.m22 = 0x0;
    mNpc.mMaxAttnDistXZ = 200.0f;
    m30 = 0x258;
    m32 = 0x5;
    m34 = 0.8f;
    m38 = 0.95f;
    m3C = 0x5A;
    m3E = 0x5A;
    mChildID = -1;
}

const char daNpc_Btsw2_c::m_arc_name[] = "Btsw";

static const int l_bck_ix_tbl[] = {
    BTSW_INDEX_BCK_BN_WAIT01,
    BTSW_INDEX_BCK_BN_WAIT02,
    BTSW_INDEX_BCK_BN_TALK01,
    BTSW_INDEX_BCK_BN_TALK02,
    BTSW_INDEX_BCK_BN_ONEGAI,
    BTSW_INDEX_BCK_BN_SUGOI,
    BTSW_INDEX_BCK_BN_SUGOI,
    BTSW_INDEX_BCK_BN_WALK,
    BTSW_INDEX_BCK_BN_KASIGE,
    BTSW_INDEX_BCK_BN_SIWAKE01,
    BTSW_INDEX_BCK_BN_SIWAKE02,
};

static const int l_btp_ix_tbl[] = {
    BTSW_INDEX_BTP_BN_MABA,
};

/* 000001A8-000003E0       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int param_1) {
    if (!param_1) {
        J3DModel* model = j3dSys.getModel();
        J3DJoint* joint = (J3DJoint*)node;
        daNpc_Btsw2_c* i_this = (daNpc_Btsw2_c*)model->getUserArea();
        if (i_this) {
            static cXyz a_att_pos_offst(0.0f, 0.0f, 0.0f);
            static cXyz a_eye_pos_offst(10.0f, 20.0f, 0.0f);
            u16 jointNo = joint->getJntNo();
            mDoMtx_stack_c::copy(model->getAnmMtx(jointNo));
            if (jointNo == i_this->m_jnt.getHeadJntNum()) {
                mDoMtx_stack_c::multVec(&a_att_pos_offst, &i_this->mAttPos);
                Mtx sp14;
                cMtx_copy(mDoMtx_stack_c::get(), sp14);
                cXyz sp8;
                mDoMtx_multVecZero(sp14, &sp8);
                sp14[0][3] = sp14[1][3] = sp14[2][3] = 0.0f;
                mDoMtx_stack_c::transS(sp8);
                mDoMtx_stack_c::YrotM(i_this->current.angle.y + i_this->m_jnt.getHead_y());
                mDoMtx_stack_c::XrotM(-i_this->m_jnt.getHead_x());
                mDoMtx_stack_c::YrotM(-i_this->current.angle.y);
                mDoMtx_stack_c::concat(sp14);
                mDoMtx_stack_c::multVec(&a_eye_pos_offst, &i_this->eyePos);
            } else if (jointNo == i_this->m_jnt.getBackboneJntNum()) {
                mDoMtx_stack_c::XrotM(i_this->m_jnt.getBackbone_y());
                mDoMtx_stack_c::ZrotM(-i_this->m_jnt.getBackbone_x());
            }
            cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
            model->setAnmMtx(jointNo, mDoMtx_stack_c::get());
        }
    }
    return TRUE;
}

/* 0000041C-00000524       .text initTexPatternAnm__13daNpc_Btsw2_cFb */
BOOL daNpc_Btsw2_c::initTexPatternAnm(bool i_modify) {
    J3DModelData* modelData = mpMorf->getModel()->getModelData();
    m_btp = static_cast<J3DAnmTexPattern*>(dComIfG_getObjectRes(m_arc_name, l_btp_ix_tbl[m744]));
    JUT_ASSERT(282, m_btp != 0);
    if (!mBtpAnm.init(modelData, m_btp, TRUE, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, i_modify, 0)) {
        return FALSE;
    }
    mBtpFrame = 0;
    mBlinkTimer = 0;
    return TRUE;
}

/* 00000524-000005B0       .text playTexPatternAnm__13daNpc_Btsw2_cFv */
void daNpc_Btsw2_c::playTexPatternAnm() {
    if (cLib_calcTimer(&mBlinkTimer) == 0) {
        if (mBtpFrame >= m_btp->getFrameMax()) {
            mBtpFrame -= m_btp->getFrameMax();
            mBlinkTimer = 30 + cM_rndF(100.0f);
        } else {
            mBtpFrame++;
        }
    }
}

/* 000005B0-0000067C       .text setAnm__13daNpc_Btsw2_cFSc */
void daNpc_Btsw2_c::setAnm(s8 param_0) {
    static int a_play_mode_tbl[] = {
        J3DFrameCtrl::LOOP_REPEAT_e,
        J3DFrameCtrl::LOOP_REPEAT_e,
        J3DFrameCtrl::LOOP_REPEAT_e,
        J3DFrameCtrl::LOOP_REPEAT_e,
        J3DFrameCtrl::LOOP_ONCE_e,
        J3DFrameCtrl::LOOP_REPEAT_e,
        J3DFrameCtrl::LOOP_REPEAT_e,
        J3DFrameCtrl::LOOP_REPEAT_e,
        J3DFrameCtrl::LOOP_ONCE_e,
        J3DFrameCtrl::LOOP_REPEAT_e,
        J3DFrameCtrl::LOOP_ONCE_e,
    };
    static f32 a_morf_frame_tbl[] = {
        8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f,
    };
    static f32 a_play_speed_tbl[] = {
        1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    };
    
    if (param_0 == m745) {
        return;
    }
    if (m745 == -1) {
        return;
    }
    
    m745 = param_0;
    
    dNpc_setAnm(
        mpMorf, a_play_mode_tbl[m747],
        a_morf_frame_tbl[m747], a_play_speed_tbl[m747],
        l_bck_ix_tbl[m745], -1,
        m_arc_name
    );
    
    if (m745 == 7 || m745 == 8) {
        m_jnt.onHeadLock();
    } else {
        m_jnt.offHeadLock();
    }
}

/* 0000067C-000007D0       .text chkAttention__13daNpc_Btsw2_cF4cXyzs */
bool daNpc_Btsw2_c::chkAttention(cXyz pos, s16 facingAngleY) {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    f32 maxAttnDistXZ = l_HIO.mNpc.mMaxAttnDistXZ;
    int maxAttnAngleY = l_HIO.mNpc.mMaxAttnAngleY;
    cXyz delta;
    delta.x = player->current.pos.x - pos.x;
    delta.z = player->current.pos.z - pos.z;
    f32 distXZ = sqrtf(delta.x*delta.x + delta.z*delta.z);
    s16 targetAngleY = cM_atan2s(delta.x, delta.z);
    if (mHasAttention) {
        // Increase the attention range when we're already looking at the player so it sticks slightly out of range.
        maxAttnDistXZ += 40.0f;
        maxAttnAngleY += cAngle::d2s(10.0f);
    }
    targetAngleY -= facingAngleY;
    return maxAttnAngleY > abs(targetAngleY) && maxAttnDistXZ > distXZ;
}

/* 000007D0-00000820       .text eventOrder__13daNpc_Btsw2_cFv */
void daNpc_Btsw2_c::eventOrder() {
    if (m746 == 1 || m746 == 2) {
        eventInfo.onCondition(dEvtCmd_INTALK_e);
        if (m746 == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    }
}

/* 00000820-00000860       .text checkOrder__13daNpc_Btsw2_cFv */
void daNpc_Btsw2_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        return;
    }
    if (eventInfo.checkCommandTalk()) {
        if (m746 == 1 || m746 == 2) {
            m746 = 0;
            m71E = true;
        }
    }
}

/* 00000860-0000097C       .text anmAtr__13daNpc_Btsw2_cFUs */
void daNpc_Btsw2_c::anmAtr(u16) {
    switch (dComIfGp_getMesgAnimeAttrInfo()) {
    case 0:
        setAnm(0);
        break;
    case 1:
        setAnm(1);
        break;
    case 2:
        setAnm(2);
        break;
    case 3:
        setAnm(3);
        break;
    case 4:
        setAnm(4);
        break;
    case 5:
        setAnm(5);
        break;
    case 6:
        setAnm(6);
        break;
    }
    
    if (mpMorf->checkFrame(mpMorf->getEndFrame()-1.0f)) {
        if (m745 == 4 || m745 == 6) {
            setAnm(1);
        }
    }
    
    dComIfGp_clearMesgAnimeAttrInfo();
}

/* 0000097C-000009EC       .text getMsg__13daNpc_Btsw2_cFv */
u32 daNpc_Btsw2_c::getMsg() {
    u32 msgNo;
    if (!dComIfGs_isEventBit(0x3102)) {
        dComIfGs_onEventBit(0x3102);
        msgNo = 0x1AB0;
    } else if (dKy_daynight_check()) {
        msgNo = 0x1AB2;
    } else {
        msgNo = 0x1AB1;
    }
    return msgNo;
}

/* 000009EC-000009F4       .text next_msgStatus__13daNpc_Btsw2_cFPUl */
u16 daNpc_Btsw2_c::next_msgStatus(u32*) {
    return fopMsgStts_MSG_ENDS_e;
}

/* 000009F4-00000A20       .text setAttention__13daNpc_Btsw2_cFv */
void daNpc_Btsw2_c::setAttention() {
    attention_info.position.set(mAttPos.x, mAttPos.y + l_HIO.mNpc.mAttnYOffset, mAttPos.z);
}

/* 00000A20-00000B94       .text lookBack__13daNpc_Btsw2_cFv */
void daNpc_Btsw2_c::lookBack() {
    cXyz sp38;
    cXyz sp2c;
    sp2c.setall(0.0f);
    cXyz* r31 = NULL;
    s16 r30 = current.angle.y;
    bool r29 = true;
    
    switch (m747) {
    case 1:
    case 2:
        if (m747 == 2) {
            r29 = false;
            m_jnt.setTrn();
            if (!mHasAttention) {
                sp38 = dNpc_playerEyePos(l_HIO.mNpc.m04);
                s16 r4 = cLib_targetAngleY(&current.pos, &sp38);
                cLib_addCalcAngleS2(&current.angle.y, r4, 4, 0x1800);
            }
        }
        if (mHasAttention) {
            sp38 = dNpc_playerEyePos(l_HIO.mNpc.m04);
            r31 = &sp38;
            sp2c = current.pos;
            sp2c.y = eyePos.y;
        }
        break;
    }
    
    m_jnt.lookAtTarget(&current.angle.y, r31, sp2c, r30, l_HIO.mNpc.mMaxHeadTurnVel, r29);
}

/* 00000B94-00000BB4       .text CallbackCreateHeap__FP10fopAc_ac_c */
static BOOL CallbackCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Btsw2_c*>(i_this)->CreateHeap();
}

/* 00000BB4-00000EFC       .text CreateHeap__13daNpc_Btsw2_cFv */
BOOL daNpc_Btsw2_c::CreateHeap() {
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arc_name, BTSW_INDEX_BDL_BN));
    JUT_ASSERT(616, modelData != 0);
    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL, NULL,
        static_cast<J3DAnmTransform*>(dComIfG_getObjectRes(m_arc_name, BTSW_INDEX_BCK_BN_WAIT01)),
        J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, 1, NULL, 0x80000, 0x15020022
    );
    if (mpMorf == NULL || mpMorf->getModel() == NULL) {
        return FALSE;
    }
    
    m_jnt.setHeadJntNum(modelData->getJointName()->getIndex("head"));
    JUT_ASSERT(634, m_jnt.getHeadJntNum() >= 0);
    m_jnt.setBackboneJntNum(modelData->getJointName()->getIndex("backbone"));
    JUT_ASSERT(639, m_jnt.getBackboneJntNum() >= 0);
    m_handL_jnt_num = modelData->getJointName()->getIndex("handL");
    m_handR_jnt_num = modelData->getJointName()->getIndex("handR");
    
    modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes("Btsw", BTSW_INDEX_BDL_BN_KABAN));
    mpKabanModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (mpKabanModel == NULL) {
        return FALSE;
    }
    modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes("Btsw", BTSW_INDEX_BDL_BN_TIRASI));
    mpTirasiModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (mpTirasiModel == NULL) {
        return FALSE;
    }
    
    m744 = 0;
    if (!initTexPatternAnm(false)) {
        return FALSE;
    }
    
    modelData = mpMorf->getModel()->getModelData();
    modelData->getJointNodePointer(m_jnt.getHeadJntNum())->setCallBack(nodeCallBack);
    modelData->getJointNodePointer(m_jnt.getBackboneJntNum())->setCallBack(nodeCallBack);
    mpMorf->getModel()->setUserArea((u32)this);
    mAcchCir.SetWall(30.0f, 0.0f);
    mObjAcch.Set(&current.pos, &old.pos, this, 1, &mAcchCir, &speed);
    
    return TRUE;
}

/* 00000EFC-000010F8       .text CreateInit__13daNpc_Btsw2_cFv */
BOOL daNpc_Btsw2_c::CreateInit() {
    m714 = current.angle;
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    gravity = -30.0f;
    setAction(&daNpc_Btsw2_c::wait_action, NULL);
    mAttPos = current.pos;
    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);
    setCollision(60.0f, 150.0f);
    m724 = 0;
    mPathNo = fopAcM_GetParamBit(fopAcM_GetParam(this), 0x10, 8);
    mpPath = dPath_GetRoomPath(mPathNo, current.roomNo);
    mFinalPathPntIdx = mpPath->m_num - 1;
    m73E = 1.0f + cM_rndF(3.0f);
    m742 = 90.0f + cM_rndF(300.0f);
    m735 = 0;
    m736 = 0;
    mPathPntIdx = 0;
    mEventCut.setActorInfo2("Btsw2", this);
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xAB;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xAB;
    return TRUE;
}

/* 000010F8-0000111C       .text wait01__13daNpc_Btsw2_cFv */
void daNpc_Btsw2_c::wait01() {
    if (m71E) {
        m747 = 2;
    } else {
        m746 = 2;
    }
}

/* 0000111C-000011A8       .text talk01__13daNpc_Btsw2_cFv */
void daNpc_Btsw2_c::talk01() {
    if (talk(1) == fopMsgStts_BOX_CLOSED_e) {
        m747 = 1;
        dComIfGp_event_reset();
        m71E = false;
        if (m742 == 0) {
            m736 = 1;
            setAnm(0);
        } else {
            setAnm(0);
        }
    }
}

/* 000011A8-00001574       .text pathMove__13daNpc_Btsw2_cFv */
void daNpc_Btsw2_c::pathMove() {
    if (m742 > 0) {
        m742--;
        if (m742 == 0) {
            setAnm(7);
            m73E = 1.0f + cM_rndF(3.0f);
        }
        if (m745 == 8 && mpMorf->checkFrame(mpMorf->getEndFrame()-1.0f)) {
            setAnm(0);
        }
        return;
    }
    
    s16 pathPntIdx;
    if (mPathPntIdx < mFinalPathPntIdx) {
        pathPntIdx = mPathPntIdx+1;
    } else {
        pathPntIdx = 0;
    }
    dPath__Point* pnt = &mpPath->mpPnt[pathPntIdx];
    cXyz targetPos(pnt->mPos.x, pnt->mPos.y, pnt->mPos.z);
    s16 targetAngle = cLib_targetAngleY(&current.pos, &targetPos);
    cLib_addCalcAngleS2(&current.angle.y, targetAngle, l_HIO.m32, l_HIO.m30);
    cXyz sp48 = targetPos - current.pos;
    speedF = l_HIO.m34;
    if (sp48.normalizeRS()) {
        cXyz sp3c(
            cM_ssin(current.angle.y),
            0.0f,
            cM_scos(current.angle.y)
        );
        speedF += l_HIO.m38 * sp48.inprod(sp3c);
    }
    
    if (m736 != 0) {
        speedF = 0.0f;
        s16 r27 = cLib_distanceAngleS(current.angle.y, targetAngle);
        cLib_addCalcAngleS2(&current.angle.y, targetAngle, 4, 0x1800);
        if (r27 < 0x10) {
            m736 = 0;
            setAnm(7);
        }
    }
    
    fopAcM_posMoveF(this, mStts.GetCCMoveP());
    
    cXyz sp30 = targetPos - current.pos;
    if (sp30.absXZ() < 10.0f) {
        mPathPntIdx = pathPntIdx;
        if (m73E > 0) {
            m73E--;
            return;
        }
        if (cM_rndF(1.0f) < 0.5f) {
            setAnm(0);
        } else {
            setAnm(8);
        }
        m742 = l_HIO.m3C + cM_rndF(l_HIO.m3E);
    }
}

/* 00001574-00001660       .text wait_action__13daNpc_Btsw2_cFPv */
BOOL daNpc_Btsw2_c::wait_action(void*) {
    if (mActionStatus == ACTION_STARTING) {
        m747 = 1;
        mActionStatus++; // ACTION_ONGOING
    } else if (mActionStatus != ACTION_ENDING) {
        s16 facingAngleY = current.angle.y + m_jnt.getHead_y() + m_jnt.getBackbone_y();
        mHasAttention = chkAttention(current.pos, facingAngleY);
        m746 = 0;
        
        switch (m747) {
        case 1:
            wait01();
            pathMove();
            break;
        case 2:
            talk01();
            break;
        }
        
        lookBack();
        setAttention();
    }
    
    return TRUE;
}

/* 00001660-00001884       .text _create__13daNpc_Btsw2_cFv */
s32 daNpc_Btsw2_c::_create() {
    fopAcM_SetupActor(this, daNpc_Btsw2_c);
    
    if (dComIfGs_getEventReg(0xC203) == 3 || !checkItemGet(dItem_PEARL_DIN_e, TRUE)) {
        return cPhs_ERROR_e;
    }
    
    int phase_state = dComIfG_resLoad(&mPhs, m_arc_name);
    
    if (phase_state == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(this, CallbackCreateHeap, 0x29E0)) {
            return cPhs_ERROR_e;
        }
        
        fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
        
        if (!CreateInit()) {
            return cPhs_ERROR_e;
        }
    }
    
    return phase_state;
}

/* 00001C34-00001C8C       .text _delete__13daNpc_Btsw2_cFv */
BOOL daNpc_Btsw2_c::_delete() {
    dComIfG_resDelete(&mPhs, m_arc_name);
    if (heap && mpMorf) {
        mpMorf->stopZelAnime();
    }
    return TRUE;
}

/* 00001C8C-00001DDC       .text _execute__13daNpc_Btsw2_cFv */
BOOL daNpc_Btsw2_c::_execute() {
    m_jnt.setParam(
        l_HIO.mNpc.mMaxBackboneX, l_HIO.mNpc.mMaxBackboneY, l_HIO.mNpc.mMinBackboneX, l_HIO.mNpc.mMinBackboneY,
        l_HIO.mNpc.mMaxHeadX, l_HIO.mNpc.mMaxHeadY, l_HIO.mNpc.mMinHeadX, l_HIO.mNpc.mMinHeadY,
        l_HIO.mNpc.mMaxTurnStep
    );
    playTexPatternAnm();
    mpMorf->play(&eyePos, 0, 0);
    checkOrder();
    if (!mEventCut.cutProc()) {
        (this->*mCurrActionFunc)(NULL);
    }
    eventOrder();
    mObjAcch.CrrPos(*dComIfG_Bgsp());
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    
    J3DModel* model = mpMorf->getModel();
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    model->setBaseTRMtx(mDoMtx_stack_c::get());
    
    setCollision(60.0f, 150.0f);
    
    return TRUE;
}

/* 00001DDC-00001F6C       .text _draw__13daNpc_Btsw2_cFv */
BOOL daNpc_Btsw2_c::_draw() {
    J3DModel* model = mpMorf->getModel();
    J3DModelData* modelData = model->getModelData();
    
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(model, &tevStr);
    g_env_light.setLightTevColorType(mpKabanModel, &tevStr);
    g_env_light.setLightTevColorType(mpTirasiModel, &tevStr);
    
    mBtpAnm.entry(modelData, mBtpFrame);
    mpMorf->updateDL();
    mpKabanModel->setBaseTRMtx(model->getAnmMtx(m_handL_jnt_num));
    mpTirasiModel->setBaseTRMtx(model->getAnmMtx(m_handR_jnt_num));
    mDoExt_modelUpdateDL(mpKabanModel);
    mDoExt_modelUpdateDL(mpTirasiModel);
    mBtpAnm.remove(modelData);
    
    cXyz shadowPos(current.pos.x, current.pos.y + 130.0f, current.pos.z);
    mShadowId = dComIfGd_setShadow(
        mShadowId, 1, mpMorf->getModel(), &shadowPos, 800.0f, 20.0f,
        current.pos.y, mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr
    );
    
    dSnap_RegistFig(DSNAP_TYPE_BTSW, this, current.pos, current.angle.y, 1.0f, 1.0f, 1.0f);
    
    return TRUE;
}

/* 00001F6C-00001F8C       .text daNpc_Btsw2_Create__FP10fopAc_ac_c */
static s32 daNpc_Btsw2_Create(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Btsw2_c*>(i_this)->_create();
}

/* 00001F8C-00001FAC       .text daNpc_Btsw2_Delete__FP13daNpc_Btsw2_c */
static BOOL daNpc_Btsw2_Delete(daNpc_Btsw2_c* i_this) {
    return static_cast<daNpc_Btsw2_c*>(i_this)->_delete();
}

/* 00001FAC-00001FCC       .text daNpc_Btsw2_Execute__FP13daNpc_Btsw2_c */
static BOOL daNpc_Btsw2_Execute(daNpc_Btsw2_c* i_this) {
    return static_cast<daNpc_Btsw2_c*>(i_this)->_execute();
}

/* 00001FCC-00001FEC       .text daNpc_Btsw2_Draw__FP13daNpc_Btsw2_c */
static BOOL daNpc_Btsw2_Draw(daNpc_Btsw2_c* i_this) {
    return static_cast<daNpc_Btsw2_c*>(i_this)->_draw();
}

/* 00001FEC-00001FF4       .text daNpc_Btsw2_IsDelete__FP13daNpc_Btsw2_c */
static BOOL daNpc_Btsw2_IsDelete(daNpc_Btsw2_c* i_this) {
    return TRUE;
}

static actor_method_class l_daNpc_Btsw2_Method = {
    (process_method_func)daNpc_Btsw2_Create,
    (process_method_func)daNpc_Btsw2_Delete,
    (process_method_func)daNpc_Btsw2_Execute,
    (process_method_func)daNpc_Btsw2_IsDelete,
    (process_method_func)daNpc_Btsw2_Draw,
};

actor_process_profile_definition g_profile_NPC_BTSW2 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_BTSW2,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Btsw2_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x0163,
    /* Actor SubMtd */ &l_daNpc_Btsw2_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_12_e,
};
