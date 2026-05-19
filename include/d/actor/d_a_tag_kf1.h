#ifndef D_A_TAG_KF1_H
#define D_A_TAG_KF1_H

#include "d/d_npc.h"
#include "m_Do/m_Do_hostIO.h"

class daTag_Kf1_c : public fopNpc_npc_c {
public:
    BOOL createInit();
    void setStt(signed char);
    u16 next_msgStatus(unsigned long*);
    void eventOrder();
    void checkOrder();
    BOOL chkAttention(cXyz);
    void partner_srch();
    s16 checkPartner();
    void goto_nextStage();
    void event_talkInit(int);
    BOOL event_mesSet();
    BOOL event_mesEnd();
    void bensyoInit();
    BOOL event_bensyo();
    void event_cntTsubo();
    void privateCut();
    void event_proc();
    BOOL set_action(int (daTag_Kf1_c::*)(void*), void*);
    int wait01();
    int wait02();
    int wait_action1(void*);
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();

public:
    typedef int (daTag_Kf1_c::*ActionFunc)(void*);
    
    /* 0x6C4 */ ActionFunc mActionFunc;
    /* 0x6D0 */ dNpc_EventCut_c mEvent;
    /* 0x73C */ u8 field_0x73C;
    /* 0x73D */ u8 field_0x73D;
    /* 0x73E */ s16 mPartnerCount;
    /* 0x740 */ u8 field_0x73F[0x742 - 0x740];
    /* 0x742 */ u16 mRupeeCount;
    /* 0x744 */ fpc_ProcID mPartnerProcs[8];
    /* 0x764 */ s16 mNumOfPartners;
    /* 0x766 */ s8 field_0x766;
    /* 0x767 */ s8 mEventId;
    /* 0x768 */ s8 mState; // This is used in setStt so I suspect this may be dCcD_Stts?
    /* 0x769 */ u8 field_0x769;
    /* 0x76A */ s8 field_0x76A; // Event related such as state or id
    /* 0x76B */ u8 field_0x76B;
}; // Size: 0x76C
STATIC_ASSERT(sizeof(daTag_Kf1_c) == 0x76C);

class daTag_Kf1_HIO_c {
    public:
    daTag_Kf1_HIO_c();
    virtual ~daTag_Kf1_HIO_c();
    
public:
    /* Place member variables here */
    /* 0x04 */ s8 mNo;
};

#endif /* D_A_TAG_KF1_H */
