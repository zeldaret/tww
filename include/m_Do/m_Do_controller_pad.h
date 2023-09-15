#ifndef M_DO_CONTROLLER_PAD_H
#define M_DO_CONTROLLER_PAD_H

#include "JSystem/JUtility/JUTGamePad.h"
#include "SSystem/SComponent/c_API_controller_pad.h"

extern JUTGamePad* g_mDoCPd_gamePad[4];
extern interface_of_controller_pad g_mDoCPd_cpadInfo[4];

#define CPad_CHECK_HOLD_A(padNo) (g_mDoCPd_cpadInfo[padNo].mButtonHold0 & 1)
#define CPad_CHECK_HOLD_B(padNo) ((g_mDoCPd_cpadInfo[padNo].mButtonHold1 >> 7) & 1)
#define CPad_CHECK_HOLD_X(padNo) ((g_mDoCPd_cpadInfo[padNo].mButtonHold1 >> 6) & 1)
#define CPad_CHECK_HOLD_Y(padNo) ((g_mDoCPd_cpadInfo[padNo].mButtonHold1 >> 5) & 1)
#define CPad_CHECK_HOLD_Z(padNo) ((g_mDoCPd_cpadInfo[padNo].mButtonHold0 >> 3) & 1)
#define CPad_CHECK_HOLD_START(padNo) ((g_mDoCPd_cpadInfo[padNo].mButtonHold1 >> 4) & 1)
#define CPad_CHECK_HOLD_L(padNo) ((g_mDoCPd_cpadInfo[padNo].mButtonHold0 >> 1) & 1)
#define CPad_CHECK_HOLD_R(padNo) ((g_mDoCPd_cpadInfo[padNo].mButtonHold0 >> 2) & 1)
#define CPad_CHECK_HOLD_UP(padNo) ((g_mDoCPd_cpadInfo[padNo].mButtonHold0 >> 4) & 1)
#define CPad_CHECK_HOLD_DOWN(padNo) ((g_mDoCPd_cpadInfo[padNo].mButtonHold0 >> 5) & 1)
#define CPad_CHECK_HOLD_RIGHT(padNo) ((g_mDoCPd_cpadInfo[padNo].mButtonHold0 >> 6) & 1)
#define CPad_CHECK_HOLD_LEFT(padNo) ((g_mDoCPd_cpadInfo[padNo].mButtonHold0 >> 7) & 1)

#define CPad_CHECK_TRIG_A(padNo) (g_mDoCPd_cpadInfo[padNo].mButtonTrig0 & 1)
#define CPad_CHECK_TRIG_B(padNo) ((g_mDoCPd_cpadInfo[padNo].mButtonTrig1 >> 7) & 1)
#define CPad_CHECK_TRIG_X(padNo) ((g_mDoCPd_cpadInfo[padNo].mButtonTrig1 >> 6) & 1)
#define CPad_CHECK_TRIG_Y(padNo) ((g_mDoCPd_cpadInfo[padNo].mButtonTrig1 >> 5) & 1)
#define CPad_CHECK_TRIG_Z(padNo) ((g_mDoCPd_cpadInfo[padNo].mButtonTrig0 >> 3) & 1)
#define CPad_CHECK_TRIG_START(padNo) ((g_mDoCPd_cpadInfo[padNo].mButtonTrig1 >> 4) & 1)
#define CPad_CHECK_TRIG_L(padNo) ((g_mDoCPd_cpadInfo[padNo].mButtonTrig0 >> 1) & 1)
#define CPad_CHECK_TRIG_R(padNo) ((g_mDoCPd_cpadInfo[padNo].mButtonTrig0 >> 2) & 1)
#define CPad_CHECK_TRIG_UP(padNo) ((g_mDoCPd_cpadInfo[padNo].mButtonTrig0 >> 4) & 1)
#define CPad_CHECK_TRIG_DOWN(padNo) ((g_mDoCPd_cpadInfo[padNo].mButtonTrig0 >> 5) & 1)
#define CPad_CHECK_TRIG_RIGHT(padNo) ((g_mDoCPd_cpadInfo[padNo].mButtonTrig0 >> 6) & 1)
#define CPad_CHECK_TRIG_LEFT(padNo) ((g_mDoCPd_cpadInfo[padNo].mButtonTrig0 >> 7) & 1)

int mDoCPd_Create();
int mDoCPd_Read();

#endif
