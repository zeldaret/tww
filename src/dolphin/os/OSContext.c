#include "dolphin/os/OSContext.h"
#include "dolphin/db/db.h"
#include "dolphin/os/OS.h"
#include "dolphin/os/OSUtil.h"

volatile OSContext* __OSCurrentContext AT_ADDRESS(OS_BASE_CACHED | 0x00D4);
volatile OSContext* __OSFPUContext AT_ADDRESS(OS_BASE_CACHED | 0x00D8);

ASM void __OSLoadFPUContext(s32 unused0, register OSContext* context) {
    // clang-format off
#ifdef __MWERKS__
    nofralloc

    lhz r5, OSContext.state(context)
    clrlwi. r5, r5, 0x1f
    beq exit

    lfd f0, OSContext.field_0x190(context)
    mtfsf 0xFF, f0
    mfspr r5, 0x398
    rlwinm. r5, r5, 3, 0x1F, 0x1F
    beq load_fprs

    psq_l f0,  OSContext.ps[0](context), 0, 0
    psq_l f1,  OSContext.ps[1](context), 0, 0
    psq_l f2,  OSContext.ps[2](context), 0, 0
    psq_l f3,  OSContext.ps[3](context), 0, 0
    psq_l f4,  OSContext.ps[4](context), 0, 0
    psq_l f5,  OSContext.ps[5](context), 0, 0
    psq_l f6,  OSContext.ps[6](context), 0, 0
    psq_l f7,  OSContext.ps[7](context), 0, 0
    psq_l f8,  OSContext.ps[8](context), 0, 0
    psq_l f9,  OSContext.ps[9](context), 0, 0
    psq_l f10, OSContext.ps[10](context), 0, 0
    psq_l f11, OSContext.ps[11](context), 0, 0
    psq_l f12, OSContext.ps[12](context), 0, 0
    psq_l f13, OSContext.ps[13](context), 0, 0
    psq_l f14, OSContext.ps[14](context), 0, 0
    psq_l f15, OSContext.ps[15](context), 0, 0
    psq_l f16, OSContext.ps[16](context), 0, 0
    psq_l f17, OSContext.ps[17](context), 0, 0
    psq_l f18, OSContext.ps[18](context), 0, 0
    psq_l f19, OSContext.ps[19](context), 0, 0
    psq_l f20, OSContext.ps[20](context), 0, 0
    psq_l f21, OSContext.ps[21](context), 0, 0
    psq_l f22, OSContext.ps[22](context), 0, 0
    psq_l f23, OSContext.ps[23](context), 0, 0
    psq_l f24, OSContext.ps[24](context), 0, 0
    psq_l f25, OSContext.ps[25](context), 0, 0
    psq_l f26, OSContext.ps[26](context), 0, 0
    psq_l f27, OSContext.ps[27](context), 0, 0
    psq_l f28, OSContext.ps[28](context), 0, 0
    psq_l f29, OSContext.ps[29](context), 0, 0
    psq_l f30, OSContext.ps[30](context), 0, 0
    psq_l f31, OSContext.ps[31](context), 0, 0

load_fprs:
    lfd f0,  OSContext.fpr[ 0](context)
    lfd f1,  OSContext.fpr[ 1](context)
    lfd f2,  OSContext.fpr[ 2](context)
    lfd f3,  OSContext.fpr[ 3](context)
    lfd f4,  OSContext.fpr[ 4](context)
    lfd f5,  OSContext.fpr[ 5](context)
    lfd f6,  OSContext.fpr[ 6](context)
    lfd f7,  OSContext.fpr[ 7](context)
    lfd f8,  OSContext.fpr[ 8](context)
    lfd f9,  OSContext.fpr[ 9](context)
    lfd f10, OSContext.fpr[10](context)
    lfd f11, OSContext.fpr[11](context)
    lfd f12, OSContext.fpr[12](context)
    lfd f13, OSContext.fpr[13](context)
    lfd f14, OSContext.fpr[14](context)
    lfd f15, OSContext.fpr[15](context)
    lfd f16, OSContext.fpr[16](context)
    lfd f17, OSContext.fpr[17](context)
    lfd f18, OSContext.fpr[18](context)
    lfd f19, OSContext.fpr[19](context)
    lfd f20, OSContext.fpr[20](context)
    lfd f21, OSContext.fpr[21](context)
    lfd f22, OSContext.fpr[22](context)
    lfd f23, OSContext.fpr[23](context)
    lfd f24, OSContext.fpr[24](context)
    lfd f25, OSContext.fpr[25](context)
    lfd f26, OSContext.fpr[26](context)
    lfd f27, OSContext.fpr[27](context)
    lfd f28, OSContext.fpr[28](context)
    lfd f29, OSContext.fpr[29](context)
    lfd f30, OSContext.fpr[30](context)
    lfd f31, OSContext.fpr[31](context)

exit:
    blr
#endif
    // clang-format on
}

