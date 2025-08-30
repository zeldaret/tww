/**
 * d_a_npc_cb1.cpp
 * Player - Makar
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_cb1.h"
#include "d/actor/d_a_obj_vmc.h"
#include "d/actor/d_a_ship.h"
#include "d/d_camera.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo_wether.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"
#include "d/d_s_play.h"
#include "d/d_snap.h"
#include "f_op/f_op_camera.h"
#include "m_Do/m_Do_controller_pad.h"
#include "d/actor/d_a_player_main.h"
#include "d/res/res_cb.h"

daNpc_Cb1_HIO_c l_HIO;

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WIND & ~AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsPlayer_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
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
        /* Radius */ 30.0f,
        /* Height */ 80.0f,
    }},
};


static dCcD_SrcCyl l_wind_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsPlayer_e,
        /* SrcObjCo  SPrm    */ 0,
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
        /* Radius */ 30.0f,
        /* Height */ 80.0f,
    }},
};


/* 000000EC-0000031C       .text __ct__15daNpc_Cb1_HIO_cFv */
daNpc_Cb1_HIO_c::daNpc_Cb1_HIO_c() {
    mNpc.m04 = -20.0f;
    mNpc.mMaxHeadX = 0;
    mNpc.mMaxHeadY = 0;
    mNpc.mMaxBackboneX = 0xBB8;
    mNpc.mMaxBackboneY = 0x1770;
    mNpc.mMinHeadX = 0;
    mNpc.mMinHeadY = 0;
    mNpc.mMinBackboneX = -0x3E8;
    mNpc.mMinBackboneY = -0x1770;
    mNpc.mMaxTurnStep = 0x7D0;
    mNpc.mMaxHeadTurnVel = 0x7D0;
    mNpc.mAttnYOffset = 65.0f;
    mNpc.mMaxAttnAngleY = 0x4000;
    mNpc.m22 = 0;
    mNpc.mMaxAttnDistXZ = 180.0f;
    field_0x30 = 50.0f;
    mPlayerChaseDistance = 140.0f;
    mChaseDistScale = 0.05f;
    mMaxWalkSpeed = 9.0f;
    mMinWalkSpeed = 3.0f;
    mForwardAccel = 0.4f;
    field_0xE8 = 0x8FC;
    field_0xEA = 0x320;
    field_0xEC = 0x3;
    mDecelScale = 0.9f;
    mMaxDecel = 1.0f;
    mDecel = 1.0f;
    mWalkAnmSpeedScale = 0.45f;
    mMaxWalkAnmSpeed = 0.9f;
    mNpcFlyLaunchSpeedF = 50.0f;
    mNpcFlyLaunchSpeedY = 20.0f;
    field_0x64 = 8.0f;
    mHitSpeedScaleF = -1.0f;
    mHitSpeedScaleY = 3.5f;
    field_0x70 = -4.0f;
    field_0x74 = -1.5f;
    field_0x78 = -6.0f;
    field_0x7C = -7.6f;
    field_0x80 = 0.1f;
    field_0x84 = 0.2f;
    mStickWalkSpeedScale = 10.0f;
    field_0xC8 = -0x1000;
    mPlayerFlyTimer = 0x1C2;
    field_0xCC = 0x64;
    field_0xCE = 0xF;
    field_0xD0 = 0x4E20;
    field_0xD2 = 0x190;
    field_0xD4 = 0x9C4;
    field_0xD6 = 0xC8;
    field_0x8C = 0.0002f;
    field_0x90 = -15.0f;
    field_0x98 = 10.0f;
    field_0x9C = 10.0f;
    field_0xA0 = -2.5f;
    field_0xD8 = 1;
    field_0xA4 = 100.0f;
    field_0xA8 = 6000.0f;
    field_0xE0 = 0xC8;
    mStickFlySpeedScale = 0.5f;
    field_0xDA = 0x2968;
    field_0xB0 = 34.0f;
    field_0xB4 = 2.0f;
    mNpcFlyTimer = 0x3C;
    field_0xDE = 0xD;
    field_0xB8 = 2.0f;
    mFlyLaunchSpeedY = 50.0f;
    field_0xC0 = 400.0f;
    field_0xE2 = 0x5;
    field_0xE4 = 0x14;
    field_0xE6 = 0xBB8;
    field_0xC4 = 20.0f;
    mDamageTimer = 0x3C;
    field_0xEF = 0;
    mNo = -1;
}

/* 0000031C-00000424       .text isTagCheckOK__11daNpc_Cb1_cFv */
BOOL daNpc_Cb1_c::isTagCheckOK() {
    if(chkNpcAction(&daNpc_Cb1_c::waitNpcAction) || chkNpcAction(&daNpc_Cb1_c::searchNpcAction)) {
        return TRUE;
    }

    if(chkNpcAction(&daNpc_Cb1_c::carryNpcAction) && !daPy_getPlayerLinkActorClass()->checkCarryActionNow()) {
        return TRUE;
    }

    return FALSE;
}

/* 00000424-000004D8       .text setMessageAnimation__11daNpc_Cb1_cFUc */
void daNpc_Cb1_c::setMessageAnimation(u8 param_1) {
    if(!fopAcM_checkCarryNow(this) && dComIfGp_event_runCheck()) {
        int staffIdx = dComIfGp_evmng_getMyStaffId("Cb1");
        if(staffIdx != -1 && strcmp(dComIfGp_evmng_getMyActName(staffIdx), "WAIT") == 0) {
            setAnm(getAnmType(param_1));
        }
    }
}

/* 000004D8-000004F8       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Cb1_c*>(i_this)->createHeap();
}

/* 000004F8-00000814       .text create__11daNpc_Cb1_cFv */
cPhs_State daNpc_Cb1_c::create() {
    fopAcM_SetupActor(this, daNpc_Cb1_c);

    if(!isTypeBossDie()) {
#if VERSION == VERSION_DEMO
        if(dComIfGs_isStageBossEnemy(dSv_save_c::STAGE_WT))
#else
        if(dComIfGs_checkGetItem(dItem_MASTER_SWORD_3_e))
#endif
        {
            if(!isTypeKazeBoss()) {
                return cPhs_ERROR_e;
            }
        }
        else if(dComIfGs_isEventBit(0x2910)) {
            if(!isTypeKaze()) {
                return cPhs_ERROR_e;
            }
        }
        else if(dComIfGs_isEventBit(0x2E02)) {
            if(!isTypeEkaze()) {
                return cPhs_ERROR_e;
            }
        }
        else if(dComIfGs_isEventBit(0x1610)) {
            if(strcmp(dComIfGp_getStartStageName(), "sea") != 0 || !dComIfGs_isEventBit(0x1604)) {
                return cPhs_ERROR_e;
            }
        }
        else if(dComIfGs_checkGetItem(dItem_MASTER_SWORD_2_e)) {
            if(!isTypeWaterFall()) {
                return cPhs_ERROR_e;
            }
        }
        else if(dComIfGs_isEventBit(0x1820)) {
            return cPhs_ERROR_e;
        }
        else if(dComIfGs_checkGetItem(dItem_PEARL_FARORE_e)) {
            if(!isTypeForest()) {
                return cPhs_ERROR_e;
            }
        }
        else {
            return cPhs_ERROR_e;
        }
    }

    cPhs_State result = dComIfG_resLoad(&mPhs, "Cb");
    if(result == cPhs_COMPLEATE_e) {
        if(isTypeKaze()) {
            if(dComIfGs_getPlayerPriestFlag() == 1) {
                dComIfGs_setRestartOption(&dComIfGs_getPlayerPriestPos(), dComIfGs_getPlayerPriestRotate(), dComIfGs_getPlayerPriestRoomNo(), 1);
            }

            checkRestart(1);
        }

        if(dComIfGp_getCb1Player()) {
            return cPhs_ERROR_e;
        }

#if VERSION == VERSION_DEMO
        if(isTypeForest() || isTypeWaterFall() || isTypeEkaze() || isTypeKaze())
#else
        if(isTypeKazeBoss() || isTypeForest() || isTypeWaterFall() || isTypeEkaze() || isTypeKaze())
#endif
        {
            onMusic();
        }

        if(!fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x9400)) {
            return cPhs_ERROR_e;
        }

        setBaseMtx();
        fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
        
        if(!init()) {
            return cPhs_ERROR_e;
        }

        fopAcM_setStageLayer(this);

        if(l_HIO.mNo < 0) {
            l_HIO.mNo = mDoHIO_createChild("マコレ", &l_HIO);
        }
    }

    return result;
}

/* 00000814-00000984       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        J3DModel* model = j3dSys.getModel();

        daNpc_Cb1_c* a_this = (daNpc_Cb1_c*)model->getUserArea();
        if (a_this != NULL) {
            static cXyz l_offsetAttPos(0.0f, 0.0f, 0.0f);
            static cXyz l_offsetEyePos(20.0f, 10.0f, 0.0f);

            s32 jnt_no = joint->getJntNo();
            mDoMtx_stack_c::copy(model->getAnmMtx(jnt_no));
            mDoMtx_stack_c::XrotM(a_this->getBackbone_y());
            mDoMtx_stack_c::ZrotM(-a_this->getBackbone_x());
            mDoMtx_stack_c::multVec(&l_offsetEyePos, &a_this->getEyePos());

            a_this->incAttnSetCount();

            cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
            model->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
        }
    }

    return TRUE;
}

/* 00000984-00000CF4       .text nutNodeCallBack__FP7J3DNodei */
static BOOL nutNodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        J3DModel* model = j3dSys.getModel();

        daNpc_Cb1_c* a_this = (daNpc_Cb1_c*)model->getUserArea();
        if (a_this != NULL) {
            static cXyz l_nutOffset(0.0f, 0.0f, 0.0f);
            static cXyz l_nutBase(1.0f, 0.0f, 0.0f);

            s32 jnt_no = joint->getJntNo();

            cXyz temp2(model->getAnmMtx(jnt_no)[0][3], model->getAnmMtx(jnt_no)[1][3], model->getAnmMtx(jnt_no)[2][3]);
            a_this->getNutPos() += a_this->getNusSpeed();
            cXyz temp = a_this->getNutPos() - temp2;

            f32 temp4 = temp.abs();
            f32 f1;
            if(!cM3d_IsZero(temp4)) {
                f1 = 14.0f / temp4;
                temp *= f1;
            }

            a_this->getNutPos() = temp2 + temp;

            a_this->getNusSpeed() += temp * -0.15f;
            a_this->getNusSpeed().y += -1.3f;

            f32 temp5 = a_this->getNusSpeed().abs();
            if(!cM3d_IsZero(temp5)) {
                f1 = 5.8f / temp5;
                a_this->getNusSpeed() *= f1;
            }

            Mtx temp3;
            cM3d_UpMtx_Base(l_nutBase, temp, temp3);
            model->getAnmMtx(jnt_no)[0][0] = temp3[0][0];
            model->getAnmMtx(jnt_no)[0][1] = temp3[0][1];
            model->getAnmMtx(jnt_no)[0][2] = temp3[0][2];
            model->getAnmMtx(jnt_no)[1][0] = temp3[1][0];
            model->getAnmMtx(jnt_no)[1][1] = temp3[1][1];
            model->getAnmMtx(jnt_no)[1][2] = temp3[1][2];
            model->getAnmMtx(jnt_no)[2][0] = temp3[2][0];
            model->getAnmMtx(jnt_no)[2][1] = temp3[2][1];
            model->getAnmMtx(jnt_no)[2][2] = temp3[2][2];
            cMtx_copy(model->getAnmMtx(jnt_no), J3DSys::mCurrentMtx);
        }
    }

    return TRUE;
}

static fpc_ProcID l_msgId;
static msg_class* l_msg;

/* 00000CF4-00000D9C       .text ppNodeCallBack__FP7J3DNodei */
static BOOL ppNodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        J3DModel* model = j3dSys.getModel();

        daNpc_Cb1_c* a_this = (daNpc_Cb1_c*)model->getUserArea();
        if (a_this != NULL) {
            s32 jnt_no = joint->getJntNo();
            mDoMtx_stack_c::YrotS(a_this->getWork3());
            mDoMtx_stack_c::revConcat(model->getAnmMtx(jnt_no));
            cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
            model->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
        }
    }

    return TRUE;
}

/* 00000D9C-00001458       .text createHeap__11daNpc_Cb1_cFv */
BOOL daNpc_Cb1_c::createHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Cb", CB_BDL_CB);
    JUT_ASSERT(DEMO_SELECT(937, 936), modelData != NULL);

    mpMorf = new mDoExt_McaMorf(
            modelData,
            NULL, NULL,
            NULL,
            -1, 1.0f, 0, -1, 1,
            NULL,
            0x00080000,
            0x11000022
        );

    if(mpMorf == NULL || mpMorf->getModel() == NULL) {
        return FALSE;
    }

    m_backbone_jnt_num = modelData->getJointName()->getIndex("backbone");
    JUT_ASSERT(DEMO_SELECT(949, 948), m_backbone_jnt_num >= 0);

    m_armRend_jnt_num = modelData->getJointName()->getIndex("armRend");
    JUT_ASSERT(DEMO_SELECT(952, 951), m_armRend_jnt_num >= 0);

    m_armL2_jnt_num = modelData->getJointName()->getIndex("armL2");
    JUT_ASSERT(DEMO_SELECT(955, 954), m_armL2_jnt_num >= 0);

    modelData->getJointNodePointer(m_backbone_jnt_num)->setCallBack(nodeCallBack);

    mpMorf->getModel()->setUserArea((u32)this);

    mpFaceModel = mDoExt_J3DModel__create((J3DModelData*)dComIfG_getObjectRes("Cb", CB_BDL_CB_FACE), 0x00080000, 0x11000022);
    if(mpFaceModel == NULL) {
        return FALSE;
    }

    if(isMusic()) {
        modelData = (J3DModelData*)dComIfG_getObjectRes("Cb", CB_BDL_CB_STICK);
        JUT_ASSERT(DEMO_SELECT(973, 972), modelData != NULL);
        mpStickModel = mDoExt_J3DModel__create(modelData, 0x00080000, 0x11000022);
        if(mpStickModel == NULL) {
            return FALSE;
        }

        m_nut_jnt_num = modelData->getJointName()->getIndex("nut");
        JUT_ASSERT(DEMO_SELECT(983, 982), m_nut_jnt_num >= 0);
        modelData->getJointNodePointer(m_nut_jnt_num)->setCallBack(nutNodeCallBack);

        mpStickModel->setUserArea((u32)this);

        modelData = (J3DModelData*)dComIfG_getObjectRes("Cb", CB_BDL_CB_CELLO);
        JUT_ASSERT(DEMO_SELECT(990, 989), modelData != NULL);
        mpCelloModel = mDoExt_J3DModel__create(modelData, 0x00080000, 0x11000022);
        if(mpCelloModel == NULL) {
            return FALSE;
        }
    }

    modelData = (J3DModelData*)dComIfG_getObjectRes("Cb", CB_BDL_PP);
    JUT_ASSERT(DEMO_SELECT(1002, 1001), modelData != NULL);
    mpPropellerModel = mDoExt_J3DModel__create(modelData, 0x00080000, 0x11000022);
    if(mpPropellerModel == NULL) {
        return FALSE;
    }

    m_center_jnt_num = modelData->getJointName()->getIndex("center");
    modelData->getJointNodePointer(m_center_jnt_num)->setCallBack(ppNodeCallBack);

    mpPropellerModel->setUserArea((u32)this);

    if(!mPropellerBckAnim.init(modelData, (J3DAnmTransform*)dComIfG_getObjectRes("Cb", CB_BCK_M_OPEN), FALSE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false)) {
        return FALSE;
    }

    modelData = (J3DModelData*)dComIfG_getObjectRes("Cb", CB_BDL_CB_NUT);
    JUT_ASSERT(DEMO_SELECT(1026, 1025), modelData != NULL);
    mpNutModel = mDoExt_J3DModel__create(modelData, 0x00080000, 0x11000022);
    if(mpNutModel == NULL) {
        return FALSE;
    }

    if(!mNutBckAnim.init(modelData, (J3DAnmTransform*)dComIfG_getObjectRes("Cb", CB_BCK_NUT_SOW), TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false)) {
        return FALSE;
    }

    mAcchCir[0].SetWall(20.0f, 20.0f);
    mAcchCir[1].SetWall(80.0f, 20.0f);
    mAcch.SetRoofCrrHeight(100.0f);
    mAcch.ClrRoofNone();
    mAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this),  this, ARRAY_SIZE(mAcchCir), mAcchCir, fopAcM_GetSpeed_p(this));
    mAcch.OnLineCheck();

    return TRUE;
}

