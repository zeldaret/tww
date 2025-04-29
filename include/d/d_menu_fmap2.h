#ifndef D_MENU_FMAP2_H
#define D_MENU_FMAP2_H

#include "dolphin/types.h"

struct fopMsgM_pane_class;
class J2DScreen;
struct ResTIMG;
class aramCmapDat_c;
class dMenu_FmapSv_c;

class dMenu_Fmap2_c {
public:
    void getCmapDatPnt(int) {}
    void getCmapDatValue() {}
    void getCtActive() {}
    void getCtCmapSelNo() {}
    void getCtCurHX() {}
    void getCtCurHY() {}
    void getCtCurX() {}
    void getCtCurY() {}
    void getCtDispMode() {}
    void lineInter0to1ForU8(unsigned char, unsigned char, float) {}
    void setAramCmapDat(aramCmapDat_c*) {}
    void setCtActive(unsigned char) {}
    void setCtCmapSelNo(signed char) {}
    void setCtCurHX(signed char) {}
    void setCtCurHY(signed char) {}
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
    void spMapLoadForDVD(unsigned char);
    void cmapOpenCheck();
    void CmapScroll();
    void isSpMap(int);
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
    void _open();
    void _close();
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
    void fmapPlayerPosDispCheck(float*, float*);
    void changeCmapName();
    void cmapPlayerPosDisp();
    void cmapSalvagePosDisp();
    void cmapPlayerPosDispCheck(float*, float*);
    void paneTransBase(short, unsigned char, float, float, unsigned char, unsigned char, int);
    void paneAlphaFmapBase(short, unsigned char, unsigned char, int);
    void paneAlphaCmapBase(short, unsigned char, unsigned char, int);
    void paneAlphaZoomCmapBase(short, unsigned char, float, float, unsigned char, unsigned char, int);
    void paneAlphaCmapName(short, unsigned char, unsigned char);
    void paneAlphaMessage2(short, unsigned char, unsigned char, int);
    void paneTranceMessage(short, unsigned char, float, float, float, float, unsigned char, unsigned char, int);
    void paneScaleXYChild(fopMsgM_pane_class*, float);
    void paneTransSelCmapCle(short, unsigned char, float, float, float, float, unsigned char, unsigned char, int);
    void paneTransSelCmapOpn(short, unsigned char, float, float, float, float, unsigned char, unsigned char, int);
    void paneAlphaGostShipMap(short, unsigned char, unsigned char, int);
    void paneAlphaTingleMap(short, unsigned char, unsigned char, int);
    void paneAlphaTreasureMap(short, unsigned char, unsigned char, int);
    void paneAlphaSubdanMap(short, unsigned char, unsigned char, int);
    void paneAlphaHeartMMap(short, unsigned char, unsigned char, int);
    void paneAlphaYaguraMap(short, unsigned char, unsigned char, int);
    void paneAlphaDfaliyMap(short, unsigned char, unsigned char, int);
    void paneAlphaHeartPMap(short, unsigned char, unsigned char, int);
    void paneAlphaTerryMap(short, unsigned char, unsigned char, int);
    void paneAlphaSubMaMap(short, unsigned char, unsigned char, int);
    void paneAlphaMoonMap(short, unsigned char, unsigned char, int);
    void paneAlphaDoctaMap(short, unsigned char, unsigned char, int);
    void setPaneOnOff(J2DScreen*, unsigned long, bool);
    void getCollectMapTexChange();
    void finCollectMapTexChange();
    void calcGetCollectMap();
    void calcGetCollectMap2();
    void calcFinCollectMap();
    void getNowCmapFirstNum();
    void getNowCmapNextNum(signed char, int);
    void getCmapDatPnt4(int);
    void readPaneCmapTexture(const ResTIMG*, int);
    void readFmapTexture(const char*);
    void getButtonIconMode();
    void isLockBbutton();
    void isGetCollectMap(signed char);
    void isOpenCollectMap(signed char);
    void isOpenCollectMapTriforce(signed char);
    void getCollectMapKind(signed char);
    void isCompleteCollectMap(signed char);
};

class dDlst_FMAP2_c {
public:
    void draw();
};

class dDlst_FMAP2GS_c {
public:
    void draw();
};

class dMf2_HIO_c {
public:
    dMf2_HIO_c();
};

#endif /* D_MENU_FMAP2_H */
