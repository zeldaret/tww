
#ifndef F_PC_DELETOR_H_
#define F_PC_DELETOR_H_

#include "dolphin/types.h"

typedef struct base_process_class base_process_class;

BOOL fpcDt_IsComplete(void);
BOOL fpcDt_ToDeleteQ(base_process_class* pProc);
BOOL fpcDt_ToQueue(base_process_class* pProc);
void fpcDt_Handler(void);
BOOL fpcDt_Delete(void* pProc);

#endif
