#ifndef D_MENU_FMAP2_H
#define D_MENU_FMAP2_H

#include "d/d_drawlist.h"
#include "d/d_menu_fmapSv.h"

struct fopMsgM_pane_class;
class J2DScreen;
class JUTFont;
struct ResTIMG;
class STControl;
class dDlst_2DOutFont_c;

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

    void getCmapDatPnt(int) {}
    void getCmapDatValue() {}
    void lineInter0to1ForU8(u8, u8, f32) {}
    void setAramCmapDat(aramCmapDat_c* i_ptr) { mpFmapDatPnt = i_ptr; }
    void setSvPtr(dMenu_FmapSv_c*) {}

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
    void fmapPlayerPosDispCheck(f32*, f32*);
    void changeCmapName();
    void cmapPlayerPosDisp();
    void cmapSalvagePosDisp();
    void cmapPlayerPosDispCheck(f32*, f32*);
    void paneTransBase(s16, u8, f32, f32, u8, u8, int);
    void paneAlphaFmapBase(s16, u8, u8, int);
    void paneAlphaCmapBase(s16, u8, u8, int);
    void paneAlphaZoomCmapBase(s16, u8, f32, f32, u8, u8, int);
    void paneAlphaCmapName(s16, u8, u8);
    void paneAlphaMessage2(s16, u8, u8, int);
    void paneTranceMessage(s16, u8, f32, f32, f32, f32, u8, u8, int);
    void paneScaleXYChild(fopMsgM_pane_class*, f32);
    void paneTransSelCmapCle(s16, u8, f32, f32, f32, f32, u8, u8, int);
    void paneTransSelCmapOpn(s16, u8, f32, f32, f32, f32, u8, u8, int);
    void paneAlphaGostShipMap(s16, u8, u8, int);
    void paneAlphaTingleMap(s16, u8, u8, int);
    void paneAlphaTreasureMap(s16, u8, u8, int);
    void paneAlphaSubdanMap(s16, u8, u8, int);
    void paneAlphaHeartMMap(s16, u8, u8, int);
    void paneAlphaYaguraMap(s16, u8, u8, int);
    void paneAlphaDfaliyMap(s16, u8, u8, int);
    void paneAlphaHeartPMap(s16, u8, u8, int);
    void paneAlphaTerryMap(s16, u8, u8, int);
    void paneAlphaSubMaMap(s16, u8, u8, int);
    void paneAlphaMoonMap(s16, u8, u8, int);
    void paneAlphaDoctaMap(s16, u8, u8, int);
    void setPaneOnOff(J2DScreen*, u32, bool);
    void getCollectMapTexChange();
    void finCollectMapTexChange();
    int calcGetCollectMap();
    int calcGetCollectMap2();
    int calcFinCollectMap();
    int getNowCmapFirstNum();
    int getNowCmapNextNum(s8, int);
    aramCmapDatPnt_t* getCmapDatPnt4(int);
    void readPaneCmapTexture(const ResTIMG*, int);
    void readFmapTexture(const char*);
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

