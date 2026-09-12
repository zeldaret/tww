#ifndef D_A_PZ_H
#define D_A_PZ_H

#include "res/Object/Pz.h"
#include "f_op/f_op_actor.h"
#include "d/d_npc.h"
#include "d/d_particle.h"
#include "d/d_bg_s_lin_chk.h"
#include "c/c_damagereaction.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"
#include "d/d_lib.h"

class J3DMaterial;
class J3DNode;
class J3DModel;
class J3DShape;

class daPz_matAnm_c : public J3DMaterialAnm {
public:
    void clrMoveFlag() { mbMoveFlag = false; }
    f32* getNowOffsetX() { return &mOffset.x; }
    f32* getNowOffsetY() { return &mOffset.y; }
    void setMoveFlag() { mbMoveFlag = true; }

    daPz_matAnm_c();
    void calc(J3DMaterial*) const;

public:
    /* 0x6C */ cXy mOffset;
    /* 0x74 */ cXy field_0x74;
    /* 0x7C */ bool mbMoveFlag;
};  // Size: 0x80

enum daPz_Phase_e {
    PHASE_SHOOT_GND_e,
    PHASE_DOWN_e,
    PHASE_SHOOT_PLAYER_e, // Went for that name instead of phase Stand because stand is also technically what she does in phase 1
    PHASE_MAX_e,
};

class daPz_HIO_c : public mDoHIO_entry_c {
public:
    daPz_HIO_c();
    inline virtual ~daPz_HIO_c();

public:
    /* 0x004 */ dNpc_HIO_c mNpcHIO;
    /* 0x02C */ u8 m02C;
    /* 0x02D */ bool mbEnableAttack;
    /* 0x02E */ u8 m02E;
    /* 0x02F */ u8 mForceAnmId;
    /* 0x030 */ bool mbFixTarget;
    /* 0x031 */ u8 m031;
    /* 0x032 */ bool mbDoSideStep;
    /* 0x033 */ bool mbWarpToPlayer;
    // [0] forces a back step, [1] holds her out of the attack-wait transition.
    /* 0x034 */ u8 mDbgFlags[10];
    /* 0x040 */ f32 mAttnYOffset;
    /* 0x044 */ f32 mRunAnmRate;
    /* 0x048 */ f32 mRunAnmRateMax;
    /* 0x04C */ f32 mRunAnmRateMin;
    /* 0x050 */ f32 mRunSpeed;
    /* 0x054 */ s16 mEyeAreaAngle;
    /* 0x058 */ f32 mEyeAreaDist;
    /* 0x05C */ f32 mAimOffsetMax[PHASE_MAX_e];
    /* 0x068 */ f32 mAimPlayerRate[PHASE_MAX_e];
    /* 0x074 */ f32 mAimStraightRate[PHASE_MAX_e];
    /* 0x080 */ s16 mRetreatTime[PHASE_MAX_e];
    /* 0x086 */ s16 mMoveTimeBase[PHASE_MAX_e];
    /* 0x08C */ s16 mMoveTimeRand[PHASE_MAX_e];
    /* 0x092 */ s16 mAttackTimeBase[PHASE_MAX_e];
    /* 0x098 */ s16 mAttackTimeRand[PHASE_MAX_e];
    /* 0x0A0 */ f32 mCircleRadius[PHASE_MAX_e];
    /* 0x0AC */ f32 mCircleWobble;
    /* 0x0B0 */ f32 mGravity;
    /* 0x0B4 */ f32 mBackStepJumpY;
    /* 0x0B8 */ f32 mBackStepSpeed;
    /* 0x0BC */ f32 mSideStepJumpY;
    /* 0x0C0 */ f32 mSideStepSpeed;
    /* 0x0C4 */ f32 mDownJumpY;
    /* 0x0C8 */ f32 mDownSpeed;
    /* 0x0CC */ s16 mDownTime;
    /* 0x0D0 */ f32 mRetreatDist;
    /* 0x0D4 */ f32 mFallSplashYOffset;
    /* 0x0D8 */ f32 mTurnDirChangeRate;
    /* 0x0DC */ s16 m0DC;
    /* 0x0DE */ s16 m0DE;
    /* 0x0E0 */ s16 mDamageTime;
    /* 0x0E2 */ s16 mGndHitTrigger;
    /* 0x0E4 */ s16 mGndAttackNum;
    /* 0x0E6 */ s16 mPlayerHitTrigger;
    /* 0x0E8 */ s16 mPlayerAttackNum;
    /* 0x0EC */ f32 mFollowDist;
    /* 0x0F0 */ f32 mDam01Morf;
    /* 0x0F4 */ f32 mDam02Morf;
#if VERSION > VERSION_DEMO
    /* 0x0F8 */ s16 mTalkTime[PHASE_MAX_e];
    /* 0x100 */ f32 mTalkDist[PHASE_MAX_e];
#endif
};  // Size: DEMO_SELECT(0x0F8, 0x10C)

