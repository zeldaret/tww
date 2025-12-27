
#ifndef F_PC_LOAD_H_
#define F_PC_LOAD_H_

#include "SSystem/SComponent/c_phase.h"
#include "dolphin/types.h"

BOOL fpcLd_Use(s16 procName);
BOOL fpcLd_IsLoaded(s16 procName);
void fpcLd_Free(s16 procName);
cPhs_State fpcLd_Load(s16 procName);

#endif
