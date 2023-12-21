#ifndef D_D_VIBRATION_H
#define D_D_VIBRATION_H

#include "SSystem/SComponent/c_xyz.h"

class dVibration_c {
public:
    /* 0x00 */ int field_0x0;
    /* 0x04 */ int field_0x4;
    /* 0x08 */ s32 field_0x8;
    /* 0x0C */ int field_0xc;
    /* 0x10 */ int field_0x10;
    /* 0x14 */ cXyz field_0x14;
    /* 0x20 */ s32 field_0x20;
    /* 0x24 */ int field_0x24;
    /* 0x28 */ u32 field_0x28;
    /* 0x2C */ s32 field_0x2c;
    /* 0x30 */ int field_0x30;
    /* 0x34 */ int field_0x34;
    /* 0x38 */ cXyz field_0x38;
    /* 0x44 */ s32 field_0x44;
    /* 0x48 */ int field_0x48;
    /* 0x4C */ int field_0x4c;
    /* 0x50 */ s32 field_0x50;
    /* 0x54 */ s32 field_0x54;
    /* 0x58 */ s32 field_0x58;
    /* 0x5C */ s32 field_0x5c;
    /* 0x60 */ int field_0x60;
    /* 0x64 */ u32 field_0x64;
    /* 0x68 */ u32 field_0x68;
    /* 0x6C */ s32 field_0x6c;
    /* 0x70 */ s32 field_0x70;
    /* 0x74 */ s32 field_0x74;
    /* 0x78 */ s32 field_0x78;
    /* 0x7C */ int field_0x7c;

public:
    dVibration_c();
    virtual ~dVibration_c();

    int Run();
    bool StartShock(int i_strength, int, cXyz);
    bool StartQuake(u8 const*, int, int, cXyz);
    bool StartQuake(int, int, cXyz);
    int StopQuake(int);
    void Kill();
    bool CheckQuake();
    void setDefault();
    void Init();
    void Pause();
    void Remove();
};  // Size: 0x84

#endif /* D_D_VIBRATION_H */
