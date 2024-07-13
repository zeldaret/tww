#include "dolphin/os/OSArena.h"
#include "dolphin/os/OSAlloc.h"

static void* __OSArenaHi;

void* OSGetArenaHi(void) {
    return __OSArenaHi;
}

static void* __OSArenaLo = (void*)0xFFFFFFFF;

void* OSGetArenaLo(void) {
    return __OSArenaLo;
}

void OSSetArenaHi(void* hi) {
    __OSArenaHi = hi;
}

void OSSetArenaLo(void* lo) {
    __OSArenaLo = lo;
}

void* OSAllocFromArenaLo(u32 size, s32 alignment) {
    u8* blk_start = OSRoundUpPtr(__OSArenaLo, alignment);
    u8* blk_end = blk_start + size;
    blk_end = OSRoundUpPtr(blk_end, alignment);

    __OSArenaLo = blk_end;
    return blk_start;
}
