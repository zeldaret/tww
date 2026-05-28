#ifndef D_A_TN_H
#define D_A_TN_H

#include "d/d_jnt_hit.h"
#include "d/d_path.h"
#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "c/c_damagereaction.h"
#include "m_Do/m_Do_hostIO.h"

struct tn_p {
    /* 0x00 */ J3DModel* mpPartModel;
    /* 0x04 */ mDoExt_brkAnm* mpPartBrkAnm;
    /* 0x08 */ s8 m08;
    /* 0x09 */ s8 m09;
    /* 0x0A */ u8 m0A[0x0C - 0x0A];
    /* 0x0C */ cXyz m0C;
    /* 0x18 */ cXyz m18;
    /* 0x24 */ cXyz m24;
    /* 0x30 */ csXyz m30;
    /* 0x36 */ csXyz m36;
    /* 0x3C */ u8 m3C[0x42 - 0x3C];
    /* 0x42 */ s16 m42;
    /* 0x44 */ s8 m44;
    /* 0x45 */ u8 m45[0x4C - 0x45];
};

struct tn_class {
    /* 0x0000 */ fopEn_enemy_c actor;
    /* 0x02AC */ request_of_phase_process_class mPhaseTn;
    /* 0x02B4 */ request_of_phase_process_class mPhaseTkwn;
    /* 0x02BC */ u8 mBehaviorType;
    /* 0x02BD */ u8 mRangeOrFrozenAnim;
    /* 0x02BE */ u8 mPathIndex;
    /* 0x02BF */ u8 mEnableSpawnSwitch;
    /* 0x02C0 */ u8 mDisableSpawnOnDeathSwitch;
    /* 0x02C1 */ u8 m02C1;
    /* 0x02C2 */ u8 m02C2[0x02C4 - 0x02C2];
    /* 0x02C4 */ mDoExt_McaMorf* mpBodyMorf;
    /* 0x02C8 */ mDoExt_McaMorf* mpShieldMorf;
    /* 0x02CC */ mDoExt_McaMorf* mpArmorMorf;
    /* 0x02D0 */ u8 mRemainingEquipmentPieces;
    /* 0x02D1 */ u8 m02D1[0x02D4 - 0x02D1];
    /* 0x02D4 */ u32 mShadowId;
    /* 0x02D8 */ mDoExt_brkAnm* mpBrkAnm;
    /* 0x02DC */ u8 m02DC;
    /* 0x02DD */ s8 m02DD;
    /* 0x02DE */ u8 m02DE[0x02E0 - 0x02DE];
    /* 0x02E0 */ tn_p mParts[3];
    /* 0x03C4 */ u8 mArmorColorIndex;
    /* 0x03C5 */ u8 mEquipmentType;
    /* 0x03C6 */ u8 m03C6[0x03D8 - 0x03C6];
    /* 0x03D8 */ u32 m03D8;
    /* 0x03DC */ u8 m03DC[0x03E0 - 0x03DC];
    /* 0x03E0 */ s16 mCountDownTimers[5]; // 4 = mAttackIfCloseTimer
    /* 0x03EA */ s16 m03EA;
    /* 0x03EC */ s16 m03EC;
    /* 0x03EE */ s16 m03EE;
    /* 0x03F0 */ s16 m03F0;
    /* 0x03F2 */ s16 m03F2;
    /* 0x03F4 */ u8 m03F4[0x03FC - 0x03F4];
    /* 0x03FC */ s16 m03FC;
    /* 0x03FE */ u8 m03FE;
    /* 0x03FF */ u8 m03FF[0x0400 - 0x03FF];
    /* 0x0400 */ f32 mPlayerDistance;
    /* 0x0404 */ cXyz mPathXyz;
    /* 0x0410 */ u8 m0410[0x0414 - 0x0410];
#if VERSION == VERSION_DEMO
    /* 0x0414 */ s16 m0414_demo;
#endif
    /* 0x0414 */ s16 m0414;
    /* 0x0416 */ s16 mTargetAngle;
    /* 0x0418 */ s16 m0418;
    /* 0x041A */ s16 m041A;
    /* 0x041C */ cXyz m041C;
    /* 0x0428 */ csXyz m0428;
    /* 0x042E */ s16 m042E;
    /* 0x0430 */ s16 m0430;
    /* 0x0432 */ u8 m0432;
    /* 0x0433 */ u8 m0433;
    /* 0x0434 */ dPa_smokeEcallBack mSmokeCb1;
    /* 0x0454 */ dPa_smokeEcallBack mSmokeCb2;
    /* 0x0474 */ damagereaction mDamageReaction;
    /* 0x0C30 */ u8 m0C30[0x0C34 - 0x0C30];
    /* 0x0C34 */ int m0C34;
    /* 0x0C38 */ int m0C38;
    /* 0x0C3C */ cXyz m0C3C;
    /* 0x0C48 */ int m0C48;
    /* 0x0C4C */ u8 m0C4C[0x0C66 - 0x0C4C];
    /* 0x0C66 */ s8 m0C66;
    /* 0x0C67 */ s8 m0C67;
    /* 0x0C68 */ u8 m0C68[0x0C74 - 0x0C68];
    /* 0x0C74 */ dCcD_Cyl mCoCyl;
    /* 0x0DA4 */ dCcD_Cyl mTgCyl;
    /* 0x0ED4 */ dCcD_Sph mHeadSph;
    /* 0x1000 */ dCcD_Sph mDefenceSph;
    /* 0x112C */ dCcD_Sph mWeponSph;
    /* 0x1258 */ dCcD_Sph mWepon2Sph;
    /* 0x1384 */ cXyz m1384;
    /* 0x1390 */ cXyz m1390;
    /* 0x139C */ cXyz m139C;
    /* 0x13A8 */ cXyz m13A8;
    /* 0x13B4 */ cXyz m13B4;
    /* 0x13C0 */ cXyz mWeponSphMove;
    /* 0x13CC */ cXyz mWepon2SphMove;
    /* 0x13D8 */ cXyz m13D8;
    /* 0x13E4 */ cXyz m13E4;
    /* 0x13F0 */ u8 m13F0[0x13FC - 0x13F0];
    /* 0x13FC */ u8 m13FC;
    /* 0x13FD */ u8 m13FD;
    /* 0x13FE */ u8 m13FE[0x13FF - 0x13FE];
    /* 0x13FF */ u8 m13FF;
    /* 0x1400 */ s8 m1400;
    /* 0x1401 */ u8 m1401[0x1402 - 0x1401];
    /* 0x1402 */ s16 m1402;
    /* 0x1404 */ s16 m1404;
    /* 0x1406 */ u8 m1406[0x1408 - 0x1406];
    /* 0x1408 */ fpc_ProcID m1408;
    /* 0x140C */ s8 m140C;
    /* 0x140C */ u8 m140D[0x1410 - 0x140D];
    /* 0x1410 */ fpc_ProcID mBokoPcId;
    /* 0x1414 */ u8 m1414[0x1418 - 0x1414];
    /* 0x1418 */ fopAc_ac_c* m1418;
    /* 0x141C */ u16 m141C;
    /* 0x141E */ u8 m141E[0x1420 - 0x141E];
    /* 0x1420 */ s32 m1420;
    /* 0x1424 */ s8 m1424;
    /* 0x1425 */ s8 m1425;
    /* 0x1426 */ s8 m1426;
    /* 0x1427 */ u8 m1427[0x1428 - 0x1427];
    /* 0x1428 */ dPath* ppd;
    /* 0x142C */ u8 m142C[0x1430 - 0x142C];
    /* 0x1430 */ u8 mCapeEntityId;
    /* 0x1431 */ u8 m1431[0x1433 - 0x1431];
    /* 0x1433 */ u8 m1433;
    /* 0x1434 */ s8 m1434;
    /* 0x1435 */ u8 m1435[0x1436 - 0x1435];
    /* 0x1436 */ s16 m1436;
    /* 0x1438 */ cXyz m1438;
    /* 0x1444 */ s8 m1444;
    /* 0x1445 */ u8 m1445[0x1448 - 0x1445];
    /* 0x1448 */ fpc_ProcID mMantPcId;
    /* 0x144C */ dPa_cutTurnEcallBack_c m144C[3];
    /* 0x147C */ cXyz m147C[10];
    /* 0x14F4 */ s16 m14F4;
    /* 0x14F6 */ s16 m14F6;
    /* 0x14F8 */ s8 m14F8;
    /* 0x14F9 */ u8 m14F9[0x14FA - 0x14F9];
    /* 0x14FA */ s16 m14FA;
    /* 0x14FC */ cXyz mCameraEyePos;
    /* 0x1508 */ cXyz mCenterPos;
    /* 0x1514 */ f32 m1514;
    /* 0x1518 */ s8 m1518;
    /* 0x1519 */ s8 m1519;
    /* 0x151A */ u8 m151A[0x151C - 0x151A];
    /* 0x151C */ f32 m151C;
#if VERSION > VERSION_DEMO
    /* 0x1520 */ s8 m1520;
    /* 0x1521 */ u8 m1521[0x1524 - 0x1521];
#endif
    /* 0x1524 */ enemyice mEnemyIce;
    /* 0x18DC */ enemyfire mEnemyFire;
    /* 0x1B04 */ JntHit_c* mpJntHit;
}; // Size: 0x1B08

