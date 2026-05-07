#ifndef D_MENU_ITEM_H
#define D_MENU_ITEM_H

#include "dolphin/types.h"
#include "d/d_menu_base.h"
#include "m_Do/m_Do_hostIO.h"

struct fopMsgM_pane_class;
class JKRArchive;
class JUTFont;
class J2DPane;

class dMenu_Item_c : public dMenu_base_c {
public:
    void alphaChange(fopMsgM_pane_class*, f32) {}
    virtual void draw() {}
    u8 getItemMode() { return mItemMode; }
    u8 getNowItem() { return mNowItem; }
    void setNowItem(u8 val) { mNowItem = val; }
    void setArchive(JKRArchive* arc) { mpArc = arc; }
    void setFont(JUTFont* font, JUTFont* rfont) {
        mFont = font;
        mRFont = rfont;
    }
    void setItemTexBuffer(int idx, void* buffer) { mItemTexBuffer[idx] = buffer; }
    void setSubItemTexBuffer(int idx, void* buffer) { mSubItemTexBuffer[idx] = buffer; }
    void setTextArea(char* name0, char* name1, char* note0, char* note1, char* dummy0, char* dummy1) {
        name[0] = name0;
        name[1] = name1;
        note[0] = note0;
        note[1] = note1;
        dummy[0] = dummy0;
        dummy[1] = dummy1;
    }
    void setTimer(s16 val) { mTimer = val; }
    void setTriggerInfo(u8 info) { mTriggerInfo = info; }

    void initialize();
    void screenSet();
    void cursorAnime();
    void cursorMainMove();
    void cursorSubMove();
    void checkMove();
    void itemplaceCheck(int);
    void itemDecide();
    void itemMove();
    void itemScale();
    void subWindowInit();
    void subWindowDelete();
    void subItemDecide();
    void itemnameMove();
    void itemnameSet();
    void itemnoteSet();
    void outFontInit();
    void outFontMove();
    void outFontDraw();
    u8 noteCheck();
    void noteInit();
    void noteAppear();
    void noteOpen();
    void noteClose();
    void mainTrans(float, float);
    void titleTrans(float, float);
    void noteRotate(float, float);
    void nameTrans(float, float);
    void mainOpenProc(short, short, short);
    void titleOpenProc(short, short);
    void noteOpenProc(short, short);
    void nameOpenProc(short, short);
    void numberSet(J2DPane*, unsigned char);
    void numberColor(J2DPane*, unsigned char);
    void itemNumberSet();
    void itemCheck(int);
    void itemBitCheck(bool);
    void arrowLightAnime();
    void bottleFwaterCheck();
    void recollectBossCheck();
    void cornerMove();
    void equipBeastItem(int);
    virtual void _create();
    virtual void _delete();
    virtual void _move();
    virtual void _draw();
    virtual bool _open();
    virtual bool _close();
    bool _open2();
    bool _close2();

private:
    /* 0x0004 */ u8 field_0x0004[0x2310 - 0x4];
    /* 0x2310 */ JKRArchive* mpArc;
    /* 0x2314 */ JUTFont* mFont;
    /* 0x2318 */ JUTFont* mRFont;
    /* 0x231C */ u8 padding_0x231C[0x2320 - 0x231C];
    /* 0x2320 */ JUtility::TColor color_0x2320;
    /* 0x2324 */ JUtility::TColor color_0x2324;
    /* 0x2328 */ JUtility::TColor color_0x2328;
    /* 0x232C */ JUtility::TColor color_0x232C;
    /* 0x2330 */ u8 field_0x2330[0x2334 - 0x2330];
    /* 0x2334 */ void* mItemTexBuffer[21];
    /* 0x2388 */ u8 padding_0x2388[0x2394 - 0x2388];
    /* 0x2394 */ void* mSubItemTexBuffer[9];
    /* 0x23B8 */ u8 padding_0x23B8[0x23E0 - 0x23B8];
    /* 0x23E0 */ char* name[2];
    /* 0x23E8 */ char* note[2];
    /* 0x23F0 */ char* dummy[2];
    /* 0x23F8 */ u16 mTimer;
    /* 0x23FA */ u8 field_0x23FA[0x23FE - 0x23FA];
    /* 0x23FE */ u8 mItemMode;
    /* 0x23FF */ u8 mNowItem;
    /* 0x2400 */ u8 padding_0x2400[0x2421 - 0x2400];
    /* 0x2421 */ u8 mTriggerInfo;
    /* 0x2422 */ u8 field_0x2422;
    /* 0x2423 */ u8 field_0x2423;
}; // Size: 0x2424

STATIC_ASSERT(sizeof(dMenu_Item_c) == 0x2424);

class dMi_HIO_c : public JORReflexible {
public:
    dMi_HIO_c();
    virtual ~dMi_HIO_c() {}

    static const int ARR_SIZE = 5;

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ f32 field_0x08;
    /* 0x0C */ s16 field_0x0C;
    /* 0x0E */ s16 arr_0x0E[ARR_SIZE];
    /* 0x18 */ s16 field_0x18;
    /* 0x1A */ s16 arr_0x1A[ARR_SIZE];
    /* 0x24 */ s16 field_0x24;
    /* 0x26 */ s16 field_0x26;
    /* 0x28 */ s16 field_0x28;
    /* 0x2A */ s16 field_0x2A;
    /* 0x2C */ s16 field_0x2C;
    /* 0x2E */ s16 field_0x2E;
    /* 0x30 */ s16 field_0x30;
    /* 0x32 */ s16 field_0x32;
    /* 0x34 */ s16 field_0x34;
    /* 0x36 */ s16 field_0x36;
    /* 0x38 */ s16 field_0x38;
    /* 0x3A */ s16 field_0x3A;
    /* 0x3C */ s16 field_0x3C;
    /* 0x3E */ s16 field_0x3E;
    /* 0x40 */ s16 field_0x40;
    /* 0x42 */ s16 field_0x42;
    /* 0x44 */ s16 field_0x44;
    /* 0x46 */ s16 field_0x46;
    /* 0x48 */ s16 field_0x48;
    /* 0x4A */ u8 padding_0x4A[0x4C - 0x4A];
    /* 0x4C */ JUtility::TColor mBlackColor;
    /* 0x50 */ JUtility::TColor mWhiteColor;
    /* 0x54 */ GXColor mClothColor;
    /* 0x58 */ GXColor mShadowColor;
    /* 0x5C */ u8 field_0x5C;
};

extern dMi_HIO_c g_miHIO;

#endif /* D_MENU_ITEM_H */
