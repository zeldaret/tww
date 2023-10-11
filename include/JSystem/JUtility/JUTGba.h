#ifndef JUTGBA_H
#define JUTGBA_H

#include "dolphin/os/OSMessage.h"
#include "dolphin/os/OSTime.h"

struct JUTGbaParam;

typedef void (*JUTGba_Func)(JUTGbaParam*, void*);

struct JUTGbaParam {
    /* 0x00 */ OSMessageQueue msg_q;
    /* 0x20 */ OSMessage msg[1];
    /* 0x24 */ u32 field_0x24;
    /* 0x28 */ s32 channel;
    /* 0x2C */ u8* program;
    /* 0x30 */ int length;
    /* 0x34 */ int palette_color;
    /* 0x38 */ int palette_speed;
    /* 0x3C */ u8 field_0x3c;
    /* 0x40 */ int field_0x40;
    /* 0x44 */ u8 status;
    /* 0x48 */ u8* field_0x48;
    /* 0x4C */ JUTGba_Func field_0x4c;
    /* 0x50 */ void* field_0x50;
    /* 0x54 */ u8 field_0x54;
    /* 0x58 */ int field_0x58;
};

struct JUTGbaThreadVar {
    /* 0x00 */ JUTGbaParam* field_0x0;
    /* 0x08 */ OSTime field_0x8;
    /* 0x10 */ u32 field_0x10;
    /* 0x14 */ u32 field_0x14;
    /* 0x18 */ u32 field_0x18;
    /* 0x1C */ s32 field_0x1c;
};

class JUTGba {
public:
    JUTGba();

    static JUTGba* create();
    int result_common(int, u32, u32*);
    int resultStatus_common(int, u32, u8*);
    void doJoyBoot(int, s32, s32, u8*, u32, JUTGba_Func, void*);
    int resultJoyBoot(int, u8*);
    void doInitProbe(int, JUTGba_Func, void*);
    int resultInitProbe(int, u32*);
    void doProbe(int, JUTGba_Func, void*);
    BOOL resultProbe(int, u32*);
    void doReset(int, JUTGba_Func, void*);
    BOOL resultReset(int, u8*);
    void doRead(int, u8*, JUTGba_Func, void*);
    BOOL resultRead(int, u8*);
    void doWrite(int, u8*, JUTGba_Func, void*);
    BOOL resultWrite(int, u8*);
    void doGetStatus(int, JUTGba_Func, void*);
    BOOL resultGetStatus(int, u8*);
    static void* gbaThreadMain(void*);
    void gbaThread_sleep(OSTime);
    void gbaThread_Destroy(JUTGbaThreadVar*);
    int gbaThread_JoyBoot(JUTGbaThreadVar*);
    int gbaThread_InitProbe(JUTGbaThreadVar*);
    int gbaThread_Probe(JUTGbaThreadVar*);
    int gbaThread_Reset(JUTGbaThreadVar*);
    int gbaThread_Read(JUTGbaThreadVar*);
    int gbaThread_Write(JUTGbaThreadVar*);
    int gbaThread_GetStatus(JUTGbaThreadVar*);

    static JUTGba* getManager() { return sManager; }

    static JUTGba* sManager;

    /* 0x0000 */ OSThread mThreads[4];
    /* 0x0C60 */ u8 mStacks[4][4096];
    /* 0x4C60 */ JUTGbaParam mParams[4];
    /* 0x4DD0 */ u8 field0x4dd0[16];
};

#endif /* JUTGBA_H */
