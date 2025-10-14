#ifndef D_A_BGN_H
#define D_A_BGN_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"

struct part_s {
    /* 0x000 */ J3DModel* m000;
    /* 0x004 */ mDoExt_J3DModelPacketS m004;
    /* 0x018 */ dKy_tevstr_c m018;
    /* 0x0C8 */ s16 m0C8;
    /* 0x0C8 */ u8 m0CA[0x0CC - 0x0CA];
    /* 0x0CC */ f32 m0CC;
    /* 0x0D0 */ s16 m0D0;
    /* 0x0D2 */ u8 m0D2;
    /* 0x0D3 */ u8 m0D3[0x0D4 - 0x0D3];
    /* 0x0D4 */ cXyz m0D4;
    /* 0x0E0 */ csXyz m0E0;
    /* 0x0E6 */ u8 m0E6[0x0F4 - 0x0E6];
    /* 0x0F4 */ f32 m0F4;
    /* 0x0F8 */ dCcD_Sph m0F8;
    /* 0x224 */ cXyz m224;
    /* 0x230 */ JPABaseEmitter* m230;
    /* 0x234 */ JPABaseEmitter* m234;
    /* 0x238 */ s16 m238;
    /* 0x23A */ u8 m23A[0x23C - 0x23A];
}; // Size: 0x23C

struct move_s {
    /* 0x000 */ cXyz m000[60];
    /* 0x2D0 */ u8 m2D0;
    /* 0x2D1 */ u8 m2D1[0x2D4 - 0x2D1];
    /* 0x2D4 */ cXyz m2D4;
    /* 0x2E0 */ csXyz m2E0;
    /* 0x2E6 */ u8 m2E6[0x2E8 - 0x2E6];
    /* 0x2E8 */ f32 m2E8;
    /* 0x2EC */ f32 m2EC;
    /* 0x2F0 */ u8 m2F0[0x2F4 - 0x2F0];
    /* 0x2F4 */ f32 m2F4;
    /* 0x2F8 */ s16 m2F8;
    /* 0x2FA */ s16 m2FA;
    /* 0x2FC */ s16 m2FC;
    /* 0x2FE */ s16 m2FE;
    /* 0x300 */ s16 m300;
    /* 0x302 */ u8 m302[0x304 - 0x302];
    /* 0x304 */ f32 m304;
    /* 0x308 */ s8 m308;
    /* 0x309 */ u8 m309[0x30C - 0x309];
}; // Size: 0x30C

