//
// OS
//

#include "dolphin/os/OS.h"
#include "dolphin/base/PPCArch.h"
// #include "dolphin/db.h"
#include "dolphin/pad/Pad.h"
#include "dolphin/dvd/dvdfs.h"
// #include "TRK_MINNOW_DOLPHIN/Os/dolphin/dolphin_trk.h"

#define OS_BI2_DEBUG_ADDRESS 0x800000F4
#define OS_BI2_DEBUGFLAG_OFFSET 0xC
#define PAD3_BUTTON_ADDR 0x800030E4
#define OS_DVD_DEVICECODE 0x800030E6
#define DEBUGFLAG_ADDR 0x800030E8
#define OS_DEBUG_ADDRESS_2 0x800030E9
#define DB_EXCEPTIONRET_OFFSET 0xC
#define DB_EXCEPTIONDEST_OFFSET 0x8

#define OS_EXCEPTIONTABLE_ADDR 0x3000
#define OS_DBJUMPPOINT_ADDR 0x60
#define OS_CURRENTCONTEXT_PADDR 0xC0

//
// External References:
//

void _epilog();

static OSBootInfo* BootInfo;

static volatile u32* BI2DebugFlag;

static u32* BI2DebugFlagHolder;

OSTime __OSStartTime;

BOOL __OSInIPL;

extern OSExceptionHandler* OSExceptionTable;
OSExceptionHandler* OSExceptionTable;

extern BOOL AreWeInitialized;
BOOL AreWeInitialized;

extern f64 ZeroPS;
f64 ZeroPS;

extern f64 ZeroF;
f64 ZeroF;

BOOL __OSIsGcam;

asm void __OSFPRInit(void) {
    // clang-format off
    nofralloc

    mfmsr r3
    ori r3, r3, 0x2000
    mtmsr r3

    mfspr r3, 0x398
    rlwinm. r3, r3, 3, 0x1f, 0x1f
    beq skip_ps_init

    lis r3, ZeroPS@ha
    addi r3, r3, ZeroPS@l
    psq_l f0, 0(r3), 0, 0
    ps_mr f1, f0
    ps_mr f2, f0
    ps_mr f3, f0
    ps_mr f4, f0
    ps_mr f5, f0
    ps_mr f6, f0
    ps_mr f7, f0
    ps_mr f8, f0
    ps_mr f9, f0
    ps_mr f10, f0
    ps_mr f11, f0
    ps_mr f12, f0
    ps_mr f13, f0
    ps_mr f14, f0
    ps_mr f15, f0
    ps_mr f16, f0
    ps_mr f17, f0
    ps_mr f18, f0
    ps_mr f19, f0
    ps_mr f20, f0
    ps_mr f21, f0
    ps_mr f22, f0
    ps_mr f23, f0
    ps_mr f24, f0
    ps_mr f25, f0
    ps_mr f26, f0
    ps_mr f27, f0
    ps_mr f28, f0
    ps_mr f29, f0
    ps_mr f30, f0
    ps_mr f31, f0

skip_ps_init:
    lfd f0, ZeroF(r13)
    fmr f1, f0
    fmr f2, f0
    fmr f3, f0
    fmr f4, f0
    fmr f5, f0
    fmr f6, f0
    fmr f7, f0
    fmr f8, f0
    fmr f9, f0
    fmr f10, f0
    fmr f11, f0
    fmr f12, f0
    fmr f13, f0
    fmr f14, f0
    fmr f15, f0
    fmr f16, f0
    fmr f17, f0
    fmr f18, f0
    fmr f19, f0
    fmr f20, f0
    fmr f21, f0
    fmr f22, f0
    fmr f23, f0
    fmr f24, f0
    fmr f25, f0
    fmr f26, f0
    fmr f27, f0
    fmr f28, f0
    fmr f29, f0
    fmr f30, f0
    fmr f31, f0

    mtfsf 0xff, f0
    blr
    // clang-format on
}

u32 OSGetConsoleType(void) {
    if (BootInfo == NULL || BootInfo->console_type == 0) {
        return OS_CONSOLE_ARTHUR;
    }

    return BootInfo->console_type;
}

static DVDDriveInfo DriveInfo;

void* __OSSavedRegionStart;
void* __OSSavedRegionEnd;

extern OSExecParams __OSRebootParams;

