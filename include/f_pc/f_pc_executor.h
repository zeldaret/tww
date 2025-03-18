
#ifndef F_PC_EXECUTOR_H_
#define F_PC_EXECUTOR_H_

#include "f_pc/f_pc_layer_iter.h"
#include "f_pc/f_pc_line_iter.h"
#include "f_pc/f_pc_base.h"

typedef struct base_process_class base_process_class;

base_process_class* fpcEx_Search(fpcLyIt_JudgeFunc pFunc, void* pUserData);
base_process_class* fpcEx_SearchByID(fpc_ProcID id);
BOOL fpcEx_IsExist(fpc_ProcID id);
s32 fpcEx_ToLineQ(base_process_class* pProc);
BOOL fpcEx_ExecuteQTo(base_process_class* pProc);
BOOL fpcEx_Execute(base_process_class* pProc);
BOOL fpcEx_ToExecuteQ(base_process_class* pProc);
void fpcEx_Handler(fpcLnIt_QueueFunc pFunc);

inline base_process_class* fpcM_Search(fpcLyIt_JudgeFunc pFunc, void* pUserData) {
    return fpcEx_Search(pFunc, pUserData);
}

#endif
