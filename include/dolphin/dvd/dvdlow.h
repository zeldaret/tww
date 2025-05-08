#ifndef DVDLOW_H
#define DVDLOW_H

#include "dolphin/dvd/dvd.h" // IWYU pragma: export
#include "dolphin/types.h"
#include "dolphin/os/OSUtil.h"
#include "dolphin/os/OSContext.h"

typedef void (*DVDLowCallback)(u32 intType);
vu32 __DIRegs[16] AT_ADDRESS(0xCC006000);

void __DVDInitWA(void);
void __DVDInterruptHandler(short unused, OSContext * context);
void __DVDLowSetWAType(u32 type, u32 location);

BOOL DVDLowRead(void* addr, u32 length, u32 offset, DVDLowCallback callback);
BOOL DVDLowSeek(u32 offset, DVDLowCallback callback);
BOOL DVDLowWaitCoverClose(DVDLowCallback callback);
BOOL DVDLowReadDiskID(DVDDiskID* diskID, DVDLowCallback callback);
BOOL DVDLowStopMotor(DVDLowCallback callback);
BOOL DVDLowRequestError(DVDLowCallback callback);
BOOL DVDLowInquiry(DVDDriveInfo* info, DVDLowCallback callback);
BOOL DVDLowAudioStream(u32 subcmd, u32 length, u32 offset, DVDLowCallback callback);
BOOL DVDLowRequestAudioStatus(u32 subcmd, DVDLowCallback callback);
BOOL DVDLowAudioBufferConfig(BOOL enable, u32 size, DVDLowCallback callback);
void DVDLowReset();
BOOL DVDLowBreak();
DVDLowCallback DVDLowClearCallback(void);

#endif /* DVDLOW_H */
