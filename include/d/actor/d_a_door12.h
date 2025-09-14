#ifndef D_A_DOOR12_H
#define D_A_DOOR12_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_door.h"

class daDoor12_c : public dDoor_info_c {
public:
    bool checkFlag(unsigned short flag) { return (m316 & flag) != 0; }
    inline BOOL execute();
    void offFlag(unsigned short flag) { m316 &= ~flag; }
    void onFlag(unsigned short flag) { m316 |= flag; }
    void setAction(unsigned char action) { m314 = action; }

    s32 chkMakeKey();
    void setKey();
    BOOL chkMakeStop();
    s32 chkStopF();
    s32 chkStopB();
    void setStop();
    BOOL chkStopOpen();
    void setStopDemo();
    BOOL chkStopClose();
    BOOL CreateHeap();
    u8 getShapeType();
    char* getArcName();
    s32 getBdlLf();
    s32 getBdlRt();
    s32 getDzb();
    f32 openWide();
    void setEventPrm();
    void openInit();
    BOOL openProc();
    void openEnd();
    void closeInit();
    BOOL closeProc();
    void closeEnd();
    void calcMtx();
    BOOL CreateInit();
    cPhs_State create();
    void demoProc();
    BOOL draw();

public:
    /* 0x2D0 */ request_of_phase_process_class mPhase;
    /* 0x2D8 */ J3DModel* mpLeftModel;
    /* 0x2DC */ J3DModel* mpRightModel;
    /* 0x2E0 */ dBgW* mpBgw;
    /* 0x2E4 */ dDoor_key2_c mKeyLock;
    /* 0x308 */ dDoor_stop_c mStopBars;
    /* 0x314 */ u8 m314;
    /* 0x315 */ u8 m315[0x1];
    /* 0x316 */ u16 m316;
    #if VERSION > VERSION_DEMO
    /* 0x318 */ s32 m318;
    #endif
    /* 0x31C */ f32 m31C;
}; // size = 0x320

#endif /* D_A_DOOR12_H */
