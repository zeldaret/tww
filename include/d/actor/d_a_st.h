#ifndef D_A_ST_H
#define D_A_ST_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "m_Do/m_Do_ext.h"
#include "c/c_damagereaction.h"

struct st_p {
    
};

struct st_ke_s {
    
};

class st_class : public fopEn_enemy_c {
public:
    /* 0x02AC */ u8 m02AC[0x02B4 - 0x02AC];
    /* 0x02B4 */ u8 mBehaviorType;
    /* 0x02B5 */ u8 mAmbushSightRange;
    /* 0x02B6 */ u8 mUnusedParam;
    /* 0x02B7 */ u8 mAmbushSwitch;
    /* 0x02B8 */ u8 mDeathSwitch;
    /* 0x02B9 */ u8 m02B9;
    /* 0x02BA */ u8 m02BA[0x02BC - 0x02BA];
    /* 0x02BC */ int m02BC;
    /* 0x02C0 */ int m02C0;
    /* 0x02C4 */ s16 m02C4;
    /* 0x02C6 */ s16 mActionState;
    /* 0x02C8 */ u8 m02C8[0x02CC - 0x02C8];
    /* 0x02CC */ s8 m02CC;
    /* 0x02CD */ u8 m02CD[0x02E8 - 0x02CD];
    /* 0x02E8 */ u32 m02E8;
    /* 0x02EC */ s16 mTimers[5];
    /* 0x02F6 */ u16 m02F6;
    /* 0x02F8 */ u16 m02F8;
    /* 0x02FA */ u8 m02FA;
    /* 0x02FB */ u8 m02FB[0x0302 - 0x02FB];
    /* 0x0302 */ u16 m0302;
    /* 0x0304 */ s16 m0304;
    /* 0x0306 */ u8 m0306[0x0308 - 0x0306];
    /* 0x0308 */ f32 m0308;
    /* 0x030C */ dBgS_AcchCir m030C;
    /* 0x034C */ dBgS_Acch m034C;
    /* 0x0510 */ u8 m0510[0x052C - 0x0510];
    /* 0x052C */ dCcD_GStts m052C;
    /* 0x054C */ dCcD_Sph m054C[7];
    /* 0x0D80 */ u32 m0D80;
    /* 0x0D84 */ u8 m0D84[0x0ED2 - 0x0D84];
    /* 0x0ED2 */ u8 m0ED2;
    /* 0x0ED3 */ u8 m0ED3;
    /* 0x0ED4 */ st_p mParts[26];
    /* 0x19CC */ st_ke_s m19CC[3];
    /* 0x1D50 */ mDoExt_3DlineMat0_c m1D50;
    /* 0x1D58 */ u8 m1D58[0x1D6C - 0x1D58];
    /* 0x1D6C */ cXyz m1D6C[3];
    /* 0x1D90 */ csXyz m1D90[3];
    /* 0x1DA2 */ u8 m1DA2[0x1DA4 - 0x1DA2];
    /* 0x1DA4 */ cXyz m1DA4[3];
    /* 0x1DC8 */ u8 m1DC8[0x1DCC - 0x1DC8];
    /* 0x1DCC */ uint mHeldWeaponEntityId;
    /* 0x1DD0 */ u8 m1DD0;
    /* 0x1DD1 */ u8 m1DD1[0x1DD4 - 0x1DD1];
    /* 0x1DD4 */ uint mUpperBodyEntityId;
    /* 0x1DD8 */ u8 m1DD8;
    /* 0x1DD9 */ u8 m1DD9[0x1DDA - 0x1DD9];
    /* 0x1DDA */ s16 m1DDA;
    /* 0x1DDC */ u8 m1DDC[0x1DE6 - 0x1DDC];
    /* 0x1DE6 */ csXyz m1DE6[26];
    /* 0x1E82 */ u8 m1E82[0x1E84 - 0x1E82];
    /* 0x1E84 */ u8 m1E84;
    /* 0x1E85 */ u8 mCountdownToDeath;
    /* 0x1E86 */ u8 m1E86;
    /* 0x1E87 */ u8 m1E87[0x1FA8 - 0x1E87];
    /* 0x1FA8 */ enemyice mEnemyIce;
    /* 0x2360 */ u8 m2360[0x2364 - 0x2360];
    /* 0x2364 */ u8 m2364;
    /* 0x2365 */ u8 m2365[0x2368 - 0x2365];
};

#endif /* D_A_ST_H */
