#ifndef JFWSYSTEM_H
#define JFWSYSTEM_H

#include "JSystem/JUtility/JUTAssert.h"

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
    static JUTResFont* getSystemFont() { return systemFont; }
    static void setMaxStdHeap(int max) {
        JUT_ASSERT(47, sInitCalled == 0);
        CSetUpParam::maxStdHeaps = max;
    }
    static void setSysHeapSize(u32 size) {
        JUT_ASSERT(50, sInitCalled == 0);
        CSetUpParam::sysHeapSize = size;
    }
    static void setFifoBufSize(u32 size) {
        JUT_ASSERT(53, sInitCalled == 0);
        CSetUpParam::fifoBufSize = size;
    }
    static void setAramAudioBufSize(u32 size) {
        JUT_ASSERT(58, sInitCalled == 0);
        CSetUpParam::aramAudioBufSize = size;
    }
    static void setAramGraphBufSize(u32 size) {
        JUT_ASSERT(61, sInitCalled == 0);
        CSetUpParam::aramGraphBufSize = size;
    }
    static void setRenderMode(GXRenderModeObj* p_modeObj) {
        JUT_ASSERT(80, sInitCalled == 0);
        CSetUpParam::renderMode = p_modeObj;
    }

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
