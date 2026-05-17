#ifndef D_A_ST_H
#define D_A_ST_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "m_Do/m_Do_ext.h"
#include "c/c_damagereaction.h"
#include "m_Do/m_Do_hostIO.h"

struct st_p {
    /* 0x00 */ J3DModel* mpPartModel;
    /* 0x04 */ s8 mPartState;
    /* 0x05 */ s8 m05;
    /* 0x06 */ u8 m06[0x08 - 0x06];
    /* 0x08 */ cXyz mPartPos;
    /* 0x14 */ cXyz mPartPrevPos;
    /* 0x20 */ cXyz mPartVelocity;
    /* 0x2C */ csXyz mPartRot;
    /* 0x32 */ csXyz mPartRotAdd;
    /* 0x38 */ s16 m38;
    /* 0x3A */ s16 m3A;
    /* 0x3C */ s16 m3C;
    /* 0x3E */ s16 m3E;
    /* 0x40 */ s8 mWaitTimer;
    /* 0x41 */ u8 m41[0x44 - 0x41];
    /* 0x44 */ f32 m44;
    /* 0x48 */ dPa_smokeEcallBack m48;
    /* 0x68 */ u8 m68[0x6C - 0x68];
}; // Size: 0x6C

struct st_ke_s {
    /* 0x000 */ cXyz m000[10];
    /* 0x078 */ cXyz m078[10];
    /* 0x0F0 */ csXyz m0F0;
    /* 0x0F6 */ u8 m0F6[0x12C - 0x0F6];
}; // Size: 0x12C

struct st_nun_s {
    /* 0x00 */ cXyz m00[3];
    /* 0x24 */ csXyz m24[3];
    /* 0x34 */ u8 m34[0x38 - 0x36];
    /* 0x38 */ cXyz m38[3];
};

