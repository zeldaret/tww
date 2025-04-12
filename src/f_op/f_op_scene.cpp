/**
 * f_op_scene.cpp
 * Scene Process Framework
 */

#include "f_op/f_op_scene.h"
#include "f_pc/f_pc_manager.h"
#include "m_Do/m_Do_hostIO.h"

static BOOL fopScn_Draw(scene_class* i_this) {
    return fpcNd_DrawMethod((nodedraw_method_class*)i_this->mpMtd, i_this);
}

static BOOL fopScn_Execute(scene_class* i_this) {
    return fpcMtd_Execute((process_method_class*)i_this->mpMtd, i_this);
}

static BOOL fopScn_IsDelete(void* i_this) {
    return fpcMtd_IsDelete((process_method_class*)((scene_class*)i_this)->mpMtd, i_this);
}

static BOOL fopScn_Delete(void* i_this) {
    scene_class* scene = static_cast<scene_class*>(i_this);
    BOOL ret = fpcMtd_Delete((process_method_class*)scene->mpMtd, scene);
    if (ret == TRUE) {
        fopScnTg_QueueTo(&scene->mScnTg);
    }
    mDoHIO_root.update();
    return ret;
}

static cPhs_State fopScn_Create(void* i_this) {
    scene_class* scene = static_cast<scene_class*>(i_this);
    if (fpcM_IsFirstCreating(i_this)) {
        scene_process_profile_definition* profile = (scene_process_profile_definition*)fpcM_GetProfile(i_this);
        scene->mpMtd = profile->sub_method;
        fopScnTg_Init(&scene->mScnTg, i_this);
        fopScnTg_ToQueue(&scene->mScnTg);

        u32* append = (u32*)fpcM_GetAppend(i_this);
        if (append != NULL) {
            scene->base.base.mParameters = *append;
        }
    }

    return fpcMtd_Create((process_method_class*)scene->mpMtd, i_this);
}

leafdraw_method_class g_fopScn_Method = {
    (process_method_func)fopScn_Create,
    (process_method_func)fopScn_Delete,
    (process_method_func)fopScn_Execute,
    (process_method_func)fopScn_IsDelete,
    (process_method_func)fopScn_Draw,
};
