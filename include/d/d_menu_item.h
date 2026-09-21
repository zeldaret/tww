#ifndef D_MENU_ITEM_H
#define D_MENU_ITEM_H

#include "d/d_menu_base.h"
#include "f_op/f_op_msg_mng.h"
#include "m_Do/m_Do_hostIO.h"
#include "JSystem/J2DGraph/J2DWindow.h"

struct fopMsgM_pane_class;
class JKRArchive;
class JUTFont;
class J2DPane;
class STControl;
class dDlst_2DOutFont_c;
class dMenu_save_c;
class JPABaseEmitter;

class dMenu_Item_c : public dMenu_base_c {
public:
    void alphaChange(fopMsgM_pane_class*, f32) {}
    virtual void draw() { _draw(); }
    u8 getItemMode() { return itemMode; }
    u8 getNowItem() { return nowItem; }
    void setNowItem(u8 val) { nowItem = val; }
    void setArchive(JKRArchive* arc) { archive = arc; }
    void setFont(JUTFont* i_font, JUTFont* i_rfont) {
        font[0] = i_font;
        font[1] = i_rfont;
    }
    void setItemTexBuffer(int idx, void* buffer) { itemTexBuffer[idx] = (ResTIMG*)buffer; }
    void setSubItemTexBuffer(int idx, void* buffer) { subItemTexBuffer[idx] = (ResTIMG*)buffer; }
    void setTextArea(char* name0, char* name1, char* note0, char* note1, char* dummy0, char* dummy1) {
        name[0] = name0;
        name[1] = name1;
        note[0] = note0;
        note[1] = note1;
        dummy[0] = dummy0;
        dummy[1] = dummy1;
    }
    void setTimer(s16 val) { timer = val; }
    void setTriggerInfo(u8 info) { triggerInfo = info; }

