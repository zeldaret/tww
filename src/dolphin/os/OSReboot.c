#include "dolphin/os/OSReboot.h"
#include "dolphin/os/OSContext.h"
#include "dolphin/os/OSExec.h"

void __OSReboot(u32 resetCode, u32 bootDol) {
    struct OSContext context;
    char* iVar1;
	OSDisableInterrupts();
    OSSetArenaLo((void*)0x81280000);
    OSSetArenaHi((void*)0x812f0000);
    OSClearContext(&context);
    OSSetCurrentContext(&context);
    iVar1 = NULL;
    __OSBootDol(bootDol, resetCode | 0x80000000, &iVar1);
}

static void* SaveStart;

static void* SaveEnd;

void OSSetSaveRegion(void* start, void* end) {
    SaveStart = start;
    SaveEnd = end;
}

void OSGetSaveRegion(void** start, void** end) {
    *start = SaveStart;
    *end = SaveEnd;
}
