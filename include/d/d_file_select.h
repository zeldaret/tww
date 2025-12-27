#ifndef D_S_FILE_SELECT
#define D_S_FILE_SELECT

#include "d/d_drawlist.h"
#include "f_op/f_op_msg_mng.h"
#include "m_Do/m_Do_hostIO.h"
#include "JSystem/J2DGraph/J2DTextBox.h"

class JKRMemArchive;
class STControl;

class dFs_HIO_c : public JORReflexible {
public:
    dFs_HIO_c();
    virtual ~dFs_HIO_c() {}

    void genMessage(JORMContext*) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 field_0x05;
    /* 0x06 */ u8 field_0x06;
    /* 0x07 */ u8 field_0x07;
    /* 0x08 */ u8 field_0x08;
    /* 0x09 */ u8 field_0x09;
    /* 0x0A */ u8 field_0x0A;
    /* 0x0B */ u8 field_0x0B;
    /* 0x0C */ u8 field_0x0C;
    /* 0x0D */ u8 field_0x0D;
    /* 0x0E */ u8 field_0x0E;
    /* 0x0F */ u8 field_0x0F;
    /* 0x10 */ u8 field_0x10;
    /* 0x11 */ u8 field_0x11;
    /* 0x12 */ u8 field_0x12;
    /* 0x13 */ u8 field_0x13;
    /* 0x14 */ u8 field_0x14;
    /* 0x15 */ u8 field_0x15;
    /* 0x16 */ u8 field_0x16;
    /* 0x17 */ u8 field_0x17;
    /* 0x18 */ s16 field_0x18;
    /* 0x1A */ s16 field_0x1A;
    /* 0x1C */ s16 field_0x1C;
    /* 0x1E */ s16 field_0x1E;
    /* 0x20 */ u8 field_0x20;
    /* 0x21 */ u8 field_0x21;
    /* 0x22 */ u8 field_0x22;
    /* 0x23 */ u8 field_0x23;
    /* 0x24 */ u8 field_0x24;
    /* 0x25 */ u8 field_0x25;
    /* 0x26 */ u8 field_0x26;
    /* 0x27 */ u8 field_0x27;
    /* 0x28 */ u8 field_0x28;
    /* 0x29 */ u8 field_0x29;
    /* 0x2A */ u8 field_0x2A;
    /* 0x2B */ u8 field_0x2B;
    /* 0x2C */ u8 field_0x2C;
    /* 0x2D */ u8 field_0x2D;
    /* 0x2E */ u8 field_0x2E;
    /* 0x2F */ u8 field_0x2F;
    /* 0x30 */ u8 field_0x30;
    /* 0x31 */ u8 field_0x31;
    /* 0x32 */ u8 field_0x32;
    /* 0x33 */ u8 field_0x33;
    /* 0x34 */ u8 field_0x34;
    /* 0x35 */ u8 field_0x35;
    /* 0x36 */ u8 field_0x36;
    /* 0x37 */ u8 field_0x37;
    /* 0x38 */ u8 field_0x38;
    /* 0x39 */ u8 field_0x39;
    /* 0x3A */ u8 field_0x3A;
    /* 0x3B */ u8 field_0x3B;
    /* 0x3C */ s16 field_0x3C;
    /* 0x3E */ s16 field_0x3E;
    /* 0x40 */ s16 field_0x40;
    /* 0x42 */ s16 field_0x42;
    /* 0x44 */ s16 field_0x44;
    /* 0x46 */ s16 field_0x46;
    /* 0x48 */ s16 field_0x48;
    /* 0x4A */ s16 field_0x4A;
    /* 0x4C */ s16 field_0x4C;
    /* 0x4E */ u8 field_0x4E;
    /* 0x4F */ u8 field_0x4F;
    /* 0x50 */ u8 field_0x50;
    /* 0x51 */ u8 field_0x51;
    /* 0x52 */ u8 field_0x52;
    /* 0x54 */ float field_0x54;
    /* 0x58 */ float field_0x58;
};

class dDlst_FileSel_c : public dDlst_base_c {
public:
    void draw();

    /* 0x04 */ J2DScreen* Scr;
    /* 0x08 */ JUTFont* font;
};

class dFile_select_c {
public:
    u8 getIconMode() { return mIconMode; }
    void setIconMode(u8 mode) { mIconMode = mode; }
    void setSaveDataPtr(u8* dataPtr) { mSaveDataPtr = dataPtr; }
    void setSavePicDataPtr(u8* dataPtr) { mSavePicDataPtr = dataPtr; }
    void setUseType(u8 useType) { mUseType = useType; }

    void getErrType() {}
    void getSelectNum() {}
    void isDataExtra(u8) {}
    void isDataNew(u8) {}
    void isSelectEnd() {}