class daPz_c : public fopNpc_npc_c {
public:
    enum Proc_e {
        /* 0x0 */ PROC_INIT_e,
        /* 0x1 */ PROC_EXEC_e,
    };

    enum Mode_e {
        /* 0x0 */ MODE_WAIT_e,
        /* 0x1 */ MODE_MOVE_e,
        /* 0x2 */ MODE_ATTACK_WAIT_e,
        /* 0x3 */ MODE_ATTACK_e,
        /* 0x4 */ MODE_DEFEND_e,
        /* 0x5 */ MODE_DOWN_e,
        /* 0x6 */ MODE_AFRAID_e,
        /* 0x7 */ MODE_SIDE_STEP_e,
        /* 0x8 */ MODE_BACK_STEP_e,
        /* 0x9 */ MODE_TALK_e,
        /* 0xA */ MODE_FOLLOW_e,
        /* 0xB */ MODE_NULL_e,
    };

    enum BckIdx_e {
        /* 0x0 */ BCK_IDX_WAIT01_e,
        /* 0x1 */ BCK_IDX_WAIT02_e,
        /* 0x2 */ BCK_IDX_RUN01_e,
        /* 0x3 */ BCK_IDX_RELORD_e,
        /* 0x4 */ BCK_IDX_WAIT03_e,
        /* 0x5 */ BCK_IDX_SHOOT_e,
        /* 0x6 */ BCK_IDX_DAM01_e,
        /* 0x7 */ BCK_IDX_DAM02_e,
        /* 0x8 */ BCK_IDX_STAND_e,
        /* 0x9 */ BCK_IDX_DEFEND_e,
        /* 0xA */ BCK_IDX_WAIT04_e,
    };

    enum BowBckIdx_e {
        /* 0x0 */ BOW_BCK_IDX_RELORD_e,
        /* 0x1 */ BOW_BCK_IDX_WAIT03_e,
        /* 0x2 */ BOW_BCK_IDX_SHOOT_e,
    };

    enum Anm_e {
        /* 0x0 */ ANM_WAIT01_e,      // pz_wait01
        /* 0x1 */ ANM_WAIT01_B_e,    // pz_wait01 - idle (modeWait)
        /* 0x2 */ ANM_WAIT02_e,      // pz_wait02 - standing still
        /* 0x3 */ ANM_RUN01_e,       // pz_run01
        /* 0x4 */ ANM_RELORD_e,      // pz_relord - nock an arrow
        /* 0x5 */ ANM_WAIT03_e,      // pz_wait03 - holding the bow drawn
        /* 0x6 */ ANM_SHOOT_e,       // pz_shoot
        /* 0x7 */ ANM_DAM01_e,       // pz_dam01 - knocked off her feet
        /* 0x8 */ ANM_DAM02_e,       // pz_dam02 - hitting the ground
        /* 0x9 */ ANM_STAND_e,       // pz_stand - getting back up
        /* 0xA */ ANM_DEFEND_e,      // pz_defend
        /* 0xB */ ANM_WAIT04_e,      // pz_wait04 - flinch / step
        /* 0xC */ ANM_TALK01_e,      // pz_wait02 with talk01 eyes
        /* 0xD */ ANM_TALK02_e,      // pz_wait02 with talk02 eyes
        /* 0xE */ ANM_TALK03_e,      // pz_wait03 with talk01 eyes
        /* 0xF */ ANM_KEEP_e,        // sentinel: leave mAnmId unchanged
    };

