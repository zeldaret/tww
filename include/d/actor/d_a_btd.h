#ifndef D_A_BTD_H
#define D_A_BTD_H

#include "d/d_cc_d.h"
#include "d/d_magma.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"

struct btd_hahen_s {
    /* 0x00 */ J3DModel* model;
    /* 0x04 */ u8 m04;
    /* 0x05 */ u8 m05[0x08 - 0x05];
    /* 0x08 */ cXyz m08;
    /* 0x14 */ cXyz m14;
    /* 0x20 */ s16 m20;
    /* 0x22 */ s16 m22;
    /* 0x24 */ u8 m24[0x28 - 0x24];
}; // Size: 0x28

struct btd_sibuki_s {
    /* 0x00 */ s8 m00;
    /* 0x01 */ u8 m01[0x04 - 0x01];
    /* 0x04 */ cXyz m04;
    /* 0x10 */ cXyz m10;
    /* 0x20 */ u8 m1C[0x24 - 0x1C];
}; // Size: 0x24

class btd_class : public fopAc_ac_c {
public:
    /* 0x0290 */ u8 m0290[0x02AC - 0x0290];
    /* 0x02AC */ request_of_phase_process_class m02AC;
    /* 0x02B4 */ request_of_phase_process_class m02B4;
    /* 0x02BC */ mDoExt_McaMorf* m02BC;
    /* 0x02C0 */ mDoExt_btkAnm* btk;
    /* 0x02C4 */ mDoExt_brkAnm* brk;
    /* 0x02C8 */ mDoExt_McaMorf* m02C8;
    /* 0x02CC */ mDoExt_btkAnm* btkS;
    /* 0x02D0 */ mDoExt_brkAnm* brkS;
    /* 0x02D4 */ mDoExt_McaMorf* m02D4;
    /* 0x02D8 */ mDoExt_btkAnm* m02D8;
    /* 0x02DC */ mDoExt_brkAnm* m02DC;
    /* 0x02E0 */ u8 m02E0;
    /* 0x02E1 */ s8 m02E1;
    /* 0x02E2 */ s16 m02E2;
    /* 0x02E4 */ s16 m02E4;
    /* 0x02E6 */ s16 mGohmaState;
    /* 0x02E8 */ s8 mAttackType;
    /* 0x02E9 */ s8 m02E9;
    /* 0x02EA */ s8 m02EA;
    /* 0x02EB */ u8 m02EB[0x02EC - 0x02EB];
    /* 0x02EC */ s16 m02EC[2]; // m02EC[0] = mAttackTimer?
    /* 0x02F0 */ s16 m02F0;
    /* 0x02F2 */ s16 mStunTimer;
    /* 0x02F4 */ s16 mActionState;
    /* 0x02F6 */ u8 m02F6;
    /* 0x02F7 */ u8 m02F7[0x02F8 - 0x02F7];
    /* 0x02F8 */ s16 m02F8;
    /* 0x02FA */ s16 m02FA;
    /* 0x02FC */ cXyz m02FC[19];
    /* 0x03E0 */ cXyz m03E0;
    /* 0x03EC */ dCcD_Stts m03EC;
    /* 0x0428 */ dCcD_Sph m0428[19];
    /* 0x1A6C */ dCcD_Sph m1A6C;
    /* 0x1B98 */ dCcD_Sph m1B98;
    /* 0x1CC4 */ dCcD_Sph m1CC4[50];
    /* 0x575C */ dCcD_Cyl m575C[6];
    /* 0x5E7C */ u8 m5E7C;
    /* 0x5E7D */ u8 m5E7D[0x5E80 - 0x5E7D];
    /* 0x5E80 */ f32 m5E80;
    /* 0x5E84 */ u8 m5E84;
    /* 0x5E85 */ s8 mTotalDamage;
    /* 0x5E86 */ u8 m5E86;
    /* 0x5E87 */ u8 m5E87[0x5E88 - 0x5E87];
    /* 0x5E88 */ s16 m5E88;
    /* 0x5E8A */ s16 m5E8A;
    /* 0x5E8C */ s16 m5E8C;
    /* 0x5E8E */ s16 m5E8E;
    /* 0x5E90 */ s16 m5E90;
    /* 0x5E92 */ s16 m5E92;
    /* 0x5E94 */ s16 m5E94;
    /* 0x5E96 */ s16 m5E96;
    /* 0x5E98 */ cXyz m5E98[25];
    /* 0x5FC4 */ s16 m5FC4[2];
    /* 0x5FC8 */ u8 m5FC8[0x5FEA - 0x5FC8];
    /* 0x5FEA */ s16 m5FEA[2];
    /* 0x5FEE */ u8 m5FEE[0x5FF8 - 0x5FEE];
    /* 0x5FF8 */ JPABaseEmitter* m5FF8[5];
    /* 0x600C */ JPABaseEmitter* m600C[7];
    /* 0x6028 */ s16 m6028[2];
    /* 0x602C */ s16 m602C;
    /* 0x602E */ s16 m602E;
    /* 0x6030 */ s16 m6030;
    /* 0x6032 */ s16 m6032;
    /* 0x6034 */ s16 m6034;
    /* 0x6036 */ u8 m6036[0x6038 - 0x6036];
    /* 0x6038 */ JPABaseEmitter* m6038;
    /* 0x603C */ cXyz m603C;
    /* 0x6048 */ csXyz m6048;
    /* 0x604E */ u8 m604E[0x6050 - 0x604E];
    /* 0x6050 */ dPa_smokeEcallBack mPa_SmokeEcallBack[3];
    /* 0x60B0 */ LIGHT_INFLUENCE m60B0;
    /* 0x60D0 */ f32 m60D0;
    /* 0x60D4 */ f32 m60D4;
    /* 0x60D8 */ u8 m60D8;
    /* 0x60D9 */ u8 m60D9;
    /* 0x60DA */ u8 m60DA;
    /* 0x60DB */ u8 mKankyoState;
    /* 0x60DC */ s16 mKankyoTimer;
    /* 0x60DE */ u8 m60DE[0x60E0 - 0x60DE];
    /* 0x60E0 */ dKy_tevstr_c m60E0;
    /* 0x6190 */ u8 m6190;
    /* 0x6191 */ u8 m6191[0x6194 - 0x6191];
    /* 0x6194 */ btd_hahen_s hahen[35];
    /* 0x670C */ btd_sibuki_s mBtdSibukiS[50];
    /* 0x6E14 */ s8 m6E14;
    /* 0x6E15 */ u8 m6E15;
    /* 0x6E16 */ s16 m6E16;
    /* 0x6E18 */ s16 m6E18;
    /* 0x6E1A */ s16 m6E1A;
    /* 0x6E1C */ cXyz m6E1C;
    /* 0x6E28 */ cXyz m6E28;
    /* 0x6E34 */ s16 m6E34;
    /* 0x6E36 */ s16 m6E36;
    /* 0x6E38 */ u8 m6E38[0x6E3C - 0x6E38];
    /* 0x6E3C */ f32 m6E3C;
    /* 0x6E40 */ f32 m6E40;
    /* 0x6E44 */ f32 m6E44;
    /* 0x6E48 */ f32 m6E48;
    /* 0x6E4C */ u8 m6E4C;
    /* 0x6E4D */ u8 m6E4D[0x6E50 - 0x6E4D];
    /* 0x6E50 */ cXyz m6E50;
    /* 0x6E5C */ cXyz m6E5C;
    /* 0x6E68 */ cXyz m6E68;
    /* 0x6E74 */ csXyz m6E74;
    /* 0x6E7A */ u8 m6E7A[0x6E7C - 0x6E7A];
    /* 0x6E7C */ f32 m6E7C;
    /* 0x6E80 */ f32 m6E80;
    /* 0x6E84 */ f32 m6E84;
    /* 0x6E88 */ u8 m6E88;
    /* 0x6E89 */ u8 m6E89[0x6E8C - 0x6E89];
    /* 0x6E8C */ dMagma_floor_c* floor;
    /* 0x6E90 */ s8 m6E90;
    /* 0x6E91 */ u8 m6E91[0x6E94 - 0x6E91];
}; // Size: 0x6E94

#endif /* D_A_BTD_H */
