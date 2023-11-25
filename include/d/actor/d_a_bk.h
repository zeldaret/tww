#ifndef D_A_BK_H
#define D_A_BK_H

#include "f_op/f_op_actor.h"
#include "c/c_damagereaction.h"
#include "c/c_damagereaction.h"
#include "SSystem/SComponent/c_phase.h"

class bk_class : public fopEn_enemy_c {
public:
    /* 0x02AC */ request_of_phase_process_class mPhsBk;
    /* 0x02B4 */ u8 mMode;
    /* 0x02B5 */ u8 m02B5;
    /* 0x02B6 */ u8 m02B6;
    /* 0x02B7 */ u8 m02B7;
    /* 0x02B8 */ u8 m02B8;
    /* 0x02B9 */ u8 m02B9;
    /* 0x02BA */ u8 m02BA[0x0302 - 0x02BA];
    /* 0x0302 */ s16 m0302;
    /* 0x0304 */ u8 m0304[0x030C - 0x0304];
    /* 0x030C */ s16 m030C;
    /* 0x030E */ u8 m030E[0x0336 - 0x030E];
    /* 0x0336 */ s16 m0336;
    /* 0x0338 */ u8 m0338[0x0344 - 0x0338];
    /* 0x0344 */ s16 m0344;
    /* 0x0346 */ u8 m0346[0x034C - 0x0346];
    /* 0x034C */ s16 m034C;
    /* 0x034E */ u8 m034E;
    /* 0x034F */ u8 m034F[0x0370 - 0x034F];
    /* 0x0370 */ damagereaction mDamageReaction;
    /* 0x0B2C */ u8 m0B2C[0x11FC - 0x0B2C];
    /* 0x11FC */ int m11FC;
    /* 0x1200 */ u8 m1200[0x121C - 0x1200];
    /* 0x121C */ u8 m121C;
    /* 0x121D */ u8 m121D[0x1264 - 0x121D];
    /* 0x1264 */ enemyice mEnemyIce;
    /* 0x161C */ u8 m161C[0x1848 - 0x161C];
};

#endif /* D_A_BK_H */
