#ifndef D_A_AM2_H
#define D_A_AM2_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "d/d_particle.h"
#include "c/c_damagereaction.h"
#include "SSystem/SComponent/c_phase.h"

struct am2_class {
    /* 0x000 */ fopEn_enemy_c actor;
    /* 0x2AC */ request_of_phase_process_class mPhase;
    /* 0x2B4 */ JntHit_c* mEyeJntHit;
    /* 0x2B8 */ mDoExt_McaMorf* mpMorf;
    /* 0x2BC */ u8 m2BC[0x2C0 - 0x2BC];
    /* 0x2C0 */ mDoExt_btkAnm* mpBtkAnm;
    /* 0x2C4 */ mDoExt_brkAnm* mpBrkAnm;
    /* 0x2C8 */ u8 mType;
    /* 0x2C9 */ u8 mPrmAreaRadius;
    /* 0x2CA */ u8 mStartsInactive;
    /* 0x2CB */ u8 mSwitch;
    /* 0x2CC */ u8 mAction;
    /* 0x2CD */ u8 mMode;
    /* 0x2CE */ u8 m2CE;
    /* 0x2CF */ bool mbIsWeakBeingHit;
    /* 0x2D0 */ bool mbNotInHomeRoom;
    /* 0x2D1 */ bool mbMadeWaterSplash;
    /* 0x2D2 */ u8 mInAbyssTimer;
    /* 0x2D3 */ u8 m2D3[0x2E0 - 0x2D3];
    /* 0x2E0 */ cXyz mEyeballPos;
    /* 0x2EC */ cXyz mNeedlePos;
    /* 0x2F8 */ cXyz mWeakPos;
    /* 0x304 */ cXyz m304;
    /* 0x310 */ cXyz mSpawnPos;
    /* 0x31C */ cXyz mLinChkCenter;
    /* 0x328 */ cXyz mLinChkDest;
    /* 0x334 */ s16 mCountDownTimers[5];
    /* 0x33E */ s16 mCountUpTimers[4];
    /* 0x346 */ s16 mTargetAngleY;
    /* 0x348 */ s16 mSpawnRotY;
    /* 0x34A */ u8 m34A[0x34C - 0x34A];
    /* 0x34C */ int mCurrBckIdx;
    /* 0x350 */ f32 mCorrectionOffsetY;
    /* 0x354 */ f32 mAreaRadius;
    /* 0x358 */ f32 mPickedUpYPos;
    /* 0x35C */ f32 mAcchRadius;
    /* 0x360 */ dBgS_AcchCir mAcchCir;
    /* 0x3A0 */ dBgS_ObjAcch mAcch;
    /* 0x564 */ dCcD_Stts mStts;
    /* 0x5A0 */ dCcD_Cyl mBodyCyl;
    /* 0x6D0 */ dCcD_Cyl mNeedleCyl;
    /* 0x800 */ dCcD_Sph mEyeSph;
    /* 0x92C */ dCcD_Sph mWeakSph;
    /* 0xA58 */ dPa_smokeEcallBack mSmokeCb;
    /* 0xA78 */ dPa_rippleEcallBack mRippleCb;
    /* 0xA8C */ enemyice mEnemyIce;
};

#endif /* D_A_AM2_H */
