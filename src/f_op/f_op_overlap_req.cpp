/**
 * f_op_overlap_req.cpp
 * Overlap Process Request
 */

#include "SSystem/SComponent/c_request.h"
#include "f_op/f_op_overlap_req.h"
#include "f_op/f_op_overlap_mng.h"
#include "f_pc/f_pc_manager.h"
#include "f_pc/f_pc_stdcreate_req.h"

void fopOvlpReq_SetPeektime(overlap_request_class*, u16);

static cPhs_State fopOvlpReq_phase_Done(overlap_request_class* i_this) {
    if (fpcM_Delete(i_this->mpTask) == TRUE) {
        i_this->mpTask = NULL;
        i_this->field_0x4 = 0;
        i_this->mPeektime = 0;
        i_this->mIsPeek = 0;
        i_this->field_0xc = 0;
        return cPhs_NEXT_e;
    }

    return cPhs_INIT_e;
}

static cPhs_State fopOvlpReq_phase_IsDone(overlap_request_class* i_this) {
    cReq_Done(i_this);
    if (i_this->mDelay-- <= 0)
        return cPhs_NEXT_e;
    else
        return cPhs_INIT_e;
}

static cPhs_State fopOvlpReq_phase_IsWaitOfFadeout(overlap_request_class* i_this) {
    if (cReq_Is_Done(&i_this->mpTask->mRq)) {
        i_this->mIsPeek = 0;
        return cPhs_NEXT_e;
    }

    return cPhs_INIT_e;
}

static cPhs_State fopOvlpReq_phase_WaitOfFadeout(overlap_request_class* i_this) {
    if (i_this->mPeektime)
        i_this->mPeektime--;

    if (i_this->flag2 == 2 && !i_this->mPeektime) {
        cReq_Command(&i_this->mpTask->mRq, 2);
        return cPhs_NEXT_e;
    }

    i_this->mIsPeek = 1;
    return cPhs_INIT_e;
}

static cPhs_State fopOvlpReq_phase_IsComplete(overlap_request_class* i_this) {
    if (cReq_Is_Done(&i_this->mpTask->mRq)) {
        cReq_Done(i_this);
        return cPhs_NEXT_e;
    }

    return cPhs_INIT_e;
}

static cPhs_State fopOvlpReq_phase_IsCreated(overlap_request_class* i_this) {
    if (fpcM_IsCreating(i_this->mPId) == 0) {
        base_process_class* pBaseProc = fpcEx_SearchByID(i_this->mPId);
        if (pBaseProc == NULL)
            return cPhs_ERROR_e;

        i_this->mpTask = (overlap_task_class*)pBaseProc;
        return cPhs_NEXT_e;
    }

    return cPhs_INIT_e;
}

static cPhs_State fopOvlpReq_phase_Create(overlap_request_class* i_this) {
    fpcLy_SetCurrentLayer(i_this->pCurrentLayer);
    i_this->mPId = fpcSCtRq_Request(fpcLy_CurrentLayer(), i_this->mProcName, NULL, NULL, NULL);
    return cPhs_NEXT_e;
}

overlap_request_class* fopOvlpReq_Request(overlap_request_class* i_this, s16 procName, u16 peekTime) {
    static cPhs__Handler phaseMethod[8] = {
        (cPhs__Handler)fopOvlpReq_phase_Create,
        (cPhs__Handler)fopOvlpReq_phase_IsCreated,
        (cPhs__Handler)fopOvlpReq_phase_IsComplete,
        (cPhs__Handler)fopOvlpReq_phase_WaitOfFadeout,
        (cPhs__Handler)fopOvlpReq_phase_IsWaitOfFadeout,
        (cPhs__Handler)fopOvlpReq_phase_IsDone,
        (cPhs__Handler)fopOvlpReq_phase_Done,
        (cPhs__Handler)NULL,
    };

    if (i_this->field_0x4 == 1) {
        i_this = NULL;
        return i_this;
    }

    cReq_Command(i_this, 1);
    i_this->mProcName = procName;
    cPhs_Set(&i_this->mPhs, phaseMethod);
    fopOvlpReq_SetPeektime(i_this, peekTime);
    i_this->field_0x4 = 1;
    i_this->mDelay = 1;
    i_this->mpTask = NULL;
    i_this->mIsPeek = 0;
    i_this->field_0xc = 0;
    i_this->pCurrentLayer = fpcLy_RootLayer();
    return i_this;
}

cPhs_State fopOvlpReq_Handler(overlap_request_class* i_this) {
    cPhs_State phase_state = cPhs_Do(&i_this->mPhs, i_this);

    switch (phase_state) {
    case cPhs_NEXT_e:
        return fopOvlpReq_Handler(i_this);
    case cPhs_INIT_e:
        return cPhs_INIT_e;
    case cPhs_LOADING_e:
        return cPhs_INIT_e;
    case cPhs_COMPLEATE_e:
        return cPhs_COMPLEATE_e;
    case cPhs_STOP_e:
    case cPhs_ERROR_e:
        return cPhs_ERROR_e;
    default:
        return cPhs_ERROR_e;
    }
}

BOOL fopOvlpReq_Cancel(overlap_request_class* i_this) {
    return (fopOvlpReq_phase_Done(i_this) == cPhs_NEXT_e) ? TRUE : FALSE;
}

BOOL fopOvlpReq_Is_PeektimeLimit(overlap_request_class* i_this) {
    return i_this->mPeektime == 0 ? TRUE : FALSE;
}

void fopOvlpReq_SetPeektime(overlap_request_class* i_this, u16 peekTime) {
    if (peekTime > 0x7fff)
        return;

    i_this->mPeektime = peekTime;
}

BOOL fopOvlpReq_OverlapClr(overlap_request_class* i_this) {
    if (i_this->flag0 == 1 || !fopOvlpReq_Is_PeektimeLimit(i_this))
        return FALSE;

    cReq_Create(i_this, 2);
    return TRUE;
}
