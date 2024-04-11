/**
 * d_a_npc_os.cpp
 * Player - Companion Statue / Servant of the Tower
 */

#include "d/actor/d_a_npc_os.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_camera.h"
#include "m_Do/m_Do_controller_pad.h"
#include "d/actor/d_a_player_main.h"

// Needed for the .data section to match.
static f32 dummy1[3] = {1.0f, 1.0f, 1.0f};
static f32 dummy2[3] = {1.0f, 1.0f, 1.0f};
static u8 dummy3[4] = {0x02, 0x00, 0x02, 0x01};
static f64 dummy4[2] = {3.0, 0.5};

static u8 temp[0x4C]; // TODO

static daNpc_Os_HIO_c l_HIO;
static s32 l_hio_counter = 0;
static cXyz l_smoke_scale(0.5f, 0.5f, 0.5f);

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ ~AT_TYPE_BOOMERANG,
        /* SrcObjTg  SPrm    */ TG_SPRM_SET | TG_SPRM_IS_ENEMY,
        /* SrcObjCo  SPrm    */ CO_SPRM_VSGRP | CO_SPRM_IS_UNK4 | CO_SPRM_SET,
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

static const char* l_staff_name[] = {
    "Os",
    "Os1",
    "Os2"
};

static char* l_daiza_name[] = {
    "Hdai1",
    "Hdai2",
    "Hdai3"
};

static Vec l_finish_home_pos[] = {
    {683.0f, 340.0f, -8947.0f},
    {-683.0f, 340.0f, -8947.0f},
    {0.0f, 340.0f, -9630.0}
};

/* 000000EC-00000154       .text __ct__15daNpc_Os_HIO2_cFv */
daNpc_Os_HIO2_c::daNpc_Os_HIO2_c() {
    field_0x04 = 3.5f;
    field_0x08 = 17.0f;
    field_0x0C = 2.5f;
    field_0x10 = 1.8f;
    field_0x14 = 0.6f;
    field_0x24 = 3000;
    field_0x26 = 1000;
    field_0x28 = 5;
    field_0x18 = 2.5f;
    field_0x1C = 0.6f;
    field_0x20 = 1.0f;
}

/* 00000154-000002B8       .text __ct__14daNpc_Os_HIO_cFv */
daNpc_Os_HIO_c::daNpc_Os_HIO_c() {
    mNpc.m04 = -20.0f;
    mNpc.mMaxHeadX = 0;
    mNpc.mMaxHeadY = 0x1388;
    mNpc.mMaxBackboneX = 0;
    mNpc.mMaxBackboneY = 0;
    mNpc.mMinHeadX = 0;
    mNpc.mMinHeadY = -0x1388;
    mNpc.mMinBackboneX = 0;
    mNpc.mMinBackboneY = 0;
    mNpc.mMaxTurnStep = 0x1000;
    mNpc.mMaxHeadTurnVel = 0x800;
    mNpc.mAttnYOffset = 130.0f;
    mNpc.mMaxAttnAngleY = 0x4000;
    mNpc.m22 = 0x0;
    mNpc.mMaxAttnDistXZ = 200.0f;

    field_0x5C = 0;
    field_0x60 = 80.0f;
    field_0x64 = 500.0f;
    field_0x68 = 0.05f;
    field_0x6C = 17.0f;
    field_0x70 = 0.0f;
    field_0x74 = 0.5f;
    field_0x78 = 0.2f;
    field_0x7C = 0.9f;
    field_0x80 = 15.0f;
    field_0x84 = 22.0f;
    field_0x8C = 4.0f;
    field_0x90 = -1.51367f;
    field_0x94 = -1.09863f;
    field_0x98 = -0.56152f;
    field_0x9C = 0.1f;
    field_0xA0 = 0.2f;
    field_0xA4 = 10.0f;
    field_0xA8 = 0.75f;
    field_0xAC = 18.0f;
    field_0xB0 = 8.0f;
    field_0x04 = -1;
}

/* 00000300-00000354       .text searchFromName__FPcUlUl */
static fopAc_ac_c* searchFromName(char* name, u32 param_1, u32 param_2) {
    fopAc_ac_c* actor = fopAcM_searchFromName(name, param_1, param_2);

    if(actor && fpcM_IsCreating(fopAcM_GetID(actor))) {
        actor = NULL;
    }
    
    return actor;
}

/* 00000354-00000374       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Os_c*>(i_this)->createHeap();
}

/* 00000374-00000538       .text create__10daNpc_Os_cFv */
s32 daNpc_Os_c::create() {
    fopAcM_SetupActor(this, daNpc_Os_c)

    static u32 l_heap_size = 0xFA0;

    int result = dComIfG_resLoad(&mPhs, "Os");
    if(result == cPhs_COMPLEATE_e) {
        if(!fopAcM_entrySolidHeap(this, CheckCreateHeap, l_heap_size)) {
            mpMorf = NULL;
            return cPhs_ERROR_e;
        }

        if(!finishCheck()) {
            checkRestart(getRestartNumber());
        }
        else {
            if(subtype < 3) {
                home.pos = l_finish_home_pos[subtype];
                current.pos = home.pos;
            }
        }

        setBaseMtx();
        fopAcM_SetMtx(this, mpMorf->mpModel->getBaseTRMtx());
        if(l_HIO.field_0x04 < 0) {
            l_HIO.field_0x04 = mDoHIO_root.mDoHIO_createChild("お供石像", &l_HIO); // "Companion Statue" (otomo sekizou)
            l_HIO.field_0x5C = this;
            l_hio_counter = 1;
        }
        else {
            l_hio_counter += 1;
        }

        if(!init()) {
            return cPhs_ERROR_e;
        }

        fopAcM_setStageLayer(this);
    }

    return result;
}

/* 00000748-000008CC       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int param_1) {
    if (!param_1) {
        J3DModel* model = j3dSys.getModel();
        J3DJoint* joint = (J3DJoint*)node;
        daNpc_Os_c* i_this = (daNpc_Os_c*)model->getUserArea();
        if (i_this) {
            static cXyz l_offsetAttPos(0.0f, 0.0f, 0.0f);
            static cXyz l_offsetEyePos(15.0f, 0.0f, 0.0f);
            
            s32 jntNo = joint->getJntNo();
            mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));
            mDoMtx_stack_c::multVec(&l_offsetAttPos, &i_this->getAttentionBasePos());
            mDoMtx_stack_c::XrotM(i_this->getHead_y());
            mDoMtx_stack_c::ZrotM(-i_this->getHead_x());
            mDoMtx_stack_c::multVec(&l_offsetEyePos, &i_this->getEyePos());
            i_this->incAttnSetCount();
            cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
            model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
        }
    }

    return true;
}

/* 000008CC-00000988       .text tunoNodeCallBack__FP7J3DNodei */
static BOOL tunoNodeCallBack(J3DNode* node, int param_1) {
    if (!param_1) {
        J3DJoint* joint = (J3DJoint*)node;
        J3DModel* model = j3dSys.getModel();
        daNpc_Os_c* i_this = (daNpc_Os_c*)model->getUserArea();
        if (i_this) {
            s32 jntNo = joint->getJntNo();
            if(!i_this->jointCheck(jntNo)) {
                mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));
                mDoMtx_stack_c::scaleM(0.1f, 0.1f, 0.1f);
                cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
                model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
            }
        }
    }

    return true;
}

/* 00000988-00000C94       .text createHeap__10daNpc_Os_cFv */
BOOL daNpc_Os_c::createHeap() {
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes("Os", 9));
    JUT_ASSERT(0x2F9, modelData != 0);

    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL, NULL,
        static_cast<J3DAnmTransformKey*>(dComIfG_getObjectRes("Os", 6)),
        J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, 1,
        NULL,
        0x00080000,
        0x11000002
    );

    if (!mpMorf || !mpMorf->getModel()) {
        return false;
    }

    s16 headIdx = modelData->getJointName()->getIndex("head_joint");
    if(headIdx >= 0) {
        modelData->getJointNodePointer(headIdx)->setCallBack(&nodeCallBack);
    }
    mTuno1JointIdx = modelData->getJointName()->getIndex("tuno1_joint");
    if(mTuno1JointIdx >= 0) {
        modelData->getJointNodePointer(mTuno1JointIdx)->setCallBack(&tunoNodeCallBack);
    }
    mTuno2JointIdx = modelData->getJointName()->getIndex("tuno2_joint");
    if(mTuno2JointIdx >= 0) {
        modelData->getJointNodePointer(mTuno2JointIdx)->setCallBack(&tunoNodeCallBack);
    }
    mTuno3JointIdx =modelData->getJointName()->getIndex("tuno3_joint");
    if(mTuno3JointIdx >= 0) {
        modelData->getJointNodePointer(mTuno3JointIdx)->setCallBack(&tunoNodeCallBack);
    }

    mpMorf->getModel()->setUserArea((u32)this);

    u8 anm;
    if(wakeupCheck()) {
        if(finishCheck()) {
            anm = 1;
        }
        else {
            anm = 6;
        }
    }
    else {
        anm = 5;
    }

    field_0x7A2 = 9;
    
    if(!initBrkAnm(anm, false)) {
        return false;
    }

    mAcchCir[0].SetWall(20.0f, 40.0f);
    mAcchCir[1].SetWall(60.0f, 40.0f);
    mAcch.Set(&current.pos, &old.pos, this, 2, &mAcchCir[0], &speed, 0, 0);
    mAcch.OnLineCheck();
    mAcch.ClrRoofNone();
    mAcch.SetRoofCrrHeight(120.0f);

    return true;
}

/* 00000C94-00000D10       .text jointCheck__10daNpc_Os_cFSc */
BOOL daNpc_Os_c::jointCheck(s8 param_1) {
    if(subtype == 0) {
        if(param_1 == mTuno3JointIdx) {
            return true;
        }
    }
    else if(subtype == 1) {
        if(param_1 == mTuno2JointIdx) {
            return true;
        }
    }
    else if(subtype == 2) {
        if(param_1 == mTuno1JointIdx) {
            return true;
        }
    }

    return false;
}

/* 00000D10-00000DBC       .text wakeupCheck__10daNpc_Os_cFv */
BOOL daNpc_Os_c::wakeupCheck() {
    if(subtype == 0) {
        if(dComIfGs_isEventBit(0x1780)) {
            return true;
        }
    }
    else if(subtype == 1) {
        if(dComIfGs_isEventBit(0x1740)) {
            return true;
        }
    }
    else if(subtype == 2) {
        if(dComIfGs_isEventBit(0x1720)) {
            return true;
        }
    }

    return false;
}

