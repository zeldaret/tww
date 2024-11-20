#ifndef WEAK_DATA_2100_2080_H
#define WEAK_DATA_2100_2080_H

// Fake header.

#include "dolphin/mtx/vec.h"

// @2100 and @2080 are weak objects that get included in the .data sections of several TUs.
// Their true source is likely this line of code that appears twice in J3DJoint.h:
// J3DSys::mParentS = (Vec){1.0f, 1.0f, 1.0f};
// But that line causes the weak objects to appear in .rodata, while this weak object need to be in .data.
// So for now, the line is commented out, and TUs that need these objects should include this header.
// Note: For d_snap and J3DUClipper, these objects *are* supposed to appear in .rodata, but those are the only ones.
// Also, d_snap and J3DUClipper seem to be the only ones where the two symbols are in order by the compiler-generated
// names. In TUs where they appear in .data instead, their order is reversed (@2100 coming before @2080).

static inline void fake_data_2100() {
    // Value is equivalent to: {0x3F800000, 0x3F800000, 0x3F800000}
    static Vec data_2100 = {1.0f, 1.0f, 1.0f};
}

static inline void fake_data_2080() {
    // Value is equivalent to: {0x3F800000, 0x3F800000, 0x3F800000}
    static Vec data_2080 = {1.0f, 1.0f, 1.0f};
}

#endif /* WEAK_DATA_2100_2080_H */
