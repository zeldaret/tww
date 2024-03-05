#ifndef _JSYSTEM_JGADGET_ALLOCATOR_H
#define _JSYSTEM_JGADGET_ALLOCATOR_H

#include "dolphin/types.h"

namespace JGadget {
template <typename T>
struct TAllocator {
    static TAllocator get() { }

    inline TAllocator();

    /* 0x00 */ u8 _00;
    /* 0x04 */ u32 _04;
    /* 0x08 */ u32 _08;
    /* 0x0C */ u32 _0C;
};

typedef TAllocator<void*> TVoidAllocator;
}; // namespace JGadget

#endif
