#ifndef D_A_MO2_H
#define D_A_MO2_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "c/c_damagereaction.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_path.h"

struct ke_s {
    
};

class mo2_class : public fopEn_enemy_c {
public:
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
    /* 0x02DC */ u8 m02DC[0x02E0 - 0x02DC];
    /* 0x02E0 */ s16 m02E0;
    /* 0x02E2 */ s16 m02E2;
    /* 0x02E4 */ int mShadowHandle;
    /* 0x02E8 */ u8 m02E8[0x058C - 0x02E8];
    /* 0x058C */ J3DModel* m058C;
    /* 0x0590 */ u8 m0590[0x0594 - 0x0590];
    /* 0x0594 */ int m0594;
    /* 0x0598 */ int m0598;
    /* 0x059C */ int m059C;
    /* 0x05A0 */ u8 m05A0[0x05A4 - 0x05A0];
    /* 0x05A4 */ s16 m05A4;
    /* 0x05A6 */ s16 m05A6;
    /* 0x05A8 */ s16 m05A8;
    /* 0x05AA */ u8 m05AA[0x05AE - 0x05AA];
    /* 0x05AE */ s16 m05AE;
    /* 0x05B0 */ s16 m05B0;
    /* 0x05B2 */ s16 m05B2;
    /* 0x05B4 */ s16 m05B4;
    /* 0x05B6 */ s16 m05B6;
    /* 0x05B8 */ u8 m05B8[0x05BA - 0x05B8];
    /* 0x05BA */ s16 m05BA;
    /* 0x05BC */ s16 m05BC;
    /* 0x05BE */ u8 m05BE;
    /* 0x05BF */ u8 m05BF[0x05C0 - 0x05BF];
    /* 0x05C0 */ f32 m05C0;
    /* 0x05C4 */ cXyz m05C4;
    /* 0x05D0 */ u8 m05D0[0x05D4 - 0x05D0];
    /* 0x05D4 */ s16 m05D4;
    /* 0x05D6 */ s16 m05D6;
    /* 0x05D8 */ s16 m05D8;
    /* 0x05DA */ s16 m05DA;
    /* 0x05DC */ u8 m05DC[0x05E8 - 0x05DC];
    /* 0x05E8 */ s16 m05E8;
    /* 0x05EA */ s16 m05EA;
    /* 0x05EC */ u8 m05EC[0x05EE - 0x05EC];
    /* 0x05EE */ s16 m05EE;
    /* 0x05F0 */ s16 m05F0;
    /* 0x05F2 */ u8 m05F2;
    /* 0x05F3 */ u8 m05F3[0x05F4 - 0x05F3];
    /* 0x05F4 */ dPa_smokeEcallBack m05F4;
    /* 0x0614 */ damagereaction mDamageReaction;
    /* 0x0DD0 */ u8 m0DD0[0x0DD4 - 0x0DD0];
    /* 0x0DD4 */ u8 mbHasInnateWeapon;
    /* 0x0DD5 */ u8 mSpawnWeaponActor;
    /* 0x0DD6 */ u8 mSpawnWeaponActorMode;
    /* 0x0DD7 */ u8 mbThrowWeapon;
    /* 0x0DD8 */ u8 m0DD8[0x2018 - 0x0DD8];
    /* 0x2018 */ mDoExt_3DlineMat0_c m3Dline;
    /* 0x2034 */ u8 m2034[0x2060 - 0x2034];
    /* 0x2060 */ int m2060;
    /* 0x2064 */ int m2064;
    /* 0x2068 */ f32 m2068;
    /* 0x206C */ f32 m206C;
    /* 0x2070 */ u8 m2070[0x2078 - 0x2070];
    /* 0x2078 */ f32 m2078;
    /* 0x207C */ s16 m207C;
    /* 0x207E */ u8 m207E;
    /* 0x207F */ u8 m207F[0x208C - 0x207F];
    /* 0x208C */ dCcD_Cyl mCoCyl;
    /* 0x21BC */ dCcD_Cyl mTgCyl;
    /* 0x22EC */ dCcD_Sph mHeadSph;
    /* 0x2418 */ dCcD_Sph mDefenseSph;
    /* 0x2544 */ dCcD_Sph mWeaponSph;
    /* 0x2670 */ dCcD_Sph mWeapon2Sph;
    /* 0x279C */ u8 m279C[0x28C8 - 0x279C];
    /* 0x28C8 */ cXyz m28C8;
    /* 0x28D4 */ cXyz m28D4;
    /* 0x28E0 */ cXyz m28E0;
    /* 0x28EC */ cXyz m28EC;
    /* 0x28F8 */ cXyz m28F8;
    /* 0x2904 */ cXyz m2904;
    /* 0x2910 */ cXyz m2910;
    /* 0x291C */ cXyz m291C;
    /* 0x2928 */ cXyz m2928;
    /* 0x2934 */ u8 m2934[0x2940 - 0x2934];
    /* 0x2940 */ u8 m2940;
    /* 0x2941 */ u8 m2941;
    /* 0x2942 */ u8 m2942[0x2943 - 0x2942];
    /* 0x2943 */ u8 m2943;
    /* 0x2944 */ s16 m2944;
    /* 0x2946 */ s16 m2946;
    /* 0x2948 */ s16 m2948;
    /* 0x294A */ u8 m294A[0x294E - 0x294A];
    /* 0x294E */ s16 m294E;
    /* 0x2950 */ u8 mParryOpeningType;
    /* 0x2951 */ u8 m2951;
    /* 0x2952 */ s16 m2952;
    /* 0x2954 */ int m2954;
    /* 0x2958 */ uint mWeaponPcId;
    /* 0x295C */ fopAc_ac_c* mpBomb;
    /* 0x2960 */ u16 m2960;
    /* 0x2962 */ u8 m2962[0x2968 - 0x2962];
    /* 0x2968 */ u8 m2968;
    /* 0x2969 */ u8 m2969;
    /* 0x296A */ u8 mHasPath;
    /* 0x296B */ u8 m296B[0x296C - 0x296B];
    /* 0x296C */ dPath* mpPath;
    /* 0x2970 */ u8 m2970;
    /* 0x2971 */ u8 m2971[0x2A08 - 0x2971];
    /* 0x2A08 */ u8 m2A08;
    /* 0x2A09 */ u8 m2A09;
    /* 0x2A0A */ u8 m2A0A;
    /* 0x2A0B */ u8 m2A0B;
    /* 0x2A0C */ s16 m2A0C;
    /* 0x2A0E */ u8 m2A0E[0x2A1C - 0x2A0E];
    /* 0x2A1C */ u8 m2A1C;
    /* 0x2A1D */ u8 m2A1D;
    /* 0x2A1E */ u8 m2A1E[0x2A48 - 0x2A1E];
    /* 0x2A48 */ s16 m2A48;
    /* 0x2A4A */ u8 m2A4A;
    /* 0x2A4B */ u8 m2A4B;
    /* 0x2A4C */ s16 m2A4C;
    /* 0x2A4E */ u8 m2A4E[0x2A54 - 0x2A4E];
    /* 0x2A54 */ enemyice mEnemyIce;
    /* 0x2E0C */ enemyfire mEnemyFire;
    /* 0x3034 */ JntHit_c* mpJntHit;
};

#endif /* D_A_MO2_H */
