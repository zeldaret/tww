#ifndef GFTRANSFORM_H
#define GFTRANSFORM_H

#include "dolphin/gx/GXEnum.h"
#include "dolphin/mtx/mtx.h"

void GFLoadPosMtxImm(MtxP, GXPosNrmMtx);
void GFLoadNrmMtxImm(MtxP, GXPosNrmMtx);
void GFSetCurrentMtx(u32, u32, u32, u32, u32, u32, u32, u32, u32);

#endif /* GFTRANSFORM_H */
