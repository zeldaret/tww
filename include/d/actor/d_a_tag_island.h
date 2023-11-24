#ifndef D_A_TAG_ISLAND_H
#define D_A_TAG_ISLAND_H

#include "f_op/f_op_actor.h"

class daTag_Island_c : public fopAc_ac_c {
public:
    void chkFlag(unsigned short) {}
    void clrFlag(unsigned short) {}
    void create() {}
    void draw() {}
    void execute() {}
    void setActio(unsigned char) {}
    void setFlag(unsigned short) {}

    void getEventNo();
    void getSwbit();
    void getType();
    void checkArea();
    void makeEvId();
    void getArrivalFlag();
    void otherCheck();
    void arrivalTerms();
    void demoInitProc();
    void next_msgStatus(unsigned long*);
    void getMsg();
    void talkInit();
    void talk();
    void demoInitTact_Bf();
    void demoProcTact_Bf();
    void demoInitTact_Af();
    void demoProcTact_Af();
    void demoInitSpeak();
    void demoProcSpeak();
    void demoInitWait();
    void demoProcWait();
    void demoInitCom();
    void demoProcCom();
    void demoProcCom_ikada();
    void getNowEventAction();
    void demoProc();
    void actionTact();
    void actionEvent();
    void actionReady();
    void actionHunt();
    void actionArrival();
    void actionWait();

public:
    /* Place member variables here */
};

#endif /* D_A_TAG_ISLAND_H */