/* 00001458-0000155C       .text setAction__11daNpc_Cb1_cFPM11daNpc_Cb1_cFPCvPvPv_iM11daNpc_Cb1_cFPCvPvPv_iPv */
BOOL daNpc_Cb1_c::setAction(daNpc_Cb1_c::ActionFunc_t* param_1, daNpc_Cb1_c::ActionFunc_t param_2, void* param_3) {
#if VERSION > VERSION_DEMO
    setFlyingTimer(0);
    offFlying();
#endif

    if(*param_1 != param_2) {
        if(*param_1) {
            m8F0 = -1;
            (this->**param_1)(param_3);
        }

        *param_1 = param_2;

        m8F0 = 0;
        m8F4 = 0;
        m8F6 = 0;
        m8F8 = 0;
        m8FA = 0;
        m8FC = 0.0f;
        m8F1 = 0;
        m8F2 = 0;
        shape_angle.x = 0;
        shape_angle.z = 0;
        attention_info.flags = 0;

        (this->**param_1)(param_3);

        m8F0++;
    }

    return TRUE;
}

/* 0000155C-000015C0       .text setWaitAction__11daNpc_Cb1_cFPv */
void daNpc_Cb1_c::setWaitAction(void* param_1) {
    if(dComIfGp_getPlayer(0) == this) {
        setPlayerAction(&daNpc_Cb1_c::waitPlayerAction, NULL);
    }
    else {
        setWaitNpcAction(param_1);
    }
}

/* 000015C0-00001634       .text setWaitNpcAction__11daNpc_Cb1_cFPv */
void daNpc_Cb1_c::setWaitNpcAction(void*) {
    setNpcAction(isShipRide() ? &daNpc_Cb1_c::shipNpcAction : (isMusic() ? &daNpc_Cb1_c::musicNpcAction : &daNpc_Cb1_c::waitNpcAction), NULL);
}

/* 00001634-000016A4       .text npcAction__11daNpc_Cb1_cFPv */
void daNpc_Cb1_c::npcAction(void* param_1) {
    if(!mNpcAction) {
        speedF = 0.0f;
        setWaitNpcAction(NULL);
    }

    (this->*mNpcAction)(param_1);
}

/* 000016A4-00001708       .text setNpcAction__11daNpc_Cb1_cFM11daNpc_Cb1_cFPCvPvPv_iPv */
void daNpc_Cb1_c::setNpcAction(daNpc_Cb1_c::ActionFunc_t param_1, void* param_2) {
    mPlayerAction = NULL;
    setAction(&mNpcAction, param_1, param_2);
}

/* 00001708-000017AC       .text playerAction__11daNpc_Cb1_cFPv */
void daNpc_Cb1_c::playerAction(void* param_1) {
    if(!mPlayerAction) {
        speedF = 0.0f;
        setPlayerAction(&daNpc_Cb1_c::waitPlayerAction, NULL);
    }

    dComIfGp_setDoStatus(dActStts_FLY_e);

    (this->*mPlayerAction)(param_1);
}

/* 000017AC-00001810       .text setPlayerAction__11daNpc_Cb1_cFM11daNpc_Cb1_cFPCvPvPv_iPv */
void daNpc_Cb1_c::setPlayerAction(daNpc_Cb1_c::ActionFunc_t param_1, void* param_2) {
    mNpcAction = NULL;
    setAction(&mPlayerAction, param_1, param_2);
}

/* 00001810-00001858       .text getStickAngY__11daNpc_Cb1_cFv */
s16 daNpc_Cb1_c::getStickAngY() {
    return 0x8000 + g_mDoCPd_cpadInfo[0].mMainStickAngle + dCam_getControledAngleY(dComIfGp_getCamera(0));
}

/* 00001858-000019B0       .text calcStickPos__11daNpc_Cb1_cFsP4cXyz */
int daNpc_Cb1_c::calcStickPos(s16 param_1, cXyz* param_2) {
    // This temp variable for attention is probably a fakematch, but it fixes a regswap in dAttention_c::Lockon.
    dAttention_c& attention = dComIfGp_getAttention();
    dAttList_c* attList = attention.GetLockonList(0);
    
    bool r26 = attention.Lockon();
    
    int r31 = !r26 ? 0 : (attention.LockonTruth() ? 1 : -1);
    
    if (attList == NULL) {
        attList = attention.GetActionList(0);
    }
    if (attList) {
        *param_2 = attList->getActor()->eyePos;
        return r31;
    }
    
    if (r26) {
        param_1 = shape_angle.y;
    }
    
    param_2->set(
        current.pos.x +  100.0f * cM_ssin(param_1),
        current.pos.y,
        current.pos.z +  100.0f * cM_scos(param_1)
    );
    
    return r31;
}

/* 000019B0-00001A18       .text flyCheck__11daNpc_Cb1_cFv */
BOOL daNpc_Cb1_c::flyCheck() {
    if(!CPad_CHECK_TRIG_A(0)) {
        return FALSE;
    }

    setPlayerAction(&daNpc_Cb1_c::flyPlayerAction, NULL);
    return TRUE;
}

/* 00001A18-00001B28       .text checkLanding__11daNpc_Cb1_cFv */
void daNpc_Cb1_c::checkLanding() {
    if(m900 > 200.0f) {
        if(dComIfG_Bgsp()->GetSpecialCode(mAcch.m_gnd) != 1) {
            fopAcM_monsSeStart(this, JA_SE_CV_CB_LANDING, 0);
        }

        int temp;
        dComIfGp_particle_setSimpleLand(mAcch.m_gnd, &current.pos, &shape_angle, 1.25f, 1.5f, 1.0f, &tevStr, &temp, 7);
    }
    else {
        int temp;
        dComIfGp_particle_setSimpleLand(mAcch.m_gnd, &current.pos, &shape_angle, 0.625f, 0.75f, 0.5f, &tevStr, &temp, 7);
    }
}

/* 00001B28-00001B68       .text breaking__11daNpc_Cb1_cFv */
void daNpc_Cb1_c::breaking() {
    cLib_addCalc(&speedF, 0.0f, l_HIO.mDecelScale, l_HIO.mMaxDecel, l_HIO.mDecel);
}

/* 00001B68-0000270C       .text flyAction__11daNpc_Cb1_cFifsi */
BOOL daNpc_Cb1_c::flyAction(BOOL param_1, f32 param_2, s16 param_3, BOOL param_4) {
    bool isMakarPlayer = dComIfGp_getPlayer(0) == this;
    f32 ySpeedLimit = l_HIO.field_0x98;
    f32 temp3 = m8F8 * l_HIO.field_0x8C;
    BOOL temp4 = FALSE;

    if(mAcch.ChkGroundHit()) {
        breaking();
        cLib_chaseAngleS(&shape_angle.x, 0, l_HIO.field_0xE0);
        cLib_chaseAngleS(&shape_angle.z, 0, l_HIO.field_0xE0);
        gravity = l_HIO.field_0xA0 + temp3;
    }
    else if(m8F0 < 3) {
        BOOL temp7 = calcFlyingTimer();
        if(isMakarPlayer) {
            if(temp7) {
                fopAcM_monsSeStart(this, JA_SE_CV_CB_FLY_END, 0);
            }

            onFlying();
        }

        m900 = 0.0f;

        cXyz temp(0.0f, temp3 + l_HIO.field_0xA0, 0.0f);

        f32 temp5 = l_HIO.field_0x9C;

        if(m8F2) {
            temp.x += param_2 * cM_ssin(param_3);
            temp.z += param_2 * cM_scos(param_3);
        }

#if VERSION == VERSION_DEMO
        if(mWindCyl.ChkTgHit())
#else
        if(!isMusic() && mWindCyl.ChkTgHit())
#endif
        {
            cCcD_Obj* tg = mWindCyl.GetTgHitObj();
            if(tg && tg->ChkAtType(AT_TYPE_WIND)) {
                temp += *mWindCyl.GetTgRVecP() * 0.01f;
                temp5 = 30.0f;
                ySpeedLimit = 30.0f;
            }

            m8F8 = 20000;
            temp4 = TRUE;
        }
        else {
            cXyz temp3;
            f32 power;
            dKyw_get_AllWind_vec(&current.pos, &temp3, &power);
            power *= l_HIO.field_0xB8;
            temp += temp3 * power;
            temp5 += power;
            ySpeedLimit += power;
            s16 temp8 = power * 400.0f;
            if(m8F8 < temp8) {
                m8F8 = temp8;
            }
        }

        s16 angle = cM_atan2s(temp.x, temp.z);

        f32 temp6_2 = cLib_maxLimit(std::sqrtf(SQUARE(temp.x) + SQUARE(temp.z)), temp5);
        angle = angle - shape_angle.y;
        f32 temp6 = temp6_2 * l_HIO.field_0xA8;
        if (temp6 > 14000.0f) {
            temp6 = 14000.0f;
        }

        s16 cos = temp6 * cM_scos(angle);
        s16 sin = -temp6 * cM_ssin(angle);
        cLib_chaseAngleS(&shape_angle.x, cos, l_HIO.field_0xE0);
        cLib_chaseAngleS(&shape_angle.z, sin, l_HIO.field_0xE0);

        lookBack(0);

        speed += temp;

        f32 temp8 = speed.abs();
        if(!cM3d_IsZero(temp8) && temp8 > temp5) {
            f32 temp2 = temp8;
            cLib_chaseF(&temp8, temp5, 1.0f);
            if(temp8 > 30.0f) {
                temp8 = 30.0f;
            }
            speed *= temp8 / temp2;
        }

        current.angle.y = cM_atan2s(speed.x, speed.z);

        speedF = std::sqrtf(SQUARE(speed.x) + SQUARE(speed.z));
        if(speed.y > ySpeedLimit) {
            speed.y = ySpeedLimit;
        }
        gravity = 0.0f;
    }

    if(m8F0 == 1) {
        if(m8D7) {
            if(!mAcch.ChkGroundHit()) {
                m8F8 = l_HIO.field_0xDA;
                speed.y += l_HIO.field_0xB0;
                setAnm(ANM_07);
            }
            else {
                setAnm(ANM_05);
            }

            m8F0++;
        }
        else if(mpMorf->checkFrame(6.0f)) {
            fopAcM_seStart(this, JA_SE_CM_PRAPELLO_OPEN, 0);
            JPABaseEmitter* emitter = dComIfGp_particle_set(dPa_name::ID_SCENE_830B, &current.pos);
            if(emitter) {
                emitter->setGlobalRTMatrix(mpPropellerModel->getAnmMtx(m_center_jnt_num));
            }
        }
    }
    else if(m8F0 == 2) {
        if(isMakarPlayer && (temp4 || getFlyingTimer() < l_HIO.field_0xCE)) {
            if(setAnm(ANM_15) && temp4) {
                fopAcM_monsSeStart(this, JA_SE_CV_CB_FLY_END, 0);
            }
        }
        else if(m8DC != 6 && m8FC > l_HIO.field_0xD8) {
            setAnm(ANM_07);
        }

        if(getFlyingTimer() != 0 && param_1) {
            cLib_chaseS(&m8F8, l_HIO.field_0xD0, l_HIO.field_0xD4);
            m8F6 = 0;
        }
        else {
            cLib_chaseS(&m8F8, mAcch.ChkGroundHit() ? l_HIO.field_0xD2 : 0, l_HIO.field_0xD6);
        }

        m8FA += m8F8;
        m8FC += (current.pos.y - old.pos.y);

        if(m8FC > l_HIO.field_0xA4) {
            m8F2 = 1;
        }

        fopAcM_seStart(this, JA_SE_CM_PRAPELLO_ROLLING, m8F8 * (100.0f / l_HIO.field_0xD0));

        if(param_4 || (!isMakarPlayer && mAcch.ChkWallHit()) || (!mAcch.ChkGroundHit() && m8F8 == 0) ||
            (mAcch.ChkGroundHit() && m8F8 <= l_HIO.field_0xD2 && (g_mDoCPd_cpadInfo[0].mMainStickValue >= l_HIO.field_0x80 || ++m8F6 > l_HIO.field_0xCC))
        ) {
            setAnm(ANM_06);
            mpMorf->setFrame(8.0f);
            m8F0++;
            offFlying();
        }
        else if(mAcch.ChkGroundHit() && m8DC == 6) {
            setAnm(ANM_05);
        }

        maxFallSpeed = l_HIO.field_0x90;
    }
    else {
        if(m8DC == 4 && m8D7) {
            setAnm(ANM_02);
            fopAcM_seStart(this, JA_SE_CM_PRAPELLO_OPEN, 0);
        }

        if(mAcch.ChkGroundHit()) {
            if(m8E0 == 0 && m8F0 == 3) {
                if(dComIfG_Bgsp()->GetSpecialCode(mAcch.m_gnd) != 1) {
                    speed.y = l_HIO.field_0x64;
                    checkLanding();
                }

                m8F0++;
            }
            else if(m8DC != 4) {
                if(isMakarPlayer) {
                    setPlayerAction(&daNpc_Cb1_c::waitPlayerAction, NULL);
                }
                else {
                    setNpcAction(&daNpc_Cb1_c::waitNpcAction, NULL);

                    dComIfGp_getCamera(0)->mCamera.ForceLockOff(fopAcM_GetID(this));
                }

                return FALSE;
            }
        }
    }

    return TRUE;
}

