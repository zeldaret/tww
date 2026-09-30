#ifndef D_A_PT_H
#define D_A_PT_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_acch.h"
#include "c/c_damagereaction.h"
#include "m_Do/m_Do_hostIO.h"

struct pt_class {
    /* 0x000 */ fopEn_enemy_c actor;
    /* 0x2AC */ request_of_phase_process_class mPhase;
    /* 0x2B4 */ u8 mBehaviorType;
    /* 0x2B5 */ u8 mNoticeRange;
    /* 0x2B6 */ u8 mRespawnDelay;
    /* 0x2B7 */ u8 mEnableSpawnSwitch;
    /* 0x2B8 */ u8 mDisableRespawnSwitch;
    /* 0x2B9 */ s8 mInitialSpawnWaitsUntilOffScreen;
    /* 0x2BA */ s8 m2BA;
    /* 0x2BB */ u8 m2BB[0x2C0 - 0x2BB];
    /* 0x2C0 */ mDoExt_McaMorf* mpMorf;
    /* 0x2C4 */ mDoExt_btpAnm* mpBtpAnm;
    /* 0x2C8 */ mDoExt_brkAnm* mpBrkAnm;
    /* 0x2CC */ int m2CC;
    /* 0x2D0 */ s16 m2D0;
    /* 0x2D2 */ s16 mAction;
    /* 0x2D4 */ s16 mMode;
    /* 0x2D6 */ s16 m2D6;
    /* 0x2D8 */ s16 mInitialSpawnDelay;
    /* 0x2DA */ u8 m2DA[0x2E8 - 0x2DA];
    /* 0x2E8 */ cXyz m2E8;
#if VERSION > VERSION_DEMO
    /* 0x2F4 */ u32 mShadowId;
    /* 0x2F8 */ cXyz* m2F8;
    /* 0x2FC */ s16 m2FC;
    /* 0x2FE */ u8 m2FE[0x300 - 0x2FE];
    /* 0x300 */ f32 m300;
    /* 0x304 */ f32 m304;
#endif
    /* 0x308 */ s16 mTimers[3];
    /* 0x30E */ s16 m30E;
#if VERSION > VERSION_DEMO
    /* 0x310 */ s16 m310;
    /* 0x312 */ u8 m312[0x314 - 0x312];
#endif
    /* 0x314 */ f32 m314;
    /* 0x318 */ f32 m318;
    /* 0x31C */ f32 m31C;
    /* 0x320 */ f32 m320;
    /* 0x324 */ s16 m324;
    /* 0x326 */ s8 m326;
    /* 0x327 */ s8 m327;
    /* 0x328 */ dBgS_AcchCir mAcchCir;
    /* 0x368 */ dBgS_ObjAcch mAcch;
    /* 0x52C */ dCcD_Stts mStts;
    /* 0x530 */ dCcD_Sph mCCSph;
    /* 0x534 */ dCcD_Sph mAtSph;
    /* 0x7C0 */ s8 m7C0;
    /* 0x7C1 */ u8 m7C1[0x7C4 - 0x7C1];
    /* 0x7C4 */ dPa_smokeEcallBack mSmokeCb;
    /* 0x7E4 */ enemyice mEnemyIce;
    /* 0xB9C */ enemyfire mEnemyFire;
    /* 0xDC4 */ bool mDC4;
    /* 0xDC5 */ u8 mDC5[0xDC8 - 0xDC5];
}; // Size: 0xDC8

class daPt_HIO_c : public JORReflexible {
public:
    daPt_HIO_c();
    virtual ~daPt_HIO_c() {};
    void genMessage(JORMContext*) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 m05;
    /* 0x06 */ u8 m06;
    /* 0x07 */ u8 m07[0x07 - 0x06];
}; // Size: 0x08

#endif /* D_A_PT_H */
