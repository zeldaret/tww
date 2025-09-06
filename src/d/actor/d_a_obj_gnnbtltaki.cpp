/**
 * d_a_obj_gnnbtltaki.cpp
 * Object - Ganondorf Fight - Background waterfalls (during fight)
 */
#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_gnnbtltaki.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/res/res_kamome.h"

const char daObjGnnbtaki_c::M_arcname[] = "Gnnbtltaki";

/* 00000078-00000098       .text solidHeapCB__15daObjGnnbtaki_cFP10fopAc_ac_c */
BOOL daObjGnnbtaki_c::solidHeapCB(fopAc_ac_c *i_this) {
    daObjGnnbtaki_c *a_this = (daObjGnnbtaki_c *) i_this;
    return a_this->create_heap();
}

/* 00000098-000001F4       .text create_heap__15daObjGnnbtaki_cFv */
BOOL daObjGnnbtaki_c::create_heap() {
#if VERSION == VERSION_DEMO
    J3DModelData* mdl_data;
    J3DAnmTextureSRTKey* btk_data;
    BOOL ret = FALSE;
    mdl_data = (J3DModelData*)dComIfG_getObjectRes(M_arcname, 4);
#else
    BOOL ret = FALSE;
    J3DModelData *mdl_data =  static_cast<J3DModelData*>(dComIfG_getObjectRes(M_arcname, 4));
#endif
    JUT_ASSERT(0x5A, mdl_data != NULL);
    if (mdl_data != NULL) {
        mJ3DModel = mDoExt_J3DModel__create(mdl_data, 0, 0x11020203);
        if (mJ3DModel != NULL) {
#if VERSION == VERSION_DEMO
            btk_data = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes(M_arcname, 7);
#else
            J3DAnmTextureSRTKey *btk_data = static_cast<J3DAnmTextureSRTKey*>(dComIfG_getObjectRes(M_arcname, 7));
#endif
            JUT_ASSERT(0x61, btk_data != NULL);
            if (btk_data != NULL) {
                if (mBtkAnm.init(mdl_data, btk_data, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0, 0, -1, false, FALSE)) {
                    ret = TRUE;
                }
            }
        }
    }
    return ret;
}

/* 000001F4-00000348       .text _create__15daObjGnnbtaki_cFv */
cPhs_State daObjGnnbtaki_c::_create() {
    fopAcM_SetupActor(this, daObjGnnbtaki_c);
    cPhs_State state = dComIfG_resLoad(&mPhase, M_arcname);
    if (state == cPhs_COMPLEATE_e) {
        state = cPhs_ERROR_e;
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0)) {
            field_0x2B1 = base.mParameters & 0xF;
            if (field_0x2B1 == 0xF) {
                field_0x2B1 = 0;
            }
            cullMtx = mJ3DModel->getBaseTRMtx();
            init_mtx();
            mBtkAnm.getFrameCtrl()->setFrame(mBtkAnm.getStartFrame());
            if (field_0x2B1 == 1) {
                mBtkAnm.setPlaySpeed(0.0);
                field_0x2B0 = 0;
            } else {
                mBtkAnm.setPlaySpeed(1.0);
                field_0x2B0 = 1;
            }
            state = cPhs_COMPLEATE_e;
        }
    }
    return state;
}

/* 000003EC-0000041C       .text _delete__15daObjGnnbtaki_cFv */
bool daObjGnnbtaki_c::_delete() {
#if VERSION == VERSION_DEMO
    dComIfG_deleteObjectRes(M_arcname);
#else
    dComIfG_resDelete(&mPhase, M_arcname);
#endif
    return true;
}

/* 0000041C-0000043C       .text init_mtx__15daObjGnnbtaki_cFv */
void daObjGnnbtaki_c::init_mtx() {
    mJ3DModel->setBaseScale(scale);
}

/* 0000043C-00000548       .text _execute__15daObjGnnbtaki_cFv */
bool daObjGnnbtaki_c::_execute() {
    if (field_0x2B1 == 1 &&
        !strcmp(dComIfGp_getStartStageName(), "GTower") &&
        dComIfGp_event_runCheck() != FALSE &&
        dComIfGp_evmng_startCheck("g2before") &&
        dComIfGp_demo_get() != NULL &&
        field_0x2B0 == 0 &&
        dComIfGp_demo_get()->getFrameNoMsg() >= 0x126F) {
        f32 startFrame = mBtkAnm.getStartFrame();
        mBtkAnm.setFrame(startFrame);
        mBtkAnm.setPlaySpeed(1.0f);
        field_0x2B0 = 1;
    }
    mBtkAnm.play();
    return true;
}

/* 00000548-000005CC       .text _draw__15daObjGnnbtaki_cFv */
bool daObjGnnbtaki_c::_draw() {
    if (field_0x2B0 != NULL) {
        g_env_light.settingTevStruct(TEV_TYPE_BG3, &current.pos, &tevStr);
        g_env_light.setLightTevColorType(mJ3DModel, &tevStr);
        mBtkAnm.entry(mJ3DModel->getModelData());
        mDoExt_modelUpdateDL(mJ3DModel);
    }
    return true;
}

namespace {
    /* 000005CC-000005EC       .text Mthd_Create__32@unnamed@d_a_obj_gnnbtltaki_cpp@FPv */
    cPhs_State Mthd_Create(void *i_this) {
        return ((daObjGnnbtaki_c *) i_this)->_create();
    }

    /* 000005EC-00000610       .text Mthd_Delete__32@unnamed@d_a_obj_gnnbtltaki_cpp@FPv */
    BOOL Mthd_Delete(void *i_this) {
        return ((daObjGnnbtaki_c *) i_this)->_delete();
    }

    /* 00000610-00000634       .text Mthd_Execute__32@unnamed@d_a_obj_gnnbtltaki_cpp@FPv */
    BOOL Mthd_Execute(void *i_this) {
        return ((daObjGnnbtaki_c *) i_this)->_execute();
    }

    /* 00000634-00000658       .text Mthd_Draw__32@unnamed@d_a_obj_gnnbtltaki_cpp@FPv */
    BOOL Mthd_Draw(void *i_this) {
        return ((daObjGnnbtaki_c *) i_this)->_draw();
    }

    /* 00000658-00000660       .text Mthd_IsDelete__32@unnamed@d_a_obj_gnnbtltaki_cpp@FPv */
    BOOL Mthd_IsDelete(void *) {
        return TRUE;
    }

    static actor_method_class Gnnbtaki_Mthd_Table = {
        (process_method_func) Mthd_Create,
        (process_method_func) Mthd_Delete,
        (process_method_func) Mthd_Execute,
        (process_method_func) Mthd_IsDelete,
        (process_method_func) Mthd_Draw,
    };
}; // namespace

actor_process_profile_definition g_profile_Obj_Gnnbtaki = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Gnnbtaki,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjGnnbtaki_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Gnnbtaki,
    /* Actor SubMtd */ &Gnnbtaki_Mthd_Table,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
