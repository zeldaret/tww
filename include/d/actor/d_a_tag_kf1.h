#ifndef D_A_TAG_KF1_H
#define D_A_TAG_KF1_H

#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "d/d_npc.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"

class daTag_Kf1_c : public fopNpc_npc_c {
public:
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
    void event_mesSet();
    void event_mesEnd();
    void bensyoInit();
    void event_bensyo();
    void event_cntTsubo();
    void privateCut();
    void event_proc();
    void set_action(int (daTag_Kf1_c::*)(void*), void*);
    bool wait01();
    bool wait02();
    BOOL wait_action1(void*);
    bool _draw();
    bool _execute();
    bool _delete();
    s32 _create();

public:
    /* Place member variables here */

    // /* 0x290 */ dBgS_Acch acch;
    // /* 0x454 */ dBgS_AcchCir acch_cir;
    // /* 0x494 */ dCcD_Stts stts;
    // /* 0x4d0 */ dCcD_Cyl cyl;
    //fopNpc_npc_c npc;

    dNpc_EventCut_c cut;


    u32 field_0x6d8;
    u32 field_0x6dc;
    u32 field_0x738;
    u8 field_0x73c;
    u8 pad[7];

    /* 0x744 */ s32 partners[8];
    /* 0x764 */ s16 npartners;
    u8 _;
    u8 field_0x767;
    s8 field_0x768;
    u8 field_0x769;
    s8 field_0x76a;
    char pad2[39];
    /* 0x769 */ u8 id;
    u8 byte1;
    u8 byte2;
    u8 byte3;
}; /* Size: 0x076c */

class daTag_Kf1_HIO_c : public JORReflexible {
public:
    daTag_Kf1_HIO_c();

public:
    /* 0x00 */ u32 field;
    /* 0x04 */ s8 mNo;
    f32 f1;
    f32 f2;
    /* Place member variables here */
};

#endif /* D_A_TAG_KF1_H */
