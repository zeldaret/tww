/**
 * d_a_demo_dk.cpp
 * NPC - Helmaroc King (Forsaken Fortress 1 exterior)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_demo_dk.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_ext.h"
#include "d/res/res_demo_dk.h"

/* 00000078-000000E8       .text daDEMO_DK_Draw__FP13demo_dk_class */
static BOOL daDEMO_DK_Draw(demo_dk_class* i_this) {
    J3DModel* model = i_this->mpMorf->getModel();

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->actor.current.pos, &i_this->actor.tevStr);
    g_env_light.setLightTevColorType(model, &i_this->actor.tevStr);
    i_this->mpMorf->updateDL();
    return TRUE;
}

/* 000000E8-00000210       .text anm_init__FP13demo_dk_classifUcfi */
void anm_init(demo_dk_class* i_this, int bckAnmIdx, float morf, unsigned char loopMode, float playSpeed, int soundIdx) {
    if (soundIdx >= 0) {
        i_this->mpMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("DEMO_DK", bckAnmIdx), loopMode, morf, playSpeed, 0.0f, -1.0f, (J3DAnmTransform*)dComIfG_getObjectRes("DEMO_DK", soundIdx));
    } else {
        i_this->mpMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("DEMO_DK", bckAnmIdx), loopMode, morf, playSpeed, 0.0f, -1.0f, NULL);
    }
}

/* 00000210-000002EC       .text mode_wait__FP13demo_dk_class */
void mode_wait(demo_dk_class* i_this) {
    if (i_this->mpMorf->isStop()) {
        f32 tmp = 0.099999995f;

        if (i_this->unk_2C0 > 0) {
            i_this->unk_2C0--;
        }

        if (i_this->unk_2C0 == 0 && cM_rnd() < tmp) {
            anm_init(i_this, DEMO_DK_BCK_DK_L_AKUBI1, 5.0f, 0, 1.0f, 0);
            i_this->unk_2B6 = 1;
        } else {
            anm_init(i_this, DEMO_DK_BCK_DK_L_WAIT1, 0.0f, 0, 1.0f, 0);
        }
    }
}

/* 000002EC-00000378       .text mode_akubi__FP13demo_dk_class */
void mode_akubi(demo_dk_class* i_this) {
    if (i_this->mpMorf->isStop()) {
        anm_init(i_this, DEMO_DK_BCK_DK_L_WAIT1, 5.0f, 0, 2.0f, 0);
        i_this->unk_2C0 = 3;
        i_this->unk_2B6 = 0;
    }
}

/* 00000378-000004C0       .text daDEMO_DK_Execute__FP13demo_dk_class */
static BOOL daDEMO_DK_Execute(demo_dk_class* i_this) {
    for (s32 i = 0; i < 2; i++) {
        if (i_this->unk_2BC[i] != 0) {
            i_this->unk_2BC[i]--;
        }
    }

    switch (i_this->unk_2B6) {
        case 0:
            mode_wait(i_this);
            break;
            
        case 1:
            mode_akubi(i_this);
            break;
    }

    i_this->actor.scale.x = 1.0f;
    i_this->actor.scale.z = i_this->actor.scale.y = i_this->actor.scale.x;
    i_this->actor.current.pos.y = i_this->unk_2C4.y;
    fopAcM_setCullSizeFar(&i_this->actor, 10.0f);

    i_this->mpMorf->play(NULL, 0, 0);

    J3DModel* model = i_this->mpMorf->getModel();

    mDoMtx_stack_c::transS(i_this->actor.current.pos.x, i_this->actor.current.pos.y, i_this->actor.current.pos.z);
    mDoMtx_stack_c::YrotM(i_this->actor.current.angle.y);
    mDoMtx_stack_c::XrotM(i_this->actor.current.angle.x);
    mDoMtx_stack_c::ZrotM(i_this->actor.current.angle.z);

    model->setBaseScale(i_this->actor.scale);
    model->setBaseTRMtx(mDoMtx_stack_c::get());
    return TRUE;
}

/* 000004C0-000004C8       .text daDEMO_DK_IsDelete__FP13demo_dk_class */
static BOOL daDEMO_DK_IsDelete(demo_dk_class*) {
    return TRUE;
}

/* 000004C8-000004F8       .text daDEMO_DK_Delete__FP13demo_dk_class */
static BOOL daDEMO_DK_Delete(demo_dk_class* i_this) {
    dComIfG_resDeleteDemo(&i_this->mPhase, "DEMO_DK");
    return TRUE;
}

/* 000004F8-000005FC       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* a_this) {
    demo_dk_class* i_this = (demo_dk_class*)a_this;

    i_this->mpMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("DEMO_DK", DEMO_DK_BMD_DK_L),
        NULL, NULL, 
        (J3DAnmTransform*)dComIfG_getObjectRes("DEMO_DK", DEMO_DK_BCK_DK_L_WAIT1),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, NULL, 0, 0x11020203);
    
    if (i_this->mpMorf == NULL || i_this->mpMorf->mpModel == NULL) {
        return FALSE;
    }
    return TRUE;
}

/* 000005FC-00000714       .text daDEMO_DK_Create__FP10fopAc_ac_c */
static cPhs_State daDEMO_DK_Create(fopAc_ac_c* a_this) {
    demo_dk_class* i_this = (demo_dk_class*)a_this;
    
    fopAcM_SetupActor(&i_this->actor, demo_dk_class);

    cPhs_State ret = dComIfG_resLoad(&i_this->mPhase, "DEMO_DK");
    if (ret == cPhs_COMPLEATE_e) {
        i_this->unk_2C4 = a_this->current.pos;
        if (!fopAcM_entrySolidHeap(a_this, useHeapInit, 0x6000)) {
            return cPhs_ERROR_e;
        }

        fopAcM_SetMtx(a_this, i_this->mpMorf->getModel()->getBaseTRMtx());
        fopAcM_SetMin(a_this, -1000.0f, -1000.0f, -1000.0f);
        fopAcM_SetMax(a_this, 1000.0f, 1000.0f, 1000.0f);

        a_this->attention_info.flags = 0;
        a_this->scale.x = 1.0f;
        a_this->scale.y = 1.0f;
        a_this->scale.z = 1.0f;
        anm_init(i_this, DEMO_DK_BCK_DK_L_WAIT1, 0.0f, 0, 1.0f, 0);
    }
    return ret;
}

static actor_method_class l_daDEMO_DK_Method = {
    (process_method_func)daDEMO_DK_Create,
    (process_method_func)daDEMO_DK_Delete,
    (process_method_func)daDEMO_DK_Execute,
    (process_method_func)daDEMO_DK_IsDelete,
    (process_method_func)daDEMO_DK_Draw,
};

actor_process_profile_definition g_profile_DEMO_DK = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_DEMO_DK,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(demo_dk_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_DEMO_DK,
    /* Actor SubMtd */ &l_daDEMO_DK_Method,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENV_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
