//
// Generated by dtk
// Translation Unit: c_phase.cpp
//

#include "SSystem/SComponent/c_phase.h"
#include "dolphin/types.h"

/* 802451B4-802451C0       .text cPhs_Reset__FP30request_of_phase_process_class */
void cPhs_Reset(request_of_phase_process_class* pPhase) {
    pPhase->id = cPhs_INIT_e;
}

/* 802451C0-802451D0       .text cPhs_Set__FP30request_of_phase_process_classPPFPv_i */
void cPhs_Set(request_of_phase_process_class* pPhase, cPhs__Handler* pHandlerTable) {
    pPhase->mpHandlerTable = pHandlerTable;
    pPhase->id = cPhs_INIT_e;
}

/* 802451D0-802451F8       .text cPhs_UnCompleate__FP30request_of_phase_process_class */
void cPhs_UnCompleate(request_of_phase_process_class* pPhase) {
    pPhase->mpHandlerTable = NULL;
    cPhs_Reset(pPhase);
}

/* 802451F8-80245208       .text cPhs_Compleate__FP30request_of_phase_process_class */
int cPhs_Compleate(request_of_phase_process_class* pPhase) {
    pPhase->mpHandlerTable = NULL;
    return cPhs_COMPLEATE_e;
}

/* 80245208-80245268       .text cPhs_Next__FP30request_of_phase_process_class */
int cPhs_Next(request_of_phase_process_class* pPhase) {
    if (const cPhs__Handler* handlerTable = pPhase->mpHandlerTable) {
        pPhase->id++;
        cPhs__Handler handler = handlerTable[pPhase->id];

        // Double null check here actually matters for emitted assembly.
        // Wee old compilers.
        if (handler == NULL || handler == NULL) {
            return cPhs_Compleate(pPhase);
        } else {
            return cPhs_LOADING_e;
        }
    }

    return cPhs_COMPLEATE_e;
}

/* 80245268-8024533C       .text cPhs_Do__FP30request_of_phase_process_classPv */
int cPhs_Do(request_of_phase_process_class* pPhase, void* pUserData) {
    cPhs__Handler * handler = pPhase->mpHandlerTable;

    if (handler) {
        handler += pPhase->id;
        int newStep = (*handler)(pUserData);

        switch (newStep) {
        case cPhs_LOADING_e:
            return cPhs_Next(pPhase);
        case cPhs_NEXT_e:
            return cPhs_Next(pPhase) == cPhs_LOADING_e ? cPhs_NEXT_e : cPhs_COMPLEATE_e;
        case cPhs_COMPLEATE_e:
            return cPhs_Compleate(pPhase);
        case cPhs_STOP_e:
            cPhs_UnCompleate(pPhase);
            return cPhs_STOP_e;
        case cPhs_ERROR_e:
            cPhs_UnCompleate(pPhase);
            return cPhs_ERROR_e;
        case cPhs_INIT_e:
        default:
            return newStep;
        }
    }
    
    return cPhs_Compleate(pPhase);
}

/* 8024533C-80245364       .text cPhs_Handler__FP30request_of_phase_process_classPPFPv_iPv */
int cPhs_Handler(request_of_phase_process_class* pPhase, cPhs__Handler* pHandlerTable,
                 void* pUserData) {
    pPhase->mpHandlerTable = pHandlerTable;
    return cPhs_Do(pPhase, pUserData);
}
