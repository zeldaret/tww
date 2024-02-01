//
// Generated by dtk
// Translation Unit: d_a_obj_doguu_demo.cpp
//

#include "d/actor/d_a_obj_doguu_demo.h"
#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "dolphin/types.h"
#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_mtx.h"

static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daObjDoguuD_c*)i_this)->CreateHeap();
}

BOOL daObjDoguuD_c::CreateHeap() {
    mUnusedParam = fopAcM_GetParam(this) & 0xFF;  // Im not sure why this is here, none of the other
                                                  // classes I looked at did this

    J3DModelData* modelData = (J3DModelData*)(dComIfG_getObjectRes("DoguuD", 0x04));
    JUT_ASSERT(0x65, modelData != 0);
    mpModel = mDoExt_J3DModel__create(modelData, 0x00, 0x11020203);
    if (mpModel == NULL)
        return FALSE;

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    mDoMtx_stack_c::scaleM(mScale);
    mDoMtx_copy(mDoMtx_stack_c::get(), mtx);

    mpBgW = new dBgW();

    if (mpBgW == NULL) {
        return FALSE;
    }

    if (mpBgW->Set((cBgD_t*)dComIfG_getObjectRes("DoguuD", 0x07), cBgW::MOVE_BG_e, &mtx))
        return FALSE;

    return TRUE;
}

void daObjDoguuD_c::CreateInit() {
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -30000.0f, -5000.0f, -30000.0f, 30000.0f, 40000.0f, 30000.0f);
    dComIfG_Bgsp()->Regist(mpBgW, this);
    mFlag = 1;
    set_mtx();
}

void daObjDoguuD_c::set_mtx() {
    mpModel->setBaseScale(mScale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

s32 daObjDoguuD_c::_create() {
    fopAcM_SetupActor(this, daObjDoguuD_c);
    mFlag = 0;

    s32 ret = dComIfG_resLoad(&mPhs, "DoguuD");

    if (ret == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x1460) == 0) {
            ret = cPhs_ERROR_e;
        } else {
            CreateInit();
        }
    }

    return ret;
}

static s32 daObjDoguuD_create(void* i_this) {
    return ((daObjDoguuD_c*)i_this)->_create();
}

BOOL daObjDoguuD_c::_delete() {
    if (heap != NULL && mFlag == 1)
        dComIfG_Bgsp()->Release(mpBgW);

    dComIfG_resDelete(&mPhs, "DoguuD");
    return TRUE;
}

static BOOL daObjDoguuD_Delete(void* i_this) {
    return ((daObjDoguuD_c*)i_this)->_delete();
}

BOOL daObjDoguuD_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &mTevStr);
    g_env_light.setLightTevColorType(mpModel, &mTevStr);
    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();
    return TRUE;
}

static BOOL daObjDoguuD_Draw(void* i_this) {
    return ((daObjDoguuD_c*)i_this)->_draw();
}

BOOL daObjDoguuD_c::_execute() {
    if (mDemoActorId != 0) {
        dDemo_actor_c* demoAc = dComIfGp_demo_getActor(mDemoActorId);
        if (demoAc != NULL && demoAc->checkEnable(0x10)) {
            mShape = demoAc->mShapeId;
        }
    }
    set_mtx();
    return TRUE;
}

static BOOL daObjDoguuD_Execute(void* i_this) {
    return ((daObjDoguuD_c*)i_this)->_execute();
}

static BOOL daObjDoguuD_IsDelete(void*) {
    return TRUE;
}

static actor_method_class daObj_DoguuDMethodTable = {
    (process_method_func)daObjDoguuD_create,  (process_method_func)daObjDoguuD_Delete,
    (process_method_func)daObjDoguuD_Execute, (process_method_func)daObjDoguuD_IsDelete,
    (process_method_func)daObjDoguuD_Draw,
};

actor_process_profile_definition g_profile_Obj_DoguuD = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 7,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_DoguuD,
    /* Proc SubMtd  */ &g_fpcLf_Method.mBase,
    /* Size         */ sizeof(daObjDoguuD_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x01c5,
    /* Actor SubMtd */ &daObj_DoguuDMethodTable,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};