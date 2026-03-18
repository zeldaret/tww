#ifndef D_MENU_ITEM_H
#define D_MENU_ITEM_H

#include "d/d_menu_collect.h"
#include "dolphin/types.h"

struct fopMsgM_pane_class;
class JKRArchive;
class JUTFont;
class J2DPane;

class dMenu_Item_c : public dMenu_base_c {
public:
    void alphaChange(fopMsgM_pane_class*, float) {}
    virtual void draw() {}
    void getItemMode() {}
    void getNowItem() {}
    void setArchive(JKRArchive*) {}
    void setFont(JUTFont*, JUTFont*) {}
    void setItemTexBuffer(int, void*) {}
    void setNowItem(unsigned char) {}
    void setSubItemTexBuffer(int, void*) {}
    void setTextArea(char*, char*, char*, char*, char*, char*) {}
    void setTimer(short) {}
    void setTriggerInfo(unsigned char) {}

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
    void noteCheck();
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
    virtual void _open();
    virtual void _close();
    void _open2();
    void _close2();
};

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
