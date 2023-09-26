#include "dolphin/gba/GBAPriv.h"

s32 GBAGetProcessStatus(s32 chan, u8* percentp) {
    BOOL enabled;           // r26
    s32 ret;                // r29
    GBAControl* gba;        // r25
    GBABootInfo* bootInfo;  // r31
    u8 percent;             // r30
    OSTime t;               // r27

    gba = &__GBA[chan];
    bootInfo = &__GBA[chan].bootInfo;

    if (gba->callback != NULL || bootInfo->callback != NULL) {
        ret = 2;

        if (bootInfo->callback != NULL) {
            percent = (bootInfo->curOffset * 100) / bootInfo->realLength;
            if (bootInfo->begin != 0) {
                t = OSGetTime() - bootInfo->begin;
                if (OSTicksToMilliseconds(t) < 5500) {
                    percent = (percent * t) / OSMillisecondsToTicks(5500ll);
                }

                if (percent >= 100) {
                    percent = 100;
                }
            }

            if (percentp != NULL) {
                *percentp = percent;
            }
        }
    } else {
        ret = 0;
    }

    return ret;
}