    enum EyeAnm_e {
        /* 0x0 */ EYE_MABA_A_e,      // pz_maba_a - blink
        /* 0x1 */ EYE_BOW_WAIT_e,    // pz_bow_wait
        /* 0x2 */ EYE_DAM01_e,       // pz_dam01
        /* 0x3 */ EYE_DAM02_e,       // pz_dam02
        /* 0x4 */ EYE_STAND_e,       // pz_stand - BTK driven, ctrlEye is skipped
        /* 0x5 */ EYE_DEFEND_e,      // pz_defend
        /* 0x6 */ EYE_WAIT04_e,      // pz_wait04
        /* 0x7 */ EYE_MABA_B_e,      // pz_maba_b - blink
        /* 0x8 */ EYE_TALK01_e,      // pz_talk01
        /* 0x9 */ EYE_TALK02_e,      // pz_talk02
    };

    enum BowAnm_e {
        /* 0x0 */ BOW_SHOOT_STOP_e,  // pz_arrow_shoot, held at play rate 0
        /* 0x1 */ BOW_SHOOT_e,       // pz_arrow_shoot - bow at rest
        /* 0x2 */ BOW_RELORD_e,      // pz_arrow_relord
        /* 0x3 */ BOW_WAIT03_e,      // pz_arrow_wait03
        /* 0x4 */ BOW_SHOOT_FIRE_e,  // pz_arrow_shoot - release
        /* 0x5 */ BOW_KEEP_e,        // sentinel: leave mBowAnmId unchanged
    };

    enum HitType_e {
        /* 0x0 */ HIT_NONE_e,              // sword contact that was not a qualifying cut
        /* 0x1 */ HIT_SWORD_e,
        /* 0x3 */ HIT_WIND_e = 3,
        /* 0x4 */ HIT_BOOMERANG_e,         // also the Bokoblin stick
        /* 0x5 */ HIT_ARROW_e,
        /* 0x6 */ HIT_BOMB_e,
        /* 0x7 */ HIT_HAMMER_e,            // also the Stalfos mace
        /* 0x8 */ HIT_HAMMER_SIDESWING_e,
        /* 0xC */ HIT_HOOKSHOT_e = 0xC,
        /* 0xE */ HIT_GRAPPLING_HOOK_e = 0xE,
    };

    enum MatNo_e {
        /* 0x03 */ MAT_EYE0_e = 0x3,
        /* 0x06 */ MAT_EYE1_e = 0x6,
        /* 0x0D */ MAT_EYEBROW0_e = 0xD,
        /* 0x10 */ MAT_EYEBROW1_e = 0x10,
    };

    struct hit_wrk_c {
        /* 0x0 */ int m0;
        /* 0x4 */ int m4;
        /* 0x8 */ u8 m8;
    };  // Size: 0xC

    struct ModeEntry {
        typedef void (daPz_c::*ModeProcFunc)(void);
        ModeProcFunc mInitFunc;
        ModeProcFunc mUpdFunc;
        const char* mModeName;
    };

    MtxP getRightHandMatrix() { return mpMorf->getModel()->getAnmMtx(PZ_JNT_HAND_R1_e); }
    bool isAnm(s8 i_anm) { return mAnmId == i_anm; }
    bool isEyeAnm(s8 i_anm) { return mCurEye == i_anm; }
    void modeProcInit(int i_mode) { modeProc(PROC_INIT_e, i_mode); }
    void setAfraid() { mbAfraidRequest = 1; }
    void setDown() { mPhase = PHASE_DOWN_e; }
    void setMove() { mbMoveRequest = 1; }
    void setStand() { mPhase = PHASE_SHOOT_PLAYER_e; }

    void _nodeHeadControl(J3DNode*, J3DModel*);
    void _nodeWaistControl(J3DNode*, J3DModel*);
    void _nodeWaist2Control(J3DNode*, J3DModel*);
    void _nodeSkirtControl(J3DNode*, J3DModel*);
    BOOL bodyCreateHeap();
    BOOL bowCreateHeap();
    BOOL _createHeap();
    void getGndPos();
    BOOL checkEyeArea(cXyz&);
    virtual u32 getMsg();
    virtual u16 next_msgStatus(u32*);
    virtual void anmAtr(u16);
    void eventOrder();
    void checkOrder();
    void setFallSplash();
    void setHeadSplash();
    void setRipple();
    void setJntStatus();
    bool demo();
    bool checkTgHit();
    void getArg();
    void setAttention();
    void setBowAnm(s8, bool);
    void setBowString(bool);
    void setAnm(s8, bool, int);
    void setAnmRunSpeed();
    void setEyeBtp(int);
    void setEyeBtk(int);
    void setEyeAnm(s8);
    void ctrlEye();
    void playEyeAnm();
    void setMtx();
    void modeWaitInit();
    void modeWait();
    void modeMoveInit();
    void modeMove();
    void modeAttackWaitInit();
    void modeAttackWait();
    void modeAttackInit();
    void modeAttack();
    void modeDefendInit();
    void modeDefend();
    void modeDownInit();
    void modeDown();
    void modeAfraidInit();
    void modeAfraid();
    void modeSideStepInit();
    void modeSideStep();
    void modeBackStepInit();
    void modeBackStep();
    void modeTalkInit();
    void modeTalk();
    void modeFollowInit();
    void modeFollow();
    void modeProc(Proc_e, int);
    bool _execute();
#if VERSION == VERSION_DEMO
    void debugDraw();
#endif
    void bowDraw();
    void bodyDraw();
    void drawShadow();
    bool _draw();
    void bodyCreateInit();
    void createInit();
    cPhs_State _create();
    bool _delete();

