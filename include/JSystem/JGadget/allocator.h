#ifndef _JSYSTEM_JGADGET_ALLOCATOR_H
#define _JSYSTEM_JGADGET_ALLOCATOR_H

#include "dolphin/types.h"

namespace JGadget {
template <typename T>
struct TAllocator {
    // TODO: This explicit ctor needs to be removed in order to match TFunctionValue_composite's constructor
    // in functionvalue.cpp, and in order to get the @564 struct literal to appear in the .sbss section of that TU.
    // However, removing this definition also causes that bss literal to appear in other TUs it shouldn't.
    // This seems related to the 16 1-byte weak bss symbols that appear in a ton of different TUs (@936 to @1036)
    // as this literal also has alignment 1 in the debug maps but alignment for in non-debug maps.
    // Specifically it's the JGadget::TAllocator<void*>() inside of TFunctionValueAttribute_refer that creates the literal.
    TAllocator() {}

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
