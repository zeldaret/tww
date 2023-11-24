#ifndef D_A_WZ_H
#define D_A_WZ_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "m_Do/m_Do_ext.h"

class wz_class : public fopAc_ac_c {
public:
    /* 0x2AC */ u8 m2AC[0x2B4 - 0x2AC];
    /* 0x2B4 */ mDoExt_McaMorf* m2B4;
    /* 0x2B8 */ u8 m2B8[0x314 - 0x2B8];
    /* 0x314 */ cXyz m314;
    /* 0x320 */ u8 m320[0x348 - 0x320];
    /* 0x348 */ daWZ__BehaviorTypes mBehaviorType;
    /* 0x349 */ u8 mEnemySummonTableIndex;
    /* 0x34A */ u8 mEnableSpawnSwitch;
    /* 0x34B */ u8 mDisableSpawnOnDeathSwitch;
    /* 0x34C */ u8 m34C[0x350 - 0x34C];
    /* 0x350 */ bool mIsMiniBoss;
    /* 0x351 */ bool m351;
    /* 0x352 */ u8 m352[0x425 - 0x352];
    /* 0x425 */ u8 mPathIndex;
    /* 0x426 */ u8 m426[0x7D8 - 0x426];
    /* 0x7D8 */ dCcD_Sph m7D8;
    /* 0x904 */ u8 m904[0xF8C - 0x904];
};

#endif /* D_A_WZ_H */
