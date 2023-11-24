#ifndef D_A_KDDOOR_H
#define D_A_KDDOOR_H

#include "f_op/f_op_actor.h"

class daKddoor_c : public fopAc_ac_c {
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
    void chkGenocideCase();
    void chkFeelerCase();
    void chkStopOpen();
    void setStopDemo();
    void chkStopClose();
    void getBmdName();
    void getBmdName2();
    void getDzbName();
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
    /* Place member variables here */
};

#endif /* D_A_KDDOOR_H */
