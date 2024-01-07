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
        // TODO
        u32 getUseCounter() {}
        void setUseCounter(u32) {}
        u32 getDataNumber() {}
        void setDataNumber(u32) {}
        u32 getEndAddress() {}
        void setEndAddress(u32) {}

        /* 0x00 */ u8 mStatus;
        /* 0x04 */ void* mPointer;
        /* 0x08 */ u32 field_0x8;
        /* 0x0C */ u32 field_0xc;
        /* 0x10 */ u32 field_0x10;
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
