#ifndef D_PICTURE_BOX_H
#define D_PICTURE_BOX_H

#include "dolphin/types.h"

class JKRExpHeap;
struct fopMsgM_pane_class;
struct fopMsgM_pane_alpha_class;

class sub_pb_class;

class dJle_Pb_c {
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
};
void dPb_erasePicture();
#endif /* D_PICTURE_BOX_H */
