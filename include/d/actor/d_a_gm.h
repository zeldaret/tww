#ifndef D_A_GM_H
#define D_A_GM_H

#include "c/c_damagereaction.h"
#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "f_op/f_op_actor.h"

struct gm_class {
    /* 0x0000 */ fopEn_enemy_c actor;
    /* 0x02AC */ request_of_phase_process_class mPhase;
    /* 0x02B4 */ mDoExt_McaMorf* mpMorf;
    /* 0x02B8 */ u8 m02B8[0x02BC - 0x02B8];
    /* 0x02BC */ mDoExt_brkAnm* mBodyGlowBrkAnm;
    /* 0x02C0 */ mDoExt_brkAnm* mAtackBrkAnm;
    /* 0x02C4 */ mDoExt_brkAnm* mDamageBrkAnm;
    /* 0x02C8 */ mDoExt_brkAnm* mDeadBrkAnm;
    /* 0x02CC */ u8 m02CC;
    /* 0x02CD */ u8 m02CD;
    /* 0x02CE */ u8 m02CE;
    /* 0x02CF */ u8 mSwitch;
    /* 0x02D0 */ u8 mAction;
    /* 0x02D1 */ u8 m02D1;
    /* 0x02D1 */ u8 m02D2;
    /* 0x02D3 */ u8 m02D3;
    /* 0x02D4 */ u8 m02D4;
    /* 0x02D5 */ u8 m02D5;
    /* 0x02D6 */ u8 m02D6;
    /* 0x02D7 */ u8 m02D7;
    /* 0x02D8 */ u8 m02D8[0x02DA - 0x02D8];
    /* 0x02DA */ s16 m02DA;
    /* 0x02DC */ s16 mMode;
    /* 0x02DE */ s16 m02DE;
    /* 0x02E0 */ s16 m02E0;
    /* 0x02E2 */ s16 mCountDownTimers[7];
    /* 0x02F0 */ s16 mCountUpTimers[23];
    /* 0x031E */ s16 m031E;
    /* 0x0320 */ s16 m0320;
    /* 0x0322 */ s16 m0322;
    /* 0x0324 */ s16 m0324;
    /* 0x0326 */ s16 m0326;
    /* 0x0328 */ f32 m0328;
    /* 0x032C */ f32 m032C;
    /* 0x0330 */ f32 m0330;
    /* 0x0334 */ f32 m0334;
    /* 0x0338 */ cXyz m0338;
    /* 0x0344 */ int mCurrBckIdx;
    /* 0x0348 */ cXyz m0348;
    /* 0x0354 */ cXyz m0354;
    /* 0x0360 */ cXyz m0360[3];
    /* 0x0384 */ cXyz m0384[3];
    /* 0x03A8 */ cXyz m03A8;
    /* 0x03B4 */ cXyz m03B4;
    /* 0x03C0 */ cXyz m03C0;
    /* 0x03CC */ cXyz m03CC;
    /* 0x03D0 */ cXyz m03D8;
    /* 0x03E4 */ cXyz m03E4;
    /* 0x03F0 */ cXyz m03F0;
    /* 0x03FC */ cXyz m03FC;
    /* 0x0408 */ cXyz m0408;
    /* 0x0414 */ csXyz m0414[4];
    /* 0x042C */ s16 m042C;
    /* 0x042E */ s16 m042E;
    /* 0x0430 */ s16 m0430;
    /* 0x0432 */ u8 m0432[0x0434 - 0x0432];
    /* 0x0434 */ s16 m0434;
    /* 0x0436 */ s16 m0436;
    /* 0x0438 */ s16 m0438;
    /* 0x043A */ s16 m043A;
    /* 0x043C */ s16 m043C;
    /* 0x043E */ csXyz m043E;
    /* 0x0444 */ J3DModel* m0444;
    /* 0x0448 */ s32 mShadowId;
    /* 0x044C */ s16 m044C;
    /* 0x044E */ u8 m044E[0x0450 - 0x044E];
    /* 0x0450 */ cXyz m0450;
    /* 0x045C */ cXyz m045C;
    /* 0x0468 */ u8 m0468[0x0478 - 0x0468];
    /* 0x0478 */ f32 m0478;
    /* 0x047C */ dBgS_AcchCir mAcchCir;
    /* 0x04BC */ dBgS_ObjAcch mAcch;
    /* 0x0680 */ dCcD_Stts mStts;
    /* 0x06BC */ dCcD_Cyl mBodyCyl;
    /* 0x07EC */ dCcD_Cyl mWingCyl;
    /* 0x091C */ dCcD_Cyl mWindCyl;
    /* 0x0A4C */ dCcD_Sph mAtSph;
    /* 0x0B78 */ JPABaseEmitter* m0B78;
    /* 0x0B7C */ JPABaseEmitter* m0B7C;
    /* 0x0B80 */ JPABaseEmitter* m0B80;
    /* 0x0B84 */ JPABaseEmitter* m0B84;
    /* 0x0B88 */ u8 m0B88[0x0B9C - 0x0B88];
    /* 0x0B9C */ enemyice mEnemyIce;
    /* 0x0F54 */ enemyfire mEnemyFire;
    /* 0x117C */ mDoExt_invisibleModel mInvisibleModel;
}; // Size: 0x1184

#endif /* D_A_GM_H */