/* 00000DBC-00000E3C       .text setWakeup__10daNpc_Os_cFv */
void daNpc_Os_c::setWakeup() {
    if(subtype == 0) {
        dComIfGs_onEventBit(0x1780);
    }
    else if(subtype == 1) {
        dComIfGs_onEventBit(0x1740);
    }
    else if(subtype == 2) {
        dComIfGs_onEventBit(0x1720);
    }
}

/* 00000E3C-00000EE8       .text finishCheck__10daNpc_Os_cFv */
BOOL daNpc_Os_c::finishCheck() {
    if(subtype == 0) {
        if(dComIfGs_isEventBit(0x1710)) {
            return true;
        }
    }
    else if(subtype == 1) {
        if(dComIfGs_isEventBit(0x1704)) {
            return true;
        }
    }
    else if(subtype == 2) {
        if(dComIfGs_isEventBit(0x1B01)) {
            return true;
        }
    }

    return false;
}

/* 00000EE8-00000F68       .text setFinish__10daNpc_Os_cFv */
void daNpc_Os_c::setFinish() {
    if(subtype == 0) {
        dComIfGs_onEventBit(0x1710);
    }
    else if(subtype == 1) {
        dComIfGs_onEventBit(0x1704);
    }
    else if(subtype == 2) {
        dComIfGs_onEventBit(0x1B01);
    }
}

/* 00000F68-00000FA4       .text getWakeupOrderEventNum__10daNpc_Os_cFv */
s8 daNpc_Os_c::getWakeupOrderEventNum() {
    if(subtype == 0) {
        return 1;
    }
    else if(subtype == 1) {
        return 3;
    }
    else if(subtype == 2) {
        return 5;
    }
    
    return -1;
}

/* 00000FA4-00001028       .text getFinishOrderEventNum__10daNpc_Os_cFv */
s8 daNpc_Os_c::getFinishOrderEventNum() {
    if(fopAcM_checkCarryNow(this)) {
        if(subtype == 0) {
            return 0xB;
        }
        else if(subtype == 1) {
            return 0xD;
        }
        else if(subtype == 2) {
            return 0xF;
        }
    }
    else {
        if(subtype == 0) {
            return 0xA;
        }
        else if(subtype == 1) {
            return 0xC;
        }
        else if(subtype == 2) {
            return 0xE;
        }
    }
    
    return -1;
}

/* 00001028-00001084       .text getMyStaffId__10daNpc_Os_cFv */
int daNpc_Os_c::getMyStaffId() {
    if(subtype < 3) {
        return dComIfGp_evmng_getMyStaffId(l_staff_name[subtype]);
    }

    return -1;
}

/* 00001084-000010C4       .text getRestartNumber__10daNpc_Os_cFv */
s8 daNpc_Os_c::getRestartNumber() {
    if(subtype == 0) {
        return 3;
    }
    else if(subtype == 1) {
        return 4;
    }
    else if(subtype == 2) {
        return 5;
    }

    return 0;
}

/* 000010C4-0000112C       .text checkGoalRoom__10daNpc_Os_cFv */
BOOL daNpc_Os_c::checkGoalRoom() {
    if(fopAcM_GetRoomNo(this) == 7 && wakeupCheck() && !finishCheck()) {
        field_0x7A5 = getFinishOrderEventNum();

        return true;
    }

    return false;
}

/* 0000112C-000011C4       .text checkPlayerRoom__10daNpc_Os_cFv */
void daNpc_Os_c::checkPlayerRoom() {
    offPlayerRoom(subtype);
    
    if(wakeupCheck() && !finishCheck()) {
        fopAc_ac_c* link = dComIfGp_getLinkPlayer();
        if (fopAcM_GetRoomNo(this) == fopAcM_GetRoomNo(link)) {
            onPlayerRoom(subtype);
        }
    }
}

/* 000011C4-00001300       .text eventOrderCheck__10daNpc_Os_cFv */
void daNpc_Os_c::eventOrderCheck() {
    if(field_0x7A5 == -1) {
        s8 roomNo = fopAcM_GetRoomNo(this);
        if(subtype == 0) {
            if(roomNo == 7 && dComIfGs_isSwitch(field_0x794, roomNo) && !dComIfGs_isEventBit(0x2510)) {
                field_0x7A5 = 7;
            } 
        }
        else if(subtype == 1) {
            if(roomNo == 7 && dComIfGs_isSwitch(field_0x794, roomNo) && !dComIfGs_isEventBit(0x2608)) {
                field_0x7A5 = 8;
            } 
        }
        else if(subtype == 2) {
            if(roomNo == 7 && dComIfGs_isSwitch(field_0x794, roomNo) && !dComIfGs_isEventBit(0x2604)) {
                field_0x7A5 = 9;
            } 
        }
    }
}

/* 00001300-000013D4       .text makeBeam__10daNpc_Os_cFi */
void daNpc_Os_c::makeBeam(int param_1) {
    if(field_0x738.getEmitter() == NULL) {
        field_0x738.makeEmitter(0x826E, &current.pos, &shape_angle, 0);

        if(param_1) {
            fopAcM_seStartCurrent(this, JA_SE_OBJ_OSTATUE_LIGHT_ST, 0);
        }
    }

    if(field_0x740.getEmitter() == NULL) {
        field_0x740.makeEmitter(0x826F, &current.pos, &shape_angle, 0);
    }
}

/* 000013D4-0000140C       .text endBeam__10daNpc_Os_cFv */
void daNpc_Os_c::endBeam() {
    field_0x738.end();
    field_0x740.end();
}

/* 0000140C-00001454       .text wallHitCheck__10daNpc_Os_cFv */
s32 daNpc_Os_c::wallHitCheck() {
    if(mAcch.ChkWallHit()) {
        for(int i = 0; i < 2; i++) {
            if(mAcchCir[i].ChkWallHit()) {
                return i;
            }
        }
    }

    return -1;
}

/* 00001454-000014CC       .text walkProc__10daNpc_Os_cFfs */
void daNpc_Os_c::walkProc(f32 param_1, s16 param_2) {
    if(mPrevMorfFrame > l_HIO.field_0xB0 && mPrevMorfFrame < l_HIO.field_0xAC) {
        speedF = l_HIO.mOs2.field_0x08 * param_1;
    }
    else {
        speedF = 0.0f;
    }

    cLib_addCalcAngleS(&current.angle.y, param_2, l_HIO.mOs2.field_0x28, l_HIO.mOs2.field_0x24, l_HIO.mOs2.field_0x26);
}

/* 000014CC-0000159C       .text setAction__10daNpc_Os_cFPM10daNpc_Os_cFPCvPvPv_iM10daNpc_Os_cFPCvPvPv_iPv */
BOOL daNpc_Os_c::setAction(ActionFunc_t* pOut, ActionFunc_t action, void* param_1) {
    if(*pOut != action) {
        if(*pOut) {
            field_0x7A9 = 0xFF;
            (this->**pOut)(param_1);
        }

        *pOut = action;
        field_0x7A9 = 0;
        field_0x7AC = 0;
        field_0x7AE = 0;
        field_0x7B0 = 0;
        field_0x7B2 = 0;
        field_0x7B8 = 0.0f;
        (this->**pOut)(param_1);
    }

    return true;
}

/* 0000159C-0000164C       .text npcAction__10daNpc_Os_cFPv */
void daNpc_Os_c::npcAction(void* param_1) {
    if(!mNpcAction) {
        speedF = 0.0f;
        
        if(field_0x7A2 == 8) {
            initBrkAnm(6, true);
        }

        setNpcAction(&waitNpcAction, 0);
    }

    (this->*mNpcAction)(param_1);
}

/* 0000164C-000016B0       .text setNpcAction__10daNpc_Os_cFM10daNpc_Os_cFPCvPvPv_iPv */
void daNpc_Os_c::setNpcAction(ActionFunc_t action, void* param_2) {
    mPlayerAction = NULL;
    setAction(&mNpcAction, action, param_2);
}

/* 000016B0-00001760       .text playerAction__10daNpc_Os_cFPv */
void daNpc_Os_c::playerAction(void* param_1) {
    if(!mPlayerAction) {
        speedF = 0.0f;
        setPlayerAction(&waitPlayerAction, 0);
    }

    dComIfGp_setRStatusForce(7);
    dComIfGp_setDoStatus(0x3E);
    dComIfGp_setAStatus(0x3E);

    (this->*mPlayerAction)(param_1);
}

/* 00001760-000017C4       .text setPlayerAction__10daNpc_Os_cFM10daNpc_Os_cFPCvPvPv_iPv */
void daNpc_Os_c::setPlayerAction(ActionFunc_t action, void* param_2) {
    mNpcAction = NULL;
    setAction(&mPlayerAction, action, param_2);
}

/* 000017C4-0000180C       .text getStickAngY__10daNpc_Os_cFv */
s16 daNpc_Os_c::getStickAngY() {
    return dCam_getControledAngleY(dComIfGp_getCamera(0)) + (g_mDoCPd_cpadInfo[0].mMainStickAngle + 0x8000);
}

/* 0000180C-00001964       .text calcStickPos__10daNpc_Os_cFsP4cXyz */
int daNpc_Os_c::calcStickPos(s16 param_1, cXyz* param_2) {
    int ret;

    // This temp variable for attention is probably a fakematch, but it fixes a regswap in dAttention_c::Lockon.
    dAttention_c& attention = dComIfGp_getAttention();
    dAttList_c* attList = attention.GetLockonList(0);
    bool lockon = attention.Lockon();
    if(!lockon) {
        ret = 0;
    } else {
        BOOL lockon = attention.LockonTruth();
        ret = -1;
        if (lockon) {
            ret = 1;
        }
    }

    if(attList == NULL) {
        attList = attention.GetActionList(0);
    }

    if(attList) {
        *param_2 = attList->getActor()->eyePos;

        return ret;
    }

    if(lockon) {
        param_1 = shape_angle.y;
    }

    param_2->set(current.pos.x + cM_ssin(param_1) * 100.0f, current.pos.y, current.pos.z + cM_scos(param_1) * 100.0f);

    return ret;
}

/* 00001964-000019B8       .text returnLinkPlayer__10daNpc_Os_cFv */
void daNpc_Os_c::returnLinkPlayer() {
    changePlayer(dComIfGp_getLinkPlayer());
    offNpcCallCommand();
    initBrkAnm(6, true);
}

/* 000019B8-00001A08       .text returnLinkCheck__10daNpc_Os_cFv */
BOOL daNpc_Os_c::returnLinkCheck() {
    if(!dComIfGp_event_runCheck()) {
        if((CPad_CHECK_TRIG_R(0) || CPad_CHECK_TRIG_START(0)) && mAcch.ChkGroundHit()) {
            return true;
        }
    }

    return false;
}

