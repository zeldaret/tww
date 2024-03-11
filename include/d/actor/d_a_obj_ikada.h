#ifndef D_A_OBJ_IKADA_H
#define D_A_OBJ_IKADA_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "d/d_bg_w.h"
#include "d/d_particle.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_path.h"
#include "d/d_lib.h"

class daObj_Ikada_c : public fopAc_ac_c {
public:
    enum Proc_e {
        
    };

    void getCranePos() {}
    void getFrame() {}
    void getMode() {}
    void getSvDirection() {}
    void isBonbori() {}
    void isCrane() {}
    void isFlag() {}
    void isWave() {}
    void modeProcInit(int) {}
    void setInitPos() {}
    void setStart() {}
    void setStop() {}

    void _nodeControl(J3DNode*, J3DModel*);
    void _pathMove(cXyz*, cXyz*, cXyz*);
    void _ride(fopAc_ac_c*);
    void setCollision();
    void checkTgHit();
    void pathMove();
    void HandleRight();
    void HandleLeft();
    void createWave();
    void setWave();
    void incRopeCnt(int, int);
    void setRopePos();
    void setMtx();
    void modeProc(Proc_e, int);
    void modeWaitInit();
    void modeWait();
    void modeCraneUpInit();
    void modeCraneUp();
    void modeCraneUpWaitInit();
    void modeCraneUpWait();
    void modeCraneDownInit();
    void modeCraneDown();
    void modeCraneDownWaitInit();
    void modeCraneDownWait();
    void modeCraneTurnInit();
    void modeCraneTurn();
    void modeCraneResetInit();
    void modeCraneReset();
    void modeCraneWaitInit();
    void modeCraneWait();
    void modePathMoveInit();
    void modePathMove();
    void modeStopInit();
    void modeStop();
    void modePathMoveTerryInit();
    void modePathMoveTerry();
    void modeStopTerryInit();
    void modeStopTerry();
    void modeStopBombTerryInit();
    void modeStopBombTerry();
    void epProc();
    BOOL _execute();
    void debugDraw();
    BOOL _draw();
    void getArg();
    void createInit();
    void _createHeap();
    s32 _create();
    BOOL _delete();

public:
    /* 0x0290 */ u32 mType;
    /* 0x0294 */ u32 m0294;
    /* 0x0298 */ u32 m0298;
    /* 0x029C */ u32 m029C;
    /* 0x02A0 */ u32 m02A0;
    /* 0x02A4 */ u8 mPathId;
    /* 0x02A5 */ u8 m02A5[0x02A8 - 0x02A5];
    /* 0x02A8 */ cXyz mCurPathP0;
    /* 0x02B4 */ u8 mCurPathPoint;
    /* 0x02B5 */ u8 m02B5[0x02B8 - 0x02B5];
    /* 0x02B8 */ dPath* mpPath;
    /* 0x02BC */ u8 m02BC[0x02C0 - 0x02BC];
    /* 0x02C0 */ cXyz mCurPathP1;
    /* 0x02CC */ u8 m02CC[0x02D8 - 0x02CC];
    /* 0x02D8 */ f32 mVelocityFwdTarget;
    /* 0x02DC */ cXyz mPathPosTarget;
    /* 0x02E8 */ u8 m02E8[0x02EC - 0x02E8];
    /* 0x02EC */ u8 mbCraneMode;
    /* 0x02ED */ u8 m02ED[0x02F0 - 0x02ED];
    /* 0x02F0 */ int mCurMode;
    /* 0x02F4 */ int m02F4;
    /* 0x02F8 */ dPa_waveEcallBack mWaveLCallback;
    /* 0x035C */ dPa_waveEcallBack mWaveRCallback;
    /* 0x03C0 */ dPa_splashEcallBack mSplashCallBack;
    /* 0x03DC */ dPa_trackEcallBack mTrackCallBack;
    /* 0x042C */ dPa_rippleEcallBack mRippleCallBack;
    /* 0x0440 */ u8 m0440[0x0450 - 0x0440];
    /* 0x0450 */ cXyz mWavePos;
    /* 0x045C */ csXyz mWaveRot;
    /* 0x0462 */ u8 m0462[0x0464 - 0x0462];
    /* 0x0464 */ f32 mSplashScaleTimer;
    /* 0x0468 */ cXyz mTrackPos;
    /* 0x0474 */ cXyz m0474;
    /* 0x0480 */ dPa_followEcallBack mBombSmokeEasterEgg;
    /* 0x0494 */ csXyz mBombSmokeRot;
    /* 0x049A */ u8 m049A[0x049C - 0x049A];
    /* 0x049C */ cXyz mBombSmokePos;
    /* 0x04A8 */ int m04A8;
    /* 0x04AC */ s16 mBombSmokeAngle;
    /* 0x04AE */ u8 m04AE[0x04B0 - 0x04AE];
    /* 0x04B0 */ dPa_followEcallBack mFireParticle;
    /* 0x04C4 */ cXyz mFirePos;
    /* 0x04D0 */ Mtx mLightMtx;
    /* 0x0500 */ f32 mLightPower;
    /* 0x0504 */ f32 mLightPowerTarget;
    /* 0x0508 */ f32 m0508;
    /* 0x050C */ f32 m050C;
    /* 0x0510 */ int mEpTimer0;
    /* 0x0514 */ int mEpTimer1;
    /* 0x0518 */ u8 m0518[0x051C - 0x0518];
    /* 0x051C */ int mTimer;
    /* 0x0520 */ u8 m0520[0x0528 - 0x0520];
    /* 0x0528 */ s16 mLightRotX;
    /* 0x052A */ s16 mLightRotY;
    /* 0x052C */ request_of_phase_process_class mPhs;
    /* 0x0534 */ J3DModel* mpModel;
    /* 0x0538 */ mDoExt_bckAnm mBckAnm;
    /* 0x0548 */ u8 mbIsLinkRiding;
    /* 0x0549 */ u8 m0549[0x054C - 0x0549];
    /* 0x054C */ dBgW* mpBgW;
    /* 0x0550 */ Mtx mMtx;
    /* 0x0580 */ dBgS_ObjAcch mObjAcch;
    /* 0x0744 */ dBgS_AcchCir mAcchCir;
    /* 0x0784 */ uint mFlagPcId;
    /* 0x0788 */ cXyz mFlagOffset;
    /* 0x0794 */ f32 mFlagScale;
    /* 0x0798 */ J3DModel* mpRopeEnd;
    /* 0x079C */ mDoExt_3DlineMat1_c mRopeLine;
    /* 0x07D8 */ int m07D8;
    /* 0x07DC */ cXyz m07DC[200];
    /* 0x113C */ csXyz mJointRot[4];
    /* 0x1154 */ u32 m1154;
    /* 0x1158 */ s16 m1158;
    /* 0x115A */ s16 m115A;
    /* 0x115C */ s16 m115C;
    /* 0x115E */ s16 m115E;
    /* 0x1160 */ s16 mLinkRideRockTimer;
    /* 0x1162 */ s16 mLinkRideRockAmpl;
    /* 0x1164 */ s16 mWaveAnimTimer;
    /* 0x1166 */ u8 m1166;
    /* 0x1167 */ u8 m1167[0x1168 - 0x1167];
    /* 0x1168 */ int m1168;
    /* 0x116C */ int mSvId[4];
    /* 0x117C */ dCcD_Sph mSph;
    /* 0x12A8 */ dCcD_Stts mStts;
    /* 0x12E4 */ u8 m12E4[0x12E8 - 0x12E4];
    /* 0x12E8 */ cXyz mSePos;
    /* 0x12F4 */ int mStopTimer;
    /* 0x12F8 */ dLib_wave_c mWave;
    /* 0x1304 */ u8 m1304[0x1308 - 0x1304];
    /* 0x1308 */ LIGHT_INFLUENCE mPLight;
    /* 0x1328 */ cXyz mInitPos;
};

class daObj_Ikada_HIO_c {
public:
    daObj_Ikada_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_IKADA_H */
