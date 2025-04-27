#ifndef M_DO_CONTROLLER_PAD_H
#define M_DO_CONTROLLER_PAD_H

#include "JSystem/JUtility/JUTGamePad.h"
#include "SSystem/SComponent/c_API_controller_pad.h"

extern JUTGamePad* g_mDoCPd_gamePad[4];
extern interface_of_controller_pad g_mDoCPd_cpadInfo[4];

#define CPad_CHECK_HOLD_A(padNo)     (g_mDoCPd_cpadInfo[padNo].mButtonHold.a)
#define CPad_CHECK_HOLD_B(padNo)     (g_mDoCPd_cpadInfo[padNo].mButtonHold.b)
#define CPad_CHECK_HOLD_X(padNo)     (g_mDoCPd_cpadInfo[padNo].mButtonHold.x)
#define CPad_CHECK_HOLD_Y(padNo)     (g_mDoCPd_cpadInfo[padNo].mButtonHold.y)
#define CPad_CHECK_HOLD_Z(padNo)     (g_mDoCPd_cpadInfo[padNo].mButtonHold.z)
#define CPad_CHECK_HOLD_START(padNo) (g_mDoCPd_cpadInfo[padNo].mButtonHold.start)
#define CPad_CHECK_HOLD_L(padNo)     (g_mDoCPd_cpadInfo[padNo].mButtonHold.l)
#define CPad_CHECK_HOLD_R(padNo)     (g_mDoCPd_cpadInfo[padNo].mButtonHold.r)
#define CPad_CHECK_HOLD_UP(padNo)    (g_mDoCPd_cpadInfo[padNo].mButtonHold.up)
#define CPad_CHECK_HOLD_DOWN(padNo)  (g_mDoCPd_cpadInfo[padNo].mButtonHold.down)
#define CPad_CHECK_HOLD_RIGHT(padNo) (g_mDoCPd_cpadInfo[padNo].mButtonHold.right)
#define CPad_CHECK_HOLD_LEFT(padNo)  (g_mDoCPd_cpadInfo[padNo].mButtonHold.left)

#define CPad_CHECK_TRIG_A(padNo)     (g_mDoCPd_cpadInfo[padNo].mButtonTrig.a)
#define CPad_CHECK_TRIG_B(padNo)     (g_mDoCPd_cpadInfo[padNo].mButtonTrig.b)
#define CPad_CHECK_TRIG_X(padNo)     (g_mDoCPd_cpadInfo[padNo].mButtonTrig.x)
#define CPad_CHECK_TRIG_Y(padNo)     (g_mDoCPd_cpadInfo[padNo].mButtonTrig.y)
#define CPad_CHECK_TRIG_Z(padNo)     (g_mDoCPd_cpadInfo[padNo].mButtonTrig.z)
#define CPad_CHECK_TRIG_START(padNo) (g_mDoCPd_cpadInfo[padNo].mButtonTrig.start)
#define CPad_CHECK_TRIG_L(padNo)     (g_mDoCPd_cpadInfo[padNo].mButtonTrig.l)
#define CPad_CHECK_TRIG_R(padNo)     (g_mDoCPd_cpadInfo[padNo].mButtonTrig.r)
#define CPad_CHECK_TRIG_UP(padNo)    (g_mDoCPd_cpadInfo[padNo].mButtonTrig.up)
#define CPad_CHECK_TRIG_DOWN(padNo)  (g_mDoCPd_cpadInfo[padNo].mButtonTrig.down)
#define CPad_CHECK_TRIG_RIGHT(padNo) (g_mDoCPd_cpadInfo[padNo].mButtonTrig.right)
#define CPad_CHECK_TRIG_LEFT(padNo)  (g_mDoCPd_cpadInfo[padNo].mButtonTrig.left)

int mDoCPd_Create();
int mDoCPd_Read();

inline bool mDoCPd_L_LOCK_BUTTON(u32 i_padNo) {
    return g_mDoCPd_cpadInfo[i_padNo].mHoldLockL;
}

inline bool mDoCPd_L_LOCK_TRIGGER(u32 i_padNo) {
    return g_mDoCPd_cpadInfo[i_padNo].mTrigLockL;
}

inline bool mDoCPd_R_LOCK_BUTTON(u32 i_padNo) {
    return g_mDoCPd_cpadInfo[i_padNo].mHoldLockR;
}

inline bool mDoCPd_R_LOCK_TRIGGER(u32 i_padNo) {
    return g_mDoCPd_cpadInfo[i_padNo].mTrigLockR;
}

inline void mDoCPd_ANALOG_CONV(u8 analog, f32& param_1) {
    param_1 = analog * (1.0f / 15.0f);
    if (param_1 > 1.0f) {
        param_1 = 1.0f;
    }
}

inline void mDoCPd_TRIGGER_CONV(u8 analog, f32& param_1) {
    param_1 = analog * (1.0f / 140.0f);
    if (param_1 > 1.0f) {
        param_1 = 1.0f;
    }
}

#endif
