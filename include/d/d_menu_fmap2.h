#ifndef D_MENU_FMAP2_H
#define D_MENU_FMAP2_H

#include "JSystem/J2DGraph/J2DTextBox.h"
#include "d/d_drawlist.h"
#include "d/d_menu_fmapSv.h"
#include "dolphin/types.h"
#include "f_op/f_op_msg_mng.h"
#include "m_Do/m_Do_hostIO.h"

struct fopMsgM_pane_class;
class J2DScreen;
class JUTFont;
struct ResTIMG;
class STControl;
class dDlst_2DOutFont_c;
class mDoDvdThd_mountArchive_c;

class dDlst_FMAP2GS_c : public dDlst_base_c {
public:
    virtual ~dDlst_FMAP2GS_c() {}
    virtual void draw();

    /* 0x04 */ J2DScreen* scrn;
};

class dDlst_FMAP2_c : public dDlst_base_c {
public:
    virtual ~dDlst_FMAP2_c() {}
    virtual void draw();

    /* 0x04 */ J2DScreen* scrn;
};

class dMenu_Fmap2_c {
public:
    virtual ~dMenu_Fmap2_c() {}

    aramCmapDatPnt_t* getCmapDatPnt(int i_cmapIdx) {
        return mpFmapDatPnt->getCmapDatPnt4(i_cmapIdx);
    }
    void getCmapDatValue() {
    }
    u8 lineInter0to1ForU8(u8 a, u8 b, f32 c) {
        return a + (b - a) * c;
    }
    void setAramCmapDat(aramCmapDat_c* i_ptr) { mpFmapDatPnt = i_ptr; }
    void setSvPtr(dMenu_FmapSv_c* i_ptr) { fmapSv = i_ptr; }

    void _create();
    void screenSet();
    void initialize();
    void displayInit();
    void fmapPaneInit();
    void cmapPaneInit();
    void collectMapCheck();
    void _move();
    void FmapProcMain();
    void FmapChange();
    void CmapProcMain();
    void spMapLoadForDVD(u8);
    BOOL cmapOpenCheck();
    void CmapScroll();
    BOOL isSpMap(int);
    void CmapOpen();
    void CmapSpLoadWait();
    void screenSetGs();
    void gsMoonAnimeInit();
    void gsMoonAnime();
    void gsShipAnime();
    void gsIconAnimeInit();
    void gsIconAnime();
    void screenSetTn();
    void screenSetTr();
    void trTrifAnimeInit();
    void trTrifAnime();
    void screenSetIk();
    void screenSetHeartP();
    void screenSetTerry();
    void screenSetSubMa();
    void screenSetMoon();
    void screenSetDfaliy();
    void screenSetYagura();
    void screenSetHeartM();
    void screenSetSubdan();
    void setPlayerPos(fopMsgM_pane_class*, fopMsgM_pane_class*, fopMsgM_pane_class*);
    void CmapOpenSp();
    void CmapProc2();
    void CmapClose();
    void cmapMove();
    void changeSelCmap();
    void changeSelCmap2();
    void cmapAlphaSet();
    void changeZoomCmap();
    void ChangeProcMode();
    bool _open();
    bool _close();
    void _draw();
    void _delete();
    void fCursorInit();
    void fCursorMove();
    void fCursorAnime();
    void cCursorAnimeInit();
    void cCursorAnime();
    void cCursorHide();
    void cSelCursorInit();
    void cSelCursorAnimeInit();
    void cSelCursorAnime();
    void cSelCursorHide();
    void playerPointGridAnimeInit();
    void playerPointGridAnime(fopMsgM_pane_class*);
    void changeFmapTexture();
    void changeIslandName();
    void fmapPlayerPosDisp();
    BOOL fmapPlayerPosDispCheck(f32*, f32*);
    void changeCmapName();
    void cmapPlayerPosDisp();
    void cmapSalvagePosDisp();
    BOOL cmapPlayerPosDispCheck(f32*, f32*);
    BOOL paneTransBase(s16, u8, f32, f32, u8, u8, int);
    BOOL paneAlphaFmapBase(s16, u8, u8, int);
    BOOL paneAlphaCmapBase(s16, u8, u8, int);
    BOOL paneAlphaZoomCmapBase(s16, u8, f32, f32, u8, u8, int);
    BOOL paneAlphaCmapName(s16, u8, u8);
    BOOL paneAlphaMessage2(s16, u8, u8, int);
    BOOL paneTranceMessage(s16, u8, f32, f32, f32, f32, u8, u8, int);
    void paneScaleXYChild(fopMsgM_pane_class*, f32);
    BOOL paneTransSelCmapCle(s16, u8, f32, f32, f32, f32, u8, u8, int);
    BOOL paneTransSelCmapOpn(s16, u8, f32, f32, f32, f32, u8, u8, int);
    BOOL paneAlphaGostShipMap(s16, u8, u8, int);
    BOOL paneAlphaTingleMap(s16, u8, u8, int);
    BOOL paneAlphaTreasureMap(s16, u8, u8, int);
    BOOL paneAlphaSubdanMap(s16, u8, u8, int);
    BOOL paneAlphaHeartMMap(s16, u8, u8, int);
    BOOL paneAlphaYaguraMap(s16, u8, u8, int);
    BOOL paneAlphaDfaliyMap(s16, u8, u8, int);
    BOOL paneAlphaHeartPMap(s16, u8, u8, int);
    BOOL paneAlphaTerryMap(s16, u8, u8, int);
    BOOL paneAlphaSubMaMap(s16, u8, u8, int);
    BOOL paneAlphaMoonMap(s16, u8, u8, int);
    BOOL paneAlphaDoctaMap(s16, u8, u8, int);
    void setPaneOnOff(J2DScreen*, u32, bool);
    void getCollectMapTexChange();
    void finCollectMapTexChange();
    int calcGetCollectMap();
    int calcGetCollectMap2();
    int calcFinCollectMap();
    int getNowCmapFirstNum();
    int getNowCmapNextNum(s8, int);
    aramCmapDatPnt_t* getCmapDatPnt4(int);
    u32 readPaneCmapTexture(const ResTIMG*, int);
    u32 readFmapTexture(const char*);
    int getButtonIconMode();
    BOOL isLockBbutton();
    BOOL isGetCollectMap(s8);
    BOOL isOpenCollectMap(s8);
    BOOL isOpenCollectMapTriforce(s8);
    int getCollectMapKind(s8);
    BOOL isCompleteCollectMap(s8);

