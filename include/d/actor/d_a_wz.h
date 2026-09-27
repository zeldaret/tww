#ifndef D_A_WZ_H
#define D_A_WZ_H

#include "c/c_damagereaction.h"
#include "d/d_bg_s_acch.h"
#include "d/d_path.h"
#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "m_Do/m_Do_ext.h"

struct wz_class {
    /* 0x000 */ fopEn_enemy_c actor;
    /* 0x2AC */ request_of_phase_process_class mPhase;
    /* 0x2B4 */ mDoExt_McaMorf* mpMorf;
    /* 0x2B8 */ mDoExt_McaMorf* mpWandMorf;
    /* 0x2BC */ mDoExt_McaMorf* mpMaskMorf;
    /* 0x2C0 */ mDoExt_brkAnm* mpBrkAnm;
    /* 0x2C4 */ mDoExt_btkAnm* mpBtkAnm;
    /* 0x2C8 */ u8 m2C8[0x2CC - 0x2C8];
    /* 0x2CC */ Mtx m2CC;
    /* 0x2FC */ cXyz m2FC;
    /* 0x308 */ cXyz m308;
    /* 0x314 */ cXyz m314;
    /* 0x320 */ cXyz m320;
    /* 0x32C */ cXyz m32C;
    /* 0x338 */ cXyz m338;
    /* 0x344 */ fpc_ProcID m344;
    /* 0x348 */ u8 mBehaviorType;
    /* 0x349 */ u8 mEnemySummonTableIndex;
    /* 0x34A */ u8 mEnableSpawnSwitch;
    /* 0x34B */ u8 mDisableSpawnOnDeathSwitch;
    /* 0x34C */ u8 mAction;
    /* 0x34D */ u8 mMode;
    /* 0x34E */ u8 mHitType;
    /* 0x34F */ u8 m34F;
    /* 0x350 */ bool mIsMiniBoss;
    /* 0x351 */ bool m351;
    /* 0x352 */ u8 m352;
    /* 0x353 */ u8 m353;
    /* 0x354 */ u8 m354;
    /* 0x355 */ u8 m355[0x358 - 0x355];
    /* 0x358 */ s32 m358;
    /* 0x35C */ fpc_ProcID m35C[20];
    /* 0x3AC */ u8 m3AC[20];
    /* 0x3C0 */ u8 m3C0[20];
    /* 0x3D4 */ s16 m3D4[5];
    /* 0x3DE */ s16 m3DE[4];
    /* 0x3E6 */ s16 m3E6;
    /* 0x3E8 */ s16 m3E8;
    /* 0x3EA */ s16 m3EA;
    /* 0x3EC */ s32 m3EC;
    /* 0x3F0 */ u32 m3F0;
    /* 0x3F4 */ s16 m3F4;
    /* 0x3F6 */ s16 m3F6;
    /* 0x3F8 */ u8 m3F8;
    /* 0x3F9 */ u8 m3F9[0x3FC - 0x3F9];
    /* 0x3FC */ u32 mShadowId;
    /* 0x400 */ int m400;
    /* 0x404 */ f32 m404;
    /* 0x408 */ f32 m408;
    /* 0x40C */ f32 m40C;
    /* 0x410 */ f32 m410;
    /* 0x414 */ dPath* mPath;
    /* 0x418 */ u8 m418[0x425 - 0x418];
    /* 0x425 */ u8 mPathIndex;
    /* 0x426 */ u8 m426[0x428 - 0x426];
    /* 0x428 */ dPath* mNextPath;
    /* 0x426 */ u8 m42C[0x439 - 0x42C];
    /* 0x439 */ u8 m439;
    /* 0x43A */ u8 m43A[0x43C - 0x43A];
    /* 0x43C */ cXyz m43C;
    /* 0x448 */ cXyz m448;
    /* 0x454 */ u8 m454[0x464 - 0x454];
    /* 0x464 */ f32 m464;
    /* 0x468 */ dBgS_AcchCir mAcchCir;
    /* 0x4A8 */ dBgS_ObjAcch mAcch;
    /* 0x66C */ dCcD_Stts mStts;
    /* 0x6A8 */ dCcD_Cyl mBodyCoCyl;
    /* 0x7D8 */ dCcD_Sph mBallCoSph;
    /* 0x904 */ LIGHT_INFLUENCE mLightInfluence;
    /* 0x924 */ enemyice mEnemyIce;
    /* 0xCDC */ enemyfire mEnemyFire;
    /* 0xF04 */ cXyz mF04;
    /* 0xF10 */ csXyz mF10;
    /* 0xF16 */ u8 mF16[0xF18 - 0xF16];
    /* 0xF18 */ dPa_followEcallBack mF18;
    /* 0xF2C */ dPa_followEcallBack mF2C;
    /* 0xF40 */ dPa_followEcallBack mF40;
    /* 0xF54 */ dPa_followEcallBack mF54;
    /* 0xF68 */ dPa_followEcallBack mF68;
    /* 0xF7C */ mDoExt_invisibleModel mInvisibleModel;
    /* 0xF84 */ mDoExt_invisibleModel mMaskInvisibleModel;
}; // Size: 0xF8C

#endif /* D_A_WZ_H */
