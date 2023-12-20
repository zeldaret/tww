#ifndef GFPIXEL_H
#define GFPIXEL_H

#include "dolphin/gx/GXEnum.h"
#include "dolphin/gx/GXStruct.h"

void GFSetFog(GXFogType type, f32 startZ, f32 endZ, f32 nearZ, f32 farZ, GXColor color);
void GFSetBlendModeEtc(GXBlendMode, GXBlendFactor, GXBlendFactor, GXLogicOp, u8, u8, u8);

#endif /* GFPIXEL_H */
