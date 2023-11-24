#ifndef D_A_TPOTA_H
#define D_A_TPOTA_H

#include "f_op/f_op_actor.h"
#include "JSystem/JParticle/JPAParticle.h"

class daTpota_c : public fopAc_ac_c {
public:
    void _create();
    void _delete();
    void make_ripple(cXyz);
    void check_water_h(JPABaseParticle*, float);
    void clear_splash();
    void renew_splash();
    void _execute();
    void _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_TPOTA_H */
