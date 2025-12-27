#ifndef D_A_CC_H
#define D_A_CC_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "d/d_particle.h"
#include "c/c_damagereaction.h"

class mDoExt_McaMorf;
class mDoExt_brkAnm;

struct cc_class {
    /* 0x000 */ fopEn_enemy_c actor;
    /* 0x2AC */ request_of_phase_process_class mPhase;
    /* 0x2B4 */ mDoExt_McaMorf* m2B4;
    /* 0x2B8 */ mDoExt_brkAnm* m2B8;
    /* 0x2BC */ mDoExt_McaMorf* m2BC;
    /* 0x2C0 */ mDoExt_brkAnm* m2C0;
    /* 0x2C4 */ mDoExt_McaMorf* m2C4;
    /* 0x2C8 */ mDoExt_brkAnm* m2C8;
    /* 0x2CC */ mDoExt_brkAnm* m2CC;
    /* 0x2D0 */ mDoExt_btkAnm* m2D0;
    /* 0x2D4 */ mDoExt_btkAnm* m2D4;
    /* 0x2D8 */ mDoExt_McaMorf* m2D8;
    /* 0x2DC */ mDoExt_J3DModelPacketS m2DC;
    /* 0x2EC */ u8 m2EC[0x2F0 - 0x2EC];
    /* 0x2F0 */ u8 mBehaviorType;
    /* 0x2F1 */ u8 mColorType;
    /* 0x2F2 */ u8 mNoticeRangeByte;
    /* 0x2F3 */ u8 mDisableSpawnSwitchNo;
    /* 0x2F4 */ u8 mCurrAction;
    /* 0x2F5 */ u8 m2F5;
    /* 0x2F6 */ u8 m2F6;
    /* 0x2F7 */ u8 m2F7;
    /* 0x2F8 */ u8 m2F8;
    /* 0x2F9 */ u8 m2F9;
    /* 0x2FA */ u8 m2FA;
    /* 0x2FB */ u8 m2FB;
    /* 0x2FC */ u8 m2FC;
    /* 0x2FD */ u8 m2FD;
    /* 0x2FE */ u8 m2FE;
    /* 0x2FF */ u8 m2FF;
    /* 0x300 */ bool m300;
    /* 0x301 */ u8 m301;
    /* 0x302 */ u8 m302;
    /* 0x303 */ u8 m303[0x304 - 0x303];
    /* 0x304 */ u8 m304;
    /* 0x306 */ s16 m306;
    /* 0x308 */ s16 m308;
    /* 0x30C */ fpc_ProcID m30C;
    /* 0x310 */ csXyz m310;
    /* 0x316 */ csXyz m316;
    /* 0x31C */ s16 m31C;
    /* 0x320 */ s32 m320;
    /* 0x324 */ f32 m324;
    /* 0x328 */ f32 m328;
    /* 0x32C */ f32 m32C;
    /* 0x330 */ f32 m330;
    /* 0x334 */ f32 m334;
    /* 0x338 */ f32 m338;
    /* 0x33C */ f32 mNoticeRange;
    /* 0x340 */ f32 m340;
    /* 0x344 */ f32 m344;
    /* 0x348 */ s16 m348;
    /* 0x34A */ s16 m34A;
    /* 0x34C */ s16 m34C;
    /* 0x34E */ s16 m34E[7];
    /* 0x35C */ s16 m35C[5];
#if VERSION == VERSION_DEMO
    /* 0x368 */ JPABaseEmitter* mpEmitter1;
    /* 0x36C */ JPABaseEmitter* mpEmitter2;
    /* 0x370 */ dPa_rippleEcallBack m368;
#else
    /* 0x368 */ dPa_followEcallBack m368;
    /* 0x37C */ dPa_followEcallBack m37C;
    /* 0x390 */ dPa_rippleEcallBack m390;
#endif
    /* 0x3A4 */ cXyz m3A4;
    /* 0x3B0 */ u8 m3B0[0x3BA - 0x3B0];
    /* 0x3BA */ s16 m3BA;
    /* 0x3BC */ cXyz m3BC;
    /* 0x3C8 */ u8 m3C8[0x3E0 - 0x3C8];
    /* 0x3E0 */ cXyz m3E0[6];
    /* 0x428 */ cXyz m428[6];
    /* 0x470 */ cXyz m470;
    /* 0x47C */ dBgS_AcchCir mAcchCir;
    /* 0x4BC */ dBgS_ObjAcch mAcch;
    /* 0x680 */ dCcD_Stts mStts;
    /* 0x6BC */ dCcD_Cyl mCyl;
    /* 0x7EC */ Mtx m7EC;
    /* 0x81C */ enemyice mEnemyIce;
    /* 0xBD4 */ enemyfire mEnemyFire;
    /* 0xDFC */ mDoExt_invisibleModel mDFC;
};  // Size: 0xE04

#endif /* D_A_CC_H */
