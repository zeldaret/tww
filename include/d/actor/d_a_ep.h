#ifndef D_A_EP_H
#define D_A_EP_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "SSystem/SComponent/c_phase.h"

class JPABaseEmitter;

struct ep_ga_s {
    
};

class ep_class : public fopAc_ac_c {
public:
    /* 0x290 */ request_of_phase_process_class mPhsLoad_Ep;
    /* 0x298 */ Mtx mAlphaModelMtx;
    /* 0x2C8 */ J3DModel* mpModel;
    /* 0x2CC */ dBgS_AcchCir mAcchCir;
    /* 0x30C */ dBgS_Acch mAcch;
    /* 0x4D0 */ int m4D0;
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
    /* 0x506 */ u8 mOnSwitchId;
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
    /* 0x7DE */ u8 mbHasObm;
    /* 0x7DF */ u8 m7DF[0x7E0 - 0x7DF];
    /* 0x7E0 */ int m7E0;
    /* 0x7E4 */ u8 mbHasGa;
    /* 0x7E5 */ u8 m7E5[0x7E8 - 0x7E5];
    /* 0x7E8 */ ep_ga_s mEpGa[2];
    /* 0x860 */ u32 m860;
    /* 0x864 */ u32 m864;
    /* 0x868 */ u32 m868;
    /* 0x86C */ u32 m86C;
    /* 0x870 */ f32 m870;
    /* 0x874 */ u32 m874;
    /* 0x878 */ u8 m878[0x87C - 0x878];
    /* 0x87C */ f32 m87C;
    /* 0x880 */ u32 m880;
    /* 0x884 */ u32 m884;
    /* 0x888 */ f32 m888;
    /* 0x88C */ u32 m88C;
    /* 0x890 */ u32 m890;
    /* 0x894 */ u8 m894[0x910 - 0x894];
    /* 0x910 */ u8 mGroundCheckTimer;
    /* 0x911 */ u8 m911[0x914 - 0x911];
};

#endif /* D_A_EP_H */
