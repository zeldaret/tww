#ifndef _JSYSTEM_JGADGET_ALLOCATOR_H
#define _JSYSTEM_JGADGET_ALLOCATOR_H

#include "dolphin/types.h"

namespace JGadget {
template <typename T>
struct TAllocator {
    T* allocate(u32 count, const void *param_2) {
        return AllocateRaw(count * sizeof(T));
    }

    T* AllocateRaw(u32 size) {
        return (T*)operator new(size);
    }

    void deallocate(T* mem, u32 size) {
        DeallocateRaw(mem);
    }

    void DeallocateRaw(void* mem) {
        delete (T*)mem;
    }

    void destroy(T* p) {
        // JUT_ASSERT(68, p!=0);
    }

    /* 0x00 */ u8 mAllocator;
};

typedef TAllocator<void*> TVoidAllocator;
}; // namespace JGadget

#endif
