//
// Generated by dtk
// Translation Unit: JKRThread.cpp
//

#include "JSystem/JKernel/JKRThread.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "JSystem/JUtility/JUTConsole.h"
#include "dolphin/types.h"

JSUList<JKRThread> JKRThread::sThreadList;
JKRThreadSwitch* JKRThreadSwitch::sManager;
OSThread* preEnd;
JKRThreadSwitch_PreCallback JKRThreadSwitch::mUserPreCallback;
JKRThreadSwitch_PostCallback JKRThreadSwitch::mUserPostCallback;

/* 802B3D1C-802B3E38       .text __ct__9JKRThreadFUlii */
JKRThread::JKRThread(u32 stack_size, int message_count, int param_3) : mThreadListLink(this) {
    mHeap = JKRHeap::findFromRoot(this);
    if (mHeap == NULL) {
        mHeap = JKRGetSystemHeap();
    }

    mStackSize = stack_size & 0xffffffe0;
    mStackMemory = JKRAllocFromHeap(mHeap, mStackSize, 0x20);
    mThreadRecord = (OSThread*)JKRAllocFromHeap(mHeap, sizeof(OSThread), 0x20);

    void* stackBase = (void*)((int)mStackMemory + mStackSize);
    OSCreateThread(mThreadRecord, (void*)start, this, stackBase, mStackSize, param_3, 1);

    mMessageCount = message_count;
    mMessages = (OSMessage*)JKRAllocFromHeap(mHeap, mMessageCount * sizeof(OSMessage), 0);

    OSInitMessageQueue(&mMessageQueue, mMessages, mMessageCount);
    getList().append(&mThreadListLink);

    mCurrentHeap = NULL;
    mCurrentHeapError = NULL;
}

/* 802B3E38-802B3EFC       .text __ct__9JKRThreadFP8OSThreadi */
JKRThread::JKRThread(OSThread* thread, int message_count) : mThreadListLink(this) {
    mHeap = NULL;
    mThreadRecord = thread;
    mStackSize = (u32)thread->stack_end - (u32)thread->stack_base;
    mStackMemory = thread->stack_base;

    mMessageCount = message_count;
    mMessages = (OSMessage*)JKRGetSystemHeap()->alloc(mMessageCount * sizeof(OSMessage), 4);

    OSInitMessageQueue(&mMessageQueue, mMessages, mMessageCount);
    getList().append(&mThreadListLink);

    mCurrentHeap = NULL;
    mCurrentHeapError = NULL;
}

/* 802B3EFC-802B3FD4       .text __dt__9JKRThreadFv */
JKRThread::~JKRThread() {
    getList().remove(&mThreadListLink);

    if (mHeap) {
        BOOL result = OSIsThreadTerminated(mThreadRecord);
        if (result == FALSE) {
            OSDetachThread(mThreadRecord);
            OSCancelThread(mThreadRecord);
        }
        JKRFreeToHeap(mHeap, mStackMemory);
        JKRFreeToHeap(mHeap, mThreadRecord);
    }
    JKRFree(mMessages);
}

/* 802B3FD4-802B4000       .text start__9JKRThreadFPv */
void* JKRThread::start(void* param) {
    JKRThread* thread = (JKRThread*)param;
    return thread->run();
}

/* 802B4000-802B4050       .text __ct__15JKRThreadSwitchFP7JKRHeap */
JKRThreadSwitch::JKRThreadSwitch(JKRHeap* param_0) {
    mHeap = param_0;
    OSSetSwitchThreadCallback(JKRThreadSwitch::callback);
    mSetNextHeap = true;
}

/* 802B4050-802B40EC       .text createManager__15JKRThreadSwitchFP7JKRHeap */
JKRThreadSwitch* JKRThreadSwitch::createManager(JKRHeap* heap) {
    JUT_ASSERT(184, sManager == NULL);

    if (!heap) {
        heap = JKRGetCurrentHeap();
    }

    sManager = new (heap, 0) JKRThreadSwitch(heap);
    return sManager;
}

/* 802B40EC-802B41DC       .text callback__15JKRThreadSwitchFP8OSThreadP8OSThread */
void JKRThreadSwitch::callback(OSThread* current, OSThread* next) {
    if (mUserPreCallback) {
        (*mUserPreCallback)(current, next);
    }

    if (!current && !next) {
        preEnd = current;
        current = NULL;
    }

    if (!current && !next) {
        current = preEnd;
        preEnd = NULL;
    }

    JSUList<JKRThread>& threadList = JKRThread::getList();
    JSUListIterator<JKRThread> iterator;
    for (iterator = threadList.getFirst(); iterator != threadList.getEnd(); ++iterator) {
        JKRThread* thread = iterator.getObject();

        if (thread->getThreadRecord() == current) {
            thread->setCurrentHeap(JKRHeap::getCurrentHeap());
        }

        if (thread->getThreadRecord() == next) {
            if (sManager->mSetNextHeap) {
                JKRHeap* next_heap = thread->getCurrentHeap();
#if VERSION == VERSION_DEMO
                if (!next_heap) {
                    next_heap = JKRHeap::getCurrentHeap();
                } else if (!JKRHeap::getRootHeap()->isSubHeap(next_heap)) {
                    switch (thread->getCurrentHeapError()) {
                    case 0:
                        JUT_ASSERT(272, FALSE &&"JKRThreadSwitch: currentHeap destroyed.");
                        break;
                    case 1:
                        JUTWarningConsole("JKRThreadSwitch: currentHeap destroyed.\n");
                        next_heap = JKRHeap::getCurrentHeap();
                        break;
                    case 2:
                        next_heap = JKRHeap::getCurrentHeap();
                        break;
                    case 3:
                        next_heap = JKRHeap::getSystemHeap();
                        break;
                    }
                }
#endif
                next_heap->becomeCurrentHeap();
            }
        }
    }

    if (mUserPostCallback) {
        (*mUserPostCallback)(current, next);
    }
}

static void dummy() {
    OSReport("Cannot create JKRTask Manager.");
    OSReport("sManager != 0");
}
