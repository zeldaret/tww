#ifndef D_A_NPC_BTSW2_H
#define D_A_NPC_BTSW2_H

#include "f_op/f_op_actor.h"

class daNpc_Btsw2_c : public fopAc_ac_c {
public:
    void getAttentionBasePos() {}
    void setAction(int (daNpc_Btsw2_c::*)(void*), void*) {}

    void initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm(signed char);
    void chkAttention(cXyz, short);
    void eventOrder();
    void checkOrder();
    void anmAtr(unsigned short);
    void getMsg();
    void next_msgStatus(unsigned long*);
    void setAttention();
    void lookBack();
    void CreateHeap();
    void CreateInit();
    void wait01();
    void talk01();
    void pathMove();
    void wait_action(void*);
    s32 _create();
    BOOL _delete();
    BOOL _execute();
    BOOL _draw();

public:
    /* Place member variables here */
};

class daNpc_Btsw2_HIO_c {
public:
    daNpc_Btsw2_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_BTSW2_H */
