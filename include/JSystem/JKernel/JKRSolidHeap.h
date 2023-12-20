#ifndef JKRSOLIDHEAP_H
#define JKRSOLIDHEAP_H

#include "JSystem/JKernel/JKRHeap.h"

class JKRSolidHeap : public JKRHeap {
public:
    struct Unknown {
        /* 0x00 */ u32 field_0x0;
        /* 0x04 */ u32 field_0x4;
        /* 0x08 */ u32 field_0x8;
        /* 0x0C */ void* field_0xc;
        /* 0x10 */ Unknown* mNext;
    };

protected:
    JKRSolidHeap(void*, u32, JKRHeap*, bool);
    virtual ~JKRSolidHeap();

    void* allocFromHead(u32, int);
    void* allocFromTail(u32, int);

    static s32 getUsedSize(JKRSolidHeap* heap) { return heap->mSize - heap->getTotalFreeSize(); }

public:
    /* vt[04] */ virtual u32 getHeapType(void) { return 'SLID'; } /* override */
    /* vt[05] */ virtual bool check(void);               /* override */

    /* vt[07] */ virtual bool dump(void);                /* override */
    /* vt[08] */ virtual void do_destroy(void);          /* override */
    /* vt[09] */ virtual void* do_alloc(u32, int);       /* override */
    /* vt[10] */ virtual void do_free(void*);            /* override */
    /* vt[11] */ virtual void do_freeAll(void);          /* override */
    /* vt[12] */ virtual void do_freeTail(void);         /* override */
    /* vt[13] */ virtual void do_freeFill(void);     /* override */
    /* vt[14] */ virtual s32 do_resize(void*, u32);      /* override */
    /* vt[15] */ virtual s32 do_getSize(void*);          /* override */
    /* vt[16] */ virtual s32 do_getFreeSize(void) { return mFreeSize;} /* override */
    /* vt[17] */ virtual void* do_getMaxFreeBlock(void) { return mSolidHead; } /* override */
    /* vt[18] */ virtual s32 do_getTotalFreeSize(void) { return getFreeSize(); }  /* override */

    /* vt[21] */ virtual void state_register(JKRHeap::TState*, u32) const; /* override */
    /* vt[22] */ virtual bool state_compare(JKRHeap::TState const&,
                                            JKRHeap::TState const&) const; /* override */

private:
    /* 0x00 */  // vtable
    /* 0x04 */  // JKRHeap
    /* 0x6C */ u32 mFreeSize;
    /* 0x70 */ u8* mSolidHead;
    /* 0x74 */ u8* mSolidTail;
    /* 0x78 */ Unknown* field_0x78;

public:
    s32 adjustSize(void);

    static JKRSolidHeap* create(u32, JKRHeap*, bool);
};

#endif /* JKRSOLIDHEAP_H */
