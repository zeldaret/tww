/**
 * f_op_overlap_req.cpp
 * Overlap Process Request
 */

#include "SSystem/SComponent/c_request.h"
#include "f_op/f_op_overlap_req.h"
#include "f_pc/f_pc_manager.h"
#include "f_pc/f_pc_stdcreate_req.h"

void fopOvlpReq_SetPeektime(overlap_request_class*, u16);

static int fopOvlpReq_phase_Done(overlap_request_class* i_overlapReq) {
    if (fpcM_Delete(i_overlapReq->field_0x20) == 1) {
        i_overlapReq->field_0x20 = 0;
        i_overlapReq->field_0x4 = 0;
        i_overlapReq->mPeektime = 0;
        i_overlapReq->field_0x8 = 0;
        i_overlapReq->field_0xc = 0;
        return 2;
    }

    return 0;
}

static s32 fopOvlpReq_phase_IsDone(overlap_request_class* param_1) {
    cReq_Done((request_base_class*)param_1);
    return param_1->field_0x2-- <= 0 ? 2 : 0;
}

static int fopOvlpReq_phase_IsWaitOfFadeout(overlap_request_class* i_overlapReq) {
    if (cReq_Is_Done((request_base_class*)(i_overlapReq->field_0x20 + 0xC4))) {
        i_overlapReq->field_0x8 = 0;
        return 2;
    }

    return 0;
}

static int fopOvlpReq_phase_WaitOfFadeout(overlap_request_class* i_overlapReq) {
    if (i_overlapReq->mPeektime) {
        i_overlapReq->mPeektime--;
    }

    if (((u8)(i_overlapReq->field_0x0 & 0x3F)) == 2 && !i_overlapReq->mPeektime) {
        cReq_Command((request_base_class*)(i_overlapReq->field_0x20 + 0xC4), 2);
        return 2;
    }

    i_overlapReq->field_0x8 = 1;
    return 0;
}

static int fopOvlpReq_phase_IsComplete(overlap_request_class* i_overlapReq) {
    if (cReq_Is_Done((request_base_class*)(i_overlapReq->field_0x20 + 0xC4))) {
        cReq_Done((request_base_class*)i_overlapReq);
        return 2;
    }

    return 0;
}

static int fopOvlpReq_phase_IsCreated(overlap_request_class* i_overlapReq) {
    if (fpcM_IsCreating(i_overlapReq->field_0x14) == 0) {
        base_process_class* pBaseProc = fpcEx_SearchByID(i_overlapReq->field_0x14);
    
        if (pBaseProc == NULL) {
            return cPhs_ERROR_e;
        }
    
        i_overlapReq->field_0x20 = (u8*)pBaseProc;
        return 2;
    }

    return 0;
}

static int fopOvlpReq_phase_Create(overlap_request_class* i_overlapReq) {
    fpcLy_SetCurrentLayer(i_overlapReq->pCurrentLayer);
    i_overlapReq->field_0x14 =
        fpcSCtRq_Request(fpcLy_CurrentLayer(), i_overlapReq->field_0x10, 0, 0, 0);
    return 2;
}

request_base_class* fopOvlpReq_Request(overlap_request_class* i_overlapReq, s16 param_2,
                                       u16 param_3) {
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

    if (i_overlapReq->field_0x4 == 1) {
        i_overlapReq = 0;
        return (request_base_class*)i_overlapReq;
    }

    cReq_Command((request_base_class*)i_overlapReq, 1);
    i_overlapReq->field_0x10 = param_2;
    cPhs_Set(&i_overlapReq->field_0x18, phaseMethod);
    fopOvlpReq_SetPeektime(i_overlapReq, param_3);
    i_overlapReq->field_0x4 = 1;
    i_overlapReq->field_0x2 = 1;
    i_overlapReq->field_0x20 = 0;
    i_overlapReq->field_0x8 = 0;
    i_overlapReq->field_0xc = 0;
    i_overlapReq->pCurrentLayer = fpcLy_RootLayer();
    return (request_base_class*)i_overlapReq;
}

int fopOvlpReq_Handler(overlap_request_class* i_overlapReq) {
    int phase_state = cPhs_Do(&i_overlapReq->field_0x18, i_overlapReq);

    switch (phase_state) {
    case cPhs_NEXT_e:
        return fopOvlpReq_Handler(i_overlapReq);
    case cPhs_INIT_e:
        return cPhs_INIT_e;
    case cPhs_LOADING_e:
        return cPhs_INIT_e;
    case cPhs_COMPLEATE_e:
        return cPhs_COMPLEATE_e;
    case cPhs_UNK3_e:
    case cPhs_ERROR_e:
        return cPhs_ERROR_e;
    default:
        return cPhs_ERROR_e;
    }
}

int fopOvlpReq_Cancel(overlap_request_class* i_overlapReq) {
    return fopOvlpReq_phase_Done(i_overlapReq) == 2 ? 1 : 0;
}

int fopOvlpReq_Is_PeektimeLimit(overlap_request_class* i_overlapReq) {
    return i_overlapReq->mPeektime == 0 ? 1 : 0;
}

void fopOvlpReq_SetPeektime(overlap_request_class* i_overlapReq, u16 param_2) {
    if (0x7fff < param_2) {
        return;
    }

    i_overlapReq->mPeektime = param_2;
}

int fopOvlpReq_OverlapClr(overlap_request_class* i_overlapReq) {
    if ((u8)((i_overlapReq->field_0x0 >> 7) & 1) == 1 || !fopOvlpReq_Is_PeektimeLimit(i_overlapReq))
    {
        return 0;
    }

    cReq_Create((request_base_class*)i_overlapReq, 2);
    return 1;
}
