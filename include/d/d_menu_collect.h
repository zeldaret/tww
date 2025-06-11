#ifndef D_MENU_COLLECT_H
#define D_MENU_COLLECT_H

#include "dolphin/types.h"
#include "JSystem/J2DGraph/J2DScreen.h"
#include "JSystem/J2DGraph/J2DTextBox.h"
#include "f_op/f_op_msg_mng.h"
#include "d/d_2dnumber.h"

struct fopMsgM_pane_class;
class JKRArchive;
class JUTFont;

class dMenu_Collect_c {
public:

    void alphaChange(fopMsgM_pane_class*, float) {}
    void draw() {}
    void getCollectMode() {}
    void getNowItem() {}
    void setArchive(JKRArchive*) {}
    void setFont(JUTFont*, JUTFont*) {}
    void setItemTexBuffer(int, void*) {}
    void setMapTexBuffer(void*) {}
    void setNowItem(unsigned char) {}
    void setOptionArchive(JKRArchive*) {}
    void setQuitArchive(JKRArchive*) {}
    void setSymbolTexBuffer(int, void*) {}
    void setTactTexBuffer(void*) {}
    void setTextArea(char*, char*, char*, char*, char*, char*) {}
    void setTimer(short) {}
    void setTriforceTexBuffer(int, void*) {}
    void setTriggerInfo(unsigned char) {}

    void screenSet();
    void initialize();
    void cursorAnime();
    void stickDirection(unsigned char);
    void cursorMainMove();
    void noteCheck();
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
    void _create();
    void _create3();
    void _delete();
    void _move();
    void _move3();
    void _draw();
    void _open();
    void _open3();
    void _close();
    void _close3();
    void animeStep1(short, short);
    void animeStep2(short, short);
    void animeStep3(short, short);
    void animeStep4(short, short);
    void _open2();
    void _close2();

    /* 0x000 */ u8 m000[0x004 - 0x000];
    /* 0x004 */ J2DScreen* m004;
    /* 0x008 */ fopMsgM_pane_class m008;
    /* 0x040 */ fopMsgM_pane_class m040;
    /* 0x078 */ fopMsgM_pane_class m078;
    /* 0x0B0 */ fopMsgM_pane_class m0B0[15];
    /* 0x3F8 */ fopMsgM_pane_class m3F8[15];
    /* 0x740 */ fopMsgM_pane_class m740;
    /* 0x778 */ fopMsgM_pane_class m778;
    /* 0x7B0 */ fopMsgM_pane_class m7B0;
    /* 0x7E8 */ fopMsgM_pane_class m7E8;
    /* 0x820 */ fopMsgM_pane_class m820;
    /* 0x858 */ fopMsgM_pane_class m858;
    /* 0x890 */ fopMsgM_pane_class m890;
    /* 0x8C8 */ fopMsgM_pane_class m8C8;
    /* 0x900 */ fopMsgM_pane_class m900;
    /* 0x938 */ fopMsgM_pane_class m938;
    /* 0x970 */ fopMsgM_pane_class m970;
    /* 0x9A8 */ fopMsgM_pane_class m9A8;
    /* 0x9E0 */ fopMsgM_pane_class m9E0;
    /* 0xA18 */ fopMsgM_pane_class mA18[4];
    /* 0xAF8 */ fopMsgM_pane_class mAF8;
    /* 0xB30 */ fopMsgM_pane_class mB30;
    /* 0xB68 */ fopMsgM_pane_class mB68[4];
    /* 0xC48 */ fopMsgM_pane_class mC48;
    /* 0xC80 */ fopMsgM_pane_class mC80;
    /* 0xCB8 */ fopMsgM_pane_class mCB8;
    /* 0xCF0 */ fopMsgM_pane_class mCF0;
    /* 0xD28 */ fopMsgM_pane_class mD28;
    /* 0xD60 */ fopMsgM_pane_class mD60;
    /* 0xD98 */ fopMsgM_pane_class mD98;
    /* 0xDD0 */ fopMsgM_pane_class mDD0;
    /* 0xE08 */ fopMsgM_pane_class mE08[8];
    /* 0xFC8 */ fopMsgM_pane_class mFC8;
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
    /* 0x2464 */ u8 m2464[0x2470 - 0x2464];
    /* 0x2470 */ JUTFont* m2470;
    /* 0x2474 */ JUTFont* m2474;
    /* 0x2478 */ J2DPane* m2478;
    /* 0x247C */ u8 m247C[0x2498 - 0x247C];
    /* 0x2498 */ ResTIMG* m2498;
    /* 0x249C */ ResTIMG* m249C;
    /* 0x24A0 */ ResTIMG* m24A0[6];
    /* 0x24B8 */ u8 m24B8[0x27A8 - 0x24B8];
    /* 0x27A8 */ f32 m27A8;
    /* 0x27AC */ f32 m27AC;
};

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
