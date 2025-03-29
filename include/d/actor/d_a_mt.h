#ifndef D_A_MT_H
#define D_A_MT_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"

class dPath;
class mDoExt_McaMorf;
class mDoExt_btkAnm;
class mDoExt_brkAnm;
class J3DTexNoAnm;

class mt_class : public fopEn_enemy_c {
public:
    /* Place member variables here */
    /* 0x02AC */ request_of_phase_process_class mPhs;
    /* 0x02B4 */ u8 m2B4;
    /* 0x02B5 */ u8 m2B5;
    /* 0x02B6 */ u8 m2B6;
    /* 0x02B7 */ u8 m2B7;
    /* 0x02B8 */ u8 m2B8;
    /* 0x02B9 */ u8 m2B9;
    /* 0x02BA */ u8 m2BA;
    /* 0x02BB */ u8 m2BB;
    /* 0x02BC */ u8 m2BC;
    u8 m2BD[1];
    /* 0x02BE */ u8 m2BE;
    u8 m2BF[1];
    /* 0x02C0 */ dPath* mpPath;
    /* 0x02C4 */ mDoExt_McaMorf* mpMorfs[8];
    u8 m2E4[0x02F0 - 0x02E4];
    /* 0x02F0 */ mDoExt_btkAnm* btk[8];
    /* 0x0310 */ mDoExt_brkAnm* brk[8];
    /* 0x0330 */ f32 m330;
    u8 m334[0x0340 - 0x0334];
    /* 0x0340 */ J3DTexNoAnm* m340;
    u8 m344[0x0454 - 0x0344];
    /* 0x0454 */ u8 m454;
    /* 0x0455 */ u8 m455;
    /* 0x0456 */ s16 m456;
    u8 m458[0x460 - 0x458];
    /* 0x0460 */ s16 m460;
    /* 0x0462 */ s16 m462;
    u8 m464[0x466 - 0x464];
    /* 0x0466 */ s16 m466;
    /* 0x0468 */ s16 m468;
    /* 0x046A */ s16 m46A;
    u8 m46C[0x478 - 0x46C];
    /* 0x0478 */ f32 m478;
    /* 0x047C */ cXyz m47C;
    /* 0x0488 */ s16 m488;
    /* 0x048A */ s16 m48A;
    u8 m48C[0x048E - 0x048C];
    /* 0x048E */ s16 m48E;
    u8 m490[0x0494 - 0x0490];
    /* 0x0494 */ s16 m494;
    /* 0x0496 */ s16 m496;
    u8 m498[0x0600 - 0x0498];
    /* 0x0600 */ int m600[8];
    u8 m620[0x06F4 - 0x0620];
    /* 0x06F4 */ cXyz m6F4[64];
    /* 0x09F4 */ csXyz m9F4[64];
    u8 mB74[0x0C01 - 0x0B74];
    /* 0x0C01 */ u8 mC01;
    /* 0x0C02 */ s16 mC02;
    /* 0x0C04 */ u8 mC04;
    u8 mC05[0x0C08 - 0x0C05];
    /* 0x0C08 */ dBgS_AcchCir mAcchCir;
    /* 0x0C48 */ dBgS_Acch mAcch;
    /* 0x0E0C */ dCcD_Stts mStts;
    /* 0x0E48 */ dCcD_GObjInf mE48;
    u8 mF40[0x17A8 - 0x0F40];
    /* 0x17A8 */ dCcD_Sph mEyeSph;
    /* 0x18D4 */ u8 m18D4;
    u8 m18D5[0x18D8 - 0x18D5];
    /* 0x18D8 */ J3DModel* br_modelL[3];
    /* 0x18E4 */ J3DModel* br_modelR[3];
    /* 0x18F0 */ f32 m18F0;
    /* 0x18F4 */ f32 m18F4;
    /* 0x18F8 */ u8 m18F8;
    /* 0x18F9 */ u8 m18F9;
    u8 m18FA[0x18FB - 0x18FA];
    /* 0x18FB */ u8 m18FB;
    u8 m18FC[0x1900 - 0x18FC];
    /* 0x1900 */ mt_class* m1900;
    u8 m1904[0x1AB1 - 0x1904];
    /* 0x1AB1 */ u8 m1AB1;
    u8 m1AB2[0x1CC0 - 0x1AB2];
}; // Size: 0x1CC0

STATIC_ASSERT(sizeof(mt_class) == 0x1CC0);

class daMt_HIO_c {
public:
    daMt_HIO_c();

public:
    /* Place member variables here */
    u8 m00[0x10 - 0x00];
    /* 0x10 */ s16 m10;
    u8 m12[0x14 - 0x12];
    /* 0x14 */ f32 m14;
    /* 0x18 */ f32 m18;
    u8 m1C[0x24 - 0x1C];
    /* 0x24 */ f32 m24;
    /* 0x28 */ f32 m28;
    /* 0x28 */ f32 m2C;
    /* 0x30 */ s16 m30;
    /* 0x32 */ s16 m32;
    /* 0x34 */ f32 m34;
    /* 0x38 */ s16 m38;
    /* 0x3A */ s16 m3A;
    /* 0x3C */ s16 m3C;
    /* 0x3E */ s16 m3E;
    u8 m40[0x54 - 0x40];
    /* 0x54 */ s16 m54;
};

#endif /* D_A_MT_H */
