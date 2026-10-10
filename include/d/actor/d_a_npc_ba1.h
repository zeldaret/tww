#ifndef D_A_NPC_BA1_H
#define D_A_NPC_BA1_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"

class J3DNode;

class daNpc_Ba1_c : public fopNpc_npc_c {
public:
    typedef BOOL (daNpc_Ba1_c::*ProcFunc)(void*);
    struct anm_prm_c {
        /* 0x00 */ s8 mAnmNum;
        /* 0x01 */ s8 mBtpNum;
        /* 0x02 */ s16 field_0x02;
        /* 0x04 */ f32 mMorf;
        /* 0x08 */ f32 mSpeed;
        /* 0x0C */ int mLoopMode;
    };

    void holdEventOn() { mbHoldEvent = 1; }

    void nodeBa1Control(J3DNode*, J3DModel*);
    bool XyCheck_cB(int);
    s16 XyEvent_cB(int);
    bool init_BA1_0();
    bool init_BA1_1();
    bool init_BA1_2();
    bool init_BA1_3();
    bool init_BA1_4();
    bool createInit();
    void setMtx(bool);
    int anmNum_toResID(int);
    int btpNum_toResID(int);
    bool setBtp(bool, int);
    bool iniTexPttrnAnm(bool);
    void plyTexPttrnAnm();
    void setAnm_tex(s8);
    BOOL setAnm_anm(anm_prm_c*);
    void setAnm_NUM(int, int);
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
    bool chk_drct(f32);
    bool chk_partsNotMove();
    void lookBack();
    u16 next_msgStatus(u32*);
    u32 getMsg_BA1_0();
    u32 getMsg_BA1_1();
    u32 getMsg_BA1_3();
    u32 getMsg_BA1_4();
    u32 getMsg();
    bool chkAttention();
    void setAttention(bool);
    fopAc_ac_c* searchByID(fpc_ProcID);
    bool partner_srch_sub(fpcLyIt_JudgeFunc);
    void partner_srch();
    bool check_useFairyArea();
    bool checkCommandTalk();
    bool charDecide(int);
    void eInit_SET_PLYER_GOL_();
    void eInit_PLYER_INI_POS_();
    void eInit_USE_FAIRY_END_();
    void eInit_MOV_POS_();
    void eInit_SET_PLYER_TRN_ANG_();
    void eInit_ACTOR_DRW_CONTROL_(int*, int*);
    void eInit_setEvTimer(int*);
    void eInit_CHK_FAIRY_(int*);
    f32 eInit_prmFloat(f32*, f32);
    void eInit_SET_EYE_OFF_(f32*);
    void eInit_EYE_OFF_ZRO_(f32*);
    void eInit_CHK_FAIRY_MOV_1(int*);
    void event_actionInit(int);
    bool eMove_MOV_POS_();
    bool eMove_CHK_FAIRY_();
    bool eMove_EYE_OFF_ZRO_();
    bool eMove_CHK_FAIRY_MOV_1();
    bool event_action();
    void cut_init_START_TALE1(int);
    bool cut_move_START_TALE1();
    void privateCut(int);
    void endEvent();
    BOOL isEventEntry();
    void event_proc(int);
    BOOL set_action(int (daNpc_Ba1_c::*)(void*), void*);
    void setStt(s8);
    BOOL wait_0();
    BOOL wait_1();
    BOOL talk_1();
    BOOL talk_2();
    BOOL wait_2();
    BOOL wait_3();
    BOOL ZZZwai();
    BOOL wait_action1(void*);
    BOOL wait_action2(void*);
    BOOL demo_action1(void*);
    BOOL wait_action3(void*);
    BOOL wait_action4(void*);
    bool demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    J3DModelData* create_Anm();
    bool create_itm_Mdl();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 m_hed_jnt_num;
    /* 0x6CD */ s8 m_bbone_jnt_num;
    /* 0x6CE */ s8 m_footL_jnt_num;
    /* 0x6D0 */ J3DModel* mpClothModel;
    /* 0x6D4 */ u32 mShadowID;
    /* 0x6D8 */ J3DAnmTexPattern* m_hed_tex_pttrn;
    /* 0x6DC */ mDoExt_btpAnm mHeadBtpAnm;
    /* 0x6F0 */ u8 mBlinkFrame;
    /* 0x6F2 */ s16 mBlinkTimer;
    /* 0x6F4 */ ProcFunc mCurrProcFunc;
    /* 0x700 */ u8 field_0x700[0x708 - 0x700];
    /* 0x708 */ dNpc_EventCut_c mEventCut;
    /* 0x774 */ fpc_ProcID mPartnerProcID;
    /* 0x778 */ cXyz mInitialPos;
    /* 0x784 */ csXyz mInitialAngle;
    /* 0x78A */ csXyz m78A;
    /* 0x790 */ cXyz mTransformedEyePos;
    /* 0x79C */ cXyz m79C;
    /* 0x7A8 */ u8 field_0x7A8[0x7C0 - 0x7A8];
    /* 0x7C0 */ f32 mPrevMorfFrame;
    /* 0x7C4 */ f32 mEyeOffset;
    /* 0x7C8 */ f32 mEyeOffsetZero;
    /* 0x7CC */ s16 mJointHeadY;
    /* 0x7CE */ s16 mJointBackboneY;
    /* 0x7D0 */ s16 mActorAngleY;
    /* 0x7D2 */ s16 mEventIdTable[6];
    /* 0x7DE */ s16 mEventIdx;
    /* 0x7E0 */ s16 mEvTimer;
    /* 0x7E2 */ s16 mEvTimer2;
    /* 0x7E4 */ u8 field_0x7E4[0x7E8 - 0x7E4];
    /* 0x7E8 */ s16 mLookAtMaxVel;
    /* 0x7EA */ s16 mTargetYRot;
    /* 0x7EC */ u8 field_0x7EC[0x7EE - 0x7EC];
    /* 0x7EE */ s8 mbMorfAnimStopped;
    /* 0x7EF */ u8 m7EF;
    /* 0x7F0 */ s8 m7F0;
    /* 0x7F1 */ u8 mItemNo;
#if VERSION > VERSION_JPN
    /* 0x7F2 */ u8 m7F2;
#endif
    /* 0x7F3 */ u8 field_0x7F3[0x7F4 - 0x7F3];
    /* 0x7F4 */ bool mbInitGrandma0;
    /* 0x7F5 */ bool m7F5;
    /* 0x7F6 */ bool m7F6;
    /* 0x7F7 */ bool m7F7;
    /* 0x7F8 */ bool m7F8;
    /* 0x7F9 */ bool mbHoldEvent;
    /* 0x7FA */ bool m7FA;
    /* 0x7FB */ bool m7FB;
    /* 0x7FC */ bool mFairyUsed;
    /* 0x7FD */ bool m7FD;
    /* 0x7FE */ bool m7FE;
    /* 0x7FF */ bool m7FF;
    /* 0x800 */ bool mbRanExecute;
    /* 0x804 */ BOOL mbSetEyePos;
    /* 0x808 */ bool mbAttention;
    /* 0x809 */ bool m809;
    /* 0x80A */ bool mHeadOnlyFollow;
    /* 0x80B */ bool mbInDemo;
    /* 0x80C */ s8 mActionIndex;
    /* 0x80D */ s8 mActNo;
    /* 0x80E */ u8 m80E;
    /* 0x80F */ u8 mMesgAnimeTagInfo;
    /* 0x810 */ s8 mBtpNum;
    /* 0x811 */ s8 mAnmNum;
    /* 0x812 */ s8 m812;
    /* 0x813 */ s8 mStatus;
    /* 0x814 */ s8 mPrevStatus;
    /* 0x815 */ s8 mLookBackState;
    /* 0x816 */ s8 mType;
    /* 0x817 */ s8 mSpecificType;
    /* 0x818 */ s8 m818;
    /* 0x819 */ s8 m819;
};  // Size: 0x81C

#endif /* D_A_NPC_BA1_H */
