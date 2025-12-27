#include "dolphin/gx/GXFifo.h"
#include "dolphin/gx/GX.h"
#include "dolphin/os/OS.h"
#include "dolphin/base/PPCArch.h"

static void GXInitFifoLimits(GXFifoObj* fifo, u32 hi_watermark, u32 lo_watermark);

static GXFifoObj* CPUFifo;

static GXFifoObj* GPFifo;

static OSThread* __GXCurrentThread;

static GXBool CPGPLinked;

static u32 GXOverflowSuspendInProgress;

static GXBreakPtCallback BreakPointCB;

static u32 __GXOverflowCount;

static void GXOverflowHandler() {
    __GXOverflowCount += 1;
    __GXWriteFifoIntEnable(0, 1);
    __GXWriteFifoIntReset(1, 0);
    GXOverflowSuspendInProgress = TRUE;
    OSSuspendThread(__GXCurrentThread);
}

static void GXUnderflowHandler() {
    OSResumeThread(__GXCurrentThread);
    GXOverflowSuspendInProgress = FALSE;
    __GXWriteFifoIntReset(1, 1);
    __GXWriteFifoIntEnable(1, 0);
}

static void GXBreakPointHandler(OSContext* context) {
    OSContext bpContext;

    SET_REG_FIELD(gx->cpEnable, 1, 5, 0);
    GX_SET_CP_REG(1, gx->cpEnable);

    if (BreakPointCB) {
        OSClearContext(&bpContext);
        OSSetCurrentContext(&bpContext);
        BreakPointCB();
        OSClearContext(&bpContext);
        OSSetCurrentContext(context);
    }
}

static void GXCPInterruptHandler(s16 p1, OSContext* context) {
    gx->cpStatus = GX_GET_CP_REG(0);

    if ((gx->cpEnable >> 3 & 1) && (gx->cpStatus >> 1 & 1)) {
        GXUnderflowHandler();
    }

    if ((gx->cpEnable >> 2 & 1) && (gx->cpStatus >> 0 & 1)) {
        GXOverflowHandler();
    }

    if ((gx->cpEnable >> 5 & 1) && (gx->cpStatus >> 4 & 1)) {
        GXBreakPointHandler(context);
    }
}

void GXInitFifoBase(GXFifoObj* fifo, void* base, u32 size) {
    fifo->base = base;
    fifo->end = (void*)((u32)base + size - 4);
    fifo->size = size;
    fifo->rw_dst = 0;
    GXInitFifoLimits(fifo, size - 0x4000, OSRoundDown32B(size / 2));
    GXInitFifoPtrs(fifo, base, base);
}

void GXInitFifoPtrs(GXFifoObj* fifo, void* readPtr, void* writePtr) {
    int interrupts = OSDisableInterrupts();
    fifo->read_ptr = readPtr;
    fifo->write_ptr = writePtr;
    fifo->rw_dst = (u32)writePtr - (u32)readPtr;
    if (fifo->rw_dst < 0) {
        fifo->rw_dst += fifo->size;
    }
    OSRestoreInterrupts(interrupts);
}

static void GXInitFifoLimits(GXFifoObj* fifo, u32 hi_watermark, u32 lo_watermark) {
    fifo->high_wtrmark = hi_watermark;
    fifo->low_wtrmark = lo_watermark;
}

void GXSetCPUFifo(GXFifoObj* fifo) {
    BOOL interrupts;
    interrupts = OSDisableInterrupts();

    CPUFifo = fifo;

    if (fifo == GPFifo) {
        u32 reg;
        GX_SET_PI_REG(3, (u32)fifo->base & 0x3FFFFFFF);
        GX_SET_PI_REG(4, (u32)fifo->end & 0x3FFFFFFF);
        reg = 0;
        GX_BITFIELD_SET(reg, 6, 21, ((u32)fifo->write_ptr & 0x3FFFFFFF) >> 5);
        GX_BITFIELD_SET(reg, 5, 1, 0);
        GX_SET_PI_REG(5, reg);

        CPGPLinked = GX_TRUE;

        __GXWriteFifoIntReset(1, 1);
        __GXWriteFifoIntEnable(1, 0);
        __GXFifoLink(1);
    } else {
        u32 reg;
        if (CPGPLinked) {
            __GXFifoLink(0);
            CPGPLinked = GX_FALSE;
        }
        __GXWriteFifoIntEnable(0, 0);

        GX_SET_PI_REG(3, (u32)fifo->base & 0x3FFFFFFF);
        GX_SET_PI_REG(4, (u32)fifo->end & 0x3FFFFFFF);
        reg = 0;
        GX_BITFIELD_SET(reg, 6, 21, ((u32)fifo->write_ptr & 0x3FFFFFFF) >> 5);
        GX_BITFIELD_SET(reg, 5, 1, 0);
        GX_SET_PI_REG(5, reg);
    }

    PPCSync();

    OSRestoreInterrupts(interrupts);
}

