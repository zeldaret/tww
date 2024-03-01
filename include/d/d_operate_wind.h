#ifndef D_OPERATE_WIND_H
#define D_OPERATE_WIND_H

#include "dolphin/types.h"
#include "JSystem/JUtility/TColor.h"

class fopMsgM_pane_class;
class JKRExpHeap;
class J2DScreen;

class dOw_HIO_c {
public:
    dOw_HIO_c();
};

class dDlst_Ow_main_c {
public:
    void drawLine(int, f32, f32, f32, f32) {}
    void setLineColor(JUtility::TColor) {}
    void setLineMax(int) {}
    void setScreen(J2DScreen*) {}
    
    void draw();
};

class dDlst_Ow_mask_c {
public:
    void setScreen(J2DScreen*) {}
    
    void draw();
};

class dOperate_wind_c {
public:
    void setTimer(s16) {}
    
    void dOw_angleRegular(f32);
    void dOw_stickControl(int, s16);
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
    void _open();
    void _close();
};

class dOw_c {
public:
    void _close() {}
    void _draw() {}
    void _move() {}
    void _open() {}
    void getHeap() {}
    void getStatus() {}
    void setHeap(JKRExpHeap*) {}
    void setStatus(u8) {}
    void setTimer(s16) {}
    
    void _create();
    void _delete();
};

#endif /* D_OPERATE_WIND_H */
