#ifndef D_S_FILE_SELECT
#define D_S_FILE_SELECT

#include "d/d_drawlist.h"
#include "f_op/f_op_msg_mng.h"

class JKRMemArchive;
class STControl;

class dFs_HIO_c {
public:
    dFs_HIO_c();
};

class dDlst_FileSel_c : public dDlst_base_c {
public:
    void draw();

    /* 0x04 */ J2DScreen* Scr;
    /* 0x08 */ JUTFont* font;
};

class dFile_select_c {
public:
    void getErrType() {}
    void getIconMode() {}
    void getSelectNum() {}
    void isDataExtra(u8) {}
    void isDataNew(u8) {}
    void isSelectEnd() {}
    void setIconMode(u8) {}
    void setSaveDataPtr(u8*) {}
    void setSavePicDataPtr(u8*) {}
    void setUseType(u8) {}

    dFile_select_c() {}
    void _create();
    void initial();
    void _delete();
    void _move();
    bool _open();
    bool _close();
    void closeEnd();
    void closeCardErr();
    void closeBack();
    void closeErrErase();
    void closeErrCopy();
    void dataSelect();
    void menuColorChange();
    void SelectTitAnime();
    void recCursorMove();
    void recCursorAnime();
    void recCursorAlphaInit();
    void recDataPaneMove();
    void dataSelMoveSet();
    void makeRecInfo(u8);
    void dataSelectPaneMove();
    void MessagePaneMoveSet(f32, f32, f32, f32, u8, int);
    void menuSelect();
    void menuCursorAlphaInit();
    void menuCursorMove();
    void menuCursorAnime();
    void ToCopyPaneMove();
    void ToErasePaneMove();
    void ToBackPaneMove();
    void copyDataToSelect();
    void copyDataSelAnime();
    void cptCursorMove();
    void copyToSelBack();
    void copyToSelPaneMove();
    void copyPaneMoveOk();
    void copyPaneMoveOk2();
    void saveCopyBWColor();
    void DataSelectPaneCopyMove(s16, s16);
    void DataSelectPaneCopyBackMove(s16, s16);
    void DataSelectPaneCopyMove2(s16, s16);
    void DataSelectPaneCopyColorMove(s16, u8, int);
    void DataSelectPaneBackFromCopyMove(u8, u8);
    void YesNoSelect();
    void yesNoCursorMove();
    void CmdExecPaneMove0();
    void CmdExecPaneMove2();
    void CommandExec();
    void DataEraseWait();
    void DataCopyWait();
    void ErasePaneMoveOk();
    void ErasePaneMoveOk2();
    void ErrorMsgPaneMove();
    void ErrorMsgPaneMove2();
    void backDatSelPaneMove();
    void backDatSelWait();
    void backDatSelWait2();
    void DataSelectPaneBackMove(s16, s16, s16);
    void nextModeWait();
    void screenSet();
    void paneTransInit();
    void menuPaneMoveSet();
    void yesNoPaneMoveSet();
    void MessagePaneMove(f32, f32, f32, f32, s16, u8, int);
    void recInfoPaneMove(f32, f32, f32, f32, s16, u8, int);
    void menuPaneMove(f32, f32, s16, u8, int);
    void yesNoPaneMove(f32, f32, s16, u8, int);
    void PaneTranceTitle(s16, u8, f32, f32, u8, int);
    void PaneAlphaTitleTxt(s16, u8);
    void PaneTranceRecTlt1(s16, u8, f32, f32, f32, f32, u8, int);
    void PaneTranceRecTlt2(s16, u8, f32, f32, f32, f32, u8, int);
    void PaneTranceRecTlt3(s16, u8, f32, f32, f32, f32, u8, int);
    void PaneTranceRecInfo1(s16, u8, f32, f32, f32, f32, u8, int);
    void PaneTranceRecInfo2(s16, u8, f32, f32, f32, f32, u8, int);
    void PaneTranceRecInfo3(s16, u8, f32, f32, f32, f32, u8, int);
    void PaneTranceRecBase(s16, u8, f32, f32, f32, f32, u8, int);
    void PaneTranceMessageBase(s16, u8, f32, f32, f32, f32, u8, int);
    void PaneTranceYes(s16, u8, f32, f32, u8, int);
    void PaneTranceNo(s16, u8, f32, f32, u8, int);
    void PaneTranceStart(s16, u8, f32, f32, u8, int);
    void PaneTranceCopy(s16, u8, f32, f32, u8, int);
    void PaneTranceErase(s16, u8, f32, f32, u8, int);
    void PaneTranceBack(s16, u8, f32, f32, u8, int);
    void displayInit();
    void setSaveData();
    void changeExtraColor(int);
    void changeBrokenColor(int);
    void _draw();
    void dataSelectEx();
    void ExSavePaneMove();
    void YesNoSelectEx();
    void ExSavePaneMove0();
    void ExCardCheck();
    void ExBackDatSelPaneMove();
    void ExSavePaneMove1();
    void ExDataSave();
    void ExDataSaveWait();
    void ExDataSavePaneMoveOk();
    void ExDataSavePaneMoveOk2();
    void ExErrorMsgPaneMove();
    void ExErrorMsgPaneMove2();

public:
    /* 0x0000 */ JKRMemArchive* field_0x0;
    /* 0x0004 */ dDlst_FileSel_c fileSel;
    /* 0x0010 */ fopMsgM_pane_class field_0x10;
    /* 0x0048 */ fopMsgM_pane_class field_0x48;
    /* 0x0080 */ fopMsgM_pane_class field_0x80;
    /* 0x00B8 */ fopMsgM_pane_class field_0xb8;
    /* 0x00F0 */ fopMsgM_pane_class field_0xf0;
    /* 0x0128 */ fopMsgM_pane_class field_0x128;
    /* 0x0160 */ fopMsgM_pane_class field_0x160;
    /* 0x0198 */ fopMsgM_pane_class field_0x198;
    /* 0x01D0 */ fopMsgM_pane_class field_0x1d0;
    /* 0x0208 */ fopMsgM_pane_class field_0x208[12];
    /* 0x04A8 */ fopMsgM_pane_class field_0x4a8;
    /* 0x04E0 */ fopMsgM_pane_class field_0x4e0;
    /* 0x0518 */ fopMsgM_pane_class field_0x518;
    /* 0x0550 */ fopMsgM_pane_class field_0x550;
    /* 0x0588 */ fopMsgM_pane_class field_0x588;
    /* 0x05c0 */ fopMsgM_pane_class field_0x5c0;
    /* 0x05f8 */ fopMsgM_pane_class field_0x5f8;
    /* 0x0630 */ fopMsgM_pane_class field_0x630[9];
    /* 0x0828 */ fopMsgM_pane_class field_0x828[20];
    /* 0x0C88 */ fopMsgM_pane_class field_0xc88[20];
    /* 0x10E8 */ fopMsgM_pane_class field_0x10e8;
    /* 0x1120 */ fopMsgM_pane_class field_0x1120;
    /* 0x1158 */ fopMsgM_pane_class field_0x1158;
    /* 0x1190 */ fopMsgM_pane_class field_0x1190;
    /* 0x11C8 */ fopMsgM_pane_class field_0x11c8;
    /* 0x1200 */ fopMsgM_pane_class field_0x1200;
    /* 0x1238 */ fopMsgM_pane_class field_0x1238[16];
    /* 0x15B8 */ fopMsgM_pane_class field_0x15b8[16];
    /* 0x1938 */ fopMsgM_pane_class field_0x1938[16];
    /* 0x1CB8 */ fopMsgM_pane_class field_0x1cb8[29];
    /* 0x2310 */ fopMsgM_pane_class field_0x2310[29];
    /* 0x2968 */ fopMsgM_pane_class field_0x2968[29];
    /* 0x2FC0 */ fopMsgM_pane_class field_0x2fc0[5];
    /* 0x30D8 */ fopMsgM_pane_class field_0x30d8;
    /* 0x3110 */ fopMsgM_pane_class field_0x3110;
    /* 0x3148 */ fopMsgM_pane_class field_0x3148;
    /* 0x3180 */ fopMsgM_pane_class field_0x3180;
    /* 0x31B8 */ fopMsgM_pane_class field_0x31b8;
    /* 0x31F0 */ fopMsgM_pane_class field_0x31f0;
    /* 0x3228 */ fopMsgM_pane_class field_0x3228;
    /* 0x3260 */ fopMsgM_pane_class field_0x3260;
    /* 0x3298 */ fopMsgM_pane_class field_0x3298;
    /* 0x32D0 */ fopMsgM_pane_class field_0x32d0;
    /* 0x3308 */ fopMsgM_pane_class field_0x3308;
    /* 0x3340 */ fopMsgM_pane_class field_0x3340;
    /* 0x3378 */ fopMsgM_pane_class field_0x3378;
    /* 0x33B0 */ fopMsgM_pane_class field_0x33b0;
    /* 0x33E8 */ fopMsgM_pane_class field_0x33e8;
    /* 0x3420 */ fopMsgM_pane_class field_0x3420;
    /* 0x3458 */ fopMsgM_pane_class field_0x3458;
    /* 0x3490 */ fopMsgM_pane_class field_0x3490;
    /* 0x34C8 */ fopMsgM_pane_class field_0x34c8;
    /* 0x3500 */ fopMsgM_pane_class field_0x3500;
    /* 0x3538 */ fopMsgM_pane_class field_0x3538;
    /* 0x3570 */ fopMsgM_pane_class field_0x3570;
    /* 0x35A8 */ fopMsgM_pane_class field_0x35a8;
    /* 0x35E0 */ fopMsgM_pane_class field_0x35e0;
    /* 0x3618 */ fopMsgM_pane_class field_0x3618;
    /* 0x3650 */ fopMsgM_pane_class field_0x3650;
    /* 0x3688 */ fopMsgM_pane_class field_0x3688;
    /* 0x36C0 */ fopMsgM_pane_class field_0x36c0;
    /* 0x36F8 */ fopMsgM_pane_class field_0x36f8;
    /* 0x3730 */ fopMsgM_pane_class field_0x3730;
    /* 0x3768 */ fopMsgM_pane_class field_0x3768;
    /* 0x37A0 */ fopMsgM_pane_class field_0x37a0;
    /* 0x37D8 */ JUtility::TColor field_0x37d8[11];
    /* 0x3804 */ JUtility::TColor field_0x3804[11];
    /* 0x3830 */ JUtility::TColor field_0x3830[18];
    /* 0x3878 */ JUtility::TColor field_0x3878[18];
    /* 0x38C0 */ JUtility::TColor field_0x38c0[2];
    /* 0x38C8 */ JUtility::TColor field_0x38c8[2];
    /* 0x38D0 */ JUtility::TColor field_0x38d0[2];
    /* 0x38D8 */ JUtility::TColor field_0x38d8[2];
    /* 0x38E0 */ f32 field_0x38e0;
    /* 0x38E4 */ f32 field_0x38e4;
    /* 0x38D8 */ char* field_0x38e8[3];
    /* 0x38F4 */ char* field_0x38f4;
    /* 0x38F8 */ char* field_0x38f8;
    /* 0x38FC */ char* field_0x38fc;
    /* 0x3900 */ char* field_0x3900;
    /* 0x3904 */ char* field_0x3904;
    /* 0x3908 */ char* field_0x3908;
    /* 0x390C */ STControl* stick;
    /* 0x3910 */ STControl* stick2;
    /* 0x3914 */ u8 field_0x3914[0x3921 - 0x3914];
    /* 0x3921 */ u8 field_0x3921;
    /* 0x3922 */ u8 field_0x3922;
    /* 0x3923 */ u8 field_0x3923;
    /* 0x3924 */ u8 field_0x3924[0x3927 - 0x3924];
    /* 0x3927 */ u8 field_0x3927;
    /* 0x3928 */ u8 field_0x3928;
    /* 0x3929 */ u8 field_0x3929;
    /* 0x392A */ u8 field_0x392a;
    /* 0x392B */ u8 field_0x392b;
    /* 0x392C */ u8 field_0x392c;
    /* 0x392D */ u8 field_0x392d;
    /* 0x392E */ u8 field_0x392e;
    /* 0x392F */ u8 field_0x392f;
    /* 0x3930 */ s16 field_0x3930;
    /* 0x3932 */ s16 field_0x3932;
    /* 0x3934 */ u8 field_0x3934[0x3936 - 0x3934];
    /* 0x3936 */ u8 field_0x3936;
    /* 0x3938 */ void* field_0x3938;
    /* 0x393C */ void* field_0x393c;
    /* 0x3940 */ u8 field_0x3940;
    /* 0x3941 */ u8 field_0x3941;
    /* 0x3942 */ u8 field_0x3942[0x3948 - 0x3942];
    /* 0x3948 */ f32 field_0x3948;
};

#endif
