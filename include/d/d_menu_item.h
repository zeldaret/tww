#ifndef D_MENU_ITEM_H
#define D_MENU_ITEM_H

#include "dolphin/types.h"

class fopMsgM_pane_class;
class JKRArchive;
class JUTFont;
class J2DPane;

class dMenu_Item_c {
public:
    void alphaChange(fopMsgM_pane_class*, float) {}
    void draw() {}
    void getItemMode() {}
    void getNowItem() {}
    void setArchive(JKRArchive*) {}
    void setFont(JUTFont*, JUTFont*) {}
    void setItemTexBuffer(int, void*) {}
    void setNowItem(unsigned char) {}
    void setSubItemTexBuffer(int, void*) {}
    void setTextArea(char*, char*, char*, char*, char*, char*) {}
    void setTimer(short) {}
    void setTriggerInfo(unsigned char) {}

    void initialize();
    void screenSet();
    void cursorAnime();
    void cursorMainMove();
    void cursorSubMove();
    void checkMove();
    void itemplaceCheck(int);
    void itemDecide();
    void itemMove();
    void itemScale();
    void subWindowInit();
    void subWindowDelete();
    void subItemDecide();
    void itemnameMove();
    void itemnameSet();
    void itemnoteSet();
    void outFontInit();
    void outFontMove();
    void outFontDraw();
    void noteCheck();
    void noteInit();
    void noteAppear();
    void noteOpen();
    void noteClose();
    void mainTrans(float, float);
    void titleTrans(float, float);
    void noteRotate(float, float);
    void nameTrans(float, float);
    void mainOpenProc(short, short, short);
    void titleOpenProc(short, short);
    void noteOpenProc(short, short);
    void nameOpenProc(short, short);
    void numberSet(J2DPane*, unsigned char);
    void numberColor(J2DPane*, unsigned char);
    void itemNumberSet();
    void itemCheck(int);
    void itemBitCheck(bool);
    void arrowLightAnime();
    void bottleFwaterCheck();
    void recollectBossCheck();
    void cornerMove();
    void equipBeastItem(int);
    void _create();
    void _delete();
    void _move();
    void _draw();
    void _open();
    void _close();
    void _open2();
    void _close2();
};

class dMi_HIO_c {
public:
    dMi_HIO_c();
};


#endif /* D_MENU_ITEM_H */
