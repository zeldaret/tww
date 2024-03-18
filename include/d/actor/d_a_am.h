#ifndef D_A_AM_H
#define D_A_AM_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "d/d_particle.h"
#include "c/c_damagereaction.h"
#include "SSystem/SComponent/c_phase.h"

class am_class : public fopEn_enemy_c {
public:
    /* 0x02AC */ request_of_phase_process_class mPhase;
    /* 0x02B4 */ JntHit_c* mEyeJntHit;
    /* 0x02B8 */ mDoExt_McaMorf* mpMorf;
    /* 0x02BC */ u8 m02BC[0x02C0 - 0x02BC];
    /* 0x02C0 */ u8 mType;
    /* 0x02C1 */ u8 mPrmAreaRadius;
    /* 0x02C2 */ u8 mStartsInactive;
    /* 0x02C3 */ u8 mSwitch;
    /* 0x02C4 */ u8 mAction;
    /* 0x02C5 */ u8 mState;
    /* 0x02C6 */ u8 mHugeKnockback;
    /* 0x02C7 */ bool mbIsBodyBeingHit;
    /* 0x02C8 */ s16 mCountDownTimers[4];
    /* 0x02D0 */ s16 mCountUpTimers[5];
    /* 0x02DA */ s16 mTargetAngleY;
    /* 0x02DC */ s16 mSpawnRotY;
    /* 0x02DE */ u8 m02DE[0x02E0 - 0x02DE];
    /* 0x02E0 */ int mCurrBckIdx;
    /* 0x02E4 */ uint mSwallowedActorPID;
    /* 0x02E8 */ f32 mAreaRadius;
    /* 0x02EC */ f32 mCorrectionOffsetY;
    /* 0x02F0 */ f32 mSpawnPosY;
    /* 0x02F4 */ cXyz mEyeballPos;
    /* 0x0300 */ cXyz mMouthPos;
    /* 0x030C */ cXyz mWaistPos;
    /* 0x0318 */ cXyz mJawPos;
    /* 0x0324 */ cXyz mSpawnPos;
    /* 0x0330 */ csXyz mEyeRot;
    /* 0x0336 */ csXyz mTargetEyeRot;
    /* 0x033C */ JPABaseEmitter* m033C;
    /* 0x0340 */ JPABaseEmitter* m0340;
    /* 0x0344 */ dPa_smokeEcallBack mSmokeCbs[4];
    /* 0x03C4 */ dBgS_AcchCir mAcchCir;
    /* 0x0404 */ dBgS_ObjAcch mAcch;
    /* 0x05C8 */ dCcD_Stts mStts;
    /* 0x0604 */ dCcD_Sph mEyeSph;
    /* 0x0730 */ dCcD_Sph mMouthSph;
    /* 0x085C */ dCcD_Cyl mBodyCyl;
    /* 0x098C */ dCcD_Cyl mNeedleCyl;
    /* 0x0ABC */ enemyice mEnemyIce;
    /* 0x0E74 */ enemyfire mEnemyFire;
};

#endif /* D_A_AM_H */
