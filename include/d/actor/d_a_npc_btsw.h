#ifndef D_A_NPC_BTSW_H
#define D_A_NPC_BTSW_H

#include "f_op/f_op_actor.h"

class daNpc_Btsw_c : public fopAc_ac_c {
public:
    void getAttentionBasePos() {}
    void setAction(int (daNpc_Btsw_c::*)(void*), void*) {}

    void initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm(signed char);
    void chkAttention(cXyz, short);
    void eventOrder();
    void checkOrder();
    void next_msgStatus(unsigned long*);
    void getMsg();
    void anmAtr(unsigned short);
    void CreateInit();
    void set_mtx();
    void setAttention();
    void lookBack();
    void wait01();
    void talk01();
    void wait_action(void*);
    void dummy_event_action(void*);
    void checkNextMailThrowOK();
    void TimerCountDown();
    void shiwake_game_action(void*);
    void getdemo_action(void*);
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    void CreateHeap();

public:
    /* Place member variables here */
};

class SwMail2_c {
public:
    void CheckProc(void (SwMail2_c::*)()) {}
    void SetProc(void (SwMail2_c::*)()) {}

    void MailCreateInit(cXyz*, cXyz*);
    void getNextNo(unsigned char);
    void init();
    void set_mtx();
    void set_mtx_throw();
    void DummyInit();
    void Dummy();
    void AppearInit();
    void Appear();
    void WaitInit();
    void Wait();
    void ThrowInit(cXyz, unsigned char);
    void Throw();
    void EndInit();
    void End();
    void SeDelete();
    void move();
    void draw(dKy_tevstr_c*);
};

class SwCam2_c {
    void ActiveOff() {}
    void ActiveOn() {}
    void getCenterP() {}
    void getEyeP() {}
    void setAimIdx(signed char, signed char) {}

    void Move();
};

class daNpc_Btsw_HIO_c {
public:
    daNpc_Btsw_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_BTSW_H */
