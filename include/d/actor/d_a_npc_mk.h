#ifndef D_A_NPC_MK_H
#define D_A_NPC_MK_H

#include "f_op/f_op_actor.h"
#include "d/d_npc.h"
#include "d/actor/d_a_npc_mk_static.h"

class daNpc_Mk_c : public fopAc_ac_c {
public:

    enum TalkStates {
        TALK_FINISHED = -1,
        TALK_INIT = 0,
        TALK_MSG_CREATE = 1,
        TALK_ACTIVE = 2
    };

    enum ActionStatus {
        ACTION_STARTING = 0,
        ACTION_ONGOING = 1,
        ACTION_ENDING = -1,
    };

    enum VisitModes {
        VISIT_START = 0,
        VISIT_TALK = 1,
        VISIT_WALK_PATH = 2,
        VISIT_RUN_LINK = 3,
        VISIT_WALK_AROUND_LINK = 4,
        VISIT_REACHED_LINK = 5,
        VISIT_NOTICE_LINK = 6,
        VISIT_LEFT_PATH = 7,
        VISIT_WALK_PATH_FAST = 8,
        VISIT_WALK_PATH_IGNORE_LINK = 9,
    };

    enum States {
        STATE_WAIT = 0,
        STATE_TALK01 = 1,
        STATE_TALK02 = 2,
        STATE_VISIT = 3,
        STATE_CLIMB01 = 4,
        STATE_DROP01 = 5,
        STATE_RUNAWAY = 6,
        STATE_JUMP = 7,
        STATE_JITANDA01 = 8,
        STATE_JITANDA02 = 9,
        STATE_DEMO01 = 10,
        STATE_DEMO02 = 11,
        STATE_DEMO03 = 12,
        STATE_13 = 13 // unsure how to call
    };

    enum Types {
        TYPE_NONE = 0, // unsure how to call
        TYPE_NORMAL = 1,
        TYPE_MINIGAME = 2,
    };

    typedef BOOL (daNpc_Mk_c::*ActionFunc)(void*);

    BOOL ChkOrder(u8 flag) { return mOrderFlags & flag; }
    void ClrOrder(u8 flag) { mOrderFlags &= ~flag; }
    void SetOrder(u8 flag) { mOrderFlags |= flag; }
    
    void chkAngry() {}
    bool chkFlag(u16 flag) { return (mFlags & flag) == flag; }
    void clrFlag(u16 flag) { mFlags &= ~flag; }
    s8 getBackboneJntNum() { return m_jnt.getBackboneJntNum(); }
    s8 getHeadJntNum() { return m_jnt.getHeadJntNum(); }
    s16 getBackbone_x() { return m_jnt.getBackbone_x(); }
    s16 getBackbone_y() { return m_jnt.getBackbone_y(); }
    s16 getHead_x() { return m_jnt.getHead_x(); }
    s16 getHead_y() { return m_jnt.getHead_y(); }
    void getVisitMode() {}

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
    void setEyePos(cXyz i_eyePos) { mEyePos = i_eyePos; }
    void setFlag(u16 flag) { mFlags |= flag; }

