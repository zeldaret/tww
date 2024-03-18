#ifndef D_A_PW_H
#define D_A_PW_H

#include "c/c_damagereaction.h"
#include "d/d_bg_s_acch.h"
#include "d/d_path.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"

class pw_class : public fopEn_enemy_c {
public:
    /* 0x2AC */ request_of_phase_process_class mPhase;
    /* 0x2B4 */ mDoExt_McaMorf* mpMorf;
    /* 0x2B8 */ u8 m2B8[0x2BC - 0x2B8];
    /* 0x2BC */ mDoExt_btpAnm* m2BC;
    /* 0x2C0 */ mDoExt_brkAnm* m2C0;
    /* 0x2C4 */ mDoExt_brkAnm* m2C4;
    /* 0x2C8 */ mDoExt_brkAnm* m2C8;
    /* 0x2CC */ cXyz m2CC;
    /* 0x2D8 */ cXyz m2D8;
    /* 0x2E4 */ cXyz m2E4;
    /* 0x2F0 */ cXyz m2F0;
    /* 0x2FC */ cXyz m2FC;
    /* 0x308 */ cXyz m308;
    /* 0x314 */ cXyz m314;
    /* 0x320 */ cXyz m320;
    /* 0x32C */ csXyz m32C[2];
    /* 0x338 */ u8 mBehaviorType;
    /* 0x339 */ bool mHoversAtInitialYPos;
    /* 0x33A */ u8 mNoticeRangeParam;
    /* 0x33B */ u8 mColorIndex;
    /* 0x33C */ u8 mHitByWhat;
    /* 0x33D */ u8 m33D[0x33E - 0x33D];
    /* 0x33E */ u8 m33E;
    /* 0x33F */ u8 m33F;
    /* 0x340 */ u8 m340;
    /* 0x341 */ u8 m341;
    /* 0x342 */ u8 m342;
    /* 0x343 */ u8 m343;
    /* 0x344 */ u8 m344;
    /* 0x345 */ u8 m345;
    /* 0x346 */ s16 m346;
    /* 0x348 */ dPath* mpPath;
    /* 0x34C */ u8 m34C[0x358 - 0x34C];
    /* 0x358 */ s8 mPathPntIdx;
    /* 0x359 */ u8 mPathIndex;
    /* 0x35A */ u8 m35A[0x366 - 0x35A];
    /* 0x366 */ s16 mAction;
    /* 0x368 */ s16 mState;
    /* 0x36A */ u8 m36A[0x36C - 0x36A];
    /* 0x36C */ uint mJalhallaID;
    /* 0x370 */ uint mKanteraID;
    /* 0x374 */ int mBckIdx;
    /* 0x378 */ s16 m378;
    /* 0x37A */ s16 m37A;
    /* 0x37C */ s16 m37C;
    /* 0x37E */ s16 m37E;
    /* 0x380 */ s16 m380;
    /* 0x382 */ s16 m382;
    /* 0x384 */ s16 m384[4];
    /* 0x38C */ s16 m38C;
    /* 0x38E */ s16 m38E;
    /* 0x390 */ s16 m390;
    /* 0x392 */ u8 m392[0x398 - 0x392];
    /* 0x398 */ s16 m398;
    /* 0x39A */ s16 m39A;
    /* 0x39C */ s16 m39C;
    /* 0x39E */ s16 m39E;
    /* 0x3A0 */ f32 mCorrectionOffsetY;
    /* 0x3A4 */ f32 m3A4;
    /* 0x3A8 */ f32 mNoticeRange;
    /* 0x3AC */ f32 m3AC;
    /* 0x3B0 */ f32 m3B0;
    /* 0x3B4 */ u8 m3B4[0x3BC - 0x3B4];
    /* 0x3BC */ dBgS_AcchCir mAcchCir;
    /* 0x3FC */ dBgS_ObjAcch mAcch;
    /* 0x5C0 */ u8 m5C0[0x5C4 - 0x5C0];
    /* 0x5C4 */ dPa_followEcallBack m5C4;
    /* 0x5D8 */ actor_place mActorPlace;
    /* 0x5EC */ dCcD_Stts mStts;
    /* 0x628 */ dCcD_Cyl mCyl;
    /* 0x758 */ dCcD_Sph mSph;
    /* 0x884 */ enemyice mEnemyIce;
    /* 0xC3C */ enemyfire mEnemyFire;
    /* 0xE64 */ mDoExt_invisibleModel mInvisibleModel;
};  // Size: 0xE6C

#endif /* D_A_PW_H */
