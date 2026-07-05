#ifndef D_MENU_SAVE_H
#define D_MENU_SAVE_H

#include "d/d_drawlist.h"
#include "f_op/f_op_msg_mng.h"
#include "m_Do/m_Do_hostIO.h"

struct fopMsgM_pane_class;

class dDlst_MenuSave_c : public dDlst_base_c {
public:
    ~dDlst_MenuSave_c() {}
    void draw();

    /* 0x4 */ J2DScreen* Scr;
    /* 0x8 */ JUTFont* font;
};

class dFile_error_c;
class STControl;

class dMenu_save_c {
public:
    enum {
        PROC_SAVE_QUESTION,
        PROC_MEMCARD_CHECK,
        PROC_OPEN_SAVE_MENU,
        PROC_CLOSE_SAVE_MENU,
        PROC_MEMCARD_ERR_MSG_WAIT_KEY,
        PROC_MEMCARD_ERR_MSG_WAIT_KEY2,
        PROC_MEMCARD_ERR_MSG_WAIT_KEY3,
        PROC_MEMCARD_ERR_GO_IPL_SEL,
        PROC_MEMCARD_ERR_GO_IPL_SEL2,
        PROC_MEMCARD_FORMAT,
        PROC_MEMCARD_ERR_MSG_WAIT_FORMAT_SEL,
        PROC_MEMCARD_ERR_MSG_WAIT_FORMAT_SEL2,
        PROC_MEMCARD_FORMAT_CHECK,
        PROC_MEMCARD_MAKE_GAME_FILE_SEL,
        PROC_MEMCARD_MAKE_GAME_FILE,
        PROC_MEMCARD_MAKE_GAME_FILE_CHECK,
        PROC_MEMCARD_DATA_LOAD_WAIT,
        PROC_MEMCARD_DATA_LOAT_WAIT2,
        PROC_MEMCARD_DATA_SAVE,
        PROC_MEMCARD_DATA_SAVE_UP_MENU,
        PROC_MEMCARD_DATA_SAVE_SEL,
        PROC_MEMCARD_DATA_SAVE_DOWN_MENU,
        PROC_MEMCARD_DATA_SAVE_WAIT,
        PROC_MSG_WAIT,
        PROC_MSG_WAIT2,
        PROC_SAVE_END_WAIT,
        PROC_SAVE_WAIT,
        PROC_CAN_NOT_SAVE,
        PROC_CAN_NOT_SAVE2,
        PROC_GAME_CONTINUE,
        PROC_GAME_CONTINUE2,
        PROC_GAME_CONTINUE3,
#if VERSION >= VERSION_JPN
        PROC_GAME_CONTINUE4,
#endif
        PROC_ENDING_NO_SAVE,
        PROC_ENDING_NO_SAVE2,
        PROC_ENDING_NO_SAVE3,
        PROC_ENDING_DATA_CHECK,
        PROC_NO_SAVE,
        PROC_NO_SAVE2,
    };

    u8* getDataBufPtr() { return dataBuf; }
    u8 getEndStatus() { return endStatus; }
    u8 getSaveStatus() { return saveStatus; }
    void setErrorFlag(u8) {}
    void setErrorType(u8) {}
    void setUseType(u8 i_useType) { useType = i_useType; }

    virtual ~dMenu_save_c() {}
    void _create();
    void _draw();
    void _draw2();
    void _move();
    bool _open();
    bool _close();
    void _delete();

