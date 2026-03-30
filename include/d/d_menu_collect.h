#ifndef D_MENU_COLLECT_H
#define D_MENU_COLLECT_H

#include "dolphin/types.h"
#include "JSystem/J2DGraph/J2DScreen.h"
#include "JSystem/J2DGraph/J2DTextBox.h"
#include "d/d_2dnumber.h"
#include "d/d_menu_base.h"
#include "f_op/f_op_msg_mng.h"

struct fopMsgM_pane_class;
class JKRArchive;
class JUTFont;

class dMenu_Collect_c : public dMenu_base_c {
public:
    virtual void draw() {}

    void alphaChange(fopMsgM_pane_class* pane, float alpha) { pane->mInitAlpha *= alpha; }
    void getCollectMode() {}
    void getNowItem() {}
    void setNowItem(unsigned char) {}

    void setArchive(JKRArchive* arc) { mpArc = arc; }
    void setOptionArchive(JKRArchive* arc) { mpOptArc = arc; }
    void setQuitArchive(JKRArchive* arc) { mpSaveArc = arc; }

    void setFont(JUTFont* font, JUTFont* rfont) {
        mFont = font;
        mRFont = rfont;
    }

    void setTactTexBuffer(void* ptr) { mTactTexBuffer = (ResTIMG*)ptr; }
    void setMapTexBuffer(void* ptr) { mMapTexBuffer = (ResTIMG*)ptr; }
    void setTriforceTexBuffer(int idx, void* ptr) { mTriforceTexBuffer[idx] = (ResTIMG*)ptr; }
    void setSymbolTexBuffer(int idx, void* ptr) { mSymbolTexBuffer[idx] = ptr; }
    void setItemTexBuffer(int idx, void* ptr) { mItemTexBuffer[idx] = ptr; }

    void setTextArea(char* name0, char* name1, char* note0, char* note1, char* dummy0, char* dummy1) {
        name[0] = name0;
        name[1] = name1;
        note[0] = note0;
        note[1] = note1;
        dummy[0] = dummy0;
        dummy[1] = dummy1;
    }

    void setTimer(short timer) { mTimer = timer; }
    void setTriggerInfo(unsigned char) {}

    void screenSet();
    void initialize();
    void cursorAnime();
    void stickDirection(unsigned char);
    void cursorMainMove();
    u8 noteCheck();
    void noteInit();
    void noteAppear();
    void noteOpen();
    void noteClose();
    void mainTrans(float, float);
    void subTrans(float, float);
    void titleTrans(float, float);
    void noteRotate(float, float);
    void nameTrans(float, float);
    void mainOpenProc(short, short, short);
    void subOpenProc(short, short, short);
    void titleOpenProc(short, short);
    void noteOpenProc(short, short);
    void nameOpenProc(short, short);
    void itemBitCheck();
    void itemScale();
    void collectPriority();
    void weponPriority();
    void tactGuideShow(unsigned char, bool);
    void tactDemoMode(unsigned char);
    void tactPlayMode(unsigned char);
    void tactTrans(unsigned char, float, float);
    void tactBaseShow();
    void cornerMove();
    void triforceAnime(unsigned char);
    void tactGuideHide();
    void itemnameMove();
    void itemnameSet();
    void itemnoteSet();
    void itemSet();
    void outFontInit();
    void outFontMove();
    void outFontDraw();
    void collectItemGetCheck(unsigned char);
    virtual void _create();
    void _create3();
    virtual void _delete();
    virtual void _move();
    void _move3();
    virtual void _draw();
    bool _open();
    bool _open3();
    bool _close();
    bool _close3();
    void animeStep1(short, short);
    void animeStep2(short, short);
    void animeStep3(short, short);
    void animeStep4(short, short);
    bool _open2();
    bool _close2();

