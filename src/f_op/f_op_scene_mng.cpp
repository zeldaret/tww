/**
 * f_op_scene_mng.cpp
 * Framework - Scene Process Manager
 */

#include "f_op/f_op_scene_mng.h"
#include "f_op/f_op_scene_iter.h"
#include "f_op/f_op_scene_req.h"
#include "f_pc/f_pc_searcher.h"
#include "d/d_procname.h"
#include "JSystem/JUtility/JUTAssert.h"

scene_class* fopScnM_SearchByID(fpc_ProcID id) {
    return (scene_class*)fopScnIt_Judge((fop_ScnItFunc)fpcSch_JudgeByID, &id);
}

static uint l_scnRqID = -1;

int fopScnM_ChangeReq(scene_class* i_scene, s16 procName, s16 fadeProcName, u16 fadePeekTime) {
    uint sceneRequestID = fopScnRq_Request(2, i_scene, procName, 0, fadeProcName, fadePeekTime);

    if (sceneRequestID == -1) {
        return 0;
    }

    l_scnRqID = sceneRequestID;
    return 1;
}

BOOL fopScnM_DeleteReq(scene_class* i_scene) {
    uint sceneRequestID = fopScnRq_Request(1, i_scene, PROC_INVALID_e, 0, PROC_INVALID_e, 0);
    return sceneRequestID != -1;
}

BOOL fopScnM_CreateReq(s16 procName, s16 fadeProcName, u16 fadePeekTime, u32 user) {
    uint sceneRequestID = fopScnRq_Request(0, 0, procName, (void*)user, fadeProcName, fadePeekTime);
    return sceneRequestID != -1;
}

u32 fopScnM_ReRequest(s16 procName, u32 user) {
    if (l_scnRqID == -1) {
        return 0;
    }

    return fopScnRq_ReRequest(l_scnRqID, procName, (void*)user);
}

void fopScnM_Management() {
    if (!fopScnRq_Handler())
        JUT_ASSERT(326, FALSE);
}

void fopScnM_Init() {
}
