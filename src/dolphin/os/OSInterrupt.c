#include "dolphin/os/OSInterrupt.h"
#include "dolphin/dsp.h"
#include "dolphin/exi/EXIBios.h"
#include "dolphin/os/OS.h"
#include <string.h>

vu32 __PIRegs[12] AT_ADDRESS(0xCC003000);
vu16 __MEMRegs[64] AT_ADDRESS(0xCC004000);

ASM BOOL OSDisableInterrupts(void) {
#ifdef __MWERKS__
    // clang-format off
    nofralloc

    entry __RAS_OSDisableInterrupts_begin

    mfmsr r3
    // Clear external interrupts bit
    rlwinm r4, r3, 0, 17, 15
    mtmsr r4

    entry __RAS_OSDisableInterrupts_end

    // Return old interrupt status
    rlwinm r3, r3, 17, 31, 31
    blr
    // clang-format on
#endif
}

ASM BOOL OSEnableInterrupts(void) {
#ifdef __MWERKS__
    // clang-format off
    nofralloc

    mfmsr r3
    // Set external interrupts bit
    ori r4, r3, (1 << 15)
    mtmsr r4

    // Return old interrupt status
    rlwinm r3, r3, 17, 31, 31
    blr
    // clang-format on
#endif
}

ASM BOOL OSRestoreInterrupts(register BOOL status) {
#ifdef __MWERKS__
    // clang-format off
    nofralloc

    cmpwi status, 0
    mfmsr r4
    beq disable

    // Set external interrupts bit
    ori r5, r4, (1 << 15)
    b set_msr

disable:
    // Clear external interrupts bit
    rlwinm r5, r4, 0, 17, 15

set_msr:
    mtmsr r5
    // Return old interrupt status
    rlwinm r3, r4, 17, 31, 31
    blr
    // clang-format on
#endif
}

static __OSInterruptHandler* InterruptHandlerTable;

__OSInterruptHandler __OSSetInterruptHandler(__OSInterrupt type, __OSInterruptHandler handler) {
    __OSInterruptHandler old = InterruptHandlerTable[type];
    InterruptHandlerTable[type] = handler;
    return old;
}

__OSInterruptHandler __OSGetInterruptHandler(__OSInterrupt type) {
    return InterruptHandlerTable[type];
}

void __OSInterruptInit(void) {
    InterruptHandlerTable = OSPhysicalToCached(0x3040);
    memset(InterruptHandlerTable, 0, 32 * sizeof(__OSInterruptHandler));

    *(OSInterruptMask*)OSPhysicalToCached(0x00C4) = 0;

    *(OSInterruptMask*)OSPhysicalToCached(0x00C8) = 0;

    __PIRegs[1] = 0xf0;

    __OSMaskInterrupts(OS_INTERRUPTMASK_MEM | OS_INTERRUPTMASK_DSP | OS_INTERRUPTMASK_AI |
                       OS_INTERRUPTMASK_EXI | OS_INTERRUPTMASK_PI);

    __OSSetExceptionHandler(4, (OSExceptionHandler)ExternalInterruptHandler);
}

