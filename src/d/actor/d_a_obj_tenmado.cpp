/**
 * d_a_obj_tenmado.cpp
 * Object - Earth Temple - Doors blocking ceiling light beam
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_tenmado.h"
#include "d/res/res_tenmado.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_com_inf_game.h"
#include "f_op/f_op_actor_mng.h"

Mtx daObjTenmado::Act_c::M_tmp_mtx;
const char daObjTenmado::Act_c::M_arcname[] = "Tenmado";

/* 00000078-000001B4       .text CreateHeap__Q212daObjTenmado5Act_cFv */
BOOL daObjTenmado::Act_c::CreateHeap() {
    J3DModelData* model_data_l = (J3DModelData*)dComIfG_getObjectRes(M_arcname, TENMADO_BDL_MMADOL);
    JUT_ASSERT(85, model_data_l != NULL);

    mModel1 = mDoExt_J3DModel__create(model_data_l, 0, 0x11020203);
    if (mModel1 == NULL) {
        return FALSE;
    }

    J3DModelData* model_data_r = (J3DModelData*)dComIfG_getObjectRes(M_arcname, TENMADO_BDL_MMADOR);
    JUT_ASSERT(94, model_data_r != NULL);

    mModel2 = mDoExt_J3DModel__create(model_data_r, 0, 0x11020203);
    if (mModel2 == NULL) {
        return FALSE;
    }
    return TRUE;
}

/* 000001B4-0000029C       .text Create__Q212daObjTenmado5Act_cFv */
BOOL daObjTenmado::Act_c::Create() {
    fopAcM_SetMtx(this, mModel1->getBaseTRMtx());
    init_mtx();
    fopAcM_setCullSizeBox(this, -500.0f, -500.0f, -500.0f, 500.0f, 500.0f, 500.0f);
    if (fopAcM_isSwitch(this, prm_get_swSave())) {
        fopAcM_onSwitch(this, prm_get_swSave2());
        m2C8 = 200.0f;
        m2CC = 3;
    } else {
        m2C8 = 0.0f;
        m2CC = 0;
    }
    return TRUE;
}

/* 0000029C-00000394       .text Mthd_Create__Q212daObjTenmado5Act_cFv */
cPhs_State daObjTenmado::Act_c::Mthd_Create() {
    cPhs_State phase_state;

    fopAcM_SetupActor(this, daObjTenmado::Act_c);

    phase_state = dComIfG_resLoad(&mPhase, M_arcname);
    if (phase_state == cPhs_COMPLEATE_e) {
        phase_state = MoveBGCreate(M_arcname, TENMADO_DZB_MMADO, NULL, 0xF00);
        JUT_ASSERT(146, (phase_state == cPhs_COMPLEATE_e) || (phase_state == cPhs_ERROR_e))
    }
    return phase_state;
}

/* 00000394-0000039C       .text Delete__Q212daObjTenmado5Act_cFv */
BOOL daObjTenmado::Act_c::Delete() {
    return TRUE;
}

/* 0000039C-000003E8       .text Mthd_Delete__Q212daObjTenmado5Act_cFv */
BOOL daObjTenmado::Act_c::Mthd_Delete() {
    BOOL ret = MoveBGDelete();
    dComIfG_resDeleteDemo(&mPhase, M_arcname);
    return ret;
}

/* 000003E8-000004D8       .text set_mtx__Q212daObjTenmado5Act_cFv */
void daObjTenmado::Act_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
    cMtx_copy(mDoMtx_stack_c::get(), M_tmp_mtx);
    mDoMtx_stack_c::transM(-m2C8, 0.0f, 0.0f);
    mModel1->setBaseTRMtx(mDoMtx_stack_c::get());
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
    mDoMtx_stack_c::transM(m2C8, 0.0f, 0.0f);
    mModel2->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 000004D8-00000530       .text init_mtx__Q212daObjTenmado5Act_cFv */
void daObjTenmado::Act_c::init_mtx() {
    mModel1->setBaseScale(scale);
    mModel2->setBaseScale(scale);
    set_mtx();
}

/* 00000530-00000694       .text Execute__Q212daObjTenmado5Act_cFPPA3_A4_f */
BOOL daObjTenmado::Act_c::Execute(Mtx** mtx) {
    switch (m2CC) {
    case 0:
        if (fopAcM_isSwitch(this, prm_get_swSave())) {
            m2CC = 1;
        }
        break;

    case 1:
        fopAcM_seStartCurrent(this, JA_SE_OBJ_TENMADO_SHTR_OP, 0);
        m2CC = 2;
        break;

    case 2:
        m2C8 += 1.0f;
        if (m2C8 >= 100.0f) {
            m2C8 = 100.0f;
            m2CC = 3;
        } else if (m2C8 >= 80.0f) {
            fopAcM_onSwitch(this, prm_get_swSave2());
        }
        break;

    case 3:
        break;
    }

    set_mtx();
    *mtx = &M_tmp_mtx;
    return TRUE;
}

/* 00000694-00000750       .text Draw__Q212daObjTenmado5Act_cFv */
BOOL daObjTenmado::Act_c::Draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mModel1, &tevStr);
    g_env_light.setLightTevColorType(mModel2, &tevStr);
    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mModel1);
    mDoExt_modelUpdateDL(mModel2);
    dComIfGd_setList();
    return TRUE;
}

namespace daObjTenmado {
namespace {
/* 00000750-00000770       .text Mthd_Create__Q212daObjTenmado29@unnamed@d_a_obj_tenmado_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjTenmado::Act_c*)i_this)->Mthd_Create();
}

/* 00000770-00000790       .text Mthd_Delete__Q212daObjTenmado29@unnamed@d_a_obj_tenmado_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjTenmado::Act_c*)i_this)->Mthd_Delete();
}

/* 00000790-000007B0       .text Mthd_Execute__Q212daObjTenmado29@unnamed@d_a_obj_tenmado_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjTenmado::Act_c*)i_this)->MoveBGExecute();
}

/* 000007B0-000007DC       .text Mthd_Draw__Q212daObjTenmado29@unnamed@d_a_obj_tenmado_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjTenmado::Act_c*)i_this)->Draw();
}

/* 000007DC-00000808       .text Mthd_IsDelete__Q212daObjTenmado29@unnamed@d_a_obj_tenmado_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return ((daObjTenmado::Act_c*)i_this)->IsDelete();
}

static actor_method_class Mthd_Tenmado = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjTenmado

actor_process_profile_definition g_profile_Obj_Tenmado = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Tenmado,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjTenmado::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Tenmado,
    /* Actor SubMtd */ &daObjTenmado::Mthd_Tenmado,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
