#include "dolphin/gd/GDBase.h"
#include "dolphin/gd/GDGeometry.h"
#include "dolphin/gf/GF.h"

void GFSetTevColor(GXTevRegID reg, GXColor color) {
    u32 regRA;
    u32 regBG;

    regRA = BP_TEV_COLOR_REG_RA(color.r, color.a, 0, 0xE0 + reg * 2);
    regBG = BP_TEV_COLOR_REG_BG(color.b, color.g, 0, 0xE1 + reg * 2);

    GFWriteBPCmd(regRA);
    GFWriteBPCmd(regBG);
    GFWriteBPCmd(regBG);
    GFWriteBPCmd(regBG);
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

void GFSetAlphaCompare(GXCompare comp0, u8 ref0, GXAlphaOp op, GXCompare comp1, u8 ref1) {
    GFWriteBPCmd(BP_ALPHA_COMPARE(ref0, ref1, comp0, comp1, op, 0xF3));
}
