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
    void setScreen(J2DScreen*) {}
    
    void draw();

public:
    /* 0x004 */ J2DScreen* scrn;
};

class dOperate_wind_c {
public:
    virtual ~dOperate_wind_c() {}
    void setTimer(s16) {}
    
    static int dOw_angleRegular(f32);
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
    /* 0x00C */ fopMsgM_pane_class field_0x0c[5];
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
};

class dOw_c : public msg_class {
public:
    inline void _close();
    inline bool _draw();
    inline void _move();
    inline void _open();
    JKRExpHeap* getHeap() { return heap; }
    void getStatus() {}
    void setHeap(JKRExpHeap* h) { heap = h; }
    void setStatus(u8) {}
    void setTimer(s16) {}

    void _create();
    void _delete();

public:
    /* 0x0FC */ JKRExpHeap* heap;
    /* 0x100 */ dOperate_wind_c* dOw_scrn;
    /* 0x104 */ u8 field_0x104;
};

#endif /* D_OPERATE_WIND_H */
