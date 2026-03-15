/**
 * d_a_obj_gnndemotakie.cpp
 * Object - Ganondorf Fight - Central waterfall (after fight)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_gnndemotakie.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/res/res_gnndemotakie.h"

const char daObjGnntakie_c::M_arcname[] = "Gnndemotakie";

/* 00000078-00000098       .text solidHeapCB__15daObjGnntakie_cFP10fopAc_ac_c */
BOOL daObjGnntakie_c::solidHeapCB(fopAc_ac_c* a_this) {
    return ((daObjGnntakie_c*)a_this)->create_heap();
}

/* 00000098-000001F4       .text create_heap__15daObjGnntakie_cFv */
BOOL daObjGnntakie_c::create_heap() {
    J3DModelData* mdl_data;
    J3DAnmTextureSRTKey* btk_data;
    BOOL ret = FALSE;
    mdl_data = static_cast<J3DModelData*>(dComIfG_getObjectRes(M_arcname, GNNDEMOTAKIE_BDL_GNN_DEMO_TAKI_E));
    JUT_ASSERT(90, mdl_data != NULL);
    if (mdl_data != NULL) {
        mpModel = mDoExt_J3DModel__create(mdl_data, 0, 0x11020203);
        if (mpModel != NULL) {
            btk_data = static_cast<J3DAnmTextureSRTKey*>(dComIfG_getObjectRes(M_arcname, GNNDEMOTAKIE_BTK_GNN_DEMO_TAKI_E));
            JUT_ASSERT(97, btk_data != NULL);
            if (btk_data != NULL && mpBtkAnm.init(mdl_data, btk_data, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, FALSE)) {
                ret = TRUE;
            }
        }
    }
    return ret;
}

/* 000001F4-00000300       .text _create__15daObjGnntakie_cFv */
cPhs_State daObjGnntakie_c::_create() {
    fopAcM_ct(this, daObjGnntakie_c);
    cPhs_State state = dComIfG_resLoad(&mPhase, M_arcname);
    if (state == cPhs_COMPLEATE_e) {
        state = cPhs_ERROR_e;
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0x0)) {
            cullMtx = mpModel->getBaseTRMtx();
            init_mtx();
            mpBtkAnm.getFrameCtrl()->setFrame(mpBtkAnm.getStartFrame());
            mpBtkAnm.setPlaySpeed(1.0);
            state = cPhs_COMPLEATE_e;
        }
    }
    return state;
}

/* 000003A4-000003D4       .text _delete__15daObjGnntakie_cFv */
bool daObjGnntakie_c::_delete() {
    dComIfG_resDeleteDemo(&mPhase, M_arcname);
    return true;
}

/* 000003D4-000003F4       .text init_mtx__15daObjGnntakie_cFv */
void daObjGnntakie_c::init_mtx() {
    mpModel->setBaseScale(scale);
}

/* 000003F4-0000041C       .text _execute__15daObjGnntakie_cFv */
bool daObjGnntakie_c::_execute() {
    mpBtkAnm.play();
    return true;
}

/* 0000041C-00000494       .text _draw__15daObjGnntakie_cFv */
bool daObjGnntakie_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG3, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mpBtkAnm.entry(mpModel->getModelData());
    mDoExt_modelUpdateDL(mpModel);
    return true;
}

namespace {
/* 00000494-000004B4       .text Mthd_Create__34@unnamed@d_a_obj_gnndemotakie_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjGnntakie_c*)i_this)->_create();
}

/* 000004B4-000004D8       .text Mthd_Delete__34@unnamed@d_a_obj_gnndemotakie_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjGnntakie_c*)i_this)->_delete();
}

/* 000004D8-000004FC       .text Mthd_Execute__34@unnamed@d_a_obj_gnndemotakie_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjGnntakie_c*)i_this)->_execute();
}

/* 000004FC-00000520       .text Mthd_Draw__34@unnamed@d_a_obj_gnndemotakie_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjGnntakie_c*)i_this)->_draw();
}

/* 00000520-00000528       .text Mthd_IsDelete__34@unnamed@d_a_obj_gnndemotakie_cpp@FPv */
BOOL Mthd_IsDelete(void*) {
    return TRUE;
}

static actor_method_class Gnntakie_Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace

actor_process_profile_definition g_profile_Obj_Gnntakie = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Gnntakie,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjGnntakie_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Gnntakie,
    /* Actor SubMtd */ &Gnntakie_Mthd_Table,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
