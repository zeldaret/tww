//
// Generated by dtk
// Translation Unit: d_a_vrbox.cpp
//

#include "d/actor/d_a_vrbox.h"
#include "JSystem/J3DGraphBase/J3DMatBlock.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "m_Do/m_Do_mtx.h"
#include "d/d_kankyo_wether.h"

static BOOL daVrbox_color_set(vrbox_class* i_this);

/* 8015E3F0-8015E530       .text daVrbox_Draw__FP11vrbox_class */
static BOOL daVrbox_Draw(vrbox_class* i_this) {
    J3DModel* model = i_this->mpModel;
    f32 y_origin = 0.0f;
    dStage_FileList_dt_c* fili = NULL;

    daVrbox_color_set(i_this);

    if (g_env_light.mbVrboxInvisible != 0) {
        return TRUE;
    }

    s32 roomNo = dComIfGp_roomControl_getStayNo();
    if (roomNo >= 0) {
        fili = dComIfGp_roomControl_getStatusRoomDt(roomNo)->getFileListInfo();
    }

    if (fili) {
        y_origin = fili->mSeaLevel;
    }

    f32 y_offset;
    if (dComIfGd_getView()) {
        y_offset = (dComIfGd_getView()->mInvViewMtx[1][3] - y_origin) * 0.09f;
    } else {
        y_offset = 0.0f;
    }

    mDoMtx_stack_c::transS(
        dComIfGd_getView()->mInvViewMtx[0][3],
        dComIfGd_getView()->mInvViewMtx[1][3] - y_offset,
        dComIfGd_getView()->mInvViewMtx[2][3]
    );

    model->setBaseTRMtx(mDoMtx_stack_c::get());

    dComIfGd_setListSky();
    mDoExt_modelUpdateDL(model);
    dComIfGd_setList();

    return TRUE;
}

/* 8015E530-8015E6B0       .text daVrbox_color_set__FP11vrbox_class */
static BOOL daVrbox_color_set(vrbox_class* i_this) {
    if (g_env_light.mVrKasumiMaeColor.r + g_env_light.mVrKasumiMaeColor.g + g_env_light.mVrKasumiMaeColor.b +
        g_env_light.mVrSkyColor.r + g_env_light.mVrSkyColor.g + g_env_light.mVrSkyColor.b +
        g_env_light.mVrkumoColor.r + g_env_light.mVrkumoColor.g + g_env_light.mVrkumoColor.b == 0)
    {
        g_env_light.mbVrboxInvisible = 1;
        return TRUE;
    }

    g_env_light.mbVrboxInvisible = 0;

    J3DModelData* modelData = i_this->mpModel->getModelData();
    J3DMaterial* mat = modelData->getMaterialNodePointer(0);
    J3DGXColor color;

    mat->setCullMode(GX_CULL_NONE);
    mat->change();
    color.mColor.r = g_env_light.mVrKasumiMaeColor.r;
    color.mColor.g = g_env_light.mVrKasumiMaeColor.g;
    color.mColor.b = g_env_light.mVrKasumiMaeColor.b;
    color.mColor.a = 0xFF;
    mat->setTevKColor(0, &color);

    mat = modelData->getMaterialNodePointer(1);
    mat->setCullMode(GX_CULL_NONE);
    mat->change();
    color.mColor.r = g_env_light.mVrSkyColor.r;
    color.mColor.g = g_env_light.mVrSkyColor.g;
    color.mColor.b = g_env_light.mVrSkyColor.b;
    color.mColor.a = 0xFF;
    mat->setTevKColor(0, &color);

    return TRUE;
}

