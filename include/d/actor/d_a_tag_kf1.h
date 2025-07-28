#ifndef D_A_TAG_KF1_H
#define D_A_TAG_KF1_H

#include "f_op/f_op_actor.h"

class daTag_Kf1_c : public fopAc_ac_c {
public:
    void createInit();
    void setStt(signed char);
    void next_msgStatus(unsigned long*);
    void eventOrder();
    void checkOrder();
    void chkAttention(cXyz);
    void partner_srch();
    void checkPartner();
    void goto_nextStage();
    void event_talkInit(int);
    void event_mesSet();
    void event_mesEnd();
    void bensyoInit();
    void event_bensyo();
    void event_cntTsubo();
    void privateCut();
    void event_proc();
    void set_action(int (daTag_Kf1_c::*)(void*), void*);
    void wait01();
    void wait02();
    void wait_action1(void*);
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();

public:
    /* Place member variables here */
};

class daTag_Kf1_HIO_c {
public:
    daTag_Kf1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_TAG_KF1_H */
