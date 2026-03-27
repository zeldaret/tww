#ifndef D_MENU_FMAP_H
#define D_MENU_FMAP_H

#include "dolphin/types.h"
#include "SSystem/SComponent/c_xyz.h"
#include "d/d_menu_fmap2.h"

class JUTFont;
class J2DScreen;
struct fopMsgM_pane_class;
class dMenu_FmapSv_c;
struct cursorTable_t;
struct aramCmapDatPat_t;

class dDlst_FMAP_c : public dDlst_base_c {
public:
    virtual ~dDlst_FMAP_c() {}
    virtual void draw();
};

class dMenu_Fmap_c {
public:
    virtual ~dMenu_Fmap_c() {}

    void draw() { _draw(); }
    void getCtCurWX() {}
    void getCtCurWY() {}
    void getCtCurX() {}
    void getCtCurY() {}
    void getCtDispMode() {}
    void getCtFmapZoom() {}
    void getCtZoomGridX() {}
    void getCtZoomGridY() {}
    void lineInter0to1(float, float, float) {}
    void lineInter0to1ForU8(unsigned char, unsigned char, float) {}
    void setCtCurHX(signed char) {}
    void setCtCurHY(signed char) {}
    void setCtCurWX(signed char) {}
    void setCtCurWY(signed char) {}
    void setCtCurX(signed char) {}
    void setCtCurY(signed char) {}
    void setCtDispMode(unsigned char) {}
    void setCtFmapZoom(unsigned char) {}
    void setCtZoomGridX(signed char) {}
    void setCtZoomGridY(signed char) {}
    void setFont(JUTFont*, JUTFont*) {}
    void setSvPtr(dMenu_FmapSv_c* i_ptr) { mSvPtr = i_ptr; }
    void setTextArea_New(char*, char*, char*, char*, char*, char*) {}
    void stopWrapBackEmitter() {}
    void stopWrapSpotEmitter(int) {}

