#ifndef GFGEOMETRY_H
#define GFGEOMETRY_H

#include "dolphin/gx/GXAttr.h"

void GFSetVtxDescv(GXVtxDescList*);
void GFSetVtxAttrFmtv(GXVtxFmt, GXVtxAttrFmtList*);
void GFSetArray(GXAttr, void*, u8);
void GFSetCullMode(GXCullMode);

#endif /* GFGEOMETRY_H */
