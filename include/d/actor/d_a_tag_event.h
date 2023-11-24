#ifndef D_A_TAG_EVENT_H
#define D_A_TAG_EVENT_H

#include "f_op/f_op_actor.h"

class daTag_Event_c : public fopAc_ac_c {
public:
    void create() {}
    void draw() {}
    void execute() {}
    void setActio(unsigned char) {}

    void getEventNo();
    void getSwbit();
    void getSwbit2();
    void getType();
    void getEventFlag();
    void cancelShutter();
    void arrivalTerms();
    void demoInitProc();
    void demoEndProc();
    void demoProc();
    void actionEvent();
    void actionReady();
    void actionHunt();
    void actionArrival();
    void actionSpeEvent();
    void actionSpeReady();
    void actionSpeHunt();
    void actionSpeArrival();
    void actionWait();
    void actionMjReady();
    void actionMjHunt();
    void actionHunt2();

public:
    /* Place member variables here */
};

#endif /* D_A_TAG_EVENT_H */
