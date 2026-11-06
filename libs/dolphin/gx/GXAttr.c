#include "dolphin/gx/GXAttr.h"
#include "dolphin/gx/GX.h"

static inline void SETVCDATTR(GXAttr attr, GXAttrType type) {
    switch (attr) {
    case GX_VA_PNMTXIDX:
        GX_SET_REG(gx->vcdLo, type, GX_CP_VCD_LO_POSMTXIDX_ST, GX_CP_VCD_LO_POSMTXIDX_END);
        break;
    case GX_VA_TEX0MTXIDX:
        GX_SET_REG(gx->vcdLo, type, GX_CP_VCD_LO_TEX0MTXIDX_ST, GX_CP_VCD_LO_TEX0MTXIDX_END);
        break;
    case GX_VA_TEX1MTXIDX:
        GX_SET_REG(gx->vcdLo, type, GX_CP_VCD_LO_TEX1MTXIDX_ST, GX_CP_VCD_LO_TEX1MTXIDX_END);
        break;
    case GX_VA_TEX2MTXIDX:
        GX_SET_REG(gx->vcdLo, type, GX_CP_VCD_LO_TEX2MTXIDX_ST, GX_CP_VCD_LO_TEX2MTXIDX_END);
        break;
    case GX_VA_TEX3MTXIDX:
        GX_SET_REG(gx->vcdLo, type, GX_CP_VCD_LO_TEX3MTXIDX_ST, GX_CP_VCD_LO_TEX3MTXIDX_END);
        break;
    case GX_VA_TEX4MTXIDX:
        GX_SET_REG(gx->vcdLo, type, GX_CP_VCD_LO_TEX4MTXIDX_ST, GX_CP_VCD_LO_TEX4MTXIDX_END);
        break;
    case GX_VA_TEX5MTXIDX:
        GX_SET_REG(gx->vcdLo, type, GX_CP_VCD_LO_TEX5MTXIDX_ST, GX_CP_VCD_LO_TEX5MTXIDX_END);
        break;
    case GX_VA_TEX6MTXIDX:
        GX_SET_REG(gx->vcdLo, type, GX_CP_VCD_LO_TEX6MTXIDX_ST, GX_CP_VCD_LO_TEX6MTXIDX_END);
        break;
    case GX_VA_TEX7MTXIDX:
        GX_SET_REG(gx->vcdLo, type, GX_CP_VCD_LO_TEX7MTXIDX_ST, GX_CP_VCD_LO_TEX7MTXIDX_END);
        break;
    case GX_VA_POS:
        GX_SET_REG(gx->vcdLo, type, GX_CP_VCD_LO_POS_ST, GX_CP_VCD_LO_POS_END);
        break;
    case GX_VA_NRM:
        if (type != GX_NONE) {
            gx->hasNrms = TRUE;
            gx->hasBiNrms = FALSE;
            gx->nrmType = type;
        } else {
            gx->hasNrms = FALSE;
        }
        break;
    case GX_VA_NBT:
        if (type != GX_NONE) {
            gx->hasBiNrms = TRUE;
            gx->hasNrms = FALSE;
            gx->nrmType = type;
        } else {
            gx->hasBiNrms = FALSE;
        }
        break;
    case GX_VA_CLR0:
        GX_SET_REG(gx->vcdLo, type, GX_CP_VCD_LO_CLRDIF_ST, GX_CP_VCD_LO_CLRDIF_END);
        break;
    case GX_VA_CLR1:
        GX_SET_REG(gx->vcdLo, type, GX_CP_VCD_LO_CLRSPEC_ST, GX_CP_VCD_LO_CLRSPEC_END);
        break;
    case GX_VA_TEX0:
        GX_SET_REG(gx->vcdHi, type, GX_CP_VCD_HI_TEX0COORD_ST, GX_CP_VCD_HI_TEX0COORD_END);
        break;
    case GX_VA_TEX1:
        GX_SET_REG(gx->vcdHi, type, GX_CP_VCD_HI_TEX1COORD_ST, GX_CP_VCD_HI_TEX1COORD_END);
        break;
    case GX_VA_TEX2:
        GX_SET_REG(gx->vcdHi, type, GX_CP_VCD_HI_TEX2COORD_ST, GX_CP_VCD_HI_TEX2COORD_END);
        break;
    case GX_VA_TEX3:
        GX_SET_REG(gx->vcdHi, type, GX_CP_VCD_HI_TEX3COORD_ST, GX_CP_VCD_HI_TEX3COORD_END);
        break;
    case GX_VA_TEX4:
        GX_SET_REG(gx->vcdHi, type, GX_CP_VCD_HI_TEX4COORD_ST, GX_CP_VCD_HI_TEX4COORD_END);
        break;
    case GX_VA_TEX5:
        GX_SET_REG(gx->vcdHi, type, GX_CP_VCD_HI_TEX5COORD_ST, GX_CP_VCD_HI_TEX5COORD_END);
        break;
    case GX_VA_TEX6:
        GX_SET_REG(gx->vcdHi, type, GX_CP_VCD_HI_TEX6COORD_ST, GX_CP_VCD_HI_TEX6COORD_END);
        break;
    case GX_VA_TEX7:
        GX_SET_REG(gx->vcdHi, type, GX_CP_VCD_HI_TEX7COORD_ST, GX_CP_VCD_HI_TEX7COORD_END);
        break;
    }
}

