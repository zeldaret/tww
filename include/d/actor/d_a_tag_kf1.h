#ifndef D_A_TAG_KF1_H
#define D_A_TAG_KF1_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"

class daTag_Kf1_c : public fopAc_ac_c {
public:
    void createInit();
    void setStt(signed char);
    void next_msgStatus(unsigned long*);
    void eventOrder();
    void checkOrder();
    BOOL chkAttention(cXyz);
    void partner_srch();
    s16 checkPartner();
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
    BOOL wait01();
    BOOL wait02();
    BOOL wait_action1(void*);
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();

public:
    /* 0x290 */ u8 field_0x290[0x6C4 - 0x290];
    /* 0x6C4 */ int (daTag_Kf1_c::*mActionFunc)(void*);
    /* 0x6D0 */ dNpc_EventCut_c mEventCut;
    /* 0x73C */ u8 field_0x73C;
    /* 0x73D */ u8 field_0x73D;
    /* 0x73E */ s16 field_0x73E;
    /* 0x740 */ u8 field_0x740[0x742 - 0x740];
    /* 0x742 */ u16 field_0x742;
    /* 0x744 */ u8 field_0x744[0x764 - 0x744];
    /* 0x764 */ s16 field_0x764;
    /* 0x766 */ s8 mAction;
    /* 0x767 */ s8 field_0x767;
    /* 0x768 */ s8 mStt;
    /* 0x769 */ u8 field_0x769;
    /* 0x76A */ s8 field_0x76A;
    /* 0x76B */ u8 field_0x76B;
};
STATIC_ASSERT(sizeof(daTag_Kf1_c) == 0x76C);

class daTag_Kf1_HIO_c {
public:
    daTag_Kf1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_TAG_KF1_H */
