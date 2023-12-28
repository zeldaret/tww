//
// Generated by dtk
// Translation Unit: JKRStdHeap.cpp
//

#include "JSystem/JKernel/JKRStdHeap.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "JSystem/JUtility/JUTConsole.h"
#include "new.h"
#include "global.h"

/* 802B0F34-802B0FE0       .text create__10JKRStdHeapFUlP7JKRHeapb */
JKRStdHeap* JKRStdHeap::create(u32 size, JKRHeap* parent, bool errorFlag) {
    /* Nonmatching */
    if (!parent) {
        parent = sRootHeap;
    }
    if (size == -1) {
        size = parent->getMaxAllocatableSize(0x20);
    }

    u32 alignedSize = ALIGN_PREV(size, 0x20);
    if (alignedSize < 0xC0) {
        return NULL;
    }
    u8* memory = (u8*)JKRAllocFromHeap(parent, alignedSize, 0x20);
    u32 stdHeapSize = ALIGN_NEXT(sizeof(JKRStdHeap), 0x20);
    u8* dataPtr = (memory + stdHeapSize);
    if (!memory) {
        return NULL;
    }
    JKRStdHeap* newHeap = new(memory) JKRStdHeap(dataPtr, alignedSize - stdHeapSize, parent, errorFlag);
    return newHeap;
}

/* 802B0FE0-802B1040       .text do_destroy__10JKRStdHeapFv */
void JKRStdHeap::do_destroy() {
    JKRHeap* heap = mChildTree.getParent()->getObject();
    if (heap) {
        this->~JKRStdHeap();
        free(this, heap);
    }
}

/* 802B1040-802B108C       .text __ct__10JKRStdHeapFPvUlP7JKRHeapb */
JKRStdHeap::JKRStdHeap(void* data, u32 size, JKRHeap* parent, bool errorFlag) : JKRHeap(data, size, parent, errorFlag) {
    mHeapHandle = OSCreateHeap(mStart, mEnd);
}

/* 802B108C-802B1104       .text __dt__10JKRStdHeapFv */
JKRStdHeap::~JKRStdHeap() {
    dispose();
    if (mHeapHandle != -1) {
        OSDestroyHeap(mHeapHandle);
    }
}

static void dummy() {
    OSReport("JKRStdHeap.cpp");
    OSReport("allocFixed from %x to %x in heap %x");
    OSReport("allocFixed: cannot alloc memory (from %x to %x).\n");
}

/* 802B1104-802B11A4       .text do_alloc__10JKRStdHeapFUli */
void* JKRStdHeap::do_alloc(u32 size, int alignment) {
    if (mHeapHandle == -1) {
        return NULL;
    }
    void* ptr = OSAllocFromHeap(mHeapHandle, size);
    if (!ptr) {
        JUTWarningConsole_f("alloc: cannot alloc memory (0x%x byte).\n", size);
        if (mErrorFlag == true && mErrorHandler) {
            mErrorHandler(this, size, alignment);
        }
    }
    return ptr;
    /* Nonmatching */
}

/* 802B11A4-802B1228       .text do_free__10JKRStdHeapFPv */
void JKRStdHeap::do_free(void* ptr) {
    if (mHeapHandle != -1) {
        if (mStart <= ptr && ptr <= mEnd) {
            OSFreeToHeap(mHeapHandle, ptr);
        } else {
            JUT_WARN(279, "free: memblock %x not in heap %x", ptr, this);
        }
    }
    /* Nonmatching */
}

/* 802B1228-802B1278       .text do_freeAll__10JKRStdHeapFv */
void JKRStdHeap::do_freeAll() {
    /* Nonmatching */
    if (mHeapHandle == -1) {
        return;
    }
    JKRHeap::callAllDisposer();
    OSDestroyHeap(mHeapHandle);
    mHeapHandle = OSCreateHeap(mStart, mEnd);
}

/* 802B1278-802B12A4       .text do_freeTail__10JKRStdHeapFv */
void JKRStdHeap::do_freeTail() {
    JUTWarningConsole("freeTail: freeTail() is not work\n");
}

/* 802B12A4-802B12D8       .text do_resize__10JKRStdHeapFPvUl */
s32 JKRStdHeap::do_resize(void*, u32) {
    JUTWarningConsole_f("resize: cannot resize memory block (%08x: %d)\n");
    return -1;
}

/* 802B12D8-802B1308       .text do_getFreeSize__10JKRStdHeapFv */
s32 JKRStdHeap::do_getFreeSize() {
    JUTWarningConsole("getFreeSize: cannot get free size\n");
    return -1;
}

/* 802B1308-802B1338       .text do_getMaxFreeBlock__10JKRStdHeapFv */
void* JKRStdHeap::do_getMaxFreeBlock() {
    JUTWarningConsole("getFreeSize: cannot get free block");
    return NULL;
}

/* 802B1338-802B13F0       .text state_register__10JKRStdHeapCFPQ27JKRHeap6TStateUl */
void JKRStdHeap::state_register(JKRHeap::TState* p, u32 id) const {
    JUT_ASSERT(370, p != 0);
    JUT_ASSERT(371, p->getHeap() == this);
    setState_u32ID_(p, id);
    setState_uUsedSize_(p, 0);
    setState_u32CheckCode_(p, 0);
}

/* 802B13F0-802B1490       .text state_compare__10JKRStdHeapCFRCQ27JKRHeap6TStateRCQ27JKRHeap6TState */
bool JKRStdHeap::state_compare(const JKRHeap::TState& r1, const JKRHeap::TState& r2) const {
    JUT_ASSERT(394, r1.getHeap() == r2.getHeap());
    bool result = true;
    if (r1.mCheckCode != r2.mCheckCode) {
        result = false;
    }

    if (r1.mUsedSize != r2.mUsedSize) {
        result = false;
    }

    return result;
}

/* 802B1490-802B1494       .text do_freeFill__10JKRStdHeapFv */
void JKRStdHeap::do_freeFill() {}
