/**
 * d_a_daiocta_eye.cpp
 * Mini-Boss - Big Octo (eye)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_daiocta_eye.h"
#include "d/actor/d_a_daiocta.h"
#include "d/actor/d_a_bomb.h"
#include "d/actor/d_a_player.h"
#include "d/d_bg_s_func.h"
#include "d/d_cc_d.h"
#include "d/d_lib.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/res/res_daiocta.h"

const s32 daDaiocta_Eye_c::m_heapsize = 2848;
const char daDaiocta_Eye_c::m_arc_name[] = "daiocta";
const s32 daDaiocta_Eye_c::m_scale_damage_time = 8;

static dCcD_SrcSph l_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ dCcG_SE_UNK23,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 180.0f,
    }},
};

static daDaiocta_Eye_HIO_c l_HIO;

/* 000000EC-000001B0       .text __ct__19daDaiocta_Eye_HIO_cFv */
daDaiocta_Eye_HIO_c::daDaiocta_Eye_HIO_c() {
    mSphRadius = 195.0f;
    m04 = 0xF;  // unused
    m08 = 5.0f; // unused
    m0C = 8.0f; // unused
    mParticleTranslationX = 0.0f;
    mParticleTranslationY = 0.0f;
    mParticleTranslationZ = 30.0f;
    mEyeRotStep = 0x1000;
    mEyeRotScale = 0x4;
    m24 = 0x4000;
    m26 = 0x1000;
    m28 = 0x1000;
    mEyeRndRotMaxX = 0x7FFF;
    mEyeRndRotMaxY = 0x2000;
    mEyeRndRotMaxZ = 0x2000; 
}

/* 000001B0-000001FC       .text nodeControl_CB__FP7J3DNodei */
static BOOL nodeControl_CB(J3DNode* i_nodeP, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model_p = j3dSys.getModel();
        daDaiocta_Eye_c* this_p = (daDaiocta_Eye_c *) model_p->getUserArea();
        if (this_p) {
            this_p->_nodeControl(i_nodeP, model_p);
        }
    }
    return TRUE;
}

/* 000001FC-000002B8       .text _nodeControl__15daDaiocta_Eye_cFP7J3DNodeP8J3DModel */
void daDaiocta_Eye_c::_nodeControl(J3DNode* i_nodeP, J3DModel* i_modelP) {
    J3DJoint* jnt_p = (J3DJoint *) i_nodeP;
    s32 jnt_no = jnt_p->getJntNo();
    cXyz dummy(0.0f, 0.0f, 0.0f);
    mDoMtx_stack_c::copy(i_modelP->getAnmMtx(jnt_no));

    if (jnt_no == 2) {
        mDoMtx_stack_c::ZXYrotM(mCurEyeRot);
        mDoMtx_stack_c::scaleM(mEyeScale);
    }
    
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    i_modelP->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* 000002B8-000002D8       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c* i_this) {
    return ((daDaiocta_Eye_c *)i_this)->_createHeap();
}

/* 000002D8-000004E4       .text _createHeap__15daDaiocta_Eye_cFv */
BOOL daDaiocta_Eye_c::_createHeap() {
    static Vec eye_sph_offset[] = {
        { 0.0f, 0.0f, 0.0f },
    };

    static __jnt_hit_data_c search_data[] = {
        {
            /* mShapeType  */ 1,
            /* mJointIndex */ 2,
            /* mRadius     */ 110.0f,
            /* mpOffsets   */ eye_sph_offset
        }
    };

    J3DModelData* modelData = static_cast<J3DModelData *>(dComIfG_getObjectRes(m_arc_name, DAIOCTA_BDL_DO_EYE1));
    JUT_ASSERT(0xE9, modelData != NULL);

    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000222);

    if (!mpModel) {
        return FALSE;
    }
    
    mpModel->setUserArea((u32)this);

    mpBrk = static_cast<J3DAnmTevRegKey *>(dComIfG_getObjectRes(m_arc_name, DAIOCTA_BRK_DAMAGE_EYE_A1));

    if (!mpBrk) {
        return FALSE;
    }

    int init_result = init_result = mBrkAnm.init(
        modelData, mpBrk, TRUE, 
        J3DFrameCtrl::EMode_NONE, 1.0f, 
        0, -1, false, FALSE
    );
    
    if (init_result == 0) {
        return FALSE;
    }

    mpBtk = static_cast<J3DAnmTextureSRTKey *>(dComIfG_getObjectRes(m_arc_name, DAIOCTA_BTK_DAMAGE_EYE_A1));
    
    if (!mpBtk) {
        return FALSE;
    }

    init_result = mBtkAnm.init(
        modelData, mpBtk, TRUE, 
        J3DFrameCtrl::EMode_NONE, 1.0f, 
        0, -1, false, FALSE
    );
    
    if (init_result == 0) {
        return FALSE;
    }

    for (int i = 0; i < 3; i++) {
        if (i == 2) modelData->getJointNodePointer(i)->setCallBack(nodeControl_CB);
    }

    mpJntHit = JntHit_create(mpModel, search_data, ARRAY_SSIZE(search_data));

    if (mpJntHit) {   
        jntHit = mpJntHit;
    } else {
        return FALSE;
    }

    return TRUE;
}

