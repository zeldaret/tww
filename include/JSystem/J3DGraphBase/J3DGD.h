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
void J3DGDSetTexCoordGen(GXTexGenType, GXTexGenSrc);

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

#endif /* J3DGD_H */
