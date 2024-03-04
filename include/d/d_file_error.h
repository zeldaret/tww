#ifndef D_FILE_ERROR_H
#define D_FILE_ERROR_H

#include "dolphin/types.h"
#include "JSystem/J2DGraph/J2DPane.h"

class MyScreen {
public:
    void createPane(const J2DPane::J2DScrnBlockHeader&, JSURandomInputStream*, J2DPane*) {}
};

class dFe_HIO_c {
public:
    dFe_HIO_c();
};

class dFile_error_c {
public:
    void getStatus() {}
    void getYesNo() {}
    void setDbgErrMessage(char*, int) {}
    void setTimeCountDownMode() {}
    
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
};

class dDlst_FileErr_c {
public:
    void draw();
};

#endif /* D_FILE_ERROR_H */
