#include "dolphin/gd.h"
#include "dolphin/gf.h"
#include "dolphin/os.h"

void GFSetChanMatColor(GXChannelID chan, GXColor color) {
    GFWriteXFCmd((chan & 1) + XF_REG_MATERIAL0_ID, color.r << 24 | color.g << 16 | color.b << 8 | color.a);
}
