#ifndef D_MENU_FMAPSV_H
#define D_MENU_FMAPSV_H

#include "JSystem/JUtility/JUTAssert.h"
#include "global.h"

enum dMf_ZoomLevel {
    FMAP_ZOOM_WORLD  = 0,
    FMAP_ZOOM_SECTOR = 1,
    FMAP_ZOOM_DETAIL = 2,
};

struct aramCmapSalvagePnt_t {
    /* 0x0 */ s16 field_0x0;
    /* 0x2 */ s16 field_0x2;
    /* 0x4 */ s16 x;
    /* 0x6 */ s16 y;
}; // Size: 0x8

struct aramCmapDatPnt_t {
    /* 0x00 */ s8 gridNo;
    /* 0x01 */ s8 collectMapNo;
    /* 0x02 */ s8 cmapNo;
    /* 0x03 */ s8 mapType;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ aramCmapSalvagePnt_t salvagePnt[4];
}; // Size: 0x26
STATIC_ASSERT(sizeof(aramCmapDatPnt_t) == 0x26);

struct aramCmapDatPat_t {
    /* 0x00 */ int num;
    /* 0x04 */ aramCmapDatPnt_t pnt[];
}; // Size: 0x4+

class aramCmapDat_c {
public:
    void init(aramCmapDatPat_t* a_pat) {
        if (a_pat != NULL) {
            mNum = a_pat->num;
            mpPnt = a_pat->pnt;
        } else {
            JUT_ASSERT(252, FALSE);
        }
    }
    void getAramCmapDatValue() {}
    void getCmapDatPnt(int) {}
    aramCmapDatPnt_t* getCmapDatPnt3(int i_gridIdx) {
        aramCmapDatPnt_t* pnt = mpPnt;
        int i;
        for (i = 0; i < mNum; i++) {
            if (pnt->gridNo == i_gridIdx + 1) {
                break;
            }
            pnt++;
        }
        if (i < mNum) {
            return pnt;
        }
        return NULL;
    }
    aramCmapDatPnt_t* getCmapDatPnt4(int i_cmapIdx) {
        aramCmapDatPnt_t* pnt = mpPnt;
        int i;
        for (i = 0; i < mNum; i++) {
            if (pnt->cmapNo == i_cmapIdx + 1) {
                break;
            }
            pnt++;
        }
        if (i < mNum) {
            return pnt;
        }
        return NULL;
    }

private:
    /* 0x00 */ int mNum;
    /* 0x04 */ aramCmapDatPnt_t* mpPnt;
};  // Size: 0x8

class dMenu_FmapSv_c {
public:
    dMenu_FmapSv_c() {
        dispMode = 0;
        fmapZoom = 0;
        zoomGridX = -10;
        zoomGridY = -10;
        curX = -10;
        curY = -10;
        curWX = -10;
        curWY = -10;
        active = 0;
        cmapSelNo = -1;
        curHX = -10;
        curHY = -10;
    }

    ~dMenu_FmapSv_c() {}

    u8 getDispMode() { return dispMode; }
    void setDispMode(u8 val) { dispMode = val; }
    u8 getFmapZoom() { return fmapZoom; }
    void setFmapZoom(u8 val) { fmapZoom = val; }
    s8 getZoomGridX() { return zoomGridX; }
    void setZoomGridX(s8 val) { zoomGridX = val; }
    s8 getZoomGridY() { return zoomGridY; }
    void setZoomGridY(s8 val) { zoomGridY = val; }
    s8 getCurX() { return curX; }
    void setCurX(s8 val) { curX = val; }
    s8 getCurY() { return curY; }
    void setCurY(s8 val) { curY = val; }
    s8 getCurWX() { return curWX; }
    void setCurWX(s8 val) { curWX = val; }
    s8 getCurWY() { return curWY; }
    void setCurWY(s8 val) { curWY = val; }
    u8 getActive() { return active; }
    void setActive(u8 val) { active = val; }
    u8 getCmapSelNo() { return cmapSelNo; }
    void setCmapSelNo(s8 val) { cmapSelNo = val; }
    s8 getCurHX() { return curHX; }
    void setCurHX(s8 val) { curHX = val; }
    s8 getCurHY() { return curHY; }
    void setCurHY(s8 val) { curHY = val; }

public:
    /* 0x0 */ u8 dispMode;
    /* 0x1 */ u8 fmapZoom;
    /* 0x2 */ s8 zoomGridX;
    /* 0x3 */ s8 zoomGridY;
    /* 0x4 */ s8 curX;
    /* 0x5 */ s8 curY;
    /* 0x6 */ s8 curWX;
    /* 0x7 */ s8 curWY;
    /* 0x8 */ u8 active;
    /* 0x9 */ s8 cmapSelNo;
    /* 0xA */ s8 curHX;
    /* 0xB */ s8 curHY;
};

#endif /* D_MENU_FMAPSV_H */
