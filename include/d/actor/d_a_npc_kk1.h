#ifndef D_A_NPC_KK1_H
#define D_A_NPC_KK1_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"

class J3DNode;

class daNpc_Kk1_c : public fopNpc_npc_c {
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
    u16 next_msgStatus(unsigned long*);
    u32 getMsg_KK1_0();
    u32 getMsg();
    void eventOrder();
    void checkOrder();
    bool chk_talk();
    bool chk_parts_notMov();
    fopAc_ac_c* searchByID(fpc_ProcID, int*);
    bool partner_search_sub(void* (*)(void*, void*));
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
    bool checkCommandTalk();
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
    bool _draw();
    bool _execute();
    bool _delete();
    cPhs_State _create();
    void bodyCreateHeap();
    void effcCreateHeap();
    void CreateHeap();

public:
    /* 0x6C4 */ u8 field_0x6C4[0x6FC - 0x6C4];
    /* 0x6FC*/  u32 field_0x6FC;
    /* 0x700 */ u8 field_0x700[0x72C - 0x700];   
    /* 0x72C */ cXyz field_0x72C;
    /* 0x738 */ cXyz field_0x738;
    /* 0x744 */ u8 field_0x744[0x750 - 0x744];
    /* 0x750 */ cXyz field_0x750;
    /* 0x75C */ u8  field_0x75C[0x770 - 0x75C];
    /* 0x770 */ s16 field_0x770;
    /* 0x772 */ s16 field_0x772;
    /* 0x774 */ s16 field_0x774;
    /* 0x776 */ u8  field_0x776[0x77C - 0x776];
    /* 0x77C */ s16 field_0x77C[0x08]; //8 Elements * U16 = 16 bytes
    /* 0x78C */ s16  field_0x78C; //Array Index?
    /* 0x78E */ s8  field_0x78D[0x7AE - 0x78E];
    /* 0x7AE */ u16 field_0x7AE;
    /* 0x7B0 */ u8 field_0x7B0[0x7B4 - 0x7B0];
    /* 0x7B4 */ u8 field_0x7B4;
    /* 0x7B5 */ u8 field_0x7B5[0x7B8 - 0x7B5];
    /* 0x7B8 */ u8 field_0x7B8;
    /* 0x7B9 */ u8 field_0x7B9[0x7BA - 0x7B9];
    /* 0x7BA */ u8 field_0x7BA;
    /* 0x7BB */ u8 field_0x7BB[0x7C3 - 0x7BB];
    /* 0x7C3 */ u8 field_0x7C3;
    /* 0x7C4 */ u8 field_0x7C4;
    /* 0x7C5 */ u8 field_0x7C5[0x817 - 0x7C5];
    /* 0x817 */ u8 field_0x817;
    /* 0x818 */ u8 field_0x818;
    /* 0x819 */ u8 field_0x819[0x81B - 0x819];
    /* 0x81B */ s8 field_0x81B;
    /* 0x81C */ u8 field_0x81C;
    /* 0x81D */ u8 field_0x81D;
    /* 0x81E */ u8 field_0x81E;
    /* 0x81F */ u8 field_0x81F[0x820 - 0x81F];
    /* 0x820 */ u8 field_0x820;
    /* 0x821 */ s8 field_0x821;
};  // Size: 0x824

class daNpc_Kk1_HIO_c {
public:
    daNpc_Kk1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_KK1_H */