u32 SetInterruptMask(OSInterruptMask mask, OSInterruptMask current) {
    u32 reg;

    switch (__cntlzw(mask)) {
    case OS_INTR_MEM_0:
    case OS_INTR_MEM_1:
    case OS_INTR_MEM_2:
    case OS_INTR_MEM_3:
    case OS_INTR_MEM_ADDRESS:
        reg = 0;
        if (!(current & OS_INTERRUPTMASK_MEM_0))
            reg |= 0x1;
        if (!(current & OS_INTERRUPTMASK_MEM_1))
            reg |= 0x2;
        if (!(current & OS_INTERRUPTMASK_MEM_2))
            reg |= 0x4;
        if (!(current & OS_INTERRUPTMASK_MEM_3))
            reg |= 0x8;
        if (!(current & OS_INTERRUPTMASK_MEM_ADDRESS))
            reg |= 0x10;
        __MEMRegs[0x0000000e] = (u16)reg;
        mask &= ~OS_INTERRUPTMASK_MEM;
        break;
    case OS_INTR_DSP_AI:
    case OS_INTR_DSP_ARAM:
    case OS_INTR_DSP_DSP:
        reg = __DSPRegs[0x00000005];
        reg &= ~0x1F8;
        if (!(current & OS_INTERRUPTMASK_DSP_AI))
            reg |= 0x10;
        if (!(current & OS_INTERRUPTMASK_DSP_ARAM))
            reg |= 0x40;
        if (!(current & OS_INTERRUPTMASK_DSP_DSP))
            reg |= 0x100;
        __DSPRegs[0x00000005] = (u16)reg;
        mask &= ~OS_INTERRUPTMASK_DSP;
        break;
    case OS_INTR_AI_AI:
        reg = __AIRegs[0];
        reg &= ~0x2C;
        if (!(current & OS_INTERRUPTMASK_AI_AI))
            reg |= 0x4;
        __AIRegs[0] = reg;
        mask &= ~OS_INTERRUPTMASK_AI;
        break;
    case OS_INTR_EXI_0_EXI:
    case OS_INTR_EXI_0_TC:
    case OS_INTR_EXI_0_EXT:
        reg = __EXIRegs[0];
        reg &= ~0x2C0F;
        if (!(current & OS_INTERRUPTMASK_EXI_0_EXI))
            reg |= 0x1;
        if (!(current & OS_INTERRUPTMASK_EXI_0_TC))
            reg |= 0x4;
        if (!(current & OS_INTERRUPTMASK_EXI_0_EXT))
            reg |= 0x400;
        __EXIRegs[0] = reg;
        mask &= ~OS_INTERRUPTMASK_EXI_0;
        break;
    case OS_INTR_EXI_1_EXI:
    case OS_INTR_EXI_1_TC:
    case OS_INTR_EXI_1_EXT:
        reg = __EXIRegs[5];
        reg &= ~0xC0F;

        if (!(current & OS_INTERRUPTMASK_EXI_1_EXI))
            reg |= 0x1;
        if (!(current & OS_INTERRUPTMASK_EXI_1_TC))
            reg |= 0x4;
        if (!(current & OS_INTERRUPTMASK_EXI_1_EXT))
            reg |= 0x400;
        __EXIRegs[5] = reg;
        mask &= ~OS_INTERRUPTMASK_EXI_1;
        break;
    case OS_INTR_EXI_2_EXI:
    case OS_INTR_EXI_2_TC:
        reg = __EXIRegs[10];
        reg &= ~0xF;
        if (!(current & OS_INTERRUPTMASK_EXI_2_EXI))
            reg |= 0x1;
        if (!(current & OS_INTERRUPTMASK_EXI_2_TC))
            reg |= 0x4;

        __EXIRegs[10] = reg;
        mask &= ~OS_INTERRUPTMASK_EXI_2;
        break;
    case OS_INTR_PI_CP:
    case OS_INTR_PI_SI:
    case OS_INTR_PI_DI:
    case OS_INTR_PI_RSW:
    case OS_INTR_PI_ERROR:
    case OS_INTR_PI_VI:
    case OS_INTR_PI_DEBUG:
    case OS_INTR_PI_PE_TOKEN:
    case OS_INTR_PI_PE_FINISH:
    case OS_INTR_PI_HSP:
        reg = 0xF0;

        if (!(current & OS_INTERRUPTMASK_PI_CP)) {
            reg |= 0x800;
        }
        if (!(current & OS_INTERRUPTMASK_PI_SI)) {
            reg |= 0x8;
        }
        if (!(current & OS_INTERRUPTMASK_PI_DI)) {
            reg |= 0x4;
        }
        if (!(current & OS_INTERRUPTMASK_PI_RSW)) {
            reg |= 0x2;
        }
        if (!(current & OS_INTERRUPTMASK_PI_ERROR)) {
            reg |= 0x1;
        }
        if (!(current & OS_INTERRUPTMASK_PI_VI)) {
            reg |= 0x100;
        }
        if (!(current & OS_INTERRUPTMASK_PI_DEBUG)) {
            reg |= 0x1000;
        }
        if (!(current & OS_INTERRUPTMASK_PI_PE_TOKEN)) {
            reg |= 0x200;
        }
        if (!(current & OS_INTERRUPTMASK_PI_PE_FINISH)) {
            reg |= 0x400;
        }
        if (!(current & OS_INTERRUPTMASK_PI_HSP)) {
            reg |= 0x2000;
        }
        __PIRegs[1] = reg;
        mask &= ~OS_INTERRUPTMASK_PI;
        break;
    default:
        break;
    }
    return mask;
}

