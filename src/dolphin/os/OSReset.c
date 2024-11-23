#include "dolphin/os/OSReset.h"
#include "dolphin/os/OS.h"

vu16 __VIRegs[59] AT_ADDRESS(0xCC002000);
OSThreadQueue __OSActiveThreadQueue AT_ADDRESS(OS_BASE_CACHED | 0x00DC);

static OSResetQueue ResetFunctionQueue;

void OSRegisterResetFunction(OSResetFunctionInfo* func) {
    OSResetFunctionInfo* tmp;
    OSResetFunctionInfo* iter;

    for (iter = ResetFunctionQueue.first; iter && iter->priority <= func->priority;
         iter = iter->next)
        ;

    if (iter == NULL) {
        tmp = ResetFunctionQueue.last;
        if (tmp == NULL) {
            ResetFunctionQueue.first = func;
        } else {
            tmp->next = func;
        }
        func->prev = tmp;
        func->next = NULL;
        ResetFunctionQueue.last = func;
        return;
    }

    func->next = iter;
    tmp = iter->prev;
    iter->prev = func;
    func->prev = tmp;
    if (tmp == NULL) {
        ResetFunctionQueue.first = func;
        return;
    }
    tmp->next = func;
}

inline BOOL __OSCallResetFunctions(u32 arg0) {
    OSResetFunctionInfo* iter;
    s32 retCode = 0;
    s32 temp;

    for (iter = ResetFunctionQueue.first; iter != NULL;) {
        temp = !iter->func(arg0);
        iter = iter->next;
        retCode |= temp;
    }
    retCode |= !__OSSyncSram();
    if (retCode) {
        return 0;
    }
    return 1;
}

#ifdef __MWERKS__
static asm void Reset(register s32 param_0) {
    // clang-format off
    nofralloc

    b lbl_8033F7AC

lbl_8033F790:
    mfspr r8, 0x3f0
    ori r8, r8, 8
    mtspr 0x3f0, r8
    isync 
    sync
    nop
    b lbl_8033F7B0

lbl_8033F7AC:
    b lbl_8033F7CC

lbl_8033F7B0:
    mftb r5, 0x10c

lbl_8033F7B4:
    mftb r6, 0x10c
    subf r7, r5, r6
    cmplwi r7, 0x1124
    blt lbl_8033F7B4
    nop 
    b lbl_8033F7D0

lbl_8033F7CC:
    b lbl_8033F7EC

lbl_8033F7D0:
    lis r8, 0xCC00
    ori r8, r8, 0x3000
    li r4, 3
    stw r4, 0x24(r8)
    stw param_0, 0x24(r8)
    nop 
    b lbl_8033F7F0

lbl_8033F7EC:
    b lbl_8033F7F8

lbl_8033F7F0:
    nop 
    b lbl_8033F7F0

lbl_8033F7F8:
    b lbl_8033F790
    // clang-format on
}
#endif

inline static void KillThreads(void) {
    OSThread* thread;
    OSThread* next;

    for (thread = __OSActiveThreadQueue.head; thread; thread = next) {
        next = thread->active_threads_link.next;
        switch (thread->state) {
        case 1:
        case 4:
            OSCancelThread(thread);
            continue;
        default:
            continue;
        }
    }
}

void __OSDoHotReset(s32 arg0) {
    OSDisableInterrupts();
    __VIRegs[1] = 0;
    ICFlashInvalidate();
    Reset(arg0 * 8);
}

void OSResetSystem(int reset, u32 resetCode, BOOL forceMenu) {
    BOOL rc;
    BOOL disableRecalibration;
    u32 unk[3]; // dumb compiler

    OSDisableScheduler();
    __OSStopAudioSystem();

    if (reset == OS_RESET_SHUTDOWN) {
        disableRecalibration = __PADDisableRecalibration(TRUE);
    }

    while (!__OSCallResetFunctions(FALSE)) {
        ;
    }

    if (reset == OS_RESET_HOTRESET && forceMenu) {
        OSSram* sram;

        sram = __OSLockSram();
        sram->flags |= 0x40;
        __OSUnlockSram(TRUE);

        while (!__OSSyncSram()) {
            ;
        }
    }

    OSDisableInterrupts();
    __OSCallResetFunctions(TRUE);
    LCDisable();
    if (reset == OS_RESET_HOTRESET) {
        __OSDoHotReset(resetCode);
    } else if (reset == OS_RESET_RESTART) {
        KillThreads();
        OSEnableScheduler();
        __OSReboot(resetCode, forceMenu);
    }

    KillThreads();
    memset(OSPhysicalToCached(0x40), 0, 0xCC - 0x40);
    memset(OSPhysicalToCached(0xD4), 0, 0xE8 - 0xD4);
    memset(OSPhysicalToCached(0xF4), 0, 0xF8 - 0xF4);
    memset(OSPhysicalToCached(0x3000), 0, 0xC0);
    memset(OSPhysicalToCached(0x30C8), 0, 0xD4 - 0xC8);
    memset(OSPhysicalToCached(0x30E2), 0, 1);

    __PADDisableRecalibration(disableRecalibration);
}

u32 OSGetResetCode(void) {
    if (*(u8*)OSPhysicalToCached(0x30E2) != 0)
        return 0x80000000;

    return ((__PIRegs[9] & ~7) >> 3);
}
