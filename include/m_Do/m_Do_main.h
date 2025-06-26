#ifndef M_DO_M_DO_MAIN_H
#define M_DO_M_DO_MAIN_H

#include "JSystem/JKernel/JKRExpHeap.h"
#include "dolphin/os/OSTime.h"

class JKRExpHeap;

void version_check();
s32 LOAD_COPYDATE(void*);

extern OSThread mainThread;

const int HeapCheckTableNum = 6;

class HeapCheck {
public:
    void CheckHeap1();
    s32 getUsedCount() const;
    void heapDisplay();

    u32& getUsedCountRef() { return mUsedCount; }
    u32& getTotalUsedSizeRef() { return mTotalUsedSize; }
    JKRExpHeap* getHeap() { return mHeap; }
    void setHeap(JKRExpHeap* i_heap) { mHeap = i_heap; }
    void setHeapSize(u32 i_size) { mTargetHeapSize = i_size; }
    s32 getMaxTotalUsedSize() { return mMaxTotalUsedSize; }
    s32 getMaxTotalFreeSize() { return mMaxTotalFreeSize; }
    const char* getName() const { return mName; }
    void saveRelBase() {
        mUsedCount = getUsedCount();
        mTotalUsedSize = mHeap->getTotalUsedSize();
    }

    u32 getRelUsedCount() const { return getUsedCount() - mUsedCount; }
    u32 getRelTotalUsedSize() const { return mHeap->getTotalUsedSize() - mTotalUsedSize; }

    /* 0x00 */ const char* mName;
    /* 0x04 */ JKRExpHeap* mHeap;
    /* 0x08 */ s32 mMaxTotalUsedSize;
    /* 0x0C */ s32 mMaxTotalFreeSize;
    /* 0x10 */ s32 field_0x10;
    /* 0x14 */ s32 field_0x14;
    /* 0x18 */ u32 mTargetHeapSize;
    /* 0x1C */ u32 mUsedCount;
    /* 0x20 */ u32 mTotalUsedSize;
};

struct mDoMain {
#if VERSION == VERSION_DEMO
    static int argument;
    static int gameHeapSize;
    static int archiveHeapSize;
#endif
    static char COPYDATE_STRING[18];
    static u32 memMargin;
    static OSTime sPowerOnTime;
    static OSTime sHungUpTime;
    static s8 developmentMode;
};

#endif /* M_DO_M_DO_MAIN_H */
