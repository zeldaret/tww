#ifndef D_OPERATE_WIND_H
#define D_OPERATE_WIND_H

#include "d/d_drawlist.h"
#include "f_op/f_op_msg.h"
#include "f_op/f_op_msg_mng.h"
#include "m_Do/m_Do_hostIO.h"
#include "JSystem/JUtility/TColor.h"

struct fopMsgM_pane_class;
class JKRExpHeap;
class J2DScreen;
class STControl;

class dOw_HIO_c : public mDoHIO_entry_c {
public:
    dOw_HIO_c();

    void genMessage(JORMContext* ctx);

public:
    /* 0x04 */ f32 field_0x04;
    /* 0x08 */ s16 field_0x08;
    /* 0x0A */ s16 field_0x0a;
    /* 0x0C */ s16 field_0x0c;
    /* 0x0E */ s16 field_0x0e;
    /* 0x10 */ s16 field_0x10;
    /* 0x12 */ s16 field_0x12;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ u8 field_0x18;
};

class dDlst_Ow_main_c : public dDlst_base_c {
public:
    inline void drawLine(int, f32, f32, f32, f32);
    void setLineColor(JUtility::TColor c) { color = c; }
    void setLineMax(int v) { mLineMax = v; }
    void setScreen(J2DScreen* s) { scrn = s; }
    
    void draw();

public:
    /* 0x004 */ J2DScreen* scrn;
    /* 0x008 */ JUtility::TColor color;
    /* 0x00C */ int mLineMax;
    /* 0x010 */ f32 mX1[50];
    /* 0x0D8 */ f32 mY1[50];
    /* 0x1A0 */ f32 mX2[50];
    /* 0x268 */ f32 mY2[50];
};

class dDlst_Ow_mask_c : public dDlst_base_c {
public:
    void setScreen(J2DScreen* s) { scrn = s; }
    
    void draw();

public:
    /* 0x004 */ J2DScreen* scrn;
};

class dOperate_wind_c {
public:
    virtual ~dOperate_wind_c() {}
    void setTimer(s16 i_timer) {
        mTimer = i_timer;
    }
    
    int dOw_angleRegular(f32);
    int dOw_stickControl(int, s16);
    void screenSet();
    void alphaSet(f32);
    void arrowColor1();
    void arrowColor2();
    void maskColor();
    void arrowDirection();
    void windSet();
    void ringScale(f32);
    void directionTrans(f32);
    void lineInit(f32);
    void lineDraw();
    void arrowRotate(fopMsgM_pane_class*, s16);
    void initialize();
    void _create();
    void _delete();
    void _move();
    void _draw();
    bool _open();
    bool _close();

public:
    /* 0x004 */ J2DScreen* scrn1;
    /* 0x008 */ J2DScreen* scrn2;
    /* 0x00C */ fopMsgM_pane_class field_0x0c;
    /* 0x044 */ fopMsgM_pane_class field_0x44;
    /* 0x07C */ fopMsgM_pane_class field_0x7c;
    /* 0x0B4 */ fopMsgM_pane_class field_0xb4;
    /* 0x0EC */ fopMsgM_pane_class field_0xec;
    /* 0x124 */ fopMsgM_pane_class field_0x124[2];
    /* 0x194 */ fopMsgM_pane_class field_0x194;
    /* 0x1CC */ fopMsgM_pane_class field_0x1cc[4];
    /* 0x2AC */ fopMsgM_pane_class field_0x2ac[8];
    /* 0x46C */ fopMsgM_pane_class field_0x46c[4];
    /* 0x54C */ fopMsgM_pane_alpha_class field_0x54c;
    /* 0x554 */ fopMsgM_pane_alpha_class field_0x554;
    /* 0x55C */ STControl* stick;
    /* 0x560 */ dDlst_Ow_main_c* mMain;
    /* 0x564 */ dDlst_Ow_mask_c* mMask;
#if VERSION == VERSION_PAL
    /* 0x568 */ ResTIMG* shipfontTimg;
#endif
    /* 0x568 */ J2DPicture::TCornerColor field_0x568;
    /* 0x578 */ J2DPicture::TCornerColor field_0x578;
    /* 0x588 */ J2DPicture::TCornerColor field_0x588;
    /* 0x598 */ f32 field_0x598[50];
    /* 0x660 */ f32 field_0x660[50];
    /* 0x728 */ f32 field_0x728[50];
    /* 0x7F0 */ f32 field_0x7f0[50];
    /* 0x8B8 */ f32 field_0x8b8;
    /* 0x8BC */ u8 field_0x8BC[0x8C0 - 0x8BC];
    /* 0x8C0 */ f32 mPosX;
    /* 0x8C4 */ f32 mPosY;
    /* 0x8C8 */ s16 mTimer;
    /* 0x8CA */ s16 field_0x8ca;
    /* 0x8CC */ s16 mDeg;
    /* 0x8CE */ s16 field_0x8ce;
    /* 0x8D0 */ int field_0x8d0;
    /* 0x8D4 */ u8 field_0x8d4;
};

class dOw_c : public msg_class {
public:
    inline void _close();
    inline bool _draw();
    inline void _move();
    inline void _open();

    JKRExpHeap* getHeap() {
        return heap;
    }

    u8 getStatus() {
        return status;
    }

    void setHeap(JKRExpHeap* h) {
        heap = h;
    }

    void setStatus(u8 i_status) {
        status = i_status;
    }

    void setTimer(s16 i_timer) {
        dOw_scrn->setTimer(i_timer);
    }

    void _create();
    void _delete();

public:
    /* 0x0FC */ JKRExpHeap* heap;
    /* 0x100 */ dOperate_wind_c* dOw_scrn;
    /* 0x104 */ u8 status;
};

#endif /* D_OPERATE_WIND_H */