ASM void __OSSaveFPUContext(s32 unused0, s32 unused1, register OSContext* context) {
    // clang-format off
#ifdef __MWERKS__
    nofralloc

    lhz r3, OSContext.state(context)
    ori r3, r3, 1
    sth r3, OSContext.state(context)

    stfd f0,  OSContext.fpr[ 0](context)
    stfd f1,  OSContext.fpr[ 1](context)
    stfd f2,  OSContext.fpr[ 2](context)
    stfd f3,  OSContext.fpr[ 3](context)
    stfd f4,  OSContext.fpr[ 4](context)
    stfd f5,  OSContext.fpr[ 5](context)
    stfd f6,  OSContext.fpr[ 6](context)
    stfd f7,  OSContext.fpr[ 7](context)
    stfd f8,  OSContext.fpr[ 8](context)
    stfd f9,  OSContext.fpr[ 9](context)
    stfd f10, OSContext.fpr[10](context)
    stfd f11, OSContext.fpr[11](context)
    stfd f12, OSContext.fpr[12](context)
    stfd f13, OSContext.fpr[13](context)
    stfd f14, OSContext.fpr[14](context)
    stfd f15, OSContext.fpr[15](context)
    stfd f16, OSContext.fpr[16](context)
    stfd f17, OSContext.fpr[17](context)
    stfd f18, OSContext.fpr[18](context)
    stfd f19, OSContext.fpr[19](context)
    stfd f20, OSContext.fpr[20](context)
    stfd f21, OSContext.fpr[21](context)
    stfd f22, OSContext.fpr[22](context)
    stfd f23, OSContext.fpr[23](context)
    stfd f24, OSContext.fpr[24](context)
    stfd f25, OSContext.fpr[25](context)
    stfd f26, OSContext.fpr[26](context)
    stfd f27, OSContext.fpr[27](context)
    stfd f28, OSContext.fpr[28](context)
    stfd f29, OSContext.fpr[29](context)
    stfd f30, OSContext.fpr[30](context)
    stfd f31, OSContext.fpr[31](context)

    mffs f0
    stfd f0, OSContext.field_0x190(context)
    lfd f0, OSContext.fpr[0](context)
    mfspr r3, 0x398
    rlwinm. r3, r3, 3, 0x1f, 0x1f
    beq exit

    psq_st f0,  OSContext.ps[ 0](context), 0, 0
    psq_st f1,  OSContext.ps[ 1](context), 0, 0
    psq_st f2,  OSContext.ps[ 2](context), 0, 0
    psq_st f3,  OSContext.ps[ 3](context), 0, 0
    psq_st f4,  OSContext.ps[ 4](context), 0, 0
    psq_st f5,  OSContext.ps[ 5](context), 0, 0
    psq_st f6,  OSContext.ps[ 6](context), 0, 0
    psq_st f7,  OSContext.ps[ 7](context), 0, 0
    psq_st f8,  OSContext.ps[ 8](context), 0, 0
    psq_st f9,  OSContext.ps[ 9](context), 0, 0
    psq_st f10, OSContext.ps[10](context), 0, 0
    psq_st f11, OSContext.ps[11](context), 0, 0
    psq_st f12, OSContext.ps[12](context), 0, 0
    psq_st f13, OSContext.ps[13](context), 0, 0
    psq_st f14, OSContext.ps[14](context), 0, 0
    psq_st f15, OSContext.ps[15](context), 0, 0
    psq_st f16, OSContext.ps[16](context), 0, 0
    psq_st f17, OSContext.ps[17](context), 0, 0
    psq_st f18, OSContext.ps[18](context), 0, 0
    psq_st f19, OSContext.ps[19](context), 0, 0
    psq_st f20, OSContext.ps[20](context), 0, 0
    psq_st f21, OSContext.ps[21](context), 0, 0
    psq_st f22, OSContext.ps[22](context), 0, 0
    psq_st f23, OSContext.ps[23](context), 0, 0
    psq_st f24, OSContext.ps[24](context), 0, 0
    psq_st f25, OSContext.ps[25](context), 0, 0
    psq_st f26, OSContext.ps[26](context), 0, 0
    psq_st f27, OSContext.ps[27](context), 0, 0
    psq_st f28, OSContext.ps[28](context), 0, 0
    psq_st f29, OSContext.ps[29](context), 0, 0
    psq_st f30, OSContext.ps[30](context), 0, 0
    psq_st f31, OSContext.ps[31](context), 0, 0

exit:
    blr
#endif
    // clang-format on
}

