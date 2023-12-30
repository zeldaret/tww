#ifndef D_A_BO_H
#define D_A_BO_H

#include "f_op/f_op_actor.h"
#include "c/c_damagereaction.h"

class yodare_ato_PcallBack_c : public dPa_smokePcallBack {
public:
    void execute(JPABaseEmitter*, JPABaseParticle*);
};

class bo_class : public fopEn_enemy_c {
public:
    /* 0x2AC */ u8 m2AC[0x9FC - 0x2AC];
    /* 0x9FC */ enemyice mEnemyIce;
    /* 0xDB4 */ u8 mDB4[0xFE4 - 0xDB4];
};

#endif /* D_A_BO_H */
