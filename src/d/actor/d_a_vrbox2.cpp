//
// Generated by dtk
// Translation Unit: d_a_vrbox2.cpp
//

#include "d/actor/d_a_vrbox2.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_camera.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_kankyo_rain.h"
#include "d/d_kankyo_wether.h"
#include "m_Do/m_Do_mtx.h"
#include "JSystem/J3DGraphBase/J3DMatBlock.h"
#include "JSystem/J3DGraphBase/J3DMaterial.h"

/* 8015EA14-8015EA5C       .text texScrollCheck__FRf */
void texScrollCheck(float& v) {
    while (v < 0.0f)
        v += 1.0f;
    while (v > 1.0f)
        v -= 1.0f;
}

BOOL daVrbox2_color_set(vrbox2_class*);

/* 8015EA5C-8015EC30       .text daVrbox2_Draw__FP12vrbox2_class */
static BOOL daVrbox2_Draw(vrbox2_class* i_this) {
    J3DModel * pBackCloud = i_this->mpBackCloud;
    J3DModel * pKasumiMae = i_this->mpKasumiMae;
    J3DModel * pUsoUmi = i_this->mpUsoUmi;
    f32 y_origin = 0.0f;
    dStage_FileList_dt_c* fili = NULL;

    daVrbox2_color_set(i_this);

    if (g_env_light.mVrKasumiMaeColor.r + g_env_light.mVrKasumiMaeColor.g + g_env_light.mVrKasumiMaeColor.b +
        g_env_light.mVrSkyColor.r + g_env_light.mVrSkyColor.g + g_env_light.mVrSkyColor.b +
        g_env_light.mVrkumoColor.r + g_env_light.mVrkumoColor.g + g_env_light.mVrkumoColor.b == 0)
    {
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

    dComIfGd_setListSky();

    if (pUsoUmi != NULL) {
        pUsoUmi->setBaseTRMtx(mDoMtx_stack_c::get());
        mDoExt_modelUpdateDL(pUsoUmi);
    }

    if (pKasumiMae != NULL) {
        pKasumiMae->setBaseTRMtx(mDoMtx_stack_c::get());
        mDoExt_modelUpdateDL(pKasumiMae);
    }

    mDoMtx_stack_c::transM(0.0f, 100.0f, 0.0f);
    pBackCloud->setBaseTRMtx(mDoMtx_stack_c::get());
    mDoExt_modelUpdateDL(pBackCloud);

    dComIfGd_setList();

    return TRUE;
}

J3DZModeInfo l_zmodeInfo = { GX_FALSE, GX_LEQUAL, GX_FALSE };

/* 8015EC30-8015F368       .text daVrbox2_color_set__FP12vrbox2_class */
BOOL daVrbox2_color_set(vrbox2_class* i_this) {
    camera_class * pCamera;
    cXyz eyePosXZ;
    cXyz centerPosXZ;
    cXyz lookDirXZ;
    cXyz windNrmVec;
    GXColor k0;
    GXColorS10 c0;
    cXyz * windVec;
    J3DModelData * modelData;
    J3DMaterial * mat;
    J3DTexMtx * mtx;
    f32 windPow;
    f32 windDirView;
    f32 scrollSpeed;

    if (g_env_light.mVrKasumiMaeColor.r + g_env_light.mVrKasumiMaeColor.g + g_env_light.mVrKasumiMaeColor.b +
        g_env_light.mVrSkyColor.r + g_env_light.mVrSkyColor.g + g_env_light.mVrSkyColor.b +
        g_env_light.mVrkumoColor.r + g_env_light.mVrkumoColor.g + g_env_light.mVrkumoColor.b == 0)
    {
        return TRUE;
    }

    pCamera = (camera_class*)dComIfGp_getCamera(0);
    windVec = dKyw_get_wind_vec();
    windPow = dKyw_get_wind_pow();
    windNrmVec = *windVec;

    if (dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) == dStageType_MISC_e) {
#if VERSION == VERSION_DEMO
        int windX;
        int windY;
        windX = g_env_light.mWind.mTactWindAngleX;
        windY = g_env_light.mWind.mTactWindAngleY;
#else
        s16 stageWindY = 0;
        if (strcmp(dComIfGp_getStartStageName(), "LinkRM") == 0)
            stageWindY = 0x4000;
        else if (strcmp(dComIfGp_getStartStageName(), "Orichh") == 0)
            stageWindY = -0x4000;
        else if (strcmp(dComIfGp_getStartStageName(), "Ojhous2") == 0)
            stageWindY = 0x7fff;
        else if (strcmp(dComIfGp_getStartStageName(), "Omasao") == 0)
            stageWindY = -0x4000;
        else if (strcmp(dComIfGp_getStartStageName(), "Onobuta") == 0)
            stageWindY = 0x4000;

        s16 windY_s16; // Fakematch?
        int windX;
        int windY;
        if (dComIfGs_getWindX() == -1 && dComIfGs_getWindY() == -1) {
            windX = 0;
            windY_s16 = 0;
        } else {
            windX = g_env_light.mWind.mTactWindAngleX;
            windY_s16 = g_env_light.mWind.mTactWindAngleY;
        }

        windY_s16 += stageWindY;
        windY = windY_s16;
#endif

        windNrmVec.x = cM_scos(windX) * cM_scos(windY);
        windNrmVec.y = cM_ssin(windX);
        windNrmVec.z = cM_scos(windX) * cM_ssin(windY);
        windPow = 0.6f;
    }

    eyePosXZ = pCamera->mLookat.mEye;
    centerPosXZ = pCamera->mLookat.mCenter;
    eyePosXZ.y = 0.0f;
    centerPosXZ.y = 0.0f;

    dKyr_get_vectle_calc(&eyePosXZ, &centerPosXZ, &lookDirXZ);
    windDirView = cM3d_VectorProduct2d(0.0f, 0.0f, -windNrmVec.x, -windNrmVec.z, lookDirXZ.x, lookDirXZ.z) * 0.0005f;
    scrollSpeed = windDirView * windPow;
    if (strcmp(dComIfGp_getStartStageName(), "M_DragB") == 0)
        scrollSpeed = -0.0004f;

    modelData = i_this->mpBackCloud->getModelData();
    mat = modelData->getMaterialNodePointer(0);
    mat->setCullMode(GX_CULL_NONE);
    mat->getZMode()->setZModeInfo(l_zmodeInfo);
    mat->change();

    mtx = mat->getTexMtx(0);
    mtx->getTexMtxInfo().mSRT.mTranslationX += scrollSpeed;
    texScrollCheck(mtx->getTexMtxInfo().mSRT.mTranslationX);
    mtx = mat->getTexMtx(1);
    mtx->getTexMtxInfo().mSRT.mTranslationX += scrollSpeed;
    texScrollCheck(mtx->getTexMtxInfo().mSRT.mTranslationX);

    k0.r = g_env_light.mVrkumoColor.r;
    k0.g = g_env_light.mVrkumoColor.g;
    k0.b = g_env_light.mVrkumoColor.b;
    k0.a = 0xFF;
    mat->setTevKColor(0, (J3DGXColor*)&k0);

    mat = modelData->getMaterialNodePointer(1);
    mat->setCullMode(GX_CULL_NONE);
    mat->getZMode()->setZModeInfo(l_zmodeInfo);
    mat->change();

    mtx = mat->getTexMtx(0);
    mtx->getTexMtxInfo().mSRT.mTranslationX += scrollSpeed * 0.8f;
    texScrollCheck(mtx->getTexMtxInfo().mSRT.mTranslationX);
    mtx = mat->getTexMtx(1);
    mtx->getTexMtxInfo().mSRT.mTranslationX += scrollSpeed * 0.8f;
    texScrollCheck(mtx->getTexMtxInfo().mSRT.mTranslationX);
    mat->setTevKColor(0, (J3DGXColor*)&k0);

    mat = modelData->getMaterialNodePointer(2);
    mat->setCullMode(GX_CULL_NONE);
    mat->getZMode()->setZModeInfo(l_zmodeInfo);
    mat->change();

    mtx = mat->getTexMtx(0);
    mtx->getTexMtxInfo().mSRT.mTranslationX += scrollSpeed * 0.6f;
    texScrollCheck(mtx->getTexMtxInfo().mSRT.mTranslationX);
    mtx = mat->getTexMtx(1);
    mtx->getTexMtxInfo().mSRT.mTranslationX += scrollSpeed;
    mtx->getTexMtxInfo().mSRT.mTranslationX += scrollSpeed * 0.6f;
    texScrollCheck(mtx->getTexMtxInfo().mSRT.mTranslationX);
    mat->setTevKColor(0, (J3DGXColor*)&k0);

    if (i_this->mpKasumiMae != NULL) {
        mat = i_this->mpKasumiMae->getModelData()->getMaterialNodePointer(0);
        mat->getZMode()->setZModeInfo(l_zmodeInfo);
        mat->change();

        c0.r = g_env_light.mVrKasumiMaeColor.r;
        c0.g = g_env_light.mVrKasumiMaeColor.g;
        c0.b = g_env_light.mVrKasumiMaeColor.b;
        k0.r = g_env_light.mVrkumoColor.a;
        k0.g = 0x00;
        k0.b = 0x00;
        k0.a = 0x00;
        mat->setTevColor(0, (J3DGXColorS10*)&c0);
        mat->setTevKColor(0, (J3DGXColor*)&k0);
    }

    if (i_this->mpUsoUmi != NULL) {
        mat = i_this->mpUsoUmi->getModelData()->getMaterialNodePointer(0);
        mat->getZMode()->setZModeInfo(l_zmodeInfo);
        mat->change();

        k0.r = g_env_light.mVrUsoUmiColor.r;
        k0.g = g_env_light.mVrUsoUmiColor.g;
        k0.b = g_env_light.mVrUsoUmiColor.b;
        k0.a = 0xFF;
        mat->setTevKColor(0, (J3DGXColor*)&k0);
    }

    return TRUE;
}

