#ifndef D_MENU_FMAP_H
#define D_MENU_FMAP_H

#include "d/d_2dnumber.h"
#include "d/d_drawlist.h"
#include "d/d_lib.h"
#include "d/d_menu_fmapSv.h"
#include "dolphin/types.h"
#include "JSystem/JParticle/JPAEmitter.h"
#include "SSystem/SComponent/c_xyz.h"
#include "d/d_menu_fmap2.h"
#include "f_op/f_op_msg_mng.h"
#include "m_Do/m_Do_hostIO.h"

class JUTFont;
class J2DScreen;

struct cursorTable_t {
    /* 0x0 */ s8 gridX;
    /* 0x1 */ s8 gridY;
    /* 0x2 */ s8 no;
    /* 0x3 */ s8 left;
    /* 0x4 */ s8 right;
    /* 0x5 */ s8 up;
    /* 0x6 */ s8 down;
};

enum dMf_DispMode {
    FMAP_DISP_NORMAL = 0,
    FMAP_DISP_HIKAKU = 1,
};

enum dMf_Mode {
    FMAP_MODE_NORMAL    = 0,
    FMAP_MODE_WARP      = 1,
    FMAP_MODE_WALLPAPER = 2,
    FMAP_MODE_FISHMAN   = 3,
};

enum dMf_ButtonIconMode {
    FMAP_BTN_ICON_WORLD     = 0,
    FMAP_BTN_ICON_SECTOR    = 1,
    FMAP_BTN_ICON_DETAIL    = 2,
    FMAP_BTN_ICON_LOCKED    = 3,
    FMAP_BTN_ICON_WARP      = 4,
    FMAP_BTN_ICON_WALLPAPER = 5,
    FMAP_BTN_ICON_FISHMAN   = 6,
};

class dDlst_FMAP_c : public dDlst_base_c {
public:
    virtual ~dDlst_FMAP_c() {}
    virtual void draw();

public:
    /* 0x0004 */ J2DScreen* scrn;
};

class dMenu_Fmap_c {
public:
    virtual ~dMenu_Fmap_c() {}

