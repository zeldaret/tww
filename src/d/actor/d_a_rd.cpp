/**
 * d_a_rd.cpp
 * Enemy - ReDead
 */

#include "d/actor/d_a_rd.h"
#include "d/res/res_rd.h"
#include "d/d_procname.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_mtx.h"
#include "d/d_lib.h"
#include "d/d_material.h"
#include "d/d_snap.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_player_main.h"
#include "d/d_cc_uty.h"
#include "d/d_s_play.h"
#include "d/d_item_data.h"
#include "m_Do/m_Do_controller_pad.h"

// Needed for the .data section to match.
static Vec dummy1 = {1.0f, 1.0f, 1.0f};
static Vec dummy2 = {1.0f, 1.0f, 1.0f};
static u8 dummy3[4] = {0x02, 0x00, 0x02, 0x01};
static f64 dummy4[2] = {3.0, 0.5};

static u8 dummy5[0x4C];

static daRd_HIO_c l_HIO;

const u32 daRd_c::m_heapsize = 0x2520;
const char daRd_c::m_arc_name[] = "Rd";
const dCcD_SrcCyl daRd_c::m_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ ~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_WIND | AT_TYPE_UNK400000),
        /* SrcObjTg  SPrm    */ TG_SPRM_SET | TG_SPRM_IS_OTHER,
        /* SrcObjCo  SPrm    */ CO_SPRM_SET | CO_SPRM_IGRP | CO_SPRM_VSGRP,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ dCcD_SE_UNK23,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ G_TG_SPRM_NO_CON_HIT | G_TG_SPRM_NO_HIT_MARK,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 0.0f,
        /* Height */ 0.0f,
    },
};

/* 000000EC-0000027C       .text __ct__10daRd_HIO_cFv */
daRd_HIO_c::daRd_HIO_c() {
    m2C = 0x0;
    m30 = 650.0f;
    m34 = 650.0f;
    mCryRadius = 500.0f;
    mAttackRadius = 125.0f;
    m40 = 0x2000;
    mCrySpreadAngle = 0x1B58;
    mAttackSpreadAngle = 0x6000;
    m46 = 0xA;
    m48 = 0x5;
    m4A = 0x3C;
    m4C = 0x32;
    m4E = 0x384;
    m58 = 10.0f;
    m5C = 10.0f;
    m60 = 50.0f;
    m64 = 30.0f;
    m68 = 1.8f;
    mReturnWalkSpeed = 2.0f;
    m70 = 1.25f;
    m74 = 0.9f;
    m50 = 0x28;
    m78 = 0x2D;
    m54 = 0x87;
    m52 = 0x96;
    mParalysisDuration = 2*30;
    mNpc.m04 = -20.0f;
    mNpc.mMaxHeadX = 0x1FFE;
    mNpc.mMaxHeadY = 0x4000;
    mNpc.mMaxBackboneX = 0x0;
    mNpc.mMaxBackboneY = 0x2000;
    mNpc.mMinHeadX = -0x9C4;
    mNpc.mMinHeadY = -0x4000;
    mNpc.mMinBackboneX = 0x0;
    mNpc.mMinBackboneY = -0x2000;
    mNpc.mMaxTurnStep = 0x250;
    mNpc.mMaxHeadTurnVel = 0x150;
    mNpc.mAttnYOffset = 50.0f;
    mNpc.mMaxAttnAngleY = 0x7FFF;
    mNpc.m22 = 0x0;
    mNpc.mMaxAttnDistXZ = 400.0f;
}

/* 0000027C-000002A8       .text searchNeadDeadRd_CB__FPvPv */
static void* searchNeadDeadRd_CB(void* i_actor, void* i_this) {
    return static_cast<daRd_c*>(i_this)->_searchNearDeadRd(static_cast<fopAc_ac_c*>(i_actor));
}

/* 000002A8-0000030C       .text _searchNearDeadRd__6daRd_cFP10fopAc_ac_c */
fopAc_ac_c* daRd_c::_searchNearDeadRd(fopAc_ac_c* i_actor) {
    if (fopAcM_GetName(i_actor) == PROC_RD) {
        daRd_c* other = static_cast<daRd_c*>(i_actor);
        if (other->mMode == MODE_DEATH) {
            if (fopAcM_searchActorDistanceXZ(this, i_actor) < l_HIO.m34) {
                return i_actor;
            }
        }
    }
    return FALSE;
}

/* 0000030C-00000358       .text nodeControl_CB__FP7J3DNodei */
static BOOL nodeControl_CB(J3DNode* node, int param_1) {
    if (!param_1) {
        J3DModel* model = j3dSys.getModel();
        daRd_c* i_this = reinterpret_cast<daRd_c*>(model->getUserArea());
        if (i_this) {
            i_this->_nodeControl(node, model);
        }
    }
    return TRUE;
}

/* 00000358-00000514       .text _nodeControl__6daRd_cFP7J3DNodeP8J3DModel */
BOOL daRd_c::_nodeControl(J3DNode* node, J3DModel* model) {
    J3DJoint* joint = static_cast<J3DJoint*>(node);
    int jntNo = joint->getJntNo();
    cMtx_copy(model->getAnmMtx(jntNo), mDoMtx_stack_c::get());
    
    if (mJntCtrl.getHeadJntNum() == jntNo) {
        static cXyz l_offsetAttPos(0.0f, 0.0f, 0.0f);
        static cXyz l_offsetEyePos(24.0f, -16.0f, 0.0f);
        mDoMtx_stack_c::multVec(&l_offsetAttPos, &mTargetPos);
        mDoMtx_stack_c::XrotM((int)mJntCtrl.getHead_y());
        mDoMtx_stack_c::ZrotM((int)mJntCtrl.getHead_x());
        mDoMtx_stack_c::multVec(&l_offsetEyePos, &mRdEyePos);
        mDoMtx_stack_c::XrotM(mD1A);
        mDoMtx_stack_c::ZrotM(mD1C);
        mDoMtx_stack_c::YrotM(mD1E);
    } else if (mJntCtrl.getBackboneJntNum() == jntNo) {
        mDoMtx_stack_c::XrotM((int)mJntCtrl.getBackbone_y());
        mDoMtx_stack_c::ZrotM((int)mJntCtrl.getBackbone_x());
    }
    
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
}

/* 00000550-0000059C       .text nodeHeadControl_CB__FP7J3DNodei */
static BOOL nodeHeadControl_CB(J3DNode* node, int param_1) {
    if (!param_1) {
        J3DModel* model = j3dSys.getModel();
        daRd_c* i_this = reinterpret_cast<daRd_c*>(model->getUserArea());
        if (i_this) {
            i_this->_nodeHeadControl(node, model);
        }
    }
    return TRUE;
}

/* 0000059C-000006A0       .text _nodeHeadControl__6daRd_cFP7J3DNodeP8J3DModel */
BOOL daRd_c::_nodeHeadControl(J3DNode* node, J3DModel* model) {
    J3DJoint* joint = static_cast<J3DJoint*>(node);
    int jntNo = joint->getJntNo();
    
    cXyz temp4(mD38, 0.0f, 0.0f);
    cMtx_copy(model->getAnmMtx(jntNo), mDoMtx_stack_c::get());
    mDoMtx_stack_c::transM(temp4);
    
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    cXyz temp3(0.0f, 0.0f, 50.0f);
    mDoMtx_stack_c::multVec(&temp3, &mRdEyePos);
    model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
    cMtx_copy(mDoMtx_stack_c::get(), mCE8);
    
    Mtx mtx;
    csXyz angle;
    mDoMtx_inverseTranspose(mDoMtx_stack_c::get(), mtx);
    mDoMtx_MtxToRot(mtx, &angle);
    mHeadAngle = angle.y;
}

/* 000006A0-000006C0       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c* i_this) {
    return static_cast<daRd_c*>(i_this)->_createHeap();
}

/* 000006C0-0000096C       .text _createHeap__6daRd_cFv */
BOOL daRd_c::_createHeap() {
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arc_name, RD_BDL_RD));
    JUT_ASSERT(504, modelData != 0);
    
    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL, NULL,
        static_cast<J3DAnmTransformKey*>(dComIfG_getObjectRes(m_arc_name, RD_BCK_SUWARIP)),
        J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, 1,
        NULL,
        0x00080000,
        0x37441622
    );
    if (mpMorf == NULL || mpMorf->getModel() == NULL) {
        return FALSE;
    }
    mpMorf->getModel()->setUserArea(reinterpret_cast<u32>(this));
    
    if (!mInvisModel.create(mpMorf->getModel())) {
        return FALSE;
    }
    
    J3DAnmTextureSRTKey* btk = static_cast<J3DAnmTextureSRTKey*>(dComIfG_getObjectRes(m_arc_name, RD_BTK_RD_CLOSE));
    JUT_ASSERT(525, btk != 0);
    if (!mBtkAnm.init(modelData, btk, true, 0, 1.0f, 0, -1, false, 0)) {
        return FALSE;
    }
    
    modelData->getJointNodePointer(0x0C)->setCallBack(nodeHeadControl_CB); // ree_atama_1
    
    J3DAnmTevRegKey* brk = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(m_arc_name, RD_BRK_NML));
    JUT_ASSERT(550, brk != 0);
    if (!mBrkAnm.init(modelData, brk, true, 0, 1.0f, 0, -1, false, 0)) {
        return FALSE;
    }
    
    return createArrowHeap() ? TRUE : FALSE;
}

