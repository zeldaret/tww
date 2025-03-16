#ifndef D_A_BEAM_H
#define D_A_BEAM_H

#include "f_op/f_op_actor.h"

class daBeam_c : public fopAc_ac_c {
public:
    inline s32 _create();
    inline bool _delete();
    inline bool _draw();
    void beamCheck() {}
    void beamOff() {}
    void beamOn() {}
    void checkHFloorParticle() {}
    void checkSmokeParticle() {}
    void offHFloorParticle() {}
    void offSmokeParticle() {}
    void onHFloorParticle() {}
    void onSmokeParticle() {}
    void setDefaultProc(void (daBeam_c::*)()) {}
    void setEmitterOffset(float) {}
    void setPosAngle(cXyz&, csXyz&) {}
    void setSearchProc(void (daBeam_c::*)()) {}

    void set_mtx();
    void CreateHeap();
    void CreateInit();
    bool _execute();
    void checkRange(csXyz*);
    void move_search();
    void fix_search();
    void timer_change();
    void wait_proc();

public:
    /* Place member variables here */
};

class daBeam_HIO_c {
public:
    daBeam_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_BEAM_H */
