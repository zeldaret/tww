#ifndef D_A_TAG_MK_H
#define D_A_TAG_MK_H

#include "f_op/f_op_actor.h"

class daTag_Mk_c : public fopAc_ac_c {
public:
    inline s32 create();
    inline BOOL draw();
    void setAction(unsigned char) {}

    unsigned int getSwbit();
    unsigned int getSwbit2();
    unsigned int getType();
    void checkArea(float, float, float);
    void next_msgStatus(unsigned long*);
    void getMsg();
    void talkInit();
    void talk();
    void setTagWpEvId();
    void demoInitSetgoal();
    void demoInitDelete();
    void demoInitMake();
    void demoProcMake();
    void demoInitWait();
    void demoProcWait();
    void demoInitCom();
    void demoProcCom();
    void getNowEventAction();
    void demoProc();
    void actionEvent();
    void actionReady();
    void actionHunt();
    void actionArrival();
    int actionWait();
    void actionVillaTalk();
    void actionVilla();
    void actionTagWp2();
    void actionTagWp();
    void actionDaichi();
    BOOL execute();

public:
    /* Place member variables here */
};

#endif /* D_A_TAG_MK_H */