/* 0000096C-000009D0       .text createArrowHeap__6daRd_cFv */
bool daRd_c::createArrowHeap() {
    static Vec sebone_cyl_offset[] = {{0.0f, 0.0f, 0.0f},    {30.0f, 0.0f, 0.0f}};
    static Vec muneA_cyl_offset[]  = {{5.0f, -5.0f, 0.0f},   {20.0f, -5.0f, 0.0f}};
    static Vec muneB1_cyl_offset[] = {{15.0f, 0.0f, -15.0f}, {50.0f, 0.0f, -15.0f}};
    static Vec muneB2_cyl_offset[] = {{15.0f, 0.0f, 0.0f},   {50.0f, 0.0f, 0.0f}};
    static Vec muneB3_cyl_offset[] = {{15.0f, 0.0f, 15.0f},  {50.0f, 0.0f, 15.0f}};
    static Vec kosi1_cyl_offset[]  = {{0.0f, 0.0f, -10.0f},  {20.0f, 0.0f, -10.0f}};
    static Vec kosi2_cyl_offset[]  = {{0.0f, 0.0f, 0.0f},    {20.0f, 0.0f, 0.0f}};
    static Vec kosi3_cyl_offset[]  = {{0.0f, 0.0f, 10.0f},   {20.0f, 0.0f, 10.0f}};
    static Vec asi1_cyl_offset[]   = {{-8.0f, 0.0f, 0.0f},   {30.0f, 0.0f, 0.0f}};
    static Vec asi2_cyl_offset[]   = {{-3.0f, 0.0f, 0.0f},   {15.0f, 0.0f, 0.0f}};
    static Vec asi3_cyl_offset[]   = {{0.0f, 0.0f, 0.0f},    {11.0f, 0.0f, 0.0f}};
    static Vec head_sph_offset[]   = {{30.0f, 0.0f, -5.0f}};
    static Vec ude1_cyl_offset[]   = {{-5.0f, -8.0f, -1.0f}, {60.0f, 4.0f, 1.0f}};
    static Vec ude2_cyl_offset[]   = {{-3.0f, 0.0f, 0.0f},   {55.0f, 0.0f, 0.0f}};
    static Vec te_cyl_offset[]     = {{8.0f, 2.0f, 0.0f},    {30.0f, 2.0f, 0.0f}};
    static Vec yubi_cyl_offset[]   = {{0.0f, 0.0f, 0.0f},    {17.0f, 0.0f, 0.0f}};
    static __jnt_hit_data_c search_data[] = {
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x01,
            /* mRadius     */ 4.0f,
            /* mpOffsets   */ kosi1_cyl_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x01,
            /* mRadius     */ 4.0f,
            /* mpOffsets   */ kosi2_cyl_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x01,
            /* mRadius     */ 4.0f,
            /* mpOffsets   */ kosi3_cyl_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x02,
            /* mRadius     */ 2.0f,
            /* mpOffsets   */ asi1_cyl_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x03,
            /* mRadius     */ 2.0f,
            /* mpOffsets   */ asi2_cyl_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x04,
            /* mRadius     */ 2.0f,
            /* mpOffsets   */ asi3_cyl_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x05,
            /* mRadius     */ 2.0f,
            /* mpOffsets   */ asi1_cyl_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x06,
            /* mRadius     */ 2.0f,
            /* mpOffsets   */ asi2_cyl_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x07,
            /* mRadius     */ 2.0f,
            /* mpOffsets   */ asi3_cyl_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x08,
            /* mRadius     */ 6.0f,
            /* mpOffsets   */ sebone_cyl_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x09,
            /* mRadius     */ 10.0f,
            /* mpOffsets   */ muneA_cyl_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x09,
            /* mRadius     */ 6.0f,
            /* mpOffsets   */ muneB1_cyl_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x09,
            /* mRadius     */ 6.0f,
            /* mpOffsets   */ muneB2_cyl_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x09,
            /* mRadius     */ 6.0f,
            /* mpOffsets   */ muneB3_cyl_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x0F,
            /* mRadius     */ 2.0f,
            /* mpOffsets   */ ude1_cyl_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x10,
            /* mRadius     */ 2.0f,
            /* mpOffsets   */ ude2_cyl_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x11,
            /* mRadius     */ 6.0f,
            /* mpOffsets   */ te_cyl_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x12,
            /* mRadius     */ 6.0f,
            /* mpOffsets   */ yubi_cyl_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x13,
            /* mRadius     */ 2.0f,
            /* mpOffsets   */ ude1_cyl_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x14,
            /* mRadius     */ 2.0f,
            /* mpOffsets   */ ude2_cyl_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x15,
            /* mRadius     */ 6.0f,
            /* mpOffsets   */ te_cyl_offset,
        },
        {
            /* mShapeType  */ 0, // Cylinder
            /* mJointIndex */ 0x16,
            /* mRadius     */ 6.0f,
            /* mpOffsets   */ yubi_cyl_offset,
        },
    };
    mpJntHit = JntHit_create(mpMorf->getModel(), search_data, ARRAY_SIZE(search_data));
    if (mpJntHit) {
        jntHit = mpJntHit;
    } else {
        return false;
    }
    return true;
}

/* 000009D0-00000A38       .text checkPlayerInAttack__6daRd_cFv */
bool daRd_c::checkPlayerInAttack() {
    return dLib_checkActorInFan(current.pos, dComIfGp_getLinkPlayer(), shape_angle.y, l_HIO.mAttackSpreadAngle, l_HIO.mAttackRadius, 100.0f);
}

/* 00000A38-00000AA0       .text checkPlayerInCry__6daRd_cFv */
bool daRd_c::checkPlayerInCry() {
    return dLib_checkActorInFan(current.pos, dComIfGp_getLinkPlayer(), mHeadAngle, l_HIO.mCrySpreadAngle, l_HIO.mCryRadius, 100.0f);
}

/* 00000AA0-00000D78       .text lookBack__6daRd_cFv */
void daRd_c::lookBack() {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getLinkPlayer();
    bool r29 = false;
    if (cLib_calcTimer(&mCE4) != 0 && mMode != MODE_ATTACK && mMode != MODE_CRY && mMode != MODE_DEATH) {
        mJntCtrl.clrTrn();
        mJntCtrl.offHeadLock();
        mJntCtrl.offBackBoneLock();
        mTargetPos = player->getHeadTopPos();
    } else {
        switch (mMode) {
        case MODE_WAIT:
        case MODE_DEATH:
        case MODE_ATTACK:
            r29 = false;
            mJntCtrl.clrTrn();
            mJntCtrl.onHeadLock();
            mJntCtrl.onBackBoneLock();
            break;
        case MODE_MOVE:
        case MODE_CRY:
        case MODE_RETURN:
        case MODE_SILENT_PRAY:
            mJntCtrl.setTrn();
            // Fall-through
        default:
            mJntCtrl.offHeadLock();
            mJntCtrl.offBackBoneLock();
            break;
        }
        
        switch (mAnmPrmIdx) {
        case AnmPrm_SUWARIP:
        case AnmPrm_TATSU:
        case AnmPrm_SUWARU:
            r29 = false;
            mJntCtrl.clrTrn();
            mJntCtrl.onHeadLock();
            mJntCtrl.onBackBoneLock();
            break;
        }
        
        switch (mMode) {
        case MODE_CRY:
            if (dLib_checkActorInFan(current.pos, player, shape_angle.y, l_HIO.mCrySpreadAngle, 150.0f, 100.0f)) {
                mJntCtrl.clrTrn();
                mJntCtrl.onHeadLock();
                mJntCtrl.onBackBoneLock();
            }
            mTargetPos = player->getHeadTopPos();
            break;
        case MODE_RETURN:
            if (dLib_checkActorInCircle(mSpawnPos, this, 100.0f, 1000.0f)) {
                mJntCtrl.clrTrn();
                mJntCtrl.onHeadLock();
                mJntCtrl.onBackBoneLock();
            }
            mTargetPos = mSpawnPos;
            break;
        case MODE_SILENT_PRAY:
            break;
        default:
            mTargetPos = player->getHeadTopPos();
            break;
        }
    }
    
    if (mJntCtrl.trnChk()) {
        cLib_addCalcAngleS2(&mMaxHeadTurnVel, l_HIO.mNpc.mMaxHeadTurnVel, 4, 0x800);
    } else {
        mMaxHeadTurnVel = 0;
    }
    
    mJntCtrl.lookAtTarget(&shape_angle.y, &mTargetPos, mRdEyePos, shape_angle.y, mMaxHeadTurnVel, r29);
}

