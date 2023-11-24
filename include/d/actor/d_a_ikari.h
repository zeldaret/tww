#ifndef D_A_IKARI_H
#define D_A_IKARI_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"

class daIkari_c : public fopAc_ac_c {
public:
    void setMtx();
    void _createHeap();
    void getArg();
    void _execute();
    void _draw();
    void _create();
    void _delete();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ u8 mEnvType;
    /* 0x29D */ u8 mModelType;
    /* 0x29E */ u8 m29E[0x2A0 - 0x29E];
    /* 0x2A0 */ int mTimer;
};

#endif /* D_A_IKARI_H */
