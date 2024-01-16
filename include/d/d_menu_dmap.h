#ifndef D_MENU_DMAP_H
#define D_MENU_DMAP_H

#include "dolphin/types.h"

class J2DPane;
class fopMsgM_pane_class;
class JKRArchive;
class JUTFont;

class dMenu_Dmap_c {
public:
    void alphaChange(fopMsgM_pane_class*, float) {}
    void draw() {}
    void setArchive(JKRArchive*) {}
    void setFont(JUTFont*, JUTFont*) {}
    void setItemTexBuffer(int, void*) {}
    void setTextArea(char*, char*, char*, char*, char*, char*) {}

    void changeFloorTexture(J2DPane*, int);
    void screenSet();
    void initialize();
    void treasureSet();
    void treasureDraw();
    void paneMove(float);
    void paneAlpha(float);
    void decAlpha(float);
    void cursorMove();
    void cursorAnime();
    void noteInit();
    void noteCheck();
    void noteAppear();
    void noteOpen();
    void noteClose();
    void noteOpenProc(short);
    void itemScale();
    void floorInit();
    void mapMove();
    void mapOffsetY();
    void itemnameMove();
    void dnameSet();
    void itemnameSet();
    void itemnoteSet();
    void outFontInit();
    void linkAnime();
    void bossAnime();
    void bossEyeAnime();
    void _create();
    void _delete();
    void _move();
    void _draw();
    void _open();
    void _close();
};

class dMd_HIO_c {
public:
    dMd_HIO_c();
};

#endif /* D_MENU_DMAP_H */
