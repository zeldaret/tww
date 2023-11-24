#ifndef D_A_OBJ_AJAV_H
#define D_A_OBJ_AJAV_H

#include "f_op/f_op_actor.h"

class daObjAjav : public fopAc_ac_c {
public:
    void daObjAjav_make_splash(cXyz, float);
    void check_angle(short*, short);
    void daObjAjav_limit_angle(short*, short);
    void daObjAjav_get_rot_speed(cXyz, cXyz, short);

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_AJAV_H */
