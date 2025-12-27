#ifndef D_A_OBJ_DEMO_BARREL_H
#define D_A_OBJ_DEMO_BARREL_H

#include "f_op/f_op_actor.h"

class mDoExt_McaMorf;

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
    BOOL CreateHeap();

    static const char M_arcname[];

public:
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ mDoExt_McaMorf* mpMorf;
    /* 0x2A0 */ u8 m2A0[0x2D0 - 0x2A0];
    /* 0x2D0 */ cXyz m2D0;
    /* 0x2DC */ s16 m2DC;
    /* 0x2DE */ s16 m2DE;
    /* 0x2E0 */ u8 m2E0[0x2E4 - 0x2E0];
}; // size = 0x2E4

#endif /* D_A_OBJ_DEMO_BARREL_H */