/* 00001A08-00001CD8       .text waitNpcAction__10daNpc_Os_cFPv */
BOOL daNpc_Os_c::waitNpcAction(void*) {
    if(field_0x7A9 == 0) {
        maxFallSpeed = -100.0f;
        gravity = l_HIO.field_0x8C;
        speedF = 0.0f;
        field_0x788 = 120.0f;

        field_0x7A9 += 1;
    }
    else if(field_0x7A9 != -1) {
        if(field_0x78C && mReachedAnimEnd) {
            setAnm(0);
        }

        if(field_0x7A9 == 1) {
            if(wakeupCheck() && dComIfGp_getCb1Player() == this) {
                if(checkNpcNotChange()) {
                    offNpcNotChange();
                    initBrkAnm(4, true);
                    field_0x7A1 = 0;
                    field_0x7A9 += 1;
                }
                else {
                    field_0x7A9 += 1;
                }
            }
        }
        else {
            attention_info.flags |= fopAc_Attn_ACTION_CARRY_e;
            s16 angle = shape_angle.y + mJntCtrl.getHead_y() + mJntCtrl.getBackbone_y();
            field_0x7A4 = chkAttention(current.pos, angle);

            if(chkArea(&current.pos)) {
                lookBack(field_0x7A4, 0, 1);
            }

            current.angle.y = shape_angle.y;

            if(finishCheck()) {
                setNpcAction(&finish01NpcAction, 0);
            }
        }

        attention_info.flags &= ~(fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_TALK_e);

        f32 dist = fopAcM_searchPlayerDistance2(this);
        if(!checkNpcCallCommand()) {
            if(dist < l_HIO.field_0x64 * l_HIO.field_0x64) {
                daPy_getPlayerLinkActorClass()->onNpcCallCommand();
            }
        }
        else {
            if(wakeupCheck()) {
                if(dist >= l_HIO.field_0x60 * l_HIO.field_0x60) {
                    setNpcAction(&searchNpcAction, 0);
                }
            }
            else {
                field_0x7A5 = getWakeupOrderEventNum();
            }
        }

        setAttention(true);
    }

    return true;
}

/* 00001CD8-00001E34       .text finish01NpcAction__10daNpc_Os_cFPv */
BOOL daNpc_Os_c::finish01NpcAction(void* param_1) {
    if(field_0x7A9 == 0) {
        if(dComIfGp_getCb1Player() == this) {
            onNpcNotChange();
            dComIfGp_setCb1Player(NULL);
        }
        
        setAnm(0);
        initBrkAnm(0, true);
        field_0x7A1 = 0;
        maxFallSpeed = -100.0f;
        gravity = l_HIO.field_0x8C;
        speedF = 0.0f;
        field_0x788 = 120.0f;

        field_0x7A9 += 1;
    }
    else if(field_0x7A9 != -1) {
        mJntCtrl.lookAtTarget(&shape_angle.y, 0, cXyz::Zero, shape_angle.y, field_0x798, true);

        if(field_0x7A1) {
            setNpcAction(&finish02NpcAction, 0);
        }

        setAttention(true);
    }

    return true;
}

/* 00001E34-00001F48       .text finish02NpcAction__10daNpc_Os_cFPv */
BOOL daNpc_Os_c::finish02NpcAction(void* param_1) {
    if(field_0x7A9 == 0) {
        if(param_1 == NULL) {
            if(dComIfGs_isEventBit(0x1B01)) {
                setAnm_brkAnm(7);
            }
            else {
                setAnm_brkAnm(1);
            }
        }
        
        onFinish();
        maxFallSpeed = -100.0f;
        gravity = l_HIO.field_0x8C;
        speedF = 0.0f;
        field_0x788 = 120.0f;

        field_0x7A9 += 1;
    }
    else if(field_0x7A9 != -1) {
        mJntCtrl.lookAtTarget(&shape_angle.y, 0, cXyz::Zero, shape_angle.y, field_0x798, true);
    }

    return true;
}

static uint l_msgId;
static msg_class* l_msg;

/* 00001F48-00002118       .text talkNpcAction__10daNpc_Os_cFPv */
BOOL daNpc_Os_c::talkNpcAction(void*) {
    if(field_0x7A9 == 0) {
        l_msgId = -1;
        field_0x780 = getMsg();
        attention_info.flags &= ~fopAc_Attn_ACTION_CARRY_e;
        field_0x7A3 = 0;
        field_0x7A9 += 1;
    }
    else if(field_0x7A9 != -1) {
        s16 angle = shape_angle.y + mJntCtrl.getHead_y() + mJntCtrl.getBackbone_y();
        field_0x7A4 = chkAttention(current.pos, angle);

        if(field_0x7A9 == 1) {
            if(talk_init()) {
                field_0x7A9 = 2;
            }
        }
        else if(field_0x7A9 == 2) {
            if(talk()) {
                setNpcAction(&waitNpcAction, 0);
                dComIfGp_event_reset();
            }
        }
        else if(field_0x7A9 == 3) {
            setNpcAction(&waitNpcAction, 0);
        }

        mJntCtrl.setTrn();
        lookBack(field_0x7A4, 0, 0);
        current.angle.y = shape_angle.y;
        setAttention(mpMorf->isMorf());
    }

    return true;
}

/* 00002118-000023A4       .text carryNpcAction__10daNpc_Os_cFPv */
BOOL daNpc_Os_c::carryNpcAction(void* param_1) {
    if(field_0x7A9 == 0) {
        setAnm(0);

        attention_info.flags &= ~fopAc_Attn_ACTION_CARRY_e;
        offNpcCallCommand();
        field_0x7AC = shape_angle.y - dComIfGp_getPlayer(0)->shape_angle.y;
        field_0x788 = 120.0f;
        field_0x7A9 += 1;
    }
    else if(field_0x7A9 == -1) {
        field_0x7E4.y = 0.0f;
        field_0x7E4.z = 0.0f;
    }
    else {
        setRestart(getRestartNumber());

        cLib_chaseF(&field_0x7E4.x, l_HIO.field_0x90, 1.0f);
        cLib_chaseF(&field_0x7E4.y, l_HIO.field_0x94, 1.0f);
        cLib_chaseF(&field_0x7E4.z, l_HIO.field_0x98, 1.0f);

        s32 wallHit = wallHitCheck();
        if(wallHit >= 0 || mAcch.ChkRoofHit()) {
            fopAcM_cancelCarryNow(this);

            s16 temp = mAcchCir[wallHit].GetWallAngleY();
            setNpcAction(&throwNpcAction, &temp);

            return true;
        }

        if(!fopAcM_checkCarryNow(this)) {
            if(speedF > 0.0f) {
                setNpcAction(&throwNpcAction, 0);

                return true;
            }
            else {
                fopAcM_seStartCurrent(this, JA_SE_OBJ_OSTATUE_PUT, 0);
                smokeSet(0xA328);
                setNpcAction(&waitNpcAction, 0);

                return true;
            }
        }
        
        mJntCtrl.lookAtTarget(&shape_angle.y, 0, cXyz::Zero, shape_angle.y, 0, false);
        current.angle.y = shape_angle.y;
    }

    return true;
}

/* 000023A4-000024FC       .text throwNpcAction__10daNpc_Os_cFPv */
BOOL daNpc_Os_c::throwNpcAction(void* param_1) {
    if(field_0x7A9 == 0) {
        if(param_1) {
            speedF = 8.0f;
            speed.y = 0.0f;
            current.angle.y = *(s16*)param_1;
        }
        else {
            speedF = l_HIO.field_0x80;
            speed.y = l_HIO.field_0x84;
            current.angle.y = shape_angle.y;
        }

        maxFallSpeed = -100.0f;
        gravity = l_HIO.field_0x8C;
        field_0x7A9 += 1;
    }
    else if(field_0x7A9 != -1) {
        if(mAcch.ChkGroundHit()) {
            fopAcM_seStartCurrent(this, JA_SE_OBJ_OSTATUE_PUT, 0);
            smokeSet(0xA33B);
            setNpcAction(&waitNpcAction, 0);
        }

        setAttention(true);
    }

    return true;
}

/* 000024FC-000025F0       .text jumpNpcAction__10daNpc_Os_cFPv */
BOOL daNpc_Os_c::jumpNpcAction(void* param_1) {
    if(field_0x7A9 == 0) {
        setAnm(0);

        if(param_1) {
            speed.y = *(f32*)param_1;
        }

        speedF = 50.0f;
        maxFallSpeed = -100.0f;
        gravity = l_HIO.field_0x8C;
        field_0x7A9 += 1;
    }
    else if(field_0x7A9 != -1) {
        if(mAcch.ChkGroundHit()) {
            smokeSet(0xA33B);
            setNpcAction(&waitNpcAction, 0);
        }

        setAttention(true);
    }

    return true;
}

/* 000025F0-000026BC       .text routeAngCheck__10daNpc_Os_cFR4cXyzPs */
void daNpc_Os_c::routeAngCheck(cXyz& param_1, s16* param_2) {
    cXyz cross = field_0x7F0.outprod(param_1);
    s16 angle = cM_atan2s(cross.x, cross.z);
    if((field_0x7F0.y >= 1.0f && cLib_distanceAngleS(angle, *param_2) > 0x4000) || fopAcM_searchPlayerDistanceY(this) * cross.y < 0.0f) {
        angle += 0x8000;
    }

    *param_2 = angle;
}

/* 000026BC-00002920       .text routeWallCheck__10daNpc_Os_cFR4cXyzR4cXyzPs */
void daNpc_Os_c::routeWallCheck(cXyz& param_1, cXyz& param_2, s16* param_3) {
    dBgS_LinChk linChk;
    linChk.Set(&param_1, &param_2, 0);
    if(dComIfG_Bgsp()->LineCross(&linChk)) {
        cM3dGPla* plane = dComIfG_Bgsp()->GetTriPla(linChk.GetBgIndex(), linChk.GetPolyIndex());
        if(plane) {
            routeAngCheck(*plane->GetNP(), param_3);
        }
    }
}

/* 00002D10-00002FA4       .text checkForwardGroundY__10daNpc_Os_cFs */
f32 daNpc_Os_c::checkForwardGroundY(s16 param_1) {
    s32 wallHit = wallHitCheck();
    if(wallHit >= 0) {
        cM3dGPla* plane = dComIfG_Bgsp()->GetTriPla(mAcchCir[wallHit].GetBgIndex(), mAcchCir[wallHit].GetPolyIndex());
        if(plane) {
            if(cLib_distanceAngleS(param_1, cM_atan2s(plane->GetNP()->x, plane->GetNP()->z)) > 0x4000) {
                dBgS_GndChk gndChk;

                gndChk.OffWall();
                cXyz temp(current.pos.x + cM_ssin(param_1) * 80.0f, current.pos.y + 80.0f, current.pos.z + cM_scos(param_1) * 80.0f);
                gndChk.SetPos(&temp);

                return dComIfG_Bgsp()->GroundCross(&gndChk);
            }
        }
    }

    return -1.0e7f;
}