void GXSetGPFifo(GXFifoObj* fifo) {
    int interrupts = OSDisableInterrupts();
    u32 reg;
    __GXFifoReadDisable();
    __GXWriteFifoIntEnable(0, 0);
    GPFifo = fifo;
    GX_SET_CP_REG(16, (u16)fifo->base);
    GX_SET_CP_REG(18, (u16)fifo->end);
    GX_SET_CP_REG(24, (u16)fifo->rw_dst);
    GX_SET_CP_REG(26, (u16)fifo->write_ptr);
    GX_SET_CP_REG(28, (u16)fifo->read_ptr);
    GX_SET_CP_REG(20, (u16)fifo->high_wtrmark);
    GX_SET_CP_REG(22, (u16)fifo->low_wtrmark);

    GX_SET_CP_REG(17, ((u32)fifo->base & 0x3FFFFFFF) >> 16);
    GX_SET_CP_REG(19, ((u32)fifo->end & 0x3FFFFFFF) >> 16);
    GX_SET_CP_REG(25, (fifo->rw_dst) >> 16);
    GX_SET_CP_REG(27, ((u32)fifo->write_ptr & 0x3FFFFFFF) >> 16);
    GX_SET_CP_REG(29, ((u32)fifo->read_ptr & 0x3FFFFFFF) >> 16);
    GX_SET_CP_REG(21, (fifo->high_wtrmark) >> 16);
    GX_SET_CP_REG(23, (fifo->low_wtrmark) >> 16);

    PPCSync();

    if (CPUFifo == GPFifo) {
        CPGPLinked = 1;
        __GXWriteFifoIntEnable(1, 0);
        __GXFifoLink(1);
    } else {
        CPGPLinked = 0;
        __GXWriteFifoIntEnable(0, 0);
        __GXFifoLink(0);
    }
    reg = gx->cpEnable;
    __GXWriteFifoIntReset(1, 1);
    __GXFifoReadEnable();
    OSRestoreInterrupts(interrupts);
}

void GXSaveCPUFifo(GXFifoObj* fifo) {
    __GXSaveCPUFifoAux(fifo);
}

#define SOME_MACRO1(fifo) \
do { \
    u32 temp = GX_GET_CP_REG(29) << 16; \
    temp |= GX_GET_CP_REG(28); \
    fifo->read_ptr = OSPhysicalToCached(temp); \
} while (0)

#define SOME_MACRO2(fifo) \
do { \
    u32 temp = GX_GET_CP_REG(25) << 16; \
    temp |= GX_GET_CP_REG(24); \
    fifo->rw_dst = temp; \
} while (0)

void __GXSaveCPUFifoAux(GXFifoObj* fifo) {
    int interrupts = OSDisableInterrupts();

    GXFlush();
    fifo->base = OSPhysicalToCached(GX_GET_PI_REG(3));
    fifo->end = OSPhysicalToCached(GX_GET_PI_REG(4));
    fifo->write_ptr = OSPhysicalToCached(GX_GET_PI_REG(5) & ~0x4000000);
    if (CPGPLinked != 0) {
        SOME_MACRO1(fifo);
        SOME_MACRO2(fifo);
    } else {
        fifo->rw_dst = (u32)fifo->write_ptr - (u32)fifo->read_ptr;
        if (fifo->rw_dst < 0) {
            fifo->rw_dst += fifo->size;
        }
    }
    OSRestoreInterrupts(interrupts);
}

void GXGetGPStatus(GXBool* overhi, GXBool* underlow, GXBool* readIdle, GXBool* cmdIdle,
                   GXBool* brkpt) {
    gx->cpStatus = GX_GET_CP_REG(0);
    *overhi = gx->cpStatus & 1;
    *underlow = (gx->cpStatus >> 1) & 1;
    *readIdle = (gx->cpStatus >> 2) & 1;
    *cmdIdle = (gx->cpStatus >> 3) & 1;
    *brkpt = (gx->cpStatus >> 4) & 1;
}

