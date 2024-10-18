#ifndef GX_H_
#define GX_H_

#include "dolphin/gx/GXAttr.h" // IWYU pragma: export
#include "dolphin/gx/GXBump.h" // IWYU pragma: export
#include "dolphin/gx/GXDisplayList.h" // IWYU pragma: export
#include "dolphin/gx/GXFifo.h" // IWYU pragma: export
#include "dolphin/gx/GXFrameBuf.h" // IWYU pragma: export
#include "dolphin/gx/GXGeometry.h" // IWYU pragma: export
#include "dolphin/gx/GXLight.h" // IWYU pragma: export
#include "dolphin/gx/GXMisc.h" // IWYU pragma: export
#include "dolphin/gx/GXPerf.h" // IWYU pragma: export
#include "dolphin/gx/GXPixel.h" // IWYU pragma: export
#include "dolphin/gx/GXTev.h" // IWYU pragma: export
#include "dolphin/gx/GXTexture.h" // IWYU pragma: export
#include "dolphin/gx/GXTransform.h" // IWYU pragma: export
#include "dolphin/gx/GXStruct.h" // IWYU pragma: export

#include "dolphin/os/OSUtil.h"

#ifdef __cplusplus
extern "C" {
#endif

// Pack value into bitfield
#define GX_BITFIELD_SET(field, pos, size, value) (field) = __rlwimi((field), (value), 31 - (pos) - (size) + 1, (pos), (pos) + (size)-1)
#define GX_BITFIELD_TRUNC(field, pos, size, value) (__rlwimi((field), (value), 0, (pos), (pos) + (size)-1))

#define GX_BITGET(field, pos, size)              ((field) >> (31 - (pos) - (size) + 1) & ((1 << (size)) - 1))
#define GX_GET_REG(reg, st, end)    GX_BITGET(reg, st, (end - st + 1))
#define GX_SET_REG(reg, x, st, end) GX_BITFIELD_SET(reg, st, (end - st + 1), x)
#define GX_SET_TRUNC(reg, x, st, end) GX_BITFIELD_TRUNC((reg), (st), ((end) - (st) + 1), (x))

#define GXCOLOR_AS_U32(color) (*((u32*)&(color)))

#define INSERT_FIELD(reg, value, nbits, shift)                                 \
    (reg) = ((u32) (reg) & ~(((1 << (nbits)) - 1) << (shift))) |               \
            ((u32) (value) << (shift));

#define FAST_FLAG_SET(regOrg, newFlag, shift, size)                                                                \
    do {                                                                                                           \
        (regOrg) = (u32)__rlwimi((int)(regOrg), (int)(newFlag), (shift), (32 - (shift) - (size)), (31 - (shift))); \
    } while (0);

#define GX_LOAD_BP_REG 0x61
#define GX_NOP 0

typedef union {
    u8 u8;
    u16 u16;
    u32 u32;
    u64 u64;
    s8 s8;
    s16 s16;
    s32 s32;
    s64 s64;
    f32 f32;
    f64 f64;
} PPCWGPipe;

#define GXFIFO_ADDR 0xCC008000
volatile PPCWGPipe GXFIFO AT_ADDRESS(GXFIFO_ADDR);

#define GX_CP_LOAD_REG(addr, data)                                                                 \
    GXFIFO.s8 = GX_FIFO_CMD_LOAD_CP_REG;                                                         \
    GXFIFO.s8 = (addr);                                                                          \
    GXFIFO.s32 = (data);

/**
 * Header for an XF register load
 */
#define GX_XF_LOAD_REG_HDR(addr)                                                                   \
    GXFIFO.s8 = GX_FIFO_CMD_LOAD_XF_REG;                                                           \
    GXFIFO.s32 = (addr);

/**
 * Load immediate value into XF register
 */
#define GX_XF_LOAD_REG(addr, data)                                                                 \
    GX_XF_LOAD_REG_HDR(addr);                                                                      \
    GXFIFO.s32 = (data);

/**
 * Load immediate value into BP register
 */
#define GX_BP_LOAD_REG(data)                                                                       \
    GXFIFO.s8 = GX_FIFO_CMD_LOAD_BP_REG;                                                           \
    GXFIFO.s32 = (data);

/**
 * Load immediate values into multiple XF registers
 */
#define GX_XF_LOAD_REGS(size, addr)                                                                \
    {                                                                                              \
        u32 cmd = (size) << 16 | addr;                                                             \
        GX_XF_LOAD_REG_HDR(cmd);                                                                   \
    }

// Direct
inline void GXPosition2f32(f32 x, f32 z) {
    GXFIFO.f32 = x;
    GXFIFO.f32 = z;
}

inline void GXPosition3f32(f32 x, f32 y, f32 z) {
    GXFIFO.f32 = x;
    GXFIFO.f32 = y;
    GXFIFO.f32 = z;
}

inline void GXPosition2s8(s8 x, s8 y) {
    GXFIFO.s8 = x;
    GXFIFO.s8 = y;
}

inline void GXPosition3s8(s8 x, s8 y, s8 z) {
    GXFIFO.s8 = x;
    GXFIFO.s8 = y;
    GXFIFO.s8 = z;
}

inline void GXPosition2u16(u16 x, u16 y) {
    GXFIFO.u16 = x;
    GXFIFO.u16 = y;
}

inline void GXPosition2s16(s16 x, s16 y) {
    GXFIFO.s16 = x;
    GXFIFO.s16 = y;
}

inline void GXPosition3s16(s16 x, s16 y, s16 z) {
    GXFIFO.s16 = x;
    GXFIFO.s16 = y;
    GXFIFO.s16 = z;
}

inline void GXNormal3f32(f32 x, f32 y, f32 z) {
    GXFIFO.f32 = x;
    GXFIFO.f32 = y;
    GXFIFO.f32 = z;
}

inline void GXColor1u32(u32 c) {
    GXFIFO.u32 = c;
}

inline void GXTexCoord2f32(f32 s, f32 t) {
    GXFIFO.f32 = s;
    GXFIFO.f32 = t;
}

inline void GXTexCoord2u8(u8 s, u8 t) {
    GXFIFO.u8 = s;
    GXFIFO.u8 = t;
}

inline void GXTexCoord1x8(u8 s) {
    GXFIFO.u8 = s;
}

inline void GXTexCoord2s8(s8 x, s8 y) {
    GXFIFO.s8 = x;
    GXFIFO.s8 = y;
}

inline void GXTexCoord2u16(u16 x, u16 y) {
    GXFIFO.u16 = x;
    GXFIFO.u16 = y;
}

inline void GXTexCoord2s16(const s16 u, const s16 v) {
    GXFIFO.s16 = u;
    GXFIFO.s16 = v;
}

// Indexed
inline void GXPosition1x8(u8 x) {
    GXFIFO.u8 = x;
}

inline void GXPosition1x16(u16 x) {
    GXFIFO.u16 = x;
}

inline void GXNormal1x8(u8 x) {
    GXFIFO.u8 = x;
}

inline void GXColor1x16(u16 x) {
    GXFIFO.u16 = x;
}

inline void GXTexCoord1x16(u16 x) {
    GXFIFO.u16 = x;
}

inline void GFWriteBPCmd(u32 x) {
    GXFIFO.u8 = GX_CMD_LOAD_BP_REG;
    GXFIFO.u32 = x;
}

inline void GXEnd() {}

#ifdef __cplusplus
};
#endif

#endif