/* 8015F368-8015F370       .text daVrbox2_Execute__FP12vrbox2_class */
static BOOL daVrbox2_Execute(vrbox2_class*) {
    return TRUE;
}

/* 8015F370-8015F378       .text daVrbox2_IsDelete__FP12vrbox2_class */
static BOOL daVrbox2_IsDelete(vrbox2_class*) {
    return TRUE;
}

/* 8015F378-8015F380       .text daVrbox2_Delete__FP12vrbox2_class */
static BOOL daVrbox2_Delete(vrbox2_class*) {
    return TRUE;
}

/* 8015F380-8015F4D4       .text daVrbox2_solidHeapCB__FP10fopAc_ac_c */
static BOOL daVrbox2_solidHeapCB(fopAc_ac_c* i_actor) {
    vrbox2_class* i_this = static_cast<vrbox2_class*>(i_actor);

    J3DModelData* modelData = (J3DModelData*)dComIfG_getStageRes("Stage", "vr_back_cloud.bdl");
    JUT_ASSERT(DEMO_SELECT(511, 529), modelData != NULL);
    i_this->mpBackCloud = mDoExt_J3DModel__create(modelData, 0x80000, 0x11020202);

    modelData = (J3DModelData*)dComIfG_getStageRes("Stage", "vr_kasumi_mae.bdl");
    if (modelData != NULL)
        i_this->mpKasumiMae = mDoExt_J3DModel__create(modelData, 0x80000, 0x11020202);
    modelData = (J3DModelData*)dComIfG_getStageRes("Stage", "vr_uso_umi.bdl");
    if (modelData != NULL)
        i_this->mpUsoUmi = mDoExt_J3DModel__create(modelData, 0x80000, 0x11020202);

    bool success = FALSE;
    if (i_this->mpBackCloud != NULL && i_this->mpKasumiMae != NULL && i_this->mpUsoUmi != NULL) {
        success = TRUE;
    }
    return success;
}