/* 0000313C-00003210       .text checkWallJump__10daNpc_Os_cFs */
f32 daNpc_Os_c::checkWallJump(s16 param_1) {
    f32 delta = checkForwardGroundY(param_1) - current.pos.y;
    if(0.0f < delta && delta < 80.0f) {
        delta = sqrtf(delta) * 3.6f;
    }
    else {
        delta = -1.0f;
    }

    return delta;
}

/* 00003210-0000375C       .text routeCheck__10daNpc_Os_cFfPs */
BOOL daNpc_Os_c::routeCheck(f32 param_1, s16* param_2) {
    if(!mAcch.ChkGroundHit()) {
        current.pos = old.pos;
        speedF = 0.0f;
        field_0x7A8 = 1;

        dBgS_GndChk gndChk;
        gndChk.OffWall();
        cXyz temp(current.pos.x + cM_ssin(*param_2) * 80.0f, current.pos.y + 80.0f, current.pos.z + cM_scos(*param_2) * 80.0f);
        gndChk.SetPos(&temp);

        if(dComIfG_Bgsp()->GroundCross(&gndChk) - current.pos.y > -100.0f) {
            if(cLib_distanceAngleS(current.angle.y, *param_2) < 0x800) {
                setNpcAction(&jumpNpcAction, 0);
            }
            
            return true;
        }

        if(param_1 > 360000.0f) {
            return false;
        }

        temp.y = current.pos.y - 80.0f;
        routeWallCheck(temp, current.pos, param_2);
    }
    else {
        if(mAcch.ChkWallHit()) {
            f32 temp4 = checkWallJump(*param_2);
            if(temp4 >= 0.0f) {
                setNpcAction(&jumpNpcAction, &temp4);
                return true;
            }

            if(param_1 > 360000.0f) {
                return false;
            }
        }
        

        cXyz temp2(current.pos.x, current.pos.y + 80.0f, current.pos.z);
        cXyz temp3(current.pos.x + cM_ssin(*param_2) * 80.0f, current.pos.y + 80.0f, current.pos.z + cM_scos(*param_2) * 80.0f);
        routeWallCheck(temp2, temp3, param_2);
    }

    return true;
}

/* 0000375C-000039EC       .text searchNpcAction__10daNpc_Os_cFPv */
BOOL daNpc_Os_c::searchNpcAction(void*) {
    if(field_0x7A9 == 0) {
        attention_info.flags |= fopAc_Attn_ACTION_CARRY_e;
        setAnm(1);
        
        field_0x7A9 += 1;
    }
    else if(field_0x7A9 != -1) {
        field_0x7A4 = 1;
        daPy_py_c* player = daPy_getPlayerActorClass();

        BOOL door = player->eventInfo.checkCommandDoor();
        f32 dist = fopAcM_searchPlayerDistanceXZ2(this);
        f32 temp;
        if (dist < l_HIO.field_0x60 * l_HIO.field_0x60) {
            temp = 0.0f;
        } else {
            temp = l_HIO.field_0xA8;
        }
        s16 angle, adjustedAngle;
        angle = adjustedAngle = fopAcM_searchPlayerAngleY(this);
        BOOL temp3 = routeCheck(dist, &adjustedAngle) && cLib_distanceAngleS(angle, adjustedAngle) <= 0x2000;
        if(door || !temp3 || (dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK2000000_e | daPyStts0_UNK100_e | daPyStts0_UNK1_e) || player->checkAttentionLock())) {
            temp = 0.0f;
            offNpcCallCommand();
        }
        else {
            setRestart(getRestartNumber());
            if(!door) {
                if(cLib_calcTimer(&field_0x7A7) == 0) {
                    field_0x7A6 ^= 1;
                    field_0x7A7 = cLib_getRndValue(8, 0x14);
                }
                
                mpMorf->setPlaySpeed(2.0f);
            }
            else {
                mpMorf->setPlaySpeed(4.0f);
            }
        }

        walkProc(temp, adjustedAngle);
        cLib_addCalcAngleS(&shape_angle.y, current.angle.y, l_HIO.mOs2.field_0x28, l_HIO.mOs2.field_0x24 * 2, l_HIO.mOs2.field_0x26 * 2);
        s16 temp4 = shape_angle.y;
        lookBack(1, 0, 0);
        if(temp < 0.001f) {
            setNpcAction(&waitNpcAction, 0);
        }
        else {
            shape_angle.y = temp4;
        }

        setAttention(true);
    }

    return true;
}

/* 000039EC-00003C64       .text waitPlayerAction__10daNpc_Os_cFPv */
BOOL daNpc_Os_c::waitPlayerAction(void*) {
    if(field_0x7A9 == 0) {
        speedF = 0.0f;
        setAnm(0);
        initBrkAnm(8, true);
        
        field_0x7A9 += 1;
    }
    else if(field_0x7A9 != -1) {
        dAttention_c& attention = dComIfGp_getAttention();
        if(g_mDoCPd_cpadInfo[0].mMainStickValue >= l_HIO.field_0x9C || attention.Lockon()) {
            s16 target = getStickAngY();
            cLib_addCalcAngleS(&current.angle.y, target, 0x19, 0x7FFF, 1);
            cXyz temp;
            s32 stickPos = calcStickPos(target, &temp);
            if(stickPos == 0) {
                shape_angle.y = current.angle.y;
            }
            else if(g_mDoCPd_cpadInfo[0].mMainStickValue >= l_HIO.field_0xA0) {
                shape_angle.y = current.angle.y;
            }

            s16 temp2 = shape_angle.y;
            mJntCtrl.lookAtTarget(&temp2, &temp, current.pos, shape_angle.y, l_HIO.mNpc.mMaxTurnStep, false);

            if(stickPos > 0) {
                shape_angle.y = temp2;
            }

            current.angle.y = shape_angle.y;
            if(g_mDoCPd_cpadInfo[0].mMainStickValue >= l_HIO.field_0xA0 && stickPos == 0) {
                current.angle.y = target;
                setPlayerAction(&walkPlayerAction, 0);
            }
        }
        else {
            mJntCtrl.lookAtTarget(&shape_angle.y, 0, cXyz::Zero, shape_angle.y, 0, false);
            current.angle.y = shape_angle.y;
        }

        setAttention(mpMorf->isMorf());
    }

    return true;
}

/* 00003C64-00003E98       .text walkPlayerAction__10daNpc_Os_cFPv */
BOOL daNpc_Os_c::walkPlayerAction(void*) {
    if(field_0x7A9 == 0) {
        speedF = 0.0f;
        setAnm(1);
        initBrkAnm(8, true);
        
        field_0x7A9 += 1;
    }
    else if(field_0x7A9 != -1) {
        f32 stickValue = g_mDoCPd_cpadInfo[0].mMainStickValue;
        s16 target = getStickAngY();
        if(stickValue > 0.05f) {
            if(mPrevMorfFrame > l_HIO.field_0xB0 && mPrevMorfFrame < l_HIO.field_0xAC) {
                speedF = l_HIO.mOs2.field_0x08 * stickValue * l_HIO.mOs2.field_0x20;
            }
            else {
                speedF = 0.0f;
                cLib_addCalcAngleS(&current.angle.y, target, l_HIO.mOs2.field_0x28, l_HIO.mOs2.field_0x24, l_HIO.mOs2.field_0x26);
            }

            cXyz temp;
            s32 stickPos = calcStickPos(target, &temp);
            if(stickPos == 0) {
                cLib_addCalcAngleS(&shape_angle.y, current.angle.y, l_HIO.mOs2.field_0x28, l_HIO.mOs2.field_0x24 * 2, l_HIO.mOs2.field_0x26 * 2);
            }

            s16 temp2 = shape_angle.y;
            mJntCtrl.lookAtTarget(&temp2, &temp, current.pos, shape_angle.y, l_HIO.mNpc.mMaxTurnStep, false);

            if(stickPos > 0) {
                shape_angle.y = temp2;
            }

            if(stickPos != 0) {
                setPlayerAction(&waitPlayerAction, 0);
            }
        }
        else {
            setPlayerAction(&waitPlayerAction, 0);
        }

        setAttention(true);
    }

    return true;
}

typedef void(daNpc_Os_c::*eventInitFunc)(int);
static eventInitFunc event_init_tbl[] = {
    &daNpc_Os_c::initialWaitEvent,
    &daNpc_Os_c::initialWakeupEvent,
    &daNpc_Os_c::initialMoveEvent,
    &daNpc_Os_c::initialEndEvent,
    &daNpc_Os_c::initialTurnEvent,
    &daNpc_Os_c::initialFinishEvent,
    &daNpc_Os_c::initialMsgSetEvent,
    &daNpc_Os_c::initialDefault,
    &daNpc_Os_c::initialSwitchOnEvent,
    &daNpc_Os_c::initialNextEvent,
    &daNpc_Os_c::initialSaveEvent,
    &daNpc_Os_c::initialMoveEndEvent
};

typedef BOOL(daNpc_Os_c::*eventActionFunc)(int);
static eventActionFunc event_action_tbl[] = {
    &daNpc_Os_c::actionWaitEvent,
    &daNpc_Os_c::actionWakeupEvent,
    &daNpc_Os_c::actionMoveEvent,
    &daNpc_Os_c::actionDefault,
    &daNpc_Os_c::actionTurnEvent,
    &daNpc_Os_c::actionFinishEvent,
    &daNpc_Os_c::actionMsgSetEvent,
    &daNpc_Os_c::actionMsgEndEvent,
    &daNpc_Os_c::actionDefault,
    &daNpc_Os_c::actionDefault,
    &daNpc_Os_c::actionDefault,
    &daNpc_Os_c::actionDefault
};

static char* cut_name_tbl[] = {
    "WAIT",
    "WAKEUP",
    "MOVE",
    "END",
    "TURN",
    "FINISH",
    "MSGSET",
    "MSGEND",
    "SW_ON",
    "NEXT",
    "SAVE",
    "MOVEEND",
};

