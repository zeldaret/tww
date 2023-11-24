#ifndef D_A_OBJ_TAPESTRY_H
#define D_A_OBJ_TAPESTRY_H

#include "f_op/f_op_actor.h"

class daObjTapestryPLight_c : public fopAc_ac_c {
public:
    void plight_delete();
    void plight_move(cXyz, csXyz);
    void plight_make();
    void setPointLight(cXyz, csXyz);

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_TAPESTRY_H */
