#ifndef D_A_NPC_KF1_H
#define D_A_NPC_KF1_H

#include "f_op/f_op_actor.h"
#include "d/d_npc.h"

class daNpc_Kf1_c : public fopAc_ac_c {
public:
    struct anm_prm_c {
        
    };

    void _nodeCB_Head(J3DNode*, J3DModel*);
    void _nodeCB_Neck(J3DNode*, J3DModel*);
    void _nodeCB_BackBone(J3DNode*, J3DModel*);
    void init_KF1_0();
    void createInit();
    void play_animation();
    void setMtx(bool);
    void bckResID(int);
    void btpResID(int);
    void setBtp(signed char, bool);
    void init_texPttrnAnm(signed char, bool);
    void play_btp_anm();
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
    void getMsg_KF1_0();
    void getMsg();
    void eventOrder();
    void checkOrder();
    void chk_talk();
    void searchByID(uint, int*);
    void srch_Tsubo();
    void create_rupee(cXyz, int);
    void ready_kutaniCamera(int, int);
    void lookBack();
    void chkAttention();
    void setAttention(bool);
    void decideType(int);
    void cut_init_ANGRY_START(int);
    void cut_move_ANGRY_START();
    void cut_init_BENSYOU_START(int);
    void cut_move_BENSYOU_START();
    void cut_init_TSUBO_CNT(int);
    void cut_move_TSUBO_CNT();
    void cut_init_BENSYOU(int);
    void cut_move_BENSYOU();
    void cut_init_GET_OUT(int);
    void cut_move_GET_OUT();
    void cut_init_DSP_RUPEE_CNT(int);
    void cut_move_DSP_RUPEE_CNT();
    void cut_init_PLYER_TRN(int);
    void cut_move_PLYER_TRN();
    void cut_init_RUPEE_CNT_END(int);
    void cut_move_RUPEE_CNT_END();
    void cut_init_START_AGE(int);
    void cut_move_START_AGE();
    void cut_init_PLYER_MOV(int);
    void cut_move_PLYER_MOV();
    void cut_init_RUPEE_SET(int);
    void cut_move_RUPEE_SET();
    void cut_init_TSUBO_ATN(int);
    void cut_move_TSUBO_ATN();
    void cut_init_TLK_MSG(int);
    void cut_init_CONTNUE_TLK(int);
    void cut_move_TLK_MSG();
    void privateCut(int);
    void endEvent();
    void isEventEntry();
    void event_proc(int);
    void set_action(int (daNpc_Kf1_c::*)(void*), void*);
    void setStt(signed char);
    void set_pthPoint(unsigned char);
    void chk_tsubo();
    void orderTsuboEvent();
    void wait_1();
    void walk_1();
    void talk_1();
    void wait_action1(void*);
    void demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    s32 _create();
    void bodyCreateHeap();
    void itemCreateHeap();
    void CreateHeap();

public:
    /* 0x6C4 */ u8 m6C4[0x708 - 0x6C4];
    /* 0x708 */ dNpc_PathRun_c m708;
    /* 0x710 */ u8 m710[0x800 - 0x710];
};

class daNpc_Kf1_HIO_c {
public:
    daNpc_Kf1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_KF1_H */
