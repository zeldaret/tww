#ifndef D_MENU_SAVE_H
#define D_MENU_SAVE_H

#include "d/d_drawlist.h"
#include "dolphin/types.h"

struct fopMsgM_pane_class;

class dDlst_MenuSave_c : public dDlst_base_c {
public:
    ~dDlst_MenuSave_c() {}
    void draw();
};

class dMenu_save_c {
public:
    u8* getDataBufPtr() { return mDataBuf; }
    u8 getEndStatus() { return mEndStatus; }
    u8 getSaveStatus() { return mSaveStatus; }
    void setErrorFlag(u8) {}
    void setErrorType(u8) {}
    void setUseType(u8 useType) { mUseType = useType; }

    virtual ~dMenu_save_c() {}
    void _create();
    void _draw();
    void _draw2();
    void _move();
    bool _open();
    bool _close();
    void _delete();

    void initialize();
    void openNormal();
    void closeNormal();
    void openForCollect();
    void openForItem();
    void closeForCollect();
    void closeForItem();
    void openForGameover();
    void closeForGameover();
    void closeForGameover_1();
    void closeForGameover_2();
    void openForEnding();
    void openForEnding2();
    void closeForEnding();
    void noSave();
    void noSave2();
    void saveQuestion();
    void memCardCheck();
    void openSaveMenu();
    void closeSaveMenu();
    void memCardErrMsgWaitKey();
    void memCardErrMsgWaitKey2();
    void memCardErrMsgWaitKey3();
    void memCardErrGoIPLSel();
    void memCardErrGoIPLSel2();
    void memCardErrMsgWaitFormatSel();
    void memCardErrMsgWaitFormatSel2();
    void memCardFormat();
    void memCardFormatCheck();
    void memCardMakeGameFileSel();
    void memCardMakeGameFile();
    void memCardMakeGameFileCheck();
    void memCardDataLoadWait();
    void memCardDataLoadWait2();
    void memCardDataSave();
    void memCardDataSaveUpMenu();
    void memCardDataSaveSel();
    void memCardDataSaveDownMenu();
    void dataWrite();
    void memCardDataSaveWait();
    void msgWait();
    void msgWait2();
    void saveEndWait();
    void canNotSave();
    void canNotSave2();
    void gameContinue();
    void gameContinue2();
    void gameContinue3();
    void gameContinue4();
    void endingNoSave();
    void endingNoSave2();
    void endingNoSave3();
    void endingDataCheck();
    void saveWait();
    void YesNoSelect(int);
    void YesNoSelect2(int);
    void CursorAlphaInit();
    void CursorMove();
    void CursorAnime();
    void openSave();
    void closeSave();
    void screenSet();
    void paneTransInit();
    void displayInit();
    void initializeEx();
    void menuUp();
    void menuDown();
    void PaneAlphaMsgTxt(s16, u8);
    void PaneTranceBase(s16, u8, f32, f32, u8, int);
    void PaneScaleAlphaWipe(s16, u8, f32, u8, int);
    void PaneAlphaMask(s16, u8, u8, int);
    void PaneTranceTitle(s16, u8, f32, f32, u8, int);
    void PaneRotate(s16, u8, fopMsgM_pane_class*, f32, f32, f32, u8);
    void PaneTranceMenu(s16, u8, fopMsgM_pane_class*, f32, f32, u8, int);

public:
    /* 0x0004 */ u8 field_0x0004;
    /* 0x0008 */ dDlst_MenuSave_c mDlst;
#if VERSION == VERSION_PAL
    // Not 100% sure where these extra bytes go, but it has to be before field_0x0537.
    /* 0x000C */ u8 field_0x000c_pal[0x0038];
#endif
    /* 0x000C */ u8 field_0x000c[0x0524];
    /* 0x0530 */ u8 field_0x0530;
    /* 0x0531 */ u8 mSaveStatus;
    /* 0x0532 */ u8 field_0x0532;
    /* 0x0533 */ u8 field_0x0533;
    /* 0x0534 */ u8 field_0x0534;
    /* 0x0535 */ u8 field_0x0535;
    /* 0x0536 */ u8 field_0x0536;
    /* 0x0537 */ u8 mUseType;
    /* 0x0538 */ u8 mEndStatus;
    /* 0x0539 */ u8 field_0x0539[0x053C - 0x0539];
    /* 0x053C */ u8 field_0x053c;
    /* 0x053D */ u8 field_0x053d;
    /* 0x053E */ u8 field_0x053e[0x0554 - 0x053E];
    /* 0x0554 */ u8 mDataBuf[0x1650];
};  // Size: 0x1BA4

class dMs_HIO_c {
public:
    dMs_HIO_c();
};


#endif /* D_MENU_SAVE_H */
