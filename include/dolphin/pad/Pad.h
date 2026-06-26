#ifndef PAD_H
#define PAD_H

#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSContext OSContext;

#define PAD_CHAN0_BIT 0x80000000
#define PAD_CHAN1_BIT 0x40000000
#define PAD_CHAN2_BIT 0x20000000
#define PAD_CHAN3_BIT 0x10000000

#define PAD_SPEC_0 0
#define PAD_SPEC_1 1
#define PAD_SPEC_2 2
#define PAD_SPEC_3 3
#define PAD_SPEC_4 4
#define PAD_SPEC_5 5

#define PAD_MOTOR_STOP 0
#define PAD_MOTOR_RUMBLE 1
#define PAD_MOTOR_STOP_HARD 2

#define PAD_ERR_NONE 0
#define PAD_ERR_NO_CONTROLLER -1
#define PAD_ERR_NOT_READY -2
#define PAD_ERR_TRANSFER -3

#define PAD_BUTTON_LEFT 0x0001
#define PAD_BUTTON_RIGHT 0x0002
#define PAD_BUTTON_DOWN 0x0004
#define PAD_BUTTON_UP 0x0008
#define PAD_TRIGGER_Z 0x0010
#define PAD_TRIGGER_R 0x0020
#define PAD_TRIGGER_L 0x0040
#define PAD_BUTTON_A 0x0100
#define PAD_BUTTON_B 0x0200
#define PAD_BUTTON_X 0x0400
#define PAD_BUTTON_Y 0x0800
#define PAD_BUTTON_MENU 0x1000
#define PAD_BUTTON_START 0x1000

typedef struct PADStatus {
    /* 0x00 */ u16 button;
    /* 0x02 */ s8 stickX;
    /* 0x03 */ s8 stickY;
    /* 0x04 */ s8 substickX;
    /* 0x05 */ s8 substickY;
    /* 0x06 */ u8 triggerLeft;
    /* 0x07 */ u8 triggerRight;
    /* 0x08 */ u8 analogA;
    /* 0x09 */ u8 analogB;
    /* 0x0A */ s8 err;
} PADStatus;

typedef struct PADClampRegion {
    u8 minTrigger;
    u8 maxTrigger;
    s8 minStick;
    s8 maxStick;
    s8 xyStick;
    s8 minSubstick;
    s8 maxSubstick;
    s8 xySubstick;
    s8 radStick;
    s8 radSubstick;
} PADClampRegion;

typedef void (*PADSamplingCallback)(void);

BOOL PADInit(void);
void PADSetAnalogMode(u32 mode);
void PADSetSpec(u32 spec);
BOOL PADReset(u32 mask);
void PADClampCircle(PADStatus* status);
void PADClamp(PADStatus* status);
u32 PADRead(PADStatus* status);
void PADControlMotor(s32 channel, u32 command);
BOOL PADRecalibrate(u32 mask);
PADSamplingCallback PADSetSamplingCallback(PADSamplingCallback callback);
static void PADOriginCallback(s32 chan, u32 error, OSContext* context);
static void PADOriginUpdateCallback(s32 chan, u32 error, OSContext* context);
static void PADProbeCallback(s32 chan, u32 error, OSContext* context);
static void PADTypeAndStatusCallback(s32 chan, u32 type);
static void PADReceiveCheckCallback(s32 chan, u32 type);

extern u32 __PADSpec;
extern u32 __PADFixBits;

#ifdef __cplusplus
};
#endif

#endif /* PAD_H */
