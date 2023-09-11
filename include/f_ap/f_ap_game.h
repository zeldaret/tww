#ifndef F_AP_GAME_H
#define F_AP_GAME_H

#include "JSystem/JUtility/TColor.h"

void fapGm_After();
void fapGm_Create();
void fapGm_Execute();

class fapGm_HIO_c {
public:
    /* 80018944 */ fapGm_HIO_c();
    /* 80018AE0 */ virtual ~fapGm_HIO_c();

    /* 0x04 */ u8 field_0x04[0x06 - 0x04];
    /* 0x06 */ u8 mDisplayMeter;
    /* 0x07 */ u8 field_0x07[0x0C - 0x07];
    /* 0x0C */ f32 field_0x0c;
    /* 0x10 */ u8 field_0x10[0x24 - 0x10];
    /* 0x24 */ f32 mTriggerThreshLo;
    /* 0x28 */ f32 mTriggerThreshHi;
    /* 0x2C */ u16 field_0x2c;
    /* 0x2E */ u16 field_0x2e;
    /* 0x30 */ u8 field_0x30[0x4C - 0x30];
    /* 0x4C */ u16 field_0x4c;
    /* 0x4E */ u16 field_0x4e;
    /* 0x50 */ u16 field_0x50;
    /* 0x52 */ u16 field_0x52;
    /* 0x54 */ u16 field_0x54;
};  // Size: 0x58

extern fapGm_HIO_c g_HIO;

#endif /* F_AP_GAME_H */