    void draw() { _draw(); }
    u8 getCtDispMode() {
        JUT_ASSERT(467, fmapSv != NULL);
        return fmapSv->dispMode;
    }
    void setCtDispMode(u8 val) {
        JUT_ASSERT(472, fmapSv != NULL);
        fmapSv->dispMode = val;
    }
    u8 getCtFmapZoom() {
        JUT_ASSERT(478, fmapSv != NULL);
        return fmapSv->fmapZoom;
    }
    void setCtFmapZoom(u8 val) {
        JUT_ASSERT(483, fmapSv != NULL);
        fmapSv->fmapZoom = val;
    }
    s8 getCtCurX() {
        JUT_ASSERT(489, fmapSv != NULL);
        return fmapSv->curX;
    }
    void setCtCurX(s8 val) {
        JUT_ASSERT(494, fmapSv != NULL);
        fmapSv->curX = val;
    }
    s8 getCtCurY() {
        JUT_ASSERT(500, fmapSv != NULL);
        return fmapSv->curY;
    }
    void setCtCurY(s8 val) {
        JUT_ASSERT(505, fmapSv != NULL);
        fmapSv->curY = val;
    }
    s8 getCtCurWX() {
        JUT_ASSERT(511, fmapSv != NULL);
        return fmapSv->curWX;
    }
    void setCtCurWX(s8 val) {
        JUT_ASSERT(516, fmapSv != NULL);
        fmapSv->curWX = val;
    }
    s8 getCtCurWY() {
        JUT_ASSERT(522, fmapSv != NULL);
        return fmapSv->curWY;
    }
    void setCtCurWY(s8 val) {
        JUT_ASSERT(527, fmapSv != NULL);
        fmapSv->curWY = val;
    }
    s8 getCtZoomGridX() {
        JUT_ASSERT(533, fmapSv != NULL);
        return fmapSv->zoomGridX;
    }
    void setCtZoomGridX(s8 val) {
        JUT_ASSERT(538, fmapSv != NULL);
        fmapSv->zoomGridX = val;
    }
    s8 getCtZoomGridY() {
        JUT_ASSERT(543, fmapSv != NULL);
        return fmapSv->zoomGridY;
    }
    void setCtZoomGridY(s8 val) {
        JUT_ASSERT(548, fmapSv != NULL);
        fmapSv->zoomGridY = val;
    }
    void setCtCurHX(s8 val) {
        JUT_ASSERT(559, fmapSv != NULL);
        fmapSv->curHX = val;
    }
    void setCtCurHY(s8 val) {
        JUT_ASSERT(569, fmapSv != NULL);
        fmapSv->curHY = val;
    }
    void lineInter0to1(f32, f32, f32) {}
    void lineInter0to1ForU8(u8, u8, f32) {}
    void setFont(JUTFont* font, JUTFont* rfont) {
        mFont = font;
        mRFont = rfont;
    }
    void setSvPtr(dMenu_FmapSv_c* i_ptr) { fmapSv = i_ptr; }
    void setTextArea_New(char* name0, char* name1, char* note0, char* note1, char* dummy0, char* dummy1) {
        mTxtName[0] = name0;
        mTxtName[1] = name1;
        mTxtNote[0] = note0;
        mTxtNote[1] = note1;
        mTxtDummy[0] = dummy0;
        mTxtDummy[1] = dummy1;
    }
    void stopWrapBackEmitter() {
        if (mMainWarpPane != NULL) {
            mMainWarpPane->becomeInvalidEmitter();
        }
    }
    void stopWrapSpotEmitter(int i_idx) {
        if (mWarpPanes[i_idx] != NULL) {
            mWarpPanes[i_idx]->becomeInvalidEmitter();
        }
    }

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
    void setPaneOnOff(J2DScreen*, u32, bool);
    void childPaneMoveSp(fopMsgM_pane_class*, fopMsgM_pane_class*, f32, f32, f32);
    BOOL selGridMaskAlphaCtrl(short, u8, u8, int);
    BOOL fmapMaskAlphaCtrl(short, u8, u8, int);
    void selCursorInit();
    void selCursorHide();
    void selCursorMove();
    void islandNameChange();
    void changeIslandName(u8);
    void AreaTxtChg();
    void AreaTxtChgFast();
    void salvageGetItemChg();
    void salvageGetItemChange();
    void SalvItmDispChgFast();
    void changeSalvageGetItem(u8);
    void selCursorAnime();
    void zoomCursorInit();
    void zoomCursorAnime();
    void playerPointGridAnimeInit();
    void playerPointGridAnime();
    void setDspWindAngle();
    void windArrowColorAnime();
    void checkMarkAnimeInit();
    void checkMarkAnime();
    u32 readFmapTexture(const char*);
    void aramCmapDatRead();
    void initCmapDatPnt(aramCmapDatPat_t*);
    aramCmapDatPnt_t* getGridNumToCmapDatPnt(int);
    void setDispIslandPos(s8, s8);
    void setIslandPos(fopMsgM_pane_class*, f32, f32);
    void changeFmapTexture(s8, s8);
    void setDspNormalMapLink();
    void setDspLargeMapLink();
    void checkDspLargeMapLink();
    void checkDspLargeMapShip();
    void dispEndSalvageLargeMark();
    void setDspHugeMapLink();
    void dispEndSalvageHugeMark(f32, f32);
    void checkDspHugeMapLink();
    void checkDspHugeMapShip();
    bool _open();
    bool _close();
    bool _close_normalMode();
    void _move();
    void _draw();
    void _delete();
    void FmapProcMain();
    void SelectGrid();
    void zoom1000x1000Init();
    void zoomMapAlphaSet(s8, s8, fopMsgM_pane_class*, u8);
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
    BOOL paneTransBase(short, u8, f32, f32, u8, int);
    BOOL paneTranceZoomMap(short, u8, f32, f32, f32, f32, f32, f32, u8, int);
    BOOL paneTranceZoomMapAlpah(short, u8, u8, int);
    BOOL paneTranceZoom2Map(short, u8, f32, f32, f32, f32, f32, f32, u8, int);
    BOOL paneAlphaFmapCursor(fopMsgM_pane_class*, short, u8, u8, int);
    BOOL PaneAlphaSelvageItem(short, u8);
    void gShipMarkAnimeInit();
    void gShipMarkAnime();
    bool _open_warpMode();
    void init_warpMode();
    void selCursorMoveWarp();
    bool _close_warpMode();
    void moveMain_warpMode();
    void wrapMove();
    void wrapSelWinFadeIn1();
    void wrapSelect();
    void wrapSelWinFadeOut();
    void wrapSelWarp();
    void warpAreaAnime0();
    BOOL paneTranceWarpMsg(fopMsgM_pane_class*, short, u8, f32, f32, u8, int);
    BOOL paneAlphaWarpMsgBack(short, u8, u8, int);
    void warpSelCursorMove();
    void warpSelCursorAnimeInit();
    void warpSelCursorAnime();
    s8 getWarpAreaGridX(int);
    s8 getWarpAreaGridY(int);
    int getWarpAreaNo(const cursorTable_t*);
    int getWarpAreaNoUp(const cursorTable_t*);
    int getWarpAreaNoDown(const cursorTable_t*);
    int getWarpAreaNoLeft(const cursorTable_t*);
    int getWarpAreaNoRight(const cursorTable_t*);
    const cursorTable_t* getWarpAreaTablePtr(s8, s8);
    void areaTextChangeAnimeInit();
    void areaTextChangeAnime();
    BOOL PaneAlphaAreaTxt(short, u8, int);
    void setDspWarpBackCornerColor(f32);
    void setWrapBackEmitter(cXyz);
    void setWrapSpotEmitter(int, cXyz);
    bool _open_fishManMode();
    bool _close_fishManMode();
    void init_fishManMode();
    void movefishManMode();
    void fmDispArea();
    void fmZoomGridLv1In();
    void fmZoomGridLv2In();
    void islandNameSet(u8);
    void fmMapWrite();
    void fmMapWait();
    BOOL paneAlphaZoom2Map(short, u8, u8, int);
    void fmZoomGridLv2Out();
    void fmZoomGridLv1Out();
    void fmEndWait();
    bool _open_wallPaper();
    int getButtonIconMode();

public:
    /* 0x0004 */ u8 padding_0x4[0x18 - 0x4];
    /* 0x0018 */ ResTIMG * mChkPntTxt_p;
    /* 0x001C */ dDlst_FMAP_c fmapDl;
    /* 0x0024 */ dMenu_Fmap2_c mFmap2;
    /* 0x2874 */ u8 padding_0x2874[0x2878 - 0x2874];
    /* 0x2878 */ dMenu_FmapSv_c* fmapSv;
    /* 0x287C */ aramCmapDat_c mCmapDatPnt;
    /* 0x2884 */ dDlst_2DOutFont_c* outFont;
    /* 0x2888 */ dDlst_2DOutFont_c* outFont2;
    /* 0x288C */ fopMsgM_pane_class mFddmPane;
    /* 0x28C4 */ fopMsgM_pane_class mClPane;
    /* 0x28FC */ fopMsgM_pane_class mCi22Pane;
    /* 0x2934 */ fopMsgM_pane_class mCi21Pane;
    /* 0x296C */ fopMsgM_pane_class mCi32Pane;
    /* 0x29A4 */ fopMsgM_pane_class mCi31Pane;
    /* 0x29DC */ fopMsgM_pane_class mGtixPanes[2];
    /* 0x2A4C */ fopMsgM_pane_class mKk1xPanes[8];
    /* 0x2C0C */ fopMsgM_pane_class mKk3xPanes[8];
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
    /* 0x30DC */ fopMsgM_pane_class mSc1xPanes[9];
    /* 0x32D4 */ fopMsgM_pane_class mLnk3Pane;
    /* 0x330C */ fopMsgM_pane_class mSpi3Pane;
    /* 0x3344 */ fopMsgM_pane_class mStl1Pane;
    /* 0x337C */ fopMsgM_pane_class mR01gPane;
    /* 0x33B4 */ fopMsgM_pane_class mFmxxPanes[5];
    /* 0x34CC */ fopMsgM_pane_class mFmnPanes[15];
    /* 0x3814 */ fopMsgM_pane_class mClgPane;
    /* 0x384C */ fopMsgM_pane_class mSc2xPanes[7];
    /* 0x39D4 */ fopMsgM_pane_class mR0xPanes[11];
    /* 0x3C3C */ fopMsgM_pane_class mStxxPanes[49];
    /* 0x46F4 */ fopMsgM_pane_class mCk1xPanes[3];
    /* 0x479C */ fopMsgM_pane_class mCk2xPanes[3];
    /* 0x4844 */ fopMsgM_pane_class mCk3xPanes[2];
    /* 0x48B4 */ fopMsgM_pane_class mKr0xPanes[8];
    /* 0x4A74 */ fopMsgM_pane_class mWnd1Pane;
    /* 0x4AAC */ fopMsgM_pane_class mWnd2Pane;
    /* 0x4AE4 */ fopMsgM_pane_class mMr01Pane;
    /* 0x4B1C */ fopMsgM_pane_class mAreaTxtPanes[3];
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
    /* 0x50CC */ STControl* stick;
    /* 0x50D0 */ JUTFont* mFont;
    /* 0x50D4 */ JUTFont* mRFont;
    /* 0x50D8 */ JPABaseEmitter* mMainWarpPane;
    /* 0x50DC */ JPABaseEmitter* mWarpPanes[9];
    /* 0x5100 */ u8 padding_0x5100[0x510C - 0x5100];
    /* 0x510C */ bool mMapClose;
    /* 0x510D */ u8 mSelCursorBufIdx;
    /* 0x510E */ u8 mCursorBufIdx;
    /* 0x510F */ u8 field_0x510F;
    /* 0x5110 */ u8 field_0x5110;
    /* 0x5111 */ s8 field_0x5111;
    /* 0x5112 */ s8 field_0x5112;
    /* 0x5113 */ u8 mMainProcIdx;
    /* 0x5114 */ u8 mFmapProcIdx;
    /* 0x5115 */ u8 mHikakuProcIdx;
    /* 0x5116 */ s16 mFrameTimer;
    /* 0x5118 */ s8 mGridX;
    /* 0x5119 */ s8 mGridY;
    /* 0x511A */ s8 mTargetGridX;
    /* 0x511B */ s8 mTargetGridY;
    /* 0x511C */ cXyz field_0x511C;
    /* 0x5128 */ cXyz field_0x5128;
    /* 0x5134 */ f32 field_0x5134;
    /* 0x5138 */ f32 field_0x5138;
    /* 0x513C */ bool mFullMapMode;
    /* 0x513D */ u8 mSalvItmBufIdx;
    /* 0x513E */ u8 mSalvItmTimer;
    /* 0x513F */ bool mSalvItmChanging;
    /* 0x5140 */ u8 mAreaTxtBufIdx;
    /* 0x5141 */ u8 mAreaTxtTimer;
    /* 0x5142 */ bool mAreaTxtChanging;
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
    /* 0x5181 */ u8 mButtonIconMode;
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
    /* 0x51AC */ bool mMsgValueActive;
    /* 0x51AD */ bool mMsgValueState1;
    /* 0x51AE */ bool mMsgValueState2;
    /* 0x51AF */ u8 mMsgValueTimer;
    /* 0x51B0 */ bool mMsgValueToggle;
    /* 0x51B1 */ u8 padding_0x51B1[0x51B4-0x51B1];
}; // Size: 0x51B4