    static const s32 m_heapsize;
    static const char m_arc_name[];
    static const f32 m_smoke_ef;
    static const f32 m_grass_ef;
    static const f32 m_splash_ef;
    static const dCcD_SrcCyl m_cyl_src;

public:
    /* 0x06C4 */ int mMode;
    /* 0x06C8 */ int mPrevMode;
    /* 0x06CC */ BOOL mbAnmAtrSet;
    /* 0x06D0 */ u8 mDamageTimer;
    /* 0x06D1 */ u8 mHitType;
    /* 0x06D2 */ s8 mBckIdx;
    /* 0x06D3 */ s8 mAnmId;
    /* 0x06D4 */ s8 mOldAnmId;
    /* 0x06D5 */ s8 mCurEye;
    /* 0x06D8 */ int mBlinkTimer;
    /* 0x06DC */ bool mbEyeInRange;
    /* 0x06DD */ u8 mBowBckIdx;
    /* 0x06DE */ u8 mBowAnmId;
    /* 0x06DF */ u8 mOldBowAnmId;
    /* 0x06E0 */ dPa_rippleEcallBack mRippleCb;
    /* 0x06F4 */ dPa_followEcallBack mFallSplashCb;
    /* 0x0708 */ dPa_followEcallBack mHeadSplashCb;
    /* 0x071C */ cXyz mFallSplashPos;
    /* 0x0728 */ int mFallRippleTimer;
    /* 0x072C */ cXyz mHeadPos;
    /* 0x0738 */ u8 field_0x738[0x73E - 0x738];
    // Probably a bool but it create extra instructions if declared as such.
    /* 0x073E */ u8 mbGndInEyeArea;
    /* 0x073F */ bool mbAfraidRequest;
    /* 0x0740 */ bool mbMoveRequest;
    /* 0x0744 */ BOOL mbHitFromPlayer;
    /* 0x0748 */ cXyz mHitPos;
    /* 0x0754 */ hit_wrk_c mHitWrk[2];
    /* 0x076C */ request_of_phase_process_class mPhs;
    /* 0x0774 */ u32 mShadowKey;
    /* 0x0778 */ mDoExt_invisibleModel mInvisibleModel;
    /* 0x0780 */ dKy_tevstr_c mTevStr;
    /* 0x0830 */ cXyz mFollowTargetPos;
    /* 0x083C */ dBgS_ObjLinChk mLinChk;
    /* 0x08A8 */ J3DMaterialAnm* mpMatAnm[2];
    /* 0x08B0 */ daPz_Phase_e mPhase;
    /* 0x08B4 */ fpc_ProcID mArrowID;
    /* 0x08B8 */ cXyz mAttentionPos;
    /* 0x08C4 */ cXyz mTargetPos;
    /* 0x08D0 */ cXyz mEyeTargetPos;
    /* 0x08DC */ cXyz mEyePos;
    /* 0x08E8 */ s16 mHeadTurnVel;
    /* 0x08EA */ bool mbNoTurn;
    // Global timer used differently by each mode
    /* 0x08EC */ int mTimer;
    /* 0x08F0 */ int mRetreatTimer;
    /* 0x08F4 */ int mStepWaitTimer;
    /* 0x08F8 */ int mWallTurnTimer;
    /* 0x08FC */ dLib_circle_path_c mCirclePath;
    /* 0x0920 */ int mTurnDir;  // +1 / -1: which way she circles and side-steps
    /* 0x0924 */ f32 mTargetSpeedF;
    /* 0x0928 */ enemyice mEnemyIce;
    /* 0x0CE0 */ enemyfire mEnemyFire;
    /* 0x0F08 */ Mtx mWaistMtx;
    /* 0x0F38 */ cXyz mWaistPos;
    // Computed but never used
    /* 0x0F44 */ f32 mAimSpread;
    /* 0x0F48 */ bool mbAimAtPlayer;
    /* 0x0F4C */ cXyz mGanondorfPos;
    /* 0x0F58 */ cXyz mGanondorfPosOld;
    /* 0x0F64 */ bool mbHasGanondorf;
    /* 0x0F65 */ bool mbTalkedOnce;
    /* 0x0F66 */ bool mbInDemo;
    /* 0x0F67 */ u8 mEyeBtpFrame;
    /* 0x0F68 */ f32 mKnockbackSpeed;
    /* 0x0F6C */ s16 mKnockbackAngle;
    /* 0x0F70 */ f32 mStepSpeed;
    /* 0x0F74 */ u8 field_0xf74[0xF78 - 0xF74];
    /* 0x0F78 */ s16 mWaistRotZ;
    /* 0x0F7A */ s16 mWaistRotY;
#if VERSION > VERSION_DEMO
    // The demo has neither the auto-talk trigger nor the "Link is in front of me" check
    /* 0x0F7C */ int mTalkTimer;
    /* 0x0F80 */ bool mbTalkDone;
    // Probably a bool but it create extra instructions if declared as such.
    /* 0x0F81 */ u8 mbPlayerInFan;
#endif
    /* 0x0F82 */ u8 mTalkRequest;
    /* 0x0F84 */ int mArg;
    /* 0x0F88 */ bool mbHasBow;
    /* 0x0F8C */ mDoExt_McaMorf* mpBowMorf;
    /* 0x0F90 */ mDoExt_brkAnm mBrkAnm;
    /* 0x0FA8 */ mDoExt_btkAnm mBtkAnm;
    /* 0x0FBC */ mDoExt_btpAnm mBtpAnm;
    /* 0x0FD0 */ J3DMaterial* mpMaterial[17];
    /* 0x1014 */ J3DShape* mpShape[16];
    /* 0x1054 */ mDoExt_offCupOnAupPacket mOffCupOnAupPacket0;
    /* 0x1064 */ mDoExt_offCupOnAupPacket mOffCupOnAupPacket1;
    /* 0x1074 */ mDoExt_onCupOffAupPacket mOnCupOffAupPacket0;
    /* 0x1084 */ mDoExt_onCupOffAupPacket mOnCupOffAupPacket1;
};  // Size: 0x1094

