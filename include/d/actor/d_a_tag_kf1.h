#ifndef D_A_TAG_KF1_H
#define D_A_TAG_KF1_H

#include "d/d_npc.h"

class daTag_Kf1_c : public fopNpc_npc_c {
public:
    void createInit();
    void setStt(signed char);
    u16 next_msgStatus(unsigned long*);
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
/* 0x6C4 */ u8 field_0x6C4[0x6D0 - 0x6C4];
/* 0x6D0 */ dNpc_EventCut_c field_0x6D0;
/* 0x73C */ u8 field_0x73C[0x742 - 0x73C];
/* 0x742 */ u16 mRupeeCount;
/* 0x744 */ u8 field_0x744[0x76C - 0x744];
};  // Size: 0x76C
STATIC_ASSERT(sizeof(daTag_Kf1_c) == 0x76C);

class daTag_Kf1_HIO_c {
public:
    daTag_Kf1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_TAG_KF1_H */
