#ifndef F_PC_MANAGER_H_
#define F_PC_MANAGER_H_

#include "f_pc/f_pc_create_iter.h"
#include "f_pc/f_pc_executor.h"
#include "f_pc/f_pc_leaf.h"
#include "f_pc/f_pc_node.h"
#include "f_pc/f_pc_stdcreate_req.h"

enum {
    fpcM_ERROR_PROCESS_ID_e = -1,
};

typedef int (*FastCreateReqFunc)(void*);
typedef void (*fpcM_ManagementFunc)(void);
typedef int (*fpcM_DrawIteraterFunc)(void*, void*);

inline fpc_ProcID fpcM_GetID(void* pProc) {
    return pProc != NULL ? ((base_process_class*)pProc)->mBsPcId : fpcM_ERROR_PROCESS_ID_e;
}
inline s16 fpcM_GetName(void* pProc) {
    return ((base_process_class*)pProc)->mProcName;
}
inline u32 fpcM_GetParam(void* pProc) {
    return ((base_process_class*)pProc)->mParameters;
}

inline void fpcM_SetParam(void* pProc, u32 param) {
    ((base_process_class*)pProc)->mParameters = param;
}

inline s16 fpcM_GetProfName(void* pProc) {
    return ((base_process_class*)pProc)->mProfName;
}

inline fpc_ProcID fpcM_Create(s16 procName, FastCreateReqFunc createFunc, void* params) {
    return fpcSCtRq_Request(fpcLy_CurrentLayer(), procName, (stdCreateFunc)createFunc, NULL, params);
}

inline s16 fpcM_DrawPriority(void* pProc) {
    return fpcLf_GetPriority((leafdraw_class*)pProc);
}

inline s32 fpcM_ChangeLayerID(void* pProc, int layerID) {
    return fpcPi_Change(&((base_process_class*)pProc)->mPi, layerID, fpcPi_CURRENT_e, fpcPi_CURRENT_e);
}

inline void fpcM_SetPriority(void* pProc, int priority) {
    fpcPi_Change(&((base_process_class*)pProc)->mPi, fpcLy_CURRENT_e, priority, fpcPi_CURRENT_e);
}

inline s32 fpcM_IsJustType(int type1, int type2) {
    return fpcBs_Is_JustOfType(type1, type2);
}

inline bool fpcM_IsFirstCreating(void* pProc) {
    return ((base_process_class*)pProc)->mInitState == 0;
}

inline process_profile_definition* fpcM_GetProfile(void* pProc) {
    return (process_profile_definition*)((base_process_class*)pProc)->mpProf;
}

inline void* fpcM_GetAppend(void* pProc) {
    return ((base_process_class*)pProc)->mpUserData;
}

inline BOOL fpcM_IsExecuting(fpc_ProcID id) {
    return fpcEx_IsExist(id);
}

inline void* fpcM_LyJudge(process_node_class* i_node, fpcLyIt_JudgeFunc i_func, void* i_data) {
    return fpcLyIt_Judge(&i_node->mLayer, i_func, i_data);
}

inline s8 fpcM_CreateResult(void* pProc) {
    return ((base_process_class*)pProc)->mCreateResult;
}

BOOL fpcM_Draw(void* pProc);
BOOL fpcM_DrawIterater(fpcM_DrawIteraterFunc pFunc);
BOOL fpcM_Execute(void* pProc);
BOOL fpcM_Delete(void* pProc);
BOOL fpcM_IsCreating(fpc_ProcID pID);
void fpcM_Management(fpcM_ManagementFunc pFunc1, fpcM_ManagementFunc pFunc2);
void fpcM_Init(void);
base_process_class* fpcM_FastCreate(s16 pProcTypeID, FastCreateReqFunc createFunc, void* pUserData,
                                    void* params);
s32 fpcM_IsPause(void* pProc, u8 i_flag);
void fpcM_PauseEnable(void* pProc, u8 i_flag);
void fpcM_PauseDisable(void* pProc, u8 i_flag);
void* fpcM_JudgeInLayer(uint i_layerID, fpcCtIt_JudgeFunc i_judgeFunc, void* i_data);

#endif