    void initialize();
    void screenSet();
    void cursorAnime();
    void cursorMainMove();
    void cursorSubMove();
    void checkMove();
    bool itemplaceCheck(int);
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
    void mainTrans(f32, f32);
    void titleTrans(f32, f32);
    void noteRotate(f32, f32);
    void nameTrans(f32, f32);
    void mainOpenProc(s16, s16, s16);
    void titleOpenProc(s16, s16);
    void noteOpenProc(s16, s16);
    void nameOpenProc(s16, s16);
    void numberSet(J2DPane*, u8);
    void numberColor(J2DPane*, u8);
    void itemNumberSet();
    void itemCheck(int);
    void itemBitCheck(bool);
    void arrowLightAnime();
    int bottleFwaterCheck();
    BOOL recollectBossCheck();
    void cornerMove();
    int equipBeastItem(int);
    virtual void _create();
    virtual void _delete();
    virtual void _move();
    virtual void _draw();
    virtual bool _open();
    virtual bool _close();
    bool _open2();
    bool _close2();

private:
    /* 0x0004 */ J2DScreen* scrn;
    /* 0x0008 */ fopMsgM_pane_class field_0x8;
    /* 0x0040 */ fopMsgM_pane_class field_0x40;
    /* 0x0078 */ fopMsgM_pane_class field_0x78;
    /* 0x00B0 */ fopMsgM_pane_class field_0xb0[15];
    /* 0x03F8 */ fopMsgM_pane_class field_0x3f8[15];
    /* 0x0740 */ fopMsgM_pane_class field_0x740;
    /* 0x0778 */ fopMsgM_pane_class field_0x778;
    /* 0x07B0 */ fopMsgM_pane_class field_0x7b0;
    /* 0x07E8 */ fopMsgM_pane_class field_0x7e8;
    /* 0x0820 */ fopMsgM_pane_class field_0x820;
    /* 0x0858 */ fopMsgM_pane_class field_0x858;
    /* 0x0890 */ fopMsgM_pane_class field_0x890[2];
    /* 0x0900 */ fopMsgM_pane_class field_0x900;
    /* 0x0938 */ fopMsgM_pane_class field_0x938;
    /* 0x0970 */ fopMsgM_pane_class field_0x970;
    /* 0x09A8 */ fopMsgM_pane_class field_0x9a8;
    /* 0x09E0 */ fopMsgM_pane_class field_0x9e0;
    /* 0x0A18 */ fopMsgM_pane_class field_0xa18[4];
    /* 0x0AF8 */ fopMsgM_pane_class field_0xaf8[8];
    /* 0x0CB8 */ fopMsgM_pane_class field_0xcb8[8];
    /* 0x0E78 */ fopMsgM_pane_class field_0xe78[8];
    /* 0x1038 */ fopMsgM_pane_class field_0x1038;
    /* 0x1070 */ fopMsgM_pane_class field_0x1070[8];
    /* 0x1230 */ fopMsgM_pane_class field_0x1230;
    /* 0x1268 */ fopMsgM_pane_class field_0x1268[9];
    /* 0x1460 */ fopMsgM_pane_class field_0x1460;
    /* 0x1498 */ fopMsgM_pane_class field_0x1498;
    /* 0x14D0 */ fopMsgM_pane_class field_0x14d0;
    /* 0x1508 */ fopMsgM_pane_class field_0x1508;
    /* 0x1540 */ fopMsgM_pane_class field_0x1540;
    /* 0x1578 */ fopMsgM_pane_class field_0x1578;
    /* 0x15B0 */ fopMsgM_pane_class field_0x15b0;
    /* 0x15E8 */ fopMsgM_pane_class field_0x15e8;
    /* 0x1620 */ fopMsgM_pane_class field_0x1620;
    /* 0x1658 */ fopMsgM_pane_class field_0x1658[21];
    /* 0x1AF0 */ fopMsgM_pane_class field_0x1af0[21];
    /* 0x1F88 */ fopMsgM_pane_class field_0x1f88[3];
    /* 0x2030 */ fopMsgM_pane_class field_0x2030[3];
    /* 0x20D8 */ fopMsgM_pane_class field_0x20d8[6];
    /* 0x2228 */ fopMsgM_pane_class field_0x2228;
    /* 0x2260 */ fopMsgM_pane_class field_0x2260;
    /* 0x2298 */ fopMsgM_pane_class field_0x2298;
    /* 0x22D0 */ fopMsgM_pane_class field_0x22d0;
    /* 0x2308 */ STControl* stick;
    /* 0x230C */ dDlst_2DOutFont_c* outFont;
    /* 0x2310 */ JKRArchive* archive;
    /* 0x2314 */ JUTFont* font[2];
    /* 0x231C */ J2DPane* field_0x231c;
    /* 0x2320 */ J2DWindow::TContentsColor field_0x2320;
    /* 0x2330 */ dMenu_save_c* dMs_c;
    /* 0x2334 */ ResTIMG* itemTexBuffer[21];
    /* 0x2388 */ u8 field_0x2388[0x2394 - 0x2388];
    /* 0x2394 */ ResTIMG* subItemTexBuffer[8];
    /* 0x23B4 */ ResTIMG* field_0x23b4;
#if VERSION == VERSION_PAL
    /* 0x23B8 */ ResTIMG* field_0x23b8_pal;
    /* 0x23BC */ ResTIMG* field_0x23bc_pal;
#endif
    /* 0x23B8 */ JPABaseEmitter* field_0x23b8[2];
    /* 0x23C0 */ f32 field_0x23c0[4];
    /* 0x23D0 */ f32 field_0x23d0[4];
    /* 0x23E0 */ char* name[2];
    /* 0x23E8 */ char* note[2];
    /* 0x23F0 */ char* dummy[2];
    /* 0x23F8 */ s16 timer;
    /* 0x23FA */ s16 field_0x23fa;
    /* 0x23FC */ s16 field_0x23fc;
    /* 0x23FE */ u8 itemMode;
    /* 0x23FF */ u8 nowItem;
    /* 0x2400 */ u8 field_0x2400;
    /* 0x2401 */ u8 field_0x2401;
    /* 0x2402 */ u8 field_0x2402;
    /* 0x2403 */ u8 field_0x2403;
    /* 0x2404 */ u8 field_0x2404;
    /* 0x2405 */ u8 field_0x2405;
    /* 0x2406 */ u8 field_0x2406[21];
    /* 0x241B */ u8 field_0x241B[0x241E - 0x241B];
    /* 0x241E */ u8 field_0x241e;
    /* 0x241F */ u8 field_0x241f;
    /* 0x2420 */ u8 field_0x2420;
    /* 0x2421 */ u8 triggerInfo;
    /* 0x2422 */ u8 field_0x2422;
}; // Size: 0x2424

#if VERSION < VERSION_PAL
STATIC_ASSERT(sizeof(dMenu_Item_c) == 0x2424);
#endif

class dMi_HIO_c : public JORReflexible {
public:
    dMi_HIO_c();
    virtual ~dMi_HIO_c() {}

    void genMessage(JORMContext* ctx) { UNUSED(ctx); }

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
