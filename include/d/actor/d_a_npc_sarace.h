#ifndef D_A_NPC_SARACE_H
#define D_A_NPC_SARACE_H

#include "f_op/f_op_actor.h"

class daNpc_Sarace_c : public fopAc_ac_c {
public:
    void getAttentionBasePos() {}
    void getEyePos() {}
    void getHBarrelP() {}
    void getVBarrelP() {}
    void init() {}
    void setAction(int (daNpc_Sarace_c::*)(void*), void*) {}

    void initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm(signed char, float);
    void chkAttention(cXyz, short);
    void eventOrder();
    void checkOrder();
    void next_msgStatus(unsigned long*);
    void getMsg();
    void anmAtr(unsigned short);
    void CreateInit();
    void setAttention();
    void lookBack();
    void wait01();
    void talk01();
    void dummy_action(void*);
    void wait_action(void*);
    void event_endCheck_action(void*);
    void set_mtx();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    s32 _create();
    void CreateHeap();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_SARACE_H */
