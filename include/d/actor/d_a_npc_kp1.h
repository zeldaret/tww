#ifndef D_A_NPC_KP1_H
#define D_A_NPC_KP1_H

#include "SSystem/SComponent/c_phase.h"
#include "d/d_cc_d.h"
#include "d/d_npc.h"
#include "d/d_save.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

class daNpc_Kp1_c : public fopNpc_npc_c {
public:
    struct anm_prm_c {};

    void getAttPos() {}
    void getBackboneJntNum() {}
    void getBackbone_x() {}
    void getBackbone_y() {}
    void getEyePos() {}
    void getHeadJntNum() {}
    void getHead_x() {}
    void getHead_y() {}

    s32 createInit();
    void setMtx();
    void anmResID(int, int*, int*);
    void BtpNum2ResID(int, int*);
    void setAnm_tex(signed char);
    void init_btp(bool, int);
    void initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm_anm(anm_prm_c*);
    void setAnm_NUM(int, int);
    void setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(unsigned char);
    void ctrlAnmAtr();
    void setAnm_ATR(int);
    void anmAtr(unsigned short);
    void setStt(signed char);
    u16 next_msgStatus(unsigned long*);
    u32 getMsg();
    void eventOrder();
    void checkOrder();
    void lookBack();
    void chkAttention();
    void setAttention();
    void chk_talk();
    bool decideType(int);
    void event_actionInit(int);
    void event_action();
    void privateCut();
    void endEvent();
    void event_proc();
    void set_action(int (daNpc_Kp1_c::*)(void*), void*);
    void wait01();
    void talk01();
    void wait_action1(void*);
    void demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    void CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhase; // 0x8
    /* 0x6CC */ u8 field_0x6CC[0x708 - 0x6CC];
    /* 0x708 */ dNpc_EventCut_c mEventCut;
    /* 0x774 */ u8 field_0x774[0x7A0 - 0x774];
    /* 0x7A0 */ cXyz field_0x7a0;
    /* 0x7AC */ u8 field_0x7AC[0x7BC - 0x7AC];
    /* 0x7BC */ s8 field_0x7BC;
    /* 0x7BD */ s8 field_0x7BD;
    /* 0x7BE */ u8 field_0x7BE;
    /* 0x7BF */ u8 field_0x7BF;
    /* 0x7C0 */ u8 field_0x7C0;
    /* 0x7C1 */ u8 field_0x7C1;
    /* 0x7C2 */ u8 field_0x7C2;
    /* 0x7C3 */ u8 field_0x7C3;
    /* 0x7C4 */ u8 field_0x7C4;
    /* 0x7C5 */ u8 field_0x7C5;
    /* 0x7C6 */ bool mHeadOnlyFollow;
    /* 0x7C7 */ u8 field_0x7C7;
    /* 0x7C8 */ u8 field_0x7C8;
    /* 0x7C9 */ s8 field_0x7C9;
    /* 0x7CA */ s8 field_0x7CA;
    /* 0x7CB */ u8 field_0x7CB;
    /* 0x7CC */ u8 field_0x7CC;
    /* 0x7CD */ s8 field_0x7CD;
    /* 0x7CE */ s8 field_0x7CE;
    /* 0x7CF */ s8 field_0x7CF;
    /* 0x7D0 */ s8 field_0x7D0;
    /* 0x7D1 */ s8 field_0x7D1;
    /* 0x7D2 */ s8 field_0x7D2;
    /* 0x7D3 */ s8 field_0x7D3;
    /* 0x7D4 */ s8 field_0x7D4;
    /* 0x7D5 */ s8 field_0x7D5;
    /* 0x7D6 */ s8 field_0x7D6;
    /* 0x7D7 */ s8 field_0x7D7;
    /* 0x7D8 */ s8 field_0x7D8;
    /* 0x7D9 */ s8 field_0x7D9;
    /* 0x7DA */ s8 field_0x7DA;
    /* 0x7DB */ s8 field_0x7DB;
    /* 0x7DC */ s8 field_0x7DC;
    /* 0x7DD */ s8 field_0x7DD;
};

class daNpc_Kp1_HIO_c {
public:
    daNpc_Kp1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_KP1_H */