OSInterruptMask __OSMaskInterrupts(OSInterruptMask global) {
    BOOL enabled;
    OSInterruptMask prev;
    OSInterruptMask local;
    OSInterruptMask mask;

    enabled = OSDisableInterrupts();
    prev = *(OSInterruptMask*)OSPhysicalToCached(0x00C4);
    local = *(OSInterruptMask*)OSPhysicalToCached(0x00C8);
    mask = ~(prev | local) & global;
    global |= prev;
    *(OSInterruptMask*)OSPhysicalToCached(0x00C4) = global;
    while (mask) {
        mask = SetInterruptMask(mask, global | local);
    }
    OSRestoreInterrupts(enabled);
    return prev;
}

OSInterruptMask __OSUnmaskInterrupts(OSInterruptMask global) {
    BOOL enabled;
    OSInterruptMask prev;
    OSInterruptMask local;
    OSInterruptMask mask;

    enabled = OSDisableInterrupts();
    prev = *(OSInterruptMask*)OSPhysicalToCached(0x00C4);
    local = *(OSInterruptMask*)OSPhysicalToCached(0x00C8);
    mask = (prev | local) & global;
    global = prev & ~global;
    *(OSInterruptMask*)OSPhysicalToCached(0x00C4) = global;
    while (mask) {
        mask = SetInterruptMask(mask, global | local);
    }
    OSRestoreInterrupts(enabled);
    return prev;
}

static u32 InterruptPrioTable[] = {
    0x00000100, 0x00000040, 0xF8000000, 0x00000200, 0x00000080, 0x00003000,
    0x00000020, 0x03FF8C00, 0x04000000, 0x00004000, 0xFFFFFFFF,
};

extern OSTime __OSLastInterruptTime;
OSTime __OSLastInterruptTime;

extern s16 __OSLastInterrupt;
s16 __OSLastInterrupt;

extern u32 __OSLastInterruptSrr0;
u32 __OSLastInterruptSrr0;

