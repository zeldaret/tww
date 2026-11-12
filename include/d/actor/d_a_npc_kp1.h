#ifndef D_A_NPC_KP1_H
#define D_A_NPC_KP1_H

#include "d/d_npc.h"
#include "m_Do/m_Do_ext.h"

class daNpc_Kp1_c : public fopNpc_npc_c {
public:
    typedef int (daNpc_Kp1_c::*ActionFunc)(void*);

    struct anm_prm_c {
        s8 field_0x0;
        s8 field_0x1;
        f32 field_0x4;
        f32 field_0x8;
        int field_0xC;
    };

    enum Animation {
        /* 0x0 */ ANM_WAIT,
        /* 0x1 */ ANM_HAPPY,
        /* 0x2 */ ANM_HAND,
        /* 0x3 */ ANM_READ,
        /* 0x4 */ ANM_PRAY,
        /* 0x5 */ ANM_THINK,
        /* 0x6 */ ANM_END,
    };

    enum TexPattern {
        /* 0x0 */ TEXPATTERN_MABA,
        /* 0x1 */ TEXPATTERN_MABA2,
        /* 0x2 */ TEXPATTERN_END,
    };

    s8 getHeadJntNum() { return m_head_jnt_num; }
    s8 getBackboneJntNum() { return m_backbone_jnt_num; }
    s16 getHead_x() { return m_jnt.mAngles[0][0]; }
    s16 getHead_y() { return m_jnt.mAngles[0][1]; }
    s16 getBackbone_x() { return m_jnt.mAngles[1][0]; }
    s16 getBackbone_y() { return m_jnt.mAngles[1][1]; }
    cXyz* getAttPos() { return &mAttPos; }
    cXyz* getEyePos() { return &mEyePos; }

    bool createInit();
    void setMtx();
    bool anmResID(int, int*, int*);
    void BtpNum2ResID(int, int*);
    void setAnm_tex(s8);
    bool init_btp(bool, int);
    bool initTexPatternAnm(bool);
    void playTexPatternAnm();
    s32 setAnm_anm(anm_prm_c*);
    void setAnm_NUM(int, int);
    void setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(u8);
    void ctrlAnmAtr();
    void setAnm_ATR(int);
    void anmAtr(u16);
    void setStt(s8);
    u16 next_msgStatus(u32*);
    u32 getMsg();
    void eventOrder();
    void checkOrder();
    void lookBack();
    bool chkAttention();
    void setAttention();
    bool chk_talk();
    bool decideType(int);
    void event_actionInit(int);
    bool event_action();
    void privateCut();
    void endEvent();
    void event_proc();
    bool set_action(ActionFunc, void*);
    BOOL wait01();
    BOOL talk01();
    int wait_action1(void*);
    u8 demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 m_head_jnt_num;
    /* 0x6CD */ s8 m_backbone_jnt_num;
    /* 0x6CE */ s8 m_handL_jnt_num;
    /* 0x6D0 */ J3DModel* mpLetterModel[2];
    /* 0x6D8 */ u8 mItemType;
    /* 0x6DC */ u32 mShadowId;
    /* 0x6E0 */ J3DAnmTexPattern* m_head_tex_pattern;
    /* 0x6E4 */ mDoExt_btpAnm mBtpAnm;
    /* 0x6F8 */ u8 mBtpFrame;
    /* 0x6FA */ s16 mBlinkTimer;
    /* 0x6FC */ ActionFunc mAction;
    /* 0x708 */ dNpc_EventCut_c mEventCut;
    /* 0x774 */ csXyz mHomeAngle;
    /* 0x77C */ cXyz mHomePos;
    /* 0x788 */ cXyz mAttPos;
    /* 0x794 */ cXyz mEyePos;
    /* 0x7A0 */ cXyz mLookPos;
    /* 0x7AC */ f32 mFrame;
    /* 0x7B0 */ u8 m7B0[0x7B8 - 0x7B0];
    /* 0x7B8 */ s16 mTurnSpeed;
    /* 0x7BA */ s16 mTargetAngleY;
    /* 0x7BC */ s8 mAnmEnd;
    /* 0x7BD */ s8 mLoopCount;
    /* 0x7BE */ u8 mPreItemNo;
    /* 0x7BF */ u8 mGotLetter;
    /* 0x7C0 */ u8 mGotHeart;
    /* 0x7C1 */ u8 mTalkedBefore;
    /* 0x7C2 */ u8 mPresentCancel;
    /* 0x7C3 */ u8 mInitDone;
    /* 0x7C4 */ s32 mUpdateEye;
    /* 0x7C8 */ s32 mActionRet;
    /* 0x7CC */ u8 mHasAttention;
    /* 0x7CD */ u8 mTalkReq;
    /* 0x7CE */ bool mHeadOnlyFollow;
    /* 0x7CF */ u8 mDemo;
    /* 0x7D0 */ u8 m7D0;
    /* 0x7D1 */ s8 mActIdx;
    /* 0x7D2 */ s8 mActNo;
    /* 0x7D3 */ u8 mAtr;
    /* 0x7D4 */ u8 mTag;
    /* 0x7D5 */ s8 mTexNum;
    /* 0x7D6 */ s8 mAnmNum;
    /* 0x7D7 */ s8 mOrder;
    /* 0x7D8 */ s8 mStt;
    /* 0x7D9 */ s8 mPrevStt;
    /* 0x7DA */ s8 mLookMode;
    /* 0x7DB */ s8 mType;
    /* 0x7DC */ s8 m7DC;
    /* 0x7DD */ s8 mActionState;
    /* 0x7DE */ s8 mMsgCount;
    /* 0x7DF */ s8 m7DF;
};  // Size: 0x7E0

#endif /* D_A_NPC_KP1_H */
