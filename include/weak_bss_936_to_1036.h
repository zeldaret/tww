#ifndef WEAK_BSS_936_TO_1036_H
#define WEAK_BSS_936_TO_1036_H

// Fake header.
// These are some kind of weak objects that get included in the .bss sections of several TUs.
// Their true source is currently unknown, so include this header in TUs that need them to match for now.

#include "global.h"

#include "weak_bss_3569.h" // IWYU pragma: keep

// They each have size 1, and alignment 1 in the debug maps, but alignment 4 in the non-debug maps.
static u8 bss_1036 ALIGN_DECL(4);
static u8 bss_1034 ALIGN_DECL(4);
static u8 bss_1032 ALIGN_DECL(4);
static u8 bss_1031 ALIGN_DECL(4);
static u8 bss_1026 ALIGN_DECL(4);
static u8 bss_1024 ALIGN_DECL(4);
static u8 bss_1022 ALIGN_DECL(4);
static u8 bss_1021 ALIGN_DECL(4);
static u8 bss_984 ALIGN_DECL(4);
static u8 bss_982 ALIGN_DECL(4);
static u8 bss_980 ALIGN_DECL(4);
static u8 bss_979 ALIGN_DECL(4);
static u8 bss_941 ALIGN_DECL(4);
static u8 bss_939 ALIGN_DECL(4);
static u8 bss_937 ALIGN_DECL(4);
static u8 bss_936 ALIGN_DECL(4);

#endif /* WEAK_BSS_936_TO_1036_H */