/* 000004E4-00000510       .text coHit_CB__FP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
void coHit_CB(fopAc_ac_c* i_this, dCcD_GObjInf*, fopAc_ac_c* i_actor, dCcD_GObjInf*) {
    if(i_actor) {
        ((daDaiocta_Eye_c *)i_this)->_coHit(i_actor);
    }
}

/* 00000510-000005D0       .text _coHit__15daDaiocta_Eye_cFP10fopAc_ac_c */
void daDaiocta_Eye_c::_coHit(fopAc_ac_c* i_actor) {
    if (fpcM_GetName(i_actor) == PROC_BOMB) {
        daBomb_c* bomb_p = (daBomb_c *) i_actor;
        if (bomb_p->chk_state(daBomb_c::STATE_4)) {
            if (!mbIsDead) {
                health = 0;
                mbIsDead = true;
                m295 = true;
                dComIfGp_particle_set(
                    dPa_name::ID_SCENE_8206, &mParticlePos, &shape_angle, 
                    NULL, 0xFF, &mParticleCB, fopAcM_GetRoomNo(this)
                );
                modeDeathInit();
            } else {
                mbIsDamagedBomb = true;
            }
        }
    }
}

/* 000005D0-000006C0       .text setMtx__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::setMtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mDoMtx_stack_c::transM(
        l_HIO.mParticleTranslationX, 
        l_HIO.mParticleTranslationY, 
        l_HIO.mParticleTranslationZ
    );
    mDoMtx_stack_c::multVecZero(&mParticlePos);
}

/* 000006C0-00000A6C       .text checkTgHit__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::checkTgHit() {
    mStts.Move();
    cCcD_Obj* tg_hit_obj_p = mSph.GetTgHitObj();
    if (tg_hit_obj_p) {
        mDoAud_onEnemyDamage();
        bool damaged = false;
        
        if (tg_hit_obj_p->ChkAtType(AT_TYPE_NORMAL_ARROW)) {
            fopAcM_seStart(this, JA_SE_LK_MS_WEP_HIT, 32);
            health -= 2;
            damaged = true;
        } else if (tg_hit_obj_p->ChkAtType(AT_TYPE_ICE_ARROW)) {
            fopAcM_seStart(this, JA_SE_LK_MS_WEP_HIT, 32);
            health -= 2;
            damaged = true;
        } else if (tg_hit_obj_p->ChkAtType(AT_TYPE_FIRE_ARROW)) {
            fopAcM_seStart(this, JA_SE_LK_MS_WEP_HIT, 32);
            health -= 2;
            damaged = true;
        } else if (tg_hit_obj_p->ChkAtType(AT_TYPE_LIGHT_ARROW)) {
            fopAcM_seStart(this, JA_SE_LK_MS_WEP_HIT, 32);
            health -= 4;
            damaged = true;
        } else if (tg_hit_obj_p->ChkAtType(AT_TYPE_HOOKSHOT)) {
            fopAcM_seStart(this, JA_SE_LK_MS_WEP_HIT, 32);
            health -= 2;
            damaged = true;
        } else if (tg_hit_obj_p->ChkAtType(AT_TYPE_BOOMERANG)) {
            fopAcM_seStart(this, JA_SE_LK_W_WEP_HIT, 32);
            health--;
            damaged = true;
        }

        if (damaged == true) {        
            daPy_py_c* player_p = daPy_getPlayerActorClass();
            cXyz tg_hit_pos = *mSph.GetTgHitPosP();
            dComIfGp_particle_set(dPa_name::ID_COMMON_0010, &tg_hit_pos);
            if (health <= 0) {
                cXyz hit_particle_scale(2.0f, 2.0f, 2.0f);
                dComIfGp_particle_set(
                    dPa_name::ID_COMMON_BIG_HIT, 
                    &tg_hit_pos, 
                    &player_p->shape_angle, 
                    &hit_particle_scale
                );
                fopAcM_seStart(this, JA_SE_LK_LAST_HIT, 0);
                health = 0;
                modeDeathInit();
            } else {
                modeDamageInit();
            }
        }
    }
}

/* 00000A6C-00000A78       .text modeWaitInit__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::modeWaitInit() {
    mMode = MODE_WAIT;
}

/* 00000A78-00000A98       .text modeWait__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::modeWait() {
    checkTgHit();
}

/* 00000A98-00000BD8       .text modeDamageInit__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::modeDamageInit() {
    mMode = MODE_DAMAGE;
    mScaleAnimeIdx = m_scale_damage_time;
    mbIsDamaged = true;

    J3DModelData* model_data_p = mpModel->getModelData();
    mpBrk = (J3DAnmTevRegKey *) dComIfG_getObjectRes(m_arc_name, DAIOCTA_BRK_DAMAGE_EYE_A1);
    mBrkAnm.init(
        model_data_p, mpBrk, TRUE, 
        J3DFrameCtrl::EMode_NONE, 1.0f, 
        0, -1, true, FALSE
    );
    mpBtk = (J3DAnmTextureSRTKey *) dComIfG_getObjectRes(m_arc_name, DAIOCTA_BTK_DAMAGE_EYE_A1);
    mBtkAnm.init(
        model_data_p, mpBtk, TRUE, 
        J3DFrameCtrl::EMode_NONE, 1.0f, 
        0, -1, true, FALSE
    );
 
    fopAcM_monsSeStart(mpParentActor, JA_SE_CV_DO_DAMAGE, 0);
}

/* 00000BD8-00000CD0       .text modeDamage__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::modeDamage() {
    static float scale_table[] = {
        1.0f, 0.975f, 
        1.0f, 0.95f, 
        1.0f, 0.9f,
        1.0f, 0.85f
    };

    dLib_scaleAnime(
        &mEyeScale.x, scale_table, 
        ARRAY_SSIZE(scale_table), &mScaleAnimeIdx, 
        0.2f, 10.0f, 0.025f
    );
    mEyeScale.y = mEyeScale.x;
    mEyeScale.z = mEyeScale.x;

    if (mBtkAnm.isStop() && mBrkAnm.isStop() && mScaleAnimeIdx == 0) {
        modeWaitInit();
    } else if (mScaleAnimeIdx == 0) {
        mScaleAnimeIdx = m_scale_damage_time;
    } 
}

/* 00000CD0-00000E20       .text modeDeathInit__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::modeDeathInit() {
    mMode = MODE_DEATH;
    mbIsDamaged = true;
    mEyeScale.setall(1.0f);
    mpBrk = (J3DAnmTevRegKey *) dComIfG_getObjectRes(m_arc_name, DAIOCTA_BRK_DAMAGE_EYE_B1);
    mBrkAnm.init(
        mpModel->getModelData(), mpBrk, TRUE, 
        J3DFrameCtrl::EMode_NONE, 1.0f, 
        0, -1, true, FALSE
    );
    mpBtk = (J3DAnmTextureSRTKey *) dComIfG_getObjectRes(m_arc_name, DAIOCTA_BTK_DAMAGE_EYE_B1);
    mBtkAnm.init(
        mpModel->getModelData(), mpBtk, TRUE, 
        J3DFrameCtrl::EMode_NONE, 1.0f, 
        0, -1, true, FALSE
    );
    fopAcM_monsSeStart(mpParentActor, 0x48CB, 0);
}

/* 00000E20-00000E2C       .text modeDeath__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::modeDeath() {
    mbIsDead = true;
}

/* 00000E2C-00000ED0       .text modeProcCall__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::modeProcCall() {
    static ModeProcFunc mode_proc[] = {
        &daDaiocta_Eye_c::modeWait,
        &daDaiocta_Eye_c::modeDamage,
        &daDaiocta_Eye_c::modeDeath,
    };
    (this->*mode_proc[mMode])();
}

/* 00000ED0-00001120       .text _execute__15daDaiocta_Eye_cFv */
bool daDaiocta_Eye_c::_execute() {
    if (!mbAppear) {
        return false;
    }

    if (mbIsDead == true) {
        mSph.OffTgSPrmBit(cCcD_TgSPrm_Set_e);
    }

    m2EC = l_HIO.m24;
    m2EE = l_HIO.m26;
    m2F0 = l_HIO.m28;
    mEyeRndRotMaxX = l_HIO.mEyeRndRotMaxX;
    mEyeRndRotMaxY = l_HIO.mEyeRndRotMaxY;
    mEyeRndRotMaxZ = l_HIO.mEyeRndRotMaxZ;

    mBrkAnm.play();
    mBtkAnm.play();

    mbIsDamaged = false;
    mbIsDamagedBomb = false;
    modeProcCall();
    setMtx();

    attention_info.position = current.pos;

    attention_info.position.y += 100.0f;
    
    eyePos = current.pos;

    cLib_addCalcAngleS2(&mCurEyeRot.x, mEyeRotTargetX, l_HIO.mEyeRotScale + 1, l_HIO.mEyeRotStep);
    cLib_addCalcAngleS2(&mCurEyeRot.y, mEyeRotTargetY, l_HIO.mEyeRotScale + 1, l_HIO.mEyeRotStep);
    cLib_addCalcAngleS2(&mCurEyeRot.z, mEyeRotTargetZ, l_HIO.mEyeRotScale + 1, l_HIO.mEyeRotStep);
    mSph.SetR(l_HIO.mSphRadius);
    mSph.SetC(current.pos);
    dComIfG_Ccsp()->Set(&mSph);

    m498.set(0, shape_angle.y, 0);

    cXyz current_pos = current.pos;
    current_pos.y += 1000.0f;
    f32 water_height = dBgS_GetWaterHeight(current_pos);

    if (current.pos.y < water_height) {
        if (mParticleCB.getEmitter()) {
            mParticleCB.end();
        }
    } else if (mMode != MODE_DEATH) {
        attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
        attention_info.distances[fopAc_Attn_TYPE_BATTLE_e] = 34;
    }
    
    if (mMode == MODE_DEATH || dComIfGp_event_runCheck()) {
        attention_info.flags = 0;
    }

    return false;
}

