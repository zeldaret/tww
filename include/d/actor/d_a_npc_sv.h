#ifndef D_A_NPC_SV_H
#define D_A_NPC_SV_H

#include "d/d_cc_d.h"
#include "d/d_npc.h"

struct sSvAnmDat {
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
    /* 0x14 */ f32 mModelOfsX;
    /* 0x18 */ f32 mModelOfsY;
    /* 0x1C */ f32 mModelOfsZ;
    /* 0x20 */ f32 mPlayerEyeOfsY;
    /* 0x24 */ f32 mAttnPosOfsY;
    /* 0x28 */ f32 mEyePosOfsY;
    /* 0x2C */ f32 mAttnDist;
    /* 0x30 */ f32 mNearDist;
    /* 0x34 */ s16 mAttnAngle;
    /* 0x36 */ s16 mLookAtMaxVel;
    /* 0x38 */ f32 mCylRadius;
    /* 0x3C */ f32 mCylHeight;
    /* 0x40 */ s16 mLookResetTimer;
    /* 0x42 */ u8 mbAllowBodyTurn;
    /* 0x43 */ u8 mbLookOnly;
}; // size 0x44;

class daNpcSv_c : public fopNpc_npc_c {
public:
    enum MoveProcIdx {
        MOVE_PROC_WAIT = 0,
        MOVE_PROC_TALK = 1,
    };

    enum LookMode {
        LOOK_MODE_NONE = 0,
        LOOK_MODE_ATTN = 1,
        LOOK_MODE_TURN = 2,
    };

    enum CutAct {
        CUT_MES_SET = 0,
        CUT_GET_ITEM = 1,
        CUT_SET_ANGLE = 2,
        CUT_ATTENTION = 3,
        CUT_TURN_OK = 4,
    };

    u8 getMsgPtn() { return mMsgPtn; }
    u8 getNpcNo() {
        return mNpcNo;
    }
    request_of_phase_process_class* getPhaseP() {
        return &mPhase;
    }
    void setResFlag(u8 flag) {
        mResFlag = flag;
    }

    daNpcSv_c();
    cPhs_State _create();
    BOOL createHeap();
    cPhs_State createInit();
    bool _delete();
    bool _draw();
    bool _execute();
    BOOL executeCommon();
    void executeSetMode(u8);
    BOOL executeWaitInit();
    void executeWait();
    BOOL executeTalkInit();
    void executeTalk();
    void checkOrder();
    void eventOrder();
    void eventMove();
    void privateCut();
    void eventMesSetInit(int);
    bool eventMesSet();
    void eventGetItemInit(int);
    bool eventGetItem();
    void eventSetAngleInit();
    void eventAttentionInit(int);
    bool eventAttention();
    void eventTurnOkInit();
    u16 talk2(int, fopAc_ac_c*);
    virtual u16 next_msgStatus(u32*);
    virtual u32 getMsg();
    void setMessage(u32);
    void setAnmFromMsgTag();
    u8 getPrmNpcNo();
    void setMtx();
    void chkAttention();
    void lookBack();
    void playAnm();
    void setAnm(u8, int, f32);
    bool setAnmTbl(sSvAnmDat*);
    void setCollision(dCcD_Cyl*, cXyz, f32, f32);
    u8 getTalkNo();
    BOOL isTalkOK();

    static const char m_arcname[];

private:
    /* 0x6C4 */ request_of_phase_process_class mPhase;
    /* 0x6CC */ request_of_phase_process_class mPhaseCreate;
    /* 0x6D4 */ u32 mShadowId;
    /* 0x6D8 */ u32 field_0x6D8;
    /* 0x6DC */ u8 padding_0x6DC[0x6EC - 0x6DC];
    /* 0x6EC */ cXyz mLookAtPos;
    /* 0x6F8 */ u8 padding_0x6F8[0x704 - 0x6F8];
    /* 0x704 */ sSvAnmDat* mpAnmDat;
    /* 0x708 */ u32* mpMsgNo;
    /* 0x70C */ f32 mAnmMorfOverride;
    /* 0x710 */ f32 mAttnDist;
    /* 0x714 */ u32 mItemNo;
    /* 0x718 */ s32 mIkadaFrame;
    /* 0x71C */ bool mHeadOnlyFollow;
    /* 0x71D */ u8 field_0x71D;
    /* 0x71E */ s16 mEventIdx[3];
    /* 0x724 */ s16 mLookResetTimer;
    /* 0x726 */ s16 mAttnAngle;
    /* 0x728 */ s16 mHomeYRot;
    /* 0x72A */ s16 mAttnTimer;
    /* 0x72C */ s16 mTargetAngleY;
    /* 0x72E */ s16 mLookAtMaxVel;
    /* 0x730 */ s16 mTurnVel;
    /* 0x732 */ s16 mLookAngleY;
    /* 0x734 */ u16 mTalkFlags;
    /* 0x736 */ u8 mTalkOrder;
    /* 0x737 */ u8 mbPlayerAttention;
    /* 0x738 */ u8 mEvtOrderType;
    /* 0x739 */ u8 mMoveState;
    /* 0x73A */ u8 mResFlag;
    /* 0x73B */ u8 mNpcNo;
    /* 0x73C */ u8 mCutFlags;
    /* 0x73D */ u8 mBckIdx;
    /* 0x73E */ u8 mAnmFlag;
    /* 0x73F */ s8 mAnmLoopCnt;
    /* 0x740 */ s8 mActIdx;
    /* 0x741 */ s8 mLookMode;
    /* 0x742 */ u8 field_0x742;
    /* 0x743 */ u8 mbAllowBodyTurn;
    /* 0x744 */ u8 mbLookOnly;
    /* 0x745 */ bool mbNearPlayer;
    /* 0x746 */ u8 mTalkNo;
    /* 0x747 */ u8 mMsgPtn;
    /* 0x748 */ u8 mKyoroFlag;
    /* 0x749 */ u8 mbStopMawasi;
    /* 0x74A */ bool mbWasNearPlayer;
    /* 0x74B */ u8 padding_0x74B[0x74C - 0x74B];
}; // Size: 0x74C

#endif /* D_A_NPC_SV_H */