/* 00000D78-00001650       .text checkTgHit__6daRd_cFv */
bool daRd_c::checkTgHit() {
    if (mMode == MODE_DEATH || mMode == MODE_KANOKE || mMode == MODE_SW_WAIT) {
        return false;
    }
    
    cCcD_Obj* hitObj;
    
    if (mCyl.ChkTgHit()) {
        hitObj = mCyl.GetTgHitObj();
        if (hitObj->GetAtType() == AT_TYPE_LIGHT) {
            fopAcM_seStart(this, JA_SE_CM_PW_BECOME_SOLID, 0);
            modeProcInit(MODE_PARALYSIS);
            return true;
        }
    }
    
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getLinkPlayer();
    mStts.Move();
    if (cLib_calcTimer(&m2C4) == 0 && mCyl.ChkTgHit()) {
        bool r29 = true;
        hitObj = mCyl.GetTgHitObj();
        m2C4 = l_HIO.m48;
        if (hitObj == NULL) {
            return false;
        }
        
        switch (hitObj->GetAtType()) {
        case AT_TYPE_SWORD:
        case AT_TYPE_MACHETE:
        case AT_TYPE_UNK800:
        case AT_TYPE_DARKNUT_SWORD:
        case AT_TYPE_MOBLIN_SPEAR:
            fopAcM_seStart(this, JA_SE_LK_SW_HIT_S, 0x20);
            
            switch (player->getCutType()) {
            case 0x05:
            case 0x06:
            case 0x07:
            case 0x08:
            case 0x09:
            case 0x0A:
            case 0x0C:
            case 0x0E:
            case 0x0F:
            case 0x10:
            case 0x15:
            case 0x19:
            case 0x1A:
            case 0x1B:
                mHitType = 1;
                break;
            default:
                mHitType = 0;
                break;
            }
            break;
        case AT_TYPE_WIND:
            r29 = false;
            mHitType = 3;
            mCE0 = 40;
            break;
        case AT_TYPE_BOOMERANG:
        case AT_TYPE_BOKO_STICK:
            r29 = false;
            fopAcM_seStart(this, JA_SE_LK_W_WEP_HIT, 0x44);
            mHitType = 4;
            mCE0 = 40;
            break;
        case AT_TYPE_HOOKSHOT:
            fopAcM_seStart(this, JA_SE_LK_HS_SPIKE, 0x44);
            r29 = false;
            mHitType = 12;
            break;
        case AT_TYPE_SKULL_HAMMER:
        case AT_TYPE_STALFOS_MACE:
            fopAcM_seStart(this, JA_SE_LK_HAMMER_HIT, 0x20);
            mHitType = 7;
            if (player->getCutType() == 0x11) {
                mHitType = 8;
            }
            break;
        case AT_TYPE_BOMB:
            mHitType = 6;
            break;
        case AT_TYPE_ICE_ARROW:
            r29 = false;
            fopAcM_seStart(this, JA_SE_LK_ARROW_HIT, 0x44);
            mEnemyIce.mFreezeDuration = l_HIO.m4A;
            enemy_fire_remove(&mEnemyFire);
            health += 4;
            mHitType = 9;
            break;
        case AT_TYPE_FIRE_ARROW:
            r29 = false;
            fopAcM_seStart(this, JA_SE_LK_ARROW_HIT, 0x44);
            mEnemyFire.mFireDuration = l_HIO.m4C;
            mHitType = 0xA;
            break;
        case AT_TYPE_LIGHT_ARROW:
            r29 = false;
            fopAcM_seStart(this, JA_SE_LK_ARROW_HIT, 0x20);
            mEnemyIce.mLightShrinkTimer = 1;
            mHitType = 0xB;
            break;
        case AT_TYPE_NORMAL_ARROW:
            mHitType = 5;
            if (!dLib_checkActorInCircle(current.pos, player, l_HIO.mCryRadius, 1000.0f)) {
                fopAcM_seStart(this, JA_SE_LK_ARROW_HIT, 0x44);
                mCE0 = 40;
                r29 = false;
            } else {
                fopAcM_seStart(this, JA_SE_LK_ARROW_HIT, 0x20);
            }
            break;
        case AT_TYPE_FIRE:
        case AT_TYPE_UNK20000:
            r29 = false;
            if (mEnemyFire.mState == 0) {
                mEnemyFire.mFireDuration = l_HIO.m4C;
            } else {
                mHitType = 0xD;
            }
            break;
        case AT_TYPE_GRAPPLING_HOOK:
            dComIfGp_particle_set(dPa_name::ID_COMMON_STARS_BLOW, &attention_info.position);
            fopAcM_seStart(this, JA_SE_LK_W_WEP_HIT, 0x44);
            mHitType = 0xE;
            r29 = false;
            mCE0 = 40;
            break;
        }
        
        CcAtInfo atInfo;
        atInfo.pParticlePos = NULL;
        atInfo.mpObj = mCyl.GetTgHitObj();
        if (r29) {
            cXyz* hitPos = mCyl.GetTgHitPosP();
            cc_at_check(this, &atInfo);
            if (mHitType == 1 || mHitType == 7 || mHitType == 8 || health <= 0) {
                dComIfGp_particle_set(0x10, mCyl.GetTgHitPosP());
                cXyz scale(2.0f, 2.0f, 2.0f);
                dComIfGp_particle_set(dPa_name::ID_COMMON_BIG_HIT, hitPos, &player->shape_angle, &scale);
                if (health <= 0) {
                    modeProcInit(MODE_DEATH);
                } else {
                    modeProcInit(MODE_DAMAGE);
                }
            } else {
                dComIfGp_particle_set(dPa_name::ID_COMMON_NORMAL_HIT, hitPos, &player->shape_angle);
                modeProcInit(MODE_DAMAGE);
            }
        } else if (mHitType == 0xE) {
            s8 origHealth = health;
            health = 0xA;
            cc_at_check(this, &atInfo);
            health = origHealth;
        }
        
        return true;
    }
    
    if (dComIfGp_getDetect().chk_light(&current.pos)) {
        fopAcM_seStart(this, JA_SE_CM_PW_BECOME_SOLID, 0);
        modeProcInit(MODE_PARALYSIS);
        return true;
    }
    
    return false;
}

/* 00001650-000017D0       .text setCollision__6daRd_cFv */
void daRd_c::setCollision() {
    if (mMode == MODE_DEATH) {
        mCyl.OffCoSPrmBit(CO_SPRM_VS_UNK2);
        mCyl.OffCoSPrmBit(CO_SPRM_IS_UNK2);
        mCyl.OffTgSPrmBit(TG_SPRM_SET);
        mCyl.OffTgSPrmBit(TG_SPRM_IS_OTHER);
    } else if (mMode == MODE_ATTACK || mMode == MODE_CRY || dComIfGp_evmng_startCheck("DEFAULT_RD_CRY")) {
        mCyl.OffCoSPrmBit(CO_SPRM_VS_UNK2);
        mCyl.OffCoSPrmBit(CO_SPRM_IS_UNK2);
    } else {
        mCyl.OnCoSPrmBit(CO_SPRM_VS_UNK2);
        mCyl.OnCoSPrmBit(CO_SPRM_IS_UNK2);
    }
    
    if (isAnm(AnmPrm_SUWARIP)) {
        mCyl.SetR(80.0f + g_regHIO.mChild[8].mFloatRegs[1]);
        mCyl.SetH(170.0f + g_regHIO.mChild[8].mFloatRegs[0]);
    } else {
        mCyl.SetR(80.0f + g_regHIO.mChild[8].mFloatRegs[1]);
        mCyl.SetH(250.0f + g_regHIO.mChild[8].mFloatRegs[0]);
    }
    
    mCyl.SetC(current.pos);
    dComIfG_Ccsp()->Set(&mCyl);
}

/* 000017D0-0000180C       .text setIceCollision__6daRd_cFv */
void daRd_c::setIceCollision() {
    if (isAnm(AnmPrm_SUWARIP)) {
        mEnemyIce.mWallRadius = 50.0f;
        mEnemyIce.mCylHeight = 170.0f;
    } else {
        mEnemyIce.mWallRadius = 50.0f;
        mEnemyIce.mCylHeight = 250.0f;
    }
}

