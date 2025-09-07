#ifndef D_A_BMDFOOT_H
#define D_A_BMDFOOT_H

#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"

class bmdfoot_class {
public:
    /* 0x000 */ fopAc_ac_c actor;
    /* 0x290 */ u8 m290[0x2AC - 0x290];
    /* 0x2AC */ request_of_phase_process_class m2AC;
    /* 0x2B4 */ mDoExt_McaMorf* m2B4;
    /* 0x2B8 */ s16 m2B8;
    /* 0x2BA */ s16 m2BA;
    /* 0x2BC */ s16 m2BC;
    /* 0x2BE */ s16 m2BE;
    /* 0x2C0 */ s16 m2C0[4];
    /* 0x2C8 */ s16 m2C8[2];
    /* 0x2CC */ cXyz m2CC[18];
    /* 0x3A4 */ f32 m3A4[16];
    /* 0x3E0 */ u8 m3E0[0x3EC - 0x3E4];
    /* 0x3EC */ s16 m3EC;
    /* 0x3EE */ u8 m3EE[0x3F4 - 0x3EE];
    /* 0x3F4 */ u8 m3F4;
    /* 0x3F5 */ u8 m3F5[0x3F8 - 0x3F5];
    /* 0x3F8 */ cXyz m3F8[3];
    /* 0x41C */ dPa_followEcallBack m41C[3];
    /* 0x458 */ dPa_smokeEcallBack m458[2];
    /* 0x498 */ cXyz m498[2];
    /* 0x4B0 */ dPa_smokeEcallBack m4B0;
    /* 0x4D0 */ dCcD_Stts m4D0;
    /* 0x50C */ dCcD_Sph m50C[5];
    /* 0xAE8 */ cXyz mAE8;
    /* 0xAF4 */ mDoExt_McaMorf* mAF4;
    /* 0xAF8 */ dKy_tevstr_c mAF8;
    /* 0xBA8 */ u8 mBA8;
    /* 0xBA9 */ u8 mBA9[0xBAC - 0xBA9];
    /* 0xBAC */ cXyz mBAC;
    /* 0xBB8 */ csXyz mBB8;
    /* 0xBBC */ u8 mBBC[0xBC0 - 0xBBE];
    /* 0xBC0 */ f32 mBC0;
    /* 0xBC4 */ f32 mBC4;
    /* 0xBC8 */ u8 mBC8;
    /* 0xBC9 */ u8 mBC9[0xBCC - 0xBC9];
    /* 0xAF4 */ mDoExt_btkAnm* btk;
    /* 0xBD0 */ s16 mBD0;
    /* 0xBD2 */ u8 mBD2;
    /* 0xBD3 */ u8 mBD3[0xBD4 - 0xBD3];
}; // Size: 0xBD4

#endif /* D_A_BMDFOOT_H */
