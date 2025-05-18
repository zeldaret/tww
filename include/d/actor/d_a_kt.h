#ifndef D_A_KT_H
#define D_A_KT_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"
#include "JSystem/J3DGraphAnimator/J3DAnimation.h"

class kt_class : public fopAc_ac_c {
public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ void* field_0x29c[2];
    /* 0x2A4 */ J3DFrameCtrl mFrameCtrl;
    /* 0x2B8 */ J3DModel* mpModelWing;
    /* 0x2BC */ f32 mGroundY;
    /* 0x2C0 */ f32 mLiftY;
    /* 0x2C4 */ f32 mLiftYTimer;
    /* 0x2C8 */ f32 mSpeedLerp;
    /* 0x2CC */ s32 mWingTimer;
    /* 0x2D0 */ f32 mSpeedFwd;
    /* 0x2D4 */ cXyz mSpeedVel;
    /* 0x2E0 */ f32 mWingScale;
    /* 0x2E4 */ cXyz field_0x2e4;
    /* 0x2F0 */ cXyz mTargetPos;
    /* 0x2FC */ cXyz mTargetPosHome;
    /* 0x308 */ cXyz mHomePos;
    /* 0x314 */ s16 mTimer[3];
    /* 0x31A */ s16 mAngleRoll;
    /* 0x31C */ s8 mMode;
    /* 0x31D */ u8 field_0x31d;
    /* 0x31E */ bool mHitGround;
    /* 0x31E */ u8 field_0x31f;
};

#endif /* D_A_KT_H */