static inline void ClearArena(void) {
    BOOL var_r0;
    if (OSGetResetCode() & 0x80000000) {
        var_r0 = TRUE;
    } else {
        var_r0 = FALSE;
    }

    if (!var_r0) {
        memset(OSGetArenaLo(), 0U, (u32)OSGetArenaHi() - (u32)OSGetArenaLo());
        return;
    }

    if (*(u32*)&__OSRebootParams.regionStart == 0U) {
        memset(OSGetArenaLo(), 0U, (u32)OSGetArenaHi() - (u32)OSGetArenaLo());
        return;
    }

    if ((u32)OSGetArenaLo() < *(u32*)&__OSRebootParams.regionStart) {
        if ((u32)OSGetArenaHi() <= *(u32*)&__OSRebootParams.regionStart) {
            memset((u32)OSGetArenaLo(), 0U, (u32)OSGetArenaHi() - (u32)OSGetArenaLo());
            return;
        }

        memset(OSGetArenaLo(), 0U, *(u32*)&__OSRebootParams.regionStart - (u32)OSGetArenaLo());

        if ((u32)OSGetArenaHi() > *(u32*)&__OSRebootParams.regionEnd) {
            memset(*(u32*)&__OSRebootParams.regionEnd, 0,
                   (u32)OSGetArenaHi() - *(u32*)&__OSRebootParams.regionEnd);
        }
    }
}

static void InquiryCallback(s32 result, DVDCommandBlock* block) {
    switch (block->state) {
    case 0:
        __OSDeviceCode = (u16)(0x8000 | DriveInfo.device_code);
        break;
    default:
        __OSDeviceCode = 1;
        break;
    }
}

static u8 DriveBlock[48];

OSExecParams __OSRebootParams;

static const char* __OSVersion = "<< Dolphin SDK - OS	release build: Nov 10 2004 06:26:41 (0x2301) >>";

extern u8 __ArenaHi[];
extern u8 __ArenaLo[];
extern void* _stack_end;
extern char _db_stack_end[];