/* 00001120-000011EC       .text _draw__15daDaiocta_Eye_cFv */
bool daDaiocta_Eye_c::_draw() {
    if (!mbAppear) {
        return false;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    
    mBtkAnm.entry(mpModel->getModelData());
    mBrkAnm.entry(mpModel->getModelData());

    mDoExt_modelUpdateDL(mpModel);

    mBtkAnm.remove(mpModel->getModelData());
    mBrkAnm.remove(mpModel->getModelData());
    
    return true;
}

/* 000011EC-000012D4       .text createInit__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::createInit() {
    mbAppear = false;
    cullMtx = mpModel->getBaseTRMtx();
    mStts.Init(0, 0, this);
    mSph.Set(l_sph_src);
    mSph.SetStts(&mStts);
    mSph.SetCoHitCallback(coHit_CB);
    max_health = 4;
    health = max_health;
    mEyeScale.setall(1.0f);
    if (parentActorID != -1) {
        fopAc_ac_c* parent_p = fopAcM_SearchByID(parentActorID);
        if (parent_p && fopAc_IsActor(parent_p) && fpcM_GetName(parent_p) == PROC_DAIOCTA) {
            mpParentActor = (daDaiocta_c *) parent_p;
        }
    }
}

/* 000012D4-00001450       .text _create__15daDaiocta_Eye_cFv */
cPhs_State daDaiocta_Eye_c::_create() {
    fopAcM_SetupActor(this, daDaiocta_Eye_c);
    cPhs_State result = dComIfG_resLoad(&mPhs, m_arc_name);
    if (result == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(this, createHeap_CB, m_heapsize)) {
            return cPhs_ERROR_e;
        }
        createInit();
    }
    return result;
}