/* 00003E98-00004228       .text eventProc__10daNpc_Os_cFv */
BOOL daNpc_Os_c::eventProc() {
    if(eventInfo.checkCommandDemoAccrpt() && field_0x7A5 != -1) {
        if(field_0x7A5 == 0) {
            if(dComIfGp_evmng_startCheck("OPTION_CHAR_END") || dComIfGp_evmng_endCheck("OPTION_CHAR_END")) {
                dComIfGp_event_setTalkPartner(dComIfGp_getLinkPlayer());
                mDoAud_seStart(JA_SE_CTRL_NPC_TO_LINK);
            }
            else {
                offReturnLink();
                field_0x7A5 = -1;
            }
        }
        else if(field_0x7A5 != 2 && field_0x7A5 != 4 && field_0x7A5 != 6) {
            if(field_0x7A5 == 0xA || field_0x7A5 == 0xB || field_0x7A5 == 0xC || field_0x7A5 == 0xD || field_0x7A5 == 0xE || field_0x7A5 == 0xF) {
                setNpcAction(&waitNpcAction, 0);
                offNpcCallCommand();
                onNpcNotChange();
                dComIfGp_setCb1Player(NULL);
                setFinish();
            }
            else if(field_0x7A5 == 8) {
                dComIfGs_onEventBit(0x2608);
            }
            else if(field_0x7A5 == 9) {
                dComIfGs_onEventBit(0x2604);
            }
        }

        if(field_0x7A5 != -1) {
            onEventAccept();
            field_0x7A5 = -1;
        }
    }

    int staffIdx = getMyStaffId();
    if(dComIfGp_event_runCheck() && !checkCommandTalk()) {
        if(staffIdx != -1) {
            int actIdx = dComIfGp_evmng_getMyActIdx(staffIdx, cut_name_tbl, ARRAY_SIZE(cut_name_tbl), 1, 0);
            if(actIdx == -1) {
                dComIfGp_evmng_cutEnd(staffIdx);
            }
            else {
                if(dComIfGp_evmng_getIsAddvance(staffIdx)) {
                    (this->*event_init_tbl[actIdx])(staffIdx);
                }

                if((this->*event_action_tbl[actIdx])(staffIdx)) {
                    dComIfGp_evmng_cutEnd(staffIdx);
                }
            }
        }

        if(isEventAccept()) {
            if(dComIfGp_evmng_endCheck(field_0x7C4[field_0x7AA])) {
                dComIfGp_event_reset();
                offEventAccept();

                if(field_0x7AA == 0) {
                    returnLinkPlayer();
                    offReturnLink();
                }

                field_0x7AA = -1;
            }

            return true;
        }

        if(daPy_getPlayerLinkActorClass()->eventInfo.checkCommandDoor() == false) {
            return true;
        }
    }

    return false;
}

/* 00004228-0000422C       .text initialDefault__10daNpc_Os_cFi */
void daNpc_Os_c::initialDefault(int) {
    return;
}

/* 0000422C-00004234       .text actionDefault__10daNpc_Os_cFi */
BOOL daNpc_Os_c::actionDefault(int) {
    return true;
}

/* 00004234-000043AC       .text initialWaitEvent__10daNpc_Os_cFi */
void daNpc_Os_c::initialWaitEvent(int staffIdx) {
    field_0x7C0 = -1;

    Vec* posData = dComIfGp_evmng_getMyVec3dP(staffIdx, "pos");
    if(posData) {
        current.pos.set(posData->x, posData->y, posData->z);
    }

    u32* angleData = dComIfGp_evmng_getMyIntegerP(staffIdx, "angle");
    if(angleData) {
        s16 angle = *angleData;
        current.angle.y = angle;
        shape_angle.y = angle;
    }

    u32* gravData = dComIfGp_evmng_getMyIntegerP(staffIdx, "gravity");
    if(gravData) {
        onGravity();
        maxFallSpeed = -100.0f;
        gravity = l_HIO.field_0x8C;
    }

    u32* quakeData = dComIfGp_evmng_getMyIntegerP(staffIdx, "quake");
    if(quakeData) {
        dComIfGp_getVibration().StartShock(*quakeData, -0x11, cXyz(0.0f, 1.0f, 0.0f));
    }

    u32* timerData = dComIfGp_evmng_getMyIntegerP(staffIdx, "timer");
    if(timerData) {
        field_0x7C0 = *timerData;
    }
}

/* 000043AC-000043F0       .text actionWaitEvent__10daNpc_Os_cFi */
BOOL daNpc_Os_c::actionWaitEvent(int) {
    if(field_0x7C0 < 0) {
        return true;
    }
    
    return cLib_calcTimer(&field_0x7C0) == 0 ? TRUE : FALSE;
}

/* 000043F0-00004470       .text initialWakeupEvent__10daNpc_Os_cFi */
void daNpc_Os_c::initialWakeupEvent(int) {
    if(dComIfGp_getCb1Player() == this) {
        setWakeup();
        maxFallSpeed = -100.0f;
        gravity = l_HIO.field_0x8C;
        offNpcNotChange();
        initBrkAnm(4, true);
        field_0x7A1 = 0;
    }
}

/* 00004470-000044B0       .text actionWakeupEvent__10daNpc_Os_cFi */
BOOL daNpc_Os_c::actionWakeupEvent(int) {
    if(field_0x7A1) {
        initBrkAnm(6, true);

        return true;
    }

    return false;
}

/* 000044B0-000044D4       .text initialMoveEvent__10daNpc_Os_cFi */
void daNpc_Os_c::initialMoveEvent(int) {
    setAnm(1);
}

/* 000044D4-00004644       .text actionMoveEvent__10daNpc_Os_cFi */
BOOL daNpc_Os_c::actionMoveEvent(int staffIdx) {
    f32 value = 1.0f;
    f32* data = dComIfGp_evmng_getMyFloatP(staffIdx, "Stick");
    if(data) {
        value = *data;
    }

    if(mpPedestal) {
        if(fopAcM_searchActorDistanceXZ(this, mpPedestal) < 10.0f) {
            speedF = 0.0f;
            current.pos.x = mpPedestal->current.pos.x;
            current.pos.z = mpPedestal->current.pos.z;
            setAnm(0);
        }
        else {
            walkProc(value, fopAcM_searchActorAngleY(this, mpPedestal));
            mpMorf->setPlaySpeed(value * 2.0f);
            cLib_addCalcAngleS(&shape_angle.y, current.angle.y, l_HIO.mOs2.field_0x28, l_HIO.mOs2.field_0x24 * 2, l_HIO.mOs2.field_0x26 * 2);
            mJntCtrl.lookAtTarget(&shape_angle.y, 0, cXyz::Zero, shape_angle.y, 0, false);
        }

        setAttention(true);
    }

    return true;
}

/* 00004644-000046E4       .text initialMoveEndEvent__10daNpc_Os_cFi */
void daNpc_Os_c::initialMoveEndEvent(int staffIdx) {
    u32* data = dComIfGp_evmng_getMyIntegerP(staffIdx, "Daiza");
    if(data && mpPedestal) {
        current.pos.x = mpPedestal->current.pos.x;
        current.pos.y = mpPedestal->current.pos.y + 240.0f;
        current.pos.z = mpPedestal->current.pos.z;
    }

    speedF = 0.0f;

    setAnm(0);
}

/* 000046E4-00004748       .text initialEndEvent__10daNpc_Os_cFi */
void daNpc_Os_c::initialEndEvent(int) {
    setFinish();

    u32 temp = 0;
    setNpcAction(&finish02NpcAction, &temp);
}

/* 00004748-0000474C       .text initialTurnEvent__10daNpc_Os_cFi */
void daNpc_Os_c::initialTurnEvent(int) {
    return;
}

/* 0000474C-000047D4       .text actionTurnEvent__10daNpc_Os_cFi */
BOOL daNpc_Os_c::actionTurnEvent(int staffIdx) {
    u32* data = dComIfGp_evmng_getMyIntegerP(staffIdx, "Angle");
    if(data) {
        s16 temp = cLib_addCalcAngleS(&shape_angle.y, *data, 0x1E, 0x2000, 0x800);
        current.angle.y = shape_angle.y;
        
        if(temp == 0) {
            return true;
        }
    }

    return false;
}

/* 000047D4-00004860       .text initialFinishEvent__10daNpc_Os_cFi */
void daNpc_Os_c::initialFinishEvent(int staffIdx) {
    u32* data = dComIfGp_evmng_getMyIntegerP(staffIdx, "Type");

    u32 value = 0;
    if(data) {
        value = *data;
    }

    setAnm_brkAnm(value);
    if(field_0x78C == 2 || field_0x78C == 4) {
        makeBeam(1);
    }
    else {
        endBeam();
    }
}

/* 00004860-00004874       .text actionFinishEvent__10daNpc_Os_cFi */
BOOL daNpc_Os_c::actionFinishEvent(int) {
    return field_0x7A1 ? TRUE : FALSE;
}

/* 00004874-000048D8       .text initialMsgSetEvent__10daNpc_Os_cFi */
void daNpc_Os_c::initialMsgSetEvent(int staffIdx) {
    l_msgId = -1;

    u32* data = dComIfGp_evmng_getMyIntegerP(staffIdx, "MsgNo");
    if(data) {
        field_0x780 = *data;
    }
}

/* 000048D8-000048F8       .text actionMsgSetEvent__10daNpc_Os_cFi */
BOOL daNpc_Os_c::actionMsgSetEvent(int) {
    return talk_init();
}

/* 000048F8-00004918       .text actionMsgEndEvent__10daNpc_Os_cFi */
BOOL daNpc_Os_c::actionMsgEndEvent(int) {
    return talk();
}

/* 00004918-00004988       .text initialSwitchOnEvent__10daNpc_Os_cFi */
void daNpc_Os_c::initialSwitchOnEvent(int) {
    s8 roomNo = fopAcM_GetRoomNo(this);
    if(roomNo == 7 && !dComIfGs_isSwitch(field_0x794, roomNo)) {
        dComIfGs_onSwitch(field_0x794, roomNo);
    }
}

/* 00004988-00004A60       .text initialNextEvent__10daNpc_Os_cFi */
void daNpc_Os_c::initialNextEvent(int staffIdx) {
    u32* data = dComIfGp_evmng_getMyIntegerP(staffIdx, "SE");

    if(data) {
        u32 value = *data;
        fopAcM_seStartCurrent(this, JA_SE_OBJ_OSTATUE_PUT, 0);
    }

    if(subtype == 0) {
        field_0x7A5 = 2;
    }
    else if(subtype == 1) {
        field_0x7A5 = 4;
    }
    else if(subtype == 2) {
        field_0x7A5 = 6;
    }
}

