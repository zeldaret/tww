#ifndef WEAK_DATA_2100_2080_H
#define WEAK_DATA_2100_2080_H

// Fake header.
// These are weak objects that get included in the .data sections of several TUs.
// Their true source is likely this line of code that appears twice in J3DJoint.h:
// J3DSys::mParentS = (Vec){1.0f, 1.0f, 1.0f};
// But for some reason, that line causes the weak objects to appear in .rodata.
// So for now, the line is commented out, and TUs that need these objects should include this header.
// Note: For d_snap and J3DUClipper, these objects *are* supposed to appear in .rodata, but those are the only ones.

#include "dolphin/mtx/vec.h"

static Vec data_2100 = {1.0f, 1.0f, 1.0f};
static Vec data_2080 = {1.0f, 1.0f, 1.0f};

#endif /* WEAK_DATA_2100_2080_H */
