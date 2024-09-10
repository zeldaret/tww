#ifndef D_A_BGN_H
#define D_A_BGN_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"

struct part_s {
    /* 0x000 */ u8 m000[0x004 - 0x000];
    /* 0x004 */ mDoExt_J3DModelPacketS m004;
    /* 0x014 */ u8 m014[0x018 - 0x014];
    /* 0x018 */ J3DLightObj m018;
    /* 0x08C */ u8 m08C[0x0F8 - 0x08C];
    /* 0x0F8 */ dCcD_Sph m0F8;
    /* 0x224 */ u8 m224[0x23C - 0x224];
};  // Size: 0x23C

struct move_s {
    /* 0x000 */ cXyz m000[60];
    /* 0x2D0 */ u8 m2D0;
    /* 0x2D1 */ u8 m2D1[0x2EC - 0x2D1];
    /* 0x2EC */ f32 m2EC;
    /* 0x2F0 */ u8 m2F0[0x300 - 0x2F0];
    /* 0x300 */ s16 m300;
    /* 0x302 */ u8 m302[0x304 - 0x302];
    /* 0x304 */ f32 m304;
    /* 0x308 */ s8 m308;
    /* 0x309 */ u8 m309[0x30C - 0x309];
};  // Size: 0x30C

class bgn_class : public fopAc_ac_c {
public:
    /* 0x0290 */ u8 m0290[0x02B5 - 0x0290];
    /* 0x02B5 */ s8 m02B5;
    /* 0x02B6 */ u8 m02B6[0x02C0 - 0x02B6];
    /* 0x02C0 */ mDoExt_J3DModelPacketS m02C0;
    /* 0x02D0 */ u8 m02D0[0x0314 - 0x02D0];
    /* 0x0314 */ part_s m0314[2];
    /* 0x078C */ part_s m078C[2];
    /* 0x0C04 */ part_s m0C04[21];
    /* 0x3AF0 */ part_s m3AF0[21];
    /* 0x69DC */ part_s m69DC[4];
    /* 0x72CC */ part_s m72CC[4];
    /* 0x7BBC */ part_s m7BBC[21];
    /* 0xAAA8 */ move_s mAAA8[8];
    /* 0xC308 */ u8 mC308[0xC33C - 0xC308];
    /* 0xC33C */ cXyz mC33C[8];
    /* 0xC39C */ mDoExt_3DlineMat1_c mC39C;
    /* 0xC3D8 */ mDoExt_3DlineMat1_c mC3D8;
    /* 0xC414 */ mDoExt_3DlineMat1_c mC414;
    /* 0xC450 */ cXyz mC450[60];
    /* 0xC720 */ u8 mC720[0xC748 - 0xC720];
    /* 0xC748 */ s16 mC748;
    /* 0xC74A */ u8 mC74A[0xC74C - 0xC74A];
    /* 0xC74C */ s16 mC74C;
    /* 0xC74E */ u8 mC74E[0xC7B0 - 0xC74E];
    /* 0xC7B0 */ u16 mC7B0;
    /* 0xC7B2 */ u8 mC7B2[0xC7C0 - 0xC7B2];
    /* 0xC7C0 */ dCcD_Stts mC7C0;
    /* 0xC7FC */ dCcD_Sph mC7FC;
    /* 0xC928 */ dCcD_Sph mC928;
    /* 0xCA54 */ u8 mCA54[0xCAAC - 0xCA54];
    /* 0xCAAC */ J3DLightObj mCAAC;
    /* 0xCB20 */ u8 mCB20[0xCB60 - 0xCB20];
    /* 0xCB60 */ mDoExt_J3DModelPacketS mCB60;
    /* 0xCB70 */ u8 mCB70[0xCB74 - 0xCB70];
    /* 0xCB74 */ J3DLightObj mCB74;
    /* 0xCBE8 */ u8 mCBE8[0xCC24 - 0xCBE8];
    /* 0xCC24 */ mDoExt_J3DModelPacketS mCC24;
    /* 0xCC34 */ u8 mCC34[0xCC3C - 0xCC34];
    /* 0xCC3C */ dPa_smokeEcallBack mCC3C[2];
    /* 0xCC7C */ u8 mCC7C[0xCC94 - 0xCC7C];
};  // Size: 0xCC94

class daBgn_HIO_c {
public:
    daBgn_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_BGN_H */
