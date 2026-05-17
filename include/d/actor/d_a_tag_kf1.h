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
    int checkPartner();
    void goto_nextStage();
    void event_talkInit(int);
    BOOL event_mesSet();
    BOOL event_mesEnd();
    void bensyoInit();
    void event_bensyo();
    void event_cntTsubo();
    void privateCut();
    void event_proc();
    void set_action(int (daTag_Kf1_c::*)(void*), void*);
    int wait01();
    int wait02();
    void wait_action1(void*);
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();

public:
    /* 0x6C4 */ u8 field_0x6C4[0x6D0 - 0x6C4];
    /* 0x6D0 */ dNpc_EventCut_c field_0x6D0;
    /* 0x73C */ u8 field_0x73C;
    /* 0x73D */ u8 field_0x73D;
    /* 0x73E */ short field_0x73E;
    /* 0x740 */ u8 field_0x73F[0x742 - 0x740];
    /* 0x742 */ u16 mRupeeCount; // This might be named wrong. I took an educated guess.
    /* 0x744 */ u8 field_0x744[0x764 - 0x744];
    /* 0x764 */ s16 field_0x764;
    /* 0x766 */ u8 field_0x766;
    /* 0x767 */ u8 field_0x767;
    /* 0x768 */ u8 field_0x768;
    /* 0x76A */ u8 field_0x76A[0x76C - 0x76A];
}; // Size: 0x76C
STATIC_ASSERT(sizeof(daTag_Kf1_c) == 0x76C);

class daTag_Kf1_HIO_c {
public:
    daTag_Kf1_HIO_c();

public:
    /* Place member variables here */
    virtual ~daTag_Kf1_HIO_c();
    s8 mId;
};

#endif /* D_A_TAG_KF1_H */
