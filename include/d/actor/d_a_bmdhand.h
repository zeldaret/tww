#ifndef D_A_BMDHAND_H
#define D_A_BMDHAND_H

#include "d/d_cc_d.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

struct hand_s {
    /* 0x00 */ cXyz m00;
    /* 0x0C */ u8 m0C[0x18 - 0x0C];
    /* 0x18 */ f32 m18;
}; // Size: 0x1C

struct bmdhand_class {
    /* 0x000 */ fopEn_enemy_c actor;
    /* 0x2AC */ request_of_phase_process_class m2AC;
    /* 0x2B4 */ mDoExt_McaMorf* m2B4;
    /* 0x2B8 */ s16 m2B8;
    /* 0x2BA */ s16 m2BA;
    /* 0x2BC */ s16 m2BC;
    /* 0x2BE */ s16 m2BE;
    /* 0x2C0 */ s16 m2C0[4];
    /* 0x2C8 */ s16 m2C8;
    /* 0x2CA */ s16 m2CA;
    /* 0x2CC */ cXyz m2CC;
    /* 0x2D8 */ cXyz m2D8;
    /* 0x2E4 */ cXyz m2E4;
    /* 0x2F0 */ cXyz m2F0;
    /* 0x2FC */ f32 m2FC;
    /* 0x300 */ s16 m300;
    /* 0x302 */ s16 m302;
    /* 0x304 */ s8 m304;
    /* 0x305 */ u8 m305[0x308 - 0x305];
    /* 0x30C */ f32 m308;
    /* 0x30C */ f32 m30C;
    /* 0x310 */ f32 m310;
    /* 0x314 */ f32 m314;
    /* 0x318 */ f32 m318;
    /* 0x31C */ f32 m31C;
    /* 0x320 */ f32 m320;
    /* 0x324 */ hand_s m324[20];
    /* 0x554 */ mDoExt_3DlineMat1_c m554;
    /* 0x590 */ dCcD_Stts m590;
    /* 0x5CC */ dCcD_Sph m5CC;
    /* 0x6F8 */ dCcD_Sph m6F8;
    /* 0x824 */ u8 m824;
    /* 0x825 */ u8 m825[0x828 - 0x825];
}; // Size: 0x828

#endif /* D_A_BMDHAND_H */
