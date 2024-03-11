#ifndef D_A_NPC_KK1_H
#define D_A_NPC_KK1_H

#include "f_op/f_op_actor.h"

class J3DNode;

class daNpc_Kk1_c : public fopAc_ac_c {
public:
    struct anm_prm_c {
        
    };

    void getSWbit() {}

    void _nodeCB_Head(J3DNode*, J3DModel*);
    void _nodeCB_BackBone(J3DNode*, J3DModel*);
    void init_KK1_0();
    void createInit();
    void play_animation();
    void setMtx(bool);
    void bckResID(int);
    void btpResID(int);
    void setBtp(signed char, bool);
    void init_texPttrnAnm(signed char, bool);
    void play_btp_anm();
    void play_eff_anm();
    void setAnm_anm(anm_prm_c*);
    void setAnm_NUM(int, int);
    void setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(unsigned char);
    void ctrlAnmAtr();
    void setAnm_ATR();
    void anmAtr(unsigned short);
    void next_msgStatus(unsigned long*);
    void getMsg_KK1_0();
    void getMsg();
    void eventOrder();
    void checkOrder();
    void chk_talk();
    void chk_parts_notMov();
    void searchByID(uint, int*);
    void partner_search_sub(void* (*)(void*, void*));
    void partner_search();
    void lookBack();
    void chkAttention();
    void setAttention(bool);
    void decideType(int);
    void cut_init_RUN_START(int);
    void cut_move_RUN_START();
    void cut_init_RUN(int);
    void cut_move_RUN();
    void cut_init_CATCH_START(int);
    void cut_move_CATCH_START();
    void cut_init_CATCH_END(int);
    void cut_move_CATCH_END();
    void cut_init_TRN(int);
    void cut_move_TRN();
    void cut_init_BYE_START(int);
    void cut_move_BYE_START();
    void cut_init_BYE(int);
    void cut_move_BYE();
    void cut_init_BYE_CONTINUE(int);
    void cut_move_BYE_CONTINUE();
    void cut_init_BYE_END(int);
    void cut_move_BYE_END();
    void cut_init_PLYER_TRN(int);
    void cut_move_PLYER_TRN();
    void cut_init_OTOBOKE(int);
    void cut_move_OTOBOKE();
    void cut_init_PLYER_MOV(int);
    void cut_move_PLYER_MOV();
    void cut_init_RUNAWAY_START(int);
    void cut_move_RUNAWAY_START();
    void cut_init_RUNAWAY_END(int);
    void cut_move_RUNAWAY_END();
    void privateCut(int);
    void endEvent();
    void isEventEntry();
    void event_proc(int);
    void checkCommandTalk();
    void set_action(int (daNpc_Kk1_c::*)(void*), void*);
    void setStt(signed char);
    void createTama(float);
    void chk_areaIN(float, cXyz);
    void startEvent_check();
    void chkHitPlayer();
    void set_pthPoint(unsigned char);
    void event_move(bool);
    void kyoroPos(int);
    void kyorokyoro();
    void chk_attn();
    void setBikon(cXyz);
    void delBikon();
    void setAse();
    void flwAse();
    void delAse();
    void wait_1();
    void walk_1();
    void wait_2();
    void init_CMT_WAI();
    void move_CMT_WAI();
    void init_CMT_TRN();
    void move_CMT_TRN();
    void init_CMT_PCK();
    void move_CMT_PCK();
    void cmmt_1();
    void wait_3();
    void wait_4();
    void talk_1();
    void wait_action1(void*);
    void demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    s32 _create();
    void bodyCreateHeap();
    void effcCreateHeap();
    void CreateHeap();

public:
    /* 0x6C4 */ u8 m6C4[0x72C - 0x6C4];
    /* 0x72C */ cXyz m72C;
    /* 0x738 */ cXyz m738;
    /* 0x744 */ u8 m744[0x750 - 0x744];
    /* 0x750 */ cXyz m750;
    /* 0x75C */ u8 m75C[0x7C4 - 0x75C];
    /* 0x7C4 */ u8 m7C4;
    /* 0x7C5 */ u8 m7C5[0x81E - 0x7C5];
    /* 0x81E */ u8 m81E;
    /* 0x81F */ u8 m81F[0x824 - 0x81F];
};

class daNpc_Kk1_HIO_c {
public:
    daNpc_Kk1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_KK1_H */
