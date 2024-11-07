#include "dolphin/gx/GXMisc.h"
#include "dolphin/gx/GX.h"
#include "dolphin/os/OSInterrupt.h"
#include "dolphin/os/OSReset.h"
#include "dolphin/os/OSTime.h"
#include "dolphin/base/PPCArch.h"

static void GXTokenInterruptHandler(__OSInterrupt interrupt, OSContext* context);
static void GXFinishInterruptHandler(__OSInterrupt interrupt, OSContext* pContext);

void GXSetMisc(GXMiscToken token, u32 val) {
    switch (token) {
    case GX_MT_NULL:
        break;

    case GX_MT_XF_FLUSH:
        gx->vNum = val;
        gx->vNumNot = !gx->vNum;
        gx->bpSentNot = GX_TRUE;

        if (gx->vNum) {
            gx->dirtyState |= GX_DIRTY_VCD;
        }
        break;

    case GX_MT_DL_SAVE_CONTEXT:
        gx->dlSaveContext = (val != 0);
        break;
    }
}

void GXFlush(void) {
    if (gx->dirtyState) {
        __GXSetDirtyState();
    }

    GXFIFO.u32 = 0;
    GXFIFO.u32 = 0;
    GXFIFO.u32 = 0;
    GXFIFO.u32 = 0;
    GXFIFO.u32 = 0;
    GXFIFO.u32 = 0;
    GXFIFO.u32 = 0;
    GXFIFO.u32 = 0;

    PPCSync();
}

static void __GXAbortWait(u32 clocks) {
    OSTime time0, time1;
    time0 = OSGetTime();

    do {
        time1 = OSGetTime();
    } while (time1 - time0 <= clocks / 4);
}

void __GXAbort(void) {
    __PIRegs[0x18 / 4] = 1;
    __GXAbortWait(200);
    __PIRegs[0x18 / 4] = 0;
    __GXAbortWait(20);
}

void GXAbortFrame(void) {
    __GXAbort();
    __GXCleanGPFifo();
}

/* ############################################################################################## */
static GXDrawSyncCallback TokenCB;

static GXDrawDoneCallback DrawDoneCB;

static GXBool DrawDone;

void GXSetDrawDone(void) {
    u8 padding[8];
    BOOL restore = OSDisableInterrupts();
    GFWriteBPCmd(0x45000002);
    GXFlush();
    DrawDone = 0;
    OSRestoreInterrupts(restore);
}

/* ############################################################################################## */
static OSThreadQueue FinishQueue;

static void GXWaitDrawDone(void) {
    BOOL restore = OSDisableInterrupts();
    while (DrawDone == 0) {
        OSSleepThread(&FinishQueue);
    }
    OSRestoreInterrupts(restore);
}

void GXDrawDone(void) {
    u8 padding[8];
    GXSetDrawDone();
    GXWaitDrawDone();
}

void GXPixModeSync(void) {
    GXFIFO.u8 = 0x61;
    GXFIFO.u32 = gx->peCtrl;
    gx->bpSentNot = 0;
}

void GXPokeAlphaMode(GXCompare comp, u8 threshold) {
    __peReg[3] = (comp << 8) | threshold;
}

void GXPokeAlphaRead(GXAlphaReadMode mode) {
    u32 val = 0;
    GX_BITFIELD_SET(val, 0x1e, 2, mode);
    GX_BITFIELD_SET(val, 0x1d, 1, 1);
    __peReg[4] = val;
}

void GXPokeAlphaUpdate(GXBool enable_update) {
    GX_BITFIELD_SET(__peReg[1], 0x1b, 1, enable_update);
}

void GXPokeBlendMode(GXBlendMode mode, GXBlendFactor srcFactor, GXBlendFactor destFactor,
                     GXLogicOp op) {
    u32 reg;

    reg = GX_GET_PE_REG(1);
    GX_SET_REG(reg, (mode == GX_BM_BLEND) || (mode == GX_BM_SUBTRACT), 31, 31);
    GX_SET_REG(reg, (mode == GX_BM_SUBTRACT), 20, 20);
    GX_SET_REG(reg, (mode == GX_BM_LOGIC), 30, 30);
    GX_SET_REG(reg, op, 16, 19);
    GX_SET_REG(reg, srcFactor, 21, 23);
    GX_SET_REG(reg, destFactor, 24, 26);
    GX_SET_REG(reg, 0x41, 0, 7);
    GX_SET_PE_REG(1, reg);
}

