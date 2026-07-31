#ifndef JRENDERER_H
#define JRENDERER_H

#include "dolphin/gx/GX.h"

void JRNLoadTexCached(GXTexMapID id, u32 addr_even, GXTexCacheSize size_even, u32 addr_odd, GXTexCacheSize size_odd);

#endif /* JRENDERER_H */
