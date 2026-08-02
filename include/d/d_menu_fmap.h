#ifndef D_MENU_FMAP_H
#define D_MENU_FMAP_H

#include "d/d_2dnumber.h"
#include "d/d_drawlist.h"
#include "d/d_lib.h"
#include "dolphin/types.h"
#include "SSystem/SComponent/c_xyz.h"
#include "d/d_menu_fmap2.h"
#include "f_op/f_op_msg_mng.h"

class JUTFont;
class J2DScreen;
class dMenu_FmapSv_c;
struct cursorTable_t;
struct aramCmapDatPat_t {
    u32 m_0x0;
    u32 m_0x4;
};

class dDlst_FMAP_c : public dDlst_base_c {
public:
    virtual ~dDlst_FMAP_c() {}
    virtual void draw();

public:
    /* 0x0004 */ J2DScreen* mScreen;
};

class dMenu_Fmap_c {
public:
    virtual ~dMenu_Fmap_c() {}

    void draw() { _draw(); }
    void getCtCurWX() {}
    void getCtCurWY() {}
    void getCtCurX() {}
    void getCtCurY() {}
    void getCtDispMode() {}
    void getCtFmapZoom() {}
    void getCtZoomGridX() {}
    void getCtZoomGridY() {}
    void lineInter0to1(float, float, float) {}
    void lineInter0to1ForU8(unsigned char, unsigned char, float) {}
    void setCtCurHX(signed char) {}
    void setCtCurHY(signed char) {}
    void setCtCurWX(signed char) {}
    void setCtCurWY(signed char) {}
    void setCtCurX(signed char) {}
    void setCtCurY(signed char) {}
    void setCtDispMode(unsigned char) {}
    void setCtFmapZoom(unsigned char) {}
    void setCtZoomGridX(signed char) {}
    void setCtZoomGridY(signed char) {}
    void setFont(JUTFont* font, JUTFont* rfont) {
        mFont = font;
        mRFont = rfont;
    }
    void setSvPtr(dMenu_FmapSv_c* i_ptr) { mFmapSv = i_ptr; }
    void setTextArea_New(char* name0, char* name1, char* note0, char* note1, char* dummy0, char* dummy1) {
        mTxtName[0] = name0;
        mTxtName[1] = name1;
        mTxtNote[0] = note0;
        mTxtNote[1] = note1;
        mTxtDummy[0] = dummy0;
        mTxtDummy[1] = dummy1;
    }
    void stopWrapBackEmitter() {}
    void stopWrapSpotEmitter(int) {}

