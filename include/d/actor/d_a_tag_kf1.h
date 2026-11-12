#ifndef D_A_TAG_KF1_H
#define D_A_TAG_KF1_H

#include "d/d_npc.h"

class daTag_Kf1_c : public fopNpc_npc_c {
public:
    typedef int (daTag_Kf1_c::*ActionFunc)(void*);

    BOOL createInit();
    void setStt(s8);
    u16 next_msgStatus(u32*);
    void eventOrder();
    void checkOrder();
    bool chkAttention(cXyz);
    bool partner_srch();
    s16 checkPartner();
    void goto_nextStage();
    void event_talkInit(int);
    bool event_mesSet();
    bool event_mesEnd();
    void bensyoInit();
    bool event_bensyo();
    void event_cntTsubo();
    void privateCut();
    void event_proc();
    bool set_action(ActionFunc, void*);
    BOOL wait01();
    BOOL wait02();
    int wait_action1(void*);
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();

public:
    /* 0x6C4 */ ActionFunc mAction;
    /* 0x6D0 */ dNpc_EventCut_c mEvtCut;
    /* 0x73C */ bool mbAttention;
    /* 0x73E */ s16 mBrokenNum;
    /* 0x740 */ u8 m740[0x742 - 0x740];
    /* 0x742 */ u16 mRupee;
    /* 0x744 */ fpc_ProcID mPartnerId[8];
    /* 0x764 */ s16 mPartnerNum;
    /* 0x766 */ s8 mActIdx;
    /* 0x767 */ s8 mOrder;
    /* 0x768 */ s8 mStt;
    /* 0x769 */ s8 mType;
    /* 0x76A */ s8 mActionState;
};  // Size: 0x76C

#endif /* D_A_TAG_KF1_H */
