#ifndef D_A_TPOTA_H
#define D_A_TPOTA_H

#include "f_op/f_op_actor.h"

class JPABaseEmitter;
class JPABaseParticle;

class daTpota_c : public fopAc_ac_c {

    struct unknown_struct {
        JPABaseParticle* ptcl;
        f32 pos_y;
    };

public:
    cPhs_State _create();
    bool _delete();
    void make_ripple(cXyz);
    BOOL check_water_h(JPABaseParticle*, float);
    void clear_splash();
    void renew_splash();
    bool _execute();
    bool _draw();

public:
    /* 0x290 */ u8 field_0x290[0x298 - 0x290];
    /* 0x298 */ JPABaseEmitter* mpEmitters[2];
    /* 0x2A0 */ cXyz mPositions[2];
    /* 0x2B8 */ csXyz mAngles[2];
    /* 0x2C4 */ unknown_struct field_0x2C4[30];
    /* 0x3B4 */ u8 field_0x3B4[0x3E4 - 0x3B4];
};  // Size: 0x3E4


#endif /* D_A_TPOTA_H */
