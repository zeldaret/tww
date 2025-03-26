
#ifndef F_PC_METHOD_H_
#define F_PC_METHOD_H_

#include "dolphin/types.h"
#include "SSystem/SComponent/c_phase.h"

typedef int (*process_method_func)(void*);

typedef struct process_method_class {
    process_method_func mpCreateFunc;
    process_method_func mpDeleteFunc;
    process_method_func mpExecuteFunc;
    process_method_func mpIsDeleteFunc;
} process_method_class;

int fpcMtd_Method(process_method_func pFunc, void* pUserData);
BOOL fpcMtd_Execute(process_method_class* pMthd, void* pUserData);
BOOL fpcMtd_IsDelete(process_method_class* pMthd, void* pUserData);
BOOL fpcMtd_Delete(process_method_class* pMthd, void* pUserData);
cPhs_State fpcMtd_Create(process_method_class* pMthd, void* pUserData);

#endif
