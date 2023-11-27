#ifndef D_A_PT_H
#define D_A_PT_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_acch.h"
#include "c/c_damagereaction.h"

class pt_class : public fopEn_enemy_c {
public:
    /* 0x2AC */ u8 m2AC[0x2B4 - 0x2AC];
    /* 0x2B4 */ u8 mBehaviorType;
    /* 0x2B5 */ u8 mNoticeRange;
    /* 0x2B6 */ u8 mRespawnDelay;
    /* 0x2B7 */ u8 mEnableSpawnSwitch;
    /* 0x2B8 */ u8 mDisableRespawnSwitch;
    /* 0x2B9 */ bool mInitialSpawnWaitsUntilOffScreen;
    /* 0x2BA */ u8 m2BA;
    /* 0x2BB */ u8 m2BB[0x2C0 - 0x2BB];
    /* 0x2C0 */ mDoExt_McaMorf* m2C0;
    /* 0x2C4 */ u32* m2C4;
    /* 0x2C8 */ u32* m2C8;
    /* 0x2CC */ int m2CC;
    /* 0x2D0 */ u16 m2D0;
    /* 0x2D2 */ s16 m2D2;
    /* 0x2D4 */ u8 m2D4[0x2D6 - 0x2D4];
    /* 0x2D6 */ s16 m2D6;
    /* 0x2D8 */ u16 mInitialSpawnDelay;
    /* 0x2DA */ u8 m2DA[0x2F8 - 0x2DA];
    /* 0x2F8 */ Vec* m2F8;
    /* 0x2FC */ s16 m2FC;
    /* 0x2FE */ u8 m2FE[0x300 - 0x2FE];
    /* 0x300 */ f32 m300;
    /* 0x304 */ f32 m304;
    /* 0x308 */ u8 m308[0x30E - 0x308];
    /* 0x30E */ s16 m30E;
    /* 0x310 */ u8 m310[0x314 - 0x310];
    /* 0x314 */ u32 m314;
    /* 0x318 */ u32 m318;
    /* 0x31C */ f32 m31C;
    /* 0x320 */ f32 m320;
    /* 0x324 */ s16 m324;
    /* 0x326 */ u8 m326[0x328 - 0x326];
    /* 0x328 */ dBgS_AcchCir m328;
    /* 0x368 */ dBgS_Acch m368;
    /* 0x52C */ f32 m52C;
    /* 0x530 */ f32 m530;
    /* 0x534 */ f32 m534;
    /* 0x538 */ u8 m538[0x544 - 0x538];
    /* 0x544 */ u32 m544;
    /* 0x548 */ u32 m548;
    /* 0x54C */ u8 m54C[0x5A4 - 0x54C];
    /* 0x5A4 */ u32 m5A4;
    /* 0x5A8 */ u8 m5A8[0x5AC - 0x5A8];
    /* 0x5AC */ float* m5AC;
    /* 0x5B0 */ u8 m5B0[0x678 - 0x5B0];
    /* 0x678 */ u32 m678;
    /* 0x67C */ u32 m67C;
    /* 0x680 */ u8 m680[0x690 - 0x680];
    /* 0x690 */ u32 m690;
    /* 0x694 */ u8 m694[0x6D0 - 0x694];
    /* 0x6D0 */ u32 m6D0;
    /* 0x6D4 */ u8 m6D4[0x6D8 - 0x6D4];
    /* 0x6D8 */ float* m6D8;
    /* 0x6DC */ u8 m6DC[0x7A4 - 0x6DC];
    /* 0x7A4 */ u32 m7A4;
    /* 0x7A8 */ u32 m7A8;
    /* 0x7AC */ u8 m7AC[0x7BC - 0x7AC];
    /* 0x7BC */ u32 m7BC;
    /* 0x7C0 */ u8 m7C0;
    /* 0x7C1 */ u8 m7C1[0x7C4 - 0x7C1];
    /* 0x7C4 */ int m7C4;
    /* 0x7C8 */ u8 m7C8[0x7E4 - 0x7C8];
    /* 0x7E4 */ enemyice mEnemyIce;
    /* 0xB9C */ pt_class* mB9C;
    /* 0xBA0 */ u8 mBA0[0xBA8 - 0xBA0];
    /* 0xBA8 */ mDoExt_McaMorf* mBA8;
    /* 0xBAC */ u8 mBAC[0xC54 - 0xBAC];
    /* 0xC54 */ u32 mC54;
    /* 0xC58 */ u32 mC58;
    /* 0xC5C */ u8 mC5C[0xCB4 - 0xC5C];
    /* 0xCB4 */ u32 mCB4;
    /* 0xCB8 */ u8 mCB8[0xD88 - 0xCB8];
    /* 0xD88 */ u32 mD88;
    /* 0xD8C */ u32 mD8C;
    /* 0xD90 */ u8 mD90[0xDA0 - 0xD90];
    /* 0xDA0 */ u32 mDA0;
    /* 0xDA4 */ u8 mDA4[0xDC4 - 0xDA4];
    /* 0xDC4 */ bool mDC4;
    /* 0xDC5 */ u8 mDC5[0xDC8 - 0xDC5];
};

#endif /* D_A_PT_H */
