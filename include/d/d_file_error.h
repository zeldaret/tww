#ifndef D_FILE_ERROR_H
#define D_FILE_ERROR_H

#include "JSystem/J2DGraph/J2DOrthoGraph.h"
#include "JSystem/J2DGraph/J2DPane.h"
#include "JSystem/J2DGraph/J2DScreen.h"
#include "JSystem/J2DGraph/J2DTextBox.h"
#include "JSystem/JKernel/JKRArchive.h"
#include "JSystem/JUtility/JUTFont.h"
#include "d/d_drawlist.h"
#include "d/d_lib.h"
#include "f_op/f_op_msg_mng.h"

class dFe_HIO_c : public JORReflexible {
public:
    dFe_HIO_c();

    virtual ~dFe_HIO_c() {}

    /* 0x004 */ s8 mNo;
    /* 0x005 */ u8 m5;
    /* 0x006 */ s16 m6;
    /* 0x008 */ u8 m8;
    /* 0x009 */ u8 m9;
    /* 0x00a */ u8 ma;
    /* 0x00b */ u8 mb;
    /* 0x00c */ u8 mc;
    /* 0x00d */ u8 md;
    /* 0x00e */ u8 me;
    /* 0x00f */ u8 mf;
    /* 0x010 */ s16 m10;
    /* 0x012 */ s16 m12;
    /* 0x014 */ f32 m14[2];
};

class dDlst_FileErr_c : public dDlst_base_c {
public:
    void draw();

    virtual ~dDlst_FileErr_c() {}

    J2DScreen* Scr;
    JUTFont* font;
};

class MyScreen : public J2DScreen {
public:
    J2DPane* createPane(const J2DPane::J2DScrnBlockHeader&, JSURandomInputStream*, J2DPane*);

    virtual ~MyScreen();
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
    int getLineCount(char*);
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
    int PaneTranceBase(s16, u8, f32, f32, f32, f32, u8, int);
    void _draw();
    void draw2();

    /* 0x004 */ JKRArchive* archive;
    /* 0x008 */ dDlst_FileErr_c fileErr;
    /* 0x014 */ fopMsgM_pane_class msgPanes[13];
    /* 0x04c */ // msgPanes[1]
    /* 0x084 */ // msgPanes[2]
    /* 0x0bc */ // msgPanes[3]
    /* 0x0f4 */ // msgPanes[4]
    /* 0x12c */ // msgPanes[5]
    /* 0x164 */ // msgPanes[6]
    /* 0x19c */ // msgPanes[7]
    /* 0x1d4 */ // msgPanes[8]
    /* 0x20c */ // msgPanes[9]
    /* 0x244 */ // msgPanes[10]
    /* 0x27c */ // msgPanes[11]
    /* 0x2b4 */ // msgPanes[12]
    /* 0x2ec */ char* mMessage;
    /* 0x2f0 */ STControl* stick;
    /* 0x2f4 */ u8 mState;
    /* 0x2f5 */ u8 m2f5;
    /* 0x2f6 */ u8 m2f6;
    /* 0x2f7 */ u8 m2f7;
    /* 0x2f8 */ u8 m2f8;
    /* 0x2f9 */ u8 m2f9;
    /* 0x2fa */ u8 m2fa;
    /* 0x2fb */ u8 m2fb;
    /* 0x2fc */ u8 m2fc;
    /* 0x2fd */ u8 m2fd;
    /* 0x2fe */ s16 m2fe;
    /* 0x300 */ f32 m300;
    /* 0x304 */ f32 mPane0Rotation;
    /* 0x308 */ f32 mPane1Rotation;
};

#endif /* D_FILE_ERROR_H */
