#ifndef D_A_KDDOOR_H
#define D_A_KDDOOR_H

#include "f_op/f_op_actor.h"
#include "d/d_door.h"

class dDoor_ssk_sub_c {
public:
    void init();
    void end();
    void openInit();
    void openProc(dDoor_info_c*);
    void closeInit();
    void closeProc(dDoor_info_c*);
    dDoor_ssk_sub_c();
    void drawSet();
    void calcMtx(dDoor_info_c*, float, float, unsigned char);

public:
    /* Place member variables here */
};

class dDoor_ssk_c {
public:
    void init(dDoor_info_c*);
    void end();
    void calcMtx(dDoor_info_c*);
    void execute(dDoor_info_c*);
    void draw(dDoor_info_c*);
    void closeInit();
    void closeProc(dDoor_info_c*);
    void openInit();
    void openProc(dDoor_info_c*);

public:
    /* Place member variables here */
};

class daKddoor_c : public dDoor_info_c {
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
