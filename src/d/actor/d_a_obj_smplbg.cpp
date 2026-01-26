/**
 * d_a_obj_smplbg.cpp
 * Object - Top/"head" of Tingle Tower
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_smplbg.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_com_inf_game.h"
#include "d/res/res_qtkhd.h"

const daObjSmplbg::Act_c::Attr_c daObjSmplbg::Act_c::M_attr[] = {
    /* mHeapSize     */ 0x15E0,
    /* mResName      */ "Qtkhd",
    /* mBDLFileIndex */ QTKHD_BDL_QTKHD,
    /* mDZBFileIndex */ QTKHD_DZB_QTKHD,
    /* mMoveBGProc   */ dBgS_MoveBGProc_TypicalRotY,
    /* mFlags        */ 1 | 4 | 8,
    /* mCullMinX     */ 0,
    /* mCullMinY     */ 2250,
    /* mCullMinZ     */ 0,
    /* mCullMaxX     */ 750,
    /* mCullMaxY     */ 0,
    /* mCullMaxZ     */ 0,
    /* mEyeOffset    */ 1687.0f,
};

Mtx daObjSmplbg::Act_c::M_tmp_mtx;

/* 00000078-00000144       .text CreateHeap__Q211daObjSmplbg5Act_cFv */
BOOL daObjSmplbg::Act_c::CreateHeap() {
    J3DModelData* model_data = (J3DModelData*)dComIfG_getObjectRes(attr().mResName, attr().mBDLFileIndex);
    JUT_ASSERT(0x6b, model_data != NULL);
    mpModel = mDoExt_J3DModel__create(model_data, 0x80000,0x11000022);
    return mpModel != NULL;
}

/* 00000144-0000032C       .text Create__Q211daObjSmplbg5Act_cFv */
BOOL daObjSmplbg::Act_c::Create() {
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    init_mtx();
    eyePos.y += attr().mEyeOffset;

    if(cLib_checkBit<u32>(attr().mFlags, 8)){
        fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
    }
    if(cLib_checkBit<u32>(attr().mFlags, 4)){
        fopAcM_SetCullSize(this, fopAc_CULLSPHERE_CUSTOM_e);
        fopAcM_setCullSizeSphere(this, attr().mCullMinX, attr().mCullMinY, attr().mCullMinZ, attr().mCullMaxX);
    } else{
        fopAcM_SetCullSize(this, fopAc_CULLBOX_CUSTOM_e);
        fopAcM_setCullSizeBox(this, attr().mCullMinX, attr().mCullMinY, attr().mCullMinZ, attr().mCullMaxX, attr().mCullMaxY, attr().mCullMaxZ);
    }
    return TRUE;
}

/* 0000032C-00000474       .text Mthd_Create__Q211daObjSmplbg5Act_cFv */
cPhs_State daObjSmplbg::Act_c::Mthd_Create() {
    fopAcM_SetupActor(this, Act_c);

    mType = prm_get_type();
    if(mType >= 1){
        mType = 0;
    }
    cPhs_State phase_state = dComIfG_resLoad(&mPhs, attr().mResName);
    if(phase_state == cPhs_COMPLEATE_e){
        phase_state = MoveBGCreate(attr().mResName, attr().mDZBFileIndex, attr().mMoveBGProc, attr().mHeapSize);
        JUT_ASSERT(181, (phase_state == cPhs_COMPLEATE_e) || (phase_state == cPhs_ERROR_e));
    }
    return phase_state;
}

/* 00000474-0000047C       .text Delete__Q211daObjSmplbg5Act_cFv */
BOOL daObjSmplbg::Act_c::Delete() {
    return TRUE;
}

/* 0000047C-000004D8       .text Mthd_Delete__Q211daObjSmplbg5Act_cFv */
BOOL daObjSmplbg::Act_c::Mthd_Delete() {
    BOOL result = MoveBGDelete();
    dComIfG_resDelete(&mPhs, attr().mResName);
    return result;
}

/* 000004D8-00000558       .text set_mtx__Q211daObjSmplbg5Act_cFv */
void daObjSmplbg::Act_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    cMtx_copy(mDoMtx_stack_c::get(), M_tmp_mtx);
}

/* 00000558-00000594       .text init_mtx__Q211daObjSmplbg5Act_cFv */
void daObjSmplbg::Act_c::init_mtx() {
    mpModel->setBaseScale(scale);
    set_mtx();
}

/* 00000594-0000061C       .text exec_qtkhd__Q211daObjSmplbg5Act_cFv */
void daObjSmplbg::Act_c::exec_qtkhd() {
    if(field_0x2D8 == 0){
        shape_angle.y += 0x5b;
        fopAcM_seStart(this, JA_SE_OBJ_TC_TOWER_ROUND, 0);
    }
}

/* 0000061C-000006CC       .text Execute__Q211daObjSmplbg5Act_cFPPA3_A4_f */
BOOL daObjSmplbg::Act_c::Execute(Mtx** matrix) {
    typedef void (daObjSmplbg::Act_c::*procFunc)();
    static procFunc exec_proc[] = {
        &daObjSmplbg::Act_c::exec_qtkhd,
    };
    (this->*exec_proc[mType])();

    set_mtx();
    *matrix = &M_tmp_mtx;
    return TRUE;
}

/* 000006CC-00000764       .text Draw__Q211daObjSmplbg5Act_cFv */
BOOL daObjSmplbg::Act_c::Draw() {
    int tevType;
    if (cLib_checkBit<u32>(attr().mFlags, 1)) {
        tevType = TEV_TYPE_BG0;
    } else if (cLib_checkBit<u32>(attr().mFlags, 2)) {
        tevType = TEV_TYPE_BG1;
    } else {    
        tevType = TEV_TYPE_ACTOR;
    }
    g_env_light.settingTevStruct(tevType, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mDoExt_modelUpdateDL(mpModel);
    return TRUE;
}

namespace daObjSmplbg {
namespace {
/* 00000764-00000784       .text Mthd_Create__Q211daObjSmplbg28@unnamed@d_a_obj_smplbg_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((Act_c*)i_this)->Mthd_Create();
}

/* 00000784-000007A4       .text Mthd_Delete__Q211daObjSmplbg28@unnamed@d_a_obj_smplbg_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((Act_c*)i_this)->Mthd_Delete();
}

/* 000007A4-000007C4       .text Mthd_Execute__Q211daObjSmplbg28@unnamed@d_a_obj_smplbg_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((Act_c*)i_this)->MoveBGExecute();
}

/* 000007C4-000007F0       .text Mthd_Draw__Q211daObjSmplbg28@unnamed@d_a_obj_smplbg_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((Act_c*)i_this)->Draw();
}

/* 000007F0-0000081C       .text Mthd_IsDelete__Q211daObjSmplbg28@unnamed@d_a_obj_smplbg_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return ((Act_c*)i_this)->IsDelete();
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjSmplbg

actor_process_profile_definition g_profile_Obj_Smplbg = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Smplbg,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjSmplbg::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Smplbg,
    /* Actor SubMtd */ &daObjSmplbg::Mthd_Table,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
