/*
 * d_a_obj_pbka.cpp
 */

#include "d/actor/d_a_obj_pbka.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_mtx.h"
#include "d/d_procname.h"

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
        return FALSE;
    }
    return TRUE;
}

void daObjPbka_c::CreateInit() {
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -300.0f, -300.0f, -300.0f, 300.0f, 300.0f, 300.0f);
    fopAcM_setCullSizeFar(this, 1.0f);
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

s32 daObjPbka_c::_create() {
    fopAcM_SetupActor(this, daObjPbka_c);

    int phase_state = dComIfG_resLoad(&mPhase, "Pbka");
    if (phase_state == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x680) == 0) {
            phase_state =  cPhs_ERROR_e;
        } else {
            CreateInit();
        }
    }
    return phase_state;
}

static int daObjPbka_Create(void* i_this) {
    return static_cast<daObjPbka_c*>(i_this)->_create();
}

BOOL daObjPbka_c::_delete() {
    dComIfG_resDelete(&mPhase,"Pbka");
    return TRUE;
}

static BOOL daObjPbka_Delete(void* i_this) {
    static_cast<daObjPbka_c*>(i_this)->_delete();
    return TRUE;
}

BOOL daObjPbka_c::_draw() {
    dKy_tevstr_c * pTevStr;
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, pTevStr = &mTevStr);
    g_env_light.setLightTevColorType(mpModel, pTevStr);
    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();
    return TRUE;
}

static BOOL daObjPbka_Draw(void* i_this) {
    daObjPbka_c* a_this = (daObjPbka_c*)i_this;
    return a_this->_draw();
}

BOOL daObjPbka_c::_execute() {
    current.angle.y += 0x500;
    shape_angle.y = current.angle.y;
    fopAcM_seStartCurrent(this, JA_SE_OBJ_BOMB_SHOP_FAN, 0);
    set_mtx();
    return TRUE;
}

static BOOL daObjPbka_Execute(void* i_this) {
    return static_cast<daObjPbka_c*>(i_this)->_execute();
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
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 7,
    /* ListPrio     */ fpcLy_CURRENT_e,
    /* ProcName     */ PROC_Obj_Pbka,
    /* Proc SubMtd  */ &g_fpcLf_Method.mBase,
    /* Size         */ sizeof(daObjPbka_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x70,
    /* Actor SubMtd */ &daObj_PbkaMethodTable,
    /* Status       */ fopAcStts_UNK40000_e | fopAcStts_CULL_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