struct bgn_class {
    /* 0x0000 */ fopEn_enemy_c actor;
    /* 0x02AC */ request_of_phase_process_class m02AC;
    /* 0x02B4 */ u8 m02B4;
    /* 0x02B5 */ s8 m02B5;
    /* 0x02B6 */ u8 m02B6[0x02B8 - 0x02B6];
    /* 0x02B8 */ mDoExt_McaMorf* m02B8;
    /* 0x02BC */ J3DModel* m02BC;
    /* 0x02C0 */ mDoExt_J3DModelPacketS m02C0;
    /* 0x02D4 */ JPABaseEmitter* m02D4;
    /* 0x02D8 */ JPABaseEmitter* m02D8;
    /* 0x02DC */ s16 m02DC;
    /* 0x02DE */ u8 m02DE[0x02E0 - 0x02DE];
    /* 0x02E0 */ J3DModel* m02E0;
    /* 0x02E4 */ J3DModel* m02E4;
    /* 0x02E8 */ J3DModel* m02E8;
    /* 0x02EC */ mDoExt_brkAnm* m02EC;
    /* 0x02F0 */ mDoExt_brkAnm* m02F0;
    /* 0x02F4 */ u8 m02F4[0x02F8 - 0x02F4];
    /* 0x02F8 */ s16 m02F8;
    /* 0x02FA */ u8 m02FA[0x02FC - 0x02FA];
    /* 0x02FC */ f32 m02FC;
    /* 0x0300 */ s16 m0300;
    /* 0x0302 */ s16 m0302;
    /* 0x0304 */ s16 m0304;
    /* 0x0306 */ u8 m0306[0x0308 - 0x0306];
    /* 0x0308 */ cXyz m0308;
    /* 0x0314 */ part_s m0314[2];
    /* 0x078C */ part_s m078C[2];
    /* 0x0C04 */ part_s m0C04[21];
    /* 0x3AF0 */ part_s m3AF0[21];
    /* 0x69DC */ part_s m69DC[4];
    /* 0x72CC */ part_s m72CC[4];
    /* 0x7BBC */ part_s m7BBC[21];
    /* 0xAAA8 */ move_s mAAA8[8];
    /* 0xC308 */ cXyz mC308;
    /* 0xC314 */ csXyz mC314;
    /* 0xC31A */ s16 mC31A;
    /* 0xC31C */ u8 mC31C[0xC324 - 0xC31C];
    /* 0xC324 */ f32 mC324[2];
    /* 0xC32C */ f32 mC32C[2];
    /* 0xC334 */ f32 mC334;
    /* 0xC338 */ f32 mC338;
    /* 0xC33C */ cXyz mC33C[8];
    /* 0xC39C */ mDoExt_3DlineMat1_c mC39C;
    /* 0xC3D8 */ mDoExt_3DlineMat1_c mC3D8;
    /* 0xC414 */ mDoExt_3DlineMat1_c mC414;
    /* 0xC450 */ cXyz mC450[60];
    /* 0xC720 */ s8 mC720;
    /* 0xC721 */ u8 mC721[0xC724 - 0xC721];
    /* 0xC724 */ f32 mC724;
    /* 0xC728 */ cXyz mC728;
    /* 0xC734 */ cXyz mC734;
    /* 0xC740 */ u8 mC740[0xC744 - 0xC740];
    /* 0xC744 */ s16 mC744;
    /* 0xC746 */ s16 mC746;
    /* 0xC748 */ s16 mC748;
    /* 0xC74A */ s16 mC74A;
    /* 0xC74C */ s16 mC74C;
    /* 0xC74E */ s16 mC74E;
    /* 0xC750 */ s16 mC750;
    /* 0xC752 */ s16 mC752;
    /* 0xC754 */ s16 mC754;
    /* 0xC756 */ u8 mC756[0xC758 - 0xC756];
    /* 0xC758 */ cXyz mC758;
    /* 0xC764 */ s16 mC764;
    /* 0xC766 */ u8 mC766[0xC76C - 0xC766];
    /* 0xC76C */ f32 mC76C;
    /* 0xC770 */ s16 mC770;
    /* 0xC772 */ u8 mC772[0xC774 - 0xC772];
    /* 0xC774 */ f32 mC774;
    /* 0xC778 */ s8 mC778;
    /* 0xC779 */ s8 mC779;
    /* 0xC772 */ u8 mC77A[0xC77C - 0xC77A];
    /* 0xC77C */ cXyz mC77C;
    /* 0xC788 */ cXyz mC788;
    /* 0xC794 */ cXyz mC794;
    /* 0xC7A0 */ cXyz mC7A0;
    /* 0xC7AC */ s16 mC7AC[2];
    /* 0xC7B0 */ s16 mC7B0;
    /* 0xC7B2 */ s16 mC7B2;
    /* 0xC7B4 */ u8 mC7B4[0xC7B6 - 0xC7B4];
    /* 0xC7B6 */ s16 mC7B6;
    /* 0xC7B8 */ s16 mC7B8;
    /* 0xC7BA */ u8 mC7BA[0xC7BC - 0xC7BA];
    /* 0xC7BC */ f32 mC7BC;
    /* 0xC7C0 */ dCcD_Stts mC7C0;
    /* 0xC7FC */ dCcD_Sph mC7FC;
    /* 0xC928 */ dCcD_Sph mC928;
    /* 0xCA54 */ cXyz mCA54;
    /* 0xCA60 */ s16 mCA60;
    /* 0xCA62 */ s8 mCA62;
    /* 0xCA63 */ u8 mCA63[0xCA64 - 0xCA63];
    /* 0xCA64 */ s16 mCA64;
    /* 0xCA66 */ u8 mCA66[0xCA68 - 0xCA66];
    /* 0xCA68 */ cXyz mCA68;
    /* 0xCA74 */ cXyz mCA74;
    /* 0xCA80 */ cXyz mCA80;
    /* 0xCA8C */ u8 mCA8C[0xCA98 - 0xCA8C];
    /* 0xCA98 */ f32 mCA98;
    /* 0xCA9C */ f32 mCA9C;
    /* 0xCAA0 */ f32 mCAA0;
    /* 0xCAA4 */ J3DModel* mCAA4;
    /* 0xCAA8 */ J3DModel* mCAA8;
    /* 0xCAAC */ dKy_tevstr_c mCAAC;
    /* 0xCB5C */ J3DModel* mCB5C;
    /* 0xCB60 */ mDoExt_J3DModelPacketS mCB60;
    /* 0xCB74 */ dKy_tevstr_c mCB74;
    /* 0xCC24 */ mDoExt_J3DModelPacketS mCC24;
    /* 0xCC38 */ s8 mCC38;
    /* 0xCC39 */ u8 mCC39[0xCC3C - 0xCC39];
    /* 0xCC3C */ dPa_smokeEcallBack mCC3C[2];
    /* 0xCC7C */ s8 mCC7C;
    /* 0xCC7D */ u8 mCC7D[0xCC80 - 0xCC7D];
    /* 0xCC80 */ f32 mCC80;
    /* 0xCC84 */ f32 mCC84;
    /* 0xCC88 */ f32 mCC88;
    /* 0xCC8C */ JPABaseEmitter* mCC8C;
    /* 0xCC90 */ s8 mCC90;
    /* 0xCC91 */ u8 mCC91;
    /* 0xCC92 */ u8 mCC92[0xCC94 - 0xCC92];
}; // Size: 0xCC94

#endif /* D_A_BGN_H */