void* GXGetFifoBase(GXFifoObj* fifo) {
    return fifo->base;
}

u32 GXGetFifoSize(GXFifoObj* fifo) {
    return fifo->size;
}

GXBreakPtCallback GXSetBreakPtCallback(GXBreakPtCallback cb) {
    GXBreakPtCallback oldCallback = BreakPointCB;
    int interrupts = OSDisableInterrupts();
    BreakPointCB = cb;
    OSRestoreInterrupts(interrupts);
    return oldCallback;
}

void __GXFifoInit(void) {
    __OSSetInterruptHandler(0x11, GXCPInterruptHandler);
    __OSUnmaskInterrupts(0x4000);
    __GXCurrentThread = OSGetCurrentThread();
    GXOverflowSuspendInProgress = 0;
    CPUFifo = NULL;
    GPFifo = NULL;
}

void __GXFifoReadEnable(void) {
    SET_REG_FIELD(gx->cpEnable, 1, 0, 1);
    GX_SET_CP_REG(1, gx->cpEnable);
}

void __GXFifoReadDisable(void) {
    SET_REG_FIELD(gx->cpEnable, 1, 0, 0);
    GX_SET_CP_REG(1, gx->cpEnable);
}

void __GXFifoLink(u8 en) {
    SET_REG_FIELD(gx->cpEnable, 1, 4, (en != 0) ? 1 : 0);
    GX_SET_CP_REG(1, gx->cpEnable);
}

void __GXWriteFifoIntEnable(u8 hiWatermarkEn, u8 loWatermarkEn) {
    SET_REG_FIELD(gx->cpEnable, 1, 2, hiWatermarkEn);
    SET_REG_FIELD(gx->cpEnable, 1, 3, loWatermarkEn);
    GX_SET_CP_REG(1, gx->cpEnable);
}

void __GXWriteFifoIntReset(u8 hiWatermarkClr, u8 loWatermarkClr) {
    SET_REG_FIELD(gx->cpClr, 1, 0, hiWatermarkClr);
    SET_REG_FIELD(gx->cpClr, 1, 1, loWatermarkClr);
    GX_SET_CP_REG(2, gx->cpClr);
}

void __GXCleanGPFifo(void) {
    BOOL interrupts;
    GXFifoObj tempObj;   // 0x14
    u32 i, j, k;         // stack alloc
    GXFifoObj* gpFifo;   // r31
    GXFifoObj* cpuFifo;  // r30
    void* tempPtr;       // r29

    gpFifo = GXGetGPFifo();
    if (!gpFifo) {
        return;
    }

    cpuFifo = GXGetCPUFifo();
    tempPtr = gpFifo->base;

    tempObj = *gpFifo;

    interrupts = OSDisableInterrupts();

    tempObj.read_ptr = tempPtr;
    tempObj.write_ptr = tempPtr;
    tempObj.rw_dst = 0;
    if (tempObj.rw_dst < 0) {
        tempObj.rw_dst += tempObj.size;
    }

    OSRestoreInterrupts(interrupts);

    GXSetGPFifo(&tempObj);

    if (cpuFifo == gpFifo) {
        GXSetCPUFifo(&tempObj);
    }

    interrupts = OSDisableInterrupts();

    gpFifo->read_ptr = tempPtr;
    gpFifo->write_ptr = tempPtr;
    gpFifo->rw_dst = 0;

    if (gpFifo->rw_dst < 0) {
        gpFifo->rw_dst += gpFifo->size;
    }
    OSRestoreInterrupts(interrupts);

    GXSetGPFifo(gpFifo);
    if (cpuFifo == gpFifo) {
        GXSetCPUFifo(cpuFifo);
    }
}

OSThread* GXSetCurrentGXThread(void) {
    BOOL interrupts = OSDisableInterrupts();
    OSThread* prevThread = __GXCurrentThread;
    __GXCurrentThread = OSGetCurrentThread();
    OSRestoreInterrupts(interrupts);
    return prevThread;
}

OSThread* GXGetCurrentGXThread(void) {
    return *(OSThread**)(&__GXCurrentThread);
}

GXFifoObj* GXGetCPUFifo(void) {
    return *(GXFifoObj**)(&CPUFifo);
}

GXFifoObj* GXGetGPFifo(void) {
    return GPFifo;
}