static void __GXXfVtxSpecs(void) {
    u32 nCols = 0;
    u32 nNrm;
    u32 nTex;
    u32 reg;

    nCols = GET_REG_FIELD(gx->vcdLo, 2, 13) ? 1 : 0;
    nCols += GET_REG_FIELD(gx->vcdLo, 2, 15) ? 1 : 0;
    nNrm = gx->hasBiNrms ? 2 : gx->hasNrms ? 1 : 0;
    nTex = 0;
    nTex += GET_REG_FIELD(gx->vcdHi, 2, 0) ? 1 : 0;
    nTex += GET_REG_FIELD(gx->vcdHi, 2, 2) ? 1 : 0;
    nTex += GET_REG_FIELD(gx->vcdHi, 2, 4) ? 1 : 0;
    nTex += GET_REG_FIELD(gx->vcdHi, 2, 6) ? 1 : 0;
    nTex += GET_REG_FIELD(gx->vcdHi, 2, 8) ? 1 : 0;
    nTex += GET_REG_FIELD(gx->vcdHi, 2, 10) ? 1 : 0;
    nTex += GET_REG_FIELD(gx->vcdHi, 2, 12) ? 1 : 0;
    nTex += GET_REG_FIELD(gx->vcdHi, 2, 14) ? 1 : 0;
    reg = (nCols) | (nNrm << 2) | (nTex << 4);
    GX_WRITE_XF_REG(8, reg);
    gx->bpSentNot = GX_TRUE;
}

void GXSetVtxDesc(GXAttr name, GXAttrType type) {
    SETVCDATTR(name, type);

    // Set normal data type if enabled
    if (gx->hasNrms || gx->hasBiNrms) {
        GX_BITFIELD_SET(gx->vcdLo, 19, 2, gx->nrmType);
    } else {
        GX_BITFIELD_SET(gx->vcdLo, 19, 2, 0);
    }

    gx->dirtyState |= GX_DIRTY_VCD;
}

void GXSetVtxDescv(GXVtxDescList* list) {
    for (; list->attr != GX_VA_NULL; list++) {
        SETVCDATTR(list->attr, list->type);
    }

    // Set normal data type if enabled
    if (gx->hasNrms || gx->hasBiNrms) {
        GX_BITFIELD_SET(gx->vcdLo, 19, 2, gx->nrmType);
    } else {
        GX_BITFIELD_SET(gx->vcdLo, 19, 2, 0);
    }

    gx->dirtyState |= GX_DIRTY_VCD;
}

void __GXSetVCD(void) {
    GX_CP_LOAD_REG(GX_CP_REG_VCD_LO, gx->vcdLo);
    GX_CP_LOAD_REG(GX_CP_REG_VCD_HI, gx->vcdHi);

    __GXXfVtxSpecs();
}

