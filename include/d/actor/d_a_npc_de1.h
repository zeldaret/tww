#ifndef D_A_NPC_DE1_H
#define D_A_NPC_DE1_H

#include "f_op/f_op_actor.h"

class daNpc_De1_c : public fopAc_ac_c {
public:
    struct anm_prm_c {
        
    };

    void createInit();
    void setMtx();
    void anmResID(int, int*, int*);
    void setAnm_anm(anm_prm_c*);
    void setAnm_NUM(int);
    void setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(unsigned char);
    void ctrlAnmAtr();
    void setAnm_ATR();
    void anmAtr(unsigned short);
    void setStt(signed char);
    void next_msgStatus(unsigned long*);
    void getMsg();
    void eventOrder();
    void checkOrder();
    void chkAttention();
    void setAttention();
    void searchByID(uint);
    void setDemoStartCenter();
    void partner_srch();
    void ccCreate();
    void cc_set();
    void set_pa_happa();
    void del_pa_happa();
    void followPa_happa();
    void decideType(int);
    void event_actionInit(int);
    void event_action();
    void privateCut();
    void endEvent();
    void event_proc();
    void set_action(int (daNpc_De1_c::*)(void*), void*);
    void wait01();
    void wait02();
    void wait03();
    void wait04();
    void wait05();
    void talk01();
    void talk02();
    void wait_action1(void*);
    void wait_action2(void*);
    void demo();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    s32 _create();
    void CreateHeap();

public:
    /* Place member variables here */
};

class daNpc_De1_HIO_c {
public:
    daNpc_De1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_DE1_H */
