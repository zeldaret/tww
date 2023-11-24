#ifndef D_A_SWTACT_H
#define D_A_SWTACT_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"

class daSwTact_c : public fopAc_ac_c {
public:
    void getR() {}

    void CreateInit();
    void set_mtx();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ f32 mRadius;
    /* 0x2A0 */ u32 m2A0;
    /* 0x2A4 */ u8 mAnswer;
    /* 0x2A5 */ u8 m2A5;
    /* 0x2A6 */ u8 m2A6;
    /* 0x2A7 */ u8 m2A7[0x2A8 - 0x2A7];
};

#endif /* D_A_SWTACT_H */