    u8 getCtDispMode() {
        JUT_ASSERT(VERSION_SELECT(409, 409, 428, 428), fmapSv != NULL);
        return fmapSv->getDispMode();
    }

    u8 getCtActive() {
        JUT_ASSERT(VERSION_SELECT(415, 415, 434, 434), fmapSv != NULL);
        return fmapSv->getActive();
    }

    void setCtActive(u8 active) {
        JUT_ASSERT(VERSION_SELECT(420, 420, 439, 439), fmapSv != NULL);
        fmapSv->setActive(active);
    }

    s8 getCtCurX() {
        JUT_ASSERT(VERSION_SELECT(426, 426, 445, 445), fmapSv != NULL);
        return fmapSv->getCurX();
    }

    s8 getCtCurY() {
        JUT_ASSERT(VERSION_SELECT(436, 436, 455, 455), fmapSv != NULL);
        return fmapSv->getCurY();
    }

    s8 getCtCurHX() {
        JUT_ASSERT(VERSION_SELECT(447, 447, 466, 466), fmapSv != NULL);
        return fmapSv->getCurHX();
    }

    void setCtCurHX(s8 x) {
        JUT_ASSERT(VERSION_SELECT(452, 452, 471, 471), fmapSv != NULL);
        fmapSv->setCurHX(x);
    }

    s8 getCtCurHY() {
        JUT_ASSERT(VERSION_SELECT(457, 457, 476, 476), fmapSv != NULL);
        return fmapSv->getCurHY();
    }

    void setCtCurHY(s8 y) {
        JUT_ASSERT(VERSION_SELECT(462, 462, 481, 481), fmapSv != NULL);
        fmapSv->setCurHY(y);
    }