void __GXCalculateVLim(void) {
    static u8 tbl1[] = {0, 4, 1, 2};
    static u8 tbl2[] = {0, 8, 1, 2};
    static u8 tbl3[] = {0, 12, 1, 2};

    u32 vlim;
    u32 vcdLoReg;
    u32 vcdHiReg;
    s32 compCnt;

    if (gx->vNum == 0) {
        return;
    }

    vcdLoReg = gx->vcdLo;
    vcdHiReg = gx->vcdHi;

    // GXCompCnt bit of normal parameters
    compCnt = gx->vatA[GX_VTXFMT0];
    compCnt = (compCnt & 0x200) >> 9;

    vlim = GX_GET_REG(vcdLoReg, GX_CP_VCD_LO_POSMTXIDX_ST, GX_CP_VCD_LO_POSMTXIDX_END);
    vlim += GX_GET_REG(vcdLoReg, GX_CP_VCD_LO_TEX0MTXIDX_ST, GX_CP_VCD_LO_TEX0MTXIDX_END);
    vlim += GX_GET_REG(vcdLoReg, GX_CP_VCD_LO_TEX1MTXIDX_ST, GX_CP_VCD_LO_TEX1MTXIDX_END);
    vlim += GX_GET_REG(vcdLoReg, GX_CP_VCD_LO_TEX2MTXIDX_ST, GX_CP_VCD_LO_TEX2MTXIDX_END);
    vlim += GX_GET_REG(vcdLoReg, GX_CP_VCD_LO_TEX3MTXIDX_ST, GX_CP_VCD_LO_TEX3MTXIDX_END);
    vlim += GX_GET_REG(vcdLoReg, GX_CP_VCD_LO_TEX4MTXIDX_ST, GX_CP_VCD_LO_TEX4MTXIDX_END);
    vlim += GX_GET_REG(vcdLoReg, GX_CP_VCD_LO_TEX5MTXIDX_ST, GX_CP_VCD_LO_TEX5MTXIDX_END);
    vlim += GX_GET_REG(vcdLoReg, GX_CP_VCD_LO_TEX6MTXIDX_ST, GX_CP_VCD_LO_TEX6MTXIDX_END);
    vlim += GX_GET_REG(vcdLoReg, GX_CP_VCD_LO_TEX7MTXIDX_ST, GX_CP_VCD_LO_TEX7MTXIDX_END);

    vlim += tbl3[GX_GET_REG(vcdLoReg, GX_CP_VCD_LO_POS_ST, GX_CP_VCD_LO_POS_END)];
    vlim += tbl3[GX_GET_REG(vcdLoReg, GX_CP_VCD_LO_NRM_ST, GX_CP_VCD_LO_NRM_END)] *
            (compCnt == GX_NRM_NBT ? 3 : 1);
    vlim += tbl1[GX_GET_REG(vcdLoReg, GX_CP_VCD_LO_CLRDIF_ST, GX_CP_VCD_LO_CLRDIF_END)];
    vlim += tbl1[GX_GET_REG(vcdLoReg, GX_CP_VCD_LO_CLRSPEC_ST, GX_CP_VCD_LO_CLRSPEC_END)];

    vlim += tbl2[GX_GET_REG(vcdHiReg, GX_CP_VCD_HI_TEX0COORD_ST, GX_CP_VCD_HI_TEX0COORD_END)];
    vlim += tbl2[GX_GET_REG(vcdHiReg, GX_CP_VCD_HI_TEX1COORD_ST, GX_CP_VCD_HI_TEX1COORD_END)];
    vlim += tbl2[GX_GET_REG(vcdHiReg, GX_CP_VCD_HI_TEX2COORD_ST, GX_CP_VCD_HI_TEX2COORD_END)];
    vlim += tbl2[GX_GET_REG(vcdHiReg, GX_CP_VCD_HI_TEX3COORD_ST, GX_CP_VCD_HI_TEX3COORD_END)];
    vlim += tbl2[GX_GET_REG(vcdHiReg, GX_CP_VCD_HI_TEX4COORD_ST, GX_CP_VCD_HI_TEX4COORD_END)];
    vlim += tbl2[GX_GET_REG(vcdHiReg, GX_CP_VCD_HI_TEX5COORD_ST, GX_CP_VCD_HI_TEX5COORD_END)];
    vlim += tbl2[GX_GET_REG(vcdHiReg, GX_CP_VCD_HI_TEX6COORD_ST, GX_CP_VCD_HI_TEX6COORD_END)];
    vlim += tbl2[GX_GET_REG(vcdHiReg, GX_CP_VCD_HI_TEX7COORD_ST, GX_CP_VCD_HI_TEX7COORD_END)];

    gx->vLim = vlim;
}

