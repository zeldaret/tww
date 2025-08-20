#ifndef D_A_KNOB00_H
#define D_A_KNOB00_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_door.h"

class daKnob00_c : public dDoor_info_c {
public:
    bool checkFlag(unsigned short bit) {
        return m312 & bit;
    }
    void nextAction() {
        mAction++;
    }
    void offFlag(unsigned short bit) {
        m312 &= ~bit;
    }
    void onFlag(unsigned short bit) {
        m312 |= bit;
    }
    void setAction(unsigned char action) {
        mAction = action;
    }

    BOOL CreateHeap();
    u8 getShapeType();
    void setEventPrm();
    u8 getType2();
    s32 chkPassward();
    BOOL msgDoor();
    void openInit(int);
    BOOL openProc(int);
    void openEnd();
    BOOL chkException();
    void calcMtx();
    BOOL CreateInit();
    cPhs_State create();
    void setStart(float, float);
    void setAngle();
    BOOL adjustmentProc();
    BOOL demoProc();
    BOOL demoProc2();
    BOOL actionWait();
    BOOL actionDemo();
    BOOL actionTalk();
    BOOL actionTalkWait();
    BOOL actionPassward2();
    BOOL actionVilla();
    BOOL actionPassward();
    BOOL actionInit();
    BOOL actionFigure();
    BOOL actionDead();
    BOOL draw();
    inline BOOL execute();

    static const char M_arcname[];

public:
    /* 0x2D0 */ dDoor_msg_c m2D0;
    /* 0x2DC */ request_of_phase_process_class mPhase;
    /* 0x2E4 */ J3DModel* mpModel;
    /* 0x2E8 */ mDoExt_bckAnm mBckAnm;
    /* 0x2F8 */ J3DModel* mpModel2;
    /* 0x2FC */ s8 m_jnt;
    /* 0x2FD */ u8 m2FD[0x300 - 0x2FD];
    /* 0x300 */ dBgW* mpBgW;
    /* 0x304 */ dDoor_stop_c mStopBars;
    /* 0x310 */ u8 mAction;
    /* 0x311 */ u8 m311[0x312 - 0x311];
    /* 0x312 */ u16 m312;
    /* 0x314 */ s16 m314;
    /* 0x316 */ u8 m316;
    /* 0x317 */ u8 mDoorType;
}; // size = 0x318

#endif /* D_A_KNOB00_H */