    s8 getCtCmapSelNo() {
        JUT_ASSERT(VERSION_SELECT(469, 469, 488, 488), fmapSv != NULL);
        return fmapSv->getCmapSelNo();
    }

    void setCtCmapSelNo(s8 no) {
        JUT_ASSERT(VERSION_SELECT(474, 474, 493, 493), fmapSv != NULL);
        fmapSv->setCmapSelNo(no);
    }

private:
    /* 0x0004 */ ResTIMG* mChkPntTxt_p;
    /* 0x0008 */ ResTIMG* mCmapTxtMain_p[2];
    /* 0x0010 */ dMenu_FmapSv_c* fmapSv;
    /* 0x0014 */ u8 padding_0x14[0x18 - 0x14];
    /* 0x0018 */ mDoDvdThd_mountArchive_c* mpMount;
    /* 0x001C */ aramCmapDat_c* mpFmapDatPnt;
    /* 0x0020 */ dDlst_FMAP2_c fmap2Dl;
    /* 0x0028 */ dDlst_FMAP2GS_c fmap2GsDl;
    /* 0x0030 */ STControl* stick;
    /* 0x0034 */ JUTFont* mFont;
    /* 0x0038 */ JUTFont* mRFont;
    /* 0x003C */ dDlst_2DOutFont_c* outFont[2];
    /* 0x0044 */ dDlst_2DOutFont_c* outFontS[2];
    /* 0x004C */ fopMsgM_pane_class mClPane;
    /* 0x0084 */ fopMsgM_pane_class mFcxxPanes[8];
    /* 0x0244 */ fopMsgM_pane_class mCcxxPanes[8];
    /* 0x0404 */ fopMsgM_pane_class mKdmPane;
    /* 0x043c */ fopMsgM_pane_class mMswPanes[5];
    /* 0x0554 */ fopMsgM_pane_class mCk1Panes[17];
    /* 0x090C */ fopMsgM_pane_class mCk2Panes[17];
    /* 0x0CC4 */ fopMsgM_pane_class* mCkPanes[2];
    /* 0x0CCC */ fopMsgM_pane_class mCi22Pane;
    /* 0x0D04 */ fopMsgM_pane_class mCi21Pane;
    /* 0x0D3C */ fopMsgM_pane_class mCi12Pane;
    /* 0x0D74 */ fopMsgM_pane_class mCi11Pane;
    /* 0x0DAC */ fopMsgM_pane_class mLnk3Pane;
    /* 0x0DE4 */ fopMsgM_pane_class mAreaPane;
    /* 0x0E1C */ fopMsgM_pane_class mIslandNamePanes[2];
    /* 0x0E8C */ fopMsgM_pane_class mCmyuPane;
    /* 0x0EC4 */ fopMsgM_pane_class mCmydPane;
    /* 0x0EFC */ fopMsgM_pane_class mCnd0Pane;
    /* 0x0F34 */ fopMsgM_pane_class mCm1xPanes[2];
    /* 0x0FA4 */ fopMsgM_pane_class mCm2xPanes[2];
    /* 0x1014 */ fopMsgM_pane_class mClS1Panes[5];
    /* 0x112C */ fopMsgM_pane_class mClS2Panes[5];
    /* 0x1244 */ fopMsgM_pane_class* mCmxxPanes[2];
    /* 0x124C */ fopMsgM_pane_class* mClSPanes[2];
    /* 0x1254 */ fopMsgM_pane_class mMkfdPane;
    /* 0x128C */ fopMsgM_pane_class mMkcdPane;
    /* 0x12C4 */ fopMsgM_pane_class mMkm0Pane;
    /* 0x12FC */ fopMsgM_pane_class mNcddPane;
    /* 0x1334 */ fopMsgM_pane_class mNfkdPane;
    /* 0x136C */ fopMsgM_pane_class mR01gPane;
    /* 0x13A4 */ fopMsgM_pane_class mClgPane;
    /* 0x13DC */ fopMsgM_pane_class mFmk1Pane;
    /* 0x1414 */ fopMsgM_pane_class mRkjnPane;
    /* 0x144C */ fopMsgM_pane_class mClg2Pane;
    /* 0x1484 */ fopMsgM_pane_class mCmtPanes[8];
    /* 0x1644 */ fopMsgM_pane_class mCdd1Panes[10];
    /* 0x1874 */ fopMsgM_pane_class mCdd2Panes[10];
    /* 0x1AA4 */ fopMsgM_pane_class* mCddPanes[2];
    /* 0x1AAC */ fopMsgM_pane_alpha_class mGsMs01PaneAlpha;
    /* 0x1AB4 */ fopMsgM_pane_alpha_class mGsMs02PaneAlpha;
    /* 0x1ABC */ fopMsgM_pane_alpha_class mGsSd05PaneAlpha;
    /* 0x1AC4 */ fopMsgM_pane_alpha_class mGsHs04PaneAlpha;
    /* 0x1ACC */ fopMsgM_pane_alpha_class mGsYg01PaneAlpha;
#if VERSION == VERSION_DEMO
    /* 0x1AD4 */ fopMsgM_pane_alpha_class mGsWk3PaneAlpha;
#endif
    /* 0x1AD4 */ fopMsgM_pane_alpha_class mGsBsdmPaneAlpha;
    /* 0x1ADC */ fopMsgM_pane_alpha_class mGsTk0xPanesAlpha[7];
    /* 0x1B14 */ fopMsgM_pane_alpha_class mGsTkd2PaneAlpha;
    /* 0x1B1C */ fopMsgM_pane_alpha_class mGsTkd1PaneAlpha;
    /* 0x1B24 */ fopMsgM_pane_alpha_class mGsS02PaneAlpha;
    /* 0x1B2C */ fopMsgM_pane_alpha_class mGsKz05PaneAlpha;
    /* 0x1B34 */ fopMsgM_pane_alpha_class mGsKz01PaneAlpha;
#if VERSION == VERSION_DEMO
    /* 0x1B44 */ fopMsgM_pane_alpha_class mGsBt1PaneAlpha;
    /* 0x1B4C */ fopMsgM_pane_alpha_class mGsBt2PaneAlpha;
    /* 0x1B54 */ fopMsgM_pane_alpha_class mGsBt3PaneAlpha;
#endif
#if VERSION > VERSION_JPN
    /* 0x1B3C */ fopMsgM_pane_alpha_class mGsGsixPanesAlpha[7];
#endif
    /* 0x1B74 */ fopMsgM_pane_alpha_class mTnHk00PaneAlpha;
    /* 0x1B7C */ fopMsgM_pane_alpha_class mTnHk01PaneAlpha;
    /* 0x1B84 */ fopMsgM_pane_alpha_class mTnHn19PaneAlpha;
    /* 0x1B8C */ fopMsgM_pane_alpha_class mTnHk29PaneAlpha;
#if VERSION > VERSION_JPN
    /* 0x1B94 */ fopMsgM_pane_class mTnGddmPane;
#endif
    /* 0x1BCC */ fopMsgM_pane_alpha_class mTnMiscPanesAlpha[VERSION_SELECT(17, 17, 22, 22)];
#if VERSION > VERSION_JPN
    /* 0x1C7C */ fopMsgM_pane_class mTnLnkPane;
    /* 0x1CB4 */ fopMsgM_pane_class mTnGdgtPane;
#endif
    /* 0x1CEC */ fopMsgM_pane_alpha_class mTrMs01PaneAlpha;
    /* 0x1CF4 */ fopMsgM_pane_alpha_class mTrMs02PaneAlpha;
    /* 0x1CFC */ fopMsgM_pane_alpha_class mTrHs04PaneAlpha;
    /* 0x1D04 */ fopMsgM_pane_alpha_class mTrSd05PaneAlpha;
    /* 0x1D0C */ fopMsgM_pane_alpha_class mTrKz05PaneAlpha;
    /* 0x1D14 */ fopMsgM_pane_class mTrGddmPane;
    /* 0x1D4C */ fopMsgM_pane_alpha_class mTrMkdmPaneAlpha;
    /* 0x1D54 */ fopMsgM_pane_class mTrLnkPane;
    /* 0x1D8C */ fopMsgM_pane_class mTrGdgtPane;
#if VERSION > VERSION_JPN
    /* 0x1DC4 */ fopMsgM_pane_alpha_class mTrMgxPanesAlpha[8];
    /* 0x1E04 */ fopMsgM_pane_alpha_class mTrTfxPanesAlpha[8];
    /* 0x1E44 */ fopMsgM_pane_alpha_class mTrTgxPanesAlpha[8];
#endif
    /* 0x1E84 */ fopMsgM_pane_alpha_class mIkMs01PaneAlpha;
    /* 0x1E8C */ fopMsgM_pane_alpha_class mIkMs02PaneAlpha;
    /* 0x1E94 */ fopMsgM_pane_alpha_class mIkSd05PaneAlpha;
    /* 0x1E9C */ fopMsgM_pane_alpha_class mIlHs04PaneAlpha;
    /* 0x1EA4 */ fopMsgM_pane_class mIkGddmPane;
    /* 0x1EDC */ fopMsgM_pane_alpha_class mIkMkdkPaneAlpha;
    /* 0x1EE4 */ fopMsgM_pane_class mIkLnkPane;
    /* 0x1F1C */ fopMsgM_pane_class mIkGdgtPane;
    /* 0x1F54 */ fopMsgM_pane_alpha_class mHeartPMs01PaneAlpha;
    /* 0x1F5C */ fopMsgM_pane_alpha_class mHeartPMs02PaneAlpha;
    /* 0x1F64 */ fopMsgM_pane_alpha_class mHeartPSd05PaneAlpha;
    /* 0x1F6C */ fopMsgM_pane_alpha_class mHeartPHs04PaneAlpha;
    /* 0x1F74 */ fopMsgM_pane_class mHeartPGddmPane;
    /* 0x1FAC */ fopMsgM_pane_alpha_class mHeartPMk20PaneAlpha;
    /* 0x1FB4 */ fopMsgM_pane_alpha_class mHeartPNm08PaneAlpha;
    /* 0x1FBC */ fopMsgM_pane_alpha_class mHeartPKk12PaneAlpha;
    /* 0x1FC4 */ fopMsgM_pane_alpha_class mHeartPBh01PaneAlpha;
    /* 0x1FCC */ fopMsgM_pane_alpha_class mHeartPBh02PaneAlpha;
    /* 0x1FD4 */ fopMsgM_pane_class mHeartPLnkPane;
    /* 0x200C */ fopMsgM_pane_class mHeartPGdgtPane;
    /* 0x2044 */ fopMsgM_pane_alpha_class mTerryMs01PaneAlpha;
    /* 0x204C */ fopMsgM_pane_alpha_class mTerryMs02PaneAlpha;
    /* 0x2054 */ fopMsgM_pane_alpha_class mTerrySd05PaneAlpha;
    /* 0x205C */ fopMsgM_pane_alpha_class mTerryHs04PaneAlpha;
    /* 0x2064 */ fopMsgM_pane_class mTerryGddmPane;
    /* 0x209C */ fopMsgM_pane_class mTerryLnkPane;
    /* 0x20D4 */ fopMsgM_pane_class mTerryGdgtPane;
    /* 0x210C */ fopMsgM_pane_alpha_class mSubMaMs01PaneAlpha;
    /* 0x2114 */ fopMsgM_pane_alpha_class mSubMaMs02PaneAlpha;
    /* 0x211C */ fopMsgM_pane_alpha_class mSubMaSd05PaneAlpha;
    /* 0x2124 */ fopMsgM_pane_alpha_class mSubMaHs04PaneAlpha;
    /* 0x212C */ fopMsgM_pane_class mSubMaGddmPane;
    /* 0x2164 */ fopMsgM_pane_class mSubMaLnkPane;
    /* 0x219C */ fopMsgM_pane_class mSubMaGdgtPane;
    /* 0x21D4 */ fopMsgM_pane_alpha_class mMoonMs01PaneAlpha;
    /* 0x21DC */ fopMsgM_pane_alpha_class mMoonMs02PaneAlpha;
    /* 0x21E4 */ fopMsgM_pane_alpha_class mMoonSd05PaneAlpha;
    /* 0x21EC */ fopMsgM_pane_alpha_class mMoonHs04PaneAlpha;
    /* 0x21F4 */ fopMsgM_pane_class mMoonGddmPane;
    /* 0x222C */ fopMsgM_pane_alpha_class mMoonKrxPanesAlpha[38];
    /* 0x235C */ fopMsgM_pane_class mMoonLnkPane;
    /* 0x2394 */ fopMsgM_pane_class mMoonGdgtPane;
    /* 0x23CC */ fopMsgM_pane_alpha_class mDfaliyMs01PaneAlpha;
    /* 0x23D4 */ fopMsgM_pane_alpha_class mDfaliyMs02PaneAlpha;
    /* 0x23DC */ fopMsgM_pane_alpha_class mDfaliySd05PaneAlpha;
    /* 0x23E4 */ fopMsgM_pane_alpha_class mDfaliyHs04PaneAlpha;
    /* 0x23EC */ fopMsgM_pane_class mDfaliyGddmPane;
    /* 0x2424 */ fopMsgM_pane_class mDfaliyLnkPane;
    /* 0x245C */ fopMsgM_pane_class mDfaliyGdgtPane;
    /* 0x2494 */ fopMsgM_pane_alpha_class mYaguraMs01PaneAlpha;
    /* 0x249C */ fopMsgM_pane_alpha_class mYaguraMs02PaneAlpha;
    /* 0x24A4 */ fopMsgM_pane_alpha_class mYaguraSd05PaneAlpha;
    /* 0x24AC */ fopMsgM_pane_alpha_class mYaguraHs04PaneAlpha;
    /* 0x24B4 */ fopMsgM_pane_class mYaguraGddmPane;
    /* 0x24EC */ fopMsgM_pane_alpha_class mYaguraTtlxPaneAlpha[2];
    /* 0x24FC */ fopMsgM_pane_class mYaguraLnkPane;
    /* 0x2534 */ fopMsgM_pane_class mYaguraGdgtPane;
    /* 0x256C */ fopMsgM_pane_alpha_class mHeartMMs01PaneAlpha;
    /* 0x2574 */ fopMsgM_pane_alpha_class mHeartMMs02PaneAlpha;
    /* 0x257C */ fopMsgM_pane_alpha_class mHeartMSd05PaneAlpha;
    /* 0x2584 */ fopMsgM_pane_alpha_class mHeartMHs04PaneAlpha;
    /* 0x258C */ fopMsgM_pane_class mHeartMGddmPane;
    /* 0x25C4 */ fopMsgM_pane_alpha_class mHeartMSt09PaneAlpha;
    /* 0x25CC */ fopMsgM_pane_alpha_class mHeartMNhxPanesAlpha[DEMO_SELECT(9, 7)];
    /* 0x2604 */ fopMsgM_pane_alpha_class mHeartMMkxPanesAlpha[DEMO_SELECT(13, 9)];
    /* 0x264C */ fopMsgM_pane_class mHeartMLnkPane;
    /* 0x2684 */ fopMsgM_pane_class mHeartMGdgtPane;
    /* 0x26BC */ fopMsgM_pane_alpha_class mSubdanMs01PaneAlpha;
    /* 0x26C4 */ fopMsgM_pane_alpha_class mSubdanMs02PaneAlpha;
    /* 0x26CC */ fopMsgM_pane_alpha_class mSubdanSd05PaneAlpha;
    /* 0x26D4 */ fopMsgM_pane_alpha_class mSubdanHs04PaneAlpha;
    /* 0x26DC */ fopMsgM_pane_class mSubdanGddmPane;
    /* 0x2714 */ fopMsgM_pane_alpha_class mSubdanIg26PaneAlpha;
    /* 0x271C */ fopMsgM_pane_alpha_class mSubdanIgnxPanesAlpha[DEMO_SELECT(6, 2)];
    /* 0x272C */ fopMsgM_pane_class mSubdanLnkPane;
    /* 0x2764 */ fopMsgM_pane_class mSubdanGdgtPane;
    /* 0x279C */ fopMsgM_pane_class* mpGdgtPane;
    /* 0x27A0 */ u8 field_0x27A0;
    /* 0x27A1 */ u8 mMainProcIdx;
    /* 0x27A2 */ u8 padding_0x27A2[0x27A5 - 0x27A2];
    /* 0x27A5 */ u8 mFCursorBufIdx;
    /* 0x27A6 */ u8 mCCursorBufIdx;
    /* 0x27A7 */ u8 mCSelCursorToggle;
    /* 0x27A8 */ u8 mCollectMapNum;
    /* 0x27A9 */ s8 mCmapSelNo;
    /* 0x27AA */ s8 mPrevCmapSelNo;
    /* 0x27AB */ s8 mCmapScrollDir;
    /* 0x27AC */ s16 mFrameTimer;
    /* 0x27AE */ u8 padding_0x27AE[0x27B0 - 0x27AE];
    /* 0x27B0 */ f32 mPlayerPosX;
    /* 0x27B4 */ f32 mPlayerPosZ;
    /* 0x27B8 */ f32 mPlayerAngleDeg;
    /* 0x27BC */ s8 mGridX;
    /* 0x27BD */ s8 mGridY;
    /* 0x27BE */ s8 mPlayerPointTimer;
    /* 0x27BF */ s8 mPlayerPointToggle;
    /* 0x27C0 */ char* mTxtIslandName[2];
    /* 0x27C8 */ char* mTxtCmapName[4];
    /* 0x27D8 */ char* mTxtCk1;
    /* 0x27DC */ char* mTxtCk1S;
    /* 0x27E0 */ char* mTxtCk2;
    /* 0x27E4 */ char* mTxtCk2S;
    /* 0x27E8 */ char* mTxtCk1Ruby;
    /* 0x27EC */ char* mTxtCk1RubyS;
    /* 0x27F0 */ char* mTxtCk2Ruby;
    /* 0x27F4 */ char* mTxtCk2RubyS;
    /* 0x27F8 */ u8 mBlackAlpha;
    /* 0x27F9 */ u8 mWhiteAlpha;
    /* 0x27FA */ u8 field_0x27FA;
    /* 0x27FB */ u8 mSpMapDrawMode;
    /* 0x27FC */ u8 mLockBbutton;
    /* 0x2800 */ f32 field_0x2800;
    /* 0x2804 */ f32 field_0x2804;
    /* 0x2808 */ f32 field_0x2808;
    /* 0x280C */ u8 field_0x280C;
    /* 0x280D */ u8 mLeftTriggerHold;
    /* 0x280E */ u8 mRightTriggerHold;
    /* 0x280F */ u8 mSpMapKind;
    /* 0x2810 */ u8 mOnSea;
    /* 0x2811 */ u8 field_0x2811;
    /* 0x2812 */ u8 mButtonIconMode;
    /* 0x2813 */ u8 mClSBufIdx;
    /* 0x2814 */ u8 mCmxxBufIdx;
    /* 0x2815 */ u8 mCddBufIdx;
    /* 0x2816 */ u8 mCkBufIdx;
    /* 0x2817 */ u8 field_0x2817;
    /* 0x2818 */ u8 field_0x2818;
    /* 0x2819 */ u8 field_0x2819;
    /* 0x281A */ u8 field_0x281A;
    /* 0x281B */ u8 field_0x281B;
    /* 0x281C */ u8 field_0x281C;
    /* 0x281D */ u8 padding_0x281D[0x2820 - 0x281D];
    /* 0x2820 */ JUtility::TColor color_0x2820;
    /* 0x2824 */ JUtility::TColor color_0x2824;
    /* 0x2828 */ JUtility::TColor color_0x2828;
    /* 0x282C */ JUtility::TColor color_0x282C;
    /* 0x2830 */ J2DTextBox::TFontSize mCkTextFontSize;
    /* 0x2838 */ J2DTextBox::TFontSize mCkRubyFontSize;
    /* 0x2840 */ f32 mCkTextLineSpace;
    /* 0x2844 */ f32 mCkRubyLineSpace;
    /* 0x2848 */ u16 mCkMsgNo[2];
#if VERSION > VERSION_JPN
    /* 0x284C */ u8 field_0x284C;
    /* 0x284D */ u8 field_0x284D;
    /* 0x284E */ u8 field_0x284E;
    /* 0x284F */ u8 field_0x284F;
    /* 0x2850 */ u8 field_0x2850;
#endif
}; // Size: 0x2854