    dFile_select_c() {}
    void _create();
    void initial();
#if VERSION == VERSION_DEMO
    void _deleteSp();
#endif
    void _delete();
    void _move();
    bool _open();
    bool _close();
    int closeEnd();
    int closeCardErr();
    int closeBack();
    int closeErrErase();
    int closeErrCopy();
    void dataSelect();
    void menuColorChange();
    void SelectTitAnime();
    void recCursorMove();
    void recCursorAnime();
    void recCursorAlphaInit();
    int recDataPaneMove();
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
    int DataSelectPaneCopyMove(s16, s16);
    int DataSelectPaneCopyBackMove(s16, s16);
    int DataSelectPaneCopyMove2(s16, s16);
    int DataSelectPaneCopyColorMove(s16, u8, int);
    int DataSelectPaneBackFromCopyMove(u8, u8);
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
    int DataSelectPaneBackMove(s16, s16, s16);
    void nextModeWait();
    void screenSet();
    void paneTransInit();
    void menuPaneMoveSet();
    void yesNoPaneMoveSet();
    int MessagePaneMove(f32, f32, f32, f32, s16, u8, int);
    int recInfoPaneMove(f32, f32, f32, f32, s16, u8, int);
    int menuPaneMove(f32, f32, s16, u8, int);
    int yesNoPaneMove(f32, f32, s16, u8, int);
    int PaneTranceTitle(s16, u8, f32, f32, u8, int);
    int PaneAlphaTitleTxt(s16, u8);
    int PaneTranceRecTlt1(s16, u8, f32, f32, f32, f32, u8, int);
    int PaneTranceRecTlt2(s16, u8, f32, f32, f32, f32, u8, int);
    int PaneTranceRecTlt3(s16, u8, f32, f32, f32, f32, u8, int);
    int PaneTranceRecInfo1(s16, u8, f32, f32, f32, f32, u8, int);
    int PaneTranceRecInfo2(s16, u8, f32, f32, f32, f32, u8, int);
    int PaneTranceRecInfo3(s16, u8, f32, f32, f32, f32, u8, int);
    int PaneTranceRecBase(s16, u8, f32, f32, f32, f32, u8, int);
    int PaneTranceMessageBase(s16, u8, f32, f32, f32, f32, u8, int);
    int PaneTranceYes(s16, u8, f32, f32, u8, int);
    int PaneTranceNo(s16, u8, f32, f32, u8, int);
    int PaneTranceStart(s16, u8, f32, f32, u8, int);
    int PaneTranceCopy(s16, u8, f32, f32, u8, int);
    int PaneTranceErase(s16, u8, f32, f32, u8, int);
    int PaneTranceBack(s16, u8, f32, f32, u8, int);
    void displayInit();
    void setSaveData();
    void changeExtraColor(int);
    void changeBrokenColor(int);
    void _draw();
    void dataSelectEx();
    void ExSavePaneMove();
    void YesNoSelectEx();
    void ExSavePaneMove0();
    int ExCardCheck();
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
    /* 0x0080 */ fopMsgM_pane_class field_0x80[2];
    /* 0x00F0 */ fopMsgM_pane_class field_0xf0[2];
    /* 0x0160 */ fopMsgM_pane_class field_0x160;
    /* 0x0198 */ fopMsgM_pane_class field_0x198[2];
    /* 0x0208 */ fopMsgM_pane_class field_0x208[0xC];
    /* 0x04A8 */ fopMsgM_pane_class field_0x4a8[3];
    /* 0x0550 */ fopMsgM_pane_class field_0x550[3];
    /* 0x05f8 */ fopMsgM_pane_class field_0x5f8;
    /* 0x0630 */ fopMsgM_pane_class field_0x630[9];
    /* 0x0828 */ fopMsgM_pane_class field_0x828[0x14];
    /* 0x0C88 */ fopMsgM_pane_class field_0xc88[0x14];
    /* 0x10E8 */ fopMsgM_pane_class field_0x10e8[2];
    /* 0x1158 */ fopMsgM_pane_class field_0x1158[2];
    /* 0x11C8 */ fopMsgM_pane_class field_0x11c8[2];
    /* 0x1238 */ fopMsgM_pane_class field_0x1238[0x10];
    /* 0x15B8 */ fopMsgM_pane_class field_0x15b8[0x10];
    /* 0x1938 */ fopMsgM_pane_class field_0x1938[0x10];
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
    /* 0x38E0 */ J2DTextBox::TFontSize field_0x38e0;
    /* 0x38E8 */ char* field_0x38e8[3];
    /* 0x38F4 */ char* field_0x38f4[3];
    /* 0x3900 */ char* field_0x3900[3];
    /* 0x390C */ STControl* stick;
    /* 0x3910 */ STControl* stick2;
    /* 0x3914 */ u8 field_0x3914[3];
    /* 0x3917 */ u8 field_0x3917[3];
    /* 0x391A */ u8 saveStatus[3];
    /* 0x391D */ u8 field_0x391D[3];
    /* 0x3920 */ u8 field_0x3920;
    /* 0x3921 */ u8 field_0x3921;
    /* 0x3922 */ u8 saveSlot;
    /* 0x3923 */ s8 field_0x3923;
    /* 0x3924 */ u8 field_0x3924;
    /* 0x3925 */ u8 field_0x3925;
    /* 0x3926 */ u8 field_0x3926;
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
    /* 0x3936 */ u8 mIconMode;
    /* 0x3938 */ u8* mSaveDataPtr;
    /* 0x393C */ u8* mSavePicDataPtr;
    /* 0x3940 */ u8 mUseType;
    /* 0x3941 */ u8 field_0x3941;
    /* 0x3942 */ u8 field_0x3942[0x3944 - 0x3942];
    /* 0x3944 */ f32 field_0x3944;
    /* 0x3948 */ f32 field_0x3948;
};

#endif