    /* 0x0000 */ // vtable
    /* 0x0004 */ J2DScreen* m004;
    /* 0x0008 */ fopMsgM_pane_class m008;
    /* 0x0040 */ fopMsgM_pane_class m040;
    /* 0x0078 */ fopMsgM_pane_class m078;
    /* 0x00B0 */ fopMsgM_pane_class m0B0[15];
    /* 0x03F8 */ fopMsgM_pane_class m3F8[15];
    /* 0x0740 */ fopMsgM_pane_class m740;
    /* 0x0778 */ fopMsgM_pane_class m778;
    /* 0x07B0 */ fopMsgM_pane_class m7B0;
    /* 0x07E8 */ fopMsgM_pane_class m7E8;
    /* 0x0820 */ fopMsgM_pane_class m820;
    /* 0x0858 */ fopMsgM_pane_class m858;
    /* 0x0890 */ fopMsgM_pane_class m890;
    /* 0x08C8 */ fopMsgM_pane_class m8C8;
    /* 0x0900 */ fopMsgM_pane_class m900;
    /* 0x0938 */ fopMsgM_pane_class m938;
    /* 0x0970 */ fopMsgM_pane_class m970;
    /* 0x09A8 */ fopMsgM_pane_class m9A8;
    /* 0x09E0 */ fopMsgM_pane_class m9E0;
    /* 0x0A18 */ fopMsgM_pane_class mA18[4];
    /* 0x0AF8 */ fopMsgM_pane_class mAF8;
    /* 0x0B30 */ fopMsgM_pane_class mB30;
    /* 0x0B68 */ fopMsgM_pane_class mB68[4];
    /* 0x0C48 */ fopMsgM_pane_class mC48;
    /* 0x0C80 */ fopMsgM_pane_class mC80;
    /* 0x0CB8 */ fopMsgM_pane_class mCB8;
    /* 0x0CF0 */ fopMsgM_pane_class mCF0;
    /* 0x0D28 */ fopMsgM_pane_class mD28;
    /* 0x0D60 */ fopMsgM_pane_class mD60;
    /* 0x0D98 */ fopMsgM_pane_class mD98;
    /* 0x0DD0 */ fopMsgM_pane_class mDD0;
    /* 0x0E08 */ fopMsgM_pane_class mE08[8];
    /* 0x0FC8 */ fopMsgM_pane_class mFC8;
    /* 0x1000 */ fopMsgM_pane_class m1000[3];
    /* 0x10A8 */ fopMsgM_pane_class m10A8[3];
    /* 0x1150 */ fopMsgM_pane_class m1150[11];
    /* 0x13B8 */ fopMsgM_pane_class m13B8[3];
    /* 0x1460 */ fopMsgM_pane_class m1460;
    /* 0x1498 */ fopMsgM_pane_class m1498[6];
    /* 0x15E8 */ fopMsgM_pane_class m15E8[6];
    /* 0x1738 */ fopMsgM_pane_class m1738;
    /* 0x1770 */ fopMsgM_pane_class m1770;
    /* 0x17A8 */ fopMsgM_pane_class m17A8[6];
    /* 0x18F8 */ fopMsgM_pane_class m18F8[6];
    /* 0x1A48 */ fopMsgM_pane_class m1A48[6];
    /* 0x1B98 */ fopMsgM_pane_class m1B98[6];
    /* 0x1CE8 */ fopMsgM_pane_class m1CE8[6];
    /* 0x1E38 */ fopMsgM_pane_class m1E38[6];
    /* 0x1460 */ fopMsgM_pane_class m1F88;
    /* 0x1460 */ fopMsgM_pane_class m1FC0;
    /* 0x1460 */ fopMsgM_pane_class m1FF8;
    /* 0x2030 */ fopMsgM_pane_class m2030[5];
    /* 0x2148 */ fopMsgM_pane_class m2148[5];
    /* 0x2260 */ fopMsgM_pane_class m2260[5];
    /* 0x2378 */ fopMsgM_pane_class m2378;
    /* 0x23B0 */ fopMsgM_pane_class m23B0;
    /* 0x23E8 */ fopMsgM_pane_class m23E8;
    /* 0x2420 */ fopMsgM_pane_class m2420;
    /* 0x2458 */ u8 m2458[0x2460 - 0x2458];
    /* 0x2460 */ dDlst_2DOutFont_c* m2460;
    /* 0x2464 */ JKRArchive* mpArc;
    /* 0x2468 */ JKRArchive* mpOptArc;
    /* 0x246C */ JKRArchive* mpSaveArc;
    /* 0x2470 */ JUTFont* mFont;
    /* 0x2474 */ JUTFont* mRFont;
    /* 0x2478 */ J2DPane* m2478;
    /* 0x247C */ u8 m247C[0x2488 - 0x247C];
    /* 0x2488 */ JUtility::TColor color_2488;
    /* 0x248C */ JUtility::TColor color_248C;
    /* 0x2490 */ JUtility::TColor color_2490;
    /* 0x2494 */ JUtility::TColor color_2494;
    /* 0x2498 */ ResTIMG* mTactTexBuffer;
    /* 0x249C */ ResTIMG* mMapTexBuffer;
    /* 0x24A0 */ ResTIMG* mTriforceTexBuffer[8];
    /* 0x24C0 */ void* mSymbolTexBuffer[3];
    /* 0x24CC */ void* mItemTexBuffer[5];
    /* 0x24E0 */ fopMsgM_msgDataProc_c mMsgProc;
    /* 0x2780 */ u8 m2780[0x27A8 - 0x2780];
    /* 0x27A8 */ f32 m27A8;
    /* 0x27AC */ f32 m27AC;
    /* 0x27B0 */ char* name[2];
    /* 0x27B8 */ char* note[2];
    /* 0x27C0 */ char* dummy[2];
    /* 0x27C8 */ u8 m27C8[0x27E2 - 0x27C8];
    /* 0x27E2 */ u16 mTimer;
    /* 0x27E4 */ u8 m27E4[0x27EC - 0x27E4];
    /* 0x27EC */ u8 m27EC;
    /* 0x27ED */ u8 m27ED;
    /* 0x27EE */ u8 mCollectMode;
    /* 0x27EF */ u8 m27EF[0x27F4 - 0x27EF];
}; // Size: 0x27F4

STATIC_ASSERT(sizeof(dMenu_Collect_c) == 0x27F4);

class dMc_HIO_c {
public:
    dMc_HIO_c();
    virtual ~dMc_HIO_c() {}

public:
    /* 0x00 */ // vtable
    /* 0x04 */ u8 m04[0x44 - 0x04];
    /* 0x44 */ s16 m44;
    /* 0x46 */ s16 m46;
    /* 0x48 */ s16 m48;
    /* 0x4A */ s16 m4A;
    /* 0x4C */ s16 m4C;
    /* 0x4E */ s16 m4E;
    /* 0x50 */ s16 m50;
    /* 0x52 */ u8 m52;
    /* 0x53 */ u8 m53;
    /* 0x54 */ f32 m54;
    /* 0x58 */ JUtility::TColor m58;
    /* 0x5C */ u8 m5C;
    /* 0x5D */ u8 m5D;
};

#endif /* D_MENU_COLLECT_H */
