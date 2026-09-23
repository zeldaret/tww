#include "dolphin/gd/GDBase.h"
#include "dolphin/gd/GDGeometry.h"
#include "dolphin/gf/GF.h"
#include "dolphin/os/OS.h"

void GFSetChanMatColor(GXChannelID chan, GXColor color) {
    GFWriteXFCmd((chan & 1) + XF_REG_MATERIAL0_ID, color.r << 24 | color.g << 16 | color.b << 8 | color.a);
}
