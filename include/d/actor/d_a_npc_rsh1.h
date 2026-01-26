#ifndef D_A_NPC_RSH1_H
#define D_A_NPC_RSH1_H

#include "f_op/f_op_actor.h"

class ShopItems_c;

class daNpc_Rsh1_c : public fopAc_ac_c {
public:
    void chkAction(int (daNpc_Rsh1_c::*)(void*)) {}
    void getBackboneJntNum() {}
    void getBackbone_x() {}
    void getBackbone_y() {}
    void getHeadJntNum() {}
    void getHead_x() {}
    void getHead_y() {}
    void incAttnSetCount() {}
    void setAction(int (daNpc_Rsh1_c::*)(void*), void*) {}
    void setAttentionBasePos(cXyz) {}
    void setEyePos(cXyz) {}
    void setShopIdx(int) {}

    void checkCreateInShopPlayer();
    void initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm(signed char);
    void setTexAnm(signed char);
    void setAnmFromMsgTag();
    void chkAttention(cXyz, short);
    void eventOrder();
    void checkOrder();
    void next_msgStatus(unsigned long*);
    void getMsg();
    void setCollision();
    void talkInit();
    void normal_talk();
    void shop_talk();
    void talk();
    void CreateInit();
    void createShopList();
    void setAttention();
    void lookBack();
    void pathGet();
    void getAimShopPosIdx();
    void shopPosMove();
    void pathMove(int*);
    void wait01();
    void talk01();
    void getdemo_action(void*);
    void wait_action(void*);
    void pl_shop_out_action(void*);
    void evn_setAnm_init(int);
    void evn_talk_init(int);
    void evn_continue_talk_init(int);
    void evn_talk();
    void evn_turn_init(int);
    void evn_turn();
    void privateCut();
    void event_action(void*);
    void dummy_action(void*);
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    void CreateHeap();
    void set_mtx();

public:
    /* 0x290 */ u8 m290[0x810 - 0x290];
    /* 0x810 */ ShopItems_c* mpShopItems;
    /* 0x814 */ u8 m814[0x968 - 0x814];
};

class daNpc_Rsh1_HIO_c {
public:
    daNpc_Rsh1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_RSH1_H */
