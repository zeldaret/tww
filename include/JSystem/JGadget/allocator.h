#ifndef _JSYSTEM_JGADGET_ALLOCATOR_H
#define _JSYSTEM_JGADGET_ALLOCATOR_H

#include "dolphin/types.h"

namespace JGadget {
template <typename T>
struct TAllocator {
    // TODO: this constructor declaration needs to be removed in order to match TFunctionValue_composite's constructor
    // in functionvalue.cpp, and in order to get the @564 struct literal to appear in the .sbss section of that TU.
    // however, removing this declaration also causes that bss literal to appear in hundreds of other TUs it shouldn't.
    TAllocator();

    // TODO
    void AllocateRaw(u32) {}
    void DeallocateRaw(void*) {}
    void allocate(u32, const void*) {}
    void deallocate(T*, u32) {}
    void destroy(T*) {}

    /* 0x00 */ u8 _00;
};

typedef TAllocator<void*> TVoidAllocator;
}; // namespace JGadget

#endif
