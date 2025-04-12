#ifndef D_A_OBJ_DEMO_BARREL_H
#define D_A_OBJ_DEMO_BARREL_H

#include "f_op/f_op_actor.h"

class daObj_Demo_Barrel_c : public fopAc_ac_c {
public:
    inline cPhs_State _create();
    inline bool _delete();
    inline bool _draw();
    inline bool _execute();
    void demo_move() {}
    void set_mtx() {}

    void setParticleHahen();
    void setParticleSibuki();
    void CreateHeap();

public:
    /* Place member variables here */
};

#endif /* D_A_OBJ_DEMO_BARREL_H */
