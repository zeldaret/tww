#ifndef D_A_NPC_BA1_H
#define D_A_NPC_BA1_H

#include "f_op/f_op_actor.h"
#include "JSystem/J3DGraphAnimator/J3DNode.h"

class daNpc_Ba1_c : public fopAc_ac_c {
public:
    void holdEventOn() {}

    void nodeBa1Control(J3DNode*, J3DModel*);
    void XyCheck_cB(int);
    void XyEvent_cB(int);
    void init_BA1_0();
    void init_BA1_1();
    void init_BA1_2();
    void init_BA1_3();
    void init_BA1_4();
    void createInit();
    void setMtx(bool);
    void anmNum_toResID(int);
    void btpNum_toResID(int);
    void setBtp(bool, int);
    void iniTexPttrnAnm(bool);
    void plyTexPttrnAnm();
    void setAnm_tex(signed char);
    void setAnm_anm(daNpc_Ba1_c::anm_prm_c*);
    void setAnm_NUM(int, int);
    void setAnm();
    void chg_anmTag();
    void control_anmTag();
    void chg_anmAtr(unsigned char);
    void control_anmAtr();
    void setAnm_ATR(int);
    void anmAtr(unsigned short);
    void eventOrder();
    void checkOrder();
    void chk_talk();
    void chk_drct(float);
    void chk_partsNotMove();
    void lookBack();
    void next_msgStatus(unsigned long*);
    void getMsg_BA1_0();
    void getMsg_BA1_1();
    void getMsg_BA1_3();
    void getMsg_BA1_4();
    void getMsg();
    void chkAttention();
    void setAttention(bool);
    void searchByID(unsigned int);
    void partner_srch_sub(void* (*)(void*, void*));
    void partner_srch();
    void check_useFairyArea();
    void checkCommandTalk();
    void charDecide(int);
    void eInit_setEvTimer(int*);
    void eInit_prmFloat(float*, float);
    void eInit_CHK_FAIRY_MOV_1(int*);
    void event_actionInit(int);
    void eMove_CHK_FAIRY_MOV_1();
    void event_action();
    void cut_init_START_TALE1(int);
    void cut_move_START_TALE1();
    void privateCut(int);
    void endEvent();
    void isEventEntry();
    void event_proc(int);
    void set_action(int (daNpc_Ba1_c::*)(void*), void*);
    void setStt(signed char);
    void wait_0();
    void wait_1();
    void talk_1();
    void talk_2();
    void wait_2();
    void wait_3();
    void ZZZwai();
    void wait_action1(void*);
    void wait_action2(void*);
    void demo_action1(void*);
    void wait_action3(void*);
    void wait_action4(void*);
    void demo();
    void shadowDraw();
    void _draw();
    void _execute();
    void _delete();
    void _create();
    void create_Anm();
    void create_itm_Mdl();
    void CreateHeap();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_BA1_H */
