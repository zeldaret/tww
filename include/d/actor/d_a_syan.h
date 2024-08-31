#ifndef D_A_SYAN_H
#define D_A_SYAN_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_particle.h"

class mDoExt_McaMorf;

class syan_class : public fopAc_ac_c {
public:
    enum {
        kEmtrNum = 6,
    };

    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ mDoExt_McaMorf* morf;
    /* 0x29C */ s32 frameCount;
    /* 0x2A0 */ u32 state;
    /* 0x2A4 */ csXyz field_0x2a4[2];
    /* 0x2B0 */ csXyz field_0x2b0;
    /* 0x2B8 */ f32 field_0x2b8;
    /* 0x2BC */ f32 field_0x2bc;
    /* 0x2C0 */ f32 field_0x2c0;
    /* 0x2C4 */ f32 field_0x2c4;
    /* 0x2C8 */ f32 field_0x2c8;
    /* 0x2CC */ f32 field_0x2cc;
    /* 0x2D0 */ f32 field_0x2d0;
    /* 0x2D4 */ s16 timer[2];
    /* 0x2D8 */ f32 field_0x2d8;
    /* 0x2DC */ f32 field_0x2dc;
    /* 0x2E0 */ Mtx partMtx[kEmtrNum];
    /* 0x400 */ cXyz partPos[kEmtrNum];
    /* 0x448 */ cXyz partPosOld[kEmtrNum];
    /* 0x490 */ s16 partRotY[kEmtrNum];
    /* 0x49C */ dPa_followEcallBack emtrCallBack[kEmtrNum];
    /* 0x514 */ f32 partAlpha[kEmtrNum];
    /* 0x52C */ f32 field_0x52c[kEmtrNum];
    /* 0x544 */ f32 partScale1[kEmtrNum];
    /* 0x55C */ f32 field_0x55c[kEmtrNum];
    /* 0x574 */ f32 partScale2[kEmtrNum];
    /* 0x58C */ s16 field_0x58c[kEmtrNum];
    /* 0x598 */ s16 field_0x598[kEmtrNum];
    /* 0x5A4 */ s16 field_0x5a4[kEmtrNum];
    /* 0x5B0 */ bool emtrEnabled[kEmtrNum];
};

#endif /* D_A_SYAN_H */