/* 0000270C-00002818       .text walkAction__11daNpc_Cb1_cFffs */
BOOL daNpc_Cb1_c::walkAction(f32 targetSpeed, f32 accel, s16 targetAngle) {
    cLib_chaseAngleS(&current.angle.y, targetAngle, 0x400);
    lookBack(1);
    shape_angle.y = current.angle.y;
    if(cLib_chaseF(&speedF, targetSpeed, accel) && targetSpeed == 0.0f) {
        setNpcAction(&daNpc_Cb1_c::waitNpcAction, NULL);

        return TRUE;
    }

    f32 playSpeed = std::fabsf(speedF) * l_HIO.mWalkAnmSpeedScale;
    playSpeed = cLib_minLimit(playSpeed, l_HIO.mMaxWalkAnmSpeed);
    mpMorf->setPlaySpeed(playSpeed);

    return FALSE;
}

/* 00002818-00002868       .text returnLinkPlayer__11daNpc_Cb1_cFv */
void daNpc_Cb1_c::returnLinkPlayer() {
    changePlayer(dComIfGp_getLinkPlayer());
    offFlying();
    setWaitNpcAction(NULL);
}

/* 00002868-00002914       .text isFlyAction__11daNpc_Cb1_cFv */
BOOL daNpc_Cb1_c::isFlyAction() {
    return chkPlayerAction(&daNpc_Cb1_c::flyPlayerAction) || chkNpcAction(&daNpc_Cb1_c::flyNpcAction);
}

