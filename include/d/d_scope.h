#ifndef D_SCOPE_H
#define D_SCOPE_H

#include "JSystem/J2DGraph/J2DTextBox.h"
#include "dolphin/types.h"
#include "f_op/f_op_msg.h"
#include "f_op/f_op_msg_mng.h"
#include "JSystem/JUtility/TColor.h"
#include "d/d_drawlist.h"

class J2DTextBox;

enum dScpTyp {
    dScpTyp_UNK0_e = 0,
    dScpTyp_UNK1_e = 1,
    dScpTyp_UNK2_e = 2,
};

class sub_scp_class : public msg_class {
public:
    /* 0x0FC */ JKRExpHeap* mpHeap;
    /* 0x100 */ mesg_header* head_p;
    /* 0x104 */ fopMsgM_pane_class mWcrsPane;
    /* 0x13C */ fopMsgM_pane_class mWnumPane;
    /* 0x174 */ fopMsgM_pane_class mWcrkPane;
    /* 0x1AC */ fopMsgM_pane_class mWnukPane;
    /* 0x1E4 */ fopMsgM_pane_class mWpbaPane;
    /* 0x21C */ fopMsgM_pane_class mWbapPane;
    /* 0x254 */ fopMsgM_pane_class mWpscPane;
    /* 0x28C */ fopMsgM_pane_class mYrtnPane;
    /* 0x2C4 */ fopMsgM_pane_class mYzomPane;
    /* 0x2FC */ fopMsgM_pane_class mCrtnPane;
    /* 0x334 */ fopMsgM_pane_class mCzomPane;
    /* 0x36C */ fopMsgM_pane_class mLrtnPane;
    /* 0x3A4 */ fopMsgM_pane_class mRzomPane;
    /* 0x3DC */ fopMsgM_pane_class mWpxxPanes[8];
    /* 0x59C */ fopMsgM_pane_class mYz80Pane;
    /* 0x5D4 */ fopMsgM_pane_class mDt80Pane;
    /* 0x60C */ J2DTextBox* mpTextBox;
    /* 0x610 */ J2DTextBox* mpRubyBox;
    /* 0x614 */ J2DTextBox* mpTextBoxSdw;
    /* 0x618 */ J2DTextBox* mpRubyBoxSdw;
    /* 0x61C */ JMSMesgEntry_c mMesgEntry;
    /* 0x634 */ fopMsgM_msgDataProc_c mMesgDataProc;
    /* 0x8D4 */ fopMsgM_msgGet_c mMsgGet;
    /* 0x8E4 */ J2DTextBox::TFontSize mFontSize;
    /* 0x8EC */ J2DTextBox::TFontSize mRubyFontSize;
    /* 0x8F4 */ JUtility::TColor mDotBlackOrig;
    /* 0x8F8 */ JUtility::TColor mDotBlackNow;
    /* 0x8FC */ JUtility::TColor mDotWhiteOrig;
    /* 0x900 */ JUtility::TColor mDotWhiteNow;
    /* 0x904 */ f32 field_0x904;
    /* 0x908 */ f32 field_0x908;
    /* 0x90C */ int mArrowBaseY;
    /* 0x910 */ f32 mZoomScale;
    /* 0x914 */ s16 field_0x914;
    /* 0x916 */ s16 mLineCount;
    /* 0x918 */ s16 field_0x918;
    /* 0x91C */ const char* mpMesgStr;
    /* 0x920 */ char* oTx;
    /* 0x924 */ char* oRb;
    /* 0x928 */ char* oTxSdw;
    /* 0x92C */ char* oRbSdw;
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