/* 00004A60-00004AF8       .text initialSaveEvent__10daNpc_Os_cFi */
void daNpc_Os_c::initialSaveEvent(int) {
    home.pos = current.pos;
    dComIfGs_setRestartOption(&current.pos, home.angle.y, fopAcM_GetRoomNo(this), getRestartNumber());
}

/* 00004AF8-00004B64       .text talk_init__10daNpc_Os_cFv */
BOOL daNpc_Os_c::talk_init() {
    if(l_msgId == -1) {
        l_msgId = fopMsgM_messageSet(field_0x780, this);
    }
    else {
        l_msg = fopMsgM_SearchByID(l_msgId);
        if(l_msg) {
            return true;
        }
    }

    return false;
}

/* 00004B64-00004C04       .text talk__10daNpc_Os_cFv */
BOOL daNpc_Os_c::talk() {
    if(l_msg->mStatus == fopMsgStts_MSG_DISPLAYED_e) {
        l_msg->mStatus = next_msgStatus(&field_0x780);

        if(l_msg->mStatus == fopMsgStts_MSG_CONTINUES_e) {
            fopMsgM_messageSet(field_0x780);
        }
    }
    else if(l_msg->mStatus != fopMsgStts_UNK15_e && l_msg->mStatus != fopMsgStts_MSG_TYPING_e && l_msg->mStatus == fopMsgStts_BOX_CLOSED_e) {
        l_msg->mStatus = fopMsgStts_MSG_DESTROYED_e;

        return true;
    }

    return false;
}

/* 00004C04-00004D20       .text setAnm__10daNpc_Os_cFi */
void daNpc_Os_c::setAnm(int param_1) {
    struct anmPrm_c {
        /* 0x00 */ s8 mAnmTblIdx;
        /* 0x04 */ int mLoopMode;
        /* 0x08 */ f32 mMorf;
        /* 0x0C */ f32 mPlaySpeed;
        /* 0x10 */ int m10;
    };

    static s8 l_anmTbl[] = {
        6,
        6,
        5,
        0
    };

    static anmPrm_c l_anmPrm[] = {
        {
            /* mAnmTblIdx */ 0,
            /* mLoopMode  */ J3DFrameCtrl::LOOP_REPEAT_e,
            /* mMorf      */ 8.0f,
            /* mPlaySpeed */ 0.0f,
            /* m10        */ 0,
        },
        {
            /* mAnmTblIdx */ 1,
            /* mLoopMode  */ J3DFrameCtrl::LOOP_REPEAT_e,
            /* mMorf      */ 8.0f,
            /* mPlaySpeed */ 2.0f,
            /* m10        */ 0,
        },
        {
            /* mAnmTblIdx */ 2,
            /* mLoopMode  */ J3DFrameCtrl::LOOP_ONCE_e,
            /* mMorf      */ 0.0f,
            /* mPlaySpeed */ 1.0f,
            /* m10        */ 0,
        },
        {
            /* mAnmTblIdx */ 2,
            /* mLoopMode  */ J3DFrameCtrl::LOOP_ONCE_e,
            /* mMorf      */ 0.0f,
            /* mPlaySpeed */ -1.0f,
            /* m10        */ 0,
        },
        {
            /* mAnmTblIdx */ 2,
            /* mLoopMode  */ J3DFrameCtrl::LOOP_ONCE_e,
            /* mMorf      */ 0.0f,
            /* mPlaySpeed */ 0.0f,
            /* m10        */ -1,
        }
    };

    field_0x78C = param_1;
    anmPrm_c& prm = l_anmPrm[param_1];
    f32 playSpeed = prm.mPlaySpeed;
    if(prm.mAnmTblIdx != field_0x7A0 || prm.mPlaySpeed != mpMorf->getPlaySpeed()) {
        field_0x7A0 = prm.mAnmTblIdx;
        s8* temp2 = &l_anmTbl[field_0x7A0]; // fakematch
        mPrevMorfFrame = 0.0f;
        mReachedAnimEnd = false;
        dNpc_Os_setAnm(mpMorf, prm.mLoopMode, prm.mMorf, playSpeed, *temp2, "Os");

        if(prm.m10 < 0) {
            mpMorf->setFrame(mpMorf->getEndFrame());
        }
    }
}

/* 00004D20-00004DD4       .text dNpc_Os_setAnm__10daNpc_Os_cFP14mDoExt_McaMorfiffiPCc */
BOOL daNpc_Os_c::dNpc_Os_setAnm(mDoExt_McaMorf* pMorf, int loopMode, f32 morf, f32 playSpeed, int idx, const char* arcName) {
    BOOL ret = false;

    if(pMorf) {
        J3DAnmTransform* pAnimRes = (J3DAnmTransform*)dComIfG_getObjectRes(arcName, idx);
        pMorf->setAnm(pAnimRes, loopMode, morf, playSpeed, 0.0f, -1.0f, 0);
        ret = true;
    }

    return ret;
}

/* 00004DD4-00004F48       .text initBrkAnm__10daNpc_Os_cFUcb */
BOOL daNpc_Os_c::initBrkAnm(u8 param_1, bool param_2) {
    struct AnmTableEntry {
        u8 unk_1;
        u32 unk_2;
        f32 unk_3;
        s32 unk_4;
    };

    static AnmTableEntry brkAnmTbl[] = {
        {0x0F, 0x00, 1.0f, 0},
        {0x0F, 0x00, 1.0f, -1},
        {0x0D, 0x00, 1.0f, 0},
        {0x0D, 0x00, -1.0f, 0},
        {0x10, 0x00, 1.0f, 0},
        {0x10, 0x00, 0.0f, 0},
        {0x0E, 0x02, 1.0f, 0},
        {0x0D, 0x00, 0.0f, -1},
        {0x0C, 0x02, 1.0f, 0},
    };

    J3DModelData* modelData = mpMorf->getModel()->getModelData();

    bool ret = false;
    if(field_0x7A2 != param_1) {
        J3DAnmTevRegKey* a_brk = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes("Os", brkAnmTbl[param_1].unk_1));
        JUT_ASSERT(0xBB9, a_brk != 0);

        if(mBrkAnm.init(modelData, a_brk, true, brkAnmTbl[param_1].unk_2, brkAnmTbl[param_1].unk_3, 0, -1, param_2, 0)) {
            field_0x7A2 = param_1;
            if(brkAnmTbl[param_1].unk_4 < 0) {
                mBrkAnm.setFrame(mBrkAnm.getEndFrame());
            }

            field_0x764 = mBrkAnm.getFrame();
            
            ret = true;
        }
    }
    else {
        ret = true;
    }

    return ret;
}

/* 00004F48-00005048       .text playBrkAnm__10daNpc_Os_cFv */
void daNpc_Os_c::playBrkAnm() {
    field_0x7A1 = mBrkAnm.play();

    if(mBrkAnm.getPlaySpeed() < 0.0f) {
        if(mBrkAnm.getFrame() > field_0x764) {
            field_0x7A1 = 1;
        }
    }
    else if(mBrkAnm.getFrame() < field_0x764) {
        field_0x7A1 = 1;
    }

    field_0x764 = mBrkAnm.getFrame();
    if(field_0x7A2 == 6 && field_0x764 > 5.0f && field_0x764 < 50.0f) {
        fopAcM_seStartCurrent(this, JA_SE_OBJ_OSTATUE_BLINK, 0);
    }
}

/* 00005048-000050B0       .text setAnm_brkAnm__10daNpc_Os_cFi */
void daNpc_Os_c::setAnm_brkAnm(int param_1) {
    struct BrkTableEntry {
        u8 unk_1;
        u8 unk_2;
    };

    static BrkTableEntry anmBrkTbl[] = {
        {0x00, 0x00},
        {0x00, 0x01},
        {0x02, 0x02},
        {0x03, 0x03},
        {0x00, 0x04},
        {0x00, 0x05},
        {0x00, 0x06},
        {0x04, 0x07},
    };

    setAnm(anmBrkTbl[param_1].unk_1);
    initBrkAnm(anmBrkTbl[param_1].unk_2, true);
    field_0x7A1 = 0;
}

/* 000050B0-00005204       .text chkAttention__10daNpc_Os_cF4cXyzs */
BOOL daNpc_Os_c::chkAttention(cXyz param_1, s16 param_2) {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    f32 maxDist = l_HIO.mNpc.mMaxAttnDistXZ;
    s32 maxAngle = l_HIO.mNpc.mMaxAttnAngleY;

    cXyz delta;
    delta.x = player->current.pos.x - param_1.x;
    delta.z = player->current.pos.z - param_1.z;
    f32 dist = sqrtf(delta.x*delta.x + delta.z*delta.z);

    s16 angle = cM_atan2s(delta.x, delta.z);
    if(field_0x7A4) {
        maxDist += 40.0f;
        maxAngle += 0x71C;
    }

    angle -= param_2;
    BOOL ret = false;
    if(maxAngle > abs(angle) && maxDist > dist) {
        ret = true;
    }

    return ret;
}

/* 00005204-000052D4       .text chkArea__10daNpc_Os_cFP4cXyz */
bool daNpc_Os_c::chkArea(cXyz* param_1) {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    f32 maxDist = l_HIO.mNpc.mMaxAttnDistXZ;

    cXyz delta;
    delta.x = player->current.pos.x - param_1->x;
    delta.z = player->current.pos.z - param_1->z;
    f32 dist = sqrtf(delta.x*delta.x + delta.z*delta.z);

    maxDist += 40.0f;
    return maxDist > dist;
}

/* 000052D4-00005328       .text carryCheck__10daNpc_Os_cFv */
void daNpc_Os_c::carryCheck() {
    if(fopAcM_checkCarryNow(this)) {
        setNpcAction(&carryNpcAction, 0);
    }
}

/* 00005328-000053C8       .text eventOrder__10daNpc_Os_cFv */
void daNpc_Os_c::eventOrder() {
    if(!isEventAccept()) {
        if(field_0x7A5 == 0x12 || field_0x7A5 == 0x11) {
            eventInfo.onCondition(dEvtCnd_CANTALK_e);

            if(field_0x7A5 == 0x12) {
                fopAcM_orderSpeakEvent(this);
            }
        }
        else if(field_0x7A5 != -1 && field_0x7A5 < 0x10) {
            field_0x7AA = field_0x7A5;
            fopAcM_orderOtherEventId(this, field_0x7C4[field_0x7AA]);
        }
    }
}

/* 000053C8-00005454       .text checkOrder__10daNpc_Os_cFv */
void daNpc_Os_c::checkOrder() {
    if(eventInfo.checkCommandTalk() && (field_0x7A5 == 0x12 || field_0x7A5 == 0x11)) {
        field_0x7A5 = 0xFF;
        setNpcAction(&talkNpcAction, 0);
        fopAcM_cancelCarryNow(this);
    }
}

