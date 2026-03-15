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

#define JUMP_ANIMATION_TIME 70

enum daJbo_Mode {
    daJbo_Mode_IDLE_e = 0,
    daJbo_Mode_WAIT_JUMP_e = 1,
    daJbo_Mode_SPAWN_e = 2,
};

/* 00000078-00000108       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* i_node, int i_calcTiming) {
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
void jbo_draw_SUB(jbo_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    J3DModel *model = i_this->mpMorf->getModel();
    model->setBaseScale(actor->scale);
    mDoMtx_stack_c::transS(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z);
    mDoMtx_stack_c::YrotM(actor->shape_angle.y);
    mDoMtx_stack_c::XrotM(actor->shape_angle.x);
    mDoMtx_stack_c::ZrotM(actor->shape_angle.z);
    if (i_this->mAnimationSpeed) {
        cXyz scale;
        scale.set(REG8_F(1) + 1.1F, REG8_F(2) + 1.0F, REG8_F(3) + 0.9F);
        i_this->mAnimRotation += i_this->mAnimationSpeed;
        mDoMtx_stack_c::YrotM(i_this->mAnimRotation);
        mDoMtx_stack_c::scaleM(scale);
        mDoMtx_stack_c::YrotM(-i_this->mAnimRotation);
    }
    model->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000240-000002C4       .text daJBO_Draw__FP9jbo_class */
static BOOL daJBO_Draw(jbo_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    J3DModel *model = i_this->mpMorf->getModel();
    if (i_this->mType == daJbo_Type_APPEAR_AFTER_DEKU_TREE_e)
        return TRUE;
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
    g_env_light.setLightTevColorType(model, &actor->tevStr);
    i_this->mpMorf->updateDL();
    return TRUE;
}

/* 000002C4-00000584       .text jbo_move__FP9jbo_class */
void jbo_move(jbo_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    switch (i_this->mMode) {
        case daJbo_Mode_IDLE_e: {
            if (dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK80_e) && i_this->mCoSph.ChkCoHit()) {
                J3DAnmTransform* anm = (J3DAnmTransform*)dComIfG_getObjectRes("JBO", JBO_BCK_IN1);
                i_this->mpMorf->setAnm(anm, J3DFrameCtrl::EMode_NONE, 0.0, 1.0, 0.0, -1.0, NULL);
                fopAcM_seStart(actor, JA_SE_OBJ_JFLOWER_IN, 0);
                dComIfGp_setItemMagicCount(4);
                i_this->mFramesUntilJump = JUMP_ANIMATION_TIME;
                i_this->mMode += 1;
            }
            break;
        }
        case daJbo_Mode_WAIT_JUMP_e: {
            i_this->mAnimationSpeed = JUMP_ANIMATION_TIME - i_this->mFramesUntilJump;
            i_this->mAnimationSpeed *= 200;
            if (i_this->mFramesUntilJump == 1) {
                daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
                player->onForceVomitJump();
            }
            if (dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK80000000_e)) {
                J3DAnmTransform* anm = (J3DAnmTransform*)dComIfG_getObjectRes("JBO", JBO_BCK_OUT1);
                i_this->mpMorf->setAnm(anm, J3DFrameCtrl::EMode_NONE, 0.0, 1.0, 0.0, -1.0, NULL);
                fopAcM_seStart(actor, JA_SE_OBJ_JFLOWER_OUT, 0);
                i_this->mAnimationSpeed = 0;
                i_this->mAnimRotation = 0;
                JPABaseEmitter* emitter = dComIfGp_particle_setToon(0xa110, &i_this->mParticlePos);
                if (emitter != NULL) {
                    emitter->setGlobalAlpha(100);
                }
                if (i_this->mType == daJbo_Type_UNK_2_e) {
                    i_this->m2BA = 1;
                }
                i_this->mMode = daJbo_Mode_IDLE_e;
            }
            break;
        }
        case daJbo_Mode_SPAWN_e: {
            if (i_this->mpMorf->isStop()) {
                i_this->mMode = daJbo_Mode_IDLE_e;
            }
            break;
        }
    }
}