STATIC_ASSERT(offsetof(daPz_c, mRippleCb) == 0x6E0);
STATIC_ASSERT(offsetof(daPz_c, mPhs) == 0x76C);
STATIC_ASSERT(offsetof(daPz_c, mTevStr) == 0x780);
STATIC_ASSERT(offsetof(daPz_c, mLinChk) == 0x83C);
STATIC_ASSERT(offsetof(daPz_c, mPhase) == 0x8B0);
STATIC_ASSERT(offsetof(daPz_c, mCirclePath) == 0x8FC);
STATIC_ASSERT(offsetof(daPz_c, mEnemyIce) == 0x928);
STATIC_ASSERT(offsetof(daPz_c, mEnemyFire) == 0xCE0);
STATIC_ASSERT(offsetof(daPz_c, mGanondorfPos) == 0xF4C);
STATIC_ASSERT(offsetof(daPz_c, mpBowMorf) == DEMO_SELECT(0xF88, 0xF8C));
STATIC_ASSERT(offsetof(daPz_c, mpMaterial) == DEMO_SELECT(0xFCC, 0xFD0));
STATIC_ASSERT(offsetof(daPz_c, mpShape) == DEMO_SELECT(0x1010, 0x1014));
STATIC_ASSERT(offsetof(daPz_c, mOffCupOnAupPacket0) == DEMO_SELECT(0x1050, 0x1054));
STATIC_ASSERT(offsetof(daPz_c, mOnCupOffAupPacket0) == DEMO_SELECT(0x1070, 0x1074));
STATIC_ASSERT(sizeof(daPz_c) == DEMO_SELECT(0x1090, 0x1094));

#endif /* D_A_PZ_H */
