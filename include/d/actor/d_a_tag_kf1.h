#ifndef D_A_TAG_KF1_H
#define D_A_TAG_KF1_H

#include "d/d_npc.h"
#include "m_Do/m_Do_hostIO.h"

class daTag_Kf1_c : public fopNpc_npc_c {
public:
    typedef int (daTag_Kf1_c::*ActionFunc)(void*);
    BOOL createInit();
    char setStt(signed char);
    u16 next_msgStatus(unsigned long*);
    void eventOrder();
    void checkOrder();
    BOOL chkAttention(cXyz);
    BOOL partner_srch();
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
    BOOL set_action(ActionFunc, void*);
    bool wait01();
    bool wait02();
    BOOL wait_action1(void*);
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    // s32
    cPhs_State _create();
    
public:
    /* 0x6c4 */ ActionFunc mAction;
    /* 0x6d0 */ dNpc_EventCut_c tag_event_cut;
    /* 0x73c */ u8 mHasAttention;
    /* 0x73e */ s16 mTenthCost;
    /* 0x740 */ u16 f_0x740;
    /* 0x742 */ u16 mRupeeCount;

    /* 0x744 */ s32 mPartners[8];
    /* 0x764 */ s16 mNumPartners;
    /* 0x766 */ s8 mActIdx;
    /* 0x767 */ s8 mEventState;
    /* 0x768 */ s8 mStt;
    /* 0x769 */ u8 field_0x769;
    /* 0x76a */ s8 mActionState;
}; /* Size: 0x076c */

class daTag_Kf1_HIO_c : public JORReflexible {
public:
    daTag_Kf1_HIO_c();
    virtual ~daTag_Kf1_HIO_c() {};

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ f32 mAttentionMaxEuclidDistance;
    /* 0x0C */ f32 mAttentionMaxYDistance;
    /* 0x10 */ u8 f0x10;
}; /* Size: 0x14 */

#endif /* D_A_TAG_KF1_H */