void OSInit(void) {
    /*
    Initializes the Dolphin operating system.
        - most of the main operations get farmed out to other functions
        - loading debug info and setting up heap bounds largely happen here
        - a lot of OS reporting also gets controlled here
    */

    BI2Debug* DebugInfo;
    void* debugArenaLo;
    u32 inputConsoleType;
    u32 tdev;

    if ((BOOL)AreWeInitialized == FALSE) {
        AreWeInitialized = TRUE;

        // SYSTEM //
        __OSStartTime = __OSGetSystemTime();
        OSDisableInterrupts();

        __OSGetExecParams(&__OSRebootParams);
        PPCMtmmcr0(0);
        PPCMtmmcr1(0);
        PPCMtpmc1(0);
        PPCMtpmc2(0);
        PPCMtpmc3(0);
        PPCMtpmc4(0);
        PPCDisableSpeculation();
        PPCSetFpNonIEEEMode();

        // DEBUG //
        BI2DebugFlag = 0;                        // debug flag from the DVD BI2 header
        BootInfo = (OSBootInfo*)OS_BASE_CACHED;  // set pointer to BootInfo

        __DVDLongFileNameFlag =
            (u32)0;  // flag to tell us whether we make it through the debug loading

        // time to grab a bunch of debug info from the DVD
        // the address for where the BI2 debug info is, is stored at OS_BI2_DEBUG_ADDRESS
        DebugInfo = (BI2Debug*)*((u32*)OS_BI2_DEBUG_ADDRESS);

        if (DebugInfo != NULL) {
            BI2DebugFlag = &DebugInfo->debugFlag;        // debug flag from DVD BI2
            __PADSpec = (u32)DebugInfo->padSpec;         // some other info from DVD BI2
            *((u8*)DEBUGFLAG_ADDR) = (u8)*BI2DebugFlag;  // store flag in mem
            *((u8*)OS_DEBUG_ADDRESS_2) = (u8)__PADSpec;  // store other info in mem
        } else if (BootInfo->arena_hi) {
            BI2DebugFlagHolder =
                (u32*)*((u8*)DEBUGFLAG_ADDR);               // grab whatever's stored at 0x800030E8
            BI2DebugFlag = (u32*)&BI2DebugFlagHolder;       // flag is then address of flag holder
            __PADSpec = (u32) * ((u8*)OS_DEBUG_ADDRESS_2);  // pad spec is whatever's at 0x800030E9
        }

        __DVDLongFileNameFlag = 1;

        // HEAP //
        OSSetArenaLo((BootInfo->arena_lo == NULL) ? __ArenaLo : BootInfo->arena_lo);

        // if the input arenaLo is null, and debug flag location exists (and flag is < 2),
        //     set arenaLo to just past the end of the db stack
        if ((BootInfo->arena_lo == NULL) && (BI2DebugFlag != 0) && (*BI2DebugFlag < 2)) {
            debugArenaLo = (char*)(((u32)_db_stack_end + 0x1f) & ~0x1f);
            OSSetArenaLo(debugArenaLo);
        }

        OSSetArenaHi((BootInfo->arena_hi == NULL) ? __ArenaHi : BootInfo->arena_hi);

        // OS INIT AND REPORT //
        OSExceptionInit();
        __OSInitSystemCall();
        OSInitAlarm();
        __OSModuleInit();
        __OSInterruptInit();
        __OSSetInterruptHandler(OS_INTR_PI_RSW, (void*)__OSResetSWInterruptHandler);
        __OSContextInit();
        __OSCacheInit();
        EXIInit();
        SIInit();
        __OSInitSram();
        __OSThreadInit();
        __OSInitAudioSystem();
        PPCMthid2(PPCMfhid2() & 0xBFFFFFFF);
        if ((BOOL)__OSInIPL == FALSE) {
            __OSInitMemoryProtection();
        }

        OSReport("\nDolphin OS\n");
        OSReport("Kernel built : %s %s\n", "Nov 10 2004", "06:26:41");
        OSReport("Console Type : ");

        if (BootInfo == NULL || (inputConsoleType = BootInfo->console_type) == 0) {
            inputConsoleType = OS_CONSOLE_ARTHUR;  // default console type
        } else {
            inputConsoleType = BootInfo->console_type;
        }

        switch (inputConsoleType & 0xF0000000) {
        case OS_CONSOLE_RETAIL:
            OSReport("Retail %d\n", inputConsoleType);
            break;
        case OS_CONSOLE_DEVELOPMENT:
        case OS_CONSOLE_TDEV:
            switch (inputConsoleType & 0x0FFFFFFF) {
            case OS_CONSOLE_EMULATOR:
                OSReport("Mac Emulator\n");
                break;
            case OS_CONSOLE_PC_EMULATOR:
                OSReport("PC Emulator\n");
                break;
            case OS_CONSOLE_ARTHUR:
                OSReport("EPPC Arthur\n");
                break;
            case OS_CONSOLE_MINNOW:
                OSReport("EPPC Minnow\n");
                break;
            default:
                tdev = (u32)inputConsoleType & 0x0FFFFFFF;
                OSReport("Development HW%d (%08x)\n", tdev - 3, inputConsoleType);
                break;
            }
            break;
        default:
            OSReport("%08x\n", inputConsoleType);
            break;
        }

        OSReport("Memory %d MB\n", (u32)BootInfo->memory_size >> 0x14U);
        OSReport("Arena : 0x%x - 0x%x\n", OSGetArenaLo(), OSGetArenaHi());
        OSRegisterVersion(__OSVersion);

        if (BI2DebugFlag && ((*BI2DebugFlag) >= 2)) {
            EnableMetroTRKInterrupts();
        }

        ClearArena();
        OSEnableInterrupts();

        if ((BOOL)__OSInIPL == FALSE) {
            DVDInit();
            if ((BOOL)__OSIsGcam) {
                __OSDeviceCode = 0x9000;
                return;
            }
            DCInvalidateRange(&DriveInfo, sizeof(DriveInfo));
            DVDInquiryAsync((DVDCommandBlock*)&DriveBlock, &DriveInfo, InquiryCallback);
        }
    }
}

static u32 __OSExceptionLocations[] = {
    0x00000100,  // 0  System reset
    0x00000200,  // 1  Machine check
    0x00000300,  // 2  DSI - seg fault or DABR
    0x00000400,  // 3  ISI
    0x00000500,  // 4  External interrupt
    0x00000600,  // 5  Alignment
    0x00000700,  // 6  Program
    0x00000800,  // 7  FP Unavailable
    0x00000900,  // 8  Decrementer
    0x00000C00,  // 9  System call
    0x00000D00,  // 10 Trace
    0x00000F00,  // 11 Performance monitor
    0x00001300,  // 12 Instruction address breakpoint.
    0x00001400,  // 13 System management interrupt
    0x00001700   // 14 Thermal interrupt
};

// dummy entry points to the OS Exception vector
void __OSEVStart(void);
void __OSDBINTSTART(void);
void __OSDBINTEND(void);
void __OSDBJUMPSTART(void);
void __OSDBJUMPEND(void);