void GXGetVtxDesc(GXAttr attr, GXAttrType* type) {
    u32 cpType;

    switch (attr) {
    case GX_VA_PNMTXIDX:   cpType = GET_REG_FIELD(gx->vcdLo, 1, 0); break;
    case GX_VA_TEX0MTXIDX: cpType = GET_REG_FIELD(gx->vcdLo, 1, 1); break;
    case GX_VA_TEX1MTXIDX: cpType = GET_REG_FIELD(gx->vcdLo, 1, 2); break;
    case GX_VA_TEX2MTXIDX: cpType = GET_REG_FIELD(gx->vcdLo, 1, 3); break;
    case GX_VA_TEX3MTXIDX: cpType = GET_REG_FIELD(gx->vcdLo, 1, 4); break;
    case GX_VA_TEX4MTXIDX: cpType = GET_REG_FIELD(gx->vcdLo, 1, 5); break;
    case GX_VA_TEX5MTXIDX: cpType = GET_REG_FIELD(gx->vcdLo, 1, 6); break;
    case GX_VA_TEX6MTXIDX: cpType = GET_REG_FIELD(gx->vcdLo, 1, 7); break;
    case GX_VA_TEX7MTXIDX: cpType = GET_REG_FIELD(gx->vcdLo, 1, 8); break;
    case GX_VA_POS:        cpType = GET_REG_FIELD(gx->vcdLo, 2, 9); break;
    case GX_VA_NRM:        cpType = gx->hasNrms ? GET_REG_FIELD(gx->vcdLo, 2, 11) : 0; break;
    case GX_VA_NBT:        cpType = gx->hasBiNrms ? GET_REG_FIELD(gx->vcdLo, 2, 11) : 0; break;
    case GX_VA_CLR0:       cpType = GET_REG_FIELD(gx->vcdLo, 2, 13); break;
    case GX_VA_CLR1:       cpType = GET_REG_FIELD(gx->vcdLo, 2, 15); break;
    case GX_VA_TEX0:       cpType = GET_REG_FIELD(gx->vcdHi, 2, 0);  break;
    case GX_VA_TEX1:       cpType = GET_REG_FIELD(gx->vcdHi, 2, 2);  break;
    case GX_VA_TEX2:       cpType = GET_REG_FIELD(gx->vcdHi, 2, 4);  break;
    case GX_VA_TEX3:       cpType = GET_REG_FIELD(gx->vcdHi, 2, 6);  break;
    case GX_VA_TEX4:       cpType = GET_REG_FIELD(gx->vcdHi, 2, 8);  break;
    case GX_VA_TEX5:       cpType = GET_REG_FIELD(gx->vcdHi, 2, 10); break;
    case GX_VA_TEX6:       cpType = GET_REG_FIELD(gx->vcdHi, 2, 12); break;
    case GX_VA_TEX7:       cpType = GET_REG_FIELD(gx->vcdHi, 2, 14); break;
    default: cpType = 0; break;
    }
    *type = cpType;
}

void GXGetVtxDescv(GXVtxDescList* vcd) {
    GXAttr attr;

    for (attr = 0; attr < GX_VA_MAX_ATTR; attr++) {
        vcd[attr].attr = attr;
        GXGetVtxDesc(attr, &vcd[attr].type);
    }
    vcd[attr].attr = 0xFF;
}

void GXClearVtxDesc(void) {
    gx->vcdLo = 0;
    GX_BITFIELD_SET(gx->vcdLo, 0x15, 2, GX_DIRECT);
    gx->vcdHi = 0;
    gx->hasNrms = FALSE;
    gx->hasBiNrms = FALSE;
    gx->dirtyState |= GX_DIRTY_VCD;
}

/* ############################################################################################## */

