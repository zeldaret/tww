#ifndef D_A_NPC_AC1_H
#define D_A_NPC_AC1_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"

class J3DNode;

class daNpc_Ac1_c : public fopNpc_npc_c {
public:
    typedef BOOL (daNpc_Ac1_c::*ProcFunc)(void*);

    struct anm_prm_c {
        /* 0x00 */ s8 mAnmNum;
        /* 0x01 */ s8 mBtpNum;
        /* 0x04 */ f32 mMorf;
        /* 0x08 */ f32 mSpeed;
        /* 0x0C */ int mLoopMode;
        /* 0x10 */ int mHasArms;
    };  // Size: 0x14

    inline daNpc_Ac1_c();

    void nodeWngControl(J3DNode*, J3DModel*);
    void nodeArmControl(J3DNode*, J3DModel*);
    void nodeAc1Control(J3DNode*, J3DModel*);
    bool init_AC1_0();
    bool createInit();
    void setMtx(bool);
    int anmNum_toResID(int);
    int wingAnmNum_toResID(int);
    int btpNum_toResID(int);
    bool setBtp(bool, int);
    bool iniTexPttrnAnm(bool);
    void plyTexPttrnAnm();
    void setAnm_tex(s8);
    BOOL setAnm_anm(anm_prm_c*);
    BOOL setAnm();
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
    int isEventEntry();
    void event_proc(int);
    BOOL set_action(ProcFunc, void*);
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
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 m_hed_jnt_num;
    /* 0x6CD */ s8 m_bbone_jnt_num;
    /* 0x6CE */ s8 m_arm_L_jnt_num;
    /* 0x6CF */ s8 m_arm_R_jnt_num;
    /* 0x6D0 */ s8 m_hnd_R_jnt_num;
    /* 0x6D4 */ J3DModel* mpItemModel;
    /* 0x6D8 */ u32 mShadowID;
    /* 0x6DC */ J3DAnmTexPattern* m_hed_tex_pttrn;
    /* 0x6E0 */ mDoExt_btpAnm mBtpAnm;
    /* 0x6F4 */ u8 mBtpFrame;
    /* 0x6F6 */ s16 mBlinkTimer;
    /* 0x6F8 */ u8 m6F8[0x6FC - 0x6F8];
    /* 0x6FC */ mDoExt_McaMorf* mpWingMorf;
    /* 0x700 */ s8 m_wngL1_jnt_num;
    /* 0x701 */ s8 m_wngR1_jnt_num;
    /* 0x702 */ u8 m702[0x708 - 0x702];
    /* 0x708 */ mDoExt_McaMorf* mpArmMorf;
    /* 0x70C */ s8 m_armL1_jnt_num;
    /* 0x70D */ s8 m_armR1_jnt_num;
    /* 0x710 */ ProcFunc mCurrProcFunc;
    /* 0x71C */ Mtx mLeftArmMtx;
    /* 0x74C */ Mtx mRightArmMtx;
    /* 0x77C */ dNpc_PathRun_c mPath;
    /* 0x784 */ dNpc_EventCut_c mEventCut;
    /* 0x7F0 */ u8 m7F0[0x7F4 - 0x7F0];
    /* 0x7F4 */ cXyz mHomePos;
    /* 0x800 */ csXyz mHomeAngle;
    /* 0x806 */ u8 m806[0x808 - 0x806];
    /* 0x808 */ cXyz mTransformedEyePos;
    /* 0x814 */ cXyz mLookPos;
    /* 0x820 */ u8 m820[0x82C - 0x820];
    /* 0x82C */ f32 mPrevMorfFrame;
    /* 0x830 */ u8 m830[0x844 - 0x830];
    /* 0x844 */ s16 mJointHeadY;
    /* 0x846 */ s16 mJointBackboneY;
    /* 0x848 */ s16 mActorAngleY;
    /* 0x84A */ u8 m84A[0x84C - 0x84A];
    /* 0x84C */ s16 mTalkTimer;
    /* 0x84E */ u8 m84E[0x852 - 0x84E];
    /* 0x852 */ s16 mLookAtMaxVel;
    /* 0x854 */ s16 mTargetAngleY;
    /* 0x856 */ u16 mPrevMsgStatus;
    /* 0x858 */ s8 mbMorfAnimStopped;
    /* 0x859 */ s8 m859;
    /* 0x85A */ u8 m85A;
    /* 0x85B */ u8 mItemNo;
    /* 0x85C */ u8 m85C;
    /* 0x85D */ bool mbHide;
    /* 0x85E */ bool mbHasArms;
    /* 0x85F */ bool m85F;
    /* 0x860 */ bool mbNoMove;
    /* 0x861 */ bool m861;
    /* 0x862 */ u8 m862;
    /* 0x863 */ bool mbInitDone;
    /* 0x864 */ BOOL mbSetEyePos;
    /* 0x868 */ bool mbAttention;
    /* 0x869 */ bool mbTalkReq;
    /* 0x86A */ bool mbHeadOnly;
    /* 0x86B */ bool mbDemo;
    /* 0x86C */ s8 mActionIndex;
    /* 0x86D */ s8 mActNo;
    /* 0x86E */ u8 mAnmAtr;
    /* 0x86F */ u8 mMesgAnimeTag;
    /* 0x870 */ s8 mBtpNum;
    /* 0x871 */ s8 mAnmNum;
    /* 0x872 */ u8 m872[0x874 - 0x872];
    /* 0x874 */ s8 mOrder;
    /* 0x875 */ s8 mStt;
    /* 0x876 */ s8 mPrevStt;
    /* 0x877 */ s8 mLookMode;
    /* 0x878 */ s8 mHioType;
    /* 0x879 */ s8 mType;
    /* 0x87A */ s8 mActionState;
    /* 0x87B */ s8 mMsgCount;
};  // Size: 0x87C

#endif /* D_A_NPC_AC1_H */
