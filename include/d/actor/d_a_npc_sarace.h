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
    void setAnm(s8, f32);
    void chkAttention(cXyz, s16);
    void eventOrder();
    void checkOrder();
    void next_msgStatus(u32*);
    void getMsg();
    void anmAtr(u16);
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
    cPhs_State _create();
    void CreateHeap();
    
    static s32 ship_race_rupee;
    static s32 ship_race_result;

public:
    /* Place member variables here */
};

class daNpc_Sarace_HIO_c {
public:
    daNpc_Sarace_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_SARACE_H */