static inline void SETVAT(u32* vatA, u32* vatB, u32* vatC, GXAttr attr, GXCompCnt compCnt,
                          GXCompType compType, u8 shift) {
    switch (attr) {
    case GX_VA_POS:
        GX_SET_REG(*vatA, compCnt, GX_CP_VAT_GRP0_POS_CNT_ST, GX_CP_VAT_GRP0_POS_CNT_END);
        GX_SET_REG(*vatA, compType, GX_CP_VAT_GRP0_POS_TYPE_ST, GX_CP_VAT_GRP0_POS_TYPE_END);
        GX_SET_REG(*vatA, shift, GX_CP_VAT_GRP0_POS_SHIFT_ST, GX_CP_VAT_GRP0_POS_SHIFT_END);
        break;
    case GX_VA_NRM:
    case GX_VA_NBT:
        GX_SET_REG(*vatA, compType, GX_CP_VAT_GRP0_NRM_TYPE_ST, GX_CP_VAT_GRP0_NRM_TYPE_END);
        if (compCnt == GX_NRM_NBT3) {
            // Probably because the compCnt can only be one bit?
            GX_SET_REG(*vatA, GX_NRM_NBT, GX_CP_VAT_GRP0_NRM_CNT_ST, GX_CP_VAT_GRP0_NRM_CNT_END);
            GX_SET_REG(*vatA, TRUE, GX_CP_VAT_GRP0_NRMIDX3_ST, GX_CP_VAT_GRP0_NRMIDX3_END);
        } else {
            GX_SET_REG(*vatA, compCnt, GX_CP_VAT_GRP0_NRM_CNT_ST, GX_CP_VAT_GRP0_NRM_CNT_END);
            GX_SET_REG(*vatA, FALSE, GX_CP_VAT_GRP0_NRMIDX3_ST, GX_CP_VAT_GRP0_NRMIDX3_END);
        }
        break;
    case GX_VA_CLR0:
        GX_SET_REG(*vatA, compCnt, GX_CP_VAT_GRP0_CLRDIFF_CNT_ST, GX_CP_VAT_GRP0_CLRDIFF_CNT_END);
        GX_SET_REG(*vatA, compType, GX_CP_VAT_GRP0_CLRDIFF_TYPE_ST, GX_CP_VAT_GRP0_CLRDIFF_TYPE_END);
        break;
    case GX_VA_CLR1:
        GX_SET_REG(*vatA, compCnt, GX_CP_VAT_GRP0_CLRSPEC_CNT_ST, GX_CP_VAT_GRP0_CLRSPEC_CNT_END);
        GX_SET_REG(*vatA, compType, GX_CP_VAT_GRP0_CLRSPEC_TYPE_ST, GX_CP_VAT_GRP0_CLRSPEC_TYPE_END);
        break;
    case GX_VA_TEX0:
        GX_SET_REG(*vatA, compCnt, GX_CP_VAT_GRP0_TXC0_CNT_ST, GX_CP_VAT_GRP0_TXC0_CNT_END);
        GX_SET_REG(*vatA, compType, GX_CP_VAT_GRP0_TXC0_TYPE_ST, GX_CP_VAT_GRP0_TXC0_TYPE_END);
        GX_SET_REG(*vatA, shift, GX_CP_VAT_GRP0_TXC0_SHIFT_ST, GX_CP_VAT_GRP0_TXC0_SHIFT_END);
        break;
    case GX_VA_TEX1:
        GX_SET_REG(*vatB, compCnt, GX_CP_VAT_GRP1_TXC1_CNT_ST, GX_CP_VAT_GRP1_TXC1_CNT_END);
        GX_SET_REG(*vatB, compType, GX_CP_VAT_GRP1_TXC1_TYPE_ST, GX_CP_VAT_GRP1_TXC1_TYPE_END);
        GX_SET_REG(*vatB, shift, GX_CP_VAT_GRP1_TXC1_SHIFT_ST, GX_CP_VAT_GRP1_TXC1_SHIFT_END);
        break;
    case GX_VA_TEX2:
        GX_SET_REG(*vatB, compCnt, GX_CP_VAT_GRP1_TXC2_CNT_ST, GX_CP_VAT_GRP1_TXC2_CNT_END);
        GX_SET_REG(*vatB, compType, GX_CP_VAT_GRP1_TXC2_TYPE_ST, GX_CP_VAT_GRP1_TXC2_TYPE_END);
        GX_SET_REG(*vatB, shift, GX_CP_VAT_GRP1_TXC2_SHIFT_ST, GX_CP_VAT_GRP1_TXC2_SHIFT_END);
        break;
    case GX_VA_TEX3:
        GX_SET_REG(*vatB, compCnt, GX_CP_VAT_GRP1_TXC3_CNT_ST, GX_CP_VAT_GRP1_TXC3_CNT_END);
        GX_SET_REG(*vatB, compType, GX_CP_VAT_GRP1_TXC3_TYPE_ST, GX_CP_VAT_GRP1_TXC3_TYPE_END);
        GX_SET_REG(*vatB, shift, GX_CP_VAT_GRP1_TXC3_SHIFT_ST, GX_CP_VAT_GRP1_TXC3_SHIFT_END);
        break;
    case GX_VA_TEX4:
        GX_SET_REG(*vatB, compCnt, GX_CP_VAT_GRP1_TXC4_CNT_ST, GX_CP_VAT_GRP1_TXC4_CNT_END);
        GX_SET_REG(*vatB, compType, GX_CP_VAT_GRP1_TXC4_TYPE_ST, GX_CP_VAT_GRP1_TXC4_TYPE_END);
        GX_SET_REG(*vatC, shift, GX_CP_VAT_GRP2_TXC4_SHIFT_ST, GX_CP_VAT_GRP2_TXC4_SHIFT_END);
        break;
    case GX_VA_TEX5:
        GX_SET_REG(*vatC, compCnt, GX_CP_VAT_GRP2_TXC5_CNT_ST, GX_CP_VAT_GRP2_TXC5_CNT_END);
        GX_SET_REG(*vatC, compType, GX_CP_VAT_GRP2_TXC5_TYPE_ST, GX_CP_VAT_GRP2_TXC5_TYPE_END);
        GX_SET_REG(*vatC, shift, GX_CP_VAT_GRP2_TXC5_SHIFT_ST, GX_CP_VAT_GRP2_TXC5_SHIFT_END);
        break;
    case GX_VA_TEX6:
        GX_SET_REG(*vatC, compCnt, GX_CP_VAT_GRP2_TXC6_CNT_ST, GX_CP_VAT_GRP2_TXC6_CNT_END);
        GX_SET_REG(*vatC, compType, GX_CP_VAT_GRP2_TXC6_TYPE_ST, GX_CP_VAT_GRP2_TXC6_TYPE_END);
        GX_SET_REG(*vatC, shift, GX_CP_VAT_GRP2_TXC6_SHIFT_ST, GX_CP_VAT_GRP2_TXC6_SHIFT_END);
        break;
    case GX_VA_TEX7:
        GX_SET_REG(*vatC, compCnt, GX_CP_VAT_GRP2_TXC7_CNT_ST, GX_CP_VAT_GRP2_TXC7_CNT_END);
        GX_SET_REG(*vatC, compType, GX_CP_VAT_GRP2_TXC7_TYPE_ST, GX_CP_VAT_GRP2_TXC7_TYPE_END);
        GX_SET_REG(*vatC, shift, GX_CP_VAT_GRP2_TXC7_SHIFT_ST, GX_CP_VAT_GRP2_TXC7_SHIFT_END);
        break;
    }
}

