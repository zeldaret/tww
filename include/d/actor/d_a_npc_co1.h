#ifndef D_A_NPC_CO1_H
#define D_A_NPC_CO1_H

#include "d/d_kankyo.h"
#include "d/d_npc.h"
#include "f_op/f_op_actor.h"

class J3DNode;

class daNpc_Co1_c : public fopNpc_npc_c {
public:
    typedef BOOL (daNpc_Co1_c::*ProcFunc)(void*);

    struct anm_prm_c {
        /* 0x00 */ s8 mAnmNum;
        /* 0x01 */ s8 mBtpNum;
        /* 0x04 */ f32 mMorf;
        /* 0x08 */ f32 mSpeed;
        /* 0x0C */ int mLoopMode;
    };  // Size: 0x10

    inline daNpc_Co1_c();

    void nodeCo1Control(J3DNode*, J3DModel*);
    bool init_CO1_0();
    bool createInit();
    void setMtx(bool);
    int anmNum_toResID(int);
    int anmNum_toResID_prl(int);
    int btpNum_toResID(int);
    bool setBtp(bool, int);
    bool setBtk(bool);
    bool iniTexPttrnAnm(bool);
    void plyTexPttrnAnm();
    void setAnm_tex(s8);
    BOOL setAnm_anm(anm_prm_c*);
    void setAnm_NUM(int, int);
    BOOL setAnm();
    void chg_anmTag();
    void control_anmTag();
    void chg_anmAtr(u8);
    void control_anmAtr();
    void setAnm_ATR(int);
    void anmAtr(u16);
    void eventOrder();
    void checkOrder();
    void setCollision_SP_();
    void set_target(int);
    bool chk_talk();
    bool chk_partsNotMove();
    void lookBack();
    u16 next_msgStatus(u32*);
    u32 getMsg_CO1_0();
    u32 getMsg();
    bool chkAttention();
    void setAttention(bool);
    bool charDecide(int);
    void eInit_MDR_();
    void eInit_RED_LTR_();
    void event_actionInit(int);
    bool eMove_MDR_();
    bool eMove_RED_LTR_();
    bool event_action();
    void privateCut(int);
    void endEvent();
    int isEventEntry();
    void event_proc(int);
    BOOL set_action(ProcFunc, void*);
    void setStt(s8);
    BOOL wait_1();
    BOOL wait_2();
    BOOL wakeup();
    BOOL talk_1();
    BOOL toru_1();
    BOOL read_1();
    BOOL modoru();
    BOOL wait_action1(void*);
    bool demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    J3DModelData* create_Anm();
    J3DModelData* create_prl_Anm();
    bool create_itm_Mdl();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 m_hed_jnt_num;
    /* 0x6CD */ s8 m_bbone_jnt_num;
    /* 0x6CE */ s8 m_hnd_R_jnt_num;
    /* 0x6D0 */ mDoExt_McaMorf* mpPrlMorf;
    /* 0x6D4 */ J3DAnmTextureSRTKey* m_prl_btk;
    /* 0x6D8 */ s8 m_prl_jnt_num;
    /* 0x6DC */ mDoExt_btkAnm mBtkAnm;
    /* 0x6F0 */ u8 mBtkFrame;
    /* 0x6F4 */ J3DModel* mpItemModel;
    /* 0x6F8 */ u32 mShadowID;
    /* 0x6FC */ J3DAnmTexPattern* m_hed_tex_pttrn;
    /* 0x700 */ mDoExt_btpAnm mBtpAnm;
    /* 0x714 */ u8 mBtpFrame;
    /* 0x716 */ s16 mBlinkTimer;
    /* 0x718 */ ProcFunc mCurrProcFunc;
    /* 0x724 */ u8 m724[0x72C - 0x724];
    /* 0x72C */ dNpc_EventCut_c mEventCut;
    /* 0x798 */ u8 m798[0x79C - 0x798];
    /* 0x79C */ cXyz mHomePos;
    /* 0x7A8 */ csXyz mHomeAngle;
    /* 0x7AE */ u8 m7AE[0x7B0 - 0x7AE];
    /* 0x7B0 */ cXyz mTransformedEyePos;
    /* 0x7BC */ cXyz mLookPos;
    /* 0x7C8 */ u8 m7C8[0x7D4 - 0x7C8];
    /* 0x7D4 */ f32 mPrevMorfFrame;
    /* 0x7D8 */ u8 m7D8[0x7EC - 0x7D8];
    /* 0x7EC */ s16 mJointHeadY;
    /* 0x7EE */ s16 mJointBackboneY;
    /* 0x7F0 */ s16 mActorAngleY;
    /* 0x7F2 */ s16 mEventIdTbl[3];
    /* 0x7F8 */ s16 mEventIdx;
    /* 0x7FA */ u8 m7FA[0x7FC - 0x7FA];
    /* 0x7FC */ s16 mTalkTimer;
    /* 0x7FE */ u8 m7FE[0x802 - 0x7FE];
    /* 0x802 */ s16 mLookAtMaxVel;
    /* 0x804 */ s16 mTargetAngleY;
    /* 0x806 */ u8 m806[0x808 - 0x806];
    /* 0x808 */ s8 mbMorfAnimStopped;
    /* 0x809 */ s8 m809;
    /* 0x80A */ s8 m80A;
    /* 0x80B */ u8 mItemNo;
    /* 0x80C */ u8 m80C;
    /* 0x80D */ bool mbHide;
    /* 0x80E */ u8 m80E;
    /* 0x80F */ bool m80F;
    /* 0x810 */ bool mbNoMove;
    /* 0x811 */ bool m811;
    /* 0x812 */ u8 m812;
    /* 0x813 */ bool mbShowItem;
    /* 0x814 */ u8 m814;
    /* 0x815 */ bool mbInitDone;
    /* 0x818 */ BOOL mbSetEyePos;
    /* 0x81C */ bool mbAttention;
    /* 0x81D */ bool mbTalkReq;
    /* 0x81E */ bool mbHeadOnly;
    /* 0x81F */ bool mbDemo;
    /* 0x820 */ LIGHT_INFLUENCE mLight;
    /* 0x840 */ cXyz mPearlPos;
    /* 0x84C */ f32 mGlow;
    /* 0x850 */ s16 mGlowPhase;
    /* 0x852 */ u8 m852[0x854 - 0x852];
    /* 0x854 */ s8 mActionIndex;
    /* 0x855 */ s8 mActNo;
    /* 0x856 */ u8 mAnmAtr;
    /* 0x857 */ u8 mMesgAnimeTag;
    /* 0x858 */ s8 mBtpNum;
    /* 0x859 */ s8 mAnmNum;
    /* 0x85A */ u8 m85A[0x85C - 0x85A];
    /* 0x85C */ s8 mOrder;
    /* 0x85D */ s8 mStt;
    /* 0x85E */ s8 mNextStt;
    /* 0x85F */ s8 mLookMode;
    /* 0x860 */ s8 mHioType;
    /* 0x861 */ s8 mType;
    /* 0x862 */ s8 mActionState;
    /* 0x863 */ s8 mMsgCount;
};  // Size: 0x864

#endif /* D_A_NPC_CO1_H */
