/**
 * d_com_lib_game.cpp
 * Game - Shared Library ("Common Library Game")
 */

#include "d/dolzel.h" // IWYU pragma: keep
#include "d/d_com_lib_game.h"
#include "SSystem/SComponent/c_phase.h"

/* 800565CC-8005662C       .text dComLbG_PhaseHandler__FP30request_of_phase_process_classPPFPv_iPv */
cPhs_State dComLbG_PhaseHandler(request_of_phase_process_class* i_phaseReq, cPhs__Handler* i_handler,
                         void* i_data) {
    cPhs_State phase = cPhs_Handler(i_phaseReq, i_handler, i_data);
    switch (phase) {
    case cPhs_NEXT_e:
        phase = dComLbG_PhaseHandler(i_phaseReq, i_handler, i_data);
        break;
    case cPhs_LOADING_e:
    case cPhs_STOP_e:
    default:
        break;
    }

    return phase;
}