void GXSetVtxAttrFmt(GXVtxFmt format, GXAttr attr, GXCompCnt count, GXCompType type, u8 frac) {
    u32* vA = (u32*)&gx->vatA[format];
    u32* vB = (u32*)&gx->vatB[format];
    u32* vC = &gx->vatC[format];

    SETVAT(vA, vB, vC, attr, count, type, frac);

    gx->dirtyState |= GX_DIRTY_VAT;
    gx->dirtyVAT |= (u8)(1 << (u8)format);
}

void GXSetVtxAttrFmtv(GXVtxFmt format, GXVtxAttrFmtList* list) {
    u32* vatA;
    u32* vatB;
    u32* vatC;

    vatA = (u32*)&gx->vatA[format];
    vatB = (u32*)&gx->vatB[format];
    vatC = &gx->vatC[format];

    for (; list->attr != GX_VA_NULL; list++) {
        SETVAT(vatA, vatB, vatC, list->attr, list->cnt, list->type, list->frac);
    }

    gx->dirtyState |= GX_DIRTY_VAT;
    gx->dirtyVAT |= (u8)(1 << (u8)format);
}

void __GXSetVAT(void) {
    u8 i;

    for (i = 0; i < 8; i++) {
        if (gx->dirtyVAT & (1 << (u8)i)) {
            GX_WRITE_SOME_REG4(8, i | 0x70, gx->vatA[i], i - 12);
            GX_WRITE_SOME_REG4(8, i | 0x80, gx->vatB[i], i - 12);
            GX_WRITE_SOME_REG4(8, i | 0x90, gx->vatC[i], i - 12);
        }
    }
    gx->dirtyVAT = 0;
}

static inline u8 GetFracForNrm(GXCompType type) {
    u8 frac;

    switch (type) {
    case GX_S8:
        frac = 6;
        break;
    case GX_S16:
        frac = 14;
        break;
    default:
    case GX_U16:
        frac = 0;
        break;
    }

    return frac;
}

