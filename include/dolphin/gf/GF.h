#ifndef GF_H
#define GF_H

#include "dolphin/gd/GDBase.h"
#include "dolphin/gf/GFGeometry.h" // IWYU pragma: export
#include "dolphin/gf/GFLight.h" // IWYU pragma: export
#include "dolphin/gf/GFPixel.h" // IWYU pragma: export
#include "dolphin/gf/GFTev.h" // IWYU pragma: export
#include "dolphin/gf/GFTransform.h" // IWYU pragma: export

inline void GFWrite_u8(u8 data) {
    GXCmd1u8(data);
}

inline void GFWrite_u16(u16 data) {
    GXCmd1u16(data);
}

inline void GFWrite_u32(u32 data) {
    GXCmd1u32(data);
}

inline void GFWriteCPCmd(u8 addr, u32 val) {
    GFWrite_u8(GX_LOAD_CP_REG);
    GFWrite_u8(addr);
    GFWrite_u32(val);
}

inline void GFWriteXFCmd(u16 addr, u32 val) {
    GFWrite_u8(GX_LOAD_XF_REG);
    GFWrite_u16(0);
    GFWrite_u16(addr);
    GFWrite_u32(val);
}

inline void GFWriteXFCmdHdr(u16 addr, u8 len) {
    GFWrite_u8(GX_LOAD_XF_REG);
    GFWrite_u16(len - 1);
    GFWrite_u16(addr);
}

inline void GFWriteBPCmd(u32 x) {
    GFWrite_u8(GX_LOAD_BP_REG);
    GFWrite_u32(x);
}

#endif /* GF_H */
