#ifndef D_A_MO2_H
#define D_A_MO2_H

#include "d/d_jnt_hit.h"
#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "c/c_damagereaction.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_path.h"
#include "m_Do/m_Do_hostIO.h"

struct ke_s {
    /* 0x000 */ cXyz m000[10];
    /* 0x078 */ cXyz m078[10];
    /* 0x0F0 */ u8 m0F0[0x124 - 0x0F0];
}; // Size: 0x124

// Note: copy-pasted from "h3_ga_s" (doesn't seem to be used?)
struct ga_s {
    /* 0x00 */ J3DModel* mpModel;
    /* 0x04 */ cXyz mPos;
    /* 0x04 */ cXyz m10;
    /* 0x1C */ s16 m1C;
    /* 0x1E */ s16 m1E;
    /* 0x20 */ u8 m20[0x24 - 0x20];
    /* 0x24 */ f32 m24;
    /* 0x28 */ f32 m28;
    /* 0x2C */ s16 m2C;
    /* 0x2E */ u8 m2E;
    /* 0x2F */ u8 m2F;
}; // Size: 0x30

struct mo2_class {
    enum Action_e {
        Action_JYUNKAI_e = 0,
        Action_FIGHT_RUN_e = 4,
        Action_FIGHT_e = 5,
        Action_NAGE_e = 6,
        Action_OSHI_e = 7,
        Action_P_LOST_e = 8,
        Action_B_NIGE_e = 9,
        Action_DEFENCE_e = 10,
        Action_HUKKI_e = 11,
        Action_WEPON_SEARCH_e = 12,
        Action_HIP_DAMAGE_e = 13,
        Action_AITE_MIRU_e = 14,
        Action_D_SIT_e = 17,
        Action_D_MAHI_e = 18,
        Action_FAIL_e = 20,
        Action_YOGAN_FAIL_e = 21,
        Action_D_DOZOU_e = 23,
        Action_CARRY_e = 30,
        Action_CARRY_DROP_e = 31,
        Action_E3_DEMO_e = 40,
    };

