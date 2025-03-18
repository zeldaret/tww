#ifndef D_A_TPOTA_H
#define D_A_TPOTA_H

#include "f_op/f_op_actor.h"
#include "d/d_particle.h"

class JPABaseEmitter;
class JPABaseParticle;

class daTpota_c : public fopAc_ac_c {
public:
    s32 _create();
    BOOL _delete();
    void make_ripple(cXyz);
    int check_water_h(JPABaseParticle*, float);
    void clear_splash();
    void renew_splash();
    bool _execute();
    bool _draw();

public:
//     /* 0x290 */ u8 field_0x290[0x298 - 0x290];
//     /* 0x298 */ JPABaseEmitter* field_0x298;
//     /* 0x29C */ int* field_0x29C;
//     /* 0x2A0 */ f32 field_0x2A0;
//     /* 0x2A4 */ f32 field_0x2A4;
//     /* 0x2A8 */ f32 field_0x2A8;
//     /* 0x2AC */ u8 field_0x2AC[0x2B8 - 0x2AC];
//     /* 0x2B8 */ s16 field_0x2B8;
//     /* 0x2BA */ s16 field_0x2BA;
//     /* 0x2BC */ s16 field_0x2BC;
//     /* 0x2BE */ u8 field_0x2BE[0x2C4 - 0x2BE];
//     /* 0x2C4 */ int field_0x2C4[10];
//     /* 0x2EC */ u8 field_0x2EC[0x3E4 - 0x2EC];
// };  // Size: 0x3E4
    /* 0x290 */ u8 field_0x290[0x298 - 0x290];
    /* 0x298 */ JPABaseEmitter* field_0x298;
    /* 0x29C */ JPABaseEmitter* emitter;
    /* 0x2A0 */ f32 field_0x2A0;
    /* 0x2A4 */ f32 field_0x2A4;
    /* 0x2A8 */ f32 field_0x2A8;
    /* 0x2AC */ u8 field_0x2AC[0x2B8 - 0x2AC];
    /* 0x2B8 */ s16 field_0x2B8;
    /* 0x2BA */ s16 field_0x2BA;
    /* 0x2BC */ s16 field_0x2BC;
    /* 0x2BE */ u8 field_0x2BE[0x3E4 - 0x2BE];
};  // Size: 0x3E4


#endif /* D_A_TPOTA_H */
