#ifndef D_A_NPC_DS1_H
#define D_A_NPC_DS1_H

#include "JSystem/JParticle/JPAEmitter.h"
#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "d/d_lib.h"
#include "d/d_npc.h"
#include "f_op/f_op_actor.h"
#include "d/d_shop.h"

class daNpc_Ds1_c : public fopAc_ac_c {
public:
    typedef BOOL (daNpc_Ds1_c::*ActionFunc)(void*) ;

    enum ActionStatus {
        ACTION_STARTING = 0,
        ACTION_ONGOING  = 1,
        ACTION_ENDING   = -1,
    };

    BOOL checkAction(ActionFunc func) {return mCurrActionFunc == func;}
    s8 getBackboneJntNum() { return m_backbone_jnt_num; }
    s16 getBackbone_x() {return mJntCtrl.getBackbone_x();}
    s16 getBackbone_y() {return mJntCtrl.getBackbone_y();}
    s8 getHeadJntNum() {return m_head_jnt_num;}
    s16 getHead_x() {return mJntCtrl.getHead_x();}
    s16 getHead_y() {return mJntCtrl.getHead_y();}
    void incAttnSetCount() {if(attnSetCount != 0xff) attnSetCount++;}
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
    void setAttentionBasePos(cXyz value) {mAttPos = value;}
    void setEyePos(cXyz value) {eyePos = value;}

    s16 XyEventCB(int);
    BOOL initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm(signed char, float);
    void setTexAnm(signed char);
    void setAnmFromMsgTag();
    bool chkAttention(cXyz, short);
    void eventOrder();
    void checkOrder();
    u16 next_msgStatus(unsigned long*);
    u32 getMsg();
    void setCollision();
    void talkInit();
    u16 normal_talk();
    u16 shop_talk();
    u16 talk();
    BOOL CreateInit();
    void setAttention(bool);
    void lookBack();
    bool wait01();
    bool talk01();
    BOOL getdemo_action(void*);
    BOOL privateCut();
    BOOL evn_setAnm_init(int);
    BOOL evn_Anm();
    BOOL evn_talk_init(int);
    BOOL evn_continue_talk_init(int);
    BOOL evn_talk();
    BOOL evn_jnt_lock_init(int);
    BOOL evn_player_hide_init(int);
    BOOL evn_head_swing_init(int);
    BOOL evn_ItemModel_init(int);
    BOOL evn_move_pos_init(int);
    BOOL evn_move_pos();
    BOOL evn_init_pos_init(int);
    BOOL event_action(void*);
    BOOL wait_action(void*);
    BOOL dummy_action(void*);
    void RoomEffectSet();
    void RoomEffectDelete();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL CreateHeap();

    static char m_arcname[];

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ mDoExt_McaMorf* mpMorf;
    /* 0x29C */ u32 mShadowId;
    /* 0x2A0 */ u8 field_0x2A0[0x2A4 - 0x2A0];
    /* 0x2A4 */ J3DAnmTexPattern* m_head_tex_pattern;
    /* 0x2A8 */ mDoExt_btpAnm mBtpAnm;
    /* 0x2BC */ u8 mBtpAnmFrame;
    /* 0x2BD */ u8 field_0x2BD[0x2BE - 0x2BD];
    /* 0x2BE */ s16 mTimer;
    /* 0x2C0 */ J3DModel* mpFlascoModel;
    /* 0x2C4 */ J3DModel* mpJarModel;
    /* 0x2C8 */ dBgS_ObjAcch mAcch;
    /* 0x48C */ dBgS_AcchCir mAcchCir;
    /* 0x4CC */ dCcD_Stts mStts;
    /* 0x508 */ dCcD_Cyl mCyl;
    /* 0x638 */ s8 m_head_jnt_num;
    /* 0x639 */ s8 m_backbone_jnt_num;
    /* 0x63A */ s8 m_handL_jnt_num;
    /* 0x63B */ s8 m_handR_jnt_num;
    /* 0x63C */ dNpc_EventCut_c mEventCut;
    /* 0x6A8 */ dNpc_JntCtrl_c mJntCtrl;
    /* 0x6DC */ dNpc_HeadAnm_c mHeadAnm;
    /* 0x700 */ cXyz mTargetPos;
    /* 0x70C */ s16 mTargetAngle;
    /* 0x710 */ STControl mStickControl;
    /* 0x738 */ s8 field_0x738;
    /* 0x739 */ u8 field_0x739[0x748 - 0x739];
    /* 0x748 */ cXyz mAttPos;
    /* 0x754 */ s16 mVel;
    /* 0x756 */ csXyz field_0x756;
    /* 0x75C */ u8 field_0x75C[0x75E - 0x75C];
    /* 0x75E */ u8 field_0x75E;
    /* 0x75F */ u8 attnSetCount;
    /* 0x760 */ u8 field_0x760;
    /* 0x761 */ u8 field_0x761;
    /* 0x764 */ f32 mPrevMorfFrame;
    /* 0x768 */ JPABaseEmitter* mpBaseEmitter;
    /* 0x76C */ JPABaseEmitter* field_0x76C[8];
    /* 0x78C */ J3DModel* mpGtydsModel;
    /* 0x790 */ mDoExt_btkAnm mGtydsAnm;
    /* 0x7A4 */ LIGHT_INFLUENCE mLightInfluence;
    /* 0x7C4 */ u32 mMsgNo;
    /* 0x7C8 */ u32 mNextMsgNo;
    /* 0x7CC */ u32 mEndMsgNo;
    /* 0x7D0 */ u32 field_0x7D0;
    /* 0x7D4 */ u8 mItemNo;
    /* 0x7D5 */ u8 field_0x7D5;
    /* 0x7D6 */ u8 field_0x7D6;
    /* 0x7D7 */ u8 field_0x7D7;
    /* 0x7D8 */ ActionFunc mCurrActionFunc;
    /* 0x7E4 */ ShopCam_action_c mShopCam;
    /* 0x83C */ ShopItems_c mShopItems;
    /* 0x880 */ ShopCursor_c* mpShopCursor;
    /* 0x884 */ s8 mBtpResIDIndex;
    /* 0x885 */ s8 field_0x885;
    /* 0x886 */ s8 field_0x886;
    /* 0x887 */ s8 field_0x887;
    /* 0x888 */ s32 field_0x888;
    /* 0x88C */ s16 mEventIdx[4];
    /* 0x894 */ s8 field_0x894;
    /* 0x895 */ u8 field_0x895;
    /* 0x896 */ s8 mType;
    /* 0x897 */ u8 field_0x897;
    /* 0x898 */ s8 mActionStatus;
    /* 0x899 */ s8 field_0x899;
    /* 0x89A */ u8 field_0x89A;
    /* 0x89B */ u8 mDrugChuchuNo;
    /* 0x89C */ u8 field_0x89C[0x8A0 - 0x89C];
};  // Size: 0x8A0

#endif /* D_A_NPC_DS1_H */
