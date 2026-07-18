#ifndef D_PICTURE_BOX_H
#define D_PICTURE_BOX_H

#include "dolphin/types.h"
#include "f_op/f_op_msg.h"
#include "f_op/f_op_msg_mng.h"
#include "d/d_drawlist.h"
#include "JSystem/J2DGraph/J2DScreen.h"
#include "JSystem/J2DGraph/J2DTextBox.h"
#include "d/d_lib.h"


class J3DModel;
class JKRExpHeap;
class J2DScreen;
class J2DTextBox;
class mDoDvdThd_toMainRam_c;
struct fopMsgM_pane_class;
struct fopMsgM_pane_alpha_class;

enum dJlePbExecState {
    PB_EXEC_CAMERA_OPEN_e = 0x0,
    PB_EXEC_CAMERA_MOVE_e = 0x1,
    PB_EXEC_BROWSE_OPEN_e = 0x2,
    PB_EXEC_BROWSE_MOVE_e = 0x3,
    PB_EXEC_GET_OPEN_e = 0x4,
    PB_EXEC_GET_MOVE_e = 0x5,
    PB_EXEC_CLOSE_e = 0x6,
    PB_EXEC_CLOSED_e = 0x7,
};

enum dJlePbModeSubState {
    PB_SUB_IDLE_e = 0x0,
    PB_SUB_CONFIRM_e = 0x1,
    PB_SUB_SHIFT_1_TO_0_e = 0x2,
    PB_SUB_SHIFT_0_TO_2_e = 0x3,
    PB_SUB_SHIFT_0_TO_1_e = 0x4,
    PB_SUB_SHIFT_2_TO_0_e = 0x5,
};

enum dJlePbViewMode {
    PB_VIEW_CAMERA_e = 0x0,
    PB_VIEW_BROWSE_e = 0x1,
    PB_VIEW_GET_e = 0x2,
};

struct dPbPhotoSlotData {
    /* 0x0000 */ u8 pad[0x1EE0 - 0x0000];
    /* 0x1EE0 */ u32 mSnapResultId;
    /* 0x1EE4 */ u8 mSnapResultDetail;
    /* 0x1EE5 */ u8 mPhotoFormat;
};

void dPb_erasePicture();

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
    bool label_sort();
    u8 getPicLabelData(u8);
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
    /* 0x004 */ J2DScreen* scrn;
    /* 0x008 */ J2DScreen* scrn1;
    /* 0x00C */ J2DScreen* scrn2;
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
    /* 0xF60 */ fopMsgM_pane_alpha_class pane_tx[4];
    /* 0xF80 */ mDoDvdThd_toMainRam_c* mImportedPhotoLoadReq; // Async request for imported gallery photo data.
    /* 0xF84 */ J2DPicture* mMsgIconFontMainPic; // Message icon sheet used by fopMsgM_outFontDraw.
    /* 0xF88 */ J2DPicture* mMsgIconFontSubPic; // Secondary icon sheet used by fopMsgM_outFontDraw.
    /* 0xF8C */ J2DPicture* mMsgSelectArrowPic; // Select-arrow sprite for two-choice message prompts.
    /* 0xF90 */ JUTFont* font0;
    /* 0xF94 */ JUTFont* font1;
    /* 0xF98 */ STControl* stick;
    /* 0xF9C */ u8 mF9C[0xFA0 - 0xF9C];
    /* 0xFA0 */ mesg_header* head_p;
    /* 0xFA4 */ JMSMesgEntry_c mMsgEntry; // Current parsed message entry metadata.
    /* 0xFBC */ fopMsgM_msgDataProc_c mMsgDataProc; // Message parser/layout state and choice helper.
    /* 0x125C */ JUtility::TColor icn_white;
    /* 0x1260 */ JUtility::TColor icn_black;
    /* 0x1264 */ JUtility::TColor emp_white;
    /* 0x1268 */ JUtility::TColor emp_black;
    /* 0x126C */ dPbPhotoSlotData* mPhotoBuffer[4]; // Three saved slots + one import/get temporary slot.
    /* 0x127C */ f32 mZoomScale;
    /* 0x1280 */ f32 mShutterLineX1[12];
    /* 0x12B0 */ f32 mShutterLineY1[12];
    /* 0x12E0 */ f32 mShutterLineX2[12];
    /* 0x1310 */ f32 mShutterLineY2[12];
    /* 0x1340 */ int mChoiceCursorX0; // X anchor for first message choice marker.
    /* 0x1344 */ int mChoiceCursorX1; // X anchor for second message choice marker.
    /* 0x1348 */ int mChoiceCursorY; // Y anchor for message choice marker.
    /* 0x134C */ int mChoiceCursorYAlt; // Alternate Y anchor parsed from second choice token.
    /* 0x1350 */ char* mMsgTextBuffer[4]; // Output text buffers for the four message panes.
    /* 0x1360 */ s16 mFadeTimer; // Open/close fade timer.
    /* 0x1362 */ s16 mShutterCounter;
    /* 0x1364 */ s16 mMsgLineCount; // Cached message line count for vertical alignment.
    /* 0x1366 */ s16 mMsgIconDrawState; // Scratch state used by icon font setup/draw helpers.
    /* 0x1368 */ u8 mPictureSlotSortMap[3]; // Mapping from sorted slot order to source slot index.
    /* 0x136B */ u8 mExecState; // Top-level state machine used by execute dispatch (open/move/close/etc.).
    /* 0x136C */ u8 mModeSubState; // Per-mode substate (camera capture/select, browse erase/slide animation states).
    /* 0x136D */ u8 mViewMode; // Selects camera vs browse vs get-photo mode paths.
    /* 0x136E */ u8 mSelectedPhotoSlot; // Active browse slot index.
    /* 0x136F */ u8 mSelectedChoiceIndex; // Active index in two-choice message prompts.
    /* 0x1370 */ u8 mModeSwapActive; // Non-zero while shutter transition between camera/browse is running.
    /* 0x1371 */ u8 mPhotoSlotOccupied[3]; // Per-slot occupancy flags for saved photos.
    /* 0x1374 */ u8 mPhotoDeletedFlag; // Set when a photo was deleted during this session.
    /* 0x1375 */ u8 mChoiceArrowIconIdx; // Icon token index currently used for select-arrow placement.
    /* 0x1376 */ u8 mCaptureFormat;
};

class sub_pb_class : public msg_class {
public:
    /* 0x00FC */ JKRExpHeap* heap;
    /* 0x0100 */ dJle_Pb_c* dPb_c;
    /* 0x0104 */ dPbPhotoSlotData* buffer[4];
};
#endif /* D_PICTURE_BOX_H */
