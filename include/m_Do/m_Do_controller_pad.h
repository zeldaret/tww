#ifndef M_DO_CONTROLLER_PAD_H
#define M_DO_CONTROLLER_PAD_H

#include "JSystem/JUtility/JUTGamePad.h"
#include "SSystem/SComponent/c_API_controller_pad.h"

extern JUTGamePad* g_mDoCPd_gamePad[4];
extern interface_of_controller_pad g_mDoCPd_cpadInfo[4];

void mDoCPd_Create();
void mDoCPd_Read();

#endif