/* 00001764-000017B4       .text _delete__15daDaiocta_Eye_cFv */
bool daDaiocta_Eye_c::_delete() {
    dComIfG_resDelete(&mPhs, m_arc_name);
    mParticleCB.remove();
    return true;
}

/* 000017B4-000017D4       .text daDaiocta_EyeCreate__FPv */
static cPhs_State daDaiocta_EyeCreate(void* i_this) {
    return ((daDaiocta_Eye_c*)i_this)->_create();
}

/* 000017D4-000017F8       .text daDaiocta_EyeDelete__FPv */
static BOOL daDaiocta_EyeDelete(void* i_this) {
    return ((daDaiocta_Eye_c*)i_this)->_delete();
}

/* 000017F8-0000181C       .text daDaiocta_EyeExecute__FPv */
static BOOL daDaiocta_EyeExecute(void* i_this) {
    return ((daDaiocta_Eye_c*)i_this)->_execute();
}

/* 0000181C-00001840       .text daDaiocta_EyeDraw__FPv */
static BOOL daDaiocta_EyeDraw(void* i_this) {
    return ((daDaiocta_Eye_c*)i_this)->_draw();
}

/* 00001840-00001848       .text daDaiocta_EyeIsDelete__FPv */
static BOOL daDaiocta_EyeIsDelete(void*) {
    return TRUE;
}

static actor_method_class daDaiocta_EyeMethodTable = {
    (process_method_func)daDaiocta_EyeCreate,
    (process_method_func)daDaiocta_EyeDelete,
    (process_method_func)daDaiocta_EyeExecute,
    (process_method_func)daDaiocta_EyeIsDelete,
    (process_method_func)daDaiocta_EyeDraw,
};

actor_process_profile_definition g_profile_DAIOCTA_EYE = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_DAIOCTA_EYE,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daDaiocta_Eye_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_DAIOCTA_EYE,
    /* Actor SubMtd */ &daDaiocta_EyeMethodTable,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_4_e,
};
