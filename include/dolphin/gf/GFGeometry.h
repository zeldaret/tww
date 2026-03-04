#ifndef GFGEOMETRY_H
#define GFGEOMETRY_H

#include "dolphin/gx/GXAttr.h"

void GFSetVtxDescv(GXVtxDescList*);
void GFSetVtxAttrFmtv(GXVtxFmt, GXVtxAttrFmtList*);
void GFSetArray(GXAttr, void*, u8);
void GFSetCullMode(GXCullMode);

inline void GFBegin(GXPrimitive type, GXVtxFmt fmt, u16 vert_num) {
    GXFIFO.u8 = fmt | type;
    GXFIFO.u16 = vert_num;
}

inline void GFEnd() {}

inline void GFWrite_f32(f32 f) {
    GX_WRITE_U32(*reinterpret_cast<u32*>(&f));
}

inline void GFWrite_s16(s16 s) {
    GXFIFO.s16 = s;
}

inline void GFPosition3f32(f32 x, f32 y, f32 z) {
    GFWrite_f32(x);
    GFWrite_f32(y);
    GFWrite_f32(z);
}

inline void GFTexCoord2s16(s16 u, s16 v) {
    GFWrite_s16(u);
    GFWrite_s16(v);
}

#endif /* GFGEOMETRY_H */
