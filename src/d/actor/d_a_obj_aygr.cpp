/**
 * d_a_obj_aygr.cpp
 * Object - Lookout Platform
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_aygr.h"
#include "res/Object/Aygr.h"

Mtx daObjAygr::Act_c::M_tmp_mtx;
const char daObjAygr::Act_c::M_arcname[] = "Aygr";

/* 00000078-000002A4       .text CreateHeap__Q29daObjAygr5Act_cFv */
BOOL daObjAygr::Act_c::CreateHeap() {
    J3DModelData* model_data_yagura = (J3DModelData*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_AYGR_BDL_AYGR_e);
    JUT_ASSERT(80, model_data_yagura != 0);
    mModel1 = mDoExt_J3DModel__create(model_data_yagura, 0, 0x11020203);
    if (mModel1 == NULL) {
        return FALSE;
    }
    if (prm_get_mdl()) {
        J3DModelData* model_data_hashigo = (J3DModelData*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_AYGR_BDL_AYGRH_e);
        JUT_ASSERT(89, model_data_hashigo != 0);
        mModel2 = mDoExt_J3DModel__create(model_data_hashigo, 0, 0x11020203);
        if (mModel2 == NULL) {
            return FALSE;
        }
        BOOL ok = TRUE;
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::YrotM(shape_angle.y);
        mDoMtx_stack_c::scaleM(scale.x, scale.y, scale.z);
        cMtx_copy(mDoMtx_stack_c::get(), mMtx);
        mBgw = new dBgW();
        if (mBgw == NULL ||
            mBgw->Set((cBgD_t*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_AYGR_DZB_AYGRH_e), cBgW::MOVE_BG_e, &mMtx)) {
            ok = FALSE;
        }
        if (ok != TRUE) {
            return FALSE;
        }
        field_0x30C = 1;
    } else {
        mModel2 = NULL;
        mBgw = NULL;
        field_0x30C = 0;
    }
    return TRUE;
}

/* 000002A4-00000310       .text Create__Q29daObjAygr5Act_cFv */
BOOL daObjAygr::Act_c::Create() {
    cullMtx = mModel1->getBaseTRMtx();
    init_mtx();
    fopAcM_setCullSizeBox(this, -500.0f, -100.0f, -500.0f, 500.0f, 4000.0f, 500.0f);
    return TRUE;
}

/* 00000310-000004D4       .text Mthd_Create__Q29daObjAygr5Act_cFv */
cPhs_State daObjAygr::Act_c::Mthd_Create() {
    fopAcM_ct(this, daObjAygr::Act_c);
    field_0x30C = 0;
    cPhs_State phase_state = dComIfG_resLoad(&mPhase, M_arcname);
    if (phase_state == cPhs_COMPLEATE_e) {
        phase_state = MoveBGCreate(M_arcname, dRes_INDEX_AYGR_DZB_AYGR_e, NULL, 0x85F0);
        if (mpBgW != NULL && mpBgW->ChkUsed()) {
            mpBgW->Move();
            mpBgW->SetLock();
        }
        if (prm_get_mdl()) {
            dComIfG_Bgsp()->Regist(mBgw, this);
            if (mBgw != NULL && mBgw->ChkUsed()) {
                mBgw->Move();
                mBgw->SetLock();
            }
        }
        JUT_ASSERT(183, (phase_state == cPhs_COMPLEATE_e) || (phase_state == cPhs_ERROR_e));
    }
    return phase_state;
}

/* 000004D4-000004DC       .text Delete__Q29daObjAygr5Act_cFv */
BOOL daObjAygr::Act_c::Delete() {
    return TRUE;
}

/* 000004DC-0000054C       .text Mthd_Delete__Q29daObjAygr5Act_cFv */
BOOL daObjAygr::Act_c::Mthd_Delete() {
    if (field_0x30C != 0) {
        dComIfG_Bgsp()->Release(mBgw);
    }
    BOOL result = MoveBGDelete();
    dComIfG_resDelete(&mPhase, M_arcname);
    return result;
}

/* 0000054C-000005F8       .text set_mtx__Q29daObjAygr5Act_cFv */
void daObjAygr::Act_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mModel1->setBaseTRMtx(mDoMtx_stack_c::get());
    if (prm_get_mdl()) {
        mModel2->setBaseTRMtx(mDoMtx_stack_c::get());
    }
    cMtx_copy(mDoMtx_stack_c::get(), M_tmp_mtx);
}

/* 000005F8-00000674       .text init_mtx__Q29daObjAygr5Act_cFv */
void daObjAygr::Act_c::init_mtx() {
    mModel1->setBaseScale(scale);
    if (prm_get_mdl()) {
        mModel2->setBaseScale(scale);
    }
    set_mtx();
}

/* 00000674-000006B0       .text Execute__Q29daObjAygr5Act_cFPPA3_A4_f */
BOOL daObjAygr::Act_c::Execute(Mtx** param_1) {
    set_mtx();
    *param_1 = &M_tmp_mtx;
    return TRUE;
}

/* 000006B0-0000079C       .text Draw__Q29daObjAygr5Act_cFv */
BOOL daObjAygr::Act_c::Draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mModel1, &tevStr);
    if (prm_get_mdl()) {
        g_env_light.setLightTevColorType(mModel2, &tevStr);
    }
    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mModel1);
    if (prm_get_mdl()) {
        mDoExt_modelUpdateDL(mModel2);
    }
    dComIfGd_setList();
    return TRUE;
}

namespace daObjAygr {
namespace {
/* 0000079C-000007BC       .text Mthd_Create__Q29daObjAygr26@unnamed@d_a_obj_aygr_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjAygr::Act_c*)i_this)->Mthd_Create();
}

/* 000007BC-000007DC       .text Mthd_Delete__Q29daObjAygr26@unnamed@d_a_obj_aygr_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjAygr::Act_c*)i_this)->Mthd_Delete();
}

/* 000007DC-000007FC       .text Mthd_Execute__Q29daObjAygr26@unnamed@d_a_obj_aygr_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjAygr::Act_c*)i_this)->MoveBGExecute();
}

/* 000007FC-00000828       .text Mthd_Draw__Q29daObjAygr26@unnamed@d_a_obj_aygr_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjAygr::Act_c*)i_this)->Draw();
}

/* 00000828-00000854       .text Mthd_IsDelete__Q29daObjAygr26@unnamed@d_a_obj_aygr_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return ((daObjAygr::Act_c*)i_this)->IsDelete();
}

static actor_method_class Mthd_Aygr = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjAygr

actor_process_profile_definition g_profile_Obj_Aygr = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Aygr_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjAygr::Act_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Aygr_e,
    /* Actor SubMtd */ &daObjAygr::Mthd_Aygr,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
