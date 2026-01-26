#ifndef JKRSTDHEAP_H
#define JKRSTDHEAP_H

#include "JSystem/JKernel/JKRHeap.h"
#include "dolphin/os/OSAlloc.h"

class JKRStdHeap : public JKRHeap {
public:
    static JKRStdHeap* create(u32, JKRHeap*, bool);
    void do_destroy();
    JKRStdHeap(void*, u32, JKRHeap*, bool);
    ~JKRStdHeap();
    void* do_alloc(u32, int);
    void do_free(void*);
    void do_freeAll();
    void do_freeTail();
    s32 do_resize(void*, u32);
    s32 do_getFreeSize();
    void* do_getMaxFreeBlock();
    void state_register(JKRHeap::TState*, u32) const;
    bool state_compare(const JKRHeap::TState&, const JKRHeap::TState&) const;
#if VERSION > VERSION_DEMO
    void do_freeFill();
#endif
    u32 getHeapType() { return 'STDH'; }
    bool check() { return OSCheckHeap(mHeapHandle) != -1; }
    bool dump() {
        OSDumpHeap(mHeapHandle);
        return OSCheckHeap(mHeapHandle) != -1;
    }
    s32 do_getSize(void* ptr) { return OSReferentSize(ptr); };
    s32 do_getTotalFreeSize() { return getFreeSize(); };

    OSHeapHandle mHeapHandle;
};

#endif /* JKRSTDHEAP_H */
