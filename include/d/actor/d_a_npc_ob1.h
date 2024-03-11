#ifndef D_A_NPC_OB1_H
#define D_A_NPC_OB1_H

#include "f_op/f_op_actor.h"

class J3DNode;

class daNpc_Ob1_c : public fopAc_ac_c {
public:
    struct anm_prm_c {
        
    };

    void nodeOb1Control(J3DNode*, J3DModel*);
    void init_OB1_0();
    void init_OB1_1();
    void init_OB1_2();
    void createInit();
    void setMtx(bool);
    void anmNum_toResID(int);
    void btpNum_toResID(int);
    void setBtp(bool, int);
    void iniTexPttrnAnm(bool);
    void plyTexPttrnAnm();
    void setAnm_tex(signed char);
    void setAnm_anm(anm_prm_c*);
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
    void chk_partsNotMove();
    void lookBack();
    void next_msgStatus(unsigned long*);
    void getMsg_OB1_0();
    void getMsg_OB1_1();
    void getMsg_OB1_2();
    void getMsg();
    void chkAttention();
    void setAttention(bool);
    void searchByID(uint);
    void partner_srch();
    void bitCount(unsigned char);
    void set_pigCnt();
    void ob_setPthPos();
    void get_attPos();
    void ob_movPass();
    void ob_clcMovSpd();
    void ob_nMove();
    void charDecide(int);
    void event_actionInit(int);
    void event_action();
    void privateCut(int);
    void endEvent();
    void isEventEntry();
    void event_proc(int);
    void set_action(int (daNpc_Ob1_c::*)(void*), void*);
    void clrSpd();
    void setStt(signed char);
    void wait_1();
    void wait_2();
    void wait_3();
    void walk_1();
    void talk_1();
    void manzai();
    void wait_action1(void*);
    void wait_action2(void*);
    void demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    s32 _create();
    void create_Anm();
    void create_hed_Mdl();
    void CreateHeap();

public:
    /* Place member variables here */
};

class daNpc_Ob1_HIO_c {
public:
    daNpc_Ob1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_OB1_H */