struct st_class {
    /* 0x0000 */ fopEn_enemy_c actor;
    /* 0x02AC */ request_of_phase_process_class mPhase;
    /* 0x02B4 */ u8 mBehaviorType;
    /* 0x02B5 */ u8 mAmbushSightRange;
    /* 0x02B6 */ u8 mUnusedParam;
    /* 0x02B7 */ u8 mAmbushSwitch;
    /* 0x02B8 */ u8 mDeathSwitch;
    /* 0x02B9 */ u8 m02B9;
    /* 0x02BA */ u8 m02BA[0x02BC - 0x02BA];
    /* 0x02BC */ mDoExt_McaMorf* mpMorf;
    /* 0x02C0 */ mDoExt_McaMorf* mpMorf2;
    /* 0x02C4 */ s16 m02C4;
    /* 0x02C6 */ s16 mActionState;
    /* 0x02C8 */ s8 mFightBehavior;
    /* 0x02C9 */ u8 m02C9[0x02CA - 0x02C9];
    /* 0x02CA */ s16 m02CA;
    /* 0x02CC */ s8 m02CC;
    /* 0x02CD */ u8 m02CD[0x02D0 - 0x02CD];
    /* 0x02D0 */ cXyz mPlayerPos;
    /* 0x02DC */ f32 m02DC;
    /* 0x02E0 */ f32 m02E0;
    /* 0x02E4 */ s16 m02E4;
    /* 0x02E6 */ u8 m02E6[0x02E8 - 0x02E6];
    /* 0x02E8 */ u32 m02E8;
    /* 0x02EC */ s16 mTimers[5];
    /* 0x02F6 */ s16 m02F6;
#if VERSION > VERSION_DEMO
    /* 0x02F8 */ s16 m02F8;
#endif
    /* 0x02FA */ s8 m02FA;
    /* 0x02FB */ u8 m02FB;
    /* 0x02FC */ csXyz m02FC;
    /* 0x0302 */ s16 m0302;
    /* 0x0304 */ s16 m0304;
#if VERSION > VERSION_DEMO
    /* 0x0306 */ u8 m0306[0x0308 - 0x0306];
#endif
    /* 0x0308 */ f32 m0308;
    /* 0x030C */ dBgS_AcchCir mAcchCir;
    /* 0x034C */ dBgS_ObjAcch mAcch;
    /* 0x0510 */ dCcD_Stts mStts;
    /* 0x054C */ dCcD_Sph m054C[7];
    /* 0x0D80 */ dCcD_Sph m0D80;
    /* 0x0EAC */ cXyz m0EAC;
    /* 0x0EB8 */ cXyz m0EB8;
    /* 0x0EC4 */ cXyz m0EC4;
    /* 0x0ED0 */ s8 m0ED0;
    /* 0x0ED1 */ s8 m0ED1;
    /* 0x0ED2 */ s8 m0ED2;
    /* 0x0ED3 */ s8 m0ED3;
    /* 0x0ED4 */ st_p mParts[26];
    /* 0x19CC */ st_ke_s mKe[3];
    /* 0x1D50 */ mDoExt_3DlineMat0_c mLineMat;
    /* 0x1D6C */ st_nun_s mNun;
    /* 0x1DC8 */ s8 m1DC8;
    /* 0x1DC9 */ u8 m1DC9[0x1DCC - 0x1DC9];
    /* 0x1DCC */ fpc_ProcID mHeldWeaponEntityId;
    /* 0x1DD0 */ s8 m1DD0;
    /* 0x1DD1 */ u8 m1DD1[0x1DD4 - 0x1DD1];
    /* 0x1DD4 */ fpc_ProcID mUpperBodyEntityId;
    /* 0x1DD8 */ s8 m1DD8;
    /* 0x1DD9 */ u8 m1DD9[0x1DDA - 0x1DD9];
    /* 0x1DDA */ s16 m1DDA;
    /* 0x1DDC */ s16 m1DDC;
    /* 0x1DDE */ s16 m1DDE;
    /* 0x1DE0 */ f32 m1DE0;
    /* 0x1DE4 */ s8 m1DE4;
    /* 0x1DE5 */ s8 m1DE5;
    /* 0x1DE6 */ csXyz m1DE6[26];
#if VERSION > VERSION_DEMO
    /* 0x1E82 */ s16 m1E82;
#endif
    /* 0x1E84 */ s8 m1E84;
    /* 0x1E85 */ s8 mCountdownToDeath;
#if VERSION > VERSION_DEMO
    /* 0x1E86 */ s8 m1E86;
#endif
    /* 0x1E87 */ s8 m1E87;
    /* 0x1E88 */ dPa_smokeEcallBack m1E88[3];
    /* 0x1EE8 */ JPABaseEmitter* m1EE8[20];
    /* 0x1F38 */ s16 m1F38[20];
    /* 0x1F60 */ s16 m1F60;
    /* 0x1F62 */ u8 m1F62[0x1F64 - 0x1F62];
    /* 0x1F64 */ f32 m1F64;
    /* 0x1F68 */ s8 m1F68;
    /* 0x1F69 */ u8 m1F69[0x1F6C - 0x1F69];
    /* 0x1F6C */ cXyz m1F6C;
    /* 0x1F78 */ csXyz m1F78;
    /* 0x1F7E */ s16 m1F7E;
    /* 0x1F80 */ s16 m1F80;
    /* 0x1F82 */ s8 m1F82;
    /* 0x1F83 */ s8 m1F83;
    /* 0x1F84 */ s8 m1F84;
    /* 0x1F85 */ u8 m1F85[0x1F88 - 0x1F85];
#if VERSION == VERSION_DEMO
    /* 0x1F84 */ JPABaseEmitter* m1F84_demo;
#endif
    /* 0x1F88 */ dPa_smokeEcallBack m1F88;
    /* 0x1FA8 */ enemyice mEnemyIce;
    /* 0x2360 */ u32 mShadowId;
#if VERSION > VERSION_DEMO
    /* 0x2364 */ s8 m2364;
#endif
}; // Size: 0x2368

class HIO_c : public JORReflexible {
public:
    HIO_c() {
        m06 = 9;
        m08 = 0x2c;
        m0A = 0x15;
        m0C = 0x35;
        m10 = 6.0f;
        m14 = 7.0f;
        m18 = 0x46;
        m1A = 200;
    };
    virtual ~HIO_c() {};
    void genMessage(JORMContext*) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 m05[0x06 - 0x05];
    /* 0x06 */ s16 m06;
    /* 0x08 */ s16 m08;
    /* 0x0A */ s16 m0A;
    /* 0x0A */ s16 m0C;
    /* 0x0E */ u8 m0E[0x10 - 0x0E];
    /* 0x10 */ f32 m10;
    /* 0x14 */ f32 m14;
    /* 0x18 */ s16 m18;
    /* 0x1A */ s16 m1A;
}; // Size: 0x1C

#endif /* D_A_ST_H */
