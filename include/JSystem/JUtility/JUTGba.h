#ifndef JUTGBA_H
#define JUTGBA_H

#include "dolphin/types.h"

struct JUTGbaParam;
struct JUTGbaThreadVar;

typedef void (*JUTGba_Func)(JUTGbaParam*, void*);

class JUTGba {
public:
    JUTGba();

    static void create();
    void result_common(int, u32, u32*);
    void resultStatus_common(int, u32, u8*);
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
    void gbaThreadMain(void*);
    void gbaThread_sleep(s64);
    void gbaThread_Destroy(JUTGbaThreadVar*);
    void gbaThread_JoyBoot(JUTGbaThreadVar*);
    void gbaThread_InitProbe(JUTGbaThreadVar*);
    void gbaThread_Probe(JUTGbaThreadVar*);
    void gbaThread_Reset(JUTGbaThreadVar*);
    void gbaThread_Read(JUTGbaThreadVar*);
    void gbaThread_Write(JUTGbaThreadVar*);
    void gbaThread_GetStatus(JUTGbaThreadVar*);

    static JUTGba* getManager() { return sManager; }

    static JUTGba* sManager;
};

#endif /* JUTGBA_H */
