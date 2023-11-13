#ifndef D_A_SWHIT0_H
#define D_A_SWHIT0_H

#include "d/d_cc_d.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "dolphin/types.h"

class daSwhit0_c : public fopAc_ac_c {
public:
    ~daSwhit0_c() {
        
    }

    s32 getSwNo();
    u8 getEvNo();
    u8 getType();
    u8 getTimer();
    s32 getSwNo2();

    s32 CreateHeap();
    void decisionRtType();
    
    s32 CreateInit();
    s32 create();

    s32 checkHit();
    s32 DemoProc();

    s32 actionOffWait();
    s32 actionToOnReady();
    s32 actionToOnOrder();
    s32 actionToOnDemo();
    s32 actionOnWait();
    s32 actionOnTimer();

    void setDrawMtx();

    /* 0x0290 */ J3DModel* mpModel;
    /* 0x0294 */ mDoExt_bckAnm mAnm;
    /* 0x02A4 */ mDoExt_btkAnm mTexAnm;

    /* 0x02B8 */ dCcD_Stts mColStatus;
    /* 0x02F4 */ dCcD_Cyl mColCyl;
    /* 0x0424 */ dCcD_Sph mColSph;

    /* 0x0550 */ u8 mHitTimer;
    /* 0x0551 */ u8 mState;
    /* 0x0552 */ u8 mTimer;
    /* 0x0553 */ u8 mRetType;
    
    /* 0x0554 */ s16 mOnTimer;
    /* 0x0556 */ u16 mFlags;
    /* 0x0558 */ s16 mEventIdx;

    /* 0x055C */ s32 mStaffId;

    void onFlag(u16 flag) { mFlags |= flag; }
    void offFlag(u16 flag) { mFlags &= ~flag; }
    s32 checkFlag(u16 flag) { return mFlags & flag; }
};

#endif