/* 00002914-00002A2C       .text sowCheck__11daNpc_Cb1_cFv */
BOOL daNpc_Cb1_c::sowCheck() {
#if VERSION > VERSION_DEMO
    if(!dComIfGp_event_runCheck() && (m4E4 & 1) == 0)
#endif
    {
        dAttList_c* list = dComIfGp_getAttention().getActionBtnB();
        if(list) {
            fopAc_ac_c* actor = list->getActor();

            if((list->mType == fopAc_Attn_TYPE_SPEAK_e || list->mType == fopAc_Attn_TYPE_TALK_e) && (actor->attention_info.flags & fopAc_Attn_UNK10000000_e)) {
                if(m8E2 != 0x2D) {
#if VERSION == VERSION_DEMO
                    dComIfGp_getVibration().StartShock(2, -0x21, cXyz(0.0f, 1.0f, 0.0f));
#else
                    dComIfGp_getVibration().StartShock(4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
#endif
                }

                dComIfGp_setDoStatus(dActStts_ba_nageru__dupe_2D);

                if(CPad_CHECK_TRIG_A(0)) {
                    eventInfo.onCondition(dEvtCnd_CANTALK_e);
                    fopAcM_orderTalkEvent(this, actor);

                    return TRUE;
                }

                return FALSE;
            }
        }
    }

    return flyCheck();
}

/* 00002A2C-00002AD8       .text shipRideCheck__11daNpc_Cb1_cFv */
BOOL daNpc_Cb1_c::shipRideCheck() {
    if(dComIfGs_isEventBit(0x1604) && dComIfGp_getShipActor()) {
        setNpcAction(&daNpc_Cb1_c::shipNpcAction, NULL);
        onShipRide();
        fopDwTg_DrawQTo(&draw_tag);

        return TRUE;
    }

    return FALSE;
}

#ifdef __MWERKS__
static
#endif
daNpc_Cb1_c::mode_entry_t daNpc_Cb1_c::m_evProcTbl[] = {
    {
        &daNpc_Cb1_c::evInitWait,
        &daNpc_Cb1_c::evActWait
    },
    {
        &daNpc_Cb1_c::evInitMsgSet,
        &daNpc_Cb1_c::evActMsgSet
    },
    {
        &daNpc_Cb1_c::evInitMsgEnd,
        &daNpc_Cb1_c::evActMsgEnd
    },
    {
        &daNpc_Cb1_c::evInitMovePos,
        &daNpc_Cb1_c::evActMovePos
    },
    {
        &daNpc_Cb1_c::evInitOffsetLink,
        &daNpc_Cb1_c::evActOffsetLink
    },
    {
        &daNpc_Cb1_c::evInitWalk,
        &daNpc_Cb1_c::evActWalk
    },
    {
        &daNpc_Cb1_c::evInitToLink,
        &daNpc_Cb1_c::evActToLink
    },
    {
        &daNpc_Cb1_c::evInitTact,
        &daNpc_Cb1_c::evActTact
    },
    {
        &daNpc_Cb1_c::evInitCelloPlay,
        &daNpc_Cb1_c::evActCelloPlay
    },
    {
        &daNpc_Cb1_c::evInitTurn,
        &daNpc_Cb1_c::evActTurn
    },
    {
        &daNpc_Cb1_c::evInitSow,
        &daNpc_Cb1_c::evActSow
    },
    {
        &daNpc_Cb1_c::evInitSetAnm,
        &daNpc_Cb1_c::evActSetAnm
    },
    {
        &daNpc_Cb1_c::evInitSetGoal,
        &daNpc_Cb1_c::evActSetGoal
    },
    {
        &daNpc_Cb1_c::evInitWarp,
        &daNpc_Cb1_c::evActWarp
    },
    {
        &daNpc_Cb1_c::evInitEnd,
        &daNpc_Cb1_c::evActEnd
    },
};

static char* l_cutNameTbl[] = {
    "WAIT",
    "MSG_SET",
    "MSG_END",
    "POS_MOV",
    "OFFSET_LINK",
    "WALK",
    "TO_LINK",
    "TACT",
    "CELLOPLAY",
    "TURN",
    "SOW",
    "SET_ANM",
    "SET_GOAL",
    "WARP",
    "END",
};

/* 00002AD8-00002DC8       .text eventProc__11daNpc_Cb1_cFv */
BOOL daNpc_Cb1_c::eventProc() {
#if VERSION > VERSION_DEMO
    mAcch.ClrWallNone();
#endif

    if(eventInfo.checkCommandDemoAccrpt() && m8DD != -1) {
        if(m8DD == 0) {
            fopAcM_onDraw(this);
        }
        else if(m8DD == 1) {
            dComIfGp_event_setTalkPartner(dComIfGp_getLinkPlayer());
            mDoAud_seStart(JA_SE_CTRL_NPC_TO_LINK);
        }

        m4E4 |= 2;
        m8DD = -1;
    }

    int staffIdx = dComIfGp_evmng_getMyStaffId("Cb1");
    if(dComIfGp_event_runCheck() && (dComIfGp_getPlayer(0) == this || !checkCommandTalk())) {
        if(staffIdx != -1) {
            int actIdx = dComIfGp_evmng_getMyActIdx(staffIdx, l_cutNameTbl, ARRAY_SIZE(l_cutNameTbl), TRUE, 0);
            if(actIdx == -1) {
                dComIfGp_evmng_cutEnd(staffIdx);
            }
            else {
                if(dComIfGp_evmng_getIsAddvance(staffIdx)) {
                    (this->*m_evProcTbl[actIdx].init)(staffIdx);
                    speedF = 0.0f;
                }

                if((this->*m_evProcTbl[actIdx].run)(staffIdx)) {
                    dComIfGp_evmng_cutEnd(staffIdx);
                }
            }

            mPlayerAction = NULL;
            mNpcAction = NULL;

#if VERSION > VERSION_DEMO
            mAcch.SetWallNone();
#endif
        }


        if(m4E4 & 2) {
            if(dComIfGp_evmng_endCheck(mEventIdx[m8E3])) {
                dComIfGp_event_reset();
                m4E4 &= ~2;

                if(m8E3 == 1) {
                    returnLinkPlayer();
                    m4E4 &= ~1;
                }

                m8E3 = 0xFF;
            }

            return TRUE;
        }

        if(staffIdx != -1) {
            return TRUE;
        }

#if VERSION > VERSION_DEMO
        if(dComIfGp_getLinkPlayer()->eventInfo.checkCommandDoor() == FALSE) {
            return TRUE;
        }
#endif
    }

    return FALSE;
}

/* 00002DC8-00002E5C       .text evCheckDisp__11daNpc_Cb1_cFi */
void daNpc_Cb1_c::evCheckDisp(int staffIdx) {
    int* pDisp = dComIfGp_evmng_getMyIntegerP(staffIdx, "Disp");
    if(pDisp) {
        if(*pDisp) {
            fopAcM_onDraw(this);
        }
        else {
            fopDwTg_DrawQTo(&draw_tag);
        }
    }
    else {
        fopAcM_onDraw(this);
    }
}

/* 00002E5C-00002EF8       .text evInitWait__11daNpc_Cb1_cFi */
void daNpc_Cb1_c::evInitWait(int staffIdx) {
    evCheckDisp(staffIdx);

    int* pTimer = dComIfGp_evmng_getMyIntegerP(staffIdx, "Timer");
    if(pTimer) {
        m8EE = *pTimer;
    }
    else {
        m8EE = 0;
    }

    setAnm(isMusic() ? ANM_08 : ANM_00);
}

/* 00002EF8-00002F5C       .text evActWait__11daNpc_Cb1_cFi */
BOOL daNpc_Cb1_c::evActWait(int) {
    s16 temp = m8EE;
    if(cLib_chaseS(&m8EE, 0, 1)) {
        if(temp < 0) {
            dComIfGp_event_reset();
        }

        return TRUE;
    }

    return FALSE;
}

/* 00002F5C-00002FF0       .text evInitMsgSet__11daNpc_Cb1_cFi */
void daNpc_Cb1_c::evInitMsgSet(int staffIdx) {
    l_msgId = fpcM_ERROR_PROCESS_ID_e;

    int* pMsgNo = dComIfGp_evmng_getMyIntegerP(staffIdx, "MsgNo");
    if(pMsgNo) {
        mMsgNo = *pMsgNo;

        if(mMsgNo == 0x1520 && dComIfGs_isEventBit(0x1840)) {
            mMsgNo = 0x1522;
        }
    }
}

/* 00002FF0-00003010       .text evActMsgSet__11daNpc_Cb1_cFi */
BOOL daNpc_Cb1_c::evActMsgSet(int) {
    return initTalk();
}

/* 00003010-00003014       .text evInitMsgEnd__11daNpc_Cb1_cFi */
void daNpc_Cb1_c::evInitMsgEnd(int) {}

/* 00003014-000030A4       .text evActMsgEnd__11daNpc_Cb1_cFi */
BOOL daNpc_Cb1_c::evActMsgEnd(int staffIdx) {
    BOOL result = execTalk(0);

    if(result) {
        dComIfGp_evmng_getMyIntegerP(staffIdx, "EndMode");
        setWaitAction(NULL);
    }
    else {
        mJntCtrl.setTrn();
        lookBack(1);
    }

    return result;
}

/* 000030A4-000031E0       .text evInitMovePos__11daNpc_Cb1_cFi */
void daNpc_Cb1_c::evInitMovePos(int staffIdx) {
    f32* pAngle = dComIfGp_evmng_getMyFloatP(staffIdx, "Angle");
    if(pAngle) {
        s16 angle = cM_deg2s(*pAngle);
        current.angle.y = angle;
        shape_angle.y = angle;
    }

    cXyz* pPos = dComIfGp_evmng_getMyXyzP(staffIdx, "Pos");
    if(pPos) {
        current.pos = *pPos;
    }

    const char* pShipRide = dComIfGp_evmng_getMyStringP(staffIdx, "ShipRide");
    if(pShipRide) {
        if(strcmp(pShipRide, "on") == 0) {
            onShipRide();
        }
        else if(strcmp(pShipRide, "off") == 0) {
            offShipRide();
        }
    }
}

/* 000031E0-000031E8       .text evActMovePos__11daNpc_Cb1_cFi */
BOOL daNpc_Cb1_c::evActMovePos(int) {
    return 1;
}

/* 000031E8-000032E4       .text evInitOffsetLink__11daNpc_Cb1_cFi */
void daNpc_Cb1_c::evInitOffsetLink(int staffIdx) {
    daPy_lk_c* pLink = daPy_getPlayerLinkActorClass();

    cXyz* pTo = dComIfGp_evmng_getMyXyzP(staffIdx, "To");
    if(pTo) {
        cXyz dest;
        cLib_offsetPos(&dest, &current.pos, shape_angle.y, pTo);
        pLink->setPlayerPosAndAngle(&dest, cLib_targetAngleY(&dest, &current.pos));
    }

    cXyz* pFrom = dComIfGp_evmng_getMyXyzP(staffIdx, "From");
    if(pFrom) {
        fopAc_ac_c* pPlayer = dComIfGp_getPlayer(0);
        cLib_offsetPos(&current.pos, &pLink->current.pos, pPlayer->shape_angle.y, pFrom);
    }

    current.angle.y = fopAcM_searchActorAngleY(this, dComIfGp_getPlayer(0));
    shape_angle.y = current.angle.y;
}

/* 000032E4-000032EC       .text evActOffsetLink__11daNpc_Cb1_cFi */
BOOL daNpc_Cb1_c::evActOffsetLink(int) {
    return 1;
}

/* 000032EC-00003328       .text evInitWalk__11daNpc_Cb1_cFi */
void daNpc_Cb1_c::evInitWalk(int) {
    setAnm(ANM_01);
    speedF = 0.0f;
}

/* 00003328-0000373C       .text evActWalk__11daNpc_Cb1_cFi */
BOOL daNpc_Cb1_c::evActWalk(int staffIdx) {
    f32* speed_p = dComIfGp_evmng_getMyFloatP(staffIdx, "Speed");
    f32* pDist = dComIfGp_evmng_getMyFloatP(staffIdx, "Dist");

    JUT_ASSERT(DEMO_SELECT(2042, 2060), speed_p != NULL);

    cXyz* pPos = dComIfGp_evmng_getMyXyzP(staffIdx, "Pos");
    cXyz temp;
    cXyz temp2;
    cXyz temp4;
    if(pPos) {
        temp = *pPos;
        temp4 = *pPos;
    }
    else {
        cXyz* pOffset = dComIfGp_evmng_getMyXyzP(staffIdx, "Offset");
        if(pOffset) {
            fopAc_ac_c* target = dComIfGp_event_getTalkPartner();
            JUT_ASSERT(DEMO_SELECT(2059, 2077), target != NULL);

            cLib_offsetPos(&temp, &target->current.pos, fopAcM_searchActorAngleY(this, target), pOffset);
            temp4 = target->current.pos;
        }
        else {
            temp = *dComIfGp_evmng_getGoal();
            temp4 = temp;
        }
    }

    temp2 = temp - current.pos;
    s16 angle = cM_atan2s(temp2.x, temp2.z);

    if(!pDist) {
        if(temp2.absXZ() <= *speed_p) {
            setAnm(ANM_00);
            current.pos = temp;
            speedF = 0.0f;

            return TRUE;
        }
    }
    else {
        if(temp2.absXZ() < *pDist) {
            setAnm(ANM_00);
            speedF = 0.0f;

            return TRUE;
        }
    }

    f32 walkSpeed = *speed_p;
    if(cLib_distanceAngleS(shape_angle.y, angle) > 0x4000) {
        walkSpeed = -walkSpeed;
        angle += 0x8000;
    }

    if(mAcch.ChkGroundHit()) {
        walkAction(walkSpeed, l_HIO.mForwardAccel, angle);
    }
    else if(m8E0) {
        speed.y = 10.0f;
    }

    return FALSE;
}

/* 0000373C-00003798       .text evInitToLink__11daNpc_Cb1_cFi */
void daNpc_Cb1_c::evInitToLink(int) {
    setAnm(ANM_01);
    speedF = 0.0f;
    current.angle.y = fopAcM_searchActorAngleY(this, dComIfGp_getPlayer(0));
    shape_angle.y = current.angle.y;
}

/* 00003798-000038D8       .text evActToLink__11daNpc_Cb1_cFi */
BOOL daNpc_Cb1_c::evActToLink(int staffIdx) {
    f32* speed_p = dComIfGp_evmng_getMyFloatP(staffIdx, "Speed");
    f32* dist_p = dComIfGp_evmng_getMyFloatP(staffIdx, "Dist");

    JUT_ASSERT(DEMO_SELECT(2131, 2149), speed_p != NULL && dist_p != NULL);

    if(fopAcM_searchActorDistanceXZ(this, dComIfGp_getPlayer(0)) < *dist_p) {
        setAnm(ANM_00);
        speedF = 0.0f;

        return TRUE;
    }
    else {
        walkAction(*speed_p, l_HIO.mForwardAccel, fopAcM_searchActorAngleY(this, dComIfGp_getPlayer(0)));
    }

    return FALSE;
}

/* 000038D8-000038FC       .text evInitTact__11daNpc_Cb1_cFi */
void daNpc_Cb1_c::evInitTact(int) {
    setAnm(ANM_08);
}

/* 000038FC-00003A2C       .text evActTact__11daNpc_Cb1_cFi */
BOOL daNpc_Cb1_c::evActTact(int staffIdx) {
    int* pPrm0 = dComIfGp_evmng_getMyIntegerP(staffIdx, "prm0");

    s32 prm = 0;
    if(pPrm0) {
        prm = *pPrm0;
    }

    s32 song = daPy_getPlayerActorClass()->getTactMusic();
    if(song >= 0) {
        onTactCorrect();
    }

    BOOL result = execTalk(1);
    if(result) {
        if(isTactCorrect()) {
            offTactCorrect();
            if(song == prm) {
                mMsgNo = 0x1526;
            }
            else {
                mMsgNo = 0x1523;
            }
        }
        else {
            m8DD = 3;

            if(isTactCancel()) {
                mMsgNo = 0x1525;
                offTactCancel();
            }

            fopAcM_onDraw(this);

            dComIfGp_event_reset();
        }
    }

    return result;
}

/* 00003A2C-00003A50       .text evInitCelloPlay__11daNpc_Cb1_cFi */
void daNpc_Cb1_c::evInitCelloPlay(int) {
#if VERSION == VERSION_DEMO
    setAnm(ANM_09);
#else
    setAnm(ANM_17);
#endif
}

/* 00003A50-00003A84       .text evActCelloPlay__11daNpc_Cb1_cFi */
BOOL daNpc_Cb1_c::evActCelloPlay(int) {
    return daPy_getPlayerLinkActorClass()->checkEndTactMusic() ? TRUE : FALSE;
}

/* 00003A84-00003ABC       .text evInitTurn__11daNpc_Cb1_cFi */
void daNpc_Cb1_c::evInitTurn(int param_1) {
    evCheckDisp(param_1);
    setAnm(ANM_00);
}

/* 00003ABC-00003C0C       .text evActTurn__11daNpc_Cb1_cFi */
BOOL daNpc_Cb1_c::evActTurn(int staffIdx) {
    f32* pAngle = dComIfGp_evmng_getMyFloatP(staffIdx, "Angle");

    s16 angle;
    if(pAngle) {
        angle = cM_deg2s(*pAngle);
    }
    else {
        fopAc_ac_c* target;
        if(dComIfGp_evmng_getMyIntegerP(staffIdx, "Target")) {
            target = dComIfGp_getLinkPlayer();
        }
        else {
            target = dComIfGp_event_getTalkPartner();
        }

        JUT_ASSERT(DEMO_SELECT(2308, 2326), target != NULL);

        angle = fopAcM_searchActorAngleY(this, target);
    }

    if(cLib_chaseAngleS(&shape_angle.y, angle, 0x800)) {
        shape_angle.y = angle;
        current.angle.y = angle;

        return TRUE;
    }

    current.angle.y = shape_angle.y;

    return FALSE;
}

/* 00003C0C-00003CEC       .text evInitSow__11daNpc_Cb1_cFi */
void daNpc_Cb1_c::evInitSow(int staffIdx) {
    setAnm(ANM_0C);

    mNutBckAnim.initPlay(mNutBckAnim.getBckAnm()->getFrameMax(), J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true);
    onNut();

    int* timer_p = dComIfGp_evmng_getMyIntegerP(staffIdx, "Timer");
    JUT_ASSERT(DEMO_SELECT(2353, 2371), timer_p != NULL);

    m8EE = *timer_p;
}

/* 00003CEC-00003D90       .text evActSow__11daNpc_Cb1_cFi */
BOOL daNpc_Cb1_c::evActSow(int staffIdx) {
    if(mNutBckAnim.play() && isNut()) {
        offNut();

        ((daObjVmc::Act_c*)dComIfGp_event_getTalkPartner())->daObjVmc_ChangeGrow();
    }

    if(m8D7) {
        setAnm(ANM_00);
    }

    if(cLib_calcTimer(&m8EE) == 0) {
        return TRUE;
    }

    return FALSE;
}

/* 00003D90-00003DF8       .text evInitSetAnm__11daNpc_Cb1_cFi */
void daNpc_Cb1_c::evInitSetAnm(int staffIdx) {
    int* pNumber = dComIfGp_evmng_getMyIntegerP(staffIdx, "Number");
    if(pNumber) {
        setAnm(getAnmType(*pNumber));
    }
}

/* 00003DF8-00003E00       .text evActSetAnm__11daNpc_Cb1_cFi */
BOOL daNpc_Cb1_c::evActSetAnm(int) {
    return TRUE;
}

/* 00003E00-00003E74       .text evInitSetGoal__11daNpc_Cb1_cFi */
void daNpc_Cb1_c::evInitSetGoal(int staffIdx) {
    cXyz* pOffset = dComIfGp_evmng_getMyXyzP(staffIdx, "Offset");
    if(pOffset) {
        cLib_offsetPos(dComIfGp_evmng_getGoal(), &current.pos, shape_angle.y, pOffset);
    }
}

/* 00003E74-00003E98       .text evActSetGoal__11daNpc_Cb1_cFi */
BOOL daNpc_Cb1_c::evActSetGoal(int param_1) {
#if VERSION > VERSION_DEMO
    evInitSetGoal(param_1);
#endif

    return TRUE;
}

/* 00003E98-00003EF4       .text evInitWarp__11daNpc_Cb1_cFi */
void daNpc_Cb1_c::evInitWarp(int) {
    setAnm(ANM_00);
    speed.y = REG18_F(13) + 2.5f;
    m8EE = -(REG18_S(5) + 0x14);
}

/* 00003EF4-0000405C       .text evActWarp__11daNpc_Cb1_cFi */
BOOL daNpc_Cb1_c::evActWarp(int) {
    gravity = 0.0f;

    if(m8EE < 0) {
        if(cLib_chaseF(&speed.y, 0.0f, REG18_F(14) + 0.1f) && cLib_chaseS(&m8EE, 0, 1)) {
            m8EE = 0;
        }
    }
    else {
        if(cLib_chaseS(&m8EE, REG18_S(6) + 8000, REG18_S(7) + 400)) {
            cLib_chaseF(&speed.y, REG18_F(15) + 20.0f, REG18_F(16) + 0.5f);
            cLib_chaseF(&scale.x, 0.0f, REG18_F(17) + 0.05f);

            scale.z = scale.x;

            if(cLib_chaseF(&scale.y, REG18_F(18) + 4.0f, REG18_F(19) + 0.05f)) {
                return TRUE;
            }
        }

        current.angle.y += m8EE;
        shape_angle.y = current.angle.y;
    }

    return FALSE;
}

/* 0000405C-00004174       .text evInitEnd__11daNpc_Cb1_cFi */
void daNpc_Cb1_c::evInitEnd(int staffIdx) {
    int* pEndMode = dComIfGp_evmng_getMyIntegerP(staffIdx, "EndMode");
    
    int mode;
    if(pEndMode == NULL) {
        mode = 0;
    }
    else {
        mode = *pEndMode;
    }

    if(mode == -2) {
        if(mMsgNo == 0x1526) {
            dComIfGp_setNextStage("Otkura", 0xE6, 0, 8);
            dComIfGs_onEventBit(0x1610);
            dComIfGs_onEventBit(0x1604);
        }

        dComIfGp_event_reset();
        setWaitAction(NULL);
    }
    else if(mode == -1) {
        dComIfGp_event_reset();
        setWaitAction(NULL);
    }
    else {
        setWaitAction(NULL);
    }
}

/* 00004174-0000417C       .text evActEnd__11daNpc_Cb1_cFi */
BOOL daNpc_Cb1_c::evActEnd(int) {
    return TRUE;
}

/* 0000417C-000041A4       .text getAnmType__11daNpc_Cb1_cFi */
u8 daNpc_Cb1_c::getAnmType(int param_1) {
    static u8 l_talkAnmType[] = {ANM_00, ANM_08, ANM_0A, ANM_0E, ANM_10, ANM_11, ANM_12, ANM_13, ANM_14, ANM_0D, ANM_17};

    if((u32)param_1 < ARRAY_SIZE(l_talkAnmType)) {
        return l_talkAnmType[param_1];
    }

    return l_talkAnmType[0];
}

/* 000041A4-00004228       .text initTalk__11daNpc_Cb1_cFv */
BOOL daNpc_Cb1_c::initTalk() {
    if(l_msgId == fpcM_ERROR_PROCESS_ID_e) {
        if(mMsgNo == 0x5AC) {
            l_msgId = fopMsgM_tactMessageSet();
        }
        else {
            l_msgId = fopMsgM_messageSet(mMsgNo, this);
        }
    }
    else {
        l_msg = fopMsgM_SearchByID(l_msgId);
        if(l_msg) {
            return TRUE;
        }
    }

    return FALSE;
}

/* 00004228-00004358       .text execTalk__11daNpc_Cb1_cFi */
BOOL daNpc_Cb1_c::execTalk(BOOL param_1) {
    if(l_msg->mStatus == fopMsgStts_MSG_DISPLAYED_e) {
        l_msg->mStatus = next_msgStatus(&mMsgNo);

        if(l_msg->mStatus == fopMsgStts_MSG_CONTINUES_e) {
            fopMsgM_messageSet(mMsgNo);
        }
    }
    else if(l_msg->mStatus == fopMsgStts_UNK15_e) {
        if(param_1) {
            if(dComIfGp_checkMesgCancelButton()) {
                l_msg->mStatus = fopMsgStts_MSG_ENDS_e;
                fopMsgM_messageSendOn();
                onTactCancel();
            }

            if(isTactCorrect()) {
                l_msg->mStatus = fopMsgStts_MSG_ENDS_e;
                fopMsgM_messageSendOn();
            }
        }
    }
    else if(l_msg->mStatus == fopMsgStts_MSG_TYPING_e) {
        if(mMsgNo != 0x5AC) {
            setAnm(getAnmType(dComIfGp_getMesgAnimeAttrInfo()));
        }
    }
    else if(l_msg->mStatus == fopMsgStts_BOX_CLOSED_e) {
        l_msg->mStatus = fopMsgStts_MSG_DESTROYED_e;

        return TRUE;
    }

    return FALSE;
}

/* 00004358-0000461C       .text waitNpcAction__11daNpc_Cb1_cFPv */
BOOL daNpc_Cb1_c::waitNpcAction(void* param_1) {
    if(m8F0 == 0) {
        if(dComIfGs_isEventBit(0x1610)) {
            cLib_onBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
        }

        u8 anm = ANM_00;
        if(param_1) {
            u32 seNum;

            if(isPlayerFind()) {
                anm = ANM_0F;
                seNum = JA_SE_CV_CB_LEFT_ALONE;
            }
            else {
                anm = ANM_14;
                seNum = JA_SE_CV_CB_TROUBLE;
            }

            fopAcM_monsSeStart(this, seNum, 0);
        }

        setAnm(anm);
        offPlayerFind();
        speedF = 0.0f;
    }
    else if(m8F0 != -1) {
        if(m8E1) {
            setNpcAction(&daNpc_Cb1_c::searchNpcAction, NULL);
        }
        else {
            mHasAttention = chkAttention(m8DC == 0x14 ? 4000.0f : l_HIO.mNpc.mMaxAttnDistXZ, 0x10000);

            BOOL temp = mHasAttention;
            if(temp) {
                if(getMsg()) {
                    m8DD = 6;
                    cLib_onBit<u32>(attention_info.flags, fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_LOCKON_TALK_e);
                }
                else {
                    cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_LOCKON_TALK_e);
                }
            }
            else {
                cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_LOCKON_TALK_e);
            }

            f32 dist_sq = fopAcM_searchActorDistance2(this, dComIfGp_getPlayer(0));

            if(!checkNpcCallCommand()) {
                if(dComIfGs_isEventBit(0x1610) && dist_sq < SQUARE(l_HIO.field_0xC0)) {
                    daPy_getPlayerLinkActorClass()->onNpcCall();

                    temp = TRUE;
                }
            }
            else {
                if(dist_sq >= SQUARE(l_HIO.mPlayerChaseDistance)) {
                    setNpcAction(&daNpc_Cb1_c::searchNpcAction, NULL);
                }

                temp = TRUE;
            }

            lookBack(temp);

            current.angle.y = shape_angle.y;
        }
    }

    return TRUE;
}