    /* 0x0000 */ fopEn_enemy_c actor;
    /* 0x02AC */ request_of_phase_process_class mPhsMo2;
    /* 0x02B4 */ request_of_phase_process_class mPhsSpear;
    /* 0x02BC */ u8 mMode;
    /* 0x02BD */ u8 mFrozenInTimePose;
    /* 0x02BE */ u8 mPathIndex;
    /* 0x02BF */ u8 mEnableSpawnSwitch;
    /* 0x02C0 */ u8 mDeathSwitch;
    /* 0x02C1 */ u8 m02C1;
    /* 0x02C2 */ u8 m02C2[0x02C4 - 0x02C2];
    /* 0x02C4 */ mDoExt_McaMorf* mpMorf;
    /* 0x02C8 */ mDoExt_btpAnm m02C8;
    /* 0x02DC */ u8 m02DC;
    /* 0x02DD */ u8 m02DD;
    /* 0x02DE */ u8 m02DE;
    /* 0x02DF */ u8 m02DF[0x02E0 - 0x02DF];
    /* 0x02E0 */ s16 m02E0;
    /* 0x02E2 */ s16 m02E2;
    /* 0x02E4 */ int mShadowHandle;
    /* 0x02E8 */ fpc_ProcID m02E8;
    /* 0x02EC */ u8 m02EC[0x0570 - 0x02EC];
    /* 0x0570 */ mDoExt_3DlineMat0_c m0570;
    /* 0x058C */ J3DModel* m058C;
    /* 0x0590 */ f32 m0590;
    /* 0x0594 */ int m0594;
    /* 0x0598 */ int m0598;
    /* 0x059C */ int m059C;
    /* 0x05A0 */ int m05A0;
    /* 0x05A4 */ s16 m05A4[5];
    /* 0x05AE */ s16 m05AE;
    /* 0x05B0 */ s16 m05B0;
    /* 0x05B2 */ s16 m05B2;
    /* 0x05B4 */ s16 m05B4;
    /* 0x05B6 */ s16 m05B6;
    /* 0x05B8 */ u8 m05B8[0x05BA - 0x05B8];
    /* 0x05BA */ s16 m05BA;
    /* 0x05BC */ s16 m05BC;
    /* 0x05BE */ u8 m05BE;
    /* 0x05BF */ u8 m05BF;
    /* 0x05C0 */ f32 m05C0;
    /* 0x05C4 */ cXyz m05C4;
    /* 0x05D0 */ u8 m05D0[0x05D4 - 0x05D0];
    /* 0x05D4 */ s16 m05D4;
    /* 0x05D6 */ s16 m05D6;
    /* 0x05D8 */ s16 m05D8;
    /* 0x05DA */ s16 m05DA;
    /* 0x05DC */ cXyz m05DC;
    /* 0x05E8 */ csXyz m05E8;
    /* 0x05EE */ s16 m05EE;
    /* 0x05F0 */ s16 m05F0;
    /* 0x05F2 */ u8 m05F2;
    /* 0x05F3 */ u8 m05F3;
    /* 0x05F4 */ dPa_smokeEcallBack m05F4;
    /* 0x0614 */ damagereaction mDamageReaction;
    /* 0x0DD0 */ u8 m0DD0[0x0DD4 - 0x0DD0];
    /* 0x0DD4 */ s8 mbHasInnateWeapon;
    /* 0x0DD5 */ s8 mSpawnWeaponActor;
    /* 0x0DD6 */ s8 mSpawnWeaponActorMode;
    /* 0x0DD7 */ s8 mbThrowWeapon;
    /* 0x0DD8 */ ke_s m0DD8[16];
    /* 0x2018 */ mDoExt_3DlineMat0_c m3Dline;
    /* 0x2034 */ cXyz m2034;
    /* 0x2040 */ cXyz m2040[2];
    /* 0x2058 */ u8 m2058[0x2060 - 0x2058];
    /* 0x2060 */ int m2060;
    /* 0x2064 */ int m2064;
    /* 0x2068 */ f32 m2068;
    /* 0x206C */ f32 m206C;
    /* 0x2070 */ f32 m2070;
    /* 0x2074 */ f32 m2074;
    /* 0x2078 */ f32 m2078;
    /* 0x207C */ s16 m207C;
    /* 0x207E */ s8 m207E;
    /* 0x207F */ u8 m207F[0x208C - 0x207F];
    /* 0x208C */ dCcD_Cyl mCoCyl;
    /* 0x21BC */ dCcD_Cyl mTgCyl;
    /* 0x22EC */ dCcD_Sph mHeadSph;
    /* 0x2418 */ dCcD_Sph mDefenseSph;
    /* 0x2544 */ dCcD_Sph mWeaponSph;
    /* 0x2670 */ dCcD_Sph mWeapon2Sph;
    /* 0x279C */ dCcD_Sph m279C;
    /* 0x28C8 */ cXyz m28C8;
    /* 0x28D4 */ cXyz m28D4;
    /* 0x28E0 */ cXyz m28E0;
    /* 0x28EC */ cXyz m28EC;
    /* 0x28F8 */ cXyz m28F8;
    /* 0x2904 */ cXyz m2904;
    /* 0x2910 */ cXyz m2910;
    /* 0x291C */ cXyz m291C;
    /* 0x2928 */ cXyz m2928;
    /* 0x2934 */ cXyz m2934;
    /* 0x2940 */ u8 m2940;
    /* 0x2941 */ u8 m2941;
    /* 0x2942 */ u8 m2942;
    /* 0x2943 */ u8 m2943;
    /* 0x2944 */ s16 m2944;
    /* 0x2946 */ s16 m2946;
    /* 0x2948 */ s16 m2948;
    /* 0x294A */ s16 m294A;
    /* 0x294C */ s16 m294C;
    /* 0x294E */ s16 m294E;
    /* 0x2950 */ u8 mParryOpeningType;
    /* 0x2951 */ s8 m2951;
    /* 0x2952 */ s16 m2952;
    /* 0x2954 */ fpc_ProcID m2954;
    /* 0x2958 */ fpc_ProcID mWeaponPcId;
    /* 0x295C */ fopAc_ac_c* mpBomb;
    /* 0x2960 */ u16 m2960;
    /* 0x2962 */ u8 m2962[0x2964 - 0x2962];
    /* 0x2964 */ int m2964;
    /* 0x2968 */ s8 m2968;
    /* 0x2969 */ s8 m2969;
    /* 0x296A */ s8 mHasPath;
    /* 0x296B */ u8 m296B[0x296C - 0x296B];
    /* 0x296C */ dPath* ppd;
    /* 0x2970 */ s8 m2970;
    /* 0x2971 */ u8 m2971[0x2978 - 0x2971];
    /* 0x2978 */ ga_s m2978[3];
    /* 0x2A08 */ s8 m2A08;
    /* 0x2A09 */ u8 m2A09;
    /* 0x2A0A */ u8 m2A0A;
    /* 0x2A0B */ s8 m2A0B;
    /* 0x2A0C */ s16 m2A0C;
    /* 0x2A0E */ u8 m2A0E[0x2A10 - 0x2A0E];
    /* 0x2A10 */ cXyz m2A10;
    /* 0x2A1C */ s8 m2A1C;
    /* 0x2A1D */ s8 m2A1D;
    /* 0x2A1E */ s16 m2A1E;
    /* 0x2A20 */ cXyz m2A20;
    /* 0x2A2C */ cXyz m2A2C;
    /* 0x2A38 */ f32 m2A38;
    /* 0x2A3C */ f32 m2A3C;
    /* 0x2A40 */ f32 m2A40;
    /* 0x2A44 */ f32 m2A44;
    /* 0x2A48 */ s16 m2A48;
    /* 0x2A4A */ u8 m2A4A;
    /* 0x2A4B */ u8 m2A4B;
    /* 0x2A4C */ s16 m2A4C;
    /* 0x2A4E */ u8 m2A4E[0x2A50 - 0x2A4E];
    /* 0x2A50 */ J3DMaterialTable* m2A50;
    /* 0x2A54 */ enemyice mEnemyIce;
    /* 0x2E0C */ enemyfire mEnemyFire;
    /* 0x3034 */ JntHit_c* mpJntHit;
}; // Size: 0x3038

