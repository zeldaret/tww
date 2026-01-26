#ifndef D_A_KI_H
#define D_A_KI_H

#include "f_op/f_op_actor.h"
#include "c/c_damagereaction.h"
#include "d/d_particle.h"

class mDoExt_McaMorf;
class mDoExt_btkAnm;
class dPath;
class J3DTexNoAnm;

struct ki_class {
    enum Action_e {
        ACT_WAIT_MOVE_e         = 0,
        ACT_FLY_MOVE_e          = 1,
        ACT_FIRE_SET_MOVE_e     = 2,
        ACT_ATTACK_MOVE_e       = 3,
        ACT_ATTACK_MOVE_INDEX_e = 10,
        ACT_DAMAGE_MOVE_e       = 20,
        ACT_FAIL_MOVE_e         = 30,
    };

    /* 0x000 */ fopEn_enemy_c actor;
    /* 0x2AC */ request_of_phase_process_class mPhase;
    /* 0x2B4 */ mDoExt_McaMorf* mpMorf;
    /* 0x2B8 */ mDoExt_J3DModelPacketS m2B8;
    /* 0x2C8 */ u8 m2C8[0x2CC - 0x2C8];
    /* 0x2CC */ u8 mParameters;
    /* 0x2CD */ u8 m2CD;
    /* 0x2CE */ u8 mKiPathIndex;
    /* 0x2CF */ u8 m2CF;
    /* 0x2D0 */ u8 m2D0[0x2D1 - 0x2D0];
    /* 0x2D1 */ u8 mAction;
    /* 0x2D2 */ u8 m2D2[0x2D3 - 0x2D2];
    /* 0x2D3 */ s8 mBehaviorType;
    /* 0x2D4 */ u8 m2D4;
    /* 0x2D5 */ s8 mCurrKiPathIndex;
    /* 0x2D6 */ s8 m2D6;
    /* 0x2D7 */ s8 m2D7;
    /* 0x2D8 */ dPath* ppd;
    /* 0x2DC */ u8 m2DC;
#if VERSION > VERSION_DEMO
    /* 0x2E0 */ s32 m2E0;
#endif
    /* 0x2E4 */ f32 mMaxAttackMoveDist300;
    /* 0x2E8 */ cXyz mPosMove;
    /* 0x2F4 */ f32 mPosMoveTarget;
    /* 0x2F8 */ f32 mPosMoveMaxSpeed;
    /* 0x2FC */ f32 mPosMoveDist;
    /* 0x300 */ u8 m300[0x304 - 0x300];
    /* 0x304 */ f32 m304;
    /* 0x308 */ u8 m308[0x30C - 0x308];
    /* 0x30C */ s16 mTimers[4];
    /* 0x314 */ s16 m314;
    /* 0x316 */ s16 m316;
    /* 0x318 */ s16 mRand2000;
    /* 0x31C */ f32 m31C;
    /* 0x320 */ s16 m320;
    /* 0x322 */ s16 m322;
    /* 0x324 */ s16 m324;
    /* 0x326 */ s16 m326;
    /* 0x328 */ s16 m328;
    /* 0x32C */ J3DAnmTexPattern* m32C;
    /* 0x330 */ J3DTexNoAnm* m330;
    /* 0x334 */ u8 m334;
    /* 0x335 */ u8 m335;
    /* 0x336 */ u8 m336;
    /* 0x337 */ u8 m337;
    /* 0x338 */ s8 m338;
    /* 0x339 */ s8 m339;
    /* 0x33A */ u8 m33A[0x33C - 0x33A];
    /* 0x33C */ dBgS_AcchCir mAcchCir;
    /* 0x37C */ dBgS_ObjAcch mAcch;
    /* 0x540 */ u8 m540;
    /* 0x544 */ dCcD_Stts mStts;
    /* 0x580 */ dCcD_Sph m580;
    /* 0x6AC */ dCcD_Sph m6AC;
    /* 0x7D8 */ dCcD_Sph mDamageSphere;
    /* 0x904 */ u8 m904;
    /* 0x905 */ u8 mDamageType;
    /* 0x908 */ dPa_followEcallBack m908;
    /* 0x91C */ JPABaseEmitter* m91C;
    /* 0x920 */ mDoExt_btkAnm* m920;
    /* 0x924 */ enemyice mEnemyIce;
    /* 0xCDC */ enemyfire mEnemyFire;
}; // size = 0xF04

#endif /* D_A_KI_H */
