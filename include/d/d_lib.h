#ifndef D_LIB_H
#define D_LIB_H

#include "dolphin/types.h"

class STControl {
public:
    void STControl(s16, s16, s16, s16, f32, f32, s16, s16);
    void setWaitParm(s16, s16, s16, s16, f32, f32, s16, s16);
    void init();
    void Xinit();
    void Yinit();
    void getValueStick();
    void getAngleStick();
    void checkTrigger();
    void checkLeftTrigger();
    void checkRightTrigger();
    void checkUpTrigger();
    void checkDownTrigger();

    /* 0x00 */ void* vtbl;
    /* 0x04 */ f32 field_0x04;
    /* 0x08 */ f32 field_0x08;
    /* 0x0C */ u8 field_0x0c;
    /* 0x0D */ u8 field_0x0d;
    /* 0x0E */ u16 field_0x0e;
    /* 0x10 */ u16 field_0x10;
    /* 0x12 */ u16 field_0x12;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ u16 field_0x18;
    /* 0x1A */ u16 field_0x1a;
    /* 0x1C */ u16 field_0x1c;
    /* 0x1E */ u16 field_0x1e;
    /* 0x20 */ u16 field_0x20;
    /* 0x22 */ u16 field_0x22;
    /* 0x24 */ s16 field_0x24;
    /* 0x26 */ s16 field_0x26;
};

#endif /* D_LIB_H */