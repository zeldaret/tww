//
// Generated by dtk
// Translation Unit: JRenderer.cpp
//

#include "dolphin/gx/GX.h"
#include "JSystem/J3DGraphBase/J3DGD.h"

u8 JRNTexImage1Ids[] = { 0x8c, 0x8d, 0x8e, 0x8f, 0xac, 0xad, 0xae, 0xaf };
u8 JRNTexImage2Ids[] = { 0x90, 0x91, 0x92, 0x93, 0xb0, 0xb1, 0xb2, 0xb3 };

/* 802D5EB8-802D5F38       .text JRNLoadTexCached__F11_GXTexMapIDUl15_GXTexCacheSizeUl15_GXTexCacheSize */
void JRNLoadTexCached(GXTexMapID id, u32 addr_even, GXTexCacheSize size_even, u32 addr_odd, GXTexCacheSize size_odd) {
    GFWriteBPCmd((addr_even >> 5) | ((size_even + 3) << 15) | ((size_even + 3) << 18) | (JRNTexImage1Ids[id] << 24));
    if (size_odd != GX_TEXCACHE_NONE && addr_odd < 0x100000)
        GFWriteBPCmd((addr_odd >> 5) | ((size_odd + 3) << 15) | ((size_odd + 3) << 18) | (JRNTexImage2Ids[id] << 24));
}
