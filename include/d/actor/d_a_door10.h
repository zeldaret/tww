#ifndef D_A_DOOR10_H
#define D_A_DOOR10_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"
#include "d/d_door.h"

class daDoor10_c : public dDoor_info_c {
public:
    bool checkFlag(unsigned short flag) { return m356 & flag; }
    inline BOOL execute();
    void offFlag(unsigned short flag) { m356 &= ~flag; }
    void onFlag(unsigned short flag) { m356 |= flag; }
    void setAction(u8 action) { m354 = action; }

    s32 chkMakeKey();
    void setKey();
    BOOL chkMakeStop();
    s32 chkStopF();
    s32 chkStopB();
    void setStop();
    BOOL chkStopOpen();
    void setStopDemo();
    BOOL chkStopClose();
    const char* getBdlName();
    const char* getDzbName();
    f32 getSize2X();
    BOOL CreateHeap();
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

    static const char M_arcname[];

public:
    /* 0x2D0 */ dDoor_smoke_c m2D0;
    /* 0x308 */ dDoor_key2_c mKeyLock;
    /* 0x32C */ dDoor_stop_c mStopBars;
    /* 0x338 */ dDoor_hkyo_c mHkyo;
    /* 0x34C */ J3DModel* mpModel;
    /* 0x350 */ dBgW* mpBgW;
    /* 0x354 */ u8 m354;
    /* 0x355 */ u8 m355[0x356 - 0x355];
    /* 0x356 */ u16 m356;
    /* 0x358 */ f32 m358;
    /* 0x35C */ request_of_phase_process_class mPhase;
    /* 0x364 */ int m364;
}; // size = 0x368

#endif /* D_A_DOOR10_H */
