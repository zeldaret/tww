#ifndef D_A_TAG_MD_CB_H
#define D_A_TAG_MD_CB_H

#include "f_op/f_op_actor.h"

class daTag_MdCb_c : public fopAc_ac_c {
public:
    ~daTag_MdCb_c();

    void offEventAccept() {}
    void onEventAccept() {}
    void setTimer(short) {}

    cPhs_State create();
    void init();
    void checkTimer();
    void checkEventFinish();
    void action(void*);
    void setAction(int (daTag_MdCb_c::*)(void*), void*);
    void warpAction(void*);
    void messageAction(void*);
    void talk_init();
    void talk();
    void next_msgStatus(unsigned long*);
    void eventProc();
    void eventEnd();
    void getMyStaffId();
    void initialDefault(int);
    void actionDefault(int);
    void initialInitEvent(int);
    void initialMsgSetEvent(int);
    void actionMsgSetEvent(int);
    void actionMessageEvent(int);
    void initialPlayerOffDrow(int);
    void initialPlayerOnDrow(int);
    void eventOrder();
    void checkCommandTalk();
    void checkAreaIn(fopAc_ac_c*);
    void checkCondition();
    BOOL execute();
    BOOL draw();

public:
    /* Place member variables here */
};

class daTag_MdCb_HIO_c {
public:
    daTag_MdCb_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_TAG_MD_CB_H */