public:
    /* 0x0004 */ void* mChkPntTxt_p;
    /* 0x0008 */ void* mCmapTxtMain_p[2];
    /* 0x0010 */ dMenu_FmapSv_c* fmapSv;
    /* 0x0014 */ u8 padding_0x14[0x18 - 0x14];
    /* 0x0018 */ mDoDvdThd_mountArchive_c* field_0x18;
    /* 0x001C */ aramCmapDat_c* mpFmapDatPnt;
    /* 0x0020 */ dDlst_FMAP2_c fmap2Dl;
    /* 0x0028 */ dDlst_FMAP2GS_c fmap2GsDl;
    /* 0x0030 */ STControl* stick;
    /* 0x0034 */ JUTFont* field_0x34;
    /* 0x0038 */ JUTFont* field_0x38;
    /* 0x003C */ dDlst_2DOutFont_c* outFont[2];
    /* 0x0044 */ dDlst_2DOutFont_c* outFontS[2];
    /* 0x004C */ fopMsgM_pane_class mClPane;
    /* 0x0084 */ fopMsgM_pane_class mFc0xPanes[4];
    /* 0x0164 */ fopMsgM_pane_class mFc1xPanes[4];
    /* 0x0244 */ fopMsgM_pane_class mCc0xPanes[4];
    /* 0x0324 */ fopMsgM_pane_class mCc1xPanes[4];
    /* 0x0404 */ fopMsgM_pane_class mKdmPane;
    /* 0x043c */ fopMsgM_pane_class field_0x43c[5];
    /* 0x0554 */ fopMsgM_pane_class field_0x554[17];
    /* 0x090C */ fopMsgM_pane_class field_0x90c[17];
    /* 0x0CC4 */ fopMsgM_pane_class* field_0xcc4[2];
    /* 0x0CCC */ fopMsgM_pane_class mCi22Pane;
    /* 0x0D04 */ fopMsgM_pane_class mCi21Pane;
    /* 0x0D3C */ fopMsgM_pane_class mCi12Pane;
    /* 0x0D74 */ fopMsgM_pane_class mCi11Pane;
    /* 0x0DAC */ fopMsgM_pane_class mLnk3Pane;
    /* 0x0DE4 */ fopMsgM_pane_class mAreaPane;
    /* 0x0E1C */ fopMsgM_pane_class field_0xe1c[2];
    /* 0x0E8C */ fopMsgM_pane_class mCmyuPane;
    /* 0x0EC4 */ fopMsgM_pane_class mCmydPane;
    /* 0x0EFC */ fopMsgM_pane_class mCnd0Pane;
    /* 0x0F34 */ fopMsgM_pane_class mCm1xPanes[2];
    /* 0x0FA4 */ fopMsgM_pane_class mCm2xPanes[2];
    /* 0x1014 */ fopMsgM_pane_class field_0x1014[5];
    /* 0x112C */ fopMsgM_pane_class field_0x112c[5];
    /* 0x1244 */ fopMsgM_pane_class* field_0x1244[2];
    /* 0x124C */ fopMsgM_pane_class* field_0x124c[2];
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
    /* 0x1484 */ fopMsgM_pane_class field_0x1484[8];
    /* 0x1644 */ fopMsgM_pane_class field_0x1644[10];
    /* 0x1874 */ fopMsgM_pane_class field_0x1874[10];
    /* 0x1AA4 */ fopMsgM_pane_class* field_0x1aa4[2];
    /* 0x1AAC */ fopMsgM_pane_alpha_class mMs01PaneAlpha;
    /* 0x1AB4 */ fopMsgM_pane_alpha_class mMs02PaneAlpha;
    /* 0x1ABC */ fopMsgM_pane_alpha_class mSd05PaneAlpha;
    /* 0x1AC4 */ fopMsgM_pane_alpha_class mHs04PaneAlpha;
    /* 0x1ACC */ fopMsgM_pane_alpha_class mYg01PaneAlpha;
#if VERSION == VERSION_DEMO
    /* 0x1AD4 */ fopMsgM_pane_alpha_class mWk3PaneAlpha;
#endif
    /* 0x1AD4 */ fopMsgM_pane_alpha_class mBsdmPaneAlpha;
    /* 0x1ADC */ fopMsgM_pane_alpha_class mTk0xPaneAlpha[7];
    /* 0x1B14 */ fopMsgM_pane_alpha_class mTkd2PaneAlpha;
    /* 0x1B1C */ fopMsgM_pane_alpha_class mTkd1PaneAlpha;
    /* 0x1B24 */ fopMsgM_pane_alpha_class mS02PaneAlpha;
    /* 0x1B2C */ fopMsgM_pane_alpha_class mKz05PaneAlpha;
    /* 0x1B34 */ fopMsgM_pane_alpha_class mKz01PaneAlpha;
#if VERSION == VERSION_DEMO
    /* 0x1B44 */ fopMsgM_pane_alpha_class mBt1PaneAlpha;
    /* 0x1B4C */ fopMsgM_pane_alpha_class mBt2PaneAlpha;
    /* 0x1B54 */ fopMsgM_pane_alpha_class mBt3PaneAlpha;
#endif
#if VERSION > VERSION_JPN
    /* 0x1B3C */ fopMsgM_pane_alpha_class mGsixPaneAlpha[7];
#endif
    /* 0x1B74 */ fopMsgM_pane_alpha_class mHk00PaneAlpha;
    /* 0x1B7C */ fopMsgM_pane_alpha_class mHk01PaneAlpha;
    /* 0x1B84 */ fopMsgM_pane_alpha_class mHn19PaneAlpha;
    /* 0x1B8C */ fopMsgM_pane_alpha_class mHk29PaneAlpha;
    /* 0x1B94 */ fopMsgM_pane_class mGddmPane;
    /* 0x1BCC */ fopMsgM_pane_alpha_class field_0x1bcc[22];
    /* 0x1C7C */ fopMsgM_pane_class mLnkPane;
    /* 0x1CB4 */ fopMsgM_pane_class mGdgtPane;
