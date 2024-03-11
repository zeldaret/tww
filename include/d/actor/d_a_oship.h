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

class daOship_c : public fopAc_ac_c {
public:
    enum Proc_e {
        
    };

    void getSw() {}
    void isSpecial() {}
    void modeProcInit(int) {}

    void _nodeControl(J3DNode*, J3DModel*);
    void _pathMove(cXyz*, cXyz*, cXyz*);
    void pathMove();
    void plFireRepeat();
    void lineCheck(cXyz*, cXyz*);
    void changeModeByRange();
    void createWave();
    void setWave();
    void checkTgHit();
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
    BOOL _execute();
    BOOL _draw();
    void createInit();
    void _createHeap();
    void getArg();
    s32 _create();
    BOOL _delete();

public:
    /* 0x290 */ u8 m290[0x2AC - 0x290];
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
    /* 0x2D4 */ u8 m2D4;
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
    /* 0xAE0 */ dBgS_Acch mAcch;
    /* 0xCA4 */ dBgS_AcchCir mAcchCir;
    /* 0xCE4 */ dLib_wave_c mWave;
    /* 0xCF0 */ cXyz mTargetPos;
    /* 0xCFC */ cXyz mBombSpawnPos;
    /* 0xD08 */ cXyz mSmokePos;
    /* 0xD14 */ cXyz mFlagOffset;
    /* 0xD20 */ Mtx mFlagMtx;
    /* 0xD50 */ uint mFlagPcId;
    /* 0xD54 */ uint mBombPcId[1];
    /* 0xD58 */ u8 mD58[0xD68 - 0xD58];
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
    /* 0xD8C */ u8 mBombAlloc[1];
    /* 0xD8D */ u8 mD8D[0xD94 - 0xD8D];
    /* 0xD94 */ dBgS_LinChk mLinChk;
};

class daOship_HIO_c {
public:
    daOship_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_OSHIP_H */