/* 8015E6B8-8015E864       .text dungeon_rain_proc__Fv */
static void dungeon_rain_proc() {
    dScnKy_env_light_c* env_light = &g_env_light; // Probably a fakematch
    u8 mode = 0;
    int roomNo = dComIfGp_roomControl_getStayNo();

    if (!dKy_checkEventNightStop()) {
        return;
    }

    bool inDungeon = true;
    if (strcmp(dComIfGp_getStartStageName(), "M_NewD2") == 0) {
        if (roomNo == 3) {
            mode = 1;
        }
    } else if (strcmp(dComIfGp_getStartStageName(), "M_Dra09") == 0) {
        mode = 1;
    } else if (strcmp(dComIfGp_getStartStageName(), "kinMB") == 0) {
        mode = 1;
    } else if (strcmp(dComIfGp_getStartStageName(), "kindan") == 0) {
        if (roomNo == 2 || roomNo == 13) {
            mode = 1;
        } else if (roomNo == 4) {
            mode = 2;
        }
    } else {
        inDungeon = false;
    }

    if (inDungeon) {
        if (mode == 1) { // Rain and thunder
            if (env_light->mRainCountOrig != 250) {
                dKy_change_colpat(1);
                dKyw_rain_set(250);
                env_light = &g_env_light;
                env_light->mThunderEff.mMode = 1;
            }
        } else if (mode == 2) { // Thunder, but no rain
            env_light = &g_env_light;
            if (env_light->mThunderEff.mMode == 0) {
                dKy_change_colpat(1);
                env_light->mThunderEff.mMode = 0xA;
            }
        } else { // No rain or thunder
            env_light = &g_env_light;
            if (env_light->mThunderEff.mMode != 0) {
                dKyw_rain_set(0);
                env_light->mThunderEff.mMode = 0;
            }
        }
    }
}

/* 8015E864-8015E888       .text daVrbox_Execute__FP11vrbox_class */
static BOOL daVrbox_Execute(vrbox_class* i_this) {
    dungeon_rain_proc();
    return TRUE;
}

/* 8015E888-8015E890       .text daVrbox_IsDelete__FP11vrbox_class */
static BOOL daVrbox_IsDelete(vrbox_class* i_this) {
    return TRUE;
}

/* 8015E890-8015E898       .text daVrbox_Delete__FP11vrbox_class */
static BOOL daVrbox_Delete(vrbox_class* i_this) {
    return TRUE;
}

/* 8015E898-8015E968       .text daVrbox_solidHeapCB__FP10fopAc_ac_c */
static BOOL daVrbox_solidHeapCB(fopAc_ac_c* i_actor) {
    vrbox_class* i_this = static_cast<vrbox_class*>(i_actor);

    J3DModelData* modelData = (J3DModelData*)dComIfG_getStageRes("Stage", "vr_sky.bdl");
    JUT_ASSERT(469, modelData != NULL);

    i_this->mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11020202);

    bool success = FALSE;
    if (modelData && i_this->mpModel) {
        success = TRUE;
    }
    return success;
}

/* 8015E968-8015EA14       .text daVrbox_Create__FP10fopAc_ac_c */
static cPhs_State daVrbox_Create(fopAc_ac_c* i_actor) {
    fopAcM_SetupActor(i_actor, vrbox_class);
    vrbox_class* i_this = static_cast<vrbox_class*>(i_actor);

    i_this->m29C = 0;

    cPhs_State phase_state = cPhs_COMPLEATE_e;
    if (fopAcM_entrySolidHeap(i_this, daVrbox_solidHeapCB, 0xC60)) {
        dComIfGp_onStatus(1);
        g_env_light.mbVrboxInvisible = 0;
    } else {
        phase_state = cPhs_ERROR_e;
    }

    return phase_state;
}

static actor_method_class l_daVrbox_Method = {
    (process_method_func)daVrbox_Create,
    (process_method_func)daVrbox_Delete,
    (process_method_func)daVrbox_Execute,
    (process_method_func)daVrbox_IsDelete,
    (process_method_func)daVrbox_Draw,
};

actor_process_profile_definition g_profile_VRBOX = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_VRBOX,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(vrbox_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x0007,
    /* Actor SubMtd */ &l_daVrbox_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
