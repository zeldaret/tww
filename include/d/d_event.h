#ifndef D_EVENT_D_EVENT_H
#define D_EVENT_D_EVENT_H

#include "global.h"

class fopAc_ac_c;

enum dEvtType_e {
    /* 0x00 */ dEvtType_TALK_e,
    /* 0x01 */ dEvtType_DOOR_e,
    /* 0x02 */ dEvtType_OTHER_e,
    /* 0x03 */ dEvtType_COMPULSORY_e,
    /* 0x04 */ dEvtType_POTENTIAL_e,
    /* 0x05 */ dEvtType_ITEM_e,
    /* 0x06 */ dEvtType_SHOWITEM_X_e,
    /* 0x07 */ dEvtType_SHOWITEM_Y_e,
    /* 0x08 */ dEvtType_SHOWITEM_Z_e,
    /* 0x09 */ dEvtType_CATCH_e,
    /* 0x0A */ dEvtType_TREASURE_e,
    /* 0x0B */ dEvtType_PHOTO_e,
    /* 0x0A */ dEvtType_CHANGE_e,
};

class dEvt_order_c {
public:
    ~dEvt_order_c() {}
    dEvt_order_c();

    /* 0x00 */ u16 mEventType;
    /* 0x02 */ u16 mFlag;
    /* 0x04 */ u16 mHindFlag;
    /* 0x08 */ fopAc_ac_c* mActor1;
    /* 0x0C */ fopAc_ac_c* mActor2;
    /* 0x10 */ s16 mEventId;
    /* 0x12 */ u16 mPriority;
    /* 0x14 */ s8 mNextOrderIdx;
    /* 0x15 */ u8 mEventInfoIdx;
};  // Size = 0x18

class dEvt_control_c {
public:
    dEvt_control_c();

    s32 orderOld(u16, u16, u16, u16, void*, void*, const void*);
    s32 order(u16, u16, u16, u16, void*, void*, s16, u8);
    void setParam(dEvt_order_c*);
    void beforeFlagProc(dEvt_order_c*);
    void afterFlagProc(dEvt_order_c*);
    void commonCheck(dEvt_order_c*, u16, u16);
    void talkCheck(dEvt_order_c*);
    void talkXyCheck(dEvt_order_c*);
    void photoCheck(dEvt_order_c*);
    void catchCheck(dEvt_order_c*);
    void talkEnd();
    void demoCheck(dEvt_order_c*);
    void demoEnd();
    void potentialCheck(dEvt_order_c*);
    void doorCheck(dEvt_order_c*);
    void itemCheck(dEvt_order_c*);
    void endProc();
    void checkChange();
    void changeProc();
    void checkStart();
    void soundProc();
    void check();
    void photoCheck();
    s32 moveApproval(void*);
    BOOL compulsory(void*, const char*, u16);
    void remove();
    void getStageEventDt();
    void nextStageEventDt(void*);
    int getPId(void*);
    fopAc_ac_c * convPId(unsigned int);
    void getTactFreeMStick(int);
    void getTactFreeCStick(int);
    void giveItemCut(u8);

    u8 getTalkXYBtn() { return mTalkButton; }
    bool chkTalkXY() { return mTalkButton == 1 || mTalkButton == 2 || mTalkButton == 3; }
    void setPtI_Id(u32 id) { mPtItem = id; }
    void setPtI(void* actor) { mPtItem = getPId(actor); }
    void setGtItm(u8 itemNo) { mGetItemNo = itemNo; }
    u8 getGtItm() { return mGetItemNo; }
    void setPtT(void* i_actor) { mPtTalk = getPId(i_actor); }
    u8 getPreItemNo() { return mItemNo; }
    
    f32 getCullRate() { return mCullFarClipRatio; }
    void setCullRate(f32 ratio) { mCullFarClipRatio = ratio; }
    
    u16 chkEventFlag(u16 flag) { return flag & mEventFlag; }
    void onEventFlag(u16 flag) { mEventFlag |= flag; }
    void offEventFlag(u16 flag) { mEventFlag &= ~flag; }
    void reset() { onEventFlag(8); }

    bool runCheck() { return mMode != 0; }

    /* 0x00 */ dEvt_order_c mOrder[8];
    /* 0xC0 */ u8 mOrderCount;
    /* 0xC1 */ u8 mFirstOrderIdx;
    /* 0xC2 */ u8 mMode;
    /* 0xC3 */ u8 mbEndProc;
    /* 0xC4 */ u32 mPt1;
    /* 0xC8 */ u32 mPt2;
    /* 0xCC */ int mPtTalk;
    /* 0xD0 */ u32 mPtItem;
    /* 0xD4 */ u8 mGetItemNo;
    /* 0xD5 */ u8 field_0xD5[0xD6 - 0xD5];
    /* 0xD6 */ s16 field_0xd6;
    /* 0xD8 */ s16 mEventId;
    /* 0xDA */ u8 mEventEndSound;
    /* 0xDB */ u8 field_0xdb;
    /* 0xDC */ u8 field_0xdc;
    /* 0xDD */ u8 field_0xdd;
    /* 0xDE */ u8 field_0xde;
    /* 0xDF */ u8 field_0xdf;
    /* 0xE0 */ u8 mTalkButton;
    /* 0xE1 */ u8 mItemNo;
    /* 0xE2 */ u8 mbInPhoto;
    /* 0xE3 */ u8 field_0xE3[0xE4 - 0xE3];
    /* 0xE4 */ f32 mCullFarClipRatio;
    /* 0xE8 */ u16 mEventFlag;
    /* 0xEA */ u8 mTactFreeMStick[4];
    /* 0xEE */ u8 mTactFreeCStick[4];
};  // Size = 0xF4

#endif /* D_EVENT_D_EVENT_H */
