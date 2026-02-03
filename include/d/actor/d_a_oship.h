#ifndef D_A_OSHIP_H
#define D_A_OSHIP_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_bg_s_acch.h"
#include "d/d_particle.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_path.h"
#include "d/d_lib.h"
#include "m_Do/m_Do_hostIO.h"

class daOship_c : public fopAc_ac_c {
public:
    enum Proc_e {
        PROC_INIT = 0,
        PROC_EXEC = 1
    };

    struct ActorModeTable {
        typedef void (daOship_c::*ModeProcFunc)(void);
        ModeProcFunc mInitFunc;
        ModeProcFunc mUpdFunc;
        char* mModeName;
    };

#if VERSION == VERSION_DEMO
    u8 getSw() { return m295; }
#else
    u8 getSw() { return mSwitchA; }
#endif
    void isSpecial() {}
    void modeProcInit(int i_newMode) { modeProc(PROC_INIT, i_newMode); }

    void _nodeControl(J3DNode*, J3DModel*);
    BOOL _pathMove(cXyz*, cXyz*, cXyz*);
    void pathMove();
    bool plFireRepeat();
    bool lineCheck(cXyz*, cXyz*);
    void changeModeByRange();
    void createWave();
    void setWave();
    bool checkTgHit();
    void setAttention();
    void setCollision();
    void attackCannon(int);
    void setMtx();
    void modeWaitInit();
    void modeWait();
    void modeRangeAInit();
    void modeRangeA();
    void modeRangeBInit();
    void modeRangeB();
    void modeRangeCInit();
    void modeRangeC();
    void modeRangeDInit();
    void modeRangeD();
    void modeDamageInit();
    void modeDamage();
    void modeAttackInit();
    void modeAttack();
    void modeDeleteInit();
    void modeDelete();
    void modeProc(Proc_e, int);
    bool _execute();
    bool _draw();
    void createInit();
    BOOL _createHeap();
    void getArg();
    cPhs_State _create();
    bool _delete();

    static const dCcD_SrcCyl m_cyl_src;
    static const char m_arc_name[];
    static const s32 m_heapsize;

public:
    /* 0x290 */ u8 m290[0x295 - 0x290];
    /* 0x295 */ u8 m295;
    /* 0x296 */ u8 m296[0x2AC - 0x296];
    /* 0x2AC */ int mCurrentProc;
    /* 0x2B0 */ u8 mSubMode;
    /* 0x2B1 */ u8 mSwitchA;
    /* 0x2B2 */ u8 mSwitchB;
    /* 0x2B3 */ u8 mPathId;
    /* 0x2B4 */ u8 mTriforce;
    /* 0x2B5 */ u8 mRandomSalvagePoint;
    /* 0x2B6 */ u8 mModelType;
    /* 0x2B7 */ u8 m2B7[0x2B8 - 0x2B7];
    /* 0x2B8 */ cXyz mOrigPos;
    /* 0x2C4 */ u8 m2C4[0x2C8 - 0x2C4];
    /* 0x2C8 */ cXyz mPathP0;
    /* 0x2D4 */ s8 m2D4;
    /* 0x2D5 */ u8 m2D5[0x2D8 - 0x2D5];
    /* 0x2D8 */ dPath* mpPath;
    /* 0x2DC */ u8 m2DC[0x2E0 - 0x2DC];
    /* 0x2E0 */ cXyz mPathP1;
    /* 0x2EC */ u8 m2EC[0x2F8 - 0x2EC];
    /* 0x2F8 */ dPa_waveEcallBack mWaveCallback1;
    /* 0x35C */ dPa_waveEcallBack mWaveCallback2;
    /* 0x3C0 */ dPa_splashEcallBack mSplashCallback;
    /* 0x3DC */ dPa_trackEcallBack mTrackCallback;
    /* 0x42C */ dPa_followEcallBack mSmokeFollowCallback[3];
    /* 0x468 */ cXyz mWavePos;
    /* 0x474 */ csXyz mWaveRot;
    /* 0x47A */ u8 m47A[0x47C - 0x47A];
    /* 0x47C */ f32 mSplashScaleTimer;
    /* 0x480 */ cXyz mTrackPos;
    /* 0x48C */ csXyz mSmokeRot[3];
    /* 0x49E */ s16 mSmokeRotY[3];
    /* 0x4A4 */ int mSmokePtclCount;
    /* 0x4A8 */ request_of_phase_process_class mPhs;
    /* 0x4B0 */ J3DModel* mpModel;
    /* 0x4B4 */ dCcD_Stts mStts;
    /* 0x4F0 */ dCcD_Cyl mCyl[5];
    /* 0xAE0 */ dBgS_ObjAcch mAcch;
    /* 0xCA4 */ dBgS_AcchCir mAcchCir;
    /* 0xCE4 */ dLib_wave_c mWave;
    /* 0xCF0 */ cXyz mTargetPos;
    /* 0xCFC */ cXyz mBombSpawnPos;
    /* 0xD08 */ cXyz mSmokePos;
    /* 0xD14 */ cXyz mFlagOffset;
    /* 0xD20 */ Mtx mFlagMtx;
    /* 0xD50 */ fpc_ProcID mFlagPcId;
    /* 0xD54 */ fpc_ProcID mBombPcId[5];
    /* 0xD68 */ f32 mVelocityFwdTarget;
    /* 0xD6C */ int mAimCounter;
    /* 0xD70 */ int mHitTimer;
    /* 0xD74 */ int mAttackTimer;
    /* 0xD78 */ u8 mD78[0xD7C - 0xD78];
    /* 0xD7C */ int mPlFireTimer;
    /* 0xD80 */ s16 mAttackSwayTimer;
    /* 0xD82 */ s16 mAttackSwayAmount;
    /* 0xD84 */ s16 mAimRotY;
    /* 0xD86 */ s16 mAimRotYTarget;
    /* 0xD88 */ s16 mAimRotX;
    /* 0xD8A */ s16 mAimRotXTarget;
    /* 0xD8C */ u8 mBombAlloc[5];
    /* 0xD91 */ u8 mD91[0xD94 - 0xD91];
    /* 0xD94 */ dBgS_ObjLinChk mLinChk;
};  // Size: 0xE00
STATIC_ASSERT(sizeof(daOship_c) == 0xE00);

