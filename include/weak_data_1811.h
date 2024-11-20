#ifndef WEAK_DATA_1811_H
#define WEAK_DATA_1811_H

// Fake header.

#include "dolphin/gx/GXEnum.h"
#include "weak_data_2100_2080.h" // IWYU pragma: keep

// @1811 is a weak object that gets included in the .data sections of several TUs.
// Its true source is this line:
// u8 attnFnTbl[] = { GX_AF_NONE, GX_AF_SPEC, GX_AF_NONE, GX_AF_SPOT };
// Which appears in the weak function J3DColorChan::getAttnFn, which is supposed to go in a header.
// But that line causes the weak object to appear in .rodata, while this weak object need to be in .data.
// So for now, that function is moved to the .cpp file, and TUs that need this object should include this header.

static inline void fake_getAttnFn() {
    // Value is equivalent to: {0x02, 0x00, 0x02, 0x01}
    static u8 attnFnTbl_1811[] = { GX_AF_NONE, GX_AF_SPEC, GX_AF_NONE, GX_AF_SPOT };
}

// These two weak objects are strange, as they have no symbols associated with them.
// They always seems to come after @1811 ends at offset 0x1C, getting padded to start at 0x20 and ending at 0x30.
// These are likely the 3.0 and .5 double literals from std::sqrtf.
// But those literals get placed in .rodata, while these weak objects need to be in .data.
// Also, the order of these two literals is reversed. std::sqrtf has _half before _three.
// static f64 data_no_symbol_3_5[2] = {3.0, 0.5};

extern inline void fake_sqrtf(float x) {
    static double _three[1] = {3.0};
    static double _half[1] = {.5};
}

// Note: These weak objects get stripped out for main.dol, because all three of them are within the
// 8-byte limit for .sdata. They do not get stripped out in RELs.

#endif /* WEAK_DATA_1811_H */