#if VERSION > VERSION_JPN
    /* 0x1CEC */ u8 padding_0x1cec[0x27a1 - 0x1CEC];
#else
    /* 0x1CB4 */ u8 padding_0x1cb4[0x25D9 - 0x1CB4];
#endif
    /* 0x27A1 */ u8 field_0x27a1;
    /* 0x27A2 */ u8 padding_0x27a2[0x27A8 - 0x27A2];
    /* 0x27A8 */ u8 field_0x27a8;
    /* 0x27A9 */ s8 field_0x27a9;
    /* 0x27AA */ u8 field_0x27aa;
    /* 0x27AB */ s8 field_0x27ab;
    /* 0x27AC */ s16 field_0x27ac;
    /* 0x27AE */ u8 padding_0x27ae[0x27B0 - 0x27AE];
    /* 0x27B0 */ f32 field_0x27b0;
    /* 0x27B4 */ f32 field_0x27b4;
    /* 0x27B8 */ f32 field_0x27b8;
    /* 0x27BC */ s8 field_0x27bc;
    /* 0x27BD */ s8 field_0x27bd;
    /* 0x27C0 */ char* field_0x27c0[2];
    /* 0x27C8 */ char* field_0x27c8[4];
    /* 0x27D8 */ char* field_0x27d8;
    /* 0x27DC */ char* field_0x27dc;
    /* 0x27E0 */ char* field_0x27e0;
    /* 0x27E4 */ char* field_0x27e4;
    /* 0x27E8 */ char* field_0x27e8;
    /* 0x27EC */ char* field_0x27ec;
    /* 0x27F0 */ char* field_0x27f0;
    /* 0x27F4 */ char* field_0x27f4;
    /* 0x27F8 */ u8 field_0x27f8;
    /* 0x27F9 */ u8 field_0x27f9;
    /* 0x27FA */ u8 field_0x27fa;
    /* 0x27FB */ u8 field_0x27fb;
    /* 0x27FC */ u8 field_0x27fc;
    /* 0x2800 */ f32 field_0x2800;
    /* 0x2804 */ f32 field_0x2804;
    /* 0x2808 */ f32 field_0x2808;
    /* 0x280C */ u8 field_0x280c;
    /* 0x280D */ u8 field_0x280d;
    /* 0x280E */ u8 field_0x280e;
    /* 0x280F */ u8 field_0x280f;
    /* 0x2810 */ u8 field_0x2810;
    /* 0x2811 */ u8 field_0x2811;
    /* 0x2812 */ u8 field_0x2812;
    /* 0x2813 */ u8 field_0x2813;
    /* 0x2814 */ u8 field_0x2814;
    /* 0x2815 */ u8 field_0x2815;
    /* 0x2816 */ u8 field_0x2816;
    /* 0x2817 */ u8 field_0x2817;
    /* 0x2818 */ u8 field_0x2818;
    /* 0x2819 */ u8 field_0x2819;
    /* 0x281A */ u8 field_0x281a;
    /* 0x281B */ u8 field_0x281b;
    /* 0x281C */ u8 field_0x281c;
    /* 0x281D */ u8 padding_0x281d[0x2820 - 0x281D];
    /* 0x2820 */ JUtility::TColor color_0x2820;
    /* 0x2824 */ JUtility::TColor color_0x2824;
    /* 0x2828 */ JUtility::TColor color_0x2828;
    /* 0x282C */ JUtility::TColor color_0x282C;
    /* 0x2830 */ f32 field_0x2830;
    /* 0x2834 */ f32 field_0x2834;
    /* 0x2838 */ f32 field_0x2838;
    /* 0x283C */ f32 field_0x283c;
    /* 0x2840 */ f32 field_0x2840;
    /* 0x2844 */ f32 field_0x2844;
    /* 0x2848 */ u16 field_0x2848[2];
#if VERSION > VERSION_JPN
    /* 0x284C */ u8 field_0x284c;
    /* 0x284D */ u8 field_0x284d;
    /* 0x284E */ u8 field_0x284e;
    /* 0x284F */ u8 padding_0x284f[0x2854 - 0x284F];