STATIC_ASSERT(sizeof(dMenu_Fmap_c) == 0x51B4);

class dMf_HIO_c : public JORReflexible {
public:
    dMf_HIO_c();
    virtual ~dMf_HIO_c() {}

    void genMessage(JORMContext* ctx) { UNUSED(ctx); }

public:
    /* 0x004 */ s8 mNo;
    /* 0x005 */ u8 field_0x05;
    /* 0x006 */ u8 field_0x06;
    /* 0x007 */ u8 field_0x07;
    /* 0x008 */ u8 field_0x08;
    /* 0x009 */ GXColor field_0x09;
    /* 0x00D */ GXColor field_0x0D;
    /* 0x011 */ u8 padding_0x11[0x12 - 0x11];
    /* 0x012 */ s16 field_0x12;
    /* 0x014 */ s16 field_0x14;
    /* 0x016 */ u8 field_0x16;
    /* 0x017 */ u8 field_0x17;
    /* 0x018 */ u8 field_0x18;
    /* 0x019 */ u8 field_0x19;
    /* 0x01A */ u8 field_0x1A;
    /* 0x01B */ u8 field_0x1B;
    /* 0x01C */ u8 field_0x1C;
    /* 0x01D */ u8 field_0x1D;
    /* 0x01E */ u8 field_0x1E;
    /* 0x01F */ u8 field_0x1F;
    /* 0x020 */ u8 field_0x20;
    /* 0x021 */ u8 field_0x21;
    /* 0x022 */ u8 field_0x22;
    /* 0x023 */ u8 field_0x23;
    /* 0x024 */ u8 field_0x24;
    /* 0x025 */ u8 field_0x25;
    /* 0x026 */ s16 field_0x26;
    /* 0x028 */ s16 field_0x28;
    /* 0x02A */ s16 field_0x2A;
    /* 0x02C */ s16 field_0x2C;
    /* 0x02E */ u8 field_0x2E;
    /* 0x02F */ u8 field_0x2F;
    /* 0x030 */ u8 field_0x30;
    /* 0x031 */ u8 field_0x31;
    /* 0x032 */ u8 field_0x32;
    /* 0x033 */ u8 field_0x33;
    /* 0x034 */ u8 field_0x34;
    /* 0x035 */ u8 padding_0x35[0x36 - 0x35];
    /* 0x036 */ s16 field_0x36;
    /* 0x038 */ s16 field_0x38;
    /* 0x03A */ u8 field_0x3A;
    /* 0x03B */ u8 field_0x3B;
    /* 0x03C */ u8 field_0x3C;
    /* 0x03D */ u8 field_0x3D;
    /* 0x03E */ u8 field_0x3E;
    /* 0x03F */ u8 field_0x3F;
    /* 0x040 */ u8 field_0x40;
    /* 0x041 */ u8 field_0x41;
    /* 0x042 */ u8 field_0x42;
    /* 0x043 */ u8 field_0x43;
    /* 0x044 */ s16 field_0x44;
    /* 0x046 */ u8 field_0x46;
    /* 0x047 */ u8 field_0x47;
    /* 0x048 */ u8 field_0x48;
    /* 0x049 */ u8 field_0x49;
    /* 0x04A */ s16 field_0x4A;
    /* 0x04C */ u8 field_0x4C;
    /* 0x04D */ u8 field_0x4D;
    /* 0x04E */ u8 field_0x4E;
    /* 0x04F */ u8 padding_0x4F[0x50 - 0x4F];
    /* 0x050 */ f32 field_0x50[9];
    /* 0x074 */ f32 field_0x74[9];
    /* 0x098 */ f32 field_0x98;
    /* 0x09C */ f32 field_0x9C;
    /* 0x0A0 */ f32 field_0xA0;
    /* 0x0A4 */ f32 field_0xA4;
    /* 0x0A8 */ f32 field_0xA8;
    /* 0x0AC */ f32 field_0xAC;
    /* 0x0B0 */ f32 field_0xB0;
    /* 0x0B4 */ f32 field_0xB4;
    /* 0x0B8 */ f32 field_0xB8;
    /* 0x0BC */ f32 field_0xBC;
    /* 0x0C0 */ f32 field_0xC0;
    /* 0x0C4 */ f32 field_0xC4;
    /* 0x0C8 */ f32 field_0xC8;
    /* 0x0CC */ f32 field_0xCC;
    /* 0x0D0 */ f32 field_0xD0;
    /* 0x0D4 */ f32 field_0xD4;
    /* 0x0D8 */ f32 field_0xD8;
    /* 0x0DC */ f32 field_0xDC;
    /* 0x0E0 */ u8 field_0xE0;
    /* 0x0E1 */ GXColor field_0xE1;
    /* 0x0E5 */ GXColor field_0xE5;
    /* 0x0E9 */ u8 field_0xE9;
    /* 0x0EA */ GXColor field_0xEA;
    /* 0x0EE */ GXColor field_0xEE;
    /* 0x0F2 */ u8 field_0xF2;
    /* 0x0F3 */ GXColor field_0xF3;
    /* 0x0F7 */ GXColor field_0xF7;
    /* 0x0FB */ u8 field_0xFB;
    /* 0x0FC */ GXColor field_0xFC;
    /* 0x100 */ GXColor field_0x100;
    /* 0x104 */ u8 field_0x104;
    /* 0x105 */ u8 field_0x105;
    /* 0x106 */ u8 field_0x106;
    /* 0x107 */ u8 field_0x107;
    /* 0x108 */ u8 field_0x108;
    /* 0x109 */ u8 field_0x109;
    /* 0x10A */ u8 field_0x10A;
    /* 0x10B */ u8 field_0x10B;
    /* 0x10C */ u8 field_0x10C;
    /* 0x10D */ u8 field_0x10D;
    /* 0x10E */ u8 field_0x10E;
    /* 0x10F */ u8 field_0x10F;
    /* 0x110 */ u8 field_0x110;
    /* 0x111 */ u8 field_0x111;
    /* 0x112 */ u8 field_0x112;
    /* 0x113 */ u8 field_0x113;
    /* 0x114 */ u8 field_0x114;
    /* 0x115 */ u8 field_0x115;
    /* 0x116 */ u8 field_0x116;
    /* 0x117 */ u8 field_0x117;
    /* 0x118 */ u8 field_0x118;
    /* 0x119 */ u8 field_0x119;
    /* 0x11A */ u8 field_0x11A;
    /* 0x11B */ u8 field_0x11B;
    /* 0x11C */ u8 field_0x11C;
    /* 0x11D */ u8 field_0x11D;
    /* 0x11E */ u8 field_0x11E;
    /* 0x11F */ u8 padding_0x11F[0x120 - 0x11F];
};

extern dMf_HIO_c g_mfHIO;

#endif /* D_MENU_FMAP_H */
