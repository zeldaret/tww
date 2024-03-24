/**
 * f_op_scene_mng.cpp
 * Framework - Scene Process Manager
 */

#include "f_op/f_op_scene_mng.h"
#include "f_op/f_op_scene_iter.h"
#include "f_op/f_op_scene_req.h"
#include "f_pc/f_pc_searcher.h"
#include "JSystem/JUtility/JUTAssert.h"

scene_class* fopScnM_SearchByID(uint id) {
    return (scene_class*)fopScnIt_Judge((fop_ScnItFunc)fpcSch_JudgeByID, &id);
}

static u32 l_scnRqID = fpcM_ERROR_PROCESS_ID_e;

int fopScnM_ChangeReq(scene_class* i_scene, s16 procName, s16 fadeTime, u16 param_4) {
    uint sceneRequestID = fopScnRq_Request(2, i_scene, procName, 0, fadeTime, param_4);

    if (sceneRequestID == fpcM_ERROR_PROCESS_ID_e) {
        return 0;
    }

    l_scnRqID = sceneRequestID;
    return 1;
}

uint fopScnM_DeleteReq(scene_class* i_scene) {
    uint sceneRequestID = fopScnRq_Request(1, i_scene, 0x7FFF, 0, 0x7FFF, 0);
    return sceneRequestID != fpcM_ERROR_PROCESS_ID_e;
}

int fopScnM_CreateReq(s16 param_1, s16 param_2, u16 param_3, u32 param_4) {
    uint sceneRequestID = fopScnRq_Request(0, 0, param_1, (void*)param_4, param_2, param_3);
    return sceneRequestID != fpcM_ERROR_PROCESS_ID_e;
}

u32 fopScnM_ReRequest(s16 param_1, u32 param_2) {
    if (l_scnRqID == fpcM_ERROR_PROCESS_ID_e) {
        return 0;
    }

    return fopScnRq_ReRequest(l_scnRqID, param_1, (void*)param_2);
}

void fopScnM_Management() {
    if (!fopScnRq_Handler())
        JUT_ASSERT(326, 0);
}

void fopScnM_Init() {
}
