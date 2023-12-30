#ifndef D_A_OBJ_HSEHI1_H
#define D_A_OBJ_HSEHI1_H

#include "f_op/f_op_actor.h"

class JPABaseEmitter;

class daObj_hsh_c : public fopAc_ac_c {
public:
    void isEventAccept() {}
    void isOffDraw() {}
    void isTactCancel() {}
    void isTactCorrect() {}
    void offEventAccept() {}
    void offTactCancel() {}
    void offTactCorrect() {}
    void onEventAccept() {}
    void onTactCancel() {}
    void onTactCorrect() {}

    void XyCheckCB(int);
    void XyEventCB(int);
    void particle_set(unsigned short);
    void particle_set(JPABaseEmitter**, unsigned short);
    void emitterDelete(JPABaseEmitter**);
    void setAttention(bool);
    void onOffDraw();
    void offOffDraw();
    void drawStop();
    void drawStart();
    void setBaseMtx();
    void createHeap();
    s32 create();
    void init();
    void action(void*);
    void setAction(int (daObj_hsh_c::*)(void*), void*);
    void waitAction(void*);
    void talkAction(void*);
    void offAction(void*);
    void deleteAction(void*);
    void eventOrder();
    void checkOrder();
    void checkCommandTalk();
    void chkAttention(cXyz, short);
    void eventProc();
    void eventEnd();
    void initialDefault(int);
    void actionDefault(int);
    void initialLinkDispEvent(int);
    void initialMsgSetEvent(int);
    void actionMsgSetEvent(int);
    void actionMessageEvent(int);
    void actionTactEvent(int);
    void initialJudgeEvent(int);
    void initialAppearEvent(int);
    void actionAppearEvent(int);
    void initialDeleteEvent(int);
    void actionDeleteEvent(int);
    void talk_init();
    void talk(int);
    void getMsg();
    void next_msgStatus(unsigned long*);
    BOOL execute();
    BOOL draw();

public:
    /* Place member variables here */
};

class daObj_hsh_HIO_c {
public:
    daObj_hsh_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_HSEHI1_H */