void GXGetVtxAttrFmt(GXVtxFmt fmt, int attr, GXCompCnt* cnt, GXCompType* type, u8* frac) {
    u32 *va;
    u32 *vb;
    u32 *vc;

    va = &gx->vatA[fmt];
    vb = &gx->vatB[fmt];
    vc = &gx->vatC[fmt];
    switch (attr) {
    case GX_VA_POS:
        *cnt  = GET_REG_FIELD(*va, 1, 0);
        *type = GET_REG_FIELD(*va, 3, 1);
        *frac = GET_REG_FIELD(*va, 5, 4);
        return;
    case GX_VA_NRM:
    case GX_VA_NBT:
        *cnt = GET_REG_FIELD(*va, 1, 9);
        if (*cnt == GX_TEX_ST && (u8)(*va >> 0x1F) != 0) {
            *cnt = GX_NRM_NBT3;
        }
        *type = GET_REG_FIELD(*va, 3, 10);
        *frac = GetFracForNrm(*type);
        return;
    case GX_VA_CLR0:
        *cnt  = GET_REG_FIELD(*va, 1, 13);
        *type = GET_REG_FIELD(*va, 3, 14);
        *frac = 0;
        return;
    case GX_VA_CLR1:
        *cnt  = GET_REG_FIELD(*va, 1, 17);
        *type = GET_REG_FIELD(*va, 3, 18);
        *frac = 0;
        return;
    case GX_VA_TEX0:
        *cnt  = GET_REG_FIELD(*va, 1, 21);
        *type = GET_REG_FIELD(*va, 3, 22);
        *frac = (u8)(*va >> 0x19U) & 0x1F;
        return;
    case GX_VA_TEX1:
        *cnt  = GET_REG_FIELD(*vb, 1, 0);
        *type = GET_REG_FIELD(*vb, 3, 1);
        *frac = (u8)(*vb >> 4U) & 0x1F;
        return;
    case GX_VA_TEX2:
        *cnt  = GET_REG_FIELD(*vb, 1, 9);
        *type = GET_REG_FIELD(*vb, 3, 10);
        *frac = (u8)(*vb >> 0xDU) & 0x1F;
        return;
    case GX_VA_TEX3:
        *cnt  = GET_REG_FIELD(*vb, 1, 18);
        *type = GET_REG_FIELD(*vb, 3, 19);
        *frac = (u8)(*vb >> 0x16U) & 0x1F;
        return;
    case GX_VA_TEX4:
        *cnt  = GET_REG_FIELD(*vb, 1, 27);
        *type = GET_REG_FIELD(*vb, 3, 28);
        *frac = GET_REG_FIELD(*vc, 5, 0);
        return;
    case GX_VA_TEX5:
        *cnt = GET_REG_FIELD(*vc, 1, 5);
        *type = GET_REG_FIELD(*vc, 3, 6);
        *frac = (u8)(*vc >> 9U) & 0x1F;
        return;
    case GX_VA_TEX6:
        *cnt = GET_REG_FIELD(*vc, 1, 14);
        *type = GET_REG_FIELD(*vc, 3, 15);
        *frac = (u8)(*vc >> 0x12) & 0x1F;
        return;
    case GX_VA_TEX7:
        *cnt  = GET_REG_FIELD(*vc, 1, 23);
        *type = GET_REG_FIELD(*vc, 3, 24);
        *frac = (int)(*vc >> 0x1BU);
        return;
    default:
        *cnt = GX_TEX_ST;
        *type = GX_RGB565;
        *frac = 0;
        return;
    }
}

void GXGetVtxAttrFmtv(GXVtxFmt fmt, GXVtxAttrFmtList* vat) {
    GXAttr attr;

    for (attr = GX_VA_POS; attr <= GX_VA_TEX7; attr++) {
        vat->attr = attr;
        GXGetVtxAttrFmt(fmt, attr, &vat->cnt, &vat->type, &vat->frac);
        vat++;
    }
    vat->attr = GX_VA_NULL;
}

void GXSetArray(GXAttr attr, void* base_ptr, u8 stride) {
    GXAttr cpAttr;
    u32 phyAddr;

    if (attr == GX_VA_NBT) {
        attr = GX_VA_NRM;
    }
    cpAttr = attr - GX_VA_POS;
    phyAddr = (u32)base_ptr & 0x3FFFFFFF;
    GX_WRITE_SOME_REG2(8, cpAttr | GX_BP_REG_SETMODE0_TEX4, phyAddr, cpAttr - 12);
    GX_WRITE_SOME_REG3(8, cpAttr | GX_BP_REG_SETIMAGE2_TEX4, stride, cpAttr - 12);
}

void GXInvalidateVtxCache(void) {
    GXFIFO.u8 = GX_FIFO_CMD_INVAL_VTX;
}

