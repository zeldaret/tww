#ifndef D_A_NPC_KG2_H
#define D_A_NPC_KG2_H

#include "f_op/f_op_actor.h"

class daNpc_Kg2_c : public fopAc_ac_c {
public:
    void getAttentionBasePos() {}
    void getEyePos() {}
    void init() {}
    void seStart(unsigned long) {}
    void setAction(int (daNpc_Kg2_c::*)(void*), void*) {}
    void setCanonGameResult(unsigned char) {}

    void set_mtx();
    void initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm(signed char, float);
    void subAnm();
    void chkAttention(cXyz, short);
    void eventOrder();
    void checkOrder();
    void getMsg();
    void next_msgStatus(unsigned long*);
    void anmAtr(unsigned short);
    void setAttention();
    void lookBack();
    void CreateHeap();
    void CreateInit();
    void wait01();
    void talk01();
    void evn_setAnm_init(int);
    void evn_setAnm();
    void evn_jnt_lock_init(int);
    void evn_talk_init(int);
    void evn_talk();
    void evn_createItem_init(int);
    void privateCut();
    void processMove();
    void wait_action(void*);
    void event_wait_action(void*);
    s32 _create();
    BOOL _delete();
    BOOL _execute();
    BOOL _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_KG2_H */
