#ifndef OSALLOC_H
#define OSALLOC_H

#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSHeapDescriptor {
    /* 0x0 */ s32 size;
    /* 0x4 */ struct OSHeapCell* free;
    /* 0x8 */ struct OSHeapCell* allocated;
} OSHeapDescriptor;

typedef struct OSHeapCell {
    /* 0x00 */ struct OSHeapCell* prev;
    /* 0x04 */ struct OSHeapCell* next;
    /* 0x08 */ u32 size;
    /* 0x0C */ struct OSHeapDescriptor* hd;
    /* 0x10 */ u32 usedSize;
    /* 0x14 */ char field_0x14[0x20 - 0x14];
} OSHeapCell;

typedef s32 OSHeapHandle;

extern volatile s32 __OSCurrHeap;

#define OSRoundUp32B(x) (((u32)(x) + 0x1F) & ~(0x1F))
#define OSRoundDown32B(x) (((u32)(x)) & ~(0x1F))

#define OSRoundUp(x, align) (((x) + (align)-1) & (-(align)))
#define OSRoundUpPtr(x, align) ((void*)((((u32)(x)) + (align)-1) & (~((align)-1))))

#define OSRoundDown(x, align) ((x) & (-(align)))
#define OSRoundDownPtr(x, align) ((void*)(((u32)(x)) & (~((align)-1))))

static OSHeapCell* DLInsert(OSHeapCell* list, OSHeapCell* child);
void* OSAllocFromHeap(OSHeapHandle handle, u32 size);
void OSFreeToHeap(OSHeapHandle handle, void* ptr);
s32 OSSetCurrentHeap(OSHeapHandle handle);
void* OSInitAlloc(void* lo, void* hi, s32 maxHeaps);
OSHeapHandle OSCreateHeap(void* start, void* end);
void OSDestroyHeap(OSHeapHandle handle);
s32 OSCheckHeap(OSHeapHandle handle);
s32 OSReferentSize(void* ptr);
void OSDumpHeap(OSHeapHandle handle);

#ifdef __cplusplus
};
#endif

#endif /* OSALLOC_H */
