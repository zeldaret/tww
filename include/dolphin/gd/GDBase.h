#ifndef GDBASE_H
#define GDBASE_H

#include "dolphin/gx/GXAttr.h"
#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define GX_LOAD_CP_REG         0x08
#define GX_LOAD_XF_REG         0x10
#define GX_LOAD_INDX_A         0x20
#define GX_LOAD_INDX_B         0x28
#define GX_LOAD_INDX_C         0x30
#define GX_LOAD_INDX_D         0x38
#define GX_LOAD_BP_REG         0x61

typedef struct _GDLObj {
    /* 0x0 */ u8* start;
    /* 0x4 */ u32 length;
    /* 0x8 */ u8* ptr;
    /* 0xC */ u8* top;
} GDLObj;  // Size: 0x10

extern GDLObj* __GDCurrentDL;

typedef void (*GDOverflowCallback)(void);

void GDInitGDLObj(GDLObj*, void*, u32);
void GDFlushCurrToMem(void);
void GDPadCurr32(void);
void GDOverflowed(void);
void GDSetVtxDescv(GXVtxDescList*);

inline void __GDWrite(u8 data) {
    *__GDCurrentDL->ptr++ = data;
}

inline void GDSetCurrent(GDLObj* obj) {
    __GDCurrentDL = obj;
}

inline u32 GDGetGDLObjOffset(GDLObj* obj) {
    return (u32)(obj->ptr - obj->start);
}

inline u8* GDGetCurrPointer() {
    return __GDCurrentDL->ptr;
}

inline s32 GDGetCurrOffset() {
    return __GDCurrentDL->ptr - __GDCurrentDL->start;
}

inline void GDSetCurrOffset(s32 offs) {
    __GDCurrentDL->ptr = __GDCurrentDL->start + offs;
}

inline void GDAdvCurrOffset(s32 offs) {
    __GDCurrentDL->ptr += offs;
}

/* Unused
inline GDLObj* GDGetCurrent() {
    return __GDCurrentDL;
} */

inline void GDOverflowCheck(u32 len) {
    if (__GDCurrentDL->ptr + len > __GDCurrentDL->top) {
        GDOverflowed();
    }
}

inline void GDWrite_u32(u32 v) {
    GDOverflowCheck(4);
    __GDWrite((v >> 24) & 0xff);
    __GDWrite((v >> 16) & 0xff);
    __GDWrite((v >> 8) & 0xff);
    __GDWrite((v >> 0) & 0xff);
}

inline void GDWrite_u16(u16 v) {
    GDOverflowCheck(2);
    __GDWrite(v >> 8);
    __GDWrite(v & 0xff);
}

inline void GDWrite_u8(u8 v) {
    GDOverflowCheck(1);
    __GDWrite(v);
}

inline static void GDWriteXFCmdHdr(u16 addr, u8 len) {
    GDWrite_u8(GX_LOAD_XF_REG);
    GDWrite_u16(len - 1);
    GDWrite_u16(addr);
}

inline static void GDWriteXFCmd(u16 addr, u32 val) {
    GDWrite_u8(GX_LOAD_XF_REG);
    GDWrite_u16(0);
    GDWrite_u16(addr);
    GDWrite_u32(val);
}

inline static void GDWriteXFIndxDCmd(u16 addr, u8 len, u16 index) {
    GDWrite_u8(GX_LOAD_INDX_D);
    GDWrite_u16(index);
    GDWrite_u16((len - 1) << 12 | addr);
}

inline static void GDWriteXFIndxACmd(u16 addr, u8 len, u16 index) {
    GDWrite_u8(GX_LOAD_INDX_A);
    GDWrite_u16(index);
    GDWrite_u16(((len - 1) << 12) | addr);
}

inline static void GDWriteXFIndxBCmd(u16 addr, u8 len, u16 index) {
    GDWrite_u8(GX_LOAD_INDX_B);
    GDWrite_u16(index);
    GDWrite_u16(((len - 1) << 12) | addr);
}

inline static void GDWriteXFIndxCCmd(u16 addr, u8 len, u16 index) {
    GDWrite_u8(GX_LOAD_INDX_C);
    GDWrite_u16(index);
    GDWrite_u16(((len - 1) << 12) | addr);
}

inline static void GDWriteCPCmd(u8 addr, u32 val) {
    GDWrite_u8(GX_LOAD_CP_REG);
    GDWrite_u8(addr);
    GDWrite_u32(val);
}

inline static void GDWriteBPCmd(u32 regval) {
    GDWrite_u8(GX_LOAD_BP_REG);
    GDWrite_u32(regval);
}

#ifdef __cplusplus
};
#endif

#endif /* GDBASE_H */
