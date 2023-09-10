/**
 * f_op_scene_req.cpp
 * Scene Process Request
 */

#include "f_op/f_op_scene_req.h"
#include "f_op/f_op_overlap_mng.h"
#include "f_op/f_op_scene.h"
#include "f_op/f_op_scene_pause.h"
#include "f_pc/f_pc_executor.h"

static cPhs__Step fopScnRq_phase_ClearOverlap(scene_request_class* i_sceneReq) {
    if (fopOvlpM_ClearOfReq() == 1) {
        return cPhs_NEXT_e;
    } else {
        return cPhs_INIT_e;
    }
}

static cPhs__Step fopScnRq_phase_Execute(scene_request_class* i_sceneReq) {
    return (cPhs__Step)fpcNdRq_Execute(&i_sceneReq->mCrtReq);
}

static cPhs__Step fopScnRq_phase_IsDoingOverlap(scene_request_class* i_sceneReq) {
    if (fopOvlpM_IsDoingReq() == 1) {
        return cPhs_NEXT_e;
    } else {
        return cPhs_INIT_e;
    }
}

static cPhs__Step fopScnRq_phase_IsDoneOverlap(scene_request_class* i_sceneReq) {
    if (fopOvlpM_IsDone() == 1) {
        return cPhs_NEXT_e;
    } else {
        return cPhs_INIT_e;
    }
}

static s32 l_fopScnRq_IsUsingOfOverlap;

static cPhs__Step fopScnRq_phase_Done(scene_request_class* i_sceneReq) {
    if (i_sceneReq->mCrtReq.mParameter != 1) {
        fopScnPause_Disable((scene_class*)fpcEx_SearchByID(i_sceneReq->mCrtReq.mCreatingID));
    }
    l_fopScnRq_IsUsingOfOverlap = 0;
    return cPhs_NEXT_e;
}

static void fopScnRq_Execute(scene_request_class* i_sceneReq) {
    int tmp = cPhs_Do(&i_sceneReq->mReqPhsProcCls, i_sceneReq);
    switch (tmp) {
    case 2:
        fopScnRq_Execute(i_sceneReq);
    }
}

static int fopScnRq_PostMethod(void* param_1, scene_request_class* i_sceneReq) {
    fopScnPause_Enable((scene_class*)param_1);
    if (i_sceneReq->mFadeRequest) {
        fopOvlpM_ToldAboutID(((scene_class*)param_1)->mBase.mBase.mBsPcId);
    }
    return 1;
}

static int fopScnRq_Cancel(scene_request_class* i_sceneReq) {
    if (i_sceneReq->mFadeRequest && !fopOvlpM_Cancel()) {
        return 0;
    } else {
        return 1;
    }
}

static scene_request_class* fopScnRq_FadeRequest(s16 param_1, u16 param_2) {
    request_base_class* req = NULL;

    if (l_fopScnRq_IsUsingOfOverlap == 0 && (req = fopOvlpM_Request(param_1, param_2), req != NULL))
    {
        l_fopScnRq_IsUsingOfOverlap = 1;
    }

    return (scene_request_class*)req;
}

s32 fopScnRq_Request(int param_1, scene_class* i_scene, s16 param_3, void* param_4, s16 param_5,
                     u16 param_6) {
    static node_create_request_method_class submethod = {
        (process_method_func)fopScnRq_Execute,
        (process_method_func)fopScnRq_Cancel,
        NULL,
        (process_method_func)fopScnRq_PostMethod,
    };

    static cPhs__Handler noFadeFase[8] = {
        (cPhs__Handler)fopScnRq_phase_Execute,
        (cPhs__Handler)fopScnRq_phase_Done,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };

    static cPhs__Handler fadeFase[8] = {
        (cPhs__Handler)fopScnRq_phase_IsDoingOverlap,
        (cPhs__Handler)fopScnRq_phase_IsDoneOverlap,
        (cPhs__Handler)fopScnRq_phase_Execute,
        (cPhs__Handler)fopScnRq_phase_ClearOverlap,
        (cPhs__Handler)fopScnRq_phase_IsDoneOverlap,
        (cPhs__Handler)fopScnRq_phase_Done,
        NULL,
        NULL,
    };

    s32 ret;
    int tmp = 0;
    cPhs__Handler* phase_handler_table;
    phase_handler_table = noFadeFase;
    scene_request_class* pScnReq = (scene_request_class*)fpcNdRq_Request(
        sizeof(scene_request_class), param_1, (process_node_class*)i_scene, param_3, param_4,
        &submethod);

    if (!pScnReq) {
        ret = -1;
    } else {
        if (param_5 != 0x7fff) {
            phase_handler_table = fadeFase;
            tmp = (int)fopScnRq_FadeRequest(param_5, param_6);
            if (!tmp) {
                fpcNdRq_Delete(&pScnReq->mCrtReq);
                return -1;
            }
        }
        pScnReq->mFadeRequest = tmp;
        cPhs_Set(&pScnReq->mReqPhsProcCls, phase_handler_table);
        ret = pScnReq->mCrtReq.mRequestId;
    }

    return ret;
}

s32 fopScnRq_ReRequest(unsigned int param_1, s16 param_2, void* param_3) {
    return fpcNdRq_ReRequest(param_1, param_2, param_3);
}

void fopScnRq_Handler() {
    fpcNdRq_Handler();
}
