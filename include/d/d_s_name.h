#ifndef D_S_NAME
#define D_S_NAME

#include "d/d_drawlist.h"
#include "f_op/f_op_msg_mng.h"
#include "f_op/f_op_scene.h"
#include "m_Do/m_Do_MemCardRWmng.h"
#include "m_Do/m_Do_hostIO.h"

class J2DScreen;
class JKRMemArchive;
class dFile_error_c;
class dFile_select_c;
class dMenu_save_c;
class dMCloth_c;
class dName_c;
class mDoDvdThd_toMainRam_c;

class dSn_HIO_c : public JORReflexible {
public:
    dSn_HIO_c();
    virtual ~dSn_HIO_c() {}

    void genMessage(JORMContext* ctx);

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 field_0x5;
    /* 0x06 */ u8 field_0x6;
    /* 0x07 */ u8 field_0x7;
    /* 0x08 */ u8 field_0x8;
    /* 0x09 */ u8 field_0x9;
    /* 0x0A */ u8 field_0xa;
    /* 0x0B */ u8 field_0xb;
    /* 0x0C */ s16 field_0xc;
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
};

class dDlst_BTICN_c : public dDlst_base_c {
public:
    ~dDlst_BTICN_c() {}
    void draw();

    /* 0x04 */ J2DScreen* scr;
};

class dDlst_FLSEL_CLOTH_c : public dDlst_base_c {
public:
    ~dDlst_FLSEL_CLOTH_c() {}
    void draw();

    /* 0x04 */ dMCloth_c* cloth_c;
};

class dScnName_c : public scene_class {
public:
    ~dScnName_c();
    cPhs_State create();
    void cloth_create();
    void cloth_move();
    void cloth2D_create();
    void buttonIconCreate();
    BOOL paneTransButtonIcon(s16, u8, f32, f32, u8);
    BOOL execute();
    void setView();
    BOOL draw();
    void MemCardCheckMain();
    void MemCardStatCheck();
    void MemCardLoadWait();
    void MemCardErrMsgWaitKey();
    void MemCardErrMsgWaitKey2();
    void MemCardGotoIPLSelect();
    void MemCardGotoIPL();
    void MemCardErrMsgWaitNoSaveSel();
    void MemCardErrMsgWaitFormatSel();
    void MemCardErrMsgWaitFormatSel2();
    void MemCardFormat();
    void MemCardFormatCheck();
    void MemCardMakeGameFileSel();
    void MemCardMakeGameFile();
    void MemCardMakeGameFileCheck();
    void MemCardGotoFileSelect();
    void MemCardCheckDbg();
    void MemCardCheckDbgWait();
    void FileErrorDraw();
    void NoteOpen();
    void NoteOpenWait();
    void FileSelectOpen();
    void buttonIconProc();
    void FileSelOpenMain();
    void FileselOpenWait();
    void FileSelectMain();
    void FileSelectMainNormal();
    void FileSelectMainExSave();
    void ResetWait();
    void FileSelectClose();
    void FileSelectDraw();
    void NameInOpen();
    void NameOpenMain();
    void NameOpenWait();
    void NameInMain();
    void NameInClose();
    void NameInDraw();
    void ShopDemoDataLoad();
    void ShopDemoDataSet();
    void SaveOpen();
    void SaveMain();
    void SaveClose();
    void SaveDraw();
    void NoneDraw();
    void changeGameScene();

    /* 0x01C4 */ request_of_phase_process_class mPhs;
    /* 0x01CC */ JKRHeap* heap;
    /* 0x01D0 */ JKRHeap* oldHeap;
    /* 0x01D4 */ u8 field_0x1d4[0x29C - 0x1D4];
    /* 0x029C */ f32 field_0x29c;
    /* 0x02A0 */ f32 field_0x2a0;
    /* 0x02A4 */ f32 field_0x2a4;
    /* 0x02A8 */ f32 field_0x2a8;
    /* 0x02AC */ Vec field_0x2ac;
    /* 0x02B8 */ Vec field_0x2b8;
    /* 0x02C4 */ u8 field_0x2c4[0x2D0 - 0x2C4];
    /* 0x02D0 */ s16 field_0x2d0;
    /* 0x02D4 */ Mtx44 field_0x2d4;
    /* 0x0314 */ Mtx field_0x314;
    /* 0x0344 */ Mtx field_0x344;
    /* 0x0374 */ Mtx field_0x374;
    /* 0x03A4 */ u8 field_0x3a4[0x3B4 - 0x3A4];
    /* 0x03B4 */ Mtx field_0x3b4;
    /* 0x03E4 */ u8 field_0x3e4[0x40C - 0x3E4];
    /* 0x040C */ JKRMemArchive* mArchive;
    /* 0x0410 */ mDoDvdThd_toMainRam_c* field_0x410;
    /* 0x0414 */ dDlst_BTICN_c btnIcon;
    /* 0x041C */ dDlst_FLSEL_CLOTH_c cloth;
    /* 0x0424 */ dName_c* dNm_c;
    /* 0x0428 */ dFile_select_c* dFs_c;
    /* 0x042C */ dFile_error_c* dFe_c;
    /* 0x0430 */ dMenu_save_c* dMs_c;
    /* 0x0434 */ u8 field_0x434[0x43C - 0x434];
    /* 0x043C */ fopMsgM_pane_class field_0x43c;
    /* 0x0474 */ fopMsgM_pane_class field_0x474;
    /* 0x04AC */ fopMsgM_pane_class field_0x4ac;
    /* 0x04E4 */ fopMsgM_pane_class field_0x4e4;
    /* 0x051C */ fopMsgM_pane_class field_0x51c;
    /* 0x0554 */ u8 mMainProc;
    /* 0x0555 */ u8 field_0x555;
    /* 0x0556 */ u8 field_0x556;
    /* 0x0557 */ u8 mDrawProc;
    /* 0x0558 */ u8 field_0x558;
    /* 0x0559 */ u8 field_0x559;
    /* 0x055A */ u8 field_0x55a;
    /* 0x055B */ u8 field_0x55b;
    /* 0x055C */ u8 field_0x55c;
    /* 0x055D */ u8 field_0x55d;
    /* 0x055E */ u8 field_0x55e;
    /* 0x055F */ u8 field_0x55f;
    /* 0x0560 */ u8 saveMemory[3 * sizeof(card_gamedata)];
    /* 0x1BB0 */ card_pictdata* savePicDatabuf;
    /* 0x1BB4 */ s16 field_0x1bb4;
    /* 0x1BB6 */ u8 field_0x1bb6;
    /* 0x1BB7 */ u8 field_0x1bb7;
    /* 0x1BB8 */ u8 field_0x1bb8;
    /* 0x1BB9 */ u8 field_0x1bb9;
    /* 0x1BBA */ u8 field_0x1bba[0x1BBC - 0x1BBA];
    /* 0x1BBC */ int field_0x1bbc;
};

extern dSn_HIO_c g_snHIO;

#endif /* D_S_NAME */
