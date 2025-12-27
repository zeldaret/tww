#ifndef D_A_NPC_PM1_H
#define D_A_NPC_PM1_H

#include "f_op/f_op_actor.h"

class daNpc_Pm1_c : public fopAc_ac_c {
public:
    struct anm_prm_c {
        
    };

    void getAttPos() {}
    void getBackboneJntNum() {}
    void getBackbone_x() {}
    void getBackbone_y() {}
    void getEyePos() {}
    void getHeadJntNum() {}
    void getHead_x() {}
    void getHead_y() {}

    void createInit();
    void setMtx();
    void anmResID(int, int*, int*);
    void BtpNum2ResID(int, int*);
    void setAnm_tex(signed char);
    void init_btp(bool, int);
    void initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm_anm(anm_prm_c*);
    void setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(unsigned char);
    void ctrlAnmAtr();
    void setAnm_ATR(int);
    void anmAtr(unsigned short);
    void setStt(signed char);
    void next_msgStatus(unsigned long*);
    void getMsg();
    void eventOrder();
    void checkOrder();
    void lookBack();
    void chkAttention();
    void setAttention();
    void decideType(int);
    void event_actionInit(int);
    void event_action();
    void privateCut();
    void endEvent();
    void event_proc();
    void set_action(int (daNpc_Pm1_c::*)(void*), void*);
    void wait01();
    void talk01();
    void wait_action1(void*);
    void demo();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    void CreateHeap();

public:
    /* Place member variables here */
};

class daNpc_Pm1_HIO_c {
public:
    daNpc_Pm1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_PM1_H */
