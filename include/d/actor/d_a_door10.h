#ifndef D_A_DOOR10_H
#define D_A_DOOR10_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"
#include "d/d_door.h"

class daDoor10_c : public dDoor_info_c {
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
    void getBdlName();
    void getDzbName();
    void getSize2X();
    void CreateHeap();
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
    /* 0x2D0 */ dDoor_smoke_c m2D0;
    /* 0x306 */ u8 m306[0x308 - 0x306];
    /* 0x308 */ dDoor_key2_c mKeyLock;
    /* 0x32C */ dDoor_stop_c mStopBars;
    /* 0x338 */ dDoor_hkyo_c mHkyo;
    /* 0x34C */ J3DModel* mpModel;
    /* 0x350 */ dBgW* mpBgW;
    /* 0x354 */ u8 m354;
    /* 0x355 */ u8 m355[0x356 - 0x355];
    /* 0x356 */ u16 m356;
    /* 0x358 */ u8 m358[0x364 - 0x358];
    /* 0x364 */ int m364;
};

#endif /* D_A_DOOR10_H */
