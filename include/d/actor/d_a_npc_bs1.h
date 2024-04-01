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

    enum Animation {
        ANM_UNK_0 = 0,
        ANM_UNK_1 = 1,
        ANM_UNK_2 = 2,
        ANM_UNK_3 = 3,
        ANM_UNK_4 = 4,
        ANM_UNK_5 = 5,
        ANM_UNK_6 = 6,
        ANM_UNK_7 = 7,
        ANM_UNK_8 = 8,
        ANM_UNK_9 = 9,
        ANM_UNK_A = 0xA,
        ANM_UNK_B = 0xB,
    };

    daNpc_Bs1_c();
    int getBackboneJntNum() { return m_backbone_jnt_num; }
    int getBackbone_x() { return mJntCtrl.getBackbone_x(); }
    int getBackbone_y() { return mJntCtrl.getBackbone_y(); }
    void getBuyItem() {}
    void getBuyItemMax() {}
    int getHeadJntNum() { return m_head_jnt_num; }
    int getHead_x() { return mJntCtrl.getHead_x(); }
    int getHead_y() { return mJntCtrl.getHead_y(); }
    void getPayRupee() {}
    void incAttnSetCount() {}
    void setAction(int (daNpc_Bs1_c::*)(void*), void*) {}
    void setAttentionBasePos(cXyz value) { m718 = value;}
    void setBuyItem(unsigned char) {}
    void setBuyItemMax(unsigned char) {}
    void setEyePos(cXyz other) { eyePos = other; }
    void setPayRupee(short) {}

    s16 XyEventCB(int);
    BOOL initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm(signed char);
    void setTexAnm(signed char);
    void setAnmFromMsgTag();
    BOOL chkAttention(cXyz, short);
    void eventOrder();
    void checkOrder();
    u16 next_msgStatus(unsigned long*);
    void getMsg();
    void setCollision();
    void talkInit();
    u32 shopMsgCheck(unsigned long);
    void getDefaultMsg();
    void shopStickMoveMsgCheck(unsigned long);
    BOOL checkBeastItemSellMsg(u32);
    void normal_talk();
    void shop_talk();
    u16 talk();
    void createShopList();
    BOOL isSellBomb();
    BOOL CreateInit();
    void setAttention(bool);
    void lookBack();
    BOOL wait01();
    BOOL talk01();
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

    typedef BOOL (daNpc_Bs1_c::*ActionFunc)(void*);

public:
    /* 0x290 */ request_of_phase_process_class mphs;
    /* 0x298 */ mDoExt_McaMorf* mpMorf;
    /* 0x29C */ u32 m29C;
    /* 0x2A0 */ J3DModel* mpModelArr[3];
    /* 0x2AC */ J3DAnmTexPattern* m_head_tex_pattern;
    /* 0x2B0 */ mDoExt_btpAnm mBtpAnm;
    /* 0x2C4 */ u8 mFrame;
    /* 0x2C5 */ u8 m2C5;
    /* 0x2C6 */ s16 m2C6;
    /* 0x2C8 */ J3DModel* mpModel;
    /* 0x2CC */ dBgS_Acch mAcch;
    /* 0x490 */ dBgS_AcchCir mAcchCir;
    /* 0x4D0 */ cXyz m4D0;
    /* 0x4D0 */ u8 m2CC[0x63C - 0x4DC];
    /* 0x63C */ s8 m_head_jnt_num;
    /* 0x63D */ s8 m_backbone_jnt_num;
    /* 0x63E */ s16 m63E;
    /* 0x640 */ char* m640;
    /* 0x644 */ u8 m644[0x6AC - 0x644];
    /* 0x6AC */ dNpc_JntCtrl_c mJntCtrl;
    /* 0x6E0 */ STControl mStickControl;
    /* 0x708 */ u8 m708[0x718 - 0x708];
    /* 0x718 */ cXyz m718;
    /* 0x724 */ s16 m724;
    /* 0x726 */ u16 m726;
    /* 0x728 */ u8 m728[0x72E - 0x728];
    /* 0x72E */ u8 m72E;
    /* 0x72F */ u8 m72F;
    /* 0x730 */ u8 m730;
    /* 0x731 */ u8 m731;
    /* 0x732 */ u8 m732;
    /* 0x733 */ u8 m733;
    /* 0x734 */ f32 m734;
    /* 0x738 */ u32 m738;
    /* 0x73C */ u8 m73C[0x740 - 0x73C];
    /* 0x740 */ u32 m740;
    /* 0x744 */ u32 m744;
    /* 0x748 */ cXyz mItemPosOffsets[3];
    /* 0x76C */ u8 m76C;
    /* 0x76D */ u8 m76D[0x770 - 0x76D];
    /* 0x770 */ ActionFunc m770;
    /* 0x77C */ ShopCam_action_c mShopCamAction;
    /* 0x7D4 */ ShopItems_c mShopItems;
    /* 0x818 */ ShopCursor_c* mpShopCursor;
    /* 0x81C */ __shop_items_set_data* mpItemSetList[3];
    /* 0x828 */ s8 m828;
    /* 0x829 */ s8 m829;
    /* 0x82A */ s8 m82A;
    /* 0x82B */ s8 m82B;
    /* 0x82C */ s16 m82C;
    /* 0x82E */ s16 m82E;
    /* 0x830 */ s8 m830;  // Unknown usage
    /* 0x831 */ u8 m831;  // Unknown usage
    /* 0x832 */ s8 mLHioChildIdx;  // Used in createShopList
    /* 0x833 */ u8 mShopIndex;
    /* 0x834 */ s8 m834;
    /* 0x835 */ u8 m835;
    /* 0x836 */ u8 m836[0x83A - 0x836];
    /* 0x83A */ s16 m83A;
    /* 0x83C */ u8 m83C[0x844 - 0x83C];
};

class daNpc_Bs1_childHIO_c {
public:
    daNpc_Bs1_childHIO_c();
    virtual ~daNpc_Bs1_childHIO_c();

public:
    /* Place member variables here */
    /* 0x000 */  // this.__vt
    /* 0x004 */ dNpc_HIO_c mHIO;
    /* 0x02C */ u8 m2C;  // Isolating at u8 based on stb in Constructor
    /* 0x02D */ u8 m2D[0x3];
    /* 0x030 */ f32 m30;
    /* 0x034 */ f32 m34;
    /* 0x038 */ f32 m38;
    /* 0x03C */ f32 m3C;
    /* 0x040 */ f32 m40;
};

class daNpc_Bs1_HIO_c : public JORReflexible {
public:
    daNpc_Bs1_HIO_c();
    virtual ~daNpc_Bs1_HIO_c();

public:
    /* 0x000 */  // this.__vt
    /* 0x004 */ s8 mChildId;
    /* 0x008 */ int m8;
    /* 0x00C */ daNpc_Bs1_childHIO_c mpChildArray[2];
};

STATIC_ASSERT(sizeof(daNpc_Bs1_c) == 0x844);
STATIC_ASSERT(sizeof(daNpc_Bs1_HIO_c) == 0x94);
STATIC_ASSERT(sizeof(daNpc_Bs1_childHIO_c) == 0x44);
#endif /* D_A_NPC_BS1_H */
