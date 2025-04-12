#ifndef WEAK_BSS_3569_H
#define WEAK_BSS_3569_H

// Fake header.
// This is some kind of weak objects that get included in the .bss sections of several TUs.
// Its true source is currently unknown, so include this header in TUs that need it to match for now.

#include "dolphin/types.h"
template <typename T> struct bss_3569 { u8 val[0xC]; };

static inline void dummy_bss_3569() {
    bss_3569<void*>(); // @3569
}

#endif /* WEAK_BSS_3569_H */