    void _create();
    void phantomShipCheck();
    void screenSet();
    void initialize();
    void displayinit();
    void backClothDispInit();
    void calcGetMapCount();
    void dispEndSalvageMark();
    void checkMarkCheck1();
    void checkMarkCheck2();
    void checkMarkCheck3();
    bool isFmapClose();
    void setPaneOnOff(J2DScreen*, unsigned long, bool);
    void childPaneMoveSp(fopMsgM_pane_class*, fopMsgM_pane_class*, float, float, float);
    void selGridMaskAlphaCtrl(short, unsigned char, unsigned char, int);
    void fmapMaskAlphaCtrl(short, unsigned char, unsigned char, int);
    void selCursorInit();
    void selCursorHide();
    void selCursorMove();
    void islandNameChange();
    void changeIslandName(unsigned char);
    void AreaTxtChg();
    void AreaTxtChgFast();
    void salvageGetItemChg();
    void salvageGetItemChange();
    void SalvItmDispChgFast();
    void changeSalvageGetItem(unsigned char);
    void selCursorAnime();
    void zoomCursorInit();
    void zoomCursorAnime();
    void playerPointGridAnimeInit();
    void playerPointGridAnime();
    void setDspWindAngle();
    void windArrowColorAnime();
    void checkMarkAnimeInit();
    void checkMarkAnime();
    void readFmapTexture(const char*);
    void aramCmapDatRead();
    void initCmapDatPnt(aramCmapDatPat_t*);
    void getGridNumToCmapDatPnt(int);
    void setDispIslandPos(signed char, signed char);
    void setIslandPos(fopMsgM_pane_class*, float, float);
    void changeFmapTexture(signed char, signed char);
    void setDspNormalMapLink();
    void setDspLargeMapLink();
    void checkDspLargeMapLink();
    void checkDspLargeMapShip();
    void dispEndSalvageLargeMark();
    void setDspHugeMapLink();
    void dispEndSalvageHugeMark(float, float);
    void checkDspHugeMapLink();
    void checkDspHugeMapShip();
    bool _open();
    bool _close();
    void _close_normalMode();
    void _move();
    void _draw();
    void _delete();
    void FmapProcMain();
    void SelectGrid();
    void zoom1000x1000Init();
    void zoomMapAlphaSet(signed char, signed char, fopMsgM_pane_class*, unsigned char);
    void ZoomGridLv1In();
    void ZoomGridLv1Proc();
    void zoom200x200Init();
    void ZoomGridLv1Out();
    void ZoomGridLv2In();
    void ZoomGridLv2Proc();
    void ZoomGridLv2Out();
    void move_normal();
    void FmapProc();
    void HikakuProc();
    void fmap2Open();
    void fmap2Move();
    void fmap2Close();
    void paneTransBase(short, unsigned char, float, float, unsigned char, int);
    void paneTranceZoomMap(short, unsigned char, float, float, float, float, float, float, unsigned char, int);
    void paneTranceZoomMapAlpah(short, unsigned char, unsigned char, int);
    void paneTranceZoom2Map(short, unsigned char, float, float, float, float, float, float, unsigned char, int);
    void paneAlphaFmapCursor(fopMsgM_pane_class*, short, unsigned char, unsigned char, int);
    void PaneAlphaSelvageItem(short, unsigned char);
    void gShipMarkAnimeInit();
    void gShipMarkAnime();
    bool _open_warpMode();
    void init_warpMode();
    void selCursorMoveWarp();
    void _close_warpMode();
    void moveMain_warpMode();
    void wrapMove();
    void wrapSelWinFadeIn1();
    void wrapSelect();
    void wrapSelWinFadeOut();
    void wrapSelWarp();
    void warpAreaAnime0();
    void paneTranceWarpMsg(fopMsgM_pane_class*, short, unsigned char, float, float, unsigned char, int);
    void paneAlphaWarpMsgBack(short, unsigned char, unsigned char, int);
    void warpSelCursorMove();
    void warpSelCursorAnimeInit();
    void warpSelCursorAnime();
    void getWarpAreaGridX(int);
    void getWarpAreaGridY(int);
    void getWarpAreaNo(const cursorTable_t*);
    void getWarpAreaNoUp(const cursorTable_t*);
    void getWarpAreaNoDown(const cursorTable_t*);
    void getWarpAreaNoLeft(const cursorTable_t*);
    void getWarpAreaNoRight(const cursorTable_t*);
    void getWarpAreaTablePtr(signed char, signed char);
    void areaTextChangeAnimeInit();
    void areaTextChangeAnime();
    void PaneAlphaAreaTxt(short, unsigned char, int);
    void setDspWarpBackCornerColor(float);
    void setWrapBackEmitter(cXyz);
    void setWrapSpotEmitter(int, cXyz);
    bool _open_fishManMode();
    void _close_fishManMode();
    void init_fishManMode();
    void movefishManMode();
    void fmDispArea();
    void fmZoomGridLv1In();
    void fmZoomGridLv2In();
    void islandNameSet(unsigned char);
    void fmMapWrite();
    void fmMapWait();
    void paneAlphaZoom2Map(short, unsigned char, unsigned char, int);
    void fmZoomGridLv2Out();
    void fmZoomGridLv1Out();
    void fmEndWait();
    bool _open_wallPaper();
    u8 getButtonIconMode();

public:
    /* 0x0004 */ u8 padding_0x4[0x1C - 0x4];
    /* 0x001C */ dDlst_FMAP_c mDlst;
    /* 0x0020 */ u8 padding_0x20[0x24 - 0x20];
    /* 0x0024 */ dMenu_Fmap2_c mFmap2;
    // TODO
    /* 0x2874 */ u8 padding_0x2874[0x2878 - 0x2874];
    /* 0x2878 */ dMenu_FmapSv_c* mSvPtr;
    /* 0x287C */ u8 padding_0x287C[0x51B4 - 0x287C];
}; // Size: 0x51B4

STATIC_ASSERT(sizeof(dMenu_Fmap_c) == 0x51B4);

class dMf_HIO_c {
public:
    dMf_HIO_c();
};

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

#endif /* D_MENU_FMAP_H */
