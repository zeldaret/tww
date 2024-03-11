#ifndef D_FILE_ERROR_H
#define D_FILE_ERROR_H

#include "d/d_drawlist.h"

class MyScreen {
public:
    void createPane(const J2DPane::J2DScrnBlockHeader&, JSURandomInputStream*, J2DPane*) {}
};

class dFe_HIO_c {
public:
    dFe_HIO_c();
};

class dDlst_FileErr_c : public dDlst_base_c {
public:
    void draw();
};

class dFile_error_c {
public:
    void getStatus() {}
    void getYesNo() {}
    void setDbgErrMessage(char*, int) {}
    void setTimeCountDownMode() {}

    virtual ~dFile_error_c() {}
    void _create();
    void initial();
    void _delete();
    void setErrMessage(u32, int);
    void closeMessage();
    void resizeMsgBoard(int);
    void setMessage(char*);
    void getLineCount(char*);
    void _move();
    void ProcWait();
    void ShowMsgBoard();
    void ynCursorInit();
    void HideMsgBoard();
    void msgDispWait();
    void yesNoSelectWait();
    void ynCursorMove();
    void ynCursorAnime();
    void screenSet();
    void paneTransInit();
    void displayInit();
    void PaneTranceBase(s16, u8, f32, f32, f32, f32, u8, int);
    void _draw();
    void draw2();

    /* 0x004 */ u8 field_0x4[0x008 - 0x004];
    /* 0x008 */ dDlst_FileErr_c field_0x8;
    /* 0x00C */ u8 field_0xc[0x30C - 0x00C];
};

#endif /* D_FILE_ERROR_H */