/* 0000461C-000047B0       .text talkNpcAction__11daNpc_Cb1_cFPv */
BOOL daNpc_Cb1_c::talkNpcAction(void*) {
    if(m8F0 == 0) {
        l_msgId = fpcM_ERROR_PROCESS_ID_e;

        mMsgNo = getMsg();

        cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);

        if(!isMusic()) {
            setAnm(isShipRide() ? ANM_0D : ANM_00);
        }
    }
    else if(m8F0 != -1) {
        mHasAttention = true;

        if(m8F0 == 1) {
            if(initTalk()) {
                m8F0 = 2;
            }
        }
        else if(m8F0 == 2) {
            if(execTalk(0)) {
                setWaitNpcAction(NULL);

                dComIfGp_event_reset();
            }
        }

        if(isShipRide()) {
            daShip_c* pShip = dComIfGp_getShipActor();
            if(pShip) {
                fopAc_ac_c* pLink = dComIfGp_getLinkPlayer();
                cXyz temp = current.pos - (pLink->current.pos - current.pos);
                pShip->setAtnPos(&temp);
            }
        }
        else {
            mJntCtrl.setTrn();
            lookBack(1);
        }
    }

    return TRUE;
}

/* 000047B0-00004B74       .text carryNpcAction__11daNpc_Cb1_cFPv */
BOOL daNpc_Cb1_c::carryNpcAction(void*) {
    /* Nonmatching - regswap */

    if(m8F0 == 0) {
        cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
        offNpcCallCommand();
        m8F4 = fopAcM_toPlayerShapeAngleY(this);

        if(isNoCarryAction()) {
            fopAcM_monsSeStart(this, JA_SE_CV_CB_DAMAGE, 0);
            setAnm(ANM_0B);
        }
        else {
            fopAcM_monsSeStart(this, JA_SE_CV_CB_LIFT_UP, 0);
            setAnm(ANM_03);
        }

        onNpcNotChange();
    }
    else if(m8F0 == -1) {
        m904.y = 0.0f;
        m904.z = 0.0f;
        
        offNoCarryAction();

        offNpcNotChange();
    }
    else {
        if(isNoCarryAction()) {
            mpMorf->setPlaySpeed(2.0f);
        }
        else {
            setRestart(1);

            daPy_py_c* pPlayer = (daPy_py_c*)dComIfGp_getPlayer(0);
            f32 oldPlaySpeed = mpMorf->getPlaySpeed();

            if(0.0f == pPlayer->getSpeedF() && pPlayer->getBaseAnimeFrame() <= mpMorf->getEndFrame()) {
                mpMorf->setFrame(pPlayer->getBaseAnimeFrame());
                mpMorf->setPlaySpeed(0.0f);
            }
            else {
                mpMorf->setPlaySpeed(1.0f);
            }

            if(oldPlaySpeed != mpMorf->getPlaySpeed()) {
                mpMorf->setMorf(4.0f);
            }

            cLib_chaseF(&m904.x, l_HIO.field_0x74, 1.0f);
            cLib_chaseF(&m904.y, l_HIO.field_0x78, 1.0f);
            cLib_chaseF(&m904.z, l_HIO.field_0x7C, 1.0f);

            cLib_chaseAngleS(&m8F4, 0, 0x800);
            shape_angle.y += m8F4;
        }

        if(!fopAcM_checkCarryNow(this)) {
            if(fopAcM_GetSpeedF(this) > 0.0f) {
                setNpcAction(&daNpc_Cb1_c::flyNpcAction, NULL);
            }
            else {
                setNpcAction(&daNpc_Cb1_c::waitNpcAction, NULL);
            }
        }

        mJntCtrl.lookAtTarget(&shape_angle.y, NULL, cXyz::Zero, shape_angle.y, 0, false);
        current.angle.y = shape_angle.y;
    }

    return TRUE;
}

/* 00004B74-00004CBC       .text flyNpcAction__11daNpc_Cb1_cFPv */
BOOL daNpc_Cb1_c::flyNpcAction(void*) {
    s8 temp = m8F0;
    if(temp == 0) {
        speedF = l_HIO.mNpcFlyLaunchSpeedF;
        speed.y = l_HIO.mNpcFlyLaunchSpeedY;

        setAnm(ANM_04);

        setFlyingTimer(l_HIO.mNpcFlyTimer);

        m8FC = l_HIO.field_0xD8 + 1;

        fopAcM_monsSeStart(this, JA_SE_CV_CB_THROW, 0);
    }
    else if(temp != -1) {
        flyAction(m8F1 ? FALSE : TRUE, 0.0f, 0, FALSE);

        if(temp != 1) {
            m8F1 = (m8F1 + 1) % l_HIO.field_0xDE;
        }
    }

    return TRUE;
}

/* 00004CBC-00004D88       .text routeAngCheck__11daNpc_Cb1_cFR4cXyzPs */
void daNpc_Cb1_c::routeAngCheck(cXyz& param_1, s16* param_2) {
    cXyz temp = m910.outprod(param_1);
    s16 angle = cM_atan2s(temp.x, temp.z);

    if((m910.y >= 1.0f && cLib_distanceAngleS(angle, *param_2) > 0x4000) || fopAcM_searchPlayerDistanceY(this) * temp.y < 0.0f) {
        angle += 0x8000;
    }

    *param_2 = angle;
}

/* 00004D88-00004FEC       .text routeWallCheck__11daNpc_Cb1_cFR4cXyzR4cXyzPs */
void daNpc_Cb1_c::routeWallCheck(cXyz& param_1, cXyz& param_2, s16* param_3) {
    dBgS_LinChk lin_chk;
    lin_chk.Set(&param_1, &param_2, NULL);

    if(dComIfG_Bgsp()->LineCross(&lin_chk)) {
        cM3dGPla* pla = dComIfG_Bgsp()->GetTriPla(lin_chk);
        if(pla) {
            routeAngCheck(pla->mNormal, param_3);
        }
    }
}

/* 000053DC-0000565C       .text checkForwardGroundY__11daNpc_Cb1_cFs */
f32 daNpc_Cb1_c::checkForwardGroundY(s16 param_1) {
    cM3dGPla* pla = dComIfG_Bgsp()->GetTriPla(mAcchCir[0]);

    if(pla && cLib_distanceAngleS(param_1, cM_atan2s(pla->mNormal.x, pla->mNormal.z)) > 0x4000) {
        dBgS_GndChk gnd_chk;
        gnd_chk.OffWall();
        cXyz pos(current.pos.x + cM_ssin(param_1) * 80.0f, current.pos.y + 80.0f, current.pos.z + cM_scos(param_1) * 80.0f);
        gnd_chk.SetPos(&pos);
        return dComIfG_Bgsp()->GroundCross(&gnd_chk);
    }
    
    return -1e+7;
}

/* 000057F4-000058C8       .text checkWallJump__11daNpc_Cb1_cFs */
f32 daNpc_Cb1_c::checkWallJump(s16 param_1) {
    f32 temp = checkForwardGroundY(param_1) - current.pos.y;
    if(0.0f < temp && temp < 80.0f) {
        return std::sqrtf(temp) * 3.8f;
    }

    return -1.0f;
}

/* 000058C8-0000593C       .text chkWallHit__11daNpc_Cb1_cFv */
BOOL daNpc_Cb1_c::chkWallHit() {
    if(mAcch.ChkWallHit()) {
        s16 temp;
        if(mAcchCir[0].ChkWallHit()) {
            temp = mAcchCir[0].GetWallAngleY();
        }
        else if(mAcchCir[1].ChkWallHit()) {
            temp = mAcchCir[1].GetWallAngleY();
        }

        return cLib_distanceAngleS(shape_angle.y, temp) > 0x6000;
    }

    return FALSE;
}

/* 0000593C-00005F0C       .text routeCheck__11daNpc_Cb1_cFfPs */
BOOL daNpc_Cb1_c::routeCheck(f32 param_1, s16* param_2) {
    if(!mAcch.ChkGroundHit()) {
        cXyz temp = current.pos;
        current.pos = old.pos;
        speedF = 0.0f;
        m8E0 = 1;

        dBgS_LinChk lin_chk;
        lin_chk.Set(&temp, &current.pos, NULL);

        if(dComIfG_Bgsp()->LineCross(&lin_chk)) {
            cM3dGPla* pla = dComIfG_Bgsp()->GetTriPla(lin_chk);
            if(pla && cLib_distanceAngleS(*param_2, cM_atan2s(pla->mNormal.x, pla->mNormal.z)) > 0x4000) {
                return TRUE;
            }
        }

        if(mAcch.GetGroundH() - temp.y < -30.0f) {
            return FALSE;
        }

        setNpcAction(&daNpc_Cb1_c::jumpNpcAction, NULL);
    }
    else {
        if(chkWallHit()) {
            f32 temp = checkWallJump(*param_2);
            if(temp >= 0.0f) {
                setNpcAction(&daNpc_Cb1_c::jumpNpcAction, &temp);

                return TRUE;
            }

            if(param_1 > SQUARE(600.0f)) {
                return FALSE;
            }

            if(std::fabsf(dComIfGp_getPlayer(0)->current.pos.y - current.pos.y) > 100.0f) {
                return FALSE;
            }
        }

        cXyz temp(current.pos.x, current.pos.y + 100.0f, current.pos.z);
        cXyz temp2(cM_ssin(*param_2) * 80.0f + current.pos.x, current.pos.y + 100.0f, cM_scos(*param_2) * 80.0f + current.pos.z);
        routeWallCheck(temp, temp2, param_2);
    }

    return TRUE;
}

/* 00005F0C-000062F4       .text searchNpcAction__11daNpc_Cb1_cFPv */
BOOL daNpc_Cb1_c::searchNpcAction(void*) {
    f32 temp2;

    if(m8F0 == 0) {
        cLib_onBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
        setAnm(ANM_01);
    }
    else if(m8F0 != -1) {
        s16 temp;
        if(m8E1) {
            s16 temp3 = m8E1 < 0 ? -0x4000 : 0x4000;
            temp = temp3 + cM_atan2s(m91C.x, m91C.z);
        }
        else {
            if(!checkNpcCallCommand()) {
                temp2 = 0.0f;
                
                if(speedF == 0.0f) {
                    setNpcAction(&daNpc_Cb1_c::waitNpcAction, NULL);

                    return TRUE;
                }

                temp2 = 0.0f;
                temp = current.angle.y;
            }
            else {
                mHasAttention = true;

                fopAc_ac_c* pPlayer = dComIfGp_getPlayer(0);

                BOOL door = pPlayer->eventInfo.checkCommandDoor();
                f32 dist_sq = fopAcM_searchPlayerDistance2(this);
                f32 dist_xz_sq = fopAcM_searchPlayerDistanceXZ2(this);

                if(!door && dist_sq < SQUARE(l_HIO.mPlayerChaseDistance)) {
                    temp2 = 0.0f;
                }
                else {
                    temp2 = l_HIO.mChaseDistScale * std::sqrtf(dist_xz_sq);
                    temp2 = cLib_maxLimit(temp2, l_HIO.mMaxWalkSpeed);
                }

                temp = fopAcM_searchPlayerAngleY(this);
                if(door || !routeCheck(dist_xz_sq, &temp) || dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK2000000_e | daPyStts0_UNK100_e | daPyStts0_UNK1_e) || ((daPy_py_c*)pPlayer)->checkAttentionLock()) {
                    temp2 = 0.0f;

                    if(speedF == 0.0f) {
                        offNpcCallCommand();

                        setNpcAction(&daNpc_Cb1_c::waitNpcAction, this);

                        return TRUE;
                    }

                    temp2 = 0.0f;
                    temp = current.angle.y;
                }

                if(dist_xz_sq < SQUARE(400.0f) && cLib_distanceAngleS(shape_angle.y, temp) < 0x2000 && std::fabsf(fopAcM_searchPlayerDistanceY(this)) < 100.0f) {
                    onPlayerFind();
                }

                if(cLib_calcTimer(&m8DF) == 0) {
                    m8DE ^= 1;
                    m8DF = cLib_getRndValue(l_HIO.field_0xE2, l_HIO.field_0xE4);
                }

                temp += m8DE ? -l_HIO.field_0xE6 : l_HIO.field_0xE6;
            }
        }

        if(mCyl.ChkCoHit()) {
            setNpcAction(&daNpc_Cb1_c::hitNpcAction, NULL);
        }
        else {
            walkAction(temp2, l_HIO.mForwardAccel, temp);
        }
    }

    return TRUE;
}

/* 000062F4-00006440       .text hitNpcAction__11daNpc_Cb1_cFPv */
BOOL daNpc_Cb1_c::hitNpcAction(void*) {
    if(m8F0 == 0) {
        cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);

        speedF = cLib_maxLimit(speedF, l_HIO.mMaxWalkSpeed * 0.5f);
        speed.y = l_HIO.mHitSpeedScaleY * std::fabsf(speedF);
        speedF *= l_HIO.mHitSpeedScaleF;

        fopAcM_seStart(this, JA_SE_CM_CB_BOUND, 0);

        setAnm(ANM_02);
    }
    else if(m8F0 != -1 && mAcch.ChkGroundHit()) {
        speedF = 0.0f;

        setNpcAction(&daNpc_Cb1_c::waitNpcAction, NULL);
    }

    return TRUE;
}

/* 00006440-00006518       .text jumpNpcAction__11daNpc_Cb1_cFPv */
BOOL daNpc_Cb1_c::jumpNpcAction(void* param_1) {
    if(m8F0 == 0) {
        if(param_1) {
            speed.y = *(f32*)param_1;
        }
        else {
            speed.y = 10.0f;
        }

        speedF = 4.0f;
        m900 = 0.0f;
        setAnm(ANM_16);
    }
    else if(m8F0 != -1 && mAcch.ChkGroundHit()) {
        checkLanding();
        speedF = 0.0f;
        setNpcAction(&daNpc_Cb1_c::waitNpcAction, NULL);
    }

    return TRUE;
}

/* 00006518-00006574       .text rescueNpcAction__11daNpc_Cb1_cFPv */
BOOL daNpc_Cb1_c::rescueNpcAction(void*) {
#if VERSION == VERSION_DEMO
    if(m8F0 == 0) {
        setAnm(ANM_00);
        fopDwTg_DrawQTo(&draw_tag);
    } else if(m8F0 != -1) {
        m8DD = 0;
    }
#else
    if(m8F0 != -1) {
        if(m8F0 == 0) {
            setAnm(ANM_00);
            fopDwTg_DrawQTo(&draw_tag);
        }

        m8DD = 0;
    }
#endif

    return TRUE;
}