#endif
#if VERSION == VERSION_DEMO
    // TODO: move these bytes to the correct offsets
    u8 pad4[0x50];
#endif
}; // Size: 0x2854

STATIC_ASSERT(sizeof(dMenu_Fmap2_c) == VERSION_SELECT(0x26F4, 0x2684, 0x2854, 0x2854));

class dMf2_HIO_c : public JORReflexible {
public:
    dMf2_HIO_c();
    virtual ~dMf2_HIO_c() {}

    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 field_0x5;
    /* 0x06 */ u8 field_0x6;
    /* 0x07 */ u8 field_0x7;
    /* 0x08 */ u8 field_0x8;
    /* 0x09 */ u8 field_0x9;
    /* 0x0A */ u8 field_0xa;
    /* 0x0B */ u8 field_0xb;
    /* 0x0C */ u8 field_0xc;
    /* 0x0D */ u8 field_0xd;
    /* 0x0E */ u8 field_0xe;
    /* 0x0F */ u8 field_0xf;
    /* 0x10 */ u8 field_0x10;
    /* 0x11 */ u8 field_0x11;
    /* 0x12 */ u8 field_0x12;
    /* 0x13 */ u8 field_0x13;
    /* 0x14 */ u8 field_0x14;
    /* 0x16 */ u16 field_0x16;
    /* 0x18 */ u8 field_0x18[0x1E - 0x18];
    /* 0x1E */ u8 field_0x1e;
    /* 0x1F */ u8 field_0x1f;
    /* 0x20 */ u8 field_0x20;
    /* 0x21 */ u8 field_0x21;
    /* 0x22 */ u8 field_0x22;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ u8 field_0x28;
    /* 0x29 */ u8 field_0x29[0x30 - 0x29];
    /* 0x30 */ u8 field_0x30;
    /* 0x31 */ u8 field_0x31;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ u8 field_0x38;
    /* 0x3A */ s16 field_0x3a;
    /* 0x3C */ u16 field_0x3c;
    /* 0x3E */ u8 field_0x3e;
    /* 0x3F */ u8 field_0x3f;
    /* 0x40 */ u8 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ u8 field_0x48;
    /* 0x49 */ u8 field_0x49;
    /* 0x4A */ u8 field_0x4a;
    /* 0x4B */ u8 field_0x4b;
    /* 0x4C */ u8 field_0x4c;
    /* 0x4D */ u8 field_0x4d;
    /* 0x4E */ u8 field_0x4e;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5c;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ u8 field_0x64;
    /* 0x68 */ f32 field_0x68;
    /* 0x6C */ f32 field_0x6c;
    /* 0x70 */ f32 field_0x70;
    /* 0x74 */ u8 field_0x74;
    /* 0x75 */ u8 field_0x75;
    /* 0x76 */ u8 field_0x76;
    /* 0x77 */ u8 field_0x77;
    /* 0x78 */ u8 field_0x78;
    /* 0x79 */ u8 field_0x79;
    /* 0x7A */ u8 field_0x7a;
    /* 0x7B */ u8 field_0x7b;
    /* 0x7C */ u8 field_0x7c;
    /* 0x7D */ u8 field_0x7d;
    /* 0x7E */ u8 field_0x7e;
    /* 0x7F */ u8 field_0x7f;
    /* 0x80 */ u8 field_0x80;
    /* 0x81 */ u8 field_0x81;
    /* 0x82 */ u8 field_0x82;
    /* 0x83 */ u8 field_0x83;
    /* 0x84 */ u8 field_0x84;
    /* 0x85 */ u8 field_0x85;
    /* 0x86 */ u8 field_0x86;
    /* 0x87 */ u8 field_0x87;
    /* 0x88 */ u8 field_0x88;
    /* 0x89 */ u8 field_0x89;
    /* 0x8A */ u8 field_0x8a;
    /* 0x8B */ u8 field_0x8b;
    /* 0x8C */ u8 field_0x8c;
    /* 0x8D */ u8 field_0x8d;
#if VERSION > VERSION_JPN
    /* 0x8E */ u8 field_0x8e;
    /* 0x8F */ u8 field_0x8f;
    /* 0x90 */ u8 field_0x90;
    /* 0x91 */ u8 field_0x91;
    /* 0x92 */ u8 field_0x92;
    /* 0x93 */ u8 field_0x93;
    /* 0x94 */ u8 field_0x94;
#endif
};

#endif /* D_MENU_FMAP2_H */
