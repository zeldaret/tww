#ifndef D_A_NPC_HO_H
#define D_A_NPC_HO_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "d/d_npc.h"

class daNpc_Ho_c : public fopAc_ac_c {
public:

    enum HoFlags {
        HO_FLAG_00000001 = 0x00000001,
        HO_FLAG_00000002 = 0x00000002,
        HO_FLAG_00000004 = 0x00000004,
        HO_FLAG_00000008 = 0x00000008,
        HO_FLAG_00000010 = 0x00000010,
        HO_FLAG_00000020 = 0x00000020,
        HO_FLAG_00000040 = 0x00000040,
        HO_FLAG_00000080 = 0x00000080,
        HO_FLAG_00000100 = 0x00000100,
        HO_FLAG_00000200 = 0x00000200,
        HO_FLAG_00000400 = 0x00000400,
        HO_FLAG_00000800 = 0x00000800,
    };

    enum HoStates {
        HO_STATE_WAIT_01 = 0,
        HO_STATE_TALK_01 = 1,
        HO_STATE_TALK_02 = 2,
        HO_STATE_TALK_03 = 3,
        HO_STATE_GIVE_01 = 5,
        HO_STATE_GIVE_02 = 6,
        HO_STATE_PREACH = 7

    };

    enum ActionStatus {
        ACTION_STARTING = 0,
        ACTION_ONGOING = 1,
        ACTION_ENDING = -1,
    };

    enum TalkStates {
        TALK_INIT = 0,
        TALK_MSG_CREATE = 1,
        TALK_ACTIVE = 2,
        TALK_FINISHED = -1
    };
    
    typedef int (daNpc_Ho_c::*ActionFunc)(void*);


    bool ChkOrder(u8 temp) { return mOrderFlags & temp; }
    void ClrOrder() { mOrderFlags = 0; }
    void SetOrder(u8 temp) { mOrderFlags |= temp; }
    bool chkFlag(u16 flag) { return (mFlags & flag) == flag; }
    void clrFlag(u16 flag) { mFlags &= ~flag; }

    s8 getBackboneJntNum() { return m_jnt.getBackboneJntNum(); }
    s16 getBackbone_y() { return m_jnt.getBackbone_y(); }
    s8 getHeadJntNum() { return m_jnt.getHeadJntNum(); }
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
    void setEyePos(cXyz i_eyePos) { mEyePos = i_eyePos; }
    void setFlag(u16 flag) { mFlags |= flag; }

    s16 XyCheckCB(int);
    void receivePendant(int);
    BOOL initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm(s8);
    void setAnmStatus();
    bool chkAttentionLocal();
    void chkAttention();
    void eventOrder();
    void checkOrder();
    u32 next_msg_sub0(u32);
    u16 next_msgStatus(u32*);
    u32 getMsg();
    void setCollision();
    void msgPushButton();
    void msgAnm(u8);
    void talkInit();
    u16 talk();
    BOOL init();
    void setAttention(bool);
    void lookBack();
    bool wait01();
    bool talk01();
    bool talk02();
    bool talk03();
    bool give01();
    bool give02();
    bool preach();
    BOOL wait_action(void*);
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL CreateHeap();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ mDoExt_McaMorf* mpMorf;
    /* 0x29C */ J3DModel* mpJoyPendentModel;
    /* 0x2A0 */ u32 mShadowId;
    /* 0x2A4 */ J3DAnmTexPattern* m_head_tex_pattern;
    /* 0x2A8 */ mDoExt_btpAnm mBtpAnm;
    /* 0x2BC */ u8 mBlinkFrame;
    /* 0x2BD */ u8 field_0x2BD[0x2BE - 0x2BD];
    /* 0x2BE */ s16 mBlinkTimer;
    /* 0x2C0 */ dBgS_ObjAcch mObjAcch;
    /* 0x484 */ dBgS_AcchCir mAcchCir;
    /* 0x4C4 */ dCcD_Stts mStts;
    /* 0x500 */ dCcD_Cyl mCyl;
    /* 0x630 */ dNpc_JntCtrl_c m_jnt;
    /* 0x664 */ cXyz mEyePos;
    /* 0x670 */ cXyz mAttnBasePos;
    /* 0x67C */ s16 mMaxHeadTurnVelocity;
    /* 0x67E */ s8 mAnmEnded;
    /* 0x67F */ u8 mAttnSetCount;
    /* 0x680 */ f32 mAnmTimer;
    /* 0x684 */ u32 mCurrMsgNo;
    /* 0x688 */ u16 mFlags;
    /* 0x68A */ u8 field_0x68A;
    /* 0x68B */ u8 mMsgSelectNum;
    /* 0x68C */ u8 mMsgAnmIdx;
    /* 0x68D */ u8 field_0x68D;
    /* 0x68E */ u8 field_0x68E;
    /* 0x68F */ u8 field_0x68F[0x690 - 0x68F];
    /* 0x690 */ int mNextMessageId;
    /* 0x694 */ f32 mCylinderCollisionRadius;
    /* 0x698 */ ActionFunc mCurrActionFunc;
    /* 0x6A4 */ s8 mTexPatternIdx;
    /* 0x6A5 */ s8 mCurrAnmIdx;
    /* 0x6A6 */ s8 mOrderFlags;
    /* 0x6A7 */ s8 mState;
    /* 0x6A8 */ s8 field_0x6A8;
    /* 0x6A9 */ u8 field_0x6A9;
    /* 0x6AA */ s8 mActionStatus;
    /* 0x6AB */ s8 mTalkState;
    /* 0x6AC */ int mCurrentFloorSoundId;
    /* 0x6B0 */ s8 mReverb;
    /* 0x6B1 */ u8 field_0x6B1[0x6B4 - 0x6B1];
};  // Size: 0x6B4

#endif /* D_A_NPC_HO_H */