/* 0000180C-00001970       .text setAttention__6daRd_cFv */
void daRd_c::setAttention() {
    cXyz attnPos(60.0f, 0.0f, 0.0f);
    cXyz eyeballPos(60.0f, 0.0f, 0.0f);
    mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(0x0C)); // ree_atama_1 joint
    mDoMtx_stack_c::multVec(&attnPos, &attention_info.position);
    mDoMtx_stack_c::multVecZero(&eyeballPos);
    eyePos = eyeballPos;
    attention_info.position.y += l_HIO.m58;
    eyePos.y += l_HIO.m5C;
    
    if (dComIfGp_event_runCheck()) {
        attention_info.position = current.pos;
        eyePos = current.pos;
        attention_info.position.y += 150.0f;
        eyePos.y += 150.0f;
    }
    
    if (mEnemyIce.mFreezeTimer > 20) {
        fopAcM_OffStatus(this, fopAcStts_UNK200000_e);
    } else {
        fopAcM_OnStatus(this, fopAcStts_UNK200000_e);
    }
}

/* 00001970-000019F8       .text setMtx__6daRd_cFv */
void daRd_c::setMtx() {
    J3DModel* model = mpMorf->getModel();
    model->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    model->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 000019F8-00001A3C       .text modeWaitInit__6daRd_cFv */
void daRd_c::modeWaitInit() {
    mAcchCir.SetWallR(60.0f);
    speedF = 0.0f;
}

/* 00001A3C-00001DDC       .text modeWait__6daRd_cFv */
void daRd_c::modeWait() {
    if (checkTgHit()) {
        return;
    }
    
    speedF = 0.0f;
    fopAc_ac_c* player = dComIfGp_getLinkPlayer();
    BOOL isOto = fopAcM_otoCheck(this, mAreaRadius);
    if (!isLinkControl()) {
        if (dLib_checkActorInCircle(mSpawnPos, this, mAreaRadius, 1000.0f)) {
            // The ReDead will only wake up if the player is in a 200-unit-tall cylinder around its spawn point.
            // Bug: If the ReDead spawned high up in the air, its spawn point will remain there even after the ReDead
            // itself has fallen down to ground level. This means it will not be able to notice the player properly.
            if (dLib_checkActorInCircle(mSpawnPos, player, mAreaRadius, 100.0f)) {
                if ((dLib_checkActorInCircle(mSpawnPos, player, mAreaRadius, 100.0f) && player->speedF > 10.0f + g_regHIO.mChild[12].mFloatRegs[4]) ||
                    isOto ||
                    dLib_checkActorInFan(current.pos, player, shape_angle.y, l_HIO.m40, l_HIO.m34, 100.0f)
                ) {
                    modeProcInit(MODE_MOVE);
                    return;
                }
            }
        }
    }
    
    if (dLib_checkActorInCircle(mSpawnPos, this, 100.0f, 1000.0f)) {
        cLib_addCalcAngleS2(&shape_angle.y, mSpawnAngle, 0x4, 0x200);
        if (cLib_distanceAngleS(shape_angle.y, mSpawnAngle) <= 0x200) {
            shape_angle.y = mSpawnAngle;
            if (mWhichIdleAnm == 1 && !isAnm(AnmPrm_SUWARIP)) {
                setAnm(AnmPrm_SUWARU, false);
            }
            if (mWhichIdleAnm == 0) {
                setAnm(AnmPrm_TACHIP1, false);
            }
        }
    } else if (!dLib_checkActorInCircle(mSpawnPos, this, mAreaRadius, 1000.0f) ||
               !dLib_checkActorInCircle(mSpawnPos, player, mAreaRadius, 100.0f)
    ) {
        modeProcInit(MODE_RETURN);
        return;
    }
    if (!isLinkControl() && checkPlayerInAttack() && isAnm(AnmPrm_TACHIP1)) {
        modeProcInit(MODE_ATTACK);
    }
}

/* 00001DDC-00001E68       .text modeDeathInit__6daRd_cFv */
void daRd_c::modeDeathInit() {
    fopAcM_monsSeStart(this, JA_SE_CV_RD_DIE, 0);
    setAnm(AnmPrm_DEAD, false);
    speedF = 0.0f;
    mTimer1 = 10*30;
}

/* 00001E68-00001F14       .text modeDeath__6daRd_cFv */
void daRd_c::modeDeath() {
    if (!mpMorf->isStop()) {
        return;
    }
    
    fopAcM_onActor(this);
    
    // Do not consider the ReDead to be a living enemy while its death animation is playing out.
    fopAcM_SetGroup(this, fopAc_ENV_e);
    
    if (cLib_calcTimer(&mTimer1) == 0) {
        fopAcM_createDisappear(this, &current.pos, 5);
        fopAcM_delete(this);
    }
}

/* 00001F14-00001F98       .text modeDamageInit__6daRd_cFv */
void daRd_c::modeDamageInit() {
    fopAcM_monsSeStart(this, JA_SE_CV_RD_DAMAGE, 0);
    setAnm(AnmPrm_DAMAGE, true);
    speedF = 0.0f;
}

/* 00001F98-00002084       .text modeDamage__6daRd_cFv */
void daRd_c::modeDamage() {
    if (checkTgHit()) {
        return;
    }
    fopAc_ac_c* player = dComIfGp_getLinkPlayer();
    if (!mpMorf->isStop()) {
        return;
    }
    
    if (dLib_checkActorInCircle(mSpawnPos, player, mAreaRadius, 100.0f)) {
        modeProcInit(MODE_MOVE);
    } else {
        modeProcInit(MODE_WAIT);
    }
}

/* 00002084-000020EC       .text modeParalysisInit__6daRd_cFv */
void daRd_c::modeParalysisInit() {
    if (!isAnm(AnmPrm_BEAM_HIT) && !isAnm(AnmPrm_BEAM)) {
        setAnm(AnmPrm_BEAM_HIT, false);
    }
    mTimer1 = l_HIO.mParalysisDuration;
    speedF = 0.0f;
}

/* 000020EC-000021F0       .text modeParalysis__6daRd_cFv */
void daRd_c::modeParalysis() {
    if (isAnm(AnmPrm_BEAM_HIT) && mpMorf->isStop()) {
        setAnm(AnmPrm_BEAM, false);
    } else if (isAnm(AnmPrm_BEAM)) {
        if (cLib_calcTimer(&mTimer1) == 0) {
            setAnm(AnmPrm_BEAM_END, false);
        }
    } else if (isAnm(AnmPrm_BEAM_END) && mpMorf->isStop()) {
        modeProcInit(MODE_WAIT);
    }
    
    if (checkTgHit()) {
        // This line setting speedF to itself gets optimized out and produces no code, but affects codegen.
        // It's not known what the original code that got optimized out here was, it could be speedF or something else.
        speedF = speedF;
    }
}

/* 000021F0-0000223C       .text modeMoveInit__6daRd_cFv */
void daRd_c::modeMoveInit() {
    if (mWhichIdleAnm == 1 && (isAnm(AnmPrm_SUWARIP) || isAnm(AnmPrm_SUWARU))) {
        setAnm(AnmPrm_TATSU, false);
    }
}

/* 0000223C-000024B0       .text modeMove__6daRd_cFv */
void daRd_c::modeMove() {
    if (!checkTgHit() && !isAnm(AnmPrm_TATSU)) {
        if (!isLinkControl() && checkPlayerInCry()) {
            modeProcInit(MODE_CRY);
            return;
        }
        daPy_py_c* player = (daPy_py_c*)dComIfGp_getLinkPlayer();
        if (!dLib_checkActorInCircle(mSpawnPos, this, mAreaRadius, 1000.0f) || !dLib_checkActorInCircle(mSpawnPos, player, mAreaRadius, 100.0f)) {
            modeProcInit(MODE_RETURN);
            return;
        }
        int angle = cLib_distanceAngleS(fopAcM_searchPlayerAngleY(this), mHeadAngle);
        if (angle < 0x50) {
            f32 dist = fopAcM_searchPlayerDistanceXZ(this);
            f32 temp = (dist / 100.0f) + g_regHIO.mChild[12].mFloatRegs[3];
            if (temp > 1.0f) {
                temp = 1.0f;
            }
            if (temp < 0.1f) {
                temp = 0.1f;
            }
            f32 temp2 = l_HIO.m68;
            if (mEnemyFire.mState != 0) {
                temp2 *= 2.0f;
            }
            cLib_addCalc2(&speedF, temp2*temp, 0.1f, 0.1f + g_regHIO.mChild[12].mFloatRegs[0]);
        } else {
            cLib_addCalc2(&speedF, 0.0f, 0.1f, 0.1f + g_regHIO.mChild[12].mFloatRegs[0]);
        }
        if (speedF < 0.1f) {
            setAnm(AnmPrm_TACHIP1, false);
        } else {
            setAnm(AnmPrm_WALK, false);
        }
        if (!isLinkControl() && checkPlayerInAttack()) {
            modeProcInit(MODE_ATTACK);
        }
    }
}

/* 000024B0-000025A8       .text modeCryInit__6daRd_cFv */
void daRd_c::modeCryInit() {
    if (isLinkControl()) {
        modeProcInit(MODE_RETURN);
        return;
    }
    if (dComIfGp_evmng_startCheck("DEFAULT_RD_CRY")) {
        dComIfGp_event_reset();
    }
    fopAcM_orderOtherEvent(this, "DEFAULT_RD_CRY");
    fopAcM_monsSeStart(this, JA_SE_CV_RD_SCREAM, 0);
    mTimer1 = l_HIO.m54;
    mBreakFreeCounter = l_HIO.m78;
}

/* 000025A8-000028B8       .text modeCry__6daRd_cFv */
void daRd_c::modeCry() {
    setAnm(AnmPrm_WALK, false);
    
    f32 stickPosX = g_mDoCPd_cpadInfo[0].mMainStickPosX;
    f32 stickPosY = g_mDoCPd_cpadInfo[0].mMainStickPosY;
    if (eventInfo.checkCommandDemoAccrpt() || dComIfGp_evmng_startCheck("DEFAULT_RD_CRY")) {
        if (isLinkControl()) {
            dComIfGp_event_reset();
            modeProcInit(MODE_RETURN);
        } else if (checkTgHit()) {
            dComIfGp_event_reset();
        } else {
            s16 targetY = fopAcM_searchPlayerAngleY(this);
            f32 dist = fopAcM_searchPlayerDistanceXZ(this);
            f32 temp = (dist / 100.0f) + g_regHIO.mChild[12].mFloatRegs[3];
            if (temp > 1.0f) {
                temp = 1.0f;
            }
            if (temp < 0.1f) {
                temp = 0.1f;
            }
            f32 temp2 = l_HIO.m68;
            if (mEnemyFire.mState != 0) {
                temp2 *= 2.0f;
            }
            cLib_addCalc2(&speedF, temp2*temp, 0.1f, 0.1f + g_regHIO.mChild[12].mFloatRegs[0]);
            
            if (mD3C > 0 && stickPosX < 0.0f) {
                mD3C = -1;
                mBreakFreeCounter--;
            } else if (mD3C < 0 && stickPosX > 0.0f) {
                mD3C = 1;
                mBreakFreeCounter--;
            }
            
            if (mD40 > 0 && stickPosY < 0.0f) {
                mD40 = -1;
                mBreakFreeCounter--;
            } else if (mD40 < 0 && stickPosY > 0.0f) {
                mD40 = 1;
                mBreakFreeCounter--;
            }
            
            if (CPad_CHECK_TRIG_A(0) || CPad_CHECK_TRIG_B(0) || CPad_CHECK_TRIG_X(0) || CPad_CHECK_TRIG_Y(0)) {
                mBreakFreeCounter--;
            }
            
            if (cLib_calcTimer(&mTimer1) == 0 || mBreakFreeCounter < 0) {
                dComIfGp_event_reset();
                modeProcInit(MODE_CRY_WAIT);
            } else if (checkPlayerInAttack()) {
                dComIfGp_event_reset();
                modeProcInit(MODE_ATTACK);
            }
        }
    } else {
        modeProcInit(MODE_CRY_WAIT);
    }
}

/* 000028B8-000028CC       .text modeCryWaitInit__6daRd_cFv */
void daRd_c::modeCryWaitInit() {
    mTimer1 = 60;
    mTimer2 = 45;
}

/* 000028CC-000029E4       .text modeCryWait__6daRd_cFv */
void daRd_c::modeCryWait() {
    if (checkTgHit()) {
        return;
    }
    if (isLinkControl()) {
        modeProcInit(MODE_RETURN);
        return;
    }
    if (dComIfGp_evmng_startCheck("DEFAULT_RD_CRY")) {
        onIkari();
        setBtkAnm(3);
    }
    if (dComIfGp_event_runCheck()) {
        mTimer1 = 60;
        mTimer2 = 45;
    } else if (isAnm(AnmPrm_WALK)) {
        if (cLib_calcTimer(&mTimer1) == 0) {
            modeProcInit(MODE_MOVE);
        } else if (cLib_calcTimer(&mTimer2) == 0 && checkPlayerInAttack()) {
            modeProcInit(MODE_ATTACK);
        }
    }
}

/* 000029E4-00002A58       .text modeAttackInit__6daRd_cFv */
void daRd_c::modeAttackInit() {
    mAcchCir.SetWallR(70.0f);
    mTimer1 = l_HIO.m52;
    mBreakFreeCounter = l_HIO.m50;
    mTimer2 = 30;
    setAnm(AnmPrm_WALK, false);
    speedF = 0.0f;
}

/* 00002A58-00002F30       .text modeAttack__6daRd_cFv */
void daRd_c::modeAttack() {
    if (dComIfGp_evmng_startCheck("DEFAULT_RD_CRY")) {
        dComIfGp_event_reset();
    }
    if ((dComIfGp_evmng_startCheck("DEFAULT_RD_CRY") || dComIfGp_evmng_startCheck("DEFAULT_RD_ATTACK")) && isLinkControl()) {
        dComIfGp_event_reset();
        modeProcInit(MODE_RETURN);
        return;
    }
    
    f32 stickPosX = g_mDoCPd_cpadInfo[0].mMainStickPosX;
    f32 stickPosY = g_mDoCPd_cpadInfo[0].mMainStickPosY;
    if (eventInfo.checkCommandDemoAccrpt()) {
        daPy_py_c* player = (daPy_py_c*)dComIfGp_getLinkPlayer();
        if (isAnm(AnmPrm_ATACK)) {
            f32 frame = player->getBaseAnimeFrame();
            mpMorf->setFrame(frame);
            cLib_addCalcAngleS2(&shape_angle.y, player->shape_angle.y, 0x4, 0x2000);
        } else {
            s16 targetY = fopAcM_searchPlayerAngleY(this);
            cLib_addCalcAngleS2(&shape_angle.y, targetY, 0x4, 0x2000);
        }
        
        if (checkTgHit()) {
            dComIfGp_event_reset();
            return;
        }
        f32 dist = fopAcM_searchPlayerDistanceXZ(this);
        if (dist <= 50.0f + g_regHIO.mChild[12].mFloatRegs[5] && !isAnm(AnmPrm_ATACK)) {
            offIkari();
            setAnm(AnmPrm_WALK2ATACK, false);
        }
        if (dist <= 20.0f + g_regHIO.mChild[12].mFloatRegs[2]) {
            cLib_addCalcPosXZ2(&current.pos, player->current.pos, 0.3f, 1.0f);
            if (cLib_calcTimer(&mTimer2) == 0) {
                if (!daPy_getPlayerLinkActorClass()->checkNoDamageMode()) {
                    daPy_getPlayerLinkActorClass()->setDamagePoint(-1.0f);
                }
                mTimer2 = 30;
            }
        } else if (mAcch.ChkWallHit()) {
            player->changeOriginalDemo();
            cXyz pos = player->current.pos;
            cLib_addCalcPosXZ2(&pos, current.pos, 0.3f, 10.0f);
            player->setPlayerPosAndAngle(&pos, player->shape_angle.y);
        } else {
            cLib_addCalcPosXZ2(&current.pos, player->current.pos, 0.3f, 10.0f);
        }
        
        if (dComIfGs_getLife() == 0) {
            dComIfGp_event_reset();
            setAnm(AnmPrm_ATACK2WALK, false);
            modeProcInit(MODE_WAIT);
            return;
        }
        
        if (mD3C > 0 && stickPosX < 0.0f) {
            mD3C = -1;
            mBreakFreeCounter--;
        } else if (mD3C < 0 && stickPosX > 0.0f) {
            mD3C = 1;
            mBreakFreeCounter--;
        }
        
        if (mD40 > 0 && stickPosY < 0.0f) {
            mD40 = -1;
            mBreakFreeCounter--;
        } else if (mD40 < 0 && stickPosY > 0.0f) {
            mD40 = 1;
            mBreakFreeCounter--;
        }
        
        if (CPad_CHECK_TRIG_A(0) || CPad_CHECK_TRIG_B(0) || CPad_CHECK_TRIG_X(0) || CPad_CHECK_TRIG_Y(0)) {
            mBreakFreeCounter--;
        }
        
        if (cLib_calcTimer(&mTimer1) == 0 || mBreakFreeCounter < 0) {
            dComIfGp_event_reset();
            setAnm(AnmPrm_ATACK2WALK, false);
            modeProcInit(MODE_CRY_WAIT);
        }
    } else if (!checkTgHit()) {
        fopAcM_orderOtherEvent(this, "DEFAULT_RD_ATTACK", 0x1CF);
    }
}

/* 00002F30-00002F34       .text modeReturnInit__6daRd_cFv */
void daRd_c::modeReturnInit() {
}

/* 00002F34-00003208       .text modeReturn__6daRd_cFv */
void daRd_c::modeReturn() {
    if (checkTgHit()) {
        return;
    }
    
    setAnm(AnmPrm_WALK, false);
    
    if (dLib_checkActorInCircle(mSpawnPos, this, 100.0f, 1000.0f)) {
        speedF = 0.0f;
        cLib_addCalcAngleS2(&shape_angle.y, mSpawnAngle, 0xA, 0x200);
        if (cLib_distanceAngleS(shape_angle.y, mSpawnAngle) <= 0x200) {
            shape_angle.y = mSpawnAngle;
            modeProcInit(MODE_WAIT);
            return;
        }
    } else {
        cLib_addCalc2(&speedF, l_HIO.mReturnWalkSpeed, 0.1f, 0.1f + g_regHIO.mChild[12].mFloatRegs[0]);
    }
    
    if (dComIfGp_evmng_startCheck("DEFAULT_RD_ATTACK")) {
        return;
    }
    
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getLinkPlayer();
    BOOL isOto = fopAcM_otoCheck(this, mAreaRadius);
    if (!isLinkControl()) {
        if (dLib_checkActorInCircle(mSpawnPos, this, mAreaRadius, 1000.0f)) {
            if (dLib_checkActorInCircle(mSpawnPos, player, mAreaRadius, 100.0f)) {
                if ((dLib_checkActorInCircle(mSpawnPos, player, mAreaRadius, 100.0f) && player->speedF > 10.0f + g_regHIO.mChild[12].mFloatRegs[4]) ||
                    isOto ||
                    dLib_checkActorInFan(current.pos, player, shape_angle.y, l_HIO.m40, l_HIO.m34, 100.0f)
                ) {
                    modeProcInit(MODE_MOVE);
                    return;
                }
            }
        }
    }
}

/* 00003208-0000320C       .text modeSilentPrayInit__6daRd_cFv */
void daRd_c::modeSilentPrayInit() {
}

/* 0000320C-00003400       .text modeSilentPray__6daRd_cFv */
void daRd_c::modeSilentPray() {
    if (checkTgHit()) {
        return;
    }
    
    setAnm(AnmPrm_WALK, false);
    
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getLinkPlayer();
    fopAc_ac_c* corpse;
    if (fopAcM_SearchByID(mCorpseID, &corpse)) {
        mTargetPos = corpse->current.pos;
        if (dLib_checkActorInCircle(mTargetPos, this, 200.0f, 1000.0f)) {
            setAnm(AnmPrm_TACHIP1, false);
            speedF = 0.0f;
        } else {
            cLib_addCalc2(&speedF, l_HIO.mReturnWalkSpeed, 0.1f, 0.1f + g_regHIO.mChild[12].mFloatRegs[0]);
        }
    } else if (!isLinkControl()) {
        if (dLib_checkActorInCircle(mSpawnPos, player, mAreaRadius, 100.0f)) {
            modeProcInit(MODE_MOVE);
        } else {
            modeProcInit(MODE_WAIT);
        }
    } else {
        modeProcInit(MODE_RETURN);
    }
    
    if (!isLinkControl()) {
        if (checkPlayerInCry()) {
            modeProcInit(MODE_CRY);
        }
        if (checkPlayerInAttack()) {
            modeProcInit(MODE_ATTACK);
        }
    }
}

/* 00003400-00003428       .text modeSwWaitInit__6daRd_cFv */
void daRd_c::modeSwWaitInit() {
    setAnm(AnmPrm_KANOKEP, false);
}

/* 00003428-00003480       .text modeSwWait__6daRd_cFv */
void daRd_c::modeSwWait() {
    if (dComIfGs_isSwitch(mSwNo, current.roomNo)) {
        modeProcInit(MODE_KANOKE);
    }
}

/* 00003480-00003514       .text modeKanokeInit__6daRd_cFv */
void daRd_c::modeKanokeInit() {
    setAnm(AnmPrm_KANOKEP, false);
    mTimer1 = 90;
    cXyz offset(0.0f, 0.0f, 150.0f);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    mDoMtx_stack_c::multVec(&offset, &mSpawnPos);
}

/* 00003514-0000355C       .text modeKanoke__6daRd_cFv */
void daRd_c::modeKanoke() {
    if (cLib_calcTimer(&mTimer1) == 0) {
        modeProcInit(MODE_RETURN);
    }
}

/* 0000355C-000038D4       .text modeProc__6daRd_cFQ26daRd_c6Proc_ei */
void daRd_c::modeProc(daRd_c::Proc_e proc, int newMode) {
    struct ModeEntry {
        ModeFunc init;
        ModeFunc run;
        const char* name;
    };

    static ModeEntry mode_tbl[] = {
        {
            &modeWaitInit,
            &modeWait,
            "WAIT",
        },
        {
            &modeDamageInit,
            &modeDamage,
            "DAMAGE",
        },
        {
            &modeParalysisInit,
            &modeParalysis,
            "PARALYSIS",
        },
        {
            &modeDeathInit,
            &modeDeath,
            "DEATH",
        },
        {
            &modeMoveInit,
            &modeMove,
            "MOVE",
        },
        {
            &modeCryInit,
            &modeCry,
            "CRY",
        },
        {
            &modeCryWaitInit,
            &modeCryWait,
            "CRY_WAIT",
        },
        {
            &modeAttackInit,
            &modeAttack,
            "ATTACK",
        },
        {
            &modeReturnInit,
            &modeReturn,
            "RETURN",
        },
        {
            &modeSilentPrayInit,
            &modeSilentPray,
            "SILENT_PRAY",
        },
        {
            &modeSwWaitInit,
            &modeSwWait,
            "SW_WAIT",
        },
        {
            &modeKanokeInit,
            &modeKanoke,
            "KANOKE",
        },
    };
    
    if (proc == PROC_INIT) {
        if (newMode == MODE_CRY || newMode == MODE_ATTACK) {
            onIkari();
            setBtkAnm(3);
        } else if (newMode != MODE_DAMAGE) {
            offIkari();
            setBtkAnm(4);
        }
        
        if (newMode == MODE_DEATH || newMode == MODE_SW_WAIT) {
            fopAcM_OffStatus(this, fopAcStts_SHOWMAP_e);
            cLib_offBit<u32>(attention_info.flags, fopAc_Attn_LOCKON_BATTLE_e);
        } else {
            fopAcM_OnStatus(this, fopAcStts_SHOWMAP_e);
            cLib_onBit<u32>(attention_info.flags, fopAc_Attn_LOCKON_BATTLE_e);
        }
        
        mMode = newMode;
        (this->*mode_tbl[mMode].init)();
    } else if (proc == PROC_EXEC) {
        (this->*mode_tbl[mMode].run)();
    }
}

/* 000038D4-000039AC       .text setBrkAnm__6daRd_cFSc */
void daRd_c::setBrkAnm(s8 idx) {
    static const int a_anm_idx_tbl[] = {
        RD_BRK_NML,
        RD_BRK_BEAM_HIT,
        RD_BRK_BEAM,
        RD_BRK_BEAM_END,
    };
    static const int a_play_mod_tbl[] = {
        0, 0, 2, 0,
    };
    
    J3DModel* model = mpMorf->getModel();
    J3DAnmTevRegKey* brk = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(m_arc_name, a_anm_idx_tbl[idx]));
    JUT_ASSERT(1890, brk != 0);
    mBrkAnm.init(model->getModelData(), brk, true, a_play_mod_tbl[idx], 1.0f, 0, -1, true, 0);
}