/* 00006574-00006658       .text musicNpcAction__11daNpc_Cb1_cFPv */
BOOL daNpc_Cb1_c::musicNpcAction(void*) {
    if(m8F0 == 0) {
        setAnm(ANM_09);
    }
#if VERSION == VERSION_DEMO
    else if(m8F0 != -1)
#else
    else if(m8F0 != -1 && !isTypeKazeBoss())
#endif
    {
#if VERSION == VERSION_DEMO
        getStickAngY();
#endif
        cLib_addCalcAngleS(&shape_angle.y, home.angle.y, 8, 0x2000, 0x400);
        current.angle.y = shape_angle.y;

        mHasAttention = chkAttention(l_HIO.mNpc.mMaxAttnDistXZ, 0x10000);

        if(mHasAttention) {
            if(isTypeWaterFall()) {
                m8DD = 7;
            }
            else {
                m8DD = 6;
            }

            cLib_onBit<u32>(attention_info.flags, fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_LOCKON_TALK_e);
        }
        else {
            cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_LOCKON_TALK_e);
        }
    }

    return TRUE;
}

/* 00006658-000067A4       .text shipNpcAction__11daNpc_Cb1_cFPv */
BOOL daNpc_Cb1_c::shipNpcAction(void*) {
    if(m8F0 == 0) {
        onNpcNotChange();

        setAnm(ANM_0D);

        speedF = 0.0f;

        m8F0++;
    }
    else if(m8F0 != -1) {
        if(!dComIfGs_isEventBit(0x1604)) {
            setNpcAction(&daNpc_Cb1_c::waitNpcAction, NULL);
            offShipRide();
        }
        else {
            mHasAttention = chkAttention(500.0f, l_HIO.mNpc.mMaxAttnAngleY);

            BOOL temp = mHasAttention;
            if(temp && !dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) && getMsg()) {
                m8DD = 6;
                cLib_onBit<u32>(attention_info.flags, fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_LOCKON_TALK_e);
            }
            else {
                cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_LOCKON_TALK_e);
            }
        }
    }

    return TRUE;
}

/* 000067A4-000069E8       .text waitPlayerAction__11daNpc_Cb1_cFPv */
BOOL daNpc_Cb1_c::waitPlayerAction(void*) {
    if(m8F0 == 0) {
        setAnm(ANM_00);
        cLib_onBit<u32>(attention_info.flags, ~0);
    }
    else if(m8F0 != -1 && !sowCheck()) {
        dAttention_c& attention = dComIfGp_getAttention();

        if(g_mDoCPd_cpadInfo[0].mMainStickValue >= l_HIO.field_0x80 || attention.Lockon()) {
            s16 target = getStickAngY();
            cLib_addCalcAngleS(&current.angle.y, target, 0x19, 0x7FFF, 1);

            cXyz temp;
            int stickPos = calcStickPos(target, &temp);
            if(stickPos == 0) {
                shape_angle.y = current.angle.y;
            }
            else if(g_mDoCPd_cpadInfo[0].mMainStickValue >= l_HIO.field_0x84) {
                shape_angle.y = current.angle.y;
            }

            s16 temp3 = shape_angle.y;
            mJntCtrl.lookAtTarget(&temp3, &temp, current.pos, shape_angle.y, l_HIO.mNpc.mMaxTurnStep, false);

            if(stickPos > 0) {
                shape_angle.y = temp3;
            }

            current.angle.y = shape_angle.y;

            if(g_mDoCPd_cpadInfo[0].mMainStickValue >= l_HIO.field_0x84 && stickPos == 0) {
                current.angle.y = target;
                setPlayerAction(&daNpc_Cb1_c::walkPlayerAction, NULL);
            }
        }
        else {
            mJntCtrl.lookAtTarget(&shape_angle.y, NULL, cXyz::Zero, shape_angle.y, 0, false);
            current.angle.y = shape_angle.y;
        }

        breaking();
    }

    return TRUE;
}

/* 000069E8-00006D00       .text walkPlayerAction__11daNpc_Cb1_cFPv */
BOOL daNpc_Cb1_c::walkPlayerAction(void*) {
    if(m8F0 == 0) {
        setAnm(ANM_01);
        cLib_onBit<u32>(attention_info.flags, ~0);
    }
    else if(m8F0 != -1 && !sowCheck()) {
        f32 temp = g_mDoCPd_cpadInfo[0].mMainStickValue * l_HIO.mStickWalkSpeedScale;
        s16 temp7 = getStickAngY();
        s32 temp2 = cLib_distanceAngleS(temp7, current.angle.y);
        f32 temp6 = l_HIO.mForwardAccel;

        if(temp > speedF) {
            if(temp < l_HIO.mMinWalkSpeed) {
                temp = l_HIO.mMinWalkSpeed;
            }
        }
        else {
            temp6 = l_HIO.mDecel;
        }

        if(temp2 > 0x6000) {
            temp = 0.0f;
            if(speedF != 0.0f) {
                temp7 = current.angle.y;
            }

            temp6 = 2.0f;
        }

        cLib_addCalcAngleS(&current.angle.y, temp7, l_HIO.field_0xEC, l_HIO.field_0xE8, l_HIO.field_0xEA);

        cXyz temp4;
        int stickPos = calcStickPos(temp7, &temp4);
        if(stickPos == 0) {
            cLib_addCalcAngleS(&shape_angle.y, current.angle.y, 8, 0x2000, 0x400);
        }

        s16 temp3 = shape_angle.y;
        mJntCtrl.lookAtTarget(&temp3, &temp4, current.pos, shape_angle.y, l_HIO.mNpc.mMaxTurnStep, false);
        
        if(stickPos > 0) {
            shape_angle.y = temp3;
        }

        temp = cLib_maxLimit(temp, l_HIO.mMaxWalkSpeed);

        if(cLib_chaseF(&speedF, temp, temp6) && temp == 0) {
            setPlayerAction(&daNpc_Cb1_c::waitPlayerAction, NULL);
        }
        else {
            f32 temp8 = speedF * l_HIO.mWalkAnmSpeedScale;
            mpMorf->setPlaySpeed(cLib_minLimit(temp8, l_HIO.mMaxWalkAnmSpeed));

            if(!mAcch.ChkGroundHit()) {
                setPlayerAction(&daNpc_Cb1_c::jumpPlayerAction, NULL);
            }
            else if(chkWallHit()) {
                f32 temp5 = checkWallJump(current.angle.y);
                if(temp5 >= 0.0f) {
                    setPlayerAction(&daNpc_Cb1_c::jumpPlayerAction, &temp5);

                    return TRUE;
                }
            }
        }
    }

    return TRUE;
}

/* 00006D00-00006E20       .text hitPlayerAction__11daNpc_Cb1_cFPv */
BOOL daNpc_Cb1_c::hitPlayerAction(void*) {
    if(m8F0 == 0) {
        speedF = cLib_maxLimit(speedF, 0.5f * l_HIO.mMaxWalkSpeed);
        speed.y = l_HIO.mHitSpeedScaleY * std::fabsf(speedF);
        speedF *= l_HIO.mHitSpeedScaleF;

        fopAcM_seStart(this, JA_SE_CM_CB_BOUND, 0);

        setAnm(ANM_02);
    }
    else if(m8F0 != -1 && mAcch.ChkGroundHit()) {
        m4E4 |= 1;
        speedF = 0.0f;
    }

    return TRUE;
}

/* 00006E20-00006EFC       .text jumpPlayerAction__11daNpc_Cb1_cFPv */
BOOL daNpc_Cb1_c::jumpPlayerAction(void* param_1) {
    if(m8F0 == 0) {
        if(param_1) {
            speed.y = *(f32*)param_1;
        }
        else {
            speed.y = 10.0f;
        }

        m900 = 0.0f;
        setAnm(ANM_16);
    }
    else if(m8F0 != -1 && !flyCheck() && mAcch.ChkGroundHit()) {
        checkLanding();
        speedF = 0.0f;
        setPlayerAction(&daNpc_Cb1_c::waitPlayerAction, NULL);
    }

    return TRUE;
}

/* 00006EFC-00006FFC       .text flyPlayerAction__11daNpc_Cb1_cFPv */
BOOL daNpc_Cb1_c::flyPlayerAction(void*) {
    if(m8F0 == 0) {
        speed.y = l_HIO.mFlyLaunchSpeedY;
        
        setAnm(ANM_04);

        setFlyingTimer(l_HIO.mPlayerFlyTimer);

        fopAcM_monsSeStart(this, JA_SE_CV_CB_LEAF_OUT, 0);
    }
    else if(m8F0 != -1) {
        dComIfGp_setAStatus(dActStts_LET_GO_e);
        flyAction(CPad_CHECK_TRIG_A(0), g_mDoCPd_cpadInfo[0].mMainStickValue * l_HIO.mStickFlySpeedScale, getStickAngY(), CPad_CHECK_TRIG_B(0));
    }

    return TRUE;
}

/* 00006FFC-0000707C       .text carryPlayerAction__11daNpc_Cb1_cFPv */
BOOL daNpc_Cb1_c::carryPlayerAction(void*) {
    if(m8F0 == 0) {
        setAnm(ANM_0B);
        
        fopAcM_monsSeStart(this, JA_SE_CV_CB_DAMAGE_S, 0);
    }

    return TRUE;
}

/* 0000707C-000070D0       .text daNpc_Cb1_XyCheckCB__FPvi */
static s16 daNpc_Cb1_XyCheckCB(void* i_this, int i_itemBtn) {
    return static_cast<daNpc_Cb1_c*>(i_this)->XyCheckCB(i_itemBtn);
}

/* 000070D0-000070D8       .text daNpc_Cb1_XyEventCB__FPvi */
static s16 daNpc_Cb1_XyEventCB(void* param_1, int param_2) {
    return static_cast<daNpc_Cb1_c*>(param_1)->XyEventCB(param_2);
}

/* 000070D8-0000711C       .text calcFlyingTimer__11daNpc_Cb1_cFv */
BOOL daNpc_Cb1_c::calcFlyingTimer() {
    if(getFlyingTimer() != 0 && !cLib_calcTimer(&m_flyingTimer)) {
        return TRUE;
    }

    return FALSE;
}

/* 0000711C-00007250       .text initAnm__11daNpc_Cb1_cFSci */
void daNpc_Cb1_c::initAnm(s8 param_1, BOOL param_2) {
    if(param_1 >= 0) {
        m8DC = param_1;

        AnmData& data = anmTblData[m8DC];

        m8B0 = 0;

        dNpc_setAnm(mpMorf, data.mLoopMode, param_2 ? data.field_0x02 : 0.0f, data.mSpeed, abs(data.mAnmFileIdx), -1, "Cb");

        m8D7 = 0;
        m8D8 = 0;

        if(data.mAnmFileIdx < 0) {
            onMusic();
        }
        else {
            offMusic();
        }
    }
}

/* 00007250-000072B4       .text musicPlay__11daNpc_Cb1_cFv */
void daNpc_Cb1_c::musicPlay() {
    if(!isTypeKazeBoss()) {
        mDoAud_cbPracticePlay(&eyePos);
    }
    else {
        mDoAud_bgmStart(JA_BGM_MAKORE_TAKT_8);
    }
}

/* 000072B4-000072EC       .text musicStop__11daNpc_Cb1_cFv */
void daNpc_Cb1_c::musicStop() {
    if(!isTypeKazeBoss()) {
        mDoAud_cbPracticeStop();
    }
}

daNpc_Cb1_c::AnmData daNpc_Cb1_c::anmTblData[] = {
    {0x17, 0x02, 0x08, 0x01, -1, -1},
    {0x1A, 0x02, 0x04, 0x01, -1, -1},
    {0x0C, 0x00, 0x04, 0x01, -1, -1},
    {0x0B, 0x02, 0x04, 0x01, -1, -1},
    {0x10, 0x00, 0x04, 0x01, -1, -1},
    {0x11, 0x02, 0x00, 0x01, -1, -1},
    {0x09, 0x02, 0x0F, 0x01, -1, -1},
    {-0x18, 0x02, 0x10, 0x01, -1, -1},
    {-0x13, 0x02, 0x08, 0x01, -1, -1},
    {-0x12, 0x02, 0x08, 0x01, -1, -1},
    {0x0D, 0x02, 0x08, 0x01, -1, -1},
    {0x15, 0x00, 0x08, 0x01, -1, -1},
    {0x14, 0x02, 0x08, 0x01, -1, -1},
    {-0x18, 0x02, 0x08, 0x01, 0x02, 0x0E},
    {-0x04, 0x00, 0x10, 0x01, -1, 0x0F},
    {-0x18, 0x02, 0x00, 0x01, 0x02, -1},
    {-0x13, 0x00, 0x10, 0x01, -1, 0x11},
    {-0x12, 0x02, 0x00, 0x01, 0x18, 0x12},
    {-0x13, 0x00, 0x00, 0x01, -1, 0x13},
    {-0x18, 0x02, 0x10, 0x01, 0x03, 0x10},
    {0x06, 0x02, 0x08, 0x01, 0x04, 0x00},
    {0x05, 0x00, 0x08, 0x01, -1, 0x00},
    {0x07, 0x00, 0x08, 0x01, -1, 0x17},
    {0x06, 0x02, 0x08, 0x01, -1, -1},
    {0x08, 0x02, 0x08, 0x01, -1, -1},
    {0x19, 0x02, 0x08, 0x01, 0x03, 0x00},
    {0x0A, 0x02, 0x08, 0x01, -1, -1},
    {0x17, 0x02, 0x08, 0x01, -1, -1},
};
s8 daNpc_Cb1_c::anmPrmData[] = {0, 1, 2, 3, 4, 5, 4, 6, 7, 0x10, 8, 0xA, 0xB, 0xC, 0xE, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x09};

/* 000072EC-00007390       .text setAnm__11daNpc_Cb1_cFUc */
BOOL daNpc_Cb1_c::setAnm(u8 param_1) {
    if(m8DB == param_1) {
        return FALSE;
    }

    if(m8DB == 9) {
#if VERSION == VERSION_DEMO
        mDoAud_cbPracticeStop();
#else
        musicStop();
#endif
    }

    m8DB = param_1;

    if(m8DB == 9) {
        fopAcM_OnStatus(this, fopAcStts_NOPAUSE_e);
    }
    else {
        fopAcM_OffStatus(this, fopAcStts_NOPAUSE_e);
    }

    initAnm(anmPrmData[m8DB], 1);

    return TRUE;
}

