#ifndef D_A_NPC_MN_H
#define D_A_NPC_MN_H

#include "JSystem/J3DGraphAnimator/J3DAnimation.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_cc_d.h"
#include "d/d_npc.h"
#include "m_Do/m_Do_ext.h"

struct sMnAnmDat {
    /* 0x00 */ u8 mBckIdx;
    /* 0x01 */ u8 mMorf;
    /* 0x02 */ s8 mLoopCount;
}; // Size: 0x03

struct NpcDatStruct {
    /* 0x00 */ s16 mMax_head_x;
    /* 0x02 */ s16 mMax_head_y;
    /* 0x04 */ s16 mMax_backbone_x;
    /* 0x06 */ s16 mMax_backbone_y;
    /* 0x08 */ s16 mMin_head_x;
    /* 0x0A */ s16 mMin_head_y;
    /* 0x0C */ s16 mMin_backbone_x;
    /* 0x0E */ s16 mMin_backbone_y;
    /* 0x10 */ s16 mMax_turn_step;
    /* 0x12 */ s16 field_0x12;
    /* 0x14 */ f32 mPlayerEyeOfsY;
    /* 0x18 */ f32 mAttnPosOfsY;
    /* 0x1C */ f32 mEyePosOfsY;
    /* 0x20 */ f32 mAttnDist;
    /* 0x24 */ f32 mNearDist;
    /* 0x28 */ s16 mAttnAngle;
    /* 0x2A */ s16 mLookAtMaxVel;
    /* 0x2C */ s16 mWalkLookAtMaxVel;
    /* 0x2E */ s16 field_0x2E;
    /* 0x30 */ f32 mCylRadius;
    /* 0x34 */ f32 mWalkAnmRate;
    /* 0x38 */ f32 mWalkSpeed;
    /* 0x3C */ s16 field_0x3C;
    /* 0x3E */ s16 field_0x3E;
    /* 0x40 */ s16 mWaitTimerMin;
    /* 0x42 */ s16 mWaitTimerMax;
    /* 0x44 */ s16 mTurnWaitMin;
    /* 0x46 */ s16 mTurnWaitMax;
    /* 0x48 */ s16 mLookResetTimer;
    /* 0x4A */ s8 mbAllowBodyTurn;
    /* 0x4B */ s8 mbLookOnly;
}; // Size: 0x4C

class daNpcMn_c : public fopNpc_npc_c {
public:
    enum Prm_e {
        PRM_SWITCH_W = 0x8,
        PRM_SWITCH_S = 0x8,
        PRM_SWITCH2_W = 0x8,
        PRM_SWITCH2_S = 0x10,
        PRM_RAIL_W = 0x8,
        PRM_RAIL_S = 0x18,
    };

    enum MoveProcIdx {
        MOVE_PROC_WAIT = 0,
        MOVE_PROC_TALK = 1,
        MOVE_PROC_WALK = 2,
        MOVE_PROC_TURN = 3,
        MOVE_PROC_TALK3 = 4,
    };

    enum LookMode {
        LOOK_MODE_NONE = 0,
        LOOK_MODE_ATTN = 1,
        LOOK_MODE_TURN = 2,
    };

    enum Talk3State {
        TALK3_INIT = 0,
        TALK3_ORDER = 1,
        TALK3_TALK = 2,
    };

    enum BckIdx {
        BCK_WAIT01 = 0,
        BCK_WAIT02 = 1,
        BCK_TALK01 = 2,
        BCK_TALK02 = 3,
        BCK_WALK = 4,
        BCK_BIKKURI = 5,
        BCK_JUMP01 = 6,
        BCK_JUMP02 = 7,
        BCK_NULL = 0xFF,
    };

    u8 getNpcNo() { return mNpcNo; }
    request_of_phase_process_class* getPhaseP() { return &mPhs; }
    u8 getPosFlag() {
        return mPosFlag;
    }
    void setResFlag(u8 flag) {
        mResFlag = flag;
    }

