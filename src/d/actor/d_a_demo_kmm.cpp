/**
 * d_a_demo_kmm.cpp
 * NPC - Seagull (cutscenes)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_demo_kmm.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_ext.h"
#include "d/res/res_demo_kmm.h"

const char daDemo_Kmm_c::M_arcname[] = "Demo_Kmm";

/* 00000078-00000098       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* a_this) {
    return ((daDemo_Kmm_c*)a_this)->CreateHeap();
}

/* 00000098-00000190       .text CreateHeap__12daDemo_Kmm_cFv */
BOOL daDemo_Kmm_c::CreateHeap() {
    mpMorf = new mDoExt_McaMorf((J3DModelData*)dComIfG_getObjectIDRes(M_arcname, DEMO_KMM_BMD_KA), NULL, NULL, NULL, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 0, NULL, 0, 0x11020203);
    if (mpMorf == NULL || mpMorf->getModel() == NULL) {
        return FALSE;
    }
    setAnime(DEMO_KMM_BCK_KA_WAIT1, J3DFrameCtrl::EMode_LOOP, 0.0f, 1.0f);
    return TRUE;
}

/* 00000190-00000228       .text calcMtx__12daDemo_Kmm_cFv */
void daDemo_Kmm_c::calcMtx() {
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    eyePos = current.pos;
    attention_info.position = current.pos;
}

/* 00000228-000002D0       .text setAnime__12daDemo_Kmm_cFiiff */
void daDemo_Kmm_c::setAnime(int animIdx, int loopMode, float morf, float playSpeed) {
    mpMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectIDRes(M_arcname, animIdx), loopMode, morf, playSpeed, 0.0f, -1.0f, NULL);
}

/* 000002D0-00000308       .text CreateInit__12daDemo_Kmm_cFv */
BOOL daDemo_Kmm_c::CreateInit() {
    tevStr.mRoomNo = current.roomNo;
    setAction(0);
    unk_29E = 0;
    calcMtx();
    return TRUE;
}

/* 00000308-000003A0       .text create__12daDemo_Kmm_cFv */
cPhs_State daDemo_Kmm_c::create() {
#if VERSION == DEMO
    cPhs_State ret = dComIfG_resLoad(&this->mPhase, M_arcname);
    if (ret != cPhs_COMPLEATE_e) {
        return ret;
    }
    fopAcM_SetupActor(this, daDemo_Kmm_c);
#else
    fopAcM_SetupActor(this, daDemo_Kmm_c);
    cPhs_State ret = dComIfG_resLoad(&this->mPhase, M_arcname);
    if (ret != cPhs_COMPLEATE_e) {
        return ret;
    }
#endif

    if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x5700)) {
        return cPhs_ERROR_e;
    }

    CreateInit();
    return cPhs_COMPLEATE_e;
}

/* 000003A0-000003A8       .text daDemo_Kmm_actionWait__FP12daDemo_Kmm_c */
static BOOL daDemo_Kmm_actionWait(daDemo_Kmm_c* i_this) {
    return TRUE;
}

/* 000003A8-0000040C       .text daDemo_Kmm_Draw__FP12daDemo_Kmm_c */
static BOOL daDemo_Kmm_Draw(daDemo_Kmm_c* i_this) {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &i_this->current.pos, &i_this->tevStr);
    g_env_light.setLightTevColorType(i_this->mpMorf->getModel(), &i_this->tevStr);
    i_this->mpMorf->entryDL();
    return TRUE;
}

BOOL daDemo_Kmm_c::execute() {
    typedef BOOL (*action)(daDemo_Kmm_c*);
    static action l_action[] = {
        daDemo_Kmm_actionWait,
    };

    l_action[unk_29C](this);
    calcMtx();

    if (!dDemo_setDemoData(this, dDemo_actor_c::ENABLE_TRANS_e | dDemo_actor_c::ENABLE_ROTATE_e | dDemo_actor_c::ENABLE_ANM_e | dDemo_actor_c::ENABLE_ANM_FRAME_e, mpMorf, M_arcname)) {
        mpMorf->play(&eyePos,0,0);
    }
    mpMorf->calc();
    return TRUE;
}

/* 0000040C-000004A8       .text daDemo_Kmm_Execute__FP12daDemo_Kmm_c */
static BOOL daDemo_Kmm_Execute(daDemo_Kmm_c* i_this) {
    return i_this->execute();
}

/* 000004A8-000004B0       .text daDemo_Kmm_IsDelete__FP12daDemo_Kmm_c */
static BOOL daDemo_Kmm_IsDelete(daDemo_Kmm_c*) {
    return TRUE;
}

/* 000004B0-00000500       .text daDemo_Kmm_Delete__FP12daDemo_Kmm_c */
static BOOL daDemo_Kmm_Delete(daDemo_Kmm_c* i_this) {
    dComIfG_resDelete(&i_this->mPhase, daDemo_Kmm_c::M_arcname);
    i_this->~daDemo_Kmm_c();
    return TRUE;
}

/* 00000500-00000520       .text daDemo_Kmm_Create__FP10fopAc_ac_c */
static cPhs_State daDemo_Kmm_Create(fopAc_ac_c* i_this) {
    return ((daDemo_Kmm_c*)i_this)->create();
}

static actor_method_class l_daDemo_Kmm_Method = {
    (process_method_func)daDemo_Kmm_Create,
    (process_method_func)daDemo_Kmm_Delete,
    (process_method_func)daDemo_Kmm_Execute,
    (process_method_func)daDemo_Kmm_IsDelete,
    (process_method_func)daDemo_Kmm_Draw,
};

actor_process_profile_definition g_profile_DEMO_KMM = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_DEMO_KMM,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daDemo_Kmm_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_DEMO_KMM,
    /* Actor SubMtd */ &l_daDemo_Kmm_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_6_e,
};
