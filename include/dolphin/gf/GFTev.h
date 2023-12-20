#ifndef GFTEV_H
#define GFTEV_H

#include "dolphin/gx/GXEnum.h"
#include "dolphin/gx/GXStruct.h"

void GFSetTevColor(GXTevRegID, GXColor);
void GFSetTevColorS10(GXTevRegID, GXColorS10);
void GFSetAlphaCompare(GXCompare, u8, GXAlphaOp, GXCompare, u8);

#endif /* GFTEV_H */
