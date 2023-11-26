//
// Generated by dtk
// Translation Unit: d_a_obj_cafelmp.cpp
//

#include "d/actor/d_a_obj_cafelmp.h"
#include "f_op/f_op_actor_mng.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "d/d_bg_w.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"

/* 00000078-00000098       .text CheckCreateHeap__FP10fopAc_ac_c */
BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daObjCafelmp_c*)i_this)->CreateHeap();
}

/* 00000098-0000015C       .text CreateHeap__14daObjCafelmp_cFv */
BOOL daObjCafelmp_c::CreateHeap() {
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes("Cafelmp", 0x03));
    JUT_ASSERT(0x51, modelData != 0);
    mpModel = mDoExt_J3DModel__create(modelData, 0x00, 0x11020203);
    if (!mpModel)
        return FALSE;
    else
        return TRUE;
}

/* 0000015C-000001CC       .text CreateInit__14daObjCafelmp_cFv */
void daObjCafelmp_c::CreateInit() {
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -600.0f, -0.0f, -600.0f, 600.0f, 900.0f, 600.0f);
    fopAcM_setCullSizeFar(this, 1.0f);
    set_mtx();
}

/* 000001CC-0000024C       .text set_mtx__14daObjCafelmp_cFv */
void daObjCafelmp_c::set_mtx() {
    mpModel->setBaseScale(mScale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

s32 daObjCafelmp_c::_create() {
    fopAcM_SetupActor(this, daObjCafelmp_c);

    s32 ret = dComIfG_resLoad(&mPhs, "Cafelmp");

    if (ret == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x680) == 0) {
            ret = cPhs_ERROR_e;
        } else {
            CreateInit();
        }
    }

    return ret;
}

BOOL daObjCafelmp_c::_delete() {
    dComIfG_resDelete(&mPhs, "Cafelmp");
    return true;
}

BOOL daObjCafelmp_c::_execute() {
    current.angle.y += 0xda;
    set_mtx();
    return true;
}

BOOL daObjCafelmp_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &mTevStr);
    g_env_light.setLightTevColorType(mpModel, &mTevStr);
    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();
    return true;
}

/* 0000024C-000002EC       .text daObjCafelmp_Create__FPv */
s32 daObjCafelmp_Create(void* i_this) {
    return ((daObjCafelmp_c*)i_this)->_create();
}

/* 000002EC-0000031C       .text daObjCafelmp_Delete__FPv */
BOOL daObjCafelmp_Delete(void* i_this) {
    return ((daObjCafelmp_c*)i_this)->_delete();
}

/* 0000031C-000003C0       .text daObjCafelmp_Draw__FPv */
BOOL daObjCafelmp_Draw(void* i_this) {
    return ((daObjCafelmp_c*)i_this)->_draw();
}

/* 000003C0-000003F0       .text daObjCafelmp_Execute__FPv */
BOOL daObjCafelmp_Execute(void* i_this) {
    return ((daObjCafelmp_c*)i_this)->_execute();
}

/* 000003F0-000003F8       .text daObjCafelmp_IsDelete__FPv */
BOOL daObjCafelmp_IsDelete(void* i_this) {
    return TRUE;
}

static actor_method_class l_daObjCafelmp_Method = {
    (process_method_func)daObjCafelmp_Create,
    (process_method_func)daObjCafelmp_Delete,
    (process_method_func)daObjCafelmp_Execute,
    (process_method_func)daObjCafelmp_IsDelete,
    (process_method_func)daObjCafelmp_Draw,
};

actor_process_profile_definition g_profile_Obj_Cafelmp = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 7,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Cafelmp,
    /* Proc SubMtd  */ &g_fpcLf_Method.mBase,
    /* Size         */ sizeof(daObjCafelmp_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x0077,
    /* Actor SubMtd */ &l_daObjCafelmp_Method,
    /* Status       */ fopAcStts_UNK40000_e | fopAcStts_CULL_e | fopAcStts_NOCULLEXEC_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
