#ifndef D_A_PW_H
#define D_A_PW_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "d/d_particle.h"
#include "c/c_damagereaction.h"

class pw_class : public fopEn_enemy_c {
public:
    /* 0x2AC */ u8 m2AC[0x2B4 - 0x2AC];
    /* 0x2B4 */ mDoExt_McaMorf* m2B4;
    /* 0x2B8 */ u8 m2B8[0x32C - 0x2B8];
    /* 0x32C */ csXyz m32C[2];
    /* 0x338 */ u8 mBehaviorType;
    /* 0x339 */ bool mHoversAtInitialYPos;
    /* 0x33A */ u8 mNoticeRangeParam;
    /* 0x33B */ u8 mColorIndex;
    /* 0x33C */ u8 mHitByWhat;
    /* 0x33D */ u8 m33D[0x33E - 0x33D];
    /* 0x33E */ u8 m33E;
    /* 0x33F */ u8 m33F[0x344 - 0x33F];
    /* 0x344 */ u8 m344;
    /* 0x345 */ u8 m345;
    /* 0x346 */ u8 m346[0x359 - 0x346];
    /* 0x359 */ u8 mPathIndex;
    /* 0x35A */ u8 m35A[0x366 - 0x35A];
    /* 0x366 */ s16 m366;
    /* 0x368 */ s16 m368;
    /* 0x36A */ u8 m36A[0x36C - 0x36A];
    /* 0x36C */ int mJalhallaParentId;
    /* 0x370 */ u8 m370[0x374 - 0x370];
    /* 0x374 */ u32 m374;
    /* 0x378 */ s16 m378;
    /* 0x37A */ u8 m37A[0x384 - 0x37A];
    /* 0x384 */ s16 m384[4];
    /* 0x38C */ s16 m38C;
    /* 0x38E */ s16 m38E;
    /* 0x390 */ u8 m390[0x39A - 0x390];
    /* 0x39A */ s16 m39A;
    /* 0x39C */ u8 m39C[0x3A8 - 0x39C];
    /* 0x3A8 */ f32 mNoticeRange;
    /* 0x3AC */ u8 m3AC[0x3BC - 0x3AC];
    /* 0x3BC */ dBgS_AcchCir m3BC;
    /* 0x3FC */ dBgS_Acch m3FC;
    /* 0x5C0 */ u8 m5C0[0x5C4 - 0x5C0];
    /* 0x5C4 */ dPa_followEcallBack m5C4;
    /* 0x5D8 */ u8 m5D8[0x608 - 0x5D8];
    /* 0x608 */ dCcD_GStts m608;
    /* 0x628 */ dCcD_GObjInf m628;
    /* 0x720 */ u8 m720[0x758 - 0x720];
    /* 0x758 */ dCcD_GObjInf m758;
    /* 0x850 */ u8 m850[0x884 - 0x850];
    /* 0x884 */ enemyice mEnemyIce;
    /* 0xC3C */ u8 mC3C[0xCF8 - 0xC3C];
    /* 0xCF8 */ dCcD_GStts mCF8;
    /* 0xD18 */ dCcD_GObjInf mD18;
    /* 0xE10 */ u8 mE10[0xE6C - 0xE10];
};

#endif /* D_A_PW_H */
