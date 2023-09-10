#ifndef JFWSYSTEM_H
#define JFWSYSTEM_H

#include "dolphin/types.h"

typedef struct _GXRenderModeObj GXRenderModeObj;
class JKRExpHeap;
class JKRThread;
class JUTConsole;
class JUTConsoleManager;
class JUTDbPrint;
class JUTResFont;
struct ResFONT;

struct JFWSystem {
    struct CSetUpParam {
        static s32 maxStdHeaps;
        static u32 sysHeapSize;
        static u32 fifoBufSize;
        static u32 aramAudioBufSize;
        static u32 aramGraphBufSize;
        static u32 streamPriority;
        static u32 decompPriority;
        static u32 aPiecePriority;
        static ResFONT* systemFontRes;
        static GXRenderModeObj* renderMode;
        static u32 exConsoleBufferSize;
    };

    static void firstInit();
    static void init();

    static JUTConsole* getSystemConsole() { return systemConsole; }
    static JKRExpHeap* getSystemHeap() { return systemHeap; }

    static JKRExpHeap* rootHeap;
    static JKRExpHeap* systemHeap;
    static JKRThread* mainThread;
    static JUTDbPrint* debugPrint;
    static JUTResFont* systemFont;
    static JUTConsoleManager* systemConsoleManager;
    static JUTConsole* systemConsole;
    static bool sInitCalled;
};

#endif /* JFWSYSTEM_H */