/* 00007390-000074F0       .text playAnm__11daNpc_Cb1_cFv */
void daNpc_Cb1_c::playAnm() {
    BOOL r3 = mpMorf->play(
        &eyePos,
#if VERSION == VERSION_DEMO
        mAcch.ChkGroundHit() ? dComIfG_Bgsp()->GetMtrlSndId(mAcch.m_gnd) : 0,
#else
        (m_status & daCbStts_UNK_0100) && mAcch.ChkGroundHit() ? dComIfG_Bgsp()->GetMtrlSndId(mAcch.m_gnd) : 0,
#endif
        dComIfGp_getReverb(fopAcM_GetRoomNo(this))
    );
    if(r3 || mpMorf->getFrame() < m8B0) {
        m8D7 = 1;
        m8D8++;

        AnmData& data = anmTblData[m8DC];

#if VERSION == VERSION_DEMO
        if(m8D8 >= data.field_0x04)
#else
        s8 temp = data.field_0x04;
        if(isTypeKazeBoss() && temp == 0x18) {
            temp = 0xD;
        }
        if(m8D8 >= temp)
#endif
        {
            if(data.field_0x05 == 0x13) {
#if VERSION == VERSION_DEMO
                mDoAud_cbPracticeStop();
#else
                musicStop();
#endif
            }
            else if(data.field_0x05 == 0x11) {
#if VERSION == VERSION_DEMO
                mDoAud_cbPracticePlay(&eyePos);
#else
                musicPlay();
#endif
            }

            initAnm(data.field_0x05, 1);
        }
    }

    m8B0 = mpMorf->getFrame();
}

/* 000074F0-00007650       .text chkAttention__11daNpc_Cb1_cFfl */
BOOL daNpc_Cb1_c::chkAttention(f32 param_1, s32 param_2) {
    cXyz temp;
    temp.x = dComIfGp_getPlayer(0)->current.pos.x - current.pos.x;
    temp.z = dComIfGp_getPlayer(0)->current.pos.z - current.pos.z;

    f32 diff = std::sqrtf(SQUARE(temp.x) + SQUARE(temp.z));
    s16 angle = cM_atan2s(temp.x, temp.z);

    if(mHasAttention) {
        param_1 += 40.0f;
        param_2 += 0x71C;
    }

    s16 temp2 = shape_angle.y + getHead_y() + getBackbone_y();
    angle -= temp2;

    BOOL result = FALSE;
    if(abs(angle) < param_2 && param_1 > diff) {
        result = TRUE;
    }

    return result;
}

/* 00007650-000076A4       .text carryCheck__11daNpc_Cb1_cFv */
void daNpc_Cb1_c::carryCheck() {
    if(fopAcM_checkCarryNow(this)) {
        setNpcAction(&daNpc_Cb1_c::carryNpcAction, NULL);
    }
}

/* 000076A4-0000776C       .text eventOrder__11daNpc_Cb1_cFv */
void daNpc_Cb1_c::eventOrder() {
    if(m8DD == 5 || m8DD == 6) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);

        if(m8DD == 5) {
            fopAcM_orderSpeakEvent(this);
        }
    }
    else if(m8DD == 7) {
        eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
    }
    else if(m8DD != -1 && m8DD < 5) {
        m8E3 = m8DD;
        if(m8E3 != -1 && mEventIdx[m8E3] != -1) {
            fopAcM_orderOtherEventId(this, mEventIdx[m8E3]);
        }
    }
}

/* 0000776C-00007848       .text checkOrder__11daNpc_Cb1_cFv */
void daNpc_Cb1_c::checkOrder() {
    if(eventInfo.checkCommandTalk()) {
        if(m8DD == 5 || m8DD == 6 || m8DD == 7) {
            m8DD = -1;
            if(dComIfGp_event_chkTalkXY()) {
                onTact();
            }
            else {
                setNpcAction(&daNpc_Cb1_c::talkNpcAction, NULL);
            }

            fopAcM_cancelCarryNow(this);
        }
    }
}

/* 00007848-000078C4       .text checkCommandTalk__11daNpc_Cb1_cFv */
BOOL daNpc_Cb1_c::checkCommandTalk() {
    if(eventInfo.checkCommandTalk()) {
        if(dComIfGp_event_chkTalkXY()) {
            if(m8DD == 7) {
                m8DD = -1;
            }

            onTact();

            return FALSE;
        }

        return TRUE;
    }

    return FALSE;
}

/* 000078C4-000079AC       .text next_msgStatus__11daNpc_Cb1_cFPUl */
u16 daNpc_Cb1_c::next_msgStatus(u32* pMsgNo) {
    if(*pMsgNo == 0x5AC) {
        return fopMsgStts_MSG_ENDS_e;
    }
    else if(*pMsgNo == 0x1520 || (0x1519 <= *pMsgNo && *pMsgNo <= 0x151D) || *pMsgNo == 0x1523 || (0x14C2 <= *pMsgNo && *pMsgNo <= 0x14C3)) {
        *pMsgNo += 1;
    }
    else if(*pMsgNo == 0x151E) {
        dComIfGs_onEventBit(0x1880);
        return fopMsgStts_MSG_ENDS_e;
    }
    else if(*pMsgNo == 0x1521) {
        dComIfGs_onEventBit(0x1840);
        return fopMsgStts_MSG_ENDS_e;
    }
    else if(*pMsgNo == 0x14C4) {
        dComIfGs_onEventBit(0x1904);
        return fopMsgStts_MSG_ENDS_e;
    }
    else {
        return fopMsgStts_MSG_ENDS_e;
    }

    return fopMsgStts_MSG_CONTINUES_e;
}

/* 000079AC-00007A8C       .text getMsg__11daNpc_Cb1_cFv */
u32 daNpc_Cb1_c::getMsg() {
#if VERSION == VERSION_DEMO
    if(isShipRide()) {
        return 0x152F;
    }
#endif

    if(isTypeBossDie()) {
        return 0x1456;
    }

    if(isTypeForest()) {
        return dComIfGs_isEventBit(0x1904) ? 0x14C5 : 0x14C2;
    }

    if(isTypeWaterFall()) {
        if(isTact()) {
            return dComIfGs_isEventBit(0x1840) ? 0x1522 : 0x1520;
        }

        return dComIfGs_isEventBit(0x1880) ? 0x151F : 0x1519;
    }

#if VERSION > VERSION_DEMO
    if(isShipRide()) {
        return 0x152F;
    }
#endif

    return 0;
}

/* 00007A8C-00007B38       .text setCollision__11daNpc_Cb1_cFv */
void daNpc_Cb1_c::setCollision() {
    mCyl.SetC(current.pos);
    mCyl.SetR(20.0f);
    mCyl.SetH(60.0f);

    dComIfG_Ccsp()->Set(&mCyl);

    mWindCyl.SetC(current.pos);
    mWindCyl.SetR(20.0f);
    mWindCyl.SetH(60.0f);

    dComIfG_Ccsp()->Set(&mWindCyl);
}

/* 00007B38-00007C4C       .text lookBack__11daNpc_Cb1_cFi */
void daNpc_Cb1_c::lookBack(BOOL param_1) {
    cXyz* dstPos = NULL;
    cXyz vec2;
    cXyz vec(0.0f, 0.0f, 0.0f);

    s16 desiredY = shape_angle.y;

    if(mJntCtrl.trnChk()) {
        cLib_addCalcAngleS2(&m8D0, l_HIO.mNpc.mMaxHeadTurnVel, 4, 0x800);
    }
    else {
        m8D0 = 0;
    }

    if(param_1) {
        vec2 = dNpc_playerEyePos(l_HIO.mNpc.m04);
        dstPos = &vec2;
        vec = current.pos;
        vec.y = eyePos.y;
    }

    mJntCtrl.lookAtTarget(&shape_angle.y, dstPos, vec, desiredY, m8D0, 0);
}

/* 00007C4C-00007E7C       .text setBaseMtx__11daNpc_Cb1_cFv */
void daNpc_Cb1_c::setBaseMtx() {
    J3DModel* pModel = mpMorf->getModel();

    if(isShipRide()) {
        daShip_c* pShip = dComIfGp_getShipActor();
        if(pShip != NULL) {
            mDoMtx_stack_c::copy(pShip->getHeadJntMtx());
            mDoMtx_stack_c::transM(10.92f, 0.57f, -14.0f);
            mDoMtx_stack_c::XYZrotM(-0x3AAA, 0, 0x40FE);

            pModel->setBaseTRMtx(mDoMtx_stack_c::get());
            MtxP pMtx = mDoMtx_stack_c::get();
            current.pos.set(pMtx[0][3], pMtx[1][3], pMtx[2][3]);

            shape_angle.y = pShip->shape_angle.y + 0x8000;

            fopAcM_OnStatus(this, fopAcStts_UNK4000_e);

            tevStr.mRoomNo = pShip->tevStr.mRoomNo;
            tevStr.mEnvrIdxOverride = pShip->tevStr.mEnvrIdxOverride;

            pShip->onCb1Ride();

            fopAcM_onDraw(this);
        }
    }
    else {
        pModel->setBaseScale(scale);

        mDoMtx_stack_c::transS(current.pos.x, current.pos.y + 25.0f, current.pos.z);
        mDoMtx_stack_c::YrotM(shape_angle.y);
        mDoMtx_stack_c::transM(m904);
        mDoMtx_stack_c::XrotM(shape_angle.x);
        mDoMtx_stack_c::transM(0.0f, -25.0f, 0.0f);
        mDoMtx_stack_c::ZrotM(shape_angle.z);

        pModel->setBaseTRMtx(mDoMtx_stack_c::get());

        if(mpNutModel && isNut()) {
            mpNutModel->setBaseTRMtx(mDoMtx_stack_c::get());
        }

        if(mpPropellerModel) {
            mDoMtx_stack_c::transM(0.0f, 24.8f, 1.5f);
            mpPropellerModel->setBaseTRMtx(mDoMtx_stack_c::get());
            mpPropellerModel->calc();
        }
    }
}

/* 00007E7C-00008104       .text init__11daNpc_Cb1_cFv */
BOOL daNpc_Cb1_c::init() {
    gravity = l_HIO.field_0x70;

#if VERSION > VERSION_DEMO
    offPlayerRoom();
    offFlying();
    setFlyingTimer(0);
    m_status = 0;
#endif

    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xAB;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xAB;
    attention_info.distances[fopAc_Attn_TYPE_CARRY_e] = 8;

#if VERSION == VERSION_DEMO
    if(!dComIfGs_isEventBit(0x1610)) {
        onNpcNotChange();
    }

    if (shipRideCheck()) {
        attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xAF;
        attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xAF;
    } else if(isTypeBossDie()) {
        setNpcAction(&daNpc_Cb1_c::rescueNpcAction, NULL);
    } else if(isTypeForest()) {
        setNpcAction(&daNpc_Cb1_c::musicNpcAction, NULL);
    } else if(isTypeWaterFall()) {
        setNpcAction(&daNpc_Cb1_c::musicNpcAction, NULL);
    } else {
        if(isTypeEkaze()) {
            onNpcCallCommand();
            setNpcAction(&daNpc_Cb1_c::waitNpcAction, NULL);
        } else {
            setNpcAction(&daNpc_Cb1_c::waitNpcAction, NULL);
        }
        offMusic();
    }
#else
    static const char* l_eventNameTbl[] = {
        "cb_rescue",
        "OPTION_CHAR_END",
        "cb_tact",
        "cb_tactCancel",
        "cb_sow"
    };

    for(int i = 0; i < 5; i++) {
        mEventIdx[i] = dComIfGp_evmng_getEventIdx(l_eventNameTbl[i]);
    }

    m8E3 = -1;
    m8DD = -1;

    eventInfo.setXyCheckCB(&daNpc_Cb1_XyCheckCB);
    eventInfo.setXyEventCB(&daNpc_Cb1_XyEventCB);

    onNpcNotChange();

    if(isTypeKazeBoss() || isTypeForest() || isTypeWaterFall()) {
        setNpcAction(&daNpc_Cb1_c::musicNpcAction, NULL);

        home.roomNo = -1;
        current.roomNo = -1;

        gravity = -0.1f;
    }
    else if(isTypeBossDie()) {
        setNpcAction(dComIfGs_isStageBossEnemy(4) ? &daNpc_Cb1_c::waitNpcAction : &daNpc_Cb1_c::rescueNpcAction, NULL);
    }
    else if(!isTypeEkaze() && !isTypeKaze() && shipRideCheck()) {
        attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xAF;
        attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xAF;
    }
    else {
        if(dComIfGs_isEventBit(0x1610)) {
            offNpcNotChange();
        }

        if(isTypeEkaze()) {
            onNpcCallCommand();
        }

        setNpcAction(&daNpc_Cb1_c::waitNpcAction, NULL);

        offMusic();
    }
#endif

    mStts.Init(0xFE, 0xFF, this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);
    mWindCyl.Set(l_wind_cyl_src);
    mWindCyl.SetStts(&mStts);

#if VERSION == VERSION_DEMO
    static const char* l_eventNameTbl[] = {
        "cb_rescue",
        "OPTION_CHAR_END",
        "cb_tact",
        "cb_tactCancel",
        "cb_sow"
    };

    for(int i = 0; i < 5; i++) {
        mEventIdx[i] = dComIfGp_evmng_getEventIdx(l_eventNameTbl[i]);
    }

    m8E3 = -1;

    eventInfo.setXyCheckCB(&daNpc_Cb1_XyCheckCB);
    eventInfo.setXyEventCB(&daNpc_Cb1_XyEventCB);
#endif

    return TRUE;
}

