#ifndef D_A_NPC_TT_H
#define D_A_NPC_TT_H

#include "f_op/f_op_actor.h"
#include "d/d_npc.h"

struct tt_ke_s {
    /* 0x00 */ cXyz field_0x00[10];
    /* 0x78 */ cXyz field_0x78[10];
    void ke_control(f32);
    void ke_pos_set(cXyz*);
};

struct daNpc_Tt_ke_c {
    tt_ke_s field_0x6C8[8];
    mDoExt_3DlineMat0_c mLineMat;
};

class daNpc_Tt_c : public fopAc_ac_c {
public:

    enum ActionStatus {
        ACTION_ENDING = -1,
        ACTION_STARTING = 0,
        ACTION_ONGOING = 1
    };

    enum TalkStates {
        TALK_FINISHED = -1,
        TALK_INIT = 0,
        TALK_MSG_CREATE = 1,
        TALK_ACTIVE = 2
    };

    typedef BOOL (daNpc_Tt_c::*ActionFunc)(void*);

    bool ChkOrder(u8 flag) { return mOrderFlags & flag; }
    void ClrOrder() { mOrderFlags = 0; }
    void SetOrder(u8 flag) { mOrderFlags |= flag; }
    bool chkEvFlag(u16 evFlag) { return (mEvFlags & evFlag) == evFlag; }
    bool chkFlag(u16 flag) { return (mFlags & flag) == flag; }
    void clrEvFlag(u16 evFlag) { mEvFlags &= ~evFlag; }
    void clrFlag(u16 flag) { mFlags &= ~flag; }

    s8 getBackboneJntNum() { return m_backbone_jnt_num; }
    s8 getHeadJntNum() { return m_head_jnt_num; }
    s16 getBackbone_x() { return m_jnt.getBackbone_x(); }
    s16 getBackbone_y() { return m_jnt.getBackbone_y(); }
    s16 getHead_x() { return m_jnt.getHead_x(); }
    s16 getHead_y() { return m_jnt.getHead_y(); }

    void incAttnSetCount() {
        if (mAttnSetCount != 0xff) {
            mAttnSetCount++;
        }  
    }

    BOOL setAction(ActionFunc actionFunc, void* arg) {
        if (mCurrActionFunc != actionFunc) {
            if (mCurrActionFunc != NULL) {
                mActionStatus = ACTION_ENDING;
                (this->*mCurrActionFunc)(arg);
            }
            mCurrActionFunc = actionFunc;
            mActionStatus = ACTION_STARTING;
            (this->*mCurrActionFunc)(arg);
        }
        return TRUE;
    }

    void setAttentionBasePos(cXyz i_attnBasePos) { mAttnBasePos = i_attnBasePos; }
    void setEvFlag(u16 evFlag) { mEvFlags |= evFlag;}
    void setEyePos(cXyz i_eyePos) { mEyePos = i_eyePos; }
    void setFlag(u16 flag) { mFlags |= flag; }

    s16 XyCheckCB(int);
    void setAnmStatus();
    void eventOrder();
    void checkOrder();
    u16 next_msgStatus(u32*);
    u32 getMsg();
    void setCollision();
    void talkInit();
    void msgAnm();
    void msgPushButton();
    void msgContinue();
    u16 talk();
    void demoInitChange();
    bool demoProcTact1();
    void demoInitPatten();
    bool demoProcPatten();
    void demoInitSpeak();
    bool demoProcSpeak();
    void demoInitWait();
    bool demoProcWait();
    void demoInitCom();
    void demoProcCom();
    s32 getNowEventAction();
    bool demoProc();
    BOOL init();
    void setAttention(bool);
    void lookBack();
    bool wait01();
    bool talk01();
    bool tact00();
    BOOL wait_action(void*);
    void set_ke_root(int, int, int);
    void ke_execute();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL CreateHeap();

    BOOL initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm(int);
    void danceInit(int);
    BOOL danceProc();
    BOOL danceNext();

public:
    /* 0x290 */ dNpc_HeadAnm_c mHeadAnm;
    /* 0x2B4 */ s16 mEventIdx;
    /* 0x2B6 */ u8 field_0x2B6[0x2B8 - 0x2B6];
    /* 0x2B8 */ request_of_phase_process_class mPhs;
    /* 0x2C0 */ mDoExt_McaMorf* mpMorf;
    /* 0x2C4 */ u32 mShadowId;
    /* 0x2C8 */ J3DAnmTexPattern* m_head_tex_pattern;
    /* 0x2CC */ mDoExt_btpAnm mBtpAnm;
    /* 0x2E0 */ u8 mBlinkFrame;
    /* 0x2E1 */ u8 field_0x2E1[0x2E2 - 0x2E1];
    /* 0x2E2 */ s16 mBlinkTimer;
    /* 0x2E4 */ dBgS_ObjAcch mObjAcch;
    /* 0x4A8 */ dBgS_AcchCir mAcchCir;
    /* 0x4E8 */ dCcD_Stts mStts;
    /* 0x524 */ dCcD_Cyl mCyl;
    /* 0x654 */ s8 m_head_jnt_num;
    /* 0x655 */ s8 m_backbone_jnt_num;
    /* 0x656 */ u8 field_0x656[0x658 - 0x656];
    /* 0x658 */ dNpc_JntCtrl_c m_jnt;
    /* 0x68C */ cXyz mEyePos;
    /* 0x698 */ cXyz mAttnBasePos;
    /* 0x6A4 */ s16 mMaxHeadTurnVelocity;
    /* 0x6A6 */ u8 field_0x6A6[0x6A8 - 0x6A6];
    /* 0x6A8 */ s8 mAnmEnded;
    /* 0x6A9 */ u8 mAttnSetCount;
    /* 0x6AA */ u8 field_0x6AA[0x6AC - 0x6AA];
    /* 0x6AC */ f32 mAnmTimer;
    /* 0x6B0 */ u32 mCurrMsgNo;
    /* 0x6B4 */ u16 mFlags;
    /* 0x6B6 */ s16 mNoticeLinkTimer;
    /* 0x6B8 */ ActionFunc mCurrActionFunc;
    /* 0x6C4 */ u8 mDanceStep;
    /* 0x6C5 */ u8 mDanceStepTimer;
    /* 0x6C6 */ u8 field_0x6C6[0x6C8 - 0x6C6];
    /* 0x6C8 */ daNpc_Tt_ke_c mLineKe;
    /* 0xE64 */ s8 mTexPatternIdx;
    /* 0xE65 */ s8 mCurrAnmIdx;
    /* 0xE66 */ s8 mAnmLoopCount;
    /* 0xE67 */ u8 mOrderFlags;
    /* 0xE68 */ s8 mState;
    /* 0xE69 */ s8 mReturnToState;
    /* 0xE6A */ u8 mType;
    /* 0xE6B */ s8 mActionStatus;
    /* 0xE6C */ s8 mTalkState;
    /* 0xE6D */ u8 mMsgAnmIdx;
    /* 0xE6E */ u8 field_0xE6E[0xE70 - 0xE6E];
    /* 0xE70 */ u32 mMtrlSndId;
    /* 0xE74 */ s8 mReverb;
    /* 0xE75 */ u8 mEvFlags;
    /* 0xE76 */ s16 mSoundTimer;
    /* 0xE78 */ s16 mTimer;
    /* 0xE7A */ u8 field_0xE7A;
    /* 0xE7B */ u8 field_0xE7B[0xE7C - 0xE7B];
    /* 0xE7C */ u32 mMsgNo;
    /* 0xE80 */ int mStaffIdx;
};  // Size: 0xE84

#endif /* D_A_NPC_TT_H */