void GXPokeColorUpdate(GXBool enable_update) {
    GX_BITFIELD_SET(__peReg[1], 0x1c, 1, enable_update);
}

void GXPokeDstAlpha(GXBool enable, u8 alpha) {
    u32 val = 0;
    GX_BITFIELD_SET(val, 0x18, 8, alpha);
    GX_BITFIELD_SET(val, 0x17, 1, enable);
    __peReg[2] = val;
}

void GXPokeDither(GXBool enable) {
    GX_BITFIELD_SET(__peReg[1], 0x1d, 1, enable);
}

void GXPokeZMode(GXBool enable_compare, GXCompare comp, GXBool update_enable) {
    u32 val = 0;
    GX_BITFIELD_SET(val, 0x1f, 1, enable_compare);
    GX_BITFIELD_SET(val, 0x1c, 3, comp);
    GX_BITFIELD_SET(val, 0x1b, 1, update_enable);
    __peReg[0] = val;
}

void GXPeekZ(u16 x, u16 y, u32* z) {
    u32 addr = 0xc8000000;
    GX_BITFIELD_SET(addr, 0x14, 10, x);
    GX_BITFIELD_SET(addr, 0xa, 10, y);
    GX_BITFIELD_SET(addr, 8, 2, 1);
    *z = *(u32*)addr;
}

GXDrawSyncCallback GXSetDrawSyncCallback(GXDrawSyncCallback callback) {
    BOOL restore;
    GXDrawSyncCallback prevCb = TokenCB;
    restore = OSDisableInterrupts();
    TokenCB = callback;
    OSRestoreInterrupts(restore);
    return prevCb;
}

static void GXTokenInterruptHandler(__OSInterrupt interrupt, OSContext* context) {
    u16 token;
    OSContext exceptContext;
    u32 reg;

    token = GX_GET_PE_REG(7);

    if (TokenCB) {
        OSClearContext(&exceptContext);
        OSSetCurrentContext(&exceptContext);
        TokenCB(token);
        OSClearContext(&exceptContext);
        OSSetCurrentContext(context);
    }

    reg = GX_GET_PE_REG(5);
    GX_SET_REG(reg, 1, 29, 29);
    GX_SET_PE_REG(5, reg);
}

GXDrawDoneCallback GXSetDrawDoneCallback(GXDrawDoneCallback callback) {
    BOOL restore;
    GXDrawDoneCallback prevCb = DrawDoneCB;
    restore = OSDisableInterrupts();
    DrawDoneCB = callback;
    OSRestoreInterrupts(restore);
    return prevCb;
}

static void GXFinishInterruptHandler(__OSInterrupt interrupt, OSContext* context) {
    OSContext exceptContext;
    u32 reg;

    reg = GX_GET_PE_REG(5);
    GX_SET_REG(reg, 1, 28, 28);
    GX_SET_PE_REG(5, reg);

    DrawDone = GX_TRUE;

    if (DrawDoneCB) {
        OSClearContext(&exceptContext);
        OSSetCurrentContext(&exceptContext);
        DrawDoneCB();
        OSClearContext(&exceptContext);
        OSSetCurrentContext(context);
    }

    OSWakeupThread(&FinishQueue);
}

void __GXPEInit(void) {
    u32 val;
    __OSSetInterruptHandler(OS_INTR_PI_PE_TOKEN, GXTokenInterruptHandler);
    __OSSetInterruptHandler(OS_INTR_PI_PE_FINISH, GXFinishInterruptHandler);
    OSInitThreadQueue(&FinishQueue);
    __OSUnmaskInterrupts(OS_INTERRUPTMASK_PI_PE_TOKEN);
    __OSUnmaskInterrupts(OS_INTERRUPTMASK_PI_PE_FINISH);
    val = __peReg[5];
    GX_BITFIELD_SET(val, 0x1d, 1, 1);
    GX_BITFIELD_SET(val, 0x1c, 1, 1);
    GX_BITFIELD_SET(val, 0x1f, 1, 1);
    GX_BITFIELD_SET(val, 0x1e, 1, 1);
    __peReg[5] = val;
}
