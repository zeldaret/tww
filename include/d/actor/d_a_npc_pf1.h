#ifndef D_A_NPC_PF1_H
#define D_A_NPC_PF1_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"

class J3DNode;

class daNpc_Pf1_c : public fopNpc_npc_c {
public:
    typedef BOOL (daNpc_Pf1_c::*ProcFunc)(void*);

    struct anm_prm_c {
        /* 0x00 */ s8 bckNum;
        /* 0x01 */ s8 btpNum;
        /* 0x04 */ f32 morf;
        /* 0x08 */ f32 speed;
        /* 0x0C */ int loopMode;
    };  // Size: 0x10

    enum BckNum {
        /* 0x00 */ BCKNUM_WAIT01_e,
        /* 0x01 */ BCKNUM_WALK01_e,
        /* 0x02 */ BCKNUM_WALK02_e,
        /* 0x03 */ BCKNUM_CRY_e,
        /* 0x04 */ BCKNUM_REGRET_e,
        /* 0x05 */ BCKNUM_SPIT_e,
        /* 0x06 */ BCKNUM_WISH_e,
        /* 0x07 */ BCKNUM_TALK01_e,
        /* 0x08 */ BCKNUM_NULL_e,
    };

    enum BtpNum {
        /* 0x00 */ BTPNUM_MABA01_e,
        /* 0x01 */ BTPNUM_MABA02_e,
        /* 0x02 */ BTPNUM_NULL_e,
    };

    void _nodeCB_Head(J3DNode*, J3DModel*);
    void _nodeCB_BackBone(J3DNode*, J3DModel*);
    bool init_PF1_0();
    bool createInit();
    void play_animation();
    void setMtx(bool);
    int bckResID(int);
    int btpResID(int);
    bool setBtp(s8, bool);
    bool init_texPttrnAnm(s8, bool);
    void play_btp_anm();
    void setAnm_anm(anm_prm_c*);
    void setAnm_NUM(int, int);
    void setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(u8);
    void ctrlAnmAtr();
    void setAnm_ATR();
    void anmAtr(u16);
    u16 next_msgStatus(u32*);
    u32 getMsg_PF1_0();
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
    void createTama(f32);
    bool chk_areaIN(f32, cXyz);
    bool endEvent_check();
    bool startEvent_check();
    void set_pthPoint(u8);
    bool chk_attn();
    void setBikon(cXyz);
    void delBikon();
    BOOL wait_1();
    BOOL regret();
    BOOL attk_1();
    BOOL walk_1();
    BOOL wait_2();
    BOOL wait_3();
    BOOL talk_1();
    BOOL wait_action1(void*);
    bool demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL bodyCreateHeap();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 m_hed_jnt_num;
    /* 0x6CD */ s8 m_bbone_jnt_num;
    /* 0x6CE */ char mArcName[3];
    /* 0x6D4 */ u32 mShadowID;
    /* 0x6D8 */ mDoExt_btpAnm mBtpAnm;
    /* 0x6EC */ u8 mBtpFrame;
    /* 0x6EE */ s16 mBlinkTimer;
    /* 0x6F0 */ ProcFunc mCurrProcFunc;
    /* 0x6FC */ u8 m6FC[0x700 - 0x6FC];
    /* 0x700 */ fpc_ProcID mPartnerID;
    /* 0x704 */ dNpc_PathRun_c mPath;
    /* 0x70C */ cXyz mHomePos;
    /* 0x718 */ csXyz mHomeAngle;
    /* 0x71E */ csXyz mAngle;
    /* 0x724 */ u8 m724[0x72C - 0x724];
    /* 0x72C */ cXyz mTransformedEyePos;
    /* 0x738 */ cXyz mPlayerEyePos;
    /* 0x744 */ u8 m744[0x750 - 0x744];
    /* 0x750 */ cXyz mHeadPos;
    /* 0x75C */ u8 m75C[0x768 - 0x75C];
    /* 0x768 */ cXyz mGndNormal;
    /* 0x774 */ f32 mPrevMorfFrame;
    /* 0x778 */ u8 m778[0x77C - 0x778];
    /* 0x77C */ s16 mActorAngleY;
    /* 0x77E */ s16 mJointHeadY;
    /* 0x780 */ s16 mJointBackboneY;
    /* 0x782 */ u8 m782[0x784 - 0x782];
    /* 0x784 */ BOOL mbSetEyePos;
    /* 0x788 */ s16 mEventIDTbl[1];
    /* 0x78A */ s16 mEventIndex;
    /* 0x78C */ u8 m78C[0x796 - 0x78C];
    /* 0x796 */ s16 mAttkTimer;
    /* 0x798 */ s16 mTimer;
    /* 0x79A */ u8 m79A[0x79E - 0x79A];
    /* 0x79E */ s16 mTargetAngleY;
    /* 0x7A0 */ s8 mbMorfAnimStopped;
    /* 0x7A1 */ s8 mLoopCount;
    /* 0x7A2 */ u8 mItemNo;
    /* 0x7A3 */ u8 m7A3;
    /* 0x7A4 */ bool m7A4;
    /* 0x7A5 */ bool mbTalked;
    /* 0x7A6 */ u8 m7A6;
    /* 0x7A7 */ bool mbResLoadIsComplete;
    /* 0x7A8 */ bool m7A8;
    /* 0x7A9 */ u8 m7A9;
    /* 0x7AA */ bool m7AA;
    /* 0x7AB */ u8 m7AB;
    /* 0x7AC */ bool mbInitDone;
    /* 0x7AD */ bool mbAttention;
    /* 0x7AE */ bool mbTalkReq;
    /* 0x7AF */ bool m7AF;
    /* 0x7B0 */ bool m7B0;
    /* 0x7B1 */ bool mbDemo;
    /* 0x7B2 */ s8 mActionIndex;
    /* 0x7B3 */ u8 mAnmAtr;
    /* 0x7B4 */ u8 mMesgAnimeTag;
    /* 0x7B5 */ s8 mBtpNum;
    /* 0x7B6 */ s8 mBckNum;
    /* 0x7B7 */ s8 mOrder;
    /* 0x7B8 */ s8 mStt;
    /* 0x7B9 */ s8 mPrevStt;
    /* 0x7BA */ s8 mLookMode;
    /* 0x7BB */ s8 m7BB;
    /* 0x7BC */ s8 mType;
    /* 0x7BD */ s8 mActionState;
    /* 0x7BE */ s8 mMsgCount;
    /* 0x7BF */ u8 m7BF;
};  // Size: 0x7C0

#endif /* D_A_NPC_PF1_H */
