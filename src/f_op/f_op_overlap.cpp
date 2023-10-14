/**
 * f_op_overlap.cpp
 * Overlap Process Framework
 */

#include "SSystem/SComponent/c_request.h"
#include "f_op/f_op_overlap.h"
#include "f_op/f_op_overlap_mng.h"
#include "f_pc/f_pc_manager.h"

static s32 fopOvlp_Draw(void* i_ovlp) {
    overlap_task_class* i_this = (overlap_task_class*)i_ovlp;
    return fpcLf_DrawMethod((leafdraw_method_class*)i_this->mSubMtd, i_this);
}

static s32 fopOvlp_Execute(void* i_ovlp) {
    overlap_task_class* i_this = (overlap_task_class*)i_ovlp;
    return fpcMtd_Execute((process_method_class*)i_this->mSubMtd, i_this);
}

static s32 fopOvlp_IsDelete(void* i_ovlp) {
    overlap_task_class* i_this = (overlap_task_class*)i_ovlp;
    return fpcMtd_IsDelete((process_method_class*)i_this->mSubMtd, i_this);
}

static s32 fopOvlp_Delete(void* i_ovlp) {
    overlap_task_class* i_this = (overlap_task_class*)i_ovlp;
    return fpcMtd_Delete((process_method_class*)i_this->mSubMtd, i_this);
}

static s32 fopOvlp_Create(void* i_ovlp) {
    overlap_task_class* i_this = (overlap_task_class*)i_ovlp;

    if (fpcM_IsFirstCreating(i_this)) {
        overlap_process_profile_definition* profile = (overlap_process_profile_definition*)fpcM_GetProfile(i_this);

        cReq_Create(&i_this->mRq, 1);
        i_this->mSubMtd = profile->mSubMtd;
        i_this->mScenePId = -1;
    }

    return fpcMtd_Create((process_method_class*)i_this->mSubMtd, i_this);
}

leafdraw_method_class g_fopOvlp_Method = {
    (process_method_func)fopOvlp_Create,
    (process_method_func)fopOvlp_Delete,
    (process_method_func)fopOvlp_Execute,
    (process_method_func)fopOvlp_IsDelete,
    (process_method_func)fopOvlp_Draw,
};