/* 000039AC-00003B3C       .text setBtkAnm__6daRd_cFSc */
void daRd_c::setBtkAnm(s8 idx) {
    static const int a_anm_idx_tbl[] = {
        RD_BTK_RD_IKARI,
        RD_BTK_RD_NML,
        RD_BTK_RD_OPEN,
        RD_BTK_RD_CLOSE,
    };
    struct play_prm_struct {
        s8 m00;
        s8 m01;
        s32 m04;
    };
    static const play_prm_struct a_play_prm_tbl[] = {
        {0x01,   -1, 0x00},
        {0x00,   -1, 0x02},
        {0x01,   -1, 0x02},
        {0x02, 0x01, 0x00},
        {0x03, 0x02, 0x00},
    };
    
    if (idx != 5) {
        m6DB = idx;
    }
    
    int r5 = a_play_prm_tbl[m6DB].m00;
    if (m6DC != m6DB && r5 != -1) {
        J3DAnmTextureSRTKey* btk = static_cast<J3DAnmTextureSRTKey*>(dComIfG_getObjectRes(m_arc_name, a_anm_idx_tbl[r5]));
        JUT_ASSERT(1930, btk != 0);
        J3DModelData* modelData = mpMorf->getModel()->getModelData();
        mBtkAnm.init(modelData, btk, true, a_play_prm_tbl[m6DB].m04, 1.0f, 0, -1, true, 0);
        
        if (mBtkAnm.isStop()) {
            if (a_play_prm_tbl[m6DB].m01 != -1 && a_play_prm_tbl[m6DB].m04 == 0) {
                m6DB = a_play_prm_tbl[m6DB].m01;
            }
        }
    }
    
    m6DC = m6DB;
}

