#ifndef D_MENU_DMAP_H
#define D_MENU_DMAP_H

#include "JSystem/J2DGraph/J2DPicture.h"
#include "dolphin/types.h"
#include "d/d_menu_base.h"
#include "f_op/f_op_msg_mng.h"
#include "m_Do/m_Do_hostIO.h"

class J2DPane;
class J2DScreen;
struct fopMsgM_pane_class;
class JKRArchive;
class JUTFont;
class STControl;
class dMap_Dmap_c;
struct ResTIMG;

struct dMap_pane_c {
    /* 0x00 */ J2DPicture* ppane;
    /* 0x04 */ f32 field_0x04;
    /* 0x08 */ f32 field_0x08;
    /* 0x0C */ f32 field_0x0C;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ u8 padding_0x14[2];
    /* 0x16 */ u8 field_0x16;
    /* 0x17 */ u8 padding_0x17[1];
} /* Size: 0x18 */;

class dMenu_Dmap_c : public dMenu_base_c {
public:
    void alphaChange(fopMsgM_pane_class*, float) {}
    virtual void draw() { _draw(); }
    void setArchive(JKRArchive* arc) { mpArc = arc; }
    void setFont(JUTFont* font, JUTFont* rfont) {
        mFont = font;
        mRFont = rfont;
    }
    void setItemTexBuffer(int, void*) {}
    void setTextArea(char* name0, char* name1, char* note0, char* note1, char* dummy0, char* dummy1) {
        mTxtName[0] = name0;
        mTxtName[1] = name1;
        mTxtNote[0] = note0;
        mTxtNote[1] = note1;
        mTxtDummy[0] = dummy0;
        mTxtDummy[1] = dummy1;
    }

    void changeFloorTexture(J2DPane*, int);
    void screenSet();
    void initialize();
    void treasureSet();
    void treasureDraw();
    void paneMove(float);
    void paneAlpha(float);
    void decAlpha(float);
    void cursorMove();
    void cursorAnime();
    void noteInit();
    bool noteCheck();
    void noteAppear();
    void noteOpen();
    void noteClose();
    void noteOpenProc(short);
    void itemScale();
    void floorInit();
    void mapMove();
    void mapOffsetY();
    void itemnameMove();
    void dnameSet();
    void itemnameSet();
    void itemnoteSet();
    void outFontInit();
    void linkAnime();
    void bossAnime();
    void bossEyeAnime();
    virtual void _create();
    virtual void _delete();
    virtual void _move();
    virtual void _draw();
    virtual bool _open();
    virtual bool _close();

public:
    /* 0x0004 */ J2DScreen* scrn;
    /* 0x0008 */ J2DScreen* scrn2;
    /* 0x000C */ fopMsgM_pane_class mFtPanes[15];
    /* 0x0354 */ fopMsgM_pane_class mFdPanes[15];
    /* 0x069C */ fopMsgM_pane_class mCarPanes[4];
    /* 0x077C */ fopMsgM_pane_class mNm00Pane;
    /* 0x07B4 */ fopMsgM_pane_class mNm01Pane;
    /* 0x07EC */ fopMsgM_pane_class mItnmPane;
    /* 0x0824 */ fopMsgM_pane_class mItnkPane;
    /* 0x085C */ fopMsgM_pane_class mMsk0Pane;
    /* 0x0894 */ fopMsgM_pane_class mStr0Pane;
    /* 0x08CC */ fopMsgM_pane_class mSt00Pane;
    /* 0x0904 */ fopMsgM_pane_class mNt00Pane;
    /* 0x093C */ fopMsgM_pane_class mNk00Pane;
    /* 0x0974 */ fopMsgM_pane_class mNo11Pane;
    /* 0x09AC */ fopMsgM_pane_class mDtlePane;
    /* 0x09E4 */ fopMsgM_pane_class mDt00Pane;
    /* 0x0A1C */ fopMsgM_pane_class mDk00Pane;
    /* 0x0A54 */ fopMsgM_pane_class mItPanes[3];
    /* 0x0AFC */ fopMsgM_pane_class mIkPanes[3];
    /* 0x0BA4 */ fopMsgM_pane_class mIpPanes[3];
    /* 0x0C4C */ fopMsgM_pane_class mIp01Pane;
    /* 0x0C84 */ fopMsgM_pane_class mLnkPanes[3];
    /* 0x0D2C */ fopMsgM_pane_class mBey1Pane;
    /* 0x0D64 */ fopMsgM_pane_class mBey2Pane;
    /* 0x0D9C */ fopMsgM_pane_class mBossPane;
    /* 0x0DD4 */ fopMsgM_pane_class mBos2Pane;
    /* 0x0E0C */ u8 padding[0xE7C - 0xE0C];
    /* 0x0E7C */ fopMsgM_pane_class mFlPanes[6];
    /* 0x0FCC */ fopMsgM_pane_class mFbPanes[6];
    /* 0x111C */ fopMsgM_pane_class mFbkPanes[6];
    /* 0x126C */ fopMsgM_pane_class mFw00Pane;
    /* 0x12A4 */ fopMsgM_pane_class mFw01Pane;
    /* 0x12DC */ fopMsgM_pane_class mCc38Pane;
    /* 0x1314 */ fopMsgM_pane_class mCc31Pane;
    /* 0x134C */ fopMsgM_pane_class mCc24Pane;
    /* 0x1384 */ fopMsgM_pane_class mCc17Pane;
    /* 0x13BC */ fopMsgM_pane_class mCc10Pane;
    /* 0x13F4 */ fopMsgM_pane_class mCc05pane;
    /* 0x142C */ fopMsgM_pane_class mCc00Pane;
    /* 0x1464 */ fopMsgM_pane_class mMskPane;
    /* 0x149C */ STControl* stick;
    /* 0x14A0 */ dMap_Dmap_c* dmap_c;
    /* 0x14A4 */ JKRArchive* mpArc;
    /* 0x14A8 */ JUTFont* mFont;
    /* 0x14AC */ JUTFont* mRFont;
    /* 0x14B0 */ u8 field_0x14B0[0x14B4 - 0x14B0];
    /* 0x14B4 */ JUtility::TColor field_0x14B4;
    /* 0x14B8 */ JUtility::TColor field_0x14B8;
    /* 0x14BC */ JUtility::TColor field_0x14BC;
    /* 0x14C0 */ JUtility::TColor field_0x14C0;
    /* 0x14C4 */ JUtility::TColor field_0x14C4;
    /* 0x14C8 */ JUtility::TColor field_0x14C8;
    /* 0x14CC */ dMap_pane_c treasure_p[32];
    /* 0x17CC */ dMap_pane_c door_p[32];
    /* 0x1ACC */ dMap_pane_c npc_p;
    /* 0x1AE4 */ dMap_pane_c boss_p;
    /* 0x1AFC */ ResTIMG* mpTIMG[3];
    /* 0x1B08 */ fopMsgM_msgDataProc_c field_0x1B08;
    /* 0x1DA8 */ char* mTxtName[2];
    /* 0x1DB0 */ char* mTxtNote[2];
    /* 0x1DB8 */ char* mTxtDummy[2];
    /* 0x1DC0 */ char field_0x1DC0[0x1DCC - 0x1DC0];
    /* 0x1DCC */ f32 field_0x1DCC[4];
    /* 0x1DDC */ f32 field_0x1DDC[4];
    /* 0x1DEC */ f32 field_0x1DEC[4];
    /* 0x1DFC */ f32 field_0x1DFC[4];
    /* 0x1E0C */ s16 field_0x1E0C;
    /* 0x1E0E */ s16 field_0x1E0E;
    /* 0x1E10 */ s16 field_0x1E10;
    /* 0x1E12 */ s16 field_0x1E12;
    /* 0x1E14 */ s16 field_0x1E14;
    /* 0x1E16 */ u16 field_0x1E16;
    /* 0x1E18 */ s16 field_0x1E18;
    /* 0x1E1A */ s16 field_0x1E1A;
    /* 0x1E1C */ s16 field_0x1E1C;
    /* 0x1E1E */ u16 field_0x1E1E;
    /* 0x1E20 */ s16 field_0x1E20;
    /* 0x1E22 */ s16 field_0x1E22;
    /* 0x1E24 */ s16 field_0x1E24;
    /* 0x1E26 */ s16 field_0x1E26;
    /* 0x1E28 */ s16 field_0x1E28;
    /* 0x1E2A */ s16 field_0x1E2A;
    /* 0x1E2C */ s16 field_0x1E2C;
    /* 0x1E2E */ u8 field_0x1E2E;
    /* 0x1E2F */ u8 mCurFloor;
    /* 0x1E30 */ u8 mBossFloor;
    /* 0x1E31 */ u8 mTopFloor;
    /* 0x1E32 */ u8 mBottomFloor;
    /* 0x1E33 */ u8 field_0x1E33;
    /* 0x1E34 */ bool field_0x1E34;
    /* 0x1E35 */ bool field_0x1E35;
    /* 0x1E36 */ u8 field_0x1E36;
    /* 0x1E37 */ u8 pad;
}; // Size: 0x1E38

