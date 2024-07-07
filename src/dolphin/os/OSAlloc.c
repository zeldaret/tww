#include "dolphin/os/OSAlloc.h"

static OSHeapCell* DLInsert(OSHeapCell* list, OSHeapCell* child) {
    OSHeapCell* prev = NULL;
    OSHeapCell* next = list;

    for (; next != NULL; prev = next, next = next->next) {
        if ((char*)child <= (char*)next) {
            break;
        }
    }

    child->next = next;
    child->prev = prev;

    if (next != NULL) {
        next->prev = child;

        if ((char*)child + child->size == (char*)next) {
            child->size += next->size;
            next = next->next;
            child->next = next;
            if (next != NULL) {
                next->prev = child;
            }
        }
    }

    if (prev != NULL) {
        prev->next = child;

        if ((char*)prev + prev->size == (char*)child) {
            prev->size += child->size;
            prev->next = next;
            if (next != NULL) {
                next->prev = prev;
            }
        }

        return list;
    } else {
        return child;
    }
}

inline OSHeapCell* DLExtract(OSHeapCell* list, OSHeapCell* child) {
    if (child->next != NULL) {
        child->next->prev = child->prev;
    }

    if (child->prev == NULL) {
        return child->next;
    }

    child->prev->next = child->next;
    return list;
}

static OSHeapDescriptor* HeapArray;

void OSFreeToHeap(OSHeapHandle handle, void* ptr) {
    OSHeapDescriptor* hd = &HeapArray[handle];
    OSHeapCell* cell = (OSHeapCell*)((char*)ptr - sizeof(OSHeapCell));
    hd->usedList = DLExtract(hd->usedList, cell);
    hd->freeList = DLInsert(hd->freeList, cell);
}

volatile s32 __OSCurrHeap = -1;

s32 OSSetCurrentHeap(OSHeapHandle handle) {
    s32 old = __OSCurrHeap;
    __OSCurrHeap = handle;
    return old;
}

static s32 NumHeaps;

static void* ArenaStart;

static void* ArenaEnd;

void* OSInitAlloc(void* lo, void* hi, s32 maxHeaps) {
    u32 totalSize = maxHeaps * sizeof(OSHeapDescriptor);
    int i;

    HeapArray = lo;
    NumHeaps = maxHeaps;

    for (i = 0; i < NumHeaps; i++) {
        OSHeapDescriptor* hd = &HeapArray[i];
        hd->size = -1;
        
        hd->freeList = hd->usedList = NULL;
    }

    __OSCurrHeap = -1;

    lo = (u8*)HeapArray + totalSize;
	lo = OSRoundUpPtr(lo, 0x20);

	ArenaStart = lo;
	ArenaEnd = OSRoundDownPtr(hi, 0x20);

    return ArenaStart;
}

OSHeapHandle OSCreateHeap(void* start, void* end) {
    int i;
	OSHeapCell* cell = OSRoundUpPtr(start, 0x20);
	end = OSRoundDownPtr(end, 0x20);

	for (i = 0; i < NumHeaps; i++) {
		OSHeapDescriptor* hd = &HeapArray[i];

		if (hd->size < 0) {
			hd->size = (u8*)end - (u8*)cell;
			cell->prev = NULL;
			cell->next = NULL;
			cell->size = hd->size;
			hd->freeList = cell;
			hd->usedList = NULL;
			return i;
		}
	}

	return -1;
}
