#ifndef D_A_NPC_KAMOME_H
#define D_A_NPC_KAMOME_H

#include "d/actor/d_a_player_npc.h"
#include "d/d_bg_s_lin_chk.h"
#include "m_Do/m_Do_hostIO.h"

class JORMContext;
class daNpc_kam_c;

class daNpc_kam_c : public daPy_npc_c {
public:
    enum ActionStatus {
        ACTION_STARTING  = 0,
        ACTION_ONGOING_1 = 1,
        ACTION_ONGOING_2 = 2,
        ACTION_ONGOING_3 = 3,
        ACTION_ENDING    = -1,
    };
    
    enum Animation {
        ANM_WAIT1 = 0,
        ANM_WAIT2 = 1,
        ANM_SING = 2,
    };
    
    typedef int (daNpc_kam_c::*ActionFunc)(void*);
    typedef void (daNpc_kam_c::*EventActionInitFunc)(int evtStaffId);
    typedef BOOL (daNpc_kam_c::*EventActionFunc)(int evtStaffId);
    
    void offLineHit() { cLib_offBit(mHitFlags, 0x07UL); }
    void onFrontLineHit() { cLib_onBit(mHitFlags, 0x01UL); }
    u32 isFrontLineHit() { return cLib_checkBit(mHitFlags, 0x01UL); }
    void onLeftLineHit() { cLib_onBit(mHitFlags, 0x02UL); }
    u32 isLeftLineHit() { return cLib_checkBit(mHitFlags, 0x02UL); }
    void onRightLineHit() { cLib_onBit(mHitFlags, 0x04UL); }
    u32 isRightLineHit() { return cLib_checkBit(mHitFlags, 0x04UL); }
    void onWaterHit() { cLib_onBit(mHitFlags, 0x08UL); }
    void offWaterHit() { cLib_offBit(mHitFlags, 0x08UL); }
    u32 isWaterHit() { return cLib_checkBit(mHitFlags, 0x08UL); }
    void onNoBgCheck() { cLib_onBit(mHitFlags, 0x10UL); }
    void offNoBgCheck() { cLib_offBit(mHitFlags, 0x10UL); }
    u32 isNoBgCheck() { return cLib_checkBit(mHitFlags, 0x10UL); }
    
    void onHyoiKamome() { m_hyoi_kamome = true; }
    void offHyoiKamome() { m_hyoi_kamome = false; }
    
    s16 XyCheckCB(int);
    BOOL callDemoStartCheck();
    s16 XyEventCB(int);
    ~daNpc_kam_c();
    void setAttention(bool, int);
    void setBaseMtx();
    BOOL createHeap();
    cPhs_State create();
    BOOL init();
    BOOL setAction(ActionFunc*, ActionFunc, void*);
    void npcAction(void*);
    void setNpcAction(ActionFunc, void*);
    void playerAction(void*);
    void setPlayerAction(ActionFunc, void*);
    BOOL returnLinkCheck();
    BOOL changeAreaCheck();
    BOOL areaOutCheck();
    BOOL getStickAngY(s16*, s16*);
    s16 getAngleX();
    int wallHitCheck();
    BOOL npcTurnCheck(s16*);
    int waitNpcAction(void*);
    BOOL keyProc();
    int waitPlayerAction(void*);
    BOOL damagePlayerAction(void*);
    void eventOrder();
    void checkOrder();
    BOOL checkCommandTalk();
    void returnLinkPlayer();
    BOOL eventProc();
    void eventEnd();
    BOOL actionDefault(int);
    void initialWaitEvent(int);
    BOOL actionWaitEvent(int);
    void initialChangeEvent(int);
    void initialDescendEvent(int);
    BOOL actionDescendEvent(int);
    void initialAreaOutTurn(int);
    BOOL actionAreaOutTurn(int);
    void setAnm(int);
    void setCollision();
    void setLineBgCheck();
    void animationPlay();
    BOOL execute();
    BOOL draw();
    f32 getGroundY() { return mAcch.GetGroundH(); }
    MtxP getLeftHandMatrix() { return cullMtx; }
    MtxP getRightHandMatrix() { return cullMtx; }
    f32 getBaseAnimeFrameRate() { return 1.0f; }
    f32 getBaseAnimeFrame() { return 0.0f; }
    void restartPoint(s16) {}
    
