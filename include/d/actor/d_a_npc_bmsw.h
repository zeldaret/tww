#ifndef D_A_NPC_BMSW_H
#define D_A_NPC_BMSW_H

#include "f_op/f_op_actor.h"

class daNpc_Bmsw_c : public fopAc_ac_c {
public:
    void getArmLMtx() {}
    void getArmRMtx() {}
    void getAttentionBasePos() {}
    void setAction(int (daNpc_Bmsw_c::*)(void*), void*) {}

    void initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm(signed char);
    void chkAttention(cXyz, short);
    void eventOrder();
    void checkOrder();
    void next_msgStatus(unsigned long*);
    void getMsg();
    void anmAtr(unsigned short);
    void CreateInit();
    void set_mtx();
    void setAttention();
    void lookBack();
    void wait01();
    void talk01();
    void wait_action(void*);
    void checkNextMailThrowOK();
    void setGameGetRupee(short);
    void TimerCountDown();
    void shiwake_game_action(void*);
    void _draw();
    void _execute();
    void _delete();
    void _create();
    void CreateHeap();

public:
    /* 0x6C4 */ u8 m6C4[0x968 - 0x6C4];
    /* 0x968 */ ShopCursor_c* mpShopCursor;
    /* 0x96C */ u8 m96C[0x9E4 - 0x96C];
};

#endif /* D_A_NPC_BMSW_H */
