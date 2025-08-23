/**
 * d_a_jbo.cpp
 * Object - Baba Bud
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_jbo.h"
#include "d/actor/d_a_player.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "d/d_s_play.h"
#include "d/d_procname.h"
#include "d/res/res_jbo.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_priority.h"

/* 00000078-00000108       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode *i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = reinterpret_cast<J3DJoint*>(i_node);
        s32 jntNo = joint->getJntNo();
        jbo_class* jbo = reinterpret_cast<jbo_class*>(j3dSys.getModel()->getUserArea());
        if (jbo != NULL && jntNo == 9) {
            MTXCopy(j3dSys.getModel()->getAnmMtx(jntNo), *calc_mtx);
            cXyz pos;
            pos.x = 0;
            pos.y = 0;
            pos.z = 0;
            MtxPosition(&pos, &jbo->mParticlePos);
        }
    }
    return TRUE;
}

/* 00000108-00000240       .text jbo_draw_SUB__FP9jbo_class */
void jbo_draw_SUB(jbo_class *i_this) {
    J3DModel *model = i_this->mpMorf->mpModel;
    model->setBaseScale(i_this->scale);
    mDoMtx_stack_c::transS(i_this->current.pos.x, i_this->current.pos.y, i_this->current.pos.z);
    mDoMtx_stack_c::YrotM(i_this->shape_angle.y);
    mDoMtx_stack_c::XrotM(i_this->shape_angle.x);
    mDoMtx_stack_c::ZrotM(i_this->shape_angle.z);
    if (i_this->mAnimationSpeed) {
        cXyz scale;
        scale.x = REG8_F(1) + 1.1F;
        scale.y = REG8_F(2) + 1.0F;
        scale.z = REG8_F(3) + 0.9F;
        i_this->mAnimRotation += i_this->mAnimationSpeed;
        mDoMtx_stack_c::YrotM(i_this->mAnimRotation);
        mDoMtx_stack_c::scaleM(scale);
        mDoMtx_stack_c::YrotM(-i_this->mAnimRotation);
    }
    MTXCopy(mDoMtx_stack_c::now, model->getBaseTRMtx());
}

/* 00000240-000002C4       .text daJBO_Draw__FP9jbo_class */
static BOOL daJBO_Draw(jbo_class *i_this) {
    J3DModel *model = i_this->mpMorf->getModel();
    if (i_this->mParam == 3)
        return TRUE;
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->current.pos, &i_this->tevStr);
    g_env_light.setLightTevColorType(model, &i_this->tevStr);
    i_this->mpMorf->updateDL();
    return TRUE;
}

// time from link entering blub to being vomited out
#define JUMP_ANIMATION_TIME 70

enum daJbo_State {
    daJbo_State_IDLE = 0,
    daJbo_State_WAIT_JUMP = 1,
    daJbo_State_SPAWN = 2,
};

/* 000002C4-00000584       .text jbo_move__FP9jbo_class */
void jbo_move(jbo_class *i_this) {
    u8 state = i_this->mState;
    switch (state) {
        case daJbo_State_IDLE: {
            if (dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK80_e) && i_this->mSph.ChkCoHit()) {
                J3DAnmTransform* anm = (J3DAnmTransform*)dComIfG_getObjectRes("JBO", JBO_BCK_IN1);
                i_this->mpMorf->setAnm(anm, J3DFrameCtrl::EMode_NONE, 0.0, 1.0, 0.0, -1.0, NULL);
                fopAcM_seStart(i_this, JA_SE_OBJ_JFLOWER_IN, 0);
                dComIfGp_setItemMagicCount(4);
                i_this->mFramesUntilJump = JUMP_ANIMATION_TIME;
                i_this->mState += 1;
            }
            break;
        }
        case daJbo_State_WAIT_JUMP: {
            i_this->mAnimationSpeed = JUMP_ANIMATION_TIME - i_this->mFramesUntilJump;
            i_this->mAnimationSpeed *= 200;
            if (i_this->mFramesUntilJump == 1) {
                ((daPy_py_c *)dComIfGp_getPlayer(0))->onForceVomitJump();
            }
            if (dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK80000000_e)) {
                J3DAnmTransform* anm = (J3DAnmTransform*)dComIfG_getObjectRes("JBO", JBO_BCK_OUT1);
                i_this->mpMorf->setAnm(anm, J3DFrameCtrl::EMode_NONE, 0.0, 1.0, 0.0, -1.0, NULL);
                fopAcM_seStart(i_this, JA_SE_OBJ_JFLOWER_OUT, 0);
                i_this->mAnimationSpeed = 0;
                i_this->mAnimRotation = 0;
                JPABaseEmitter *emitter = dComIfGp_particle_setToon(0xa110, &i_this->mParticlePos);
                if (emitter != NULL) {
                    emitter->setGlobalAlpha(100);
                }
                if (i_this->mParam == 2) {
                    i_this->m2BA = 1;
                }
                i_this->mState = daJbo_State_IDLE;
            }
            break;
        }
        case daJbo_State_SPAWN: {
            if (i_this->mpMorf->isStop()) {
                i_this->mState = daJbo_State_IDLE;
            }
            break;
        }
    }
}

