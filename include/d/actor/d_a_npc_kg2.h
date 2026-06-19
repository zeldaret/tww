#ifndef D_A_NPC_KG2_H
#define D_A_NPC_KG2_H

#include "f_op/f_op_actor.h"

class daNpc_Kg2_c : public fopAc_ac_c {
public:
    void getAttentionBasePos() {}
    void getEyePos() {}
    void seStart(u32) {}
    void setAction(int (daNpc_Kg2_c::*)(void*), void*) {}
    static void setCanonGameResult(u8 result) { canon_game_result = result; }

    void set_mtx();
    void initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm(s8, f32);
    void subAnm();
    void chkAttention(cXyz, s16);
    void eventOrder();
    void checkOrder();
    void getMsg();
    void next_msgStatus(u32*);
    void anmAtr(u16);
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
    cPhs_State _create();
    BOOL _delete();
    BOOL _execute();
    BOOL _draw();

    static void init() {
        canon_game_result = 0;
    }

    static s8 canon_game_result;
    static daNpc_Kg2_c* l_kg2_pointer;

public:
    /* Place member variables here */
};

class daNpc_Kg2_HIO_c {
public:
    daNpc_Kg2_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_KG2_H */