class daOship_HIO_c : public mDoHIO_entry_c {
public:
    daOship_HIO_c();
    virtual ~daOship_HIO_c() {}
public:
    /* 0x04 */ s8 field_0x04;
    /* 0x05 */ u8 field_0x05;
    /* 0x06 */ u8 field_0x06;
    /* 0x07 */ s8 field_0x07;
    /* 0x08 */ u8 field_0x08;
    /* 0x09 */ u8 field_0x09[0x0C - 0x09];
    /* 0x0C */ f32 mAttentionOffsY;
    /* 0x10 */ f32 mEyeOffsY;
    /* 0x14 */ f32 mWaveOffsZ;
    /* 0x18 */ f32 mTrackOffsZ;
    /* 0x1C */ cXyz mBombOffset;
    /* 0x28 */ f32 mDistRangeA;
    /* 0x2C */ f32 mDistRangeB;
    /* 0x30 */ f32 mDistRangeC;
    /* 0x34 */ s16 mAttackDelayA;
    /* 0x36 */ s16 mAttackDelayB;
    /* 0x38 */ f32 mPathSpeed;
    /* 0x3C */ f32 mSpecScale;
    /* 0x40 */ f32 mTrackOffsY;
    /* 0x44 */ f32 mTrackScaleY;
    /* 0x48 */ f32 mSplashScaleTimerTarget;
    /* 0x4C */ f32 mSplashMaxScaleTimer;
    /* 0x50 */ f32 mWaveVelFade1;
    /* 0x54 */ f32 mTrackVel;
    /* 0x58 */ f32 mWaveVelSpeed;
    /* 0x5C */ f32 mWaveVelFadeOffs;
    /* 0x60 */ f32 mWaveMaxVelocity;
    /* 0x64 */ cXyz mWaveCollapsePos0;
    /* 0x70 */ cXyz mWaveCollapsePos1;
    /* 0x7C */ f32 mBombSpeed;
    /* 0x80 */ f32 mBombAcceleration;
    /* 0x84 */ s16 mBombNoGravityTime;
    /* 0x86 */ u8 field_0x86[0x88 - 0x86];
    /* 0x88 */ f32 mBadAimAdjustDistanceStart;
    /* 0x8C */ s16 mBadAimMax;
    /* 0x8E */ s16 field_0x8E;
    /* 0x90 */ s16 field_0x90;
    /* 0x92 */ s16 mNode2RotZ;
};  // Size: 0x94

#endif /* D_A_OSHIP_H */
