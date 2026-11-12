#ifndef D_A_NPC_GK1_H
#define D_A_NPC_GK1_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"

class J3DNode;

class daNpc_Gk1_c : public fopNpc_npc_c {
public:
    typedef BOOL (daNpc_Gk1_c::*ProcFunc)(void*);

    struct anm_prm_c {
        /* 0x00 */ s8 bckNum;
        /* 0x01 */ s8 btpNum;
        /* 0x04 */ f32 morf;
        /* 0x08 */ f32 speed;
        /* 0x0C */ int loopMode;
    };  // Size: 0x10

    enum BckNum {
        /* 0x00 */ BCKNUM_WAIT01_e,
        /* 0x01 */ BCKNUM_WALK_e,
        /* 0x02 */ BCKNUM_TALK01_e,
        /* 0x03 */ BCKNUM_TALK02_e,
        /* 0x04 */ BCKNUM_TALK03_e,
        /* 0x05 */ BCKNUM_NULL_e,
    };

    enum BtpNum {
        /* 0x00 */ BTPNUM_GK_e,
        /* 0x01 */ BTPNUM_NULL_e,
    };

    void _nodeCB_Head(J3DNode*, J3DModel*);
    void _nodeCB_Neck(J3DNode*, J3DModel*);
    void _nodeCB_BackBone(J3DNode*, J3DModel*);
    bool init_GK1_0();
    bool createInit();
    void play_animation();
    void setMtx(bool);
    int bckResID(int);
    int btpResID(int);
    bool setBtp(s8, bool);
    bool init_texPttrnAnm(s8, bool);
    void play_btp_anm();
    void setAnm_anm(anm_prm_c*);
    void setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(u8);
    void ctrlAnmAtr();
    void setAnm_ATR();
    void anmAtr(u16);
    u16 next_msgStatus(u32*);
    u32 getMsg_GK1_0();
    u32 getMsg();
    void eventOrder();
    void checkOrder();
    bool chk_talk();
    bool chk_parts_notMov();
    fopAc_ac_c* searchByID(fpc_ProcID, int*);
    void lookBack();
    bool chkAttention();
    void setAttention(bool);
    bool decideType(int);
    void privateCut(int);
    void endEvent();
    int isEventEntry();
    void event_proc(int);
    BOOL set_action(ProcFunc, void*);
    void setStt(s8);
    bool chk_attn();
    BOOL wait_1();
    BOOL talk_1();
    BOOL wait_action1(void*);
    bool demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL bodyCreateHeap();
    BOOL itemCreateHeap();
    BOOL hat_CreateHeap();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 m_hed_jnt_num;
    /* 0x6CD */ s8 m_bbone_jnt_num;
    /* 0x6CE */ s8 m_nck_jnt_num;
    /* 0x6D0 */ J3DModel* mpHairModel;
    /* 0x6D4 */ J3DModel* mpHatModel;
    /* 0x6D8 */ char mArcName[4];
    /* 0x6DC */ u32 mShadowID;
    /* 0x6E0 */ mDoExt_btpAnm mBtpAnm;
    /* 0x6F4 */ u8 mBtpFrame;
    /* 0x6F6 */ s16 mBlinkTimer;
    /* 0x6F8 */ ProcFunc mCurrProcFunc;
    /* 0x704 */ u8 m704[0x708 - 0x704];
    /* 0x708 */ fpc_ProcID mPartnerID;
    /* 0x70C */ u8 m70C[0x714 - 0x70C];
    /* 0x714 */ cXyz mHomePos;
    /* 0x720 */ csXyz mHomeAngle;
    /* 0x726 */ csXyz mAngle;
    /* 0x72C */ u8 m72C[0x734 - 0x72C];
    /* 0x734 */ cXyz mTransformedEyePos;
    /* 0x740 */ cXyz mPlayerEyePos;
    /* 0x74C */ u8 m74C[0x758 - 0x74C];
    /* 0x758 */ cXyz mHeadPos;
    /* 0x764 */ u8 m764[0x770 - 0x764];
    /* 0x770 */ f32 mPrevMorfFrame;
    /* 0x774 */ u8 m774[0x778 - 0x774];
    /* 0x778 */ s16 mActorAngleY;
    /* 0x77A */ s16 mJointHeadY;
    /* 0x77C */ s16 mJointBackboneY;
    /* 0x77E */ u8 m77E[0x780 - 0x77E];
    /* 0x780 */ BOOL mbSetEyePos;
    /* 0x784 */ s16 mEventIDTbl[1];
    /* 0x786 */ s16 mEventIndex;
    /* 0x788 */ u8 m788[0x790 - 0x788];
    /* 0x790 */ s16 mTalkTimer;
    /* 0x792 */ u8 m792[0x79A - 0x792];
    /* 0x79A */ s16 mTargetAngleY;
    /* 0x79C */ s8 mbMorfAnimStopped;
    /* 0x79D */ u8 m79D;
    /* 0x79E */ u8 mItemNo;
    /* 0x79F */ bool mbResLoadIsComplete;
    /* 0x7A0 */ bool m7A0;
    /* 0x7A1 */ bool m7A1;
    /* 0x7A2 */ u8 m7A2;
    /* 0x7A3 */ bool mbInitDone;
    /* 0x7A4 */ bool mbAttention;
    /* 0x7A5 */ bool mbTalkReq;
    /* 0x7A6 */ bool m7A6;
    /* 0x7A7 */ bool mbTurnHome;
    /* 0x7A8 */ bool mbDemo;
    /* 0x7A9 */ s8 mActionIndex;
    /* 0x7AA */ u8 mAnmAtr;
    /* 0x7AB */ u8 mMesgAnimeTag;
    /* 0x7AC */ s8 mBtpNum;
    /* 0x7AD */ s8 mBckNum;
    /* 0x7AE */ s8 mOrder;
    /* 0x7AF */ s8 mStt;
    /* 0x7B0 */ s8 mPrevStt;
    /* 0x7B1 */ s8 mLookMode;
    /* 0x7B2 */ s8 m7B2;
    /* 0x7B3 */ s8 mType;
    /* 0x7B4 */ s8 mActionState;
    /* 0x7B5 */ s8 mMsgCount;
    /* 0x7B6 */ u8 m7B6[0x7B8 - 0x7B6];
};  // Size: 0x7B8


#endif /* D_A_NPC_GK1_H */