void GXSetTexCoordGen2(GXTexCoordID dst_coord, GXTexGenType func, GXTexGenSrc src_param, u32 mtx, GXBool normalize, u32 pt_texmtx) {
    u32 reg = 0;
    u32 row;
    u32 bumprow;  // unused
    u32 form;
    GXAttr mtxIdAttr;

    form = 0;
    row = 5;
    switch (src_param) {
    case GX_TG_POS:     row = 0; form = 1; break;
    case GX_TG_NRM:     row = 1; form = 1; break;
    case GX_TG_BINRM:   row = 3; form = 1; break;
    case GX_TG_TANGENT: row = 4; form = 1; break;
    case GX_TG_COLOR0:  row = 2; break;
    case GX_TG_COLOR1:  row = 2; break;
    case GX_TG_TEX0:    row = 5; break;
    case GX_TG_TEX1:    row = 6; break;
    case GX_TG_TEX2:    row = 7; break;
    case GX_TG_TEX3:    row = 8; break;
    case GX_TG_TEX4:    row = 9; break;
    case GX_TG_TEX5:    row = 10; break;
    case GX_TG_TEX6:    row = 11; break;
    case GX_TG_TEX7:    row = 12; break;
    case GX_TG_TEXCOORD0: bumprow; break;
    case GX_TG_TEXCOORD1: bumprow; break;
    case GX_TG_TEXCOORD2: bumprow; break;
    case GX_TG_TEXCOORD3: bumprow; break;
    case GX_TG_TEXCOORD4: bumprow; break;
    case GX_TG_TEXCOORD5: bumprow; break;
    case GX_TG_TEXCOORD6: bumprow; break;
    default:
        break;
    }
    switch (func)
    {
    case GX_TG_MTX2x4:
        SET_REG_FIELD(reg, 1, 1, 0);
        SET_REG_FIELD(reg, 1, 2, form);
        SET_REG_FIELD(reg, 3, 4, 0);
        SET_REG_FIELD(reg, 5, 7, row);
        break;
    case GX_TG_MTX3x4:
        SET_REG_FIELD(reg, 1, 1, 1);
        SET_REG_FIELD(reg, 1, 2, form);
        SET_REG_FIELD(reg, 3, 4, 0);
        SET_REG_FIELD(reg, 5, 7, row);
        break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        SET_REG_FIELD(reg, 1, 1, 0);
        SET_REG_FIELD(reg, 1, 2, form);
        SET_REG_FIELD(reg, 3, 4, 1);
        SET_REG_FIELD(reg, 5, 7, row);
        SET_REG_FIELD(reg, 3, 12, src_param - 12);
        SET_REG_FIELD(reg, 3, 15, func - 2);
        break;
    case GX_TG_SRTG:
        SET_REG_FIELD(reg, 1, 1, 0);
        SET_REG_FIELD(reg, 1, 2, form);
        if (src_param == GX_TG_COLOR0) {
            SET_REG_FIELD(reg, 3, 4, 2);
        } else {
            SET_REG_FIELD(reg, 3, 4, 3);
        }
        SET_REG_FIELD(reg, 5, 7, 2);
        break;
    default:
        break;
    }
    GX_WRITE_XF_REG(dst_coord + 0x40, reg);
    reg = 0;
    SET_REG_FIELD(reg, 6, 0, pt_texmtx - 64);
    SET_REG_FIELD(reg, 1, 8, normalize);
    GX_WRITE_XF_REG(dst_coord + 0x50, reg);
    switch (dst_coord) {
    case GX_TEXCOORD0: SET_REG_FIELD(gx->matIdxA, 6, 6, mtx);  break;
    case GX_TEXCOORD1: SET_REG_FIELD(gx->matIdxA, 6, 12, mtx); break;
    case GX_TEXCOORD2: SET_REG_FIELD(gx->matIdxA, 6, 18, mtx); break;
    case GX_TEXCOORD3: SET_REG_FIELD(gx->matIdxA, 6, 24, mtx); break;
    case GX_TEXCOORD4: SET_REG_FIELD(gx->matIdxB, 6, 0, mtx);  break;
    case GX_TEXCOORD5: SET_REG_FIELD(gx->matIdxB, 6, 6, mtx);  break;
    case GX_TEXCOORD6: SET_REG_FIELD(gx->matIdxB, 6, 12, mtx); break;
    default:           SET_REG_FIELD(gx->matIdxB, 6, 18, mtx); break;
    }
    mtxIdAttr = dst_coord + 1;
    __GXSetMatrixIndex(mtxIdAttr);
}

void GXSetNumTexGens(u8 nTexGens) {
    SET_REG_FIELD(gx->genMode, 4, 0, nTexGens);
    GX_WRITE_XF_REG(0x3F, nTexGens);
    gx->dirtyState |= GX_DIRTY_GEN_MODE;
}