/* 00003B3C-00003C48       .text setAnm__6daRd_cFScb */
void daRd_c::setAnm(s8 anmIdx, bool param_2) {
    static const int a_anm_bcks_tbl[] = {
        RD_BCK_TACHIP,
        RD_BCK_SUWARIP,
        RD_BCK_WALK2ATACK,
        RD_BCK_ATACK,
        RD_BCK_ATACK2WALK,
        RD_BCK_WALK,
        RD_BCK_DAMAGE,
        RD_BCK_DEAD,
        RD_BCK_TATSU,
        RD_BCK_SUWARU,
        RD_BCK_KANOKEP,
        RD_BCK_BEAM_HIT,
        RD_BCK_BEAM,
        RD_BCK_BEAM_END,
    };
    static const dLib_anm_prm_c a_anm_prm_tbl[] = {
        {
            // AnmPrm_TACHIP0
            /* mBckIdx     */ BckIdx_TACHIP,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::LOOP_REPEAT_e
        },
        {
            // AnmPrm_TACHIP1
            /* mBckIdx     */ BckIdx_TACHIP,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::LOOP_REPEAT_e
        },
        {
            // AnmPrm_SUWARIP
            /* mBckIdx     */ BckIdx_SUWARIP,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::LOOP_REPEAT_e
        },
        {
            // AnmPrm_WALK2ATACK
            /* mBckIdx     */ BckIdx_WALK2ATACK,
            /* mNextPrmIdx */ AnmPrm_ATACK,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::LOOP_ONCE_e
        },
        {
            // AnmPrm_ATACK
            /* mBckIdx     */ BckIdx_ATACK,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::LOOP_REPEAT_e
        },
        {
            // AnmPrm_ATACK2WALK
            /* mBckIdx     */ BckIdx_ATACK2WALK,
            /* mNextPrmIdx */ AnmPrm_WALK,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::LOOP_ONCE_e
        },
        {
            // AnmPrm_WALK
            /* mBckIdx     */ BckIdx_WALK,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::LOOP_REPEAT_e
        },
        {
            // AnmPrm_DAMAGE
            /* mBckIdx     */ BckIdx_DAMAGE,
            /* mNextPrmIdx */ AnmPrm_TACHIP1,
            /* field_0x02  */ 0,
            /* mMorf       */ 2.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::LOOP_ONCE_e
        },
        {
            // AnmPrm_DEAD
            /* mBckIdx     */ BckIdx_DEAD,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 2.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::LOOP_ONCE_e
        },
        {
            // AnmPrm_TATSU
            /* mBckIdx     */ BckIdx_TATSU,
            /* mNextPrmIdx */ AnmPrm_TACHIP1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 0.5f,
            /* mLoopMode   */ J3DFrameCtrl::LOOP_ONCE_e
        },
        {
            // AnmPrm_SUWARU
            /* mBckIdx     */ BckIdx_SUWARU,
            /* mNextPrmIdx */ AnmPrm_SUWARIP,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 0.5f,
            /* mLoopMode   */ J3DFrameCtrl::LOOP_ONCE_e
        },
        {
            // AnmPrm_KANOKEP
            /* mBckIdx     */ BckIdx_KANOKEP,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::LOOP_REPEAT_e
        },
        {
            // AnmPrm_BEAM_HIT
            /* mBckIdx     */ BckIdx_BEAM_HIT,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 2.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::LOOP_ONCE_e
        },
        {
            // AnmPrm_BEAM
            /* mBckIdx     */ BckIdx_BEAM,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 2.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::LOOP_REPEAT_e
        },
        {
            // AnmPrm_BEAM_END
            /* mBckIdx     */ BckIdx_BEAM_END,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 2.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::LOOP_ONCE_e
        },
    };
    
    if (anmIdx != AnmPrm_NULL) {
        mAnmPrmIdx = anmIdx;
    }
    
    if (m6DA != mAnmPrmIdx) {
        if (isAnm(AnmPrm_BEAM_HIT)) {
            setBrkAnm(0x1);
        } else if (isAnm(AnmPrm_BEAM)) {
            setBrkAnm(0x2);
        } else if (isAnm(AnmPrm_BEAM_END)) {
            setBrkAnm(0x3);
        } else {
            setBrkAnm(0x0);
        }
    }
    
    if (mBckIdx == RD_BCK_DAMAGE || mBckIdx == RD_BCK_DEAD || mBckIdx == RD_BCK_IKARI_SAMPLE) {
        mBrkAnm.setFrame(mpMorf->getFrame());
    }
    
    dLib_bcks_setAnm(m_arc_name, mpMorf, &mBckIdx, &mAnmPrmIdx, &m6DA, a_anm_bcks_tbl, a_anm_prm_tbl, param_2);
}