class tnHIO_c : public JORReflexible {
public:
    tnHIO_c() {
        m005 = 0;
        m006 = 0;
        m007 = 0;
        m008 = 0;
        m014 = 1.0f;
        m018 = 25.0f;
        m01E = 0xb9;
        m020 = 0xc;
        m01C = 0;
        m00A = 0x32;
        m00C = 1.0f;
        m024 = 50.0f;
        m028 = 1000.0f;
        m02C = 400.0f;
        m030 = 250.0f;
        m034 = 23000;
        m036 = 11000;
        m038 = 400.0f;
        m03C = 500.0f;
        m040 = 130.0f;
        m044 = 500.0f;
        m048 = -125.0f;
        m04C = 20.0f;
        m050 = 20.0f;
        m054 = 70.0f;
        m058 = 90.0f;
        m05C = 10.0f;
        m060 = 10.0f;
        m064 = 70.0f;
        m068 = 1.0f;
        m06C = 0x1e;
        m070 = 75.0f;
        m074 = 40.0f;
        m078 = 40.0f;
        m07C = 70.0f;
        m080 = 0x1e;
        m082 = 300;
        m084 = 0.9f;
        m088 = 1.0f;
        m08C = 1.0f;
        m0C4 = 0xe;
        m090 = 1.0f;
        m094 = 1.0f;
        m098 = 1.0f;
        m0C6 = 0x18;
        m09C = 1.1f;
        m0A0 = 1.0f;
        m0A4 = 1.0f;
        m0C8 = 0x16;
        m0A8 = 0.5f;
        m0AC = 1.0f;
        m0B0 = 1.2f;
        m0CA = 5;
        m0B4 = 1.0f;
        m0CC = 100;
        m0B8 = 1.0f;
        m0BC = 1.0f;
        m0C0 = 1.0f;
        m0CE = 0x1c;
        m0D0 = 0.0f;
        m0D4 = 500.0f;
    };
    virtual ~tnHIO_c() {};
    void genMessage(JORMContext*) {}

public:
    /* 0x004 */ s8 mNo;
    /* 0x005 */ u8 m005;
    /* 0x006 */ u8 m006;
    /* 0x007 */ u8 m007;
    /* 0x008 */ u8 m008;
    /* 0x009 */ u8 m009[0x00A - 0x009];
    /* 0x00A */ s16 m00A;
    /* 0x00C */ f32 m00C;
    /* 0x010 */ u8 m010[0x014 - 0x010];
    /* 0x014 */ f32 m014;
    /* 0x018 */ f32 m018;
    /* 0x01C */ s16 m01C;
    /* 0x01E */ s16 m01E;
    /* 0x020 */ s16 m020;
    /* 0x022 */ u8 m022[0x024 - 0x022];
    /* 0x024 */ f32 m024;
    /* 0x028 */ f32 m028;
    /* 0x02C */ f32 m02C;
    /* 0x030 */ f32 m030;
    /* 0x034 */ s16 m034;
    /* 0x036 */ s16 m036;
    /* 0x038 */ f32 m038;
    /* 0x03C */ f32 m03C;
    /* 0x040 */ f32 m040;
    /* 0x040 */ f32 m044;
    /* 0x040 */ f32 m048;
    /* 0x04C */ f32 m04C;
    /* 0x050 */ f32 m050;
    /* 0x054 */ f32 m054;
    /* 0x058 */ f32 m058;
    /* 0x05C */ f32 m05C;
    /* 0x060 */ f32 m060;
    /* 0x064 */ f32 m064;
    /* 0x068 */ f32 m068;
    /* 0x06C */ s16 m06C;
    /* 0x06E */ u8 m06E[0x070 - 0x06E];
    /* 0x070 */ f32 m070;
    /* 0x074 */ f32 m074;
    /* 0x078 */ f32 m078;
    /* 0x07C */ f32 m07C;
    /* 0x080 */ s16 m080;
    /* 0x082 */ s16 m082;
    /* 0x084 */ f32 m084;
    /* 0x088 */ f32 m088;
    /* 0x08C */ f32 m08C;
    /* 0x090 */ f32 m090;
    /* 0x094 */ f32 m094;
    /* 0x098 */ f32 m098;
    /* 0x09C */ f32 m09C;
    /* 0x0A0 */ f32 m0A0;
    /* 0x0A4 */ f32 m0A4;
    /* 0x0A8 */ f32 m0A8;
    /* 0x0AC */ f32 m0AC;
    /* 0x0B0 */ f32 m0B0;
    /* 0x0B4 */ f32 m0B4;
    /* 0x0B8 */ f32 m0B8;
    /* 0x0BC */ f32 m0BC;
    /* 0x0C0 */ f32 m0C0;
    /* 0x0C4 */ s16 m0C4;
    /* 0x0C6 */ s16 m0C6;
    /* 0x0C8 */ s16 m0C8;
    /* 0x0CA */ s16 m0CA;
    /* 0x0CC */ s16 m0CC;
    /* 0x0CE */ s16 m0CE;
    /* 0x0D0 */ f32 m0D0;
    /* 0x0D4 */ f32 m0D4;
    /* 0x0D8 */ JntHit_HIO_c mJntHitHIO;
}; // Size: 0x104

#endif /* D_A_TN_H */