/* 00000584-00000698       .text daJBO_Execute__FP9jbo_class */
static BOOL daJBO_Execute(jbo_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    if (i_this->mType == daJbo_Type_APPEAR_AFTER_DEKU_TREE_e) {
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1801)) {
            i_this->mType = daJbo_Type_NORMAL_e;
            i_this->mCoSph.OnCoSetBit();
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
    cXyz pos(actor->current.pos);
    pos.y += 30.0;
    i_this->mCoSph.SetC(pos);
    i_this->mCoSph.SetR(55.0);
    dComIfG_Ccsp()->Set(&i_this->mCoSph);
    jbo_draw_SUB(i_this);
    return TRUE;
}

/* 00000698-000006A0       .text daJBO_IsDelete__FP9jbo_class */
static BOOL daJBO_IsDelete(jbo_class*) {
    return true;
}

/* 000006A0-000006D0       .text daJBO_Delete__FP9jbo_class */
static BOOL daJBO_Delete(jbo_class* i_this) {
    dComIfG_resDeleteDemo(&i_this->mPhs, "JBO");
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
    if (a_this->mpMorf == NULL || a_this->mpMorf->getModel() == NULL) {
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
    #if VERSION > VERSION_DEMO
    fopAcM_ct(i_this, jbo_class);
    #endif
    jbo_class* a_this = (jbo_class*)i_this;
    cPhs_State state = dComIfG_resLoad(&a_this->mPhs, "JBO");
    if (state == cPhs_COMPLEATE_e) {
        #if VERSION == VERSION_DEMO
        fopAcM_ct(i_this, jbo_class);
        #endif
        if (!fopAcM_entrySolidHeap(i_this, &useHeapInit, 0x1c20)) {
            return cPhs_ERROR_e;
        } else {
            a_this->mType = fopAcM_GetParam(a_this);
            if (a_this->mType == 0xFF) {
                a_this->mType = daJbo_Type_NORMAL_e;
            }

            if (REG8_S(9) != 0) {
                a_this->mType = REG8_S(9);
            }
            fopAcM_SetMtx(i_this, a_this->mpMorf->getModel()->getBaseTRMtx());
            i_this->attention_info.flags = 0;
            a_this->mStts.Init(0xff, 0xff, i_this);
            static dCcD_SrcSph co_sph_src = {
                // dCcD_SrcGObjInf
                {
                    /* Flags             */ 0,
                    /* SrcObjAt  Type    */ 0,
                    /* SrcObjAt  Atp     */ 0,
                    /* SrcObjAt  SPrm    */ 0,
                    /* SrcObjTg  Type    */ 0,
                    /* SrcObjTg  SPrm    */ 0,
                    /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e,
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
            a_this->mCoSph.Set(co_sph_src);
            a_this->mCoSph.SetStts(&a_this->mStts);
            if (a_this->mType == daJbo_Type_APPEAR_AFTER_DEKU_TREE_e) {
                fopAcM_OffStatus(i_this, fopAcStts_SHOWMAP_e);
                a_this->mCoSph.ClrCoSet();
            }
            if (a_this->mType == daJbo_Type_POPS_UP_e) {
                J3DAnmTransform* pAnimRes = (J3DAnmTransform*) dComIfG_getObjectRes("JBO", JBO_BCK_UMARERU1);
                a_this->mpMorf->setAnm(pAnimRes, J3DFrameCtrl::EMode_NONE, 0.0, 1.0, 0.0, -1.0, NULL);
                fopAcM_seStart(i_this, JA_SE_CM_BV_BASE_POPUP, 0);
                a_this->mMode = daJbo_Mode_SPAWN_e;
            }
            i_this->gbaName = 0x21;
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
