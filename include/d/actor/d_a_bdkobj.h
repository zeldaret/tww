#ifndef D_A_BDKOBJ_H
#define D_A_BDKOBJ_H

#include "f_op/f_op_actor.h"
#include "d/d_particle.h"

struct bdo_eff_s {
    
};

class bdkobj_class : public fopAc_ac_c {
public:
    /* 0x290 */ u8 m290[0x918 - 0x290];
    /* 0x918 */ dPa_smokeEcallBack m918;
    /* 0x938 */ u8 m938[0x970 - 0x938];
};

#endif /* D_A_BDKOBJ_H */
