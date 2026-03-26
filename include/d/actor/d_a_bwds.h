#ifndef D_A_BWDS_H
#define D_A_BWDS_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"
#include "d/d_particle.h"

class bwds_class {
public:
    /* 0x0000 */ fopEn_enemy_c actor;
    /* 0x02AC */ request_of_phase_process_class m02AC;
    /* 0x02B4 */ u8 m02B4;
    /* 0x02B8 */ mDoExt_McaMorf* mpMorf;
    /* 0x02BC */ J3DModel* mp02BC[0xE];
    /* 0x02F4 */ s16 m02F4;
    /* 0x02F6 */ s16 m02F6;
    /* 0x02F8 */ s16 m02F8;
    /* 0x02FA */ s8 m02FA;
    /* 0x02FB */ s8 m02FB;
    /* 0x02FC */ cXyz m02FC;
    /* 0x0308 */ u8 m0308[0x030C - 0x0308];
    /* 0x030C */ f32 m030C;
    /* 0x0310 */ f32 m0310;
    /* 0x0314 */ s16 m0314[5];
    /* 0x031E */ s16 m031E;
    /* 0x0320 */ f32 m0320;
    /* 0x0324 */ s16 m0324;
    /* 0x0326 */ s16 m0326;
    /* 0x0328 */ s16 m0328;
    /* 0x032C */ cXyz m032C[0xF];
    /* 0x03E0 */ csXyz m03E0[0xF];
    /* 0x043C */ cXyz m043C[0xF];
    /* 0x04F0 */ s32 m04F0;
    /* 0x04F4 */ s8 m04F4;
    /* 0x04F5 */ s8 m04F5;
    /* 0x04F6 */ u8 m04F6[0x4FC - 0x04F6];
    /* 0x04FC */ s16 m04FC;
    /* 0x04FE */ u8 m04FE[0x500 - 0x04FE];
    /* 0x0500 */ s16 m0500;
    /* 0x0502 */ s16 m0502;
    /* 0x0504 */ f32 m0504;
    /* 0x0508 */ dCcD_Stts m0508;
    /* 0x0544 */ dCcD_Sph m0544;
    /* 0x0670 */ dCcD_Sph m0670[0xF];
    /* 0x1804 */ cXyz m1804;
#if VERSION > VERSION_DEMO
    /* 0x1810 */ cXyz m1810;
#endif
    /* 0x181C */ s8 m181C;
    /* 0x181D */ s8 m181D;
    /* 0x181E */ s8 m181E;
    /* 0x1820 */ dPa_smokeEcallBack m1820[3];
    /* 0x1880 */ dPa_followEcallBack m1880;
    /* 0x1894 */ s8 m1894[2];
    /* 0x1898 */ cXyz m1898[2];
    /* 0x18B0 */ mDoExt_McaMorf* mp18B0[2];
    /* 0x18B8 */ mDoExt_btkAnm* mp18B8[2];
    /* 0x18C0 */ mDoExt_brkAnm* mp18C0[2];
    /* 0x18C8 */ u8 m18C8;
}; // Size: 0x18CC

class daBwds_HIO_c : public JORReflexible {
public:
    daBwds_HIO_c();
    virtual ~daBwds_HIO_c() {}

public:
    /* 0x004 */ s8 mNo;
    /* 0x005 */ u8 m005;
    /* 0x008 */ f32 m008;
    /* 0x00C */ f32 m00C;
    /* 0x010 */ f32 m010;
    /* 0x014 */ s16 m014;
    /* 0x018 */ f32 m018;
    /* 0x01C */ f32 m01C;
}; // Size: 0x20

#endif /* D_A_BWDS_H */
