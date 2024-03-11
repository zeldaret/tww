#ifndef D_A_TN_H
#define D_A_TN_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "c/c_damagereaction.h"

struct tn_p {
    /* 0x00 */ u8 m00[0x4C - 0x00];
};

class tn_class : public fopEn_enemy_c {
public:
    /* 0x02AC */ u8 m02AC[0x02BC - 0x02AC];
    /* 0x02BC */ u8 mBehaviorType;
    /* 0x02BD */ u8 mRangeOrFrozenAnim;
    /* 0x02BE */ u8 mPathIndex;
    /* 0x02BF */ u8 mEnableSpawnSwitch;
    /* 0x02C0 */ u8 mDisableSpawnOnDeathSwitch;
    /* 0x02C1 */ u8 m02C1[0x02D0 - 0x02C1];
    /* 0x02D0 */ u8 mRemainingEquipmentPieces;
    /* 0x02D1 */ u8 m02D1[0x02E0 - 0x02D1];
    /* 0x02E0 */ tn_p parts[3];
    /* 0x03C4 */ u8 mArmorColorIndex;
    /* 0x03C5 */ u8 mEquipmentType;
    /* 0x03C6 */ u8 m03C6[0x03E2 - 0x03C6];
    /* 0x03E2 */ s16 m03E2;
    /* 0x03E4 */ u8 m03E4[0x03EE - 0x03E4];
    /* 0x03EE */ s16 m03EE;
    /* 0x03F0 */ s16 m03F0;
    /* 0x03F2 */ u8 m03F2[0x041A - 0x03F2];
    /* 0x041A */ s16 m041A;
    /* 0x041C */ u8 m041C[0x0428 - 0x041C];
    /* 0x0428 */ s16 m0428;
    /* 0x042A */ u8 m042A[0x0430 - 0x042A];
    /* 0x0430 */ s16 m0430;
    /* 0x0432 */ u8 m0432[0x0474 - 0x0432];
    /* 0x0474 */ damagereaction mDamageReaction;
    /* 0x0C30 */ u8 m0C30[0x0C5C - 0x0C30];
    /* 0x0C5C */ dCcD_GObjInf m0C5C;
    /* 0x0D54 */ u8 m0D54[0x0D8C - 0x0D54];
    /* 0x0D8C */ dCcD_GObjInf m0D8C;
    /* 0x0E84 */ u8 m0E84[0x0EBC - 0x0E84];
    /* 0x0EBC */ dCcD_GObjInf m0EBC;
    /* 0x0FB4 */ u8 m0FB4[0x0FE8 - 0x0FB4];
    /* 0x0FE8 */ dCcD_GObjInf m0FE8;
    /* 0x10E0 */ u8 m10E0[0x1114 - 0x10E0];
    /* 0x1114 */ dCcD_GObjInf m1114;
    /* 0x120C */ u8 m120C[0x1240 - 0x120C];
    /* 0x1240 */ dCcD_GObjInf m1240;
    /* 0x1338 */ u8 m1338[0x1384 - 0x1338];
    /* 0x1384 */ cXyz m1384;
    /* 0x1390 */ u8 m1390[0x1408 - 0x1390];
    /* 0x1408 */ int m1408;
    /* 0x140C */ u8 m140C[0x1430 - 0x140C];
    /* 0x1430 */ uint mCapeEntityId;
    /* 0x1434 */ dPa_cutTurnEcallBack_c m1434[3];
    /* 0x1464 */ cXyz m1464[10];
    /* 0x14DC */ u8 m14DC[0x150C - 0x14DC];
    /* 0x150C */ enemyice mEnemyIce;
    /* 0x18C4 */ enemyfire mEnemyFire;
    /* 0x1AEC */ u8 m1AEC[0x1AF0 - 0x1AEC];
};

#endif /* D_A_TN_H */
