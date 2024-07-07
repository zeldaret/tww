#include "dolphin/os/OSSync.h"
#include "dolphin/os/OS.h"

void __OSSystemCallVectorStart();
void __OSSystemCallVectorEnd();

static asm void SystemCallVector(void) {
    // clang-format off
    nofralloc

entry __OSSystemCallVectorStart
    mfspr r9, HID0
    ori r10, r9, 8
    mtspr HID0, r10
    isync
    sync
    mtspr HID0, r9
    rfi

entry __OSSystemCallVectorEnd
    nop
    // clang-format on
}

void __OSInitSystemCall(void) {
    void* addr = OSPhysicalToCached(0x00C00);
    memcpy(addr, __OSSystemCallVectorStart,
           (size_t)__OSSystemCallVectorEnd - (size_t)__OSSystemCallVectorStart);
    DCFlushRangeNoSync(addr, 0x100);
    __sync();
    ICInvalidateRange(addr, 0x100);
}