STATIC_ASSERT(sizeof(dMenu_Dmap_c) == 0x1E38);

class dMd_HIO_c : public JORReflexible {
public:
    dMd_HIO_c();
    virtual ~dMd_HIO_c() {}

    void genMessage(JORMContext*) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x06 */ s16 field_0x06;
    /* 0x08 */ s16 field_0x08;
    /* 0x0A */ s16 field_0x0A;
    /* 0x0C */ s16 field_0x0C;
    /* 0x0E */ u8 padding_0x0E[0x10 - 0x0E];
    /* 0x10 */ JUtility::TColor field_0x10;
    /* 0x14 */ JUtility::TColor field_0x14;
    /* 0x18 */ s16 field_0x18;
    /* 0x1A */ s16 field_0x1A;
    /* 0x1C */ JUtility::TColor field_0x1C;
    /* 0x20 */ JUtility::TColor field_0x20;
    /* 0x24 */ s16 field_0x24;
    /* 0x26 */ s16 field_0x26;
    /* 0x28 */ JUtility::TColor field_0x28;
    /* 0x2C */ JUtility::TColor field_0x2C;
    /* 0x30 */ s16 field_0x30;
    /* 0x32 */ s16 field_0x32;
    /* 0x34 */ JUtility::TColor field_0x34;
    /* 0x38 */ JUtility::TColor field_0x38;
    /* 0x3C */ s16 field_0x3C;
    /* 0x3E */ s16 field_0x3E;
    /* 0x40 */ s16 field_0x40;
    /* 0x42 */ s16 field_0x42;
    /* 0x44 */ s16 field_0x44;
    /* 0x46 */ s16 field_0x46;
    /* 0x48 */ s16 field_0x48;
}; // Size: 0x4C

STATIC_ASSERT(sizeof(dMd_HIO_c) == 0x4C);

extern dMd_HIO_c g_mdHIO;

#endif /* D_MENU_DMAP_H */
