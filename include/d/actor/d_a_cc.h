#ifndef D_A_CC_H
#define D_A_CC_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "d/d_bg_s_acch.h"
#include "m_Do/m_Do_ext.h"
#include "c/c_damagereaction.h"
#include "SSystem/SComponent/c_phase.h"

class cc_class : public fopAc_ac_c {
public:
    /* 0x2AC */ request_of_phase_process_class mPhs;
    /* 0x2B4 */ mDoExt_McaMorf* m2B4;
    /* 0x2B8 */ u8 m2B8[0x2BC - 0x2B8];
    /* 0x2BC */ mDoExt_McaMorf* m2BC;
    /* 0x2C0 */ u8 m2C0[0x2C4 - 0x2C0];
    /* 0x2C4 */ mDoExt_McaMorf* m2C4;
    /* 0x2C8 */ u8 m2C8[0x2D8 - 0x2C8];
    /* 0x2D8 */ mDoExt_McaMorf* m2D8;
    /* 0x2DC */ u32 m2DC;
    /* 0x2E0 */ u32 m2E0;
    /* 0x2E4 */ u32 m2E4;
    /* 0x2E8 */ u32 m2E8;
    /* 0x2EC */ u8 m2EC[0x2F0 - 0x2EC];
    /* 0x2F0 */ u8 mBehaviorType;
    /* 0x2F1 */ u8 mColorType;
    /* 0x2F2 */ u8 mNoticeRangeByte;
    /* 0x2F3 */ u8 mDisableSpawnSwitchIndex;
    /* 0x2F4 */ u8 mCurrAction;
    /* 0x2F5 */ u8 m2F5;
    /* 0x2F6 */ u8 m2F6[0x2F7 - 0x2F6];
    /* 0x2F7 */ u8 m2F7;
    /* 0x2F8 */ u8 m2F8;
    /* 0x2F9 */ u8 m2F9;
    /* 0x2FA */ u8 m2FA[0x2FB - 0x2FA];
    /* 0x2FB */ u8 m2FB;
    /* 0x2FC */ u8 m2FC[0x2FE - 0x2FC];
    /* 0x2FE */ u8 m2FE;
    /* 0x2FF */ u8 m2FF[0x301 - 0x2FF];
    /* 0x301 */ u8 m301;
    /* 0x302 */ u8 m302;
    /* 0x303 */ u8 m303[0x316 - 0x303];
    /* 0x316 */ s16 m316;
    /* 0x318 */ u8 m318[0x31A - 0x318];
    /* 0x31A */ s16 m31A;
    /* 0x31C */ s16 m31C;
    /* 0x31E */ u8 m31E[0x328 - 0x31E];
    /* 0x328 */ f32 m328;
    /* 0x32C */ u8 m32C[0x334 - 0x32C];
    /* 0x334 */ f32 m334;
    /* 0x338 */ u8 m338[0x33C - 0x338];
    /* 0x33C */ f32 mNoticeRange;
    /* 0x340 */ u32 m340;
    /* 0x344 */ u8 m344[0x34C - 0x344];
    /* 0x34C */ s16 m34C;
    /* 0x34E */ u8 m34E[0x356 - 0x34E];
    /* 0x356 */ s16 m356;
    /* 0x358 */ u8 m358[0x390 - 0x358];
    /* 0x390 */ u32 m390;
    /* 0x394 */ u32 m394;
    /* 0x398 */ u8 m398[0x3BC - 0x398];
    /* 0x3BC */ cXyz m3BC;
    /* 0x3C8 */ u8 m3C8[0x3E0 - 0x3C8];
    /* 0x3E0 */ cXyz m3E0[6];
    /* 0x428 */ cXyz m428[6];
    /* 0x470 */ u8 m470[0x47C - 0x470];
    /* 0x47C */ dBgS_AcchCir m47C;
    /* 0x4BC */ dBgS_Acch m4BC;
    /* 0x680 */ dCcD_Stts m680;
    /* 0x6BC */ dCcD_Cyl m6BC;
    /* 0x7EC */ u8 m7EC[0x81C - 0x7EC];
    /* 0x81C */ cc_class* m81C;
    /* 0x820 */ u8 m820[0x864 - 0x820];
    /* 0x864 */ u32 m864;
    /* 0x868 */ u32 m868;
    /* 0x86C */ u8 m86C[0x8C4 - 0x86C];
    /* 0x8C4 */ u32 m8C4;
    /* 0x8C8 */ u8 m8C8[0x998 - 0x8C8];
    /* 0x998 */ u32 m998;
    /* 0x99C */ u32 m99C;
    /* 0x9A0 */ u8 m9A0[0x9B4 - 0x9A0];
    /* 0x9B4 */ u32 m9B4;
    /* 0x9B8 */ u32 m9B8;
    /* 0x9BC */ u32 m9BC;
    /* 0x9C0 */ u8 m9C0[0xA20 - 0x9C0];
    /* 0xA20 */ u32 mA20;
    /* 0xA24 */ u32 mA24;
    /* 0xA28 */ u8 mA28[0xA30 - 0xA28];
    /* 0xA30 */ u32 mA30;
    /* 0xA34 */ u8 mA34[0xBD4 - 0xA34];
    /* 0xBD4 */ enemyfire mEnemyFire;
    /* 0xDFC */ u8 mDFC[0xE04 - 0xDFC];
};

#endif /* D_A_CC_H */
