#ifndef D_A_NPC_TC_H
#define D_A_NPC_TC_H

#include "f_op/f_op_actor.h"
#include "d/d_npc.h"

namespace daObjSmplbg { class Act_c; };

class daNpc_Tc_c : public fopNpc_npc_c {
public:

    enum Status {
        STATUS_WAIT = 1,
        STATUS_SIT = 2,
        STATUS_TALK = 3,
        STATUS_JUMP = 4,
        STATUS_WALK_TO_JAIL = 5,
        STATUS_TALK_NEAR_JAIL = 6,
        STATUS_WAIT_NEAR_JAIL = 7,
        STATUS_WALK_TO_STOOL = 8,
        STATUS_SIT_TO_STOOL = 9,
        STATUS_DEMO_JUMP = 10,
        STATUS_DEMO_RESCUE = 11,
        STATUS_DEMO_TALK = 12,
        STATUS_PAY_RUPEE = 13,
        STATUS_DEMO_PAY_RUPEE = 14,
        STATUS_GET_RUPEE = 15,
        STATUS_DEMO_GET_RUPEE = 16,
        STATUS_MONUMENT_COMPLETE = 17,
        STATUS_DEMO_MONUMENT_COMPLETE = 18,
    };

    enum ActionStatus {
        ACTION_STARTING = 0,
        ACTION_ONGOING  = 1,
        ACTION_ENDING   = -1,
    };

    enum Type {
        TYPE_NORMAL2 = 0,
        TYPE_RED = 1,
        TYPE_WHITE = 2,
        TYPE_BLUE = 3,
        TYPE_NORMAL = 4,
    };

    enum BckIdx {
        BCK_IDX_WAIT01 = 0,
        BCK_IDX_WAIT03 = 1,
        BCK_IDX_WAIT02 = 2,
        BCK_IDX_TALK01 = 3,
        BCK_IDX_WALK01 = 4,
        BCK_IDX_JAMP_A = 5,
        BCK_IDX_JAMP_B = 6,
        BCK_IDX_JAMP_C = 7,
        BCK_IDX_GUARD = 8,
        BCK_IDX_JTBT = 9,
        BCK_IDX_HAPPY = 10,
        BCK_IDX_DANCE01 = 11,
        BCK_IDX_DANCE02 = 12,
        BCK_IDX_GET = 13,
        BCK_IDX_MAWASU = 14,
        BCK_IDX_WAIT04 = 15,
        BCK_IDX_TALK02 = 16,
    };

    enum AnmPrmIdx {
        ANM_PRM_IDX_NONE = 0,
        ANM_PRM_IDX_WAIT01 = 1,
        ANM_PRM_IDX_WAIT03 = 2,
        ANM_PRM_IDX_WAIT02 = 3,
        ANM_PRM_IDX_TALK01 = 4,
        ANM_PRM_IDX_WALK01 = 5,
        ANM_PRM_IDX_JAMP_A = 6,
        ANM_PRM_IDX_JAMP_B = 7,
        ANM_PRM_IDX_JAMP_C1 = 8,
        ANM_PRM_IDX_JAMP_C2 = 9,
        ANM_PRM_IDX_GUARD = 10,
        ANM_PRM_IDX_JTBT = 11,
        ANM_PRM_IDX_HAPPY = 12,
        ANM_PRM_IDX_DANCE01 = 13,
        ANM_PRM_IDX_DANCE02 = 14,
        ANM_PRM_IDX_GET = 15,
        ANM_PRM_IDX_HAPPY2 = 16, // ANM_PRM_IDX_HAPPY gets set to this
        ANM_PRM_IDX_DANCE01_TO_TALK01 = 17,
        ANM_PRM_IDX_DANCE02_TO_WAIT03 = 18,
        ANM_PRM_IDX_MAWASU = 19,
        ANM_PRM_IDX_WAIT04 = 20,
        ANM_PRM_IDX_TALK02 = 21,
        ANM_PRM_IDX_TALK01_WAIT01 = 22,  // loops 3x then -> WAIT01
        ANM_PRM_IDX_TALK01_TALK02 = 23,  // loops 5x then -> TALK02
    };

