#ifndef D_A_FF_H
#define D_A_FF_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "SSystem/SComponent/c_phase.h"

class mDoExt_brkAnm;

class ff_class : public fopAc_ac_c {
public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel[2];
    /* 0x2A0 */ mDoExt_brkAnm* mBrkAnm[2];
    /* 0x2A8 */ u8 m2A8[0x2A9 - 0x2A8];
    /* 0x2A9 */ u8 mbNoUseGroundY;
    /* 0x2AA */ u8 m2AA[0x2AC - 0x2AA];
    /* 0x2AC */ f32 mRotVel;
    /* 0x2B0 */ f32 mVelocityFwdTarget;
    /* 0x2B4 */ cXyz mVelImpulse;
    /* 0x2C0 */ cXyz m2C0;
    /* 0x2CC */ f32 mScale;
    /* 0x2D0 */ f32 mScaleTarget;
    /* 0x2D4 */ f32 mGlowScale;
    /* 0x2D8 */ f32 mGlowScaleY;
    /* 0x2DC */ f32 mGroundY;
    /* 0x2E0 */ cXyz mScatterPos;
    /* 0x2EC */ cXyz m2EC;
    /* 0x2F8 */ cXyz mHomePos;
    /* 0x304 */ s16 mTargetRotX;
    /* 0x306 */ s16 mTargetRotY;
    /* 0x308 */ s16 mTimers[5];
    /* 0x312 */ s16 mLiveTimer;
    /* 0x314 */ s8 mMode;
    /* 0x315 */ u8 m315[0x317 - 0x315];
    /* 0x317 */ u8 mbNotVisibleZ;
    /* 0x318 */ dCcD_Stts mStts;
    /* 0x354 */ dCcD_Sph mSph;
};

#endif /* D_A_FF_H */
