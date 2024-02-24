#ifndef D_A_KT_H
#define D_A_KT_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"
#include "JSystem/J3DGraphAnimator/J3DAnimation.h"

class kt_class : public fopAc_ac_c {
public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ void* field_0x29c[2];
    /* 0x2A4 */ J3DFrameCtrl mFrameCtrl;
    /* 0x2B8 */ J3DModel* mpModelWing;
    /* 0x2BC */ f32 field_0x2bc;
    /* 0x2C0 */ f32 field_0x2c0;
    /* 0x2C4 */ f32 field_0x2c4;
    /* 0x2C8 */ f32 field_0x2c8;
    /* 0x2CC */ s32 field_0x2cc;
    /* 0x2D0 */ f32 field_0x2d0;
    /* 0x2D4 */ cXyz field_0x2d4;
    /* 0x2E0 */ f32 field_0x2e0;
    /* 0x2E4 */ cXyz field_0x2e4;
    /* 0x2F0 */ cXyz field_0x2f0;
    /* 0x2FC */ cXyz field_0x2fc;
    /* 0x308 */ cXyz field_0x308;
    /* 0x314 */ s16 mTimer[3];
    /* 0x31A */ s16 field_0x31a;
    /* 0x31C */ s8 mState;
    /* 0x31D */ u8 field_0x31d;
    /* 0x31E */ u8 field_0x31e;
    /* 0x31E */ u8 field_0x31f;
};

#endif /* D_A_KT_H */
