#include "dolphin/os/OSAlloc.h"
#include "dolphin/os/OS.h"

#define ALIGNMENT  32
#define MINOBJSIZE 64

#define HEADERSIZE 32

#define InRange(addr, start, end) ((u8*)(start) <= (u8*)(addr) && (u8*)(addr) < (u8*)(end))
#define OFFSET(addr, align)       (((u32)(addr) & ((align)-1)))

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

static inline void* DLAddFront(OSHeapCell* neighbor, OSHeapCell* cell)
{
    cell->next = neighbor;
    cell->prev = NULL;
    if (neighbor != NULL)
        neighbor->prev = cell;
    return cell;
}

void* OSAllocFromHeap(OSHeapHandle heap, u32 size)
{
    OSHeapDescriptor* hd = &HeapArray[heap];
    s32 sizeAligned = OSRoundUp32B(ALIGNMENT + size);
    OSHeapCell* cell;
    OSHeapCell* oldTail;
    u32 leftoverSpace;

    // find first cell with enough capacity
    for (cell = hd->free; cell != NULL; cell = cell->next) {
        if (sizeAligned <= (s32)cell->size)
            break;
    }
    if (cell == NULL)
        return NULL;

    leftoverSpace = cell->size - sizeAligned;
    if (leftoverSpace < MINOBJSIZE) {
        // remove this cell from the free list
        hd->free = DLExtract(hd->free, cell);
    } else {
        // remove this cell from the free list and make a new cell out of the
        // remaining space
        OSHeapCell* newcell = (void*)((u8*)cell + sizeAligned);
        cell->size               = sizeAligned;
        newcell->size            = leftoverSpace;
        newcell->prev            = cell->prev;
        newcell->next            = cell->next;
        if (newcell->next != NULL)
            newcell->next->prev = newcell;
        if (newcell->prev != NULL)
            newcell->prev->next = newcell;
        else
            hd->free = newcell;
    }

    // add the cell to the beginning of the allocated list
    hd->allocated = DLAddFront(hd->allocated, cell);

    return (u8*)cell + ALIGNMENT;
}

void OSFreeToHeap(OSHeapHandle handle, void* ptr) {
    OSHeapDescriptor* hd = &HeapArray[handle];
    OSHeapCell* cell = (OSHeapCell*)((char*)ptr - sizeof(OSHeapCell));
    hd->allocated = DLExtract(hd->allocated, cell);
    hd->free = DLInsert(hd->free, cell);
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
        
        hd->free = hd->allocated = NULL;
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
            hd->free = cell;
            hd->allocated = NULL;
            return i;
        }
    }

    return -1;
}

void OSDestroyHeap(OSHeapHandle heap) {
    OSHeapDescriptor* hd;
    long size;

    hd = &HeapArray[heap];
    
    hd->size = -1;
}

// custom macro for OSCheckHeap
#define ASSERTREPORT(line, cond) \
    if (!(cond)) { OSReport("OSCheckHeap: Failed " #cond " in %d", line); return -1; }

long OSCheckHeap(OSHeapHandle heap) {
    OSHeapDescriptor* hd;
    OSHeapCell* cell;
    long total = 0;
    long free = 0;

    ASSERTREPORT(0x37D, HeapArray);
    ASSERTREPORT(0x37E, 0 <= heap && heap < NumHeaps);
    hd = &HeapArray[heap];
    ASSERTREPORT(0x381, 0 <= hd->size);
    
    ASSERTREPORT(0x383, hd->allocated == NULL || hd->allocated->prev == NULL);

    for(cell = hd->allocated; cell; cell = cell->next) {
        ASSERTREPORT(0x386, InRange(cell, ArenaStart, ArenaEnd));
        ASSERTREPORT(0x387, OFFSET(cell, ALIGNMENT) == 0);
        ASSERTREPORT(0x388, cell->next == NULL || cell->next->prev == cell);
        ASSERTREPORT(0x389, MINOBJSIZE <= cell->size);
        ASSERTREPORT(0x38A, OFFSET(cell->size, ALIGNMENT) == 0);
        total += cell->size;
        ASSERTREPORT(0x38D, 0 < total && total <= hd->size);
#ifdef ENABLE_HEAPDESC
        ASSERTREPORT(0x390, cell->hd == hd);
        ASSERTREPORT(0x391, HEADERSIZE + cell->requested <= cell->size);
#endif
    }

    
    ASSERTREPORT(0x395, hd->free == NULL || hd->free->prev == NULL); 
    
    for(cell = hd->free; cell; cell = cell->next) {
        ASSERTREPORT(0x398, InRange(cell, ArenaStart, ArenaEnd));
        ASSERTREPORT(0x399, OFFSET(cell, ALIGNMENT) == 0);
        ASSERTREPORT(0x39A, cell->next == NULL || cell->next->prev == cell);
        ASSERTREPORT(0x39B, MINOBJSIZE <= cell->size);
        ASSERTREPORT(0x39C, OFFSET(cell->size, ALIGNMENT) == 0);
        ASSERTREPORT(0x39D, cell->next == NULL || (char*) cell + cell->size < (char*) cell->next);
        total += cell->size;
        free = (cell->size + free);
        free -= HEADERSIZE;
        ASSERTREPORT(0x3A1, 0 < total && total <= hd->size);
#ifdef ENABLE_HEAPDESC
        ASSERTREPORT(0x3A4, cell->hd == NULL);
#endif
    }
    ASSERTREPORT(0x3A8, total == hd->size);
    return free;
}

s32 OSReferentSize(void* ptr) {
    OSHeapCell* cell;

    cell = (void*)((u32)ptr - HEADERSIZE);
    return (long)((u32)cell->size - HEADERSIZE);
}

void OSDumpHeap(OSHeapHandle heap) {
    OSHeapDescriptor* hd;
    OSHeapCell* cell;

    OSReport("\nOSDumpHeap(%d):\n", heap);
    hd = &HeapArray[heap];
    if (hd->size < 0) {
        OSReport("--------Inactive\n");
        return;
    }

    OSReport("addr	size		end	prev	next\n");
    OSReport("--------Allocated\n");

    for(cell = hd->allocated; cell; cell = cell->next) {
        OSReport("%x	%d	%x	%x	%x\n", cell, cell->size, (char*)cell + cell->size, cell->prev, cell->next);
    }
    OSReport("--------Free\n");
    for(cell = hd->free; cell; cell = cell->next) {
        OSReport("%x	%d	%x	%x	%x\n", cell, cell->size, (char*)cell + cell->size, cell->prev, cell->next);
    }
}
