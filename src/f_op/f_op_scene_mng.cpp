/**
 * f_op_scene_mng.cpp
 * Framework - Scene Process Manager
 */

#include "f_op/f_op_scene_mng.h"
#include "f_op/f_op_scene_iter.h"
#include "f_op/f_op_scene_req.h"
#include "f_pc/f_pc_searcher.h"

scene_class* fopScnM_SearchByID(unsigned int id) {
    return (scene_class*)fopScnIt_Judge((fop_ScnItFunc)fpcSch_JudgeByID, &id);
}

static u32 l_scnRqID = 0xFFFFFFFF;

int fopScnM_ChangeReq(scene_class* i_scene, s16 param_2, s16 param_3, u16 param_4) {
    u32 sceneRequestID = fopScnRq_Request(2, i_scene, param_2, 0, param_3, param_4);

    if (sceneRequestID == 0xFFFFFFFF) {
        return 0;
    }

    l_scnRqID = sceneRequestID;
    return 1;
}

unsigned int fopScnM_DeleteReq(scene_class* i_scene) {
    u32 sceneRequestID = fopScnRq_Request(1, i_scene, 0x7FFF, 0, 0x7FFF, 0);
    return sceneRequestID != 0xFFFFFFFF;
}

int fopScnM_CreateReq(s16 param_1, s16 param_2, u16 param_3, u32 param_4) {
    u32 sceneRequestID = fopScnRq_Request(0, 0, param_1, (void*)param_4, param_2, param_3);
    return sceneRequestID != 0xFFFFFFFF;
}

u32 fopScnM_ReRequest(s16 param_1, u32 param_2) {
    if (l_scnRqID == 0xFFFFFFFF) {
        return 0;
    }

    return fopScnRq_ReRequest(l_scnRqID, param_1, (void*)param_2);
}

void fopScnM_Management() {
    fopScnRq_Handler();
}

void fopScnM_Init() {}