class mo2HIO_c : public JORReflexible {
public:
    mo2HIO_c() {
        m005 = 0;
        m006 = 0;
        m007 = 0;
        m008 = 0;
        m009 = 0;
        m018 = 1.0f;
        m01C = 25.0f;
        m022 = 0xb9;
        m024 = 0xc;
        m020 = 0;
        m00C = 0x28;
        m00A = 0x14;
        m010 = 1.0f;
        m028 = 25.0f;
        m02C = 1250.0f;
        m030 = 575.0f;
        m034 = 375.0f;
        m038 = 0x31c4;
        m03C = 400.0f;
        m040.x = 500.0f;
        m040.y = 130.0f;
        m040.z = 500.0f;
        m04C = -125.0f;
        m050 = 12.0f;
        m054 = 60.0f;
        m058 = 45.0f;
        m05C = 70.0f;
        m060 = 90.0f;
        m06C = 70.0f;
        m070 = 1.0f;
        m064 = 20.0f;
        m068 = 20.0f;
        m074 = 0xf;
        m078 = 80.0f;
        m07C = 40.0f;
        m080 = 30.0f;
        m084 = 50.0f;
        m088 = 0x1e;
        m08A = 300;
        m08C = 0.9f;
        m090 = 1.0f;
        m094 = 1.0f;
        m0CC = 0xe;
        m098 = 1.0f;
        m09C = 1.0f;
        m0A0 = 1.0f;
        m0CE = 0x18;
        m0A4 = 1.1f;
        m0A8 = 1.0f;
        m0AC = 1.0f;
        m0D0 = 0x16;
        m0B0 = 0.5f;
        m0B4 = 1.0f;
        m0B8 = 1.2f;
        m0D2 = 5;
        m0BC = 1.0f;
        m0D4 = 100;
        m0C0 = 1.0f;
        m0C4 = 1.0f;
        m0C8 = 1.0f;
        m0D6 = 0x1c;
        m0D8 = 0x1d;
        m0DA = 1;
        m0DC = 2;
        m0DE = 1;
        m0E0[0] = 1.0f;
        m0E0[1] = 1.25f;
        m0E0[2] = 1.25f;
        m0E0[3] = 1.0f;
        m0E0[4] = 0.5f;
        m0E0[5] = 0.5f;
        m0E0[6] = 0.5f;
        m0E0[7] = 1.0f;
        m0E0[8] = 1.0f;
        m0E0[9] = 1.0f;
        m108 = 0x28;
        m10A = 1;
        m10C = 3;
        m10E = 1;
        m110[0] = 1.0f;
        m110[1] = 1.1f;
        m110[2] = 1.15f;
        m110[3] = 1.25f;
        m110[4] = 1.1f;
        m110[5] = 1.0f;
        m110[6] = 1.0f;
        m110[7] = 1.0f;
        m110[8] = 1.0f;
        m110[9] = 1.0f;
        m138 = -22.25f;
        m014 = 1.0f;
        m13C = 30.0f;
        m140 = 650.0f;
        m144 = 8;
        m146 = DEMO_SELECT(10, 12);
        m148 = 0x22;
        m14A = 0x19;
        m14C = 0x10;
        m14E = DEMO_SELECT(10, 12);
        m150 = 0x2d;
        m152 = 0x1e;
        m154 = 8;
        m156 = DEMO_SELECT(10, 12);
        m158 = 0x28;
        m15A = 0x19;
    };
    virtual ~mo2HIO_c() {};
    void genMessage(JORMContext*) {}

public:
    /* 0x004 */ s8 mNo;
    /* 0x005 */ u8 m005;
    /* 0x006 */ u8 m006;
    /* 0x007 */ u8 m007;
    /* 0x008 */ u8 m008;
    /* 0x009 */ u8 m009;
    /* 0x00A */ s16 m00A;
    /* 0x00C */ s16 m00C;
    /* 0x00E */ u8 m00E[0x010 - 0x00E];
    /* 0x010 */ f32 m010;
    /* 0x014 */ f32 m014;
    /* 0x018 */ f32 m018;
    /* 0x01C */ f32 m01C;
    /* 0x020 */ s16 m020;
    /* 0x022 */ s16 m022;
    /* 0x024 */ s16 m024;
    /* 0x026 */ u8 m026[0x028 - 0x026];
    /* 0x028 */ f32 m028;
    /* 0x02C */ f32 m02C;
    /* 0x030 */ f32 m030;
    /* 0x034 */ f32 m034;
    /* 0x038 */ s16 m038;
    /* 0x03A */ u8 m03A[0x03C - 0x03A];
    /* 0x03C */ f32 m03C;
    /* 0x040 */ cXyz m040;
    /* 0x04C */ f32 m04C;
    /* 0x050 */ f32 m050;
    /* 0x054 */ f32 m054;
    /* 0x058 */ f32 m058;
    /* 0x05C */ f32 m05C;
    /* 0x060 */ f32 m060;
    /* 0x064 */ f32 m064;
    /* 0x068 */ f32 m068;
    /* 0x06C */ f32 m06C;
    /* 0x070 */ f32 m070;
    /* 0x074 */ s16 m074;
    /* 0x076 */ u8 m076[0x078 - 0x076];
    /* 0x078 */ f32 m078;
    /* 0x07C */ f32 m07C;
    /* 0x080 */ f32 m080;
    /* 0x084 */ f32 m084;
    /* 0x088 */ s16 m088;
    /* 0x08A */ s16 m08A;
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
    /* 0x0C4 */ f32 m0C4;
    /* 0x0C8 */ f32 m0C8;
    /* 0x0CC */ s16 m0CC;
    /* 0x0CE */ s16 m0CE;
    /* 0x0D0 */ s16 m0D0;
    /* 0x0D2 */ s16 m0D2;
    /* 0x0D4 */ s16 m0D4;
    /* 0x0D6 */ s16 m0D6;
    /* 0x0D8 */ s16 m0D8;
    /* 0x0DA */ s16 m0DA;
    /* 0x0DC */ s16 m0DC;
    /* 0x0DE */ s16 m0DE;
    /* 0x0E0 */ f32 m0E0[10];
    /* 0x108 */ s16 m108;
    /* 0x10A */ s16 m10A;
    /* 0x10C */ s16 m10C;
    /* 0x10E */ s16 m10E;
    /* 0x110 */ f32 m110[10];
    /* 0x138 */ f32 m138;
    /* 0x13C */ f32 m13C;
    /* 0x140 */ f32 m140;
    /* 0x144 */ s16 m144;
    /* 0x146 */ s16 m146;
    /* 0x148 */ s16 m148;
    /* 0x14A */ s16 m14A;
    /* 0x14C */ s16 m14C;
    /* 0x14E */ s16 m14E;
    /* 0x150 */ s16 m150;
    /* 0x152 */ s16 m152;
    /* 0x154 */ s16 m154;
    /* 0x156 */ s16 m156;
    /* 0x158 */ s16 m158;
    /* 0x15A */ s16 m15A;
    /* 0x15C */ JntHit_HIO_c mJntHitHIO;
}; // Size: 0x188

#endif /* D_A_MO2_H */