ASM void OSSaveFPUContext(register OSContext* context) {
    // clang-format off
#ifdef __MWERKS__
    nofralloc

    addi r5, context, 0
    b __OSSaveFPUContext
#endif
    // clang-format on
}

ASM void OSSetCurrentContext(register OSContext* context) {
    // clang-format off
#ifdef __MWERKS__
    nofralloc

    lis r4, OS_CURRENT_CONTEXT@ha
    stw context, OS_CURRENT_CONTEXT@l(r4)
    clrlwi r5, context, 2
    stw r5, OS_PHYSICAL_CONTEXT@l(r4)
    lwz r5, OS_CURRENT_FPU_CONTEXT@l(r4)
    cmpw r5, context
    bne disable_fpu
    lwz r6, OSContext.srr1(context)
    ori r6, r6, 0x2000
    stw r6, OSContext.srr1(context)
    mfmsr r6
    ori r6, r6, 2
    mtmsr r6
    blr

disable_fpu:
    lwz r6, OSContext.srr1(context)
    rlwinm r6, r6, 0, 0x13, 0x11
    stw r6, OSContext.srr1(context)
    mfmsr r6
    rlwinm r6, r6, 0, 0x13, 0x11
    ori r6, r6, 2
    mtmsr r6
    isync
    blr
#endif
    // clang-format on
}

OSContext* OSGetCurrentContext(void) {
    return OS_CURRENT_CONTEXT;
}

ASM u32 OSSaveContext(register OSContext* context) {
    // clang-format off
#ifdef __MWERKS__
    nofralloc

    stmw r13, OSContext.gpr[13](context)

    mfspr r0, GQR1
    stw r0, OSContext.gqr[1](context)
    mfspr r0, GQR2
    stw r0, OSContext.gqr[2](context)
    mfspr r0, GQR3
    stw r0, OSContext.gqr[3](context)
    mfspr r0, GQR4
    stw r0, OSContext.gqr[4](context)
    mfspr r0, GQR5
    stw r0, OSContext.gqr[5](context)
    mfspr r0, GQR6
    stw r0, OSContext.gqr[6](context)
    mfspr r0, GQR7
    stw r0, OSContext.gqr[7](context)

    mfcr r0
    stw r0, OSContext.cr(context)
    mflr r0
    stw r0, OSContext.lr(context)
    stw r0, OSContext.srr0(context)
    mfmsr r0
    stw r0, OSContext.srr1(context)
    mfctr r0
    stw r0, OSContext.ctr(context)
    mfxer r0
    stw r0, OSContext.xer(context)

    stw r1, OSContext.gpr[1](context)
    stw r2, OSContext.gpr[2](context)

    li r0, 1
    stw r0, OSContext.gpr[3](context)

    li r3, 0
    blr
#endif
    // clang-format on
}

