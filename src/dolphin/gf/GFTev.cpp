#include "dolphin/gd/GDBase.h"
#include "dolphin/gd/GDGeometry.h"
#include "dolphin/gf/GF.h"

void GFSetTevColor(GXTevRegID, GXColor) {
    // NONMATCHING
}

void GFSetTevColorS10(GXTevRegID reg, GXColorS10 color) {
    u32 regRA;
    u32 regBG;

    regRA = BP_TEV_COLOR_REG_RA(color.r & 0x7FF, color.a & 0x7FF, 0, 0xE0 + reg * 2);
    regBG = BP_TEV_COLOR_REG_BG(color.b & 0x7FF, color.g & 0x7FF, 0, 0xE1 + reg * 2);

    GFWriteBPCmd(regRA);
    GFWriteBPCmd(regBG);
    GFWriteBPCmd(regBG);
    GFWriteBPCmd(regBG);
}

void GFSetAlphaCompare(GXCompare, u8, GXAlphaOp, GXCompare, u8) {
    // NONMATCHING
}
