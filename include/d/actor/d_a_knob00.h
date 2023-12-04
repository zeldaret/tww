#ifndef D_A_KNOB00_H
#define D_A_KNOB00_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_door.h"

class daKnob00_c : public dDoor_info_c {
public:
    void checkFlag(unsigned short) {}
    inline BOOL execute();
    void nextAction() {}
    void offFlag(unsigned short) {}
    void onFlag(unsigned short) {}
    void setAction(unsigned char) {}

    void CreateHeap();
    void getShapeType();
    void setEventPrm();
    void getType2();
    void chkPassward();
    void msgDoor();
    void openInit(int);
    void openProc(int);
    void openEnd();
    void chkException();
    void calcMtx();
    void CreateInit();
    s32 create();
    void setStart(float, float);
    void setAngle();
    void adjustmentProc();
    void demoProc();
    void demoProc2();
    void actionWait();
    void actionDemo();
    void actionTalk();
    void actionTalkWait();
    void actionPassward2();
    void actionVilla();
    void actionPassward();
    void actionInit();
    void actionFigure();
    void actionDead();
    BOOL draw();

public:
    /* 0x2D0 */ dDoor_msg_c m2D0;
    /* 0x2DC */ u8 m2DC[0x2E4 - 0x2DC];
    /* 0x2E4 */ J3DModel* mpModel;
    /* 0x2E8 */ mDoExt_bckAnm mBckAnm;
    /* 0x2F8 */ J3DModel* mpModel2;
    /* 0x2FC */ bool mJoint;
    /* 0x2FD */ u8 m2FD[0x300 - 0x2FD];
    /* 0x300 */ dBgW* mpBgW;
    /* 0x304 */ u8 m304[0x310 - 0x304];
    /* 0x310 */ u8 mState;
    /* 0x311 */ u8 m311[0x312 - 0x311];
    /* 0x312 */ u16 m312;
    /* 0x314 */ s16 m314;
    /* 0x316 */ u8 m316[0x317 - 0x316];
    /* 0x317 */ u8 mDoorType;
    /* 0x318 */ u8 m318[0x400 - 0x318];
};

#endif /* D_A_KNOB00_H */
