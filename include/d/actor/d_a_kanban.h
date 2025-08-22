#ifndef D_A_KANBAN_H
#define D_A_KANBAN_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "d/d_bg_s_acch.h"
#include "m_Do/m_Do_hostIO.h"

struct kanban_class {
    /* 0x000 */ fopAc_ac_c actor;
    /* 0x290 */ bool m290;
    /* 0x294 */ u32 m294;
    /* 0x298 */ u8 m298;
    /* 0x299 */ u8 m299[0x29A - 0x299];
    /* 0x29A */ u8 m29A;
    /* 0x29B */ u8 m29B;
    /* 0x29C */ u8 m29C;
    /* 0x2A0 */ f32 m2A0;
    /* 0x2A4 */ f32 m2A4;
    /* 0x2A8 */ f32 m2A8;
    /* 0x2AC */ csXyz m2AC;
    /* 0x2B2 */ s16 m2B2[5];
    /* 0x2BC */ s16 m2BC;
    /* 0x2BE */ s16 m2BE;
    /* 0x2C0 */ s16 m2C0;
    /* 0x2C2 */ s16 m2C2;
    /* 0x2C4 */ s16 m2C4;
    /* 0x2C6 */ s16 m2C6;
    /* 0x2C8 */ fpc_ProcID m2C8;
    /* 0x2CC */ cXyz m2CC;
    /* 0x2D8 */ cXyz m2D8;
    /* 0x2E4 */ f32 m2E4;
    /* 0x2E8 */ f32 m2E8;
    /* 0x2EC */ f32 m2EC;
    /* 0x2F0 */ csXyz m2F0;
    /* 0x2F8 */ cXyz m2F8;
    /* 0x304 */ cXyz m304;
    /* 0x310 */ dBgS_AcchCir m310;
    /* 0x350 */ dBgS_ObjAcch m350;
    /* 0x514 */ dPa_rippleEcallBack m514;
    /* 0x528 */ cXyz m528;
    /* 0x534 */ u8 m534[0x53C - 0x534];
    /* 0x53C */ request_of_phase_process_class mPhase;
    /* 0x544 */ J3DModel* m544[11];
    /* 0x570 */ u32 m570;
    /* 0x574 */ dCcD_Stts m574;
    /* 0x5B0 */ dCcD_Cyl m5B0;
}; // size = 0x6E0

#endif /* D_A_KANBAN_H */