/* 00000584-00000698       .text daJBO_Execute__FP9jbo_class */
static BOOL daJBO_Execute(jbo_class* i_this) {
    if (i_this->mParam == 3) {
        if (dComIfGs_isEventBit(0x1801)) {
            i_this->mParam = 0;
            i_this->mSph.OnCoSPrmBit(cCcD_CoSPrm_Set_e);
        }
        return TRUE;
    }
    if (i_this->mFramesUntilJump != 0) {
        i_this->mFramesUntilJump--;
    }
    switch(i_this->m2BB) {
        case 0:
            jbo_move(i_this);
            break;
    }
    i_this->mpMorf->play(NULL, 0, 0);
    cXyz pos(i_this->current.pos);
    pos.y += 30.0;
    i_this->mSph.SetC(pos);
    i_this->mSph.SetR(55.0);
    dComIfG_Ccsp()->Set(&i_this->mSph);
    jbo_draw_SUB(i_this);
    return TRUE;
}

/* 00000698-000006A0       .text daJBO_IsDelete__FP9jbo_class */
static BOOL daJBO_IsDelete(jbo_class*) {
    return true;
}

/* 000006A0-000006D0       .text daJBO_Delete__FP9jbo_class */
static BOOL daJBO_Delete(jbo_class* i_this) {
    dComIfG_resDelete(&i_this->mPhs, "JBO");
    return TRUE;
}

/* 000006D0-0000081C       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* i_this) {
    jbo_class* a_this = (jbo_class*)i_this;
    mDoExt_McaMorf* morf = new mDoExt_McaMorf(
        (J3DModelData *)dComIfG_getObjectRes("JBO", JBO_BMD_JH),
        /*callback1=*/ NULL,
        /*callback2=*/ NULL,
        (J3DAnmTransformKey *)dComIfG_getObjectRes("JBO", JBO_BCK_IN1),
        J3DFrameCtrl::EMode_RESET,
        0.0f,
        0,
        -1,
        1,
        /*basAnm=*/ NULL,
        0,
        /*differedDlistFlag=*/ 0x11020203
    );
    a_this->mpMorf = morf;
    if (a_this->mpMorf == NULL || a_this->mpMorf->mpModel == NULL) {
        return FALSE;
    }
    a_this->mpMorf->getModel()->setUserArea(reinterpret_cast<u32>(a_this));
    for (u16 i = 0; i < a_this->mpMorf->getModel()->getModelData()->getJointNum(); i++) {
        a_this->mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack);
    }
    return TRUE;
}

/* 0000081C-00000A90       .text daJBO_Create__FP10fopAc_ac_c */
static cPhs_State daJBO_Create(fopAc_ac_c* i_this) {
    fopAcM_SetupActor(i_this, jbo_class);
    jbo_class* a_this = (jbo_class*)i_this;
    cPhs_State state = dComIfG_resLoad(&a_this->mPhs, "JBO");
    if (state == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(i_this, &useHeapInit, 0x1c20)) {
            return cPhs_ERROR_e;
        } else {
            a_this->mParam = fopAcM_GetParam(a_this);
            if (a_this->mParam == 0xFF) {
                a_this->mParam = 0;
            }

            if (REG8_S(9) != 0) {
                a_this->mParam = REG8_S(9);
            }
            fopAcM_SetMtx(a_this, a_this->mpMorf->getModel()->getBaseTRMtx());
            a_this->attention_info.flags = 0;
            a_this->mStts.Init(0xff, 0xff, a_this);
            static dCcD_SrcSph co_sph_src = {
                // dCcD_SrcGObjInf
                {
                    /* Flags             */ 0,
                    /* SrcObjAt  Type    */ 0,
                    /* SrcObjAt  Atp     */ 0,
                    /* SrcObjAt  SPrm    */ 0,
                    /* SrcObjTg  Type    */ 0,
                    /* SrcObjTg  SPrm    */ 0,
                    /* SrcObjCo  SPrm    */ cCcD_CoSPrm_VsEnemy_e|cCcD_CoSPrm_IsOther_e|cCcD_CoSPrm_Set_e,
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
                {{
                    /* Center */ {0.0f, 0.0f, 0.0f},
                    /* Radius */ 15.0f,
                }},
            };
            a_this->mSph.Set(co_sph_src);
            a_this->mSph.SetStts(&a_this->mStts);
            if (a_this->mParam == 3) {
                fopAcM_OffStatus(a_this, fopAcStts_SHOWMAP_e);
                a_this->mSph.ClrCoSet();
            }
            if (a_this->mParam == 1) {
                J3DAnmTransform* pAnimRes = (J3DAnmTransform*) dComIfG_getObjectRes("JBO", JBO_BCK_UMARERU1);
                a_this->mpMorf->setAnm(pAnimRes, J3DFrameCtrl::EMode_NONE, 0.0, 1.0, 0.0, -1.0, NULL);
                fopAcM_seStart(a_this, JA_SE_CM_BV_BASE_POPUP, 0);
                a_this->mState = daJbo_State_SPAWN;
            }
            a_this->gbaName = 0x21;
            jbo_draw_SUB(a_this);
        }
    }
    return state;
}


static actor_method_class l_daJBO_Method = {
    (process_method_func)daJBO_Create,
    (process_method_func)daJBO_Delete,
    (process_method_func)daJBO_Execute,
    (process_method_func)daJBO_IsDelete,
    (process_method_func)daJBO_Draw,
};

actor_process_profile_definition g_profile_JBO = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_JBO,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(jbo_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_JBO,
    /* Actor SubMtd */ &l_daJBO_Method,
    /* Status       */ fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENV_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
