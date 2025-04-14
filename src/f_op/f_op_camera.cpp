//
// Generated by dtk
// Translation Unit: f_op_camera.cpp
//

#include "f_op/f_op_camera.h"
#include "f_op/f_op_camera_mng.h"
#include "f_op/f_op_draw_tag.h"
#include "dolphin/types.h"
#include "d/d_meter.h"
#include "d/d_s_play.h"

/* 80029278-800292CC       .text fopCam_Draw__FP12camera_class */
BOOL fopCam_Draw(camera_class* camera) {
    BOOL cam_proc = TRUE;

    if (!dMenu_flag()) {
        cam_proc = fpcLf_DrawMethod(camera->mpMtd, camera);
    }
    return cam_proc;
}

/* 800292CC-80029328       .text fopCam_Execute__FP12camera_class */
BOOL fopCam_Execute(camera_class* camera) {
    BOOL ret;

    if (!dMenu_flag() && !dScnPly_ply_c::isPause()) {
        ret = fpcMtd_Execute((process_method_class*)camera->mpMtd, camera);
    }

    return ret;
}

/* 80029328-8002937C       .text fopCam_IsDelete__FP12camera_class */
BOOL fopCam_IsDelete(camera_class* camera) {
    BOOL ret = fpcMtd_IsDelete((process_method_class*)camera->mpMtd, camera);
    if (ret == TRUE)
        fopDwTg_DrawQTo(&camera->draw_tag);
    return ret;
}

/* 8002937C-800293D0       .text fopCam_Delete__FP12camera_class */
BOOL fopCam_Delete(camera_class* camera) {
    BOOL ret = fpcMtd_Delete((process_method_class*)camera->mpMtd, camera);
    if (ret == TRUE)
        fopDwTg_DrawQTo(&camera->draw_tag);
    return ret;
}

/* 800293D0-80029468       .text fopCam_Create__FPv */
cPhs_State fopCam_Create(void* pProc) {
    camera_class* camera = (camera_class*)pProc;

    if (fpcM_IsFirstCreating(pProc)) {
        camera_process_profile_definition* profile =
            (camera_process_profile_definition*)fpcM_GetProfile(pProc);
        camera->mpMtd = profile->sub_method;

        fopDwTg_Init(&camera->draw_tag, camera);
        fopCamM_prm_class* append = (fopCamM_prm_class*)fpcM_GetAppend(camera);

        if (append) {
            fpcM_SetParam(camera, append->base.parameters);
        }
    }

    cPhs_State ret = fpcMtd_Create(&camera->mpMtd->base, camera);
    if (ret == cPhs_COMPLEATE_e) {
        s32 priority = fpcLf_GetPriority(camera);
        fopDwTg_ToDrawQ(&camera->draw_tag, priority);
    }

    return ret;
}

leafdraw_method_class g_fopCam_Method = {
    (process_method_func)fopCam_Create,
    (process_method_func)fopCam_Delete,
    (process_method_func)fopCam_Execute,
    (process_method_func)fopCam_IsDelete,
    (process_method_func)fopCam_Draw,
};