    daNpcMn_c();
    cPhs_State _create();
    BOOL createHeap();
    cPhs_State createInit();
    bool _delete();
    bool _draw();
    bool _execute();
    u8 executeCommon();
    void executeSetMode(u8);
    int executeWaitInit();
    void executeWait();
    int executeTalkInit();
    void executeTalk();
    int executeTalk3Init();
    void executeTalk3();
    int executeWalkInit();
    void executeWalk();
    int executeTurnInit();
    void executeTurn();
    void checkOrder();
    void eventOrder();
    void eventMove();
    void privateCut();
    void eventMesSetInit(int);
    bool eventMesSet();
    void eventGetItemInit();
    void eventWaitInit(int);
    bool eventWait(int);
    void eventSwOnInit(int);
    bool eventSwOn();
    void eventHatchInit();
    bool eventHatch();
    void eventBikkuriInit(int);
    bool eventBikkuri();
    void eventTurnInit();
    bool eventTurn(int);
    void eventWalkInit();
    bool eventWalk();
    void eventLookInit();
    bool eventLook();
    void eventJumpInit(int);
    bool eventJump();
    u16 talk2(int);
    u16 talk3(int);
    virtual u16 next_msgStatus(u32*);
    virtual u32 getMsg();
    u32 getMsg3();
    void chkMsg();
    void setMessage(u32);
    void setAnmFromMsgTag();
    bool getPrmNpcNo();
    u8 getPrmRailID();
    u8 getPrmSwitchBit();
    u8 getPrmSwitchBit2();
    void setMtx();
    void chkAttention();
    void lookBack();
    BOOL initTexPatternAnm(bool);
    void playTexPatternAnm();
    void playAnm();
    void setAnm(u8, int, f32);
    bool setAnmTbl(sMnAnmDat*);
    s16 XyCheckCB(int);
    int getRand(int);
    void setCollision(dCcD_Cyl*, cXyz, f32, f32);
    BOOL chkEndEvent();
    u8 chkPosNo();
    u8 getPosNo();
    BOOL isChangePos(u8);

    static const char m_arcname[];

public:
    /* 0x6C4 */ u8 field_0x6C4[0x60];
    /* 0x724 */ request_of_phase_process_class mPhs;
    /* 0x72C */ request_of_phase_process_class mPhsMethod;
    /* 0x734 */ J3DModel* mpModel;
    /* 0x738 */ J3DAnmTexPattern* m_head_tex_pattern;
    /* 0x73C */ mDoExt_btpAnm mBtpAnm;
    /* 0x750 */ u32 mShadowId;
    /* 0x754 */ dNpc_PathRun_c mPathRun;
    /* 0x75C */ cXyz field_0x75C;
    /* 0x768 */ cXyz mLookAtPos;
    /* 0x774 */ sMnAnmDat* mpAnmDat;
    /* 0x778 */ u32* mpMsgNo;
    /* 0x77C */ f32 mTargetSpeedF;
    /* 0x780 */ f32 mAnmMorfOverride;
    /* 0x784 */ f32 mAttnDist;
    /* 0x788 */ f32 mJumpSpeedY;
    /* 0x78C */ u32 mItemNo;
    /* 0x790 */ u32 mFigureArg;
    /* 0x794 */ bool mHeadOnlyFollow;
    /* 0x795 */ u8 field_0x795;
    /* 0x796 */ s16 mHatchEventIdx;
    /* 0x798 */ s16 mWaitTimer;
    /* 0x79A */ s16 mLookResetTimer;
    /* 0x79C */ s16 mEventTimer;
    /* 0x79E */ s16 mAttnAngle;
    /* 0x7A0 */ s16 mHomeYRot;
    /* 0x7A2 */ u16 mLastMsgStatus;
    /* 0x7A4 */ u16 mEtcFlag;
    /* 0x7A6 */ s16 field_0x7A6;
    /* 0x7A8 */ s16 mBtpTimer;
    /* 0x7AA */ s16 mLookAtMaxVel;
    /* 0x7AC */ s16 mTurnVel;
    /* 0x7AE */ s16 mTargetYRot;
    /* 0x7B0 */ u8 mTalkOrder;
    /* 0x7B1 */ u8 mbPlayerAttention;
    /* 0x7B2 */ u8 mEvtOrderType;
    /* 0x7B3 */ u8 mBtpFrame;
    /* 0x7B4 */ u8 mMoveState;
    /* 0x7B5 */ u8 mResFlag;
    /* 0x7B6 */ u8 mNpcNo;
    /* 0x7B7 */ u8 mSwitchFlag;
    /* 0x7B8 */ u8 mBckIdx;
    /* 0x7B9 */ u8 mAnmFlag;
    /* 0x7BA */ s8 mAnmLoopCnt;
    /* 0x7BB */ s8 mActIdx;
    /* 0x7BC */ u8 field_0x7BC;
    /* 0x7BD */ s8 mLookMode;
    /* 0x7BE */ u8 mbAllowBodyTurn;
    /* 0x7BF */ u8 mbLookOnly;
    /* 0x7C0 */ u8 mbNearPlayer;
    /* 0x7C1 */ u8 mPosFlag;
    /* 0x7C2 */ s8 mShoulderRJoint;
    /* 0x7C3 */ u8 mTalk3State;
    /* 0x7C4 */ u8 mbLookFigure;
    /* 0x7C5 */ u8 mFigureMsgIdx;
    /* 0x7C6 */ u8 field_0x7C6[0x7C8 - 0x7C6];
}; // Size: 0x7C8

#endif /* D_A_NPC_MN_H */