void __OSDispatchInterrupt(__OSException exception, OSContext* context) {
    u32 intsr;
    u32 reg;
    OSInterruptMask cause;
    OSInterruptMask unmasked;
    OSInterruptMask* prio;
    __OSInterrupt interrupt;
    __OSInterruptHandler handler;
    intsr = __PIRegs[0];
    intsr &= ~0x00010000;

    if (intsr == 0 || (intsr & __PIRegs[1]) == 0) {
        OSLoadContext(context);
    }

    cause = 0;

    if (intsr & 0x00000080) {
        reg = __MEMRegs[15];
        if (reg & 0x1)
            cause |= OS_INTERRUPTMASK_MEM_0;
        if (reg & 0x2)
            cause |= OS_INTERRUPTMASK_MEM_1;
        if (reg & 0x4)
            cause |= OS_INTERRUPTMASK_MEM_2;
        if (reg & 0x8)
            cause |= OS_INTERRUPTMASK_MEM_3;
        if (reg & 0x10)
            cause |= OS_INTERRUPTMASK_MEM_ADDRESS;
    }

    if (intsr & 0x00000040) {
        reg = __DSPRegs[5];
        if (reg & 0x8)
            cause |= OS_INTERRUPTMASK_DSP_AI;
        if (reg & 0x20)
            cause |= OS_INTERRUPTMASK_DSP_ARAM;
        if (reg & 0x80)
            cause |= OS_INTERRUPTMASK_DSP_DSP;
    }

    if (intsr & 0x00000020) {
        reg = __AIRegs[0];
        if (reg & 0x8)
            cause |= OS_INTERRUPTMASK_AI_AI;
    }

    if (intsr & 0x00000010) {
        reg = __EXIRegs[0];
        if (reg & 0x2)
            cause |= OS_INTERRUPTMASK_EXI_0_EXI;
        if (reg & 0x8)
            cause |= OS_INTERRUPTMASK_EXI_0_TC;
        if (reg & 0x800)
            cause |= OS_INTERRUPTMASK_EXI_0_EXT;
        reg = __EXIRegs[5];
        if (reg & 0x2)
            cause |= OS_INTERRUPTMASK_EXI_1_EXI;
        if (reg & 0x8)
            cause |= OS_INTERRUPTMASK_EXI_1_TC;
        if (reg & 0x800)
            cause |= OS_INTERRUPTMASK_EXI_1_EXT;
        reg = __EXIRegs[10];
        if (reg & 0x2)
            cause |= OS_INTERRUPTMASK_EXI_2_EXI;
        if (reg & 0x8)
            cause |= OS_INTERRUPTMASK_EXI_2_TC;
    }

    if (intsr & 0x00002000)
        cause |= OS_INTERRUPTMASK_PI_HSP;
    if (intsr & 0x00001000)
        cause |= OS_INTERRUPTMASK_PI_DEBUG;
    if (intsr & 0x00000400)
        cause |= OS_INTERRUPTMASK_PI_PE_FINISH;
    if (intsr & 0x00000200)
        cause |= OS_INTERRUPTMASK_PI_PE_TOKEN;
    if (intsr & 0x00000100)
        cause |= OS_INTERRUPTMASK_PI_VI;
    if (intsr & 0x00000008)
        cause |= OS_INTERRUPTMASK_PI_SI;
    if (intsr & 0x00000004)
        cause |= OS_INTERRUPTMASK_PI_DI;
    if (intsr & 0x00000002)
        cause |= OS_INTERRUPTMASK_PI_RSW;
    if (intsr & 0x00000800)
        cause |= OS_INTERRUPTMASK_PI_CP;
    if (intsr & 0x00000001)
        cause |= OS_INTERRUPTMASK_PI_ERROR;

    unmasked = cause & ~(*(OSInterruptMask*)OSPhysicalToCached(0x00C4) |
                         *(OSInterruptMask*)OSPhysicalToCached(0x00C8));
    if (unmasked) {
        for (prio = InterruptPrioTable;; ++prio) {
            if (unmasked & *prio) {
                interrupt = (__OSInterrupt)__cntlzw(unmasked & *prio);
                break;
            }
        }

        handler = __OSGetInterruptHandler(interrupt);
        if (handler) {
            if (OS_INTR_MEM_ADDRESS < interrupt) {
                __OSLastInterrupt = interrupt;
                __OSLastInterruptTime = OSGetTime();
                __OSLastInterruptSrr0 = context->srr0;
            }

            OSDisableScheduler();
            handler(interrupt, context);
            OSEnableScheduler();
            __OSReschedule();
            OSLoadContext(context);
        }
    }

    OSLoadContext(context);
}

static ASM void ExternalInterruptHandler(register __OSInterrupt type, register OSContext* context) {
#ifdef __MWERKS__
    // clang-format off
    nofralloc

    stw r0, context->gpr[0]
    stw r1, context->gpr[1]
    stw r2, context->gpr[2]
    stmw r6, context->gpr[6]

    mfspr r0, GQR1
    stw r0, context->gqr[1]
    mfspr r0, GQR2
    stw r0, context->gqr[2]
    mfspr r0, GQR3
    stw r0, context->gqr[3]
    mfspr r0, GQR4
    stw r0, context->gqr[4]
    mfspr r0, GQR5
    stw r0, context->gqr[5]
    mfspr r0, GQR6
    stw r0, context->gqr[6]
    mfspr r0, GQR7
    stw r0, context->gqr[7]

    stwu r1, -8(r1)
    b __OSDispatchInterrupt
    // clang-format on
#endif
}
