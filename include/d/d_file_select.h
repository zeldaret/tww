#ifndef D_S_FILE_SELECT
#define D_S_FILE_SELECT

#include "d/d_drawlist.h"

class dFs_HIO_c {
public:
    dFs_HIO_c();
};

class dDlst_FileSel_c {
public:
    void draw();
};

class dFile_select_c : public dDlst_base_c {
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
    
    dFile_select_c();
    void _create();
    void initial();
    void _delete();
    void _move();
    void _open();
    void _close();
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

private:
    u32 field_0x00[100];
};

#endif
