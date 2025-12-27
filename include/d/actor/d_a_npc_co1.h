#ifndef D_A_NPC_CO1_H
#define D_A_NPC_CO1_H

#include "f_op/f_op_actor.h"

class J3DNode;

class daNpc_Co1_c : public fopAc_ac_c {
public:
    struct anm_prm_c {
        
    };

    void nodeCo1Control(J3DNode*, J3DModel*);
    void init_CO1_0();
    void createInit();
    void setMtx(bool);
    void anmNum_toResID(int);
    void anmNum_toResID_prl(int);
    void btpNum_toResID(int);
    void setBtp(bool, int);
    void setBtk(bool);
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
    void setCollision_SP_();
    void set_target(int);
    void chk_talk();
    void chk_partsNotMove();
    void lookBack();
    void next_msgStatus(unsigned long*);
    void getMsg_CO1_0();
    void getMsg();
    void chkAttention();
    void setAttention(bool);
    void charDecide(int);
    void eInit_MDR_();
    void eInit_RED_LTR_();
    void event_actionInit(int);
    void eMove_MDR_();
    void eMove_RED_LTR_();
    void event_action();
    void privateCut(int);
    void endEvent();
    void isEventEntry();
    void event_proc(int);
    void set_action(int (daNpc_Co1_c::*)(void*), void*);
    void setStt(signed char);
    void wait_1();
    void wait_2();
    void wakeup();
    void talk_1();
    void toru_1();
    void read_1();
    void modoru();
    void wait_action1(void*);
    void demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    void create_Anm();
    void create_prl_Anm();
    void create_itm_Mdl();
    void CreateHeap();

public:
    /* Place member variables here */
};

class daNpc_Co1_HIO_c {
public:
    daNpc_Co1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_CO1_H */