    static bool m_hyoi_kamome;
    
public:
    /* 0x4EC */ request_of_phase_process_class mPhs;
    /* 0x4F4 */ mDoExt_McaMorf* mpMorf;
    /* 0x4F8 */ dBgS_ObjAcch mAcch;
    /* 0x6BC */ dBgS_AcchCir mAcchCirs[2];
    /* 0x73C */ dBgS_LinChk mLinChk;
    /* 0x7A8 */ dCcD_Stts mStts;
    /* 0x7E4 */ dCcD_Sph mAtSph;
    /* 0x910 */ dCcD_Sph mTgSph;
    /* 0xA3C */ dCcD_Cps mCps;
    /* 0xB74 */ cXyz mDescendStartPos;
    /* 0xB80 */ cXyz mDescendStartPosUnangled;
    /* 0xB8C */ csXyz mDescendStartAngle;
    /* 0xB92 */ u8 mB92[0xBA0 - 0xB92];
    /* 0xBA0 */ cBgS_PolyInfo mPolyInfo;
    /* 0xBB0 */ ActionFunc mCurrNpcActionFunc;
    /* 0xBBC */ ActionFunc mCurrPlayerActionFunc;
    /* 0xBC8 */ u32 mShadowId;
    /* 0xBCC */ u32 mHitFlags;
    /* 0xBD0 */ u8 mBD0[0xBD4 - 0xBD0];
    /* 0xBD4 */ int mAnmIdx;
    /* 0xBD8 */ f32 mMaxY;
    /* 0xBDC */ f32 mMinY;
    /* 0xBE0 */ f32 mPrevMorfFrame;
    /* 0xBE4 */ f32 mTargetSpeedF;
    /* 0xBE8 */ f32 mAccelF;
    /* 0xBEC */ s16 mTargetAngleX;
    /* 0xBEE */ s16 mLockAngleXTimer;
    /* 0xBF0 */ s16 mAngVelY;
    /* 0xBF2 */ s16 mAngVelX;
    /* 0xBF4 */ s16 mTargetAngVelY;
    /* 0xBF6 */ s16 mTargetAngVelX;
    /* 0xBF8 */ s16 m_jnt_body;
    /* 0xBFA */ s16 mFlapTimer;
    /* 0xBFC */ s16 mFlapExhaustedTimer;
    /* 0xBFE */ s16 mFlapEnergyTimer;
    /* 0xC00 */ s8 mAnmTblIdx;
    /* 0xC01 */ s8 mReachedAnimEnd;
    /* 0xC02 */ s8 mEventState;
    /* 0xC03 */ s8 mCurrEventIdxIdx;
    /* 0xC04 */ u8 mC04[0xC05 - 0xC04];
    /* 0xC05 */ s8 mActionStatus;
    /* 0xC06 */ u8 mUnusedC06;
    /* 0xC07 */ u8 mC07[0xC08 - 0xC07];
    /* 0xC08 */ s16 mC08;
    /* 0xC08 */ s16 mC0A;
    /* 0xC08 */ s16 mC0C;
    /* 0xC08 */ s16 mUnusedC0E;
    /* 0xC10 */ u8 mC10[0xC14 - 0xC10];
    /* 0xC14 */ f32 mUnusedC14;
    /* 0xC18 */ u8 mC18[0xC1C - 0xC18];
    /* 0xC1C */ s16 mWaitTimer;
    /* 0xC1E */ s16 mAreaOutTimer;
    /* 0xC20 */ s16 mEventIdxs[3];
    /* 0xC26 */ u8 field_C26[0xC28 - 0xC26];
};

#endif /* D_A_NPC_KAMOME_H */
