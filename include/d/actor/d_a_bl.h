#ifndef D_A_BL_H
#define D_A_BL_H

#include "c/c_damagereaction.h"
#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "d/d_path.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

struct bl_class {
    /* 0x000 */ fopEn_enemy_c actor;
    /* 0x2AC */ request_of_phase_process_class mPhase;
    /* 0x2B4 */ mDoExt_McaMorf* mpMorf;
    /* 0x2B8 */ u8 field_0x2B8[0x2BC - 0x2B8];
    /* 0x2BC */ mDoExt_btkAnm* m2BC;
    /* 0x2C0 */ mDoExt_btkAnm* m2C0;
    /* 0x2C4 */ cXyz m2C4;
    /* 0x2D0 */ u8 m2D0;
    /* 0x2D1 */ u8 m2D1;
    /* 0x2D2 */ u8 mAction;
    /* 0x2D3 */ u8 m2D3;
    /* 0x2D4 */ u8 mHitType;
    /* 0x2D5 */ u8 m2D5;
    /* 0x2D6 */ u8 field_0x2D6[0x2D8 - 0x2D6];
    /* 0x2D8 */ dPath* mpPath;
    /* 0x2DC */ u8 field_0x2DC[0x2E8 - 0x2DC];
    /* 0x2E8 */ s8 m2E8;
    /* 0x2E9 */ u8 m2E9;
    /* 0x2EA */ s8 m2EA;
    /* 0x2EB */ u8 field_0x2EB[0x2EC - 0x2EB];
#if VERSION == VERSION_DEMO
    /* 0x2EC */ s16 m2EC[5];
    /* 0x2F8 */ s16 m2F8[3];
#elif VERSION == VERSION_JPN
    /* 0x2EC */ s16 m2EC[6];
    /* 0x2F8 */ s16 m2F8[3];
#else
    /* 0x2EC */ s16 m2EC[6];
    /* 0x2F8 */ s16 m2F8[4];
#endif
    /* 0x300 */ s16 m300;
    /* 0x302 */ s16 m302;
    /* 0x304 */ s16 m304;
    /* 0x306 */ s16 mMode;
    /* 0x308 */ int mCurrBckIdx;
    /* 0x30C */ u8 field_0x30C[0x310 - 0x30C];
    /* 0x310 */ f32 m310;
    /* 0x314 */ f32 m314;
    /* 0x318 */ f32 m318;
    /* 0x31C */ f32 m31C;
    /* 0x320 */ f32 m320;
    /* 0x324 */ f32 m324;
    /* 0x328 */ f32 m328;
    /* 0x32C */ dBgS_AcchCir mAcchCir;
    /* 0x36C */ dBgS_ObjAcch mAcch;
    /* 0x530 */ dCcD_Stts mStts;
    /* 0x56C */ dCcD_Sph mBodyCoSph;
    /* 0x698 */ cXyz m698[3];
    /* 0x6BC */ union {
        csXyz m6BC_csXyz[2];
        cXyz m6BC_cXyz;
    };
    /* 0x6C8 */ dPa_smokeEcallBack m6C8;
    /* 0x6E8 */ dPa_followEcallBack m6E8;
    /* 0x6FC */ dPa_followEcallBack m6FC;
    /* 0x710 */ enemyice mEnemyIce;
    /* 0xAC8 */ enemyfire mEnemyFire;
    /* 0xCF0 */ mDoExt_invisibleModel mInvisibleModel;
}; // Size: 0xCF8

#endif /* D_A_BL_H */
