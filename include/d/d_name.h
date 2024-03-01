#ifndef D_NAME_H
#define D_NAME_H

#include "dolphin/types.h"

class dNm_HIO_c {
public:
    dNm_HIO_c();
};

class dName_c {
public:
    void draw() {}
    void getInputStrPtr() {}
    void isInputEnd() {}
    void setNextNameStr(char*) {}
    
    void _create();
    void initial();
    void _delete();
    void _move();
    void nameCheck();
    void playNameSet(int);
    void _open();
    void _close();
    void NameInMain();
    void nameCursorAnime();
    void EndWait();
    void MojiSelect();
    void mojiChange(u8);
    void selectMojiSet();
    void getMoji();
    void setMoji(int);
    void setNameText();
    void nameCursorMove();
    void selectCursorMove();
    void selectCursorTxtChange();
    void selectCursorAnime();
    void menuCursorPosSet();
    void MenuSelect();
    void MenuButtonAnime();
    void menuAbtnSelect();
    void backSpace();
    void mojiListChange(u8);
    void menuCursorMove();
    void selectCursorPosSet(int);
    void menuCursorAnime();
    void _draw();
    void screenSet();
    void paneTransInit();
    void PaneTranceTitle(s16, u8, f32, f32, u8, int);
    void PaneTranceName(s16, u8, f32, f32, u8, int);
    void PaneTranceBase0(s16, u8, f32, f32, u8, int);
    void PaneTranceBase(s16, u8, f32, f32, u8, int);
    void PaneTranceHira(s16, u8, f32, f32, u8, int);
    void PaneTranceKata(s16, u8, f32, f32, u8, int);
    void PaneTranceEisu(s16, u8, f32, f32, u8, int);
    void PaneTranceArrow(s16, u8, f32, f32, u8, int);
    void PaneTranceEnd(s16, u8, f32, f32, u8, int);
    void displayInit();
    void NameStrSet();
};

class dDlst_NameIN_c {
    void draw();
};

#endif /* D_NAME_H */
