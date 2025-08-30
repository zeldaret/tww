#ifndef D_MENU_OPTION_H
#define D_MENU_OPTION_H

#include "JSystem/J2DGraph/J2DScreen.h"
#include "d/d_drawlist.h"
#include "d/d_lib.h"
#include "f_op/f_op_msg_mng.h"
#include "m_Do/m_Do_hostIO.h"

struct fopMsgM_pane_class;
class JKRArchive;
class JUTFont;

class dMenu_Option_c : public dDlst_base_c {
public:
    void alphaChange(fopMsgM_pane_class*, f32) {}
    void getQuitStatus() {}
    void setArchive(JKRArchive* archive) {
        mpArchive = archive;
    }
    void setFont(JUTFont* font_1, JUTFont* font_2) {
        mD2C = font_1;
        mD30 = font_2;
    }
    void setTextArea(char* param_1, char* param_2, char* param_3, char* param_4) {
        mD38 = param_1;
        mD3C = param_2;
        mD40 = param_3;
        mD44 = param_4;
    }

    void screenSet();
    void mainInit();
    void noteInit();
    void titleInit();
    void mainMove();
    void noteMove();
    void titleMove();
    void cursorMove();
    void cursorScale();
    void typeMove();
    void yazAnime();
    void ccAnime();
    void stickMove(u8);
    void noteSet();
    void outFontInit();
    void outFontMove();
    void outFontDraw();
    f32 stringlength(fopMsgM_pane_class*, char*);
    void changeScaleCenter(fopMsgM_pane_class*, char*);
    void setSoundMode(u32);
    void changeScaleRight(fopMsgM_pane_class*, char*);
    void initialize();
    void _create();
    void _delete();
    void _move();
    void _draw();
    bool _open();
    bool _close();

private:
    /* 0x004 */ J2DScreen* scrn;
    /* 0x008 */ fopMsgM_pane_class m008;
    /* 0x040 */ fopMsgM_pane_class m040;
    /* 0x078 */ fopMsgM_pane_class m078;
    /* 0x0B0 */ fopMsgM_pane_class m0B0[15];
    /* 0x3F8 */ fopMsgM_pane_class m3F8[15];
    /* 0x740 */ fopMsgM_pane_class m740[2];
    /* 0x7B0 */ fopMsgM_pane_class m7B0;
    /* 0x7E8 */ fopMsgM_pane_class m7E8;
    /* 0x820 */ fopMsgM_pane_class m820;
    /* 0x858 */ fopMsgM_pane_class m858[2];
    /* 0x8C8 */ fopMsgM_pane_class m8C8[4];
    /* 0x9A8 */ fopMsgM_pane_class m9A8[2];
    /* 0xA18 */ fopMsgM_pane_class mA18[3];
    /* 0xAC0 */ fopMsgM_pane_class mAC0[2];
    /* 0xB30 */ fopMsgM_pane_class mB30[6];
    /* 0xC80 */ fopMsgM_pane_class mC80[2];
    /* 0xCF0 */ fopMsgM_pane_class mCF0;
    /* 0xD28 */ JKRArchive* mpArchive;
    /* 0xD2C */ JUTFont* mD2C;
    /* 0xD30 */ JUTFont* mD30;
    /* 0xD34 */ STControl* stick;
    /* 0xD38 */ char* mD38;
    /* 0xD3C */ char* mD3C;
    /* 0xD40 */ char* mD40;
    /* 0xD44 */ char* mD44;
    /* 0xD48 */ char mD48[20];
    /* 0xD5C */ char mD5C[2][20];
    /* 0xD84 */ char mD84[2][20];
    /* 0xDAC */ char mDAC[3][20];
    /* 0xDE8 */ char mDE8[4][20];
    /* 0xE38 */ u8 mE38;
    /* 0xE39 */ u8 mE39;
    /* 0xE3A */ u8 mE3A;
    /* 0xE3B */ u8 mE3B;
    /* 0xE3C */ u8 mE3C;
    /* 0xE3D */ u8 mE3D;
    /* 0xE3E */ u8 mE3E;
    /* 0xE3F */ u8 mE3F;
    /* 0xE40 */ u8 mE40;
    /* 0xE41 */ u8 mE41;
};  // Size: 0xE42

class dMo_HIO_c : public JORReflexible {
public:
    dMo_HIO_c();
    virtual ~dMo_HIO_c() {}

    void genMessage(JORMContext* ctx);

public:
    /* 0x04 */ s8 mNo;
};  // Size: 0x08


#endif /* D_MENU_OPTION_H */