STATIC_ASSERT(sizeof(dMenu_Fmap2_c) == VERSION_SELECT(0x26F4, 0x2684, 0x2854, 0x2854));

class dMf2_HIO_c : public JORReflexible {
public:
    dMf2_HIO_c();
    virtual ~dMf2_HIO_c() {}

    void genMessage(JORMContext* ctx) { UNUSED(ctx); }

    /* 0x04 */ s8 mNo;
    /* 0x05 */ GXColor mPlayerPointWhite1;
    /* 0x09 */ GXColor mPlayerPointWhite2;
    /* 0x0D */ GXColor mPlayerPointBlack1;
    /* 0x11 */ GXColor mPlayerPointBlack2;
    /* 0x16 */ s16 mPlayerPointTimer;
    /* 0x18 */ u8 padding_0x18[0x1E - 0x18];
    /* 0x1E */ u8 field_0x1E;
    /* 0x1F */ u8 field_0x1F;
    /* 0x20 */ u8 field_0x20;
    /* 0x21 */ u8 field_0x21;
    /* 0x22 */ u8 field_0x22;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ u8 field_0x28;
    /* 0x29 */ u8 padding_0x29[0x30 - 0x29];
    /* 0x30 */ u8 field_0x30;
    /* 0x31 */ u8 field_0x31;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ u8 mBaseAnimFrame;
    /* 0x3A */ s16 mOpenPosY;
    /* 0x3C */ s16 mClosePosY;
    /* 0x3E */ u8 mChangeAnimFrame;
    /* 0x3F */ u8 mCmapOpenAnimFrame;
    /* 0x40 */ u8 mSpMapAnimFrame;
    /* 0x44 */ f32 mMsgScale;
    /* 0x48 */ u8 mFCursorFlashFrame;
    /* 0x49 */ u8 mCCursorFlashFrame;
    /* 0x4A */ u8 mSelCursorAlphaFrame;
    /* 0x4B */ u8 mSelCursorMove;
    /* 0x4C */ u8 field_0x4C;
    /* 0x4D */ u8 field_0x4D;
    /* 0x4E */ u8 field_0x4E;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 mScrollSelOffset;
    /* 0x5C */ f32 mScrollMsgOffset;
    /* 0x60 */ f32 mScrollScale;
    /* 0x64 */ u8 mScrollAnimFrame;
    /* 0x68 */ f32 mScrollHoldSelOffset;
    /* 0x6C */ f32 mScrollHoldMsgOffset;
    /* 0x70 */ f32 mScrollHoldScale;
    /* 0x74 */ u8 mScrollHoldAnimFrame;
    /* 0x75 */ u8 mScrollHoldFrame;
    /* 0x76 */ u8 field_0x76;
    /* 0x77 */ u8 field_0x77;
    /* 0x78 */ u8 field_0x78;
    /* 0x79 */ u8 field_0x79;
    /* 0x7A */ u8 mGsMoonAnimFrame;
    /* 0x7B */ u8 mGsMoonHoldFrame;
    /* 0x7C */ GXColor mGsMoonWhite;
    /* 0x80 */ GXColor mGsMoonBlack;
    /* 0x84 */ u8 mGsShipDelay;
    /* 0x85 */ u8 mGsShipAnimFrame;
    /* 0x86 */ GXColor mGsShipWhite;
    /* 0x8A */ GXColor mGsShipBlack;
#if VERSION > VERSION_JPN
    /* 0x8E */ u8 mGsIconAnimFrame;
    /* 0x8F */ u8 mGsIconHoldFrame;
    /* 0x90 */ u8 mGsIconAlphaMax;
    /* 0x91 */ u8 mGsIconAlphaMin;
    /* 0x92 */ u8 mTriforceAnimFrame;
    /* 0x93 */ u8 mTriforceAlphaMax;
    /* 0x94 */ u8 mTriforceAlphaMin;
#endif
};

#endif /* D_MENU_FMAP2_H */
