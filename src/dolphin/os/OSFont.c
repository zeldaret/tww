#include "dolphin/os/OSFont.h"
#include "dolphin/os/OS.h"
#include "dolphin/vi/vi.h"

u16 OSGetFontEncode(void) {
    static u16 fontEncode = 0xFFFF;

    if (fontEncode <= 1) {
        return fontEncode;
    }

    switch (*(u32*)OSPhysicalToCached(0xCC)) {
    case VI_NTSC:
        fontEncode = ((__VIRegs[55] & 2) != 0)
                         ? OS_FONT_ENCODE_SJIS
                         : OS_FONT_ENCODE_ANSI;
        break;
    case VI_PAL:
    case VI_MPAL:
    case VI_DEBUG:
    case VI_DEBUG_PAL:
    case VI_EURGB60:
    default:
        fontEncode = OS_FONT_ENCODE_ANSI;
    }

    return fontEncode;
}