    void initialize();
    BOOL openNormal();
    BOOL closeNormal();
    BOOL openForCollect();
    BOOL openForItem();
    BOOL closeForCollect();
    BOOL closeForItem();
    BOOL openForGameover();
    BOOL closeForGameover();
    BOOL closeForGameover_1();
    BOOL closeForGameover_2();
    BOOL openForEnding();
    BOOL openForEnding2();
    BOOL closeForEnding();
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
    BOOL YesNoSelect(int);
    BOOL YesNoSelect2(int);
    void CursorAlphaInit();
    void CursorMove();
    void CursorAnime();
    BOOL openSave();
    BOOL closeSave();
    void screenSet();
    void paneTransInit();
    void displayInit();
    void initializeEx();
    BOOL menuUp();
    BOOL menuDown();
    BOOL PaneAlphaMsgTxt(s16, u8);
    BOOL PaneTranceBase(s16, u8, f32, f32, u8, int);
    BOOL PaneScaleAlphaWipe(s16, u8, f32, u8, int);
    BOOL PaneAlphaMask(s16, u8, u8, int);
    BOOL PaneTranceTitle(s16, u8, f32, f32, u8, int);
    BOOL PaneRotate(s16, u8, fopMsgM_pane_class*, f32, f32, f32, u8);
    BOOL PaneTranceMenu(s16, u8, fopMsgM_pane_class*, f32, f32, u8, int);

public:
    /* 0x0004 */ JKRArchive* archive;
    /* 0x0008 */ dDlst_MenuSave_c MenuSave;
    /* 0x0014 */ fopMsgM_pane_class field_0x14[8];
    /* 0x01D4 */ fopMsgM_pane_class field_0x1d4;
    /* 0x020C */ fopMsgM_pane_class field_0x20c[5];
    /* 0x0324 */ fopMsgM_pane_class field_0x324;
    /* 0x035C */ fopMsgM_pane_class field_0x35c;
    /* 0x0394 */ fopMsgM_pane_class field_0x394;
    /* 0x03CC */ fopMsgM_pane_class field_0x3cc;
    /* 0x0404 */ fopMsgM_pane_class field_0x404;
    /* 0x043C */ fopMsgM_pane_class field_0x43c;
    /* 0x0474 */ fopMsgM_pane_class field_0x474;
    /* 0x04AC */ fopMsgM_pane_class field_0x4ac;
    /* 0x04E4 */ fopMsgM_pane_class field_0x4e4;
#if VERSION == VERSION_PAL
    /* 0x051C */ fopMsgM_pane_class field_0x51c_pal;
#endif
    /* 0x051C */ char* field_0x51c[2];
    /* 0x0524 */ dFile_error_c* dFe_c;
    /* 0x0528 */ STControl* stick;
    /* 0x052C */ u8 proc;
    /* 0x052D */ u8 field_0x52d;
    /* 0x052E */ u8 field_0x52e;
    /* 0x052F */ u8 field_0x52f;
    /* 0x0530 */ u8 field_0x530;
    /* 0x0531 */ u8 saveStatus;
    /* 0x0532 */ u8 field_0x532;
    /* 0x0533 */ u8 field_0x533;
    /* 0x0534 */ u8 field_0x534;
    /* 0x0535 */ u8 field_0x535;
    /* 0x0536 */ u8 field_0x536;
    /* 0x0537 */ u8 useType;
    /* 0x0538 */ u8 endStatus;
    /* 0x0539 */ u8 field_0x539;
    /* 0x053A */ u8 field_0x53a;
    /* 0x053B */ u8 field_0x53b;
    /* 0x053C */ u8 field_0x53c;
    /* 0x053D */ u8 field_0x53d;
    /* 0x0540 */ int field_0x540;
    /* 0x0544 */ s16 field_0x544;
    /* 0x0546 */ u8 field_0x546[0x0554 - 0x0546];
    /* 0x0554 */ u8 dataBuf[5712];
};  // Size: 0x1BA4

class dMs_HIO_c : public JORReflexible {
public:
    dMs_HIO_c();
    virtual ~dMs_HIO_c() {}

    /* 0x04 */ s8 id;
    /* 0x05 */ u8 field_0x5;
    /* 0x06 */ u8 field_0x6;
    /* 0x07 */ u8 field_0x7;
    /* 0x08 */ u8 field_0x8;
    /* 0x09 */ u8 field_0x9;
    /* 0x0A */ u8 field_0xa;
    /* 0x0B */ u8 field_0xb;
    /* 0x0C */ s16 field_0xc;
    /* 0x0E */ s16 field_0xe;
    /* 0x10 */ u8 field_0x10;
    /* 0x11 */ u8 field_0x11;
    /* 0x12 */ u8 field_0x12;
    /* 0x13 */ u8 field_0x13;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ u8 field_0x18;
    /* 0x19 */ u8 field_0x19;
    /* 0x1A */ u8 field_0x1a;
    /* 0x1B */ u8 field_0x1b;
    /* 0x1C */ u8 field_0x1c;
    /* 0x1E */ s16 field_0x1e;
    /* 0x20 */ u8 field_0x20;
    /* 0x21 */ u8 field_0x21;
    /* 0x22 */ u8 field_0x22;
    /* 0x23 */ u8 field_0x23;
    /* 0x24 */ u8 field_0x24;
    /* 0x25 */ u8 field_0x25;
    /* 0x26 */ s16 field_0x26;
    /* 0x28 */ u8 field_0x28;
    /* 0x29 */ u8 field_0x29;
    /* 0x2A */ u8 field_0x2a;
    /* 0x2C */ s16 field_0x2c;
    /* 0x2E */ u8 field_0x2e;
};


#endif /* D_MENU_SAVE_H */
