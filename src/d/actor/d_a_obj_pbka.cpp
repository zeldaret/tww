/*
 * d_a_obj_pbka.cpp
 */

#include "d/actor/d_a_obj_pbka.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_mtx.h"
#include "d/d_procname.h"

BOOL daObjPbka_c::_draw() {
    dKy_tevstr_c * pTevStr;
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, pTevStr = &mTevStr);
    g_env_light.setLightTevColorType(mpModel, pTevStr);
    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();
    return true;
}

static int CheckCreateHeap(fopAc_ac_c* i_this) {
    daObjPbka_c* a_this = (daObjPbka_c*)i_this;
    return a_this->CreateHeap();
}

/* 00000098-0000015C       .text CreateHeap__11daObjPbka_cFv */
BOOL daObjPbka_c::CreateHeap() {
    J3DModelData *modelData = (J3DModelData *)dComIfG_getObjectRes("Pbka", 3);
    JUT_ASSERT(0x51, modelData != 0);
    mpModel = mDoExt_J3DModel__create(modelData,0,0x11020203);
    if(mpModel == NULL) {
        return false;
    }
    return TRUE;
}

void daObjPbka_c::CreateInit() {
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -300.0f, -300.0f, -300.0f, 300.0f, 300.0f, 300.0f);
    mCullSizeFar = 1.0f;
    set_mtx();
}

void daObjPbka_c::set_mtx() {
    J3DModel* model;
    model = mpModel;
    model->mBaseScale.x = mScale.x;
    model->mBaseScale.y = mScale.y;
    model->mBaseScale.z = mScale.z;
    mDoMtx_trans(mDoMtx_stack_c::get(), current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_YrotM(mDoMtx_stack_c::get(), current.angle.y);
    mDoMtx_copy(mDoMtx_stack_c::get(), mpModel->mBaseTransformMtx);
}

static cPhs__Step daObjPbka_Create(void* i_this) {
    int cPhsStep;
    daObjPbka_c* a_this = (daObjPbka_c*)i_this;
    fopAcM_SetupActor(a_this, daObjPbka_c);

    cPhsStep = dComIfG_resLoad(&a_this->mPhase, "Pbka");
    if (cPhsStep == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(a_this, CheckCreateHeap, 0x680) == 0) {
            cPhsStep =  cPhs_ERROR_e;
        } else {
            a_this->CreateInit();
        }
    }
    return (cPhs__Step)cPhsStep;
}

static BOOL daObjPbka_Delete(void* i_this) {
    daObjPbka_c* a_this = (daObjPbka_c*)i_this;
    dComIfG_resDelete(&a_this->mPhase,"Pbka");
    return TRUE;
}

static BOOL daObjPbka_Draw(void* i_this) {
    daObjPbka_c* a_this = (daObjPbka_c*)i_this;
    return a_this->_draw();
}

static BOOL daObjPbka_Execute(void* i_this) {
    daObjPbka_c* a_this = (daObjPbka_c*)i_this;
    a_this->current.angle.y += 0x500;
    a_this->shape_angle.y = a_this->current.angle.y;
    fopAcM_seStartCurrent(a_this, JA_SE_OBJ_BOMB_SHOP_FAN, 0);
    a_this->set_mtx();
    return TRUE;
}

static BOOL daObjPbka_IsDelete(void*) {
    return TRUE;
}

static actor_method_class daObj_PbkaMethodTable = {
    (process_method_func)daObjPbka_Create,
    (process_method_func)daObjPbka_Delete,
    (process_method_func)daObjPbka_Execute,
    (process_method_func)daObjPbka_IsDelete,
    (process_method_func)daObjPbka_Draw,
};

actor_process_profile_definition g_profile_Obj_Pbka = {
    fpcLy_CURRENT_e,
    7,
    fpcLy_CURRENT_e,
    PROC_Obj_Pbka,
    &g_fpcLf_Method.mBase,
    sizeof(daObjPbka_c),
    0,
    0,
    &g_fopAc_Method.base,
    0x70,
    &daObj_PbkaMethodTable,
    fopAcStts_UNK40000_e | fopAcStts_CULL_e,
    fopAc_ACTOR_e,
    fopAc_CULLBOX_CUSTOM_e,
};
