/**
 * d_a_leaflift.cpp
 * Object - Forest Haven - Lilypad lift
 */

#include "d/actor/d_a_leaflift.h"
#include "d/d_bg_s_func.h"
#include "d/d_bg_s_movebg_actor.h"
#include "d/d_com_inf_game.h"
#include "d/d_lib.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/res/res_olift.h"
#include "m_Do/m_Do_ext.h"

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ cCcD_TgSPrm_IsPlayer_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 280.0f,
        /* Height */ 510.0f,
    },
};

static cXyz up_vec(0.0f, 1.0f, 0.0f);

const char daLlift_c::m_arcname[6] = "Olift";

/* 000000EC-000001C0       .text _delete__9daLlift_cFv */
bool daLlift_c::_delete() {
    if (mEmitter1) {
        mEmitter1->becomeInvalidEmitter();
        mEmitter1 = NULL;
    }
    if (mEmitter2) {
        mEmitter2->becomeInvalidEmitter();
        mEmitter2 = NULL;
    }
    if (mEmitter3) {
        mEmitter3->becomeInvalidEmitter();
        mEmitter3 = NULL;
    }
    if (heap)
        dComIfG_Bgsp()->Release(mpBgW);
    dComIfG_resDelete(&mPhs, m_arcname);
    return TRUE;
}

/* 000001C0-000001E0       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daLlift_c*)i_this)->CreateHeap();
}

static void rideCallBack(dBgW* param1, fopAc_ac_c* i_this, fopAc_ac_c* i_other);

/* 000001E0-00000338       .text CreateHeap__9daLlift_cFv */
BOOL daLlift_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData *)dComIfG_getObjectRes(m_arcname, OLIFT_BDL_OLIFT);
    JUT_ASSERT(0x14e, modelData != NULL);

    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
    if (!mpModel) {
        return FALSE;
    }

    mpModel->setUserArea((u32)this);
    mpBgW = new dBgW();
    if (mpBgW) {
        cBgD_t* pData = (cBgD_t *)dComIfG_getObjectRes(m_arcname, OLIFT_DZB_OLIFT);
        if (mpBgW->Set(pData, cBgW::MOVE_BG_e, &mMtx) == 1) {
            return FALSE; 
        }
        mpBgW->SetCrrFunc(dBgS_MoveBGProc_TypicalRotY);
        mpBgW->SetRideCallback(rideCallBack);
    }
    else {
        return FALSE;
    }
    return TRUE;
} 

static BOOL nodeCallBack(J3DNode* node, int calcTiming);

/* 00000338-000005F8       .text CreateInit__9daLlift_cFv */
void daLlift_c::CreateInit() {
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -300.0f, -600.0f, -300.0f, 300.0f, 100.0f, 300.0f);
    fopAcM_setCullSizeFar(this, 1.0f);
    mStts.Init(0xFF,0xFF,this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);
    cXyz waterCheckPos = current.pos;
    waterCheckPos.y += 200.0f;
    mWaterY = dBgS_ObjGndChk_Wtr_Func(waterCheckPos);
    if (mWaterY != -G_CM3D_F_INF) {
        cXyz particlePos = current.pos;
        particlePos.y = mWaterY + 1.0f; 
        mEmitter3 = dComIfGp_particle_set(dPa_name::ID_SCENE_82AA, &particlePos, &current.angle);
        if (mEmitter3) {
            mEmitter3->stopCreateParticle();
        }
    }
    home.pos.y += 15.0f;
    current.pos.y = home.pos.y;
    JUTNameTab* jointName = mpModel->getModelData()->getJointName();
    for (u16 i = 0; i < mpModel->getModelData()->getJointNum(); i++) {
        if (strcmp("j_happa", jointName->getName(i)) == 0) {
            mpModel->getModelData()->getJointNodePointer(i)->setCallBack(&nodeCallBack);
            break;
        }
    }
    mTargetRotation = ZeroQuat;
    mCurrentRotation = mTargetRotation;
    if ((s32)daLlift_prm::getPos(this) == 1) {
        current.pos.y =  home.pos.y + m_height;
    }
    else {
        if (mEmitter3) {
            mEmitter3->playCreateParticle();
        }
    }
    m43F = 0x1e;
    mpModel->calc();
    setMoveBGMtx();
    dComIfG_Bgsp()->Regist(mpBgW, this);
    set_mtx();
    mpBgW->Move();
}

