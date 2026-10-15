/**
 * GXGeometry.c
 * Description:
 */

#include "dolphin/gx/GXGeometry.h"
#include "dolphin/gx/GX.h"

void __GXSetDirtyState(void) {
    u32 dirtyFlags = gx->dirtyState;

    if (dirtyFlags & GX_DIRTY_SU_TEX) {
        __GXSetSUTexRegs();
    }

    if (dirtyFlags & GX_DIRTY_BP_MASK) {
        __GXUpdateBPMask();
    }

    if (dirtyFlags & GX_DIRTY_GEN_MODE) {
        __GXSetGenMode();
    }

    if (dirtyFlags & GX_DIRTY_VCD) {
        __GXSetVCD();
    }

    if (dirtyFlags & GX_DIRTY_VAT) {
        __GXSetVAT();
    }

    if (dirtyFlags & GX_DIRTY_VLIM) {
        __GXCalculateVLim();
    }

    gx->dirtyState = 0;
}

void GXBegin(GXPrimitive type, GXVtxFmt fmt, u16 vert_num) {
    GXData* data = gx;
    u32 dirtyFlags = data->dirtyState;

    if (data->dirtyState != 0) {
        if (dirtyFlags & GX_DIRTY_SU_TEX) {
            __GXSetSUTexRegs();
        }

        if (dirtyFlags & GX_DIRTY_BP_MASK) {
            __GXUpdateBPMask();
        }

        if (dirtyFlags & GX_DIRTY_GEN_MODE) {
            __GXSetGenMode();
        }

        if (dirtyFlags & GX_DIRTY_VCD) {
            __GXSetVCD();
        }

        if (dirtyFlags & GX_DIRTY_VAT) {
            __GXSetVAT();
        }

        if (dirtyFlags & GX_DIRTY_VLIM) {
            __GXCalculateVLim();
        }

        gx->dirtyState = 0;
    }

    if (*(u32*)gx == 0) {
        __GXSendFlushPrim();
    }

    GXFIFO.u8 = fmt | type;
    GXFIFO.u16 = vert_num;
}

void __GXSendFlushPrim(void) {
    u32 i;
    u32 sz = gx->vNum * gx->vLim;

    GXFIFO.u8 = 0x98;
    GXFIFO.u16 = gx->vNum;

    for (i = 0; i < sz; i += 4) {
        GXFIFO.s32 = 0;
    }

    gx->bpSentNot = 1;
}

void GXSetLineWidth(u8 width, GXTexOffset offsets) {
    GXData* data = gx;

    GX_BITFIELD_SET(data->lpSize, 24, 8, width);
    GX_BITFIELD_SET(data->lpSize, 13, 3, offsets);
    GXFIFO.u8 = 0x61;
    GXFIFO.u32 = data->lpSize;
    data->bpSentNot = 0;
}

void GXSetPointSize(u8 size, GXTexOffset offsets) {
    GXData* data = gx;

    GX_BITFIELD_SET(data->lpSize, 16, 8, size);
    GX_BITFIELD_SET(data->lpSize, 10, 3, offsets);
    GXFIFO.u8 = 0x61;
    GXFIFO.u32 = data->lpSize;
    data->bpSentNot = 0;
}

void GXEnableTexOffsets(GXTexCoordID coord, GXBool line, GXBool point) {
    GX_BITFIELD_SET(gx->suTs0[coord], 13, 1, line);
    GX_BITFIELD_SET(gx->suTs0[coord], 12, 1, point);
    GXFIFO.u8 = 0x61;
    GXFIFO.u32 = gx->suTs0[coord];
    gx->bpSentNot = 0;
}

void GXSetCullMode(GXCullMode mode) {
    GXData* data;
    GXCullMode hwMode;

    switch (mode) {
    case GX_CULL_FRONT:
        hwMode = GX_CULL_BACK;
        break;
    case GX_CULL_BACK:
        hwMode = GX_CULL_FRONT;
        break;
    default:
        hwMode = mode;
        break;
    }

    data = gx;
    GX_BITFIELD_SET(data->genMode, 16, 2, hwMode);
    data->dirtyState |= GX_DIRTY_GEN_MODE;
}

void GXSetCoPlanar(GXBool enable) {
    GXData* data = gx;

    GX_BITFIELD_SET(data->genMode, 12, 1, enable);
    GXFIFO.u8 = 0x61;
    GXFIFO.u32 = 0xFE080000;
    GXFIFO.u8 = 0x61;
    GXFIFO.u32 = data->genMode;
}

void __GXSetGenMode(void) {
    GXFIFO.u8 = 0x61;
    GXFIFO.u32 = gx->genMode;
    gx->bpSentNot = 0;
}