/* 00003C48-000040A8       .text _execute__6daRd_cFv */
bool daRd_c::_execute() {
    if (mMode == MODE_SW_WAIT) {
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
        mAcch.CrrPos(*dComIfG_Bgsp());
        setMtx();
        mpMorf->play(NULL, 0, 0);
        mpMorf->calc();
        modeProc(PROC_EXEC, MODE_NULL);
        return true;
    }
    
    fopAcM_setGbaName(this, MIRROR_SHIELD, 0x12, 0x30);
    setIceCollision();
    if (mMode != MODE_SILENT_PRAY && mMode != MODE_DEATH && mMode != MODE_DAMAGE &&
        mMode != MODE_ATTACK && mMode != MODE_CRY && mMode != MODE_CRY_WAIT)
    {
        daRd_c* corpse = (daRd_c*)fopAcIt_Judge(&searchNeadDeadRd_CB, this);
        if (corpse != NULL) {
            mCorpseID = fopAcM_GetID(corpse);
            modeProcInit(MODE_SILENT_PRAY);
        }
    }
    if (mMode != MODE_ATTACK && mMode != MODE_WAIT && mMode != MODE_DEATH && mMode != MODE_RETURN) {
        if (dComIfGp_evmng_startCheck("DEFAULT_RD_ATTACK")) {
            modeProcInit(MODE_RETURN);
        }
    }
    current.angle = shape_angle;
    
    if (mEnemyFire.mState == 0) { // Not on fire (TODO enum)
        mCyl.SetAtType(0);
        m6D4 = l_HIO.m4E;
    } else {
        mCyl.SetAtType(AT_TYPE_FIRE);
        if (mMode != MODE_DEATH && mMode != MODE_CRY && mMode != MODE_ATTACK) {
            if (cLib_calcTimer(&m6D4) == 0) {
                modeProcInit(MODE_DEATH);
            }
        }
    }
    
    if (enemy_ice(&mEnemyIce)) {
        mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
        mpMorf->calc();
        speedF = 0.0f;
        setAttention();
        return true;
    }
    
    if (mCE0 == 1) {
        mCE4 = 4*30;
    }
    
    if (cLib_calcTimer(&mCE0) == 0) {
        cLib_addCalcAngleS2(&mD1E, 0, 0xC, 0x100);
        cLib_addCalcAngleS2(&mD2E, 0, 0xC, 0x100);
    } else {
        cLib_addCalcAngleS2(&mD1E, 0x2000, 0x4, 0x800);
        cLib_addCalcAngleS2(&mD2E, 0x500, 0x4, 0x200);
    }
    
    mJntCtrl.setParam(
        l_HIO.mNpc.mMaxBackboneX, l_HIO.mNpc.mMaxBackboneY, l_HIO.mNpc.mMinBackboneX, l_HIO.mNpc.mMinBackboneY,
        l_HIO.mNpc.mMaxHeadX, l_HIO.mNpc.mMaxHeadY, l_HIO.mNpc.mMinHeadX, l_HIO.mNpc.mMinHeadY,
        l_HIO.mNpc.mMaxTurnStep
    );
    
    if (mMode != MODE_PARALYSIS) {
        lookBack();
    }
    
    if (mbIkari) {
        cLib_addCalc2(&mD38, l_HIO.m60, 0.1f, l_HIO.m64);
    } else {
        cLib_addCalc2(&mD38, 0.0f, 0.1f, l_HIO.m64);
    }
    
    if (isAnm(AnmPrm_WALK)) {
        f32 temp = speedF * l_HIO.m70;
        mpMorf->setPlaySpeed(temp < l_HIO.m74 ? l_HIO.m74 : temp);
        if (mMode == MODE_ATTACK) {
            mpMorf->setPlaySpeed(3.0f);
        }
    }
    
    setAttention();
    setCollision();
    fopAcM_posMoveF(this, mStts.GetCCMoveP());
    mAcch.CrrPos(*dComIfG_Bgsp());
    setMtx();
    mBtkAnm.play();
    mBrkAnm.play();
    mpMorf->play(&current.pos, 0, 0);
    mpMorf->calc();
    enemy_fire(&mEnemyFire);
    modeProc(PROC_EXEC, MODE_NULL);
    setAnm(AnmPrm_NULL, false);
    setBtkAnm(0x5);
    g_env_light.settingTevStruct(0, &current.pos, &tevStr);
    
    return false;
}

