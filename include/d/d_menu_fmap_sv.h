#ifndef D_MENU_FMAP_SV_H
#define D_MENU_FMAP_SV_H

#include "dolphin/types.h"

class dMenu_FmapSv_c {
public:
    dMenu_FmapSv_c() {
        field_0x0 = 0;
        field_0x1 = 0;
        field_0x2 = -10;
        field_0x3 = -10;
        field_0x4 = -10;
        field_0x5 = -10;
        field_0x6 = -10;
        field_0x7 = -10;
        field_0x8 = 0;
        field_0x9 = -1;
        field_0xA = -10;
        field_0xB = -10;
    }

    ~dMenu_FmapSv_c() {}

    // TODO
    u8 getActive() {}
    void setActive(u8 val) {}
    s8 getCmapSelNo() {}
    void setCmapSelNo(s8 val) {}
    s8 getCurX() {}
    void setCurX(s8 val) {}
    s8 getCurY() {}
    void setCurY(s8 val) {}
    s8 getCurWX() {}
    void setCurWX(s8 val) {}
    s8 getCurWY() {}
    void setCurWY(s8 val) {}
    s8 getCurHX() {}
    void setCurHX(s8 val) {}
    s8 getCurHY() {}
    void setCurHY(s8 val) {}
    u8 getDispMode() {}
    void setDispMode(u8 val) {}
    u8 getFmapZoom() {}
    void setFmapZoom(u8 val) {}
    s8 getZoomGridX() {}
    void setZoomGridX(s8 val) {}
    s8 getZoomGridY() {}
    void setZoomGridY(s8 val) {}

public:
    /* 0x0 */ s8 field_0x0;
    /* 0x1 */ s8 field_0x1;
    /* 0x2 */ s8 field_0x2;
    /* 0x3 */ s8 field_0x3;
    /* 0x4 */ s8 field_0x4;
    /* 0x5 */ s8 field_0x5;
    /* 0x6 */ s8 field_0x6;
    /* 0x7 */ s8 field_0x7;
    /* 0x8 */ s8 field_0x8;
    /* 0x9 */ s8 field_0x9;
    /* 0xA */ s8 field_0xA;
    /* 0xB */ s8 field_0xB;
};

#endif //D_MENU_FMAP_SV_H
