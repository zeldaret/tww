/**
 * d_a_dr.cpp
 * Valoo / ドラゴン (Dragon)
 */

#include "d/actor/d_a_dr.h"
#include "d/res/res_dr.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_hostIO.h"
#include "d/d_snap.h"
#include "d/d_com_inf_game.h"

static daDr_HIO_c l_HIO;

/* 000000EC-00000148       .text __ct__10daDr_HIO_cFv */
daDr_HIO_c::daDr_HIO_c() {
    mNo = -1;
    mScale = 1.0f;
    m0C = false;
    m0E = 10*30;
    mWait1Morf = 10.0f;
    mAkubi1Morf = 10.0f;
    mBiku1Morf = 2.0f;
    mAbare1Morf = 5.0f;
    mAbare2Morf = 5.0f;
    mHo1Morf = 10.0f;
}

/* 00000148-000001DC       .text daDr_Draw__FP8dr_class */
static BOOL daDr_Draw(dr_class* i_this) {
    J3DModel* model = i_this->mpMorf->getModel();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->current.pos, &i_this->tevStr);
    g_env_light.setLightTevColorType(model, &i_this->tevStr);
    i_this->mpMorf->entryDL();
    dSnap_RegistFig(DSNAP_TYPE_DR, i_this, i_this->eyePos, i_this->shape_angle.y, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 000001DC-00000320       .text anm_init__FP8dr_classifUcfi */
static void anm_init(dr_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed, int soundFileIdx) {
    if (i_this->mCurrBckIdx == bckFileIdx) {
        morf = 0.0f;
    }
    if (soundFileIdx >= 0) {
        void* soundAnm = dComIfG_getObjectRes("Dr", soundFileIdx);
        J3DAnmTransform* bckAnm = (J3DAnmTransform*)dComIfG_getObjectRes("Dr", bckFileIdx);
        i_this->mpMorf->setAnm(bckAnm, loopMode, morf, speed, 0.0f, -1.0f, soundAnm);
    } else {
        J3DAnmTransform* bckAnm = (J3DAnmTransform*)dComIfG_getObjectRes("Dr", bckFileIdx);
        i_this->mpMorf->setAnm(bckAnm, loopMode, morf, speed, 0.0f, -1.0f, NULL);
    }
    i_this->mCurrBckIdx = bckFileIdx;
}

/* 00000320-0000091C       .text move__FP8dr_class */
static void move(dr_class* i_this) {
    bool isIdle = false;
    switch (i_this->mMode) {
    case 0:
        isIdle = true;
        anm_init(i_this, DR_BCK_DR_WAIT1, l_HIO.mWait1Morf, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->mMode++;
        i_this->mCountDownTimers[0] = (s16)(200.0f + cM_rndF(200.0f));
        break;
    case 1:
        isIdle = true;
        if (i_this->mCountDownTimers[0] == 0) {
            anm_init(i_this, DR_BCK_DR_AKUBI1, l_HIO.mAkubi1Morf, J3DFrameCtrl::EMode_NONE, 1.0f, DR_BAS_AKUBI1);
            i_this->mMode++;
        }
        break;
    case 2:
        isIdle = true;
        if (i_this->mpMorf->isStop()) {
            i_this->mMode = 0;
        }
        break;
    case 10:
        anm_init(i_this, DR_BCK_DR_BIKU1, l_HIO.mBiku1Morf, J3DFrameCtrl::EMode_NONE, 1.0f, DR_BAS_BIKU1);
        i_this->mMode++;
        i_this->mCountDownTimers[0] = l_HIO.m0E;
        i_this->mpBreathEmitter = dComIfGp_particle_set(dPa_name::ID_SCENE_81C4, &i_this->current.pos);
        i_this->m2C9 = 0;
        // Fall-through
    case 11:
        if (i_this->m2C9 == 0 && (int)i_this->mpMorf->getFrame() == 15) {
            i_this->mCountDownTimers[1] = 5;
        }
        
        if (i_this->mpMorf->isStop()) {
            i_this->m2C9 = 1;
            if (i_this->mpBreathEmitter) {
                i_this->mpBreathEmitter->becomeInvalidEmitter();
                i_this->mpBreathEmitter = NULL;
            }
            
            if (i_this->mCountDownTimers[0] != 0) {
                if (cM_rndF(1.0f) < 0.5f) {
                    anm_init(i_this, DR_BCK_DR_ABARE1, l_HIO.mAbare1Morf, J3DFrameCtrl::EMode_NONE, 1.0f, DR_BAS_ABARE1);
                    i_this->mpBreathEmitter = dComIfGp_particle_set(dPa_name::ID_SCENE_81C5, &i_this->current.pos);
                    i_this->mCountDownTimers[1] = 500;
                } else {
                    anm_init(i_this, DR_BCK_DR_ABARE2, l_HIO.mAbare2Morf, J3DFrameCtrl::EMode_NONE, 1.0f, DR_BAS_ABARE2);
                    
                    cXyz rootPos;
                    cXyz offset(0.0f, 0.0f, 0.0f);
                    MtxP rootJntMtx = i_this->mpMorf->getModel()->getAnmMtx(0x00); // dr_all_root joint
                    cMtx_copy(rootJntMtx, *calc_mtx);
                    MtxPosition(&offset, &rootPos);
                    dComIfGp_particle_set(dPa_name::ID_SCENE_81C7, &rootPos);
                    
                    fopAcM_seStart(i_this, JA_SE_CM_DRG_MTOP_MAGMA, 0);
                    i_this->mCountDownTimers[1] = 0;
                }
            } else {
                anm_init(i_this, DR_BCK_DR_HO1, l_HIO.mHo1Morf, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                i_this->mpBreathEmitter = dComIfGp_particle_set(dPa_name::ID_SCENE_81C6, &i_this->current.pos);
                i_this->mMode++;
            }
        }
        
        if (i_this->mpBreathEmitter) {
            MtxP tongueJntMtx = i_this->mpMorf->getModel()->getAnmMtx(0x20); // j_dr_sita2 (tongue) joint
            i_this->mpBreathEmitter->setGlobalRTMatrix(tongueJntMtx);
        }
        break;
    case 12:
        if (i_this->mpBreathEmitter) {
            MtxP tongueJntMtx = i_this->mpMorf->getModel()->getAnmMtx(0x20); // j_dr_sita2 (tongue) joint
            i_this->mpBreathEmitter->setGlobalRTMatrix(tongueJntMtx);
        }
        
        if ((int)i_this->mpMorf->getFrame() == 34) {
            i_this->mCountDownTimers[1] = 5;
        }
        
        if (i_this->mpMorf->isStop()) {
            i_this->mMode = 0;
            if (i_this->mpBreathEmitter) {
                i_this->mpBreathEmitter->becomeInvalidEmitter();
                i_this->mpBreathEmitter = NULL;
            }
        }
        break;
    }
    
    if (!dComIfGs_isStageBossEnemy(dSv_save_c::STAGE_DRC)) {
        if ((isIdle && (l_HIO.m0C || dComIfGp_getVibration().CheckQuake())) || i_this->m2C8 != 0) {
            l_HIO.m0C = false;
            i_this->m2C8 = 0;
            i_this->mMode = 10;
        }
    }
    
    i_this->mpMorf->play(&i_this->current.pos, 0, 0);
    
    if (i_this->mCountDownTimers[1] != 0) {
        fopAcM_seStart(i_this, JA_SE_CM_DRG_MTOP_FIRE, 0);
    }
}

/* 0000091C-000009CC       .text daDr_setMtx__FP8dr_class */
static void daDr_setMtx(dr_class* i_this) {
    J3DModel* model = i_this->mpMorf->getModel();
    model->setBaseScale(i_this->scale);
    mDoMtx_stack_c::transS(i_this->current.pos);
    mDoMtx_stack_c::YrotM(i_this->current.angle.y);
    mDoMtx_stack_c::XrotM(i_this->current.angle.x);
    mDoMtx_stack_c::ZrotM(i_this->current.angle.z);
    model->setBaseTRMtx(mDoMtx_stack_c::get());
    
    i_this->mpMorf->calc();
}

/* 000009CC-00000A8C       .text daDr_Execute__FP8dr_class */
static BOOL daDr_Execute(dr_class* i_this) {
    for (int i = 0; i < ARRAY_SIZE(i_this->mCountDownTimers); i++) {
        if (i_this->mCountDownTimers[i] != 0) {
            i_this->mCountDownTimers[i]--;
        }
    }
    
    move(i_this);
    
    i_this->scale.x = i_this->scale.y = i_this->scale.z = l_HIO.mScale;
    
    daDr_setMtx(i_this);
    
    MtxP tongueJntMtx = i_this->mpMorf->getModel()->getAnmMtx(0x20); // j_dr_sita2 (tongue) joint
    cMtx_copy(tongueJntMtx, *calc_mtx);
    cXyz offset(0.0f, 0.0f, 0.0f);
    MtxPosition(&offset, &i_this->eyePos);
    
    return TRUE;
}

/* 00000A8C-00000A94       .text daDr_IsDelete__FP8dr_class */
static BOOL daDr_IsDelete(dr_class* i_this) {
    return TRUE;
}

/* 00000A94-00000AE8       .text daDr_Delete__FP8dr_class */
static BOOL daDr_Delete(dr_class* i_this) {
    dComIfG_resDelete(&i_this->mPhs, "Dr");
    if (l_HIO.mNo >= 0) {
        mDoHIO_deleteChild(l_HIO.mNo);
    }
    return TRUE;
}

/* 00000AE8-00000C08       .text createHeap__FP10fopAc_ac_c */
static BOOL createHeap(fopAc_ac_c* i_actor) {
    dr_class* i_this = (dr_class*)i_actor;

    i_this->mpMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Dr", DR_BMD_DR1),
        NULL, NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Dr", DR_BCK_DR_BIKU1),
        J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, 1,
        dComIfG_getObjectRes("Dr", DR_BAS_BIKU1),
        0x00000000,
        0x11020203
    );
    if (!i_this->mpMorf || !i_this->mpMorf->getModel()) {
        return FALSE;
    }
    
    return TRUE;
}

/* 00000C08-00000CE4       .text daDr_Create__FP10fopAc_ac_c */
static cPhs_State daDr_Create(fopAc_ac_c* i_actor) {
    fopAcM_SetupActor(i_actor, dr_class);
    
    dr_class* i_this = (dr_class*)i_actor;
    
    cPhs_State phase_state = dComIfG_resLoad(&i_this->mPhs, "Dr");
    if (phase_state == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(i_this, createHeap, 0xF000)) {
            return cPhs_ERROR_e;
        }
        
        daDr_setMtx(i_this);
        
        if (l_HIO.mNo < 0) {
            l_HIO.mNo = mDoHIO_createChild("ドラゴン", &l_HIO); // "Dragon"
        }
    }
    
    return phase_state;
}

static actor_method_class l_daDr_Method = {
    (process_method_func)daDr_Create,
    (process_method_func)daDr_Delete,
    (process_method_func)daDr_Execute,
    (process_method_func)daDr_IsDelete,
    (process_method_func)daDr_Draw,
};

actor_process_profile_definition g_profile_DR = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_DR,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(dr_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_DR,
    /* Actor SubMtd */ &l_daDr_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
