#ifndef D_A_BB_H
#define D_A_BB_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_path.h"
#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "c/c_damagereaction.h"

struct bb_class {
    /* 0x0000 */ fopEn_enemy_c actor;
    /* 0x02AC */ request_of_phase_process_class mPhase;
    /* 0x02B4 */ mDoExt_McaMorf* mpMorf;
    /* 0x02B8 */ mDoExt_btpAnm mBtpAnm;
    /* 0x02CC */ u8 unk_2CC;
    /* 0x02CD */ u8 unk_2CD;
    /* 0x02CE */ u8 unk_2CE;
    /* 0x02D0 */ s16 unk_2D0;
    /* 0x02D4 */ u32 unk_2D4;
    /* 0x02D8 */ u8 unk_2D8;
    /* 0x02D9 */ u8 unk_2D9;
    /* 0x02DA */ u8 unk_2DA;
    /* 0x02DB */ u8 unk_2DB;
    /* 0x02DC */ u8 unk_2DC;
    /* 0x02DD */ u8 unk_2DD;
    /* 0x02DE */ char unk2DE[0x1];
    /* 0x02DF */ u8 unk_2DF;
    /* 0x02E0 */ u8 unk_2E0;
    /* 0x02E4 */ fopAc_ac_c* unk_2E4;
    /* 0x02E8 */ fpc_ProcID unk_2E8;
    /* 0x02EC */ s32 unk_2EC;
    /* 0x02F0 */ s8 unk_2F0;
    /* 0x02F1 */ s8 unk_2F1;
    /* 0x02F2 */ u8 unk_2F2;
    /* 0x02F4 */ cXyz unk_2F4;
    /* 0x0300 */ f32 unk_300;
    /* 0x0304 */ f32 unk_304;
    /* 0x0308 */ f32 unk_308;
    /* 0x030C */ f32 unk_30C;
    /* 0x0310 */ f32 unk_310;
    /* 0x0314 */ char unk314[0x4];
    /* 0x0318 */ s16 unk_318[6];
    /* 0x0324 */ s16 unk_324;
    /* 0x0326 */ s16 unk_326;
    /* 0x0328 */ f32 unk_328;
    /* 0x032C */ f32 unk_32C;
    /* 0x0330 */ fpc_ProcID unk_330;
    /* 0x0334 */ char unk334[0x2];
    /* 0x0336 */ s16 unk_336;
    /* 0x0338 */ s16 unk_338;
    /* 0x033C */ f32 unk_33C;
    /* 0x0340 */ s16 unk_340;
    /* 0x0342 */ s16 unk_342;
    /* 0x0344 */ s16 unk_344;
    /* 0x0348 */ f32 unk_348;
    /* 0x034C */ f32 unk_34C;
    /* 0x0350 */ s16 unk_350;
    /* 0x0352 */ s16 unk_352;
    /* 0x0354 */ s16 unk_354;
    /* 0x0358 */ f32 unk_358;
    /* 0x035C */ char unk35C[0x1];
    /* 0x035D */ s8 unk_35D;
    /* 0x035E */ s8 unk_35E;
    /* 0x035F */ s8 unk_35F;
    /* 0x0360 */ dPath* ppd;
    /* 0x0364 */ u8 unk_364;
    /* 0x0366 */ s16 unk_366;
    /* 0x0364 */ s16 unk_368;
    /* 0x036A */ char unk36A[0xE];
    /* 0x0378 */ dBgS_AcchCir mAcchCir;
    /* 0x03B8 */ dBgS_ObjAcch mAcch;
    /* 0x057C */ u8 unk_57C;
    /* 0x0580 */ dCcD_Stts mStts;
    /* 0x05BC */ dCcD_Sph mHeadAtSph;
    /* 0x06E8 */ dCcD_Sph mHeadTgSph;
    /* 0x0814 */ dCcD_Sph mBodyTgSph;
    /* 0x0940 */ dCcD_Sph mBodyCoSph;
    /* 0x0A6C */ cXyz unk_A6C[2];
    /* 0x0A84 */ J3DModel* unk_A84[9];
    /* 0x0AA8 */ cXyz unk_AA8[10];
    /* 0x0B20 */ csXyz unk_B20[10];
    /* 0x0B5C */ cXyz unk_B5C[10];
    /* 0x0BD4 */ cXyz unk_BD4[2];
    /* 0x0BEC */ s16 unk_BEC;
    /* 0x0BEE */ s16 unk_BEE;
    /* 0x0BF0 */ char unkBF0[0x4];
    /* 0x0BF0 */ cXyz unk_BF4;
    /* 0x0C00 */ csXyz unk_C00[11];
    /* 0x0C42 */ csXyz unk_C42[2];
    /* 0x0C4E */ s16 unk_C4E;
    /* 0x0C50 */ s16 unk_C50;
    /* 0x0C52 */ s16 unk_C52;
    /* 0x0C54 */ u32 unk_C54;
    /* 0x0C58 */ f32 unk_C58;
    /* 0x0C5C */ s16 unk_C5C;
    /* 0x0C5E */ s16 unk_C5E;
    /* 0x0C5C */ u8 unk_C60;
    /* 0x0C16 */ char unkC61[0x7];
    /* 0x0C68 */ dPa_followEcallBack mParticleCallBack;
    /* 0x0C7C */ s8 unk_C7C;
    /* 0x0C7D */ char unkC7D[0x1];
    /* 0x0C7E */ u8 unk_C7E;
    /* 0x0C80 */ enemyice mEnemyIce;
    /* 0x1038 */ enemyfire mEnemyFire;
}; // size = 0x1260

#endif /* D_A_BB_H */
