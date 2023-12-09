#ifndef D_A_DOOR12_H
#define D_A_DOOR12_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_door.h"

class daDoor12_c : public dDoor_info_c {
public:
    void checkFlag(unsigned short) {}
    inline BOOL execute();
    void offFlag(unsigned short) {}
    void onFlag(unsigned short) {}
    void setAction(unsigned char) {}

    void chkMakeKey();
    void setKey();
    void chkMakeStop();
    void chkStopF();
    void chkStopB();
    void setStop();
    void chkStopOpen();
    void setStopDemo();
    void chkStopClose();
    void CreateHeap();
    void getShapeType();
    void getArcName();
    void getBdlLf();
    void getBdlRt();
    void getDzb();
    void openWide();
    void setEventPrm();
    void openInit();
    void openProc();
    void openEnd();
    void closeInit();
    void closeProc();
    void closeEnd();
    void calcMtx();
    void CreateInit();
    s32 create();
    void demoProc();
    BOOL draw();

public:
    /* 0x2D0 */ request_of_phase_process_class m2D0;
    /* 0x2D8 */ J3DModel* mpLeftModel;
    /* 0x2DC */ J3DModel* mpRightModel;
    /* 0x2E0 */ dBgW* m2E0;
    /* 0x2E4 */ dDoor_key2_c mKeyLock;
    /* 0x308 */ dDoor_stop_c mStopBars;
    /* 0x314 */ u8 m314[0x35C - 0x314];
};

#endif /* D_A_DOOR12_H */
