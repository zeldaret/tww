#ifndef D_MENU_FMAP_SV_H
#define D_MENU_FMAP_SV_H

#include "dolphin/types.h"

class dMenu_FmapSv_c {
public:
    dMenu_FmapSv_c() {
        active = 0;
        cmapSelNo = 0;
        curX = -10;
        curY = -10;
        curWX = -10;
        curWY = -10;
        curHX = -10;
        curHY = -10;
        dispMode = 0;
        fmapZoom = -1;
        zoomGridX = -10;
        zoomGridY = -10;
    }

    ~dMenu_FmapSv_c() {}

    u8 getActive() { return active; }
    void setActive(u8 val) { active = val; }
    s8 getCmapSelNo() { return cmapSelNo; }
    void setCmapSelNo(s8 val) { cmapSelNo = val; }
    s8 getCurX() { return curX; }
    void setCurX(s8 val) { curX = val; }
    s8 getCurY() { return curY; }
    void setCurY(s8 val) { curY = val; }
    s8 getCurWX() { return curWX; }
    void setCurWX(s8 val) { curWX = val; }
    s8 getCurWY() { return curWY; }
    void setCurWY(s8 val) { curWY = val; }
    s8 getCurHX() { return curHX; }
    void setCurHX(s8 val) { curHX = val; }
    s8 getCurHY() { return curHY; }
    void setCurHY(s8 val) { curHY = val; }
    u8 getDispMode() { return dispMode; }
    void setDispMode(u8 val) { dispMode = val; }
    u8 getFmapZoom() { return fmapZoom; }
    void setFmapZoom(u8 val) { fmapZoom = val; }
    s8 getZoomGridX() { return zoomGridX; }
    void setZoomGridX(s8 val) { zoomGridX = val; }
    s8 getZoomGridY() { return zoomGridY; }
    void setZoomGridY(s8 val) { zoomGridY = val; }

public:
    /* 0x0 */ u8 active;
    /* 0x1 */ s8 cmapSelNo;
    /* 0x2 */ s8 curX;
    /* 0x3 */ s8 curY;
    /* 0x4 */ s8 curWX;
    /* 0x5 */ s8 curWY;
    /* 0x6 */ s8 curHX;
    /* 0x7 */ s8 curHY;
    /* 0x8 */ u8 dispMode;
    /* 0x9 */ u8 fmapZoom;
    /* 0xA */ s8 zoomGridX;
    /* 0xB */ s8 zoomGridY;
};

#endif //D_MENU_FMAP_SV_H
