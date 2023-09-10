/**
 * f_op_scene.cpp
 * Scene Process Framework
 */

#include "f_op/f_op_scene.h"
#include "f_pc/f_pc_manager.h"
#include "m_Do/m_Do_hostIO.h"

static void fopScn_Draw(scene_class* i_this) {
    fpcNd_DrawMethod((nodedraw_method_class*)i_this->mpMtd, i_this);
}

static void fopScn_Execute(scene_class* i_this) {
    fpcMtd_Execute(i_this->mpMtd, i_this);
}

static s32 fopScn_IsDelete(void* i_this) {
    return fpcMtd_IsDelete(static_cast<scene_class*>(i_this)->mpMtd, i_this);
}

static s32 fopScn_Delete(void* i_this) {
    scene_class* scene = static_cast<scene_class*>(i_this);
    s32 ret = fpcMtd_Delete(scene->mpMtd, scene);
    if (ret == 1) {
        fopScnTg_QueueTo(&scene->mScnTg);
    }
    mDoHIO_root.update();
    return ret;
}

static s32 fopScn_Create(void* i_this) {
    scene_class* scene = static_cast<scene_class*>(i_this);
    if (fpcM_IsFirstCreating(i_this)) {
        scene_process_profile_definition* profile =
            (scene_process_profile_definition*)fpcM_GetProfile(i_this);
        scene->mpMtd = profile->mpMtd;
        fopScnTg_Init(&scene->mScnTg, i_this);
        fopScnTg_ToQueue(&scene->mScnTg);

        u32* append = (u32*)fpcM_GetAppend(i_this);
        if (append != NULL) {
            scene->mBase.mBase.mParameters = *append;
        }
    }

    return fpcMtd_Create(scene->mpMtd, i_this);
}

leafdraw_method_class g_fopScn_Method = {
    (process_method_func)fopScn_Create,  (process_method_func)fopScn_Delete,
    (process_method_func)fopScn_Execute, (process_method_func)fopScn_IsDelete,
    (process_method_func)fopScn_Draw,
};
