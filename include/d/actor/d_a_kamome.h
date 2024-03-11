#ifndef D_A_KAMOME_H
#define D_A_KAMOME_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_path.h"

class mDoExt_McaMorf;

class kamome_class : public fopAc_ac_c {
public:
    /* 0x290 */ request_of_phase_process_class mPhsKamome;
    /* 0x298 */ mDoExt_McaMorf* mpMorf;
    /* 0x29C */ u32 mShadowId;
    /* 0x2A0 */ u8 mType;
    /* 0x2A1 */ u8 mKoMaxCount;
    /* 0x2A2 */ u8 mPathIdx;
    /* 0x2A3 */ u8 mSwitchIdArg;
    /* 0x2A4 */ int mGlobalTimer;
    /* 0x2A8 */ u8 mAnimState;
    /* 0x2A9 */ u8 mMoveState;
    /* 0x2AA */ u8 mSwitchId;
    /* 0x2AB */ u8 m2AB;
    /* 0x2AC */ s16 mJointRotY;
    /* 0x2AE */ s16 mJointRotZ;
    /* 0x2B0 */ s16 mJointRotYTarget;
    /* 0x2B2 */ s16 mJointRotZTarget;
    /* 0x2B4 */ s16 m2B4;
    /* 0x2B6 */ u8 m2B6[0x2B8 - 0x2B6];
    /* 0x2B8 */ f32 m2B8;
    /* 0x2BC */ u8 mbNoDraw;
    /* 0x2BD */ u8 m2BD[0x2C0 - 0x2BD];
    /* 0x2C0 */ cXyz mTargetPos;
    /* 0x2CC */ f32 mVelocityFwdTarget;
    /* 0x2D0 */ f32 mVelocityFwdTargetMaxVel;
    /* 0x2D4 */ f32 mRotVelFade;
    /* 0x2D8 */ f32 mRotVel;
    /* 0x2DC */ u8 m2DC[0x2E0 - 0x2DC];
    /* 0x2E0 */ s16 mTimer0;
    /* 0x2E2 */ s16 mTimer1;
    /* 0x2E4 */ s16 mTimer2;
    /* 0x2E6 */ s16 mTimer3;
    /* 0x2E8 */ s16 mTimer4;
    /* 0x2EA */ s16 mTimer5;
    /* 0x2EC */ s16 mRiseTimer;
    /* 0x2EE */ u8 m2EE[0x2F0 - 0x2EE];
    /* 0x2F0 */ f32 mScale;
    /* 0x2F4 */ uint mEsaProcID;
    /* 0x2F8 */ fopAc_ac_c* mpTargetActor;
    /* 0x2FC */ s16 m2FC;
    /* 0x2FE */ u8 mbUsePathMovement;
    /* 0x2FF */ u8 mCurPointIdx;
    /* 0x300 */ s8 mPathIdxIncr;
    /* 0x301 */ u8 m301[0x304 - 0x301];
    /* 0x304 */ dPath* mpPath;
    /* 0x308 */ u8 m308;
    /* 0x309 */ u8 m309[0x30A - 0x309];
    /* 0x30A */ s16 mRotX;
    /* 0x30C */ s16 mRotY;
    /* 0x30E */ u8 m30E[0x31C - 0x30E];
    /* 0x31C */ dBgS_AcchCir mAcchCir;
    /* 0x35C */ dBgS_Acch mAcch;
    /* 0x520 */ dCcD_Stts mCcD;
    /* 0x55C */ dCcD_Sph mSph;
    /* 0x688 */ u8 m688;
    /* 0x689 */ u8 m689[0x68C - 0x689];
};

#endif /* D_A_KAMOME_H */
