#ifndef D_NAME_H
#define D_NAME_H

#include "d/d_drawlist.h"
#include "m_Do/m_Do_hostIO.h"
#include "f_op/f_op_msg_mng.h"

class dNm_HIO_c : public JORReflexible {
public:
    dNm_HIO_c();
    virtual ~dNm_HIO_c() {}

    void genMessage(JORMContext* ctx) { /* TODO */ }

    /* 0x04 */ s8 id;
    /* 0x05 */ u8 field_0x5;
    /* 0x06 */ u8 field_0x6;
    /* 0x07 */ u8 field_0x7;
    /* 0x08 */ u8 field_0x8;
    /* 0x09 */ u8 field_0x9;
    /* 0x0A */ u8 field_0xa;
    /* 0x0B */ u8 field_0xb;
    /* 0x0C */ u8 field_0xc;
    /* 0x0D */ u8 field_0xd;
    /* 0x0E */ u8 field_0xe;
    /* 0x0F */ u8 field_0xf;
    /* 0x10 */ u8 field_0x10;
    /* 0x11 */ u8 field_0x11;
    /* 0x12 */ u8 field_0x12;
    /* 0x13 */ u8 field_0x13;
    /* 0x14 */ u8 field_0x14;
    /* 0x15 */ u8 field_0x15;
    /* 0x16 */ u8 field_0x16;
    /* 0x17 */ u8 field_0x17;
    /* 0x18 */ u8 field_0x18;
    /* 0x19 */ u8 field_0x19;
    /* 0x1A */ u8 field_0x1a;
    /* 0x1B */ u8 field_0x1b;
    /* 0x1C */ u8 field_0x1c;
    /* 0x1D */ u8 field_0x1d;
    /* 0x1E */ u8 field_0x1e;
    /* 0x1F */ u8 field_0x1f;
    /* 0x20 */ u8 field_0x20;
    /* 0x21 */ u8 field_0x21;
    /* 0x22 */ u8 field_0x22;
    /* 0x23 */ u8 field_0x23;
    /* 0x24 */ u8 field_0x24[0x26 - 0x24];
    /* 0x26 */ s16 field_0x26;
    /* 0x28 */ s16 field_0x28;
    /* 0x2A */ s16 field_0x2a[3];
    /* 0x30 */ s16 field_0x30[3];
    /* 0x36 */ s16 field_0x36[3];
    /* 0x3C */ s16 field_0x3c[3];
    /* 0x42 */ s16 field_0x42;
    /* 0x44 */ s16 field_0x44;
    /* 0x46 */ s16 field_0x46;
    /* 0x48 */ s16 field_0x48;
};

class J2DScreen;

class dDlst_NameIN_c : public dDlst_base_c {
public:
    virtual ~dDlst_NameIN_c() {}
    void draw();

    /* 0x4 */ J2DScreen* NameInScr;
    /* 0x8 */ JUTFont* font;
};

class STControl;

class ChrInfo_c {
public:
    /* 0x0 */ u8 column;
    /* 0x1 */ u8 row;
    /* 0x2 */ u8 set;
    /* 0x3 */ u8 field_0x3;
    /* 0x4 */ int character;
};

class dName_c {
public:
    enum {
        PROC_MOJI_SELECT,
        PROC_MENU_SELECT,
        PROC_MENU_BUTTON_ANIME,
        PROC_END_WAIT
    };

    enum {
        MOJI_HIRA, // hiragana characters
        MOJI_KATA, // katakana characters
        MOJI_EIGO, // english characters
    };

    enum {
        MENU_HIRA, // (JPN )hiragana menu, (PAL) uppercase menu
        MENU_KATA, // (JPN )katakana menu, (PAL) lowercase menu
#if VERSION < VERSION_PAL
        MENU_EIGO, // english menu
#endif
        MENU_BACKSPACE,
        MENU_END,

        MENU_MAX = 5,
    };

    dName_c() {}
    virtual ~dName_c() {}

    void draw() { _draw(); }
    int isInputEnd() { return isInputEnd_; }
    char* getInputStrPtr() { return inputStr; }
    void setNextNameStr(char* i_name) { strcpy(nextNameStr, i_name); }

    void _create();
    void initial();
    void _delete();
    void _move();
    int nameCheck();
    void playNameSet(int);
    bool _open();
    bool _close();
    void NameInMain();
    void nameCursorAnime();
    void EndWait();
    void MojiSelect();
    int mojiChange(u8);
    void selectMojiSet();
    int getMoji();
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
    int PaneTranceTitle(s16, u8, f32, f32, u8, int);
    int PaneTranceName(s16, u8, f32, f32, u8, int);
    int PaneTranceBase0(s16, u8, f32, f32, u8, int);
    int PaneTranceBase(s16, u8, f32, f32, u8, int);
    int PaneTranceHira(s16, u8, f32, f32, u8, int);
    int PaneTranceKata(s16, u8, f32, f32, u8, int);
    int PaneTranceEisu(s16, u8, f32, f32, u8, int);
    int PaneTranceArrow(s16, u8, f32, f32, u8, int);
    int PaneTranceEnd(s16, u8, f32, f32, u8, int);
    void displayInit();
    void NameStrSet();

