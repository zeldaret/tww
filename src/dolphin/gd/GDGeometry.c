#include "dolphin/gx/GX.h"
#include "dolphin/gd/GDGeometry.h"
#include "dolphin/gd/GDBase.h"
#include "dolphin/os/OS.h"

void GDSetVtxDescv(GXVtxDescList* attrPtr) {
    u32 nnorms = 0;
    u32 ncols = 0;
    u32 ntexs = 0;
    u32 pnMtxIdx = GX_NONE;
    u32 txMtxIdxMask = 0;
    u32 posn = GX_DIRECT;
    u32 norm = GX_NONE;
    u32 col0 = GX_NONE;
    u32 col1 = GX_NONE;
    u32 tex0 = GX_NONE;
    u32 tex1 = GX_NONE;
    u32 tex2 = GX_NONE;
    u32 tex3 = GX_NONE;
    u32 tex4 = GX_NONE;
    u32 tex5 = GX_NONE;
    u32 tex6 = GX_NONE;
    u32 tex7 = GX_NONE;

    for (; attrPtr->attr != GX_VA_NULL; ++attrPtr) {
        ASSERTMSGLINE(91, attrPtr->attr >= GX_VA_PNMTXIDX && attrPtr->attr <= GX_VA_MAX_ATTR, "GDSetVtxDescv: invalid attribute");
        ASSERTMSGLINE(95, attrPtr->type >= GX_NONE && attrPtr->type <= GX_INDEX16, "GDSetVtxDescv: invalid type");

        ASSERTMSGLINE(101, attrPtr->attr >= GX_VA_PNMTXIDX && attrPtr->attr <= GX_VA_TEX7MTXIDX ? (attrPtr->type == 0 || attrPtr->type == 1) : TRUE, "GDSetVtxDescv: invalid type for given attribute");

        switch (attrPtr->attr) {
        case GX_VA_PNMTXIDX:
            pnMtxIdx = attrPtr->type;
            break;
        case GX_VA_TEX0MTXIDX:
            txMtxIdxMask = (txMtxIdxMask & ~0x1) | (attrPtr->type << 0);
            break;
        case GX_VA_TEX1MTXIDX:
            txMtxIdxMask = (txMtxIdxMask & ~0x2) | (attrPtr->type << 1);
            break;
        case GX_VA_TEX2MTXIDX:
            txMtxIdxMask = (txMtxIdxMask & ~0x4) | (attrPtr->type << 2);
            break;
        case GX_VA_TEX3MTXIDX:
            txMtxIdxMask = (txMtxIdxMask & ~0x8) | (attrPtr->type << 3);
            break;
        case GX_VA_TEX4MTXIDX:
            txMtxIdxMask = (txMtxIdxMask & ~0x10) | (attrPtr->type << 4);
            break;
        case GX_VA_TEX5MTXIDX:
            txMtxIdxMask = (txMtxIdxMask & ~0x20) | (attrPtr->type << 5);
            break;
        case GX_VA_TEX6MTXIDX:
            txMtxIdxMask = (txMtxIdxMask & ~0x40) | (attrPtr->type << 6);
            break;
        case GX_VA_TEX7MTXIDX:
            txMtxIdxMask = (txMtxIdxMask & ~0x80) | (attrPtr->type << 7);
            break;
        case GX_VA_POS:
            posn = attrPtr->type;
            break;
        case GX_VA_NRM:
            if (attrPtr->type != GX_NONE) {
                norm = attrPtr->type;
                nnorms = 1;
            }
            break;
        case GX_VA_NBT:
            if (attrPtr->type != GX_NONE) {
                norm = attrPtr->type;
                nnorms = 2;
            }
            break;
        case GX_VA_CLR0:
            col0 = attrPtr->type;
            ncols += (col0 != GX_NONE);
            break;
        case GX_VA_CLR1:
            col1 = attrPtr->type;
            ncols += (col1 != GX_NONE);
            break;
        case GX_VA_TEX0:
            tex0 = attrPtr->type;
            ntexs += (tex0 != GX_NONE);
            break;
        case GX_VA_TEX1:
            tex1 = attrPtr->type;
            ntexs += (tex1 != GX_NONE);
            break;
        case GX_VA_TEX2:
            tex2 = attrPtr->type;
            ntexs += (tex2 != GX_NONE);
            break;
        case GX_VA_TEX3:
            tex3 = attrPtr->type;
            ntexs += (tex3 != GX_NONE);
            break;
        case GX_VA_TEX4:
            tex4 = attrPtr->type;
            ntexs += (tex4 != GX_NONE);
            break;
        case GX_VA_TEX5:
            tex5 = attrPtr->type;
            ntexs += (tex5 != GX_NONE);
            break;
        case GX_VA_TEX6:
            tex6 = attrPtr->type;
            ntexs += (tex6 != GX_NONE);
            break;
        case GX_VA_TEX7:
            tex7 = attrPtr->type;
            ntexs += (tex7 != GX_NONE);
            break;
        }
    }

    GDWriteCPCmd(CP_REG_VCD_LO_ID, CP_REG_VCD_LO(pnMtxIdx, txMtxIdxMask, posn, norm, col0, col1));
    GDWriteCPCmd(CP_REG_VCD_HI_ID, CP_REG_VCD_HI(tex0, tex1, tex2, tex3, tex4, tex5, tex6, tex7));
    GDWriteXFCmd(XF_REG_INVERTEXSPEC_ID, XF_REG_INVTXSPEC(ncols, nnorms, ntexs));
}

void GDSetArray(GXAttr attr, void* base_ptr, u8 stride) {
    s32 cpAttr;
    if (attr == GX_VA_NBT) {
        cpAttr = GX_VA_TEX0MTXIDX;
    } else {
        cpAttr = attr - GX_VA_POS;
    }

    GDWriteCPCmd(cpAttr + CP_REG_ARRAYBASE_ID, OSCachedToPhysical(base_ptr));
    GDWriteCPCmd(cpAttr + CP_REG_ARRAYSTRIDE_ID, stride);
}

void GDSetArrayRaw(GXAttr attr, u32 base_ptr_raw, u8 stride) {
    s32 cpAttr;
    if (attr == GX_VA_NBT) {
        cpAttr = GX_VA_TEX0MTXIDX;
    } else {
        cpAttr = attr - GX_VA_POS;
    }

    GDWriteCPCmd(cpAttr + CP_REG_ARRAYBASE_ID, base_ptr_raw);
    GDWriteCPCmd(cpAttr + CP_REG_ARRAYSTRIDE_ID, stride);
}