/* 00000634-00000760       .text _create__9daLlift_cFv */
cPhs_State daLlift_c::_create() {
    int res;
    fopAcM_SetupActor(this, daLlift_c);
    res = dComIfG_resLoad(&mPhs, m_arcname);
    if (res == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, 0xf40)) {
            return cPhs_ERROR_e;
        }
        else {
            CreateInit();
        }
    }
    return res;
}

/* 00000918-000009C4       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        daLlift_c* i_this = (daLlift_c*)model->getUserArea();
        if (i_this) {
            mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));
            mDoMtx_stack_c::quatM(&i_this->mCurrentRotation);
            cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
            model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
            cMtx_copy(mDoMtx_stack_c::get(), i_this->mBGMtx);
        }
    }
    return TRUE;
}

/* 000009C4-00000CAC       .text rideCallBack__FP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
static void rideCallBack(dBgW* param1, fopAc_ac_c* i_act, fopAc_ac_c* i_other) {
    daLlift_c* i_this = (daLlift_c*)i_act;
    f32 tiltFactor;
    f32 offsetMagnitude;

    cXyz posOffset = i_other->current.pos - i_this->current.pos;
    tiltFactor = 2.0f;
    if (fopAcM_GetName(i_other) == PROC_PLAYER) {
        i_this->m43C = TRUE;
        i_this->m43E = TRUE;
        posOffset = posOffset.outprod(up_vec);
        mDoMtx_stack_c::YrotS(-i_this->current.angle.y);
        mDoMtx_stack_c::multVec(&posOffset, &posOffset);
        if (i_this->m43D) {
            posOffset = i_other->current.pos;
            posOffset.x += 200.0f;
            posOffset = posOffset.outprod(up_vec);
            mDoMtx_stack_c::YrotS(-i_this->current.angle.y);
            mDoMtx_stack_c::multVec(&posOffset, &posOffset);
            s16 angle = (i_this->mActorLifetimeFrameCount % 32U) * (0x10000 / 32);
            tiltFactor = cM_ssin(angle) * 2.0f * 0.25f * (cM_rndFX(0.2f) + 1.0f);
        }
        offsetMagnitude = posOffset.abs();
        if (!posOffset.normalizeRS() ) {
          return;
        }
        cLib_addCalcAngleS2(&i_this->mTiltAngle, -offsetMagnitude * tiltFactor, 8, 0x200);
        tiltFactor = cM_ssin(i_this->mTiltAngle);
        i_this->mTargetRotation.x = posOffset.x * tiltFactor;
        i_this->mTargetRotation.y = posOffset.y * tiltFactor;
        i_this->mTargetRotation.z = posOffset.z * tiltFactor;
        i_this->mTargetRotation.w = cM_scos(i_this->mTiltAngle);
    }
    i_this->m43D = FALSE;
}

/* 00000CAC-00000D34       .text set_mtx__9daLlift_cFv */
void daLlift_c::set_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::ZXYrotM(current.angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000D34-00000D9C       .text setMoveBGMtx__9daLlift_cFv */
void daLlift_c::setMoveBGMtx() {
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mDoMtx_stack_c::quatM(&mCurrentRotation);
    MTXCopy(mDoMtx_stack_c::get(), mMtx);
}

/* 00000D9C-00000F24       .text _execute__9daLlift_cFv */
bool daLlift_c::_execute() {
    Quaternion interpolatedRotation;
    cXyz adjustedPosition;
    float distXZ = fopAcM_searchActorDistanceXZ(this, dComIfGp_getPlayer(0));
    mActorLifetimeFrameCount++;
    if (m43F > 0) {
        m43F--;
        if (m43F == 0) {
            m43E = TRUE;
        }
    }
    if ((!m43C) && (m43E)) {
        mTargetRotation = ZeroQuat;
        if (distXZ > 270.0f) {
            mbIsDescending = TRUE;
        }
    }
    MoveDownLift();
    set_mtx();
    setMoveBGMtx();
    m43C = FALSE;
    mpModel->calc();
    mDoMtx_quatSlerp(&mCurrentRotation, &mTargetRotation, &interpolatedRotation, 0.25f);
    mCurrentRotation = interpolatedRotation;
    mpBgW->Move();
    adjustedPosition = current.pos;
    adjustedPosition.y -= m_height;
    mCyl.SetC(adjustedPosition);
    dComIfG_Ccsp()->Set(&mCyl);
    emitterCtrl();
    return TRUE;
}

/* 00000F24-00000FE0       .text emitterCtrl__9daLlift_cFv */
void daLlift_c::emitterCtrl() {  
    if (mEmitterTimer == 200) {
        if (mEmitter1) {
            mEmitter1->becomeInvalidEmitter();
            mEmitter1 = NULL;
        }
        if (mEmitter2) {
            mEmitter2->becomeInvalidEmitter();
            mEmitter2 = NULL;
        }
    }
    if (mEmitter1) {
        mEmitter1->setGlobalRTMatrix(mBGMtx);
    }
    if (mEmitter2) {
        mEmitter2 ->setGlobalRTMatrix(mBGMtx);
    }
}

/* 00000FE0-000010E0       .text MoveDownLift__9daLlift_cFv */
BOOL daLlift_c::MoveDownLift() {
    float maxSpeed = m_max_speed;
    float minSpeed = m_min_speed;
    if (!mbIsDescending) {
        return TRUE;
    }
    float downVel = cLib_addCalc(&current.pos.y, home.pos.y, 0.1f, maxSpeed, minSpeed);
    if (downVel == 0.0f) {
        mbIsAscending = FALSE;
        mbIsDescending = FALSE;
        if (mEmitter3) {
            mEmitter3->playCreateParticle();
        }
        return TRUE;
    }
    if (downVel != 0.0f && !mbIsAscending) {
        fopAcM_seStart(this, JA_SE_OBJ_LOTUS_LIFT_DOWN, 0);
        mbIsAscending = TRUE;
    }
    return FALSE;
}

/* 000010E0-00001180       .text _draw__9daLlift_cFv */
bool daLlift_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    dComIfGd_setListBG();
    mDoExt_modelEntryDL(mpModel);
    dComIfGd_setList();
    return TRUE;
}

