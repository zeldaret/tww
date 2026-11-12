#include "TRK_MINNOW_DOLPHIN/ppc/Generic/targimpl.h"
#include "TRK_MINNOW_DOLPHIN/Os/dolphin/dolphin_trk.h"
#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/main_TRK.h"
#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/mem_TRK.h"
#include "TRK_MINNOW_DOLPHIN/Os/dolphin/dolphin_trk_glue.h"

#include "global.h"

#undef DBAT3U
#undef LR

extern u32 _db_stack_addr;

#define EXCEPTIONMASK_ADDR 0x80000044

u32 lc_base;

u32 TRK_ISR_OFFSETS[15] = {PPC_SystemReset,
                           PPC_MachineCheck,
                           PPC_DataStorage,
                           PPC_InstructionStorage,
                           PPC_ExternalInterrupt,
                           PPC_Alignment,
                           PPC_Program,
                           PPC_FloatingPointUnavaiable,
                           PPC_Decrementer,
                           PPC_SystemCall,
                           PPC_Trace,
                           PPC_PerformanceMonitor,
                           PPC_InstructionAddressBreakpoint,
                           PPC_SystemManagementInterrupt,
                           PPC_ThermalManagementInterrupt};

void EnableMetroTRKInterrupts(void) {
    EnableEXI2Interrupts();
}

u32 TRKTargetTranslate(u32 param_0) {
    if (param_0 >= lc_base) {
        if ((param_0 < lc_base + 0x4000) && ((gTRKCPUState.Extended1.DBAT3U & 3) != 0)) {
            return param_0;
        }
    }
    return param_0 & 0x3FFFFFFF | 0x80000000;
}

extern u8 gTRKInterruptVectorTable[];

static inline void TRK_copy_vector(u32 offset) {
    void* destPtr = (void*)TRKTargetTranslate(offset);
    TRK_memcpy(destPtr, gTRKInterruptVectorTable + offset, 0x100);
    TRK_flush_cache(destPtr, 0x100);
}

static inline void TRK_copy_enabled_vectors(u32* maskPtr) {
    int i;
    u32 mask = *maskPtr;

    for (i = 0; i <= 14; i++) {
        if (mask & (1 << i)) {
            TRK_copy_vector(TRK_ISR_OFFSETS[i]);
        }
    }
}

__declspec(section ".init") void __TRK_copy_vectors(void) {
    TRK_copy_enabled_vectors((u32*)TRKTargetTranslate(0x44));
}

DSError TRKInitializeTarget() {
    gTRKState.isStopped = TRUE;
    gTRKState.msr = __TRK_get_MSR();
    lc_base = 0xE0000000;
    return DS_NoError;
}

asm void InitMetroTRK() {
    // clang-format off
    nofralloc
	addi r1, r1, -4
	stw r3, 0(r1)
	lis r3, gTRKCPUState@h
	ori r3, r3, gTRKCPUState@l
	stmw r0, ProcessorState_PPC.Default.GPR(r3) //Save the gprs
	lwz r4, 0(r1)
	addi r1, r1, 4
	stw r1, ProcessorState_PPC.Default.GPR[1](r3)
	stw r4, ProcessorState_PPC.Default.GPR[3](r3)
	mflr r4
	stw r4, ProcessorState_PPC.Default.LR(r3)
	stw r4, ProcessorState_PPC.Default.PC(r3)
	mfcr r4
	stw r4, ProcessorState_PPC.Default.CR(r3)
	//???
	mfmsr r4
	ori r3, r4, (1 << (31 - 16))
	xori r3, r3, (1 << (31 - 16))
	mtmsr r3
	mtsrr1 r4 //Copy msr to srr1
	//Save misc registers to gTRKCPUState
	bl TRKSaveExtended1Block
	lis r3, gTRKCPUState@h
	ori r3, r3, gTRKCPUState@l
	lmw r0, ProcessorState_PPC.Default.GPR(r3) //Restore the gprs
	//Reset IABR and DABR
	li r0, 0
	mtspr  0x3f2, r0
	mtspr  0x3f5, r0
	//Restore stack pointer
	lis r1, _db_stack_addr@h
	ori r1, r1, _db_stack_addr@l
	mr r3, r5
	bl InitMetroTRKCommTable //Initialize comm table
	/*
	If InitMetroTRKCommTable returned 1 (failure), an invalid hardware
	id or the id for GDEV was somehow passed. Since only BBA or NDEV
	are supported, we return early. Otherwise, we proceed with
	starting up TRK.
	*/
	cmpwi r3, 1
	bne initCommTableSuccess
	/*
	BUG: The code probably orginally reloaded gTRKCPUState here, but
	as is it will read the returned value of InitMetroTRKCommTable
	as a TRKCPUState struct pointer, causing the CPU to return to
	a garbage code address.
	*/
	lwz r4, ProcessorState_PPC.Default.LR(r3)
	mtlr r4
	lmw r0, ProcessorState_PPC.Default.GPR(r3) //Restore the gprs
	blr
initCommTableSuccess:
	b TRK_main //Jump to TRK_main
    // clang-format on
}
