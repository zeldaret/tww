#ifndef D_A_EP_H
#define D_A_EP_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "SSystem/SComponent/c_phase.h"

class JPABaseEmitter;

struct ep_ga_s {
    /* 0x00 */ J3DModel* mpModel;
    /* 0x04 */ cXyz mPos;
    /* 0x10 */ cXyz m10;
    /* 0x1C */ cXyz m1C;
    /* 0x28 */ s16 rotX;
    /* 0x2A */ s16 rotY;
    /* 0x2C */ char m2C[0x4];
    /* 0x30 */ f32 scaleXZ;
    /* 0x34 */ f32 scaleY;
    /* 0x38 */ s16 m38;
    /* 0x3A */ u8 mbEnabled;
    /* 0x3B */ u8 m3B;
}; // size = 0x3C

struct ep_class {
    ep_class();

    /* 0x000 */ fopAc_ac_c actor;
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ Mtx mAlphaModelMtx;
    /* 0x2C8 */ J3DModel* mpModel;
    /* 0x2CC */ dBgS_AcchCir mAcchCir;
    /* 0x30C */ dBgS_ObjAcch mAcch;
    /* 0x4D0 */ s32 m4D0;
    /* 0x4D4 */ u8 m4D4[0x4DC - 0x4D4];
    /* 0x4DC */ f32 mLightPower;
    /* 0x4E0 */ f32 m4E0;
    /* 0x4E4 */ f32 mAlphaModelScale;
    /* 0x4E8 */ f32 mAlphaModelScaleTarget;
    /* 0x4EC */ f32 mAlphaModelAlpha;
    /* 0x4F0 */ f32 mAlphaModelAlphaTarget;
    /* 0x4F4 */ s16 mTimers[4];
    /* 0x4FC */ u8 m4FC[0x4FD - 0x4FC];
    /* 0x4FD */ u8 mbNoEp;
    /* 0x4FE */ u8 mbShouldDrawModel;
    /* 0x4FF */ u8 m4FF[0x500 - 0x4FF];
    /* 0x500 */ s16 mAlphaModelRotX;
    /* 0x502 */ s16 mAlphaModelRotY;
    /* 0x504 */ u8 mType;
    /* 0x505 */ u8 m505;
    /* 0x506 */ u8 mOnSwitchNo;
    /* 0x507 */ u8 m507;
    /* 0x508 */ u8 m508;
    /* 0x509 */ u8 m509[0x50C - 0x509];
    /* 0x50C */ JPABaseEmitter* mpEmitter;
    /* 0x510 */ LIGHT_INFLUENCE mLight;
    /* 0x530 */ cXyz mPosTop;
    /* 0x53C */ dCcD_Stts mStts;
    /* 0x578 */ dCcD_Cyl mCyl;
    /* 0x6A8 */ dCcD_Sph mSph1;
    /* 0x7D4 */ s16 m7D4;
    /* 0x7D6 */ u8 m7D6[0x7D8 - 0x7D6];
    /* 0x7D8 */ f32 m7D8;
    /* 0x7DC */ s16 m7DC;
    /* 0x7DE */ s8 mbHasObm;
    /* 0x7DF */ u8 m7DF[0x7E0 - 0x7DF];
    /* 0x7E0 */ s32 m7E0;
    /* 0x7E4 */ u8 mbHasGa;
    /* 0x7E5 */ u8 m7E5[0x7E8 - 0x7E5];
    /* 0x7E8 */ ep_ga_s mEpGa[2];
    /* 0x860 */ J3DLightInfo m860;
    /* 0x894 */ u8 m894[0x910 - 0x894];
    /* 0x910 */ u8 mGroundCheckTimer;
    /* 0x911 */ u8 m911[0x914 - 0x911];
};  // Size: 0x914

#endif /* D_A_EP_H */
