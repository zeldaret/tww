#ifndef D_A_TPOTA_H
#define D_A_TPOTA_H

#include "f_op/f_op_actor.h"

class JPABaseParticle;

class daTpota_c : public fopAc_ac_c {
public:
    cPhs_State _create();
    bool _delete();
    void make_ripple(cXyz);
    void check_water_h(JPABaseParticle*, float);
    void clear_splash();
    void renew_splash();
    bool _execute();
    bool _draw();

public:
    /* Place member variables here */
};

#endif /* D_A_TPOTA_H */
