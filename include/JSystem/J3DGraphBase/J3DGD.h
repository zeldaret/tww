#ifndef J3DGD_H
#define J3DGD_H

#include "dolphin/gx/GX.h"
#include "dolphin/gd/GDBase.h"

inline void J3DGDWrite_u8(u8 param) {
    __GDWrite(param);
}

inline void J3DGDWrite_u16(u16 param) {
    __GDWrite((param >> 8) & 0xff);
    __GDWrite(param & 0xff);
}

inline void J3DGDWrite_u32(u32 param) {
    __GDWrite((param >> 24) & 0xff);
    __GDWrite((param >> 16) & 0xff);
    __GDWrite((param >> 8) & 0xff);
    __GDWrite(param & 0xff);
}

inline void J3DGDWrite_f32(f32 param) {
    u32 tmp = *(u32*)&param;
    J3DGDWrite_u32(tmp);
}

inline void J3DGDWriteBPCmd(u32 param_1) {
    J3DGDWrite_u8(0x61);
    J3DGDWrite_u32(param_1);
}

inline void J3DGDWriteXFCmd(u16 cmd, u32 param) {
    J3DGDWrite_u8(0x10);
    J3DGDWrite_u16(0);
    J3DGDWrite_u16(cmd);
    J3DGDWrite_u32(param);
}

inline void J3DGDWriteXFCmdHdr(u16 cmd, u8 len) {
    J3DGDWrite_u8(0x10);
    J3DGDWrite_u16(len - 1);
    J3DGDWrite_u16(cmd);
}

void J3DGDSetGenMode(u8 texGenNum, u8 colorChanNum, u8 tevStageNum, u8 IndTexStageNum, _GXCullMode cullMode);
void J3DGDSetGenMode_3Param(u8 texGenNum, u8 tevStageNum, u8 indTexStageNum);
void J3DGDSetIndTexStageNum(u32);
void J3DGDSetLightAttn(_GXLightID, f32, f32, f32, f32, f32, f32);
void J3DGDSetLightColor(GXLightID, GXColor);
void J3DGDSetLightPos(GXLightID, f32, f32, f32);
void J3DGDSetLightDir(GXLightID, f32, f32, f32);
void J3DGDSetVtxAttrFmtv(GXVtxFmt, GXVtxAttrFmtList*, bool);
void J3DGDSetTexCoordGen(GXTexGenType, GXTexGenSrc);
void J3DGDSetTexCoordScale2(GXTexCoordID, u16, u8, u8, u16, u8, u8);
void J3DGDSetTexLookupMode(GXTexMapID, GXTexWrapMode, GXTexWrapMode, GXTexFilter, GXTexFilter, f32, f32, f32, u8, u8, GXAnisotropy);
void J3DGDSetTexImgAttr(GXTexMapID, u16, u16, GXTexFmt);
void J3DGDSetTexImgPtr(GXTexMapID, void*);
void J3DGDSetTexImgPtrRaw(GXTexMapID, u32);
void J3DGDSetTexTlut(GXTexMapID, u32, GXTlutFmt);
void J3DGDLoadTlut(void*, u32, GXTlutSize);
void J3DGDSetIndTexMtx(GXIndTexMtxID, Mtx23, s8);
void J3DGDSetIndTexCoordScale(GXIndTexStageID, GXIndTexScale, GXIndTexScale, GXIndTexScale, GXIndTexScale);
void J3DGDSetIndTexOrder(u32, GXTexCoordID, GXTexMapID, GXTexCoordID, GXTexMapID, GXTexCoordID, GXTexMapID, GXTexCoordID, GXTexMapID);
void J3DGDSetTevOrder(GXTevStageID, GXTexCoordID, GXTexMapID, GXChannelID, GXTexCoordID, GXTexMapID, GXChannelID);
void J3DGDSetTevKColor(GXTevKColorID, GXColor);
void J3DGDSetTevColorS10(GXTevRegID, GXColorS10);
void J3DGDSetFog(GXFogType, f32, f32, f32, f32, GXColor);
void J3DGDSetFogRangeAdj(u8, u16, GXFogAdjTable*);

static inline void J3DFifoLoadIndx(u8 cmd, u16 indx, u16 addr) {
    GFX_FIFO(u8) = cmd;
    GFX_FIFO(u16) = indx;
    GFX_FIFO(u16) = addr;
}

inline void J3DGDSetNumChans(u8 numChans) {
    J3DGDWriteXFCmd(0x1009, numChans);
}

inline void J3DGDSetNumTexGens(u8 numTexGens) {
    J3DGDWriteXFCmd(0x103f, numTexGens);
}

inline void J3DGDSetAlphaCompare(GXCompare param_0, u8 param_1, GXAlphaOp param_2, GXCompare param_3, u8 param_4) {
    J3DGDWriteBPCmd(param_2 << 22 | param_3 << 19 | param_0 << 16 | param_4 << 8 | param_1 | 0xF3000000);
}

inline void J3DGDSetBlendMode(GXBlendMode param_0, GXBlendFactor param_1, GXBlendFactor param_2, GXLogicOp param_3) {
    J3DGDWriteBPCmd(0xFE001FE3);
    bool r30 = true;
    if (param_0 != GX_BM_BLEND && param_0 != GX_BM_SUBTRACT) {
        r30 = false;
    }
    J3DGDWriteBPCmd(param_3 << 12 | (param_0 == GX_BM_LOGIC) << 11 | param_1 << 8 | param_2 << 5 | (param_0 == GX_BM_BLEND) << 1 | r30 | 0x41000000);
}

inline void J3DGDSetZMode(u8 param_0, GXCompare param_1, u8 param_2) {
    J3DGDWriteBPCmd(param_2 << 4 | param_0 | param_1 << 1 | 0x40000000);
}

inline void J3DGDSetZCompLoc(u32 param_0) {
    J3DGDWriteBPCmd(0xFE000040);
    J3DGDWriteBPCmd(param_0 << 6 | 0x43000000);
}

inline void J3DGDSetTevKonstantSel_SwapModeTable(GXTevStageID stage, GXTevKColorSel colorSel1, GXTevKAlphaSel alphaSel1, GXTevKColorSel colorSel2, GXTevKAlphaSel alphaSel2, GXTevColorChan chan1, GXTevColorChan chan2) {
    J3DGDWriteBPCmd((stage / 2 + 0xf6) << 24 | (chan1 | chan2 << 2 | colorSel1 << 4 | alphaSel1 << 9 | colorSel2 << 14 | alphaSel2 << 19) & 0x00FFFFFF);
}

#endif /* J3DGD_H */