ASM void OSLoadContext(register OSContext* context) {
    // clang-format off
#ifdef __MWERKS__
    nofralloc

    lis r4, __RAS_OSDisableInterrupts_begin@ha
    lwz r6, OSContext.srr0(context)
    addi r5, r4, __RAS_OSDisableInterrupts_begin@l
    cmplw r6, r5
    ble srr0_not_in_disableintr
    lis r4, __RAS_OSDisableInterrupts_end@ha
    addi r0, r4, __RAS_OSDisableInterrupts_end@l
    cmplw r6, r0
    bge srr0_not_in_disableintr
    stw r5, OSContext.srr0(context)
        
srr0_not_in_disableintr:
    lwz r0, OSContext.gpr[0](context)
    lwz r1, OSContext.gpr[1](context)
    lwz r2, OSContext.gpr[2](context)
    lhz r4, OSContext.state(context)
    rlwinm. r5, r4, 0, 0x1e, 0x1e
    beq load_saved_gprs
    rlwinm r4, r4, 0, 0x1f, 0x1d
    sth r4, OSContext.state(context)
    lmw r5, OSContext.gpr[5](context)
    b load_special_regs
    
load_saved_gprs:
    lmw r13, OSContext.gpr[13](context)
    
load_special_regs:
    lwz r4, OSContext.gqr[1](context)
    mtspr 0x391, r4
    lwz r4, OSContext.gqr[2](context)
    mtspr 0x392, r4
    lwz r4, OSContext.gqr[3](context)
    mtspr 0x393, r4
    lwz r4, OSContext.gqr[4](context)
    mtspr 0x394, r4
    lwz r4, OSContext.gqr[5](context)
    mtspr 0x395, r4
    lwz r4, OSContext.gqr[6](context)
    mtspr 0x396, r4
    lwz r4, OSContext.gqr[7](context)
    mtspr 0x397, r4
    lwz r4, OSContext.cr(context)
    mtcrf 0xff, r4
    lwz r4, OSContext.lr(context)
    mtlr r4
    lwz r4, OSContext.ctr(context)
    mtctr r4
    lwz r4, OSContext.xer(context)
    mtxer r4
    mfmsr r4
    rlwinm r4, r4, 0, 0x11, 0xf
    rlwinm r4, r4, 0, 0x1f, 0x1d
    mtmsr r4
    lwz r4, OSContext.srr0(context)
    mtspr 0x1a, r4
    lwz r4, OSContext.srr1(context)
    mtspr 0x1b, r4
    lwz r4, OSContext.gpr[4](context)
    lwz context, OSContext.gpr[3](context)
    rfi
#endif
    // clang-format on
}

ASM u8* OSGetStackPointer(void) {
    // clang-format off
#ifdef __MWERKS__
    nofralloc

    mr r3, r1
    blr
#endif
    // clang-format on
}

void OSClearContext(OSContext* context) {
    context->mode = 0;
    context->state = 0;

    if (context == OS_CURRENT_FPU_CONTEXT) {
        OS_CURRENT_FPU_CONTEXT = NULL;
    }
}

ASM void OSInitContext(register OSContext* context, register u32 srr0, register u32 stack) {
    // clang-format off
#ifdef __MWERKS__
    nofralloc
    
    stw srr0, OSContext.srr0(context)
    stw stack, OSContext.gpr[1](context)
    li r11, 0
    ori r11, r11, 0x9032
    stw r11, OSContext.srr1(context)
    li r0, 0
    stw r0, OSContext.cr(context)
    stw r0, OSContext.xer(context)
    stw r2, OSContext.gpr[2](context)
    stw r13, OSContext.gpr[13](context)
    stw r0, OSContext.gpr[3](context)
    stw r0, OSContext.gpr[4](context)
    stw r0, OSContext.gpr[5](context)
    stw r0, OSContext.gpr[6](context)
    stw r0, OSContext.gpr[7](context)
    stw r0, OSContext.gpr[8](context)
    stw r0, OSContext.gpr[9](context)
    stw r0, OSContext.gpr[10](context)
    stw r0, OSContext.gpr[11](context)
    stw r0, OSContext.gpr[12](context)
    stw r0, OSContext.gpr[14](context)
    stw r0, OSContext.gpr[15](context)
    stw r0, OSContext.gpr[16](context)
    stw r0, OSContext.gpr[17](context)
    stw r0, OSContext.gpr[18](context)
    stw r0, OSContext.gpr[19](context)
    stw r0, OSContext.gpr[20](context)
    stw r0, OSContext.gpr[21](context)
    stw r0, OSContext.gpr[22](context)
    stw r0, OSContext.gpr[23](context)
    stw r0, OSContext.gpr[24](context)
    stw r0, OSContext.gpr[25](context)
    stw r0, OSContext.gpr[26](context)
    stw r0, OSContext.gpr[27](context)
    stw r0, OSContext.gpr[28](context)
    stw r0, OSContext.gpr[29](context)
    stw r0, OSContext.gpr[30](context)
    stw r0, OSContext.gpr[31](context)
    stw r0, OSContext.gqr[0](context)
    stw r0, OSContext.gqr[1](context)
    stw r0, OSContext.gqr[2](context)
    stw r0, OSContext.gqr[3](context)
    stw r0, OSContext.gqr[4](context)
    stw r0, OSContext.gqr[5](context)
    stw r0, OSContext.gqr[6](context)
    stw r0, OSContext.gqr[7](context)

    b OSClearContext
#endif
    // clang-format on
}

