#ifndef D_A_KANTERA_H
#define D_A_KANTERA_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "d/d_particle.h"
#include "SSystem/SComponent/c_phase.h"

struct mo_ga_s {
    /* 0x00 */ J3DModel* mpModel;
    /* 0x04 */ cXyz mPos;
    /* 0x10 */ cXyz m10;
    /* 0x1C */ s16 mRotX;
    /* 0x1E */ s16 mRotY;
    /* 0x20 */ u8 m20[0x24 - 0x20];
    /* 0x24 */ f32 mScale;
    /* 0x28 */ f32 mScaleY;
    /* 0x2C */ s16 m2C;
    /* 0x2E */ u8 m2E;
    /* 0x2F */ u8 m2F;
};

class kantera_class : public fopAc_ac_c {
public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ u8 mParam0;
    /* 0x299 */ u8 mParam1;
    /* 0x29A */ u8 mParam2;
    /* 0x29B */ u8 mSwitchID;
    /* 0x29C */ J3DModel* mpModel;
    /* 0x2A0 */ J3DModel* mpModel2;
    /* 0x2A4 */ uint mTargetActorID;
    /* 0x2A8 */ mDoExt_brkAnm* mpBrkAnm1;
    /* 0x2AC */ mDoExt_brkAnm* mpBrkAnm2;
    /* 0x2B0 */ int m2B0;
    /* 0x2B4 */ int m2B4;
    /* 0x2B8 */ csXyz mJointRot[2];
    /* 0x2C4 */ csXyz mJointBaseRot;
    /* 0x2CA */ csXyz m2CA;
    /* 0x2D0 */ csXyz mJointBaseRotTarget;
    /* 0x2D6 */ u8 m2D6[0x2D8 - 0x2D6];
    /* 0x2D8 */ cXyz mBonPos;
    /* 0x2E4 */ cXyz m2E4;
    /* 0x2F0 */ LIGHT_INFLUENCE mPlight;
    /* 0x310 */ Mtx mAlphaModelMtx;
    /* 0x340 */ f32 mBonAlpha;
    /* 0x344 */ f32 mBonAlphaTarget;
    /* 0x348 */ f32 mBonScale;
    /* 0x34C */ f32 mBonScaleTarget;
    /* 0x350 */ s16 mBonRot;
    /* 0x352 */ s16 mAnimCounters[2];
    /* 0x356 */ u8 m356[0x358 - 0x356];
    /* 0x358 */ int mAnimCounter;
    /* 0x35C */ s16 m35C;
    /* 0x35E */ u8 m35E[0x360 - 0x35E];
    /* 0x360 */ f32 mModel2Scale;
    /* 0x364 */ u8 mState;
    /* 0x365 */ u8 m365[0x368 - 0x365];
    /* 0x368 */ f32 mOffsY;
    /* 0x36C */ u32 mPeekZResult;
    /* 0x370 */ dBgS_AcchCir mBgS_AcchCir;
    /* 0x3B0 */ dBgS_Acch mBgS_Acch;
    /* 0x574 */ dCcD_Stts mStts;
    /* 0x5B0 */ dCcD_Sph mSph;
    /* 0x6DC */ dPa_followEcallBack mPtclCallBack0;
    /* 0x6F0 */ dPa_followEcallBack mPtclCallBack1;
    /* 0x704 */ cXyz mParticleScale;
    /* 0x710 */ mo_ga_s mGa[2];
};

#endif /* D_A_KANTERA_H */