/* 8015F4D4-8015F550       .text daVrbox2_Create__FP10fopAc_ac_c */
static cPhs_State daVrbox2_Create(fopAc_ac_c* i_actor) {
    fopAcM_SetupActor(i_actor, vrbox2_class);
    vrbox2_class* i_this = static_cast<vrbox2_class*>(i_actor);

#if VERSION == VERSION_DEMO
    fopAcM_entrySolidHeap(i_this, daVrbox2_solidHeapCB, 0x21a0);
    cPhs_State phase_state = cPhs_COMPLEATE_e;
#else
    cPhs_State phase_state = cPhs_COMPLEATE_e;
    if (!fopAcM_entrySolidHeap(i_this, daVrbox2_solidHeapCB, 0x21a0))
        phase_state = cPhs_ERROR_e;
#endif

    return phase_state;
}

static actor_method_class l_daVrbox2_Method = {
    (process_method_func)daVrbox2_Create,
    (process_method_func)daVrbox2_Delete,
    (process_method_func)daVrbox2_Execute,
    (process_method_func)daVrbox2_IsDelete,
    (process_method_func)daVrbox2_Draw,
};

actor_process_profile_definition g_profile_VRBOX2 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_VRBOX2,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(vrbox2_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_VRBOX2,
    /* Actor SubMtd */ &l_daVrbox2_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
