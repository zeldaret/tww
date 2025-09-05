#ifndef D_A_KOKIIE_H
#define D_A_KOKIIE_H

#include "f_op/f_op_actor.h"

class dBgW;

struct kokiie_class {
    /* 0x000 */ fopAc_ac_c actor;
    /* 0x290 */ request_of_phase_process_class mPhase;
    /* 0x298 */ s16 m298;
    /* 0x29A */ s16 m29A;
    /* 0x29C */ J3DModel* mpModel;
    /* 0x2A0 */ u8 m2A0;
    /* 0x2A1 */ u8 m2A1[0x2A2 - 0x2A1];
    /* 0x2A2 */ u8 m2A2;
    /* 0x2A3 */ u8 m2A3[0x2A4 - 0x2A3];
    /* 0x2A4 */ cXyz m2A4;
    /* 0x2B0 */ f32 m2B0;
    /* 0x2B4 */ u8 m2B4[0x2B8 - 0x2B4];
    /* 0x2B8 */ f32 m2B8;
    /* 0x2BC */ f32 m2BC;
    /* 0x2C0 */ u8 m2C0[0x2C4 - 0x2C0];
    /* 0x2C4 */ f32 m2C4;
    /* 0x2C8 */ csXyz m2C8;
    /* 0x2CE */ u8 m2CE[0x2D0 - 0x2CE];
    /* 0x2D0 */ f32 m2D0;
    /* 0x2D4 */ fpc_ProcID m2D4[5];
    /* 0x2E8 */ u8 m2E8[5];
    /* 0x2ED */ u8 m2ED[0x2F0 - 0x2ED];
    /* 0x2F0 */ cXyz m2F0[5];
    /* 0x32C */ u8 m32C[5];
    /* 0x331 */ u8 m331[0x332 - 0x331];
    /* 0x332 */ s16 m332;
    /* 0x334 */ s16 m334;
    /* 0x336 */ u8 m336[0x338 - 0x336];
    /* 0x338 */ f32 m338;
    /* 0x33C */ u8 m33C[0x340 - 0x33C];
    /* 0x340 */ Mtx m340;
    /* 0x370 */ dBgW* pm_bgw;
    /* 0x374 */ f32 m374;
    /* 0x378 */ s16 m378;
    /* 0x37A */ s16 m37A;
    /* 0x37C */ cXyz m37C;
    /* 0x388 */ cXyz m388;
    /* 0x394 */ u8 m394[0x39C - 0x394];
    /* 0x39C */ f32 m39C;
    /* 0x3A0 */ f32 m3A0;
}; // size = 0x3A4

#endif /* D_A_KOKIIE_H */
