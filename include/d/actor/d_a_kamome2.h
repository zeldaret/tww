#ifndef D_A_KAMOME2_H
#define D_A_KAMOME2_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"

class mDoExt_McaMorf;

struct kamome2_class {
    /* 0x000 */ fopAc_ac_c actor;
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ mDoExt_McaMorf* mpMorf;
    /* 0x29C */ J3DModel* mpModel;
    /* 0x2A0 */ s32 m2A0;
    /* 0x2A4 */ u8 m2A4;
    /* 0x2A8 */ s32 m2A8;
    /* 0x2AC */ s8 m2AC;
    /* 0x2AD */ u8 m2AD[0x2BC - 0x2AD];
    /* 0x2BC */ f32 m2BC;
    /* 0x2C0 */ f32 m2C0;
    /* 0x2C4 */ u8 m2C4[0x2D0 - 0x2C4];
    /* 0x2D0 */ s16 m2D0[5];
    /* 0x2DA */ s16 m2DA;
    /* 0x2DC */ s16 m2DC;
    /* 0x2DE */ u8 m2DE[0x2EC - 0x2DE];
    /* 0x2EC */ u8 m2EC;
    /* 0x2F0 */ cXyz m2F0;
    /* 0x2FC */ cXyz m2FC;
    /* 0x308 */ s16 m308;
    /* 0x30A */ u8 m30A[0x314 - 0x30A];
    /* 0x314 */ f32 m314;
    /* 0x318 */ u8 m318[0x320 - 0x318];
    /* 0x320 */ dBgS_AcchCir mAcchCir;
    /* 0x360 */ dBgS_ObjAcch mAcch;
    /* 0x524 */ dCcD_Stts mStts;
    /* 0x560 */ dCcD_Sph mSph;
    /* 0x68C */ bool m68C;
};  // Size: 0x690

#endif /* D_A_KAMOME2_H */