#define NOP 0x60000000

static void OSExceptionInit(void) {
    __OSException exception;
    void* destAddr;

    // These two vars help us change the exception number embedded
    // in the exception handler code.
    u32* opCodeAddr;
    u32 oldOpCode;

    // Address range of the actual code to be copied.
    u8* handlerStart;
    u32 handlerSize;

    // Install the first level exception vector.
    opCodeAddr = (u32*)__OSEVSetNumber;
    oldOpCode = *opCodeAddr;
    handlerStart = (u8*)__OSEVStart;
    handlerSize = (u32)((u8*)__OSEVEnd - (u8*)__OSEVStart);

    // Install the DB integrator, only if we are the first OSInit to be run
    destAddr = (void*)OSPhysicalToCached(OS_DBJUMPPOINT_ADDR);
    if (*(u32*)destAddr == 0)  // Lomem should be zero cleared only once by BS2
    {
        DBPrintf("Installing OSDBIntegrator\n");
        memcpy(destAddr, (void*)__OSDBINTSTART, (u32)__OSDBINTEND - (u32)__OSDBINTSTART);
        DCFlushRangeNoSync(destAddr, (u32)__OSDBINTEND - (u32)__OSDBINTSTART);
        __sync();
        ICInvalidateRange(destAddr, (u32)__OSDBINTEND - (u32)__OSDBINTSTART);
    }

    // Copy the right vector into the table
    for (exception = 0; exception < 15; exception++) {
        if (BI2DebugFlag && (*BI2DebugFlag >= 2) && __DBIsExceptionMarked(exception)) {
            // this DBPrintf is suspicious.
            DBPrintf(">>> OSINIT: exception %d commandeered by TRK\n", exception);
            continue;
        }

        // Modify the copy of code in text before transferring
        // to the exception table.
        *opCodeAddr = oldOpCode | exception;

        // Modify opcodes at __DBVECTOR if necessary
        if (__DBIsExceptionMarked(exception)) {
            DBPrintf(">>> OSINIT: exception %d vectored to debugger\n", exception);
            memcpy((void*)__DBVECTOR, (void*)__OSDBJUMPSTART,
                   (u32)__OSDBJUMPEND - (u32)__OSDBJUMPSTART);
        } else {
            // make sure the opcodes are still nop
            u32* ops = (u32*)__DBVECTOR;
            int cb;

            for (cb = 0; cb < (u32)__OSDBJUMPEND - (u32)__OSDBJUMPSTART; cb += sizeof(u32)) {
                *ops++ = NOP;
            }
        }

        // Install the modified handler.
        destAddr = (void*)OSPhysicalToCached(__OSExceptionLocations[(u32)exception]);
        memcpy(destAddr, handlerStart, handlerSize);
        DCFlushRangeNoSync(destAddr, handlerSize);
        __sync();
        ICInvalidateRange(destAddr, handlerSize);
    }

    // initialize pointer to exception table
    OSExceptionTable = OSPhysicalToCached(OS_EXCEPTIONTABLE_ADDR);

    // install default exception handlers
    for (exception = 0; exception < 15; exception++) {
        __OSSetExceptionHandler(exception, OSDefaultExceptionHandler);
    }

    // restore the old opcode, so that we can re-start an application without
    // downloading the text segments
    *opCodeAddr = oldOpCode;

    DBPrintf("Exceptions initialized...\n");
}

asm void __OSDBIntegrator(void) {
    // clang-format off
    nofralloc

entry __OSDBINTSTART
    li r5, 0x40
    mflr r3
    stw r3, 0xc(r5)
    lwz r3, 8(r5)
    oris r3, r3, 0x8000
    mtlr r3
    li r3, 0x30
    mtmsr r3
    blr
entry __OSDBINTEND
    // clang-format on
}

asm void __OSDBJump(void){
    // clang-format off
    nofralloc

entry __OSDBJUMPSTART
    bla 0x60
entry __OSDBJUMPEND
    // clang-format on
}

OSExceptionHandler __OSSetExceptionHandler(__OSException exception, OSExceptionHandler handler) {
    OSExceptionHandler old = OSExceptionTable[exception];
    OSExceptionTable[exception] = handler;
    return old;
}

OSExceptionHandler __OSGetExceptionHandler(__OSException exception) {
    return OSExceptionTable[exception];
}