    void _deleteSp();

    #if VERSION <= VERSION_JPN
    BOOL checkDakuon(int, u8);
    BOOL setDakuon(int, u8);
    #endif

    /* 0x0004 */ JKRArchive* archive;
    /* 0x0008 */ dDlst_NameIN_c nameIn;
    /* 0x0014 */ fopMsgM_pane_class field_0x14;
    /* 0x004C */ fopMsgM_pane_class eisuMojiPanes[13];
    /* 0x0324 */ fopMsgM_pane_class kataMojiPanes[13];
    /* 0x05FC */ fopMsgM_pane_class hiraMojiPanes[13];
    /* 0x08D4 */ fopMsgM_pane_class field_0x8d4[3];
    /* 0x097C */ fopMsgM_pane_class field_0x97c[5];
    /* 0x0A94 */ fopMsgM_pane_class finBtnPane;
    /* 0x0ACC */ fopMsgM_pane_class field_0xacc[10];
    /* 0x0CFC */ fopMsgM_pane_class field_0xcfc[5];
    /* 0x0E14 */ fopMsgM_pane_class yazBtnPane;
    /* 0x0E4C */ fopMsgM_pane_class field_0xe4c[10];
    /* 0x107C */ fopMsgM_pane_class field_0x107c[5];
    /* 0x1194 */ fopMsgM_pane_class englBtnPane;
    /* 0x11CC */ fopMsgM_pane_class field_0x11cc[10];
    /* 0x13FC */ fopMsgM_pane_class field_0x13fc[5];
    /* 0x1514 */ fopMsgM_pane_class kanaBtnPane;
    /* 0x154C */ fopMsgM_pane_class field_0x154c[10];
    /* 0x177C */ fopMsgM_pane_class field_0x177c[5];
    /* 0x1894 */ fopMsgM_pane_class hiraBtnPane;
    /* 0x18CC */ fopMsgM_pane_class field_0x18cc[10];
    /* 0x1AFC */ fopMsgM_pane_class field_0x1afc[5];
    /* 0x1C14 */ fopMsgM_pane_class namePane;
    /* 0x1C4C */ fopMsgM_pane_class field_0x1c4c;
    /* 0x1C84 */ fopMsgM_pane_class field_0x1c84[5];
    /* 0x1D9C */ fopMsgM_pane_class field_0x1d9c[7];
    /* 0x1F24 */ fopMsgM_pane_class field_0x1f24[7];
    /* 0x20AC */ fopMsgM_pane_class titlePane;
    /* 0x20E4 */ fopMsgM_pane_class field_0x20e4[5];
    /* 0x21FC */ fopMsgM_pane_class field_0x21fc[7];
    /* 0x2384 */ fopMsgM_pane_class field_0x2384[7];
    /* 0x250C */ fopMsgM_pane_class field_0x250c[9];
    /* 0x2704 */ fopMsgM_pane_class field_0x2704[9];
    /* 0x28FC */ STControl* stick;
    /* 0x2900 */ u8 charColumn;
    /* 0x2901 */ u8 charRow;
    /* 0x2902 */ u8 mojiSet;
    /* 0x2903 */ u8 selProc;
    /* 0x2904 */ u8 selMenu;
    /* 0x2905 */ u8 field_0x2905;
    /* 0x2906 */ u8 field_0x2906;
    /* 0x2907 */ u8 curPos;
    /* 0x2908 */ u8 field_0x2908;
    /* 0x2909 */ u8 field_0x2909;
    /* 0x290A */ u8 field_0x290a;
    /* 0x290B */ u8 isInputEnd_;
    /* 0x290C */ u8 prevMojiSet;
    /* 0x290D */ u8 field_0x290d;
    /* 0x290E */ u8 field_0x290E[0x2910 - 0x290E];
    /* 0x2910 */ s16 paneTransTimer;
    /* 0x2912 */ u8 field_0x2912[0x2914 - 0x2912];
    /* 0x2914 */ char nameBuffer[320];
    /* 0x2A54 */ char* pCurTxt;
    /* 0x2A58 */ char* pNameTxt;
    /* 0x2A5C */ char inputStr[20];
    /* 0x2A70 */ ChrInfo_c chrInfo[8];
    /* 0x2AB0 */ u8 field_0x2ab0[MENU_MAX][4];
    /* 0x2AC4 */ f32 field_0x2ac4;
    /* 0x2AC8 */ f32 field_0x2ac8;
    /* 0x2ACC */ f32 field_0x2acc;
    /* 0x2AD0 */ char nextNameStr[20];
    /* 0x2AE4 */ u32 inputCompleteSound;
#if VERSION == VERSION_PAL
    /* 0x2AE8 */ char* field_0x2ae8;
#endif
};

//STATIC_ASSERT(sizeof(dName_c) == 0x2AE8);

#endif /* D_NAME_H */
