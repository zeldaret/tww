/**
 * f_op_overlap_mng.cpp
 * Overlap Process Manager
 */

#include "f_op/f_op_overlap_mng.h"
#include "SSystem/SComponent/c_request.h"
#include "f_op/f_op_overlap_req.h"
#include "f_op/f_op_scene_pause.h"
#include "f_pc/f_pc_executor.h"
#include "JSystem/JUtility/JUTAssert.h"

// making it not an array put it in .bss
static overlap_request_class* l_fopOvlpM_overlap[1] = {NULL};

int fopOvlpM_SceneIsStop() {
    if (l_fopOvlpM_overlap[0] != NULL) {
        return fopScnPause_Enable((scene_class*)fpcEx_SearchByID(l_fopOvlpM_overlap[0]->mpTask->mScenePId));
    } else {
        return 0;
    }
}

int fopOvlpM_SceneIsStart() {
    if (l_fopOvlpM_overlap[0] != NULL) {
        return fopScnPause_Disable((scene_class*)fpcEx_SearchByID(l_fopOvlpM_overlap[0]->mpTask->mScenePId));
    } else {
        return 0;
    }
}

int fopOvlpM_IsOutReq(overlap_task_class* pTaskClass) {
    return pTaskClass->mRq.flag2 == 2;
}

void fopOvlpM_Done(overlap_task_class* pTaskClass) {
    cReq_Done(&pTaskClass->mRq);
}

void fopOvlpM_ToldAboutID(uint pcId) {
    if (l_fopOvlpM_overlap[0] != NULL)
        l_fopOvlpM_overlap[0]->mpTask->mScenePId = pcId;
}

int fopOvlpM_IsPeek() {
    if (l_fopOvlpM_overlap[0] != NULL)
        return l_fopOvlpM_overlap[0]->mIsPeek;
    else
        return 0;
}

int fopOvlpM_IsDone() {
    if (l_fopOvlpM_overlap[0] != NULL)
        return cReq_Is_Done(l_fopOvlpM_overlap[0]);
    else
        return 0;
}

int fopOvlpM_IsDoingReq() {
    if (l_fopOvlpM_overlap[0] && l_fopOvlpM_overlap[0]->field_0x4 == 1) {
        return 1;
    }

    return 0;
}

int fopOvlpM_ClearOfReq() {
    if (l_fopOvlpM_overlap[0] != NULL)
        return fopOvlpReq_OverlapClr(l_fopOvlpM_overlap[0]);
    else
        return 0;
}

static overlap_request_class l_fopOvlpM_Request;

request_base_class* fopOvlpM_Request(s16 procName, u16 peekTime) {
    if (l_fopOvlpM_overlap[0] == NULL) {
        l_fopOvlpM_overlap[0] = fopOvlpReq_Request(&l_fopOvlpM_Request, procName, peekTime);
        return l_fopOvlpM_overlap[0];
    }

    return 0;
}

void fopOvlpM_Management() {
    if (l_fopOvlpM_overlap[0] != NULL) {
        int tmp = fopOvlpReq_Handler(l_fopOvlpM_overlap[0]);
        if (6 <= tmp || 3 > tmp) {
            return;
        }
        l_fopOvlpM_overlap[0] = NULL;
    }
}

int fopOvlpM_Cancel() {
    if (l_fopOvlpM_overlap[0] == NULL)
        return 1;

    if (fopOvlpReq_Cancel(l_fopOvlpM_overlap[0]) == true) {
        l_fopOvlpM_overlap[0] = NULL;
        JUT_WARN(331, "%s", "fopOvlpM_Cancel SUCCESSED");
        return 1;
    }

    return 0;
}

void fopOvlpM_Init() {}
