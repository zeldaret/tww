/**
 * f_op_scene_req.cpp
 * Scene Process Request
 */

#include "f_op/f_op_scene_req.h"
#include "f_op/f_op_overlap_mng.h"
#include "f_op/f_op_scene.h"
#include "f_op/f_op_scene_pause.h"
#include "f_pc/f_pc_executor.h"
#include "f_pc/f_pc_manager.h"

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
        fopOvlpM_ToldAboutID(((scene_class*)param_1)->base.base.mBsPcId);
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

static scene_request_class* fopScnRq_FadeRequest(s16 procName, u16 peekTime) {
    request_base_class* req = NULL;

    if (l_fopScnRq_IsUsingOfOverlap == 0 && (req = fopOvlpM_Request(procName, peekTime), req != NULL))
        l_fopScnRq_IsUsingOfOverlap = 1;

    return (scene_request_class*)req;
}

uint fopScnRq_Request(int reqType, scene_class* i_scene, s16 procName, void* user, s16 fadeProcName, u16 fadePeekTime) {
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

    uint ret;
    scene_request_class* fade = NULL;
    cPhs__Handler* phase_handler_table;
    phase_handler_table = noFadeFase;
    scene_request_class* pScnReq = (scene_request_class*)fpcNdRq_Request(
        sizeof(scene_request_class), reqType, (process_node_class*)i_scene, procName, user,
        &submethod);

    if (!pScnReq) {
        ret = -1;
    } else {
        if (fadeProcName != 0x7fff) {
            phase_handler_table = fadeFase;
            fade = fopScnRq_FadeRequest(fadeProcName, fadePeekTime);
            if (!fade) {
                fpcNdRq_Delete(&pScnReq->mCrtReq);
                return -1;
            }
        }
        pScnReq->mFadeRequest = fade;
        cPhs_Set(&pScnReq->mReqPhsProcCls, phase_handler_table);
        ret = pScnReq->mCrtReq.mRequestId;
    }

    return ret;
}

s32 fopScnRq_ReRequest(uint i_requestID, s16 i_procName, void* i_data) {
    return fpcNdRq_ReRequest(i_requestID, i_procName, i_data);
}

s32 fopScnRq_Handler() {
    return fpcNdRq_Handler();
}
