#ifndef D_A_OBJ_HAT_H
#define D_A_OBJ_HAT_H

#include "f_op/f_op_actor.h"

class daObjHat_c : public fopAc_ac_c {
public:
    daObjHat_c();

    s32 _create();
    void createHeap();
    void createInit();
    BOOL _delete();
    BOOL _draw();
    BOOL _execute();
    void executeNormal();
    void getPrmHatNo();
    void setMtx();
    void setSpeed(cXyz);

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_HAT_H */
