#include "Runtime.PPCEABI.H/GCN_mem_alloc.h"
#include "dolphin/os/OS.h"


inline static void InitDefaultHeap() {
    void* arenaLo;
    void* arenaHi;

    // This is to force the two strings be two separate rodata entries with padding instead of a single stringbase.
    static const char dummy1[] = "GCN_Mem_Alloc.c : InitDefaultHeap. No Heap Available\n";
    static const char dummy2[] = "Metrowerks CW runtime library initializing default heap\n";
    OSReport(dummy1);
    OSReport(dummy2);

    arenaLo = OSGetArenaLo();
    arenaHi = OSGetArenaHi();

    arenaLo = OSInitAlloc(arenaLo, arenaHi, 1);
    OSSetArenaLo(arenaLo);

    arenaLo = (void*)OSRoundUp32B(arenaLo);
    arenaHi = (void*)OSRoundDown32B(arenaHi);

    OSSetCurrentHeap(OSCreateHeap(arenaLo, arenaHi));
    OSSetArenaLo(arenaLo = arenaHi);
}

void __sys_free(void* ptr) {
    if (__OSCurrHeap == -1) {
        InitDefaultHeap();
    }

    OSFreeToHeap(__OSCurrHeap, ptr);
    return;
}
