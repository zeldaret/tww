#ifndef C_DAMAGEREACTION_H
#define C_DAMAGEREACTION_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "d/d_particle.h"

class mDoExt_McaMorf;
class JPABaseEmitter;

struct enemyice {
public:
    /* 0x000 */ fopAc_ac_c* mpActor;
    /* 0x004 */ s16 mFreezeDuration;
    /* 0x006 */ s8 mLightShrinkTimer;
    /* 0x007 */ u8 m007[0x008 - 0x007];
    /* 0x008 */ f32 mYOffset;
    /* 0x00C */ s8 m00C;
    /* 0x00D */ s8 mState;
    /* 0x00E */ s16 mFreezeTimer;
    /* 0x010 */ s16 mMoveDelayTimer;
    /* 0x012 */ s16 mAngleY;
    /* 0x014 */ s16 mAngularVelY;
    /* 0x016 */ u8 m016[0x018 - 0x016];
    /* 0x018 */ cXyz mSpeed;
    /* 0x024 */ f32 mSpeedF;
    /* 0x028 */ f32 m028;
    /* 0x02C */ f32 m02C;
    /* 0x030 */ dCcD_Stts mStts;
    /* 0x06C */ dCcD_Cyl mCyl;
    /* 0x19C */ f32 mCylHeight;
    /* 0x1A0 */ f32 mWallRadius;
    /* 0x1A4 */ f32 mScaleXZ;
    /* 0x1A8 */ f32 mScaleY;
    /* 0x1AC */ f32 mParticleScale;
    /* 0x1B0 */ u8 m1B0;
    /* 0x1B1 */ u8 mDeathSwitch;
    /* 0x1B2 */ u8 m1B2[0x1B4 - 0x1B2];
    /* 0x1B4 */ dBgS_AcchCir mBgAcchCir;
    /* 0x1F4 */ dBgS_ObjAcch mBgAcch;
};
STATIC_ASSERT(sizeof(enemyice) == 0x3B8);

struct enemyfire {
public:
    /* 0x000 */ fopAc_ac_c* mpActor;
    /* 0x004 */ s16 mFireDuration;
    /* 0x006 */ s8 mState;
    /* 0x007 */ u8 m007[0x008 - 0x007];
    /* 0x008 */ s16 mFireTimer;
    /* 0x00A */ u8 m00A[0x00C - 0x00A];
    /* 0x00C */ mDoExt_McaMorf* mpMcaMorf;
    /* 0x010 */ s8 mFlameJntIdxs[10];
    /* 0x01A */ u8 m01A[0x01C - 0x01A];
    /* 0x01C */ f32 mParticleScale[10];
    /* 0x044 */ s16 mFlameTimers[10];
    /* 0x058 */ JPABaseEmitter* mpFlameEmitters[10];
    /* 0x080 */ cXyz mPrevPos;
    /* 0x08C */ JGeometry::TVec3<f32> mDirection;
    /* 0x098 */ f32 mFlameScaleY;
    /* 0x09C */ u8 m09C[0x09D - 0x09C];
    /* 0x09D */ u8 mHitboxFlameIdx;
    /* 0x09E */ u8 m09E[0x0A0 - 0x09E];
    /* 0x0A0 */ dCcD_Stts mStts;
    /* 0x0DC */ dCcD_Sph mSph;
    /* 0x208 */ LIGHT_INFLUENCE mLight;
};
STATIC_ASSERT(sizeof(enemyfire) == 0x228);

struct damagereaction {
public:
    enum EnemyType {
        TYPE_MOBLIN = 1,
        TYPE_BOKOBLIN = 2,
        TYPE_DARKNUT = 3,
    };
    