void OSDumpContext(OSContext* context) {
    u32 i;
    u32* p;

    OSReport("------------------------- Context 0x%08x -------------------------\n", context);

    for (i = 0; i < 16; ++i) {
        OSReport("r%-2d  = 0x%08x (%14d)  r%-2d  = 0x%08x (%14d)\n", i, context->gpr[i],
                 context->gpr[i], i + 16, context->gpr[i + 16], context->gpr[i + 16]);
    }

    OSReport("LR   = 0x%08x                   CR   = 0x%08x\n", context->lr, context->cr);
    OSReport("SRR0 = 0x%08x                   SRR1 = 0x%08x\n", context->srr0, context->srr1);

    OSReport("\nGQRs----------\n");
    for (i = 0; i < 4; ++i) {
        OSReport("gqr%d = 0x%08x \t gqr%d = 0x%08x\n", i, context->gqr[i], i + 4,
                 context->gqr[i + 4]);
    }

    if (context->state & OS_CONTEXT_STATE_FPSAVED) {
        OSContext* currentContext;
        OSContext fpuContext;
        BOOL enabled;

        enabled = OSDisableInterrupts();
        currentContext = OSGetCurrentContext();
        OSClearContext(&fpuContext);
        OSSetCurrentContext(&fpuContext);

        OSReport("\n\nFPRs----------\n");
        for (i = 0; i < 32; i += 2) {
            OSReport("fr%d \t= %d \t fr%d \t= %d\n", i, (u32)context->fpr[i], i + 1,
                     (u32)context->fpr[i + 1]);
        }
        OSReport("\n\nPSFs----------\n");
        for (i = 0; i < 32; i += 2) {
            OSReport("ps%d \t= 0x%x \t ps%d \t= 0x%x\n", i, (u32)context->ps[i], i + 1,
                     (u32)context->ps[i + 1]);
        }

        OSClearContext(&fpuContext);
        OSSetCurrentContext(currentContext);
        OSRestoreInterrupts(enabled);
    }

    OSReport("\nAddress:      Back Chain    LR Save\n");
    for (i = 0, p = (u32*)context->gpr[1]; p && (u32)p != 0xffffffff && i++ < 16; p = (u32*)*p) {
        OSReport("0x%08x:   0x%08x    0x%08x\n", p, p[0], p[1]);
    }
}

static ASM void OSSwitchFPUContext(register u8 err, register OSContext* context) {
    // clang-format off
#ifdef __MWERKS__
    nofralloc

    mfmsr r5
    ori r5, r5, 0x2000
    mtmsr r5
    isync
    lwz r5, OSContext.srr1(context)
    ori r5, r5, 0x2000
    mtspr 0x1b, r5
    lis r3, OS_CURRENT_FPU_CONTEXT@ha
    lwz r5, OS_CURRENT_FPU_CONTEXT@l(r3)
    stw context, OS_CURRENT_FPU_CONTEXT@l(r3)
    cmpw r5, context
    beq context_is_curr_fpu_context
    cmpwi r5, 0
    beq context_is_null
    bl __OSSaveFPUContext

context_is_null:
    bl __OSLoadFPUContext

context_is_curr_fpu_context:
    lwz r3, OSContext.cr(context)
    mtcrf 0xff, r3
    lwz r3, OSContext.lr(context)
    mtlr r3
    lwz r3, OSContext.srr0(context)
    mtspr 0x1a, r3
    lwz r3, OSContext.ctr(context)
    mtctr r3
    lwz r3, OSContext.xer(context)
    mtxer r3
    lhz r3, OSContext.state(context)
    rlwinm r3, r3, 0, 0x1f, 0x1d
    sth r3, OSContext.state(context)
    lwz r5, OSContext.gpr[5](context)
    lwz r3, OSContext.gpr[3](context)
    lwz context, OSContext.gpr[4](context)
    rfi
#endif
    // clang-format on
}

void __OSContextInit(void) {
    __OSSetExceptionHandler(EXCEPTION_FLOATING_POINT, OSSwitchFPUContext);
    __OSFPUContext = NULL;
    DBPrintf("FPU-unavailable handler installed\n");
}

