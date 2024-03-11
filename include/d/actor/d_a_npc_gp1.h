#ifndef D_A_NPC_GP1_H
#define D_A_NPC_GP1_H

#include "f_op/f_op_actor.h"

class J3DNode;

class daNpc_Gp1_c : public fopAc_ac_c {
public:
    struct anm_prm_c {
        
    };

    void nodeGp1Control(J3DNode*, J3DModel*);
    void init_GP1_0();
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
    void chk_forceTlkArea();
    void lookBack();
    void next_msgStatus(unsigned long*);
    void getMsg_GP1_0();
    void getMsg();
    void chkAttention();
    void setAttention(bool);
    void searchByID(uint);
    void partner_srch_sub(void* (*)(void*, void*));
    void partner_srch();
    void ctrl_WAITanm();
    void gp_movPass();
    void gp_clcMovSpd();
    void gp_nMove();
    void create_rupee();
    void charDecide(int);
    void eInit_INI_KAERE_KAERE_();
    void eInit_END_KAERE_KAERE_();
    void event_actionInit(int);
    void event_action();
    void privateCut(int);
    void endEvent();
    void isEventEntry();
    void event_proc(int);
    void set_action(int (daNpc_Gp1_c::*)(void*), void*);
    void setStt(signed char);
    void wait_1();
    void talk_1();
    void walk_1();
    void hair_1();
    void wait_2();
    void wait_action1(void*);
    void demo();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    s32 _create();
    void create_Anm();
    void CreateHeap();

public:
    /* Place member variables here */
};

class daNpc_Gp1_HIO_c {
public:
    daNpc_Gp1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_GP1_H */
