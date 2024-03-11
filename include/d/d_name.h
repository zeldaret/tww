#ifndef D_NAME_H
#define D_NAME_H

#include "d/d_drawlist.h"

class dNm_HIO_c {
public:
    dNm_HIO_c();
};

class dDlst_NameIN_c : public dDlst_base_c {
    void draw();
};

class dName_c {
public:
    void draw() {}
    void getInputStrPtr() {}
    void isInputEnd() {}
    void setNextNameStr(char*) {}

    virtual ~dName_c() {}
    void _create();
    void initial();
    void _delete();
    void _move();
    void nameCheck();
    void playNameSet(int);
    bool _open();
    bool _close();
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

    /* 0x0004 */ u8 field_0x4[0x0008 - 0x0004];
    /* 0x0008 */ dDlst_NameIN_c field_0x8;
    /* 0x000C */ u8 field_0xc[0x2AD0 - 0x000C];
    /* 0x2AD0 */ char field_0x2ad0[0x2AE8 - 0x2AD0];
};

#endif /* D_NAME_H */