/* 000040A8-000041A8       .text debugDraw__6daRd_cFv */
void daRd_c::debugDraw() {
    cXyz spawnPos = mSpawnPos;
    spawnPos.y += 10.0f;
    cXyz pos = current.pos;
    pos.y += 10.0f;
    (GXColor){0x00, 0xFF, 0x00, 0x80}; // Unused color, needed for the .rodata section to match.
    dLib_debugDrawFan(pos, mHeadAngle, l_HIO.mCrySpreadAngle, l_HIO.mCryRadius, (GXColor){0xFF, 0xFF, 0x00, 0x80});
    dLib_debugDrawFan(pos, shape_angle.y, l_HIO.mAttackSpreadAngle, l_HIO.mAttackRadius, (GXColor){0xFF, 0x00, 0x00, 0x80});
    dLib_debugDrawFan(pos, shape_angle.y, l_HIO.m40, l_HIO.m34, (GXColor){0xFF, 0x00, 0xFF, 0x80});
    dLib_debugDrawAxis(mCE8, 50.0f);
}

/* 000041A8-00004318       .text _draw__6daRd_cFv */
bool daRd_c::_draw() {
    if (mMode == MODE_SW_WAIT) {
        return true;
    }
    
    if (l_HIO.m2C != 0) {
        debugDraw();
    }
    
    J3DModel* model = mpMorf->getModel();
    J3DModelData* modelData = model->getModelData();
    g_env_light.setLightTevColorType(model, &tevStr);
    
    if (mEnemyIce.mFreezeTimer > 20) {
        dMat_control_c::iceEntryDL(mpMorf, -1, &mInvisModel);
    } else {
        mBrkAnm.entry(modelData);
        mBtkAnm.entry(modelData);
        mpMorf->updateDL();
        mBtkAnm.remove(modelData);
        mBrkAnm.remove(modelData);
    }
    
    cXyz shadowPos(current.pos.x, current.pos.y + 150.0f, current.pos.z);
    mShadowId = dComIfGd_setShadow(
        mShadowId, 1, mpMorf->getModel(), &shadowPos, 800.0f, 40.0f,
        current.pos.y, mAcch.GetGroundH(), mAcch.m_gnd, &tevStr
    );
    
    dSnap_RegistFig(DSNAP_TYPE_RD, this, 1.0f, 1.0f, 1.0f);
    
    return true;
}

/* 00004318-00004338       .text isLinkControl__6daRd_cFv */
bool daRd_c::isLinkControl() {
    return dComIfGp_getPlayer(0) != dComIfGp_getLinkPlayer();
}

/* 00004338-000046A4       .text createInit__6daRd_cFv */
void daRd_c::createInit() {
    mStts.Init(0xFF, 0, this);
    mCyl.Set(m_cyl_src);
    mCyl.SetStts(&mStts);
    mAcchCir.SetWall(30.0f, 30.0f);
    mAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this));
    mAcch.SetRoofNone();
    J3DModelData* modelData = mpMorf->getModel()->getModelData();
    mJntCtrl.setHeadJntNum(0x0A); // ree_kubi_1
    mJntCtrl.setBackboneJntNum(0x08); // ree_mune_1
    modelData->getJointNodePointer(0x0A)->setCallBack(nodeControl_CB); // ree_kubi_1
    modelData->getJointNodePointer(0x08)->setCallBack(nodeControl_CB); // ree_mune_1
    setBtkAnm(2);
    
    if (mChecksSwitch == 0) {
        modeProcInit(MODE_SW_WAIT);
        cXyz offset(0.0f, 40.0f, 10.0f);
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::YrotM(shape_angle.y);
        mDoMtx_stack_c::multVec(&offset, &current.pos);
    } else {
        modeProcInit(MODE_WAIT);
        switch (mWhichIdleAnm) {
        case 0:
            setAnm(AnmPrm_TACHIP1, false);
            break;
        case 1:
            setAnm(AnmPrm_SUWARIP, false);
            break;
        }
    }
    
    setBrkAnm(0);
    setMtx();
    mBtkAnm.play();
    mBrkAnm.play();
    mpMorf->play(&current.pos, 0, 0);
    mBrkAnm.setFrame(0.0f);
    mpMorf->calc();
    g_env_light.settingTevStruct(0, &current.pos, &tevStr);
    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -100.0f, -10.0f, -100.0f, 100.0f, 250.0f, 150.0f);
    
    mD3C = 1;
    mD40 = 1;
    stealItemLeft = 5;
    
    mEnemyFire.mpMcaMorf = mpMorf;
    mEnemyFire.mpActor = this;
    static u8 fire_j[ARRAY_SIZE(mEnemyFire.mFlameJntIdxs)] = {
        0x0C, 0x01, 0x0F, 0x11, 0x13, 0x15, 0x02, 0x04, 0x05, 0x07,
    };
    static f32 fire_sc[ARRAY_SIZE(mEnemyFire.mParticleScale)] = {
        2.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    };
    for (int i = 0; i < ARRAY_SIZE(mEnemyFire.mFlameJntIdxs); i++) {
        mEnemyFire.mFlameJntIdxs[i] = fire_j[i];
        mEnemyFire.mParticleScale[i] = fire_sc[i];
    }
    
    mEnemyIce.mpActor = this;
    mEnemyIce.m00C = 1;
    mEnemyIce.mWallRadius = 50.0f;
    mEnemyIce.mCylHeight = 250.0f;
    
    max_health = l_HIO.m46;
    health = max_health;
    mSpawnPos = current.pos;
    mSpawnAngle = shape_angle.y;
    gravity = -4.5f;
    
    // TODO: figure out if 1 and 2 actually drop different items
    if (mWhichIdleAnm == 0) {
        itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("Rdead1", 0);
    }
    if (mWhichIdleAnm == 1) {
        itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("Rdead2", 0);
    }
}

/* 000046A4-00004720       .text getArg__6daRd_cFv */
void daRd_c::getArg() {
    u32 params = fopAcM_GetParam(this);
    mWhichIdleAnm = fopAcM_GetParamBit(params, 0x00, 1);
    u8 radiusParam = fopAcM_GetParamBit(params, 0x01, 7);
    s32 areaRadius = radiusParam;
    mChecksSwitch = fopAcM_GetParamBit(params, 0x08, 8);
    mSwNo = fopAcM_GetParamBit(params, 0x18, 8);
    if ((s32)radiusParam == 0x7F) {
        areaRadius = 0;
    }
    mAreaRadius = l_HIO.m30 + areaRadius;
}

/* 00004720-000047C8       .text _create__6daRd_cFv */
s32 daRd_c::_create() {
    fopAcM_SetupActor(this, daRd_c);
    
    s32 phase_state = dComIfG_resLoad(&mPhs, m_arc_name);
    
    if (phase_state == cPhs_COMPLEATE_e) {
        getArg();
        
        if (!fopAcM_entrySolidHeap(this, createHeap_CB, 0x2520)) {
            return cPhs_ERROR_e;
        }
        
        createInit();
    }
    
    return phase_state;
}

/* 00004F60-00004FB8       .text _delete__6daRd_cFv */
bool daRd_c::_delete() {
    dComIfG_resDelete(&mPhs, m_arc_name);
    enemy_fire_remove(&mEnemyFire);
    if (heap) {
        mpMorf->stopZelAnime();
    }
    return true;
}

/* 00004FB8-00004FD8       .text daRdCreate__FPv */
static s32 daRdCreate(void* i_this) {
    return static_cast<daRd_c*>(i_this)->_create();
}

/* 00004FD8-00004FFC       .text daRdDelete__FPv */
static BOOL daRdDelete(void* i_this) {
    return static_cast<daRd_c*>(i_this)->_delete();
}

/* 00004FFC-00005020       .text daRdExecute__FPv */
static BOOL daRdExecute(void* i_this) {
    return static_cast<daRd_c*>(i_this)->_execute();
}

/* 00005020-00005044       .text daRdDraw__FPv */
static BOOL daRdDraw(void* i_this) {
    return static_cast<daRd_c*>(i_this)->_draw();
}

/* 00005044-0000504C       .text daRdIsDelete__FPv */
static BOOL daRdIsDelete(void* i_this) {
    return TRUE;
}

static actor_method_class daRdMethodTable = {
    (process_method_func)daRdCreate,
    (process_method_func)daRdDelete,
    (process_method_func)daRdExecute,
    (process_method_func)daRdIsDelete,
    (process_method_func)daRdDraw,
};

actor_process_profile_definition g_profile_RD = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_RD,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daRd_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x00D4,
    /* Actor SubMtd */ &daRdMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e | fopAcStts_UNK200000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