/* 00001180-000011A0       .text daLlift_Create__FPv */
static cPhs_State daLlift_Create(void* i_this) {
    return ((daLlift_c*)i_this)->_create();
}

/* 000011A0-000011C4       .text daLlift_Delete__FPv */
static BOOL daLlift_Delete(void* i_this) {
    return ((daLlift_c*)i_this)->_delete();
}

/* 000011C4-000011E8       .text daLlift_Draw__FPv */
static BOOL daLlift_Draw(void* i_this) {
    return ((daLlift_c*)i_this)->_draw();
}

/* 000011E8-0000120C       .text daLlift_Execute__FPv */
static BOOL daLlift_Execute(void* i_this) {
    return ((daLlift_c*)i_this)->_execute();
}

/* 0000120C-00001214       .text daLlift_IsDelete__FPv */
static BOOL daLlift_IsDelete(void* i_this) {
    return TRUE;
}

static actor_method_class daLliftMethodTable = {
    (process_method_func)daLlift_Create,
    (process_method_func)daLlift_Delete,
    (process_method_func)daLlift_Execute,
    (process_method_func)daLlift_IsDelete,
    (process_method_func)daLlift_Draw,
};

actor_process_profile_definition g_profile_LEAF_LIFT = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_LEAF_LIFT,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daLlift_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_LEAF_LIFT,
    /* Actor SubMtd */ &daLliftMethodTable,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
