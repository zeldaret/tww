#ifndef D_MENU_OPTION_H
#define D_MENU_OPTION_H

#include "dolphin/types.h"

class fopMsgM_pane_class;
class JKRArchive;
class JUTFont;

class dMenu_Option_c {
public:
    void alphaChange(fopMsgM_pane_class*, float) {}
    void getQuitStatus() {}
    void setArchive(JKRArchive*) {}
    void setFont(JUTFont*, JUTFont*) {}
    void setTextArea(char*, char*, char*, char*) {}

    void screenSet();
    void mainInit();
    void noteInit();
    void titleInit();
    void mainMove();
    void noteMove();
    void titleMove();
    void cursorMove();
    void cursorScale();
    void typeMove();
    void yazAnime();
    void ccAnime();
    void stickMove(unsigned char);
    void noteSet();
    void outFontInit();
    void outFontMove();
    void outFontDraw();
    void stringlength(fopMsgM_pane_class*, char*);
    void changeScaleCenter(fopMsgM_pane_class*, char*);
    void setSoundMode(unsigned long);
    void changeScaleRight(fopMsgM_pane_class*, char*);
    void initialize();
    void _create();
    void _delete();
    void _move();
    void _draw();
    void _open();
    void _close();
};

class dMo_HIO_c {
public:
    dMo_HIO_c();
};


#endif /* D_MENU_OPTION_H */
