#ifndef D_A_NPC_KF1_H
#define D_A_NPC_KF1_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"

class J3DNode;

class daNpc_Kf1_c : public fopNpc_npc_c {
public:
    typedef BOOL (daNpc_Kf1_c::*ProcFunc)(void*);

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
        /* 0x05 */ BCKNUM_TALK04_e,
        /* 0x06 */ BCKNUM_OKORU_e,
        /* 0x07 */ BCKNUM_BAKUHATU_e,
        /* 0x08 */ BCKNUM_BARAMAKU_e,
        /* 0x09 */ BCKNUM_WAIT02_e,
        /* 0x0A */ BCKNUM_NULL_e,
    };

    enum BtpNum {
        /* 0x00 */ BTPNUM_KF_e,
        /* 0x01 */ BTPNUM_CLOSE_e,
        /* 0x02 */ BTPNUM_NULL_e,
    };

    void _nodeCB_Head(J3DNode*, J3DModel*);
    void _nodeCB_Neck(J3DNode*, J3DModel*);
    void _nodeCB_BackBone(J3DNode*, J3DModel*);
    bool init_KF1_0();
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
    u32 getMsg_KF1_0();
    u32 getMsg();
    void eventOrder();
    void checkOrder();
    bool chk_talk();
    fopAc_ac_c* searchByID(fpc_ProcID, int*);
    bool srch_Tsubo();
    void create_rupee(cXyz, int);
    void ready_kutaniCamera(int, int);
    void lookBack();
    bool chkAttention();
    void setAttention(bool);
    bool decideType(int);
    void cut_init_ANGRY_START(int);
    bool cut_move_ANGRY_START();
    void cut_init_BENSYOU_START(int);
    bool cut_move_BENSYOU_START();
    void cut_init_TSUBO_CNT(int);
    bool cut_move_TSUBO_CNT();
    void cut_init_BENSYOU(int);
    bool cut_move_BENSYOU();
    void cut_init_GET_OUT(int);
    bool cut_move_GET_OUT();
    void cut_init_DSP_RUPEE_CNT(int);
    bool cut_move_DSP_RUPEE_CNT();
    void cut_init_PLYER_TRN(int);
    bool cut_move_PLYER_TRN();
    void cut_init_RUPEE_CNT_END(int);
    bool cut_move_RUPEE_CNT_END();
    void cut_init_START_AGE(int);
    bool cut_move_START_AGE();
    void cut_init_PLYER_MOV(int);
    bool cut_move_PLYER_MOV();
    void cut_init_RUPEE_SET(int);
    bool cut_move_RUPEE_SET();
    void cut_init_TSUBO_ATN(int);
    bool cut_move_TSUBO_ATN();
    void cut_init_TLK_MSG(int);
    void cut_init_CONTNUE_TLK(int);
    bool cut_move_TLK_MSG();
    void privateCut(int);
    void endEvent();
    int isEventEntry();
    void event_proc(int);
    BOOL set_action(ProcFunc, void*);
    void setStt(s8);
    void set_pthPoint(u8);
    s16 chk_tsubo();
    BOOL orderTsuboEvent();
    BOOL wait_1();
    BOOL walk_1();
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
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 m_hed_jnt_num;
    /* 0x6CD */ s8 m_bbone_jnt_num;
    /* 0x6CE */ s8 m_nck_jnt_num;
    /* 0x6D0 */ J3DModel* mpHairModel;
    /* 0x6D4 */ char mArcName[4];
    /* 0x6D8 */ u32 mShadowID;
    /* 0x6DC */ mDoExt_btpAnm mBtpAnm;
    /* 0x6F0 */ u8 mBtpFrame;
    /* 0x6F2 */ s16 mBlinkTimer;
    /* 0x6F4 */ ProcFunc mCurrProcFunc;
    /* 0x700 */ fpc_ProcID m700;
    /* 0x704 */ fpc_ProcID mPartnerID;
    /* 0x708 */ dNpc_PathRun_c mPath;
    /* 0x710 */ cXyz mHomePos;
    /* 0x71C */ csXyz mHomeAngle;
    /* 0x722 */ csXyz mAngle;
    /* 0x728 */ u8 m728[0x730 - 0x728];
    /* 0x730 */ cXyz mTransformedEyePos;
    /* 0x73C */ cXyz mPlayerEyePos;
    /* 0x748 */ u8 m748[0x754 - 0x748];
    /* 0x754 */ cXyz mHeadPos;
    /* 0x760 */ u8 m760[0x76C - 0x760];
    /* 0x76C */ f32 mPrevMorfFrame;
    /* 0x770 */ u8 m770[0x774 - 0x770];
    /* 0x774 */ s16 mActorAngleY;
    /* 0x776 */ s16 mJointHeadY;
    /* 0x778 */ s16 mJointBackboneY;
    /* 0x77A */ u8 m77A[0x77C - 0x77A];
    /* 0x77C */ BOOL mbSetEyePos;
    /* 0x780 */ s16 mEventIDTbl[3];
    /* 0x786 */ s16 mEventIndex;
    /* 0x788 */ u8 m788[0x78C - 0x788];
    /* 0x78C */ s16 mCutTimer;
    /* 0x78E */ s16 mCutCount;
    /* 0x790 */ s16 mTalkTimer;
    /* 0x792 */ s16 mWaitTimer;
    /* 0x794 */ s16 mWalkTimer;
    /* 0x796 */ u8 m796[0x79A - 0x796];
    /* 0x79A */ s16 mTargetAngleY;
    /* 0x79C */ s8 mbMorfAnimStopped;
    /* 0x79D */ u8 m79D;
    /* 0x79E */ u8 mItemNo;
    /* 0x79F */ u8 mSwitchNo;
    /* 0x7A0 */ bool m7A0;
    /* 0x7A1 */ bool mbPaid;
    /* 0x7A2 */ u8 m7A2;
    /* 0x7A3 */ s8 mbGroundHit;
    /* 0x7A4 */ s8 mbWaterHit;
    /* 0x7A5 */ bool m7A5;
    /* 0x7A6 */ bool mbResLoadIsComplete;
    /* 0x7A7 */ bool m7A7;
    /* 0x7A8 */ bool m7A8;
    /* 0x7A9 */ u8 m7A9;
    /* 0x7AA */ bool mbInitDone;
    /* 0x7AB */ bool mbAttention;
    /* 0x7AC */ bool mbTalkReq;
    /* 0x7AD */ bool m7AD;
    /* 0x7AE */ bool mbDemo;
    /* 0x7AF */ u8 m7AF;
    /* 0x7B0 */ fpc_ProcID mRupeeIDs[3];
    /* 0x7BC */ fpc_ProcID mTsuboIDs[8];
    /* 0x7DC */ fpc_ProcID mCamTsuboIDs[3];
    /* 0x7E8 */ fpc_ProcID mItemID;
    /* 0x7EC */ s16 mTsuboNum;
    /* 0x7EE */ s16 mBrokenNum;
    /* 0x7F0 */ u16 mRupee;
    /* 0x7F2 */ s8 mActionIndex;
    /* 0x7F3 */ u8 mAnmAtr;
    /* 0x7F4 */ u8 mMesgAnimeTag;
    /* 0x7F5 */ s8 mBtpNum;
    /* 0x7F6 */ s8 mBckNum;
    /* 0x7F7 */ s8 mOrder;
    /* 0x7F8 */ s8 mStt;
    /* 0x7F9 */ s8 mPrevStt;
    /* 0x7FA */ s8 mLookMode;
    /* 0x7FB */ s8 m7FB;
    /* 0x7FC */ s8 mType;
    /* 0x7FD */ s8 mActionState;
    /* 0x7FE */ s8 mMsgCount;
    /* 0x7FF */ u8 m7FF;
};  // Size: 0x800

#endif /* D_A_NPC_KF1_H */
