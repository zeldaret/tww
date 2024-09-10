/**
 * GXDisplayList.c
 * Description:
 */

#include "dolphin/gx/GXDisplayList.h"
#include "dolphin/gx/GX.h"

void GXCallDisplayList(void* list, u32 nbytes) {
    if (__GXData->dirtyState != 0) {
        __GXSetDirtyState();
    }

    if (*(u32*)__GXData == 0) {
        __GXSendFlushPrim();
    }

    GXFIFO.u8 = 0x40;
    GXFIFO.u32 = (u32)list;
    GXFIFO.u32 = nbytes;
}