    BOOL initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm(s8);
    void setAnmStatus();
    bool chkAttentionLocal();
    void chkAttention();
    void eventOrder();
    void checkOrder();
    u16 next_msgStatus(u32*);
    u32 getMsg();
    void setCollision();
    void msgAnm(u8);
    void talkInit();
    void msgPushButton();
    u16 talk();
    BOOL checkDemoStart();
    s32 getNowEventAction();
    BOOL init();
    u8 getType();
    u8 getPath();
    u8 nextVisitMode();
    void visitInit(u8);
    void visitProc();
    void runawayInit();
    void walkPath(u8);
    void runLink();
    void aroundLink();
    void remove_Um2();
    void demoInitCom();
    bool demoProc();
    void setAttention(bool);
    u8 getLookBackMode();
    void lookBack();
    bool wait01();
    bool talk01();
    bool talk02();
    u8 visitTalkInit();
    void visitSetEvent();
    bool visit01();
    bool climb01();
    bool drop01();
    bool runaway();
    bool jump();
    bool jitanda01();
    bool jitanda02();
    bool demo01();
    bool demo02();
    bool demo03();
    BOOL wait_action(void*);
    BOOL seek_action(void*);
    BOOL hind_action(void*);
    BOOL visit_action(void*);
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL CreateHeap();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ mDoExt_McaMorf* mpMorf;
    /* 0x29C */ u32 mShadowId;
    /* 0x2A0 */ J3DAnmTexPattern* m_head_tex_pattern;
    /* 0x2A4 */ mDoExt_btpAnm mBtpAnm;
    /* 0x2B8 */ u8 mBlinkFrame;
    /* 0x2B9 */ u8 field_0x2B9[0x2BA - 0x2B9];
    /* 0x2BA */ s16 mBlinkTimer;
    /* 0x2BC */ dBgS_ObjAcch mObjAcch;
    /* 0x480 */ dBgS_AcchCir mAcchCir;
    /* 0x4C0 */ dCcD_Stts mStts;
    /* 0x4FC */ dCcD_Cyl mCyl;
    /* 0x62C */ dNpc_JntCtrl_c m_jnt;
    /* 0x660 */ cXyz mEyePos;
    /* 0x66C */ cXyz mAttnBasePos;
    /* 0x678 */ s16 mMaxHeadTurnVelocity;
    /* 0x67A */ s8 mAnmEnded;
    /* 0x67B */ u8 mAttnSetCount;
    /* 0x67C */ f32 mAnmTimer;
    /* 0x680 */ u32 mCurrMsgNo;
    /* 0x684 */ u16 mFlags;
    /* 0x686 */ u8 mAttentionTimer;
    /* 0x687 */ u8 mMsgSelectNum;
    /* 0x688 */ dNpc_PathRun_c field_0x688;
    /* 0x690 */ dNpc_PathRun_c field_0x690;
    /* 0x698 */ dNpc_PathRun_c field_0x698;
    /* 0x6A0 */ u8 mVisitMode;
    /* 0x6A1 */ u8 mWaitTimer;
    /* 0x6A2 */ u8 mRunAroundLinkTimer;
    /* 0x6A3 */ u8 mTimerToReachLink;
    /* 0x6A4 */ u16 field_0x6A4;
    /* 0x6A6 */ u8 field_0x6A6[0x6A8 - 0x6A6];
    /* 0x6A8 */ ActionFunc mCurrActionFunc;
    /* 0x6B4 */ s8 mTexPatternIdx;
    /* 0x6B5 */ s8 mAnmIdx;
    /* 0x6B6 */ u8 field_0x6B6[0x6B8 - 0x6B6];
    /* 0x6B8 */ int mStaffIdx;
    /* 0x6BC */ s32 mEventAction;
    /* 0x6C0 */ u8 mOrderFlags;
    /* 0x6C1 */ s8 mState;
    /* 0x6C2 */ s8 mPrevState;
    /* 0x6C3 */ s8 mType;
    /* 0x6C4 */ s8 mActionStatus;
    /* 0x6C5 */ s8 mTalkState;
    /* 0x6C6 */ u8 mMsgAnmIdx;
    /* 0x6C7 */ u8 field_0x6C7[0x6C8 - 0x6C7];
    /* 0x6C8 */ u32 mMtrlSndId;
    /* 0x6CC */ s8 mReverb;
    /* 0x6CD */ u8 field_0x6CD[0x6D0 - 0x6CD];
    /* 0x6D0 */ cXyz field_0x6D0;
    /* 0x6DC */ cXyz field_0x6DC;
    /* 0x6E8 */ s16 field_0x6E8;
    /* 0x6EA */ s16 mEventIdx;
    /* 0x6EC */ char* mpName;
    /* 0x6F0 */ s16 field_0x6F0;
    /* 0x6F2 */ u8 field_0x6F2[0x6F4 - 0x6F2];
    /* 0x6F4 */ u32 mMsgNo;
    /* 0x6F8 */ daNpc_Mk_Static_c mMkStatic;
};  // Size: 0x708

#endif /* D_A_NPC_MK_H */
