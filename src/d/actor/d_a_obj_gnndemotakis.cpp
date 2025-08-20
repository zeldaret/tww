/**
 * d_a_obj_gnndemotakis.cpp
 * Object - Ganondorf Fight - Background waterfalls (before fight)
 */

#include "d/actor/d_a_obj_gnndemotakis.h"
#include "d/d_com_inf_game.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

namespace {
    static const char l_arcname[] = "Gnndemotakis";
};

/* 00000078-00000098       .text solidHeapCB__15daObjGnntakis_cFP10fopAc_ac_c */
BOOL daObjGnntakis_c::solidHeapCB(fopAc_ac_c* a_this) {
    return ((daObjGnntakis_c*)a_this)->create_heap();
}

/* 00000098-000001F4       .text create_heap__15daObjGnntakis_cFv */
BOOL daObjGnntakis_c::create_heap() {
    BOOL ret = FALSE;

    J3DModelData* mdl_data = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcname, 4));
    JUT_ASSERT(0x9b, mdl_data != NULL);

    if (mdl_data != NULL) {
        mpModel = mDoExt_J3DModel__create(mdl_data, 0, 0x11020203);
        
        if (mpModel) {
            J3DAnmTextureSRTKey* btk_data = static_cast<J3DAnmTextureSRTKey*>(dComIfG_getObjectRes(l_arcname, 7));
            JUT_ASSERT(0xa2, btk_data != NULL);
            
            if (btk_data != NULL && field_0x29C.init(mdl_data, btk_data, TRUE, 0, 1.0f, 0, -1, FALSE, 0) != NULL)
                ret = TRUE;
        }
    }

    return ret;
}

/* 000001F4-00000308       .text _create__15daObjGnntakis_cFv */
cPhs_State daObjGnntakis_c::_create() {
    fopAcM_SetupActor(this, daObjGnntakis_c);

    cPhs_State ret = dComIfG_resLoad(&field_0x294, l_arcname);

    if (ret == cPhs_COMPLEATE_e) {
        ret = cPhs_ERROR_e;
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0)) {
            fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
            init_mtx();
            field_0x29C.setFrame(field_0x29C.getStartFrame());
            field_0x29C.setPlaySpeed(0.0f);
            ret = cPhs_COMPLEATE_e;
            field_0x2B0 = 0;
        }
    }

    return ret;
}

/* 000003AC-000003DC       .text _delete__15daObjGnntakis_cFv */
bool daObjGnntakis_c::_delete() {
    dComIfG_resDelete(&field_0x294, l_arcname);
    return TRUE;
}

/* 000003DC-000003FC       .text init_mtx__15daObjGnntakis_cFv */
void daObjGnntakis_c::init_mtx() {
    mpModel->setBaseScale(scale);
}

/* 000003FC-00000514       .text _execute__15daObjGnntakis_cFv */
bool daObjGnntakis_c::_execute() {
    if (strcmp(g_dComIfG_gameInfo.play.getStartStageName(), "GTower") == FALSE &&
    g_dComIfG_gameInfo.play.mEvtCtrl.runCheck() &&
    dComIfGp_evmng_startCheck("g2before") &&
    dComIfGp_demo_get() != FALSE) {
        if (!field_0x2B0 && dComIfGp_demo_get()->getFrameNoMsg() >= 0x11d9) {
            field_0x29C.setFrame(field_0x29C.getStartFrame());
            field_0x29C.setPlaySpeed(1.0f);
            field_0x2B0 = 1;
        } else if (dComIfGp_demo_get()->getFrameNoMsg() >= 0x126f) {
            fopAcM_delete(this);
        }
    }

    field_0x29C.play();
    return TRUE;
}

/* 00000514-0000058C       .text _draw__15daObjGnntakis_cFv */
bool daObjGnntakis_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG3, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    J3DModelData* mpModelData = mpModel->getModelData();
    field_0x29C.entry(mpModelData, field_0x29C.getFrame());
    mDoExt_modelUpdateDL(mpModel);
    return TRUE;
}

namespace {
/* 0000058C-000005AC       .text Mthd_Create__34@unnamed@d_a_obj_gnndemotakis_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjGnntakis_c*)i_this)->_create();
}

/* 000005AC-000005D0       .text Mthd_Delete__34@unnamed@d_a_obj_gnndemotakis_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjGnntakis_c*)i_this)->_delete();
}

/* 000005D0-000005F4       .text Mthd_Execute__34@unnamed@d_a_obj_gnndemotakis_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjGnntakis_c*)i_this)->_execute();
}

/* 000005F4-00000618       .text Mthd_Draw__34@unnamed@d_a_obj_gnndemotakis_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjGnntakis_c*)i_this)->_draw();
}

/* 00000618-00000620       .text Mthd_IsDelete__34@unnamed@d_a_obj_gnndemotakis_cpp@FPv */
BOOL Mthd_IsDelete(void*) {
    return TRUE;
}

static actor_method_class Gnntakis_Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace

actor_process_profile_definition g_profile_Obj_Gnntakis = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Gnntakis,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjGnntakis_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Gnntakis,
    /* Actor SubMtd */ &Gnntakis_Mthd_Table,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
