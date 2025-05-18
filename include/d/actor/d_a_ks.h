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
    /* 0x2B4 */ mDoExt_McaMorf* mpBodyMorf;
    /* 0x2B8 */ mDoExt_McaMorf* mpEyeMorf;
    /* 0x2BC */ mDoExt_btkAnm* mpEyeBtkAnm;
    /* 0x2C0 */ mDoExt_brkAnm* mpBodyBrkAnm;
    /* 0x2C4 */ mDoExt_brkAnm* mpEyeBrkAnm;
    /* 0x2C8 */ u8 m2C8;
    /* 0x2C9 */ u8 m2C9;
    /* 0x2CA */ u8 m2CA;
    /* 0x2CB */ u8 mAction;
    /* 0x2CC */ u8 mMode;
    /* 0x2CD */ u8 m2CD;
    /* 0x2CE */ u8 m2CE;
    /* 0x2CF */ u8 m2CF;
    /* 0x2D0 */ u8 m2D0;
    /* 0x2D1 */ u8 m2D1;
    /* 0x2D2 */ u8 m2D2;
    /* 0x2D3 */ u8 m2D3;
    /* 0x2D4 */ fpc_ProcID mGmID; // Mothula
    /* 0x2D8 */ fpc_ProcID mKsID; // Morth
    /* 0x2DC */ cXyz m2DC;
    /* 0x2E8 */ s16 m2E8[4];
    /* 0x2F0 */ s16 m2F0[5];
    /* 0x2FA */ s16 m2FA;
    /* 0x2FC */ s16 m2FC;
    /* 0x2FE */ s16 m2FE;
    /* 0x300 */ s16 m300;
    /* 0x302 */ s16 m302;
    /* 0x304 */ f32 m304;
    /* 0x308 */ f32 m308;
    /* 0x30C */ f32 m30C;
    /* 0x310 */ f32 m310;
    /* 0x314 */ f32 m314;
    /* 0x318 */ f32 m318;
    /* 0x31C */ f32 m31C;
    /* 0x320 */ f32 m320;
    /* 0x324 */ dBgS_AcchCir mAcchCir;
    /* 0x364 */ dBgS_ObjAcch mAcch;
    /* 0x528 */ MtxP m528;
    /* 0x52C */ dPa_rippleEcallBack m52C;
    /* 0x540 */ dCcD_Stts mStts;
    /* 0x57C */ dCcD_Sph mSph;
    /* 0x6A8 */ enemyice mEnemyIce;
    /* 0xA60 */ enemyfire mEnemyFire;
};

#endif /* D_A_KS_H */
