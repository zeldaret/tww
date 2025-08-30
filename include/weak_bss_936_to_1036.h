#ifndef WEAK_BSS_936_TO_1036_H
#define WEAK_BSS_936_TO_1036_H

// Fake header.
// These are some kind of weak objects that get included in the .bss sections of several TUs.
// They each have size 1, and alignment 1 in the debug maps, but alignment 4 in the non-debug maps.
// Their true source is currently unknown, so include this header in TUs that need them to match for now.

// A possible origin for one of these could be the constructor of TFunctionValueAttribute_refer in
// functionvalue.h. That constructor includes `JGadget::TAllocator<void*>()` in it, which produces
// one weak bss object that has the correct size and alignment. However, we need 16 of them, while
// that only creates one. Also, that header seems to be required in some actors that *don't* need
// any of these weak bss objects. So that constructor is moved to functionvalue.cpp and this fake
// header should be included where necessary instead.

#include "JSystem/JStudio/JStudio/functionvalue.h" // IWYU pragma: keep

// They each have size 1, and alignment 1 in the debug maps, but alignment 4 in the non-debug maps.
static inline void dummy_bss_936_to_1036() {
    JGadget::TAllocator<void*>(); // @1036
    JGadget::TAllocator<void*>(); // @1034
    JGadget::TAllocator<void*>(); // @1032
    JGadget::TAllocator<void*>(); // @1031
    JGadget::TAllocator<void*>(); // @1026
    JGadget::TAllocator<void*>(); // @1024
    JGadget::TAllocator<void*>(); // @1022
    JGadget::TAllocator<void*>(); // @1021
    JGadget::TAllocator<void*>(); // @984
    JGadget::TAllocator<void*>(); // @982
    JGadget::TAllocator<void*>(); // @980
    JGadget::TAllocator<void*>(); // @979
    JGadget::TAllocator<void*>(); // @941
    JGadget::TAllocator<void*>(); // @939
    JGadget::TAllocator<void*>(); // @937
    JGadget::TAllocator<void*>(); // @936
}

#endif /* WEAK_BSS_936_TO_1036_H */