/* 00005454-00005468       .text checkCommandTalk__10daNpc_Os_cFv */
BOOL daNpc_Os_c::checkCommandTalk() {
    return eventInfo.checkCommandTalk() ? TRUE : FALSE;
}

/* 00005468-000054BC       .text next_msgStatus__10daNpc_Os_cFPUl */
u16 daNpc_Os_c::next_msgStatus(u32* pMsgNo) {
    u16 status = fopMsgStts_MSG_CONTINUES_e;

    if(*pMsgNo == 0) {
        status = fopMsgStts_MSG_ENDS_e;
    }
    else if(*pMsgNo == 0xEF4) {
        dComIfGs_onEventBit(0x2510);
        status = fopMsgStts_MSG_ENDS_e;
    }

    return status;
}

/* 000054BC-000054C4       .text getMsg__10daNpc_Os_cFv */
u32 daNpc_Os_c::getMsg() {
    return 0;
}

/* 000054C4-0000557C       .text setCollision__10daNpc_Os_cFv */
void daNpc_Os_c::setCollision() {
    cXyz dummy(0.0f, 0.0f, 0.0f);
    cXyz temp = current.pos;
    mCyl.SetC(temp);
    mCyl.SetR(30.0f);
    mCyl.SetH(field_0x788);

    if(dComIfGp_getPlayer(0) == this) {
        mStts.SetWeight(0xFE);
    }
    else {
        mStts.SetWeight(0xFF);
    }

    dComIfG_Ccsp()->Set(&mCyl);
}

/* 0000557C-000055D4       .text setAttention__10daNpc_Os_cFb */
void daNpc_Os_c::setAttention(bool param_1) {
    if(!param_1 && field_0x7A3 >= 2) {
        return;
    }

    eyePos.set(field_0x748.x, field_0x748.y, field_0x748.z);
    attention_info.position.set(current.pos.x, current.pos.y + l_HIO.mNpc.mAttnYOffset, current.pos.z);
}

/* 000055D4-000056F4       .text lookBack__10daNpc_Os_cFiii */
void daNpc_Os_c::lookBack(int param_1, int param_2, int param_3) {
    cXyz* dstPos = NULL;
    cXyz temp2;
    cXyz temp(0.0f, 0.0f, 0.0f);
    s16 targetY = shape_angle.y;
    
    if(mJntCtrl.trnChk()) {
        cLib_addCalcAngleS2(&field_0x798, l_HIO.mNpc.mMaxHeadTurnVel, 4, 0x800);
    }
    else {
        field_0x798 = 0;
    }

    if(param_1) {
        temp2 = dNpc_playerEyePos(l_HIO.mNpc.m04);
        dstPos = &temp2;
        temp = current.pos;
        temp.y = eyePos.y;
    }

    mJntCtrl.lookAtTarget(&shape_angle.y, dstPos, temp, targetY, field_0x798, param_3);
}

/* 000056F4-00005824       .text setBaseMtx__10daNpc_Os_cFv */
void daNpc_Os_c::setBaseMtx() {
    J3DModel* pModel = mpMorf->getModel();
    if(fopAcM_checkCarryNow(this)) {
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::YrotM(shape_angle.y);
        mDoMtx_stack_c::transM(field_0x7E4);
        mDoMtx_stack_c::XrotM(shape_angle.x);
        mDoMtx_stack_c::ZrotM(shape_angle.z);
    }
    else {
        mDoMtx_stack_c::transS(current.pos.x, current.pos.y + 95.0f, current.pos.z);
        mDoMtx_stack_c::YrotM(shape_angle.y);
        mDoMtx_stack_c::transM(field_0x7E4);
        mDoMtx_stack_c::XrotM(shape_angle.x);
        mDoMtx_stack_c::ZrotM(shape_angle.z);
        mDoMtx_stack_c::transM(0.0f, -95.0f, 0.0f);
    }

    pModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
}

static const char* event_name_tbl[] = {
    "OPTION_CHAR_END",
    "Os_Wakeup",
    "Os_Finish",
    "Os1_Wakeup",
    "Os1_Finish",
    "Os2_Wakeup",
    "Os2_Finish",
    "Os_Message",
    "Os1_Message",
    "Os2_Message",
    "Os_Finit0",
    "Os_Finit1",
    "Os1_Finit0",
    "Os1_Finit1",
    "Os2_Finit0",
    "Os2_Finit1"
};

/* 00005824-00005B58       .text init__10daNpc_Os_cFv */
BOOL daNpc_Os_c::init() {
    cXyz dummy(0.0f, 0.0f, 0.0f);

    field_0x794 = fopAcM_GetParam(this) >> 0x10 & 0xFF;
    attention_info.distances[4] = 0x27;
    // Fakematch, the next two lines get optimized out, but they affect the regalloc when copying the tevstr.
    speedF = speedF;
    speedF = speedF;
    m_smoke_tevstr = tevStr;
    m_smoke.setTevStr(&m_smoke_tevstr);
    m_playerRoom[subtype] = false;
    clearStatus();
    gravity = l_HIO.field_0x8C;
    field_0x7A0 = 3;
    field_0x78C = 5;
    if(wakeupCheck()) {
        onGravity();
    }
    else {
        offGravity();
    }

    if(finishCheck()) {
        setNpcAction(&finish02NpcAction, 0);
    }
    else {
        setAnm(0);
        setNpcAction(&waitNpcAction, 0);
    }

    field_0x754 = current.pos;
    field_0x748 = current.pos;

    field_0x7AA = -1;
    field_0x7A5 = -1;
    field_0x788 = 120.0f;
    mpPedestal = NULL;
    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);
    for(int i = 0; i < 0x10; i++) {
        field_0x7C4[i] = dComIfGp_evmng_getEventIdx(event_name_tbl[i], -1);
    }

    return true;
}

/* 00005B58-00005CC8       .text draw__10daNpc_Os_cFv */
BOOL daNpc_Os_c::draw() {
    if(fopAcM_GetHomeRoomNo(this) < 0) {
        return true;
    }
    else if(finishCheck() && mpPedestal == NULL) {
        return true;
    } 
    else if(!dComIfGp_roomControl_checkStatusFlag(fopAcM_GetRoomNo(this), 0x10)) {
        return true;
    }

    J3DModel* pModel = mpMorf->getModel();
    J3DModelData* pModelData = pModel->getModelData();

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(pModel, &tevStr);
    
    mBrkAnm.entry(pModelData, mBrkAnm.getFrame());
    mpMorf->entryDL();
    mBrkAnm.remove(pModelData);

    if(!fopAcM_checkCarryNow(this) && field_0x784 & 0x10) {
        cXyz shadowPos(current.pos.x, current.pos.y + 150.0f, current.pos.z);

        mShadowId = dComIfGd_setShadow(
            mShadowId, 0, pModel, &shadowPos, 800.0f, 20.0f,
            current.pos.y, mAcch.GetGroundH(), mAcch.m_gnd, &tevStr,
            0, 1.0f, dDlst_shadowControl_c::getSimpleTex()
        );
    }

    return true;
}

