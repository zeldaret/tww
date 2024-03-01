#ifndef D_2DNUMBER_H
#define D_2DNUMBER_H

#include "dolphin/types.h"

struct ResTIMG;
class JUTFont;
class fopMsgM_pane_class;

class dDlst_2DNumber_c {
public:
    dDlst_2DNumber_c();
    ~dDlst_2DNumber_c();
    void init(int, s16, s16, s16, s16, u8);
    void draw();
};

class dDlst_2DMinigame_c {
public:
    void init(ResTIMG*, ResTIMG*);
    void draw();
};

class dDlst_2DBattery_c {
public:
    void init(ResTIMG*, ResTIMG*, ResTIMG*, ResTIMG*);
    void setRotate(float);
    void draw();
};

class dDlst_2DObject_c {
public:
    void init(ResTIMG*, ResTIMG*);
    void draw();
};

class dDlst_2DOutFont_c {
public:
    void initial();
    void setPane(JUTFont*, fopMsgM_pane_class*, fopMsgM_pane_class*, fopMsgM_pane_class*, fopMsgM_pane_class*);
    void setPaneEx(JUTFont*, fopMsgM_pane_class*, fopMsgM_pane_class*, fopMsgM_pane_class*, fopMsgM_pane_class*, char*);
    void setRuby(JUTFont*, fopMsgM_pane_class*);
    void setRubyEx(JUTFont*, fopMsgM_pane_class*, char*);
    void charWidth(int);
    void rubyCharWidth(int);
    void iconset(int, char**);
    void messageSet(u32);
    void outFontStickAnime1(u8);
    void outFontStickAnime2(u8, u8);
    void outFontStickAnime3(u8, u8);
    void outFontStickAnimePiece(u8, u8);
    void move();
    void setAlpha(u8);
};

#endif /* D_2DNUMBER_H */
