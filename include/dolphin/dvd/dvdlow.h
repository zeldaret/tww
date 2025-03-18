#ifndef DVDLOW_H
#define DVDLOW_H

#include "dolphin/dvd/dvd.h" // IWYU pragma: export
#include "dolphin/types.h"
#include "dolphin/os/OSUtil.h"

typedef void (*DVDLowCallback)(u32 intType);
vu32 __DIRegs[16] AT_ADDRESS(0xCC006000);

void __DVDInitWA(void);
void __DVDInterruptHandler(short unused, struct OSContext * context);
void __DVDLowSetWAType(u32 type, u32 location);
DVDLowCallback DVDLowClearCallback(void);

#endif /* DVDLOW_H */