/* 00005CC8-00005DF4       .text animationPlay__10daNpc_Os_cFv */
void daNpc_Os_c::animationPlay() {
    u32 mtrlSndId = 0;
    if (field_0x784 & 0x10 && mAcch.ChkGroundHit() && dComIfG_Bgsp()->ChkPolySafe(mAcch.m_gnd)) {
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

    if(field_0x78C == 1 && mpMorf->checkFrame(17.0f)) {
        smokeSet(0xA328);
    }

    playBrkAnm();
}

/* 00005DF4-00005E5C       .text smokeSet__10daNpc_Os_cFUs */
void daNpc_Os_c::smokeSet(u16 particle) {
    dComIfGp_particle_set(particle, &current.pos, 0, 0, -1, &m_smoke);
}

/* 00005E5C-00006AF8       .text execute__10daNpc_Os_cFv */
BOOL daNpc_Os_c::execute() {
    static JGeometry::TVec3<f32> splash_scale(0.6f, 0.6f, 0.6f);
    static JGeometry::TVec3<f32> ripple_scale(1.0f, 1.0f, 1.0f);

    field_0x784 &= ~0x10;
    fopAcM_OffStatus(this, fopAcStts_SHOWMAP_e);
    checkPlayerRoom();
    if(!finishCheck()) {
        if(!check_initialRoom()) {
            if(dComIfGp_getCb1Player() == this) {
                dComIfGp_setCb1Player(NULL);
            }

            endBeam();
            return true;
        }

        initialRestartOption(getRestartNumber(), TRUE);

        if(wakeupCheck()) {
            offNpcNotChange();
        }
        else {
            onNpcNotChange();
        }
    }

    fopAcM_setStageLayer(this);

    if(chkNpcAction(&carryNpcAction)) {
        mAcchCir[0].SetWallR(15.0f);
        mAcchCir[1].SetWallR(15.0f);
    }
    else {
        mAcchCir[0].SetWallR(40.0f);
        mAcchCir[1].SetWallR(40.0f);
    }

    mpPedestal = (daPedestal::daPds_c*)searchFromName(l_daiza_name[subtype], 0xFF, 1);
    if(mpPedestal) {
        if(!isFinish()) {
            if(finishCheck()) {
                home.pos.x = mpPedestal->current.pos.x;
                home.pos.y = mpPedestal->current.pos.y + 240.0f;
                home.pos.z = mpPedestal->current.pos.z;
            }
        }
        else if(!isSetHomePos()) {
            home.pos.x = mpPedestal->current.pos.x;
            home.pos.y = mpPedestal->current.pos.y + 240.0f;
            home.pos.z = mpPedestal->current.pos.z;

            s32 pedestalHomeRoom = fopAcM_GetHomeRoomNo(mpPedestal);
            if(pedestalHomeRoom != fopAcM_GetHomeRoomNo(this)) {
                fopAcM_SetHomeRoomNo(this, pedestalHomeRoom);
            }
            if(pedestalHomeRoom != fopAcM_GetRoomNo(this)) {
                fopAcM_SetRoomNo(this, pedestalHomeRoom);
            }

            mAcch.CrrPos(*dComIfG_Bgsp());
            
            field_0x784 |= 0x10;
            if(mAcch.GetGroundH() != -1.0e9f) {
                tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mAcch.m_gnd);
                tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mAcch.m_gnd);

                onSetHomePos();
            }
        }
    }

    if(finishCheck()) {
        if(isFinish()) {
            current.pos = home.pos;
        }

        s32 roomNo = fopAcM_GetRoomNo(this);
        BOOL flag = dComIfGp_roomControl_checkStatusFlag(roomNo, 0x10);
        if(roomNo < 0 || !flag || mpPedestal == NULL) {
            endBeam();

            return true;
        }
    }
    else {
        if(check_moveStop()) {
            setNpcAction(&waitNpcAction, 0);
            field_0x7A3 = 0;
            endBeam();

            return true;
        }

        if(field_0x7A8 && dComIfG_Bgsp()->ChkPolySafe(field_0x7FC) && dComIfG_Bgsp()->ChkMoveBG(field_0x7FC)) {
            cXyz dummy = old.pos;

            dComIfG_Bgsp()->MoveBgCrrPos(field_0x7FC, true, &old.pos, 0, 0);
        }
    }

    fopAcM_SetStatusMap(this, 0xE);
    mJntCtrl.setParam(l_HIO.mNpc.mMaxBackboneX, l_HIO.mNpc.mMaxBackboneY, l_HIO.mNpc.mMinBackboneX, l_HIO.mNpc.mMinBackboneY,l_HIO.mNpc.mMaxHeadX, l_HIO.mNpc.mMaxHeadY, l_HIO.mNpc.mMinHeadX, l_HIO.mNpc.mMinHeadY, l_HIO.mNpc.mMaxTurnStep);

    if(!isFinish()) {
        if(!fopAcM_checkCarryNow(this) && isGravity() && checkNowPosMove(l_staff_name[subtype])) {
            if (maxFallSpeed < speed.y) {
                speed.y -= gravity;
                if (speed.y < maxFallSpeed) {
                    speed.y = maxFallSpeed;
                }
            } else if (maxFallSpeed > speed.y) {
                speed.y += gravity;
                if (speed.y > maxFallSpeed) {
                    speed.y = maxFallSpeed;
                }
            }

            speed.x = speedF * cM_ssin(current.angle.y);
            speed.z = speedF * cM_scos(current.angle.y);

            fopAcM_posMove(this, mStts.GetCCMoveP());
        }
        
    
        mAcch.CrrPos(*dComIfG_Bgsp());
        field_0x784 |= 0x10;

        if(chkPlayerAction(&walkPlayerAction) || chkNpcAction(&searchNpcAction)) {
            if(!mAcch.ChkGroundHit()) {
                f32 gndY = mAcch.GetGroundH();
                f32 delta = gndY - current.pos.y;
                if(delta < 0.0f && delta >= -30.1f) {
                    current.pos.y = gndY;
                    mAcch.SetGroundHit();
                    speed.y = 0.0f;
                }
            }
        }

        if(mAcch.GetGroundH() != -1.0e9f) {
            cM3dGPla* plane = dComIfG_Bgsp()->GetTriPla(mAcch.m_gnd.GetBgIndex(), mAcch.m_gnd.GetPolyIndex());
            if(plane) {
                field_0x7F0 = *plane->GetNP();
            }

            s8 roomNo = dComIfG_Bgsp()->GetRoomId(mAcch.m_gnd);
            fopAcM_SetRoomNo(this, roomNo);
            tevStr.mRoomNo = roomNo;
            tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mAcch.m_gnd);
            mStts.SetRoomId(roomNo);
            field_0x7FC.SetPolyInfo(mAcch.m_gnd);

            if(roomNo != 7) {
                mpPedestal = NULL;
            }
        }

        field_0x7A8 = mAcch.ChkGroundHit();
        if(!fopAcM_checkCarryNow(this)) {
            if(mAcch.GetGroundH() == -1.0e9f || dComIfG_Bgsp()->GetGroundCode(mAcch.m_gnd) == 4) {
                if(m4E8 < 30) {
                    m4E8 += 1;
                }
                else if(!dComIfGp_roomControl_checkStatusFlag(fopAcM_GetHomeRoomNo(this), 0x10)) {
                    current = home;
                    shape_angle = home.angle;
                    speedF = 0.0f;
                    m4E8 = 0;
                }
                else {
                    daPy_getPlayerLinkActorClass()->startRestartRoom(5, 0xC9, -1.0f, 0);
                }
            }
            else {
                m4E8 = 0;
            }
            
            if(mAcch.ChkWaterIn()) {
                daPy_getPlayerLinkActorClass()->startRestartRoom(5, 0xC9, -1.0f, 0);

                if(!isWaterHit()) {
                    onWaterHit();

                    JPABaseEmitter* splash = dComIfGp_particle_set(0x40, &current.pos);
                    if(splash) {
                        splash->setRate(15.0f);
                        splash->setGlobalScale(splash_scale);
                    }

                    JPABaseEmitter* ripple = dComIfGp_particle_setSingleRipple(0x3D, &current.pos);
                    if(ripple) {
                        ripple->setGlobalScale(ripple_scale);
                    }
                }
            }
        }
    }
    else {
        mAcch.CrrPos(*dComIfG_Bgsp());

        field_0x784 |= 0x10;
        if(mAcch.GetGroundH() != -1.0e9f) {
            tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mAcch.m_gnd);
            tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mAcch.m_gnd);
        }
    }

    if(!fopAcM_checkCarryNow(this)) {
        setCollision();
    }

    if(checkNowPosMove(l_staff_name[subtype])) {
        animationPlay();
    }

    if(!eventProc()) {
        if(!finishCheck()) {
            if(dComIfGp_getPlayer(0) == this) {
                fopAcM_SetStatusMap(this, 0x13);

                if(isReturnLink()) {
                    field_0x7A5 = 0;
                }
                else {
                    playerAction(0);
                    if(returnLinkCheck()) {
                        returnLink();
                    }
                }
            }
            else {
                if(wakeupCheck()) {
                    fopAcM_SetStatusMap(this, 0xE);
                }

                carryCheck();
                checkOrder();
                npcAction(0);

                if(!chkNpcAction(&throwNpcAction)) {
                    current.angle.y = shape_angle.y;
                }
            }

            checkGoalRoom();
        }

        if(field_0x78C == 2 || field_0x78C == 4) {
            makeBeam(0);
        }
        else {
            endBeam();
        }

        eventOrderCheck();
    }

    eventOrder();
    setBaseMtx();
    if(field_0x738.getEmitter() || field_0x740.getEmitter()) {
        fopAcM_seStartCurrent(this, JA_SE_OBJ_OSTATUE_LIGHT_SUS, 0);
    }

    m_smoke_tevstr = tevStr;

    return true;
}

/* 00006AF8-00006E1C       .text __dt__10daNpc_Os_cFv */
daNpc_Os_c::~daNpc_Os_c() {
    dComIfG_resDelete(&mPhs, "Os");

    if (heap) {
        mpMorf->stopZelAnime();
    }

    endBeam();
    m_smoke.remove();
    if(l_hio_counter != 0) {
        l_hio_counter -= 1;
    }
    
    if(l_hio_counter <= 0 && l_HIO.field_0x04 >= 0) {
        mDoHIO_root.mDoHIO_deleteChild(l_HIO.field_0x04);
        l_HIO.field_0x04 = -1;
    }

    m_playerRoom[subtype] = false;
    m_cattleRoomNo = -1;
}

/* 00006E1C-00006E3C       .text daNpc_Os_Create__FP10fopAc_ac_c */
static s32 daNpc_Os_Create(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Os_c*>(i_this)->create();
}

/* 00006E3C-00006E64       .text daNpc_Os_Delete__FP10daNpc_Os_c */
static BOOL daNpc_Os_Delete(daNpc_Os_c* i_this) {
    i_this->~daNpc_Os_c();
    return true;
}

/* 00006E64-00006EA8       .text daNpc_Os_Execute__FP10daNpc_Os_c */
static BOOL daNpc_Os_Execute(daNpc_Os_c* i_this) {
    BOOL ret = i_this->execute();

    if(i_this->subtype == 2) {
        i_this->setCattleRoomNo(fopAcM_GetRoomNo(i_this));
    }

    return ret;
}

/* 00006EA8-00006EC8       .text daNpc_Os_Draw__FP10daNpc_Os_c */
static BOOL daNpc_Os_Draw(daNpc_Os_c* i_this) {
    return  i_this->draw();
}

/* 00006EC8-00006ED0       .text daNpc_Os_IsDelete__FP10daNpc_Os_c */
static BOOL daNpc_Os_IsDelete(daNpc_Os_c* i_this) {
    return true;
}

/* 00006ED0-00006F04       .text end__28daNpc_Os_infiniteEcallBack_cFv */
void daNpc_Os_infiniteEcallBack_c::end() {
    if(mpBaseEmitter) {
        mpBaseEmitter->becomeInvalidEmitter();
        mpBaseEmitter->setEmitterCallBackPtr(0);
        mpBaseEmitter = NULL;
    }
}

/* 00006F04-00006F8C       .text makeEmitter__28daNpc_Os_infiniteEcallBack_cFUsPC4cXyzPC5csXyzPC4cXyz */
void daNpc_Os_infiniteEcallBack_c::makeEmitter(u16 param_1, const cXyz* param_2, const csXyz* param_3, const cXyz* param_4) {
    end();
    dComIfGp_particle_set(param_1, param_2, param_3, param_4, -1, this);
}

/* 00007A10-00007A14       .text execute__28daNpc_Os_infiniteEcallBack_cFP14JPABaseEmitter */
void daNpc_Os_infiniteEcallBack_c::execute(JPABaseEmitter*) {
    return;
}

/* 00007A14-00007A1C       .text setup__28daNpc_Os_infiniteEcallBack_cFP14JPABaseEmitterPC4cXyzPC5csXyzSc */
void daNpc_Os_infiniteEcallBack_c::setup(JPABaseEmitter* pEmitter, const cXyz*, const csXyz*, signed char) {
    mpBaseEmitter = pEmitter;
}

static actor_method_class l_daNpc_Os_Method = {
    (process_method_func)daNpc_Os_Create,
    (process_method_func)daNpc_Os_Delete,
    (process_method_func)daNpc_Os_Execute,
    (process_method_func)daNpc_Os_IsDelete,
    (process_method_func)daNpc_Os_Draw,
};

actor_process_profile_definition g_profile_NPC_OS = {
    fpcLy_CURRENT_e,
    7,
    fpcPi_CURRENT_e,
    PROC_NPC_OS,
    &g_fpcLf_Method.base,
    sizeof(daNpc_Os_c),
    0,
    0,
    &g_fopAc_Method.base,
    0x013D,
    &l_daNpc_Os_Method,
    fopAcStts_UNK8000000_e | fopAcStts_UNK2000000_e | fopAcStts_UNK40000_e | fopAcStts_UNK4000_e | fopAcStts_FREEZE_e | fopAcStts_CULL_e,
    fopAc_ACTOR_e,
    fopAc_CULLBOX_0_e,
};
