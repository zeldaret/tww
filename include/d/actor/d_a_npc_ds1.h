#ifndef D_A_NPC_DS1_H
#define D_A_NPC_DS1_H

#include "f_op/f_op_actor.h"
#include "d/d_shop.h"

class daNpc_Ds1_c : public fopAc_ac_c {
public:
    void checkAction(int (daNpc_Ds1_c::*)(void*)) {}
    void getBackboneJntNum() {}
    void getBackbone_x() {}
    void getBackbone_y() {}
    void getHeadJntNum() {}
    void getHead_x() {}
    void getHead_y() {}
    void incAttnSetCount() {}
    void setAction(int (daNpc_Ds1_c::*)(void*), void*) {}
    void setAttentionBasePos(cXyz) {}
    void setEyePos(cXyz) {}

    void XyEventCB(int);
    void initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm(signed char, float);
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
    void setAttention(bool);
    void lookBack();
    void wait01();
    void talk01();
    void getdemo_action(void*);
    void privateCut();
    void evn_setAnm_init(int);
    void evn_Anm();
    void evn_talk_init(int);
    void evn_continue_talk_init(int);
    void evn_talk();
    void evn_jnt_lock_init(int);
    void evn_player_hide_init(int);
    void evn_head_swing_init(int);
    void evn_ItemModel_init(int);
    void evn_move_pos_init(int);
    void evn_move_pos();
    void evn_init_pos_init(int);
    void event_action(void*);
    void wait_action(void*);
    void dummy_action(void*);
    void RoomEffectSet();
    void RoomEffectDelete();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    void CreateHeap();

public:
    /* 0x290 */ u8 m290[0x83C - 0x290];
    /* 0x83C */ ShopItems_c mShopItems;
    /* 0x880 */ ShopCursor_c* mpShopCursor;
    /* 0x884 */ u8 m884[0x8A0 - 0x884];
};

class daNpc_Ds1_childHIO_c {
public:
    daNpc_Ds1_childHIO_c();

public:
    /* Place member variables here */
};

class daNpc_Ds1_HIO_c {
public:
    daNpc_Ds1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_DS1_H */
