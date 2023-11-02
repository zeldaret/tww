#ifndef JKRTHREAD_H
#define JKRTHREAD_H

#include "JSystem/JKernel/JKRHeap.h"
#include "dolphin/os/OSMessage.h"
#include "dolphin/os/OSTime.h"
#include "dolphin/types.h"

struct JKRThreadName_ {
    s32 id;
    char* name;
};

class JUTConsole;
class JKRThread : JKRDisposer {
public:
    JKRThread(u32 stack_size, int message_count, int param_3);
    JKRThread(OSThread* thread, int message_count);
    virtual ~JKRThread();

    /* vt[03] */ virtual void* run() { return NULL; }

    OSThread* getThreadRecord() const { return mThreadRecord; }
    void* getStack() const { return mStackMemory; }
    JKRHeap* getCurrentHeap() const { return mCurrentHeap; }
    s32 getCurrentHeapError() const { return mCurrentHeapError; }

    void setCurrentHeap(JKRHeap* heap) {
        mCurrentHeap = heap ? heap : JKRHeap::getCurrentHeap();
    }

protected:
    void resume() { OSResumeThread(mThreadRecord); }
    BOOL sendMessage(OSMessage message) {
        return OSSendMessage(&mMessageQueue, message, OS_MESSAGE_NOBLOCK);
    }
    BOOL sendMessageBlock(OSMessage message) {
        return OSSendMessage(&mMessageQueue, message, OS_MESSAGE_BLOCK);
    }
    OSMessage waitMessage() {
        OSMessage message;
        OSReceiveMessage(&mMessageQueue, &message, OS_MESSAGE_NOBLOCK);
        return message;
    }
    OSMessage waitMessageBlock() {
        OSMessage message;
        OSReceiveMessage(&mMessageQueue, &message, OS_MESSAGE_BLOCK);
        return message;
    }
    void jamMessageBlock(OSMessage message) {
        OSJamMessage(&mMessageQueue, message, OS_MESSAGE_BLOCK);
    }

private:
    /* 0x00 */  // vtable
    /* 0x04 */  // JKRDisposer
    /* 0x18 */ JSULink<JKRThread> mThreadListLink;
    /* 0x28 */ JKRHeap* mHeap;
    /* 0x2C */ OSThread* mThreadRecord;
    /* 0x30 */ OSMessageQueue mMessageQueue;
    /* 0x50 */ OSMessage* mMessages;
    /* 0x54 */ s32 mMessageCount;
    /* 0x58 */ void* mStackMemory;
    /* 0x5C */ u32 mStackSize;
    /* 0x60 */ JKRHeap* mCurrentHeap;
    /* 0x64 */ s32 mCurrentHeapError;

public:
    static void* start(void* param_1);
    static JKRThread* searchThread(OSThread* thread);
    static JSUList<JKRThread>& getList() { return (JSUList<JKRThread>&)sThreadList; }

    static JSUList<JKRThread> sThreadList;
    // static u8 sThreadList[12];
};

typedef void (*JKRThreadSwitch_PreCallback)(OSThread* current, OSThread* next);
typedef void (*JKRThreadSwitch_PostCallback)(OSThread* current, OSThread* next);

class JKRThreadSwitch {
public:
    JKRThreadSwitch(JKRHeap*);

    static JKRThreadSwitch* createManager(JKRHeap* heap);

    JKRThread* enter(JKRThread* param_1, int param_2);
    static void callback(OSThread* param_1, OSThread* param_2);

    static JKRThreadSwitch* getManager() { return sManager; }
    static u32 getTotalCount() { return sTotalCount; }

private:
    static JKRThreadSwitch* sManager;
    static u32 sTotalCount;
    static u32 sTotalStart;
    static JKRThreadSwitch_PreCallback mUserPreCallback;
    static JKRThreadSwitch_PostCallback mUserPostCallback;

private:
    /* 0x00 */  // vtable
    /* 0x04 */ JKRHeap* mHeap;
    /* 0x08 */ bool mSetNextHeap;

public:
    virtual ~JKRThreadSwitch() {}
};

struct JKRTask {
    static JSUList<JKRTask> sTaskList;
    static u8 sEndMesgQueue[32];
};

#endif /* JKRTHREAD_H */
