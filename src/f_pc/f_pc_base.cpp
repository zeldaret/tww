//
// Generated by dtk
// Translation Unit: f_pc_base.cpp
//

#include "f_pc/f_pc_base.h"
#include "SSystem/SComponent/c_malloc.h"
#include "SSystem/SComponent/c_phase.h"
#include "SSystem/SStandard/s_basic.h"
#include "f_pc/f_pc_layer.h"
#include "f_pc/f_pc_method.h"
#include "f_pc/f_pc_pause.h"
#include "f_pc/f_pc_profile.h"
#include "dolphin/types.h"

/* 8003C88C-8003C89C       .text fpcBs_Is_JustOfType__Fii */
BOOL fpcBs_Is_JustOfType(int i_typeA, int i_typeB) {
    if (i_typeB == i_typeA) {
        return TRUE;
    } else {
        return FALSE;
    }
}

static int g_fpcBs_type;

/* 8003C89C-8003C8DC       .text fpcBs_MakeOfType__FPi */
s32 fpcBs_MakeOfType(int* i_type) {
    static s32 t_type = 0x9130000;
    if (*i_type == 0) {
        *i_type = ++t_type;
    }
    return *i_type;
}

/* 8003C8DC-8003C904       .text fpcBs_MakeOfId__Fv */
fpc_ProcID fpcBs_MakeOfId() {
    static fpc_ProcID process_id = 1;
    return process_id++;
}

/* 8003C904-8003C960       .text fpcBs_Execute__FP18base_process_class */
s32 fpcBs_Execute(base_process_class* i_proc) {
    s32 result;
    layer_class* savedLayer = fpcLy_CurrentLayer();
    fpcLy_SetCurrentLayer(i_proc->mLyTg.mpLayer);
    result = fpcMtd_Execute(i_proc->mpPcMtd, i_proc);
    fpcLy_SetCurrentLayer(savedLayer);
    return result;
}

/* 8003C960-8003C9A0       .text fpcBs_DeleteAppend__FP18base_process_class */
void fpcBs_DeleteAppend(base_process_class* i_proc) {
    if (i_proc->mpUserData != NULL) {
        cMl::free(i_proc->mpUserData);
        i_proc->mpUserData = NULL;
    }
}

/* 8003C9A0-8003C9FC       .text fpcBs_IsDelete__FP18base_process_class */
s32 fpcBs_IsDelete(base_process_class* i_proc) {
    s32 result;
    layer_class* savedLayer = fpcLy_CurrentLayer();
    fpcLy_SetCurrentLayer(i_proc->mLyTg.mpLayer);
    result = fpcMtd_IsDelete(i_proc->mpPcMtd, i_proc);
    fpcLy_SetCurrentLayer(savedLayer);
    return result;
}

/* 8003C9FC-8003CA60       .text fpcBs_Delete__FP18base_process_class */
s32 fpcBs_Delete(base_process_class* i_proc) {
    s32 deleteResult = fpcMtd_Delete(i_proc->mpPcMtd, i_proc);
    if (deleteResult == 1) {
        fpcBs_DeleteAppend(i_proc);
        i_proc->mBsType = 0;
        cMl::free(i_proc);
    }
    return deleteResult;
}

/* 8003CA60-8003CB5C       .text fpcBs_Create__FsUiPv */
base_process_class* fpcBs_Create(s16 i_profName, fpc_ProcID i_procID, void* i_data) {
    process_profile_definition* procProfDef;
    base_process_class* procClass;
    u32 size;

    procProfDef = (process_profile_definition*)fpcPf_Get(i_profName);
    size = procProfDef->mSize + procProfDef->mSizeOther;
    procClass = (base_process_class*)cMl::memalignB(-4, size);
    if (procClass == NULL) {
        return NULL;
    } else {
        sBs_ClearArea(procClass, size);
        fpcLyTg_Init(&procClass->mLyTg, procProfDef->mLayerID, procClass);
        fpcLnTg_Init(&procClass->mLnTg, procClass);
        fpcDtTg_Init(&procClass->mDtTg, procClass);
        fpcPi_Init(&procClass->mPi, procClass, procProfDef->mLayerID, procProfDef->mListID,
                   procProfDef->mListPrio);
        procClass->mInitState = 0;
        procClass->mUnk0 = 0;
        procClass->mBsPcId = i_procID;
        procClass->mProfName = i_profName;
        procClass->mBsType = fpcBs_MakeOfType(&g_fpcBs_type);
        procClass->mProcName = procProfDef->mProcName;
        fpcPause_Init(procClass);
        procClass->mpPcMtd = procProfDef->sub_method;
        procClass->mpProf = procProfDef;
        procClass->mpUserData = i_data;
        procClass->mParameters = procProfDef->mParameters;
        return procClass;
    }
}

/* 8003CB5C-8003CC08       .text fpcBs_SubCreate__FP18base_process_class */
s32 fpcBs_SubCreate(base_process_class* i_proc) {
    switch (fpcMtd_Create(i_proc->mpPcMtd, i_proc)) {
    case cPhs_NEXT_e:
    case cPhs_COMPLEATE_e:
        fpcBs_DeleteAppend(i_proc);
        i_proc->mCreateResult = cPhs_NEXT_e;
        return cPhs_NEXT_e;
    case cPhs_INIT_e:
    case cPhs_LOADING_e:
        i_proc->mInitState = 1;
        i_proc->mCreateResult = cPhs_INIT_e;
        return cPhs_INIT_e;
    case cPhs_STOP_e:
        i_proc->mCreateResult = cPhs_STOP_e;
        return cPhs_STOP_e;
    case cPhs_ERROR_e:
    default:
        i_proc->mCreateResult = cPhs_ERROR_e;
        return cPhs_ERROR_e;
    }
}
