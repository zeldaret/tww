#ifndef D_A_NPC_AC1_H
#define D_A_NPC_AC1_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"

class daNpc_Ac1_c : public fopNpc_npc_c {
public:
    struct anm_prm_c {
        /* 0x00 */ s8 anmNum;
        /* 0x01 */ s8 btpNum;
        /* 0x04 */ f32 morf;
        /* 0x08 */ f32 speed;
        /* 0x0C */ int loopMode;
        /* 0x10 */ BOOL hasArms;
    }; // Size: 0x14

    typedef BOOL (daNpc_Ac1_c::*ActionFunc)(void*);

    void nodeWngControl(J3DNode*, J3DModel*);
    void nodeArmControl(J3DNode*, J3DModel*);
    void nodeAc1Control(J3DNode*, J3DModel*);
    bool init_AC1_0();
    bool createInit();
    void setMtx(bool);
    u32 anmNum_toResID(int);
    u32 wingAnmNum_toResID(int);
    u32 btpNum_toResID(int);
    bool setBtp(bool, int);
    bool iniTexPttrnAnm(bool);
    void plyTexPttrnAnm();
    void setAnm_tex(s8);
    BOOL setAnm_anm(anm_prm_c*);
    bool setAnm();
    void chg_anmTag();
    void control_anmTag();
    void chg_anmAtr(u8);
    void control_anmAtr();
    void setAnm_ATR(int);
    void anmAtr(u16);
    void eventOrder();
    void checkOrder();
    bool chk_talk();
    bool chk_partsNotMove();
    void lookBack();
    u16 next_msgStatus(u32*);
    s8 getBitMask();
    u32 getMsg_AC1_0();
    u32 getMsg();
    bool chkAttention();
    void setAttention(bool);
    bool charDecide(int);
    void event_actionInit(int);
    bool event_action();
    void privateCut(int);
    void endEvent();
    BOOL isEventEntry();
    void event_proc(int);
    BOOL set_action(ActionFunc, void*);
    void setStt(s8);
    BOOL wait_1();
    BOOL talk_1();
    BOOL wait_action1(void*);
    bool demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    J3DModelData* create_Anm();
    J3DModelData* create_wng_Anm();
    J3DModelData* create_arm_Anm();
    bool create_itm_Mdl();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhase;
    /* 0x6CC */ s8 m_hed_jnt_num;
    /* 0x6CD */ s8 m_bbone_jnt_num;
    /* 0x6CE */ s8 m_arm_L_jnt_num;
    /* 0x6CF */ s8 m_arm_R_jnt_num;
    /* 0x6D0 */ s8 m_hnd_R_jnt_num;
    /* 0x6D1 */ u8 field_0x6D1[0x6D4 - 0x6D1];
    /* 0x6D4 */ J3DModel* mpItemModel;
    /* 0x6D8 */ u32 mShadowID;
    /* 0x6DC */ J3DAnmTexPattern* m_hed_tex_pttrn;
    /* 0x6E0 */ mDoExt_btpAnm mBtpAnim;
    /* 0x6F4 */ u8 mBlinkFrame;
    /* 0x6F5 */ u8 field_0x6F5[0x6F6 - 0x6F5];
    /* 0x6F6 */ s16 mBlinkTimer;
    /* 0x6F8 */ u8 field_0x6F8[0x6FC - 0x6F8];
    /* 0x6FC */ mDoExt_McaMorf* mpWingMorf;
    /* 0x700 */ s8 m_wngL1_jnt_num;
    /* 0x701 */ s8 m_wngR1_jnt_num;
    /* 0x702 */ u8 field_0x702[0x708 - 0x702];
    /* 0x708 */ mDoExt_McaMorf* mpArmMorf;
    /* 0x70C */ s8 m_armL1_jnt_num;
    /* 0x70D */ s8 m_armR1_jnt_num;
    /* 0x70E */ u8 field_0x70E[0x710 - 0x70E];
    /* 0x710 */ ActionFunc mCurrActionFunc;
    /* 0x71C */ Mtx mLeftArmMtx;
    /* 0x74C */ Mtx mRightArmMtx;
    /* 0x77C */ dNpc_PathRun_c mPathRun;
    /* 0x784 */ dNpc_EventCut_c mEventCut;
    /* 0x7F0 */ u8 field_0x7F0[0x7F4 - 0x7F0];
    /* 0x7F4 */ cXyz mInitialPos;
    /* 0x800 */ csXyz mInitialAngle;
    /* 0x806 */ u8 field_0x806[0x808 - 0x806];
    /* 0x808 */ cXyz mEyePos;
    /* 0x814 */ cXyz mLookAtPos;
    /* 0x820 */ u8 field_0x820[0x82C - 0x820];
    /* 0x82C */ f32 mFrame;
    /* 0x830 */ u8 field_0x830[0x844 - 0x830];
    /* 0x844 */ s16 mPrevHeadY;
    /* 0x846 */ s16 mPrevBackboneY;
    /* 0x848 */ s16 mPrevAngleY;
    /* 0x84A */ u8 field_0x84A[0x84C - 0x84A];
    /* 0x84C */ s16 mTimer;
    /* 0x84E */ u8 field_0x84E[0x852 - 0x84E];
    /* 0x852 */ s16 mHeadLookAtMaxVel;
    /* 0x854 */ s16 field_0x854;
    /* 0x856 */ s16 field_0x856;
    /* 0x858 */ u8 mbMorfAnimStopped;
    /* 0x859 */ u8 field_0x859;
    /* 0x85A */ u8 field_0x85A;
    /* 0x85B */ u8 mItemNo;
    /* 0x85C */ u8 field_0x85C[0x85D - 0x85C];
    /* 0x85D */ u8 field_0x85D;
    /* 0x85E */ bool mbHasArms;
    /* 0x85F */ bool mbSetShapeAngle;
    /* 0x860 */ u8 field_0x860;
    /* 0x861 */ u8 field_0x861;
    /* 0x862 */ u8 field_0x862;
    /* 0x863 */ bool mbRanExecute;
    /* 0x864 */ int mbSetEyePos;
    /* 0x868 */ bool mbAttention;
    /* 0x869 */ bool mbTalking;
    /* 0x86A */ bool mbHeadOnlyFollow;
    /* 0x86B */ bool mbInDemo;
    /* 0x86C */ s8 mActionIndex;
    /* 0x86D */ u8 mActNo;
    /* 0x86E */ u8 mAnmAtr;
    /* 0x86F */ u8 mAnmTag;
    /* 0x870 */ s8 mBtpNum;
    /* 0x871 */ s8 mAnmNum;
    /* 0x872 */ u8 field_0x872[0x874 - 0x872];
    /* 0x874 */ s8 mTalkOrder;
    /* 0x875 */ s8 mStatus;
    /* 0x876 */ s8 mPrevStatus;
    /* 0x877 */ s8 mLookBackState;
    /* 0x878 */ s8 mType;
    /* 0x879 */ s8 mSpecificType;
    /* 0x87A */ s8 mActionPhase;
    /* 0x87B */ s8 field_0x87B;
};

#endif /* D_A_NPC_AC1_H */
