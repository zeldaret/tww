#ifndef D_A_MSW_H
#define D_A_MSW_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_bg_w.h"

class msw_class : public fopAc_ac_c {
public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ s16 m298;
    /* 0x29A */ u8 m29A[0x29C - 0x29A];
    /* 0x29C */ J3DModel* mpModel;
    /* 0x2A0 */ u8 m2A0[0x2A4 - 0x2A0];
    /* 0x2A4 */ cXyz m2A4;
    /* 0x2B0 */ f32 m2B0;
    /* 0x2B4 */ u8 m2B4[0x2B8 - 0x2B4];
    /* 0x2B8 */ f32 m2B8;
    /* 0x2BC */ f32 m2BC;
    /* 0x2C0 */ u8 m2C0[0x2C4 - 0x2C0];
    /* 0x2C4 */ f32 m2C4;
    /* 0x2C8 */ u8 m2C8[0x2D0 - 0x2C8];
    /* 0x2D0 */ J3DModel* m2D0[4];
    /* 0x2E0 */ cXyz m2E0[4];
    /* 0x310 */ cXyz m310[4];
    /* 0x340 */ u8 m340[0x83C - 0x340];
    /* 0x83C */ s16 m83C[4];
    /* 0x844 */ u8 m844[0x84C - 0x844];
    /* 0x84C */ Mtx mMtx;
    /* 0x87C */ dBgW* mpBgW;
};

#endif /* D_A_MSW_H */