    void _create();
    void phantomShipCheck();
    void screenSet();
    void initialize();
    void displayinit();
    void backClothDispInit();
    void calcGetMapCount();
    void dispEndSalvageMark();
    void checkMarkCheck1();
    void checkMarkCheck2();
    void checkMarkCheck3();
    bool isFmapClose();
    void setPaneOnOff(J2DScreen*, unsigned long, bool);
    void childPaneMoveSp(fopMsgM_pane_class*, fopMsgM_pane_class*, float, float, float);
    void selGridMaskAlphaCtrl(short, unsigned char, unsigned char, int);
    void fmapMaskAlphaCtrl(short, unsigned char, unsigned char, int);
    void selCursorInit();
    void selCursorHide();
    void selCursorMove();
    void islandNameChange();
    void changeIslandName(unsigned char);
    void AreaTxtChg();
    void AreaTxtChgFast();
    void salvageGetItemChg();
    void salvageGetItemChange();
    void SalvItmDispChgFast();
    void changeSalvageGetItem(unsigned char);
    void selCursorAnime();
    void zoomCursorInit();
    void zoomCursorAnime();
    void playerPointGridAnimeInit();
    void playerPointGridAnime();
    void setDspWindAngle();
    void windArrowColorAnime();
    void checkMarkAnimeInit();
    void checkMarkAnime();
    void readFmapTexture(const char*);
    void aramCmapDatRead();
    void initCmapDatPnt(aramCmapDatPat_t*);
    void getGridNumToCmapDatPnt(int);
    void setDispIslandPos(signed char, signed char);
    void setIslandPos(fopMsgM_pane_class*, float, float);
    void changeFmapTexture(signed char, signed char);
    void setDspNormalMapLink();
    void setDspLargeMapLink();
    void checkDspLargeMapLink();
    void checkDspLargeMapShip();
    void dispEndSalvageLargeMark();
    void setDspHugeMapLink();
    void dispEndSalvageHugeMark(float, float);
    void checkDspHugeMapLink();
    void checkDspHugeMapShip();
    bool _open();
    bool _close();
    void _close_normalMode();
    void _move();
    void _draw();
    void _delete();
    void FmapProcMain();
    void SelectGrid();
    void zoom1000x1000Init();
    void zoomMapAlphaSet(signed char, signed char, fopMsgM_pane_class*, unsigned char);
    void ZoomGridLv1In();
    void ZoomGridLv1Proc();
    void zoom200x200Init();
    void ZoomGridLv1Out();
    void ZoomGridLv2In();
    void ZoomGridLv2Proc();
    void ZoomGridLv2Out();
    void move_normal();
    void FmapProc();
    void HikakuProc();
    void fmap2Open();
    void fmap2Move();
    void fmap2Close();
    void paneTransBase(short, unsigned char, float, float, unsigned char, int);
    void paneTranceZoomMap(short, unsigned char, float, float, float, float, float, float, unsigned char, int);
    void paneTranceZoomMapAlpah(short, unsigned char, unsigned char, int);
    void paneTranceZoom2Map(short, unsigned char, float, float, float, float, float, float, unsigned char, int);
    void paneAlphaFmapCursor(fopMsgM_pane_class*, short, unsigned char, unsigned char, int);
    void PaneAlphaSelvageItem(short, unsigned char);
    void gShipMarkAnimeInit();
    void gShipMarkAnime();
    bool _open_warpMode();
    void init_warpMode();
    void selCursorMoveWarp();
    void _close_warpMode();
    void moveMain_warpMode();
    void wrapMove();
    void wrapSelWinFadeIn1();
    void wrapSelect();
    void wrapSelWinFadeOut();
    void wrapSelWarp();
    void warpAreaAnime0();
    void paneTranceWarpMsg(fopMsgM_pane_class*, short, unsigned char, float, float, unsigned char, int);
    void paneAlphaWarpMsgBack(short, unsigned char, unsigned char, int);
    void warpSelCursorMove();
    void warpSelCursorAnimeInit();
    void warpSelCursorAnime();
    void getWarpAreaGridX(int);
    void getWarpAreaGridY(int);
    void getWarpAreaNo(const cursorTable_t*);
    void getWarpAreaNoUp(const cursorTable_t*);
    void getWarpAreaNoDown(const cursorTable_t*);
    void getWarpAreaNoLeft(const cursorTable_t*);
    void getWarpAreaNoRight(const cursorTable_t*);
    void getWarpAreaTablePtr(signed char, signed char);
    void areaTextChangeAnimeInit();
    void areaTextChangeAnime();
    void PaneAlphaAreaTxt(short, unsigned char, int);
    void setDspWarpBackCornerColor(float);
    void setWrapBackEmitter(cXyz);
    void setWrapSpotEmitter(int, cXyz);
    bool _open_fishManMode();
    void _close_fishManMode();
    void init_fishManMode();
    void movefishManMode();
    void fmDispArea();
    void fmZoomGridLv1In();
    void fmZoomGridLv2In();
    void islandNameSet(unsigned char);
    void fmMapWrite();
    void fmMapWait();
    void paneAlphaZoom2Map(short, unsigned char, unsigned char, int);
    void fmZoomGridLv2Out();
    void fmZoomGridLv1Out();
    void fmEndWait();
    bool _open_wallPaper();
    u8 getButtonIconMode();

public:
    /* 0x0004 */ u8 padding_0x4[0x18 - 0x4];
    /* 0x0018 */ ResTIMG * mpImg;
    /* 0x001C */ dDlst_FMAP_c mDlst;
    /* 0x0024 */ dMenu_Fmap2_c mFmap2;
    /* 0x2874 */ u8 padding_0x2874[0x2878 - 0x2874];
    /* 0x2878 */ dMenu_FmapSv_c* mFmapSv;
    /* 0x287C */ aramCmapDatPat_t mCmapDatPnt;
    /* 0x2884 */ dDlst_2DOutFont_c* field_0x2884;
    /* 0x2888 */ dDlst_2DOutFont_c* field_0x2888;
    /* 0x288C */ fopMsgM_pane_class mFddmPane;
    /* 0x28C4 */ fopMsgM_pane_class mClPane;
    /* 0x28FC */ fopMsgM_pane_class mCi22Pane;
    /* 0x2934 */ fopMsgM_pane_class mCi21Pane;
    /* 0x296C */ fopMsgM_pane_class mCi32Pane;
    /* 0x29A4 */ fopMsgM_pane_class mCi31Pane;
    /* 0x29DC */ fopMsgM_pane_class mGti1Pane;
    /* 0x2A14 */ fopMsgM_pane_class mGti2Pane;
    /* 0x2A4C */ fopMsgM_pane_class mKk1xPanes[4];
    /* 0x2B2C */ fopMsgM_pane_class mKk2xPanes[4];
    /* 0x2C0C */ fopMsgM_pane_class mKk3xPanes[4];
    /* 0x2CEC */ fopMsgM_pane_class mKk4xPanes[4];
    /* 0x2DCC */ fopMsgM_pane_class mAreaPane;
    /* 0x2E04 */ fopMsgM_pane_class mLnk1Pane;
    /* 0x2E3C */ fopMsgM_pane_class mSpi1Pane;
    /* 0x2E74 */ fopMsgM_pane_class mKkdmPane;
    /* 0x2EAC */ fopMsgM_pane_class mSmskPane;
    /* 0x2EE4 */ fopMsgM_pane_class mLnk2Pane;
    /* 0x2F1C */ fopMsgM_pane_class mSpi2Pane;
    /* 0x2F54 */ fopMsgM_pane_class mTsw1Pane;
    /* 0x2F8C */ fopMsgM_pane_class mR01bPane;
    /* 0x2FC4 */ fopMsgM_pane_class mStm1Pane;
    /* 0x2FFC */ fopMsgM_pane_class mKtx1Pane;
    /* 0x3034 */ fopMsgM_pane_class mKtx2Pane;
    /* 0x306C */ fopMsgM_pane_class mClb2Pane;
    /* 0x30A4 */ fopMsgM_pane_class mClbPane;
    /* 0x30DC */ fopMsgM_pane_class mSc11Pane;
    /* 0x3114 */ fopMsgM_pane_class mSc12Pane;
    /* 0x314C */ fopMsgM_pane_class mSc13Pane;
    /* 0x3184 */ fopMsgM_pane_class mSc14Pane;
    /* 0x31BC */ fopMsgM_pane_class mSc15Pane;
    /* 0x31F4 */ fopMsgM_pane_class mSc16Pane;
    /* 0x322C */ fopMsgM_pane_class mSc17Pane;
    /* 0x3264 */ fopMsgM_pane_class mSc18Pane;
    /* 0x329C */ fopMsgM_pane_class mSc19Pane;
    /* 0x32D4 */ fopMsgM_pane_class mLnk3Pane;
    /* 0x330C */ fopMsgM_pane_class mSpi3Pane;
    /* 0x3344 */ fopMsgM_pane_class mStl1Pane;
    /* 0x337C */ fopMsgM_pane_class mR01gPane;
    /* 0x33B4 */ fopMsgM_pane_class mFmumPane;
    /* 0x33EC */ fopMsgM_pane_class mFmw1Pane;
    /* 0x3424 */ fopMsgM_pane_class mFmw2Pane;
    /* 0x345C */ fopMsgM_pane_class mFmw3Pane;
    /* 0x3494 */ fopMsgM_pane_class mFmw4Pane;
    /* 0x34CC */ fopMsgM_pane_class mFmnPanes[15];
    /* 0x3814 */ fopMsgM_pane_class mClgPane;
    /* 0x384C */ fopMsgM_pane_class mSc2xPanes[7];
    /* 0x39D4 */ fopMsgM_pane_class mR0xPanes[11];
    /* 0x3C3C */ fopMsgM_pane_class mStxxPanes[49];
    /* 0x46F4 */ fopMsgM_pane_class mCk1xPanes[3];
    /* 0x479C */ fopMsgM_pane_class mCk2xPanes[3];
    /* 0x4844 */ fopMsgM_pane_class mCk31Pane;
    /* 0x487C */ fopMsgM_pane_class mCk32Pane;
    /* 0x48B4 */ fopMsgM_pane_class mKr0xPanes[8];
    /* 0x4A74 */ fopMsgM_pane_class mWnd1Pane;
    /* 0x4AAC */ fopMsgM_pane_class mWnd2Pane;
    /* 0x4AE4 */ fopMsgM_pane_class* mMr01Pane;
    /* 0x4AE8 */ u8 padding_0x4AE8[0x4B1C - 0x4AE8];
    /* 0x4B1C */ fopMsgM_pane_class mTxtxPanes[3];
    /* 0x4BC4 */ fopMsgM_pane_class mBt00Pane;
    /* 0x4BFC */ fopMsgM_pane_class mBt01Pane;
    /* 0x4C34 */ fopMsgM_pane_class mBt02Pane;
    /* 0x4C6C */ fopMsgM_pane_class mWts1Pane;
    /* 0x4CA4 */ fopMsgM_pane_class mCc01Pane;
    /* 0x4CDC */ fopMsgM_pane_class mWt1Pane;
    /* 0x4D14 */ fopMsgM_pane_class mWt0Pane;
    /* 0x4D4C */ fopMsgM_pane_class mYs01Pane;
    /* 0x4D84 */ fopMsgM_pane_class mYs00Pane;
    /* 0x4DBC */ fopMsgM_pane_class mYsk0Pane;
    /* 0x4DF4 */ fopMsgM_pane_class mYesPane;
    /* 0x4E2C */ fopMsgM_pane_class mNo01Pane;
    /* 0x4E64 */ fopMsgM_pane_class mNo00Pane;
    /* 0x4E9C */ fopMsgM_pane_class mNok0Pane;
    /* 0x4ED4 */ fopMsgM_pane_class mNoPane;
    /* 0x4F0C */ fopMsgM_pane_class mCur1Pane;
    /* 0x4F44 */ fopMsgM_pane_class mGsPanes[7];
    /* 0x50CC */ STControl* mStControl;
    /* 0x50D0 */ JUTFont* mFont;
    /* 0x50D4 */ JUTFont* mRFont;
    /* 0x50D8 */ J2DPane* mMainWarpPane;
    /* 0x50DC */ J2DPane* mWarpPanes[9];
    /* 0x5100 */ u8 padding_0x5100[0x510C - 0x5100];
    /* 0x510C */ bool mMapClose;
    /* 0x510D */ u8 mSelCursorBufIdx;
    /* 0x510E */ u8 mCursorBufIdx;
    /* 0x510F */ u8 field_0x510F;
    /* 0x5110 */ u8 field_0x5110;
    /* 0x5111 */ u8 field_0x5111;
    /* 0x5112 */ u8 field_0x5112;
    /* 0x5113 */ u8 mMainProcIdx;
    /* 0x5114 */ u8 mFmapProcIdx;
    /* 0x5115 */ u8 mHikakuProcIdx;
    /* 0x5116 */ u16 mFrameTimer;
    /* 0x5118 */ s8 mGridX;
    /* 0x5119 */ s8 mGridY;
    /* 0x511A */ s8 mTargetGridX;
    /* 0x511B */ s8 mTargetGridY;
    /* 0x511C */ cXyz field_0x511C;
    /* 0x5128 */ cXyz field_0x5128;
    /* 0x5134 */ float field_0x5134;
    /* 0x5138 */ float field_0x5138;
    /* 0x513C */ bool mFullMapMode;
    /* 0x513D */ u8 field_0x513D;
    /* 0x513E */ u8 field_0x513E;
    /* 0x513F */ u8 field_0x513F;
    /* 0x5140 */ u8 field_0x5140;
    /* 0x5141 */ u8 field_0x5141;
    /* 0x5142 */ u8 field_0x5142;
    /* 0x5143 */ u8 mWarpAnimTimer;
    /* 0x5144 */ u8 mWarpBlinkToggle;
    /* 0x5145 */ u8 padding_0x5145[0x5148-0x5145];
    /* 0x5148 */ char* mTxtName[3];
    /* 0x5154 */ char* mTxtNote[2];
    /* 0x515C */ char* mTxtDummy[2];
    /* 0x5164 */ bool mWarpScrollGuard;
    /* 0x5165 */ bool mWarpAnimActive;
    /* 0x5166 */ u8 mBlackAlpha;
    /* 0x5167 */ u8 mWhiteAlpha;
    /* 0x5168 */ bool mMapSelectActive;
    /* 0x5169 */ bool mZoomLocked;
    /* 0x516A */ bool mInputDisabled;
    /* 0x516B */ u8 mFmapMode;
    /* 0x516C */ u8 mWarpProcIdx;
    /* 0x516D */ u8 mWarpSubState;
    /* 0x516E */ u8 padding_0x516E[0x5176-0x516E];
    /* 0x5176 */ u8 mFrameCounter;
    /* 0x5177 */ u8 mFishmanProcIdx;
    /* 0x5178 */ u8 mFishmanTimer1;
    /* 0x5179 */ u8 mFishmanTimer2;
    /* 0x517A */ u8 mFishmanTimer3;
    /* 0x517B */ u8 mFishmanMsgTimer;
    /* 0x517C */ u8 mFishmanMsgToggle;
    /* 0x517D */ u8 padding_0x517D[0x517F-0x517D];
    /* 0x517F */ bool mFishmanActive;
    /* 0x5180 */ u8 field_0x5180;
    /* 0x5181 */ u8 field_0x5181;
    /* 0x5182 */ u8 field_0x5182;
    /* 0x5183 */ bool field_0x5183;
    /* 0x5184 */ bool field_0x5184;
    /* 0x5185 */ bool field_0x5185;
    /* 0x5186 */ bool field_0x5186;
    /* 0x5187 */ u8 padding_0x5187[0x518C-0x5187];
    /* 0x518C */ char* mpKtx1String;
    /* 0x5190 */ char* mpKtx2String;
    /* 0x5194 */ JUtility::TColor mCk1Color;
    /* 0x5198 */ JUtility::TColor mCk1Color2;
    /* 0x519C */ JUtility::TColor mKr0Color;
    /* 0x51A0 */ JUtility::TColor mKr0Color2;
    /* 0x51A4 */ JUtility::TColor mYs01Color;
    /* 0x51A8 */ JUtility::TColor mYs01Color2;
    /* 0x51AC */ u8 mMsgValueActive;
    /* 0x51AD */ u8 mMsgValueState1;
    /* 0x51AE */ u8 mMsgValueState2;
    /* 0x51AF */ u8 mMsgValueTimer;
    /* 0x51B0 */ u8 mMsgValueToggle;
    /* 0x51B1 */ u8 padding_0x51B1[0x51B4-0x51B1];
}; // Size: 0x51B4

STATIC_ASSERT(sizeof(dMenu_Fmap_c) == 0x51B4);

class dMf_HIO_c {
public:
    dMf_HIO_c();
    virtual ~dMf_HIO_c() {}

public:
    /* 0x04 */ u8 field_0x04[0x3A - 0x04];
    /* 0x3A */ u8 field_0x3A;
    /* 0x3B */ u8 field_0x3B[0x120 - 0x3B];
};

extern dMf_HIO_c g_mfHIO;

#endif /* D_MENU_FMAP_H */
