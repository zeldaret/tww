#ifndef JHIRMCC_H
#define JHIRMCC_H

#include "dolphin/types.h"

struct JHIMccContext;

BOOL JHIhioCallbackEnum(s32 type);
void JHIEnumDevices(s32*, u32*);
u32 JHIInitInterface();
bool JHINegotiateInterface(u32);
JHIMccContext JHIGetHiSpeedContext();
JHIMccContext JHIGetLowSpeedContext();
BOOL JHIInitMCC(JHIMccContext* pCtx, bool* param_1);

#endif /* JHIRMCC_H */