/* 00008104-000084A4       .text draw__11daNpc_Cb1_cFv */
BOOL daNpc_Cb1_c::draw() {
    if(isShipRide()) {
        daShip_c* pShip = dComIfGp_getShipActor();
        if(pShip && pShip->checkHeadNoDraw()) {
            return TRUE;
        }
    }
    else
#if VERSION > VERSION_DEMO
    if(!fopAcM_checkCarryNow(this))
#endif
    {
        s32 homeRoomNo = fopAcM_GetHomeRoomNo(this);
        if (homeRoomNo < 0 || !dComIfGp_roomControl_checkStatusFlag(homeRoomNo, 0x10)) {
            return TRUE;
        }
    }

    J3DModel* pModel = mpMorf->getModel();

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    drawDamageFog();
    g_env_light.setLightTevColorType(pModel, &tevStr);

    mpMorf->updateDL();

    J3DModel* pFaceModel = mpFaceModel;
    g_env_light.setLightTevColorType(pFaceModel, &tevStr);

    pFaceModel->setBaseTRMtx(pModel->getAnmMtx(m_backbone_jnt_num));
    mDoExt_modelUpdateDL(pFaceModel);

    mShadowId = 0;
    if(
#if VERSION > VERSION_DEMO
        (m_status & daCbStts_UNK_0100) &&
#endif
        fopAcM_GetHomeRoomNo(this) >= 0 && !fopAcM_checkCarryNow(this) && !isShipRide()
    ) {
        cXyz shadowPos(current.pos.x, current.pos.y + 80.0f, current.pos.z);
        mShadowId = dComIfGd_setShadow(
            mShadowId, 0, mpMorf->getModel(), &shadowPos, 600.0f, 20.0f,
            current.pos.y, mAcch.GetGroundH(), mAcch.m_gnd, &tevStr
        );
    }

    if(isMusic()) {
        g_env_light.setLightTevColorType(mpStickModel, &tevStr);

        mpStickModel->setBaseTRMtx(pModel->getAnmMtx(m_armRend_jnt_num));
        mDoExt_modelUpdateDL(mpStickModel);

        g_env_light.setLightTevColorType(mpCelloModel, &tevStr);

        mpCelloModel->setBaseTRMtx(pModel->getAnmMtx(m_armL2_jnt_num));
        mDoExt_modelUpdateDL(mpCelloModel);

        if(
#if VERSION > VERSION_DEMO
            (m_status & daCbStts_UNK_0100) &&
#endif
            mShadowId
        ) {
            dComIfGd_addRealShadow(mShadowId, mpStickModel);
            dComIfGd_addRealShadow(mShadowId, mpCelloModel);
        }
    }
    else {
        if(mpPropellerModel && isFlyAction() && m8DC != 2) {
            f32 frame = 11.0f;
            if(m8DC == 4) {
                frame = mpMorf->getFrame();
            }
            mPropellerBckAnim.entry(mpPropellerModel->getModelData(), frame);

            g_env_light.setLightTevColorType(mpPropellerModel, &tevStr);

            mDoExt_modelUpdateDL(mpPropellerModel);

            if(
#if VERSION > VERSION_DEMO
                (m_status & daCbStts_UNK_0100) &&
#endif
                mShadowId
            ) {
                dComIfGd_addRealShadow(mShadowId, mpPropellerModel);
            }
        }
        else if(mpNutModel && isNut()) {
            J3DModelData* pModelData = mpNutModel->getModelData();
            mNutBckAnim.entry(pModelData, mNutBckAnim.getFrame());

            g_env_light.setLightTevColorType(mpNutModel, &tevStr);

            mDoExt_modelUpdateDL(mpNutModel);
        }
    }

    dSnap_RegistFig(DSNAP_TYPE_CB1, this, 1.0f, 1.0f, 1.0f);

    return TRUE;
}

/* 000084A4-00009090       .text execute__11daNpc_Cb1_cFv */
BOOL daNpc_Cb1_c::execute() {
    cLib_offBit<u32>(actor_status, fopAcStts_SHOWMAP_e);

    executeDamageFog();

    fopAcM_setStageLayer(this);

    if(fopAcM_GetRoomNo(this) == dComIfGp_roomControl_getStayNo()) {
        onPlayerRoom();
    }
    else {
        offPlayerRoom();
    }
    
#if VERSION > VERSION_DEMO
    m_status &= ~daCbStts_UNK_0100;
#endif

    if(
        !isShipRide()
#if VERSION > VERSION_DEMO
        && !fopAcM_checkCarryNow(this)
#endif
    ) {
        if(
            !check_initialRoom()
#if VERSION > VERSION_DEMO
            || (isTypeKazeBoss() && !dComIfG_Bgsp()->ChkMoveBG_NoDABg(mAcch.m_gnd))
#endif
        ) {
#if VERSION > VERSION_DEMO
            home.roomNo = 0xFF;
            current.roomNo = 0xFF;
#endif

            if(dComIfGp_getCb1Player() == this) {
                dComIfGp_setCb1Player(NULL);
            }

            return TRUE;
        }

        initialRestartOption(1, isTypeKaze());

        if(!isShipRide() && check_moveStop()) {
            setWaitNpcAction(NULL);

            return TRUE;
        }

        if(m8E0 && dComIfG_Bgsp()->ChkPolySafe(mPolyInfo) && dComIfG_Bgsp()->ChkMoveBG(mPolyInfo)) {
            cXyz temp = old.pos;
            dComIfG_Bgsp()->MoveBgCrrPos(mPolyInfo, true, &old.pos, NULL, NULL);
        }

        mJntCtrl.setParam(l_HIO.mNpc.mMaxBackboneX, l_HIO.mNpc.mMaxBackboneY,
            l_HIO.mNpc.mMinBackboneX, l_HIO.mNpc.mMinBackboneY,
            l_HIO.mNpc.mMaxHeadX, l_HIO.mNpc.mMaxHeadY,
            l_HIO.mNpc.mMinHeadX, l_HIO.mNpc.mMinHeadY,
            l_HIO.mNpc.mMaxTurnStep
        );
    }

#if VERSION == VERSION_DEMO
    if (checkNowPosMove("Cb1")) {
        playAnm();
    }
#endif

    cXyz temp2 = cXyz::Zero;
    f32 temp3 = 3.0f;

    if(!fopAcM_checkCarryNow(this) && !isShipRide()) {
        if(checkNowPosMove("Cb1") && !(m4E4 & 1)) {
            f32 temp4 = current.pos.y;
            fopAcM_posMoveF(this, mStts.GetCCMoveP());
            m900 += temp4 - current.pos.y;
            current.pos.x += m88C.x;
            current.pos.z += m88C.z;
            maxFallSpeed = -100.0f;
            gravity = l_HIO.field_0x70;
        }

        m8E0 = mAcch.ChkGroundHit();
        mAcch.CrrPos(*dComIfG_Bgsp());
#if VERSION > VERSION_DEMO
        m_status |= daCbStts_UNK_0100;
#endif

        if(mAcch.GetGroundH() == -G_CM3D_F_INF || dComIfG_Bgsp()->GetGroundCode(mAcch.m_gnd) == 4) {
            if(isFlyAction() && m8FC > -400.0f) {
                m4E8 = 0;
            }
            else if(m4E8 < 0x1E) {
                m4E8++;
            }
            else if(!dComIfGp_roomControl_checkStatusFlag(fopAcM_GetHomeRoomNo(this), 0x10)) {
                current = home;
                shape_angle = home.angle;
                speedF = 0.0f;
                m4E8 = 0;

                fopAcM_seStart(this, JA_SE_CV_CB_LEFT_ALONE, 0);
            }
            else {
                daPy_getPlayerLinkActorClass()->npcStartRestartRoom();
            }
        }
        else {
            m4E8 = 0;
        }

        if(mAcch.GetGroundH() != -G_CM3D_F_INF) {
            cM3dGPla* pla = dComIfG_Bgsp()->GetTriPla(mAcch.m_gnd);
            if(pla) {
                m910 = pla->mNormal;

                if(m8E0) {
                    maxFallSpeed = -4.0f - (1.0f - m910.y) * 100.0f;

                    if(dComIfG_Bgsp()->GetSpecialCode(mAcch.m_gnd) == 1) {
                        f32 temp = m910.abs2XZ();
                        temp2.x = m910.x * 40.0f;
                        temp2.z = m910.z * 40.0f;
                        speed.y = std::sqrtf(1.0f - temp) * -40.0f;
                        maxFallSpeed = speed.y;
                        temp3 = temp * 2.0f;

                        checkLanding();
                    }
                }
            }

            s8 roomNo = dComIfG_Bgsp()->GetRoomId(mAcch.m_gnd);
            fopAcM_SetRoomNo(this, roomNo);
            tevStr.mRoomNo = roomNo;
            tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mAcch.m_gnd);
            mStts.SetRoomId(roomNo);
            mPolyInfo = mAcch.m_gnd;
        }

        setCollision();
    }

#if VERSION > VERSION_DEMO
    if(checkNowPosMove("Cb1")) {
        playAnm();
    }

    if(dComIfGp_getPlayer(0) == this) {
        dComIfGp_setDoStatus(dActStts_BLANK_e);
        dComIfGp_setAStatus(dActStts_HIDDEN_e);
        dComIfGp_setRStatusForce(dActStts_BLANK_e);
    }
#endif

    if(!eventProc()) {
        offTact();

        if(
            !isFlyAction()
#if VERSION > VERSION_DEMO
            && !isMusic()
#endif
            && mWindCyl.ChkTgHit()
        ) {
            temp2 = *mWindCyl.GetTgRVecP();
            f32 temp = mWindCyl.GetTgRVecP()->absXZ();
            if(temp < 1.0f) {
                temp2 = (current.pos - *mWindCyl.GetTgHitPosP()) * 30.0f;
            }

            if(temp > 30.0f) {
                temp2 *= 30.0f / temp;
            }

            temp3 = 1.0f;
        }

        cLib_addCalcPosXZ(&m88C, temp2, 0.5f, temp3, 0.5f);
        if(dComIfGp_getPlayer(0) == this) {
#if VERSION == VERSION_DEMO
            int r4 = dActStts_BLANK_e;
            dComIfGp_setDoStatus(r4);
            dComIfGp_setAStatus(dActStts_HIDDEN_e);
            if(mAcch.ChkGroundHit()) {
                r4 = dActStts_RETURN_e;
            }
            dComIfGp_setRStatusForce(r4);
#else
            if(mAcch.ChkGroundHit()) {
                dComIfGp_setRStatusForce(dActStts_RETURN_e);
            }
#endif

            fopAcM_SetStatusMap(this, 0x12);

            if(m4E4 & 1) {
                m8DD = 1;
            }
            else {
                if(isNoCarryAction()) {
                    setPlayerAction(&daNpc_Cb1_c::carryPlayerAction, NULL);
                    m4E4 |= 1;
                }

#if VERSION == VERSION_DEMO
                playerAction(NULL);

                if(dComIfGp_getRStatusForce() == 7 && !dComIfGp_event_runCheck() && (CPad_CHECK_TRIG_R(0) || CPad_CHECK_TRIG_START(0))) {
                    m4E4 |= 1;
                } else
#else

                if(!dComIfGp_event_runCheck() && dComIfGp_getRStatusForce() == 7 && !dComIfGp_event_runCheck() && (CPad_CHECK_TRIG_R(0) || CPad_CHECK_TRIG_START(0))) {
                    m4E4 |= 1;
                }

                playerAction(NULL);
#endif

                if(
                    getDamageFogTimer() == 0
#if VERSION > VERSION_DEMO
                    && !isMusic()
#endif
                    && mCyl.ChkTgHit()
                    && mCyl.GetTgHitObj()
                ) {
                    cXyz temp = current.pos - *mCyl.GetTgHitPosP();
                    current.angle.y = cM_atan2s(temp.x, temp.z);
                    speedF = l_HIO.field_0xC4;
                    setPlayerAction(&daNpc_Cb1_c::hitPlayerAction, NULL);
                    setDamageFogTimer(l_HIO.mDamageTimer);
                    fopAcM_monsSeStart(this, JA_SE_CV_CB_DAMAGE, 0);
                }
            }

            m8E2 = dComIfGp_getDoStatus();
        }
        else {
            m8E1 = chkMoveBlock(&m91C);

            if(dComIfGs_isEventBit(0x1610)) {
                fopAcM_SetStatusMap(this, 0xD);
            }
            else {
                fopAcM_SetStatusMap(this, 0x7);
            }

            carryCheck();
            checkOrder();
            npcAction(NULL);

            if(!chkNpcAction(&daNpc_Cb1_c::flyNpcAction)) {
                current.angle.y = shape_angle.y;
            }

            if(
                getDamageFogTimer() == 0 &&
#if VERSION > VERSION_DEMO
                !isMusic() &&
#endif
                mCyl.ChkTgHit() &&
                mCyl.GetTgHitObj()
            ) {
                cXyz temp = current.pos - *mCyl.GetTgHitPosP();
                current.angle.y = cM_atan2s(temp.x, temp.z);
                speedF = l_HIO.field_0xC4;
                setNpcAction(&daNpc_Cb1_c::hitNpcAction, NULL);
                setDamageFogTimer(l_HIO.mDamageTimer);
                fopAcM_monsSeStart(this, JA_SE_CV_CB_DAMAGE, 0);
            }

            m8E2 = 0;
        }
    }

    eventOrder();
    setBaseMtx();

    cXyz temp5(0.0f, l_HIO.mNpc.mAttnYOffset, 0.0f);
    cLib_offsetPos(&attention_info.position, &current.pos, shape_angle.y, &temp5);
    cXyz temp6(0.0f, l_HIO.field_0x30, 0.0f);
    cLib_offsetPos(&eyePos, &current.pos, shape_angle.y, &temp6);

    return TRUE;
}

/* 00009090-000093A8       .text __dt__11daNpc_Cb1_cFv */
daNpc_Cb1_c::~daNpc_Cb1_c() {
    dComIfG_resDelete(&mPhs, "Cb");


#if VERSION == VERSION_DEMO
    if(mpMorf)
#else
    if(heap && mpMorf)
#endif
    {
        mpMorf->stopZelAnime();
    }

    if(l_HIO.mNo >= 0) {
        mDoHIO_deleteChild(l_HIO.mNo);
        l_HIO.mNo = -1;
    }

    offFlying();
    offPlayerRoom();

#if VERSION == VERSION_DEMO
    mDoAud_cbPracticeStop();
#else
    musicStop();
#endif
}

/* 000093A8-000093C8       .text daNpc_Cb1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Cb1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Cb1_c*)i_this)->create();
}

/* 000093C8-000093F0       .text daNpc_Cb1_Delete__FP11daNpc_Cb1_c */
static BOOL daNpc_Cb1_Delete(daNpc_Cb1_c* i_this) {
    ((daNpc_Cb1_c*)i_this)->~daNpc_Cb1_c();
    return TRUE;
}

/* 000093F0-00009410       .text daNpc_Cb1_Execute__FP11daNpc_Cb1_c */
static BOOL daNpc_Cb1_Execute(daNpc_Cb1_c* i_this) {
    return ((daNpc_Cb1_c*)i_this)->execute();
}

/* 00009410-00009430       .text daNpc_Cb1_Draw__FP11daNpc_Cb1_c */
static BOOL daNpc_Cb1_Draw(daNpc_Cb1_c* i_this) {
    return ((daNpc_Cb1_c*)i_this)->draw();
}

/* 00009430-00009438       .text daNpc_Cb1_IsDelete__FP11daNpc_Cb1_c */
static BOOL daNpc_Cb1_IsDelete(daNpc_Cb1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Cb1_Method = {
    (process_method_func)daNpc_Cb1_Create,
    (process_method_func)daNpc_Cb1_Delete,
    (process_method_func)daNpc_Cb1_Execute,
    (process_method_func)daNpc_Cb1_IsDelete,
    (process_method_func)daNpc_Cb1_Draw,
};

actor_process_profile_definition g_profile_NPC_CB1 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_CB1,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Cb1_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_CB1,
    /* Actor SubMtd */ &l_daNpc_Cb1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_FREEZE_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e | fopAcStts_UNK2000000_e,
    /* Group        */ fopAc_NPC_e,
    /* CullType     */ fopAc_CULLBOX_12_e,
};
