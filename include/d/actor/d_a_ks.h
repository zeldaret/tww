#ifndef D_A_KS_H
#define D_A_KS_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_bg_s_poly_info.h"
#include "c/c_damagereaction.h"

class mDoExt_McaMorf;
class mDoExt_brkAnm;
class mDoExt_btkAnm;

class ks_class : public fopEn_enemy_c {
public:
    /* 0x2AC */ u8 m2AC[0x2B4 - 0x2AC];
    /* 0x2B4 */ mDoExt_McaMorf* m2B4;
    /* 0x2B8 */ mDoExt_McaMorf* m2B8;
    /* 0x2BC */ mDoExt_btkAnm* m2BC;
    /* 0x2C0 */ mDoExt_brkAnm* m2C0;
    /* 0x2C4 */ mDoExt_brkAnm* m2C4;
    /* 0x2C8 */ u8 m2C8;
    /* 0x2C9 */ u8 m2C9[0x2CD - 0x2C9];
    /* 0x2CD */ u8 m2CD;
    /* 0x2CE */ u8 m2CE[0x2D0 - 0x2CE];
    /* 0x2D0 */ u8 m2D0;
    /* 0x2D1 */ u8 m2D1[0x2FA - 0x2D1];
    /* 0x2FA */ csXyz m2FA;
    /* 0x300 */ u8 m300[0x302 - 0x300];
    /* 0x302 */ s16 m302;
    /* 0x304 */ f32 m304;
    /* 0x308 */ u8 m308[0x320 - 0x308];
    /* 0x320 */ f32 m320;
    /* 0x324 */ u8 m324[0x44C - 0x324];
    /* 0x44C */ cBgS_PolyInfo m44C;
    /* 0x45C */ u8 m45C[0xA60 - 0x45C];
    /* 0xA60 */ enemyfire mA60;
};

#endif /* D_A_KS_H */