    /* 0x000 */ fopEn_enemy_c* mpEnemy;
    /* 0x004 */ s16 m004;
    /* 0x006 */ s16 mState;
    /* 0x008 */ u16 mEnemyType;
    /* 0x00A */ u8 m00A[0x00C - 0x00A];
    /* 0x00C */ int mTimer;
    /* 0x010 */ csXyz m010[20];
    /* 0x088 */ csXyz m088[20];
    /* 0x100 */ cXyz m100[20];
    /* 0x1F0 */ cXyz m1F0[20];
    /* 0x2E0 */ cXyz m2E0[20];
    /* 0x3D0 */ u8 m3D0[0x410 - 0x3D0];
    /* 0x410 */ int m410;
    /* 0x414 */ u8 m414[0x418 - 0x414];
    /* 0x418 */ int m418;
    /* 0x41C */ u8 m41C[0x420 - 0x41C];
    /* 0x420 */ int m420;
    /* 0x424 */ int m424;
    /* 0x428 */ f32 m428;
    /* 0x42C */ cXyz m42C;
    /* 0x438 */ int m438;
    /* 0x43C */ u8 m43C[0x440 - 0x43C];
    /* 0x440 */ s16 m440;
    /* 0x442 */ s16 m442;
    /* 0x444 */ s16 m444;
    /* 0x446 */ u8 m446[0x448 - 0x446];
    /* 0x448 */ s16 m448;
    /* 0x44A */ u8 m44A[0x44C - 0x44A];
    /* 0x44C */ cXyz m44C;
    /* 0x458 */ cXyz m458;
    /* 0x464 */ u8 m464[0x468 - 0x464];
    /* 0x468 */ f32 m468;
    /* 0x46C */ f32 m46C;
    /* 0x470 */ f32 m470;
    /* 0x474 */ f32 m474;
    /* 0x478 */ f32 m478;
    /* 0x47C */ int m47C;
    /* 0x480 */ s16 m480;
    /* 0x482 */ s16 m482;
    /* 0x484 */ s16 m484;
    /* 0x486 */ s16 m486;
    /* 0x488 */ s16 m488;
    /* 0x48A */ s16 m48A;
    /* 0x48C */ csXyz m48C;
    /* 0x492 */ u8 m492[0x496 - 0x492];
    /* 0x496 */ s16 m496;
    /* 0x498 */ s16 m498;
    /* 0x49A */ s16 m49A;
    /* 0x49C */ s16 m49C;
    /* 0x49E */ s16 m49E;
    /* 0x4A0 */ s16 m4A0;
    /* 0x4A2 */ s16 m4A2;
    /* 0x4A4 */ s16 m4A4;
    /* 0x4A6 */ s16 m4A6;
    /* 0x4A8 */ s16 m4A8;
    /* 0x4AA */ s16 m4AA;
    /* 0x4AC */ s16 m4AC;
    /* 0x4AE */ s16 m4AE;
    /* 0x4B0 */ s16 m4B0;
    /* 0x4B2 */ s16 m4B2;
    /* 0x4B4 */ s16 m4B4;
    /* 0x4B6 */ s16 m4B6;
    /* 0x4B8 */ s16 m4B8;
    /* 0x4BA */ s16 m4BA;
    /* 0x4BC */ s16 m4BC;
    /* 0x4BE */ s16 m4BE;
    /* 0x4C0 */ s16 m4C0;
    /* 0x4C2 */ u8 m4C2[0x4C8 - 0x4C2];
    /* 0x4C8 */ s16 m4C8[3];
    /* 0x4CE */ s16 mInvincibleTimer;
    /* 0x4D0 */ s16 m4D0;
    /* 0x4D2 */ u8 m4D2[0x4D4 - 0x4D2];
    /* 0x4D4 */ f32 m4D4;
    /* 0x4D8 */ u8 m4D8[0x4DC - 0x4D8];
    /* 0x4DC */ dBgS_AcchCir mAcchCir;
    /* 0x51C */ dBgS_ObjAcch mAcch;
    /* 0x6E0 */ int m6E0;
    /* 0x6E4 */ f32 mSpawnY;
    /* 0x6E8 */ cXyz m6E8;
    /* 0x6F4 */ cXyz m6F4[2];
    /* 0x70C */ u8 m70C;
    /* 0x70D */ u8 m70D;
    /* 0x70E */ u8 m70E;
    /* 0x70F */ u8 m70F[0x710 - 0x70F];
    /* 0x710 */ u8 m710;
    /* 0x711 */ u8 m711[0x712 - 0x711];
    /* 0x712 */ u8 m712;
    /* 0x713 */ u8 m713;
    /* 0x714 */ fopAc_ac_c* m714;
    /* 0x718 */ u8 m718[0x71E - 0x718];
    /* 0x71E */ s16 m71E;
    /* 0x720 */ f32 mMaxFallDistance;
    /* 0x724 */ dCcD_Stts mStts;
    /* 0x760 */ cXyz mParticlePos;
    /* 0x76C */ csXyz mParticleAngle;
    /* 0x772 */ u8 m772[0x774 - 0x772];
    /* 0x774 */ dPa_smokeEcallBack mParticleCallBack;
    /* 0x794 */ s16 m794;
    /* 0x796 */ u8 m796[0x7A0 - 0x796];
    /* 0x7A0 */ cXyz m7A0;
    /* 0x7AC */ u8 m7AC[0x7AE - 0x7AC];
    /* 0x7AE */ s16 m7AE;
    /* 0x7B0 */ u8 m7B0[0x7B2 - 0x7B0];
    /* 0x7B2 */ s16 m7B2;
    /* 0x7B4 */ u8 m7B4[0x7B8 - 0x7B4];
    /* 0x7B8 */ int m7B8;
};
// STATIC_ASSERT(sizeof(damagereaction) == 0x7BC);

BOOL ice_bg_check(enemyice*);
BOOL enemy_ice(enemyice*);
void enemy_fire(enemyfire*);
void enemy_fire_remove(enemyfire*);
void enemy_piyo_set(fopAc_ac_c*);
void wall_angle_get(fopAc_ac_c*, s16);
void dr_body_bg_check(damagereaction*);
void dr_joint_bg_check(damagereaction*);
void kado_check(damagereaction*);
void hang_ang_get(damagereaction*);
void dr_damage_set(damagereaction*);
void dr_damage_anime(damagereaction*);
void dr_matrix_set(damagereaction*);
void damage_reaction(damagereaction*);

#endif /* C_DAMAGEREACTION_H */
