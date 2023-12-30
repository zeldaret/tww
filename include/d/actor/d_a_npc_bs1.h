#ifndef D_A_NPC_BS1_H
#define D_A_NPC_BS1_H

#include "f_op/f_op_actor.h"
#include "d/d_shop.h"

class daNpc_Bs1_c : public fopAc_ac_c {
public:
    void getBackboneJntNum() {}
    void getBackbone_x() {}
    void getBackbone_y() {}
    void getBuyItem() {}
    void getBuyItemMax() {}
    void getHeadJntNum() {}
    void getHead_x() {}
    void getHead_y() {}
    void getPayRupee() {}
    void incAttnSetCount() {}
    void setAction(int (daNpc_Bs1_c::*)(void*), void*) {}
    void setAttentionBasePos(cXyz) {}
    void setBuyItem(unsigned char) {}
    void setBuyItemMax(unsigned char) {}
    void setEyePos(cXyz) {}
    void setPayRupee(short) {}

    void XyEventCB(int);
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
    void shopMsgCheck(unsigned long);
    void getDefaultMsg();
    void shopStickMoveMsgCheck(unsigned long);
    void checkBeastItemSellMsg(unsigned long);
    void normal_talk();
    void shop_talk();
    void talk();
    void createShopList();
    void isSellBomb();
    void CreateInit();
    void setAttention(bool);
    void lookBack();
    void wait01();
    void talk01();
    void wait_action(void*);
    void getdemo_action(void*);
    void evn_talk_init(int);
    void evn_continue_talk_init(int);
    void evn_talk();
    void evn_jnt_lock_init(int);
    void evn_wait_init(int);
    void evn_wait();
    void evn_set_anm_init(int);
    void evn_praise_init();
    void evn_mantan_init();
    void privateCut();
    void event_action(void*);
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    s32 _create();
    void CreateHeap();

public:
    /* 0x290 */ u8 m290[0x748 - 0x290];
    /* 0x748 */ cXyz mItemPosOffsets[3];
    /* 0x76C */ u8 m76C;
    /* 0x76D */ u8 m76D[0x7D4 - 0x76D];
    /* 0x7D4 */ ShopItems_c mShopItems;
    /* 0x818 */ u8 m818[0x81C - 0x818];
    /* 0x81C */ __shop_items_set_data* mpItemSetList[4];
    /* 0x82C */ u8 m82C[0x833 - 0x82C];
    /* 0x833 */ u8 mShopIndex;
    /* 0x834 */ u8 m834[0x844 - 0x834];
};

class daNpc_Bs1_childHIO_c {
public:
    daNpc_Bs1_childHIO_c();

public:
    /* Place member variables here */
};

class daNpc_Bs1_HIO_c {
public:
    daNpc_Bs1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_BS1_H */
