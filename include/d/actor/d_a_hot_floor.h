#ifndef D_A_HOT_FLOOR_H
#define D_A_HOT_FLOOR_H

#include "f_op/f_op_actor.h"
#include "JSystem/JParticle/JPAEmitter.h"

class daHot_Floor_c : public fopAc_ac_c {
public:
    void _create() {}
    void _delete() {}
    void _draw() {}
    void _execute() {}
    void setAimMtx(float(*)[4]) {}

    void set_mtx_init();
    void set_mtx();

public:
    /* 0x290 */ u8 m290[0x2B8 - 0x290];
    /* 0x2B8 */ f32 m2B8;
    /* 0x2BC */ u8 m2BC[0x2D4 - 0x2BC];
    /* 0x2D4 */ JPABaseEmitter* m2D4;
    /* 0x2D8 */ JPABaseEmitter* m2D8;
    /* 0x2DC */ u8 m2DC[0x2E0 - 0x2DC];
    /* 0x2E0 */ Mtx m2E0;
    /* 0x310 */ u8 m310[0x3D4 - 0x310];
};

#endif /* D_A_HOT_FLOOR_H */
