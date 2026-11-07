#ifndef JAISEQUENCEHEAP_H
#define JAISEQUENCEHEAP_H

#include "dolphin/types.h"

namespace JAInter {
    class HeapBlock {
    public:
        HeapBlock();

        u8 getStatus() { return mStatus; }
        void setStatus(u8 status) { mStatus = status; }
        void* getPointer() { return mPointer; }
        void setPointer(void* pointer) { mPointer = pointer; }
        u32 getDataNumber() { return mDataNumber;}
        void setDataNumber(u32 number) { mDataNumber = number; }
        u32 getEndAddress() { return mEndAddress; }
        void setEndAddress(u32 address) { mEndAddress = address; }
        u32 getUseCounter() { return mUseCounter; }
        void setUseCounter(u32 counter) { mUseCounter = counter; }

        /* 0x00 */ u8 mStatus;
        /* 0x04 */ void* mPointer;
        /* 0x08 */ u32 mDataNumber;
        /* 0x0C */ u32 mEndAddress;
        /* 0x10 */ u32 mUseCounter;
    };

    namespace HeapMgr {
        void init(u8, u32, u8, u32);
        JAInter::HeapBlock* getAutoHeapPointer();
        void* checkOnMemory(u32, u8*);
        void releaseAutoHeapPointer(u8);
        u8 checkUsefulAutoHeapPosition();
        void* getFreeAutoHeapPointer(u8, u32);
        void* getFreeStayHeapPointer(u32, u32);
        void setAutoHeapLoadedFlag(u8, u8);

        extern HeapBlock* sAutoHeap;
        extern HeapBlock* sStayHeap;
        extern u32 sAutoHeapCount;
        extern u32 sStayHeapCount;
    }
}

#endif /* JAISEQUENCEHEAP_H */