    typedef int (daNpc_Tc_c::*ActionFunc)(void*);
    daNpc_Tc_c();
    
    cXyz& getAttentionBasePos() { return mAttPos; }
    cXyz& getEyePos() { return mEyePos; }

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
    
    fopAc_ac_c* _searchTower(fopAc_ac_c*);
    BOOL initTexPatternAnm(bool);
    void playTexPatternAnm();
    void smoke_set(f32, f32, f32, f32, f32);
    void setAnm();
    void setTexAnm();
    bool chkAttention(cXyz, s16);
    void eventOrder();
    void checkOrder();
    bool existTcMonument();
    void anmAtr(u16);
    void stopTower();
    void startTower();
    u16 next_msgStatusBlue(u32*);
    u16 next_msgStatusNormal(u32*);
    u16 next_msgStatus(u32*);
    u32 setFirstMsg(bool*, u32, u32);
    u32 getMsgNormal();
    u32 getMsgBlue();
    u32 getMsg();
    void getArg();
    void createInit();
    static void* searchStoolPos(void*, void*);
    void setAttention();
    void calcMove();
    void lookBack();
    void statusWait();
    void statusSit();
    void statusJump();
    void statusWalkToJail();
    void statusTalkNearJail();
    void statusWaitNearJail();
    void statusWalkToStool();
    void statusSitToStool();
    void statusTalk();
    void statusPayRupee();
    void statusDemoPayRupee();
    void statusGetRupee();
    void statusDemoGetRupee();
    void statusMonumentComplete();
    void statusDemoMonumentComplete();
    void statusDemoJump();
    void statusDemoRescue();
    void statusDemoTalk();
    BOOL help_action(void*);
    BOOL wait_action(void*);
    void calc_sitpos();
    void set_mtx();
    BOOL _draw();
    void setTower();
    BOOL _execute();
    BOOL _delete();
    bool isCreate();
    cPhs_State _create();
    BOOL _createHeap();
    u16 next_msgStatusNormal2(u32*);
    u32 getMsgNormal2();
#if VERSION != VERSION_DEMO
    u32 setRupeeSizeMsg();
#endif
    bool existUnknownCollectMap();
    int analysisCollectMap();
    bool existKnownCollectMap();
    u16 next_msgStatusWhite(u32*);
    u32 getMsgWhite();
    u16 next_msgStatusRed(u32*);
    u32 setFinishMsg();
    u32 getMsgRed();
    bool checkMonumentFee(u16, u16);
    bool checkAllMonumentFee();
#if VERSION == VERSION_DEMO
    bool checkOneMonumentGet();
#endif
    int checkAllMonumentPay();
    bool checkMonumentPay(u16, u16);
    void cutProc();
    void cutSitToJumpStart(int);
    void cutSitToJumpProc(int);
    void cutPresentStart(int);
    void cutPresentProc(int);
    void cutSetAnmStart(int);
    void cutSetAnmProc(int);
    void cutBackJumpStart(int);
    void cutBackJumpProc(int);
    void cutEffectStart(int);
    void cutEffectProc(int);
    void cutDoorOpenStart(int);
    void cutDoorOpenProc(int);
    void cutDoorCloseStart(int);
    void cutDoorCloseProc(int);
    void cutDoorClose2Start(int);
    void cutDoorClose2Proc(int);
    void cutPayStart(int);
    void cutPayProc(int);

public:
    /* 0x6C4 */ u8 field_0x6C4[0x6C8 - 0x6C4];
    /* 0x6C8 */ BOOL field_0x6C8;
    /* 0x6CC */ u8 mJtbtTimer;
    /* 0x6CD */ u8 mTalk01Wait01Timer;
    /* 0x6CE */ u8 mTalk01Talk02Timer;
    /* 0x6CF */ s8 mStatus;
    /* 0x6D0 */ ActionFunc mCurrActionFunc;
    /* 0x6DC */ s8 mActionStatus;
    /* 0x6DD */ u8 field_0x6DD[0x6E0 - 0x6DD];
    /* 0x6E0 */ cXyz mSmokePos;
    /* 0x6EC */ csXyz mSmokeAngle;
    /* 0x6F2 */ u8 field_0x6F2[0x6F4 - 0x6F2];
    /* 0x6F4 */ dPa_smokeEcallBack mSmokeCallBack;
    /* 0x714 */ dPa_followEcallBack field_0x714;
    /* 0x728 */ dPa_followEcallBack field_0x728;
    /* 0x73C */ request_of_phase_process_class mPhs;
    /* 0x744 */ u32 mShadowId;
#if VERSION == VERSION_DEMO
    /* 0x748 */ J3DModel* mpModel;
#endif
    /* 0x748 */ J3DAnmTexPattern* m_head_tex_pattern;
    /* 0x74C */ mDoExt_btpAnm mBtpAnm;
    /* 0x760 */ u8 mBlinkFrame;
    /* 0x761 */ u8 field_0x761[0x762 - 0x761];
    /* 0x762 */ s16 mBlinkTimer;
    /* 0x764 */ cXyz mEyePos;
    /* 0x770 */ cXyz mAttPos;
    /* 0x77C */ u8 mAttnSetCount;
    /* 0x77D */ u8 field_0x77D[0x780 - 0x77D];
    /* 0x780 */ cXyz mStoolLookPos;
    /* 0x78C */ s16 mMaxHeadTurnVelocity;
    /* 0x78E */ u8 field_0x78E[0x790 - 0x78E];
    /* 0x790 */ csXyz field_0x790;
    /* 0x796 */ u8 field_0x796[0x798 - 0x796];
    /* 0x798 */ s8 field_0x798;
    /* 0x799 */ u8 field_0x799[0x79C - 0x799];
    /* 0x79C */ f32 mTargetSpeed;
    /* 0x7A0 */ cXyz mStoolPos;
    /* 0x7AC */ cXyz mSitPos;
    /* 0x7B8 */ cXyz mWalkToStoolPos;
    /* 0x7C4 */ cXyz mDeltaPos;
    /* 0x7D0 */ u8 field_0x7D0[0x7DC - 0x7D0];
    /* 0x7DC */ cXyz mParticlePos;
    /* 0x7E8 */ bool mHasAttention;
    /* 0x7E9 */ bool mTalkingNearJail;
    /* 0x7EA */ u8 field_0x7EA[0x7F1 - 0x7EA];
    /* 0x7F1 */ bool mHasTalkedNearJail;
    /* 0x7F2 */ bool mHasEnteredSitRadius;
    /* 0x7F3 */ s8 mJumpLandingTimer;
    /* 0x7F4 */ u8 field_0x7F4[0x7F6 - 0x7F4];
    /* 0x7F6 */ s8 mTexPatternNum;
    /* 0x7F7 */ s8 mTexPatternNumIdx;
    /* 0x7F8 */ s8 mBckIdx;
    /* 0x7F9 */ s8 mAnmPrmIdx;
    /* 0x7FA */ s8 mOldAnmPrmIdx;
    /* 0x7FB */ s8 mEventIdx;
    /* 0x7FC */ u8 mType;
    /* 0x7FD */ u8 field_0x7FD[0x804 - 0x7FD];
    /* 0x804 */ daObjSmplbg::Act_c* m_tower_actor;
    /* 0x808 */ bool field_0x808;
    /* 0x809 */ bool field_0x809;
    /* 0x80A */ u8 field_0x80A[0x80B - 0x80A];
    /* 0x80B */ bool field_0x80B;
    /* 0x80C */ u8 field_0x80C;
    /* 0x80D */ bool field_0x80D;
    /* 0x80E */ bool field_0x80E;
    /* 0x80F */ bool field_0x80F;
    /* 0x810 */ bool field_0x810;
    /* 0x811 */ bool field_0x811;
    /* 0x812 */ bool field_0x812;
    /* 0x813 */ bool field_0x813;
    /* 0x814 */ bool field_0x814;
    /* 0x815 */ u8 field_0x815[0x81C - 0x815];
};  // Size: 0x81C
#endif /* D_A_NPC_TC_H */
