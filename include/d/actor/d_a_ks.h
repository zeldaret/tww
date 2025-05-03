#ifndef D_A_KS_H
#define D_A_KS_H

#include "f_op/f_op_actor.h"
#include "c/c_damagereaction.h"

class mDoExt_McaMorf;
class mDoExt_brkAnm;
class mDoExt_btkAnm;
class daPy_lk_c;

class ks_class : public fopEn_enemy_c {
public:
    /* 0x2AC */ request_of_phase_process_class mPhs;
    /* 0x2B4 */ mDoExt_McaMorf* m2B4;
    /* 0x2B8 */ mDoExt_McaMorf* m2B8;
    /* 0x2BC */ mDoExt_btkAnm* m2BC;
    /* 0x2C0 */ mDoExt_brkAnm* m2C0;
    /* 0x2C4 */ mDoExt_brkAnm* m2C4;
    /* 0x2C8 */ u8 m2C8;
    /* 0x2C9 */ u8 m2C9[0x2CB - 0x2C9];
    /* 0x2CB */ u8 m2CB;
    /* 0x2CC */ u8 m2CC;
    /* 0x2CD */ u8 m2CD;
    /* 0x2CE */ u8 m2CE;
    /* 0x2CF */ u8 m2CF;
    /* 0x2D0 */ u8 m2D0;
    /* 0x2D1 */ u8 m2D1;
    /* 0x2D2 */ u8 m2D2;
    /* 0x2D3 */ u8 m2D3;
    /* 0x2D4 */ fpc_ProcID mGmID;
    /* 0x2D8 */ u8 m2D8[0x2E8 - 0x2D8];
    /* 0x2E8 */ s16 m2E8[4];
    /* 0x2F0 */ s16 m2F0[5];
    /* 0x2FA */ csXyz m2FA;
    /* 0x300 */ u8 m300[0x302 - 0x300];
    /* 0x302 */ s16 m302;
    /* 0x304 */ f32 m304;
    /* 0x308 */ f32 m308;
    /* 0x30C */ f32 m30C;
    /* 0x310 */ f32 m310;
    /* 0x314 */ f32 m314;
    /* 0x318 */ f32 m318;
    /* 0x31C */ f32 m31C;
    /* 0x320 */ f32 m320;
    /* 0x324 */ u8 m324[0x364 - 0x324];
    /* 0x364 */ dBgS_Acch mAcch;
    /* 0x528 */ u8 m528[0x52C - 0x528];
    /* 0x52C */ dPa_rippleEcallBack m52C;
    /* 0x540 */ cXyz m540;
    /* 0x54C */ u8 m54C[0x55C - 0x54C];
    /* 0x55C */ dCcD_GStts mGStts;
    /* 0x57C */ dCcD_Sph mSph;
    /* 0x6A8 */ enemyice mEnemyIce;
    /* 0xA60 */ enemyfire mEnemyFire;
};

#endif /* D_A_KS_H */
