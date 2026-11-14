#ifndef D_A_NPC_YW1_H
#define D_A_NPC_YW1_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"

class J3DNode;

class daNpc_Yw1_c : public fopNpc_npc_c {
public:
    typedef BOOL (daNpc_Yw1_c::*ProcFunc)(void*);

    struct anm_prm_c {
        /* 0x00 */ s8 bckNum;
        /* 0x01 */ s8 btpNum;
        /* 0x04 */ f32 morf;
        /* 0x08 */ f32 speed;
        /* 0x0C */ int loopMode;
    };  // Size: 0x10

    enum BckNum {
        /* 0x00 */ BCKNUM_WAIT01_e,
        /* 0x01 */ BCKNUM_TWAIT_e,
        /* 0x02 */ BCKNUM_TWALK_e,
        /* 0x03 */ BCKNUM_TTALK_e,
        /* 0x04 */ BCKNUM_TALK01_e,
        /* 0x05 */ BCKNUM_WAIT02_e,
        /* 0x06 */ BCKNUM_TALK02_e,
        /* 0x07 */ BCKNUM_NULL_e,
    };

    enum BtpNum {
        /* 0x00 */ BTPNUM_HEAD_e,
        /* 0x01 */ BTPNUM_NULL_e,
    };

    inline daNpc_Yw1_c();

    void _nodeCB_Hair(J3DNode*, J3DModel*);
    void _nodeCB_Head(J3DNode*, J3DModel*);
    void _nodeCB_BackBone(J3DNode*, J3DModel*);
    bool init_YW1_0();
    bool init_YW1_1();
    bool init_YW1_2();
    bool init_YW1_3();
    bool createInit();
    void play_animation();
    bool upLift();
    void setMtx(bool);
    int bckResID(int);
    int btpResID(int);
    bool init_texPttrnAnm(s8, bool);
    void play_texPttrnAnm();
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
    u32 getMsg_YW1_0();
    u32 getMsg_YW1_1();
    u32 getMsg_YW1_2();
    u32 getMsg_YW1_3();
    u32 getMsg();
    void eventOrder();
    void checkOrder();
    bool chk_talk();
    bool chk_parts_notMov();
    fopAc_ac_c* searchByID(fpc_ProcID, int*);
    bool partner_search_sub(void* (*)(void*, void*));
    void partner_search();
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
    void chngTsuboAnm();
    bool chk_areaIN(f32, f32, s16, cXyz);
    void set_pthPoint(u8);
    void setHairAngle();
    bool chk_brkTsubo();
    bool chk_bm1Odoroki();
    BOOL wait_1();
    BOOL wait_2();
    BOOL wait_3();
    BOOL walk_1();
    BOOL turn_1();
    BOOL talk_1();
    BOOL wait_action1(void*);
    BOOL wait_action2(void*);
    bool demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL bodyCreateHeap();
    BOOL headCreateHeap();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 m_hed_jnt_num;
    /* 0x6CD */ s8 m_bbone_jnt_num;
    /* 0x6CE */ s8 m_hair1;
    /* 0x6CF */ s8 m_hair2;
    /* 0x6D0 */ s8 m_hair3;
    /* 0x6D4 */ u32 mShadowID;
    /* 0x6D8 */ J3DModel* mpHeadModel;
    /* 0x6DC */ mDoExt_btpAnm mBtpAnm;
    /* 0x6F0 */ u8 mBtpFrame;
    /* 0x6F2 */ s16 mBlinkTimer;
    /* 0x6F4 */ ProcFunc mCurrProcFunc;
    /* 0x700 */ fpc_ProcID mPartnerID;
    /* 0x704 */ fpc_ProcID mTsuboID;
    /* 0x708 */ fpc_ProcID mLookID;
    /* 0x70C */ dNpc_PathRun_c mPath;
    /* 0x714 */ cXyz mHomePos;
    /* 0x720 */ csXyz mHomeAngle;
    /* 0x726 */ csXyz mAngle;
    /* 0x72C */ cXyz mTransformedEyePos;
    /* 0x738 */ cXyz mLookPos;
    /* 0x744 */ cXyz mHeadPos;
    /* 0x750 */ f32 mPrevMorfFrame;
    /* 0x754 */ u8 m754[0x758 - 0x754];
    /* 0x758 */ s16 mActorAngleY;
    /* 0x75A */ s16 mJointHeadY;
    /* 0x75C */ s16 mJointBackboneY;
    /* 0x760 */ BOOL mbSetEyePos;
    /* 0x764 */ u8 m764[0x766 - 0x764];
    /* 0x766 */ s16 mLookTimer;
    /* 0x768 */ u8 m768[0x76C - 0x768];
    /* 0x76C */ s16 mHeadTurnVel;
    /* 0x76E */ s16 mTargetAngleY;
    /* 0x770 */ s8 mbMorfAnimStopped;
    /* 0x771 */ s8 m771;
    /* 0x772 */ u8 mItemNo;
    /* 0x773 */ bool mbCarry;
    /* 0x774 */ bool mbPaid;
    /* 0x775 */ bool mbTsuboBroken;
    /* 0x776 */ bool mbPathEnd;
    /* 0x777 */ bool mbHide;
    /* 0x778 */ bool m778;
    /* 0x779 */ u8 m779;
    /* 0x77A */ bool mbInitDone;
    /* 0x77B */ bool mbAttention;
    /* 0x77C */ bool mbTalkReq;
    /* 0x77D */ bool mbHeadOnly;
    /* 0x77E */ bool mbDemo;
    /* 0x780 */ s16 mHairRotX;
    /* 0x782 */ s16 mHairRotY;
    /* 0x784 */ s16 mHair1RotZ;
    /* 0x786 */ s16 mHair1RotY;
    /* 0x788 */ u8 m788[0x794 - 0x788];
    /* 0x794 */ cXyz mPrevHeadPos;
    /* 0x7A0 */ s16 mHair1VelZ;
    /* 0x7A2 */ s16 mHair1VelY;
    /* 0x7A4 */ s16 mHair2RotZ;
    /* 0x7A6 */ s16 mHair2RotY;
    /* 0x7A8 */ s16 mHair2VelZ;
    /* 0x7AA */ s16 mHair2VelY;
    /* 0x7AC */ s16 mHair3RotZ;
    /* 0x7AE */ s16 mHair3RotY;
    /* 0x7B0 */ s16 mHair3VelZ;
    /* 0x7B2 */ s16 mHair3VelY;
    /* 0x7B4 */ s16 mWindPhase;
    /* 0x7B6 */ s16 mHair1Wind;
    /* 0x7B8 */ s16 mHair2Wind;
    /* 0x7BA */ s16 mHair3Wind;
    /* 0x7BC */ s8 mActionIndex;
    /* 0x7BD */ u8 mAnmAtr;
    /* 0x7BE */ u8 mMesgAnimeTag;
    /* 0x7BF */ s8 mBtpNum;
    /* 0x7C0 */ s8 mBckNum;
    /* 0x7C1 */ s8 mOrder;
    /* 0x7C2 */ s8 mStt;
    /* 0x7C3 */ s8 mPrevStt;
    /* 0x7C4 */ s8 mLookMode;
    /* 0x7C5 */ s8 mHioType;
    /* 0x7C6 */ s8 mType;
    /* 0x7C7 */ s8 mActionState;
    /* 0x7C8 */ s8 mMsgCount;
};  // Size: 0x7CC

#endif /* D_A_NPC_YW1_H */