ASM void OSFillFPUContext(register OSContext* context) {
    // clang-format off
#ifdef __MWERKS__
    nofralloc

    mfmsr r5
    ori r5, r5, 0x2000
    mtmsr r5
    isync

    stfd f0,  OSContext.fpr[ 0](context)
    stfd f1,  OSContext.fpr[ 1](context)
    stfd f2,  OSContext.fpr[ 2](context)
    stfd f3,  OSContext.fpr[ 3](context)
    stfd f4,  OSContext.fpr[ 4](context)
    stfd f5,  OSContext.fpr[ 5](context)
    stfd f6,  OSContext.fpr[ 6](context)
    stfd f7,  OSContext.fpr[ 7](context)
    stfd f8,  OSContext.fpr[ 8](context)
    stfd f9,  OSContext.fpr[ 9](context)
    stfd f10, OSContext.fpr[10](context)
    stfd f11, OSContext.fpr[11](context)
    stfd f12, OSContext.fpr[12](context)
    stfd f13, OSContext.fpr[13](context)
    stfd f14, OSContext.fpr[14](context)
    stfd f15, OSContext.fpr[15](context)
    stfd f16, OSContext.fpr[16](context)
    stfd f17, OSContext.fpr[17](context)
    stfd f18, OSContext.fpr[18](context)
    stfd f19, OSContext.fpr[19](context)
    stfd f20, OSContext.fpr[20](context)
    stfd f21, OSContext.fpr[21](context)
    stfd f22, OSContext.fpr[22](context)
    stfd f23, OSContext.fpr[23](context)
    stfd f24, OSContext.fpr[24](context)
    stfd f25, OSContext.fpr[25](context)
    stfd f26, OSContext.fpr[26](context)
    stfd f27, OSContext.fpr[27](context)
    stfd f28, OSContext.fpr[28](context)
    stfd f29, OSContext.fpr[29](context)
    stfd f30, OSContext.fpr[30](context)
    stfd f31, OSContext.fpr[31](context)

    mffs f0
    stfd f0, OSContext.field_0x190(context)
    lfd f0, OSContext.fpr[0](context)
    mfspr r5, 0x398
    rlwinm. r5, r5, 3, 0x1f, 0x1f
    beq exit

    psq_st f0,  OSContext.ps[ 0](context), 0, 0
    psq_st f1,  OSContext.ps[ 1](context), 0, 0
    psq_st f2,  OSContext.ps[ 2](context), 0, 0
    psq_st f3,  OSContext.ps[ 3](context), 0, 0
    psq_st f4,  OSContext.ps[ 4](context), 0, 0
    psq_st f5,  OSContext.ps[ 5](context), 0, 0
    psq_st f6,  OSContext.ps[ 6](context), 0, 0
    psq_st f7,  OSContext.ps[ 7](context), 0, 0
    psq_st f8,  OSContext.ps[ 8](context), 0, 0
    psq_st f9,  OSContext.ps[ 9](context), 0, 0
    psq_st f10, OSContext.ps[10](context), 0, 0
    psq_st f11, OSContext.ps[11](context), 0, 0
    psq_st f12, OSContext.ps[12](context), 0, 0
    psq_st f13, OSContext.ps[13](context), 0, 0
    psq_st f14, OSContext.ps[14](context), 0, 0
    psq_st f15, OSContext.ps[15](context), 0, 0
    psq_st f16, OSContext.ps[16](context), 0, 0
    psq_st f17, OSContext.ps[17](context), 0, 0
    psq_st f18, OSContext.ps[18](context), 0, 0
    psq_st f19, OSContext.ps[19](context), 0, 0
    psq_st f20, OSContext.ps[20](context), 0, 0
    psq_st f21, OSContext.ps[21](context), 0, 0
    psq_st f22, OSContext.ps[22](context), 0, 0
    psq_st f23, OSContext.ps[23](context), 0, 0
    psq_st f24, OSContext.ps[24](context), 0, 0
    psq_st f25, OSContext.ps[25](context), 0, 0
    psq_st f26, OSContext.ps[26](context), 0, 0
    psq_st f27, OSContext.ps[27](context), 0, 0
    psq_st f28, OSContext.ps[28](context), 0, 0
    psq_st f29, OSContext.ps[29](context), 0, 0
    psq_st f30, OSContext.ps[30](context), 0, 0
    psq_st f31, OSContext.ps[31](context), 0, 0

exit:
    blr
#endif
    // clang-format on
}
