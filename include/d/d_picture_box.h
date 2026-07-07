#ifndef D_PICTURE_BOX_H
#define D_PICTURE_BOX_H

#include "dolphin/types.h"
#include "f_op/f_op_msg.h"
#include "f_op/f_op_msg_mng.h"
#include "d/d_drawlist.h"
#include "JSystem/J2DGraph/J2DScreen.h"
#include "JSystem/J2DGraph/J2DTextBox.h"


class JKRExpHeap;
class J2DScreen;
class J2DTextBox;
struct fopMsgM_pane_class;
struct fopMsgM_pane_alpha_class;

struct sPhotoDat {
    /* 0x00 */ char* field_0x00;
    /* 0x04 */ char* field_0x04;
    /* 0x08 */ char* field_0x08;
    /* 0x0C */ char* field_0x0C;
    /* 0x10 */ char* field_0x10;
    /* 0x14 */ char* field_0x14;
    /* 0x18 */ char* field_0x18;
};

class sub_pb_class : public msg_class {
public:
    /* Place member variables here */
};

class dJle_Pb_c : public dDlst_base_c {
public:
    void alphaChange(fopMsgM_pane_alpha_class*, f32) {}
    void alphaChange(fopMsgM_pane_class*, f32) {}
    void getMemory(void*, int) {}
    void getStatus() {}
    void setTextArea(char*, int) {}
    
    void screenSet();
    void screenSet2();
    void cameraAlphaInc(f32);
    void browseAlphaInc(f32);
    void getAlphaInc(f32);
    void alphaDec(f32);
    void zoomScale();
    void changeScale(int);
    void up_downIconMove();
    void left_rightIconMove();
    void clickShutterMode();
    void selectMode();
    void cameraMode();
    void pictureDraw(u8, int);
    void pictureEraseWait();
    void pictureDecide();
    void pictureErase();
    void pictureTransX(f32, f32, f32, f32, f32);
    void changePicture();
    void shutterChange();
    void moveCamera();
    void moveBrowse();
    void selectBrowse();
    void getBrowse();
    void changeBrowseToCamera();
    void changeCameraToBrowse();
    void setColorInit(u8);
    void setColorAnime(u8);
    void changeData();
    void label_sort();
    void getPicLabelData(u8);
    void shutterLineRotateCenter(f32, int);
    void shutterLineRotateInitPos(f32, int);
    void shutterLineMove();
    void shutterLineDraw(u8);
    void messageSet(u32);
    void remainMessageSet(u8);
    void existMessageSet(u8);
    void shutterShow();
    void shutterHide();
    void _create(JKRExpHeap*);
    void _copen();
    void _bopen();
    void _gopen();
    void _close();
    void _cmove();
    void _bmove();
    void _gmove();
    void draw();
    void _delete(JKRExpHeap*);

public:
    /* 0x004 */ J2DScreen* scrn_04;
    /* 0x008 */ J2DScreen* scrn_08;
    /* 0x00C */ J2DScreen* scrn_0C;
    /* 0x010 */ fopMsgM_pane_class pane_st[12];
    /* 0x2B0 */ fopMsgM_pane_class pane_sb[12];
    /* 0x550 */ fopMsgM_pane_class pane_ylig;
    /* 0x588 */ fopMsgM_pane_class pane_ylef;
    /* 0x5C0 */ fopMsgM_pane_class pane_icn[3];
    /* 0x668 */ fopMsgM_pane_class pane_emp[3];
    /* 0x710 */ fopMsgM_pane_class pane_ct1;
    /* 0x748 */ fopMsgM_pane_class pane_ct2;
    /* 0x780 */ fopMsgM_pane_class pane_sp[8];
    /* 0x940 */ fopMsgM_pane_class pane_no[3];
    /* 0x9E8 */ fopMsgM_pane_class pane_nob[3];
    /* 0xA90 */ fopMsgM_pane_class pane_nok[3];
    /* 0xB38 */ fopMsgM_pane_class pane_b1;
    /* 0xB70 */ fopMsgM_pane_class pane_b2;
    /* 0xBA8 */ fopMsgM_pane_class pane_wnum;
    /* 0xBE0 */ fopMsgM_pane_class pane_wnuk;
    /* 0xC18 */ fopMsgM_pane_class pane_wpba;
    /* 0xC50 */ fopMsgM_pane_class pane_wbap;
    /* 0xC88 */ fopMsgM_pane_class pane_wpsc;
    /* 0xCC0 */ fopMsgM_pane_class pane_yrtn;
    /* 0xCF8 */ fopMsgM_pane_class pane_yzom;
    /* 0xD30 */ fopMsgM_pane_class pane_crtn;
    /* 0xD68 */ fopMsgM_pane_class pane_czom;
    /* 0xDA0 */ fopMsgM_pane_class pane_lrtn;
    /* 0xDD8 */ fopMsgM_pane_class pane_rzom;
    /* 0xE10 */ fopMsgM_pane_class pane_shut;
    /* 0xE48 */ fopMsgM_pane_class pane_fd00;
    /* 0xE80 */ fopMsgM_pane_class pane_wp04;
    /* 0xEB8 */ fopMsgM_pane_class pane_wp01;
    /* 0xEF0 */ fopMsgM_pane_class pane_wp02;
    /* 0xF28 */ fopMsgM_pane_class pane_wp03;
    /* 0xF60 */ fopMsgM_pane_alpha_class pane_tx82;
    /* 0xF68 */ fopMsgM_pane_alpha_class pane_tx83;
    /* 0xF70 */ fopMsgM_pane_alpha_class pane_tx80;
    /* 0xF78 */ fopMsgM_pane_alpha_class pane_tx81;
    /* 0xF80 */ u8 mF80[0xF90 - 0xF80];
    /* 0xF90 */ JUTFont* mF90;
    /* 0xF94 */ JUTFont* mF94;
    /* 0xF98 */ u8 mF98[0x125C - 0xF98];
    /* 0x125C */ JUtility::TColor icn_white;
    /* 0x1260 */ JUtility::TColor icn_black;
    /* 0x1264 */ JUtility::TColor emp_white;
    /* 0x1268 */ JUtility::TColor emp_black;
    /* 0x126C */ u8 m126C[0x127C - 0x126C];
    /* 0x127C */ f32 mZoomScale;
    /* 0x1280 */ u8 m1280[0x136E - 0x1280];
    /* 0x136E */ u8 m136E;
    /* 0x136F */ u8 m136F[0x1371 - 0x136F];
    /* 0x1371 */ u8 m1371[3];
};
void dPb_erasePicture();
#endif /* D_PICTURE_BOX_H */
