#ifndef D_A_NPC_BS1_H
#define D_A_NPC_BS1_H

#include "SSystem/SComponent/c_phase.h"
#include "d/d_npc.h"
#include "d/d_shop.h"
#include "d/d_lib.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"


class daNpc_Bs1_c : public fopAc_ac_c {
public:
    typedef BOOL (daNpc_Bs1_c::*ActionFunc)(void*);

    enum ActionStatus {
        ACTION_STARTING = 0,
        ACTION_ONGOING  = 1,
        ACTION_ENDING   = -1,
    };

    s8 getBackboneJntNum() { return m_backbone_jnt_num; }
    s16 getBackbone_x() { return mJntCtrl.getBackbone_x(); }
    s16 getBackbone_y() { return mJntCtrl.getBackbone_y(); }
    void getBuyItem() {}
    void getBuyItemMax() {}
    int getHeadJntNum() { return m_head_jnt_num; }
    s16 getHead_x() { return mJntCtrl.getHead_x(); }
    s16 getHead_y() { return mJntCtrl.getHead_y(); }
    void getPayRupee() {}
    void incAttnSetCount() {}
    void setAction(ActionFunc func, void* arg) {
        if (mCurrActionFunc != func) {
            if (mCurrActionFunc) {
                mActionStatus = ACTION_ENDING;
                (this->*mCurrActionFunc)(NULL);
            }
            mCurrActionFunc = func;
            mActionStatus = ACTION_STARTING;
            (this->*mCurrActionFunc)(arg);
        }
    }
    void setAttentionBasePos(cXyz value) { m718 = value;}
    void setBuyItem(u8) {}
    void setBuyItemMax(u8) {}
    void setEyePos(cXyz other) { eyePos = other; }
    void setPayRupee(s16) {}

    s16 XyEventCB(int);
    BOOL initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm(s8);
    void setTexAnm(s8);
    void setAnmFromMsgTag();
    BOOL chkAttention(cXyz, s16);
    void eventOrder();
    void checkOrder();
    u16 next_msgStatus(u32*);
    u32 getMsg();
    void setCollision();
    void talkInit();
    BOOL shopMsgCheck(u32);
    u32 getDefaultMsg();
    BOOL shopStickMoveMsgCheck(u32);
    BOOL checkBeastItemSellMsg(u32);
    u16 normal_talk();
    u16 shop_talk();
    u16 talk();
    void createShopList();
    BOOL isSellBomb();
    BOOL CreateInit();
    void setAttention(bool);
    void lookBack();
    bool wait01();
    bool talk01();
    BOOL wait_action(void*);
    BOOL getdemo_action(void*);
    BOOL evn_talk_init(int);
    BOOL evn_continue_talk_init(int);
    BOOL evn_talk();
    BOOL evn_jnt_lock_init(int);
    BOOL evn_wait_init(int);
    BOOL evn_wait();
    BOOL evn_set_anm_init(int);
    BOOL evn_praise_init();
    BOOL evn_mantan_init();
    BOOL privateCut();
    BOOL event_action(void*);
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    s32 _create();
    BOOL CreateHeap();
    
    static u8 m_tag_buy_item_max;
    static u8 m_tag_buy_item;
    static s16 m_tag_pay_rupee;

public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ mDoExt_McaMorf* mpMorf;
    /* 0x29C */ u32 m29C;
    /* 0x2A0 */ J3DModel* mpSoldSignModels[3];
    /* 0x2AC */ J3DAnmTexPattern* m_head_tex_pattern;
    /* 0x2B0 */ mDoExt_btpAnm mBtpAnm;
    /* 0x2C4 */ u8 mFrame;
    /* 0x2C5 */ u8 m2C5;
    /* 0x2C6 */ s16 m2C6;
    /* 0x2C8 */ J3DModel* mpHelmetModel;
    /* 0x2CC */ dBgS_ObjAcch mAcch;
    /* 0x490 */ dBgS_AcchCir mAcchCir;
    /* 0x4D0 */ dCcD_Stts mStts;
    /* 0x50C */ dCcD_Cyl mCyl;
    /* 0x63C */ s8 m_head_jnt_num;
    /* 0x63D */ s8 m_backbone_jnt_num;
    /* 0x63E */ s16 m63E;
    /* 0x640 */ dNpc_EventCut_c mEventCut;
    /* 0x6AC */ dNpc_JntCtrl_c mJntCtrl;
    /* 0x6E0 */ STControl mStickControl;
    /* 0x708 */ s8 m708;
    /* 0x709 */ u8 m70C[0x718 - 0x709];
    /* 0x718 */ cXyz m718;
    /* 0x724 */ s16 m724;
    /* 0x726 */ csXyz m726;
    /* 0x72C */ u16 m72C;
    /* 0x72E */ u8 m72E;
    /* 0x72F */ u8 m72F;
    /* 0x730 */ u8 m730;
    /* 0x731 */ u8 m731;
    /* 0x732 */ u8 m732;
    /* 0x733 */ u8 m733;
    /* 0x734 */ f32 m734;
    /* 0x738 */ u32 m738;
    /* 0x73C */ u32 m73C;
    /* 0x740 */ u32 m740;
    /* 0x744 */ u32 m744;
    /* 0x748 */ cXyz mItemPosOffsets[3];
    /* 0x76C */ u8 m76C[3];
    /* 0x76F */ u8 m76D[0x770 - 0x76F];
    /* 0x770 */ ActionFunc mCurrActionFunc;
    /* 0x77C */ ShopCam_action_c mShopCamAction;
    /* 0x7D4 */ ShopItems_c mShopItems;
    /* 0x818 */ ShopCursor_c* mpShopCursor;
    /* 0x81C */ __shop_items_set_data* mpItemSetList[3];
    /* 0x828 */ s8 m828;
    /* 0x829 */ s8 m829;
    /* 0x82A */ s8 m82A;
    /* 0x82B */ s8 m82B;
    /* 0x82C */ s16 mEventIdxs[2];
    /* 0x830 */ s8 m830;
    /* 0x831 */ u8 m831;
    /* 0x832 */ s8 mType;
    /* 0x833 */ s8 mShopIndex;
    /* 0x834 */ s8 mActionStatus;
    /* 0x835 */ s8 m835;
    /* 0x836 */ s8 m836;
    /* 0x837 */ s8 m837;
    /* 0x838 */ s8 m838;
    /* 0x839 */ u8 m839;
    /* 0x83A */ s16 m83A;
    /* 0x83C */ u32 m83C;
    /* 0x840 */ u32 m840;
};  // Size: 0x844

class daNpc_Bs1_childHIO_c {
public:
    daNpc_Bs1_childHIO_c();
    virtual ~daNpc_Bs1_childHIO_c() {}

public:
    /* 0x000 */ // this.__vt
    /* 0x004 */ dNpc_HIO_c mNpc;
    /* 0x02C */ u8 m2C;
    /* 0x02D */ u8 m2D[0x3];
    /* 0x030 */ f32 m30;
    /* 0x034 */ f32 m34;
    /* 0x038 */ f32 m38;
    /* 0x03C */ f32 m3C;
    /* 0x040 */ f32 m40;
};  // Size: 0x44

class daNpc_Bs1_HIO_c : public JORReflexible {
public:
    daNpc_Bs1_HIO_c();
    virtual ~daNpc_Bs1_HIO_c() {}

public:
    /* 0x000 */ // this.__vt
    /* 0x004 */ s8 mChildId;
    /* 0x008 */ int m8;
    /* 0x00C */ daNpc_Bs1_childHIO_c mChild[2];
};  // Size: 0x94

#endif /* D_A_NPC_BS1_H */
