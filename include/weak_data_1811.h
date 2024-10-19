#ifndef WEAK_DATA_1811_H
#define WEAK_DATA_1811_H

// Fake header.
// @1811 is a weak object that gets included in the .data sections of several TUs.
// Its true source is this line:
// u8 attnFnTbl[] = { GX_AF_NONE, GX_AF_SPEC, GX_AF_NONE, GX_AF_SPOT };
// Which appears in the weak function J3DColorChan::getAttnFn, which is supposed to go in a header.
// But for some reason, that line causes the weak objects to appear in .rodata.
// So for now, that function is moved to the .cpp file, and TUs that need this object should include this header.

#include "weak_data_2100_2080.h" // IWYU pragma: keep

static u8 data_1811[] = {0x02, 0x00, 0x02, 0x01};

// This object is strange, as it has no symbol associated with it.
// It always seems to come after @1811 ends at offset 0x1C, getting padded to start at 0x20 and ending at 0x30.
// It being an array of two doubles is guessed based on how it looks and its apparently 0x8 byte alignment.
// Its actual purpose is unknown since it's never used.
static f64 data_no_symbol_3_5[2] = {3.0, 0.5};

#endif /* WEAK_DATA_1811_H */
