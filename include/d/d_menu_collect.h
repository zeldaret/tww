#ifndef D_MENU_COLLECT_H
#define D_MENU_COLLECT_H

#include "dolphin/types.h"

struct fopMsgM_pane_class;
class JKRArchive;
class JUTFont;

class dMenu_Collect_c {
public:

    void alphaChange(fopMsgM_pane_class*, float) {}
    void draw() {}
    void getCollectMode() {}
    void getNowItem() {}
    void setArchive(JKRArchive*) {}
    void setFont(JUTFont*, JUTFont*) {}
    void setItemTexBuffer(int, void*) {}
    void setMapTexBuffer(void*) {}
    void setNowItem(unsigned char) {}
    void setOptionArchive(JKRArchive*) {}
    void setQuitArchive(JKRArchive*) {}
    void setSymbolTexBuffer(int, void*) {}
    void setTactTexBuffer(void*) {}
    void setTextArea(char*, char*, char*, char*, char*, char*) {}
    void setTimer(short) {}
    void setTriforceTexBuffer(int, void*) {}
    void setTriggerInfo(unsigned char) {}

    void screenSet();
    void initialize();
    void cursorAnime();
    void stickDirection(unsigned char);
    void cursorMainMove();
    void noteCheck();
    void noteInit();
    void noteAppear();
    void noteOpen();
    void noteClose();
    void mainTrans(float, float);
    void subTrans(float, float);
    void titleTrans(float, float);
    void noteRotate(float, float);
    void nameTrans(float, float);
    void mainOpenProc(short, short, short);
    void subOpenProc(short, short, short);
    void titleOpenProc(short, short);
    void noteOpenProc(short, short);
    void nameOpenProc(short, short);
    void itemBitCheck();
    void itemScale();
    void collectPriority();
    void weponPriority();
    void tactGuideShow(unsigned char, bool);
    void tactDemoMode(unsigned char);
    void tactPlayMode(unsigned char);
    void tactTrans(unsigned char, float, float);
    void tactBaseShow();
    void cornerMove();
    void triforceAnime(unsigned char);
    void tactGuideHide();
    void itemnameMove();
    void itemnameSet();
    void itemnoteSet();
    void itemSet();
    void outFontInit();
    void outFontMove();
    void outFontDraw();
    void collectItemGetCheck(unsigned char);
    void _create();
    void _create3();
    void _delete();
    void _move();
    void _move3();
    void _draw();
    void _open();
    void _open3();
    void _close();
    void _close3();
    void animeStep1(short, short);
    void animeStep2(short, short);
    void animeStep3(short, short);
    void animeStep4(short, short);
    void _open2();
    void _close2();
};

class dMc_HIO_c {
public:
    dMc_HIO_c();
};

#endif /* D_MENU_COLLECT_H */
