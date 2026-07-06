#ifndef D_SCOPE_H
#define D_SCOPE_H

#include "dolphin/types.h"
#include "f_op/f_op_msg.h"
#include "f_op/f_op_msg_mng.h"
#include "JSystem/JUtility/TColor.h"
#include "d/d_drawlist.h"

class J2DTextBox;

class sub_scp_class : public msg_class {
public:
    /* 0x0FC */ JKRExpHeap* mpHeap;
    /* 0x100 */ mesg_header* head_p;
    /* 0x104 */ fopMsgM_pane_class mWipeCross;
    /* 0x13C */ fopMsgM_pane_class mWipeNum;
    /* 0x174 */ fopMsgM_pane_class mWipeCrossKage;
    /* 0x1AC */ fopMsgM_pane_class mWipeNumKage;
    /* 0x1E4 */ fopMsgM_pane_class mWipeBarA;
    /* 0x21C */ fopMsgM_pane_class mWipeBarPivot;
    /* 0x254 */ fopMsgM_pane_class mWipeScope;
    /* 0x28C */ fopMsgM_pane_class mCursorReturn;
    /* 0x2C4 */ fopMsgM_pane_class mCursorZoom;
    /* 0x2FC */ fopMsgM_pane_class mCursorReturnAnime;
    /* 0x334 */ fopMsgM_pane_class mCursorZoomAnime;
    /* 0x36C */ fopMsgM_pane_class mArrowL;
    /* 0x3A4 */ fopMsgM_pane_class mArrowR;
    /* 0x3DC */ fopMsgM_pane_class mWipePanel[8];
    /* 0x59C */ fopMsgM_pane_class mArrow;
    /* 0x5D4 */ fopMsgM_pane_class mDot;
    /* 0x60C */ J2DTextBox* mpTextBox;
    /* 0x610 */ J2DTextBox* mpRubyBox;
    /* 0x614 */ J2DTextBox* mpTextBoxSdw;
    /* 0x618 */ J2DTextBox* mpRubyBoxSdw;
    /* 0x61C */ JMSMesgEntry_c mMesgEntry;
    /* 0x634 */ fopMsgM_msgDataProc_c mMesgDataProc;
    /* 0x8D4 */ fopMsgM_msgGet_c mMsgGet;
    /* 0x8E4 */ f32 mFontSizeX;
    /* 0x8E8 */ f32 mFontSizeY;
    /* 0x8EC */ f32 mRubyFontSizeX;
    /* 0x8F0 */ f32 mRubyFontSizeY;
    /* 0x8F4 */ JUtility::TColor mDotBlackOrig;
    /* 0x8F8 */ JUtility::TColor mDotBlackNow;
    /* 0x8FC */ JUtility::TColor mDotWhiteOrig;
    /* 0x900 */ JUtility::TColor mDotWhiteNow;
    /* 0x904 */ f32 mOffsetX;
    /* 0x908 */ f32 mOffsetY;
    /* 0x90C */ int mArrowBaseY;
    /* 0x910 */ f32 mZoomScale;
    /* 0x914 */ s16 mTransTimer;
    /* 0x916 */ s16 mLineCount;
    /* 0x918 */ s16 mAnimeTimer;
    /* 0x91C */ const char* mpMesgStr;
    /* 0x920 */ void* oTx;
    /* 0x924 */ void* oRb;
    /* 0x928 */ void* oTxSdw;
    /* 0x92C */ void* oRbSdw;
    /* 0x930 */ u8 mDemoCloseFlag;
}; // Size: 0x934

class dDlst_2DSCP_c : public dDlst_base_c {
public:
    dDlst_2DSCP_c() {}
    virtual ~dDlst_2DSCP_c();
    virtual void draw();
    void outFontDraw();
    void setActorP(sub_scp_class* i_scp) { mpScp = i_scp; }

    /* 0x04 */ sub_scp_class* mpScp;
};

#endif /* D_SCOPE_H */