static asm void OSExceptionVector(void) {
    // clang-format off
    nofralloc

entry __OSEVStart
    // Save r4 into SPRG0
    mtsprg 0, r4

    // Load current context physical address into r4
    lwz r4, OS_CURRENTCONTEXT_PADDR

    // Save r3 - r5 into the current context
    stw r3, OS_CONTEXT_R3(r4)
    mfsprg r3, 0
    stw r3, OS_CONTEXT_R4(r4)
    stw r5, OS_CONTEXT_R5(r4)

    lhz r3, OS_CONTEXT_STATE(r4)
    ori r3, r3, OS_CONTEXT_STATE_EXC
    sth r3, OS_CONTEXT_STATE(r4)

    // Save misc registers
    mfcr r3
    stw r3, OS_CONTEXT_CR(r4)
    mflr r3
    stw r3, OS_CONTEXT_LR(r4)
    mfctr r3
    stw r3, OS_CONTEXT_CTR(r4)
    mfxer r3
    stw r3, OS_CONTEXT_XER(r4)
    mfsrr0 r3
    stw r3, OS_CONTEXT_SRR0(r4)
    mfsrr1 r3
    stw r3, OS_CONTEXT_SRR1(r4)
    mr r5, r3

entry __DBVECTOR
    nop

    // Set SRR1[IR|DR] to turn on address
    // translation at the next RFI
    mfmsr r3
    ori r3, r3, 0x30
    mtsrr1 r3

    // This lets us change the exception number based on the
    // exception we're installing.
entry __OSEVSetNumber
    li r3, 0

    // Load current context virtual address into r4
    lwz r4, 0xd4(r0)

    // Check non-recoverable interrupt
    rlwinm. r5, r5, 0, MSR_RI_BIT, MSR_RI_BIT
    bne recoverable
    lis r5, OSDefaultExceptionHandler@ha
    addi r5, r5, OSDefaultExceptionHandler@l
    mtsrr0 r5
    rfi
    // NOT REACHED HERE

recoverable:
    // Locate exception handler.
    rlwinm r5, r3, 2, 0x16, 0x1d  // r5 contains exception*4
    lwz r5, OS_EXCEPTIONTABLE_ADDR(r5)
    mtsrr0 r5

    // Final state
    // r3 - exception number
    // r4 - pointer to context
    // r5 - garbage
    // srr0 - exception handler
    // srr1 - address translation enabled, not yet recoverable

    rfi 
    // NOT REACHED HERE
    // The handler will restore state

entry __OSEVEnd
    nop
    // clang-format on
}

static asm void OSDefaultExceptionHandler(register __OSException exception,
                                          register OSContext* context) {
    // clang-format off
    nofralloc

    stw r0, 0(context)
    stw r1, 4(context)
    stw r2, 8(context)
    stmw r6, 0x18(context)
    mfspr r0, 0x391
    stw r0, 0x1a8(context)
    mfspr r0, 0x392
    stw r0, 0x1ac(context)
    mfspr r0, 0x393
    stw r0, 0x1b0(context)
    mfspr r0, 0x394
    stw r0, 0x1b4(context)
    mfspr r0, 0x395
    stw r0, 0x1b8(context)
    mfspr r0, 0x396
    stw r0, 0x1bc(context)
    mfspr r0, 0x397
    stw r0, 0x1c0(context)

    mfdsisr r5
    mfdar r6

    stwu r1, -8(r1)
    b __OSUnhandledException
    // clang-format on
}

asm void __OSPSInit(void){
    // clang-format off
    nofralloc

    mflr r0
    stw r0, 4(r1)
    stwu r1, -8(r1)
    bl PPCMfhid2
    oris r3, r3, 0xa000
    bl PPCMthid2
    bl ICFlashInvalidate
    sync

    li r3, 0
    mtspr 0x390, r3
    mtspr 0x391, r3
    mtspr 0x392, r3
    mtspr 0x393, r3
    mtspr 0x394, r3
    mtspr 0x395, r3
    mtspr 0x396, r3
    mtspr 0x397, r3

    lwz r0, 0xc(r1)
    addi r1, r1, 8
    mtlr r0
    blr
    // clang-format on
}

vu32 __DIRegs[16] : 0xCC006000;
#define DI_CONFIG_IDX 0x9
#define DI_CONFIG_CONFIG_MASK 0xFF

u32 __OSGetDIConfig(void) {
    return (__DIRegs[DI_CONFIG_IDX] & DI_CONFIG_CONFIG_MASK);
}

void OSRegisterVersion(const char* version) {
    OSReport("%s\n", version);
}
